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
#include <cmath>
#include <memory.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"
#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"
#include "OSGFileSystem.h"
#include "OSGImageFunctions.h"

#include "OSGCHDRImageFileType.h"

// Static Class Varible implementations: 
static const OSG::Char8 *suffixArray[] = 
{
    "chdr"
};

OSG_BEGIN_NAMESPACE

/*! \class HDRImageFileType 

Image File Type to read/write and store/restore Image objects as
HDR data.

All the type specific code is included in the class. Does
not depend on external libs.
    
 */

/*****************************
 *   Types
 *****************************/

CHDRImageFileType CHDRImageFileType::_the("chdr",
                                          suffixArray, sizeof(suffixArray),
                                          OSG_READ_SUPPORTED);


/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/


/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
  Tries to fill the image object with the data read from
  the given input stream. Returns true on success.
*/

bool CHDRImageFileType::read(      Image        *image, 
                                   std::istream &is, 
                             const std::string  &mimetype)
{
    ImageUnrecPtr pTmpImage = Image::create();

    bool returnValue   = Inherited::read(pTmpImage, is, mimetype);

    if(returnValue == false)
    {
        pTmpImage = NULL;

        return returnValue;
    }


    returnValue = convertCrossToCubeMap(pTmpImage,
                                        image);

    pTmpImage = NULL;

    return returnValue;
}

//-------------------------------------------------------------------------
/*!
  Tries to write the image object to the given output stream.
  Returns true on success.
*/

bool CHDRImageFileType::write(const Image        *image, 
                                    std::ostream &os, 
                              const std::string  &mimetype)
{
#if 0
    if(image->getDataType() != Image::OSG_FLOAT32_IMAGEDATA)
    {
        FWARNING(("HDRImageFileType::write: Image has non float data "
                  "type!\n"));
        return false;
    }
    
    if(!os.good())
        return false;

    int width  = image->getWidth();
    int height = image->getHeight();

    os << "#?RADIANCE" << std::endl;
    os << "# Written with OpenSG" << std::endl;
    os << "FORMAT=32-bit_rle_rgbe" << std::endl;
    os << "EXPOSURE=" << 1.0f << std::endl << std::endl;
    os << "-Y " << height << " +X " << width << std::endl;

    RGBE *rgbe_scan = new RGBE[width];

    Real32 *data = ((Real32 *)(image->getData()));

    //upside down !!!
    for(int y=height-1;y>=0;y--)
    {
        if (fwritecolrs(os, 
                        &data[y * width * 3], 
                        rgbe_scan, 
                        width, 
                        height) < 0)
        {
            delete [] rgbe_scan;
            return false;
        }
    }

    delete [] rgbe_scan;
#endif

    return true;
}

//-------------------------------------------------------------------------
/*!
  Tries to restore the image data from the given memblock.
  Returns the amount of data read.
*/

UInt64 CHDRImageFileType::restoreData(      Image  *image, 
                                      const UChar8 *buffer,
                                            Int32         )
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*!
  Tries to store the image data to the given memblock.
  Returns the amount of data written.
*/

UInt64 CHDRImageFileType::storeData(const Image  *image, 
                                          UChar8 *buffer,
                                          Int32   OSG_CHECK_ARG(memSize))
{
    UInt32 dataSize = image->getSize();

    const UChar8 *src = image->getData();

    if(dataSize && src && buffer)
        memcpy(buffer, src, dataSize);
  
    return dataSize;
} 


//-------------------------------------------------------------------------
/*!
  Constructor used for the singleton object
*/

CHDRImageFileType::CHDRImageFileType(const Char8 *mimeType,
                                     const Char8 *suffixArray[], 
                                           UInt16 suffixByteCount,
                                           UInt32 flags          ) :
    Inherited(mimeType, 
              suffixArray, 
              suffixByteCount, 
              flags )
{
}

//-------------------------------------------------------------------------
/*!
  Destructor
*/

CHDRImageFileType::~CHDRImageFileType(void)
{
}

OSG_END_NAMESPACE
