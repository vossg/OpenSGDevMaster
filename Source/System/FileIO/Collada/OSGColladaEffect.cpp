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
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#include "OSGColladaEffect.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaImage.h"
#include "OSGColladaInstanceEffect.h"
#include "OSGColladaMaterial.h"
#include "OSGColladaSampler2D.h"

#include "OSGGeometry.h"
#include "OSGChunkMaterial.h"
#include "OSGBlendChunk.h"
#include "OSGDepthChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureEnvChunk.h"

#include "OSGCgFXPassChunk.h"
#include "OSGCgFXMaterial.h"
#include "OSGCgFXVariableTexObj.h"
#include "OSGNameAttachment.h"

#include "OSGImageFileHandler.h"

#include <dom/domEffect.h>
#include <dom/domInstance_effect.h>
#include <dom/domProfile_COMMON.h>
#include <dom/domProfile_GLSL.h>
#include <dom/domProfile_CG.h>
#include <dom/domGl_pipeline_settings.h>

#include <sstream>

// It is not clear what is the best way to handle <transparent>/<texture>, so
// OSG_COLLADA_TRANSPARENT_MODE allows choosing between implementations
// to experiment. See below for what the modes do.

#define OSG_COLLADA_TRANSPARENT_MODE 1
// #define OSG_COLLADA_TRANSPARENT_MODE 2

OSG_BEGIN_NAMESPACE

ColladaInstInfoTransitPtr
ColladaEffect::ColladaEffectInstInfo::create(
    ColladaMaterial *colInstParent, ColladaInstanceEffect *colInst)
{
    return ColladaInstInfoTransitPtr(
        new ColladaEffectInstInfo(colInstParent, colInst));
}

void
ColladaEffect::ColladaEffectInstInfo::process(void)
{
    SFATAL << "ColladaEffectInstInfo::process called!" << std::endl;
}

ColladaEffect::ColladaEffectInstInfo::ColladaEffectInstInfo(
    ColladaMaterial *colInstParent, ColladaInstanceEffect *colInst)

    : Inherited(colInstParent, colInst)
{
}

ColladaEffect::ColladaEffectInstInfo::~ColladaEffectInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaEffect::_regHelper(
    &ColladaEffect::create, "effect");


ColladaElementTransitPtr
ColladaEffect::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaEffect(elem, global));
}

void
ColladaEffect::read(ColladaElement *colElemParent)
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

            param.colSurface->read(this);

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
            param.colSampler2D->read     (this);

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
ColladaEffect::createInstance(ColladaInstInfo *colInstInfo)
{
    OSG_COLLADA_LOG(("ColladaEffect::createInstance\n"));

    MaterialUnrecPtr            retVal        = NULL;
    domEffectRef                effect        = getDOMElementAs<domEffect>();
    ColladaInstanceEffectRefPtr colInstEffect =
        dynamic_cast<ColladaInstanceEffect *>(colInstInfo->getColInst());
    domInstance_effectRef       instEffect    =
        colInstInfo->getColInst()->getDOMElementAs<domInstance_effect>();

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

/*! Return parameter of the effect (\c &lt;newparam&gt; tags) with the given \a name.
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

    return NULL;
}

/*! Return the loader element for the parameter of the effect (\c
    &lt;newparam&gt; tags) with the given \a name.
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

    return NULL;
}

ColladaEffect::ColladaEffect(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaEffect::~ColladaEffect(void)
{
}

/*! Fills internal data structures for \c &lt;profile_COMMON&gt;.
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

    readImageArray(prof->getImage_array   ());
    readNewParams (prof->getNewparam_array());

    domProfile_COMMON::domTechniqueRef tech = prof->getTechnique();

    readNewParams (tech->getNewparam_array());
    readImageArray(tech->getImage_array   ());
}

void
ColladaEffect::readNewParams(const CommonParamArray &newParams)
{
    for(UInt32 i = 0; i < newParams.getCount(); ++i)
    {
        // must read surface params before sampler params, because their
        // <source> element can refer to a surface

        domFx_surface_commonRef paramSurface =
            newParams[i]->getSurface();

        if(paramSurface != NULL)
        {
            ParamSurface param;

            param.surface    = paramSurface;
            param.colSurface = dynamic_pointer_cast<ColladaSurface>(
                ColladaElementFactory::the()->create(
                    paramSurface, getGlobal()));

            param.colSurface->read(this);

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
            param.colSampler2D->read     (this);

            _sampler2DParams[newParams[i]->getSid()] = param;
            continue;
        }

        // param is unhandled if we get to here
        SWARNING << "ColladaEffect::readProfileCommon: Unhandled <newparam> ["
                 << newParams[i]->getSid() << "]."
                 << std::endl;
    }

}

void
ColladaEffect::readProfileGLSL(domProfile_GLSL *prof)
{
    SWARNING << "ColladaEffect::readProfileGLSL: NIY." << std::endl;
}

void
ColladaEffect::readProfileCG(domProfile_CG *prof)
{
 //  // SWARNING << "ColladaEffect::readProfileCG: NIY." << std::endl;
 //   if(prof == NULL)
 //   {
 //       SWARNING << "ColladaEffect::readProfileCG: No DOM element or "
 //                << "incorrect type." << std::endl;
 //       return;
 //   }

 //   readImageArray(prof->getImage_array());

 //   const domCg_newparam_Array &newParams = prof->getNewparam_array();

	//
	//for(UInt32 i = 0; i < newParams.getCount(); ++i)
	//{
	//	if(newParams[i] == NULL) continue;
	//	// must read surface params before sampler params, because their <source>
	//	// element can refer to a surface
	//	domCg_surface_typeRef paramSurface =
	//		newParams[i]->getCg_param_type()->getSurface();

	//	if(paramSurface != NULL)
	//	{
	//		//ParamSurface param;

	//		//param.surface    = paramSurface;
	//		//param.colSurface = dynamic_pointer_cast<ColladaSurface>(
	//		//    ColladaElementFactory::the()->create(
	//		//        paramSurface, getGlobal()));

	//		//param.colSurface->read();

	//		//_surfaceParams[newParams[i]->getSid()] = param;
	//		//continue;
	//	}

	//	domCg_sampler2DRef paramSampler2D =
	//		newParams[i]->getCg_param_type()->getSampler2D();

	//	if(paramSampler2D != NULL)
	//	{
	//		//ParamSampler2D param;

	//		//param.sampler2D    = paramSampler2D;
	//		//param.colSampler2D = dynamic_pointer_cast<ColladaSampler2D>(
	//		//    ColladaElementFactory::the()->create(
	//		//        paramSampler2D, getGlobal()));

	//		//param.colSampler2D->setEffect(this);
	//		//param.colSampler2D->read     (    );

	//		//_sampler2DParams[newParams[i]->getSid()] = param;
	//		//continue;
	//	}

	//	// param is unhandled if we get to here
 // /*      SWARNING << "ColladaEffect::readProfileCG: Unhandled <newparam> ["
	//			 << newParams[i]->getSid() << "]."
	//			 << std::endl;*/
	//}
	//// read any images that may be in any of the techniques
	//domProfile_CG::domTechnique_Array techs = prof->getTechnique_array();
	//for(UInt32 i = 0; i < techs.getCount(); ++i)
	//{
	//	readImageArray(techs[i]->getImage_array());
	//} 
	//
}

