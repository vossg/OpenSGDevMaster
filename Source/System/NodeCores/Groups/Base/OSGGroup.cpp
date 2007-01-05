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

#include <OSGRenderAction.h>
#ifndef OSG_WINCE
#include <OSGIntersectAction.h>
#endif

#include "OSGGroup.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGGroup.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Group::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
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

    ra->pushVisibility();
    
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

#ifndef OSG_WINCE
ActionBase::ResultE Group::intersect(Action *action)
{
          IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    const DynamicVolume   &dv = ia->getActNode()->getVolume();
    
    if(dv.isValid() && ! dv.intersect(ia->getLine()))
    {
        return Action::Skip;  //bv missed -> can not hit children
    }
    
    return ActionBase::Continue;
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Group::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);


    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(&Group::renderEnter));

        RenderAction::registerLeaveDefault( 
            getClassType(),
            reinterpret_cast<Action::Callback>(&Group::renderLeave));
        
#ifndef OSG_WINCE
        IntersectAction::registerEnterDefault( 
            getClassType(),
            reinterpret_cast<Action::Callback>(&Group::intersect));
#endif
    }
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGGROUP_INLINE_CVSID;
}





