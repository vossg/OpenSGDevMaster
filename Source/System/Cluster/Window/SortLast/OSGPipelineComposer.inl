/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

#define COMBINE
#define TOCLIENT

template<class DepthT,class ColorT>
UInt32 PipelineComposer::getMinMaxOcclude(DepthT    &depth,
                                          ColorT    &color,
                                          DepthInfo *result)
{
    UInt32             x,y;
    TileBuffer        *tile;
    UInt32             count=0;
    DepthInfo         *first = result;
    DepthInfo         *reuseEmpty=NULL;

    first->min=0;
    result++;
    for(y = 0; y < _composeTilesY ; ++y)
    {
        for(x = 0; x < _composeTilesX ; ++x)
        {
            tile = getComposeTileBuffer(x,y);

            if(tile->depth.min == DepthT(-1) &&
               tile->depth.max == DepthT(-1)) {
                if(!reuseEmpty) {
                    reuseEmpty=result;
                    result++;
                    count++;
                    reuseEmpty->min = DepthT(-1);
                    reuseEmpty->max = 0;
                }
                reuseEmpty->max++;
            } else {
                *result = tile->depth;
                result++;
                count++;
                reuseEmpty=NULL;
            }
        }
    }
//    printf("compr %f\n",count*100.0/(_composeTilesX*_composeTilesY));

    first->min = count;
    return count+1;
}

template<class DepthT,class ColorT>
void PipelineComposer::setTransInfo(DepthT &depth,ColorT &color)
{
    UInt32                      x,y;
    Connection                 *client,*readCon;
    std::vector<DepthInfo>      depthInfo;
    TileBuffer                 *tile;
    std::vector<TransInfo>      transInfo;
    std::vector<TransInfo>      transInfoDummy;
    UInt32                      count;

    transInfo.resize(_composeTilesX * _composeTilesY * serverCount());
    depthInfo.resize(_composeTilesX * _composeTilesY + 1);
    count = getMinMaxOcclude(depth,color,&depthInfo[0]);

    _statistics.sortTime = -getSystemTime();

    // send depth info
    client = clusterWindow()->getNetwork()->getMainConnection();

    client->put(&depthInfo[0],sizeof(DepthInfo)*count);
    _statistics.bytesOut += sizeof(DepthInfo)*count;
    client->flush();

    // read transmit info
    readCon = clusterWindow()->getNetwork()->getMainConnection();
    readCon->selectChannel();

    UInt32 infoCount;
    readCon->getValue(infoCount);
    readCon->get(&transInfo[0],sizeof(TransInfo)*infoCount);
    _statistics.bytesIn += sizeof(TransInfo)*infoCount +sizeof(UInt32);
    uncompressTransInfo(transInfo,infoCount);
    for(y = 0; y < _composeTilesY ; ++y)
    {
        for(x = 0; x < _composeTilesX ; ++x)
        {
            tile = getComposeTileBuffer(x,y);
            tile->trans = transInfo[x + y*_composeTilesX + 
                                    clusterId()*_composeTilesX*_composeTilesY];
            // occluded
            if(tile->trans.empty)
                tile->empty = true;
        }
    }
/*
    clusterWindow()->getNetwork()->getMainConnection()->signal();
    clusterWindow()->getNetwork()->getMainConnection()->wait();
*/
    _statistics.sortTime += getSystemTime();
}    

