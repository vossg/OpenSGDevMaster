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
//      Includes                                    
//-------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGBaseFunctions.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGSGIImageFileType.h"

#ifdef OSG_SGI_STL
//#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<int>::max()
#endif
#else
#include <climits>
#endif

static const OSG::Char8 *suffixArray[] = 
{
    "rgb", "rgba", "sgi", "bw"
};

OSG_BEGIN_NAMESPACE

/*! \class SGIImageFileType 
  
  Image File Type to read/write and store/restore Image objects as
  SGI data. 
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
*/


/* the basic reader functions */

/* I found these on the net a long time ago. They didn't contain any copyright
   notice and I couldn't find out where I found them.
   If you wrote them please let us know (info@opensg.org) so that we can either
   credit you or remove them if you have a problem with us using them.
   Thanks
            Dirk
*/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \nohierarchy
 */

struct ImageRec 
{
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short xsize, ysize, zsize;
    unsigned int min, max;
    unsigned int wasteBytes;
    char name[80];
    unsigned long colorMap;
    std::istream *is;
    std::vector<unsigned char> tmp;
    std::vector<unsigned int> rowStart;
    std::vector<unsigned int> rowSize;
};

#endif

static void
ConvertShort(unsigned short *array, long length) 
{
    unsigned b1, b2;
    unsigned char *ptr;

    ptr = reinterpret_cast<unsigned char *>(array);
    while (length--) 
    {
        b1 = *ptr++;
        b2 = *ptr++;
        *array++ = (b1 << 8) | (b2);
    }
}

static void
ConvertLong(unsigned *array, unsigned long length) 
{
    unsigned long b1, b2, b3, b4;
    unsigned char *ptr;

    ptr = reinterpret_cast<unsigned char *>(array);
    while (length--) 
    {
        b1 = *ptr++;
        b2 = *ptr++;
        b3 = *ptr++;
        b4 = *ptr++;
        *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
    }
}

static bool ImageOpen(ImageRec &image, std::istream &is)
{
    image.is = &is;

    is.read(reinterpret_cast<char*>(&image), 12);

    if(is.gcount() != 12)
        return false;

    bool swapFlag = !osgIsBigEndian();

    if(swapFlag == true)
        ConvertShort(&image.imagic, 6);

    if((image.type & 0xFF00) == 0x0100) 
    {
        is.ignore(512 - 12);
        if (is.gcount() != 512 - 12)
            return false;

        int n = image.ysize * image.zsize;
        int len = n * sizeof(unsigned);

        image.rowStart.resize(n);

        is.read(reinterpret_cast<char*>(&(image.rowStart.front())), len);

        if(is.gcount() != len)
            return false;

        image.rowSize.resize(n);

        is.read(reinterpret_cast<char*>(&(image.rowSize.front())), len);

        if(is.gcount() != len)
            return false;

        if(swapFlag == true)
        {
            ConvertLong(&(image.rowStart.front()), n);
            ConvertLong(&(image.rowSize .front()), n);
        }
        unsigned int maxSize = 0;

        for(int i = 0; i < n; ++i)
        {
            if(image.rowSize[i] > maxSize)
                maxSize = image.rowSize[i];
        }

        image.tmp.resize(maxSize);
    }
    else
    {
        image.tmp.resize(image.xsize);
    }

    return true;
}

static bool ImageGetRow(ImageRec      &image, 
                        unsigned char *buf, 
                        int            y, 
                        int            z, 
                        int            stride) 
{
    unsigned char *iPtr = &(image.tmp.front());
    unsigned char *oPtr = buf;

    if((image.type & 0xFF00) == 0x0100) 
    {
        unsigned int row = y + z * image.ysize;

        image.is->seekg(image.rowStart[row], std::ios::beg);

        long len = image.rowSize[row];

        image.is->read(reinterpret_cast<char*>(iPtr), len);

        if(image.is->gcount() != len)
            return false;

        int npix = image.xsize;

        while(len > 0)
        {
            --len;
            unsigned char pixel = *iPtr++;
            int count = pixel & 0x7F;

            if(count == 0)
                break;

            if(npix < count)
                return false;

            npix -= count;

            if(pixel & 0x80) 
            {
                if(len < count)
                    return false;

                len -= count;

                while(count--)
                {
                    *oPtr = *iPtr++;
                    oPtr += stride;
                }
            } 
            else 
            {
                if(len < 1)
                    return false;

                --len;

                pixel = *iPtr++;

                while(count--) 
                {
                    *oPtr = pixel;
                    oPtr += stride;
                }
            }
        }
    } 
    else 
    {
        image.is->seekg(512 + (y + z * image.ysize) * image.xsize, 
                        std::ios::beg);

        image.is->read(reinterpret_cast<char*>(iPtr), image.xsize);

        if(image.is->gcount() != image.xsize)
            return false;

        int count = image.xsize;

        while(count--)
        {
            *oPtr = *iPtr++;
            oPtr += stride;
        }
    }

    return true;
}

static const UInt32 zsize2pixelformat[] =
{
    Image::OSG_L_PF,
    Image::OSG_LA_PF,
    Image::OSG_RGB_PF,
    Image::OSG_RGBA_PF
};

SGIImageFileType SGIImageFileType::_the("image/x-sgi",
                                        suffixArray,
                                        sizeof(suffixArray));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given input stream. Returns true on success.
 */

bool SGIImageFileType::read(      Image            *pImage, 
                                  std::istream     &is, 
                            const std::string      &mimetype)
{
    ImageRec img;

	if(ImageOpen(img, is) == false)
        return false;

    if((img.zsize < 1) || (img.zsize > 4))
        return false;

    pImage->set(zsize2pixelformat[img.zsize - 1], img.xsize, img.ysize);

    unsigned char *lptr = pImage->editData();

    unsigned int lineStride = img.xsize * img.zsize;

    for(int y = 0; y < img.ysize; ++y)
    {
        for(int z = 0; z < img.zsize; ++z)
        {
            if(ImageGetRow(img, lptr + z, y, z, img.zsize) == false)
                return false;
        }

        lptr += lineStride;
    }

    return true;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
    Returns true on success.
 */

bool SGIImageFileType::write(const Image            *pImage, 
                                   std::ostream     &os, 
                             const std::string      &mimetype)
{ 
    FWARNING(("SGIImageFileType::write: not implemented yet!\n"));

    return false;
}

bool SGIImageFileType::validateHeader(const Char8 *fileName, bool &implemented)
{
    implemented = true;

    if(fileName == NULL)
        return false;
    
    FILE *file = fopen(fileName, "rb");

    if(file == NULL)
        return false;

    UInt16 magic = 0;

    fread(static_cast<void *>(&magic), sizeof(magic), 1, file);

    fclose(file);

#if BYTE_ORDER == LITTLE_ENDIAN
    if(magic == 0xda01) // the magic header is big endian need to swap it.
#else
    if(magic == 0x01da)
#endif
    {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string SGIImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[2];

    is.read(filecode, 2);
    is.seekg(-2, std::ios::cur);

    return strncmp(filecode, "\x01\xda", 2) == 0 ?
        std::string(getMimeType()) : std::string();
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

SGIImageFileType::SGIImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[], 
                                         UInt16  suffixByteCount) :

    Inherited(mimeType, suffixArray, suffixByteCount)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

SGIImageFileType::~SGIImageFileType(void)
{
}

OSG_END_NAMESPACE

