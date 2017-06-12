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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wsign-compare"
#endif

#ifdef WIN32
#pragma warning( disable : 4018 )
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEIMAGE

#include <cstdlib>
#include <cstdio>

#include <algorithm>
#include <boost/functional/hash/hash.hpp>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGImageGenericAtt.h"
#include "OSGFieldContainerFields.h"
#include "OSGFileSystem.h"
#include "OSGImageFileHandler.h"
#include "OSGSquish.h"

/*
#include "OSGPathHandler.h"
#include "OSGSceneFileHandler.h"
 */

#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Image
  1D/2D/3D Image with various pixel types data, can also optional hold
  mipMap and simple multi-frame data.
 */

/*------------------------------------------------------------------------*/
/*                              static member                             */

/*! Static dictionary to map pixelData values to the bytes per pixel
  (bpp) value.
  Internaly used in the createData() method.
 */

UInt32 Image::_formatDic[][2] =
{
    { OSG_A_PF,      1 },
    { OSG_I_PF,      1 },
    { OSG_L_PF,      1 },
    { OSG_LA_PF,     2 },
    { OSG_R_PF,      1 },
    { OSG_RG_PF,     2 },
    { OSG_RGB_PF,    3 },
    { OSG_RGBA_PF,   4 },
    { OSG_BGR_PF,    3 },
    { OSG_BGRA_PF,   4 },
    { OSG_RGB_DXT1,  3 },
    { OSG_RGBA_DXT1, 4 },
    { OSG_RGBA_DXT3, 4 },
    { OSG_RGBA_DXT5, 4 },
    { OSG_DEPTH_PF,                   1 },
    { OSG_DEPTH_STENCIL_PF,           1 },
    { OSG_ALPHA_INTEGER_PF,           1 },
    { OSG_RGB_INTEGER_PF,             3 },
    { OSG_RGBA_INTEGER_PF,            4 },
    { OSG_BGR_INTEGER_PF,             3 },
    { OSG_BGRA_INTEGER_PF,            4 },
    { OSG_LUMINANCE_INTEGER_PF,       1 },
    { OSG_LUMINANCE_ALPHA_INTEGER_PF, 2 }
};

Int32 Image::_typeDic[][2] =
{
    { OSG_INVALID_IMAGEDATATYPE, 0 },
    { OSG_UINT8_IMAGEDATA,       1 },
    { OSG_UINT16_IMAGEDATA,      2 },
    { OSG_UINT32_IMAGEDATA,      4 },
    { OSG_FLOAT32_IMAGEDATA,     4 },
    { OSG_FLOAT16_IMAGEDATA,     2 },
    { OSG_INT16_IMAGEDATA,       2 },
    { OSG_INT32_IMAGEDATA,       4 },
    { OSG_UINT24_8_IMAGEDATA,    4 }
};

/*----------------------------- class specific ----------------------------*/

void Image::initMethod(InitPhase ePhase)
{
}

/*! Inform parents, when image was changed
 */

void Image::changed(ConstFieldMaskArg whichField, 
                    UInt32            origin,
                    BitVector         details)
{
    MFParentFieldContainerPtr::const_iterator parentsIt  = 
        this->_mfParents.begin();

    MFParentFieldContainerPtr::const_iterator parentsEnd = 
        this->_mfParents.end();

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
            TypeTraits<BitVector>::One << parentsIt.getParentFieldPos(),
            ChangedOrigin::Child,
            whichField);

        ++parentsIt;
    }

    if(0x0000 != (whichField & DataTypeFieldMask))
    {
        // Update internals
        Int32 mapSizeType = sizeof(_typeDic) / sizeof(UInt32[2]);
        UInt32 typeFormat  = 0;
        Int32 i;
        
        for(i = 0; i < mapSizeType; i++)
        {
            if(_typeDic[i][0] == _sfDataType.getValue())
            {
                typeFormat = _typeDic[i][1];
            }
        }
        
        setComponentSize( typeFormat );
    }

    if(0x0000 != (whichField & (MipMapCountFieldMask |
                                WidthFieldMask       |
                                HeightFieldMask      |
                                DepthFieldMask       |
                                PixelFormatFieldMask )))
    {
        setSideSize(calcMipmapSumSize(_sfMipMapCount.getValue()));
    }

    if(0x0000 != (whichField & (SideSizeFieldMask | SideCountFieldMask)))
    {
        setFrameSize(_sfSideSize.getValue() * _sfSideCount.getValue());
    }

    calcMipmapOffsets();

    _hashValid = false;

    Inherited::changed(whichField, origin, details);
}

/*----------------------------- output ------------------------------------*/

void Image::dump(      UInt32    ,
                 const BitVector ) const
{
    const Char8  *pfStr   = "UNDEF_PIXEL_FORMAT";
    const Char8  *typeStr = "INVALID_IMAGEDATA_TYPE";

    switch(getPixelFormat())
    {
        case OSG_A_PF:
            pfStr = "ALPHA";
            break;
        case OSG_I_PF:
            pfStr = "INTENSITY";
            break;
        case OSG_L_PF:
            pfStr = "LUMINANCE";
            break;
        case OSG_LA_PF:
            pfStr = "LUMINANCE_ALPHA";
            break;
        case OSG_BGR_PF:
            pfStr = "BGR";
            break;
        case OSG_BGRA_PF:
            pfStr = "BGRA";
            break;
        case OSG_R_PF:
            pfStr = "RED";
            break;
        case OSG_RG_PF:
            pfStr = "RG";
            break;
        case OSG_RGB_PF:
            pfStr = "RGB";
            break;
        case OSG_RGBA_PF:
            pfStr = "RGBA";
            break;
        case OSG_RGB_DXT1:
            pfStr = "RGB_DXT1";
            break;
        case OSG_RGBA_DXT1:
            pfStr = "RGBA_DXT1";
            break;
        case OSG_RGBA_DXT3:
            pfStr = "RGBA_DXT3";
            break;
        case OSG_RGBA_DXT5:
            pfStr = "RGBA_DXT5";
            break;
        case OSG_DEPTH_PF:
            pfStr = "DEPTH";
            break;
        case OSG_DEPTH_STENCIL_PF:
            pfStr = "DEPTH_STENCIL";
            break;
        case OSG_ALPHA_INTEGER_PF:
            pfStr = "ALPHA_INTEGER";
            break;
        case OSG_RGB_INTEGER_PF:
            pfStr = "RGB_INTEGER";
            break;
        case OSG_RGBA_INTEGER_PF:
            pfStr = "RGBA_INTEGER";
            break;
        case OSG_BGR_INTEGER_PF:
            pfStr = "BGR_INTEGER";
            break;
        case OSG_BGRA_INTEGER_PF:
            pfStr = "BGRA_INTEGER";
            break;
        case OSG_LUMINANCE_INTEGER_PF:
            pfStr = "LUMINANCE_INTEGER";
            break;
        case OSG_LUMINANCE_ALPHA_INTEGER_PF:
            pfStr = "LUMINANCE_ALPHA_INTEGER";
            break;
        default:
            pfStr = "UNKNOWN_PIXEL_FORMAT";
            break;
    };

    switch (getDataType())
    {
        case OSG_UINT8_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE UCHAR8";
            break;
        case OSG_UINT16_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE UCHAR16";
            break;
        case OSG_UINT32_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE UCHAR32";
            break;
        case OSG_FLOAT16_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE FLOAT16";
            break;
        case OSG_FLOAT32_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE FLOAT32";
            break;
        case OSG_INT16_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE INT16";
            break;
        case OSG_INT32_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE INT32";
            break;
        case OSG_UINT24_8_IMAGEDATA:
            typeStr = "IMAGEDATA_TYPE UINT24_8";
            break;

        default:
            typeStr = "UNKNOWN_IMAGEDATA_TYPE";
            break;
    };

    FLOG (("ImageDump: %s; %d/%d/%d; #mm: %d, side %d, #frame: %d, "
           "frameDelay %g, dataType %s, size: %ld\n",
           pfStr,
           getWidth(),
           getHeight(),
           getDepth(),
           getMipMapCount(),
           getSideCount(),
           getFrameCount(),
           getFrameDelay(),
           typeStr,
           getSize()));
}

// Return the number of components per pixel.

UInt8  Image::getComponents(void) const
{
    UInt16 mapSizeFormat = sizeof(_formatDic) / sizeof(UInt32[2]);

    for(UInt16 i = 0; i < mapSizeFormat; i++)
    {
        if(_formatDic[i][0] == getPixelFormat())
            return _formatDic[i][1];
    }

    FWARNING(("Image::getComponents: image %p has unknown pixel format 0x%x!",
                static_cast<const void *>(this), getPixelFormat()));

    return 0;
}

/*------------------------------ set object data --------------------------*/

/*! method to set the image data. Use the doCopy parameter to specify, whether
    the method should copy or link the pixel data.
*/
bool Image::set(      UInt32  pixelFormat, 
                      Int32   width,       
                      Int32   height,      
                      Int32   depth,       
                      Int32   mipmapCount, 
                      Int32   frameCount,  
                      Time    frameDelay,  
                const UInt8  *data,        
                      Int32   type,        
                      bool    allocMem,
                      Int32   sidecount  ) 
{
    setPixelFormat(pixelFormat);

    setWidth      (osgMax(1, width ));
    setHeight     (osgMax(1, height));
    setDepth      (osgMax(1, depth ));

    setMipMapCount(osgMax(1, mipmapCount));
    setSideCount  (osgMax(1, sidecount  ));
    setFrameCount (osgMax(1, frameCount ));

    setFrameDelay (frameDelay);

    setDataType   (type      );

    calcMipmapOffsets();

    return createData(data, allocMem);
}

/*! method to set the image from another image object.
    Use the doCopy parameter to specify, whether
    the method should copy or link the pixel data.
 */

bool Image::set(Image *image)
{
    this->set(image->getPixelFormat(),
              image->getWidth      (),
              image->getHeight     (),
              image->getDepth      (),
              image->getMipMapCount(),
              image->getFrameCount (),
              image->getFrameDelay (),
              image->getData       (),
              image->getDataType   (),
              true,
              image->getSideCount  ());
    return true;
}

/*! method to set only the image pixel data, all parameter (e. pixelFormat
    width,height and depth) stay the same
 */

bool Image::setData(const UChar8 *da)
{
    if(da)
    {
        createData(da);
    }
    else
    {
        FWARNING(("Image::setData(Null) call\n"));
    }

    return (da ? true : false);
}

void Image::clearData(void)
{
    editMFPixel()->clear();
    // free unused memory.
    MFUInt8 tmp;
    tmp.swap(*editMFPixel());
}