template<class DepthT,class ColorT>
void PipelineComposer::calculateTransInfo(DepthT &depth,ColorT &color)
{
    Connection::Channel         channel;
    Int32                       id;
    GroupConnection            *servers;
    UInt32                      count = serverCount();
    UInt32                      x,y;
    DepthT                      dmin;
    GroupInfo                  *nextGroup;
    std::vector<DepthInfo>      depthInfo;
    std::vector<TransInfo>      transInfo;
    std::vector<DepthInfo>      depthInfoTmp;
    UInt32                      c;

    depthInfo.resize(_composeTilesX * _composeTilesY * count);
    depthInfoTmp.resize(_composeTilesX * _composeTilesY);
    transInfo.resize(_composeTilesX * _composeTilesY * count);

    double tr=-getSystemTime();

    // read all min max values
    servers = clusterWindow()->getNetwork()->getMainGroupConnection();
    while(servers->getSelectionCount())
    {
        DepthInfo depthCount;
        channel = servers->selectChannel();
        servers->get(&depthCount,sizeof(DepthInfo));
        servers->get(&depthInfoTmp[0],sizeof(DepthInfo)*depthCount.min);
        DepthInfo *src = &depthInfoTmp[0];
        DepthInfo *dst = &depthInfo[_composeTilesX * _composeTilesY * channel];
        for(c=0; c<depthCount.min ; ++c) {
            if(src->min == DepthT(-1)) {
                while(src->max--) {
                    dst->min = DepthT(-1);
                    dst->max = DepthT(-1);
                    dst->occlude = false;
                    dst++;
                }
            } else {
                *dst = *src;
                dst++;
            }
            src++;
        }
        _statistics.bytesIn += sizeof(DepthInfo)*(depthCount.min+1);
        servers->subSelection(channel);
    }
    servers->resetSelection();
    tr += getSystemTime();

    double t=-getSystemTime();

    // sort each group
    for(y = 0; y < _composeTilesY ; ++y)
    {
        for(x = 0; x < _composeTilesX ; ++x)
        {
            for(id = 0 ; id < Int32(count) ; ++id)
            {
                _groupInfo[id]->id    = id;
                _groupInfo[id]->depth = 
                    depthInfo[x+_composeTilesX*y + _composeTilesX*_composeTilesY*id];

                if(_groupInfo[id]->depth.min == DepthT(-1))
                    _statistics.noGeo++;
            }
            // remove occluders
            for(UInt32 id1 = 0 ; id1 < count ; ++id1)
            {
                if(_groupInfo[id1]->depth.occlude) {
                    for(UInt32 id2 = 0 ; id2 < count ; ++id2) {
                        if(id1 != id2 &&
                           _groupInfo[id1]->depth.max < 
                           _groupInfo[id2]->depth.min &&
                           _groupInfo[id2]->depth.min != DepthT(-1))
                        {
                            _groupInfo[id2]->depth.max = DepthT(-1);
                            _groupInfo[id2]->depth.min = DepthT(-1);
                            _groupInfo[id2]->depth.occlude = false;
                            _statistics.occluded++;
                        }
                    }
                }
            }
            // sort
            std::sort(_groupInfo.begin(),
                      _groupInfo.end(),
                      GroupInfoOrder());
            
            // cummulate min through the pipeline
            dmin = _groupInfo[0]->depth.min;
            for(id = 1 ; id < Int32(count) ; ++id)
            {
                if(_groupInfo[id]->depth.min != DepthT(-1))
                {
                    if(dmin < _groupInfo[id]->depth.min)
                        _groupInfo[id]->depth.min = dmin;
                    else
                        dmin = _groupInfo[id]->depth.min;
                }
            }

            getComposeTileBuffer(x,y)->empty = true;
            // determine send to
            nextGroup = NULL;
            for(id = count-1 ; id >= 0 ; --id)
            {
                _groupInfo[id]->trans.sendDepth = true;
                _groupInfo[id]->trans.first = true;
                _groupInfo[id]->trans.empty = false;
                if(_groupInfo[id]->depth.min == DepthT(-1))
                {
                    _groupInfo[id]->trans.empty = true;
                }        
                else
                {
                    if(nextGroup)
                    {
                        _groupInfo[id]->trans.sendTo = nextGroup->id;
                        nextGroup->trans.first = false;
                        if(_groupInfo[id]->depth.min >
                           nextGroup->depth.max)
                        {
                            _groupInfo[id]->trans.sendDepth = false;
                            _statistics.noDepth++;
                        }
                    }
                    else
                    {
                        // send to client
                        _groupInfo[id]->trans.sendTo    = count;
                        _groupInfo[id]->trans.sendDepth = false;
                        getComposeTileBuffer(x,y)->empty = false;
                        _statistics.noDepth++;
                    }
                    nextGroup = _groupInfo[id];
                }
            }

            for(id = 0 ; id < Int32(count) ; ++id)
            {
                transInfo[_groupInfo[id]->id * _composeTilesX * _composeTilesY +
                          x + y * _composeTilesX] = _groupInfo[id]->trans;
            }
#if 0
            for(id = 0 ; id < count ; ++id)
                printf("%d -> %d | ",_groupInfo[id]->id,_groupInfo[id]->trans.sendTo);
            printf("\n");
#endif

#if 0
            int sum=0;
            if(y==0 && x==0)
                printf("\n");
            if(x==0)
                printf("\n");
            for(id = 0 ; id < count ; ++id)
            {
                if(!_groupInfo[id]->trans.empty)
                    sum++;
            }
            printf("%d ",sum);
#endif
        }
    }
//    std::vector<TransInfo> ti=transInfo;
    UInt32 infoCount = compressTransInfo(transInfo);

    t+=getSystemTime();
/*
    printf("\nsetup time %lf\n",t);
    printf("read  time %lf\n",tr);
*/

    clusterWindow()->getNetwork()->getMainConnection()->putValue(infoCount);
    clusterWindow()->getNetwork()->getMainConnection()->put(
        &transInfo[0],infoCount*sizeof(TransInfo));
    _statistics.bytesOut += infoCount*_composeTilesY*count*sizeof(TransInfo);
    clusterWindow()->getNetwork()->getMainConnection()->flush();
}

