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

#include <iostream>
#include <fstream>

#include "OSGLog.h"

#include "OSGMTDImageFileType.h"

static const OSG::Char8 *suffixArray[] = 
{
    "mtd","opensg","opensgImage"
};

OSG_BEGIN_NAMESPACE

/*! \class MTDImageFileType 

  Image File Type to read/write and store/restore Image objects as
  MTD data.
  
  All the type specific code is included in the class. Does
  not depend on external libs.
  
 */

MTDImageFileType MTDImageFileType::_the("image/x-mtd",
                                        suffixArray, sizeof(suffixArray),
                                        (OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED));

//-------------------------------------------------------------------------
/*! Tries to fill the image object with the data read from
    the given stream. Returns true on success.
 */

bool MTDImageFileType::read(      Image         *pImage, 
                                  std::istream  &is, 
                            const std::string   &mimetype)
{
  bool retCode = false;
  Head head;
  void *headData = static_cast<void*>(&head);
  unsigned dataSize, headSize = sizeof(Head);
  
  if(is.read(static_cast<char *>(headData), headSize) && 
     head.netToHost()                                 &&
     pImage->set(Image::PixelFormat(head.pixelFormat), 
                 head.width, 
                 head.height, 
                 head.depth, 
                 head.mipmapCount, 
                 head.frameCount, 
                 float(head.frameDelay) / 1000.0, 
                 0,
                 (head.dataType ? 
                  Image::Type(head.dataType) : Image::OSG_UINT8_IMAGEDATA), 
                 true, 
                 head.sideCount)                       &&
     (dataSize = pImage->getSize())                    && 
     is.read(reinterpret_cast<char *>(pImage->editData()), dataSize )    )
  {
      retCode = true;
  }
  else
  {
      retCode = false;
  }

  return retCode;
}

//-------------------------------------------------------------------------
/*!
Tries to write the image object to the given stream.
Returns true on success.
*/
bool MTDImageFileType::write(const Image        *pImage, 
                                   std::ostream &os, 
                             const std::string  &mimetype)
{
    bool retCode = false;

    Head head;

    const void *headData = static_cast<void *>(&head);
    unsigned dataSize = pImage->getSize(), headSize = sizeof(Head);

    head.pixelFormat  = pImage->getPixelFormat();
    head.width        = pImage->getWidth();
    head.height       = pImage->getHeight();
    head.depth        = pImage->getDepth();
    head.mipmapCount  = pImage->getMipMapCount();
    head.frameCount   = pImage->getFrameCount();
    head.frameDelay   = short(pImage->getFrameDelay() * 1000.0);
    head.sideCount    = pImage->getSideCount();
    head.dataType     = pImage->getDataType();
    head.hostToNet();
  
    if(os.write(static_cast<const char *>(headData), headSize) && 
       dataSize                                                 && 
       os.write(reinterpret_cast<const char *>(pImage->getData()), dataSize) )
    {
        retCode = true;
    }
    else
    {
        retCode = false; 
    }

    return retCode;
}


//-------------------------------------------------------------------------
/*!
Tries to restore the image data from the given memblock.
Returns the amount of data read.
*/
UInt64 MTDImageFileType::restoreData(      Image  *pImage, 
                                     const UChar8 *buffer,
                                           Int32         )
{
    pImage->setData(buffer);

    return pImage->getSize();
}

//-------------------------------------------------------------------------
/*! Tries to store the image data to the given memblock.
    Returns the amount of data written.
 */

UInt64 MTDImageFileType::storeData(const Image  *pImage, 
                                         UChar8 *buffer,
                                         Int32         )
{
    unsigned dataSize = pImage->getSize();
    const UChar8 *src = pImage->getData();

    if(dataSize && src && buffer)
        memcpy(buffer, src, dataSize);
    
    return dataSize;
} 


//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

MTDImageFileType::MTDImageFileType(const Char8  *mimeType,
                                   const Char8  *suffixArray[], 
                                         UInt16  suffixByteCount,
                                         UInt32  flags          ) :

    Inherited(mimeType, suffixArray, suffixByteCount, flags)
{
}

//-------------------------------------------------------------------------
/*! Destructor
 */

MTDImageFileType::~MTDImageFileType(void)
{
}

OSG_END_NAMESPACE

