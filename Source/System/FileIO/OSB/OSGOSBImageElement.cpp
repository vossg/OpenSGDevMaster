/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#include "OSGOSBImageElement.h"

#include "OSGOSBRootElement.h"
#include "OSGImage.h"
#include "OSGImageFileHandler.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBImageElement                                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBImageElement>
    OSBImageElement::_regHelper =
        OSBElementRegistrationHelper<OSBImageElement>("Image");

const UInt8 OSBImageElement::FlagPixelDataCompressedMask;
const UInt8 OSBImageElement::FlagPixelDataCompressed;
const UInt8 OSBImageElement::FlagPixelDataOutOfLineMask;
const UInt8 OSBImageElement::FlagPixelDataOutOfLine;

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBImageElement::OSBImageElement(OSBRootElement *root)
    : Inherited      (root, OSGOSBHeaderVersion200),
      _hasJPEGSupport(false                        ),
      _version       (OSGOSBHeaderVersion200      )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBImageElement::~OSBImageElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBImageElement::read(const std::string &typeName)
{
    FDEBUG(("OSBImageElement::read [%s]\n", typeName.c_str()));

    const OSBRootElement *root      = getRoot();
    BinaryReadHandler     *rh        = editRoot()->getReadHandler();
    UInt8                  fcPtrType;

    if(root->getHeaderVersion() >= OSGOSBHeaderVersion200)
    {
        if(root->getHeaderVersion() > OSGOSBHeaderVersion200)
        {
            FINFO(("OSBImageElement::read: "
                   "Unknown version, trying to process as latest.\n"));
        }

        rh->getValue(fcPtrType);
    }

    ImageUnrecPtr img = Image::create();
    setContainer(img);

    rh->getValue(_version);

    if(_version >= OSGOSBHeaderVersion200)
    {
        UInt8 flags;
        rh->getValue(flags);

        if(flags & FlagPixelDataCompressedMask)
        {
            std::string endMarker = "'pixel'";
            std::string fieldName = readFields("", endMarker);

            if(fieldName == "pixel")
            {
                readCompressedPixelData();
            }
        }
        else if(flags & FlagPixelDataOutOfLineMask)
        {
            readFields("", "");

            // read out-of-line image data
            const std::string &fileName = img->getName();
            img = ImageFileHandler::the()->read(fileName.c_str());
            setContainer(img);
        }
    }
    else if(_version >= OSGOSBHeaderVersion100)
    {
        std::string endMarker = "'cpixel'";
        std::string fieldName = readFields("", endMarker);

        // read compressed pixel data - should be the last field
        if(fieldName == "cpixel")
        {
            readCompressedPixelData();
        }

        // read any remaining fields - should be none, but this is safe to do.
        readFieldsContinue(fieldName, "", "");

        // read out-of-line image data
        if(img->getMFPixel()->empty())
        {
            const std::string &fileName = img->getName();
            img = ImageFileHandler::the()->read(fileName.c_str());
            setContainer(img);
        }
    }
}

void
OSBImageElement::postRead(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBImageElement::preWrite(FieldContainer * const fc)
{
    FDEBUG(("OSBImageElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBImageElement::write(void)
{
    FDEBUG(("OSBImageElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBImageElement::write: Attempt to write NULL.\n"));
        return;
    }

    Image                *img   = dynamic_cast<Image *>(getContainer());
    BinaryWriteHandler   *wh    = editRoot()->getWriteHandler();
    const OSBRootElement *root  = getRoot();
    UInt8                 flags = 0;

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    std::string excludeFields    = "";
    bool        compressTextures = false;

    if(getRoot()->getOptions().inlineTextures() == false)
    {
        // only write "name" field
        flags |= FlagPixelDataOutOfLine;
        excludeFields.append("'dimension' 'width' 'height' 'depth' 'bpp' "
                             "'mipMapCount' 'frameCount' 'frameDelay' "
                             "'pixelFormat' 'pixel' 'frameSize' "         );
    }
    else
    {
        if(_hasJPEGSupport && root->getOptions().compressTextures() &&
           (img->getDataType() == Image::OSG_UINT8_IMAGEDATA)       &&
           ((img->getBpp() == 1) || (img->getBpp() == 3))             )
        {
            compressTextures =  true;
            flags            |= FlagPixelDataCompressed;
            excludeFields.append("'pixel'");
        }
    }

    // write flags
    wh->putValue(flags);

    // write all fields that do not require special handling
    writeFields(excludeFields, false);

    if(compressTextures)
        writeCompressedPixelData();

    writeEndMarker();
}

/*-------------------------------------------------------------------------*/
/* Reading Helper Functions                                                */

void
OSBImageElement::readCompressedPixelData(void)
{
    BinaryReadHandler *rh  = editRoot()->getReadHandler();
    Image             *img = dynamic_cast<Image *>(getContainer());

    std::string        fieldTypeName;
    UInt32             fieldSize;
    UInt32             byteSize;
    std::vector<UInt8> buffer;

    rh->getValue(fieldTypeName);
    rh->getValue(fieldSize    );

    if(!_hasJPEGSupport)
    {
        FWARNING(("OSBImageElement::readCompressedPixelData: "
                  "JPEG Support not available, skipping compressed "
                  "texture data.\n"));
        rh->skip(fieldSize);
        return;
    }

    rh->getValue(byteSize);

    // allocate and fill buffer
    buffer.resize(byteSize);
    rh->getValues(&buffer.front(), byteSize);

    img->restore(&buffer.front(), byteSize);
}

/*-------------------------------------------------------------------------*/
/* Writing Helper Functions                                                */

void
OSBImageElement::writeCompressedPixelData(void)
{
    // FIXME Inline Images are disabled right now. A more recent versin of
    //       the ImageFileHandler from CVS needs to be ported to OpenSG 2.

    const OSBRootElement *root = getRoot();
    BinaryWriteHandler   *wh   = editRoot()->getWriteHandler();

    Image       *img       = dynamic_cast<Image *>(getContainer());
    std::string imageType = root->getOptions().texturesImageType();
//     std::string imageType = "jpeg";

    std::vector<UInt8> buffer;
    UInt32             factor = 1;

    // JPEG always uses RGB, so single channel images need additional memory
    if((imageType == "jpeg") && (img->getBpp() == 1))
        factor = 3;

    // some extra space is needed for the image header
    UInt32 bufferSize =
       ImageFileHandler::the()->getDefaultType()->maxBufferSize(img) * factor +
           16384;

    buffer.resize(bufferSize);
    UInt64 compressedSize = img->store(imageType.c_str(), &buffer.front());
//     UInt64 compressedSize = 0;

    UInt32 byteSize  = static_cast<UInt32>(compressedSize);
    UInt32 fieldSize = sizeof(UInt32) + sizeof(UInt8) * byteSize;

    wh->putValue (fieldSize                );
    wh->putValue (byteSize                 );
    wh->putValues(&buffer.front(), byteSize);
}