template<class DepthT,class ColorT>
void PipelineComposer::clientCompose(DepthT &depth,ColorT &color)
{
    GroupConnection   *servers;
    UInt32             tx,ty;
    UInt32             recvCount=0;
    TileBuffer        *readTile = getWorkingTileBuffer();
#ifdef COMPRESS_IMAGES
    std::vector<UInt32> src;
    src.resize(512*512*8);
    UInt32 dstLen,srcLen;
#endif

    servers = clusterWindow()->getNetwork()->getGroupConnection(clusterId());

    for(ty = 0; ty < _composeTilesY ; ++ty)
        for(tx = 0; tx < _composeTilesX ; ++tx)
            if(!getComposeTileBuffer(tx,ty)->empty)
                recvCount++;

//    printf("expect %d \n",recvCount);

    while(recvCount--)
    {
        Connection::Channel c = servers->selectChannel();
#ifdef COMPRESS_IMAGES
        servers->get(&srcLen,sizeof(UInt32));
        servers->get(&src[0],srcLen);
        dstLen = lzf_decompress (&src[0],srcLen,
                        &(readTile->header),512*512*8);
#else
        servers->get(&(readTile->header),
                     sizeof(readTile->header));
#endif
        // printf("%d from %d %d\n",recvCount,c,readTile->header.count);

#ifndef COMPRESS_IMAGES
        servers->get(&(readTile->data),
                     readTile->header.w*
                     readTile->header.h*
                     sizeof(ColorT));
#endif
        _statistics.bytesIn += 
                     sizeof(readTile->header)+
                     readTile->header.w*
                     readTile->header.h*
                     sizeof(ColorT);

        // draw
        glRasterPos2f(readTile->header.x * getTileSize(),
                      readTile->header.y * getTileSize());

        glDrawPixels(readTile->header.w, 
                     readTile->header.h,
                     _colorFormat,
                     _colorType,
                     readTile->data);
    }
}

