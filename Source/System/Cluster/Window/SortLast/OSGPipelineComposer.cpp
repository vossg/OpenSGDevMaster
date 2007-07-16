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

#define GL_GLEXT_PROTOTYPES 1

#include <OSGConfig.h>
#include <OSGConnection.h>
#include <OSGGLEXT.h>

#include "OSGPipelineComposer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PipelineComposer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PipelineComposer::initMethod(InitPhase ePhase)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PipelineComposer::PipelineComposer(void) :
    Inherited(),
    _readTilePtr(&_tileA),
    _composeTilePtr(&_tileB),
    _barrier(NULL),
    _composeBarrier(NULL),
    _frameEndBarrier(NULL),
    _lock(NULL),
    _writer(NULL),
    _waiting(false),
    _firstFrame(true)
{
}

PipelineComposer::PipelineComposer(const PipelineComposer &source) :
    Inherited(source),
    _readTilePtr(&_tileA),
    _composeTilePtr(&_tileB),
    _barrier(NULL),
    _composeBarrier(NULL),
    _frameEndBarrier(NULL),
    _lock(NULL),
    _writer(NULL),
    _waiting(false),
    _firstFrame(true)
{
}

PipelineComposer::~PipelineComposer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PipelineComposer::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PipelineComposer::dump(      UInt32    , 
                            const BitVector ) const
{
    SLOG << "Dump PipelineComposer NI" << std::endl;
}

/*----------------------------- composition -------------------------------*/

void PipelineComposer::open()
{
    setShort(true);

    // create server cross connection
    _clusterWindow->getNetwork()->connectAllGroupToPoint(clusterId(),
                                                         "StreamSock");
    // do not buffer any data
    for(UInt32 i=0 ; i <= serverCount() ; ++i)
        clusterWindow()->getNetwork()->getConnection(i)->forceDirectIO();
    if(!_isClient)
    {
        // create barrier
        _lock = Lock::get("PipelineComposer");
        // create barrier
        _barrier = Barrier::get("PipelineComposer");
        _frameEndBarrier = Barrier::get("PipelineComposerFrameEnd");
        // create writer thread
        _writer = BaseThread::get("PipelineComposer");
        // start writer thread
        _writer->runFunction( writeProc, this );
    }
    if(!_isClient && getPipelined())
    {
        _composeBarrier = Barrier::get("PipelineComposerCompose");
//        _composer = BaseThread::get("PipelineComposerCompose");
        _composer = dynamic_cast<Thread *>(ThreadManager::the()->getThread(NULL));
        _composer->runFunction( composeProc,0, this );
    }    

#ifdef USE_NV_OCCLUSION
    glGenOcclusionQueriesNV(1, &_occlusionQuery);
#endif
}

void PipelineComposer::startViewport(ViewportPtr)
{
    if(getPipelined())
    {
        if(!isClient()) 
        {
            _composeBarrier->enter(2);
        }
        else
        {
            // transfer tile size
            _composeTilesX  = _readTilesX;
            _composeTilesY  = _readTilesY;
        }
    }
}