/*! Create an OpenSG material that matches this \c &lt;profile_COMMON&gt;
    material (to the extent possible).
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

    domCommon_color_or_texture_typeRef emission     = NULL;
    domCommon_color_or_texture_typeRef ambient      = NULL;
    domCommon_color_or_texture_typeRef diffuse      = NULL;
    domCommon_color_or_texture_typeRef specular     = NULL;
    domCommon_float_or_param_typeRef   shininess    = NULL;
    domCommon_transparent_typeRef      transparent  = NULL;
    domCommon_float_or_param_typeRef   transparency = NULL;

    if(tech->getConstant() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <constant> shader\n"));

        domProfile_COMMON::domTechnique::domConstantRef constant =
            tech->getConstant();

        emission     = constant->getEmission    ();
        transparent  = constant->getTransparent ();
        transparency = constant->getTransparency();
    }
    else if(tech->getLambert() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <lambert> shader\n"));

        domProfile_COMMON::domTechnique::domLambertRef lambert =
            tech->getLambert();

        emission     = lambert->getEmission    ();
        ambient      = lambert->getAmbient     ();
        diffuse      = lambert->getDiffuse     ();
        transparent  = lambert->getTransparent ();
        transparency = lambert->getTransparency();
    }
    else if(tech->getPhong() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <phong> shader\n"));

        domProfile_COMMON::domTechnique::domPhongRef phong =
            tech->getPhong();

        emission     = phong->getEmission    ();
        ambient      = phong->getAmbient     ();
        diffuse      = phong->getDiffuse     ();
        specular     = phong->getSpecular    ();
        shininess    = phong->getShininess   ();
        transparent  = phong->getTransparent ();
        transparency = phong->getTransparency();
    }
    else if(tech->getBlinn() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                         "using <blinn> shader\n"));

        domProfile_COMMON::domTechnique::domBlinnRef blinn =
            tech->getBlinn();

        emission     = blinn->getEmission    ();
        ambient      = blinn->getAmbient     ();
        diffuse      = blinn->getDiffuse     ();
        specular     = blinn->getSpecular    ();
        shininess    = blinn->getShininess   ();
        transparent  = blinn->getTransparent ();
        transparency = blinn->getTransparency();
    }

    UInt32                texCount   = 0;
    Real32                transVal   = 1.f;
    ChunkMaterialUnrecPtr mat        = ChunkMaterial::create();
    MaterialChunkUnrecPtr matChunk   = MaterialChunk::create();
    BlendChunkUnrecPtr    blendChunk = NULL;
    DepthChunkUnrecPtr    depthChunk = NULL;

    getGlobal()->getStatCollector()->getElem(
        ColladaGlobal::statNMaterialCreated)->inc();

    // handle the "conventional" material attributes
    handleProfileCommonEmission(emission,   matChunk               );
    handleProfileCommonAmbient (ambient,    colInstEffect,
                                mat,        matChunk,
                                blendChunk, depthChunk,    texCount);
    handleProfileCommonDiffuse (diffuse,    colInstEffect,
                                mat,        matChunk,
                                blendChunk, depthChunk,    texCount);
    handleProfileCommonSpecular(specular,   matChunk               );

    if(shininess != NULL)
    {
        domCommon_float_or_param_type::domFloatRef value;
        domCommon_float_or_param_type::domParamRef param;

        fillFloatParam(shininess, value, param);

        if(value != NULL)
        {
            Real32 shininessVal = value->getValue();
            shininessVal = osgClamp(0.f, shininessVal, 128.f);

            matChunk->setShininess(shininessVal);
        }
        else if(param != NULL)
        {
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<shininess>/<param> not supported."
                     << std::endl;
        }
    }

    if(transparency != NULL)
    {
        // this only sets transVal to the value stored in the
        // <transparency> tag.

        domCommon_float_or_param_type::domFloatRef value;
        domCommon_float_or_param_type::domParamRef param;

        fillFloatParam(transparency, value, param);

        if(value != NULL)
        {
            transVal = value->getValue();

            if(getGlobal()->getOptions()->getInvertTransparency() == true)
                transVal = 1.f - transVal;
        }
        else if(param != NULL)
        {
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<transparency>/<param> not supported."
                     << std::endl;
        }
    }

    if(transparent != NULL)
    {
        // this handles <transparent> and <transparency> tags
        // (by considering the value of transVal) - since they are
        // so closely related that they need to be handled together

        domCommon_color_or_texture_type::domColorRef   color;
        domCommon_color_or_texture_type::domParamRef   param;
        domCommon_color_or_texture_type::domTextureRef texture;

        fillColorParamTex(transparent, color, param, texture);

        if(color != NULL)
        {
            Color4f colVal(color->getValue()[0],
                           color->getValue()[1],
                           color->getValue()[2],
                           color->getValue()[3] );

            domFx_opaque_enum opaque = transparent->getOpaque();

            if(opaque == FX_OPAQUE_ENUM_A_ONE)
            {
                Color4f constCol(colVal[3] * transVal,
                                 colVal[3] * transVal,
                                 colVal[3] * transVal,
                                 colVal[3] * transVal );

                if(constCol[0] < (1.f - TypeTraits<Real32>::getDefaultEps()))
                {
                    if(blendChunk == NULL)
                        blendChunk = BlendChunk::create();

                    blendChunk->setSrcFactor (GL_CONSTANT_ALPHA          );
                    blendChunk->setDestFactor(GL_ONE_MINUS_CONSTANT_ALPHA);

                    blendChunk->setColor     (constCol                   );

                    OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                                     "src: GL_CONSTANT_ALPHA "
                                     "dst: GL_ONE_MINUS_CONSTANT_ALPHA "
                                     "%f\n", constCol[0]));
                }
            }
            else if(opaque == FX_OPAQUE_ENUM_RGB_ZERO)
            {
                Color4f constCol(colVal[0]         * transVal,
                                 colVal[1]         * transVal,
                                 colVal[2]         * transVal,
                                 luminance(colVal) * transVal );

                if(constCol[0] > TypeTraits<Real32>::getDefaultEps() ||
                   constCol[1] > TypeTraits<Real32>::getDefaultEps() ||
                   constCol[2] > TypeTraits<Real32>::getDefaultEps()   )
                {
                    if(blendChunk == NULL)
                        blendChunk = BlendChunk::create();

                    blendChunk->setSrcFactor (GL_ONE_MINUS_CONSTANT_COLOR);
                    blendChunk->setDestFactor(GL_CONSTANT_COLOR          );

                    blendChunk->setColor     (constCol                   );

                    OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                                     "src: GL_ONE_MINUS_CONSTANT_COLOR "
                                     "dst: GL_CONSTANT_COLOR "
                                     "%f %f %f %f\n",
                                     constCol[0], constCol[1],
                                     constCol[2], constCol[3] ));
                }
            }
        }
        else if(param != NULL)
        {
            SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                     << "<transparent>/<param> not supported."
                     << std::endl;
        }
        else if(texture != NULL)
        {
            xsNCName texId      = texture->getTexture ();
            xsNCName tcSemantic = texture->getTexcoord();

            ParamSampler2DMapConstIt paramIt = _sampler2DParams.find(texId);

            if(paramIt != _sampler2DParams.end())
            {
                addTexture(texId, tcSemantic, colInstEffect,
                           paramIt->second.colSampler2D, mat, GL_MODULATE,
                           texCount                                       );

                // do we need a blend chunk?
                if(paramIt->second.colSampler2D->hasAlpha())
                {
                    if(blendChunk == NULL)
                        blendChunk = BlendChunk::create();

#if defined(OSG_COLLADA_TRANSPARENT_MODE) && OSG_COLLADA_TRANSPARENT_MODE == 1
                    // Always use alpha test with low alpha value, standard
                    // blending, but enable depth writes

                    blendChunk->setAlphaFunc (GL_GREATER);
                    blendChunk->setAlphaValue(0.1f      );

                    blendChunk->setSrcFactor (GL_SRC_ALPHA          );
                    blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                    // force depth writing even for transparent object
                    if(depthChunk == NULL)
                        depthChunk = DepthChunk::create();

#elif defined(OSG_COLLADA_TRANSPARENT_MODE) && OSG_COLLADA_TRANSPARENT_MODE == 2
                    // enable depth writes for textures with a "mask" alpha
                    // channel (only values are 0 and 1)
                    // standard blending otherwise

                    if(paramIt->second.colSampler2D->hasBinaryAlpha())
                    {
                        OSG_COLLADA_LOG((
                            "ColladaEffect::createInstanceProfileCommon: "
                            "<transparent>/<texture> using alpha test.\n"));

                        blendChunk->setAlphaFunc (GL_GREATER  );
                        blendChunk->setAlphaValue(0.5f        );

                        blendChunk->setDestFactor(GL_ZERO     );
                        blendChunk->setSrcFactor (GL_SRC_ALPHA);
                    }
                    else
                    {
                        OSG_COLLADA_LOG((
                            "ColladaEffect::createInstanceProfileCommon: "
                            "<transparent>/<texture> using blending.\n"));

                        blendChunk->setSrcFactor (GL_SRC_ALPHA          );
                        blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                    }
#endif // OSG_COLLADA_TRANSPARENT_MODE
                }
            }
            else
            {
                SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                         << "<diffuse>/<texture> could not find sampler2D ["
                         << texId << "]."
                         << std::endl;
            }
        }
    }
    else if(transparency != NULL)
    {
        // handle only <transparency> tag case (no <transparent> tag)

        Color4f constCol(transVal, transVal, transVal, transVal);

        if(constCol[0] < (1.f - TypeTraits<Real32>::getDefaultEps()))
        {
            if(blendChunk == NULL)
                blendChunk = BlendChunk::create();

            blendChunk->setSrcFactor (GL_CONSTANT_ALPHA          );
            blendChunk->setDestFactor(GL_ONE_MINUS_CONSTANT_ALPHA);

            blendChunk->setColor     (constCol                   );

            OSG_COLLADA_LOG(("ColladaEffect::createInstanceProfileCommon: "
                             "src: GL_CONSTANT_ALPHA "
                             "dst: GL_ONE_MINUS_CONSTANT_ALPHA "
                             "%f\n", constCol[0]));
        }
    }

    mat->addChunk(matChunk);

    if(blendChunk != NULL)
        mat->addChunk(blendChunk);

    if(depthChunk != NULL)
        mat->addChunk(depthChunk);

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

void
ColladaEffect::handleProfileCommonEmission(
    domCommon_color_or_texture_type *emission,
    MaterialChunk                   *matChunk )
{
    if(emission == NULL)
        return;

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
        SWARNING << "ColladaEffect::handleProfileCommonEmission: "
                 << "<emission>/<param> not supported."
                 << std::endl;
    }
    else if(texture != NULL)
    {
#if 0
        xsNCName texId      = texture->getTexture ();
        xsNCName tcSemantic = texture->getTexcoord();
#endif

        SWARNING << "ColladaEffect::handleProfileCommonEmission: "
                 << "<emission>/<texture> not supported."
                 << std::endl;
    }
}

void
ColladaEffect::handleProfileCommonAmbient(
    domCommon_color_or_texture_type *ambient,
    ColladaInstanceEffect           *colInstEffect,
    ChunkMaterial                   *mat,
    MaterialChunk                   *matChunk,
    BlendChunkUnrecPtr              &blendChunk,
    DepthChunkUnrecPtr              &depthChunk,
    UInt32                          &texCount     )
{
    if(ambient == NULL)
        return;

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

        SWARNING << "ColladaEffect::handleProfileCommonAmbient: "
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

            // do we need a blend chunk?
            if(paramIt->second.colSampler2D->hasAlpha())
            {
                if(blendChunk == NULL)
                    blendChunk = BlendChunk::create();

#if defined(OSG_COLLADA_TRANSPARENT_MODE) && OSG_COLLADA_TRANSPARENT_MODE == 1
                // Always use alpha test with low alpha value, standard
                // blending, but enable depth writes

                blendChunk->setAlphaFunc (GL_GREATER);
                blendChunk->setAlphaValue(0.1f      );

                blendChunk->setSrcFactor (GL_SRC_ALPHA          );
                blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                // force depth writing even for transparent object
                if(depthChunk == NULL)
                    depthChunk = DepthChunk::create();

#elif defined(OSG_COLLADA_TRANSPARENT_MODE) && OSG_COLLADA_TRANSPARENT_MODE == 2
                // enable depth writes for textures with a "mask" alpha
                // channel (only values are 0 and 1)
                // standard blending otherwise

                if(paramIt->second.colSampler2D->hasBinaryAlpha())
                {
                    OSG_COLLADA_LOG(("ColladaEffect::handleProfileCommonAmbient: "
                                     "<ambient>/<texture> using alpha test.\n"));

                    blendChunk->setAlphaFunc (GL_GREATER  );
                    blendChunk->setAlphaValue(0.5f        );

                    blendChunk->setDestFactor(GL_ZERO     );
                    blendChunk->setSrcFactor (GL_SRC_ALPHA);
                }
                else
                {
                    OSG_COLLADA_LOG(("ColladaEffect::handleProfileCommonAmbient: "
                                     "<ambient>/<texture> using blending.\n"));

                    blendChunk->setSrcFactor (GL_SRC_ALPHA          );
                    blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                }
#endif // OSG_COLLADA_TRANSPARENT_MODE
            }
        }
        else
        {
            SWARNING << "ColladaEffect::handleProfileCommonAmbient: "
                     << "<ambient>/<texture> could not find sampler2D ["
                     << texId << "]."
                     << std::endl;
        }
    }
}

void
ColladaEffect::handleProfileCommonDiffuse(
    domCommon_color_or_texture_type *diffuse,
    ColladaInstanceEffect           *colInstEffect,
    ChunkMaterial                   *mat,
    MaterialChunk                   *matChunk,
    BlendChunkUnrecPtr              &blendChunk,
    DepthChunkUnrecPtr              &depthChunk,
    UInt32                          &texCount     )
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
        SWARNING << "ColladaEffect::handleProfileCommonDiffuse: "
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

            // do we need a blend chunk?
            if(paramIt->second.colSampler2D->hasAlpha())
            {
                if(blendChunk == NULL)
                    blendChunk = BlendChunk::create();

#if defined(OSG_COLLADA_TRANSPARENT_MODE) && OSG_COLLADA_TRANSPARENT_MODE == 1
                // Always use alpha test with low alpha value, standard
                // blending, but enable depth writes

                blendChunk->setAlphaFunc (GL_GREATER);
                blendChunk->setAlphaValue(0.1f      );

                blendChunk->setSrcFactor (GL_SRC_ALPHA          );
                blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

                // force depth writing even for transparent object
                if(depthChunk == NULL)
                    depthChunk = DepthChunk::create();

#elif defined(OSG_COLLADA_TRANSPARENT_MODE) && OSG_COLLADA_TRANSPARENT_MODE == 2
                // enable depth writes for textures with a "mask" alpha
                // channel (only values are 0 and 1)
                // standard blending otherwise

                if(paramIt->second.colSampler2D->hasBinaryAlpha())
                {
                    OSG_COLLADA_LOG(("ColladaEffect::handleProfileCommonDiffuse: "
                                     "<diffuse>/<texture> using alpha test.\n"));

                    blendChunk->setAlphaFunc (GL_GREATER  );
                    blendChunk->setAlphaValue(0.5f        );

                    blendChunk->setDestFactor(GL_ZERO     );
                    blendChunk->setSrcFactor (GL_SRC_ALPHA);
                }
                else
                {
                    OSG_COLLADA_LOG(("ColladaEffect::handleProfileCommonDiffuse: "
                                     "<diffuse>/<texture> using blending.\n"));

                    blendChunk->setSrcFactor (GL_SRC_ALPHA          );
                    blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                }
#endif // OSG_COLLADA_TRANSPARENT_MODE
            }
        }
        else
        {
            SWARNING << "ColladaEffect::handleProfileCommonDiffuse: "
                     << "<diffuse>/<texture> could not find sampler2D ["
                     << texId << "]."
                     << std::endl;
        }

        matChunk->setDiffuse(Color4f(0.8f, 0.8f, 0.8f, 1.f));
    }
}

void
ColladaEffect::handleProfileCommonSpecular(
    domCommon_color_or_texture_type *specular,
    MaterialChunk                   *matChunk )
{
    if(specular == NULL)
        return;
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
#if 0
        xsNCName texId      = texture->getTexture ();
        xsNCName tcSemantic = texture->getTexcoord();
#endif
        SWARNING << "ColladaEffect::createInstanceProfileCommon: "
                 << "<specular>/<texture> not supported."
                 << std::endl;
    }
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

            colImg->read(this);
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
ColladaEffect::fillColorParamTex(
    domCommon_transparent_type                     *colTex,
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

    getGlobal()->getStatCollector()->getElem(
        ColladaGlobal::statNTextureUsed)->inc();

    OSG_COLLADA_LOG(("ColladaEffect::addTexture: "
                     "texCoord symbol [%s] in slot [%d]\n",
                     tcSemantic.c_str(),
                     Geometry::TexCoordsIndex + texCount));

    colInstEffect->editTCMap()[tcSemantic] =
        Geometry::TexCoordsIndex + texCount;

    ++texCount;
}

Real32
ColladaEffect::luminance(const Color4f &col)
{
    return (col[0] * 0.212671f + col[1] * 0.71516f + col[2] * 0.072169f);
}

MaterialTransitPtr
ColladaEffect::createInstanceProfileCG(
    domProfile_CG      *prof,       domEffect   *effect,
    domInstance_effect *instEffect                      )
{
    //SWARNING << "ColladaEffect::createInstanceProfileCG: NIY" << std::endl;

	bool materialInitialized(false);
	/* first things first, we need to find either the .cgfx file associated with the 
	 * effect, or grab the string embedded in the .dae file which has the .cgfx code text
	 * 
	 * Check for file reference first.
	 */
	domFx_include_common_Array includeArr = prof->getInclude_array();

	OSG::CgFXMaterialTransitPtr newCgFXmat = OSG::CgFXMaterial::create();

	std::string cgfxFileLocation("");
	if(includeArr.getCount() > 0)
	{
		bool foundFilepath(false);
		for(unsigned int i(0); i < includeArr.getCount(); i++)
		{
			domFx_include_common_complexType* cur = includeArr[i];
			cgfxFileLocation = std::string(cur->getUrl().originalStr());
			// check if the url points to something in the collada file (denoted by a #).  If it DOESN'T, then it is the file
			// path to the .cgfx file used for this effect
	
			UInt32 loc;
			if( (loc = cgfxFileLocation.find_last_of('.')) != std::string::npos)
			{
				if(cgfxFileLocation.substr(loc).compare(".cgfx") == 0 &&  cgfxFileLocation[0] != '#')
				{  /* we assume this is the location of a cgfx file
					  so we use it to create the material */
					foundFilepath = true;
					break;
				}
				else if(cgfxFileLocation.substr(loc).compare(".cg") == 0)
				{
					SWARNING << "ColladaEffect::createInstanceProfileCG: CG effects are not supported. " 
							 << "Must use CgFX instead."  << std::endl;
					break;
				}
			}
		}
		if(foundFilepath)
		{   // use the file to initialize the material
			newCgFXmat->setEffectFile(fixFilepath(cgfxFileLocation));
			materialInitialized = true;
		}
	} else // check that there is inline code for the effect
	{
		// We need to build up the state and technique info from scratch,
		// since this info isn't included in the embedded code.

		domFx_code_profile_Array inlineCode = prof->getCode_array();
		if(inlineCode.getCount() > 0)
		{// In the event that there is more than one available code string, the first one is used
			std::string effectCode = inlineCode[0]->getValue();
			// build up the code to set up techniques, passes, etc.
			int codeSize = effectCode.size();
			effectCode.append( buildCgFXCode(prof) );
			if(!(effectCode.size() == codeSize)) // true if code was appended...
			{
				newCgFXmat->setEffectString(effectCode);
			
				materialInitialized = true;
			} else // error, since we can't set techniques, passes, etc.
			{
				SWARNING << "Error appending Cg code for " << prof->getID() << ". Material will be null!" << std::endl;
			}
		} else
		{ // no code inline code was found, return a null material.
			SWARNING << "No .cgfx file found and no inline code found for " << effect->getID()
					 << ". Material will be null!" << std::endl;
		}
	}

	if(materialInitialized)
	{
		// Since the CgFXMaterial isn't initialized (i.e., the code compiled)
		// until commitChanges() is called, we call it here so that we can update 
		// the variables according to their values in the COLLADA file
		newCgFXmat->setParameterValueSource(CgFXMaterial::CURRENT);

		// In the event that there are samplers/texture, we handle them separately from the uniform variables
		// for now, if we find one, we'll just push it onto a vector and handle it later.
		std::vector<domInstance_effect::domSetparamRef> samplerParams;
		std::vector<domInstance_effect::domSetparamRef> surfaceParams;
		std::vector<domInstance_effect::domSetparamRef> matrixParams;

		// now update the variables, updated values come from the setparam array
		// Supported types are those supported by the ShaderProgramVariable class
		domInstance_effect::domSetparam_Array setParams = instEffect->getSetparam_array(); 

		for(UInt32 i(0); i < setParams.getCount(); ++i)
		{	// We only handle types that CgFXMaterial handles
			// This is ugly, the collada DOM doesn't have a way to easily determine what type of parameter
			// a <setparam> is holding.  
			domFx_basic_type_commonRef curParam = setParams[i]->getFx_basic_type_common();
			if(curParam == NULL) continue;

			std::string paramName = setParams[i]->getRef();
			
			if(curParam->getBool() != NULL)
			{
				newCgFXmat->addUniformVariable(paramName.c_str(),(bool)curParam->getBool()->getValue());
			}
			else if(curParam->getInt() != NULL)
			{
				newCgFXmat->addUniformVariable(paramName.c_str(),(Int32)curParam->getInt()->getValue());
			}
			else if(curParam->getFloat() != NULL)
			{	
				newCgFXmat->addUniformVariable(paramName.c_str(),(Real32)curParam->getFloat()->getValue());
			}
			else if(curParam->getFloat2() != NULL)
			{
				Vec2f val(curParam->getFloat2()->getValue()[0],
						  curParam->getFloat2()->getValue()[1]);
				newCgFXmat->addUniformVariable(paramName.c_str(),val);
			}
			else if(curParam->getFloat3() != NULL)
			{
				
				Vec3f val(curParam->getFloat3()->getValue()[0],
						  curParam->getFloat3()->getValue()[1],
						  curParam->getFloat3()->getValue()[2]);
				newCgFXmat->addUniformVariable(paramName.c_str(),val);
			}
			else if(curParam->getFloat4() != NULL)
			{
				
				Vec3f val(curParam->getFloat4()->getValue()[0],
						  curParam->getFloat4()->getValue()[1],
						  curParam->getFloat4()->getValue()[2],
						  curParam->getFloat4()->getValue()[3]);
				newCgFXmat->addUniformVariable(paramName.c_str(),val);
			}
			else if(curParam->getFloat4x4() != NULL)
			{
				// set matrices later, after checking if they are state matrices,
				// which we don't want to set.
				matrixParams.push_back(setParams[i]);
			} 
			else if(curParam->getSurface() != NULL)
			{	// handle surfaces later...
				surfaceParams.push_back(setParams[i]);
			}
			else if(isCGSampler(curParam))
			{	// handle samplers later
				samplerParams.push_back(setParams[i]);
			} else
			{
				SWARNING << "Profile_CG variable " << paramName
						 << "'s type is not supported by CgFXMaterial, and will be ignored." 
						 << std::endl;
				
			} // end if/else chain
		}// end for(params.getCount())		

		// now checking the matrices to make sure they are not state matrices
		// before setting them
		domCg_newparam_Array newParams = prof->getNewparam_array();
		for(UInt32 i(0); i < matrixParams.size(); i++)
		{
			std::string matrixName = matrixParams[i]->getRef();
			for(UInt32 j(0); j < newParams.getCount(); j++)
			{
				std::string newParamName = newParams[j]->getSid();
				if(newParamName.compare(matrixName) == 0)
				{
					// now check the semantic property of the newParam, 
					// to see if it is a state matrix
					if(newParams[j]->getSemantic() != NULL)
					{
						if(isStateMatrix(newParams[j]->getSemantic()->getValue()))
						{ // is it a state matrix? then don't set the new values
							break;
						}
					} 
					
					domFloat4x4 val = matrixParams[i]->getFx_basic_type_common()->getFloat4x4()->getValue();
					Matrix tmp(val.get(0),val.get(1),val.get(2),val.get(3),
							   val.get(4),val.get(5),val.get(6),val.get(7),
							   val.get(8),val.get(9),val.get(10),val.get(11),
							   val.get(12),val.get(13),val.get(14),val.get(15));

					newCgFXmat->addUniformVariable(matrixName.c_str(),tmp);
					break;
					 
				} // end if(!isStateMatrix)
			} //end for(newParams.size())
		} // end for(matrixParams.size())
	
		std::map<std::string,std::string> imgPaths; //pairs from the name of the surface to its filepath

		// now we need to handle samplers/surfaces
		for(UInt32 i(0); i < surfaceParams.size(); i++)
		{

			domFx_surface_commonRef surf = surfaceParams[i]->getFx_basic_type_common()->getSurface();
			// Checking if there is an associated image to init this surface from.
			// There is no guarantee of an associated type for a <surface> in the Cg scope,
			// so we just check what the associated image is.
			domFx_surface_init_from_common_Array inits = surf->getFx_surface_init_common()->getInit_from_array();
			for(UInt32 j(0); j < inits.getCount(); j++)
			{ // there can be only one
				domImage* image = daeSafeCast<domImage>(inits[j]->getValue().getElement());
				if(image != NULL) 
				{
					imgPaths[surfaceParams[i]->getRef()] =
					//	image->getInit_from()->getValue().getURI() // can be used to get absolute filepath
						image->getInit_from()->getValue().getOriginalURI();
				}
			}
		}

		// now we update the samplers' texture references
		for(UInt32 i(0); i < samplerParams.size(); i++)
		{
			std::string sourceName;
			domFx_sampler1D_commonRef samp1d = samplerParams[i]->getFx_basic_type_common()->getSampler1D();	
			if(samp1d != NULL)
			{
				sourceName = samp1d->getSource()->getValue();
			}
			domFx_sampler2D_commonRef samp2d = samplerParams[i]->getFx_basic_type_common()->getSampler2D();	
			if(samp2d != NULL)
			{
				sourceName = samp2d->getSource()->getValue();
			}
			domFx_sampler3D_commonRef samp3d = samplerParams[i]->getFx_basic_type_common()->getSampler3D();	
			if(samp3d != NULL)
			{
				sourceName = samp3d->getSource()->getValue();
			}
			domFx_samplerCUBE_commonRef sampCube = samplerParams[i]->getFx_basic_type_common()->getSamplerCUBE();	
			if(sampCube != NULL)
			{
				sourceName = sampCube->getSource()->getValue();
			}
			domFx_samplerRECT_commonRef sampRect = samplerParams[i]->getFx_basic_type_common()->getSamplerRECT();	
			if(sampRect != NULL)
			{
				sourceName = sampRect->getSource()->getValue();
			}
			domFx_samplerDEPTH_commonRef sampDepth = samplerParams[i]->getFx_basic_type_common()->getSamplerDEPTH();	
			if(sampDepth != NULL)
			{	
				sourceName = sampDepth->getSource()->getValue();
			}
			
			std::string szFilename = imgPaths[sourceName];
			if(!szFilename.empty())
			{
				// we have the new path of the file
				// set it as a variable, so it will be initialized later
				// by the material when it is initialized
				Int32 uiSamplerId = -1;

                CgFXVariableTexObjUnrecPtr pVar = 
                    CgFXVariableTexObj::create();

                pVar->setName (samplerParams[i]->getRef());
                pVar->setValue(uiSamplerId);
				pVar->setFilePath(fixFilepath(szFilename));

                newCgFXmat->addVariable   (pVar );

			} // end if(!szFilename.empty())
		} // end for(samplerParams.size())

		// set the technique for this effect
		domInstance_effect::domTechnique_hint_Array techHnts = instEffect->getTechnique_hint_array();
		std::string techName;
		for(UInt32 i(0); i < techHnts.getCount(); i++)
		{
			// we are interested in "ref", which is the name of the technique this CgFXMaterial is to use.
			// if there are more than 1, we use the last one listed
			techName = techHnts[i]->getRef();
		}

		if(techName.compare("") != 0 && techHnts.getCount() > 0)
		{ // a name was given for which technique to use, so we will use it
			newCgFXmat->setActiveTechnique(techName);
		}
	}// end if(materialInitialized)
	
		OSG::commitChanges();

    return MaterialTransitPtr(newCgFXmat);
}

