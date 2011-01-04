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
#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"
#include "OSGFileSystem.h"
#include "OSGZStream.h"

#include "OSGDATImageFileType.h"

// Static Class Varible implementations:

static const OSG::Char8 *suffixArray[] =
{
    "dat"
};


OSG_BEGIN_NAMESPACE

/*! \class DATImageFileType

  Image File Type to read/write and store/restore Image objects as
  PNM/RAW data.

  All the type specific code is included in the class. Does
  not depend on external libs.

 */



DATImageFileType DATImageFileType::_the("image/x-dat",
                                        suffixArray,
                                        sizeof(suffixArray) );

std::map<std::string,
         DATImageFileType::KeyType   > DATImageFileType::_keyStrMap;

std::map<std::string,
         DATImageFileType::FormatDesc> DATImageFileType::_formatStrMap;



//-------------------------------------------------------------------------

/*! Tries to fill the image object with the data read from
    the given fileName. Returns true on success.
 */

bool DATImageFileType::read(      Image *image,
                            const Char8 *fileName)
{
    bool retCode = false;

    std::ifstream inDat(fileName), inVolS;
    std::istream *inVol;
    std::string keyStr, objectFileName;
    const UInt32 lineBufferSize = 1024;
    Char8 *value, *keySepPos, lineBuffer[lineBufferSize];
    const Char8 keySep = ':';
    int fileOffset, keyL, valueL;
    std::map<std::string, KeyType>::iterator keyI;
    std::map<std::string, FormatDesc>::iterator formatI;
    KeyType key;
    Image::Type formatType;
    UInt32 channel = 1;
    UInt32 res[3];
    UInt32 dataSize = 0;
    Image::PixelFormat pixelFormat = Image::OSG_L_PF;
    char *dataBuffer = 0;
    bool needConversion = false;
    // default endian type is big endian
    bool big_endian = true;

    res[0] = res[1] = res[2] = 0;
    fileOffset = 0;
    formatType = Image::OSG_INVALID_IMAGEDATATYPE;
    dataSize = 0;
    dataBuffer = 0;

    initTypeMap();

    // read the data file
    for(lineBuffer[0] = 0;
        inDat.getline(lineBuffer, lineBufferSize);
        lineBuffer[0] = 0)
    {
        if((keySepPos = strchr(lineBuffer,keySep)))
        {
            keyL = keySepPos - lineBuffer;
            keyStr.assign( lineBuffer, keyL );
            keyI = _keyStrMap.find(keyStr);
            key = ((keyI == _keyStrMap.end()) ? UNKNOWN_KT : keyI->second);
            value = keySepPos + 1;

            while (value && isspace(*value))
                value++;

            valueL = strlen(value);

            while (isspace(value[valueL-1]))
                value[--valueL] = 0;

            switch (key)
            {
                case OBJECT_FILE_NAME_KT:
                    objectFileName = value;
                    image->setAttachmentField ( keyStr, value );
                    break;
                case CHANNEL_KT:
                    sscanf ( value, "%d", &(channel) );
                    image->setAttachmentField ( keyStr, value );
                    break;
                case RESOLUTION_KT:
                    sscanf ( value, "%d %d %d",
                             &(res[0]), &(res[1]), &(res[2]));
                    image->setAttachmentField ( keyStr, value );
                    break;
                case FORMAT_KT:
                    formatI = _formatStrMap.find(value);
                    if (formatI != _formatStrMap.end())
                    {
                        formatType = formatI->second.type;
                    }
                    else
                    {
                        formatType = Image::OSG_INVALID_IMAGEDATATYPE;
                    }
                    image->setAttachmentField ( keyStr, value );
                    break;
                case ENDIAN_KT:
                    if(!strcmp(value, "LITTLE"))
                        big_endian = false;
                    image->setAttachmentField ( keyStr, value );
                    break;
                case FILE_OFFSET_KT:
                    sscanf ( value, "%d", &fileOffset );
                    image->setAttachmentField ( keyStr, value );
                    break;
                case UNKNOWN_KT:
                    FNOTICE (( "Uknown DAT file key: >%s<\n",
                                 keyStr.c_str() ));
                    image->setAttachmentField ( keyStr, value );
                    break;
                case SLICE_THICKNESS_KT:
                default:
                    image->setAttachmentField ( keyStr, value );
                    break;
            }
        }
        else
        {
            FINFO (("Skip DAT line\n"));
        }
    }

    // set pixelformat
    switch (channel) 
    {
        case 4:
            pixelFormat = Image::OSG_RGBA_PF;
            break;
        case 3:
            pixelFormat = Image::OSG_RGB_PF;
            break;
        case 2:
            pixelFormat = Image::OSG_LA_PF;
            break;
        default:
            pixelFormat = Image::OSG_L_PF;
            break;
    }

    // check the setting and read the raw vol data
    if (objectFileName.empty() == false)
    {
        if((res[0] > 0) && (res[1] > 0) && (res[2] > 0))
        {
            if(formatType != Image::OSG_INVALID_IMAGEDATATYPE)
            {
                inVolS.open(objectFileName.c_str(),
                            std::ios::in | std::ios::binary);

                if (inVolS.fail() && ImageFileHandler::the()->getPathHandler())
                {
                    // Try to find the file in the search path
                    inVolS.clear(); // reset the error state

                    PathHandler *ph =
                        ImageFileHandler::the()->getPathHandler();

                    inVolS.open(ph->findFile(objectFileName.c_str()).c_str(),
                                std::ios::in | std::ios::binary );
                }

                if(inVolS.fail())
                {
                    // Maybe compressed and name not changed?
                    std::string gzname = objectFileName + ".gz";

                    inVolS.clear(); // reset the error state

                    inVolS.open(gzname.c_str(),
                                std::ios::in | std::ios::binary );

                    if(inVolS.fail() &&
                       ImageFileHandler::the()->getPathHandler())
                    {
                        // Try to find the file in the search path
                        inVolS.clear(); // reset the error state

                        PathHandler *ph =
                            ImageFileHandler::the()->getPathHandler();

                        inVolS.open(ph->findFile(gzname.c_str()).c_str(),
                                    std::ios::in | std::ios::binary );
                    }
                }

                if(inVolS.good())
                {
#ifdef OSG_WITH_ZLIB
                    zip_istream *unzipper = NULL;
#endif

                    image->set(pixelFormat,
                               res[0], res[1], res[2],
                               1, 1, 0.0, 0,
                               formatType);

                    image->clear();

                    dataSize = image->getSize();

                    UInt32 fileDataSize = dataSize;

                    if(isGZip(inVolS))
                    {
#ifdef OSG_WITH_ZLIB
                        unzipper = new zip_istream(inVolS);
                        inVol = unzipper;
#else
                        SFATAL << "Compressed streams are not supported! "
                               << "Configure with --enable-png "
                               << "--with-png=DIR options." << std::endl;
#endif
                    }
                    else
                    {
                        inVol = &inVolS;

                        // get length of the stream.
                        inVol->seekg(0, std::ios::end);
                        UInt64 length = inVol->tellg();
                        inVol->seekg(0, std::ios::beg);

                        if(length < dataSize - fileOffset)
                        {
                            // correct dataSize.
                            fileDataSize = length;
                            FWARNING (( "RAW file length to small!\n" ));
                        }
                        else if(length > dataSize - fileOffset)
                        {
                            FWARNING (( "RAW file length to big!\n" ));
                        }
                    }

                    if(needConversion)
                    {
                        dataBuffer = new char [ dataSize ];
                    }
                    else
                    {
                        dataBuffer = 
                            reinterpret_cast<char *>(image->editData());
                    }

                    if(fileOffset != 0)
                        inVol->ignore (fileOffset);

                    inVol->read ( dataBuffer, fileDataSize );

#ifdef OSG_WITH_ZLIB
                    if(unzipper != NULL)
                        delete unzipper;
#endif
                }
                else
                {
                    FWARNING (( "Can not open %s image data\n",
                                objectFileName.c_str() ));
                }
            }
            else
            {
                FWARNING (( "Invalid/Missing DAT Format\n" ));
            }
        }
        else
        {
            FWARNING (( "Invalid/Missing DAT Resolution\n" ));
        }
    }
    else
    {
        FWARNING (( "Invalid/Missing DAT ObjectFileName\n" ));
    }

    // check/reformat vol data
    if (dataSize && dataBuffer)
    {
        // check host endian type
        UInt16 word = 0x0001;
        UInt8 *byte = reinterpret_cast<UInt8 *>(&word);
        bool host_big_endian = byte[0] ? false : true;

        if(big_endian != host_big_endian)
            image->swapDataEndian();

        if (needConversion)
        {
            FLOG (("DAT-Data convert not impl. yet !\n"));
            {
                switch (formatType)
                {
                    case Image::OSG_UINT8_IMAGEDATA:
                        break;
                    case Image::OSG_UINT16_IMAGEDATA:
                        break;
                    case Image::OSG_UINT32_IMAGEDATA:
                        break;
                    case Image::OSG_FLOAT32_IMAGEDATA:
                        break;
                    default:
                        ;
                }
            }
        }
        else
        {
            retCode = true;
        }
    }


    /* TODO
       std::ifstream in(fileName);
       Head head;
       void *headData = (void*)(&head);
       unsigned dataSize, headSize = sizeof(Head);

       if ( in &&
       in.read(static_cast<char *>(headData),
       headSize) && head.netToHost() &&
       image.set ( Image::PixelFormat(head.pixelFormat),
       head.width, head.height, head.depth, head.mipmapCount,
       head.frameCount, float(head.frameDelay) / 1000.0) &&
       (dataSize = image.getSize()) &&
       in.read((char *)(image.getData()), dataSize ))
       retCode = true;
       else
       retCode = false;
    */

    return retCode;
}

