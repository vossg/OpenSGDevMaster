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

//-------------------------------
// Includes  
//-------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#ifdef   OSG_SGI_LIB
#include <limits>
#endif
#ifdef OSG_WITH_PNG
#include <png.h>
#endif 

#include "OSGPNGImageFileType.h"
#include "OSGLog.h"

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_PNG
#        define OSG_PNG_ARG(ARG) ARG
#    else
#        define OSG_PNG_ARG(ARG)
#    endif
#else
#    define OSG_PNG_ARG(ARG) ARG
#endif

static const OSG::Char8 *suffixArray[] =
{
    "png"
};

OSG_BEGIN_NAMESPACE

/*! \class PNGImageFileType 

  Image File Type to read/write and store/restore Image objects as
  PNG data.
  
  To be able to load PNG images you need the PNG library, 
  (check the Prerequisites page on www.opensg.org). 
  The lib comes with all Linux distributions.
  
  You have to --enable-png in the configure line to enable
  the singleton object.
  
*/

#ifdef OSG_WITH_PNG

static void isReadFunc(png_structp png_ptr, png_bytep data, png_size_t length)
{
    std::istream *is = 
        reinterpret_cast<std::istream*>(png_get_io_ptr(png_ptr));

    is->read(reinterpret_cast<char*>(data), length);

    if(png_size_t(is->gcount()) != length)
        png_error(png_ptr, "Cannot read from input stream");
}

static void osWriteFunc(png_structp png_ptr, png_bytep data, png_size_t length)
{
    std::ostream *os = 
        reinterpret_cast<std::ostream*>(png_get_io_ptr(png_ptr));

    os->write(reinterpret_cast<char*>(data), length);

    if(os->good() == false)
        png_error(png_ptr, "Cannot write to output stream");
}

static void osFlushFunc(png_structp png_ptr)
{
    std::ostream *os = 
        reinterpret_cast<std::ostream*>(png_get_io_ptr(png_ptr));

    os->flush();

    if(os->good() == false)
        png_error(png_ptr, "Cannot flush output stream");
}

static void errorOutput (png_structp png_ptr, const char *message)
{
    FFATAL   (("PNG: %s\n", message ));
    
    longjmp(png_ptr->jmpbuf, 1);
}

static void warningOutput (png_structp OSG_CHECK_ARG(png_ptr), 
                           const char *message)
{
    FWARNING (("PNG: %s\n", message )); 
}

#endif

PNGImageFileType PNGImageFileType:: _the("image/png",
                                         suffixArray, sizeof(suffixArray),
                                         (OSG_READ_SUPPORTED | 
                                          OSG_WRITE_SUPPORTED));

//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given stream. Returns true on success.
 */

bool PNGImageFileType::read(      Image        *OSG_PNG_ARG(pImage  ), 
                                  std::istream &OSG_PNG_ARG(is      ),
                            const std::string  &OSG_PNG_ARG(mimetype))
{
#ifdef OSG_WITH_PNG

    bool                retCode;
    Image::PixelFormat  pixelFormat = OSG::Image::OSG_INVALID_PF;
    png_structp         png_ptr;
    png_infop           info_ptr;
    png_uint_32         width, wc, height, h, i, res_x, res_y;
    png_byte            bit_depth, channels, color_type;
    png_bytep           *row_pointers, base;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

    if(!png_ptr)
        return false;

    png_set_error_fn(png_ptr, 0, &errorOutput, &warningOutput);

    info_ptr = png_create_info_struct(png_ptr);

    if(!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, 0, 0);
        return false;
    }

    if(setjmp(png_ptr->jmpbuf))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        return false;
    }

    png_set_read_fn(png_ptr, &is, &isReadFunc);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    res_x = png_get_x_pixels_per_meter(png_ptr, info_ptr);
    res_y = png_get_y_pixels_per_meter(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);

    // Convert paletted images to RGB
    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(png_ptr);
        channels = 3;
        bit_depth = 8;
    }

    // Convert < 8 bit to 8 bit
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    {
        png_set_gray_1_2_4_to_8(png_ptr);
        bit_depth = 8;
    }

#if BYTE_ORDER == LITTLE_ENDIAN
    if (bit_depth == 16)
        png_set_swap(png_ptr);
