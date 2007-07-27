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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

// Forget everything if we're not doing a windows compile
#ifdef OSG_USE_EGL

#include "OSGEGLWindow.h"

#include "gles/egl.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGEGLWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGEGLWindow.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

EGLWindow::EGLWindow(void) :
    Inherited()
{
}

//! Copy Constructor

EGLWindow::EGLWindow(const EGLWindow &source) :
    Inherited(source)
{
}

//! Destructor

EGLWindow::~EGLWindow(void)
{
#if 0
    if(getHglrc() != NULL)
        wglDeleteContext(getHglrc());
#endif
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void EGLWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes

void EGLWindow::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes

void EGLWindow::dump(      UInt32    , 
                     const BitVector ) const
{
    SLOG << "Dump EGLWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! init the window: create the HDC and HGLRC
*/
void EGLWindow::init( void )
{
    activate();
    setupGL();
}

/*! activate the window: set the HDC and bind the OGL context
*/
void EGLWindow::activate(void)
{    
    if(!eglMakeCurrent(getDisplay(), getWindow(), getWindow(), getContext()))
    {
/*
        std::cerr << "EGLWindow::activate: failed: "
                  << GetLastError() 
                  << std::endl;        
*/
    }
}

void EGLWindow::deactivate(void)
{
    eglMakeCurrent(getDisplay(), 
                   EGL_NO_SURFACE, 
                   EGL_NO_SURFACE, 
                   EGL_NO_CONTEXT);
}

// swap front and back buffers
bool EGLWindow::swap( void )
{
    return eglSwapBuffers(getDisplay(), getWindow());
}

#endif // OSG_USE_EGL
