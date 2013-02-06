/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGStdShadowMapHandler.h"
#include "OSGRenderAction.h"
#include "OSGShadowStage.h"
#include "OSGShadowStageData.h"
#include "OSGSpotLight.h"

OSG_BEGIN_NAMESPACE

#include "ShaderCode/OSGStdShadowMapShaderCode.cinl"

StdShadowMapHandler::StdShadowMapHandler(ShadowStage     *pSource,
                                         ShadowStageData *pData,
                                         Window          *pWindow) :
     Inherited    (pSource, 
                   pData,
                   pWindow),
    _tiledeco     (NULL   ),
    _matrixDeco   (NULL   ),
    _blender      (NULL   ),
    _shadowCmat   (NULL   ),
    _shadowSHL    (NULL   ),
    _shadowCubeSHL(NULL   ),
    _shadowSHL2   (NULL   ),
    _shadowSHL3   (NULL   ),
    _shadowSHL4   (NULL   ),
    _shadowSHL5   (NULL   ),
    _shadowSHL6   (NULL   ),
    _shadowSHL7   (NULL   ),
    _pPoly        (NULL   ),
    _firstRun     (1      )
{
    _uiMode = ShadowStage::STD_SHADOW_MAP;

    _blender = BlendChunk::createLocal();
    {
        _blender->setAlphaFunc(GL_GEQUAL);
        _blender->setAlphaValue(0.99f);
    }

    _tiledeco = NULL;


    _shadowFactorMap2O     = TextureObjChunk::createLocal();
    _shadowFactorMapImage2 = Image          ::createLocal();

    _shadowFactorMap2O->setImage         (_shadowFactorMapImage2);
    _shadowFactorMap2O->setInternalFormat(GL_RGB);
    _shadowFactorMap2O->setExternalFormat(GL_RGB);
    _shadowFactorMap2O->setMinFilter     (GL_LINEAR);
    _shadowFactorMap2O->setMagFilter     (GL_LINEAR);
    _shadowFactorMap2O->setWrapS         (GL_REPEAT);
    _shadowFactorMap2O->setWrapT         (GL_REPEAT);
    _shadowFactorMap2O->setTarget        (GL_TEXTURE_2D);


    //SHL Chunk 1

    _shadowSHL = SimpleSHLChunk::createLocal();
    _shadowSHL->setVertexProgram  (_std_shadow_vp);
    _shadowSHL->setFragmentProgram(_std_shadow_fp);

    _shadowSHL2 = SimpleSHLChunk::createLocal();
    _shadowSHL2->setVertexProgram  (_std_shadow2_vp);
    _shadowSHL2->setFragmentProgram(_std_shadow2_fp);

    _shadowSHL3 = SimpleSHLChunk::createLocal();
    _shadowSHL3->setVertexProgram  (_std_shadow3_vp);
    _shadowSHL3->setFragmentProgram(_std_shadow3_fp);

    _shadowSHL4 = SimpleSHLChunk::createLocal();
    _shadowSHL4->setVertexProgram  (_std_shadow4_vp);
    _shadowSHL4->setFragmentProgram(_std_shadow4_fp);

    _shadowSHL5 = SimpleSHLChunk::createLocal();
    _shadowSHL5->setVertexProgram  (_std_shadow5_vp);
    _shadowSHL5->setFragmentProgram(_std_shadow5_fp);

    _shadowSHL6 = SimpleSHLChunk::createLocal();
    _shadowSHL6->setVertexProgram  (_std_shadow6_vp);
    _shadowSHL6->setFragmentProgram(_std_shadow6_fp);

    _shadowSHL7 = SimpleSHLChunk::createLocal();
    _shadowSHL7->setVertexProgram  (_std_shadow7_vp);
    _shadowSHL7->setFragmentProgram(_std_shadow7_fp);

    //SHL Chunk 3
    _shadowCubeSHL = SimpleSHLChunk::createLocal();
    _shadowCubeSHL->setVertexProgram  (_std_shadowCube_vp);
    _shadowCubeSHL->setFragmentProgram(_std_shadowCube_fp);

    _shadowCmat = ChunkMaterial::createLocal();

    _matrixDeco = MatrixCameraDecorator::createLocal();

    _pPoly = PolygonChunk::createLocal();

    _unlitMat->addChunk(_pPoly);
}

StdShadowMapHandler::~StdShadowMapHandler(void)
{
    _tiledeco         = NULL;
    _matrixDeco       = NULL;
    _blender          = NULL;
    _shadowCmat       = NULL;
    _shadowSHL        = NULL;
    _shadowCubeSHL    = NULL;
    _shadowSHL2       = NULL;
    _shadowSHL3       = NULL;
    _shadowSHL4       = NULL;
    _shadowSHL5       = NULL;
    _shadowSHL6       = NULL;
    _shadowSHL7       = NULL;
    _pPoly            = NULL;
}


