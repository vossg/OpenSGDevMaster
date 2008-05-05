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

template<class DepthT,class ColorT>
void BinarySwapComposer::sendToClient(DepthT &depth,
                                      ColorT &color,
                                      UInt32 left,
                                      UInt32 bottom,
                                      UInt32 right,
                                      UInt32 top)
{
    // send the resulting tile to the client
    Connection *client = 
        clusterWindow()->getNetwork()->getConnection(clusterId());

    UInt32      tx,ty;
    TileBuffer *tile;
    UInt32      lastx = right + 1;
    UInt32      lasty = top   + 1;

    for(ty = bottom; ty <= top ; ++ty)
    {
        for(tx = left; tx <= right ; ++tx)
        {
            if(!getTileBuffer(tx,ty)->empty)
            {
                lastx=tx;
                lasty=ty;
            }
        }
    }

    for(ty = bottom; ty <= top ; ++ty)
    {
        for(tx = left; tx <= right ; ++tx)
        {
            tile = getTileBuffer(tx,ty);

            if(!tile->empty)
            {
                if(ty == lasty && tx == lastx)
                    tile->header.x^=0x8000;

                client->put(&(tile->header),
                            tile->colorSize +
                            sizeof(tile->header));

                client->flush();

                _statistics.bytesOut +=
                    tile->colorSize + sizeof(tile->header);
            }
        }
    }

    if(lastx == right + 1)
    {
        TileBuffer t;

        t.header.x=0x8000;
        t.header.y=0x8000;

        client->put(&(t.header),
                    sizeof(t.header));

        client->flush();

        _statistics.bytesOut += sizeof(t.header);
    }
}

template<class DepthT,class ColorT>
void BinarySwapComposer::recvFromServers(DepthT &depth,
                                         ColorT &color,
                                         UInt32 colorType,
                                         UInt32 colorFormat,
                                         Viewport *port)
{
    UInt32      missing  = _usableServers;
    TileBuffer *readTile = getTileReadBuffer();
    GroupConnection *servers  = 
        clusterWindow()->getNetwork()->getGroupConnection(clusterId());

    Connection::Channel channel;

    while(missing)
    {
        channel = servers->selectChannel();

        servers->get(&(readTile->header),
                     sizeof(readTile->header));

        _statistics.bytesIn += sizeof(readTile->header);

        if(readTile->header.x & 0x8000)
        {
            readTile->header.x ^= 0x8000;
            servers->subSelection(channel);
            missing--;
        }

        if(!(readTile->header.y & 0x8000))
        {
            servers->get(readTile->data,
                         readTile->header.w*readTile->header.h*
                         sizeof(ColorT));

            _statistics.bytesIn += 
                readTile->header.w * readTile->header.h * sizeof(ColorT);

            glRasterPos2f(readTile->header.x * getTileSize(),
                          readTile->header.y * getTileSize());
            glDrawPixels(readTile->header.w, 
                         readTile->header.h,
                         colorType, colorFormat,readTile->data);
        }
    }

    servers->resetSelection();
}

template<class DepthT,class ColorT>
void BinarySwapComposer::writeCombine(DepthT &depthDummy,ColorT &colorDummy)
{
    UInt32 tx,ty;
    TileBuffer *tile;
    UInt32 lastx,lasty;

    for(;;)
    {
        _barrier->enter(2);
        _barrier->enter(2);

        if(_swapWith >= _usableServers)
            break;

        lastx = _writeRight + 1;
        lasty = _writeTop   + 1;

        for(ty = _writeBottom; ty <= _writeTop ; ++ty)
        {
            for(tx = _writeLeft; tx <= _writeRight ; ++tx)
            {
                if(!getTileBuffer(tx,ty)->empty)
                {
                    lastx=tx;
                    lasty=ty;
                }
            }
        }

        for(ty = _writeBottom; ty <= _writeTop ; ++ty)
        {
            for(tx = _writeLeft; tx <= _writeRight ; ++tx)
            {
                tile = getTileBuffer(tx,ty);

                if(!tile->empty)
                {
                    if(ty == lasty &&
                       tx == lastx)
                        tile->header.x^=0x8000;

                    _swapConnection->put(&(tile->header),
                                         tile->dataSize +
                                         sizeof(tile->header));

                    _swapConnection->flush();

                    _statistics.bytesOut += 
                        tile->dataSize + sizeof(tile->header);

                    if(ty == lasty && tx == lastx)
                        tile->header.x^=0x8000;
                }                    
            }
        }
        // no data, write single header
        if(lastx == _writeRight + 1)
        {
            TileBuffer t;
            t.header.x=0x8000;
            t.header.y=0x8000;
            _swapConnection->put(&(t.header),
                                 sizeof(t.header));
            _statistics.bytesOut += sizeof(t.header);
        }
    }
}

