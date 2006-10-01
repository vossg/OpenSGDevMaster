/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <setjmp.h>

#include "TestWindow.h"

// This is ultra-ugly, but GLUT gives you no alternative
static jmp_buf jump;


TestWindow::TestWindow(void) :
    _width(-1), _height(-1), _scene(OSG::NullFC), _window(OSG::NullFC), _ssm(NULL),
    _open(false), _left(0), _right(1), _top(1), _bottom(0),
    _near(0.1), _far(100), _fov(1), _beacon(OSG::NullFC)
{
}

TestWindow::~TestWindow()
{
    if(_window != OSG::NullFC)
        OSG::subRef(_window);
    if(_ssm != NULL)
        delete _ssm;
}

void TestWindow::setFullscreen(void)
{
    if(!isOpen())
    {
        _width = -1;
        return;
    }
        
    _width = glutGet(GLUT_SCREEN_WIDTH);
    _height = glutGet(GLUT_SCREEN_HEIGHT);
    
    glutFullScreen();

    if(!setjmp(jump))
        glutMainLoop();
    
    update();
}

void TestWindow::setSize(OSG::UInt16 width, OSG::UInt16 height)
{
    _width = width;
    _height = height;
    
    if(isOpen())
    {
        glutReshapeWindow(width, height);
    
        if(!setjmp(jump))
            glutMainLoop();
    }
    
    update();
}

void TestWindow::setViewport(OSG::Real32 left,   OSG::Real32 right, 
                             OSG::Real32 bottom, OSG::Real32 top   )
{
    _left   = left;
    _right  = right;
    _bottom = bottom;
    _top    = top;

    update();
}

void TestWindow::setCamera(OSG::Matrix mat)
{
    // OSG::beginEditCP(_beacon);
    _beacon->setMatrix(mat);
    // OSG::endEditCP(_beacon);
}

void TestWindow::showAll(void)
{
    update();
    
    _ssm->showAll();
    _ssm->redraw();
}

void TestWindow::setNearFar(OSG::Real32 n, OSG::Real32 f)
{
    // OSG::beginEditCP(getCamera());
    getCamera()->setNear(n);
    getCamera()->setFar(f);
    // OSG::endEditCP(getCamera());
}

void TestWindow::setFov(OSG::Real32 fov)
{
    // OSG::beginEditCP(getCamera());
    getCamera()->setFov(fov);
    // OSG::endEditCP(getCamera());  
}

void TestWindow::redraw(void)
{
//    _ssm->redraw();
    _window->render(dynamic_cast<OSG::RenderAction*>(_ssm->getAction()));
}

OSG::ImagePtr TestWindow::snapshot(void)
{
//    _ssm->redraw();

    OSG::ViewportPtr port = _ssm->getWindow()->getPort(0);

    // OSG::beginEditCP(port);
    port->addForeground(_grabber);
    // OSG::endEditCP(port);
    
    OSG::ImagePtr img = OSG::Image::create();
    // OSG::beginEditCP(img);
    img->setPixelFormat(OSG::Image::OSG_RGB_PF);
    // OSG::endEditCP(img);
    
    // OSG::beginEditCP(_grabber);
    _grabber->setImage(img);
    // OSG::endEditCP(_grabber);
    
    _window->render(dynamic_cast<OSG::RenderAction*>(_ssm->getAction()));
    
    // OSG::beginEditCP(port);
    port->removeFromForegrounds(port->getForegrounds().size()-1);
    // OSG::endEditCP(port);
    
    return img;
}

void TestWindow::finish(void)
{    
    glFinish();
    
    OSG::UInt32 dummy;
    glReadPixels(0, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &dummy);
}

void TestWindow::setCamera(OSG::Real32 fromx, OSG::Real32 fromy, OSG::Real32 fromz, 
                           OSG::Real32 atx,   OSG::Real32 aty,   OSG::Real32 atz, 
                           OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz)
{
    OSG::Matrix m;
    
    OSG::MatrixLookAt(m, fromx, fromy, fromz, 
                           atx,   aty,   atz, 
                           upx,   upy,   upz);
    setCamera(m);
}

static void display(void)
{
    // Make sure the window is really open...
    glClear(GL_COLOR_BUFFER_BIT);

    glFinish();
    
    OSG::UInt32 dummy;
    glReadPixels(0, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &dummy);
}

static void idle(void)
{
    longjmp(jump, 0);
}

void TestWindow::open(void)
{
    static bool inited = false;
    
    if(isOpen())
        return;
        
    if(!inited)
    {
        int argc = 2;
        char *argv[2]={"OpenSG", "Benchmarks"};
        
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        inited = true;        
    }

    glutInitWindowPosition(0,0);
    if(_width > 0)
        glutInitWindowSize(_width, _height);
   
    int winid = glutCreateWindow("OpenSG Benchmark");

    if(_width < 0)
    {
        glutFullScreen();
        _width = glutGet(GLUT_SCREEN_WIDTH);
        _height = glutGet(GLUT_SCREEN_HEIGHT);       
    }
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    update();
    
    _window->setId(winid);
    _window->init();
    
    if(!setjmp(jump))
        glutMainLoop();
    
    _open = true;
}

void TestWindow::close(void)
{
    glutDestroyWindow(_window->getId());
    _open = false;
}  

void TestWindow::update(void)
{  
    if(_window == OSG::NullFC)
        _window = OSG::GLUTWindow::create();
    
    if(_grabber == OSG::NullFC)
    {
        _grabber = OSG::GrabForeground::create();
        // OSG::beginEditCP(_grabber);
        _grabber->setAutoResize(true);
        _grabber->setActive(true);       
        // OSG::endEditCP(_grabber);
    }
    
    if(_ssm == NULL)
        _ssm = new OSG::SimpleSceneManager;
    
    _ssm->setWindow(_window);
  
    _ssm->setRoot(_scene);

    _beacon = OSG::cast_dynamic<OSG::TransformPtr>(
                        getCamera()->getBeacon()->getCore());
    
    _ssm->resize(_width, _height);
   
    for(int i = 0; i < _ssm->getWindow()->getPort().size(); ++i)
    {
        OSG::ViewportPtr port = _ssm->getWindow()->getPort(i);
        
        // OSG::beginEditCP(port);
        port->setLeft(_left);
        port->setRight(_right);
        port->setBottom(_bottom);
        port->setTop(_top);
        // OSG::endEditCP(port);
    }

}