#endif

    // Add a full alpha channel if there is transparency
    // information in a tRNS chunk
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png_ptr);
        ++channels;
    } 

    Int32 dataType;

    switch (bit_depth) 
    {
        case 8:
            dataType = Image::OSG_UINT8_IMAGEDATA;
            break;
        case 16:
            dataType = Image::OSG_UINT16_IMAGEDATA;
            break;
        default:
            FWARNING (( "Invalid bit_depth: %d, can not read png-data\n",
                        bit_depth ));
            return false;
    }

    switch(channels)
    {
        case 1:
            pixelFormat = Image::OSG_L_PF;
            break;
        case 2:
            pixelFormat = Image::OSG_LA_PF;
            break;
        case 3:
            pixelFormat = Image::OSG_RGB_PF;
            break;
        case 4:
            pixelFormat = Image::OSG_RGBA_PF;
        break;
    };
    
    if(pImage->set(pixelFormat, width, height,
                   1, 1, 1, 0.0, 0,
                   dataType))
    {
        // set resolution png supports only pixel per meter,
        // so we do a conversion to dpi with some rounding.
        res_x = png_uint_32((Real32(res_x) / 39.37007874f) < 0.0f ?
                            (Real32(res_x) / 39.37007874f) - 0.5f :
                            (Real32(res_x) / 39.37007874f) + 0.5f);
        res_y = png_uint_32((Real32(res_y) / 39.37007874f) < 0.0f ?
                            (Real32(res_y) / 39.37007874f) - 0.5f :
                            (Real32(res_y) / 39.37007874f) + 0.5f);

        pImage->setResX(Real32(res_x));
        pImage->setResY(Real32(res_y));
        pImage->setResUnit(Image::OSG_RESUNIT_INCH);

        // Calculate the row pointers
        row_pointers = new png_bytep[height];
        wc = width * channels * (bit_depth / 8);
        h = height - 1;
        base = pImage->editData();

        for(i = 0; i < height; ++i)
            row_pointers[i] = base + (h - i) * wc;

        // Read the image data
        png_read_image(png_ptr, row_pointers);

        delete[] row_pointers;

        retCode = true;
    }
    else
    {
        retCode = false;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, 0);

    return retCode;

#else

    SWARNING << getMimeType() 
             << " read is not compiled into the current binary " 
             << std::endl;

    return false;

#endif

}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
    Returns true on success. Based on the public domain example.c
    from the PNG dist.
 */

