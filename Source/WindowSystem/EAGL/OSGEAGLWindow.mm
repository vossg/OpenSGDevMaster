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

#include "OSGConfig.h"

// Forget everything if we're not doing a Mac OS X compile
#ifdef __APPLE__

//#import <Cocoa/Cocoa.h>
//#import <AppKit/NSOpenGL.h>

#include "OSGEAGLWindow.h"
#include "OSGEAGLWindowWrapper.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGEAGLWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGEAGLWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void EAGLWindow::initMethod(InitPhase ePhase)
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

EAGLWindow::EAGLWindow(void) :
    Inherited()
{
}

EAGLWindow::EAGLWindow(const EAGLWindow &source) :
    Inherited(source)
{
}

EAGLWindow::~EAGLWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void EAGLWindow::changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void EAGLWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump EAGLWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! Init the window: create the context and setup the OpenGL.
*/
void EAGLWindow::init(GLInitFunctor oFunc)
{
    Inherited::init(oFunc);
}

void EAGLWindow::terminate(void)
{
}

// activate the window: bind the OGL context
void EAGLWindow::doActivate(void)
{
//    [this->getContext() makeCurrentContext];
}

// activate the window: bind the OGL context
void EAGLWindow::doDeactivate(void)
{
//    [EAGLContext clearCurrentContext];
}

// swap front and back buffers
bool EAGLWindow::doSwap(void)
{
//    [this->getContext() flushBuffer];

    return true;
}

bool EAGLWindow::hasContext(void)
{
//    return (this->getContext() != NULL);

    return true;
}

OSG_END_NAMESPACE

#endif // __APPLE__
