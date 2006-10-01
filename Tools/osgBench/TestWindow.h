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

#ifndef _TESTWINDOW_H_
#define _TESTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGGrabForeground.h>

#include <Nodes.h>

class TestWindow
{
    /*==========================  PUBLIC  =================================*/
  public:
 
    TestWindow(void);
   
    ~TestWindow();
    
    void setSize(OSG::UInt16 width, OSG::UInt16 height);
    void setFullscreen(void);
    
    void setViewport(OSG::Real32 left,   OSG::Real32 right, 
                     OSG::Real32 bottom, OSG::Real32 top   );
 
    inline OSG::UInt16 getWidth (void);
    inline OSG::UInt16 getHeight(void);
    
    inline OSG::PerspectiveCameraPtr getCamera(void);
    
    inline OSG::NodePtr getScene(void             );
    inline void         setScene(OSG::NodePtr root);
    inline void         setScene(NodeBase    &root);
    
    void setCamera(OSG::Matrix mat);
    void setCamera(OSG::Real32 fromx, OSG::Real32 fromy, OSG::Real32 fromz, 
                   OSG::Real32 atx,   OSG::Real32 aty,   OSG::Real32 atz, 
                   OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz);

    void setNearFar(OSG::Real32 n, OSG::Real32 f);
    void setFov(OSG::Real32 fov);
    
    void showAll(void);
    
    void finish(void);
    void redraw(void);

    OSG::ImagePtr snapshot(void);
    
    void open  (void);
    void close (void);    
    inline bool isOpen(void);
    
    inline OSG::SimpleSceneManager *getSSM(void);
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    void update(void);

    /*==========================  PRIVATE  ================================*/
  private:
  
    OSG::Int16 _width, _height;
    OSG::Real32 _left, _right, _bottom, _top;
    OSG::NodePtr _scene;  
    OSG::GLUTWindowPtr _window;
    OSG::SimpleSceneManager *_ssm;
    OSG::Real32 _near, _far, _fov;
    OSG::TransformPtr _beacon;
    OSG::GrabForegroundPtr _grabber;
    
    bool _open;
};

#include "TestWindow.inl"

#endif
