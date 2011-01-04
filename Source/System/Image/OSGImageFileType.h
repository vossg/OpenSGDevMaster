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

#ifndef _OSGIMAGEFILETYPE_H_
#define _OSGIMAGEFILETYPE_H_

#include <list>

#include "OSGIOFileTypeBase.h"
#include "OSGImage.h"
#include "OSGGeoReferenceAttachment.h"

#include "boost/shared_ptr.hpp"

OSG_BEGIN_NAMESPACE

class ImageFileType;

/*! \ingroup GrpSystemImageHelper
    \ingroup GrpLibOSGSystem
*/

class OSG_SYSTEM_DLLMAPPING ImageBlockAccessor
{
    /*==========================  PUBLIC  =================================*/
    
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageBlockAccessor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool isOpen(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    Vec2i              getSize       (void);
    
    Image::Type        getType       (void);
    Image::PixelFormat getFormat     (void);

    Real64             getNoDataValue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    GeoReferenceAttachment *getGeoRef(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              UInt16 *pTarget,
                              Int32   iTargetSizeBytes) = 0;

    virtual bool readBlockA16(Vec2i   vSampleOrigin,
                              Int32   iTextureSize,
                              Int16  *pTarget,
                              Int32   iTargetSizeBytes) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    GeoReferenceAttachmentUnrecPtr _pGeoRef;
    Vec2i                          _vSize;
    Image::Type                    _eImgType;
    Image::PixelFormat             _eImgFormat;
    Real64                         _fNoDataValue;

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    ImageBlockAccessor(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

/*! \ingroup GrpSystemImageHelper
 */

typedef boost::shared_ptr<ImageBlockAccessor> ImageBlockAccessorPtr;

/*! \ingroup GrpSystemImageHelper
    \ingroup GrpLibOSGSystem
*/

class OSG_SYSTEM_DLLMAPPING BlockAccessWrapper : public ImageBlockAccessor
{
    /*==========================  PUBLIC  =================================*/
    
  public:

    typedef ImageBlockAccessor Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BlockAccessWrapper(void);

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

    ImageUnrecPtr _pImage;

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    BlockAccessWrapper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    void open(const Char8 *szFilename);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ImageFileType;
};

/*! \ingroup GrpSystemImageHelper
 */

typedef boost::shared_ptr<BlockAccessWrapper> BlockAccessWrapperPtr;

/*! \brief Abstract Base ImageFileType. Defines the Interface for
    all concrete ImageFileTypes. See \ref PageSystemImage for detailed
    description. 
 
    \ingroup GrpSystemImageFileIOBase
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING ImageFileType : public IOFileTypeBase
{
    /*==========================  PUBLIC  =================================*/   
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef IOFileTypeBase Inherited;
    typedef ImageFileType  Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Flags                                    */
    /*! \{                                                                 */
  
    enum
    {
        OSG_READ_SUPPORTED  = 1,
        OSG_WRITE_SUPPORTED = 2
    };
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageFileType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */
    
    const      Char8             *getMimeType  (void) const;

    const std::list<std::string> &getSuffixList(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read          (      Image            *pImage, 
                                const Char8            *fileName   ) ;

    virtual bool write         (      Image const      *pImage, 
                                const Char8            *fileName   ) ;

    virtual bool read          (      Image            *pImage, 
                                      std::istream     &is, 
                                const std::string      &mimetype);

    virtual bool write         (      Image const      *pImage, 
                                      std::ostream     &os, 
                                const std::string      &mimetype);

    virtual bool validateHeader(const Char8            *fileName, 
                                      bool             &implemented);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual ImageBlockAccessorPtr open(const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    virtual std::string determineMimetypeFromStream(std::istream &is);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              static store/restore                            */
    /*! \{                                                                 */

    static UInt64 restore(      Image            *pImage, 
                          const UChar8           *buffer,
                                Int32             memSize = -1);

    static UInt64 store  (      Image const      *pImage,
                          const Char8            *mimeType,
                                UChar8           *buffer, 
                                Int32             memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Raw Store/Restore                           */
    /*! \{                                                                 */

    virtual UInt64 restoreData(      Image            *pImage, 
                               const UChar8           *buffer,
                                     Int32             memSize = -1);

    virtual UInt64 storeData  (      Image const      *pImage, 
                                     UChar8           *buffer,
                                     Int32             memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   store/restore                              */
    /*! \{                                                                 */

           UInt64 store         (Image const      *pImage, 
                                 UChar8           *buffer,
                                 Int32             memSize = -1);
    
    virtual UInt64 maxBufferSize(Image const      *pImage      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       dump                                   */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   MTD Header                                 */
    /*! \{                                                                 */

    /*! \nohierarchy
     */

    struct OSG_SYSTEM_DLLMAPPING Head
    {
        Char8          suffix[8];
        
        unsigned short pixelFormat;
        unsigned short width;
        unsigned short height;
        unsigned short depth;
        unsigned short mipmapCount;
        unsigned short frameCount;
        unsigned short frameDelay;
        unsigned short sideCount;
        unsigned short dataType;
        unsigned short _reserved3;
        unsigned short _reserved4;
        unsigned short attachmentSize;

        bool netToHost(void);
        bool hostToNet(void);
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    ImageFileType(const Char8  *mimeType,
                  const Char8  *suffixArray[], 
                        UInt16  suffixByteCount,
                        UInt32  flags = OSG_READ_SUPPORTED);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    /* prohibit default function (move to 'public' if needed) */
          ImageFileType            (const ImageFileType &obj);
    const ImageFileType &operator =(const ImageFileType &obj);


    std::list<std::string> _suffixList;

    std::string            _mimeType;
};

typedef ImageFileType *ImageFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGIMAGEFILETYPE_H_
