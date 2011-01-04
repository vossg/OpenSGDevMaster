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

#ifndef _CLUSTERVIEWBUFFER_H_
#define _CLUSTERVIEWBUFFER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include "OSGClusterDef.h"
#include "OSGConnection.h"

OSG_BEGIN_NAMESPACE

class ImageFileType;
class PointConnection;
class GroupConnection;

/*! \ingroup GrpClusterBase
    \ingroup GrpLibOSGCluster
 */

class OSG_CLUSTER_DLLMAPPING ClusterViewBuffer
{
    /*==========================  PUBLIC  =================================*/

  public:

    /** \brief Buffer component */
    enum Component
    {
        RED           =1,
        GREEN         =2,
        BLUE          =4,
        ALPHA         =8,
        STENCIL       =16,
        DEPTH         =32,
        RGB           =RED|GREEN|BLUE,
        RGBA          =RED|GREEN|BLUE|ALPHA
    };

    /** \brief stl vector used as char buffer */
    typedef std::vector<Int8> BufferT;

    /*! \brief RGB Color value 
        \nohierarchy
     */
    struct RGBValue
    {
        UInt8 red;
        UInt8 green;
        UInt8 blue;
    };

    /*---------------------------------------------------------------------*/
    /*! \name          Constructors / Destructor                           */
    /*! \{                                                                 */

    ClusterViewBuffer(void);
    virtual ~ClusterViewBuffer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 send/recv                                    */
    /*! \{                                                                 */

    void recv(GroupConnection &connection );

    void send(PointConnection &connection,
              UInt32           component,
              UInt32           x1,
              UInt32           y1,
              UInt32           x2,
              UInt32           y2,
              UInt32           toX,
              UInt32           toY        );

    void send(PointConnection &connection,
              UInt32           component,
              UInt32           toX,
              UInt32           toY        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 set parameters                               */
    /*! \{                                                                 */

    void   setImgTransType (const Char8  *mime = NULL      );
    void   setSubtileSize  (      UInt32  size             );
    void   setRGBADataType (      UInt32  type, UInt32 size);
    void   setRGBDataType  (      UInt32  type, UInt32 size);
    void   setDepthDataType(      UInt32  type, UInt32 size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    get                                       */
    /*! \{                                                                 */

    UInt32 getBufferWidth();
    UInt32 getBufferHeight();

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    ImageFileType *_imgTransType;
    UInt32         _subTileSize;
    UInt32         _rgbDataType;
    UInt32         _rgbDataSize;
    UInt32         _rgbaDataType;
    UInt32         _rgbaDataSize;
    UInt32         _depthDataType;
    UInt32         _depthDataSize;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /* prohibit default function (move to 'public' if needed) */
    ClusterViewBuffer(const ClusterViewBuffer &source);

    /* prohibit default function (move to 'public' if needed) */
    void operator =(const ClusterViewBuffer &source);
};

// class pointer
typedef ClusterViewBuffer *ClusterViewBufferP;

OSG_END_NAMESPACE

#endif /* _CLUSTERVIEWBUFFER_H_ */
