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

// System declarations
#include "OSGConfig.h"
#include <iostream>

// Application declarations
// to get ntons/ntohs

// Class declarations
#include "OSGImageFileType.h"
#include "OSGImageFileHandler.h"
#include "OSGImageGenericAtt.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

ImageBlockAccessor::~ImageBlockAccessor(void)
{
    _pGeoRef = NULL;
}

ImageBlockAccessor::ImageBlockAccessor(void) :
    _pGeoRef     (NULL                            ),
    _vSize       (0, 0                            ),
    _eImgType    (Image::OSG_INVALID_IMAGEDATATYPE),
    _eImgFormat  (Image::OSG_INVALID_PF           ),
    _fNoDataValue(0                               )
{
}

Vec2i ImageBlockAccessor::getSize(void)
{
    return _vSize;
}

Image::Type ImageBlockAccessor::getType(void)
{
    return _eImgType;
}

Image::PixelFormat ImageBlockAccessor::getFormat(void)
{
    return _eImgFormat;
}

GeoReferenceAttachment *ImageBlockAccessor::getGeoRef(void)
{
    return _pGeoRef;
}

Real64 ImageBlockAccessor::getNoDataValue(void)
{
    return _fNoDataValue;
}



BlockAccessWrapper::~BlockAccessWrapper(void)
{
    _pImage = NULL;
}


bool BlockAccessWrapper::isOpen(void)
{
    return (_pImage != NULL);
}

bool BlockAccessWrapper::readBlockA16(Vec2i   vSampleOrigin,
                                      Int32   iTextureSize,
                                      UInt16 *pTarget,
                                      Int32   iTargetSizeBytes)
{
    if(_pImage == NULL)
        return false;

    const UInt8 *pData = _pImage->getData();

    UInt8 *pDst = reinterpret_cast<UInt8 *>(pTarget);

    UInt32 destIdx = 0;

    Int32 xMin = vSampleOrigin.x();
    Int32 xMax = vSampleOrigin.x() + iTextureSize;

    Int32 yMin = vSampleOrigin.y();
    Int32 yMax = vSampleOrigin.y() + iTextureSize;

    for(Int32 y = yMin; y < yMax; y++)
    {
        for(Int32 x = xMin; x < xMax; x++)
        {
            for(Int32 i = 0; i < 2; i++)
            {
                if(y >= _pImage->getHeight() ||
                   x >= _pImage->getWidth()   )
                {
                    pDst[destIdx] = 0;
                }
                else
                {
                    pDst[destIdx] = 
                        pData[((y) * _pImage->getWidth() + x) * 2 + i];
                }

                destIdx++;
            }
        }
        
        destIdx += (iTextureSize - (xMax - xMin)) * 2;
    }

    return true;
}

bool BlockAccessWrapper::readBlockA16(Vec2i   vSampleOrigin,
                                      Int32   iTextureSize,
                                      Int16  *pTarget,
                                      Int32   iTargetSizeBytes)
{
    if(_pImage == NULL)
        return false;

#if 0
    const UInt8 *pData = _pImage->getData();

    UInt8 *pDst = (UInt8 *) pTarget;

    UInt32 destIdx = 0;

    Int32 xMin = vSampleOrigin.x();
    Int32 xMax = vSampleOrigin.x() + iTextureSize;

    Int32 yMin = vSampleOrigin.y();
    Int32 yMax = vSampleOrigin.y() + iTextureSize;

    for(UInt32 y = yMin; y < yMax; y++)
    {
        for(UInt32 x = xMin; x < xMax; x++)
        {
            for(UInt32 i = 0; i < 2; i++)
            {
                if(y >= _pImage->getHeight() ||
                   x >= _pImage->getWidth()   )
                {
                    pDst[destIdx] = 0;
                }
                else
                {
                    pDst[destIdx] = 
                        pData[((y) * _pImage->getWidth() + x) * 2 + i];
                }

                destIdx++;
            }
        }
        
        destIdx += (iTextureSize - (xMax - xMin)) * 2;
    }
#else
    const Int16 *pData = reinterpret_cast<const Int16 *>(_pImage->getData());

    UInt32 destIdx = 0;

    Int32 xMin = vSampleOrigin.x();
    Int32 xMax = vSampleOrigin.x() + iTextureSize;

    Int32 yMin = vSampleOrigin.y();
    Int32 yMax = vSampleOrigin.y() + iTextureSize;

    for(Int32 y = yMin; y < yMax; y++)
    {
        for(Int32 x = xMin; x < xMax; x++)
        {
            if(y >= _pImage->getHeight() ||
               x >= _pImage->getWidth()   )
            {
                pTarget[destIdx] = 0;
            }
            else
            {
                pTarget[destIdx] = 
                    pData[((y) * _pImage->getWidth() + x)];
            }

            ++destIdx;
        }
    }
#endif

    return true;
}

