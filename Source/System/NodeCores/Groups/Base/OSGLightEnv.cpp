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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGRenderAction.h>
#include "OSGLightEnv.h"

OSG_USING_NAMESPACE


/*-------------------------------------------------------------------------*/
/*                             Sync                                     */

void LightEnv::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void LightEnv::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

LightEnv::LightEnv(void) :
     Inherited()
{
}

LightEnv::LightEnv(const LightEnv &source) :
     Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

LightEnv::~LightEnv(void)
{
}


/*-------------------------------------------------------------------------*/
/*                               Init                                      */

//! initialize the static features of the class, e.g. action callbacks

void LightEnv::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        typedef ActionBase::ResultE (LightEnv::*Callback)(Action *);

        Callback enter = &LightEnv::renderEnter<RenderAction>;
        Callback leave = &LightEnv::renderLeave<RenderAction>;

        RenderAction::registerEnterDefault(
            getClassType(), 
            reinterpret_cast<Action::Callback>(enter));
        
        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(leave));
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
    static Char8 cvsid_hpp[] = OSGLIGHTENV_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGLIGHTENV_INLINE_CVSID;
}