void StdShadowMapHandler::createShadowMapsFBO(RenderAction *a,
                                              DrawEnv      *pEnv)
{

    //------Setting up Window to fit size of ShadowMap----------------

    // disable all lights more speed
    std::vector<bool> vLocalLightStates;

    const ShadowStageData::LightStore    &vLights      =
        _pStageData->getLights();

    const ShadowStageData::LStateStore   &vLightStates =
        _pStageData->getLightStates();

    const ShadowStageData::StatusStore   &vRealPLight  =
        _pStageData->getRealPointLight();

    const ShadowStageData::CamStore      &vLCams       =
        _pStageData->getLightCameras();

    const ShadowStageData::TravMaskStore &vExclTravMask =
        _pStageData->getExcludeNodeTravMask();

    for(UInt32 i = 0;i < vLights.size();++i)
    {
        // store old states.
        vLocalLightStates.push_back(vLights[i].second->getOn());

        vLights[i].second->setOn(false);
    }

    // deactivate exclude nodes:
    for(UInt32 i = 0;i < _pStage->getMFExcludeNodes()->size();++i)
    {
        Node *exnode = _pStage->getExcludeNodes(i);

        if(exnode != NULL)
            exnode->setTravMask(0);
    }

    ShadowStageData::ShadowMapStore &vShadowMaps = _pStageData->getShadowMaps();

    for(UInt32 i = 0;i < vLights.size();++i)
    {
        if(vLightStates[i])
        {
            if(_pStage->getGlobalShadowIntensity() != 0.0 ||
               vLights[i].second->getShadowIntensity() != 0.0)
            {
                //------Setting up Window to fit size of ShadowMap-------------

                if(vLights[i].second->getType() != PointLight::getClassType() ||
                   vRealPLight[i] == false)
                {
                    _pStage->pushPartition(a);
                    {
                        RenderPartition   *pPart    = a->getActivePartition();

                        pPart->addPreRenderCallback(
                            &ShadowTreeHandler::setupAmbientModelAndMasks);
                        pPart->addPostRenderCallback(
                            &ShadowTreeHandler::endAmbientModelAndMasks);

                        pPart->setRenderTarget(vShadowMaps[i].pFBO);

                        pPart->setWindow  (a->getWindow());

                        pPart->calcViewportDimension(0.f,
                                                     0.f,
                                                     _pStage->getMapSize()-1,
                                                     _pStage->getMapSize()-1,
                                                 
                                                     _pStage->getMapSize(),
                                                     _pStage->getMapSize() );


                        Matrix m, t;
                    
                        // set the projection
                        vLCams[i]->getProjection(
                            m, 
                            pPart->getViewportWidth (), 
                            pPart->getViewportHeight());
                        
                        vLCams[i]->getProjectionTranslation(
                            t, 
                            pPart->getViewportWidth (), 
                            pPart->getViewportHeight());
                        
                        pPart->setupProjection(m, t);
                        
                        vLCams[i]->getViewing(
                            m, 
                            pPart->getViewportWidth (),
                            pPart->getViewportHeight());
                        
                        
                        pPart->setupViewing(m);
                        
                        pPart->setNear     (vLCams[i]->getNear());
                        pPart->setFar      (vLCams[i]->getFar ());
                        
                        pPart->calcFrustum();

                        pPart->setBackground(_pClearBackground);

                        Node *light  = vLights[i].first;
                        Node *parent = light->getParent();

                        if(parent != NULL)
                        {
                            a->pushMatrix(parent->getToWorld());
                        }
                        

#if 1
                        a->overrideMaterial(_unlitMat, a->getActNode());
#else
                        if(_pStage->getOverrideLightMapMaterial() == true)
                        {
                            a->overrideMaterial(_unlitMat, a->getActNode());
                        }
                        else
                        {
                            a->pushState();
                            a->addOverride(_pPoly->getClassId(), _pPoly);
                        }
#endif

                        _pStage->recurse(a, light);

#if 1
                        a->overrideMaterial( NULL,       a->getActNode());
#else
                        if(_pStage->getOverrideLightMapMaterial() == true)
                        {
                            a->overrideMaterial( NULL,       a->getActNode());
                        }
                        else
                        {
                            a->popState();
                        }
#endif

                        if(parent != NULL)
                        {
                            a->popMatrix();
                        }
                    }
                    _pStage->popPartition(a);
                }
                else
                {
                    for(UInt32 j = 0;j < 6;j++)
                    {
                        UInt32  xOffset, yOffset;

                        if(j == 0)
                        {
                            xOffset = 0;
                            yOffset = 0;
                        }
                        else if(j == 1)
                        {
                            xOffset = _PLMapSize;
                            yOffset = 0;
                        }
                        else if(j == 2)
                        {
                            xOffset = 2 * _PLMapSize;
                            yOffset = 0;
                        }
                        else if(j == 3)
                        {
                            xOffset = 3 * _PLMapSize;
                            yOffset = 0;
                        }
                        else if(j == 4)
                        {
                            xOffset = 0;
                            yOffset = _PLMapSize;
                        }
                        else
                        {
                            xOffset = _PLMapSize;
                            yOffset = _PLMapSize;
                        }

                        _matrixDeco->setDecoratee    ( vLCams[i]    );
                        _matrixDeco->setPreProjection(_aCubeTrans[j]);

                        _pStage->pushPartition(a);
                        {
                            RenderPartition *pPart = a->getActivePartition();

                            pPart->addPreRenderCallback(
                                &ShadowTreeHandler::setupAmbientModelAndMasks);
                            pPart->addPostRenderCallback(
                                &ShadowTreeHandler::endAmbientModelAndMasks);

                            pPart->setRenderTarget(vShadowMaps[i].pFBO);

                            pPart->setWindow  (a->getWindow());

                            pPart->calcViewportDimension(
                                xOffset, 
                                yOffset,
                                xOffset + _PLMapSize,
                                yOffset + _PLMapSize,
                                                 
                                _pStage->getMapSize(),
                                _pStage->getMapSize() );


                            Matrix m, t;
                    
                            // set the projection
                            _matrixDeco->getProjection          (
                                m, 
                                pPart->getViewportWidth (), 
                                pPart->getViewportHeight());
                            
                            _matrixDeco->getProjectionTranslation(
                                t, 
                                pPart->getViewportWidth (), 
                                pPart->getViewportHeight());
                            
                            pPart->setupProjection(m, t);
                            
                            _matrixDeco->getViewing(
                                m, 
                                pPart->getViewportWidth (),
                                pPart->getViewportHeight());
                            
                            pPart->setupViewing(m);
                        
                            pPart->setNear     (
                                _matrixDeco->getNear());
                            pPart->setFar      (
                                _matrixDeco->getFar ());
                        
                            pPart->calcFrustum();
                            
                            pPart->setBackground(_pClearBackground);
                            
                            Node *light  = vLights[i].first;
                            Node *parent = light->getParent();
                            
                            if(parent != NULL)
                            {
                                a->pushMatrix(parent->getToWorld());
                            }
                            
                            
#if 1
                            a->overrideMaterial(_unlitMat, a->getActNode());
#else
                            if(_pStage->getOverrideLightMapMaterial() == true)
                            {
                                a->overrideMaterial(_unlitMat, a->getActNode());
                            }
                            else
                            {
                                a->pushState();
                                a->addOverride(_pPoly->getClassId(), _pPoly);
                            }
#endif

                            _pStage->recurse(a, light);

#if 1
                            a->overrideMaterial( NULL,     a->getActNode());
#else
                            if(_pStage->getOverrideLightMapMaterial() == true)
                            {
                                a->overrideMaterial( NULL,     a->getActNode());
                            }
                            else
                            {
                                a->popState();
                            }
#endif

                            if(parent != NULL)
                            {
                                a->popMatrix();
                            }
                        }
                        _pStage->popPartition(a);
                    }
                }
            }
        }
    }

    //-------Restoring old states of Window and Viewport----------

    // enable all lights.
    for(UInt32 i = 0;i < vLights.size();++i)
    {
        // restore old states.
        vLights[i].second->setOn(vLocalLightStates[i]);
    }

    // activate exclude nodes:
    for(UInt32 i = 0;i < _pStage->getMFExcludeNodes()->size();++i)
    {
        Node *exnode = _pStage->getExcludeNodes(i);
        if(exnode != NULL)
        {
            exnode->setTravMask(vExclTravMask[i]);
        }
    }
}