BlockAccessWrapper::BlockAccessWrapper(void) :
     Inherited(    ),
    _pImage   (NULL)
{
}

void BlockAccessWrapper::open(const Char8 *szFilename)
{
    _pImage = ImageFileHandler::the()->read(szFilename);

    if(_pImage != NULL)
    {
        _pGeoRef = 
            dynamic_cast<GeoReferenceAttachment *>(
                _pImage->findAttachment(
                    GeoReferenceAttachment::getClassType().getGroupId()));

        _vSize.setValues(_pImage->getWidth(),
                         _pImage->getHeight());

        _eImgType   = Image::Type       (_pImage->getDataType   ());
        _eImgFormat = Image::PixelFormat(_pImage->getPixelFormat());

        fprintf(stderr, "FOOO\n");

        _pImage->dump();
    }
}


/*! \class ImageFileType
 */

//-------------------------------------------------------------------------
/*!
  Helper method to convert the Head block from net to host format
*/

bool ImageFileType::Head::netToHost(void)
{
    pixelFormat    = osgNetToHost<UInt16>(pixelFormat);
    width          = osgNetToHost<UInt16>(width);
    height         = osgNetToHost<UInt16>(height);
    depth          = osgNetToHost<UInt16>(depth);
    mipmapCount    = osgNetToHost<UInt16>(mipmapCount);
    frameCount     = osgNetToHost<UInt16>(frameCount);
    frameDelay     = osgNetToHost<UInt16>(frameDelay);
    sideCount      = osgNetToHost<UInt16>(sideCount);
    dataType       = osgNetToHost<UInt16>(dataType);
    _reserved3     = 0;
    _reserved4     = 0;
    attachmentSize = osgNetToHost<UInt16>(attachmentSize);

    return true;
}


//-------------------------------------------------------------------------
/*!
Helper method to convert the Head block from host to net format
*/

bool ImageFileType::Head::hostToNet(void)
{
    pixelFormat    = osgHostToNet<UInt16>(pixelFormat);
    width          = osgHostToNet<UInt16>(width);
    height         = osgHostToNet<UInt16>(height);
    depth          = osgHostToNet<UInt16>(depth);
    mipmapCount    = osgHostToNet<UInt16>(mipmapCount);
    frameCount     = osgHostToNet<UInt16>(frameCount);
    frameDelay     = osgHostToNet<UInt16>(frameDelay);
    sideCount      = osgHostToNet<UInt16>(sideCount);
    dataType       = osgHostToNet<UInt16>(dataType);
    _reserved3     = 0;
    _reserved4     = 0;
    attachmentSize = osgHostToNet<UInt16>(attachmentSize);

    return true;
}

//-------------------------------------------------------------------------
/*! Get method for the mime type
*/

const Char8 *ImageFileType::getMimeType(void) const
{
    return _mimeType.c_str();
}

//-------------------------------------------------------------------------

bool ImageFileType::read(Image *pImage, const Char8 *fileName)
{
    std::ifstream is(fileName, std::ios::binary);

    if (is.good() == false)
        return false;

    return read(pImage, is, std::string());
}

//-------------------------------------------------------------------------

