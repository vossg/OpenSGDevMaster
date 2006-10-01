/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGLog.h>
#include <Image.h>


Image::Image(void)
{
    _image = OSG::NullFC;
}

Image::Image(const Image &copy)
{
    _image = copy._image;
}

Image::Image(OSG::ImagePtr image)
{
    _image = image;
}

Image::~Image()
{
}


void Image::write(std::string filename)
{
    _image->write(filename.c_str());
}
    
Image Image::clone(void)
{
    Image clone;
    
    clone._image = OSG::Image::create();
    // beginEditCP(clone._image);
    clone._image->set(_image);
    // endEditCP(clone._image);
    
    return clone;
}

    
void Image::diff(Image img)
{
    if( _image->getWidth() != img._image->getWidth() ||
        _image->getHeight() != img._image->getHeight() ||
        _image->getPixelFormat() != img._image->getPixelFormat())
    {
        FWARNING(("Image::diff: incompatible images!"));
        return;
    }
    
    // beginEditCP(_image);

    const OSG::UInt8 *sdata = img._image->getData();
          OSG::UInt8 *ddata = _image->editData();
  
    OSG::UInt32 nb = _image->getSize(false,false,false);
    
    for(OSG::UInt32 i = 0; i < nb; ++i, ++sdata, ++ddata)
    {
        *ddata = OSG::osgabs(*ddata - *sdata);
    }
    
    // endEditCP(_image);
}

