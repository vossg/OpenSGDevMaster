/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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
#include <iostream>

#include <OSGConfig.h>

#include "OSGParallelComposer.h"


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ParallelComposer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParallelComposer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParallelComposer::ParallelComposer(void) :
    Inherited()
{
}

ParallelComposer::ParallelComposer(const ParallelComposer &source) :
    Inherited(source)
{
}

ParallelComposer::~ParallelComposer(void)
{
}

/*----------------------------- features ----------------------------------*/

bool ParallelComposer::clientRendering(void)
{
    return false;
}

bool ParallelComposer::getClientRendering(void)
{
    return false;
}

UInt32 ParallelComposer::getUsableServers(void)
{
    return _usableServers;
}
/*----------------------------- composition -------------------------------*/

void ParallelComposer::open(void)
{
#ifdef OSG_WITH_PARALLEL
    if(getPcLibPath() != "")
    {
        pcSysInitialize(getPcLibPath().c_str(), 123458);
    }
    else
    {
        char *pc = getenv("PCLIB_PATH");
        if(pc!= NULL)
            pcSysInitialize(pc, 123458);
        else
            pcSysInitialize(".", 123458);
    }
    
    // Initialize buffers
    _bufColor	   = NULL;
    _bufDepth	   = NULL;
    _bufRet 	   = NULL;
    _createContext = true;
    
    // determine usable servers
    _usableServers = serverCount();

    // create server cross connection
    _clusterWindow->getNetwork()->connectAllPointToPoint(clusterId(),
                                                         "StreamSock");
    // do not buffer any data
    for(UInt32 i=0 ; i <= serverCount() ; ++i)
        clusterWindow()->getNetwork()->getConnection(i)->forceDirectIO();	
    // populate server list from inherited cluster window
    osgGetHostname(_serviceAddr, sizeof(_serviceAddr));

    _serverList = new char*[_usableServers+2];
    _serverList[0]  = _serviceAddr;
    int i = 1;
    for(; i<_usableServers+1; i++)
    {
        _serverList[i] = (char*)clusterWindow()->getServers(i-1).c_str();
    }
    _serverList[i]= NULL;
#endif
}

void ParallelComposer::composeViewport(Viewport *port)
{
#ifdef OSG_WITH_PARALLEL
    // setup viewport
    GLint 
        pl=port->getPixelLeft(), 
        pr=port->getPixelRight(),
        pb=port->getPixelBottom(), 
        pt=port->getPixelTop();
    if(_wWidth != pr-pl+1 || _wHeight != pt-pb+1)
    {
        _wWidth = pr-pl+1;
        _wHeight= pt-pb+1;
        _createContext = true;
    }
    bool full = port->isFullWindow();
    glViewport(pl, pb, _wWidth, _wHeight);
    glScissor(pl, pb, _wWidth, _wHeight);
    if(! full)
        glEnable(GL_SCISSOR_TEST);

    GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
    GLboolean blend = glIsEnabled(GL_BLEND);

    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, port->getPixelWidth(),
            0, port->getPixelHeight(),-1,1);

    if(_createContext)
    {
        createCtx(port);
        _createContext = false;
    }

    if(getAlpha())
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    if(isClient())
    {
        UInt32 id = beginFrame();
        renderRead();
        endFrame(id);
        drawFrame();
    }
    else
    {
        if(clusterId() < _usableServers)
        {
            UInt32 id = beginFrame();
            renderRead();
            endFrame(id);
            //drawFrame();
        }
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

    // reset state
    if(depth && !glIsEnabled(GL_DEPTH_TEST))
        glEnable(GL_DEPTH_TEST);
    if(!blend && glIsEnabled(GL_BLEND))
        glDisable(GL_BLEND);
#endif
}

void ParallelComposer::close(void)
{
#ifdef OSG_WITH_PARALLEL
    pcContextDestroy(_context);
    pcSysFinalize();
#endif
}

/*----------------------------- class specific ----------------------------*/

void ParallelComposer::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParallelComposer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParallelComposer NI" << std::endl;
}

/*----------------------------- helpers ----------------------------------*/