template<class DepthT,class ColorT>
void PipelineComposer::serverCompose(DepthT &depth,ColorT &color)
{
    UInt32             tx,ty;
    TileBuffer        *tile;
    UInt32             sendCount=0;
    UInt32             recvCount=0;
    GroupConnection   *srcConn;
    TileBuffer        *readTile = getWorkingTileBuffer();
    DepthT            *srcDepth,*dstDepth,*srcDepthEnd,*dstDepthEnd;
    ColorT            *srcColor=NULL,*dstColor=NULL;
#ifdef COMPRESS_IMAGES
    std::vector<UInt32> src;
    src.resize(512*512*8);
    UInt32 dstLen;
    UInt32 srcLen;
#endif

    for(ty = 0; ty < _composeTilesY ; ++ty)
        for(tx = 0; tx < _composeTilesX ; ++tx)
        {
            tile = getComposeTileBuffer(tx,ty);
            if(!tile->empty)
            {
                sendCount++;
                if(!tile->trans.first)
                    recvCount++;
            }
        }

    // semd all tiles 
    for(ty = 0; ty < _composeTilesY ; ++ty)
    {
        for(tx = 0; tx < _composeTilesX ; ++tx)
        {
            tile = getComposeTileBuffer(tx,ty);
            if(!tile->empty && tile->trans.first)
            {
                // send first tiles 
                _lock->acquire();
                tile->header.count = --sendCount;
                tile->dstConnection = clusterWindow()->
                    getNetwork()->getConnection(tile->trans.sendTo);
                _queue.push_back(tile);
                if(_waiting)
                {
                    _lock   ->release( );
                    _barrier->enter  (2);
                }
                else
                {
                    _lock->release();
                }

                if(tile->trans.sendDepth)
                    _statistics.bytesOut += tile->dataSize + sizeof(tile->header);
                else
                    _statistics.bytesOut += tile->colorSize + sizeof(tile->header);
            }
        }
    }

    srcConn = clusterWindow()->getNetwork()->getGroupConnection(clusterId());

    // recv all tiles
    while(recvCount--)
    {
        srcConn->selectChannel();
#ifdef COMPRESS_IMAGES
        srcConn->get(&srcLen,sizeof(UInt32));
        srcConn->get(&src[0],srcLen);
        dstLen = lzf_decompress (&src[0],srcLen,
                                 &(readTile->header),512*512*8);
        _statistics.bytesIn += srcLen + sizeof(UInt32);
//        printf("Ratio %f\n",srcLen*100.0/dstLen);
#else
        srcConn->get(&readTile->header,sizeof(readTile->header));
        _statistics.bytesIn += sizeof(readTile->header);
#endif

        tile = getComposeTileBuffer(readTile->header.x,readTile->header.y);
        srcDepth    = 
            reinterpret_cast<DepthT*>(readTile->data + tile->colorSize);
        srcColor    = reinterpret_cast<ColorT*>(readTile->data);
        dstDepth    = reinterpret_cast<DepthT*>(tile->data + tile->colorSize);
        dstColor    = reinterpret_cast<ColorT*>(tile->data);
        if(readTile->header.depth)
        {
            // compose with depth
#ifndef COMPRESS_IMAGES
            srcConn->get(readTile->data,tile->dataSize);
            _statistics.bytesIn += tile->dataSize;
#endif

            // compose
            srcDepthEnd = reinterpret_cast<DepthT*>(readTile->data + 
                                                    tile->dataSize);
            while(srcDepth < srcDepthEnd)
            {
//                *(char*)srcColor -=22;
//                *(char*)dstColor +=22;
                if(*srcDepth <= *dstDepth)
                {
                    *dstColor = *srcColor;
                    *dstDepth = *srcDepth;
                }
                srcDepth++;
                dstDepth++;
                srcColor++;
                dstColor++;
            }
        }
        else
        {
            // compose without depth
#ifndef COMPRESS_IMAGES
            srcConn->get(readTile->data,tile->colorSize);
            _statistics.bytesIn += tile->colorSize;
#endif

            // compose
            dstDepthEnd = reinterpret_cast<DepthT*>(tile->data + 
                                                    tile->dataSize);
            while(dstDepth < dstDepthEnd)
            {
                if(*dstDepth == DepthT(-1))
                    *dstColor = *srcColor;
                dstDepth++;
                srcColor++;
                dstColor++;
            }
        }

        // put to send queue
        _lock->acquire();
        tile->header.count = --sendCount;
        tile->dstConnection = clusterWindow()->
            getNetwork()->getConnection(tile->trans.sendTo);
        _queue.push_back(tile);
        if(_waiting)
        {
            _lock   ->release( );
            _barrier->enter  (2);
        }
        else
        {
            _lock->release();
        }
#ifndef COMPRESS_IMAGES
        if(tile->trans.sendDepth)
            _statistics.bytesOut += tile->dataSize + sizeof(tile->header);
        else
            _statistics.bytesOut += tile->colorSize + sizeof(tile->header);
#endif
    }

    // wake up sender thread, so it can finish transmitting queued tiles
    _lock->acquire();
    if(_waiting)
    {
        _lock   ->release( );
        _barrier->enter  (2);
    }
    else
    {
        _lock->release();
    }
}