//-------------------------------------------------------------------------
/*! Tries to write the image object to the given fileName.
    Returns true on success.
*/
bool DATImageFileType::write(const Image *image,
                             const Char8 *fileName)
{
    initTypeMap();

    // ok we write always in big endian.
#if BYTE_ORDER == LITTLE_ENDIAN
    Image *pSwapImage = const_cast<Image *>(&(*image));

    pSwapImage->swapDataEndian();
#endif

    std::ofstream dat(fileName, std::ios::binary);

    if(!dat)
    {
        SWARNING << "DATImageFileType::write : Can not open output stream "
                 << "for file '"
                 << fileName
                 << "'!"
                 << std::endl;

        return false;
    }

    Real64 sT[3];
    sT[0] = sT[1] = sT[2] = 1.0;

    const std::string *attr = image->findAttachmentField("SliceThickness");

    if(attr != NULL)
        sscanf(attr->c_str(), "%lf %lf %lf", &sT[0], &sT[1], &sT[2]);

    std::string format = "UCHAR";

    for(std::map<std::string, FormatDesc>::iterator it = _formatStrMap.begin();
        it != _formatStrMap.end();
        ++it)
    {
        if((*it).second.type == image->getDataType())
        {
            format = (*it).first;
            break;
        }
    }

    std::string basename = fileName;
    std::string::size_type i = basename.rfind(".");

    if(i != std::string::npos)
        basename = basename.substr(0, i);

    basename += ".raw";

    std::string name = basename;

    i = name.rfind("/");

    // on windows also a / is possible!
#if defined(WIN32)
    if(i == std::string::npos)
        i = name.rfind("\\");
#endif

    if(i != std::string::npos)
        name = name.substr(i+1);

    dat << "ObjectFileName: " << name << "\n";
    dat << "TaggedFileName: ---\n";
    dat << "Resolution:     " << image->getWidth() << " " << image->getHeight()
        << " "                << image->getDepth() << "\n";
    dat << "SliceThickness: " << sT[0] << " " << sT[1] << " " << sT[2] << "\n";
    dat << "Format:         " << format << "\n";
    dat << "NbrTags:        0\n";
    dat << "ObjectType:     TEXTURE_VOLUME_OBJECT\n";
    dat << "ObjectModel:    DENSITY\n";
    dat << "GridType:       EQUIDISTANT\n";

    if(image->getBpp() > 1)
      dat << "Channel: " << image->getBpp() << "\n";

    dat.close();

    std::ofstream raw(basename.c_str(), std::ios::binary);

    if(!raw)
    {
        SWARNING << "DATImageFileType::write : Can not open output stream "
                 << "for file '"
                 << basename
                 << "'!"
                 << std::endl;

        return false;
    }

    raw.write (reinterpret_cast<const char *>(image->getData()), 
               image->getSize());
    raw.close();

    // restore to original endian
#if BYTE_ORDER == LITTLE_ENDIAN
    pSwapImage->swapDataEndian();
#endif

    /*
    ofstream out(fileName);
    Head head;
    const void *headData = (void*)(&head);
    unsigned dataSize = image.getSize(), headSize = sizeof(Head);

    head.pixelFormat  = image.getPixelFormat();
    head.width        = image.getWidth();
    head.height       = image.getHeight();
    head.depth        = image.getDepth();
    head.mipmapCount  = image.getMipMapCount();
    head.frameCount   = image.getFrameCount();
    head.frameDelay   = short(image.getFrameDelay() * 1000.0);
    head.hostToNet();

    if ( out && out.write(static_cast<const char *>(headData), headSize) &&
         dataSize &&
             out.write((char *)(image.getData()), dataSize) )
            retCode = true;
    else
        retCode = false;
    */

    return true;
}