void ParallelComposer::createCtx( Viewport *port)
{
#ifdef OSG_WITH_PARALLEL
    // get needed attributes from viewport
    PCint attribs[40];
    UInt32 i = 0;
    PCerr err;
    
    attribs[i++] = PC_FRAME_WIDTH;              attribs[i++] = _wWidth;
    attribs[i++] = PC_FRAME_HEIGHT;             attribs[i++] = _wHeight;
    attribs[i++] = PC_COMPOSITE_TYPE;           attribs[i++] = PC_COMP_DEPTH;
    attribs[i++] = PC_PIXEL_FORMAT;             attribs[i++] = PC_PF_BGRA8|PC_PF_Z32I;
    // maybe this will change?
    attribs[i++] = PC_OUTPUT_DEPTH;             attribs[i++] = 1;
    // maybe more, force depth? compression?
    attribs[i++] = PC_ATTRIB_END;
     
    if(isClient())
    {
        // we need a global context
        err = pcContextCreateGlobal(attribs, _serverList, _serviceAddr, &_context);
        if(err)
        {
            SLOG  << "Error creating global context" << std::endl;
        }
    }
    else
    {
        // create a local context
        err = pcContextCreateLocal(PC_ID_DEFAULT, _serviceAddr, &_context);
        if(err)
        {
            SLOG << "Error creating local context" << std::endl;
        }
    }
    
    if(isClient())
    {
        pcContextSetInteger(_context,PC_OUTPUT_LEFT,PC_LOCALHOST_INDEX,0);
        pcContextSetInteger(_context,PC_OUTPUT_TOP,PC_LOCALHOST_INDEX,0);
        pcContextSetInteger(_context,PC_OUTPUT_WIDTH,PC_LOCALHOST_INDEX,_wWidth);
        pcContextSetInteger(_context,PC_OUTPUT_HEIGHT,PC_LOCALHOST_INDEX,_wHeight);
    }
    
    if(_bufColor)
        delete [] _bufColor;
    _bufColor = new UInt8 [_wWidth * _wHeight * 4 * sizeof(GLubyte)];
     
    if(_bufDepth)
        delete [] _bufDepth;
    _bufDepth = new UInt8 [_wWidth * _wHeight  * sizeof(GLuint)];
#endif
}

void ParallelComposer::endFrame(UInt32 id)
{
#ifdef OSG_WITH_PARALLEL
    
    PCerr err;

    /* send the pixels */
    err = pcFrameAddFramelet(_context,id,_bufColor,_bufDepth);
    if(err)
    {
        SLOG << "Error adding framelet in endFrame" << std::endl;
    }
    //}
    
    /* done with the frame */
    err = pcFrameEnd(_context,id);
    if(err)
    {
        SLOG << "Error while calling pcFrameEnd" << std::endl;
    }
    if (isClient()) 
    {
        /* grab the results */
        err = pcFrameResult(_context,id,0,0,_wWidth,_wHeight,reinterpret_cast<void**>(&_bufRet),NULL,
                          &_rowPixels);
        if(err)
        {
            SLOG << "Error while getting frame results" << std::endl;
        }
    }

#endif
}

UInt32 ParallelComposer::beginFrame(void)
{
   UInt32 id = 0;
#ifdef OSG_WITH_PARALLEL
   PCerr err;

   /* start the frame (all framelets are full size thus, NULLs) */  
   err = pcFrameBegin(_context, &id, 1, NULL, NULL, NULL, NULL, NULL);
   if(err)
   {
       SLOG << "Error while calling beginFrame" << std::endl;
   }
#endif
   return(id);
}

void ParallelComposer::drawFrame(void)
{
#ifdef OSG_WITH_PARALLEL
   if (isClient()) 
   {
       if (!_bufRet) return;
       glDisable(GL_DEPTH_TEST);
       glPixelStorei(GL_UNPACK_ROW_LENGTH,_rowPixels);
       glDrawPixels(_wWidth,_wHeight,GL_BGRA,GL_UNSIGNED_BYTE,_bufRet);
       glEnable(GL_DEPTH_TEST);
       // swap buffers?
       _bufRet = NULL;
   }
#endif
}

void ParallelComposer::renderRead(void)
{
#ifdef OSG_WITH_PARALLEL
    /* readback the pixels */
    glPixelStorei(GL_PACK_ROW_LENGTH,_wWidth);
    glReadPixels(0,0,_wWidth,_wHeight,GL_BGRA,GL_UNSIGNED_BYTE,_bufColor);
    glReadPixels(0,0,_wWidth,_wHeight,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,
                   _bufDepth);
#endif
}

