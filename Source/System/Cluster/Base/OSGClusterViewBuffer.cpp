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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGClusterViewBuffer.h"
#include "OSGImageFileHandler.h"
#include "OSGImageFileType.h"
#include "OSGPointConnection.h"
#include "OSGGroupConnection.h"

OSG_USING_NAMESPACE

/*! \class OSG::ClusterViewBuffer
   \ingroup GrpSystemCluster
   \brief Viewbuffer functions

   This class provides an interface to an OpenGL view buffer.
   The Buffer contents can be transfered over a Connection.
   All Image types can be used for image compression. The
   ClusterViewBuffer can access RGBA, Stencil and Z-Buffer values.

   The whole imagebuffer is divided into subtiles. Each subtile
   is read from the buffer, compressed and send over the nertwork.
   In most cases, the buffer read and the network send of the previous
   tile is done in parallel.

   todo: currently ClusterViewBuffer works on the activated window.
         Is this a good idea. Better WindowPtr as parameter and then
         call activate before send,recv? MR
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors/Destructor                      */

/*! Initialize a ClusterViewBuffer. By default, no image compression
    is set and the subtile size is set to 32. The viewbuffer contents
    is send in packages. If the package size is not too large, then 
    network transmission of the last and graphics card read of the current
    package is done in parallel. 
 */

ClusterViewBuffer::ClusterViewBuffer(void) :
    _imgTransType (NULL            ),
    _subTileSize  (32              ),
    _rgbDataType  (GL_UNSIGNED_BYTE),
    _rgbDataSize  (3               ),
    _rgbaDataType (GL_UNSIGNED_BYTE),
    _rgbaDataSize (4               ),
    _depthDataType(GL_UNSIGNED_INT ),
    _depthDataSize(4               )
{
}

/*! Destructor
 */

ClusterViewBuffer::~ClusterViewBuffer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            send/recv                                    */

/*! Receive image data from all channels of a conneciton. The receive is
 *  finished, when the last channel signals a transmission end.
 */

void ClusterViewBuffer::recv(GroupConnection &connection)
{
    UInt32              tx, ty, tw, th;
    UInt32              missing;
    BufferT             data;
    BufferT             imageData;
    UInt32              dataSize;
    UInt32              component;
    GLenum              glformat;
    int                 componentCnt;
    Connection::Channel channel;

    missing = connection.getChannelCount();

    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, getBufferWidth(), 0, getBufferHeight());
    glDisable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // we expect tiles form all connected servers
    while(missing)
    {
        channel = connection.selectChannel();
        connection.getValue(component);
        if(!component)
        {
            connection.subSelection(channel);
            missing--;
            continue;
        }

        // get dimension
        connection.getValue(tx);
        connection.getValue(ty);
        connection.getValue(tw);
        connection.getValue(th);
        glRasterPos2i(tx, ty);

        // =========== recv stencil =====================================
        if(component & STENCIL)
        {
            data.resize(tw * th);
            connection.get(&data[0], tw * th);
            glDrawPixels(tw, th, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &data[0]);
            glEnable(GL_STENCIL_TEST);
        }

        // =========== recv depth =======================================
        if(component & DEPTH)
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_ZERO, GL_REPLACE);
            data.resize(tw * th * sizeof(float));
            connection.get(&data[0], tw * th * sizeof(float));
            glDrawPixels(tw, th, GL_DEPTH_COMPONENT, GL_FLOAT, &data[0]);
            glDisable(GL_DEPTH_TEST);
        }

        // =========== recv RGBA ========================================
        if(component & RGBA)
        {
            if(component & (DEPTH | STENCIL))
            {
                glStencilFunc(GL_EQUAL, 1, 1);
            }

            switch(component & RGBA)
            {
                case RGB:
                    glformat = GL_RGB;
                    componentCnt = 3;
                    break;
                case RGBA:
                    glformat = GL_RGBA;
                    componentCnt = 4;
                    break;
                default:
                    SFATAL << "Component combination not supported"
                           << std::endl;
                    return;
            }

            connection.getValue(dataSize);

            // compression ?
            if(dataSize > 0)
            {
#if 0
                pImage = new Image;

                data.resize(dataSize);
                connection.get(&data[0], dataSize);
                imageData.resize(tw * th * componentCnt);
                ImageFileType::restore(*pImage, (UChar8 *) &data[0], dataSize);
                glDrawPixels(tw, th, glformat, GL_UNSIGNED_BYTE,
                                             pImage->getData());

                subRefP(pImage);
#endif
            }
            else
            {
                data.resize(tw * th * componentCnt);
                connection.get(&data[0], tw * th * componentCnt);
                glDrawPixels(tw, th, glformat, GL_UNSIGNED_BYTE, &data[0]);
            }
        }

        if(component & (DEPTH | STENCIL))
        {
            glDisable(GL_STENCIL_TEST);
        }
    }
    connection.resetSelection();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

