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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_WITH_JPG
extern "C" 
{

#ifdef WIN32
#define __WIN32__
#endif

#include <setjmp.h>
#include <jpeglib.h>
}
#endif

#ifdef   OSG_SGI_LIB
#include <limits>
#endif
#include "OSGJPGImageFileType.h"
#include <OSGLog.h>

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_JPG
#        define OSG_JPG_ARG(ARG) ARG
#    else
#        define OSG_JPG_ARG(ARG)
#    endif
#else
#    define OSG_JPG_ARG(ARG) ARG
#endif

OSG_USING_NAMESPACE

/*! \class OSG::JPGImageFileType 
    \ingroup GrpSystemImage

  Image File Type to read/write and store/restore Image objects as
  JPEG data.
  
  To be able to load JPEG images you need the IJG JPEG library, 
  version 6 or later (check the Prerequisites page on www.opensg.org). 
  The lib comes with all Linux distributions.
  
  You have to --enable-jpg in the configure line to enable
  the singleton object.
    
*/

#ifdef OSG_WITH_JPG

static const unsigned long BUFFERSIZE = 4096;

struct SourceManager
{
    struct jpeg_source_mgr pub;
    std::istream *is;
    char *buffer;
    SourceManager(j_decompress_ptr cinfo, std::istream &is);
};

static void istream_init_source(j_decompress_ptr cinfo)
{
} // no action necessary

static boolean istream_fill_input_buffer(j_decompress_ptr cinfo)
{
    SourceManager *sourceManager = 
        reinterpret_cast<SourceManager*>(cinfo->src);

    sourceManager->is->read(sourceManager->buffer, BUFFERSIZE);
    
    cinfo->src->next_input_byte = (const JOCTET*)sourceManager->buffer;
    
    if (sourceManager->is->gcount() == 0)
    {
        /* Insert a fake EOI marker */
        sourceManager->buffer[0] = (JOCTET) 0xFF;
        sourceManager->buffer[1] = (JOCTET) JPEG_EOI;
        cinfo->src->bytes_in_buffer = 2;
    }
    else
    {
        cinfo->src->bytes_in_buffer = sourceManager->is->gcount();
    }

    return TRUE;
}

static void istream_skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
    if ((unsigned long)num_bytes <= cinfo->src->bytes_in_buffer)
    {
        cinfo->src->bytes_in_buffer -= num_bytes;
        cinfo->src->next_input_byte += num_bytes;
    }
    else
    {
        num_bytes -= cinfo->src->bytes_in_buffer;
        SourceManager *sourceManager = 
            reinterpret_cast<SourceManager*>(cinfo->src);
        sourceManager->is->ignore(num_bytes);
        cinfo->src->bytes_in_buffer = 0;
        cinfo->src->next_input_byte = 0;
    }
}

static void istream_term_source(j_decompress_ptr cinfo) {} // no action necessary

SourceManager::SourceManager(j_decompress_ptr cinfo, std::istream &is)
{
    pub.init_source = istream_init_source;
    pub.fill_input_buffer = istream_fill_input_buffer;
    pub.skip_input_data = istream_skip_input_data;
    pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
    pub.term_source = istream_term_source;
    pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
    pub.next_input_byte = 0; /* until buffer loaded */
    this->is = &is;
    buffer = (char*)(*cinfo->mem->alloc_small)((j_common_ptr)cinfo, 
                                               JPOOL_IMAGE, 
                                               BUFFERSIZE);
}

struct DestinationManager
{
    struct jpeg_destination_mgr pub;
    std::ostream *os;
    char *buffer;
    DestinationManager(j_compress_ptr cinfo, std::ostream &os);
};

static void ostream_init_destination(j_compress_ptr cinfo)
{
} // no action necessary

static boolean ostream_empty_output_buffer(j_compress_ptr cinfo)
{
    DestinationManager *destinationManager = 
        reinterpret_cast<DestinationManager*>(cinfo->dest);

    destinationManager->os->write(
        destinationManager->buffer, 
        BUFFERSIZE - destinationManager->pub.free_in_buffer);

    destinationManager->pub.next_output_byte = 
        (JOCTET*)destinationManager->buffer;
    destinationManager->pub.free_in_buffer = BUFFERSIZE;

    return destinationManager->os->good() != false ? TRUE : FALSE;
}

static void ostream_term_destination(j_compress_ptr cinfo)
{
} // no action necessary