bool ImageFileType::write(Image const * pImage, const Char8 *fileName)
{
    std::ofstream os(fileName, std::ios::binary);

    if (os.good() == false)
        return false;

    return write(pImage, os, std::string());
}

//-------------------------------------------------------------------------
/*! Get method for the suffix list container
*/

const std::list<std::string> &ImageFileType::getSuffixList(void) const
{
    return _suffixList; 
}

//-------------------------------------------------------------------------

bool ImageFileType::validateHeader(const Char8 *fileName, bool &implemented)
{
    implemented = false;

    return true;
}

ImageBlockAccessorPtr ImageFileType::open(const Char8 *szFilename)
{
    BlockAccessWrapperPtr returnValue(new BlockAccessWrapper);

    returnValue->open(szFilename);

    return returnValue;
}

//-------------------------------------------------------------------------
/*!
  Tries to fill the image object with the data read from
  the given input stream. Returns true on success.
*/

bool ImageFileType::read(      Image        *pImage, 
                               std::istream &is, 
                         const std::string  &mimetype)
{
    SWARNING << getMimeType()
             << " read from stream is not implemented"
             << endLog;
    return false;
}

//-------------------------------------------------------------------------
/*!
  Tries to write the image object to the given output stream.
  Returns true on success.
*/

bool ImageFileType::write(Image         const  *pImage, 
                          std::ostream         &os, 
                          std::string   const  &mimetype)
{
    SWARNING << getMimeType()
             << " write to stream is not implemented"
             << endLog;

    return false;
}

//-------------------------------------------------------------------------
/*!
  Tries to determine the mime type of the data provided by an input stream
  by searching for magic bytes. Returns the mime type or an empty string
  when the function could not determine the mime type.
 */

std::string ImageFileType::determineMimetypeFromStream(std::istream &is)
{
    return std::string();
}

//-------------------------------------------------------------------------
/*! Constructor which takes a suffix array and size to add the
    ImageFileType to the Singleton ImageFileHandler
*/

ImageFileType::ImageFileType(const char   *mimeType,
                             const Char8  *suffixArray[], 
                                   UInt16  suffixByteCount,
                                   UInt32  flags)

    : Inherited(flags)
{
    Int32 suffixCount = suffixByteCount / sizeof(const Char8 *);
    Int32 i           = 0;
    std::list<std::string>::iterator sI;

    if (!mimeType) 
    {
        FFATAL (("ImageFileType without valid mimeType\n"));
    }

    _mimeType.assign(mimeType);

    _suffixList.resize(suffixCount);

    for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
    {
        sI->assign(suffixArray[i++]);
        SINFO << "add image suffix: " << *sI << endLog;
    }
        
    ImageFileHandler::the()->addImageFileType(*this);
}

//-------------------------------------------------------------------------
/*! Destructor
*/

ImageFileType::~ImageFileType(void)
{
}

//-------------------------------------------------------------------------
/*! Abstract restore method. Should be overwriten by an concrete derived
    class. Tries to restore the image data from the given memblock.
*/

UInt64 ImageFileType::restoreData(      Image  * , 
                                  const UChar8 *OSG_CHECK_ARG(buffer ),
                                        Int32   OSG_CHECK_ARG(memSize))
{
    FWARNING(("ImageXFileType::restoreData() not impl. for mimeType %s\n",
              getMimeType()));

    return 0;
}

//-------------------------------------------------------------------------
/*! Abstract restore method. Should be overwriten by an concrete derived
    class. Tries to store the given image data to the given memblock
*/

UInt64 ImageFileType::storeData(Image  const * , 
                                UChar8       *OSG_CHECK_ARG(buffer ),
                                Int32         OSG_CHECK_ARG(memSize))
{
    FWARNING(("ImageXFileType::storeData() not impl. for mimeType %s\n",
              getMimeType()));
    
    return 0;
}

//-------------------------------------------------------------------------
/*! Tries to restore the Imagedata from the given memblock. The buffer must
    include a ImageFileType::Head data block.
*/

