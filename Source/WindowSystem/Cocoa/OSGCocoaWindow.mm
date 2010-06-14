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

#import <Cocoa/Cocoa.h>
#import <AppKit/NSOpenGL.h>

#include "OSGCocoaWindow.h"
#include "OSGCocoaWindowWrapper.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCocoaWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCocoaWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CocoaWindow::initMethod(InitPhase ePhase)
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

CocoaWindow::CocoaWindow(void) :
    Inherited()
{
}

CocoaWindow::CocoaWindow(const CocoaWindow &source) :
    Inherited(source)
{
}

CocoaWindow::~CocoaWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CocoaWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CocoaWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CocoaWindow NI" << std::endl;
}

/*-------------------------- your_category---------------------------------*/

/*! Init the window: create the context and setup the OpenGL.
*/
void CocoaWindow::init(GLInitFunctor oFunc)
{
    Inherited::init(oFunc);
}

void CocoaWindow::terminate(void)
{
}

// activate the window: bind the OGL context
void CocoaWindow::doActivate(void)
{
    [this->getContext() makeCurrentContext];
}

// activate the window: bind the OGL context
void CocoaWindow::doDeactivate(void)
{
    [NSOpenGLContext clearCurrentContext];
}

// swap front and back buffers
bool CocoaWindow::doSwap(void)
{
    [this->getContext() flushBuffer];

    return true;
}

bool CocoaWindow::hasContext(void)
{
    return (this->getContext() != NULL);
}

OSG_END_NAMESPACE

#endif // __APPLE__
