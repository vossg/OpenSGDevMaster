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

#include <OSGColladaEffect.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaGlobal.h>
#include <OSGColladaImage.h>
#include <OSGColladaSampler2D.h>

#include <OSGImage.h>
#include <OSGBlendChunk.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGTextureObjChunk.h>

#include <1.4/dom/domEffect.h>
#include <1.4/dom/domProfile_COMMON.h>
#include <1.4/dom/domProfile_GLSL.h>
#include <1.4/dom/domProfile_CG.h>

OSG_BEGIN_NAMESPACE

void ColladaEffect::read(void)
{
    OSG_COLLADA_LOG(("ColladaEffect::read:\n"));

    domEffectRef effect = getDOMElementAs<domEffect>();

    if(effect == NULL)
        return;
    
    OSG_COLLADA_LOG(("ColladaEffect::read: <effect> [%s] [%s]\n",
                     effect->getId(), effect->getDocumentURI()->getURI()));

    UInt32 numProfiles =
        effect->getFx_profile_abstract_array().getCount();

    OSG_COLLADA_LOG(("ColladaEffect::read: profiles [%u]\n", numProfiles));

    for(UInt32 i = 0; i < numProfiles; ++i)
    {
        OSG_COLLADA_LOG(("ColladaEffect::read: profile [%u] [%s]\n",
                         i, effect->getFx_profile_abstract_array()[i]->getTypeName()));

        domProfile_COMMONRef profCommon =
            daeSafeCast<domProfile_COMMON>(
                effect->getFx_profile_abstract_array()[i]);

        domProfile_GLSLRef   profGLSL   =
            daeSafeCast<domProfile_GLSL>(
                effect->getFx_profile_abstract_array()[i]);

        domProfile_CGRef     profCG     =
            daeSafeCast<domProfile_CG>(
                effect->getFx_profile_abstract_array()[i]);
        
        if(profCommon != NULL)
        {
            handleCommonProfile(profCommon);
        }
        else if(profGLSL != NULL)
        {
            handleGLSLProfile(profGLSL);
        }
        else if(profCG != NULL)
        {
            handleCGProfile(profCG);
        }
        else
        {
            FWARNING(("ColladaEffect::read: Unknown profile.\n"));
        }
    }
}

domFx_surface_common *ColladaEffect::getSurface(const std::string &ref)
{
    domFx_surface_common *returnValue = NULL;

    SurfaceMap::iterator surfIt = _surfaceMap.find(ref);

    if(surfIt != _surfaceMap.end())
    {
        returnValue = surfIt->second;
    }

    return returnValue;
}

UInt32 ColladaEffect::getTexBinding(const std::string &ref)
{
    UInt32 returnValue = 0xFFFF;

    for(UInt32 i = 0; i < _texCoordMapping.size(); ++i)
    {
        if(_texCoordMapping[i] == ref)
        {
            returnValue = i;
            break;
        }
    }

    return returnValue;
}


ColladaEffect::ColladaEffect(domEffect *effect, ColladaGlobal *global)

    : Inherited(effect, global)
{
    // nothing to do
}

ColladaEffect::~ColladaEffect(void)
{
    // nothing to do
}

void ColladaEffect::handleCommonProfile(domProfile_COMMON *profCommon)
{
    OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile:\n"));
    
    domProfile_COMMON::domTechniqueRef technique = profCommon->getTechnique();

    if(technique == NULL)
        return;
    
    if(_material == NULL)
        _material = ChunkMaterial::create();
    
    const domCommon_newparam_type_Array &params =
        profCommon->getNewparam_array();

    OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile: num params [%u]\n",
                     params.getCount()));

    for(UInt32 i = 0; i < params.getCount(); ++i)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile: param [%d] sid [%s]\n",
                         i, params[i]->getSid()));

        if(params[i]->getSurface() != NULL)
        {
            _surfaceMap[params[i]->getSid()] = params[i]->getSurface();
        }

        if(params[i]->getSampler2D() != NULL)
        {
            _samplerMap[params[i]->getSid()] = params[i]->getSampler2D();
        }
    }

    if(technique->getConstant() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile: technique constant\n"));
        
        FWARNING(("ColladaEffect::handleCommonProfile: technique constant NIY\n"));
    }
    else if(technique->getLambert() != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile: technique lambert\n"));
        
        setupSimpleColorAndTex(technique->getLambert());
    }
    else if(technique->getPhong())
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile: technique phong\n"));

        setupSimpleSpecColorAndTex(technique->getPhong());
    }
    else if(technique->getBlinn())
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleCommonProfile: technique blinn\n"));

        setupSimpleSpecColorAndTex(technique->getBlinn());
    }
    else
    {
        FWARNING(("ColladaEffect::handleCommonProfile: Unknown technique.\n"));
    }
}