bool ColladaEffect::isCGSampler(domFx_basic_type_commonRef param)
{
		if(param->getSampler1D() != NULL ) return true;
		else if(param->getSampler2D() != NULL ) return true;
		else if(param->getSampler3D() != NULL ) return true;
		else if(param->getSamplerCUBE() != NULL ) return true;
		else if(param->getSamplerDEPTH() != NULL ) return true;
		else if(param->getSamplerRECT() != NULL ) return true;
		else return false;
}

/*
*	Checks whether a semantic represents a state matrix
*
*/
bool ColladaEffect::isStateMatrix(std::string semantic)
{
	if(semantic.length() < 4) return false; // early out

	static std::string stateMatrixNames[] = {
		"TIME","VIEWPROJECTION","VIEWINVERSETRANSPOSE","VIEWIT","VIEWINVERSE","VIEWI",
		"VIEW","MODELVIEWINVERSETRANSPOSE","MODELVIEWIT","MODELVIEWINVERSE",
		"MODELVIEWI","MODELVIEW","WORLDVIEWINVERSETRANSPOSE","WORLDVIEWIT",
		"WORLDVIEWINVERSE","WORLDVIEWI","WORLDVIEW","MODELINVERSERTRANSPOSE","MODELIT",
		"MODELINVERSE","MODELI","MODEL","WORLDINVERSETRANSPOSE","WORLDIT","WORLDINVERSE",
		"WORLDI","WORLD","MODELVIEWPROJECTION","WORLDVIEWPROJECTION","PROJECTION"
		};
	
	for(int i(0); i < 30; i++)
	{
		if( osgStringCaseCmp(stateMatrixNames[i].c_str(),semantic.c_str()) == 0 ) return true;
	}
	return false;
}

