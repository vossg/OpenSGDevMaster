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

#ifndef _OSGITFIMAGEFILETYPE_H_
#define _OSGITFIMAGEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include "OSGImageFileIODef.h"
#include "OSGImageFileType.h"
#include "OSGRectangle.h"

#include "boost/shared_ptr.hpp"


OSG_BEGIN_NAMESPACE

class ITFImageFileType;

/*! \ingroup GrpImageFileIOITF
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING TiledImageBlockAccessor : 
    public ImageBlockAccessor
{

    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef ImageBlockAccessor Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TiledImageBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool isOpen(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              UInt16 *pTarget,
                              Int32   iTargetSizeBytes);

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              Int16  *pTarget,
                              Int32   iTargetSizeBytes);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt32                             _uiRows;
    UInt32                             _uiColumns;

    std::vector<ImageBlockAccessorPtr> _vImages;
    std::vector<Rectangle2i>           _vSampleDescs;

    std::vector<Int16>                 _vI16Buffer;

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    TiledImageBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    void open(const Char8 *szFilename);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    bool read2HBlocksA16(Int32   iLow,
                         Int32   iHeigh,
                         Vec2i   vSampleOrigin,
                         Int32   iTextureSize,
                         Int16  *pTarget,
                         Int32   iTargetSizeBytes);

    bool read2VBlocksA16(Int32   iLow,
                         Int32   iHeigh,
                         Vec2i   vSampleOrigin,
                         Int32   iTextureSize,
                         Int16  *pTarget,
                         Int32   iTargetSizeBytes);

    bool read4BlocksA16 (Int32   iLow,
                         Int32   iHeigh,
                         Vec2i   vSampleOrigin,
                         Int32   iTextureSize,
                         Int16  *pTarget,
                         Int32   iTargetSizeBytes);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ITFImageFileType;
};

/*! \ingroup GrpImageFileIOITF
 */

typedef boost::shared_ptr<TiledImageBlockAccessor> TiledImageBlockAccessorPtr;

/*! \ingroup GrpImageFileIOITF
    \ingroup GrpLibOSGImageFileIO
 */

class OSG_IMGFILEIO_DLLMAPPING DefaultBlockAccessor : public ImageBlockAccessor
{
    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef ImageBlockAccessor Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DefaultBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool isOpen(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              UInt16 *pTarget,
                              Int32   iTargetSizeBytes);

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              Int16  *pTarget,
                              Int32   iTargetSizeBytes);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    Int32 _iDefaultValue;

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    DefaultBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    void open(const Char8 *szFilename);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class TiledImageBlockAccessor;
};

/*! \ingroup GrpImageFileIOITF
 */

typedef boost::shared_ptr<DefaultBlockAccessor> DefaultBlockAccessorPtr;


/*! \brief ITF File Handler. Used to read/write TIFF files.
    See \ref PageSystemImage for a detailed description.

    \ingroup GrpImageFileIOITF
    \ingroup GrpLibOSGImageFileIO
*/

class OSG_IMGFILEIO_DLLMAPPING ITFImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ITFImageFileType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool validateHeader(const Char8 *fileName, 
                                      bool  &implemented);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    virtual ImageBlockAccessorPtr open(const Char8 *fileName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    ITFImageFileType (const Char8  *mimeType,
                      const Char8  *suffixArray[], 
                            UInt16  suffixByteCount,
                            UInt32  flags );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Copy Op                                 */
    /*! \{                                                                 */

          ITFImageFileType            (const ITFImageFileType &obj);
    const ITFImageFileType &operator =(const ITFImageFileType &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ImageFileType Inherited;

    static ITFImageFileType _the;
};

typedef ITFImageFileType *ITFImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGITFIMAGEFILETYPE_H_
