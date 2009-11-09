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

#ifdef OSG_WITH_GLUT

#define OSG_COMPILEWINDOWGLUTINST

#include "OSGGLUTWindow.h"

#include "OSGGLUT.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGGLUTWindow.h"

#ifdef OSG_USE_GLX
#include <GL/glx.h>
#endif
#ifdef __APPLE__
#include <AGL/agl.h>
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
}

//! Copy Constructor
GLUTWindow::GLUTWindow(const GLUTWindow &source) :
    Inherited(source)
{
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
    glutSetWindow(getGlutId());

    Inherited::setContext(aglGetCurrentContext());
#else
    glutSetWindow(getGlutId());

    Inherited::setDisplay(glXGetCurrentDisplay ());
    Inherited::setContext(glXGetCurrentContext ());
    Inherited::setWindow (glXGetCurrentDrawable());
#endif

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

namespace glut
{
#define OSG_DO_GLUT_INIT()                  \
    if(pGWin != NULL)                       \
    {                                       \
        GLint glvp[4];                      \
                                            \
        glGetIntegerv(GL_VIEWPORT, glvp);   \
                                            \
        pGWin->setSize  (glvp[2], glvp[3]); \
                                            \
        pGWin->init();                      \
                                            \
        pGWin = NULL;                       \
                                            \
    }

    static glutUCIIFunc gKeyFunc     = NULL;
    static glutIFunc    gVisFunc     = NULL;
    static glutIIFunc   gReshapeFunc = NULL;
    static glutVFunc    gDisplayFunc = NULL;
    static glutIIIIFunc gMouseFunc   = NULL;
    static glutIIFunc   gMotionFunc  = NULL;
    static glutVFunc    gIdleFunc    = NULL;

    static int                winid  = 0;
    static GLUTWindowUnrecPtr pGWin  = NULL;

    static void key_internal(unsigned char key, int x, int y)
    {
        gKeyFunc(key, x, y);
    }

    static void vis_internal(int i)
    {
        gVisFunc(i);
    }

    static void reshape_internal(int w, int h)
    {
        OSG_DO_GLUT_INIT();

        gReshapeFunc(w, h);
    }

    static void display_internal(void)
    {
        OSG_DO_GLUT_INIT();

        gDisplayFunc();
    }

    static void mouse_internal(int button, int state, int x, int y)
    {
        gMouseFunc(button, state, x, y);
    }

    static void motion_internal(int x, int y)
    {
        gMotionFunc(x, y);
    }

    static void idle_internal(void)
    {
        OSG_DO_GLUT_INIT();

        gIdleFunc();
    }

    void init(int argc, char **argv)
    {
        ::glutInit(&argc, argv);
    }

    void initDisplayMode(unsigned int uiMode)
    {
        ::glutInitDisplayMode(uiMode);
    }

    int createWindow(const char *szName)
    {
        winid = ::glutCreateWindow(szName);

        return winid;
    }

    
    void keyboardFunc  (glutUCIIFunc keyFunc    )
    {
        OSG_ASSERT(keyFunc != NULL);

        gKeyFunc = keyFunc;

        ::glutKeyboardFunc(key_internal);
    }

    void visibilityFunc(glutIFunc    visFunc    )
    {
        OSG_ASSERT(visFunc != NULL);

        gVisFunc = visFunc;

        ::glutVisibilityFunc(vis_internal);
    }

    void reshapeFunc   (glutIIFunc   reshapeFunc)
    {
        OSG_ASSERT(reshapeFunc != NULL);

        gReshapeFunc = reshapeFunc;

        ::glutReshapeFunc(reshape_internal);
    }

    void displayFunc   (glutVFunc    displayFunc)
    {
        OSG_ASSERT(displayFunc != NULL);

        gDisplayFunc = displayFunc;

        ::glutDisplayFunc(display_internal);
    }
   
    void mouseFunc     (glutIIIIFunc mouseFunc  )
    {
        OSG_ASSERT(mouseFunc != NULL);

        gMouseFunc = mouseFunc;

        ::glutMouseFunc(mouse_internal);
    }

    void motionFunc    (glutIIFunc   motionFunc )
    {
        OSG_ASSERT(motionFunc != NULL);

        gMotionFunc = motionFunc;

        ::glutMotionFunc(motion_internal);
    }

    void idleFunc      (glutVFunc    idleFunc)
    {
        OSG_ASSERT(idleFunc != NULL);

        gIdleFunc = idleFunc;

        ::glutIdleFunc(idle_internal);
    }

    GLUTWindowTransitPtr createOSGWindow(void)
    {
        pGWin = GLUTWindow::create();

        pGWin->setGlutId(winid);

        return GLUTWindowTransitPtr(pGWin);
    }
}

OSG_END_NAMESPACE

#endif // OSG_WITH_GLUT