template<class DepthT,class ColorT>
void BinarySwapComposer::readCombine(DepthT &depth,
                                     ColorT &color,
                                     UInt32 colorType,
                                     UInt32 colorFormat,
                                     UInt32 left,
                                     UInt32 bottom,
                                     UInt32 right,
                                     UInt32 top,
                                     UInt32 level)
{
    UInt32      w,h;
    UInt32      aRight,bLeft,aTop,bBottom;
    UInt32      readLeft,readRight,readTop,readBottom;
    UInt32      tx,ty;
    TileBuffer *tile;
    TileBuffer *readTile=getTileReadBuffer();
    DepthT     *srcDepth,*dstDepth,*srcDepthEnd;
    ColorT     *srcColor,*dstColor;
    bool        last=false;
    ColorT      nullColor;

    memset(&nullColor,0,sizeof(ColorT));
    _barrier->enter(2);
    _swapWith = clusterId() ^ level;

    if(_swapWith >= _usableServers)
    {
        _barrier->enter(2);
        // send the resulting tile to the client
        sendToClient(depth,color,
                     left,bottom,right,top);
        return;
    }
    _swapConnection = clusterWindow()->getNetwork()->getConnection(_swapWith);

    w = right - left   + 1;
    h = top   - bottom + 1;

    if(w > h)
    {
        aRight  = left + (w/2);
        aTop    = top;
        bLeft   = aRight + 1;
        bBottom = bottom;
    }
    else
    {
        aRight  = right;
        aTop    = bottom + (h/2);
        bLeft   = left;
        bBottom = aTop + 1;
    }
    if(clusterId() > _swapWith)
    {
        _writeLeft   = left;
        _writeBottom = bottom;
        _writeRight  = aRight;
        _writeTop    = aTop;

        readLeft     = bLeft;
        readBottom   = bBottom;
        readRight    = right;
        readTop      = top;
    }
    else
    {
        _writeLeft   = bLeft;
        _writeBottom = bBottom;
        _writeRight  = right;
        _writeTop    = top;

        readLeft     = left;
        readBottom   = bottom;
        readRight    = aRight;
        readTop      = aTop;
    }
    _barrier->enter(2);
    // send
    _swapConnection->selectChannel();
    do
    {
        _swapConnection->get(&(readTile->header),
                             sizeof(readTile->header));
        _statistics.bytesIn += sizeof(readTile->header);
        if(readTile->header.x&0x8000)
        {
            last = true;
            readTile->header.x^=0x8000;
        }
        if(!(readTile->header.y & 0x8000))
        {
            tile = getTileBuffer(readTile->header.x,
                                 readTile->header.y);
            if(tile->empty)
            {
                // dest is empty, overwrite
                _swapConnection->get(tile->data,
                                     tile->dataSize);
                _statistics.bytesIn += tile->dataSize;
                if(sizeof(ColorT) == 4)
                {
                    glRasterPos2f(tile->header.x * getTileSize(),
                                  tile->header.y * getTileSize());
                    glDrawPixels(tile->header.w,tile->header.h,
                                 colorType, colorFormat,
                                 tile->data);
                }
                tile->empty = false;
            }
            else
            {
                // read 
                _swapConnection->get(readTile->data,
                                     tile->dataSize);
                _statistics.bytesIn += tile->dataSize;
                // depth compose
                srcDepth    = (DepthT*)(readTile->data + tile->colorSize);
                srcDepthEnd = (DepthT*)(readTile->data + 
                                        tile->dataSize);
                srcColor    = (ColorT*)(readTile->data);
                dstDepth    = (DepthT*)(tile->data + tile->colorSize);
                dstColor    = (ColorT*)(tile->data);
                // compose
                if(sizeof(ColorT) == 4)
                {
                    // with alpha
                    while(srcDepth < srcDepthEnd)
                    {
                        if(*srcDepth <= *dstDepth)
                            *dstDepth = *srcDepth;
                        else
                            *srcColor = nullColor;
                        srcDepth++;
                        dstDepth++;
                        srcColor++;
                    }
                    // hardware alpha combine
                    glRasterPos2f(tile->header.x * getTileSize(),
                                  tile->header.y * getTileSize());
                    glDrawPixels(tile->header.w,tile->header.h,
                                 colorType, colorFormat,
                                 readTile->data);
                    glReadPixels(tile->header.x * getTileSize(),
                                 tile->header.y * getTileSize(),
                                 tile->header.w,tile->header.h,
                                 colorType, colorFormat,
                                 tile->data);
                }
                else
                {
                    // no alpha
                    while(srcDepth < srcDepthEnd)
                    {
                        if(*srcDepth < *dstDepth)
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
            }
        }
    }
    while(!last);
    readCombine(depth,color,
                colorType,colorFormat,
                readLeft,readBottom,readRight,readTop,level<<1);
}

template<class DepthT,class ColorT>
void BinarySwapComposer::startReader(DepthT &depthMax,
                                     ColorT &color,
                                     UInt32 depthFormat,
                                     UInt32 colorType,
                                     UInt32 colorFormat,
                                     Viewport *port)
{
    UInt32      tx,ty,x,y,w,h;
    TileBuffer *tile;
    UInt32      left,bottom,top,right,front,back;
    UInt32      level=1;
    DepthT     *depthStart,*depthEnd;
    UInt8      *c,*cEnd;

    if(!getScreenAlignedBBox(port->getRoot(),
                             port,
                             left,bottom,right,top,front,back))
    {
        left=right=clusterWindow()->getWidth();
        top=bottom=clusterWindow()->getHeight();
        front=back=(UInt32)(-1);
    }

    for(ty = 0; ty < _tilesY ; ++ty)
    {
        for(tx = 0; tx < _tilesX ; ++tx)
        {
            x = tx * getTileSize();
            y = ty * getTileSize();
            w = osgMin(getTileSize(),port->getPixelWidth() - x);
            h = osgMin(getTileSize(),port->getPixelHeight() - y);
            tile = getTileBuffer(tx,ty);
            tile->header.x = tx;
            tile->header.y = ty;
            tile->header.w = w;
            tile->header.h = h;
            tile->colorSize = sizeof(ColorT)*w*h;
            tile->depthSize = sizeof(DepthT)*w*h;
            tile->dataSize  = tile->colorSize + tile->depthSize;
            if(x > right ||
               (x+w) <= left ||
               y > top ||
               (y+h) <= bottom)
            {
                tile->empty = true;
                continue;
            }
            tile->empty = false;
            glReadPixels(x, y, w, h, 
                         GL_DEPTH_COMPONENT, depthFormat,
                         tile->data+tile->colorSize);
#ifdef OPTIMIZED_BINARY_SWAP
            if(sizeof(ColorT) != 4)
            {
                depthStart = (DepthT*)(tile->data + tile->colorSize);
                depthEnd   = (DepthT*)(tile->data + 
                                       tile->colorSize +
                                       tile->depthSize);
                // empty if no depth
                while(depthStart < depthEnd &&
                      *depthStart == (DepthT)depthMax)
                    ++depthStart;
                if(depthStart == depthEnd)
                    tile->empty = true;
            }
#endif
            if(!tile->empty)
            {
                glReadPixels(x, y, w, h, 
                             colorType, colorFormat,
                             tile->data);
                if(sizeof(ColorT) == 4)
                {
                    // in alpha mode, only empty if alpha is 0
                    c    = tile->data + 3;
                    cEnd = tile->data + 3 + w * h * 4;
                    while(c != cEnd && *c == 0)
                        c += 4;
                    if(c == cEnd)
                        tile->empty = true;
                }
            }
        }
    }

    _barrier->enter(2);
    readCombine(depthMax,color,
                colorType,colorFormat,
                0,0,_tilesX-1,_tilesY-1,1);

}

OSG_END_NAMESPACE