/*! method to update just a subregion of the image data
  all paramter (e. pixelFormat,width,height,depth) stay the same
*/
bool Image::setSubData(      Int32  offX,
                             Int32  offY,
                             Int32  offZ,
                             Int32  srcW,
                             Int32  srcH,
                             Int32  srcD,
                       const UInt8 *src )
{
    UChar8 *dest = editData();
    UInt64  lineSize;

    FDEBUG(( "Image::setSubData (%d %d %d) - (%d %d %d) - src %p\n",
             offX, offY, offZ, srcW, srcH, srcD, src ));

    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::setSubData for compressed image\n"));
        return false;
    }

    if(!src || !dest)
    {
        FFATAL(("Invalid data pointer in Image::setSubData\n"));
        return false;
    }

    // determine the area to actually copy
    UInt32 xMin = osgMax(0, offX);
    UInt32 yMin = osgMax(0, offY);
    UInt32 zMin = osgMax(0, offZ);

    UInt32 xMax = osgMin(getWidth (), offX + srcW);
    UInt32 yMax = osgMin(getHeight(), offY + srcH);
    UInt32 zMax = osgMin(getDepth (), offZ + srcD);

    // fill the destination buffer with the subdata
    UInt32 destIdx, srcIdx = 0;

    for(UInt32 z = zMin; z < zMax; z++)
    {
        for(UInt32 y = yMin; y < yMax; y++)
        {
            lineSize = (xMax - xMin) * getBpp();
            destIdx  = ((z * getHeight() + y) * getWidth() + xMin) * getBpp();

            memcpy (&dest[destIdx], &src[srcIdx], size_t(lineSize));

            srcIdx  += Int32((srcW - (xMax - xMin)) * getBpp() + lineSize);
        }
        srcIdx += (srcH - (yMax - yMin)) * srcW * getBpp();
    }

    return true;
}

/*! The Image is not just a 2D container. The class can hold 3D (volume)
    and movie data. If we have 3D/singleFrame or 2D/multiFrame data without
    mipmaps we can flip between this two formats by just swapping the
    getFrameCount() and getDepth() values.
*/
bool Image::flipDepthFrameData(void)
{
    bool  retCode = false;
    Int32 value;

    if((getMipMapCount() == 1) &&
       ((getFrameCount() == 1) || (getDepth() == 1)))
    {
        value = getFrameCount();

        setFrameCount(getDepth());
        setDepth     (value     );

        retCode = true;
    }
    else
    {
      FWARNING (("Cant flipDepthFrameData(); invalid data layout\n"));
    }

    return retCode;
}

/*! This method is used by the parser to fill the image with
    string pixel data. It expects the data in VRML PixelTexture Format.
*/
bool Image::addValue(const char *value)
{
    static Image  *currentImage = 0;
    static UChar8 *currentData  = 0;

           Int64   j;
           Int64   v;

           bool    isHead = strchr(value, ' ') ? true : false;

    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::addValue for compressed image\n"));
        return false;
    }

    // make sure we only read one image at a time
    if(currentImage == this)
    {
        if(isHead)
        {
            FDEBUG(("Start new read cycle in image::addValue()\n"));
        }
    }
    else
    {
        if(!isHead)
        {
            FFATAL(("Additional image date for different image\n"));
        }
    }

    currentImage = this;

    if(isHead == true)
    {
        Int32        width;
        Int32        height;
        Int32        pixelDepth;
        PixelFormat  pf         = Image::OSG_INVALID_PF;

        // read the head
        sscanf(value, "%d %d %d", &width, &height, &pixelDepth);

        FDEBUG(("Image::addValue() set: w/h/bpp: %d/%d/%d\n",
                width, height, pixelDepth));

        switch(getDataType())
        {
            case OSG_UINT8_IMAGEDATA:
                switch(pixelDepth)
                {
                    case 1:
                        pf = OSG::Image::OSG_L_PF;
                        break;
                    case 2:
                        pf = OSG::Image::OSG_LA_PF;
                        break;
                    case 3:
                        pf = OSG::Image::OSG_RGB_PF;
                        break;
                    case 4:
                        pf = OSG::Image::OSG_RGBA_PF;
                        break;
                    default:
                        pf = OSG::Image::OSG_INVALID_PF;
                        FFATAL(("Invalid pixel depth: %d\n", pixelDepth));
                        break;
                }
                break;

            case OSG_UINT16_IMAGEDATA:
                switch(pixelDepth)
                {
                    case 2:
                        pf = OSG::Image::OSG_L_PF;
                        break;
                    case 4:
                        pf = OSG::Image::OSG_LA_PF;
                        break;
                    case 6:
                        pf = OSG::Image::OSG_RGB_PF;
                        break;
                    case 8:
                        pf = OSG::Image::OSG_RGBA_PF;
                        break;
                    default:
                        pf = OSG::Image::OSG_INVALID_PF;
                        FFATAL(("Invalid pixel depth: %d\n", pixelDepth));
                        break;
                }
                break;

            case OSG_UINT32_IMAGEDATA:
                switch(pixelDepth)
                {
                    case 4:
                        pf = OSG::Image::OSG_L_PF;
                        break;
                    case 8:
                        pf = OSG::Image::OSG_LA_PF;
                        break;
                    case 12:
                        pf = OSG::Image::OSG_RGB_PF;
                        break;
                    case 16:
                        pf = OSG::Image::OSG_RGBA_PF;
                        break;
                    default:
                        pf = OSG::Image::OSG_INVALID_PF;
                        FFATAL(("Invalid pixel depth: %d\n", pixelDepth));
                        break;
                }
                break;

            case OSG_FLOAT32_IMAGEDATA:
                switch(pixelDepth)
                {
                    case 4:
                        pf = OSG::Image::OSG_L_PF;
                        break;
                    case 8:
                        pf = OSG::Image::OSG_LA_PF;
                        break;
                    case 12:
                        pf = OSG::Image::OSG_RGB_PF;
                        break;
                    case 16:
                        pf = OSG::Image::OSG_RGBA_PF;
                        break;
                    default:
                        pf = OSG::Image::OSG_INVALID_PF;
                        FFATAL(("Invalid pixel depth: %d\n", pixelDepth));
                        break;
                }
                break;

            case OSG_FLOAT16_IMAGEDATA:
                switch(pixelDepth)
                {
                    case 2:
                        pf = OSG::Image::OSG_L_PF;
                        break;
                    case 4:
                        pf = OSG::Image::OSG_LA_PF;
                        break;
                    case 6:
                        pf = OSG::Image::OSG_RGB_PF;
                        break;
                    case 8:
                        pf = OSG::Image::OSG_RGBA_PF;
                        break;
                    default:
                        pf = OSG::Image::OSG_INVALID_PF;
                        FFATAL(("Invalid pixel depth: %d\n", pixelDepth));
                        break;
                }
                break;

			case OSG_INT16_IMAGEDATA:
			case OSG_INT32_IMAGEDATA:
            {
                FFATAL((" 'addValue' NYI\n "));
            }
            break;

            default:
                setDataType(OSG_INVALID_IMAGEDATATYPE);
                FFATAL(("Invalid type of image data: %d\n", getDataType()));
        }

        if(pf != 0 && (width > 0) && (height > 0))
        {
            set(pf, width, height);

            currentData = editData();
        }
        else
        {
            currentData = NULL;
        }
    }
    else
    {
        if(currentData != NULL)
        {
            // add data
            // TODO; should we check the bounds, should be done by the parser

            v = strtoul(value, 0, strchr(value, 'x') ? 16 : 10);

            for(j = getBpp(); j--;)
            {
                *currentData++ = UChar8( (v >> (8 * j)) & 255 );
            }

        }
    }

    return currentData ? true : false;
}