void ColladaEffect::handleGLSLProfile(domProfile_GLSL *profGLSL)
{
    FWARNING(("ColladaEffect::handleGLSLProfile: NIY\n"));
}

void ColladaEffect::handleCGProfile(domProfile_CG *profCG)
{
    FWARNING(("ColladaEffect::handleCGProfile: NIY\n"));
}

template <class TechTypeT>
void ColladaEffect::setupSimpleColorAndTex(
    TechTypeT   tech,
    DomFloat   *shininess,
    DomColor   *specularCol,
    DomTexture *specularTex )
{
    OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex:\n"));
    
    if(tech == NULL)
        return;

    domCommon_color_or_texture_type::domColorRef   diffuseCol  = NULL;
    domCommon_color_or_texture_type::domTextureRef diffuseTex  = NULL;
    
    domCommon_color_or_texture_type::domColorRef   ambientCol  = NULL;
    domCommon_color_or_texture_type::domTextureRef ambientTex  = NULL;
       
    domCommon_color_or_texture_type::domColorRef   emissionCol = NULL;
    domCommon_color_or_texture_type::domTextureRef emissionTex = NULL;

    domCommon_color_or_texture_type::domColorRef   transCol    = NULL;
    domCommon_color_or_texture_type::domTextureRef transTex    = NULL;
    
    fillElements(tech->getDiffuse    (), diffuseCol,  diffuseTex );
    fillElements(tech->getAmbient    (), ambientCol,  ambientTex );
    fillElements(tech->getEmission   (), emissionCol, emissionTex);
    fillElements(tech->getTransparent(), transCol,    transTex   );

    domCommon_float_or_param_typeRef transparency =
        tech->getTransparency();

    Real32 shininessVal    = 10.f;
    Real32 transparencyVal =  1.f;
    
    if(shininess != NULL && shininess->getFloat() != NULL)
        shininessVal = shininess->getFloat()->getValue();

    if(transparency != NULL && transparency->getFloat() != NULL)
        transparencyVal = transparency->getFloat()->getValue();
    
    MaterialChunkTransitPtr matChunk = handleSimpleColor(
            diffuseCol,
            ambientCol,
            specularCol,
            emissionCol,
            transCol,
            tech->getTransparent()->getOpaque(),
            shininessVal,
            transparencyVal);

    UInt32 currTex = 0;

    if(ambientTex != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: Got ambient texture [%s]\n",
                         ambientTex->getTexture()));

        SamplerMap::iterator samplerIt;

        samplerIt = _samplerMap.find(ambientTex->getTexture());

        if(samplerIt != _samplerMap.end())
        {
            domFx_sampler2D_commonRef sampler = samplerIt->second;

            ColladaSampler2DRefPtr colSampler =
                getUserDataAs<ColladaSampler2D>(sampler);
            
            if(colSampler == NULL)
            {
                colSampler = ColladaSampler2D::create(sampler, getGlobal());
                addElement(colSampler);
                
                colSampler->setEffect(this);
                colSampler->read     (    );
            }
            
            TextureObjChunkUnrecPtr texObj = colSampler->getTexObj();

            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: got texObj [%p]\n", texObj.get()));

            if(texObj != NULL)
            {
                TextureEnvChunkUnrecPtr texEnv = TextureEnvChunk::create();
                
                _material->addChunk(texObj);
                _material->addChunk(texEnv);
                
                texEnv->setEnvMode(GL_REPLACE);
                
                setTexCoordMapping(currTex++, ambientTex->getTexcoord());
//                 _texCoordMapping[currTex++] = ambientTex->getTexcoord();
            }
        }
        else
        {
            domEffectRef effect = getDOMElementAs<domEffect>();
            
            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: got <effect> [%s] [%s]\n",
                             effect->getId(),
                             effect->getDocumentURI()->getURI()));
            
            std::string imageUriStr = effect->getDocumentURI()->getURI();
            
            imageUriStr += "#";
            imageUriStr += ambientTex->getTexture();
            
            daeURI imageUri(getGlobal()->getDAE(), imageUriStr);
            
            imageUri.resolveElement();
            
            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: textureUri [%s] [%d]\n",
                             imageUri.getURI(), imageUri.getState()));
            
            daeElementRef      imageElem = imageUri.getElement();
            domImageRef        image     = daeSafeCast<domImage>(imageElem);
            
            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: imageElem [%s] [%s]\n",
                             imageElem->getTypeName(),
                             imageElem->getElementName()));
            
            ColladaImageRefPtr colImage  = getUserDataAs<ColladaImage>(image);
            
            if(colImage == NULL)
            {
                colImage = ColladaImage::create(image, getGlobal());
                addElement(colImage);
                
                colImage->read();
            }
            
            ImageUnrecPtr texImage = colImage->getImage();
            
            if(texImage != NULL)
            {
                TextureObjChunkUnrecPtr texObj = TextureObjChunk::create();
                TextureEnvChunkUnrecPtr texEnv = TextureEnvChunk::create();
                
                texObj->setImage(texImage);
                
                _material->addChunk(texObj);
                _material->addChunk(texEnv);
                
                texEnv->setEnvMode(GL_REPLACE);
                
                setTexCoordMapping(currTex++, ambientTex->getTexcoord());
//                 _texCoordMapping[currTex++] = ambientTex->getTexcoord();
            }
        }
    }

    if(diffuseTex != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: Got diffuse texture [%s]\n",
                         diffuseTex->getTexture()));

        Color4f colVal;

        colVal[0] = 0.8f;
        colVal[1] = 0.8f;
        colVal[2] = 0.8f;
        colVal[3] = 1.0f;

        matChunk->setDiffuse(colVal);

        SamplerMap::iterator samplerIt;

        samplerIt = _samplerMap.find(diffuseTex->getTexture());

        if(samplerIt != _samplerMap.end())
        {
            domFx_sampler2D_commonRef sampler = samplerIt->second;

            ColladaSampler2DRefPtr colSampler =
                getUserDataAs<ColladaSampler2D>(sampler);
            
            if(colSampler == NULL)
            {
                colSampler = ColladaSampler2D::create(sampler, getGlobal());
                addElement(colSampler);
                
                colSampler->setEffect(this);
                colSampler->read     (    );
            }
            
            TextureObjChunkUnrecPtr texObj = colSampler->getTexObj();

            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: got texObj [%p]\n", texObj.get()));

            if(texObj != NULL)
            {
                TextureEnvChunkUnrecPtr texEnv = TextureEnvChunk::create();
                
                _material->addChunk(texObj);
                _material->addChunk(texEnv);
                
                texEnv->setEnvMode(GL_MODULATE);
                
                OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: texCoordMapping [%u] [%s]\n",
                                 currTex, diffuseTex->getTexcoord()));
                
                setTexCoordMapping(currTex++, diffuseTex->getTexcoord());
