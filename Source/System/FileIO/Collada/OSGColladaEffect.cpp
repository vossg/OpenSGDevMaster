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

#include "OSGColladaEffect.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaImage.h"
#include "OSGColladaInstanceEffect.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#include <dom/domEffect.h>
#include <dom/domInstance_effect.h>
#include <dom/domProfile_COMMON.h>
#include <dom/domProfile_GLSL.h>
#include <dom/domProfile_CG.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaEffect::_regHelper(
    &ColladaEffect::create, "effect");


ColladaElementTransitPtr
ColladaEffect::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaEffect(elem, global));
}

void
ColladaEffect::read(void)
{
    OSG_COLLADA_LOG(("ColladaEffect::read\n"));

    domEffectRef          effect = getDOMElementAs<domEffect>();
    const domImage_Array &images = effect->getImage_array();

    readImageArray(images);

    const domFx_profile_abstract_Array &profiles =
        effect->getFx_profile_abstract_array();

    for(UInt32 i = 0; i < profiles.getCount(); ++i)
    {
        if(domProfile_COMMON::ID() == profiles[i]->typeID())
        {
            readProfileCommon(daeSafeCast<domProfile_COMMON>(profiles[i]));
        }
        else if(domProfile_GLSL::ID() == profiles[i]->typeID())
        {
            readProfileGLSL(daeSafeCast<domProfile_GLSL>(profiles[i]));
        }
        else if(domProfile_CG::ID() == profiles[i]->typeID())
        {
            readProfileCG(daeSafeCast<domProfile_CG>(profiles[i]));
        }
    }
}

Material *
ColladaEffect::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaEffect::createInstance\n"));

    MaterialUnrecPtr            retVal        = NULL;
    domEffectRef                effect        = getDOMElementAs<domEffect>();
    ColladaInstanceEffectRefPtr colInstEffect =
        dynamic_cast<ColladaInstanceEffect *>(colInstElem);
    domInstance_effectRef       instEffect    =
        colInstElem->getDOMElementAs<domInstance_effect>();

    const domFx_profile_abstract_Array &profiles =
        effect->getFx_profile_abstract_array();

    for(UInt32 i = 0; i < profiles.getCount(); ++i)
    {
        if(domProfile_COMMON::ID() == profiles[i]->typeID())
        {
            retVal = createInstanceProfileCommon(
                daeSafeCast<domProfile_COMMON>(profiles[i]),
                effect, instEffect);
        }
        else if(domProfile_GLSL::ID() == profiles[i]->typeID())
        {
            retVal = createInstanceProfileGLSL(
                daeSafeCast<domProfile_GLSL>(profiles[i]),
                effect, instEffect);
        }
        else if(domProfile_CG::ID() == profiles[i]->typeID())
        {
            retVal = createInstanceProfileCG(
                daeSafeCast<domProfile_CG>(profiles[i]),
                effect, instEffect);
        }
    }

    // XXX TODO: do we always need to create a new material?
    editInstStore().push_back(retVal);

    return retVal;
}