DestinationManager::DestinationManager(j_compress_ptr cinfo, std::ostream &os)
{
    pub.init_destination = ostream_init_destination;
    pub.empty_output_buffer = ostream_empty_output_buffer;
    pub.term_destination = ostream_term_destination;
    pub.free_in_buffer = 0; /* forces fill_input_buffer on first read */
    pub.next_output_byte = 0; /* until buffer loaded */
    this->os = &os;
    buffer = (char*)(*cinfo->mem->alloc_small)((j_common_ptr)cinfo, 
                                               JPOOL_IMAGE, 
                                               BUFFERSIZE);
}

struct jpeg_mem
{
    struct jpeg_destination_mgr dest;
    struct jpeg_source_mgr      src;
    UChar8                      *buffer;
    UInt32                      memSize;
    UInt32                      dataSize;
} jpeg_mem;

/* */
static void jpeg_mem_init_source(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.src.next_input_byte = (JOCTET *) jpeg_mem.buffer;
    jpeg_mem.src.bytes_in_buffer = (size_t) jpeg_mem.dataSize;
}

/* */

static boolean jpeg_mem_fill_input_buffer(
    j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
    SFATAL << "Missing data. Given data block to small." << std::endl;
    return false;
}

/* */
static void jpeg_mem_skip_input_data(j_decompress_ptr OSG_CHECK_ARG(cinfo    ),
                                     long                           num_bytes)
{
    jpeg_mem.src.next_input_byte += num_bytes;
    jpeg_mem.src.bytes_in_buffer -= num_bytes;
}

/* */
static boolean jpeg_mem_resync_to_restart(
    j_decompress_ptr OSG_CHECK_ARG(cinfo  ),
    int              OSG_CHECK_ARG(desired))
{
    return false;
}

/* */
static void jpeg_mem_term_source(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
}

/* */
static void jpeg_mem_init_destination(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.dest.next_output_byte = (JOCTET *) jpeg_mem.buffer;
    jpeg_mem.dest.free_in_buffer = (size_t) jpeg_mem.memSize;
}

/* */
static boolean jpeg_mem_empty_output_buffer(
    j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    SFATAL << "Not enough space left in buffer." << std::endl;
    return false;
}

/* */
static void jpeg_mem_term_destination(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.dataSize = 
        ((UChar8 *) jpeg_mem.dest.next_output_byte) - 
        ((UChar8 *) jpeg_mem.buffer);
}

/* */
static void jpeg_memory_dest(struct jpeg_compress_struct *cinfo, 
                                    UChar8               *buffer,
                                    UInt32                memSize)
{
    jpeg_mem.buffer=buffer;
    jpeg_mem.memSize=memSize;
    jpeg_mem.dest.init_destination    = jpeg_mem_init_destination;
    jpeg_mem.dest.empty_output_buffer = jpeg_mem_empty_output_buffer;
    jpeg_mem.dest.term_destination    = jpeg_mem_term_destination;

    cinfo->dest=&jpeg_mem.dest;
}

/* */
static void jpeg_memory_src(      struct jpeg_decompress_struct *cinfo, 
                            const        UChar8                 *buffer,
                                         UInt32                  dataSize)
{
    jpeg_mem.buffer = const_cast < UChar8 * > (buffer);
    jpeg_mem.dataSize = dataSize;

    jpeg_mem.src.init_source       = jpeg_mem_init_source;
    jpeg_mem.src.fill_input_buffer = jpeg_mem_fill_input_buffer;
    jpeg_mem.src.skip_input_data   = jpeg_mem_skip_input_data;
    jpeg_mem.src.resync_to_restart = jpeg_mem_resync_to_restart;
    jpeg_mem.src.term_source       = jpeg_mem_term_source;
    cinfo->src = &jpeg_mem.src;
}
#endif

// Static Class Varible implementations:

static const Char8                  *suffixArray[] = { "jpg", "jpeg" };

JPGImageFileType JPGImageFileType:: _the("jpeg",
                                         suffixArray, sizeof(suffixArray),
                                         (OSG_READ_SUPPORTED | 
                                          OSG_WRITE_SUPPORTED));

void JPGImageFileType::setQuality(UInt32 cl)
{
    if(cl > 100)
        cl = 100;
    
    _quality = cl;
}

UInt32 JPGImageFileType::getQuality(void)
{
    return _quality;
}

//-------------------------------------------------------------------------
/*!
  Tries to fill the image object with the data read from
  the given stream. Returns true on success.
*/