//                 _texCoordMapping[currTex++] = diffuseTex->getTexcoord();
            }
        }
        else
        {
            domEffectRef effect = getDOMElementAs<domEffect>();
            
            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: got <effect> [%s] [%s]\n",
                             effect->getId(),
                             effect->getDocumentURI()->getURI()));
            
            std::string imageUriStr = effect->getDocumentURI()->getURI();
            
            imageUriStr += "#";
            imageUriStr += ambientTex->getTexture();
            
            daeURI imageUri(getGlobal()->getDAE(), imageUriStr);
            
            imageUri.resolveElement();
            
            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: textureUri [%s] [%d]\n",
                             imageUri.getURI(), imageUri.getState()));
            
            daeElementRef      imageElem = imageUri.getElement();
            domImageRef        image     = daeSafeCast<domImage>(imageElem);
            
            OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: imageElem [%s] [%s]\n",
                             imageElem->getTypeName(),
                             imageElem->getElementName()));
            
            ColladaImageRefPtr colImage  = getUserDataAs<ColladaImage>(image);
            
            if(colImage == NULL)
            {
                colImage = ColladaImage::create(image, getGlobal());
                addElement(colImage);
                
                colImage->read();
            }
            
            ImageUnrecPtr texImage = colImage->getImage();
            
            if(texImage != NULL)
            {
                TextureObjChunkUnrecPtr texObj = TextureObjChunk::create();
                TextureEnvChunkUnrecPtr texEnv = TextureEnvChunk::create();
                
                texObj->setImage(texImage);
                
                _material->addChunk(texObj);
                _material->addChunk(texEnv);
                
                texEnv->setEnvMode(GL_MODULATE);
                
                OSG_COLLADA_LOG(("ColladaEffect::setupSimpleColorAndTex: texCoordMapping [%u] [%s]\n",
                                 currTex, diffuseTex->getTexcoord()));
                
                setTexCoordMapping(currTex++, diffuseTex->getTexcoord());
//                 _texCoordMapping[currTex++] = diffuseTex->getTexcoord();
            }
        }
    }
}

