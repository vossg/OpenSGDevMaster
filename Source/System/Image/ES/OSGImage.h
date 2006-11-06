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

#ifndef _OSGIMAGE_H_
#define _OSGIMAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGImageBase.h"
#include "OSGGLEXT.h"
#include "OSGReal16.h"

OSG_BEGIN_NAMESPACE

/*! \brief Image class. See \ref PageSystemImage
           for a description.
*/

class OSG_SYSTEM_DLLMAPPING Image : public ImageBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageBase                           Inherited;

    typedef PointerBuilder<Image>::ObjPtr          ObjPtr;
    typedef PointerBuilder<Image>::ObjConstPtr     ObjConstPtr;

    typedef PointerBuilder<Image>::ObjPtrArg       ObjPtrArg;
    typedef PointerBuilder<Image>::ObjConstPtrArg  ObjConstPtrArg;

    enum PixelFormat 
    {   
        OSG_INVALID_PF = 0,
        OSG_A_PF       = GL_ALPHA,
#if !defined(OSG_WINCE) || OSG_GL_ES_VERSION > 100
        OSG_I_PF       = GL_INTENSITY,
#endif
		OSG_L_PF       = GL_LUMINANCE,
        OSG_LA_PF      = GL_LUMINANCE_ALPHA,
/*** BGR ***/
#if defined(GL_BGR)
        OSG_BGR_PF     = GL_BGR,
#elif defined(GL_BGR_EXT)
        OSG_BGR_PF     = GL_BGR_EXT,
#else
        OSG_BGR_PF     = 0,
#endif
        
/*** BGRA ***/
#if defined(GL_BGRA)
        OSG_BGRA_PF    = GL_BGRA,
#elif defined(GL_BGRA_EXT)
        OSG_BGRA_PF    = GL_BGRA_EXT,
#else
        OSG_BGRA_PF    = 0,
#endif
/*** RGB_DXT1 ***/
#if defined(GL_COMPRESSED_RGB_S3TC_DXT1_EXT)
        OSG_RGB_DXT1   = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
#else
        OSG_RGB_DXT1   = 0,
#endif
        
/*** RGBA_DXT1 ***/
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
        OSG_RGBA_DXT1  = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
#else
        OSG_RGBA_DXT1  = 0,
#endif
        
/*** RGBA_DXT3 ***/
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT)
        OSG_RGBA_DXT3  = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
#else
        OSG_RGBA_DXT3  = 0,
#endif
        
/*** RGBA_DXT5 ***/
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT)
        OSG_RGBA_DXT5  = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
#else
        OSG_RGBA_DXT5  = 0,
