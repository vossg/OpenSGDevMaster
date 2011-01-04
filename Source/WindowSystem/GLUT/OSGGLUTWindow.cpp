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

#include "OSGConfig.h"

#if defined(OSG_WITH_GLUT) || defined(OSG_DO_DOC)

#define OSG_COMPILEWINDOWGLUTINST

#include "OSGGLUTWindow.h"

#include "OSGGLUT.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGGLUTWindow.h"
#include "OSGRenderActionBase.h"
#include "OSGRenderActionTask.h"

#ifdef OSG_USE_GLX
#include <GL/glx.h>
#endif
#ifdef __APPLE__
#include "OSGCocoaWindowWrapper.h"
#endif

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGGLUTWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGGLUTWindow.fcd) and
// regenerate the base file.

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
GLUTWindow::GLUTWindow(void) :
    Inherited()
{
    _sfDrawMode.setValue(
        (_sfDrawMode.getValue()  & ~Window::ContextMask) | 
        (Window::ExternalContext &  Window::ContextMask) );
}

//! Copy Constructor
GLUTWindow::GLUTWindow(const GLUTWindow &source) :
    Inherited(source)
{
    _sfDrawMode.setValue(
        (_sfDrawMode.getValue()  & ~Window::ContextMask) | 
        (Window::ExternalContext &  Window::ContextMask) );
}

//! Destructor
GLUTWindow::~GLUTWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void GLUTWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

//! react to field changes
void GLUTWindow::changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes

void GLUTWindow::dump(      UInt32    , 
                      const BitVector ) const
{
    SLOG << "Dump GLUTWindow NI" << std::endl;
}
    
/* ------------- Window functions -----------------------*/    
    
// init the window: create the context  
void GLUTWindow::init(GLInitFunctor oFunc)
{
#if defined(WIN32)
    Inherited::setHdc  (wglGetCurrentDC     ());
    Inherited::setHglrc(wglGetCurrentContext());
    Inherited::setHwnd (WindowFromDC(Inherited::getHdc()));
#elif defined(__APPLE__)
    Inherited::setContext(cocoaWrapperCurrentContext());
#else
    glutSetWindow(getGlutId());

    Inherited::setDisplay(glXGetCurrentDisplay ());
    Inherited::setContext(glXGetCurrentContext ());
    Inherited::setWindow (glXGetCurrentDrawable());
#endif
    this->doDeactivate();

    Window::init(oFunc);
}
    
void GLUTWindow::activate(void)
{
    if((_sfDrawMode.getValue() & PartitionDrawMask) == SequentialPartitionDraw)
    {
        if(glutGetWindow() != getGlutId())
            glutSetWindow(getGlutId());

        Inherited::doActivate();
    }
}

void GLUTWindow::terminate(void)
{
    Window::doTerminate();

    Inherited::setContext(NULL);
}

OSG_END_NAMESPACE

#endif // OSG_WITH_GLUT