bool PNGImageFileType::write(const Image        *OSG_PNG_ARG(pImage  ), 
                                   std::ostream &OSG_PNG_ARG(os      ),
                             const std::string  &OSG_PNG_ARG(mimetype))
{
#ifdef OSG_WITH_PNG

    png_structp png_ptr;
    png_infop info_ptr;

    if(pImage->getDimension() < 1 || pImage->getDimension() > 2)
    {
        FWARNING(("PNGImageFileType::write: invalid dimension %d!\n",
                  pImage->getDimension()));

        return false;
    }
    
    /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also check that
    * the library version is compatible with the one used at compile time,
    * in case we are using dynamically linked libraries.  REQUIRED.
     */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                      0, &errorOutput, &warningOutput);

    if(png_ptr == NULL)
        return false;

    /* Allocate/initialize the image information data.  REQUIRED */
    info_ptr = png_create_info_struct(png_ptr);

    if(info_ptr == NULL)
    {
        png_destroy_write_struct(&png_ptr,  NULL);
        return false;
    }
    
    /* set up the output handlers */
    png_set_write_fn(png_ptr, &os, &osWriteFunc, &osFlushFunc);

    /* This is the hard way */

    /* Set the image information here.  Width and height are up to 2^31,
    * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
    * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
    * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
    * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
    * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
    * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
    */

    Int32 ctype;
    switch(pImage->getPixelFormat())
    {
        case Image::OSG_L_PF:       
            ctype = PNG_COLOR_TYPE_GRAY;        
            break;
            
        case Image::OSG_LA_PF:      
            ctype = PNG_COLOR_TYPE_GRAY_ALPHA;          
            break;
            
#if defined(GL_BGR) || defined(GL_BGR_EXT)
        case Image::OSG_BGR_PF:
#endif
        case Image::OSG_RGB_PF:     
            ctype = PNG_COLOR_TYPE_RGB;                 
            break;
            
#if defined(GL_BGRA) || defined(GL_BGRA_EXT)
        case Image::OSG_BGRA_PF:
#endif
        case Image::OSG_RGBA_PF:    
            ctype = PNG_COLOR_TYPE_RGB_ALPHA;           
            break;
            
        default:
            FWARNING(("PNGImageFileType::write: unknown pixel format %d!\n",
                      pImage->getPixelFormat()));
            png_destroy_write_struct(&png_ptr,  NULL);
            return false;
            
    }
    
    Int32 bit_depth;
    switch(pImage->getDataType()) 
    {
        case Image::OSG_UINT8_IMAGEDATA:
            bit_depth = 8;
            break;
        case Image::OSG_UINT16_IMAGEDATA:
            bit_depth = 16;
            break;
        default:
            FWARNING (("Invalid pixeldepth, cannot store data\n"));
            return false;
    };

    png_set_IHDR(png_ptr, info_ptr, pImage->getWidth(), pImage->getHeight(),
                 bit_depth,ctype,      
                 PNG_INTERLACE_NONE, 
                 PNG_COMPRESSION_TYPE_BASE, 
                 PNG_FILTER_TYPE_BASE);

    // set resolution png supports only meter per pixel,
    // so we do a conversion from dpi with some rounding.
    png_uint_32 res_x = png_uint_32(pImage->getResX());
    png_uint_32 res_y = png_uint_32(pImage->getResY());
    if(pImage->getResUnit() == Image::OSG_RESUNIT_INCH)
    {
        res_x = png_uint_32((pImage->getResX() * 39.37007874f) < 0.0f ?
                            (pImage->getResX() * 39.37007874f) - 0.5f :
                            (pImage->getResX() * 39.37007874f) + 0.5f);
        res_y = png_uint_32((pImage->getResY() * 39.37007874f) < 0.0f ?
                            (pImage->getResY() * 39.37007874f) - 0.5f :
                            (pImage->getResY() * 39.37007874f) + 0.5f);
    }

    png_set_pHYs(png_ptr, info_ptr, res_x, res_y,
                 PNG_RESOLUTION_METER);

#if 0
    /* optional significant bit chunk */
    /* if we are dealing with a grayscale image then */
    sig_bit.gray = true_bit_depth;
    /* otherwise, if we are dealing with a color image then */
    sig_bit.red = true_red_bit_depth;
    sig_bit.green = true_green_bit_depth;
    sig_bit.blue = true_blue_bit_depth;
    /* if the image has an alpha channel then */
    sig_bit.alpha = true_alpha_bit_depth;
    png_set_sBIT(png_ptr, info_ptr, sig_bit);


    /* Optional gamma chunk is strongly suggested if you have any guess
    * as to the correct gamma of the image.
    */
    png_set_gAMA(png_ptr, info_ptr, gamma);

    /* Optionally write comments into the image */
    text_ptr[0].key = "Title";
    text_ptr[0].text = "Mona Lisa";
    text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
    text_ptr[1].key = "Author";
    text_ptr[1].text = "Leonardo DaVinci";
    text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
    text_ptr[2].key = "Description";
    text_ptr[2].text = "<long text>";
    text_ptr[2].compression = PNG_TEXT_COMPRESSION_zTXt;
#ifdef PNG_iTXt_SUPPORTED
    text_ptr[0].lang = NULL;
    text_ptr[1].lang = NULL;
    text_ptr[2].lang = NULL;
#endif
    png_set_text(png_ptr, info_ptr, text_ptr, 3);
#endif
    /* other optional chunks like cHRM, bKGD, tRNS, tIME, oFFs, pHYs, */
    /* note that if sRGB is present the gAMA and cHRM chunks must be ignored
    * on read and must be written in accordance with the sRGB profile */

    /* Write the file header information.  REQUIRED */
    png_write_info(png_ptr, info_ptr);

#if BYTE_ORDER == LITTLE_ENDIAN
    if (bit_depth == 16) 
      png_set_swap(png_ptr);
#endif

