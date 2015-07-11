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

#include "OSGConfig.h"

#include "OSGBinarySwapComposer.h"

OSG_USING_NAMESPACE


/*! \class OSG::BinarySwapComposer

 This composer implements the binary swap composition. 
*/

void BinarySwapComposer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/*----------------------- constructors & destructors ----------------------*/

BinarySwapComposer::BinarySwapComposer(void) :
     Inherited     (          ),
    _writer        (NULL      ),
    _barrier       (NULL      ),
    _stopWriter    (false     ),
    _swapWith      (0         ),
    _swapConnection(NULL      ),
    _tilesX        (0         ),
    _tilesY        (0         ),
    _tileBufferSize(0         ),
    _tile          (          ),
    _readTile      (          ),
    _writeLeft     (0         ),
    _writeRight    (0         ),
    _writeBottom   (0         ),
    _writeTop      (0         ),
    _usableServers (0         ),
    _statistics    (          ),
    _intDepthMax   (0xffffffff),
    _shortDepthMax (0xffff    )
{
}

BinarySwapComposer::BinarySwapComposer(const BinarySwapComposer &source) :
     Inherited     (source    ),
    _writer        (NULL      ),
    _barrier       (NULL      ),
    _stopWriter    (false     ),
    _swapWith      (0         ),
    _swapConnection(NULL      ),
    _tilesX        (0         ),
    _tilesY        (0         ),
    _tileBufferSize(0         ),
    _tile          (          ),
    _readTile      (          ),
    _writeLeft     (0         ),
    _writeRight    (0         ),
    _writeBottom   (0         ),
    _writeTop      (0         ),
    _usableServers (0         ),
    _statistics    (          ),
    _intDepthMax   (0xffffffff),
    _shortDepthMax (0xffff    )
{
}

BinarySwapComposer::~BinarySwapComposer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BinarySwapComposer::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BinarySwapComposer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BinarySwapComposer NI" << std::endl;
}

/*----------------------------- features ---------------------------------*/

/*! Currently it is not possible to do rendering on the client
 */
bool BinarySwapComposer::clientRendering()
{
    return false;
}

/*----------------------------- composition -------------------------------*/

void BinarySwapComposer::open()
{
    // determine usable servers
    if(osgIsPower2(serverCount()))
        _usableServers = serverCount();
    else
        _usableServers = osgNextPower2(serverCount()) / 2;

//    _usableServers = 1;

    // create server cross connection
    _clusterWindow->getNetwork()->connectAllPointToPoint(clusterId(),
                                                         "StreamSock");
    // do not buffer any data
    for(UInt32 i=0 ; i <= serverCount() ; ++i)
        clusterWindow()->getNetwork()->getConnection(i)->forceDirectIO();

/*
    // create barrier
    _barrier = Barrier::get(NULL);
    // create writer thread
    _writer = BaseThread::get(NULL);
*/

    // read whole buffer
    if(!_isClient && clusterId() < _usableServers)
    {
        // create barrier
        _barrier = Barrier::get(NULL, false);
        // create writer thread
        _writer = BaseThread::get(NULL, false);
        // start writer thread
        _writer->runFunction( writeProc, this );
    }
    else
    {
        _writer = NULL;
    }
}

