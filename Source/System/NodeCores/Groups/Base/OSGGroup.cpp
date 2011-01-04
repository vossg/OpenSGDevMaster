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

#include "OSGGroup.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGGroup.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Group::changed(ConstFieldMaskArg whichField, 
                    UInt32            origin,
                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Group::dump(      UInt32    uiIndent, 
                 const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Group::Group(void) :
    Inherited()
{
}

Group::Group(const Group &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Group::~Group(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Render                                     */

ActionBase::ResultE Group::renderEnter(Action *action)
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

ActionBase::ResultE Group::renderLeave(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    ra->popVisibility();
    
    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

ActionBase::ResultE Group::intersect(Action *action)
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

void Group::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);


    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault( 
            Group::getClassType(),
            reinterpret_cast<Action::Callback>(&Group::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            Group::getClassType(), 
            reinterpret_cast<Action::Callback>(&Group::renderLeave));

        IntersectAction::registerEnterDefault( 
            getClassType(),
            reinterpret_cast<Action::Callback>(&Group::intersect));
    }
}
