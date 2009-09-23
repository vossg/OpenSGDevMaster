/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include "OSGGeometryMergeGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGGroup.h"

#include "OSGDistanceLOD.h"
#include "OSGScreenLOD.h"
#include "OSGSwitch.h"
#include "OSGMultiCore.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGFieldContainerUtils.h"

/*! \class OSG::TransformPushGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    Finds Geometries that are siblings to each other and attempts to merge
    them into a smaller number of Geometries (preferably just one).

    The Geometry children of a node are checked whether they can be merged and
    and those that can are stored in groups. Then all members of each group
    are merged into a single geometry that is added as a child to the current
    node, while the members of the group are removed.
*/

OSG_BEGIN_NAMESPACE

namespace
{
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = GeometryMergeGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
} // namespace


const char *GeometryMergeGraphOp::getClassname(void)
{
    return "GeometryMergeGraphOp";
}

GeometryMergeGraphOp::GeometryMergeGraphOp(const char* name)
    : Inherited      (name),
      _mergeThreshold(200)
{
    // nothing to do
}

GeometryMergeGraphOpTransitPtr
GeometryMergeGraphOp::create(void)
{
    return GeometryMergeGraphOpTransitPtr(new GeometryMergeGraphOp);
}

GraphOpTransitPtr GeometryMergeGraphOp::clone(void)
{
    return GraphOpTransitPtr(new GeometryMergeGraphOp);
}

void GeometryMergeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);
    
    ps("mergeThreshold", _mergeThreshold);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("GeometryMergeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string GeometryMergeGraphOp::usage(void)
{
    return
    "GeometryMerge: Combine sibling Geometries.\n"
    "Params: name (type, default)\n"
    "  mergeThreshold (UInt32, 200): Maximum number of geometries to merge\n"
    "    into one new geometry. If there are more candidates to merge, they\n"
    "    are combined into more than one geometry.\n"
    ;
}


GeometryMergeGraphOp::~GeometryMergeGraphOp(void)
{
    // nothing to do
}

Action::ResultE GeometryMergeGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;
    
    return Action::Continue;
}

Action::ResultE GeometryMergeGraphOp::traverseLeave(
        Node * const node, Action::ResultE res)
{
    if(isInExcludeList(node))
        return Action::Skip;

    NodeCore *core = node->getCore();
    
    // skip cores with a dependency on the children number/order
    // TODO: find a way to make this extendable
    if(core == NULL                                               ||
       core->getType().isDerivedFrom(DistanceLOD::getClassType()) ||
       core->getType().isDerivedFrom(ScreenLOD  ::getClassType()) ||
       core->getType().isDerivedFrom(Switch     ::getClassType()) ||
       core->getType().isDerivedFrom(MultiCore  ::getClassType())   )
    {
        return Action::Continue;
    }
    
    typedef std::vector<NodeUnrecPtr> NodeStore;
    NodeStore addStore;     // nodes to add as children to current one
    NodeStore subStore;     // nodes (children) to remove from current one
    
    typedef std::vector<Node *    > MergeGroup; // geometries that can be merged
    typedef std::vector<MergeGroup> MergeList;  // list of merge groups
    
    MergeList                            ml;
    Node::MFChildrenType::const_iterator childIt  =
            node->getMFChildren()->begin();
    Node::MFChildrenType::const_iterator childEnd =
            node->getMFChildren()->end  ();
    
    // group geometry children that are mergeable
    for(; childIt != childEnd; ++childIt)
    {
        if((*childIt)->getCore()->getType() != Geometry::getClassType())
            continue;
        
        if(isInExcludeList(*childIt) || isInPreserveList(*childIt))
            continue;
        
        Geometry *geo = dynamic_cast<Geometry *>((*childIt)->getCore());
        Material *mat = geo->getMaterial();
        
        MergeList::iterator mlIt  = ml.begin();
        MergeList::iterator mlEnd = ml.end  ();
        
        bool done = false;
        
        for(; mlIt != mlEnd && !done; ++mlIt)
        {
            Geometry *mlGeo =
                    dynamic_cast<Geometry *>(mlIt->front()->getCore());
            Material *mlMat = mlGeo->getMaterial();
            
            if(compareContainerEqual(mlMat, mat) &&
               mergeableGeo         (mlGeo, geo)   )
            {
                mlIt->push_back(*childIt);
                done = true;
            }
        }
        
        if(!done)
        {
            ml       .push_back(MergeGroup());
            ml.back().push_back(*childIt    );
        }
    }
    
    // merge geometry in the same group and replace obsolete children with
    // new geometry
    MergeList::iterator mlIt  = ml.begin();
    MergeList::iterator mlEnd = ml.end  ();
    
    for(; mlIt != mlEnd; ++mlIt)
    {
        // only one geometry in merge group -> nothing to do
        if(mlIt->size() <= 1)
            continue;
        
        FINFO(("GeometryMergeGraphOp::traverseLeave: Merging [%zd] "
               "Geometries.\n", mlIt->size()));
        
        GeometryUnrecPtr     geo1;
        GeometryUnrecPtr     geo2;
        NodeUnrecPtr         newNode = Node::create();
        MergeGroup::iterator mgIt    = mlIt->begin();
        MergeGroup::iterator mgEnd   = mlIt->end  ();
        
        geo1 = dynamic_cast<Geometry *>((*mgIt)->getCore());
        ++mgIt;
        
        for(UInt32 i = 0; mgIt != mgEnd; ++mgIt, ++i)
        {
            geo2 = dynamic_cast<Geometry *>((*mgIt)->getCore());
            
            if(i > _mergeThreshold && (mgIt + 1) != mgEnd)
            {
                newNode->setCore(geo1);
                addStore.push_back(newNode);
                
                i       = 0;
                newNode = Node::create();
                geo1    = dynamic_cast<Geometry *>((*mgIt)->getCore());
                ++mgIt;
            }
            
            geo1 = mergeGeo(geo1, geo2);
            geo1->setMaterial(geo2->getMaterial());
            
            subStore.push_back(*mgIt);
        }
        
       newNode->setCore(geo1);
       addStore.push_back(newNode);
    }
    
    // add newly created geometries to current node
    NodeStore::const_iterator storeIt  = subStore.begin();
    NodeStore::const_iterator storeEnd = subStore.end  ();
    
    for(; storeIt != storeEnd; ++storeIt)
       node->subChild(*storeIt);
    
    storeIt  = addStore.begin();
    storeEnd = addStore.end  ();
    
    for(; storeIt != storeEnd; ++storeIt)
       node->addChild(*storeIt);
    
    return Action::Continue;
}

OSG_END_NAMESPACE