#if 0
    /* invert monochrome pixels */
    png_set_invert_mono(png_ptr);

    /* Shift the pixels up to a legal bit depth and fill in
    * as appropriate to correctly scale the image.
    */
    png_set_shift(png_ptr, &sig_bit);

    /* pack pixels into bytes */
    png_set_packing(png_ptr);

    /* Get rid of filler (OR ALPHA) bytes, pack XRGB/RGBX/ARGB/RGBA into
    * RGB (4 channels -> 3 channels). The second parameter is not used.
    */
    png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);

    /* swap bytes of 16-bit files to most significant byte first */
    png_set_swap(png_ptr);

    /* swap bits of 1, 2, 4 bit packed pixel formats */
    png_set_packswap(png_ptr);
#endif

    if(pImage->getPixelFormat() == Image::OSG_BGR_PF ||
       pImage->getPixelFormat() == Image::OSG_BGRA_PF )
    {
        /* flip BGR pixels to RGB */
        png_set_bgr(png_ptr);
        
        /* swap location of alpha bytes from ARGB to RGBA */
        png_set_swap_alpha(png_ptr);
    }
    
    /* The easiest way to write the image (you may have a different memory
     * layout, however, so choose what fits your needs best).  You need to
     * use the first method if you aren't handling interlacing yourself.
     */
    png_bytep *row_pointers = new png_bytep [pImage->getHeight()];
    
    for(Int32 k = 0; k < pImage->getHeight(); k++)
    {
        row_pointers[k] = 
            (const_cast<UInt8 *>(pImage->getData())) + 
            (pImage->getHeight() - 1 - k) * 
            pImage->getWidth() * pImage->getBpp();
    }
    
    /* write out the entire image data in one call */
    png_write_image(png_ptr, row_pointers);

    /* It is REQUIRED to call this to finish writing the rest of the file */
    png_write_end(png_ptr, info_ptr);
    
    /* clean up after the write, and free any memory allocated */
    png_destroy_write_struct(&png_ptr, &info_ptr);

    delete [] row_pointers;

    /* that's it */
    return true;

#else
    SWARNING << getMimeType() 
             << " write is not compiled into the current binary " 
             << endLog;

    return false;
#endif
}


//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
*/
std::string PNGImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[4];
    is.read(filecode, 4);
    is.seekg(-4, std::ios::cur);

    return strncmp(filecode, "\x89PNG", 4) == 0 ?
        std::string(getMimeType()) : std::string();
}



bool PNGImageFileType::validateHeader(const Char8 *fileName, bool &implemented)
{
    implemented = true;
    
    if(fileName == NULL)
        return false;
    
    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
        return false;

    std::string magic;

    magic.resize(4);

    fread(static_cast<void *>(&magic[0]), 4, 1, file);

    fclose(file);

    if(magic == "\x89PNG")
    {
        return true;
    }

    return false;
}

#ifdef OSG_WITH_PNG
typedef struct
{
    UChar8 *buffer;
    UInt64 length;
} BufferInfo;

static void user_read_data(png_structp png_ptr,
                           png_bytep data, png_size_t length)
{
    BufferInfo *bufferInfo = static_cast<BufferInfo *>(png_get_io_ptr(png_ptr));
    memcpy(static_cast<void *>(data), 
           static_cast<void *>(bufferInfo->buffer), 
           length);
    bufferInfo->buffer += length;
    bufferInfo->length += length;
}
#endif

/* */
UInt64 PNGImageFileType::restoreData(      Image  *OSG_PNG_ARG  (pImage ),
                                     const UChar8 *OSG_PNG_ARG  (buffer ),
                                           Int32   OSG_CHECK_ARG(memSize))
{
#ifdef OSG_WITH_PNG

    UInt64              retCode;
    Image::PixelFormat  pixelFormat = Image::OSG_INVALID_PF;
    png_structp         png_ptr;
    png_infop           info_ptr;
    png_uint_32         width, wc, height, h, i;
    png_byte            bit_depth, channels, color_type;
    png_bytep           *row_pointers, base;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

    if(!png_ptr)
    {
        return 0;
    }

    png_set_error_fn(png_ptr, 0, &errorOutput, &warningOutput);

    info_ptr = png_create_info_struct(png_ptr);

    if(!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, 0, 0);
        return 0;
    }

    if(setjmp(png_ptr->jmpbuf))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        return 0;
    }

    BufferInfo bufferInfo;
    bufferInfo.buffer = const_cast<UChar8 *>(buffer);
    bufferInfo.length = 0;
    png_set_read_fn(png_ptr, static_cast<void *>(&bufferInfo), user_read_data);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);

    // Convert paletted images to RGB
    if(color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(png_ptr);
        channels = 3;
        bit_depth = 8;
    }

    // Convert < 8 bit to 8 bit
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    {
        png_set_gray_1_2_4_to_8(png_ptr);
        bit_depth = 8;
    }

