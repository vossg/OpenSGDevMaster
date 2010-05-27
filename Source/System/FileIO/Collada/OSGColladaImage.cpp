/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaImage.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGImageFileHandler.h"

#include <dom/domImage.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaImage::_regHelper(
    &ColladaImage::create, "image");

ColladaElementTransitPtr
ColladaImage::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaImage(elem, global));
}

void
ColladaImage::read(void)
{
    OSG_COLLADA_LOG(("ColladaImage::read\n"));

    domImageRef image = getDOMElementAs<domImage>();

    domImage::domInit_fromRef initFrom = image->getInit_from();

    if(initFrom != NULL)
    {
        daeURI      imageURI  = initFrom->getValue();
        std::string imagePath = cdom::uriToNativePath(imageURI.str());
        
        OSG_COLLADA_LOG(("ColladaImage::read: URI [%s] path [%s]\n",
                         imageURI.getURI(), imagePath.c_str()));

#ifdef WIN32
        if(imagePath.size() >  3   &&
           imagePath[0]     == '/' &&
           imagePath[2]     == ':'   )
        {
            _image =
                ImageFileHandler::the()->read(imagePath.substr(1).c_str());
        }
        else
        {
            _image = ImageFileHandler::the()->read(imagePath.c_str());
        }
#else
        _image = ImageFileHandler::the()->read(imagePath.c_str());
#endif

        if(_image == NULL)
        {
            SWARNING << "ColladaImage::read: Loading of image ["
                     << imagePath << "] failed." << std::endl;
        }
    }
    else
    {
        SWARNING << "ColladaImage::read: No <init_from> tag found."
                 << std::endl;
    }
}

Image *
ColladaImage::getImage(void) const
{
    return _image;
}

ColladaImage::ColladaImage(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
    , _image   (NULL)
{
}

ColladaImage::~ColladaImage(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
 
