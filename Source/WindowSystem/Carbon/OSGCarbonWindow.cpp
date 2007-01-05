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

// Forget everything if we're not doing a Mac OS X compile
#ifdef __APPLE__

#include "OSGCarbonWindow.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CarbonWindow
The class for MacOS X Carbon windows.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CarbonWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CarbonWindow::CarbonWindow(void) :
    Inherited()
{
}

CarbonWindow::CarbonWindow(const CarbonWindow &source) :
    Inherited(source)
{
}

CarbonWindow::~CarbonWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CarbonWindow::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CarbonWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CarbonWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! Init the window: create the context and setup the OpenGL.
*/
void CarbonWindow::init(void)
{
    aglSetCurrentContext(getContext());
    setupGL();
}

// activate the window: bind the OGL context
void CarbonWindow::activate( void )
{
    aglSetCurrentContext(getContext());
}

// activate the window: bind the OGL context
void CarbonWindow::deactivate( void )
{
    aglSetCurrentContext(0);
}

// swap front and back buffers
bool CarbonWindow::swap( void )
{
    aglSwapBuffers(getContext());
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h 106 2006-09-14 03:15:53Z dirk $";
    static Char8 cvsid_hpp       [] = OSGCARBONWINDOWBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCARBONWINDOWBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCARBONWINDOWFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

#endif // __APPLE__