/*! It is a simple method to reformat the image pixelFormat (not the size).
    So you can for example convert a RGBA to RGB or RGB to Grey image.
*/
bool Image::reformat(const Image::PixelFormat  pixelFormat,
                           Image              *destination,
                           Int32               iCompressionFlags)
{
          UChar8   *data       = NULL;
    const UChar8   *sourceData = NULL;
          UInt32    srcI, destI, destSize = 0;
          UInt32         sum;
          Real64         sumReal;
          ImageUnrecPtr  dest(destination);

    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::reformat for compressed image\n"));
        return false;
    }

    if(destination == NULL)
    {
        dest = Image::create();
    }

    FINFO(("Try to reformat image from pixelDepth %d to %d\n",
           getPixelFormat(),
           pixelFormat    ));

    if(iCompressionFlags == 0)
    {
        iCompressionFlags = (osgsquish::kColourMetricPerceptual | 
                             osgsquish::kColourRangeFit         );
    }

    iCompressionFlags &= ~0x07;

    // TODO !!! code all the cases !!!

    if(getSize()    != 0              &&
       pixelFormat  != OSG_INVALID_PF &&
       (destination != 0 || (pixelFormat != static_cast<Image::PixelFormat>(getPixelFormat()))))
    {

        dest->set(pixelFormat, 
                  getWidth      (), 
                  getHeight     (), 
                  getDepth      (), 
                  getMipMapCount(),
                  getFrameCount (), 
                  getFrameDelay (), 
                  NULL, 
                  getDataType   (), 
                  true, 
                  getSideCount  ());

        sourceData = getData();

        data       = dest->editData();
        destSize   = dest->getSize();

        const UInt16 *sourceDataUC16 = 
            reinterpret_cast<const UInt16 *>(sourceData);

              UInt16 *destDataUC16   = reinterpret_cast<UInt16 *>(data);

        const UInt32 *sourceDataUC32 = 
            reinterpret_cast<const UInt32 *>(sourceData);

              UInt32 *destDataUC32   = reinterpret_cast<UInt32 *>(data);

        const Real32 *sourceDataF32  = 
            reinterpret_cast<const Real32 *>(sourceData);

              Real32 *destDataF32    = reinterpret_cast<Real32 *>(data);

        const Real16 *sourceDataH16  = 
            reinterpret_cast<const Real16 *>(sourceData);

              Real16 *destDataH16    = reinterpret_cast<Real16 *>(data);

        if(data)
        {
            switch (getPixelFormat())
            {
                //-----------------------------------------------------
                case OSG_A_PF:
                    switch (pixelFormat) 
                    {
                        case OSG_A_PF:
                        case OSG_I_PF:
                        case OSG_L_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                case OSG_UINT16_IMAGEDATA:
                                case OSG_UINT32_IMAGEDATA:
                                case OSG_FLOAT32_IMAGEDATA:
                                case OSG_FLOAT16_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                    
                                default:
                                    FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_LA_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        data[destI++] = sourceData[srcI];
                                        data[destI++] = sourceData[srcI++];
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataUC16[destI++] = sourceDataUC16[srcI];
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataUC32[destI++] = sourceDataUC32[srcI];
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataF32[destI++] = sourceDataF32[srcI];
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                    }
                                    break;
                                    
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataH16[destI++] = sourceDataH16[srcI];
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                    }
                                    break;
                                default:
                                    FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;
                            
                        case OSG_RGB_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        data[destI++] = sourceData[srcI];
                                        data[destI++] = sourceData[srcI];
                                        data[destI++] = sourceData[srcI++];
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataUC16[destI++] = sourceDataUC16[srcI];
                                        destDataUC16[destI++] = sourceDataUC16[srcI];
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataUC32[destI++] = sourceDataUC32[srcI];
                                        destDataUC32[destI++] = sourceDataUC32[srcI];
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataF32[destI++] = sourceDataF32[srcI];
                                        destDataF32[destI++] = sourceDataF32[srcI];
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataH16[destI++] = sourceDataH16[srcI];
                                        destDataH16[destI++] = sourceDataH16[srcI];
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                    }
                                    break;
                                default:
                                    FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;
                            
                        case OSG_RGBA_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;
                    default:
                        FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                        break;
                    }
                    break;

                //-----------------------------------------------------
                case OSG_I_PF:
                    switch (pixelFormat) 
                    {
                        case OSG_A_PF:
                        case OSG_I_PF:
                        case OSG_L_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;

                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_LA_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;

                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGB_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGBA_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;
                    default:
                        FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                        break;
                    }
                    break;


                //-----------------------------------------------------
                case OSG_L_PF:
                    switch (pixelFormat) 
                    {
                        case OSG_A_PF:
                        case OSG_I_PF:
                        case OSG_L_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;

                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_LA_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;

                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGB_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGBA_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;
                    default:
                        FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                        break;
                    }
                    break;

                //-----------------------------------------------------
                case OSG_LA_PF:
                    switch (pixelFormat) 
                    {
                        case OSG_A_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    srcI++;
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    srcI++;
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    srcI++;
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    srcI++;
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    srcI++;
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;
                        case OSG_I_PF:
                        case OSG_L_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                    srcI++;
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;
                        case OSG_LA_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                memcpy (data, getData(), destSize);
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGB_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                    srcI++;
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                    srcI++;
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGBA_PF:
                            switch (getDataType())
                            {
                            case OSG_UINT8_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize;)
                                {
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI];
                                    data[destI++] = sourceData[srcI++];
                                    data[destI++] = sourceData[srcI++];
                                }
                                break;
                            case OSG_UINT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                    destDataUC16[destI++] = sourceDataUC16[srcI++];
                                }
                                break;
                            case OSG_UINT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                    destDataUC32[destI++] = sourceDataUC32[srcI++];
                                }
                                break;
                            case OSG_FLOAT32_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                    destDataF32[destI++] = sourceDataF32[srcI++];
                                }
                                break;
                            case OSG_FLOAT16_IMAGEDATA:
                                for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                {
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                    destDataH16[destI++] = sourceDataH16[srcI++];
                                }
                                break;
                            default:
                                FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;
                    default:
                        FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
                        break;
                    }
                    break;

                //-----------------------------------------------------
                case OSG_RGB_PF:
                    switch (pixelFormat) 
                    {
                        case OSG_A_PF:
                        case OSG_I_PF:
                        case OSG_L_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        sum = 0;
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        data[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        destDataF32[destI++] = sumReal / 3.0;
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        destDataH16[destI++] = sumReal / 3.0;
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGB: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;
                        case OSG_LA_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        sum = 0;
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        data[destI++] = sum / 3;
                                        data[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sum / 3;
                                        destDataUC16[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sum / 3;
                                        destDataUC32[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        destDataF32[destI++] = sumReal / 3.0;
                                        destDataF32[destI++] = sumReal / 3.0;
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        destDataH16[destI++] = sumReal / 3.0;
                                        destDataH16[destI++] = sumReal / 3.0;
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGB: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;
                        case OSG_RGB_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                default:
                                    FWARNING (( "RGB: Invalid source IMAGE_DATA_TYPE\n" ));
                                break;
                            }
                            break;

                        case OSG_RGBA_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        sum = 0;
                                        sum += data[destI++] = sourceData[srcI++];
                                        sum += data[destI++] = sourceData[srcI++];
                                        sum += data[destI++] = sourceData[srcI++];
                                        data[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += destDataUC16[destI++] = sourceDataUC16[srcI++];
                                        sum += destDataUC16[destI++] = sourceDataUC16[srcI++];
                                        sum += destDataUC16[destI++] = sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += destDataUC32[destI++] = sourceDataUC32[srcI++];
                                        sum += destDataUC32[destI++] = sourceDataUC32[srcI++];
                                        sum += destDataUC32[destI++] = sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sum / 3;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += destDataF32[destI++] = sourceDataF32[srcI++];
                                        sumReal += destDataF32[destI++] = sourceDataF32[srcI++];
                                        sumReal += destDataF32[destI++] = sourceDataF32[srcI++];
                                        destDataF32[destI++] = sumReal / 3.0;
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += destDataH16[destI++] = sourceDataH16[srcI++];
                                        sumReal += destDataH16[destI++] = sourceDataH16[srcI++];
                                        sumReal += destDataH16[destI++] = sourceDataH16[srcI++];
                                        destDataH16[destI++] = sumReal / 3.0;
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGB: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;
#if defined(GL_COMPRESSED_RGB_S3TC_DXT1_EXT)
                        case OSG_RGB_DXT1:
                        {
                            iCompressionFlags |= osgsquish::kDxt1;

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     255, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
                        case OSG_RGBA_DXT1:
                        {
                            iCompressionFlags |= osgsquish::kDxt1;

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     255, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT)
                        case OSG_RGBA_DXT3:
                        {
                            iCompressionFlags |= osgsquish::kDxt3; 

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     255, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT)
                        case OSG_RGBA_DXT5:
                        {
                            iCompressionFlags |= osgsquish::kDxt5;

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     255, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif

                        default:
                            FWARNING (( "RGB: Invalid target IMAGE_DATA_TYPE\n" ));
                            break;
                    }
                    break;


                    //-----------------------------------------------------
                case OSG_RGBA_PF:
                {
                    switch (pixelFormat) 
                    {
                        case OSG_A_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        srcI += 3;
                                        data[destI++] = sourceData[srcI++];;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        srcI += 3;
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        srcI += 3;
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        srcI += 3;
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        srcI += 3;
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGBA: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;

                        case OSG_I_PF:
                        case OSG_L_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        sum = 0;
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        data[destI++] = sum / 3;
                                        srcI++;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sum / 3;
                                        srcI++;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sum / 3;
                                        srcI++;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        destDataF32[destI++] = sumReal / 3.0;
                                        srcI++;
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        destDataH16[destI++] = sumReal / 3.0;
                                        srcI++;
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGBA: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;

                        case OSG_LA_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        sum = 0;
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        sum += sourceData[srcI++];
                                        data[destI++] = sum / 3;
                                        data[destI++] = sourceData[srcI++];;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        sum += sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sum / 3;
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sum = 0;
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        sum += sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sum / 3;
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        sumReal += sourceDataF32[srcI++];
                                        destDataF32[destI++] = sumReal / 3.0;
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        sumReal = 0;
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        sumReal += sourceDataH16[srcI++];
                                        destDataH16[destI++] = sumReal / 3.0;
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGBA: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;

                        case OSG_RGB_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize;)
                                    {
                                        data[destI++] = sourceData[srcI++];
                                        data[destI++] = sourceData[srcI++];
                                        data[destI++] = sourceData[srcI++];
                                        srcI++;
                                    }
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];
                                        destDataUC16[destI++] = sourceDataUC16[srcI++];
                                        srcI++;
                                    }
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];
                                        destDataUC32[destI++] = sourceDataUC32[srcI++];
                                        srcI++;
                                    }
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                        destDataF32[destI++] = sourceDataF32[srcI++];
                                        srcI++;
                                    }
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    for (srcI = destI = 0; destI < destSize/getComponentSize();)
                                    {
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                        destDataH16[destI++] = sourceDataH16[srcI++];
                                        srcI++;
                                    }
                                    break;
                                default:
                                    FWARNING (( "RGBA: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;

                        case OSG_RGBA_PF:
                            switch (getDataType())
                            {
                                case OSG_UINT8_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_UINT16_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_UINT32_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_FLOAT32_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                case OSG_FLOAT16_IMAGEDATA:
                                    memcpy (data, getData(), destSize);
                                    break;
                                default:
                                    FWARNING (( "RGBA: Invalid source IMAGE_DATA_TYPE\n" ));
                                    break;
                            }
                            break;

#if defined(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
                        case OSG_RGBA_DXT1:
                        {
                            iCompressionFlags |= osgsquish::kDxt1;

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT)
                        case OSG_RGBA_DXT3:
                        {
                            iCompressionFlags |= osgsquish::kDxt3; 

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif
#if defined(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT)
                        case OSG_RGBA_DXT5:
                        {
                            iCompressionFlags |= osgsquish::kDxt5;

#ifdef OSG_DEBUG
                            Int32 iStorage = osgsquish::GetStorageRequirements(getWidth(), 
                                                                               getHeight(), 
                                                                               iCompressionFlags);

                            OSG_ASSERT(iStorage == Int32(destSize));
#endif

                            osgsquish::CompressImage(sourceData, 
                                                     getWidth (), 
                                                     getHeight(),
                                                     data,
                                                     iCompressionFlags);
                        }
                        break;
#endif

                        default:
                            break;
                    }
                    break;
                }

                case OSG_DEPTH_PF:
#if defined(GL_DEPTH_STENCIL_EXT) || defined(GL_DEPTH_STENCIL_NV)
                case OSG_DEPTH_STENCIL_PF:
#endif
                case OSG_ALPHA_INTEGER_PF:
                case OSG_RGB_INTEGER_PF:
                case OSG_RGBA_INTEGER_PF:
                case OSG_BGR_INTEGER_PF:
                case OSG_BGRA_INTEGER_PF:
                case OSG_LUMINANCE_INTEGER_PF:
                case OSG_LUMINANCE_ALPHA_INTEGER_PF:
                case OSG_R_PF:
                case OSG_RG_PF:
                {
                    FFATAL((" 'reformat' NYI\n "));
                }
                break;

                default:
                    FWARNING (( "Unvalid pixeldepth (%d) in reformat() !\n",
                                pixelFormat ));
            }
        }
        if (data)
        {
            // rip the data from the local destImage if necessary
            if(destination == NULL)
            {
                this->set(dest);
            }
        }
    }

    return (data ? true : false);
}

void Image::swapDataEndian(void)
{
    UChar8 *data     = editData();

    UInt32  size     = getSize() / getComponentSize();
    UInt16 *dataUC16 = reinterpret_cast<UInt16 *>(data);
    UInt32 *dataUC32 = reinterpret_cast<UInt32 *>(data);
    Real32 *dataF32  = reinterpret_cast<Real32 *>(data);


    switch (getDataType())
    {
        case OSG_UINT8_IMAGEDATA:
            // do nothing
            break;

        case OSG_UINT16_IMAGEDATA:

            for(UInt32 i=0;i<size;++i)
            {
                UInt16 p = dataUC16[i];

                dataUC16[i] = (((p >> 8)) | (p << 8));
            }
            break;

        case OSG_UINT32_IMAGEDATA:

            for(UInt32 i=0;i<size;++i)
            {
                UInt32 p = dataUC32[i];

                dataUC32[i] =
                    (((p & 0x000000FF) << 24) | ((p & 0x0000FF00) <<  8) |
                     ((p & 0x00FF0000) >>  8) | ((p & 0xFF000000) >> 24) );
            }

            break;

        case OSG_FLOAT32_IMAGEDATA:

            for(UInt32 i=0;i<size;++i)
            {
                Real32 p = dataF32[i];
                UInt8 *b = reinterpret_cast<UInt8 *>(&p);

                std::swap(b[0], b[3]);
                std::swap(b[1], b[2]);

                dataF32[i] = p;
            }
            break;

		case OSG_INT16_IMAGEDATA:
		case OSG_INT32_IMAGEDATA:
        {
            FFATAL((" 'swapDataEndian' NYI\n "));
        }
		break;

        default:
            FWARNING (( "invalid source data type \n"));
            break;
    }
}

