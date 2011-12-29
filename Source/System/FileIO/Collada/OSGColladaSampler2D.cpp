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
    &ColladaSampler2D::create, 
     "sampler2D"             );


ColladaElementTransitPtr ColladaSampler2D::create(daeElement    *elem, 
                                                  ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaSampler2D(elem, global));
}

void ColladaSampler2D::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("OSGColladaSampler2D::read\n"));

#if 0
   
    _texObj = TextureObjChunk::create();
    _texObj->setImage(colSurface->getImage());

    getGlobal()->getStatCollector()->getElem(
        ColladaGlobal::statNTextureCreated)->inc();

#endif
}

ColladaSurface *ColladaSampler2D::getSurface(void) const
{
    domFx_sampler2D_commonRef            sampler2D =
        this->getDOMElementAs<domFx_sampler2D_common>();

    domFx_sampler2D_common::domSourceRef source    = sampler2D->getSource();

    if(_colEffect == NULL)
    {
        SWARNING << "ColladaSampler2D::read: No effect set, can not resolve "
                 << "<source> elements." << std::endl;
        return NULL;
    }

    ColladaElement *colElem    = _colEffect->findParam(source->getValue());
    ColladaSurface *colSurface = dynamic_cast<ColladaSurface *>(colElem);

    if(colElem == NULL || colSurface == NULL)
    {
        SWARNING << "ColladaSampler2D::read: Could not resolve <source> ["
                 << source->getValue() << "]." << std::endl;

        return NULL;
    }

    return colSurface;
}

void ColladaSampler2D::setupTexObj(TextureObjChunk *pTex)
{
    if(pTex == NULL)
        return;

    domFx_sampler2D_commonRef            sampler2D =
        this->getDOMElementAs<domFx_sampler2D_common>();

    if(sampler2D->getWrap_s() != NULL)
    {
        switch(sampler2D->getWrap_s()->getValue())
        {
            case FX_SAMPLER_WRAP_COMMON_NONE:
                pTex->setWrapS(GL_CLAMP_TO_BORDER);
                break;

            case FX_SAMPLER_WRAP_COMMON_WRAP:
                pTex->setWrapS(GL_REPEAT);
                break;

            case FX_SAMPLER_WRAP_COMMON_MIRROR:
                pTex->setWrapS(GL_MIRRORED_REPEAT);
                break;

            case FX_SAMPLER_WRAP_COMMON_CLAMP:
                pTex->setWrapS(GL_CLAMP_TO_EDGE);
                break;

            case FX_SAMPLER_WRAP_COMMON_BORDER:
                pTex->setWrapS(GL_CLAMP_TO_BORDER);
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
                pTex->setWrapT(GL_CLAMP_TO_BORDER);
                break;
                
            case FX_SAMPLER_WRAP_COMMON_WRAP:
                pTex->setWrapT(GL_REPEAT);
                break;

            case FX_SAMPLER_WRAP_COMMON_MIRROR:
                pTex->setWrapT(GL_MIRRORED_REPEAT);
                break;

            case FX_SAMPLER_WRAP_COMMON_CLAMP:
                pTex->setWrapT(GL_CLAMP_TO_EDGE);
                break;

            case FX_SAMPLER_WRAP_COMMON_BORDER:
                pTex->setWrapT(GL_CLAMP_TO_BORDER);
                break;            

            case FX_SAMPLER_WRAP_COMMON_COUNT:
                SWARNING << "OSGColladaSampler2D::read <wrap_t> "
                         << "FX_SAMPLER_WRAP_COMMON_COUNT not handled" 
                         << std::endl;
                break;
        }
    }
}

ColladaEffect *ColladaSampler2D::getEffect(void) const
{
    return _colEffect;
}

void ColladaSampler2D::setEffect(ColladaEffect *colEffect)
{
    _colEffect = colEffect;
}


ColladaSampler2D::ColladaSampler2D(daeElement *elem, ColladaGlobal *global) :
     Inherited(elem, 
               global),
    _colEffect(NULL  )
{
}

ColladaSampler2D::~ColladaSampler2D(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
