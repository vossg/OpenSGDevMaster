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

#ifndef _TEST_H_
#define _TEST_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGStatCollector.h>
#include "TestWindow.h"
#include "Nodes.h"
#include "Image.h"

class Test
{
    /*==========================  PUBLIC  =================================*/
  public:
 
    Test(void);
    
    ~Test();

    // Set up scene characteristics
    
    void setScene(NodeBase &scene);
    
    void setScene(OSG::NodePtr scene);
    
    void setWindow(TestWindow &win);
    
    void setHeadlight(bool on);
     
    // set near and far, if any <= 0 use showAll() values
    void setNearFar(OSG::Real32 n, OSG::Real32 f);
   
    // Setup Test Frames
   
    // clear all the animation data
    void clear(void);
    
    // MinTime takes precedence, the path is repeated fully until the time is
    // reached
   
    void setNFrames(OSG::UInt32 nframes);     
    void setMinTime(OSG::Real32 minTime);
    
    void addFromAtUp(OSG::Real32 fromx, OSG::Real32 fromy, OSG::Real32 fromz, 
                     OSG::Real32 atx,   OSG::Real32 aty,   OSG::Real32 atz, 
                     OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz);
    
    void addFromAtUp(OSG::Pnt3f from, OSG::Pnt3f at, OSG::Vec3f up);
    
    // Define Path from VRML-Style Positon/Quaternion Strings
    void addFromOri(OSG::Char8 *from, OSG::Char8 *ori);
    
    // Make a rotational path around the whole model
    void makeOrbit(OSG::Real32 upx = 0, OSG::Real32 upy = 1, OSG::Real32 upz =
    0);
    
    // Make a pirouette inside the model
    void makePirouette(OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz);

    // add a FOV to animate
    void addFov(OSG::Real32 fov);  
    
    // Run Test
    
    void setVerbose(bool on);
    
    void useRenderTraversal(bool on);
    
    void setIgnoreGeometry(bool ignore);
    
    void setStatistics(OSG::UInt16 level);
    
    OSG::UInt16 getStatistics(void);
    
    void run(void);
    
    Image snapshot(OSG::UInt32 frame);
    
    // Get Results
    
    OSG::Real32 getFPS(void);
    
    OSG::Real32 getTime(void);
    
    OSG::UInt32 getNRenderedFrames(void);
    
    OSG::Real64 getStatValue(OSG::Char8 *name, OSG::UInt32 frame);
    
         
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Expand the data to fit NFrames 
    void expandData(std::vector<OSG::Matrix>& views, 
                    std::vector<OSG::Real32> &fovs);

    void runLoop(std::vector<OSG::Matrix> &views, 
                 std::vector<OSG::Real32> &fovs);

    /*==========================  PRIVATE  ================================*/
  private:
    
    TestWindow *_win;

    OSG::NodePtr _scene;
    
    OSG::Real32 _near, _far;    
    std::vector<OSG::Pnt3f> _froms;
    std::vector<OSG::Quaternion> _oris;
    std::vector<OSG::Real32> _fovs;
    
    OSG::Real32 _minTime;    
    OSG::UInt32 _nFrames;
    bool _headlight;
    OSG::UInt16 _statsLevel;
    bool _verbose;
    bool _useRenderTraversal;
    
    // Results
    OSG::Real32 _time;    
    OSG::UInt32 _nRenderedFrames;

    std::vector<OSG::StatCollector> _stats;
};

#endif
