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

#include "OSGPCFShadowMapHandler.h"
#include "OSGShadowStageData.h"
#include "OSGRenderAction.h"
#include "OSGShadowStage.h"
#include "OSGSpotLight.h"

OSG_BEGIN_NAMESPACE

#include "ShaderCode/OSGPCFShadowMapShaderCode.cinl"

PCFShadowMapHandler::PCFShadowMapHandler(ShadowStage     *pSource,
                                         ShadowStageData *pData,
                                         GLenum           eTargetBufferFormat,
                                         Window          *pWindow) :
     Inherited        (pSource, 
                       pData,
                       eTargetBufferFormat,
                       pWindow            ),
    _vShadowCmat      (                   ),
    _pPoly            (NULL               ),
    _matrixDeco       (NULL               ),

    _shadowSHL        (NULL               ),
    _shadowSHL2       (NULL               ),
    _shadowSHL3       (NULL               ),
    _shadowSHL4       (NULL               ),
    _shadowCubeSHL    (NULL               ),

    _firstRun         (1                  ),
    _oldRange         (0                  ),

    _vShadowSHLVar    (                   ),
    _vShadowSHLVar2   (                   ),
    _vShadowSHLVar3   (                   ),
    _vShadowSHLVar4   (                   ),

    _vShadowCubeSHLVar(                   )
{
    _uiMode = ShadowStage::PCF_SHADOW_MAP;

    _shadowFactorMap2O     = TextureObjChunk::createLocal();
    _shadowFactorMapImage2 = Image          ::createLocal();

    _shadowFactorMap2O->setImage         (_shadowFactorMapImage2);
    _shadowFactorMap2O->setInternalFormat(eTargetBufferFormat);
    _shadowFactorMap2O->setExternalFormat(GL_RGB);
    _shadowFactorMap2O->setMinFilter     (GL_LINEAR);
    _shadowFactorMap2O->setMagFilter     (GL_LINEAR);
    _shadowFactorMap2O->setWrapS         (GL_REPEAT);
    _shadowFactorMap2O->setWrapT         (GL_REPEAT);
    _shadowFactorMap2O->setTarget        (GL_TEXTURE_2D);

    //SHL Chunk 1
    _shadowSHL  = SimpleSHLChunk::createLocal();
    _shadowSHL2 = SimpleSHLChunk::createLocal();
    _shadowSHL3 = SimpleSHLChunk::createLocal();
    _shadowSHL4 = SimpleSHLChunk::createLocal();


    //SHL Chunk 3
    _shadowCubeSHL = SimpleSHLChunk::createLocal();


    _oldRange = _pStage->getShadowSmoothness();

    if(_oldRange <= 0.1999)
    {
        _shadowSHL->setVertexProgram  (_pcf_shadow_vp);
        _shadowSHL->setFragmentProgram(_pcf2_shadow_fp);

        _shadowSHL2->setVertexProgram  (_pcf_shadow2_vp);
        _shadowSHL2->setFragmentProgram(_pcf2_shadow2_fp);

        _shadowSHL3->setVertexProgram  (_pcf_shadow3_vp);
        _shadowSHL3->setFragmentProgram(_pcf2_shadow3_fp);

        _shadowSHL4->setVertexProgram  (_pcf_shadow4_vp);
        _shadowSHL4->setFragmentProgram(_pcf2_shadow4_fp);

        _shadowCubeSHL->setVertexProgram  (_pcf_shadowCube_vp);
        _shadowCubeSHL->setFragmentProgram(_pcf2_shadowCube_fp);
    }
    else if(_oldRange <= 0.3999)
    {
        _shadowSHL->setVertexProgram  (_pcf_shadow_vp);
        _shadowSHL->setFragmentProgram(_pcf3_shadow_fp);

        _shadowSHL2->setVertexProgram  (_pcf_shadow2_vp);
        _shadowSHL2->setFragmentProgram(_pcf3_shadow2_fp);

        _shadowSHL3->setVertexProgram  (_pcf_shadow3_vp);
        _shadowSHL3->setFragmentProgram(_pcf3_shadow3_fp);

        _shadowSHL4->setVertexProgram  (_pcf_shadow4_vp);
        _shadowSHL4->setFragmentProgram(_pcf3_shadow4_fp);

        _shadowCubeSHL->setVertexProgram  (_pcf_shadowCube_vp);
        _shadowCubeSHL->setFragmentProgram(_pcf3_shadowCube_fp);
    }
    else if(_oldRange <= 0.5999)
    {
        _shadowSHL->setVertexProgram  (_pcf_shadow_vp);
        _shadowSHL->setFragmentProgram(_pcf4_shadow_fp);

        _shadowSHL2->setVertexProgram  (_pcf_shadow2_vp);
        _shadowSHL2->setFragmentProgram(_pcf4_shadow2_fp);

        _shadowSHL3->setVertexProgram  (_pcf_shadow3_vp);
        _shadowSHL3->setFragmentProgram(_pcf4_shadow3_fp);

        _shadowSHL4->setVertexProgram  (_pcf_shadow4_vp);
        _shadowSHL4->setFragmentProgram(_pcf4_shadow4_fp);

        _shadowCubeSHL->setVertexProgram  (_pcf_shadowCube_vp);
        _shadowCubeSHL->setFragmentProgram(_pcf4_shadowCube_fp);
    }
    else if(_oldRange <= 0.7999)
    {
        _shadowSHL->setVertexProgram  (_pcf_shadow_vp);
        _shadowSHL->setFragmentProgram(_pcf5_shadow_fp);

        _shadowSHL2->setVertexProgram  (_pcf_shadow2_vp);
        _shadowSHL2->setFragmentProgram(_pcf5_shadow2_fp);

        _shadowSHL3->setVertexProgram  (_pcf_shadow3_vp);
        _shadowSHL3->setFragmentProgram(_pcf5_shadow3_fp);

        _shadowSHL4->setVertexProgram  (_pcf_shadow4_vp);
        _shadowSHL4->setFragmentProgram(_pcf5_shadow4_fp);

        _shadowCubeSHL->setVertexProgram  (_pcf_shadowCube_vp);
        _shadowCubeSHL->setFragmentProgram(_pcf5_shadowCube_fp);
    }
    else
    {
        _shadowSHL->setVertexProgram  (_pcf_shadow_vp);
        _shadowSHL->setFragmentProgram(_pcf6_shadow_fp);

        _shadowSHL2->setVertexProgram  (_pcf_shadow2_vp);
        _shadowSHL2->setFragmentProgram(_pcf6_shadow2_fp);

        _shadowSHL3->setVertexProgram  (_pcf_shadow3_vp);
        _shadowSHL3->setFragmentProgram(_pcf6_shadow3_fp);

        _shadowSHL4->setVertexProgram  (_pcf_shadow4_vp);
        _shadowSHL4->setFragmentProgram(_pcf6_shadow4_fp);

        _shadowCubeSHL->setVertexProgram  (_pcf_shadowCube_vp);
        _shadowCubeSHL->setFragmentProgram(_pcf6_shadowCube_fp);
    }


    _pPoly = PolygonChunk::createLocal();

    _unlitMat->addChunk(_pPoly);

    _matrixDeco = MatrixCameraDecorator::createLocal();
}