void BinarySwapComposer::composeViewport(Viewport *port)
{
    // setup viewport
    GLint 
        pl=port->calcPixelLeft(), 
        pr=port->calcPixelRight(),
        pb=port->calcPixelBottom(), 
        pt=port->calcPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;
    bool full = port->calcIsFullWindow();
    glViewport(pl, pb, pw, ph);
    glScissor(pl, pb, pw, ph);
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
    glOrtho(0, port->calcPixelWidth(),
            0, port->calcPixelHeight(),-1,1);

//    printf("max %x,%x\n",_intDepthMax,_shortDepthMax);

    if(getAlpha())
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    _tilesX = port->calcPixelWidth()  / getTileSize() + 1;
    _tilesY = port->calcPixelHeight() / getTileSize() + 1;

    _tileBufferSize = getTileSize()*getTileSize()*8+sizeof(TileBuffer);
    _readTile.resize(_tileBufferSize);

    _statistics.bytesIn  = 0;
    _statistics.bytesOut = 0;

    if(isClient())
    {
        if(getShort())
        {
            UInt16 colorDummy;
            UInt32 depthDummy;
            recvFromServers(depthDummy,colorDummy,
                            GL_RGB,
                            GL_UNSIGNED_SHORT_5_6_5,
                            port);
        }
        else
        {
            if(getAlpha())
            {
                UInt32 colorDummy;
                UInt32 depthDummy;
                recvFromServers(depthDummy,colorDummy,
                                GL_RGBA,
                                GL_UNSIGNED_BYTE,
                                port);
            }
            else
            {
                RGBValue colorDummy;
                UInt32   depthDummy;
                recvFromServers(depthDummy,colorDummy,
                                GL_RGB,
                                GL_UNSIGNED_BYTE,
                                port);
            }
        }
        if(getStatistics())
        {
            UInt32      maxIn   = _statistics.bytesIn;
            UInt32      maxOut  = _statistics.bytesOut;
            UInt32      maxIO   = maxIn + maxOut;
            UInt32      sumOut  = _statistics.bytesOut;
            UInt32      missing = _usableServers;
            double      composeTime = 1e32;
            
            Connection *server;
            Statistics  statistics;
            for(UInt32 i=0 ; i<_usableServers ;++i)
            {
                server = clusterWindow()->getNetwork()->getConnection(i);
                server->selectChannel();
                server->get(&statistics,sizeof(Statistics));
                sumOut += statistics.bytesOut;
                if(statistics.composeTime < composeTime)
                    composeTime = statistics.composeTime;
                if(statistics.bytesOut > maxOut)
                    maxOut = statistics.bytesOut;
                if(statistics.bytesIn > maxIn)
                    maxIn = statistics.bytesIn;
                if(statistics.bytesIn + statistics.bytesOut > maxIO)
                    maxIO = statistics.bytesIn + statistics.bytesOut;
                missing--;
            }
            printf("compose Time     : %1.5lf\n",composeTime);
            printf("Transfered bytes : %10d\n",sumOut);
            printf("Max out          : %10d\n",maxOut);
            printf("Max in           : %10d\n",maxIn);
            printf("Max io           : %10d\n",maxIO);
        }
    }
    else
    {
        if(clusterId() < _usableServers)
        {
            _statistics.composeTime = -getSystemTime();
            _tile.resize(_tileBufferSize * _tilesX * _tilesY);
            if(getShort())
            {
                UInt16 colorDummy;
                UInt32 depthDummy=_shortDepthMax;
//                UInt32 depthDummy=_intDepthMax;
                startReader(depthDummy,colorDummy,
//                            GL_UNSIGNED_SHORT,
                            GL_UNSIGNED_INT,
                            GL_RGB,
                            GL_UNSIGNED_SHORT_5_6_5,
                            port);
            }
            else
            {
                if(getAlpha())
                {
                    UInt32 colorDummy;
                    UInt32 depthDummy=_intDepthMax;
                    startReader(depthDummy,colorDummy,
                                GL_UNSIGNED_INT,
                                GL_RGBA,
                                GL_UNSIGNED_BYTE,
                                port);
                }
                else
                {
                    RGBValue colorDummy;
                    UInt32   depthDummy=_intDepthMax;
                    startReader(depthDummy,colorDummy,
                                GL_UNSIGNED_INT,
                                GL_RGB,
                                GL_UNSIGNED_BYTE,
                                port);
                }
            }
            _statistics.composeTime += getSystemTime();
            if(getStatistics())
            {
                Connection *client = clusterWindow()->getNetwork()->getConnection(serverCount());
                client->put(&_statistics,sizeof(Statistics));
                client->flush();
            }
        }
/*
        // max depth value !! find a better way
        glClear(GL_DEPTH_BUFFER_BIT);
        glReadPixels(0, 0, 1, 1, 
                     GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,
                     &_intDepthMax);
        glReadPixels(0, 0, 1, 1, 
                     GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT,
                     &_shortDepthMax);
*/
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

void BinarySwapComposer::close(void)
{
    if(!isClient() && _writer)
    {
        _stopWriter = true;
        _barrier->enter(2);
        BaseThread::join(_writer);
        _writer  = NULL;
        _barrier = NULL;
    }
}

/*----------------------------- features ---------------------------------*/

/*! it is not possible to do rendering on the client with binary swap
  currently ;-) 
 */
bool BinarySwapComposer::getClientRendering()
{
    return false;
}

/*! use only 2^n servers
 */
UInt32 BinarySwapComposer::getUsableServers()
{
    return _usableServers;
}

/*----------------------------- helper ------------------------------------*/

BinarySwapComposer::TileBuffer *BinarySwapComposer::getTileBuffer(UInt32 x,UInt32 y)
{
    return reinterpret_cast<TileBuffer*>(
        &_tile[(y*_tilesX + x)*_tileBufferSize]);
}

BinarySwapComposer::TileBuffer *BinarySwapComposer::getTileReadBuffer(void)
{
    return reinterpret_cast<TileBuffer*>(&_readTile[0]);
}

/*----------------------------- thread proc -------------------------------*/


void BinarySwapComposer::writeProc(void *arg) 
{
    BinarySwapComposer *the=static_cast<BinarySwapComposer*>(arg);
    for(;;)
    {
        the->_barrier->enter(2);
        if(the->_stopWriter)
            break;
        if(the->getShort())
        {
            UInt16 colorDummy;
            UInt32 depthDummy;
            the->writeCombine(depthDummy,colorDummy);
        }
        else
        {
            if(the->getAlpha())
            {
                RGBValue colorDummy;
                UInt32   depthDummy;
                the->writeCombine(depthDummy,colorDummy);
            }
            else
            {
                UInt32 colorDummy;
                UInt32 depthDummy;
                the->writeCombine(depthDummy,colorDummy);
            }
        }
    }
}

