/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGPassiveWindow.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PassiveWindow
    \ingroup GrpSystemWindowPassive

A PassiveWindow is a Window class for integration into other OpenGL
programs. See \ref PageSystemWindowWindowPassive for a description.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PassiveWindow::initMethod (InitPhase ePhase)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PassiveWindow::PassiveWindow(void) :
    Inherited()
{
}

PassiveWindow::PassiveWindow(const PassiveWindow &source) :
    Inherited(source)
{
}

PassiveWindow::~PassiveWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PassiveWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PassiveWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PassiveWindow NI" << std::endl;
}

/*! Just call the standard OpenGL setup.
*/
void PassiveWindow::init( void )
{
    setupGL();
}

/* Do nothing, has to be setup when we come here.
*/
void PassiveWindow::activate( void )
{
}
    
/* Do nothing, has to be done manually for this class.
*/
bool PassiveWindow::swap( void )
{
    return true;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPassiveWindow.cpp,v 1.1.2.2 2006/08/01 07:54:18 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGPASSIVEWINDOWBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPASSIVEWINDOWBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPASSIVEWINDOWFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