ColladaEffect::ColladaEffect(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaEffect::~ColladaEffect(void)
{
}

void
ColladaEffect::readProfileCommon(domProfile_COMMON *prof)
{
    if(prof == NULL)
    {
        SWARNING << "ColladaEffect::readProfileCommon: No DOM element or "
                 << "incorrect type." << std::endl;
        return;
    }

    readImageArray(prof->getImage_array());

    domProfile_COMMON::domTechniqueRef tech = prof->getTechnique();

    readImageArray(tech->getImage_array());
}

void
ColladaEffect::readProfileGLSL(domProfile_GLSL *prof)
{
    SWARNING << "ColladaEffect::readProfileGLSL: NIY." << std::endl;
}

void
ColladaEffect::readProfileCG(domProfile_CG *prof)
{
    SWARNING << "ColladaEffect::readProfileCG: NIY." << std::endl;
}

Material *
ColladaEffect::createInstanceProfileCommon(
    domProfile_COMMON  *prof,       domEffect *effect,
    domInstance_effect *instEffect                      )
{
    OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon\n"));

    domProfile_COMMON::domTechniqueRef tech = prof->getTechnique();

    domCommon_color_or_texture_typeRef emission = NULL;
    domCommon_color_or_texture_typeRef ambient  = NULL;
    domCommon_color_or_texture_typeRef diffuse  = NULL;
    domCommon_color_or_texture_typeRef specular = NULL;

    if(tech->getConstant() != NULL)
    {
        domProfile_COMMON::domTechnique::domConstantRef constant =
            tech->getConstant();

        emission = constant->getEmission();
    }
    else if(tech->getLambert() != NULL)
    {
        domProfile_COMMON::domTechnique::domLambertRef lambert =
            tech->getLambert();

        emission = lambert->getEmission();
        ambient  = lambert->getAmbient ();
        diffuse  = lambert->getDiffuse ();
    }
    else if(tech->getPhong() != NULL)
    {
        domProfile_COMMON::domTechnique::domPhongRef phong =
            tech->getPhong();

        emission = phong->getEmission();
        ambient  = phong->getAmbient ();
        diffuse  = phong->getDiffuse ();
        specular = phong->getSpecular();
    }
    else if(tech->getBlinn() != NULL)
    {
        domProfile_COMMON::domTechnique::domBlinnRef blinn =
            tech->getBlinn();

        emission = blinn->getEmission();
        ambient  = blinn->getAmbient ();
        diffuse  = blinn->getDiffuse ();
        specular = blinn->getSpecular();
    }

    ChunkMaterialUnrecPtr mat      = ChunkMaterial::create();
    MaterialChunkUnrecPtr matChunk = MaterialChunk::create();

    if(emission != NULL)
    {
        domCommon_color_or_texture_type::domColorRef   color   =
            emission->getColor  ();
        domCommon_color_or_texture_type::domParamRef   param   =
            emission->getParam  ();
        domCommon_color_or_texture_type::domTextureRef texture =
            emission->getTexture();

        if(color != NULL)
        {
            Color4f colVal(color->getValue()[0],
                           color->getValue()[1],
                           color->getValue()[2],
                           color->getValue()[3] );

            matChunk->setEmission(colVal);
        }
        else if(param != NULL)
        {
            
        }
        else if(texture != NULL)
        {
        }
    }

    // XXX TODO: return constructed material
    return NULL;
}

Material *
ColladaEffect::createInstanceProfileGLSL(
    domProfile_GLSL    *prof,       domEffect   *effect,
    domInstance_effect *instEffect                      )
{
    SWARNING << "ColladaEffect::createInstanceProfileGLSL: NIY" << std::endl;

    return NULL;
}

Material *
ColladaEffect::createInstanceProfileCG(
    domProfile_CG      *prof,       domEffect   *effect,
    domInstance_effect *instEffect                      )
{
    SWARNING << "ColladaEffect::createInstanceProfileCG: NIY" << std::endl;

    return NULL;
}

void
ColladaEffect::readImageArray(const domImage_Array &images)
{
    for(UInt32 i = 0; i < images.getCount(); ++i)
    {
        ColladaImageRefPtr colImg = getUserDataAs<ColladaImage>(images[i]);

        if(colImg == NULL)
        {
            colImg = dynamic_pointer_cast<ColladaImage>(
                ColladaElementFactory::the()->create(
                    images[i], getGlobal()));

            colImg->read();
        }
    }
}

void
ColladaEffect::fillTexColor(
    domCommon_color_or_texture_type                *colTex,
    domCommon_color_or_texture_type::domColorRef   &colOut,
    domCommon_color_or_texture_type::domTextureRef &texOut )
{
    if(colTex != NULL)
    {
        colOut = colTex->getColor  ();
        texOut = colTex->getTexture();
    }
}



OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
