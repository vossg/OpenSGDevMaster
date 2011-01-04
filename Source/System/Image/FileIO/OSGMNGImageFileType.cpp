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
//  Includes
//-------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#ifdef   OSG_SGI_LIB
#include <limits>
#endif

#ifdef MNG_LIB
#include <mng.h>
#endif

#include "OSGMNGImageFileType.h"
#include "OSGLog.h"

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_MNG
#        define OSG_MNG_ARG(ARG) ARG
#    else
#        define OSG_MNG_ARG(ARG)
#    endif
#else
#    define OSG_MNG_ARG(ARG) ARG
#endif

// Static Class Varible implementations:
static const OSG::Char8 *suffixArray[] = 
{
    "mng"
};

OSG_BEGIN_NAMESPACE

/*! \class MNGImageFileType 

  Image File Type to read/write and store/restore Image objects as
  MNG data.
  
  To be able to load MNG images you need the MNG library, 
  (check the Prerequisites page on www.opensg.org). 
  The lib comes with all Linux distributions.
  
  You have to --enable-mng in the configure line to enable
  the singleton object.
    
*/

MNGImageFileType MNGImageFileType::_the("video/x-mng",
                                        suffixArray, 
                                        sizeof(suffixArray));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
   the given fileName. Returns true on success.
 */

bool MNGImageFileType::read(      Image            *, 
                                  std::istream     &, 
                            const std::string      &)
{

#ifdef MNG_LIB

  /*

    png_structp png_ptr;
    png_infop info_ptr;
    png_uint_32 width, wc, height, h, i;
    png_byte bit_depth, channels, color_type;
    png_bytep *row_pointers, base;
    FILE *fd;
  bool retCode;

    if ((fd = fopen(fileName, "rb")) == 0) {
        cerr << "Could not open file " << fileName << std::endl;
        return false;
    }

    png_ptr = png_create_read_struct(MNG_LIBMNG_VER_STRING, 0, 0, 0);
    if (!png_ptr) {
        fclose(fd);
        return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fclose(fd);
        png_destroy_read_struct(&png_ptr, 0, 0);
        return false;
    }

    if (setjmp(png_ptr->jmpbuf)) {
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        fclose(fd);
        return false;
    }

    png_init_io(png_ptr, fd);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);

    if (image.set(width, height, channels)) {

        // Convert paletted images to RGB
        if (color_type == MNG_COLOR_TYPE_PALETTE && bit_depth <= 8)
            png_set_expand(png_ptr);
        // Convert < 8 bit to 8 bit
        if (color_type == MNG_COLOR_TYPE_GRAY && bit_depth < 8)
            png_set_expand(png_ptr);
        // Add a full alpha channel if there is transparency
        // information in a tRNS chunk
        if (png_get_valid(png_ptr, info_ptr, MNG_INFO_tRNS))
            png_set_expand(png_ptr);

        // Convert 16 bit to 8 bit
        if (bit_depth == 16)
            png_set_strip_16(png_ptr);

        // Calculate the row pointers
        row_pointers = new png_bytep[height];
        wc = width * channels;
        h = height - 1;
        base = image.data();
        for (i = 0; i < height; ++i)
            row_pointers[i] = base + (h - i) * wc;

        // Read the image data
        png_read_image(png_ptr, row_pointers);

        delete [] row_pointers;

        retCode = true;
    }
    else
        retCode = false;

    png_destroy_read_struct(&png_ptr, &info_ptr, 0);

    fclose(fd);

    return retCode;

  */

    SWARNING << getMimeType()
             << " write is not implemented "
             << endLog;

#else

    SWARNING << getMimeType()
             << " read is not compiled into the current binary "
             << std::endl;

  return false;

#endif

}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
    Returns true on success.
 */

bool MNGImageFileType::write(const Image        *, 
                                   std::ostream &, 
                             const std::string  &)
{

#ifdef MNG_LIB

    SWARNING << getMimeType()
             << " write is not implemented "
             << endLog;

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

std::string MNGImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[4];

    is.read(filecode, 4);
    is.seekg(-4, std::ios::cur);

    if (strncmp(filecode, "\x8aMNG", 4) == 0)
        return std::string(getMimeType());
    if (strncmp(filecode, "\x8aJNG", 4) == 0)
        return std::string(getMimeType());

    return std::string();
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

MNGImageFileType::MNGImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount) :

    Inherited(mimeType, suffixArray, suffixByteCount)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

MNGImageFileType::~MNGImageFileType (void )
{
}

OSG_END_NAMESPACE