void StdShadowMapHandler::createColorMapFBO(RenderAction *a,
                                            DrawEnv      *pEnv)
{
    _pStage->pushPartition(a,
                           (RenderPartition::CopyWindow      |
                            RenderPartition::CopyViewing     |
                            RenderPartition::CopyProjection  |
                            RenderPartition::CopyFrustum     |
                            RenderPartition::CopyNearFar     |
                            RenderPartition::CopyViewportSize),
                           RenderPartition::StateSorting);
    {
        RenderPartition *pPart = a->getActivePartition();

        pPart->addPreRenderCallback (&ShadowTreeHandler::setupAmbientModel);
        pPart->addPostRenderCallback(&ShadowTreeHandler::endAmbientModel  );

        pPart->setRenderTarget(_pSceneFBO);
        pPart->setDrawBuffer  ( GL_COLOR_ATTACHMENT0_EXT);

        Node *parent = a->getActNode()->getParent();

        if(parent != NULL)
        {
            a->pushMatrix(parent->getToWorld());
        }
        
        pPart->setBackground(a->getBackground());

        _pStage->recurseFromThis(a);

        if(parent != NULL)
        {
            a->popMatrix();
        }

        if(_pStage->getBlitZBuffer() == true)
        {
            pPart->addPostRenderCallback(&ShadowTreeHandler::blitZBufferCB);
        }
    }
    _pStage->popPartition(a);
}


