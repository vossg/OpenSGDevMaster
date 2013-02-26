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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#define OSG_COMPILEWINDOWQTINST

#include "OSGQT4Window.h"

#ifdef OSG_USE_GLX
# if defined(OSG_USE_OGL3_PROTOS) || defined(OSG_USE_OGL4_PROTOS)
//#  include <GL3/glx3.h>
#  include <GLArb/glxarb.h>
# else
#  include <GL/glx.h>
# endif
#endif
#if defined(__APPLE__) && !OSG_APPLE_IOS
#include "OSGCocoaWindowWrapper.h"
#endif


OSG_BEGIN_NAMESPACE

/*! \class OSG::QT4Window

The class for QT-based windows. See \ref PageWindowQt4 for a description.

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
QT4Window::QT4Window(void) :
    Inherited()
{
}

//! Copy Constructor
QT4Window::QT4Window(const QT4Window &source) :
    Inherited(source)
{
}

//! Destructor
QT4Window::~QT4Window(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! test QT versions, give a warning 

bool qtVersionCheckWrapper(void)
{
    if(strcmp(qVersion(), QT_VERSION_STR))
    {
        FWARNING(("WindowQTLib was compiled against QT version %s, but "
                  "the application is using %s!", QT_VERSION_STR, qVersion()));
        FWARNING(("This might result in problems. It usually doesn't, but be"
                  " warned."));
    }
    return true;
}

static StaticInitFuncWrapper qtVersionCheck(qtVersionCheckWrapper);

//! initialize the static features of the class, e.g. action callbacks

void QT4Window::initMethod (InitPhase ePhase)
{
    //Inherited::initMethod(ePhase);
}

//! react to field changes
void QT4Window::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

//! output the instance for debug purposes

void QT4Window::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump QTWindow NI" << std::endl;
}


/*------------------------- Window functions -------------------------------*/


//! init the window: create the context
void QT4Window::init(GLInitFunctor oFunc)
{
    if(_sfPrivateOSGContext.getValue() == true)
    {
        if(getGlWidget() != NULL)
        {
            getGlWidget()->doMakeCurrent();
        }

#if defined(WIN32)
        if(getGlWidget() != NULL)
        {
            setHwnd(HWND(getGlWidget()->winId()));
        }

        Inherited::setHdc(wglGetCurrentDC());
#elif defined(__APPLE__) && !OSG_APPLE_IOS
        Inherited::setContext(cocoaWrapperCurrentContext());
#elif defined(__APPLE__) && OSG_APPLE_IOS
#else
        Inherited::setDisplay(glXGetCurrentDisplay ());
        Inherited::setWindow (glXGetCurrentDrawable());
#endif

        if(getGlWidget() != NULL)
        {
            getGlWidget()->doDoneCurrent();
        }

        Inherited::init(oFunc);
    }
    else
    {
        Window::init(oFunc);
    }
}

void QT4Window::doActivate(void)
{
    if(_sfPrivateOSGContext.getValue() == true)
    {
        Inherited::doActivate();
    }
    else
    {
        if(getGlWidget() != NULL)
        {
            getGlWidget()->doMakeCurrent();
        }
    }
}

void QT4Window::doDeactivate(void)
{
    if(_sfPrivateOSGContext.getValue() == true)
    {
        Inherited::doDeactivate();
    }
    else
    {
        if(getGlWidget() != NULL)
        {
            getGlWidget()->doDoneCurrent();
        }
    }
}

bool QT4Window::doSwap(void)
{
    if(_sfPrivateOSGContext.getValue() == true)
    {
        Inherited::doSwap();
    }
    else
    {
        if(getGlWidget() != NULL)
        {
            getGlWidget()->doSwapBuffers();
            
            return true;
        }
    }

    return false;
}

OSG_END_NAMESPACE
