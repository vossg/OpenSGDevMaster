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

#ifndef _OSGBINARYSWAPCOMPOSER_H_
#define _OSGBINARYSWAPCOMPOSER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseThread.h"
#include "OSGLock.h"
#include "OSGBinarySwapComposerBase.h"
#include "OSGGLEXT.h"
#include "OSGClusterNetwork.h"

OSG_BEGIN_NAMESPACE

/*! \brief BinarySwapComposer class. See \ref 
           PageSystemBinarySwapComposer for a description.

    \ingroup GrpClusterWindowComposer
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

class OSG_CLUSTER_DLLMAPPING BinarySwapComposer : 
    public BinarySwapComposerBase
{
  private:

    typedef BinarySwapComposerBase Inherited;

    /*! \brief RGB Color value 
        \nohierarchy
     */

    struct RGBValue
    {
        UInt8 red;
        UInt8 green;
        UInt8 blue;
    };

    /*! \nohierarchy
     */

    struct TileBuffer
    {
        bool empty;
        UInt32 size;
        UInt32 colorSize;
        UInt32 depthSize;
        UInt32 dataSize;

        /*! \nohierarchy
         */

        struct 
        {
            UInt16 x;
            UInt16 y;
            UInt16 w;
            UInt16 h;
        } header;

        UInt8 data[1];
    };

    /*! \nohierarchy
     */

    struct Statistics 
    {
        UInt32 bytesIn;
        UInt32 bytesOut;
        double composeTime;
    };

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      features                                                */
    /*! \{                                                                 */

    virtual bool clientRendering(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      composition                                             */
    /*! \{                                                                 */

    virtual void open           (              );
    virtual void composeViewport(Viewport *port);
    virtual void close          (void          );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name      features                                                */
    /*! \{                                                                 */

    virtual bool   getClientRendering(void);
    virtual UInt32 getUsableServers  (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    BaseThreadRefPtr          _writer;
    BarrierRefPtr             _barrier;
    bool                     _stopWriter;
    UInt32                   _swapWith;
    Connection              *_swapConnection;
    UInt32                   _tilesX;
    UInt32                   _tilesY;
    UInt32                   _tileBufferSize;
    std::vector<UInt8>       _tile;
    std::vector<UInt8>       _readTile;
    UInt32                   _writeLeft;
    UInt32                   _writeRight;
    UInt32                   _writeBottom;
    UInt32                   _writeTop;
    UInt32                   _usableServers;
    Statistics               _statistics;
    UInt32                   _intDepthMax;
    UInt32                   _shortDepthMax;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BinarySwapComposer(void);
    BinarySwapComposer(const BinarySwapComposer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BinarySwapComposer(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              compose                                         */
    /*! \{                                                                 */

    void writeBuffer();
    void readBuffer();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      helper function                         */
    /*! \{                                                                 */

    template<class DepthT,class ColorT>
    void sendToClient(DepthT &depth,ColorT &color,
                      UInt32 left,
                      UInt32 bottom,
                      UInt32 right,
                      UInt32 top);

    template<class DepthT,class ColorT>
    void recvFromServers(DepthT &depth,ColorT &color,
                         UInt32 colorType,
                         UInt32 colorFormat,
                         Viewport *port);

    template<class DepthT,class ColorT>
    void writeCombine(DepthT &depthDummy,ColorT &colorDummy);

    template<class DepthT,class ColorT>
    void readCombine(DepthT &depth,ColorT &color,
                     UInt32 colorType,
                     UInt32 colorFormat,
                     UInt32 left,
                     UInt32 bottom,
                     UInt32 right,
                     UInt32 top,
                     UInt32 level);

    template<class DepthT,class ColorT>
    void startReader(DepthT &depth,ColorT &color,
                     UInt32 depthFormat,
                     UInt32 colorType,
                     UInt32 colorFormat,
                     Viewport *port);

    TileBuffer *getTileBuffer(UInt32 x,UInt32 y);
    TileBuffer *getTileReadBuffer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BinarySwapComposerBase;

    static void writeProc(void *arg);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BinarySwapComposer &source);
};

typedef BinarySwapComposer *BinarySwapComposerP;

OSG_END_NAMESPACE

#include "OSGBinarySwapComposerBase.inl"
#include "OSGBinarySwapComposer.inl"

#endif /* _OSGBINARYSWAPCOMPOSER_H_ */
