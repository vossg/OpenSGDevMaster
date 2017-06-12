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
    \ingroup GrpSystemImageObj
    \ingroup GrpLibOSGSystem
    \includebasedoc
*/

class OSG_SYSTEM_DLLMAPPING Image : public ImageBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageBase                           Inherited;

    enum PixelFormat 
    {   
        OSG_INVALID_PF = 0,
        OSG_A_PF       = GL_ALPHA,
        OSG_I_PF       = GL_INTENSITY,
        OSG_L_PF       = GL_LUMINANCE,
        OSG_LA_PF      = GL_LUMINANCE_ALPHA,

        OSG_R_PF       = GL_RED,
        OSG_RG_PF      = GL_RG,

        OSG_RGB_PF     = GL_RGB,
        OSG_RGBA_PF    = GL_RGBA,
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

        OSG_DEPTH_PF                   = GL_DEPTH_COMPONENT,

/*** GL_EXT_packed_depth_stencil ***/
#if defined(GL_DEPTH_STENCIL)
        OSG_DEPTH_STENCIL_PF           = GL_DEPTH_STENCIL,
#elif defined(GL_DEPTH_STENCIL_EXT)
        OSG_DEPTH_STENCIL_PF           = GL_DEPTH_STENCIL_EXT,
#elif defined(GL_DEPTH_STENCIL_NV)
        OSG_DEPTH_STENCIL_PF           = GL_DEPTH_STENCIL_NV,
#else
        OSG_DEPTH_STENCIL_PF           = 0,
#endif

        OSG_ALPHA_INTEGER_PF           = GL_ALPHA_INTEGER_EXT,
        OSG_RGB_INTEGER_PF             = GL_RGB_INTEGER_EXT,
        OSG_RGBA_INTEGER_PF            = GL_RGBA_INTEGER_EXT,
        OSG_BGR_INTEGER_PF             = GL_BGR_INTEGER_EXT,
        OSG_BGRA_INTEGER_PF            = GL_BGRA_INTEGER_EXT,
        OSG_LUMINANCE_INTEGER_PF       = GL_LUMINANCE_INTEGER_EXT,
        OSG_LUMINANCE_ALPHA_INTEGER_PF = GL_LUMINANCE_ALPHA_INTEGER_EXT


    };

    enum Type 
    {
        OSG_INVALID_IMAGEDATATYPE  = GL_NONE,
        OSG_UINT8_IMAGEDATA        = GL_UNSIGNED_BYTE,
        OSG_UINT16_IMAGEDATA       = GL_UNSIGNED_SHORT,
        OSG_UINT32_IMAGEDATA       = GL_UNSIGNED_INT,
        OSG_FLOAT16_IMAGEDATA      = GL_HALF_FLOAT_NV,
        OSG_FLOAT32_IMAGEDATA      = GL_FLOAT,
        OSG_INT16_IMAGEDATA        = GL_SHORT,
        OSG_INT32_IMAGEDATA        = GL_INT,

/*** GL_EXT_packed_depth_stencil ***/
#if defined(GL_UNSIGNED_INT_24_8_EXT)
        OSG_UINT24_8_IMAGEDATA     = GL_UNSIGNED_INT_24_8_EXT
#elif defined(GL_UNSIGNED_INT_24_8_NV)
        OSG_UINT24_8_IMAGEDATA     = GL_UNSIGNED_INT_24_8_NV
#else
        OSG_UINT24_8_IMAGEDATA     = GL_NONE
#endif
    };

    enum ResUnit 
    {
        OSG_RESUNIT_INVALID       = 0,
        OSG_RESUNIT_NONE          = 1,
        OSG_RESUNIT_INCH          = 2
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details);

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
    bool set               (      Image    *image                            );
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

    bool reformat(const PixelFormat  pixelFormat,
                        Image       *destination       = NULL,
                        Int32        iCompressionFlags = 0);

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

    bool scale          (Int32  width, 
                         Int32  height      = 1,
                         Int32  depth       = 1,
                         Image *destination = NULL);
    bool scaleNextPower2(Image *destination = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mirror                                  */
    /*! \{                                                                 */

    bool mirror         (bool   horizontal,
                         bool   vertical,
                         bool   flipDepth   = false,
                         Image *destination = NULL  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      SubImage                                */
    /*! \{                                                                 */

    bool subImage(Int32  offX, 
                  Int32  offY, 
                  Int32  offZ,
                  Int32  destW, 
                  Int32  destH, 
                  Int32  destD,
                  Image *destination = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Slice                                   */
    /*! \{                                                                 */

    bool slice(Int32  offX = -1, 
               Int32  offY = -1, 
               Int32  offZ = -1,
               Image *destination = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mipmap                                  */
    /*! \{                                                                 */

    bool createMipmap(Int32  level       = -1, 
                      Image *destination = NULL);

    bool removeMipmap(void                     );

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

    SizeT  getHash          (bool force = false) const;

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

    const UInt8 *getDataFast   (UInt32 mipmapNum = 0,
                                UInt32 frameNum  = 0,
                                UInt32 sidecount = 0);
          UInt8 *editDataFast  (UInt32 mipmapNum = 0,
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
    /*---------------------------------------------------------------------*/
    /*! \name                        Don't know yet                        */
    /*! \{                                                                 */

#if 0
    void imageContentChanged(Int32 minX = -1, Int32 maxX = -1,
                             Int32 minY = -1, Int32 maxY = -1,
                             Int32 minZ = -1, Int32 maxZ = -1 );
#endif    

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    std::vector<Int32> _mipmapOffset;
    mutable SizeT      _hash;
    mutable bool       _hashValid;

    /*---------------------------------------------------------------------*/
    /*! \name                  static element                              */
    /*! \{                                                                 */

    static UInt32 _formatDic[][2];
    static Int32  _typeDic  [][2];

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

    bool createData       (const UInt8 *data, 
                                 bool   allocMem = true  );
    bool scaleData        (const UInt8 *srcData,
                                 Int32  srcW, 
                                 Int32  srcH, 
                                 Int32  srcD,
                                 UInt8 *destData,
                                 Int32  destW, 
                                 Int32  destH, 
                                 Int32  destD            );

    void calcMipmapOffsets(      void                    );
    void calcHash         (      void                    ) const;

    bool mirrorData       (const UInt8 *srcData,
                                 UInt8 *destData,
                                 Int32  width,
                                 Int32  height,
                                 Int32  depth,
                                 bool   horizontal,
                                 bool   vertical,
                                 bool   flipDepth = false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    friend class FieldContainer;
    friend class ImageBase;
};

typedef Image *ImageP;

OSG_END_NAMESPACE

#include "OSGImageBase.inl"
#include "OSGImage.inl"

#endif /* _OSGIMAGE_H_ */
