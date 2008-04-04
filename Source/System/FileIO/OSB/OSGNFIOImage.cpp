/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <OSGConfig.h>
#include "OSGNFIOImage.h"
#include "OSGNFIOFactory.h"

#include <vector>

#include <OSGLog.h>
#include <OSGImageFileHandler.h>
//#include <OSGJPGImageFileType.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOImage
           reads and writes a image.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOImage NFIOImage::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOImage::NFIOImage(void) :
    NFIOBase("Image")
{
    _version = 200;
}

/*------------------------------ destructor -------------------------------*/

NFIOImage::~NFIOImage(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

FieldContainerPtr NFIOImage::readFC(const std::string &/*typeName*/)
{
    FDEBUG(("NFIOImage::readFC\n"));
    
    ImagePtr img = Image::create();
    
    UInt16 version;
    _in->getValue(version);
    
    std::string fieldName = readFCFields(img, "", "'cpixel'");
    
    // compressed pixel
    if(fieldName == "cpixel")
    {
        readCompressedPixel(img);
        _in->getValue(fieldName); // read end marker
    }
    
    if(img->getPixel().empty())
    {
        // read texture
        //beginEditCP(img);
            //img->read(img->getName().c_str());
            subRefX(img);
            img = ImageFileHandler::the()->read(img->getName().c_str());
        //endEditCP(img);
    }
    
    return img;
}

void NFIOImage::writeFC(const FieldContainerPtr &fc)
{
    FDEBUG(("NFIOImage::witeFC\n"));
    
    static bool jpeg = isJPEGSupported();
    
    ImagePtr img = dynamic_cast<ImagePtr>(fc);
    
    _out->putValue(_version);
    
    bool compressTextures = false;
    std::string exclude;
    if(!getOptions().inlineTextures())
    {
        // only write the name field.
        exclude = "'dimension' 'width' 'height' 'depth' 'bpp' 'mipMapCount' "
                  "'frameCount' 'frameDelay' 'pixelFormat' 'pixel' 'frameSize'";
    }
    else
    {
        // jpeg supports only 1 and 3 byte per pixel images :-(
        if(jpeg && getOptions().compressTextures() &&
           img->getDataType() == Image::OSG_UINT8_IMAGEDATA &&
           (img->getBpp() == 1 || img->getBpp() == 3))
        {
            compressTextures = true;
            exclude += " 'pixel'";
        }
    }
    
    writeFCFields(img, exclude, false);
    
    if(compressTextures)
        writeCompressedPixel(img);

    writeEndMarker();
}

void NFIOImage::readCompressedPixel(ImagePtr &img)
{
    static bool jpeg = isJPEGSupported();
    
    std::string fieldType;
    _in->getValue(fieldType);
    
    UInt32 size;
    UInt32 noe;
    
    _in->getValue(size);
    
    // skip data if jpeg is not supported.
    if(!jpeg)
    {
        FWARNING(("NFIOImage::readCompressedPixel : skipping compressed texture"
                  ", jpeg is not supported\n"));
        _in->skip(size);
        return;
    }
    
    _in->getValue(noe);
    
    std::vector<UInt8> buffer;
    buffer.reserve(noe);
    UInt8 p;
    for(UInt32 i=0;i<noe;++i)
    {
        _in->getValue(p);
        buffer.push_back(p);
    }
    
    //beginEditCP(img);
    // FIXME missing in Image.cpp
    //UInt64 msize = img->restore(&buffer[0], buffer.size());
    //endEditCP(img);
}

void NFIOImage::writeCompressedPixel(const ImagePtr &img)
{
    _out->putValue(std::string("cpixel"));
    _out->putValue(std::string("MFUInt8"));
    
    std::vector<UInt8> buffer;
    buffer.resize(img->getSize(false, false));
    // FIXME need to add a option inteface like in the SceneFileHandler.
    //JPGImageFileType::the().setQuality(getOptions().texturesCompressionQuality());
    // FIXME missing in Image.cpp
    //UInt64 msize = img->store("jpeg", &buffer[0]);
    UInt64 msize = 0;
    
    UInt32 noe = (UInt32) msize;
    UInt32 size = sizeof(UInt32) + sizeof(UInt8) * noe;

    _out->putValue(size);
    _out->putValue(noe);
    
    for(UInt32 i=0;i<noe;++i)
        _out->putValue(buffer[i]);
}

bool NFIOImage::isJPEGSupported(void)
{
    std::list<const Char8*> sl;
    if(ImageFileHandler::the()->getSuffixList(sl) > 0)
    {
        for(std::list<const Char8*>::iterator i=sl.begin();i!=sl.end();++i)
        {
            if(!strcmp(*i, "jpeg"))
                return true;
        }
    }
    return false;
}
