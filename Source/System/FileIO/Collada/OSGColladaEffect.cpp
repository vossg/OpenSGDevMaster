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
#include "OSGColladaGlobal.h"
#include "OSGColladaImage.h"
#include "OSGColladaSampler2D.h"
#include "OSGColladaInstanceEffect.h"

#include "OSGGeometry.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureEnvChunk.h"

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

    const domFx_newparam_common_Array &newParams = effect->getNewparam_array();

    for(UInt32 i = 0; i < newParams.getCount(); ++i)
    {
        if(newParams[i]->getFx_basic_type_common() == NULL)
        {
            SWARNING << "ColladaEffect::read: <newparam> ["
                     << newParams[i]->getSid()
                     << "] without contents encountered, ignored."
                     << std::endl;
            continue;
        }

        // must read surface params before sampler params, because
        // a samplers <source> can refer to a surface
        domFx_surface_commonRef paramSurface =
            newParams[i]->getFx_basic_type_common()->getSurface();

        if(paramSurface != NULL)
        {
            ParamSurface param;

            param.surface    = paramSurface;
            param.colSurface = dynamic_pointer_cast<ColladaSurface>(
                ColladaElementFactory::the()->create(
                    paramSurface, getGlobal()));

            param.colSurface->read();

            _surfaceParams[newParams[i]->getSid()] = param;
            continue;
        }

        domFx_sampler2D_commonRef paramSampler2D =
            newParams[i]->getFx_basic_type_common()->getSampler2D();

        if(paramSampler2D != NULL)
        {
            ParamSampler2D param;

            param.sampler2D    = paramSampler2D;
            param.colSampler2D = dynamic_pointer_cast<ColladaSampler2D>(
                ColladaElementFactory::the()->create(
                    paramSampler2D, getGlobal()));

            param.colSampler2D->setEffect(this);
            param.colSampler2D->read     (    );

            _sampler2DParams[newParams[i]->getSid()] = param;
            continue;
        }
    }

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

    editInstStore().push_back(retVal);

    return retVal;
}

/*! Return parameter of the effect (\c <newparam> tags) with the given \a name.
 */
daeElement *
ColladaEffect::findDOMParam(const std::string &name) const
{
    ParamSampler2DMapConstIt sampler2DIt = _sampler2DParams.find(name);

    if(sampler2DIt != _sampler2DParams.end())
    {
        return sampler2DIt->second.sampler2D;
    }

    ParamSurfaceMapConstIt surfaceIt = _surfaceParams.find(name);

    if(surfaceIt != _surfaceParams.end())
    {
        return surfaceIt->second.surface;
    }
}

/*! Return the loader element for the parameter of the effect (\c <newparam>
    tags) with the given \a name.
 */
ColladaElement *
ColladaEffect::findParam(const std::string &name) const
{
    ParamSampler2DMapConstIt sampler2DIt = _sampler2DParams.find(name);

    if(sampler2DIt != _sampler2DParams.end())
    {
        return sampler2DIt->second.colSampler2D;
    }

    ParamSurfaceMapConstIt surfaceIt = _surfaceParams.find(name);

    if(surfaceIt != _surfaceParams.end())
    {
        return surfaceIt->second.colSurface;
    }
}