bool JPGImageFileType::read(      ImagePtrArg   OSG_JPG_ARG(pImage  ), 
                                  std::istream &OSG_JPG_ARG(is      ),
                            const std::string  &OSG_JPG_ARG(mimetype))
{
#ifdef OSG_WITH_JPG

    struct local_error_mgr
    {
        struct jpeg_error_mgr pub;
        jmp_buf setjmp_buffer;
    } jerr;

    struct jpeg_decompress_struct cinfo;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        return false;
    }

    jpeg_create_decompress(&cinfo);

    SourceManager *sourceManager =
        new ((*cinfo.mem->alloc_small)((j_common_ptr)&cinfo, 
                                       JPOOL_IMAGE, 
                                       sizeof(SourceManager)))
        SourceManager(&cinfo, is);

    cinfo.src = (jpeg_source_mgr*)sourceManager;

    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    Image::PixelFormat pixelFormat;

    switch (cinfo.output_components)
    {
        case 1:
            pixelFormat = Image::OSG_L_PF;
            break;
        case 3:
            pixelFormat = Image::OSG_RGB_PF;
            break;
        default:
            pixelFormat = Image::OSG_INVALID_PF;
            break;
    };
    
    bool retCode;
    
    if(pImage->set(pixelFormat, 
                   cinfo.output_width, 
                   cinfo.output_height) == true)
    {
        unsigned char *destData = pImage->editData() + pImage->getSize();

        int row_stride = cinfo.output_width * cinfo.output_components;

        while (cinfo.output_scanline < cinfo.output_height)
        {
            destData -= row_stride;
            jpeg_read_scanlines(&cinfo, &destData, 1);
        }
        retCode = true;
    }
	else
    {
		retCode = false;
    }

    jpeg_finish_decompress (&cinfo);
    jpeg_destroy_decompress(&cinfo);

	return retCode;

#else

    SWARNING << getMimeType()
             << " read is not compiled into the current binary " 
             << std::endl;

    return false;

#endif
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given stream.
    Returns true on success.
*/

bool JPGImageFileType::write(      ImageConstPtrArg  OSG_JPG_ARG(pImage  ), 
                                   std::ostream     &OSG_JPG_ARG(os      ),
                             const std::string      &OSG_JPG_ARG(mimetype))
{
#ifdef OSG_WITH_JPG

    if((pImage->getBpp() != 1 && 
        pImage->getBpp() != 3) || pImage->getDepth() != 1)
    {
        SWARNING << getMimeType() 
                 << " JPEG write only works for 2D 1 or 3 bpp images " 
                 << std::endl;

        return false;
    }

    struct local_error_mgr
    {
        struct jpeg_error_mgr pub;
        jmp_buf setjmp_buffer;
    } jerr;

    struct jpeg_compress_struct cinfo;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_compress(&cinfo);
        return false;
    }

    jpeg_create_compress(&cinfo);

    DestinationManager *destinationManager =
        new ((*cinfo.mem->alloc_small)((j_common_ptr)&cinfo, 
                                       JPOOL_IMAGE, 
                                       sizeof(DestinationManager)))
        DestinationManager(&cinfo, os);

    cinfo.dest = (jpeg_destination_mgr*)destinationManager;

    cinfo.image_width = pImage->getWidth();
    cinfo.image_height = pImage->getHeight();
    cinfo.input_components = pImage->getBpp();
    cinfo.in_color_space = (pImage->getBpp() == 1) ? JCS_GRAYSCALE : JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, _quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    unsigned char *srcData = 
        const_cast<UInt8 *>(pImage->getData()) + 
        pImage->getSize();
    int row_stride = cinfo.image_width * cinfo.input_components;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        srcData -= row_stride;
        jpeg_write_scanlines(&cinfo, &srcData, 1);
    }

    jpeg_finish_compress (&cinfo);
    jpeg_destroy_compress(&cinfo);

    return true;
#else

    SWARNING << getMimeType() 
             << " write is not compiled into the current binary " 
             << std::endl;

	return false;

#endif
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string JPGImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[2];

    is.read(filecode, 2);
    is.seekg(-2, std::ios::cur);

    return strncmp(filecode, "\xff\xd8", 2) == 0 ?
        std::string(getMimeType()) : std::string();
}