template<class DepthT,class ColorT>
void PipelineComposer::writeResult(DepthT &depth,ColorT &color)
{
    TileBuffer   *tile;

#ifdef COMPRESS_IMAGES
    std::vector<UInt32> dst;
    dst.resize(512*512*8);
#endif
    for(;;)
    {
        _lock->acquire();
        while(_queue.empty())
        {
            _waiting = true;
            _lock   ->release( );
            _barrier->enter  (2);
            _lock   ->acquire( );
        }

        _waiting = false;
        tile     = _queue.front();
        _queue.pop_front();
        _lock->release();

        if(tile == NULL)
            break;

        if(tile->trans.sendDepth)
        {
            tile->header.depth = true;
#ifdef COMPRESS_IMAGES
            dst[0] = lzf_compress(&(tile->header),
                                  tile->dataSize + sizeof(tile->header),
                                  &dst[1],512*512*8);
            tile->dstConnection->put(&dst[0],dst[0]+sizeof(UInt32));
            _statistics.bytesOut += dst[0]+sizeof(UInt32);
#else

            tile->dstConnection->put(&(tile->header),
                                     tile->dataSize +
                                     sizeof(tile->header));
#endif
        }
        else
        {
            tile->header.depth = false;
#ifdef COMPRESS_IMAGES
            dst[0] = lzf_compress(&(tile->header),
                                  tile->colorSize + sizeof(tile->header),
                                  &dst[1],512*512*8);
            tile->dstConnection->put(&dst[0],dst[0]+sizeof(UInt32));
            _statistics.bytesOut += dst[0]+sizeof(UInt32);
#else
            tile->dstConnection->put(&(tile->header),
                                     tile->colorSize +
                                     sizeof(tile->header));
#endif
        }
        tile->dstConnection->flush();
    }
}

template<class DepthT,class ColorT>
void PipelineComposer::readBuffer(DepthT &depth,ColorT &color,
                                  Viewport *port)
{
    UInt32      left,bottom,top,right,front,back;
    UInt32      width,height;
    UInt32      tx,ty,x,y,w,h;
    TileBuffer *tile;
#if 0
    DepthT     *depthEnd;
#endif
    DepthT     *depthPtr;
    DepthT      depthMin;
    DepthT      depthMax;
    bool        occlude;

    if(isClient())
        return;
    width  = port->getPixelWidth();
    height = port->getPixelHeight();
    if(!getScreenAlignedBBox(port->getRoot(),
                             port,
                             left,bottom,right,top,front,back))
    {
        left = right = width;
        top = bottom = height;
    }
    width = port->getPixelWidth();
    height = port->getPixelHeight();

    _statistics.pixelReadTime = -getSystemTime();
#ifdef USE_NV_OCCLUSION
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glColorMask(false,false,false,false);
    glDepthMask(false);
#endif

    for(ty = 0; ty < _readTilesY ; ++ty)
    {
        for(tx = 0; tx < _readTilesX ; ++tx)
        {
            occlude = true;

            x = tx * getTileSize();
            y = ty * getTileSize();
            w = osgMin(getTileSize(),width - x);
            h = osgMin(getTileSize(),height - y);

            tile = getReadTileBuffer(tx,ty);
            tile->header.x = tx;
            tile->header.y = ty;
            tile->header.w = w;
            tile->header.h = h;
            tile->colorSize = sizeof(ColorT)*w*h;
            tile->depthSize = sizeof(DepthT)*w*h;
            tile->dataSize  = tile->colorSize + tile->depthSize;

            if(x > right || (x+w) <= left ||
               y > top   || (y+h) <= bottom)
            {
                tile->depth.min     = DepthT(-1);
                tile->depth.max     = DepthT(-1);
                tile->depth.occlude = false;
                tile->empty = true;
                _statistics.clipped++;
                continue;
            }

            tile->empty = false;

#ifdef USE_NV_OCCLUSION
            // fast empty test
            glBeginOcclusionQueryNV(_occlusionQuery);
            glBegin(GL_QUADS);
            glColor3f(0,1,0);
            glVertex3f(x    ,y    ,-1);
            glVertex3f(x+w  ,y    ,-1);
            glVertex3f(x+w  ,y+h  ,-1);
            glVertex3f(x    ,y+h  ,-1);
            glEnd();
            glEndOcclusionQueryNV();
            GLuint samples=-1;
            glGetOcclusionQueryuivNV(_occlusionQuery, GL_PIXEL_COUNT_NV, &samples);
            _statistics.occluded+=samples - w*h;
            if(samples == w*h)
            {
                tile->depth.min     = (DepthT)-1;
                tile->depth.max     = (DepthT)-1;
                tile->depth.occlude = false;
                tile->empty = true;
#if 1
                glColorMask(true,true,true,true);
                glBegin(GL_QUADS);
                glColor3f(1,0,0);
                glVertex3f(x    ,y    ,-1);
                glVertex3f(x+w  ,y    ,-1);
                glVertex3f(x+w  ,y+h  ,-1);
                glVertex3f(x    ,y+h  ,-1);
                glEnd();
                glColorMask(false,false,false,false);
#endif
                continue;
            }
#endif
            // read depth
            glReadPixels(x, y, w, h, 
                         GL_DEPTH_COMPONENT, _depthType,
                         tile->data+tile->colorSize);

            // old version
#if 0
            depthPtr = (DepthT*)(tile->data + tile->colorSize);
            depthEnd = (DepthT*)(tile->data + 
                                 tile->colorSize +
                                 tile->depthSize);

            for( ; depthPtr != depthEnd && *depthPtr == (DepthT)(-1) ; ++depthPtr)
                occlude = false;
            if(depthPtr != depthEnd)
            {
                depthMin = depthMax = *depthPtr;
                for( ; depthPtr != depthEnd ; ++depthPtr)
                {
                    if(*depthPtr > depthMax)
                        if(*depthPtr != (DepthT)(-1))
                            depthMax = *depthPtr;
                        else
                            occlude = false;
                    else
                        if(*depthPtr < depthMin)
                            depthMin = *depthPtr;
                }
            }
            else
            {
                depthMin = depthMax = (DepthT)-1;
                occlude  = false;
            }
#else
            depthPtr = reinterpret_cast<DepthT*>(tile->data + tile->colorSize);
            // new version
            occlude = checkDepth<DepthT, DepthT(-1)>(
                depthPtr,
                depthMin,
                depthMax,
                w*h);
#endif
            if(depthMin == DepthT(-1))
                tile->empty = true;
            else
                tile->empty = false;

            tile->depth.min     = depthMin;
            tile->depth.max     = depthMax;
            tile->depth.occlude = occlude;

            if(!tile->empty)
            {
                glReadPixels(x, y, w, h, 
                             _colorFormat,_colorType,
                             tile->data);
            }
        }
    }

#ifdef USE_NV_OCCLUSION
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glColorMask(true,true,true,true);
    glDepthMask(true);
#endif
    _statistics.pixelReadTime += getSystemTime();

    // sync with compose thread
    if(getPipelined()) 
        _composeBarrier->enter(2);

    // swap buffers
    std::vector<UInt8> *save = _composeTilePtr;
    _composeTilePtr = _readTilePtr;
    _readTilePtr = save;

    // transfer tile size
    _composeTilesX  = _readTilesX;
    _composeTilesY  = _readTilesY;
    
}