/*
 *	Generates   techniques, passes, and bindings embedded in the COLLADA file are 
 *	converting them to compileable code for the Cg compiler to use. Requires valid
 *  vertex and fragment shaders.
 */
std::string ColladaEffect::buildCgFXCode(domProfile_CG *prof)
{
	std::stringstream buf;
	buf << std::endl;
	// getting the techniques. There must be at least one
	domProfile_CG::domTechnique_Array techs = prof->getTechnique_array();
	for(UInt32 i(0); i < techs.getCount(); i++) 
	{
		buf << std::endl << "technique " << techs[i]->getSid() << " { ";
		domProfile_CG::domTechnique::domPass_Array passes = techs[i]->getPass_array();
		for(UInt32 j(0); j < passes.getCount(); j++)
		{
			
			buf << " pass " << passes[j]->getSid() << " { ";
			domProfile_CG::domTechnique::domPass::domShader* vertex = NULL;
			domProfile_CG::domTechnique::domPass::domShader* fragment = NULL;
			domProfile_CG::domTechnique::domPass::domShader_Array 
				shds = passes[j]->getShader_array();

			for(UInt32 k(0); k < shds.getCount(); k++)
			{
				if(shds[k]->getStage() == CG_PIPELINE_STAGE_FRAGMENT
					&& fragment == NULL)
				{
					fragment = shds[k];
					continue;
				}
				if(shds[k]->getStage() == CG_PIPELINE_STAGE_VERTEX
					&& vertex == NULL)
				{
					vertex = shds[k];
					continue;
				}
			}
			if(vertex == NULL || fragment == NULL) return ""; // can't continue
			
			std::string compTargV(vertex->getCompiler_target()->getCharData()),
						compNameV(vertex->getName()->getCharData());

			if(compTargV.size() == 0 || compNameV.size() == 0) return ""; // can't continue

			buf << "VertexProgram = compile " << compTargV << " " << compNameV
				<< "(" << extractCgBindParams(vertex) << "); ";

			// need to get render state information
			buf << extractCgStates(passes[j]);

			// add in fragment program stuff...  
			std::string compTargF(fragment->getCompiler_target()->getCharData()),
						compNameF(fragment->getName()->getCharData());

			if(compTargF.size() == 0 || compNameF.size() == 0) return "";

			buf << "FragmentProgram = compile " << compTargF << " " << compNameF
				<< "(" << extractCgBindParams(fragment) << ");}";
			
		}
		
		buf << " } " << std::endl;

	}
	
	return buf.str();
}