/*! It is a simple method to convert the image dataType. Does not change
  the pixelFormat. So you can for example convert a image consisting of
  UChar8 data to Float data.
 */

bool Image::convertDataTypeTo(Int32 destDataType)
{
    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::convertDataTypeTo for compressed image\n"));
        return false;
    }

    if(destDataType == getDataType())
    {
        FWARNING (( "source image and destination image have same data "
                    "types: no conversion possible"));
        return true;
    }

    FINFO(("Try to convert image from dataType %d to %d\n",
           getDataType(), destDataType));

    ImageUnrecPtr dest;

    dest = Image::create();

    dest->set(getPixelFormat(),
              getWidth      (),
              getHeight     (),
              getDepth      (),
              getMipMapCount(),
              getFrameCount (),
              0.0,
              0,
              destDataType,
              true,
              getSideCount()  );

    const UChar8 *sourceData = getData();
          UChar8 *destData   = dest->editData();

    UInt32 sourceSize = getSize() / getComponentSize();

    const UInt16 *sourceDataUC16 = reinterpret_cast<const UInt16 *>(sourceData);
          UInt16 *destDataUC16   = reinterpret_cast<      UInt16 *>(destData  );
    const UInt32 *sourceDataUC32 = reinterpret_cast<const UInt32 *>(sourceData);
          UInt32 *destDataUC32   = reinterpret_cast<      UInt32 *>(destData  );
    const Real32 *sourceDataF32  = reinterpret_cast<const Real32 *>(sourceData);
          Real32 *destDataF32    = reinterpret_cast<      Real32 *>(destData  );
//    const Real16 *sourceDataH16  = reinterpret_cast<const Real16 *>(sourceData);
          Real16 *destDataH16    = reinterpret_cast<      Real16 *>(destData  );

    switch (getDataType())
    {
        case OSG_UINT8_IMAGEDATA:

            switch (destDataType)
            {
                case OSG_UINT16_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataUC16[i] = UInt16(sourceData[i]<<8);
                    }
                    break;

                case OSG_UINT32_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataUC32[i] = UInt32(sourceData[i]<<24);
                    }
                    break;

                case OSG_FLOAT32_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataF32[i] = Real32(sourceData[i]/255.0);
                    }
                    break;

                case OSG_FLOAT16_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataH16[i] = Real16(sourceData[i]/255.0);
                    }
                    break;

                default:
                    FWARNING (( "invalid destination data type \n" ));
                    break;
            }

            break;

        case OSG_UINT16_IMAGEDATA:

            switch (destDataType)
            {
                case OSG_UINT8_IMAGEDATA:
                {
                    UInt16 nMin = UInt16(65535);
                    UInt16 nMax = UInt16(0    );

                    for (UInt32 i = 0; i < sourceSize; ++i)
                    {
                        if(sourceDataUC16[i] > nMax)
                            nMax = sourceDataUC16[i];

                        if(sourceDataUC16[i] < nMin)
                            nMin = sourceDataUC16[i];
                    }

                    Real32 fRange = Real32(nMax - nMin);

                    if (fRange <= 0.0)
                    {
                        for(UInt32 i = 0; i < sourceSize; ++i)
                            destData[i] = 0;
                    }
                    else
                    {
                        for(UInt32 i = 0; i < sourceSize; ++i)
                        {
                            destData[i] = UInt8
                                (255.0 *
                                 (Real32 (sourceDataUC16[i] - nMin)) /
                                 fRange)                              ;
                        }
                    }
                }
                break;

                case OSG_UINT32_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataUC32[i] = UInt32(sourceDataUC16[i]<<16);
                    }
                    break;

                case OSG_FLOAT32_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataF32[i] = Real32(sourceDataUC16[i]/65535.0);
                    }

                    break;

                case OSG_FLOAT16_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataH16[i] = Real16(sourceDataUC16[i]/255.0);
                    }
                    break;

                default:
                    FWARNING (( "invalid destination data type \n" ));
                    break;
            }
            break;

        case OSG_UINT32_IMAGEDATA:

            switch (destDataType)
            {
                case OSG_UINT8_IMAGEDATA:
                {
                    UInt32 nMin = UInt32(4294967295ul);
                    UInt32 nMax = UInt32(0           );

                    for (UInt32 i = 0; i < sourceSize; ++i)
                    {
                        if(sourceDataUC32[i] > nMax)
                            nMax = sourceDataUC32[i];

                        if(sourceDataUC32[i] < nMin)
                            nMin = sourceDataUC32[i];
                    }

                    Real32 fRange = Real32(nMax - nMin);

                    if (fRange <= 0.0)
                    {
                        for(UInt32 i = 0; i < sourceSize; ++i)
                            destData[i] = 0;
                    }
                    else
                    {
                        for(UInt32 i = 0; i < sourceSize; ++i)
                        {
                            destData[i] = UInt8
                                (255.0 *
                                 (Real32(sourceDataUC32[i] - nMin)) /
                                 fRange                             );
                        }
                    }
                }
                break;

                case OSG_UINT16_IMAGEDATA:
                {
                    UInt32 nMin = UInt32(4294967295ul);
                    UInt32 nMax = UInt32(0           );

                    for(UInt32 i = 0; i < sourceSize; ++i)
                    {
                        if(sourceDataUC32[i] > nMax)
                            nMax = sourceDataUC32[i];

                        if(sourceDataUC32[i] < nMin)
                            nMin = sourceDataUC32[i];
                    }

                    Real32 fRange = Real32(nMax - nMin);

                    if(fRange <= 0.0)
                    {
                        for(UInt32 i = 0; i < sourceSize; ++i)
                            destDataUC16[i] = 0;
                    }
                    else
                    {
                        for(UInt32 i = 0; i < sourceSize; ++i)
                            destDataUC16[i] = UInt16
                                (65535.0 *
                                 (Real32(sourceDataUC32[i] - nMin)) /
                                 fRange);
                    }
                }
                break;

                case OSG_FLOAT32_IMAGEDATA:
                    for(UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataF32[i] =
                            (Real32(sourceDataUC32[i])) / 4294967295.0;
                    }
                    break;

                case OSG_FLOAT16_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataH16[i] =
                            (Real16(sourceDataUC32[i])) / REAL16_MAX;
                    }
                    break;

                default:
                    FWARNING(("invalid destination data type \n"));
                    break;
            }
            break;

        case OSG_FLOAT32_IMAGEDATA:

            switch(destDataType)
            {
                case OSG_UINT8_IMAGEDATA:

                    for(UInt32 i = 0; i < sourceSize; i++)
                    {
                        destData[i] = UInt8(sourceDataF32[i]*255.0);
                    }
                    break;

                case OSG_UINT16_IMAGEDATA:

                    for(UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataUC16[i] =
                            UInt16(sourceDataF32[i] * 65535.0);
                    }
                    break;

                case OSG_UINT32_IMAGEDATA:
                    for(UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataUC32[i] =
                            UInt32(sourceDataF32[i] * 4294967295.0);
                    }
                    break;

                case OSG_FLOAT16_IMAGEDATA:

                    for (UInt32 i = 0; i < sourceSize; i++)
                    {
                        destDataH16[i] =
                            Real16(sourceDataF32[i]); // half-constructor
                    }
                    break;

                default:
                    FWARNING(("invalid destination data type \n"));
                    break;
            }
            break;

		case OSG_INT16_IMAGEDATA:
		case OSG_INT32_IMAGEDATA:
        {
            FFATAL((" 'convertDataTypeTo' NYI\n "));
        }
        break;

        default:
            FWARNING (( "invalid source data type \n"));
            break;
    }

    if(dest->getData() != NULL)
    {
        this->set(dest);
    }

    return (getData() ? true : false);
}

/*! It just fills the hole image data with the given pixel value. It is
    mainly used to initialize the image data.
 */

void Image::clear(UChar8 pixelValue)
{
    if(getData() != NULL)
        memset(editData(), pixelValue, getSize());
}

void Image::clearFloat(Real32 pixelValue)
{
    unsigned long  n = getSize()/getComponentSize();
    Real32        *d = reinterpret_cast<Real32 *>(editData());

    if(n && d)
    {
        while(n--)
        {
            *d++ = pixelValue;
        }
    }
}

void Image::clearHalf(Real16 pixelValue)
{
    unsigned long  n = getSize()/getComponentSize();
    Real16        *d = reinterpret_cast<Real16 *>(editData());

    if(n && d)
        while(n--)
            *d++ = pixelValue;
}

/*-------------------------------------------------------------------------*/
/*                             attachment handling                         */

/*! returns true if the image has any attachments
 */

bool Image::hasAttachment(void) const
{
    Image *img=const_cast<Image*>(this);

    ImageGenericAtt *att = dynamic_cast<ImageGenericAtt *>(
        img->Inherited::findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));

    if(att != NULL && att->getType().getNumFieldDescs() > 1)
        return true;
    else
        return false;
}

/*! returns the number of attachments
 */

UInt32 Image::attachmentCount(void) const
{
    Image *img = const_cast<Image*>(this);

    ImageGenericAtt *att = dynamic_cast<ImageGenericAtt *>(
        img->Inherited::findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));

    if(att != NULL)
    {
        return att->getType().getNumFieldDescs() - 1;
    }
    else
    {
        return 0;
    }
}

/*! set a single string attachment for the given key/data pair
 */

void Image::setAttachmentField(const std::string &key,
                               const std::string &data)
{
    ImageGenericAttUnrecPtr att(dynamic_cast<ImageGenericAtt *>(
        findAttachment(
            ImageGenericAtt::getClassType().getGroupId())));


    if(att == NULL)
    {
        att = ImageGenericAtt::create();

        addAttachment(att);
    }

    if(att == NULL)
    {
        FWARNING(("Image::setAttachmentField - can not create attachment\n"));

        return;
    }

    EditFieldHandlePtr field = att->editDynamicFieldByName(key.c_str());

    if(field == NULL)
    {
        SFString::Description pDesc = SFString::Description(
            SFString::getClassType(),
            key.c_str(),
            "",
            0,
            0,
            true,
            Field::SFDefaultFlags,
            static_cast<FieldIndexEditMethodSig>(
                &ImageGenericAtt::editDynamicField),
            static_cast<FieldIndexGetMethodSig >(
                &ImageGenericAtt::getDynamicField ));


        UInt32 fieldId = att->addField(pDesc);

        field = att->editDynamicField(fieldId);
    }

    SFString::EditHandlePtr strField = 
        boost::static_pointer_cast<SFString::EditHandle>(field);

    if(strField != NULL && strField->isValid() == true)
        (*strField)->setValue(data);
}