UInt64 ImageFileType::restore(      Image  *pImage, 
                              const UChar8 *buffer, 
                                    Int32   memSize)
{
    long            imageSize, headSize = sizeof(Head);
    unsigned long   size = 0, attachmentSize;
    Head            head;
    const UChar8   *data = buffer ? (buffer + headSize) : 0;
    ImageFileType  *type;
    std::string     mimeType;
    Image::Type     dataType;

    if((pImage != NULL) && (buffer != NULL) && (memSize >= headSize))
    {
        // Copy header. Otherwise netToHost would change the original
        // data structur.

        memcpy(&head,buffer,sizeof(Head));
        head.netToHost();
        mimeType = 
            ImageFileHandler::the()->determineMimetypeFromSuffix(head.suffix);

        if((type = ImageFileHandler::the()->getFileType(mimeType.c_str(), 0)))
        {
            if (head.dataType)
                dataType = Image::Type(head.dataType);
            else
                dataType = Image::OSG_UINT8_IMAGEDATA;
            
            pImage->set(Image::PixelFormat(head.pixelFormat), 
                       head.width,
                       head.height, 
                       head.depth, 
                       head.mipmapCount,
                       head.frameCount, 
                       float(head.frameDelay) / 1000.0, 
                       0,
                       dataType,
                       true,
                       head.sideCount);

            imageSize = static_cast<unsigned long>(
                type->restoreData(pImage, data, memSize - headSize));

            attachmentSize = 0; // head->attachmentSize;

            /*
            if ((attachmentSize = head->attachmentSize))
            {
                attData = (char*)(buffer + headSize + imageSize);
                attKey = attData;
                attValue = 0;
                for (i = 0; i < (attachmentSize-1); i++) {
                    if (attData[i] == 0) 
                        if (attKey) {
                            attValue = &(attData[i+1]);
                            image->setAttachmentField (attKey,attValue);
                            attKey = attValue = 0;
                        }
                        else
                            attKey = &(attData[i+1]);
                }
                if (attKey || attValue) {
                    FFATAL (("Attachment restore error\n"));
                }
            }
            */

            size = headSize + imageSize + attachmentSize;
            
            FDEBUG (( "Restore image data: %lu (%lu/%lu/%lu)\n",
                      size, headSize, imageSize, attachmentSize ));

        }
        else
        {
            imageSize = 0;

            FWARNING(("Can not restore image data, invalid mimeType: %s\n",
                      mimeType.empty() == false ? 
                          mimeType.c_str() : "Unknown"));
        }
    }

    return size;
}

//-------------------------------------------------------------------------
/*! Tries to store the raster data to the given mem block.
    Will include a ImageFileType::Head description and the data encoded
    as 'mimeType'
*/

UInt64 ImageFileType::store(Image  const *pImage, 
                            Char8  const *mimeType,
                            UChar8       *buffer, 
                            Int32         memSize)
{
    ImageFileType *type = ImageFileHandler::the()->getFileType(mimeType);
    
    return type ? type->store(pImage, buffer, memSize) : 0;
}

//-------------------------------------------------------------------------
/*! Tries to store the raster data to the given mem block.
    Will include a ImageFileType::Head description for the derived
    concreate mimeType.
*/