ColladaEffect::ColladaEffect(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaEffect::~ColladaEffect(void)
{
}

/*! Fills internal data structures for \c <profile_COMMON>.
    This mainly collects relevant parameters so they can be looked up
    efficiently when creating an instance of this effect.
 */
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

    const domCommon_newparam_type_Array &newParams = prof->getNewparam_array();

    for(UInt32 i = 0; i < newParams.getCount(); ++i)
    {
        // must read surface params before sampler params, because their <source>
        // element can refer to a surface
        domFx_surface_commonRef paramSurface =
            newParams[i]->getSurface();

        if(paramSurface != NULL)
        {
            ParamSurface param;

            param.surface    = paramSurface;
            param.colSurface = dynamic_pointer_cast<ColladaSurface>(
                ColladaElementFactory::the()->create(
                    paramSurface, getGlobal()));

            param.colSurface->read();

            _surfaceParams[newParams[i]->getSid()] = param;
            continue;
        }

        domFx_sampler2D_commonRef paramSampler2D =
            newParams[i]->getSampler2D();

        if(paramSampler2D != NULL)
        {
            ParamSampler2D param;

            param.sampler2D    = paramSampler2D;
            param.colSampler2D = dynamic_pointer_cast<ColladaSampler2D>(
                ColladaElementFactory::the()->create(
                    paramSampler2D, getGlobal()));

            param.colSampler2D->setEffect(this);
            param.colSampler2D->read     (    );

            _sampler2DParams[newParams[i]->getSid()] = param;
            continue;
        }

        // param is unhandled if we get to here
        SWARNING << "ColladaEffect::readProfileCommon: Unhandled <newparam> ["
                 << newParams[i]->getSid() << "]."
                 << std::endl;
    }

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

/*! Create an OpenSG material that matches this \c <profile_COMMON> material
    (to the extent possible).
 */
MaterialTransitPtr
ColladaEffect::createInstanceProfileCommon(
    domProfile_COMMON  *prof,       domEffect *effect,
    domInstance_effect *instEffect                      )
{
    OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon\n"));

    ColladaInstanceEffectRefPtr colInstEffect =
        getUserDataAs<ColladaInstanceEffect>(instEffect);

    domProfile_COMMON::domTechniqueRef tech = prof->getTechnique();

    domCommon_color_or_texture_typeRef emission  = NULL;
    domCommon_color_or_texture_typeRef ambient   = NULL;
    domCommon_color_or_texture_typeRef diffuse   = NULL;
    domCommon_color_or_texture_typeRef specular  = NULL;
    domCommon_float_or_param_typeRef   shininess = NULL;

    if(tech->getConstant() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <constant> shader\n"));

        domProfile_COMMON::domTechnique::domConstantRef constant =
            tech->getConstant();

        emission = constant->getEmission();
    }
    else if(tech->getLambert() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <lambert> shader\n"));

        domProfile_COMMON::domTechnique::domLambertRef lambert =
            tech->getLambert();

        emission = lambert->getEmission();
        ambient  = lambert->getAmbient ();
        diffuse  = lambert->getDiffuse ();
    }
    else if(tech->getPhong() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <phong> shader\n"));

        domProfile_COMMON::domTechnique::domPhongRef phong =
            tech->getPhong();

        emission  = phong->getEmission ();
        ambient   = phong->getAmbient  ();
        diffuse   = phong->getDiffuse  ();
        specular  = phong->getSpecular ();
        shininess = phong->getShininess();
    }
    else if(tech->getBlinn() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <blinn> shader\n"));

        domProfile_COMMON::domTechnique::domBlinnRef blinn =
            tech->getBlinn();

        emission  = blinn->getEmission ();
        ambient   = blinn->getAmbient  ();
        diffuse   = blinn->getDiffuse  ();
        specular  = blinn->getSpecular ();
        shininess = blinn->getShininess();
    }

    UInt32                texCount = 0;
    ChunkMaterialUnrecPtr mat      = ChunkMaterial::create();
    MaterialChunkUnrecPtr matChunk = MaterialChunk::create();

    getGlobal()->getStatCollector()->getElem(
        ColladaGlobal::statNMaterialCreated)->inc();

    if(emission != NULL)
    {
        domCommon_color_or_texture_type::domColorRef   color;
        domCommon_color_or_texture_type::domParamRef   param;
        domCommon_color_or_texture_type::domTextureRef texture;

        fillColorParamTex(emission, color, param, texture);

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
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<emission>/<param> not supported."
                     << std::endl;
        }
        else if(texture != NULL)
        {
            xsNCName texId      = texture->getTexture ();
            xsNCName tcSemantic = texture->getTexcoord();

            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<emission>/<texture> not supported."
                     << std::endl;
        }
    }

    if(ambient != NULL)
    {
        domCommon_color_or_texture_type::domColorRef   color;
        domCommon_color_or_texture_type::domParamRef   param;
        domCommon_color_or_texture_type::domTextureRef texture;

        fillColorParamTex(ambient, color, param, texture);

        if(color != NULL)
        {
            Color4f colVal(color->getValue()[0],
                           color->getValue()[1],
                           color->getValue()[2],
                           color->getValue()[3] );

            matChunk->setAmbient(colVal);
        }
        else if(param != NULL)
        {
            
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<ambient>/<param> not supported."
                     << std::endl;
        }
        else if(texture != NULL)
        {
            std::string texId      = texture->getTexture ();
            std::string tcSemantic = texture->getTexcoord();

            ParamSampler2DMapConstIt paramIt = _sampler2DParams.find(texId);

            if(paramIt != _sampler2DParams.end())
            {
                addTexture(texId, tcSemantic, colInstEffect,
                           paramIt->second.colSampler2D, mat, GL_REPLACE,
                           texCount                                      );
            }
            else
            {
                SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                         << "<ambient>/<texture> could not find sampler2D ["
                         << texId << "]."
                         << std::endl;
            }
        }
    }

    if(diffuse != NULL)
    {
        domCommon_color_or_texture_type::domColorRef   color;
        domCommon_color_or_texture_type::domParamRef   param;
        domCommon_color_or_texture_type::domTextureRef texture;

        fillColorParamTex(diffuse, color, param, texture);

        if(color != NULL)
        {
            Color4f colVal(color->getValue()[0],
                           color->getValue()[1],
                           color->getValue()[2],
                           color->getValue()[3] );

            matChunk->setDiffuse(colVal);
        }
        else if(param != NULL)
        {
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<diffuse>/<param> not supported."
                     << std::endl;
        }
        else if(texture != NULL)
        {
            std::string texId      = texture->getTexture ();
            std::string tcSemantic = texture->getTexcoord();

            ParamSampler2DMapConstIt paramIt = _sampler2DParams.find(texId);

            if(paramIt != _sampler2DParams.end())
            {
                addTexture(texId, tcSemantic, colInstEffect,
                           paramIt->second.colSampler2D, mat, GL_MODULATE,
                           texCount                                       );
            }
            else
            {
                SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                         << "<diffuse>/<texture> could not find sampler2D ["
                         << texId << "]."
                         << std::endl;
            }

            matChunk->setDiffuse(Color4f(0.8f, 0.8f, 0.8f, 1.f));
        }
    }

    if(specular != NULL)
    {
        domCommon_color_or_texture_type::domColorRef   color;
        domCommon_color_or_texture_type::domParamRef   param;
        domCommon_color_or_texture_type::domTextureRef texture;

        fillColorParamTex(specular, color, param, texture);

        if(color != NULL)
        {
            Color4f colVal(color->getValue()[0],
                           color->getValue()[1],
                           color->getValue()[2],
                           color->getValue()[3] );

            matChunk->setSpecular(colVal);
        }
        else if(param != NULL)
        {
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<specular>/<param> not supported."
                     << std::endl;
        }
        else if(texture != NULL)
        {
            xsNCName texId      = texture->getTexture ();
            xsNCName tcSemantic = texture->getTexcoord();

            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<specular>/<texture> not supported."
                     << std::endl;
        }
    }

    if(shininess != NULL)
    {
        domCommon_float_or_param_type::domFloatRef value;
        domCommon_float_or_param_type::domParamRef param;

        fillFloatParam(shininess, value, param);

        if(value != NULL)
        {
            matChunk->setShininess(value->getValue());
        }
        else if(param != NULL)
        {
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<shininess>/<param> not supported."
                     << std::endl;
        }
    }

    mat->addChunk(matChunk);

    return MaterialTransitPtr(mat);
}