/*! returns the string attachment for the given key or Null
 */

const std::string *Image::findAttachmentField(const std::string &key) const
{
    Image *img=const_cast<Image*>(this);

    ImageGenericAtt *att = dynamic_cast<ImageGenericAtt *>(
        img->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));

    if(att != NULL)
    {
        GetFieldHandlePtr field = att->getDynamicFieldByName(key.c_str());

        if(field != NULL)
        {
            SFString::GetHandlePtr strField = 
                boost::static_pointer_cast<SFString::GetHandle>(field);

            if(strField != NULL && strField->isValid() == true)
                return &((*strField)->getValue());
        }
    }

    return NULL;
}

/*! Method to scale the image. It just does a very simple but fast
  'nearest' scale. Should handle mipmap and frame data correct.
  The method can operate on the object or stores the result in
  the optional destination Image.
 */

bool Image::scale(Int32  width,
                  Int32  height,
                  Int32  depth,
                  Image *destination)
{
    Image         *destImage;
    UInt32         sw, sh, sd, dw, dh, dd;
    Int32          frame, side, mipmap;
    const UChar8  *src;
    UChar8        *dest;
    Int32          oldWidth =getWidth();
    Int32          oldHeight=getHeight();
    Int32          oldDepth =getDepth();

    if ( (oldWidth  == width ) &&
         (oldHeight == height) &&
         (oldDepth  == depth )   ) 
    {
        if(destination != NULL)
            *destination = *this;
        
        return true;
    }
    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::scale for compressed image\n"));
        return false;
    }

    if(destination != NULL)
    {
        destImage = destination;
    }
    else
    {
        destImage = this;
    }

    // get pixel
    // !!!!!!!!        WARNING WARNING        !!!!!!!!!!!
    // !!!!!!!! Obscure copy of the old Image !!!!!!!!!!!
    const MFUInt8 srcPixel = *getMFPixel();

    // set image data

    destImage->set(PixelFormat(getPixelFormat()),
                   width,
                   height,
                   depth,
                   getMipMapCount(),
                   getFrameCount (),
                   getFrameDelay (),
                   0,
                   getDataType   (),
                   true,
                   getSideCount  ());

    // copy every mipmap in every side in every frame
    for(frame = 0; frame < getFrameCount(); frame++)
    {
        for (side = 0; side < getSideCount(); side++)
        {

            for(mipmap = 0; mipmap < getMipMapCount(); mipmap++)
            {
                // get the memory pointer
                src = (&(srcPixel[0])) +
                    (side  * getSideSize ()) +
                    (frame * getFrameSize()) ;

                if(mipmap)
                {
                    src += calcMipmapSumSize (mipmap,
                                              oldWidth,
                                              oldHeight,
                                              oldDepth);
                }

                dest = destImage->editData(mipmap, frame, side);

                // calc the mipmap size
                sw = oldWidth  >> mipmap;
                sh = oldHeight >> mipmap;
                sd = oldDepth  >> mipmap;

                destImage->calcMipmapGeometry(mipmap, dw, dh, dd);

                // copy and scale the data
                scaleData(src, sw, sh, sd, dest, dw, dh, dd);

            }
        }
    }

    return true;
}

/*! Mirror the image along horizontal, vertical, or depth.
    The method can operate on the object or stores the result in
    the optional destination Image.
 */

bool Image::mirror(bool   horizontal,
                   bool   vertical,
                   bool   flipDepth,
                   Image *destination)
{
    if ( !horizontal && !vertical)
    {
        if(destination != NULL)
            *destination = *this;
        
        return true;
    }

    Image *destImage;

    if(destination != NULL)
    {
        destImage = destination;
    }
    else
    {
        destImage = this;
    }

    // Get pixels.
    // !!!!!!!!        WARNING WARNING        !!!!!!!!!!!
    // !!!!!!!! Obscure copy of the old Image !!!!!!!!!!!
    const MFUInt8 srcPixel = (*getMFPixel());

    UInt32 width = getWidth();
    UInt32 height = getHeight();
    UInt32 depth = getDepth();

    destImage->set(PixelFormat(getPixelFormat()),
                   width,
                   height,
                   depth,
                   getMipMapCount(),
                   getFrameCount (),
                   getFrameDelay (),
                   0,
                   getDataType   (),
                   true,
                   getSideCount  ());

    Int32         frame, side, mipmap;
    const UChar8 *src;
    UChar8       *dest;

    // copy every mipmap in every side in every frame
    for(frame = 0; frame < getFrameCount(); frame++)
    {
        for (side = 0; side < getSideCount(); side++)
        {
            for(mipmap = 0; mipmap < getMipMapCount(); mipmap++)
            {
                // get the memory pointer
                src = (&(srcPixel[0])) +
                      (side  * getSideSize ()) +
                      (frame * getFrameSize());

                if(mipmap)
                {
                    src += calcMipmapSumSize(mipmap, width, height, depth);
                }

                dest = destImage->editData(mipmap, frame, side);
                destImage->calcMipmapGeometry(mipmap, width, height, depth);

                // copy and mirror the data
                mirrorData(src, dest, width, height, depth, horizontal,
                           vertical, flipDepth);
            }
        }
    }
    return true;
}

/*! Scale the image to the next power of 2 dimensions
    The method can operate on the object or stores the result in
    the optional destination Image.
 */

bool Image::scaleNextPower2(Image *destination)
{
  return scale(osgNextPower2(getWidth ()),
               osgNextPower2(getHeight()),
               osgNextPower2(getDepth ()),
               destination              );
}

/*! Crop the image to the given bounding box.
  The method can operate on the object or stores the result in
  the optional destination Image.
 */

bool Image::subImage(Int32  offX,
                     Int32  offY,
                     Int32  offZ,
                     Int32  destW,
                     Int32  destH,
                     Int32  destD,
                     Image *destination)
{
    ImageUnrecPtr destImage(destination);
    bool          retCode   = true;

    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::subImage for compressed image\n"));
        return false;
    }

    if(destination == NULL)
    {
        destImage = Image::create();
    }

    destImage->set(PixelFormat(getPixelFormat()),
                   destW,
                   destH,
                   destD,
                   1,
                   1,
                   0.0,
                   0,
                   getDataType());

    const UChar8  *src =            getData ();
          UChar8 *dest = destImage->editData();

    FDEBUG(("Image::subImage (%d %d %d) - (%d %d %d) - destPtr %p\n",
            offX, offY, offZ, destW, destH, destD, dest));

    // ensure destination data is zero
    memset(dest, 0, destImage->getSize());

    // determine the area to actually copy
    UInt32 xMin = offX;
    UInt32 yMin = offY;
    UInt32 zMin = offZ;

    UInt32 xMax = osgMin(getWidth (), offX + destW);
    UInt32 yMax = osgMin(getHeight(), offY + destH);
    UInt32 zMax = osgMin(getDepth (), offZ + destD);

    // fill the destination buffer with the subdata
    UInt32 destIdx = 0;

    for(UInt32 z = zMin; z < zMax; z++)
    {
        for(UInt32 y = yMin; y < yMax; y++)
        {
            for(UInt32 x = xMin; x < xMax; x++)
            {
                for(Int32 i = 0; i < getBpp(); i++)
                {
                    dest[destIdx] = src[((z * getHeight() + y) *
                                         getWidth() + x) * getBpp() + i];
                    destIdx++;
                }
            }

            destIdx += (destW - (xMax - xMin)) * getBpp();
        }

        destIdx += (destH - (yMax - yMin)) * destW * getBpp();
    }

    // rip the data from the local destImage if necessary
    if(destination == NULL)
    {
        this->set(destImage);
    }

    return retCode;
}

/*! Crop a slice.
  The method can operate on the object or stores the result in
  the optional destination Image.
 */

bool Image::slice(Int32  offX,
                  Int32  offY,
                  Int32  offZ,
                  Image *destination)
{
    ImageUnrecPtr destImage(destination);
    bool          retCode   = true;
    UInt32        counter   = 0;

    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::slice for compressed image\n"));
        return false;
    }

    if(destination == NULL)
    {
        destImage = Image::create();
    }

    FDEBUG(("Image::slice (%d %d %d)\n",
            offX, offY, offZ));

    if(offX >= 0)
        counter++;

    if(offY >= 0)
        counter++;

    if(offZ >= 0)
        counter++;

    if(counter != 1)
    {
        FWARNING(("Image::slice - more/less than one non negative value\n"));
        return false;
    }

    if(offZ >= 0)
    {
        // XY slice
        retCode = subImage(0,
                           0,
                           offZ,
                           getWidth (),
                           getHeight(),
                           1,
                           destImage );
    }

    if(offY >= 0)
    {
        // XZ slice
        destImage->set(PixelFormat(getPixelFormat()),
                       getWidth(),
                       getDepth(),
                       1,
                       1,
                       1,
                       0.0,
                       0,
                       getDataType());

        const UChar8 *src  =            getData ();
              UChar8 *dest = destImage->editData();

        // ensure destination data is zero
        memset(dest, 0, destImage->getSize());

        for(Int32 z = 0; z < getDepth(); z++)
        {
            for(Int32 x = 0; x < getWidth(); x++)
            {
                for(Int32 i = 0; i < getBpp(); i++)
                {
                    dest[(z * getWidth() + x) * getBpp() + i] =
                        src[((z * getHeight() + offY) * getWidth() + x) *
                            getBpp() + i];
                }
            }
        }
    }

    if(offX >= 0)
    {
        // YZ slice
        destImage->set(PixelFormat(getPixelFormat()),
                       getWidth(),
                       getDepth(),
                       1,
                       1,
                       1,
                       0.0,
                       0,
                       getDataType());

        const UChar8 *src  =            getData ();
              UChar8 *dest = destImage->editData();

        // ensure destination data is zero
        memset(dest, 0, destImage->getSize());

        for(Int32 z = 0; z < getDepth(); z++)
        {
            for(Int32 y = 0; y < getHeight(); y++)
            {
                for(Int32 i = 0; i < getBpp(); i++)
                {
                    dest[(z * getHeight() + y) * getBpp() + i] =
                        src[((z * getHeight() + y) * getWidth() + offX) *
                            getBpp() + i];
                }
            }
        }
    }

    // rip the data from the local destImage if necessary
    if(destination == NULL)
    {
        this->set(destImage);
    }

    return retCode;
}

/*! Create mipmaps data, level defines the number of level
  The method can operate on the object or stores the result in
  the optional destination Image.
 */

