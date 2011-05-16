/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

#include "OSGRootGroup.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGRootGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGRootGroup.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void RootGroup::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void RootGroup::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

RootGroup::RootGroup(void) :
    Inherited()
{
}

RootGroup::RootGroup(const RootGroup &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

RootGroup::~RootGroup(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Render                                     */

ActionBase::ResultE RootGroup::renderEnter(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    if(ra->pushVisibility() == true)
    {
        if(ra->selectVisibles() == 0)
        {
            ra->popVisibility();
            return Action::Skip;
        }
    }

    return ActionBase::Continue;
}

ActionBase::ResultE RootGroup::renderLeave(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    ra->popVisibility();
    
    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

ActionBase::ResultE RootGroup::intersect(Action *action)
{
          IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    const BoxVolume       &bv = ia->getActNode()->getVolume();
    
    if(bv.isValid() && ! bv.intersect(ia->getLine()))
    {
        return Action::Skip;  //bv missed -> can not hit children
    }
    
    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void RootGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);


    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault( 
            RootGroup::getClassType(),
            reinterpret_cast<Action::Callback>(&RootGroup::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            RootGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(&RootGroup::renderLeave));

        IntersectAction::registerEnterDefault( 
            getClassType(),
            reinterpret_cast<Action::Callback>(&RootGroup::intersect));
    }
}