/*
*	Helper function for extracting names of parameters that need to be bound to the compilers.
*/
std::string ColladaEffect::extractCgBindParams(domProfile_CG::domTechnique::domPass::domShader* shader)
{
	std::stringstream buf;
	domProfile_CG::domTechnique::domPass::domShader::domBind_Array arr = shader->getBind_array();
	for(UInt32 i(0); i < arr.getCount(); i++)
	{
		buf << arr[i]->getParam()->getRef();
		if(i < arr.getCount() - 1) buf << ",";
	}

	return buf.str();
}

/*
*	Extracts all explicitly defined states for a given pass.  There are a LOT of different
*	states, so this function is quite long...
*
*/
std::string ColladaEffect::extractCgStates(domProfile_CG::domTechnique::domPassRef pass)
{
	std::stringstream buf;

	// rendering to texture not currently supported, may do so in the future.

	buf << " ";
	// now handle all of the possible states assignments...
	domGl_pipeline_settings_Array states = pass->getGl_pipeline_settings_array();
	int numStates = states.getCount();
	for(UInt32 i(0); i < states.getCount(); i++)
	{	
		domGl_pipeline_settings::domAlpha_funcRef af = states[i]->getAlpha_func();
		if(af != NULL)
		{
			buf << " AlphaFunc = float2(" << getFuncTypeString(af->getFunc()->getValue()) 
				<< "," << af->getValue()->getValue() << "); ";
			continue;
		}

		domGl_pipeline_settings::domBlend_funcRef bf = states[i]->getBlend_func();
		if(bf != NULL)
		{
			buf << " BlendFunc = int2(" << getBlendFuncTypeString(bf->getSrc()->getValue())
				<< "," << getBlendFuncTypeString(bf->getDest()->getValue()) << "); ";
			continue;
		}

		domGl_pipeline_settings::domBlend_func_separateRef bfs = 
			states[i]->getBlend_func_separate();
		if(bfs != NULL)
		{
			buf << " BlendFuncSeparate = int4(" 
				<< getBlendFuncTypeString(bfs->getSrc_rgb()->getValue()) << ","
				<< getBlendFuncTypeString(bfs->getDest_rgb()->getValue()) << ","
				<< getBlendFuncTypeString(bfs->getSrc_alpha()->getValue()) << ","
				<< getBlendFuncTypeString(bfs->getDest_alpha()->getValue()) << "); ";
			continue;
		}

		domGl_pipeline_settings::domBlend_equationRef ble = states[i]->getBlend_equation();
		if(ble != NULL)
		{	
			buf<< " BlendEquation = " << getBlendEquationString(ble->getValue()) << "; ";
			continue;
		}

		domGl_pipeline_settings::domBlend_equation_separateRef bles = 
			states[i]->getBlend_equation_separate();
		if(bles != NULL)
		{
			buf << " BlendEquationSeparate = int2(" << getBlendEquationString(bles->getRgb()->getValue())
				<< "," << getBlendEquationString(bles->getAlpha()->getValue()) << "); ";
			
			continue;
		}

		domGl_pipeline_settings::domDepth_funcRef df = states[i]->getDepth_func();
		if(df != NULL)
		{
			buf << " DepthFunc = " << getFuncTypeString(df->getValue()) << "; ";
			continue;
		} 

		domGl_pipeline_settings::domDepth_maskRef dm = states[i]->getDepth_mask();
		if(dm != NULL)
		{
			buf << " DepthMask = " << (dm->getValue()?("true"):("false")) << "; ";
			continue;
		}

		domGl_pipeline_settings::domColor_materialRef cm = states[i]->getColor_material();
		if(cm != NULL)
		{
			buf << " ColorMaterial = int2(" << getFaceTypeString(cm->getFace()->getValue()) 
				<< "," << getMaterialModeTypeString(cm->getMode()->getValue()) << "); ";
			continue;
		}

		domGl_pipeline_settings::domCull_faceRef cf = states[i]->getCull_face();
		if(cf != NULL)
		{
			buf << " CullFace = " << getFaceTypeString(cf->getValue())<< "; ";
			continue;
		}

		domGl_pipeline_settings::domFog_modeRef fm = states[i]->getFog_mode();
		if(fm != NULL)
		{
			std::string fogMode;
			switch(fm->getValue())
			{
			case GL_FOG_TYPE_LINEAR:
				fogMode = "Linear";
				break;
			case GL_FOG_TYPE_EXP:
				fogMode = "Exp";
				break;
			case GL_FOG_TYPE_EXP2:
				fogMode = "Exp2";
				break;
			}
			buf << " FogMode = " << fogMode << "; "; 
			continue;
		}

		domGl_pipeline_settings::domFog_coord_srcRef fcs = states[i]->getFog_coord_src();
		if(fcs != NULL)
		{	
			buf << " FogCoordSrc = " 
				<< ((fcs->getValue() == GL_FOG_COORD_SRC_TYPE_FOG_COORDINATE)?
				("FogCoord"):("FragmentDepth")) << "; ";
			continue;
		}

		domGl_pipeline_settings::domFront_faceRef ff = states[i]->getFront_face();
		if(ff != NULL)
		{
			buf << " FrontFace = " << ((ff->getValue() == GL_FRONT_FACE_TYPE_CW)?
				("CW"):("CCW")) << "; ";
			continue;
		}

		domGl_pipeline_settings::domLight_model_color_controlRef lmcc = 
			states[i]->getLight_model_color_control();
		if(lmcc != NULL)
		{
			buf << " LightModelColorControl = " 
				<< ((lmcc->getValue() == GL_LIGHT_MODEL_COLOR_CONTROL_TYPE_SINGLE_COLOR)?
					("SingleColor"):("SeparateSpecular"))  << "; ";
			continue;
		}

		domGl_pipeline_settings::domLogic_opRef lop = states[i]->getLogic_op();
		if(lop != NULL)
		{
			buf << " LogicOp = " << getLogicOpTypeString(lop->getValue()) << "; ";
			continue;
		}

		domGl_pipeline_settings::domPolygon_modeRef pm = states[i]->getPolygon_mode();
		if(pm != NULL)
		{
			std::string mode;
			switch(pm->getMode()->getValue())
			{
				case GL_POLYGON_MODE_TYPE_POINT:
					mode = "Point";
					break;
				case GL_POLYGON_MODE_TYPE_LINE:
					mode = "Line";
					break;
				case GL_POLYGON_MODE_TYPE_FILL:
					mode = "Fill";
					break;
				default:
					mode = "Fill";
			}
			buf << " PolygonMode = int2(" << getFaceTypeString(pm->getFace()->getValue())
				<< "," << mode << "); ";
			continue;
		}

		domGl_pipeline_settings::domShade_modelRef shm = states[i]->getShade_model();
		if(shm != NULL)
		{
			buf << " ShadeModel = " 
				<< ((shm->getValue() == GL_SHADE_MODEL_TYPE_FLAT)?("Flat"):("Smooth")) << "; ";
			continue;
		}

		domGl_pipeline_settings::domStencil_funcRef stf = states[i]->getStencil_func();
		if(stf != NULL)
		{	
			buf << " StencilFunc = int3(" << getFuncTypeString(stf->getFunc()->getValue()) 
				<< "," << (unsigned int)stf->getMask()->getValue() 
				<< "," << (unsigned int)stf->getRef()->getValue() << "); ";

			continue;
		}

		domGl_pipeline_settings::domStencil_opRef sto = states[i]->getStencil_op();
		if(sto != NULL)
		{
			buf << " StencilOp = int3(" << getStencilOpTypeString(sto->getZfail()->getValue())
				<< "," << getStencilOpTypeString(sto->getFail()->getValue())
				<< "," << getStencilOpTypeString(sto->getZpass()->getValue()) << "); ";

			continue;
		}

		domGl_pipeline_settings::domStencil_op_separateRef stos = 
			states[i]->getStencil_op_separate();
		if(stos != NULL)
		{
			buf << " StencilOpSeparate = int4(" << getFaceTypeString(stos->getFace()->getValue())
				<< "," << getStencilOpTypeString(stos->getZfail()->getValue())
				<< "," << getStencilOpTypeString(stos->getFail()->getValue())
				<< "," << getStencilOpTypeString(stos->getZpass()->getValue()) << "); ";
			continue;

		}
	
		domGl_pipeline_settings::domStencil_mask_separateRef stms = 
			states[i]->getStencil_mask_separate();
		if(stms != NULL)
		{
			buf << " StencilMaskSeparate = (" << getFaceTypeString(stms->getFace()->getValue())
				<< "," << (unsigned int)stms->getMask()->getValue() << "); ";
			continue;
		}

		domGl_pipeline_settings::domLight_ambientRef la = states[i]->getLight_ambient();
		if(la != NULL)
		{
			domFloat4 ambient = la->getValue();
			buf << " LightAmbient" << "[" << la->getIndex() << "] = float4(" << ambient[0] 
				<< "," << ambient[1] << "," << ambient[2] << "," << ambient[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLight_diffuseRef ld = states[i]->getLight_diffuse();
		if(ld != NULL)
		{
			domFloat4 diffuse = ld->getValue();
			buf << " LightDiffuse" << "[" << ld->getIndex() << "] = float4(" << diffuse[0] 
				<< "," << diffuse[1] << "," << diffuse[2] << "," << diffuse[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLight_specularRef ls = states[i]->getLight_specular();
		if(ld != NULL)
		{
			domFloat4 specular = ls->getValue();
			buf << " LightSpecular" << "[" << ls->getIndex() << "] = float4(" << specular[0] 
				<< "," << specular[1] << "," << specular[2] << "," << specular[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLight_positionRef lp = states[i]->getLight_position();
		if(lp != NULL)
		{
			domFloat4 position = lp->getValue();
			buf << " LightPosition" << "[" << lp->getIndex() << "] = float4(" << position[0] 
				<< "," << position[1] << "," << position[2] << "," << position[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLight_constant_attenuationRef lca = 
			states[i]->getLight_constant_attenuation();
		if(lca != NULL)
		{
			buf << " LightConstantAttenuation" << "[" << lca->getIndex() << "] = " 
				<< lca->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domLight_linear_attenuationRef lla = 
			states[i]->getLight_linear_attenuation();
		if(lla != NULL)
		{
			buf << " LightLinearAttenuation" << "[" << lla->getIndex() << "] = " 
				<< lla->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domLight_quadratic_attenuationRef lqa = 
			states[i]->getLight_quadratic_attenuation();
		if(lqa != NULL)
		{
			buf << " LightQuadraticAttenuation" << "[" << lqa->getIndex() << "] = " 
				<< lqa->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domLight_spot_cutoffRef lsc = 
			states[i]->getLight_spot_cutoff();
		if(lsc != NULL)
		{
			buf << " LightSpotCutoff" << "[" << lsc->getIndex() << "] = " 
				<< lsc->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domLight_spot_exponentRef lse = 
			states[i]->getLight_spot_exponent();
		if(lse != NULL)
		{
			buf << " LightSpotExponent" << "[" << lse->getIndex() << "] = " 
				<< lse->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domLight_spot_directionRef lsd = 
			states[i]->getLight_spot_direction();
		if(lsd != NULL)
		{
			domFloat3 direction = lsd->getValue();
			buf << " LightSpotDirection" << "[" << lsd->getIndex() << "] = float3(" << direction[0] 
				<< "," << direction[1] << "," << direction[2] << "); ";
			continue;
		}
	
		domGl_pipeline_settings::domClip_planeRef cp = states[i]->getClip_plane();
		if(cp != NULL)
		{
			domFloat4 clip = cp->getValue();
			buf << " ClipPlane" << cp->getIndex() << " = float4(" << clip[0]
				<< "," << clip[1] << "," << clip[2] << "," << clip[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domBlend_colorRef bc = states[i]->getBlend_color();
		if(bc != NULL)
		{
			domFloat4 color = bc->getValue();
			buf << " BlendColor = float4(" << color[0] << "," << color[1] 
				<< "," << color[2] << "," << color[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domClear_colorRef cc = states[i]->getClear_color();
		if(cc != NULL)
		{
			domFloat4 color = cc->getValue();
			buf << " ClearColor = float4(" << color[0] << "," << color[1]
				<< "," << color[2] << "," << color[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domClear_stencilRef cs = states[i]->getClear_stencil();
		if(cs != NULL)
		{
			buf << " ClearStencil = " << cs->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domClear_depthRef cd = states[i]->getClear_depth();
		if(cd != NULL)
		{
			buf << " ClearDepth = " << cd->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domColor_maskRef cmk = states[i]->getColor_mask();
		if(cmk != NULL)
		{
			domBool4 mask = cmk->getValue();
			buf << " ColorMask = bool4(" << ((mask[0])?("true"):("false")) << ","
				<< ((mask[1])?("true"):("false")) << "," << ((mask[2])?("true"):("false")) 
				<< "," << ((mask[3])?("true"):("false")) << "); ";
			continue;
		}

		domGl_pipeline_settings::domDepth_boundsRef db = states[i]->getDepth_bounds();
		if(db != NULL)
		{
			domFloat2 bounds = db->getValue();
			buf << " DepthBounds = float2( " << bounds[0] << "," << bounds[1] << "); ";
			continue;
		}


		domGl_pipeline_settings::domDepth_rangeRef dr = states[i]->getDepth_range();
		if(dr != NULL)
		{
			domFloat2 range = dr->getValue();
			buf << " DepthRange = float2( " << range[0] << "," << range[1] << "); ";	
			continue;
		}

		domGl_pipeline_settings::domFog_densityRef fd = states[i]->getFog_density();
		if(fd != NULL)
		{
			buf << " FogDensity = " << fd->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domFog_startRef fs = states[i]->getFog_start();
		if(fs != NULL)
		{
			buf << " FogStart= " << fs->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domFog_endRef fe = states[i]->getFog_end();
		if(fe != NULL)
		{
			buf << " FogEnd= " << fe->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domFog_colorRef fc = states[i]->getFog_color();
		if(fc != NULL)
		{
			domFloat4 color = fc->getValue();
			buf << " FogColor = float4(" << color[0] << "," << color[1] 
				<< "," << color[2] << "," << color[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLight_model_ambientRef lma = 
			states[i]->getLight_model_ambient();
		if(lma != NULL)
		{
			domFloat4 light = lma->getValue();
			buf << " LightModelAmbient = float4(" << light[0] << "," << light[1] 
				<< "," << light[2] << "," << light[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLine_stippleRef lst = states[i]->getLine_stipple();
		if(lst != NULL)
		{
			domInt2 stipple = lst->getValue();
			buf << " LineStipple = int2(" << stipple[0] << "," << stipple[1] << "); ";
			continue;
		}

		domGl_pipeline_settings::domLine_widthRef lw = states[i]->getLine_width();
		if(lw != NULL)
		{
			buf << " LineWidth = " << lw->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domMaterial_ambientRef mam = states[i]->getMaterial_ambient();
		if(mam != NULL)
		{
			domFloat4 ambient = mam->getValue();
			buf << " MaterialAmbient = float4(" << ambient[0] << "," << ambient[1] 
				<< "," << ambient[2] << "," << ambient[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domMaterial_diffuseRef mdf = states[i]->getMaterial_diffuse();
		if(mdf != NULL)
		{
			domFloat4 diffuse = mdf->getValue();
			buf << " MaterialDiffuse = float4(" << diffuse[0] << "," << diffuse[1] 
				<< "," << diffuse[2] << "," << diffuse[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domMaterial_emissionRef mem = states[i]->getMaterial_emission();
		if(mem != NULL)
		{
			domFloat4 emission = mem->getValue();
			buf << " MaterialEmission = float4(" << emission[0] << "," << emission[1] 
				<< "," << emission[2] << "," << emission[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domMaterial_specularRef msp = states[i]->getMaterial_specular();
		if(msp != NULL)
		{
			domFloat4 spec = msp->getValue();
			buf << " MaterialSpecular = float4(" << spec[0] << "," << spec[1] 
				<< "," << spec[2] << "," << spec[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domMaterial_shininessRef msh = states[i]->getMaterial_shininess();
		if(msh != NULL)
		{
			buf << " MaterialShininess = " << msh->getValue() << "; ";
			continue;
		}
		
		domGl_pipeline_settings::domPoint_distance_attenuationRef pda = 
			states[i]->getPoint_distance_attenuation();
		if(pda != NULL)
		{
			domFloat3 atten = pda->getValue();
			buf << " PointDistanceAttenuation = float3(" << atten[0] << "," 
				<< atten[1] << "," << atten[2]  << "); ";
			continue;
		}
		
		domGl_pipeline_settings::domPoint_fade_threshold_sizeRef pfts = 
			states[i]->getPoint_fade_threshold_size();
		if(pfts != NULL)
		{
			buf << " PointFadeThresholdSize = " << pfts->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domPoint_sizeRef pts = states[i]->getPoint_size();
		if(pts != NULL)
		{
			buf << " PointSize = " << pts->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domPoint_size_minRef ptsmn = states[i]->getPoint_size_min();
		if(ptsmn != NULL)
		{
			buf << " PointSizeMin = " << ptsmn->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domPoint_size_maxRef ptsmx = states[i]->getPoint_size_max();
		if(ptsmx != NULL)
		{
			buf << " PointSizeMax = " << ptsmx->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domPolygon_offsetRef po = states[i]->getPolygon_offset();
		if(po != NULL)
		{
			domFloat2 offset = po->getValue();
			buf << " PolygonOffset = float2(" << offset[0] << "," << offset[1] << "); ";
			continue;
		}

		domGl_pipeline_settings::domScissorRef sc = states[i]->getScissor();
		if(sc != NULL)
		{	
			domInt4 scissor = sc->getValue();
			buf << " Scissor = int4(" << scissor[0] << "," << scissor[1] << "," 
				<< scissor[2] << "," << scissor[3] << "); ";
			continue;
		}

		domGl_pipeline_settings::domModel_view_matrixRef mvm = states[i]->getModel_view_matrix();
		if(mvm != NULL)
		{
			domFloat4x4 mat = mvm->getValue();
			buf << " ModelViewMatrix = float4x4(" << mat[0] << "," << mat[1]
				<< mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
				<< mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
				<< mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
				<< mat[2] << "," << mat[2] << "); "; 
			continue;
		}

		domGl_pipeline_settings::domProjection_matrixRef pjm = states[i]->getProjection_matrix();
		if(pjm != NULL)
		{
			domFloat4x4 mat = pjm->getValue();
			buf << " ProjectionMatrix = float4x4(" << mat[0] << "," << mat[1]
				<< mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
				<< mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
				<< mat[2] << "," << mat[2] << "," << mat[2] << "," << mat[2] << "," 
				<< mat[2] << "," << mat[2] << "); "; 
			continue;
		}

		domGl_pipeline_settings::domStencil_maskRef stm = states[i]->getStencil_mask();
		if(stm != NULL)
		{
			buf << " StencilMask = " << stm->getValue() << "; ";
			continue;
		}

		domGl_pipeline_settings::domClip_plane_enableRef cpe = states[i]->getClip_plane_enable();
		if(cpe != NULL)
		{
			buf << getBoolStringRep("ClipPlaneEnable",cpe->getIndex(),cpe->getValue());
			continue;
		}

		domGl_pipeline_settings::domLight_enableRef le = states[i]->getLight_enable();
		if(le != NULL)
		{
			buf << getBoolStringRep("LightEnable", le->getIndex(),le->getValue());
			continue;
		}

		domGl_pipeline_settings::domLighting_enableRef len = states[i]->getLighting_enable();
		if(len != NULL)
		{
			buf << getBoolStringRep("LightingEnable", len->getValue());
			continue;
		}

		domGl_pipeline_settings::domDepth_test_enableRef dte = states[i]->getDepth_test_enable();
		if(dte != NULL)
		{
			buf << getBoolStringRep("DepthTestEnable", dte->getValue());
			continue;
		}

		domGl_pipeline_settings::domAlpha_test_enableRef ate = states[i]->getAlpha_test_enable();
		if(ate != NULL)
		{
			buf << getBoolStringRep("AlphaTestEnable",ate->getValue());
			continue;
		}

		domGl_pipeline_settings::domAuto_normal_enableRef ane = 
			states[i]->getAuto_normal_enable();
		if(ane != NULL)
		{
			buf << getBoolStringRep("AutoNormalEnable", ane->getValue());
			continue;
		}

		domGl_pipeline_settings::domColor_logic_op_enableRef cloe = 
			states[i]->getColor_logic_op_enable();
		if(cloe != NULL)
		{
			buf << getBoolStringRep("ColorLogicOpEnable", cloe->getValue());
			continue;
		}

		domGl_pipeline_settings::domColor_material_enableRef cme = 
			states[i]->getColor_material_enable();
		if(cme != NULL)
		{
			buf << getBoolStringRep("ColorMaterialEnable", cme->getValue());
			continue;
		}

		domGl_pipeline_settings::domBlend_enableRef be = states[i]->getBlend_enable();
		if(be != NULL)
		{
			buf << getBoolStringRep("BlendEnable", be->getValue());
			continue;
		}

		domGl_pipeline_settings::domCull_face_enableRef cfe = states[i]->getCull_face_enable();
		if(cfe != NULL)
		{
			buf << getBoolStringRep("CullFaceEnable", cfe->getValue());
			continue;
		}

		domGl_pipeline_settings::domDepth_bounds_enableRef dbe = 
			states[i]->getDepth_bounds_enable();
		if(dbe != NULL)
		{
			buf << getBoolStringRep("DepthBoundsEnable", dbe->getValue());
			continue;
		}

		domGl_pipeline_settings::domDither_enableRef dthe = states[i]->getDither_enable();
		if(dthe != NULL)
		{
			buf << getBoolStringRep("DitherEnable", dthe->getValue());
			continue;
		}

		domGl_pipeline_settings::domFog_enableRef foge = states[i]->getFog_enable();
		if(foge != NULL)
		{
			buf << getBoolStringRep("FogEnable", foge->getValue());
			continue;
		}

		domGl_pipeline_settings::domLight_model_local_viewer_enableRef lmlve = 
			states[i]->getLight_model_local_viewer_enable();
		if(lmlve != NULL)
		{
			buf << getBoolStringRep("LightModelLocalViewerEnable", lmlve->getValue());
			continue;
		}

		domGl_pipeline_settings::domLight_model_two_side_enableRef lmtse = 
			states[i]->getLight_model_two_side_enable();
		if(lmtse != NULL)
		{
			buf << getBoolStringRep("LightModelTwoSideEnable", lmtse->getValue());
			continue;
		}

		domGl_pipeline_settings::domLine_smooth_enableRef lnse = states[i]->getLine_smooth_enable();
		if(lnse != NULL)
		{
			buf << getBoolStringRep("LineSmoothEnable", lnse->getValue());
			continue;
		}

		domGl_pipeline_settings::domLine_stipple_enableRef lnste = states[i]->getLine_stipple_enable();
		if(lnste != NULL)
		{
			buf << getBoolStringRep("LineStippleEnable", lnste->getValue());
			continue;
		}

		domGl_pipeline_settings::domLogic_op_enableRef lope = states[i]->getLogic_op_enable();
		if(lope != NULL)
		{
			buf << getBoolStringRep("LogicOpEnable", lope->getValue());
			continue;
		}

		domGl_pipeline_settings::domMultisample_enableRef mse = states[i]->getMultisample_enable();
		if(mse != NULL)
		{
			buf << getBoolStringRep("MultisampleEnable", mse->getValue());
			continue;
		}

		domGl_pipeline_settings::domNormalize_enableRef nme = states[i]->getNormalize_enable();
		if(nme != NULL)
		{
			buf << getBoolStringRep("NormalizeEnable", nme->getValue());
			continue;
		}

		domGl_pipeline_settings::domPoint_smooth_enableRef ptse = states[i]->getPoint_smooth_enable();
		if(ptse != NULL)
		{
			buf << getBoolStringRep("PointSmoothEnable", ptse->getValue());
			continue;
		}

		domGl_pipeline_settings::domPolygon_offset_fill_enableRef pofe  = states[i]->getPolygon_offset_fill_enable();
		if(pofe != NULL)
		{
			buf << getBoolStringRep("PolygonOffsetFillEnable", pofe->getValue());
			continue;
		}

		domGl_pipeline_settings::domPolygon_offset_line_enableRef pole = 
			states[i]->getPolygon_offset_line_enable();
		if(pole != NULL)
		{
			buf << getBoolStringRep("PolygonOffsetLineEnable", pole->getValue());
			continue;
		}

		domGl_pipeline_settings::domPolygon_offset_point_enableRef pope = 
			states[i]->getPolygon_offset_point_enable();
		if(pope != NULL)
		{
			buf << getBoolStringRep("PolygonOffsetPointEnable", pope->getValue());
			continue;
		}

		domGl_pipeline_settings::domPolygon_smooth_enableRef pse = 
			states[i]->getPolygon_smooth_enable();
		if(pse != NULL)
		{
			buf << getBoolStringRep("PolygonSmoothEnable", pse->getValue());
			continue;
		}

		domGl_pipeline_settings::domPolygon_stipple_enableRef pste = states[i]->getPolygon_stipple_enable();
		if(pste != NULL)
		{
			buf << getBoolStringRep("PolygonStippleEnable", pste->getValue());
			continue;
		}

		domGl_pipeline_settings::domRescale_normal_enableRef rne  = states[i]->getRescale_normal_enable();
		if(rne != NULL)
		{
			buf << getBoolStringRep("RescaleNormalEnable", rne->getValue());
			continue;
		}

		domGl_pipeline_settings::domSample_alpha_to_coverage_enableRef satce = 
			states[i]->getSample_alpha_to_coverage_enable();
		if(satce != NULL)
		{
			buf << getBoolStringRep("SampleAlphaToCoverageEnable", satce->getValue());
			continue;
		}

		domGl_pipeline_settings::domSample_alpha_to_one_enableRef satoe = 
			states[i]->getSample_alpha_to_one_enable();
		if(satoe != NULL)
		{
			buf << getBoolStringRep("SampleAlphaToOneEnable", satoe->getValue());
			continue;
		}

		domGl_pipeline_settings::domSample_coverage_enableRef sce = 
			states[i]->getSample_coverage_enable();
		if(sce != NULL)
		{
			buf << getBoolStringRep("SampleCoverageEnable", sce->getValue());
			continue;
		}

		domGl_pipeline_settings::domScissor_test_enableRef scte = states[i]->getScissor_test_enable();
		if(scte != NULL)
		{
			buf << getBoolStringRep("ScissorTestEnable", scte->getValue());
			continue;
		}

		domGl_pipeline_settings::domStencil_test_enableRef stte  = states[i]->getStencil_test_enable();
		if(stte != NULL)
		{
			buf << getBoolStringRep("StencilTestEnable", stte->getValue());
			continue;
		}

		domGl_pipeline_settings::domTexture1D_enableRef t1de  = states[i]->getTexture1D_enable();
		if(t1de != NULL)
		{
			buf << getBoolStringRep("Texture1DEnable", t1de->getIndex() ,t1de->getValue());
			continue;
		}

		domGl_pipeline_settings::domTexture2D_enableRef t2de  = states[i]->getTexture2D_enable();
		if(t2de != NULL)
		{
			buf << getBoolStringRep("Texture2DEnable", t2de->getIndex(),t2de->getValue());
			continue;
		}

		domGl_pipeline_settings::domTexture3D_enableRef t3de = states[i]->getTexture3D_enable();
		if(t3de != NULL)
		{
			buf << getBoolStringRep("Texture3DEnable", t3de->getIndex(), t3de->getValue());
			continue;
		}

		domGl_pipeline_settings::domTextureRECT_enableRef trde = states[i]->getTextureRECT_enable();
		if(trde != NULL)
		{
			buf << getBoolStringRep("TextureRectangleEnable", trde->getIndex(), trde->getValue());
			continue;
		}

		domGl_pipeline_settings::domTextureCUBE_enableRef tcme  = states[i]->getTextureCUBE_enable();
		if(tcme != NULL)
		{
			buf << getBoolStringRep("TextureCubeMapEnable", tcme->getIndex(), tcme->getValue());
			continue;
		}

		buf << std::endl;
	} // end for(states.getCount())

	return buf.str();
}

std::string ColladaEffect::getBoolStringRep(std::string stateName, UInt32 idx, bool state)
{
	std::stringstream buf;
	buf << stateName << "[" << idx << "] = " << ((state)?("true"):("false")) << "; ";
	return buf.str();
}

std::string ColladaEffect::getBoolStringRep(std::string stateName, bool state)
{
	if(state) return stateName.append(" = true; ");
	else return stateName.append(" = false; ");
}

std::string ColladaEffect::getStencilOpTypeString(domGl_stencil_op_type stopType)
{
	std::string stopVal;
	switch(stopType)
	{
		case GL_STENCIL_OP_TYPE_KEEP:
			stopVal = "Keep";
			break;
		case GL_STENCIL_OP_TYPE_ZERO:
			stopVal = "Zero";
			break;
		case GL_STENCIL_OP_TYPE_REPLACE:
			stopVal = "Replace";
			break;
		case GL_STENCIL_OP_TYPE_INCR:
			stopVal = "Incr";
			break;
		case GL_STENCIL_OP_TYPE_DECR:
			stopVal = "Decr";
			break;
		case GL_STENCIL_OP_TYPE_INVERT:
			stopVal = "Invert";
			break;
		case GL_STENCIL_OP_TYPE_INCR_WRAP:
			stopVal = "IncrWrap";
			break;
		case GL_STENCIL_OP_TYPE_DECR_WRAP:
			stopVal = "DecrWrap";
			break;
		default:
			stopVal = "Keep";
	}
	return stopVal;
}

std::string ColladaEffect::getLogicOpTypeString(domGl_logic_op_type logicOp)
{
	std::string logicOpType;
	switch(logicOp)
	{
	case GL_LOGIC_OP_TYPE_CLEAR:
		logicOpType = "Clear";
		break;
	case GL_LOGIC_OP_TYPE_AND: 
		logicOpType = "And";
		break;
	case GL_LOGIC_OP_TYPE_AND_REVERSE:
		logicOpType = "AndReverse";
		break;	
	case GL_LOGIC_OP_TYPE_COPY: 
		logicOpType = "Copy";
		break;	
	case GL_LOGIC_OP_TYPE_AND_INVERTED: 
		logicOpType = "AndInverted";
		break;	
	case GL_LOGIC_OP_TYPE_NOOP: 
		logicOpType = "Noop";
		break;	
	case GL_LOGIC_OP_TYPE_XOR: 
		logicOpType = "Xor";
		break;	
	case GL_LOGIC_OP_TYPE_OR:
		logicOpType = "Or";
		break;	
	case GL_LOGIC_OP_TYPE_NOR:
		logicOpType = "Nor";
		break;	
	case GL_LOGIC_OP_TYPE_EQUIV:
		logicOpType = "Equiv";
		break;	
	case GL_LOGIC_OP_TYPE_INVERT:
		logicOpType = "Invert";
		break;	
	case GL_LOGIC_OP_TYPE_OR_REVERSE:
		logicOpType = "OrReverse";
		break;	
	case GL_LOGIC_OP_TYPE_COPY_INVERTED:
		logicOpType = "CopyInverted";
		break;	
	case GL_LOGIC_OP_TYPE_NAND:
		logicOpType = "Nand";
		break;	
	case GL_LOGIC_OP_TYPE_SET:
		logicOpType = "Set";
		break;
	default:
		logicOpType = "Or";
	}

	return logicOpType;
}
std::string ColladaEffect::getMaterialModeTypeString(domGl_material_type mat)
{
	std::string matVal;
	switch(mat)
	{
	case GL_MATERIAL_TYPE_EMISSION:
		matVal = "Emission";
		break;
	case GL_MATERIAL_TYPE_AMBIENT:
		matVal = "Ambient";
		break;
	case GL_MATERIAL_TYPE_DIFFUSE:
		matVal = "Diffuse";
		break;
	case GL_MATERIAL_TYPE_SPECULAR:
		matVal = "Specular";
		break;
	case GL_MATERIAL_TYPE_AMBIENT_AND_DIFFUSE:
		matVal = "AmbientAndDiffuse";
		break;
	}

	return matVal;
}

std::string ColladaEffect::getFaceTypeString(domGl_face_type face)
{
	std::string faceVal;
	switch(face)
	{
	case GL_FACE_TYPE_FRONT:
		faceVal = "Front";
		break;
	case GL_FACE_TYPE_BACK:
		faceVal = "Back";
		break;
	case GL_FACE_TYPE_FRONT_AND_BACK:
		faceVal = "FrontAndBack";
		break;
	default:
		faceVal = "Back";
	}
	return faceVal;
}

/*
*	Gets the string equivalent representation of a domGl_func_type needed by the Cg compiler.
*/
std::string ColladaEffect::getFuncTypeString(domGl_func_type func)
{
	std::string funcVal;
	switch(func)
	{
	case GL_FUNC_TYPE_NEVER :
		funcVal = "Never";
		break;
	case GL_FUNC_TYPE_LESS:
		funcVal = "Less";
		break;
	case GL_FUNC_TYPE_LEQUAL:
		funcVal = "LEqual";
		break;
	case GL_FUNC_TYPE_EQUAL: 
		funcVal = "Equal";
		break;
	case GL_FUNC_TYPE_GREATER: 
		funcVal = "Greater";
		break;
	case GL_FUNC_TYPE_NOTEQUAL:
		funcVal = "NotEqual";
		break;
	case GL_FUNC_TYPE_GEQUAL:
		funcVal = "GEqual";
		break;
	case GL_FUNC_TYPE_ALWAYS:
		funcVal = "Always";
		break;
	case GL_FUNC_TYPE_COUNT:
		funcVal = "Count";
		break;
	default:
		funcVal = "LEqual";
	} // end switch
	return funcVal;
}

std::string ColladaEffect::getBlendFuncTypeString(domGl_blend_type func)
{
	std::string funcVal;
	switch(func)
	{
	case GL_BLEND_TYPE_ZERO:
		funcVal = "Zero";
		break;
	case GL_BLEND_TYPE_ONE:
		funcVal = "One";
		break;
	case GL_BLEND_TYPE_SRC_COLOR:
		funcVal = "SrcColor";
		break;
	case GL_BLEND_TYPE_ONE_MINUS_SRC_COLOR:
		funcVal = "OneMinusSrcAlpha";
		break;
	case GL_BLEND_TYPE_DEST_COLOR:
		funcVal = "DestColor";
		break;
	case GL_BLEND_TYPE_ONE_MINUS_DEST_COLOR:
		funcVal = "OneMinusDestColor";
		break;
	case GL_BLEND_TYPE_SRC_ALPHA:
		funcVal = "SrcAlpha";
		break;
	case GL_BLEND_TYPE_ONE_MINUS_SRC_ALPHA:
		funcVal = "OneMinusSrcAlpha";
		break;
	case GL_BLEND_TYPE_DST_ALPHA:
		funcVal = "DstAlpha";
		break;
	case GL_BLEND_TYPE_ONE_MINUS_DST_ALPHA:
		funcVal = "OneMinusDstAlpha";
		break;
	case GL_BLEND_TYPE_CONSTANT_COLOR:
		funcVal = "ConstantColor";
		break;
	case GL_BLEND_TYPE_ONE_MINUS_CONSTANT_COLOR:
		funcVal = "OneMinusConstantColor";
		break;
	case GL_BLEND_TYPE_CONSTANT_ALPHA:
		funcVal = "ConstantAlpha";
		break;
	case GL_BLEND_TYPE_ONE_MINUS_CONSTANT_ALPHA:
		funcVal = "OneMinusConstantAlpha";
		break;
	case GL_BLEND_TYPE_SRC_ALPHA_SATURATE:
		funcVal = "SrcAlphaSaturate";
		break;
	default:
		funcVal = "Zero";
	}

	return funcVal;
}


std::string ColladaEffect::getBlendEquationString(domGl_blend_equation_type eq)
{
	std::string eqVal;
	switch(eq)
	{
	case GL_BLEND_EQUATION_TYPE_FUNC_ADD: 
		eqVal = "FuncAdd";
		break;
	case GL_BLEND_EQUATION_TYPE_FUNC_SUBTRACT:
		eqVal = "FuncSubtract";
		break;
	case GL_BLEND_EQUATION_TYPE_FUNC_REVERSE_SUBTRACT: 
		eqVal = "FuncReverseSubtract";
		break;
	case GL_BLEND_EQUATION_TYPE_MIN:
		eqVal = "Min";
		break;
	case GL_BLEND_EQUATION_TYPE_MAX:
		eqVal = "Max";
		break;
	default:
		eqVal = "FuncAdd";
	}
	return eqVal;
}

/* 
 * Helper function for de-mangling filepaths.  Removes leading filepath separators and 
 * replaces escaped url characters (i.e. "%20" with " " (a single space))
 */
std::string ColladaEffect::fixFilepath(std::string filepath)
{	

	std::string escaped[] = {"%20", "%22", "%3C", "%3E", "%23", "%25", "%7B", 
					"%7D", "%7C", "%5E", "%7E", "%5B", "%5D", "%60"};

	std::string replacements[] = {" ","\"","<",">","#","%","{",
							 "}","|","^","~","[","]","`"};
	// removing leading file path separators
	while(filepath[0] == '/' || filepath[0] == '\\')
	{
		filepath = filepath.substr(1);
	}
	// remove escaped characters and replace
	size_t pos = 0;
	for(int i(0); i < 14; i++)
	{
		for(;;)
		{
			pos = filepath.find(escaped[i], pos);
			if( pos == std::string::npos) break;
			else filepath = filepath.replace(pos,3,replacements[i]);
		}
	}
	return filepath;
}

// re-formats an image filepath so that it can be read properly
std::string	ColladaEffect::fixImageFilepath( std::string imgPath)
{
	if(imgPath.substr(0,5) == "file:")
	{
		imgPath = imgPath.substr(4);
		imgPath = fixFilepath(imgPath);
	}
	return fixFilepath(imgPath);
}


OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