MaterialTransitPtr
ColladaEffect::createInstanceProfileGLSL(
    domProfile_GLSL    *prof,       domEffect   *effect,
    domInstance_effect *instEffect                      )
{
    SWARNING << "ColladaEffect::createInstanceProfileGLSL: NIY" << std::endl;

    return MaterialTransitPtr();
}

MaterialTransitPtr
ColladaEffect::createInstanceProfileCG(
    domProfile_CG      *prof,       domEffect   *effect,
    domInstance_effect *instEffect                      )
{
    SWARNING << "ColladaEffect::createInstanceProfileCG: NIY" << std::endl;

    return MaterialTransitPtr();
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
ColladaEffect::fillColorParamTex(
    domCommon_color_or_texture_type                *colTex,
    domCommon_color_or_texture_type::domColorRef   &colOut,
    domCommon_color_or_texture_type::domParamRef   &paramOut,
    domCommon_color_or_texture_type::domTextureRef &texOut   )
{
    if(colTex != NULL)
    {
        colOut   = colTex->getColor  ();
        paramOut = colTex->getParam  ();
        texOut   = colTex->getTexture();
    }
}

void
ColladaEffect::fillFloatParam(
    domCommon_float_or_param_type              *floatParam,
    domCommon_float_or_param_type::domFloatRef &floatOut,
    domCommon_float_or_param_type::domParamRef &paramOut )
{
    if(floatParam != NULL)
    {
        floatOut = floatParam->getFloat();
        paramOut = floatParam->getParam();
    }
}

void
ColladaEffect::addTexture(
    const std::string     &texId,         const std::string &tcSemantic,
    ColladaInstanceEffect *colInstEffect, ColladaSampler2D  *colSampler2D,
    ChunkMaterial         *mat,           GLenum             envMode,
    UInt32                &texCount                                       )
{
    TextureEnvChunkUnrecPtr texEnv = TextureEnvChunk::create();
    texEnv->setEnvMode(envMode);

    mat->addChunk(colSampler2D->getTexture(), texCount);
    mat->addChunk(texEnv,                     texCount);

    OSG_COLLADA_LOG(("ColladaEffect::addTexture: "
                     "texCoord symbol [%s] in slot [%d]\n",
                     tcSemantic.c_str(),
                     Geometry::TexCoordsIndex + texCount));

    colInstEffect->editTCMap()[tcSemantic] =
        Geometry::TexCoordsIndex + texCount;

    ++texCount;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
