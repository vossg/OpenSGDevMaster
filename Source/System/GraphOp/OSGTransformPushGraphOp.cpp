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

#include "OSGTransformPushGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGAction.h"

#include <set>

#include <boost/bind.hpp>

/*! \class OSG::TransformPushGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry

    Attempts to move Tranforms towards the leafs of the scene, by either
    combining adjacent ones or applying the Transform to Geometry.
    
    It traverses the scene and when it encounters a Transform searches its
    children recursively for push targets (other Transforms or Geometry). If
    push targets can be found in each child's subtree, the current Transform is
    pushed to the targets and replaced by a Group.
    Pushing can fail if in a branch of one child's subtree no suitable push
    target is found. This can be the case if a Node that is in the exclude or
    preserve list is found or if the type of Core of a Node is recognized as a
    push barrier (e.g. Switch, LODs).
*/

OSG_BEGIN_NAMESPACE

namespace
{
    static bool registerOp(void)
    {
        GraphOpFactory::the()->registerOp(new TransformPushGraphOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
} // namespace

const char *TransformPushGraphOp::getClassname(void)
{
    return "TransformPushGraphOp";
}

TransformPushGraphOp::TransformPushGraphOp(const char* name)
    : Inherited(name)
{
    // nothing to do
}

GraphOpTransitPtr TransformPushGraphOp::create(void)
{
    return GraphOpTransitPtr(new TransformPushGraphOp());
}

void TransformPushGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("TransformPushGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string TransformPushGraphOp::usage(void)
{
    return "TransformPush: Move Transform towards leafs of the scene.\n";
}


TransformPushGraphOp::~TransformPushGraphOp(void)
{
    // nothing to do
}


Action::ResultE TransformPushGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;

    return Action::Continue;
}

Action::ResultE TransformPushGraphOp::traverseLeave(
    Node * const node, Action::ResultE res)
{
    if(isInExcludeList(node))
        return Action::Skip;
    
    if(isInPreserveList(node))
        return Action::Continue;
    
    Transform *trans = dynamic_cast<Transform *>(node->getCore());
    
    if(trans == NULL)
        return Action::Continue;
    
    // if not a leaf, search children recursively to find push targets
    if(!node->getMFChildren()->empty())
    {
        _pushPossible = true;
        _pushTargets.clear();
        
        OSG::traverse(
                      *(node->getMFChildren()),
                        boost::bind(&TransformPushGraphOp::traverseTargetsEnter, this, _1));
        
        if(_pushPossible == true)
        {
            // push transform into targets
            pushTransform(trans);
            
            // replace transform with group
            GroupUnrecPtr replaceCore = Group::create();
            node->setCore(replaceCore);
        }
    }

    return Action::Continue;
}

/*! Find push targets in subtree.
 */
Action::ResultE TransformPushGraphOp::traverseTargetsEnter(Node * const node)
{
    NodeCore *core = node->getCore();
    
    if(core == NULL)
    {
        // warn about broken subtree, but do not prevent push, just skip it
        FWARNING(("TransformPushGraphOp::traverseTargetsEnter: "
                  "Found node without core!\n"));
        return Action::Skip;
    }
    
    if(isInExcludeList(node) || isInPreserveList(node))
    {
        // prevent the push as the transform can not be moved into this branch.
        _pushPossible = false;
        
        return Action::Quit;
    }
    
    if(core->getType().isDerivedFrom(Transform::getClassType()))
    {
        _pushTargets.push_back(node);
        
        return Action::Skip;
    }
       
    if(core->getType().isDerivedFrom(Geometry ::getClassType()))
    {
        Geometry *geo = dynamic_cast<Geometry *>(core);
        
        if(geo != NULL && validTargetGeo(geo))
        {
            // found a push target in this branch, store it and stop searching
            _pushTargets.push_back(node);
        
            return Action::Skip;
        }
        else
        {
            // prevent the push as the transform can not be moved into this branch.
            _pushPossible = false;
        
            return Action::Quit;
        }
    }
    
    if(core->getType().isDerivedFrom(Group::getClassType()))
    {
        // keep searching children for push targets
        return Action::Continue;
    }
    
    // unknown core type, be conservative and prevent the push
    _pushPossible = false;
    
    return Action::Quit;
}

/*! Checks if the geometry has shared properties.
 */
bool TransformPushGraphOp::validTargetGeo(const Geometry *geo)
{
    bool returnValue = true;
    
    const Geometry::MFPropertiesType           *mfProp  =
        geo->getMFProperties ();
    Geometry::MFPropertiesType::const_iterator  propIt  = mfProp->begin();
    Geometry::MFPropertiesType::const_iterator  propEnd = mfProp->end  ();
    
    for(; propIt != propEnd; ++propIt)
    {
        if(*propIt != NULL && (*propIt)->getMFParents()->size() > 1)
        {
            returnValue = false;
            break;
        }
    }
    
    return returnValue;
}

void TransformPushGraphOp::pushTransform(const Transform *srcTrans)
{
    PushTargetStore::iterator ptIt  = _pushTargets.begin();
    PushTargetStore::iterator ptEnd = _pushTargets.end  ();
    
    for(; ptIt != ptEnd; ++ptIt)
    {
        Transform *dstTrans = dynamic_cast<Transform *>((*ptIt)->getCore());
        if(dstTrans != NULL)
        {
            pushToTransform(srcTrans, dstTrans);
            continue;
        }
        
        Geometry *dstGeo = dynamic_cast<Geometry *>((*ptIt)->getCore());
        if(dstGeo != NULL)
        {
            pushToGeometry(srcTrans, dstGeo);
            continue;
        }
        
        // should not happen
        FWARNING(("TransformPushGraphOp::pushTransform: Unhandled push target"
                  " type [%s]\n", (*ptIt)->getType().getCName()));
    }
}

/*! Push \a srcTrans into \a dstTrans
 */
void TransformPushGraphOp::pushToTransform(
    const Transform *srcTrans, Transform *dstTrans)
{
    dstTrans->editMatrix().multLeft(srcTrans->getMatrix());
}

/*! Push \a srcTrans into \a dstGeo
 */
void TransformPushGraphOp::pushToGeometry(
    const Transform *srcTrans, Geometry *dstGeo)
{
    typedef Vec4f  VecType;
    typedef Pnt3f  PntType;
    
    Matrix mat    = srcTrans->getMatrix();
    Matrix invMat;
    invMat.invertFrom(mat);
    
    const Geometry::SFLengthsType     *sfLen  = dstGeo->getSFLengths     ();
          Geometry::MFPropertiesType  *mfProp = dstGeo->editMFProperties ();
          Geometry::MFPropIndicesType *mfInd  = dstGeo->editMFPropIndices();
    
    Geometry::MFPropertiesType::const_iterator  propIt  = mfProp->begin();
    Geometry::MFPropertiesType::const_iterator  propEnd = mfProp->end  ();
    
    Geometry::MFPropIndicesType::const_iterator indIt   = mfInd ->begin();
    Geometry::MFPropIndicesType::const_iterator indEnd  = mfInd ->end  ();
    
    UInt32 propUsed = 0;
    for(UInt32 i = 0; i < sfLen->getValue()->size(); ++i)
        propUsed += sfLen->getValue()->getValue<UInt32>(i);
    
    for(; propIt != propEnd && indIt != indEnd; ++propIt, ++indIt)
    {
              GeoVectorProperty   *prop = *propIt;
        const GeoIntegralProperty *ind  = *indIt;
        
        if(prop == NULL)
            continue;
        
        if(ind == NULL)
        {
            // unindexed
            if((prop->getUsage() & GeoProperty::UsageObjectSpace) != 0x0000)
            {
                // transform with mat
                for(UInt32 i = 0; i < propUsed; ++i)
                {
                    PntType pnt = prop->getValue<PntType>(i);
                    mat.multFull(pnt, pnt);
                    prop->setValue(pnt, i);
                }
            }
            else if((prop->getUsage() & GeoProperty::UsageTangentSpace) != 0x0000)
            {
                // transform with invMat
                for(UInt32 i = 0; i < propUsed; ++i)
                {
                    VecType vec = prop->getValue<VecType>(i);
                    invMat.mult(vec, vec);
                    prop->setValue(vec, i);
                }
            }
        }
        else
        {
            std::set<UInt32> transInd;
            
            if((prop->getUsage() & GeoProperty::UsageObjectSpace) != 0x0000)
            {
                // transform with mat
                for(UInt32 i = 0; i < propUsed; ++i)
                {
                    UInt32 j = ind->getValue(i);
                    
                    if(transInd.find(j) == transInd.end())
                    {
                        PntType pnt = prop->getValue<PntType>(j);
                        mat.multFull(pnt, pnt);
                        prop->setValue(pnt, j);
                        
                        transInd.insert(j);
                    }
                }
            }
            else if((prop->getUsage() & GeoProperty::UsageTangentSpace) != 0x0000)
            {
                // transform with invMat
                for(UInt32 i = 0; i < propUsed; ++i)
                {
                    UInt32 j = ind->getValue(i);
                    
                    if(transInd.find(j) == transInd.end())
                    {
                        VecType vec = prop->getValue<VecType>(j);
                        invMat.mult(vec, vec);
                        prop->setValue(vec, j);
                        
                        transInd.insert(j);
                    }
                }
            }
        }
    }
}


OSG_END_NAMESPACE
