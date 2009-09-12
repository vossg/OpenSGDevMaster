/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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
//#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include <OSGColladaImage.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGImageFileHandler.h>

#include <dom/domImage.h>

OSG_BEGIN_NAMESPACE

void ColladaImage::read(void)
{
    OSG_COLLADA_LOG(("ColladaImage::read:\n"));

    domImageRef image = getDOMElementAs<domImage>();

    if(image != NULL)
    {
        const domImage::domInit_fromRef initFrom = image->getInit_from();
        
        if(initFrom != NULL)
        {
            xsAnyURI imageUri = initFrom->getValue();
            
            OSG_COLLADA_LOG(("ColladaImage::read: image uri [%s] [%s]\n",
                             imageUri.getURI(), imageUri.path().c_str()));
            
#ifdef WIN32
            if(imageUri.path().size()     > 3    && 
               imageUri.path().c_str()[0] == '/' && 
               imageUri.path().c_str()[2] == ':'  )
            {
                const Char8 *szFileName = imageUri.path().c_str();

                _image = ImageFileHandler::the()->read(++szFileName);
            }
            else
            {
                _image = 
                    ImageFileHandler::the()->read(imageUri.path().c_str());
            }
#else
            _image = ImageFileHandler::the()->read(imageUri.path().c_str());
#endif

            if(_image == NULL)
            {
                FWARNING(
                    ("ColladaImage::read: Loading of image [%s] failed.\n",
                     imageUri.path().c_str()));
            }
        }
    }
}

ColladaImage::ColladaImage(domImage *image, ColladaGlobal *global)
    : Inherited(image, global)
{
    // nothing to do
}

ColladaImage::~ColladaImage(void)
{
    // nothing to do
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