void PipelineComposer::composeViewport(ViewportPtr port)
{
    UInt32 s;

    // setup viewport
    GLint 
        pl=port->getPixelLeft(), 
        pr=port->getPixelRight(),
        pb=port->getPixelBottom(), 
        pt=port->getPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;
    bool full = port->isFullWindow();
    glViewport(pl, pb, pw, ph);
    glScissor(pl, pb, pw, ph);
    if(! full)
        glEnable(GL_SCISSOR_TEST);

    GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
    GLboolean blend = glIsEnabled(GL_BLEND);

//    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, port->getPixelWidth(),
            0, port->getPixelHeight(),-1,1);
    if(getAlpha())
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // only one buffer for the client
    if(isClient())
        _composeTilePtr = _readTilePtr;

    _readTilesX = (port->getPixelWidth()  - 1) / getTileSize() + 1;
    _readTilesY = (port->getPixelHeight() - 1) / getTileSize() + 1;

    _tileBufferSize = getTileSize()*getTileSize()*8+sizeof(TileBuffer);
    _workingTile.resize(_tileBufferSize);

    // resize
    _readTilePtr->resize(_tileBufferSize * _readTilesX * _readTilesY);

    if(isClient())
    {
        while(_groupInfo.size() < serverCount())
        {
            _groupInfoPool.push_back(GroupInfo());
            _groupInfo.push_back(&(*_groupInfoPool.rbegin()));
        }
        _groupInfo.resize(serverCount());
    }
    
    _statistics.bytesIn  = 0;
    _statistics.bytesOut = 0;
    _statistics.occluded = 0;
    _statistics.noDepth  = 0;
    _statistics.noGeo    = 0;
    _statistics.clipped  = 0;

    if(!getPipelined())
    {
        _composeTilesX  = _readTilesX;
        _composeTilesY  = _readTilesY;
    }
    if(getShort())
    {
        UInt16 colorDummy;
//        UInt16 depthDummy;
        UInt32 depthDummy;
//        _depthType   = GL_UNSIGNED_SHORT;
        _depthType   = GL_UNSIGNED_INT;
        _colorFormat = GL_RGB;
        _colorType   = GL_UNSIGNED_SHORT_5_6_5;
        
        readBuffer(depthDummy,colorDummy,port);
        if(!getPipelined() || isClient())
            composeBuffer(depthDummy,colorDummy);
    }
    else
    {
        if(getAlpha())
        {
            UInt32 colorDummy;
            UInt32 depthDummy;
            _depthType   = GL_UNSIGNED_INT;
            _colorFormat = GL_RGBA;
            _colorType   = GL_UNSIGNED_BYTE;
            readBuffer(depthDummy,colorDummy,port);
            if(!getPipelined() || isClient())
                composeBuffer(depthDummy,colorDummy);
        }
        else
        {
            RGBValue colorDummy;
            UInt32   depthDummy;
            _depthType   = GL_UNSIGNED_INT;
            _colorFormat = GL_RGB;
            _colorType   = GL_UNSIGNED_BYTE;
            readBuffer(depthDummy,colorDummy,port);
            if(!getPipelined() || isClient())
                composeBuffer(depthDummy,colorDummy);
        }
    }

    if(getStatistics())
    {
        if(isClient())
        {
            double      pixelReadTime = 0;
            double      sortTime      = 0;
            UInt32      maxIn      = _statistics.bytesIn;
            UInt32      maxOut     = _statistics.bytesOut;
            UInt32      maxIO      = maxIn + maxOut;
            UInt32      sumOut     = _statistics.bytesOut;
            UInt32      clipped    = 0;
            Connection::Channel channel;
            GroupConnection *server;
            Statistics  statistics;
            server = clusterWindow()->getNetwork()->getMainGroupConnection();
            for(UInt32 i=0 ; i<serverCount() ;++i)
            {
                channel = server->selectChannel();
                server->subSelection(channel);
                server->get(&statistics,sizeof(Statistics));
                sumOut += statistics.bytesOut;
                if(statistics.pixelReadTime > pixelReadTime) {
                    pixelReadTime = statistics.pixelReadTime;
                    sortTime = statistics.sortTime;
                }
                if(statistics.bytesOut > maxOut)
                    maxOut = statistics.bytesOut;
                if(statistics.bytesIn > maxIn)
                    maxIn = statistics.bytesIn;
                if(statistics.bytesIn + statistics.bytesOut > maxIO)
                    maxIO = statistics.bytesIn + statistics.bytesOut;
                clipped += statistics.clipped;
            }
            server->resetSelection();
            printf("pixel read time  : %1.5lf\n",pixelReadTime);
            printf("sort Time        : %1.5lf\n",sortTime);
            printf("compose Time     : %1.5lf\n",_statistics.composeTime);
            printf("Transfered bytes : %10d\n",sumOut);
            printf("Max out          : %10d\n",maxOut);
            printf("Max in           : %10d\n",maxIn);
            printf("Max io           : %10d\n",maxIO);
            printf("occluded         : %10d\n",_statistics.occluded);
            printf("Layerd           : %10d\n",_statistics.noDepth);
            printf("Empty            : %10d\n",_statistics.noGeo-clipped);
            printf("Clipped          : %10d\n",clipped);
            printf("DepthAndColor    : %10d\n",serverCount()*_composeTilesX*_composeTilesY-
                   _statistics.occluded-
                   _statistics.noDepth-
                   _statistics.noGeo);
        }
        else
        {
            Connection *client = clusterWindow()->getNetwork()->getMainConnection();
            client->put(&_statistics,sizeof(Statistics));
            client->flush();
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
}

void PipelineComposer::close(void)
{
    if(!isClient() && _writer)
    {
        _lock->acquire();
        _queue.push_back(NULL);
        if(_waiting)
        {
            _waiting = false;
            _barrier->enter(2);
        }
        _lock->release();
        BaseThread::join(_writer);
    }
}

/*----------------------------- features ---------------------------------*/

/*! 
 */
bool PipelineComposer::getClientRendering()
{
    return false;
}

/*----------------------------- helper ------------------------------------*/

PipelineComposer::TileBuffer *PipelineComposer::getComposeTileBuffer(UInt32 x,UInt32 y)
{
    return (TileBuffer*)(&(*_composeTilePtr)[(y*_composeTilesX + x)*_tileBufferSize]);
}

PipelineComposer::TileBuffer *PipelineComposer::getReadTileBuffer(UInt32 x,UInt32 y)
{
    return (TileBuffer*)(&(*_readTilePtr)[(y*_readTilesX + x)*_tileBufferSize]);
}

PipelineComposer::TileBuffer *PipelineComposer::getWorkingTileBuffer(void)
{
    return (TileBuffer*)(&_workingTile[0]);
}

/*! Depth order for pipe sort
 */
bool PipelineComposer::GroupInfoOrder::operator() 
    (const GroupInfo *a, const GroupInfo *b)
{
    if( a->depth.max > b->depth.max ||
        ( a->depth.max == b->depth.max &&
          a->id > b->id ))
        return true;
    else
        return false;
}

UInt32 PipelineComposer::compressTransInfo(std::vector<TransInfo> &transInfo)
{
    TransInfo *src    = &transInfo[0];
    TransInfo *srcEnd = src + _composeTilesX*_composeTilesY*serverCount();
    TransInfo *dst    = &transInfo[0];
    TransInfo *empty  = NULL;
    while(src != srcEnd) {
        if(src->empty) {
            if(!empty) {
                empty = dst++;
                empty->sendTo=1;
                empty->empty=true;
            } else {
                empty->sendTo++;
                if(empty->sendTo == 0) {
                    empty->sendTo--;
                    empty = dst++;
                    empty->sendTo=1;
                    empty->empty=true;
                }
            }
         } else {
            empty = NULL;
            *dst=*src;
            dst++;
        }
        src++;
    }
//    printf("Compress %f\n",(dst - &transInfo[0])*100.0/transInfo.size());
    return dst - &transInfo[0];
}

void PipelineComposer::uncompressTransInfo(std::vector<TransInfo> &transInfo,UInt32 infoCount)
{
    transInfo.resize(_composeTilesX*_composeTilesY*serverCount());

    TransInfo *src    = &transInfo[infoCount-1];
    TransInfo *srcEnd = &transInfo[0] - 1;
    TransInfo *dst    = &transInfo[_composeTilesX*_composeTilesY*serverCount()-1];
    while(src != srcEnd) {
        if(src->empty) {
            while(src->sendTo) {
                dst->empty = true;
                dst--;
                src->sendTo--;
            }
        } else {
            *dst=*src;
            dst--;
        }
        src--;
    }
}

/*----------------------------- thread proc -------------------------------*/

void PipelineComposer::writeProc(void *arg) 
{
    PipelineComposer *the=(PipelineComposer*)arg;
    if(the->getShort())
    {
        UInt16 colorDummy;
        UInt16 depthDummy;
        the->writeResult(depthDummy,colorDummy);
    }
    else
    {
        if(the->getAlpha())
        {
            RGBValue colorDummy;
            UInt32   depthDummy;
            the->writeResult(depthDummy,colorDummy);
        }
        else
        {
            UInt32 colorDummy;
            UInt32 depthDummy;
            the->writeResult(depthDummy,colorDummy);
        }
    }
}

void PipelineComposer::composeProc(void *arg) 
{
    PipelineComposer *the=(PipelineComposer*)arg;

    // TODO stop compose thread
    for(;;)
    {
        if(the->getShort())
        {
            UInt16 colorDummy;
            UInt32 depthDummy;
            the->composeBuffer(depthDummy,colorDummy);
        }
        else
        {
            if(the->getAlpha())
            {
                RGBValue colorDummy;
                UInt32   depthDummy;
                the->composeBuffer(depthDummy,colorDummy);
            }
            else
            {
                UInt32 colorDummy;
                UInt32 depthDummy;
                the->composeBuffer(depthDummy,colorDummy);
            }
        }
    }
}