template<class DepthT,class ColorT>
void PipelineComposer::composeBuffer(DepthT &depth,ColorT &color)
{
    // TODO use firstframe flag!!
    if(getPipelined() && _firstFrame) 
    {
        if(!isClient()) 
        {
            _composeBarrier->enter(2);
            _composeBarrier->enter(2);
        }
        _firstFrame = false;
        return;
    }
    if(isClient())
    {
        calculateTransInfo(depth,color);
        _statistics.composeTime = -getSystemTime();
        clientCompose(depth,color);
        _statistics.composeTime += getSystemTime();
    }
    else
    {
        // sync with read thread
        if(getPipelined()) 
            _composeBarrier->enter(2);
        setTransInfo(depth,color);
        serverCompose(depth,color);
        if(getPipelined()) 
            _composeBarrier->enter(2);
    }
}

/*! check depth of a tile.
 */
template <class T,T empty>
bool PipelineComposer::checkDepth(T *buffer,T &front,T &back,int size)
{
    T    *i        = buffer;
    T    *end      = buffer+size-1;
    bool  occlude  = true;
    T     endValue = *end;

    // start with last value
    back = front = *end;
    if(*end == empty) {
        back = 0;
        occlude = false;
    }
    while(i != end) {
        // check not empty
        *end = empty;
        while(*i != empty) {
            if(*i < front)
                front = *i;
            if(*i > back)
                back = *i;
            ++i;
        }
        if(i!=end) {
            occlude = false;
            // check empty
            *end = 0;
            // check for empty tile
            while(*i == empty) 
                ++i;
        }
    }
    if(front > back) {
        back = front = empty;
    }    
    *end = endValue;
    return occlude;
}

OSG_END_NAMESPACE