bool JPGImageFileType::validateHeader(const Char8 *fileName, 
                                            bool  &implemented)
{
    implemented = true;

    if(fileName == NULL)
        return false;

    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
        return false;

    UInt16 magic = 0;

    fread((void *) &magic, sizeof(magic), 1, file);

    fclose(file);

#if BYTE_ORDER == LITTLE_ENDIAN
    if(magic == 0xd8ff) // the magic header is big endian need to swap it.
#else
    if(magic == 0xffd8)
#endif
    {
        return true;
    }

    return false;
}


UInt64 JPGImageFileType::restoreData(      ImagePtrArg  OSG_JPG_ARG(pImage ), 
                                     const UChar8      *OSG_JPG_ARG(buffer ),
                                           Int32        OSG_JPG_ARG(memSize))
{
#ifdef OSG_WITH_JPG
    UInt64 retCode = 0;

    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    unsigned char                  *destData;
    Image::PixelFormat              pixelFormat = Image::OSG_INVALID_PF;

    unsigned long                    imageSize;
    typedef struct local_error_mgr  *local_error_ptr;
    struct local_error_mgr          jerr;
    struct jpeg_decompress_struct   cinfo;
    JSAMPARRAY                      imagebuffer;

    int                             row_stride;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);

        return 0;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_memory_src(&cinfo, buffer, memSize);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    switch(cinfo.output_components)
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

    if(pImage->set(pixelFormat, cinfo.output_width, cinfo.output_height))
    {
        imageSize = pImage->getSize();
        destData = pImage->editData() + imageSize;
        row_stride = cinfo.output_width * cinfo.output_components;

        imagebuffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) & cinfo, 
                                                  JPOOL_IMAGE, 
                                                  row_stride, 
                                                  1);

        while(cinfo.output_scanline < cinfo.output_height)
        {
            destData -= row_stride;
            jpeg_read_scanlines(&cinfo, imagebuffer, 1);
            memcpy(destData, *imagebuffer, row_stride);
        }
        
        retCode = imageSize;
    }
    else
    {
        retCode = 0;
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return retCode;
#else
    SWARNING << getMimeType() 
             << " read is not compiled into the current binary " 
             << std::endl;

    return 0;
#endif
}

//-------------------------------------------------------------------------
/*!
Tries to restore the image data from the given memblock.
Returns the amount of data read.
*/
UInt64 JPGImageFileType::storeData(ImageConstPtrArg  OSG_JPG_ARG(pImage ), 
                                   UChar8           *OSG_JPG_ARG(buffer ),
                                   Int32             OSG_JPG_ARG(memSize))
{
#ifdef OSG_WITH_JPG
    if((pImage->getBpp  () != 1 && pImage->getBpp() != 3) ||
       (pImage->getDepth() != 1)                          )
    {
        SWARNING << getMimeType() 
                 << " JPEG storeData only works for 2D 1 or 3 bpp images " 
                 << std::endl;

        return 0;
    }

    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    typedef struct local_error_mgr  *local_error_ptr;

    struct local_error_mgr          jerr;
    struct jpeg_compress_struct     cinfo;
    JSAMPARRAY                      imagebuffer;
    UChar8                          *data;

    cinfo.err = jpeg_std_error(&jerr.pub);

    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_compress(&cinfo);

        return 0;
    }

    jpeg_create_compress(&cinfo);
    jpeg_memory_dest    (&cinfo, buffer, memSize);

    cinfo.image_width = pImage->getWidth();
    cinfo.image_height = pImage->getHeight();
    cinfo.input_components = pImage->getBpp();
    cinfo.in_color_space = (pImage->getBpp() == 1) ? JCS_GRAYSCALE : JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, _quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    imagebuffer = &data;

    while(cinfo.next_scanline < cinfo.image_height)
    {
        data = 
            const_cast<UInt8 *>(pImage->getData()) +
            (pImage->getHeight() - 1 - cinfo.next_scanline) *
            pImage->getWidth() *
            pImage->getBpp();

        jpeg_write_scanlines(&cinfo, imagebuffer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return jpeg_mem.dataSize;
#else
    SWARNING << getMimeType() 
             << " write is not compiled into the current binary " 
             << std::endl;

    return 0;
#endif
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

JPGImageFileType::JPGImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         UInt32  flags) :

     Inherited(mimeType, 
               suffixArray, 
               suffixByteCount, 
               flags),
    _quality(90)
{
}

//-------------------------------------------------------------------------
/*! Dummy Copy Constructor
 */

//-------------------------------------------------------------------------
/*!
 */

JPGImageFileType::~JPGImageFileType(void)
{
}