#if BYTE_ORDER == LITTLE_ENDIAN
    if (bit_depth == 16)
        png_set_swap(png_ptr);
#endif
   
    // Add a full alpha channel if there is transparency
    // information in a tRNS chunk
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png_ptr);
        ++channels;
    }   
                                                                 
    Int32 dataType;

    switch (bit_depth) 
    {
        case 8:
            dataType = Image::OSG_UINT8_IMAGEDATA;
            break;
        case 16:
            dataType = Image::OSG_UINT16_IMAGEDATA;
            break;
        default:
            FWARNING (( "Invalid bit_depth: %d, can not read png-data\n",
                        bit_depth ));
            return false;
    }
    
    switch(channels)
    {
        case 1:
            pixelFormat = Image::OSG_L_PF;
            break;
        case 2:
            pixelFormat = Image::OSG_LA_PF;
            break;
        case 3:
            pixelFormat = Image::OSG_RGB_PF;
            break;
        case 4:
            pixelFormat = Image::OSG_RGBA_PF;
            break;
    };
    
    if(pImage->set(pixelFormat, width, height,
                   1, 1, 1, 0.0, 0,
                   dataType))
    {
        // Calculate the row pointers
        row_pointers = new png_bytep[height];
        wc = width * channels * (bit_depth / 8);
        h = height - 1;
        base = pImage->editData();

        for(i = 0; i < height; ++i)
            row_pointers[i] = base + (h - i) * wc;

        // Read the image data
        png_read_image(png_ptr, row_pointers);
        
        delete[] row_pointers;
        
        retCode = bufferInfo.length;
    }
    else
    {
        retCode = 0;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    
    return retCode;

#else
    SWARNING << getMimeType() 
             << " restoreData is not compiled into the current binary " 
             << std::endl;

    return 0;
#endif
}

#ifdef OSG_WITH_PNG

static void user_write_data(png_structp png_ptr,
                            png_bytep data, png_size_t length)
{
    BufferInfo *bufferInfo = static_cast<BufferInfo *>(png_get_io_ptr(png_ptr));
    memcpy(static_cast<void *>(bufferInfo->buffer), 
           static_cast<void *>(data), 
           length);
    bufferInfo->buffer += length;
    bufferInfo->length += length;
}

static void user_flush_data(png_structp OSG_CHECK_ARG(png_ptr))
{
}

#endif

//-------------------------------------------------------------------------
/*! Tries to restore the image data from the given memblock.
    Returns the amount of data read.
 */

