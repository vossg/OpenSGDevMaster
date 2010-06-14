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

#include "OSGCSMPassiveWindow.h"
#include "OSGPassiveWindow.h"
#include "OSGComplexSceneManager.h"
#include "OSGGLUT.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMPassiveWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMPassiveWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

bool              CSMPassiveWindow::_bGLUTInitialized = false;
CSMPassiveWindow *CSMPassiveWindow::_pPassiveWindow   = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMPassiveWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


void CSMPassiveWindow::csmGlutKeyHandler(UChar8 key, 
                                         Int32  x, 
                                         Int32  y  )
{
    switch(key)
    {
        case 27:    

            glutKeyboardFunc  (NULL);
            glutReshapeFunc   (NULL);
//            glutDisplayFunc   (NULL);       
            glutMouseFunc     (NULL);   
            glutMotionFunc    (NULL); 
            glutIdleFunc      (NULL);  

            ComplexSceneManager::the()->terminate();

            osgExit(); 

            exit(0);

            break;

        default:
            ComplexSceneManager::the()->key(x, 
                                            y, 
                                            CSMKeyData::ButtonDown, 
                                            key);
            break;
    }
}

void CSMPassiveWindow::csmGlutReshapeHandler(Int32 w, 
                                             Int32 h)
{
    glViewport(0, 0, 
               w * _pPassiveWindow->getViewportScale()[0], 
               h * _pPassiveWindow->getViewportScale()[1]);

    if(_pPassiveWindow->getViewportScale()[0] < 1.0 ||
       _pPassiveWindow->getViewportScale()[1] < 1.0  )
    {
        glScissor(0, 0, 
                  w * _pPassiveWindow->getViewportScale()[0], 
                  h * _pPassiveWindow->getViewportScale()[1]);
        
        glEnable(GL_SCISSOR_TEST);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }

    _pPassiveWindow->reshape(w, h);

    glutPostRedisplay();
}

void CSMPassiveWindow::csmGlutFrameHandler(void)
{
    ComplexSceneManager::the()->frame();
    
    Thread::getCurrentChangeList()->commitChangesAndClear();

    glutSwapBuffers();
}

void CSMPassiveWindow::csmGlutMouseHandler(Int32 iButton, 
                                           Int32 iState,
                                           Int32 x,       
                                           Int32 y      )
{
    _pPassiveWindow->mouse(iButton, 
                           iState, 
                           glutGetModifiers(), 
                           x, 
                           y);
}

void CSMPassiveWindow::csmGlutMouseMotionHandler(Int32 x, 
                                                 Int32 y)
{
    _pPassiveWindow->motion(x, y);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMPassiveWindow::CSMPassiveWindow(void) :
     Inherited (  ),
    _iGlutWinId(-1)
{
}

CSMPassiveWindow::CSMPassiveWindow(const CSMPassiveWindow &source) :
     Inherited (source),
    _iGlutWinId(    -1)
{
}

CSMPassiveWindow::~CSMPassiveWindow(void)
{
}

void CSMPassiveWindow::terminateGLContext(void)
{
    if(_pWindow != NULL)
    {
        _pWindow->terminate();
    }

    glutDestroyWindow(_iGlutWinId);
}

/*----------------------------- class specific ----------------------------*/

void CSMPassiveWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMPassiveWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMPassiveWindow NI" << std::endl;
}

bool CSMPassiveWindow::init(void)
{
    if(_bGLUTInitialized == false)
    {
              Int32  argc   = 1;
        const Char8 *argv[] = { "testCSM-Passive" };

        glutInit(&argc, const_cast<Char8 **>(argv));
    }

    UInt32 uiDisplayMode = (GLUT_RGBA       | 
                            GLUT_DEPTH      | 
                            GLUT_DOUBLE     | 
                            GLUT_STENCIL    |
                            GLUT_MULTISAMPLE);

#if 0
    if(_pVSCWindow->stereo() == true)
    {
        uiDisplayMode |= GLUT_STEREO;
    }
#endif

    OSG::PassiveWindowUnrecPtr pPWindow = OSG::PassiveWindow::create();

    if(pPWindow == NULL)
        return false;

    glutInitDisplayMode(uiDisplayMode);

    if(this->getXPos() > 0.f && this->getYPos() > 0.f)
    {
        glutInitWindowPosition(Int32(this->getXPos()), 
                               Int32(this->getYPos()));
    }

    if(this->getXSize() > 0.f && this->getYSize() > 0.f)
    {
        glutInitWindowSize(Int32(this->getXSize()), 
                           Int32(this->getYSize()));
    }

    _iGlutWinId = glutCreateWindow("OpenSG - CSM");

//    pGLUTWindow->setGlutId(iWinId);

    if(this->getXSize() > 0.f && this->getYSize() > 0.f)
    {
        pPWindow->resize(Int32(this->getXSize()), 
                         Int32(this->getYSize()));
    }

    if(ComplexSceneManager::the() != NULL)
        ComplexSceneManager::the()->setMainloop(glutMainLoop);

#if 0
    if(_pVSCWindow->getXSize       () <  0.f && 
       _pVSCWindow->getYSize       () <  0.f &&
       _pVSCWindow->getDecorEnabled() == false)
    {
        glutFullScreen();
    }
#endif    

    _pWindow        = pPWindow;
    _pPassiveWindow = this;

    if(_bGLUTInitialized == false)
    {
        _bGLUTInitialized = true;

//        _pFirstWindow = this;

        glutKeyboardFunc  (csmGlutKeyHandler        );
//        glutVisibilityFunc(vscGlutVisHandler        );
        glutReshapeFunc   (csmGlutReshapeHandler    );
        glutDisplayFunc   (csmGlutFrameHandler      );       
        glutMouseFunc     (csmGlutMouseHandler      );   
        glutMotionFunc    (csmGlutMouseMotionHandler); 
        glutIdleFunc      (csmGlutFrameHandler      );  
    }

    pPWindow->init();

#if 0
    OSG::IndentFileOutStream outFileStream("/tmp/window.osg");

    if(outFileStream)
    {
        std::cerr << "STARTING PRINTOUT:" << std::endl;

        OSG::OSGWriter writer(outFileStream, 4);

        writer.write(_pOSGWindow);

        outFileStream.close();
    } 
#endif

    Inherited::init();

//    pPWindow->activate();

    return true;
}

OSG_END_NAMESPACE
