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

#ifndef WIN32
#include <QtGui/qx11info_x11.h>
#include <GL/glx.h>
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


/*-------------------------- Window functions ---------------------------------*/


//! init the window: create the context
void QT4Window::init(GLInitFunctor oFunc)
{
#ifdef WIN32
    if(getGlWidget() != NULL)
    {
        setHwnd(getGlWidget()->winId());

        Inherited::init();
    }
#else
    XVisualInfo *vi;

    ///// create a new GLX context
    setDisplay(XOpenDisplay(NULL));
    setWindow(static_cast<QWidget*>(getGlWidget())->winId());

    // get the existing glWidget's visual-id and a visual for the new context
    XVisualInfo visInfo;
    memset(&visInfo, 0, sizeof(XVisualInfo));
    visInfo.visualid = XVisualIDFromVisual(
        static_cast<Visual*>(QX11Info::appVisual()));
    int nvis;
    vi = XGetVisualInfo( getDisplay(), VisualIDMask, &visInfo, &nvis );

    // is the visual GL-capable ?
    int useGL;
    glXGetConfig( getDisplay(),
                  vi,
                  GLX_USE_GL,
                  &useGL );
    if (!useGL)
    {
        SFATAL << "Visual is not OpenGL-capable!" << endLog;
    }

    // create the new context
    setContext(glXCreateContext(getDisplay(), vi, None, GL_TRUE));
#endif

    Window::init(oFunc);
}

OSG_END_NAMESPACE
