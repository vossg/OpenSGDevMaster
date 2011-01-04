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

#include <climits>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGPNMImageFileType.h"

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
    "pnm", "pbm", "pgm", "ppm"
};

OSG_BEGIN_NAMESPACE

/*! \class PNMImageFileType 

  Image File Type to read/write and store/restore Image objects as
  PNM data. Should work with binary and ascii pnm/pbm/pgm/ppm data.
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
*/

PNMImageFileType PNMImageFileType::_the("image/x-portable-bitmap",
                                        suffixArray, sizeof(suffixArray),
                                        (OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED));


//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given stream. Returns true on success.
 */

bool PNMImageFileType::read(      Image        *pImage, 
                                  std::istream &in, 
                            const std::string  &mimetype)
{
    bool           isBinary = true;
    Int16          type = 0, width, height, lineSize, maxValue=0, value, x, y;
    UInt32         i, n;
    UChar8        *imageData = 0;
    UInt8          id, commentKey = '#';

    in >> id >> type;
    in.ignore(INT_MAX, '\n');

    while(in.peek() == commentKey)
        in.ignore(INT_MAX, '\n');

    in >> width >> height;

    isBinary = ((type > 3) && (type < 7)) ? true : false;

    switch(type)
    {
        case 1:
        case 4:
            maxValue = 1;
            pImage->set(Image::OSG_L_PF, width, height);
            break;
        case 2:
        case 5:
            maxValue = 0;
            pImage->set(Image::OSG_L_PF, width, height);
            break;
        case 3:
        case 6:
            maxValue = 0;
            pImage->set(Image::OSG_RGB_PF, width, height);
            break;
        case 7: // LA extention 
            FWARNING (("Read PNM type %d: LA-ascii extention\n",type ));
            maxValue = 0;
            pImage->set(Image::OSG_LA_PF, width, height);
            break;
        case 8: // RGBA extention
            FWARNING (("Read PNM type %d: RGBA-ascii extention\n",type ));
            maxValue = 0;
            pImage->set(Image::OSG_RGBA_PF, width, height);
            break;
        default:
            SWARNING << "unknown image format type " << type << std::endl;
            break;
    }
    
    if(!maxValue)
    {
        in >> maxValue;

        if(maxValue != 255)
        {
            SWARNING <<
                "unknown max value " <<
                maxValue <<
                ", can't read the image" <<
                std::endl;
            maxValue = 0;
        }
    }

    // eat the endline
    in.ignore(INT_MAX, '\n');

    if(maxValue && (imageData = pImage->editData()))
    {
        SINFO <<
            "Read pnm file of type " <<
            type <<
            ", " <<
            width <<
            "x" <<
            height <<
            std::endl;

        lineSize = width * pImage->getBpp();

        if(isBinary)
        {   // image is binary
            for(y = height - 1; y >= 0; y--)
            {
                in.read(reinterpret_cast<Char8 *>(&(imageData[y * lineSize])),
                        lineSize);
            }
        }
        else
        {   // image is ascii
            for(y = height - 1; y >= 0; y--)
            {
                for(x = 0; x < lineSize; x++)
                {
                    in >> value;
                    imageData[y * lineSize + x] = UChar8(value);
                }
            }
        }

        if(maxValue == 1)
        {
            n = pImage->getSize();

            for(i = 0; i < n; i++)
                imageData[0] *= 255;
        }
    }

    return true;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given stream.
    Returns true on success.
 */

bool PNMImageFileType::write(const Image         *pImage, 
                                   std::ostream  &out, 
                             const std::string   &mimetype)
{
          Int16    p, y, x, lineSize;
          UInt16   bpp = pImage->getBpp();
    const UInt8   *data = 0;

    switch(bpp)
    {
        case 1:
        case 2:
            out << "P5" << std::endl;
            break;
        case 3:
        case 4:
            out << "P6" << std::endl;
            break;
    }
    
    out << "# PNMImageFileType write" << std::endl;
    out << pImage->getWidth() << " " << pImage->getHeight() << std::endl;
    out << "255" << std::endl;

    if(bpp & 1)
    {
        // with alpha
        lineSize = pImage->getBpp() * pImage->getWidth();

        for(y = pImage->getHeight() - 1; y >= 0; y--)
        {
            out.write(reinterpret_cast<const char *>(pImage->getData() + 
                                                     (lineSize * y)), 
                      lineSize);
        }
    }
    else
    {
        // skip alpha
        lineSize = pImage->getBpp() * pImage->getWidth();

        for(y = pImage->getHeight() - 1; y >= 0; y--)
        {
            data = (pImage->getData() + (lineSize * y));

            for(x = 0; x < pImage->getWidth(); x++)
            {
                for(p = bpp - 1; p--;)
                    out << *data++;

                data++;
            }
        }
    }

    return data ? true : false;
}

//-------------------------------------------------------------------------
/*!
Tries to determine the mime type of the data provided by an input stream
by searching for magic bytes. Returns the mime type or an empty string
when the function could not determine the mime type.
*/
std::string PNMImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[2];
    is.read(filecode, 2);
    is.seekg(-2, std::ios::cur);

    if (strncmp(filecode, "P1", 2) == 0)
        return std::string(getMimeType());
    if (strncmp(filecode, "P2", 2) == 0)
        return std::string(getMimeType());
    if (strncmp(filecode, "P3", 2) == 0)
        return std::string(getMimeType());
    if (strncmp(filecode, "P4", 2) == 0)
        return std::string(getMimeType());
    if (strncmp(filecode, "P5", 2) == 0)
        return std::string(getMimeType());
    if (strncmp(filecode, "P6", 2) == 0)
        return std::string(getMimeType());

    return std::string();
}

//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

PNMImageFileType::PNMImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         UInt32  flags) :

    Inherited(mimeType,suffixArray, suffixByteCount, flags)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

PNMImageFileType::~PNMImageFileType(void)
{
}

OSG_END_NAMESPACE

