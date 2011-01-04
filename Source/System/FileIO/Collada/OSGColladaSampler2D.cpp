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

#include "OSGColladaSampler2D.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaEffect.h"
#include "OSGColladaSurface.h"

#include <dom/domFx_sampler2D_common.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaSampler2D::_regHelper(
    &ColladaSampler2D::create, "sampler2D");


ColladaElementTransitPtr
ColladaSampler2D::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaSampler2D(elem, global));
}

void
ColladaSampler2D::read(void)
{
    OSG_COLLADA_LOG(("OSGColladaSampler2D::read\n"));

    domFx_sampler2D_commonRef            sampler2D =
        getDOMElementAs<domFx_sampler2D_common>();
    domFx_sampler2D_common::domSourceRef source    = sampler2D->getSource();

    if(_colEffect == NULL)
    {
        SWARNING << "ColladaSampler2D::read: No effect set, can not resolve "
                 << "<source> elements." << std::endl;
        return;
    }

    ColladaElement *colElem    = _colEffect->findParam(source->getValue());
    ColladaSurface *colSurface = dynamic_cast<ColladaSurface *>(colElem);

    if(colElem == NULL || colSurface == NULL)
    {
        SWARNING << "ColladaSampler2D::read: Could not resolve <source> ["
                 << source->getValue() << "]." << std::endl;
    }
    
    _texObj = TextureObjChunk::create();
    _texObj->setImage(colSurface->getImage());

    getGlobal()->getStatCollector()->getElem(
        ColladaGlobal::statNTextureCreated)->inc();

    if(sampler2D->getWrap_s() != NULL)
    {
        switch(sampler2D->getWrap_s()->getValue())
        {
        case FX_SAMPLER_WRAP_COMMON_NONE:
            SWARNING << "ColladaSampler2D::read: <wrap_s> == NONE "
                     << "not supported" << std::endl;
            break;

        case FX_SAMPLER_WRAP_COMMON_WRAP:
            _texObj->setWrapS(GL_REPEAT);
            break;

        case FX_SAMPLER_WRAP_COMMON_MIRROR:
            _texObj->setWrapS(GL_MIRRORED_REPEAT);
            break;

        case FX_SAMPLER_WRAP_COMMON_CLAMP:
            _texObj->setWrapS(GL_CLAMP_TO_EDGE);
            break;

        case FX_SAMPLER_WRAP_COMMON_BORDER:
            _texObj->setWrapS(GL_CLAMP_TO_BORDER);
            break;
        case FX_SAMPLER_WRAP_COMMON_COUNT:
            SWARNING << "OSGColladaSampler2D::read <wrap_s> "
                     << "FX_SAMPLER_WRAP_COMMON_COUNT not handled" 
                     << std::endl;
            break;
        }
    }

    if(sampler2D->getWrap_t() != NULL)
    {
        switch(sampler2D->getWrap_t()->getValue())
        {
        case FX_SAMPLER_WRAP_COMMON_NONE:
            SWARNING << "ColladaSampler2D::read: <wrap_t> == NONE "
                     << "not supported" << std::endl;
            break;

        case FX_SAMPLER_WRAP_COMMON_WRAP:
            _texObj->setWrapT(GL_REPEAT);
            break;

        case FX_SAMPLER_WRAP_COMMON_MIRROR:
            _texObj->setWrapT(GL_MIRRORED_REPEAT);
            break;

        case FX_SAMPLER_WRAP_COMMON_CLAMP:
            _texObj->setWrapT(GL_CLAMP_TO_EDGE);
            break;

        case FX_SAMPLER_WRAP_COMMON_BORDER:
            _texObj->setWrapT(GL_CLAMP_TO_BORDER);
            break;            
        case FX_SAMPLER_WRAP_COMMON_COUNT:
            SWARNING << "OSGColladaSampler2D::read <wrap_t> "
                     << "FX_SAMPLER_WRAP_COMMON_COUNT not handled" 
                     << std::endl;
            break;
        }
    }
}

ColladaEffect *
ColladaSampler2D::getEffect(void) const
{
    return _colEffect;
}

void
ColladaSampler2D::setEffect(ColladaEffect *colEffect)
{
    _colEffect = colEffect;
}

TextureObjChunk *
ColladaSampler2D::getTexture(void) const
{
    return _texObj;
}

bool
ColladaSampler2D::hasAlpha(void) const
{
    bool retVal = false;

    if(_texObj != NULL && _texObj->getImage() != NULL)
        retVal = _texObj->getImage()->hasAlphaChannel();

    return retVal;
}

bool
ColladaSampler2D::hasBinaryAlpha(void) const
{
    bool retVal = false;

    if(_texObj != NULL && _texObj->getImage() != NULL)
    {
        retVal = _texObj->getImage()->isAlphaBinary    () ||
                 _texObj->getImage()->calcIsAlphaBinary();
    }

    return retVal;
}

ColladaSampler2D::ColladaSampler2D(daeElement *elem, ColladaGlobal *global)
    : Inherited (elem, global)
    , _colEffect(NULL)
    , _texObj   (NULL)
{
}

ColladaSampler2D::~ColladaSampler2D(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