#endif

        OSG_RGB_PF     = GL_RGB,
        OSG_RGBA_PF    = GL_RGBA
    };

    enum Type 
    {
        OSG_INVALID_IMAGEDATATYPE  = GL_FALSE,
        OSG_UINT8_IMAGEDATA        = GL_UNSIGNED_BYTE,
        OSG_UINT16_IMAGEDATA       = GL_UNSIGNED_SHORT,
#if !defined(OSG_WINCE) || OSG_GL_ES_VERSION > 100
        OSG_UINT32_IMAGEDATA       = GL_UNSIGNED_INT,
#endif
#if !defined(OSG_WINCE)
		OSG_FLOAT16_IMAGEDATA      = GL_HALF_FLOAT_NV,
#endif
		OSG_FLOAT32_IMAGEDATA      = GL_FLOAT
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg  whichField,
                         UInt32             origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set Object Data                            */
    /*! \{                                                                 */

    bool set               (      UInt32    pixelFormat,
                                  Int32     width,
                                  Int32     height      = 1,
                                  Int32     depth       = 1,
                                  Int32     mipmapCount = 1,
                                  Int32     frameCount  = 1,
                                  Time      frameDelay  = 0.0,
                            const UInt8    *data        = 0,
                                  Int32     type        = OSG_UINT8_IMAGEDATA,
                                  bool      allocMem    = true,
                                  Int32     sidecount   = 1                  );
    bool set               (      ImagePtr  image                            );
    bool setData           (const UInt8    *data = 0                         );
    void clearData         (      void                                       );
    bool setSubData        (      Int32     offX, 
                                  Int32     offY, 
                                  Int32     offZ,
                                  Int32     srcW, 
                                  Int32     srcH, 
                                  Int32     srcD,
                            const UInt8    *data                             );
    bool flipDepthFrameData(      void                                       );


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Add Value                                */
    /*! \{                                                                 */

    bool addValue(const Char8 *value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Reformate                                */
    /*! \{                                                                 */

    bool reformat(const PixelFormat pixelFormat,
                        ImagePtr    destination = NullFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Convert dataType                          */
    /*! \{                                                                 */

    void swapDataEndian   (void                                    );
    bool convertDataTypeTo(Int32 destDataType = OSG_UINT8_IMAGEDATA);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Scale                                  */
    /*! \{                                                                 */

    bool scale          (Int32    width, 
                         Int32    height      = 1,
                         Int32    depth       = 1,
                         ImagePtr destination = NullFC );
    bool scaleNextPower2(ImagePtr destination = NullFC );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      SubImage                                */
    /*! \{                                                                 */

    bool subImage(Int32    offX, 
                  Int32    offY, 
                  Int32    offZ,
                  Int32    destW, 
                  Int32    destH, 
                  Int32    destD,
                  ImagePtr destination = NullFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Slice                                   */
    /*! \{                                                                 */

    bool slice(Int32    offX = -1, 
               Int32    offY = -1, 
               Int32    offZ = -1,
               ImagePtr destination = NullFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mipmap                                  */
    /*! \{                                                                 */

    bool createMipmap(Int32    level       = -1, 
                      ImagePtr destination = NullFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    bool write(const Char8 *fileName);
    bool read (const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Storage/Restore                              */
    /*! \{                                                                 */

    UInt64 store  (const Char8 *mimeType, 
                         UInt8 *mem, 
                         Int32  memSize = -1);
    UInt64 restore(const UInt8 *mem, 
                         Int32  memSize = -1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Comparison/Assign                              */
    /*! \{                                                                 */

    Image &operator =  (const Image &image);
    bool   operator <  (const Image &image);
    bool   operator == (const Image &image);
    bool   operator != (const Image &image);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */

    bool   isValid          (void) const;
    bool   hasAlphaChannel  (void);
    bool   isAlphaBinary    (void);
    bool   hasColorChannel  (void);
    bool   hasCompressedData(void);
    UInt8  getComponents    (void) const;
    
    bool   calcIsAlphaBinary(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Size                                    */
    /*! \{                                                                 */

    unsigned long getSize(bool withMipmap = true,
                          bool withFrames = true,
                          bool withSides  = true) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Methods                                */
    /*! \{                                                                 */

    const UInt8 *getData       (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0) const;
          UInt8 *editData      (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0);
    const UInt8 *getDataByTime (Time   time, 
                                UInt32 mipmapNum = 1) const;
          UInt8 *editDataByTime(Time   time, 
                                UInt32 mipmapNum = 1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Calculate                               */
    /*! \{                                                                 */

    void   calcMipmapGeometry  (UInt32 mipmapNum,
                                UInt32 &width,
                                UInt32 &height,
                                UInt32 &depth     ) const;
    UInt32 calcMipmapLevelCount(void              ) const;
    UInt32 calcFrameNum        (Time    time, 
                                bool    loop = true) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Clear Image                                */
    /*! \{                                                                 */

    virtual void clear     (UChar8 pixelValue = 0            );
    virtual void clearFloat(Real32 pixelValue = 0.0          );
    virtual void clearHalf (Real16 pixelValue = Real16( 0.0 ));

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               attachment handling                            */
    /*! \{                                                                 */

    bool               hasAttachment      (      void             ) const;
    UInt32             attachmentCount    (      void             ) const;
    void               setAttachmentField (const std::string &key,
                                           const std::string &data);
    const std::string *findAttachmentField(const std::string &key ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Calculate Mipmap Size                          */
    /*! \{                                                                 */

    UInt32 calcMipmapLevelSize(UInt32 mipmapNum,
                               UInt32 w, 
                               UInt32 h, 
                               UInt32 d        ) const;
    UInt32 calcMipmapLevelSize(UInt32 mipmapNum) const;

    UInt32 calcMipmapSumSize  (UInt32 mipmapNum,
                               UInt32 w, 
                               UInt32 h, 
                               UInt32 d        ) const;
    UInt32 calcMipmapSumSize  (UInt32 mipmapNum) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  static element                              */
    /*! \{                                                                 */

    static Int32 _formatDic[][2];
    static Int32 _typeDic  [][2];

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Image(void);
    Image(const Image &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Image(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                   Image Data                                 */
    /*! \{                                                                 */

    bool createData(const UInt8 *data, 
                          bool   allocMem = true);
    bool scaleData (      UInt8 *srcData,
                          Int32  srcW, 
                          Int32  srcH, 
                          Int32  srcD,
                          UInt8 *destData,
                          Int32  destW, 
                          Int32  destH, 
                          Int32  destD          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    friend class ImageBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;
};

typedef Image *ImageP;

typedef Image::ObjPtr         ImagePtr;
typedef Image::ObjConstPtr    ImageConstPtr;

typedef Image::ObjPtrArg      ImagePtrArg;
typedef Image::ObjConstPtrArg ImageConstPtrArg;

OSG_END_NAMESPACE

#include "OSGImageBase.inl"
#include "OSGImage.inl"

#define OSGIMAGE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGIMAGE_H_ */