//-------------------------------------------------------------------------
/*! Tries to restore the image data from the given memblock.
    Returns the amount of data read.
*/

UInt64 DATImageFileType::restoreData(      Image  *image,
                                     const UChar8 *buffer,
                                           Int32   OSG_CHECK_ARG(memSize))
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*! Tries to store the image data to the given memblock.
    Returns the amount of data written.
*/

UInt64 DATImageFileType::storeData(const Image  *image,
                                         UChar8 *buffer,
                                         Int32   OSG_CHECK_ARG(memSize))
{
          UInt32  dataSize = image->getSize();
    const UChar8 *src      = image->getData();

    if(dataSize && src && buffer)
        memcpy( buffer, src, dataSize);

    return dataSize;
}


//-------------------------------------------------------------------------
/*! Constructor used for the singleton object
 */

DATImageFileType::DATImageFileType(const Char8  *mimeType,
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

DATImageFileType::~DATImageFileType(void)
{
}

//-------------------------------------------------------------------------
/*! Helper to initialize the type map;
 */

void DATImageFileType::initTypeMap(void)
{
    FormatDesc *desc;

    if(_keyStrMap.empty())
    {
        _keyStrMap["ObjectFileName"]  = OBJECT_FILE_NAME_KT;
        _keyStrMap["Resolution"]      = RESOLUTION_KT;
        _keyStrMap["Channel"]         = CHANNEL_KT;
        _keyStrMap["SliceThickness"]  = SLICE_THICKNESS_KT;
        _keyStrMap["Format"]          = FORMAT_KT;
        _keyStrMap["Endian"]          = ENDIAN_KT;
        _keyStrMap["FileOffset"]      = FILE_OFFSET_KT;
    }

    if(_formatStrMap.empty())
    {
        desc = &(_formatStrMap["UCHAR"]);
        desc->type = Image::OSG_UINT8_IMAGEDATA;
        desc->bpv  = 1;
        desc->pixelFormat = Image::OSG_L_PF;
        desc->needConversion = false;

        desc = &(_formatStrMap["USHORT"]);
        desc->type = Image::OSG_UINT16_IMAGEDATA;
        desc->bpv  = 2;
        desc->pixelFormat = Image::OSG_L_PF;
        desc->needConversion = false;

        desc = &(_formatStrMap["UINT"]);
        desc->type = Image::OSG_UINT32_IMAGEDATA;
        desc->bpv  = 4; // TODO; is this right ?
        desc->pixelFormat = Image::OSG_L_PF;
        desc->needConversion = false;

        desc = &(_formatStrMap["ULONG"]);
        desc->type = Image::OSG_UINT32_IMAGEDATA;
        desc->bpv  = 4;
        desc->pixelFormat = Image::OSG_L_PF;
        desc->needConversion = false;

        desc = &(_formatStrMap["FLOAT"]);
        desc->type = Image::OSG_FLOAT32_IMAGEDATA;
        desc->bpv  = 4;
        desc->pixelFormat = Image::OSG_L_PF;
        desc->needConversion = false;

        desc = &(_formatStrMap["DOUBLE"]);
        // we have no OSG_FLOAT64_IMAGEDATA
        desc->type = Image::OSG_FLOAT32_IMAGEDATA;
        desc->bpv  = 8;
        desc->pixelFormat = Image::OSG_L_PF;
        desc->needConversion = false;
    }
}

OSG_END_NAMESPACE