UInt64 PNGImageFileType::storeData(const Image  *OSG_PNG_ARG  (pImage  ), 
                                         UChar8 *OSG_PNG_ARG  (buffer ),
                                         Int32   OSG_CHECK_ARG(memSize))
{
#ifdef OSG_WITH_PNG

    png_structp png_ptr;
    png_infop info_ptr;

    if(pImage->getDimension() < 1 || pImage->getDimension() > 2)
    {
        FWARNING(("PNGImageFileType::write: invalid dimension %d!\n",
                  pImage->getDimension()));
        return 0;
    }

    /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also check that
    * the library version is compatible with the one used at compile time,
    * in case we are using dynamically linked libraries.  REQUIRED.
    */

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                      0, &errorOutput, &warningOutput);
    
    if (png_ptr == NULL)
    {
        return 0;
    }

    /* Allocate/initialize the image information data.  REQUIRED */
    info_ptr = png_create_info_struct(png_ptr);

    if(info_ptr == NULL)
    {
        png_destroy_write_struct(&png_ptr,  NULL);
        return 0;
    }
    
    BufferInfo bufferInfo;
    bufferInfo.buffer = buffer;
    bufferInfo.length = 0;

    png_set_write_fn(png_ptr, 
                     static_cast<void *>(&bufferInfo), 
                     user_write_data, 
                     user_flush_data);

    /* This is the hard way */

    /* Set the image information here.  Width and height are up to 2^31,
    * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
    * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
    * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
    * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
    * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
    * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
    */

    Int32 ctype;
    switch(pImage->getPixelFormat())
    {
        case Image::OSG_L_PF:
            ctype = PNG_COLOR_TYPE_GRAY;        
            break;
            
        case Image::OSG_LA_PF:
            ctype = PNG_COLOR_TYPE_GRAY_ALPHA;          
            break;
            
#if defined(GL_BGR) || defined(GL_BGR_EXT)
        case Image::OSG_BGR_PF:
#endif
        case Image::OSG_RGB_PF: 
            ctype = PNG_COLOR_TYPE_RGB;                 
            break;
            
#if defined(GL_BGRA) || defined(GL_BGRA_EXT)
        case Image::OSG_BGRA_PF:
#endif
        case Image::OSG_RGBA_PF:
            ctype = PNG_COLOR_TYPE_RGB_ALPHA;           
            break;
            
        default:
            FWARNING(("PNGImageFileType::write: unknown pixel format %d!\n",
                      pImage->getPixelFormat()));
            png_destroy_write_struct(&png_ptr,  NULL);

            return 0;
    }
    
    Int32 bit_depth;

    switch (pImage->getDataType()) 
    {
        case Image::OSG_UINT8_IMAGEDATA:
            bit_depth = 8;
            break;
        case Image::OSG_UINT16_IMAGEDATA:
            bit_depth = 16;
            break;
        default:
            FWARNING (("Invalid pixeldepth, cannot store data\n"));
            return 0;
    };

    png_set_IHDR(png_ptr, 
                 info_ptr, 
                 pImage->getWidth(), 
                 pImage->getHeight(),
                 bit_depth,
                 ctype,      
                 PNG_INTERLACE_NONE, 
                 PNG_COMPRESSION_TYPE_BASE, 
                 PNG_FILTER_TYPE_BASE);
    
    /* other optional chunks like cHRM, bKGD, tRNS, tIME, oFFs, pHYs, */
    /* note that if sRGB is present the gAMA and cHRM chunks must be ignored
    * on read and must be written in accordance with the sRGB profile */

    /* Write the file header information.  REQUIRED */

    png_write_info(png_ptr, info_ptr);

#if BYTE_ORDER == LITTLE_ENDIAN
    if (bit_depth == 16)
        png_set_swap(png_ptr);
#endif
    
    if(pImage->getPixelFormat() == Image::OSG_BGR_PF ||
       pImage->getPixelFormat() == Image::OSG_BGRA_PF)
    {
        /* flip BGR pixels to RGB */
        png_set_bgr(png_ptr);
        
        /* swap location of alpha bytes from ARGB to RGBA */
        png_set_swap_alpha(png_ptr);
    }
    
    /* The easiest way to write the image (you may have a different memory
     * layout, however, so choose what fits your needs best).  You need to
     * use the first method if you aren't handling interlacing yourself.
     */

    png_bytep *row_pointers = new png_bytep [pImage->getHeight()];
    
    for(Int32 k = 0; k < pImage->getHeight(); k++)
    {
        row_pointers[k] = 
            (const_cast<UInt8 *>(pImage->getData())) + 
            (pImage->getHeight() - 1 - k) * 
            pImage->getWidth() * pImage->getBpp();
    }
    
    /* write out the entire image data in one call */
    png_write_image(png_ptr, row_pointers);

    /* It is REQUIRED to call this to finish writing the rest of the file */
    png_write_end(png_ptr, info_ptr);
    
    /* clean up after the write, and free any memory allocated */
    png_destroy_write_struct(&png_ptr, &info_ptr);

    delete [] row_pointers;

    /* that's it */
    return bufferInfo.length;
#else
    SWARNING << getMimeType() 
             << " storeData is not compiled into the current binary " 
             << std::endl;

    return 0;
#endif
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

PNGImageFileType::PNGImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         UInt32  flags          ) :

    Inherited(mimeType, suffixArray, suffixByteCount, flags)
{
}


//-------------------------------------------------------------------------
/*! Destructor
 */

PNGImageFileType::~PNGImageFileType(void)
{
}

OSG_END_NAMESPACE

