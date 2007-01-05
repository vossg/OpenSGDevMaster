/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>
#include <OSGRenderTraversalAction.h>

#include "OSGScreenLOD.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGScreenLODBase.cpp file.
// To modify it, please change the .fcd file (OSGScreenLOD.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScreenLOD::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        typedef ActionBase::ResultE (ScreenLOD::*Callback)(Action *);

        Callback enter = &ScreenLOD::render<RenderTraversalAction>;

        RenderTraversalAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(enter));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScreenLOD::ScreenLOD(void) :
    Inherited()
{
}

ScreenLOD::ScreenLOD(const ScreenLOD &source) :
    Inherited(source)
{
}

ScreenLOD::~ScreenLOD(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScreenLOD::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ScreenLOD::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScreenLOD NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h 106 2006-09-14 03:15:53Z dirk $";
    static Char8 cvsid_hpp       [] = OSGSCREENLODBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCREENLODBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCREENLODFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