UInt64 ImageFileType::store(Image  const *pImage,
                            UChar8       *buffer, 
                            Int32         memSize)
{
    Head            *head;
    unsigned long   dataSize = 0, headSize = sizeof(Head);
    unsigned long   attachmentSize;
    UChar8          *dest;
    const UChar8    *src = pImage->getData();
    std::map<std::string, std::string>::const_iterator aI;
    std::string     value;

    attachmentSize = 0;

    // get attachment size
    /*
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        const_cast<Image*>(image.getCPtr())->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NULL)
    {
        for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
        {
            FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
            Field *field=att->getField(i);
            if (fieldDesc && field) 
            {
                field->getValueByStr(value);
                attachmentSize += strlen( fieldDesc->getName().str() ) + 1;
                attachmentSize += value.length() + 1;
              
                std::cout << fieldDesc->getName().str() << std::endl; 
                std::cout << value << std::endl; 
            }
            else 
            {
                FFATAL (("Invalid Attachment in ImageFileType::store()\n"));
            }
        }
    }
    */

    if (buffer) 
    {
        head = reinterpret_cast<Head *>(buffer);

        head->pixelFormat    = pImage->getPixelFormat();
        head->width          = pImage->getWidth();
        head->height         = pImage->getHeight();
        head->depth          = pImage->getDepth();
        head->mipmapCount    = pImage->getMipMapCount();
        head->frameCount     = pImage->getFrameCount();
        head->frameDelay     = short(pImage->getFrameDelay() * 1000.0);
        head->sideCount      = pImage->getSideCount();
        head->dataType       = pImage->getDataType();
        head->attachmentSize = static_cast<unsigned short>(attachmentSize);
        head->hostToNet();
      
        strcpy(head->suffix, _suffixList.front().c_str());
      
        dest = static_cast<UChar8 *>(buffer + headSize);

        if(src) 
        {
            dataSize = static_cast<unsigned long>(
                storeData(pImage, dest, memSize - headSize));
        }

        dest = static_cast<UChar8 *>(buffer + headSize + dataSize);

        /*
        if(att != NULL)
        {
            for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
            {
                FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
                Field *field=att->getField(i);
                if (field && fieldDesc) 
                {
                    field->getValueByStr(value);

                    l = strlen( fieldDesc->getName().str() );
                    for (i = 0; i < l; i++)
                      *dest++ = fieldDesc->getName().str()[i];
                    *dest++ = 0;
                    l = value.length();
                    for (i = 0; i < l; i++)
                      *dest++ = value[i];
                    *dest++ = 0;
                }
                else
                {
                    FFATAL (("Invalid Attachment in ImageFileType::store()\n"));
                }
            }
        }
        */

        FDEBUG (( "Store image data: %lu (%lu/%lu/%lu)\n",
                  headSize + dataSize + attachmentSize, headSize, dataSize, 
                  attachmentSize ));
    }
    else 
    {
        FFATAL (("Invalid buffer in ImageFileType::store()\n"));
    }
  
    return (headSize + dataSize + attachmentSize);
}

//-------------------------------------------------------------------------
/*! Returns the max buffer size needed to store the Image (Head + mimeType
    specific data block)
*/

UInt64 ImageFileType::maxBufferSize(Image const * pImage)
{
    std::string value;
    unsigned long size, attachmentSize;
    unsigned long imageSize = pImage->getSize(), headSize = sizeof(Head);

    std::map<std::string, std::string>::const_iterator aI;

    attachmentSize = 0;

    // get attachment size
		/*
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        const_cast<Image*>(image.getCPtr())->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NULL)
    {
        for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
        {
            FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
            Field *field=att->getField(i);
            if (field && fieldDesc) 
            {
                field->getValueByStr(value);
                attachmentSize += strlen( fieldDesc->getName().str() ) + 1;
                attachmentSize += value.length() + 1;
            }
            else 
            {
                FFATAL (("Invalid Attachment in ImageFileType::maxBufferSize()\n"));
            }
        }
    }
		*/

    size = headSize + imageSize + attachmentSize;
  
    FINFO (( "ImageFileType::maxBufferSize(): %lu (%lu/%lu/%lu)\n", 
             size, headSize, imageSize, attachmentSize ));
  
    return size;
}

//-------------------------------------------------------------------------
/*! The dump method just writes some object debugging info to the LOG stream
*/

void ImageFileType::dump(void)
{
    std::list<std::string>::iterator    sI;

    SLOG << getMimeType();

    if(_suffixList.empty())
    {
        SLOG << ": Suffix: ";

        for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
        {
            Log().stream(OSG::LOG_DEBUG) << sI->c_str() << " ";
        }
    }

    std::cerr << std::endl;
}

OSG_END_NAMESPACE