/*! Send parts of a view buffer to a Connection

    \a connection defines the connection to use, \a component which color
    channels (RGB/RGBA) should be transferred, \a x1, \a y1, \a x2, \a y2
    (inclusive) define the source area and \a toX and \a toY the lower left
    corner of the destination area.
*/
void ClusterViewBuffer::send(PointConnection &connection, 
                             UInt32           component, 
                             UInt32           x1,
                             UInt32           y1, 
                             UInt32           x2, 
                             UInt32           y2, 
                             UInt32           toX,
                             UInt32           toY)
{
    UInt32              tx, ty, tw, th;
//    Image               *pImage;
    BufferT             data;
    BufferT             imageData;
    UInt32              dataSize;
    GLenum              glformat;
//    Image::PixelFormat  imgformat;
    int                 componentCnt;
    int                 imgtranssize = 0;

    switch(component & RGBA)
    {
        case RGB:
            glformat = GL_RGB;
//               imgformat = Image::OSG_RGB_PF;
            componentCnt = 3;
            break;
        case RGBA: 
            glformat = GL_RGBA;
//               imgformat = Image::OSG_RGBA_PF;
            componentCnt = 4;
            break;
        default:   
            SFATAL << "Component combination not supported" 
                   << std::endl;
            return;
    }

    // resize image buffer
    imageData.resize(_subTileSize * _subTileSize * componentCnt);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    for(ty = y1; ty <= y2; ty += _subTileSize)
    {
        for(tx = x1; tx <= x2; tx += _subTileSize)
        {
            tw = osgMin(_subTileSize, x2 + 1 - tx);
            th = osgMin(_subTileSize, y2 + 1 - ty);

            connection.putValue(component);
            connection.putValue(tx + toX);
            connection.putValue(ty + toY);
            connection.putValue(tw);
            connection.putValue(th);

            // =========== send STENCIL =======================================
            if(component & STENCIL)
            {
                // read stencil buffer
                data.resize(tw * th);
                glReadPixels(tx, 
                             ty, 
                             tw, 
                             th, 
                             GL_STENCIL_INDEX, 
                             GL_UNSIGNED_BYTE,
                             &data[0]);

                connection.put(&data[0], tw * th);
            }

            // =========== send DEPTH =======================================
            if(component & DEPTH)
            {
                // read stencil buffer
                data.resize(tw * th * sizeof(float));
                glReadPixels(tx, ty, tw, th, GL_DEPTH_COMPONENT, GL_FLOAT,
                                             &data[0]);
                connection.put(&data[0], tw * th * sizeof(float));
            }

            // =========== send RGBA ========================================
            if(component & RGBA)
            {
                // use compression ?
                if(_imgTransType)
                {
#if 0
                    // set image size
                    pImage = new Image;

                    pImage->set(imgformat, tw, th, 1, 1, 1, 0.0,
                                (UChar8 *) &imageData[0]);

                    // read buffer data into image
                    glReadPixels(tx, ty, tw, th, glformat, GL_UNSIGNED_BYTE,
                                 pImage->getData());

                    // bug maxsize is not big enugh
                    data.resize(_imgTransType->maxBufferSize(*pImage) + 1000);
                    dataSize = _imgTransType->store(*pImage, (UChar8 *) &data[0],
                                                                        data.size());
                    connection.putValue(dataSize);
                    connection.put(&data[0], dataSize);
                    imgtranssize += dataSize;

                    subRefP(pImage);
#endif
                }
                else
                {
                    data.resize(tw * th * componentCnt);

                    // read buffer data
                    glReadPixels(tx, ty, tw, th, glformat, GL_UNSIGNED_BYTE,
                                                     &data[0]);
                    dataSize = 0;
                    connection.putValue(dataSize);
                    connection.put(&data[0], tw * th * componentCnt);
                    imgtranssize += tw * th * componentCnt;
                }
            }

            connection.flush();
        }
    }

    component = 0;
    connection.putValue(component);
    connection.flush();
}

/*! Send parts of a view buffer to a Connection
 */
void ClusterViewBuffer::send(PointConnection &connection, 
                             UInt32           component,
                             UInt32           toX, 
                             UInt32           toY)
{
    send(connection, 
         component, 
         0, 
         0, 
         getBufferWidth(), 
         getBufferHeight(), toX,
         toY);
}

/*-------------------------------------------------------------------------*/
/*                            set parameters                               */

/*! Set compression type. By default, no compression is used for image 
 *  transmission. The given mime type identifies an ImageType e.g. "JPEG".
 *  This image type is used for compression. 
 */

void ClusterViewBuffer::setImgTransType(const Char8 *mimeType)
{
    if(mimeType == NULL)
    {
        _imgTransType = NULL;
    }
    else
    {
        _imgTransType = ImageFileHandler::the()->getFileType(mimeType);
    }
}

/*! Set subtile size. The whole buffer is transfered as small subtiles.
    Increasing or decreasing the subtile size will result in changes to the
    performance. The best size depends on network package size and the
    ration between network performance and buffer read/write performance.
 */

void ClusterViewBuffer::setSubtileSize(UInt32 size)
{
    _subTileSize = size;
}

/*! Set opengl datatype for rgb tramsmission
 */

void ClusterViewBuffer::setRGBADataType(UInt32 type, UInt32 size)
{
    _rgbaDataType = type;
    _rgbaDataSize = size;
}

/*! Set opengl datatype for rgba tramsmission
 */

void ClusterViewBuffer::setRGBDataType(UInt32 type, UInt32 size)
{
    _rgbDataType = type;
    _rgbDataSize = size;
}

/*! Set opengl datatype for Z-Buffer tramsmission
 */

void ClusterViewBuffer::setDepthDataType(UInt32 type, UInt32 size)
{
    _depthDataType = type;
    _depthDataSize = size;
}

/*-------------------------------------------------------------------------*/
/*                            get                                          */

/*! Get buffer width
 */

UInt32 ClusterViewBuffer::getBufferWidth(void)
{
    GLint   view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    return view[2];
}

/*! Get buffer width
 */

UInt32 ClusterViewBuffer::getBufferHeight(void)
{
    GLint   view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    return view[3];
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8    cvsid_cpp[] = "@(#)$Id$";
    static Char8    cvsid_hpp[] = OSG_CLUSTERVIEWBUFFER_HEADER_CVSID;
}
