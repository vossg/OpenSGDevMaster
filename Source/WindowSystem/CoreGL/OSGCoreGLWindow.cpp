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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

// Forget everything if we're not doing a Mac OS X compile
#ifdef __APPLE__

#include "OSGCoreGLWindow.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CoreGLWindow
The class for MacOS X CoreGL windows.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CoreGLWindow::initMethod(InitPhase ePhase)
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

CoreGLWindow::CoreGLWindow(void) :
    Inherited()
{
}

CoreGLWindow::CoreGLWindow(const CoreGLWindow &source) :
    Inherited(source)
{
}

CoreGLWindow::~CoreGLWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CoreGLWindow::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CoreGLWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CoreGLWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! Init the window: create the context and setup the OpenGL.
*/
void CoreGLWindow::init(void)
{
    CGLSetCurrentContext(getContext());
    setupGL();
}

// activate the window: bind the OGL context
void CoreGLWindow::activate( void )
{
    CGLSetCurrentContext(getContext());
}

// activate the window: bind the OGL context
void CoreGLWindow::deactivate( void )
{
    CGLSetCurrentContext(0);
}

// swap front and back buffers
bool CoreGLWindow::swap( void )
{
    CGLFlushDrawable(getContext());
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h 403 2006-11-09 12:34:33Z PatrickDaehne $";
    static Char8 cvsid_hpp       [] = OSGCOREGLWINDOWBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOREGLWINDOWBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOREGLWINDOWFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

#endif // __APPLE__
