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

#ifdef __hpux // prevent int32 clash (model.h/tiff.h)
#define _INT32
#endif

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

#include "OSGTGAImageFileType.h"

#ifdef OSG_WITH_TGA
#include <tiffio.h>
#endif
#include "OSGLog.h"

static const OSG::Char8 *suffixArray[] = 
{
    "tga", "targa"
};

OSG_BEGIN_NAMESPACE


/*! \class TGAImageFileType

  Image File Type to read/write and store/restore Image objects as
  TGA data.
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
 */

bool TGAImageFileType::readHeader(std::istream &is, TGAHeader &header)
{
    UInt8 dum[18];

    is.read(reinterpret_cast<char *>(dum), 18);

    if(is.gcount() != 18)
        return false;

    header.idLength      = dum[ 0];
    header.colorMapType  = dum[ 1];
    header.imageType     = dum[ 2];
    header.cmapFirst     = dum[ 3] | (dum[ 4] << 8);
    header.cmapLength    = dum[ 5] | (dum[ 6] << 8);
    header.cmapEntrySize = dum[ 7];
    header.xOrigin       = dum[ 8] | (dum[ 9] << 8);
    header.yOrigin       = dum[10] | (dum[11] << 8);
    header.width         = dum[12] | (dum[13] << 8);
    header.height        = dum[14] | (dum[15] << 8);
    header.depth         = dum[16];
    header.descriptor    = dum[17];

    return true;
}

bool TGAImageFileType::readCompressedImageData(std::istream &is, 
                                               Image        *pImage)
{
    UInt32 npix = pImage->getWidth() * pImage->getHeight();
    Int32  rep, len;
    UChar8 *data = pImage->editData();
    UInt16 bpp = pImage->getBpp();
    Char8 c[4];

    while(npix > 0)
    {
        rep = is.get();
        if (rep == EOF)
            return false;
        bool repFlag = (rep & 0x80) != 0;
        rep = (rep & 0x7f) + 1;
        if (static_cast<UInt32>(rep) > npix)
            return false;
        npix -= rep;

        if (repFlag == true)
        {
            switch (pImage->getPixelFormat())
            {
            case Image::OSG_L_PF:
                is.read(c, 1);
                if (is.gcount() != 1)
                    return false;
                for (; rep > 0; --rep)
                    *data++ = c[0];
                break;
            case Image::OSG_RGB_PF:
                is.read(c, 3);
                if (is.gcount() != 3)
                    return false;
                for (; rep > 0; --rep)
                {
                    *data++ = c[0];
                    *data++ = c[1];
                    *data++ = c[2];
                }
                break;
            case Image::OSG_RGBA_PF:
                is.read(c, 4);
                if (is.gcount() != 4)
                    return false;
                for (; rep > 0; --rep)
                {
                    *data++ = c[0];
                    *data++ = c[1];
                    *data++ = c[2];
                    *data++ = c[3];
                }
                break;
            default:
                FWARNING(("TGA: unknown pixel "
                          "format!?!\n"));
                return false;
            }
        }
        else // raw packet
        {
            len = bpp * rep;
            is.read(reinterpret_cast<char *>(data), len);
            if (is.gcount() != len)
                return false;
            data += len;
        }
    }
    return true;

}


TGAImageFileType TGAImageFileType::_the("image/x-targa",
                                        suffixArray, 
                                        sizeof(suffixArray));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given fileName. Returns true on success.
 */

bool TGAImageFileType::read(      Image        *pImage, 
                                  std::istream &is, 
                            const std::string  &mimetype)
{
    // read the header
    TGAHeader header;

    if(readHeader(is, header) == false)
        return false;

    // determine format
    Image::PixelFormat format = Image::OSG_INVALID_PF;

    switch(header.imageType & ~0x8)
    {
        case 1: FWARNING(("TGA: 8-bit image not supported!\n"));
            break;
            
        case 2: 
            switch (header.depth)
            {
                case 24: 
                    format = Image::OSG_RGB_PF;
                    break;
                case 32: 
                    format = Image::OSG_RGBA_PF;
                    break;
                default: 
                    FWARNING(("TGA: Unknown pixel depth %d!\n",
                              header.depth));
                    break;
            }
            break;
            
        case 3: 
            format = Image::OSG_L_PF;
            break;
    }

    if(format == Image::OSG_INVALID_PF)
    {
        FWARNING(("Unsupported image type for TGA file!\n"));
        return false;
    }

    // read the image ID
    UInt8 imageid[256];

    is.read(reinterpret_cast<char *>(imageid), header.idLength);

    if(is.gcount() != header.idLength)
        return false;

    imageid[header.idLength] = 0;

    FDEBUG(("TGA: Image ID '%s'\n", imageid));

    // read color map data
    if(header.colorMapType == 1)
    {
        Int32 len = osgMin(header.cmapEntrySize / 3, 8) * header.cmapLength;

        //UInt8 * dum = new UInt8 [len];
        //in.read(reinterpret_cast<char *>(dum), len);
        //delete [] dum;
        is.ignore(len);

        if (is.gcount() != len)
            return false;
    }

    // read image data
    pImage->set(format, header.width, header.height);

    if((header.imageType & 0x8) != 0)
    {
        if(readCompressedImageData(is, pImage) == false)
        {
            FWARNING(("Unsupported image type for TGA file!\n"));
            return false;
        }
    }
    else
    {
        Int32 len = pImage->getSize();

        is.read(reinterpret_cast<char *>(pImage->editData()), len);

        if(is.gcount() != len)
            return false;
    }

    // check origin
    switch (header.descriptor & 0x30)
    {
        case 0x00: // bottom left, ok!
            break;
        case 0x20: // top left
            // do top-bottom swap
        {
            UInt32 bpl = pImage->getBpp() * pImage->getWidth();
            UChar8 *t = pImage->editData(), 
                *b = t + (pImage->getHeight() - 1) * bpl,
                dum;
            
            for(UInt32 y = pImage->getHeight() / 2; y > 0; --y)
            {
                for(UInt32 x = bpl; x > 0; --x, ++t, ++b)
                {
                    dum = *t;
                    *t = *b;
                    *b = dum;
                }
                b -= bpl * 2;
            }
        }
        break;
        case 0x10: // bottom right
        case 0x30: // top right
            FWARNING(("TGA: origin 0x%d not supported!\n",
                      header.descriptor & 0x30));
            return false;
    }
    
    // do BGR -> RGB swap, as GL_BGR_EXT is not supported everywhere
    if(pImage->getPixelFormat() == Image::OSG_RGB_PF ||
       pImage->getPixelFormat() == Image::OSG_RGBA_PF)
    {
        UChar8 *d    = pImage->editData(), dum;
        UInt32  npix = pImage->getWidth() * pImage->getHeight();
        UInt8   bpp  = pImage->getBpp();

        while (npix--)
        {
            dum  = d[2];
            d[2] = d[0];
            d[0] = dum;
            d += bpp;
        }
    }
    
    return true;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
    Returns true on success.
 */

bool TGAImageFileType::write(const Image        *, 
                                   std::ostream &, 
                             const std::string  &)
{
    SWARNING << getMimeType() 
             << " write is not compiled into the current binary " 
             << std::endl;

    return true;
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
*/

TGAImageFileType::TGAImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount) :
    Inherited(mimeType, 
              suffixArray, 
              suffixByteCount)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

TGAImageFileType::~TGAImageFileType(void)
{
}

OSG_END_NAMESPACE
