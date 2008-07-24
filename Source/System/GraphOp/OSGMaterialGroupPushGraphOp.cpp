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

#include "OSGMaterialGroupPushGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGAction.h"
#include "OSGMaterialDrawable.h"

#include <boost/bind.hpp>

/*! \class OSG::MaterialGroupPushGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry

    Moves the Materials form MaterialGroups to the MaterialDrawables below
    them and replaces the obsolete MaterialGroups with Groups.
*/

OSG_BEGIN_NAMESPACE

namespace
{
    static bool registerOp(void)
    {
        GraphOpFactory::the()->registerOp(new MaterialGroupPushGraphOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
} // namespace

const char *MaterialGroupPushGraphOp::getClassname(void)
{
    return "MaterialGroupPushGraphOp";
}

MaterialGroupPushGraphOp::MaterialGroupPushGraphOp(const char* name)
    : Inherited(name)
{
    // nothing to do
}

GraphOpTransitPtr MaterialGroupPushGraphOp::create(void)
{
    return GraphOpTransitPtr(new MaterialGroupPushGraphOp());
}

void MaterialGroupPushGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("MaterialGroupPushGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string MaterialGroupPushGraphOp::usage(void)
{
    return "MaterialGroupPush: Move Transform towards leafs of the scene.\n";
}


MaterialGroupPushGraphOp::~MaterialGroupPushGraphOp(void)
{
    // nothing to do
}


Action::ResultE MaterialGroupPushGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;

    return Action::Continue;
}

Action::ResultE MaterialGroupPushGraphOp::traverseLeave(
    Node * const node, Action::ResultE res)
{
    if(isInExcludeList(node))
        return Action::Skip;
    
    if(isInPreserveList(node))
        return Action::Continue;
    
    MaterialGroup *mg = dynamic_cast<MaterialGroup *>(node->getCore());
    
    if(mg == NULL)
        return Action::Continue;
    
    // if not a leaf, search children recursively to find push targets
    if(!node->getMFChildren()->empty())
    {
        _pushPossible = true;
        _pushTargets.clear();
        
        OSG::traverse(
            *(node->getMFChildren()),
            boost::bind(
                &MaterialGroupPushGraphOp::traverseTargetsEnter, this, _1));
        
        if(_pushPossible == true)
        {
            // push MaterialGroup into targets
            pushMaterialGroup(mg);
            
            // replace MaterialGroup with group
            GroupUnrecPtr replaceCore = Group::create();
            node->setCore(replaceCore);
        }
    }

    return Action::Continue;
}

/*! Find push targets in subtree.
 */
Action::ResultE MaterialGroupPushGraphOp::traverseTargetsEnter(Node * const node)
{
    NodeCore *core = node->getCore();
    
    if(core == NULL)
    {
        // warn about broken subtree, but do not prevent push, just skip it
        FWARNING(("MaterialGroupPushGraphOp::traverseTargetsEnter: "
                  "Found node without core!\n"));
        return Action::Skip;
    }
    
    if(isInExcludeList(node) || isInPreserveList(node))
    {
        // prevent the push as the mat group can not be moved into this branch.
        _pushPossible = false;
        
        return Action::Quit;
    }
    
    if(core->getType().isDerivedFrom(MaterialDrawable::getClassType()))
    {
        // found a push target in this branch, store it and stop searching
        _pushTargets.push_back(node);
        
        return Action::Skip;
    }
    
    if( core->getType().isDerivedFrom(Group        ::getClassType()) &&
       !core->getType().isDerivedFrom(MaterialGroup::getClassType())   )
    {
        // keep searching children for push targets
        return Action::Continue;
    }
    
    // unknown core type, be conservative and prevent the push
    _pushPossible = false;
    
    return Action::Quit;
}

void MaterialGroupPushGraphOp::pushMaterialGroup(MaterialGroup *mg)
{
    PushTargetStore::iterator ptIt  = _pushTargets.begin();
    PushTargetStore::iterator ptEnd = _pushTargets.end  ();
    
    for(; ptIt != ptEnd; ++ptIt)
    {
        MaterialDrawable *dstMD =
            dynamic_cast<MaterialDrawable *>((*ptIt)->getCore());
        if(dstMD != NULL)
        {
            dstMD->setMaterial(mg->getMaterial());
        }
    }
}


OSG_END_NAMESPACE