bool Image::createMipmap(Int32 level, Image *destination)
{
    struct Offset
    {
        Int32   d;
        Int32   h;
        Int32   w;
    };

    Offset  offset[][8] =
    {
        {   // 000
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 100
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 010
            { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 110
            { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0, 0 }, { 1, 1, 0 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 001
            { 0, 0, 0 }, { 0, 0, 1 }, { 0, 0, 0 }, { 0, 0, 0 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 101
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 011
            { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 },
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }
        },
        {   // 111
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 },
            { 0, 0, 1 }, { 1, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 }
        }
    };

    Int32   offsetSize[] = { 0, 2, 2, 4, 2, 4, 4, 8 };

    ImageUnrecPtr destImage(destination);

    Int32   w = getWidth(), h = getHeight(), d = getDepth();
    Int32   wm, hm, dm, wi, hi, di;

    const UChar8  *src;
          UChar8  *dest;
    const UInt16 *sourceDataUC16;
          UInt16 *destDataUC16;
    const UInt32 *sourceDataUC32;
          UInt32 *destDataUC32;
    const Real32 *sourceDataF32;
          Real32 *destDataF32;
    const Real16 *sourceDataH16;
          Real16 *destDataH16;

    if (hasCompressedData())
    {
        FFATAL (("Invalid Image::createMipmap for compressed image\n"));
        return false;
    }

    if(destImage == NULL)
    {
        destImage = Image::create();
    }

    Real32 valueFloat;
    Int32  value, i, elem, dim, side, frame, size, mipmap;
    Int32  channel, lineSize, sliceSize;

    // calc the level count
    if(level < 0)
    {
        level = calcMipmapLevelCount();
    }

    // create destination image
    destImage->set(getPixelFormat(),
                   getWidth(),
                   getHeight(),
                   getDepth(),
                   level,
                   getFrameCount(),
                   getFrameDelay(),
                   0,
                   getDataType(),
                   true,
                   getSideCount());

    // copy the data;
    switch (getDataType())
    {
        case OSG_UINT8_IMAGEDATA:

            for(frame = 0; frame < getFrameCount(); frame++)
            {
                for(side = 0; side < getSideCount(); side++)
                {
                    src = this      ->getData (0, frame, side);
                    dest = destImage->editData(0, frame, side);

                    size = getWidth() * getHeight() * getDepth() * getBpp();

                    memcpy(dest, src, size);

                    src = dest;

                    dest = dest + size;

                    w = getWidth ();
                    h = getHeight();
                    d = getDepth ();

                    for(mipmap = 1; mipmap < level; mipmap++)
                    {
                        lineSize  = w *     getBpp();
                        sliceSize = w * h * getBpp();

                        wm = (w == 1) ? w : (w >> 1);
                        hm = (h == 1) ? h : (h >> 1);
                        dm = (d == 1) ? d : (d >> 1);

                        dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;

                        elem = offsetSize[dim];

                        for(di = 0; di < dm; di++)
                        {
                            for(hi = 0; hi < hm; hi++)
                            {
                                for(wi = 0; wi < wm; wi++)
                                {
                                    for(channel = 0; channel < getBpp(); channel++)
                                    {
                                        value = 0;

                                        for(i = 0; i < elem; i++)
                                        {
                                            value += src[
                                                ((wi * 2) + offset[dim][i].w) * getBpp() +
                                                ((hi * 2) + offset[dim][i].h) * lineSize +
                                                ((di * 2) + offset[dim][i].d) * sliceSize +
                                                channel];
                                        }

                                        *dest++ = Int8(value / elem);
                                    }
                                }
                            }
                        }

                        src += sliceSize;

                        w = wm;
                        h = hm;
                        d = dm;
                  }
                }
            }
            break;

        case OSG_UINT16_IMAGEDATA:

            for(frame = 0; frame < getFrameCount(); frame++)
            {
                for(side = 0; side < getSideCount(); side++)
                {
                    src  = this     ->getData (0, frame, side);
                    dest = destImage->editData(0, frame, side);

                    size = getWidth() * getHeight() * getDepth() * getBpp();

                    memcpy(dest, src, size);

                    src  = dest;
                    dest = dest + size;

                    w = getWidth ();
                    h = getHeight();
                    d = getDepth ();

                    sourceDataUC16 = reinterpret_cast<const UInt16 *>(src );
                    destDataUC16   = reinterpret_cast<      UInt16 *>(dest);

                    for(mipmap = 1; mipmap < level; mipmap++)
                    {
                        lineSize  = w *     (getBpp() / getComponentSize());
                        sliceSize = w * h * (getBpp() / getComponentSize());

                        wm = (w == 1) ? w : (w >> 1);
                        hm = (h == 1) ? h : (h >> 1);
                        dm = (d == 1) ? d : (d >> 1);

                        dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;

                        elem = offsetSize[dim];

                        for(di = 0; di < dm; di++)
                        {
                            for(hi = 0; hi < hm; hi++)
                            {
                                for(wi = 0; wi < wm; wi++)
                                {
                                    for(channel = 0;
                                        channel < (getBpp() / getComponentSize());
                                        channel++)
                                    {
                                        value = 0;

                                        for(i = 0; i < elem; i++)
                                        {
                                            value += sourceDataUC16[
                                                ((wi * 2) + offset[dim][i].w) * (getBpp() / getComponentSize()) +
                                                ((hi * 2) + offset[dim][i].h) * lineSize +
                                                ((di * 2) + offset[dim][i].d) * sliceSize +
                                                channel];
                                        }

                                        *destDataUC16++ = UInt16(value / elem);
                                    }
                                }
                            }
                        }

                        sourceDataUC16 += sliceSize;

                        w = wm;
                        h = hm;
                        d = dm;
                    }
                }
            }
            break;

        case OSG_UINT32_IMAGEDATA:

            for(frame = 0; frame < getFrameCount(); frame++)
            {
                for(side = 0; side < getSideCount(); side++)
                {
                    src  = this     ->getData (0, frame,side);
                    dest = destImage->editData(0, frame,side);

                    size = getWidth() * getHeight() * getDepth() * getBpp();

                    memcpy(dest, src, size);

                    src  = dest;
                    dest = dest + size;

                    w = getWidth ();
                    h = getHeight();
                    d = getDepth ();

                    sourceDataUC32 = reinterpret_cast<const UInt32 *>(src );
                    destDataUC32   = reinterpret_cast<      UInt32 *>(dest);

                    for(mipmap = 1; mipmap < level; mipmap++)
                    {
                        lineSize  = w *     (getBpp() / getComponentSize());
                        sliceSize = w * h * (getBpp() / getComponentSize());

                        wm = (w == 1) ? w : (w >> 1);
                        hm = (h == 1) ? h : (h >> 1);
                        dm = (d == 1) ? d : (d >> 1);

                        dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;

                        elem = offsetSize[dim];

                        for(di = 0; di < dm; di++)
                        {
                            for(hi = 0; hi < hm; hi++)
                            {
                                for(wi = 0; wi < wm; wi++)
                                {
                                    for(channel = 0;
                                        channel < (getBpp()/getComponentSize());
                                        channel++)
                                    {
                                        value = 0;

                                        for(i = 0; i < elem; i++)
                                        {
                                            value += (sourceDataUC32[
                                                          ((wi * 2) + offset[dim][i].w) * (getBpp() / getComponentSize()) +
                                                          ((hi * 2) + offset[dim][i].h) * lineSize +
                                                          ((di * 2) + offset[dim][i].d) * sliceSize +
                                                          channel]/elem);
                                        }
                                        *destDataUC32++ = UInt32(value);
                                    }
                                }
                            }
                        }

                        sourceDataUC32 += sliceSize;

                        w = wm;
                        h = hm;
                        d = dm;
                    }
                }
            }
            break;

        case OSG_FLOAT32_IMAGEDATA:

            for(frame = 0; frame < getFrameCount(); frame++)
            {
                for(side = 0; side < getSideCount(); side++)
                {
                    src  = this     ->getData (0, frame,side);
                    dest = destImage->editData(0, frame,side);

                    size = getWidth() * getHeight() * getDepth() * getBpp();

                    memcpy(dest, src, size);

                    src  = dest;
                    dest = dest + size;

                    w = getWidth ();
                    h = getHeight();
                    d = getDepth ();

                    sourceDataF32 = reinterpret_cast<const Real32 *>(src );
                    destDataF32   = reinterpret_cast<      Real32 *>(dest);

                    for(mipmap = 1; mipmap < level; mipmap++)
                    {
                        lineSize  = w *     (getBpp() / getComponentSize());
                        sliceSize = w * h * (getBpp() / getComponentSize());

                        wm = (w == 1) ? w : (w >> 1);
                        hm = (h == 1) ? h : (h >> 1);
                        dm = (d == 1) ? d : (d >> 1);

                        dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;

                        elem = offsetSize[dim];

                        for(di = 0; di < dm; di++)
                        {
                            for(hi = 0; hi < hm; hi++)
                            {
                                for(wi = 0; wi < wm; wi++)
                                {
                                    for(channel = 0;
                                        channel < (getBpp() / getComponentSize());
                                        channel++)
                                    {
                                        valueFloat = 0;

                                        for(i = 0; i < elem; i++)
                                        {
                                            valueFloat += sourceDataF32[
                                                ((wi * 2) + offset[dim][i].w) * (getBpp() / getComponentSize()) +
                                                ((hi * 2) + offset[dim][i].h) * lineSize +
                                                ((di * 2) + offset[dim][i].d) * sliceSize +
                                                channel];
                                        }

                                        *destDataF32++ = Real32(valueFloat / elem);
                                    }
                                }
                            }
                        }

                        sourceDataF32 += sliceSize;

                        w = wm;
                        h = hm;
                        d = dm;
                    }
                }
            }
            break;

        case OSG_FLOAT16_IMAGEDATA:
            for(frame = 0; frame < getFrameCount(); frame++)
            {
                for(side = 0; side < getSideCount(); side++)
                {
                    src = this->getData(0, frame,side);
                    dest = destImage->editData(0, frame,side);
                    size = getWidth() * getHeight() * getDepth() * getBpp();
                    memcpy(dest,src, size);
                    src = dest;
                    dest = dest + size;
                    w = getWidth();
                    h = getHeight();
                    d = getDepth();

                    sourceDataH16 = reinterpret_cast<const Real16 *>(src );
                    destDataH16   = reinterpret_cast<      Real16 *>(dest);

                    for(mipmap = 1; mipmap < level; mipmap++)
                    {
                        lineSize = w * (getBpp() / getComponentSize());
                        sliceSize = w * h * (getBpp() / getComponentSize());
                        wm = (w == 1) ? w : (w >> 1);
                        hm = (h == 1) ? h : (h >> 1);
                        dm = (d == 1) ? d : (d >> 1);

                        dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;
                        elem = offsetSize[dim];

                        for(di = 0; di < dm; di++)
                        {
                            for(hi = 0; hi < hm; hi++)
                            {
                                for(wi = 0; wi < wm; wi++)
                                {
                                    for(channel = 0; channel < (getBpp()/getComponentSize()); channel++)
                                    {
                                        valueFloat = 0;
                                        for(i = 0; i < elem; i++)
                                        {
                                            valueFloat += sourceDataH16[
                                                ((wi * 2) + offset[dim][i].w) * (getBpp() / getComponentSize()) +
                                                ((hi * 2) + offset[dim][i].h) * lineSize +
                                                ((di * 2) + offset[dim][i].d) * sliceSize +
                                                channel];
                                        }
                                        *destDataH16++ = Real16(valueFloat / elem);
                                    }
                                }
                            }
                        }
                        sourceDataH16 += sliceSize;
                        w = wm;
                        h = hm;
                        d = dm;
                    }
                }
            }
            break;

		case OSG_INT16_IMAGEDATA:
		case OSG_INT32_IMAGEDATA:
        {
            FFATAL((" 'createMipmap' NYI\n "));
        }
        break;

        default:
            FWARNING (( "Invalid IMAGE_DATA_TYPE\n" ));
            break;
    }

    // rip the data from the local destImage if necessary
    if(destination == NULL)
    {
        this->set(destImage);
    }

    return true;
}

bool Image::removeMipmap(void)
{
    if(getMipMapCount() == 1) // no mipmaps nothing to do.
        return true;

    // create destination image
    ImageUnrecPtr destImage = Image::create();

    destImage->set(getPixelFormat(),
                   getWidth      (), 
                   getHeight     (), 
                   getDepth      (),
                   1, 
                   getFrameCount (),
                   getFrameDelay (), 
                   NULL, 
                   getDataType   (),
                   true,
                   getSideCount  ());

    if(!destImage->isValid())
    {
        destImage = NULL;

        return false;
    }

    // copy the data;
    for(Int32 frame = 0; frame < getFrameCount(); frame++)
    {
        for(Int32 side = 0; side < getSideCount(); side++) 
        {
            const UChar8 *src = this->getData(0, frame, side);

            UChar8 *dest = destImage->editData(0, frame, side);

            Int32 size = getWidth() * getHeight() * getDepth() * getBpp();

            memcpy(dest,src, size);
        }
    }

    this->set(destImage);
    
    destImage = NULL;

    return true;
}

/*! Write the image to the a file. The mimetype will be set automatically
  from the fileName suffix. Returns true on success.
 */

bool Image::write(const Char8 *fileName)
{
    return ImageFileHandler::the()->write(this, fileName);
}

/*! Read the image data from a file. Returns true on success.
 */

bool Image::read(const Char8 *fileName)
{
    return ImageFileHandler::the()->read(this, fileName);
}


/*! Store the image to the given mem block as 'mimeType'.
  mimeType can be 0, in which case the method will store the
  object as uncompressed mtd data.
  Returns the number of bytes used.
 */

UInt64 Image::store(const Char8 *mimeType, UChar8 *mem, Int32 memSize)
{
    return ImageFileHandler::the()->store(this,
                                          mimeType,
                                          mem,
                                          memSize);
}

/*! Restore the image from the given mem block. Returns the
  number of bytes used.
 */

UInt64 Image::restore(const UChar8 *mem, Int32 memSize)
{
    return ImageFileHandler::the()->restore(this, mem, memSize);
}


/*-------------------------------------------------------------------------*/
/*                               Constructor / Destructor                  */

/*! Default Constructor. Creates a invalid Image of the size 0x0x0
 */

Image::Image(void) :
     Inherited   (),
    _mipmapOffset(),
    _hash        (0),
    _hashValid   (false)
{
}

/*! Copy Constructor. Creates a copy of the given image
 */

Image::Image(const Image &obj) :
     Inherited   (obj              ),
    _mipmapOffset(obj._mipmapOffset),
    _hash        (obj._hash        ),
    _hashValid   (obj._hashValid   )
{
}

/*! Destructor.
 */

Image::~Image(void)
{
}

/*! Method to check, whether the object data defines a alpha channel or not
 */

bool Image::hasAlphaChannel(void)
{
    return
        (getForceAlphaChannel() == true         ) ||
        (getPixelFormat      () == OSG_RGBA_PF  ) ||
        (getPixelFormat      () == OSG_BGRA_PF  ) ||
        (getPixelFormat      () == OSG_RGBA_DXT1) ||
        (getPixelFormat      () == OSG_RGBA_DXT3) ||
        (getPixelFormat      () == OSG_RGBA_DXT5) ||
        (getPixelFormat      () == OSG_A_PF     ) ||
        (getPixelFormat      () == OSG_I_PF     ) ||
        (getPixelFormat      () == OSG_LA_PF    ) ||

        (getPixelFormat      () == OSG_ALPHA_INTEGER_PF          ) ||
        (getPixelFormat      () == OSG_RGBA_INTEGER_PF           ) ||
        (getPixelFormat      () == OSG_BGRA_INTEGER_PF           ) ||
        (getPixelFormat      () == OSG_LUMINANCE_ALPHA_INTEGER_PF);
}

/*! Method to check, whether the alpha channel is just fully transparent/
    fully opaque
 */
bool Image::isAlphaBinary(void)
{
    return
        (getForceAlphaBinary() == true         ) ||
        (getPixelFormat     () == OSG_RGBA_DXT1);
}

/*! Method to check, whether the data is compressed
 */
bool Image::hasCompressedData(void)
{
  return
      (getForceCompressedData() == true         ) ||
      (getPixelFormat        () == OSG_RGB_DXT1 ) ||
      (getPixelFormat        () == OSG_RGBA_DXT1) ||
      (getPixelFormat        () == OSG_RGBA_DXT3) ||
      (getPixelFormat        () == OSG_RGBA_DXT5);

}

/*! Method to check, whether the object data defines a color channel or not
 */
bool Image::hasColorChannel(void)
{
    return
        ( !( getPixelFormat() == OSG_A_PF  ||
             getPixelFormat() == OSG_I_PF  ||
             getPixelFormat() == OSG_L_PF  ||
             getPixelFormat() == OSG_LA_PF ||

             getPixelFormat() == OSG_ALPHA_INTEGER_PF          ||
             getPixelFormat() == OSG_LUMINANCE_ALPHA_INTEGER_PF )) ||
        getForceColorChannel();
}

/*! Method returns the right frame data for the given time.
 */

const UInt8 *Image::getDataByTime(Time time, UInt32) const
{
    UInt32 frameNum = calcFrameNum(time, true);

    return getData(0, frameNum);
}

UInt8 *Image::editDataByTime(Time time, UInt32)
{
    UInt32 frameNum = calcFrameNum(time, true);

    return editData(0, frameNum);
}

/*! Check all the alpha values to see if they're 0 or 1, return true if they
  are, false if no alpha or intermediate values. No Alpha channel is considered
  0.
 */

bool Image::calcIsAlphaBinary(void)
{
    if(!hasAlphaChannel() || getPixelFormat() == OSG_RGBA_DXT1)
        return true;

    if(getPixelFormat() == OSG_RGBA_DXT3 || getPixelFormat() == OSG_RGBA_DXT5)
    {
        FWARNING(("Image::calcIsAlphaBinary: not implemenetd for DXT3 "
                  "and DXT5 yet, assuming false.\n"));
        return false;
    }

    UInt32 npix = getWidth() * getHeight() * getDepth() * getFrameCount();
    UInt8 pixelsize = getBpp();

    const UInt8 *data = getData();

    switch(getPixelFormat())
    {
        case OSG_LA_PF:
            data += getComponentSize(); break;
        case OSG_BGRA_PF:
        case OSG_RGBA_PF:
            data += getComponentSize() * 3; break;
        default:
            FWARNING(("Image::calcIsAlphaBinary: found unknown "
                      "image format %x, assumning false.\n",
                      getPixelFormat()));
            return false;
    }

    switch(getDataType())
    {
        case OSG_UINT8_IMAGEDATA:
            for(; npix > 0; --npix, data += pixelsize)
            {
                if(*data != 0 && *data != 0xffU)
                    break;
            }
            break;
        case OSG_UINT16_IMAGEDATA:
            for(; npix > 0; --npix, data += pixelsize)
            {
                const UInt16 *d = reinterpret_cast<const UInt16*>(data);
                if(*d != 0 && *d != 0xffffU)
                    break;
            }
            break;
        case OSG_UINT32_IMAGEDATA:
            for(; npix > 0; --npix, data += pixelsize)
            {
                const UInt32 *d = reinterpret_cast<const UInt32*>(data);
                if(*d != 0 && *d != 0xffffffffU)
                    break;
            }
            break;
        case OSG_FLOAT16_IMAGEDATA:
            for(; npix > 0; --npix, data += pixelsize)
            {
                const Real16 *d = reinterpret_cast<const Real16*>(data);
                if(*d != 0 && *d != 1)
                    break;
            }
            break;
        case OSG_FLOAT32_IMAGEDATA:
            for(; npix > 0; --npix, data += pixelsize)
            {
                const Real32 *d = reinterpret_cast<const Real32*>(data);
                if(*d != 0 && *d != 1)
                    break;
            }
            break;
        case OSG_INT16_IMAGEDATA:
        case OSG_INT32_IMAGEDATA:
		{
			FFATAL((" 'calcIsAlphaBinary' NYI\n "));
		}
		break;

        default:
            FWARNING(("Image::calcIsAlphaBinary: found unknown "
                      "data type %d, assumning false.\n",
                      getDataType()));
            return false;
    }

    return npix == 0;
}

/*! Method which returns the frame number for the given time
 */
UInt32 Image::calcFrameNum(Time time, bool OSG_CHECK_ARG(loop)) const
{
    UInt64 frameNum = ((getFrameDelay() > 0) && (getFrameCount() > 0)) ?
        (UInt64(time / getFrameDelay()) % getFrameCount()) : 0;

    return ((frameNum > 0) ? UInt32(frameNum) : 0);
}

/*! Internal used method to calculate the next mipmap geo for the given level
 */
void Image::calcMipmapGeometry(UInt32 mipmapNum,
                               UInt32 &width,
                               UInt32 &height,
                               UInt32 &depth   ) const
{
    width  = getWidth()  ? osgMax(getWidth () >> mipmapNum, 1) : 0 ;
    height = getHeight() ? osgMax(getHeight() >> mipmapNum, 1) : 0 ;
    depth  = getDepth()  ? osgMax(getDepth () >> mipmapNum, 1) : 0 ;
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! Internal used method to calculate the number of mipmaps levels
 */
UInt32 Image::calcMipmapLevelCount(void) const
{
    UInt32  w = getWidth(), h = getHeight(), d = getDepth();
    UInt32 level;

    for (level = 1; true; level++)
    {
        if ((w == 1) && (h == 1) && (d == 1))
        {
            break;
        }
        else
        {
            w = (w >>= 1) ? w : 1;
            h = (h >>= 1) ? h : 1;
            d = (d >>= 1) ? d : 1;
        }
    }
    return level;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            Calculate Mipmap Size                        */

/*! Method to calculate the mem sum of a mipmap level in byte
 */
UInt32 Image::calcMipmapLevelSize ( UInt32 mipmapNum,
                                    UInt32 w, UInt32 h, UInt32 d) const
{
    Int32 sum;

    switch (getPixelFormat())
    {
        case OSG_RGB_DXT1:
        case OSG_RGBA_DXT1:
            sum = (((w?w:1)+3)/4) * (((h?h:1)+3)/4) * 8;
            break;
        case OSG_RGBA_DXT3:
        case OSG_RGBA_DXT5:
            sum = (((w?w:1)+3)/4) * (((h?h:1)+3)/4) * 16;
            break;
        default:
            sum = (w?w:1) * (h?h:1) * getBpp();
            break;
    }

    sum *= (d?d:1);

    return sum;
}

/*! Internal used method to calculate the size in bpp of a single mipmap
  level for the current image settings
 */

UInt32 Image::calcMipmapLevelSize(UInt32 mipmapNum) const
{
    UInt32 w, h, d;
    calcMipmapGeometry(mipmapNum, w, h, d);
    return calcMipmapLevelSize(mipmapNum, w, h, d);
}

/*! Internal used method to calculate the mem sum of all mipmap levels in bpp
 */

UInt32 Image::calcMipmapSumSize(UInt32 mipmapNum,
                                UInt32 w,
                                UInt32 h,
                                UInt32 d) const
{
    Int32 sum = 0;

    if (w && h && d)
    {
        while (mipmapNum--)
        {
            sum += calcMipmapLevelSize(mipmapNum,w,h,d);

            w >>= 1;
            h >>= 1;
            d >>= 1;
        }
    }

    return sum;
}

/*! Method to calculate the mem sum of all mipmap levels in byte
  for the current Image paramter
 */
UInt32 Image::calcMipmapSumSize (UInt32 mipmapNum) const
{
    return calcMipmapSumSize(mipmapNum, getWidth(), getHeight(), getDepth());
}

/*-------------------------------------------------------------------------*/
/*                            Image data                                   */

/*! Internal method to set the data and update related properties.
 */

bool Image::createData(const UInt8 *data, bool allocMem)
{
    Int32 i;
    Int32 mapSizeFormat = sizeof(_formatDic) / sizeof(UInt32[2]);
    Int32 mapSizeType   = sizeof(_typeDic  ) / sizeof(UInt32[2]);

    UInt32 byteCount = 0;

    // set bpp
    UInt32 pixelFormat = 0;
    UInt32 typeFormat  = 0;

    for(i = 0; i < mapSizeFormat; i++)
    {
        if(_formatDic[i][0] == getPixelFormat())
        {
            pixelFormat = _formatDic[i][1];
            break;
        }
    }

    for(i = 0; i < mapSizeType; i++)
    {
        if(_typeDic[i][0] == getDataType())
        {
            typeFormat = _typeDic[i][1];
            break;
        }
    }

    setComponentSize(typeFormat              );
    setBpp          (pixelFormat * typeFormat);

    // set dimension
    setDimension(0);

    if(getDepth() == 1)
    {
        if(getHeight() == 1)
        {
            setDimension(1);
        }
        else
        {
            setDimension(2);
        }
    }
    else
    {
        setDimension(3);
    }

    // set sideSize
    UInt32 mipmapSumSize = calcMipmapSumSize(getMipMapCount());
    setSideSize (mipmapSumSize);

    // set frameSize
    setFrameSize(getSideSize() * getSideCount());


    // copy the data
    if(allocMem && (byteCount = getSize()))
    {
        if(getMFPixel()->size() != byteCount)
        {
            try
            {
                if(byteCount < getMFPixel()->size())
                {
                    editMFPixel()->clear();
                    // free unused memory.
                    MFUInt8 tmp;
                    tmp.swap(*editMFPixel());
                }
                editMFPixel()->resize(byteCount);
            }
            catch(...)
            {
                FFATAL(("Image::createData : Couldn't allocate %u bytes!\n",
                        byteCount));

                return false;
            }
        }

        if(data)
        {
            memcpy(editData(), data, byteCount);
        }
    }
    else
    {
        editMFPixel()->clear();
    }

    return (getData() != NULL);
}

/*! Internal method to scale image data blocks
 */
bool Image::scaleData(const UInt8 *srcData,
                            Int32  srcW,
                            Int32  srcH,
                            Int32  srcD,
                            UInt8 *destData,
                            Int32  destW,
                            Int32  destH,
                            Int32  destD   )
{
    Real32  sx = Real32(srcW) / Real32(destW);
    Real32  sy = Real32(srcH) / Real32(destH);
    Real32  sz = Real32(srcD) / Real32(destD);

    Int32   srcSize = srcW * srcH * srcD * getBpp();

    //  Int32 destDize = destW * destH * destD;

    Int32   x, y, z, p;
    const UInt8  *pSlice;
    const UInt8  *pLine;
    const UInt8  *pPixel;

    if(destW == srcW && destH == srcH && destD == srcD)
    {
        // same size, just copy
        memcpy(destData, srcData, srcSize);
    }
    else
    {       // different size, to 'nearest' copy
        for(z = 0; z < destD; z++)
        {
            pSlice = srcData + int(sz * z) * getBpp() * srcW * srcH;

            for(y = 0; y < destH; y++)
            {
                pLine = pSlice + int(sy * y) * getBpp() * srcW;

                for(x = 0; x < destW; x++)
                {
                    pPixel = pLine + int(sx * x) * getBpp();

                    p = getBpp();

                    while(p--)
                    {
                        *destData++ = *pPixel++;
                    }
                }
            }
        }
    }

    return true;
}

void Image::calcMipmapOffsets(void)
{
    UInt32 mipMapCount = getMipMapCount();
    
    if(mipMapCount == 0)
        mipMapCount = 1;

    _mipmapOffset.resize(mipMapCount);

    /*
    for(UInt32 i=0;i<mipMapCount;++i)
        _mipmapOffset[i] = calcMipmapSumSize[i];
    */

    Int32 sum = 0;

    UInt32 w = getWidth ();
    UInt32 h = getHeight();
    UInt32 d = getDepth ();

    _mipmapOffset[0] = 0;

    for(UInt32 i=1;i<mipMapCount;++i)
    {
        sum += calcMipmapLevelSize(i,w,h,d);

        _mipmapOffset[i] = sum;

        w >>= 1;
        h >>= 1;
        d >>= 1;
    }
}

void Image::calcHash(void) const
{
    _hash = 173;

    boost::hash_range(_hash, _mfPixel.begin(), _mfPixel.end());
    _hashValid = true;
}

/*! Internal method to mirror image data blocks
 */
bool Image::mirrorData(const UInt8 *srcData,
                             UInt8 *destData,
                             Int32  width,
                             Int32  height,
                             Int32  depth,
                             bool   horizontal,
                             bool   vertical,
                             bool   flipDepth)
{
    int dx_step = horizontal ? -1 : 1;
    int dx_start = horizontal ? width-1 : 0;
    int dy_step = vertical ? -1 : 1;
    int dy_start = vertical ? height-1 : 0;
    int dz_step = flipDepth ? -1 : 1;
    int dz_start = flipDepth ? depth-1 : 0;

    int dz = dz_start;
    for(int sz = 0; sz < depth; sz++, dz += dz_step)
    {
        const UInt8 *src_slice = srcData + (sz * getBpp() * width * height);
        UInt8       *dst_slice = destData + (dz * getBpp() * width * height);
        int dy = dy_start;
        for(int sy = 0; sy < height; sy++, dy += dy_step)
        {
            const UInt8 *src_line = src_slice + (sy * getBpp() * width);
            UInt8       *dst_line = dst_slice + (dy * getBpp() * width);
            int dx = dx_start;
            for(int sx = 0; sx < width; sx++, dx += dx_step)
            {
                const UInt8 *src_pixel = src_line + (sx * getBpp());
                UInt8       *dst_pixel = dst_line + (dx * getBpp());
 
                Int32 p = getBpp();
 
                while(p--)
                {
                    *dst_pixel++ = *src_pixel++;
                }
             }
        }
    }
    return true;
}

/*! Assign operator. Does a copy of the given Image object.
 */

Image &Image::operator=(const Image &image)
{
    this->set(PixelFormat(image.getPixelFormat()),
              image.getWidth      (),
              image.getHeight     (),
              image.getDepth      (),
              image.getMipMapCount(),
              image.getFrameCount (),
              image.getFrameDelay (),
              image.getData       (),
              image.getDataType   (),
              true,
              image.getSideCount  ());

    return *this;
}

/*! Less operator; compares the data sizes of the two images
*/
bool Image::operator<(const Image &image)
{
    return (getSize() < image.getSize()) ? true : false;
}

/*! Method to compare the object to another Image instance;
    Checks first all parameter and afterwards the Image data;
*/

bool Image::operator ==(const Image &image)
{
    unsigned long   i, s = getSize();

    if((getWidth      () == image.getWidth      ()) &&
       (getHeight     () == image.getHeight     ()) &&
       (getDepth      () == image.getDepth      ()) &&
       (getMipMapCount() == image.getMipMapCount()) &&
       (getFrameCount () == image.getFrameCount ()) &&
       (getFrameDelay () == image.getFrameDelay ()) &&
       (getPixelFormat() == image.getPixelFormat()) &&
       (getDataType   () == image.getDataType   ()) &&
       (getSideCount  () == image.getSideCount  ()))

    {
        for(i = 0; i < s; ++i)
        {
            if(image.getData()[i] != getData()[i])
                return false;
        }
        return true;
    }
    return false;
}

/*! Method to compare the object to another Image instance;
  Checks first all parameter and afterwards the Image data;
 */

bool Image::operator !=(const Image &image)
{
    return !(*this == image);
}

#if 0
/*! Explicitly notfies parents about a change of the image contents. This is
    not strictly required because they are notified anyways, but can be used
    for optimization by specifying only the area that has actually changed.
    
    \note Currently only TextureChunks are notified.
    
    \warning Successive calls to this function will overwrite the previously
    set dirty area. If an application makes changes to multiple regions
    they have to accumulated by the user before calling this function.
 */
void
Image::imageContentChanged(
    Int32 minX, Int32 maxX, Int32 minY, Int32 maxY, Int32 minZ, Int32 maxZ)
{
    MFFieldContainerPtr::iterator parentsIt  = _mfParents.begin();
    MFFieldContainerPtr::iterator parentsEnd = _mfParents.end  ();
    
    for(; parentsIt != parentsEnd; ++parentsIt)
    {
        TextureChunkPtr texParent = TextureChunkPtr::dcast(*parentsIt);
        
        if(texParent != NullFC)
        {
            texParent->imageContentChanged(minX, maxX, minY, maxY, minZ, maxZ);
        }
    }
}
#endif

OSG_END_NAMESPACE