template <class TechTypeT>
void ColladaEffect::setupSimpleSpecColorAndTex(TechTypeT tech)
{
    domCommon_color_or_texture_type::domColorRef   specularCol = NULL;
    domCommon_color_or_texture_type::domTextureRef specularTex = NULL;

    fillElements(tech->getSpecular(), specularCol, specularTex);

    domCommon_float_or_param_typeRef shininess = tech->getShininess();

    setupSimpleColorAndTex(tech,
                           shininess,
                           specularCol,
                           specularTex );
}

MaterialChunkTransitPtr ColladaEffect::handleSimpleColor(
    DomColor          *diffuse,
    DomColor          *ambient,
    DomColor          *specular,
    DomColor          *emission,
    DomColor          *transparent,
    domFx_opaque_enum  opaqueMode,
    Real32             shininess,
    Real32             transparency)
{
    OSG_COLLADA_LOG(("ColladaEffect::handleSimpleColor:\n"));
    
    MaterialChunkUnrecPtr matChunk      = MaterialChunk::create();
    bool                  useBlendChunk = false;
    Color4f               colVal;
    
    if(transparent != NULL || transparency < (1.0 - Eps))
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleSimpleColor: setting transparent color\n"));
        
        Color4r          blendColor(1.0, 1.0, 1.0, 1.0);
        BlendChunkRefPtr blendChunk;
        
        if(opaqueMode == FX_OPAQUE_ENUM_A_ONE)
        {
            if(transparent->getValue()[3] * transparency < (1.0 - Eps))
            {
                blendColor[0] = 0.0;
                blendColor[1] = 0.0;
                blendColor[2] = 0.0;
                blendColor[3] = transparent->getValue()[3] * transparency;
                
                blendChunk = BlendChunk::create();
                blendChunk->setSrcFactor (GL_CONSTANT_ALPHA_EXT          );
                blendChunk->setDestFactor(GL_ONE_MINUS_CONSTANT_ALPHA_EXT);
                blendChunk->setColor     (blendColor                     );
                
                useBlendChunk = true;
            }
        }
        else if(opaqueMode == FX_OPAQUE_ENUM_RGB_ZERO)
        {
            if(transparent->getValue()[0] * transparency > Eps ||
               transparent->getValue()[1] * transparency > Eps ||
               transparent->getValue()[2] * transparency > Eps   )
            {
                blendColor[0] = transparent->getValue()[0] * transparency;
                blendColor[1] = transparent->getValue()[1] * transparency;
                blendColor[2] = transparent->getValue()[2] * transparency;
                blendColor[3] = computeLuminance(blendColor[0],
                                                 blendColor[1],
                                                 blendColor[2] );
                
                blendChunk = BlendChunk::create();
                blendChunk->setSrcFactor (GL_ONE_MINUS_CONSTANT_COLOR_EXT);
                blendChunk->setDestFactor(GL_CONSTANT_COLOR_EXT          );
                blendChunk->setColor     (blendColor                     );
                
                useBlendChunk = true;
            }
        }
        else
        {
            FWARNING(("ColladaEffect::handleSimpleColor: Unknown opaque value [%d]\n",
                      opaqueMode));
        }
        
        if(blendChunk != NULL)
            _material->addChunk(blendChunk);
    }
    
    if(diffuse != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleSimpleColor: setting diffuse color\n"));
        
        const domFx_color_common &color = diffuse->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];
        colVal[3] = useBlendChunk ? color[3] : 1.0;

        matChunk->setDiffuse(colVal);
    }

    if(ambient != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleSimpleColor: setting ambient color\n"));
        
        const domFx_color_common &color = ambient->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];
        colVal[3] = useBlendChunk ? color[3] : 1.0;

        matChunk->setAmbient(colVal);
    }

    if(specular != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleSimpleColor: setting specular color\n"));
        
        const domFx_color_common &color = specular->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];
        colVal[3] = useBlendChunk ? color[3] : 1.0;

        matChunk->setSpecular(colVal);
    }

    if(emission != NULL)
    {
        OSG_COLLADA_LOG(("ColladaEffect::handleSimpleColor: setting emissive color\n"));
        
        const domFx_color_common &color = emission->getValue();
    
        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];
        colVal[3] = useBlendChunk ? color[3] : 1.0;
    
        matChunk->setEmission(colVal);
    }

    shininess = osgClamp(0.f, shininess, 128.f);

    matChunk->setShininess(shininess);

    _material->addChunk(matChunk);

    return MaterialChunkTransitPtr(matChunk);
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