void StdShadowMapHandler::createShadowFactorMapFBO(RenderAction *a,
                                                   DrawEnv      *pEnv)
{
    _activeFactorMap = 0;

    const ShadowStageData::LightStore  &vLights      = 
        _pStageData->getLights();

    const ShadowStageData::LStateStore &vLightStates = 
        _pStageData->getLightStates();

    const ShadowStageData::StatusStore &vRealPLight  = 
        _pStageData->getRealPointLight();

    const ShadowStageData::CamStore    &vLCams       =
        _pStageData->getLightCameras();


    Real32              activeLights = 0;

    if(_pStage->getGlobalShadowIntensity() != 0.0)
    {
        for(UInt32 i = 0;i < vLights.size();i++)
        {
            if(vLightStates[i] != 0)
                activeLights++;
        }
    }
    else
    {
        for(UInt32 i = 0;i < vLights.size();i++)
        {
            if(vLightStates[i]                              != 0 &&
               vLights     [i].second->getShadowIntensity() != 0.0)
            {
                activeLights++;
            }
        }
    }

    bool bCA1Cleared = false;
    bool bCA2Cleared = false;

    ShadowStageData::ShadowMapStore &vShadowMaps = _pStageData->getShadowMaps();

    //Zuerst alle echte Pointlights
    for(UInt32 i = 0;i < vLights.size();i++)
    {
        if(vLightStates[i] != 0)
        {
            if((_pStage->getGlobalShadowIntensity() != 0.0 ||
                vLights[i].second->getShadowIntensity() != 0.0) &&
               vRealPLight[i])
            {
                Real32  shadowIntensity;
                if(_pStage->getGlobalShadowIntensity() != 0.0)
                {
                    shadowIntensity = (_pStage->getGlobalShadowIntensity() /
                                       activeLights);
                }
                else
                {
                    shadowIntensity =
                        (vLights[i].second->getShadowIntensity() /
                         activeLights);
                }

                Matrix  LVM, LPM, CVM;

                vLCams[i]->getViewing(
                    LVM,
                    pEnv->getPixelWidth(), 
                    pEnv->getPixelHeight());

                vLCams[i]->getProjection(
                    LPM,
                    pEnv->getPixelWidth(), 
                    pEnv->getPixelHeight());

                CVM = pEnv->getCameraViewing();

                Matrix  iCVM = CVM;
                iCVM.invert();

                Real32  texFactor;
                if(vLights[i].second->getType() == PointLight::getClassType()|| 
                   vLights[i].second->getType() == SpotLight ::getClassType() )
                {
                    texFactor = Real32(_width) / Real32(_height);
                }
                else
                {
                    texFactor = 1.0;
                }

                Matrix  shadowMatrix = LPM;
                shadowMatrix.mult(LVM);
                shadowMatrix.mult(iCVM);

                Real32  xFactor = 1.0;
                Real32  yFactor = 1.0;

                Matrix m = pEnv->getCameraToWorld();

                Matrix  shadowMatrixOP = LVM;
                shadowMatrix.mult(iCVM);

                Matrix  shadowMatrixA = LPM;
                shadowMatrixA.mult(_aCubeTrans[0]);
                shadowMatrixA.mult(LVM);
                shadowMatrixA.mult(iCVM);

                Matrix  shadowMatrixB = LPM;
                shadowMatrixB.mult(_aCubeTrans[1]);
                shadowMatrixB.mult(LVM);
                shadowMatrixB.mult(iCVM);

                Matrix  shadowMatrixC = LPM;
                shadowMatrixC.mult(_aCubeTrans[2]);
                shadowMatrixC.mult(LVM);
                shadowMatrixC.mult(iCVM);

                Matrix  shadowMatrixD = LPM;
                shadowMatrixD.mult(_aCubeTrans[3]);
                shadowMatrixD.mult(LVM);
                shadowMatrixD.mult(iCVM);

                Matrix  shadowMatrixE = LPM;
                shadowMatrixE.mult(_aCubeTrans[4]);
                shadowMatrixE.mult(LVM);
                shadowMatrixE.mult(iCVM);

                Matrix  shadowMatrixF = LPM;
                shadowMatrixF.mult(_aCubeTrans[5]);
                shadowMatrixF.mult(LVM);
                shadowMatrixF.mult(iCVM);

                _shadowCubeSHL->addUniformVariable("shadowMap", 0);
                _shadowCubeSHL->addUniformVariable("oldFactorMap", 1);
                _shadowCubeSHL->addUniformVariable("firstRun", _firstRun);
                _shadowCubeSHL->addUniformVariable("intensity",
                                                    shadowIntensity);
                _shadowCubeSHL->addUniformVariable("texFactor", texFactor);
                _shadowCubeSHL->addUniformVariable("lightPMA", shadowMatrixA);
                _shadowCubeSHL->addUniformVariable("lightPMB", shadowMatrixB);
                _shadowCubeSHL->addUniformVariable("lightPMC", shadowMatrixC);
                _shadowCubeSHL->addUniformVariable("lightPMD", shadowMatrixD);
                _shadowCubeSHL->addUniformVariable("lightPME", shadowMatrixE);
                _shadowCubeSHL->addUniformVariable("lightPMF", shadowMatrixF);
                _shadowCubeSHL->addUniformVariable("lightPMOP",
                                                    shadowMatrixOP);
                _shadowCubeSHL->addUniformVariable("KKtoWK", m);
                _shadowCubeSHL->addUniformVariable("xFactor",
                                                    Real32(xFactor));
                _shadowCubeSHL->addUniformVariable("yFactor",
                                                    Real32(yFactor));

                _shadowCmat->clearChunks();
                _shadowCmat->addChunk(_shadowCubeSHL);
                _shadowCmat->addChunk(vShadowMaps[i].pTexO);
                _shadowCmat->addChunk(vShadowMaps[i].pTexE);

                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                GLenum dBuffers = GL_COLOR_ATTACHMENT1_EXT;

                if(_activeFactorMap == 0)
                    dBuffers = GL_COLOR_ATTACHMENT1_EXT;
                else
                    dBuffers = GL_COLOR_ATTACHMENT2_EXT;

                _pStage->pushPartition(a,
                                       (RenderPartition::CopyWindow      |
                                        RenderPartition::CopyViewing     |
                                        RenderPartition::CopyProjection  |
                                        RenderPartition::CopyFrustum     |
                                        RenderPartition::CopyNearFar     |
                                        RenderPartition::CopyViewportSize),
                                       RenderPartition::StateSorting);
                {
                    RenderPartition *pPart = a->getActivePartition();

                    pPart->addPreRenderCallback (
                        &ShadowTreeHandler::setupAmbientModel);
                    pPart->addPostRenderCallback(
                        &ShadowTreeHandler::endAmbientModel  );

                    pPart->setRenderTarget(_pSceneFBO);
                    pPart->setDrawBuffer  ( dBuffers );

                    Node *light  = vLights[i].first;
                    Node *parent = light->getParent();

                    if(parent != NULL)
                    {
                        a->pushMatrix(parent->getToWorld());
                    }

                    if(_activeFactorMap == 0 && bCA1Cleared == false)
                    {
                        pPart->setBackground(_pClearBackground);
                        bCA1Cleared = true;
                    }
                    else if(bCA2Cleared == false)
                    {
                        pPart->setBackground(_pClearBackground);
                        bCA2Cleared = true;
                    }
                             
                    a->overrideMaterial(_shadowCmat, a->getActNode());
                    _pStage->recurse(a, light);
                    a->overrideMaterial( NULL,       a->getActNode());

                    if(parent != NULL)
                    {
                        a->popMatrix();
                    }
                }
                _pStage->popPartition(a);

                _firstRun = 0;

                if(_activeFactorMap == 0)
                    _activeFactorMap = 1;
                else
                    _activeFactorMap = 0;
            }
        }
    }

    std::vector<Real32> shadowIntensityF;
    std::vector<Real32> texFactorF;
    std::vector<Real32> mapFactorF;
    std::vector<Matrix> shadowMatrixF;

    UInt32              lightCounter = 0;

    Real32              xFactor = 1.0;
    Real32              yFactor = 1.0;

    //Jetzt alle normalen Lichtquellen
    for(UInt32 i = 0;i < vLights.size();i++)
    {
        if(vLightStates[i] != 0 &&
           ((_pStage->getGlobalShadowIntensity() != 0.0 ||
             vLights[i].second->getShadowIntensity() != 0.0) &&
            vRealPLight[i]) == false)
        {

            Real32  shadowIntensity;
            if(_pStage->getGlobalShadowIntensity() != 0.0)
            {
                shadowIntensity = (_pStage->getGlobalShadowIntensity() /
                                   activeLights);
            }
            else
            {
                shadowIntensity = 
                    (vLights[i].second->getShadowIntensity() / 
                     activeLights);
            }

            shadowIntensityF.push_back(shadowIntensity);

            Matrix  LVM, LPM, CVM;
            vLCams[i]->getViewing(LVM,
                                  pEnv->getPixelWidth(),
                                  pEnv->getPixelHeight());
            vLCams[i]->getProjection(LPM,
                                     pEnv->getPixelWidth(),
                                     pEnv->getPixelHeight());

            CVM = pEnv->getCameraViewing();

            Matrix  iCVM = CVM;
            iCVM.invert();

            Real32  texFactor;
            if(vLights[i].second->getType() == PointLight::getClassType() ||
               vLights[i].second->getType() == SpotLight ::getClassType()   )
            {
                texFactor = Real32(_width) / Real32(_height);
            }
            else
            {
                texFactor = 1.0;
            }

            texFactorF.push_back(texFactor);

            Matrix  shadowMatrix = LPM;
            shadowMatrix.mult(LVM);
            shadowMatrix.mult(iCVM);

            shadowMatrixF.push_back(shadowMatrix);

            Real32  mapFactor;
            mapFactor = 
                Real32(_pStage->getMapSize()) /
                Real32(vShadowMaps[i].pImage->getWidth());
            mapFactorF.push_back(mapFactor);
            lightCounter++;
        }
    }

    if(lightCounter != 0)
    {
        GLenum  dBuffers = GL_COLOR_ATTACHMENT1_EXT;

        if(_activeFactorMap == 0)
            dBuffers = GL_COLOR_ATTACHMENT1_EXT;
        else
            dBuffers = GL_COLOR_ATTACHMENT2_EXT;

        UInt32  renderTimes = 1;
        if(lightCounter > 7)
            renderTimes = UInt32(ceil(Real32(lightCounter) / 7.0f));

        for(UInt32 i = 0;i < renderTimes;i++)
        {

            UInt32  lightOffset = lightCounter - (i * 7);

            //clear chunk and add Textures
            _shadowCmat->clearChunks();

            UInt32  lightNum = 0;
            for(UInt32 j = 0;j < vLights.size();j++)
            {
                if(vLightStates[j] != 0)
                {
                    if((_pStage->getGlobalShadowIntensity() != 0.0 ||
                        vLights[j].second->getShadowIntensity() != 0.0) &&
                       vRealPLight[j] == false)
                    {
                        if(lightNum >= (i * 7) && lightNum < ((i + 1) * 7))
                        {
                            _shadowCmat->addChunk(
                                vShadowMaps[j].pTexO);
                            _shadowCmat->addChunk(
                                vShadowMaps[j].pTexE);
                        }
                        lightNum++;
                    }
                }
            }

            if(lightOffset == 1)
            {
                _shadowCmat->addChunk(_shadowSHL);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL->addUniformVariable("oldFactorMap", 1);
                _shadowSHL->addUniformVariable("shadowMap", 0);
                _shadowSHL->addUniformVariable("firstRun", _firstRun);
                _shadowSHL->addUniformVariable("intensity",
                                                shadowIntensityF[0 + (i * 7)]);
                _shadowSHL->addUniformVariable("texFactor", texFactorF[0 +
                                                (i * 7)]);
                _shadowSHL->addUniformVariable("lightPM", shadowMatrixF[0 +
                                                (i * 7)]);
                _shadowSHL->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL->addUniformVariable("mapFactor",
                                                Real32(mapFactorF[0 +
                                                       (i * 7)]));
            }

            else if(lightOffset == 2)
            {
                _shadowCmat->addChunk(_shadowSHL2);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL2->addUniformVariable("oldFactorMap", 2);
                _shadowSHL2->addUniformVariable("shadowMap1", 0);
                _shadowSHL2->addUniformVariable("shadowMap2", 1);
                _shadowSHL2->addUniformVariable("firstRun", _firstRun);
                _shadowSHL2->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 7)]);
                _shadowSHL2->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 7)]);
                _shadowSHL2->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 7)]);
                _shadowSHL2->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 7)]);
                _shadowSHL2->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 7)]);
                _shadowSHL2->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 7)]);
                _shadowSHL2->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL2->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL2->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        7)]));
                _shadowSHL2->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        7)]));
            }

            else if(lightOffset == 3)
            {
                _shadowCmat->addChunk(_shadowSHL3);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL3->addUniformVariable("oldFactorMap", 3);
                _shadowSHL3->addUniformVariable("shadowMap1", 0);
                _shadowSHL3->addUniformVariable("shadowMap2", 1);
                _shadowSHL3->addUniformVariable("shadowMap3", 2);
                _shadowSHL3->addUniformVariable("firstRun", _firstRun);
                _shadowSHL3->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 7)]);
                _shadowSHL3->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL3->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL3->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        7)]));
                _shadowSHL3->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        7)]));
                _shadowSHL3->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        7)]));
            }

            else if(lightCounter == 4)
            {
                _shadowCmat->addChunk(_shadowSHL4);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL4->addUniformVariable("oldFactorMap", 4);
                _shadowSHL4->addUniformVariable("shadowMap1", 0);
                _shadowSHL4->addUniformVariable("shadowMap2", 1);
                _shadowSHL4->addUniformVariable("shadowMap3", 2);
                _shadowSHL4->addUniformVariable("shadowMap4", 3);
                _shadowSHL4->addUniformVariable("firstRun", _firstRun);
                _shadowSHL4->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("intensity4",
                                                 shadowIntensityF[3 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("texFactor4", texFactorF[3 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("lightPM4", shadowMatrixF[3 +
                                                 (i * 7)]);
                _shadowSHL4->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL4->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL4->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        7)]));
                _shadowSHL4->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        7)]));
                _shadowSHL4->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        7)]));
                _shadowSHL4->addUniformVariable("mapFactor4",
                                                 Real32(mapFactorF[3 + (i *
                                                                        7)]));
            }

            else if(lightCounter == 5)
            {
                _shadowCmat->addChunk(_shadowSHL5);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL5->addUniformVariable("oldFactorMap", 5);
                _shadowSHL5->addUniformVariable("shadowMap1", 0);
                _shadowSHL5->addUniformVariable("shadowMap2", 1);
                _shadowSHL5->addUniformVariable("shadowMap3", 2);
                _shadowSHL5->addUniformVariable("shadowMap4", 3);
                _shadowSHL5->addUniformVariable("shadowMap5", 4);
                _shadowSHL5->addUniformVariable("firstRun", _firstRun);
                _shadowSHL5->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("intensity4",
                                                 shadowIntensityF[3 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("intensity5",
                                                 shadowIntensityF[4 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("texFactor4", texFactorF[3 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("texFactor5", texFactorF[4 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("lightPM4", shadowMatrixF[3 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("lightPM5", shadowMatrixF[4 +
                                                 (i * 7)]);
                _shadowSHL5->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL5->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL5->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        7)]));
                _shadowSHL5->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        7)]));
                _shadowSHL5->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        7)]));
                _shadowSHL5->addUniformVariable("mapFactor4",
                                                 Real32(mapFactorF[3 + (i *
                                                                        7)]));
                _shadowSHL5->addUniformVariable("mapFactor5",
                                                 Real32(mapFactorF[4 + (i *
                                                                        7)]));
            }

            else if(lightCounter == 6)
            {
                _shadowCmat->addChunk(_shadowSHL6);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL6->addUniformVariable("oldFactorMap", 6);
                _shadowSHL6->addUniformVariable("shadowMap1", 0);
                _shadowSHL6->addUniformVariable("shadowMap2", 1);
                _shadowSHL6->addUniformVariable("shadowMap3", 2);
                _shadowSHL6->addUniformVariable("shadowMap4", 3);
                _shadowSHL6->addUniformVariable("shadowMap5", 4);
                _shadowSHL6->addUniformVariable("shadowMap6", 5);
                _shadowSHL6->addUniformVariable("firstRun", _firstRun);
                _shadowSHL6->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("intensity4",
                                                 shadowIntensityF[3 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("intensity5",
                                                 shadowIntensityF[4 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("intensity6",
                                                 shadowIntensityF[5 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("texFactor4", texFactorF[3 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("texFactor5", texFactorF[4 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("texFactor6", texFactorF[5 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("lightPM4", shadowMatrixF[3 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("lightPM5", shadowMatrixF[4 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("lightPM6", shadowMatrixF[5 +
                                                 (i * 7)]);
                _shadowSHL6->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL6->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL6->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        7)]));
                _shadowSHL6->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        7)]));
                _shadowSHL6->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        7)]));
                _shadowSHL6->addUniformVariable("mapFactor4",
                                                 Real32(mapFactorF[3 + (i *
                                                                        7)]));
                _shadowSHL6->addUniformVariable("mapFactor5",
                                                 Real32(mapFactorF[4 + (i *
                                                                        7)]));
                _shadowSHL6->addUniformVariable("mapFactor6",
                                                 Real32(mapFactorF[5 + (i *
                                                                        7)]));
            }

            else
            {
                _shadowCmat->addChunk(_shadowSHL7);
                if(_activeFactorMap == 0)
                {
                    _shadowCmat->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowCmat->addChunk(_shadowFactorMapO);
                }

                _shadowSHL7->addUniformVariable("oldFactorMap", 7);
                _shadowSHL7->addUniformVariable("shadowMap1", 0);
                _shadowSHL7->addUniformVariable("shadowMap2", 1);
                _shadowSHL7->addUniformVariable("shadowMap3", 2);
                _shadowSHL7->addUniformVariable("shadowMap4", 3);
                _shadowSHL7->addUniformVariable("shadowMap5", 4);
                _shadowSHL7->addUniformVariable("shadowMap6", 5);
                _shadowSHL7->addUniformVariable("shadowMap7", 6);
                _shadowSHL7->addUniformVariable("firstRun", _firstRun);
                _shadowSHL7->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("intensity4",
                                                 shadowIntensityF[3 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("intensity5",
                                                 shadowIntensityF[4 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("intensity6",
                                                 shadowIntensityF[5 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("intensity7",
                                                 shadowIntensityF[6 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor4", texFactorF[3 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor5", texFactorF[4 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor6", texFactorF[5 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("texFactor7", texFactorF[6 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM4", shadowMatrixF[3 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM5", shadowMatrixF[4 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM6", shadowMatrixF[5 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("lightPM7", shadowMatrixF[6 +
                                                 (i * 7)]);
                _shadowSHL7->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL7->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL7->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        7)]));
                _shadowSHL7->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        7)]));
                _shadowSHL7->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        7)]));
                _shadowSHL7->addUniformVariable("mapFactor4",
                                                 Real32(mapFactorF[3 + (i *
                                                                        7)]));
                _shadowSHL7->addUniformVariable("mapFactor5",
                                                 Real32(mapFactorF[4 + (i *
                                                                        7)]));
                _shadowSHL7->addUniformVariable("mapFactor6",
                                                 Real32(mapFactorF[5 + (i *
                                                                        7)]));
                _shadowSHL7->addUniformVariable("mapFactor7",
                                                 Real32(mapFactorF[6 + (i *
                                                                        7)]));
            }

            _pStage->pushPartition(a,
                                   (RenderPartition::CopyWindow      |
                                    RenderPartition::CopyViewing     |
                                    RenderPartition::CopyProjection  |
                                    RenderPartition::CopyFrustum     |
                                    RenderPartition::CopyNearFar     |
                                    RenderPartition::CopyViewportSize),
                                   RenderPartition::StateSorting);
            {
                RenderPartition *pPart = a->getActivePartition();
                
                pPart->addPreRenderCallback (
                    &ShadowTreeHandler::setupAmbientModel);
                pPart->addPostRenderCallback(
                    &ShadowTreeHandler::endAmbientModel  );

                pPart->setRenderTarget(_pSceneFBO);
                pPart->setDrawBuffer  ( dBuffers );
                
                Node *light  = vLights[i].first;
                Node *parent = light->getParent();
                
                if(parent != NULL)
                {
                    a->pushMatrix(parent->getToWorld());
                }
                
                if(_activeFactorMap == 0 && bCA1Cleared == false)
                {
                    pPart->setBackground(_pClearBackground);
                    bCA1Cleared = true;
                }
                else if(bCA2Cleared == false)
                {
                    pPart->setBackground(_pClearBackground);
                    bCA2Cleared = true;
                }

                a->overrideMaterial(_shadowCmat, a->getActNode());
                _pStage->recurse(a, light);
                a->overrideMaterial( NULL,       a->getActNode());

                if(parent != NULL)
                {
                    a->popMatrix();
                }
            }
            _pStage->popPartition(a);
            
            _firstRun = 0;
            if(_activeFactorMap == 0)
                _activeFactorMap = 1;
            else
                _activeFactorMap = 0;
        }
    }

    shadowIntensityF.clear();
    texFactorF.clear();
    mapFactorF.clear();
    shadowMatrixF.clear();
}


