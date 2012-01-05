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

#include "OSGColladaTexture.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaEffect.h"
#include "OSGColladaSurface.h"
#include "OSGColladaImage.h"
#include "OSGColladaExtraHandler.h"
#include "OSGColladaHandlerFactory.h"

#include <dom/domFx_sampler2D_common.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaTexture::_regHelper(
    &ColladaTexture::create, 
     "texture");


ColladaElementTransitPtr ColladaTexture::create(daeElement    *elem, 
                                                ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaTexture(elem, global));
}

void ColladaTexture::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("OSGColladaTexture::read\n"));
    
    domCommon_color_or_texture_type::domTextureRef texture = 
        dynamic_cast< domCommon_color_or_texture_type::domTexture * >(
            this->getDOMElement());
    
    if(_colEffect == NULL)
    {
        SWARNING << "ColladaTexture::read: No effect set, can not resolve "
                 << "sampler." << std::endl;
        return;
    }

    xsNCName          texId      =  texture->getTexture();
    ColladaElement   *colElem    = _colEffect->findParam(texId);
    ColladaSampler2D *colSampler =  dynamic_cast<ColladaSampler2D *>(colElem);

    if(colSampler != NULL)
    {
        this->readSampler(colSampler);
    }
    else
    {
        this->readImage(texId);
    }


    const domExtraRef &extra = texture->getExtra();

    fprintf(stderr, "texutre got %p extra entries\n", 
            &*extra);
    
    if(extra == NULL || _extraHandlers.size() == 0)
        return;

    ExtraHandlerStoreIt      ehIt  = _extraHandlers.begin();
    ExtraHandlerStoreConstIt ehEnd = _extraHandlers.end  ();
    
    for(; ehIt != ehEnd; ++ehIt)
    {
        (*ehIt)->readTextureExtraElements(this, extra);
    }

    if(_texObj == NULL)
    {
        SWARNING << "ColladaTexture::read: can not resolve "
                 << "image source." << std::endl;
    }
}

ColladaEffect *ColladaTexture::getEffect(void) const
{
    return _colEffect;
}

void ColladaTexture::setEffect(ColladaEffect *colEffect)
{
    _colEffect = colEffect;
}

TextureObjChunk *ColladaTexture::getTexture(void) const
{
    return _texObj;
}

TextureEnvChunk *ColladaTexture::getTexEnv(void) const
{
    return _texEnv;
}

TextureEnvChunk *ColladaTexture::editTexEnv(void)
{
    if(_texEnv == NULL)
        _texEnv = TextureEnvChunk::create();

    return _texEnv;
}

TextureTransformChunk *ColladaTexture::getTexTransform (void) const
{
    return _texTransform;
}

TextureTransformChunk *ColladaTexture::editTexTransform(void)
{
    if(_texTransform == NULL)
        _texTransform = TextureTransformChunk::create();

    return _texTransform;
}

bool ColladaTexture::hasAlpha(void) const
{
    bool retVal = false;

    if(_texObj != NULL && _texObj->getImage() != NULL)
        retVal = _texObj->getImage()->hasAlphaChannel();

    return retVal;
}

bool ColladaTexture::hasBinaryAlpha(void) const
{
    bool retVal = false;

    if(_texObj != NULL && _texObj->getImage() != NULL)
    {
        retVal = _texObj->getImage()->isAlphaBinary    () ||
                 _texObj->getImage()->calcIsAlphaBinary();
    }

    return retVal;
}

ColladaTexture::ColladaTexture(daeElement    *elem, 
                               ColladaGlobal *global) : 
     Inherited    (elem, 
                   global),
    _colEffect    (NULL  ),
    _texObj       (NULL  ),
    _texEnv       (NULL  ),
    _texTransform (NULL  ),
    _extraHandlers(      )
{
    ColladaHandlerFactory::the()->createExtraHandlers(_extraHandlers);
}

ColladaTexture::~ColladaTexture(void)
{
    _extraHandlers.clear();
}

void ColladaTexture::readSampler(ColladaSampler2D *colSampler)
{
    ColladaSurface *colSurface = colSampler->getSurface();

    if(colSurface == NULL)
    {
        SWARNING << "ColladaTexture::read: Could not resolve surface"
                 << std::endl;

        return;
    }

    _texObj = TextureObjChunk::create();
    _texObj->setImage(colSurface->getImage());

    getGlobal()->getStatCollector()->getElem(
        ColladaGlobal::statNTextureCreated)->inc();

    colSampler->setupTexObj(_texObj);
}

void ColladaTexture::readImage(const Char8 *texId)
{
    domCOLLADA *pDoc = this->getGlobal()->getDocRoot();

    const domLibrary_images_Array &imagesLib = pDoc->getLibrary_images_array();

    for(UInt32 i = 0; i < imagesLib.getCount(); ++i)
    {
        domImage_Array &imgArray = imagesLib[i]->getImage_array();

        for(UInt32 j = 0; j < imgArray.getCount(); ++j)
        {
            domImageRef pImg = imgArray[j];

            if(osgStringCmp(pImg->getId(), texId) == 0)
            {
                ColladaImageRefPtr colImage  = 
                    getUserDataAs<ColladaImage>(pImg);

                if(colImage == NULL)
                {
                    colImage = dynamic_pointer_cast<ColladaImage>(
                        ColladaElementFactory::the()->create(pImg, 
                                                             getGlobal()));
                    
                    colImage->read(this);
                }

                _texObj = TextureObjChunk::create();
                _texObj->setImage(colImage->getImage());

                break;
            }
        }
    }
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