PCFShadowMapHandler::~PCFShadowMapHandler(void)
{
    _pPoly            = NULL;
    _matrixDeco       = NULL;

    _shadowSHL        = NULL;
    _shadowSHL2       = NULL;
    _shadowSHL3       = NULL;
    _shadowSHL4       = NULL;
    _shadowCubeSHL    = NULL;

    _vShadowCmat      .clear();
    _vShadowSHLVar    .clear();
    _vShadowSHLVar2   .clear();
    _vShadowSHLVar3   .clear();
    _vShadowSHLVar4   .clear();
    _vShadowCubeSHLVar.clear();
}



void PCFShadowMapHandler::createShadowMapsFBO(RenderAction *a,
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
                //------Setting up Window to fit size of ShadowMap------------

                if(vLights[i].second->getType() != PointLight::getClassType() ||
                   vRealPLight[i]               == false                       )
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
                        Node *parent =  light->getParent();

                        if(parent != NULL)
                        {
                            a->pushMatrix(parent->getToWorld());
                        }
                        
                        
                        a->overrideMaterial(_unlitMat, a->getActNode());
                        _pStage->recurse(a, light);
                        a->overrideMaterial( NULL,       a->getActNode());

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
                        //Offset berechnen
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

                        _matrixDeco->setDecoratee    (vLCams     [i]);
                        _matrixDeco->setPreProjection(_aCubeTrans[j]);

                        _pStage->pushPartition(a);
                        {
                            RenderPartition   *pPart = a->getActivePartition();

                            pPart->addPreRenderCallback(
                                &ShadowTreeHandler::setupAmbientModelAndMasks);
                            pPart->addPostRenderCallback(
                                &ShadowTreeHandler::endAmbientModelAndMasks);

                            pPart->setRenderTarget(
                                vShadowMaps[i].pFBO);

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
                            
                            
                            a->overrideMaterial(_unlitMat, a->getActNode());
                            _pStage->recurse(a, light);
                            a->overrideMaterial( NULL,       a->getActNode());
                            
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

    // activate exclude nodes:
    for(UInt32 i = 0;i < _pStage->getMFExcludeNodes()->size();++i)
    {
        Node *exnode = _pStage->getExcludeNodes(i);

        if(exnode != NULL)
        {
            exnode->setTravMask(vExclTravMask[i]);
        }
    }

    // enable all lights.
    for(UInt32 i = 0;i < vLights.size();++i)
    {
        // restore old states.
        vLights[i].second->setOn(vLocalLightStates[i]);
    }
}

void PCFShadowMapHandler::createColorMapFBO(RenderAction *a,
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
        pPart->setDrawBuffer  (GL_COLOR_ATTACHMENT0_EXT);

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

void PCFShadowMapHandler::createShadowFactorMapFBO(RenderAction *a,
                                                   DrawEnv       *pEnv)
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


    //Finde alle aktiven Lichtquellen

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
            if(vLightStates[i] != 0 &&
               vLights[i].second->getShadowIntensity() != 0.0)
            {
                activeLights++;
            }
        }
    }

    bool bCA1Cleared = false;
    bool bCA2Cleared = false;

    UInt32 uiPLightCount = 0;

    ShadowStageData::ShadowMapStore &vShadowMaps = _pStageData->getShadowMaps();

    //Zuerst alle echte Pointlights
    for(UInt32 i = 0;i < vLights.size();i++)
    {
        if(vLightStates[i] != 0)
        {
            if((_pStage->getGlobalShadowIntensity   () != 0.0 ||
                 vLights[i].second->getShadowIntensity() != 0.0  ) &&
               vRealPLight[i]                            == true    )
            {
                Real32      shadowIntensity;
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
                Matrix      LVM, LPM, CVM;

                vLCams[i]->getViewing(
                    LVM,
                    pEnv->getPixelWidth(),
                    pEnv->getPixelHeight());

                vLCams[i]->getProjection(
                    LPM,
                    pEnv->getPixelWidth(), 
                    pEnv->getPixelHeight());
                
                CVM = pEnv->getCameraViewing();

                Matrix      iCVM = CVM;
                iCVM.invert();

                Real32      texFactor;
                if(vLights[i].second->getType() == PointLight::getClassType() ||
                   vLights[i].second->getType() == SpotLight ::getClassType()  )
                {
                    texFactor = Real32(_width) / Real32(_height);
                }
                else
                {
                    texFactor = 1.0;
                }

                Matrix      shadowMatrix = LPM;
                shadowMatrix.mult(LVM);
                shadowMatrix.mult(iCVM);

                Real32      xFactor = 1.0;
                Real32      yFactor = 1.0;
	
                Matrix      m = pEnv->getCameraToWorld();

                Matrix      shadowMatrixOP = LVM;
                shadowMatrix.mult(iCVM);

                Matrix      shadowMatrixA = LPM;
                shadowMatrixA.mult(_aCubeTrans[0]);
                shadowMatrixA.mult(LVM);
                shadowMatrixA.mult(iCVM);

                Matrix      shadowMatrixB = LPM;
                shadowMatrixB.mult(_aCubeTrans[1]);
                shadowMatrixB.mult(LVM);
                shadowMatrixB.mult(iCVM);

                Matrix      shadowMatrixC = LPM;
                shadowMatrixC.mult(_aCubeTrans[2]);
                shadowMatrixC.mult(LVM);
                shadowMatrixC.mult(iCVM);

                Matrix      shadowMatrixD = LPM;
                shadowMatrixD.mult(_aCubeTrans[3]);
                shadowMatrixD.mult(LVM);
                shadowMatrixD.mult(iCVM);

                Matrix      shadowMatrixE = LPM;
                shadowMatrixE.mult(_aCubeTrans[4]);
                shadowMatrixE.mult(LVM);
                shadowMatrixE.mult(iCVM);

                Matrix      shadowMatrixF = LPM;
                shadowMatrixF.mult(_aCubeTrans[5]);
                shadowMatrixF.mult(LVM);
                shadowMatrixF.mult(iCVM);

                if(_vShadowCubeSHLVar.size() == uiPLightCount)
                {
                    _vShadowCubeSHLVar.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                OSG_ASSERT(uiPLightCount < _vShadowCubeSHLVar.size());


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
                _shadowCubeSHL->addUniformVariable("mapSize",
                                                    Real32(_PLMapSize));
                _shadowCubeSHL->addUniformVariable("xFactor",
                                                    Real32(xFactor));
                _shadowCubeSHL->addUniformVariable("yFactor",
                                                    Real32(yFactor));

                if(_vShadowCmat.size() == uiPLightCount)
                {
                    _vShadowCmat.push_back(ChunkMaterial::createLocal());
                }

                OSG_ASSERT( uiPLightCount < _vShadowCmat.size());

                _vShadowCmat[uiPLightCount]->clearChunks();
                _vShadowCmat[uiPLightCount]->addChunk(_shadowCubeSHL);

                _vShadowCmat[uiPLightCount]->addChunk(
                    vShadowMaps[i].pTexO);

                _vShadowCmat[uiPLightCount]->addChunk(
                    vShadowMaps[i].pTexE);

                if(_activeFactorMap == 0)
                {
                    _vShadowCmat[uiPLightCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _vShadowCmat[uiPLightCount]->addChunk(_shadowFactorMapO);
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

                    pPart->setRenderTarget(_pShadowFactorFBO);
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
                       
                    commitChanges();
      
                    a->overrideMaterial(_vShadowCmat[uiPLightCount], 
                                         a->getActNode());
                    _pStage->recurse(a, light);
                    a->overrideMaterial( NULL,
                                         a->getActNode());

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

                ++uiPLightCount;
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

            Real32      shadowIntensity;
            if(_pStage->getGlobalShadowIntensity() != 0.0)
            {
                shadowIntensity = (_pStage->getGlobalShadowIntensity() /
                                   activeLights);
            }
            else
            {
                shadowIntensity = (vLights[i].second->getShadowIntensity() / 
                                   activeLights);
            }

            shadowIntensityF.push_back(shadowIntensity);
				
            Matrix      LVM, LPM, CVM;

            vLCams[i]->getViewing(LVM,
                                  pEnv->getPixelWidth(),
                                  pEnv->getPixelHeight());

            vLCams[i]->getProjection(LPM,
                                     pEnv->getPixelWidth(),
                                     pEnv->getPixelHeight());

            CVM = pEnv->getCameraViewing();

            Matrix      iCVM = CVM;
            iCVM.invert();

            Real32      texFactor;

            if(vLights[i].second->getType() == PointLight::getClassType() ||
               vLights[i].second->getType() == SpotLight ::getClassType()  ) 
            {
                texFactor = Real32(_width) / Real32(_height);
            }
            else
            {
                texFactor = 1.0;
            }

            texFactorF.push_back(texFactor);

            Matrix      shadowMatrix = LPM;
            shadowMatrix.mult(LVM);
            shadowMatrix.mult(iCVM);

            shadowMatrixF.push_back(shadowMatrix);

            Real32      mapFactor;

            mapFactor = Real32(_pStage->getMapSize()) /
                Real32(vShadowMaps[i].pImage->getWidth());

            mapFactorF.push_back(mapFactor);
            lightCounter++;
        }
    }

    if(lightCounter != 0)
    {
        UInt32 renderTimes = 1;
        UInt32 uiMatCount  = uiPLightCount;

        UInt32 uiVarCount  = 0;
        UInt32 uiVarCount2 = 0;
        UInt32 uiVarCount3 = 0;
        UInt32 uiVarCount4 = 0;

        if(lightCounter > 4)
            renderTimes = UInt32(ceil(Real32(lightCounter) / 4.0f));

        for(UInt32 i = 0;i < renderTimes;i++)
        {

            GLenum dBuffers = GL_COLOR_ATTACHMENT1_EXT;

            if(_activeFactorMap == 0)
                dBuffers = GL_COLOR_ATTACHMENT1_EXT;
            else
                dBuffers = GL_COLOR_ATTACHMENT2_EXT;

            UInt32  lightOffset = lightCounter - (i * 4);
		
            if(_vShadowCmat.size() == uiMatCount)
            {
                _vShadowCmat.push_back(ChunkMaterial::createLocal());
            }

            OSG_ASSERT( uiMatCount < _vShadowCmat.size());

            //clear chunk and add Textures
            _vShadowCmat[uiMatCount]->clearChunks();
	
            UInt32  lightNum = 0;
            for(UInt32 j = 0;j < vLights.size();j++)
            {
                if(vLightStates[j] != 0)
                {
                    if((_pStage->getGlobalShadowIntensity  () != 0.0 ||
                        vLights[j].second->getShadowIntensity() != 0.0) &&
                       vRealPLight[j] == false)
                    {
                        if(lightNum >= (i * 4) && lightNum < ((i + 1) * 4))
                        {
                            _vShadowCmat[uiMatCount]->addChunk(
                                vShadowMaps[j].pTexO);
                            _vShadowCmat[uiMatCount]->addChunk(
                                vShadowMaps[j].pTexE);
                        }
                        lightNum++;
                    }
                }
            }

            if(lightOffset == 1)
            {
                _vShadowCmat[uiMatCount]->addChunk(_shadowSHL);

                if(_activeFactorMap == 0)
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar.size() == uiVarCount)
                {
                    _vShadowSHLVar.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                OSG_ASSERT(uiVarCount < _vShadowSHLVar.size());

                _shadowSHL->addUniformVariable("oldFactorMap", 1);
                _shadowSHL->addUniformVariable("shadowMap", 0);
                _shadowSHL->addUniformVariable("firstRun", _firstRun);
                _shadowSHL->addUniformVariable("intensity",
                                                shadowIntensityF[0 + (i * 4)]);
                _shadowSHL->addUniformVariable("texFactor", texFactorF[0 +
                                                (i * 4)]);
                _shadowSHL->addUniformVariable("lightPM", shadowMatrixF[0 +
                                                (i * 4)]);
                _shadowSHL->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL->addUniformVariable("mapSize",
                                                Real32(_pStage->getMapSize
                                                       ()));
                _shadowSHL->addUniformVariable("mapFactor",
                                                Real32(mapFactorF[0 +
                                                       (i * 4)]));
                ++uiVarCount;
            }	

            else if(lightOffset == 2)
            {
                _vShadowCmat[uiMatCount]->addChunk(_shadowSHL2);

                if(_activeFactorMap == 0)
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar2.size() == uiVarCount2)
                {
                    _vShadowSHLVar2.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                OSG_ASSERT(uiVarCount2 < _vShadowSHLVar2.size());

                _shadowSHL2->addUniformVariable("oldFactorMap", 2);
                _shadowSHL2->addUniformVariable("shadowMap1", 0);
                _shadowSHL2->addUniformVariable("shadowMap2", 1);
                _shadowSHL2->addUniformVariable("firstRun", _firstRun);
                _shadowSHL2->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 4)]);
                _shadowSHL2->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 4)]);
                _shadowSHL2->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 4)]);
                _shadowSHL2->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 4)]);
                _shadowSHL2->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 4)]);
                _shadowSHL2->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 4)]);
                _shadowSHL2->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL2->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL2->addUniformVariable("mapSize",
                                                 Real32(
                                                 _pStage->getMapSize()));
                _shadowSHL2->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        4)]));
                _shadowSHL2->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        4)]));

                ++uiVarCount2;
            }

            else if(lightOffset == 3)
            {
                _vShadowCmat[uiMatCount]->addChunk(_shadowSHL3);

                if(_activeFactorMap == 0)
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar3.size() == uiVarCount3)
                {
                    _vShadowSHLVar3.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                OSG_ASSERT(uiVarCount3 < _vShadowSHLVar3.size());

                _shadowSHL3->addUniformVariable("oldFactorMap", 3);
                _shadowSHL3->addUniformVariable("shadowMap1", 0);
                _shadowSHL3->addUniformVariable("shadowMap2", 1);
                _shadowSHL3->addUniformVariable("shadowMap3", 2);
                _shadowSHL3->addUniformVariable("firstRun", _firstRun);
                _shadowSHL3->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 4)]);
                _shadowSHL3->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL3->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL3->addUniformVariable("mapSize",
                                                 Real32(
                                                 _pStage->getMapSize()));
                _shadowSHL3->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        4)]));
                _shadowSHL3->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        4)]));
                _shadowSHL3->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        4)]));

                ++uiVarCount3;
            }

            else
                //if(lightCounter == 4)
            {
                _vShadowCmat[uiMatCount]->addChunk(_shadowSHL4);

                if(_activeFactorMap == 0)
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _vShadowCmat[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar4.size() == uiVarCount4)
                {
                    _vShadowSHLVar4.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                OSG_ASSERT(uiVarCount4 < _vShadowSHLVar4.size());

                _shadowSHL4->addUniformVariable("oldFactorMap", 4);
                _shadowSHL4->addUniformVariable("shadowMap1", 0);
                _shadowSHL4->addUniformVariable("shadowMap2", 1);
                _shadowSHL4->addUniformVariable("shadowMap3", 2);
                _shadowSHL4->addUniformVariable("shadowMap4", 3);
                _shadowSHL4->addUniformVariable("firstRun", _firstRun);
                _shadowSHL4->addUniformVariable("intensity1",
                                                 shadowIntensityF[0 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("intensity2",
                                                 shadowIntensityF[1 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("intensity3",
                                                 shadowIntensityF[2 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("intensity4",
                                                 shadowIntensityF[3 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor1", texFactorF[0 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor2", texFactorF[1 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor3", texFactorF[2 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor4", texFactorF[3 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM1", shadowMatrixF[0 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM2", shadowMatrixF[1 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM3", shadowMatrixF[2 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM4", shadowMatrixF[3 +
                                                 (i * 4)]);
                _shadowSHL4->addUniformVariable("xFactor", Real32(xFactor));
                _shadowSHL4->addUniformVariable("yFactor", Real32(yFactor));
                _shadowSHL4->addUniformVariable("mapSize",
                                                 Real32(
                                                 _pStage->getMapSize()));
                _shadowSHL4->addUniformVariable("mapFactor1",
                                                 Real32(mapFactorF[0 + (i *
                                                                        4)]));
                _shadowSHL4->addUniformVariable("mapFactor2",
                                                 Real32(mapFactorF[1 + (i *
                                                                        4)]));
                _shadowSHL4->addUniformVariable("mapFactor3",
                                                 Real32(mapFactorF[2 + (i *
                                                                        4)]));
                _shadowSHL4->addUniformVariable("mapFactor4",
                                                 Real32(mapFactorF[3 + (i *
                                                                        4)]));

                ++uiVarCount4;
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

                pPart->setRenderTarget(_pShadowFactorFBO);
                pPart->setDrawBuffer  ( dBuffers);
                
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

                commitChanges();

                a->overrideMaterial(_vShadowCmat[uiMatCount], a->getActNode());
                _pStage->recurse(a, light);
                a->overrideMaterial( NULL,                    a->getActNode());

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

            ++uiMatCount;
        }
    }
    _firstRun = 0;
    shadowIntensityF.clear();
    texFactorF.clear();
    mapFactorF.clear();
    shadowMatrixF.clear();
}


void PCFShadowMapHandler::render(RenderAction *a,
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


    if(_pStage->getMapSize() / 4 > _maxPLMapSize)
        _PLMapSize = _maxPLMapSize;
    else
        _PLMapSize = _pStage->getMapSize() / 4;

#ifdef SHADOWCHECK 
    GLfloat globalAmbient[4];
    glGetFloatv(GL_LIGHT_MODEL_AMBIENT, globalAmbient); // not active
    GLfloat newGlobalAmbient[] =
    {
        0.0, 0.0, 0.0, 1.0
    };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, newGlobalAmbient);
#endif
    
    //Used for ShadowFactorMap
    _firstRun = 1;


    if(_oldRange != _pStage->getShadowSmoothness())
    {
        _oldRange = _pStage->getShadowSmoothness();

        if(_oldRange <= 0.1999)
        {
            _shadowSHL->setVertexProgram(_pcf_shadow_vp);
            _shadowSHL->setFragmentProgram(_pcf2_shadow_fp);
            
            _shadowSHL2->setVertexProgram(_pcf_shadow2_vp);
            _shadowSHL2->setFragmentProgram(_pcf2_shadow2_fp);

            _shadowSHL3->setVertexProgram(_pcf_shadow3_vp);
            _shadowSHL3->setFragmentProgram(_pcf2_shadow3_fp);

            _shadowSHL4->setVertexProgram(_pcf_shadow4_vp);
            _shadowSHL4->setFragmentProgram(_pcf2_shadow4_fp);

            _shadowCubeSHL->setVertexProgram(_pcf_shadowCube_vp);
            _shadowCubeSHL->setFragmentProgram(_pcf2_shadowCube_fp);
        }
        else if(_oldRange <= 0.3999)
        {
            _shadowSHL->setVertexProgram(_pcf_shadow_vp);
            _shadowSHL->setFragmentProgram(_pcf3_shadow_fp);
            
            _shadowSHL2->setVertexProgram(_pcf_shadow2_vp);
            _shadowSHL2->setFragmentProgram(_pcf3_shadow2_fp);
            
            _shadowSHL3->setVertexProgram(_pcf_shadow3_vp);
            _shadowSHL3->setFragmentProgram(_pcf3_shadow3_fp);
            
            _shadowSHL4->setVertexProgram(_pcf_shadow4_vp);
            _shadowSHL4->setFragmentProgram(_pcf3_shadow4_fp);

            _shadowCubeSHL->setVertexProgram(_pcf_shadowCube_vp);
            _shadowCubeSHL->setFragmentProgram(_pcf3_shadowCube_fp);
        }
        else if(_oldRange <= 0.5999)
        {
            _shadowSHL->setVertexProgram(_pcf_shadow_vp);
            _shadowSHL->setFragmentProgram(_pcf4_shadow_fp);
            
            _shadowSHL2->setVertexProgram(_pcf_shadow2_vp);
            _shadowSHL2->setFragmentProgram(_pcf4_shadow2_fp);
            
            _shadowSHL3->setVertexProgram(_pcf_shadow3_vp);
            _shadowSHL3->setFragmentProgram(_pcf4_shadow3_fp);
            
            _shadowSHL4->setVertexProgram(_pcf_shadow4_vp);
            _shadowSHL4->setFragmentProgram(_pcf4_shadow4_fp);
            
            _shadowCubeSHL->setVertexProgram(_pcf_shadowCube_vp);
            _shadowCubeSHL->setFragmentProgram(_pcf4_shadowCube_fp);
        }
        else if(_oldRange <= 0.7999)
        {
            _shadowSHL->setVertexProgram(_pcf_shadow_vp);
            _shadowSHL->setFragmentProgram(_pcf5_shadow_fp);
            
            _shadowSHL2->setVertexProgram(_pcf_shadow2_vp);
            _shadowSHL2->setFragmentProgram(_pcf5_shadow2_fp);
            
            _shadowSHL3->setVertexProgram(_pcf_shadow3_vp);
            _shadowSHL3->setFragmentProgram(_pcf5_shadow3_fp);

            _shadowSHL4->setVertexProgram(_pcf_shadow4_vp);
            _shadowSHL4->setFragmentProgram(_pcf5_shadow4_fp);

            _shadowCubeSHL->setVertexProgram(_pcf_shadowCube_vp);
            _shadowCubeSHL->setFragmentProgram(_pcf5_shadowCube_fp);
        }
        else
        {
            _shadowSHL->setVertexProgram(_pcf_shadow_vp);
            _shadowSHL->setFragmentProgram(_pcf6_shadow_fp);
            
            _shadowSHL2->setVertexProgram(_pcf_shadow2_vp);
            _shadowSHL2->setFragmentProgram(_pcf6_shadow2_fp);
            
            _shadowSHL3->setVertexProgram(_pcf_shadow3_vp);
            _shadowSHL3->setFragmentProgram(_pcf6_shadow3_fp);
            
            _shadowSHL4->setVertexProgram(_pcf_shadow4_vp);
            _shadowSHL4->setFragmentProgram(_pcf6_shadow4_fp);
            
            _shadowCubeSHL->setVertexProgram(_pcf_shadowCube_vp);
            _shadowCubeSHL->setFragmentProgram(_pcf6_shadowCube_fp);
        }
    }
    
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