void StdShadowMapHandler::render(RenderAction *a,
                                 DrawEnv      *pEnv)
{
    const ShadowStageData::LightStore  &vLights      = 
        _pStageData->getLights();

    const ShadowStageData::NodeStore   &vTransparents = 
        _pStageData->getTransparents();


    if(_pStageData->getShadowMaps().size() != vLights.size())
    {
        initShadowMaps();
    }

    if(_bShadowMapsConfigured == false)
    {
        configureShadowMaps();
    }

    if(_uiMapSize != _pStage->getMapSize())
    {
        updateShadowMapSize();
    }

    if(_pSceneFBO == NULL)
        initSceneFBO(pEnv, true);

    if(_width  != pEnv->getPixelWidth () ||
       _height != pEnv->getPixelHeight()  )
    {
        updateSceneFBOSize(pEnv, true);
    }

    commitChanges();

    if((_pStage->getMapSize() / 4) > _maxPLMapSize)
        _PLMapSize = _maxPLMapSize;
    else
        _PLMapSize = _pStage->getMapSize() / 4;


    _firstRun = 1;


    if(_pStage->getMapAutoUpdate() == true ||
       _pStage->_trigger_update    == true  )
    {
        _pPoly->setOffsetFill  (true                   );
        _pPoly->setOffsetFactor(_pStage->getOffFactor());
        _pPoly->setOffsetBias  (_pStage->getOffBias  ());

        createColorMapFBO(a, pEnv);
                
        
        //deactivate transparent Nodes
        for(UInt32 t = 0;t < vTransparents.size();++t)
        {
            vTransparents[t]->setTravMask(0);
        }


        createShadowMapsFBO(a, pEnv);

        
        // switch on all transparent geos
        for(UInt32 t = 0;t < vTransparents.size();++t)
        {
            vTransparents[t]->setTravMask(TypeTraits<UInt32>::BitsSet);
        }


        createShadowFactorMapFBO(a, pEnv);
        
        _pStage->_trigger_update = false;
    }
    
    setupDrawCombineMap2(a);
}

OSG_END_NAMESPACE
