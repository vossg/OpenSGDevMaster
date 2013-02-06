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

#include "OSGPCF2ShadowMapHandler.h"
#include "OSGShadowStageData.h"
#include "OSGRenderAction.h"
#include "OSGShadowStage.h"
#include "OSGSpotLight.h"

#include "OSGMatrixUtility.h"

// Shadow map implementation using percentage closer filtering (PCF).
// Performs these steps:
// - render scene into a color and a depth texture
// - render a shadow map for each light
// - combine shadow maps into a shadow factor map by rendering
//   a full screen quad, reconstructing eye space position from
//   the depth buffer and transform this into the lights coordinate
//   sytem for the shadow lookup
// - render the final image into the application frame buffer
//   by combining the scene color texture with the shadow factor map

OSG_BEGIN_NAMESPACE

#include "ShaderCode/OSGPCF2ShadowMapShaderCode.cinl"

PCF2ShadowMapHandler::PCF2ShadowMapHandler(ShadowStage     *pSource,
                                           ShadowStageData *pData,
                                           Window          *pWindow) :
     Inherited    (pSource,
                   pData,
                   pWindow),
    _pPoly        (NULL   ),
    _matrixDeco   (NULL   ),

    _shadowSHL    (NULL   ),
    _shadowSHL2   (NULL   ),
    _shadowSHL3   (NULL   ),
    _shadowSHL4   (NULL   ),
    _shadowCubeSHL(NULL   ),

    _firstRun     (1      ),
    _oldRange     (0      )
{
    _uiMode = ShadowStage::PCF2_SHADOW_MAP;

    _maxPLMapSize = _maxTexSize / 3;

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
    _shadowSHL  = SimpleSHLChunk::createLocal();
    _shadowSHL2 = SimpleSHLChunk::createLocal();
    _shadowSHL3 = SimpleSHLChunk::createLocal();
    _shadowSHL4 = SimpleSHLChunk::createLocal();


    //SHL Chunk 3
    _shadowCubeSHL = SimpleSHLChunk::createLocal();


    _oldRange = _pStage->getShadowSmoothness();

    if(_oldRange <= 0.1999)
    {
        _shadowSHL->setVertexProgram  (getPCFLightsVS());
        _shadowSHL->setFragmentProgram(getPCF1LightFS(2));

        _shadowSHL2->setVertexProgram  (getPCFLightsVS());
        _shadowSHL2->setFragmentProgram(getPCF2LightFS(2));

        _shadowSHL3->setVertexProgram  (getPCFLightsVS());
        _shadowSHL3->setFragmentProgram(getPCF3LightFS(2));

        _shadowSHL4->setVertexProgram  (getPCFLightsVS());
        _shadowSHL4->setFragmentProgram(getPCF4LightFS(2));

        _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
        _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(2));
    }
    else if(_oldRange <= 0.3999)
    {
        _shadowSHL->setVertexProgram  (getPCFLightsVS());
        _shadowSHL->setFragmentProgram(getPCF1LightFS(3));

        _shadowSHL2->setVertexProgram  (getPCFLightsVS());
        _shadowSHL2->setFragmentProgram(getPCF2LightFS(3));

        _shadowSHL3->setVertexProgram  (getPCFLightsVS());
        _shadowSHL3->setFragmentProgram(getPCF3LightFS(3));

        _shadowSHL4->setVertexProgram  (getPCFLightsVS());
        _shadowSHL4->setFragmentProgram(getPCF4LightFS(3));

        _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
        _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(3));
    }
    else if(_oldRange <= 0.5999)
    {
        _shadowSHL->setVertexProgram  (getPCFLightsVS());
        _shadowSHL->setFragmentProgram(getPCF1LightFS(4));

        _shadowSHL2->setVertexProgram  (getPCFLightsVS());
        _shadowSHL2->setFragmentProgram(getPCF2LightFS(4));

        _shadowSHL3->setVertexProgram  (getPCFLightsVS());
        _shadowSHL3->setFragmentProgram(getPCF3LightFS(4));

        _shadowSHL4->setVertexProgram  (getPCFLightsVS());
        _shadowSHL4->setFragmentProgram(getPCF4LightFS(4));

        _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
        _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(4));
    }
    else if(_oldRange <= 0.7999)
    {
        _shadowSHL->setVertexProgram  (getPCFLightsVS());
        _shadowSHL->setFragmentProgram(getPCF1LightFS(5));

        _shadowSHL2->setVertexProgram  (getPCFLightsVS());
        _shadowSHL2->setFragmentProgram(getPCF2LightFS(5));

        _shadowSHL3->setVertexProgram  (getPCFLightsVS());
        _shadowSHL3->setFragmentProgram(getPCF3LightFS(5));

        _shadowSHL4->setVertexProgram  (getPCFLightsVS());
        _shadowSHL4->setFragmentProgram(getPCF4LightFS(5));

        _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
        _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(5));
    }
    else
    {
        _shadowSHL->setVertexProgram  (getPCFLightsVS());
        _shadowSHL->setFragmentProgram(getPCF1LightFS(6));

        _shadowSHL2->setVertexProgram  (getPCFLightsVS());
        _shadowSHL2->setFragmentProgram(getPCF2LightFS(6));

        _shadowSHL3->setVertexProgram  (getPCFLightsVS());
        _shadowSHL3->setFragmentProgram(getPCF3LightFS(6));

        _shadowSHL4->setVertexProgram  (getPCFLightsVS());
        _shadowSHL4->setFragmentProgram(getPCF4LightFS(6));

        _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
        _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(6));
    }

    _pClearColorBG = SolidBackground::createLocal();
    _pClearColorBG->setClearDepth(false);

    _pColorMask = ColorMaskChunk::createLocal();
    _pColorMask->setMaskR(false);
    _pColorMask->setMaskG(false);
    _pColorMask->setMaskB(false);
    _pColorMask->setMaskA(false);

    _pLightModel = LightModelChunk::createLocal();
    _pLightModel->setAmbient(Color4f(0.f, 0.f, 0.f, 1.f));

    _pMaterial = MaterialChunk::createLocal();
    _pMaterial->setColorMaterial(GL_NONE);
    _pMaterial->setLit(false);

    _pShadeModel = ShadeModelChunk::createLocal();
    _pShadeModel->setShadeModel(GL_FLAT);

    _pPoly = PolygonChunk::createLocal();

    _matrixDeco = MatrixCameraDecorator::createLocal();
}

PCF2ShadowMapHandler::~PCF2ShadowMapHandler(void)
{
    _pPoly            = NULL;
    _matrixDeco       = NULL;

    _pClearColorBG    = NULL;

    _shadowSHL        = NULL;
    _shadowSHL2       = NULL;
    _shadowSHL3       = NULL;
    _shadowSHL4       = NULL;
    _shadowCubeSHL    = NULL;

    _shadowChunks     .clear();
    _vShadowSHLVar    .clear();
    _vShadowSHLVar2   .clear();
    _vShadowSHLVar3   .clear();
    _vShadowSHLVar4   .clear();
    _vShadowCubeSHLVar.clear();
}

void PCF2ShadowMapHandler::createShadowMapsFBO(RenderAction *a,
                                               DrawEnv      *pEnv)
{

    //------Setting up Window to fit size of ShadowMap----------------

    // disable all lights more speed
    std::vector<bool> vLocalLightStates;

    const ShadowStageData::LightStore    &vLights        =
        _pStageData->getLights();

    const ShadowStageData::LStateStore   &vLightStates   =
        _pStageData->getLightStates();

    const ShadowStageData::StatusStore   &vRealPLight    =
        _pStageData->getRealPointLight();

    const ShadowStageData::CamStore      &vLCams         =
        _pStageData->getLightCameras();

    const ShadowStageData::TravMaskStore &vExclTravMask  =
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

                        a->pushState();
                        {
                            a->addOverride(_pColorMask ->getClassId(), _pColorMask );
                            a->addOverride(_pLightModel->getClassId(), _pLightModel);
                            a->addOverride(_pMaterial  ->getClassId(), _pMaterial  );
                            a->addOverride(_pShadeModel->getClassId(), _pShadeModel);
                            a->addOverride(_pPoly      ->getClassId(), _pPoly      );

                            _pStage->recurse(a, light);
                        }
                        a->popState();

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
                            xOffset = 0;
                            yOffset = _PLMapSize;
                        }
                        else if(j == 4)
                        {
                            xOffset = _PLMapSize;
                            yOffset = _PLMapSize;
                        }
                        else
                        {
                            xOffset = 2 * _PLMapSize;
                            yOffset = _PLMapSize;
                        }

                        _matrixDeco->setDecoratee    (vLCams     [i]);
                        _matrixDeco->setPreProjection(_aCubeTrans[j]);

                        _pStage->pushPartition(a);
                        {
                            RenderPartition   *pPart = a->getActivePartition();

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

                            a->pushState();
                            {
                                a->addOverride(_pColorMask ->getClassId(), _pColorMask );
                                a->addOverride(_pLightModel->getClassId(), _pLightModel);
                                a->addOverride(_pMaterial  ->getClassId(), _pMaterial  );
                                a->addOverride(_pShadeModel->getClassId(), _pShadeModel);
                                a->addOverride(_pPoly      ->getClassId(), _pPoly      );

                                _pStage->recurse(a, light);
                            }
                            a->popState();

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

void PCF2ShadowMapHandler::createColorMapFBO(RenderAction *a,
                                             DrawEnv      *pEnv)
{
    _pStage->pushPartition(a,
                           (RenderPartition::CopyWindow     |
                            RenderPartition::CopyViewing    |
                            RenderPartition::CopyProjection |
                            RenderPartition::CopyFrustum    |
                            RenderPartition::CopyNearFar    ),
                           RenderPartition::StateSorting);
    {
        RenderPartition *pPart = a->getActivePartition();

        pPart->addPreRenderCallback (&ShadowTreeHandler::setupAmbientModel);
        pPart->addPostRenderCallback(&ShadowTreeHandler::endAmbientModel  );

        pPart->setRenderTarget(_pSceneFBO);
        pPart->setDrawBuffer  (GL_COLOR_ATTACHMENT0_EXT);

        pPart->setViewportDimension(0, 0,
                                    pEnv->getPixelWidth (),
                                    pEnv->getPixelHeight(), true);

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

void PCF2ShadowMapHandler::createShadowFactorMapFBO(RenderAction *a,
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

    // Count active light sources

    Real32 activeLights = 0;

    if(_pStage->getGlobalShadowIntensity() != 0.0)
    {
        for(UInt32 i = 0; i < vLights.size(); ++i)
        {
            if(vLightStates[i] != 0)
                activeLights++;
        }
    }
    else
    {
        for(UInt32 i = 0; i < vLights.size(); ++i)
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

    // First combine all PointLight shadow maps
    for(UInt32 i = 0; i < vLights.size(); ++i)
    {
        if(vLightStates[i] != 0)
        {
            if((_pStage->getGlobalShadowIntensity    () != 0.0 ||
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

                Matrix iCPM = pEnv->getCameraProjection();
                iCPM.invert();

                Real32 camNear = pEnv->getCameraNear();
                Real32 camFar  = pEnv->getCameraFar ();

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

                Matrix matEC2LEC;
                matEC2LEC.mult(LVM );
                matEC2LEC.mult(iCVM);

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

                _shadowCubeSHL->addUniformVariable("ProjectionMatrixInv", iCPM   );
                _shadowCubeSHL->addUniformVariable("zNear",               camNear);
                _shadowCubeSHL->addUniformVariable("zFar",                camFar );

                _shadowCubeSHL->addUniformVariable("shadowMap",     0);
                _shadowCubeSHL->addUniformVariable("oldFactorMap",  1);
                _shadowCubeSHL->addUniformVariable("depthMap",      2);
                _shadowCubeSHL->addUniformVariable("firstRun", _firstRun);
                _shadowCubeSHL->addUniformVariable("intensity",
                                                    shadowIntensity);
                _shadowCubeSHL->addUniformVariable("texFactor", texFactor);
                _shadowCubeSHL->addUniformVariable("lightPMA",  shadowMatrixA);
                _shadowCubeSHL->addUniformVariable("lightPMB",  shadowMatrixB);
                _shadowCubeSHL->addUniformVariable("lightPMC",  shadowMatrixC);
                _shadowCubeSHL->addUniformVariable("lightPMD",  shadowMatrixD);
                _shadowCubeSHL->addUniformVariable("lightPME",  shadowMatrixE);
                _shadowCubeSHL->addUniformVariable("lightPMF",  shadowMatrixF);
                _shadowCubeSHL->addUniformVariable("matEC2LEC", matEC2LEC);
                _shadowCubeSHL->addUniformVariable("mapSize",
                                                    Real32(_PLMapSize));

                if(_shadowChunks.size() == uiPLightCount)
                {
                    _shadowChunks.push_back(ChunkMaterial::createLocal());
                }

                OSG_ASSERT( uiPLightCount < _shadowChunks.size());

                _shadowChunks[uiPLightCount]->clearChunks();
                _shadowChunks[uiPLightCount]->addChunk(_shadowCubeSHL);

                _shadowChunks[uiPLightCount]->addChunk(vShadowMaps[i].pTexO);
                _shadowChunks[uiPLightCount]->addChunk(vShadowMaps[i].pTexE);

                if(_activeFactorMap == 0)
                {
                    _shadowChunks[uiPLightCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowChunks[uiPLightCount]->addChunk(_shadowFactorMapO);
                }

                _shadowChunks[uiPLightCount]->addChunk(_depthMapO);

                GLenum dBuffers = GL_COLOR_ATTACHMENT1_EXT;

                if(_activeFactorMap == 0)
                    dBuffers = GL_COLOR_ATTACHMENT1_EXT;
                else
                    dBuffers = GL_COLOR_ATTACHMENT2_EXT;

                _pStage->pushPartition(a,
                                       RenderPartition::CopyWindow,
                                       RenderPartition::SimpleCallback);
                {
                    RenderPartition *pPart = a->getActivePartition();

                    Matrix m, t;
                    MatrixOrthogonal(m, 0.f, 1.f,
                                        0.f, 1.f,
                                       -1.f, 1.f );

                    pPart->setupProjection(m, t);

                    pPart->setRenderTarget(_pSceneFBO);
                    pPart->setDrawBuffer  ( dBuffers );

                    pPart->setViewportDimension(0, 0,
                                                pEnv->getPixelWidth (),
                                                pEnv->getPixelHeight(), true);

                    if(_activeFactorMap == 0 && bCA1Cleared == false)
                    {
                        pPart->setBackground(_pClearColorBG);
                        bCA1Cleared = true;
                    }
                    else if(bCA2Cleared == false)
                    {
                        pPart->setBackground(_pClearColorBG);
                        bCA2Cleared = true;
                    }

                    commitChanges();

                    a->overrideMaterial(_shadowChunks[uiPLightCount],
                                        a->getActNode()              );

                    RenderPartition::SimpleDrawCallback cb =
                        boost::bind(&PCF2ShadowMapHandler::doCreateShadowFactorMapFBO,
                                    this, _1, uiPLightCount);

                    pPart->dropFunctor(cb);

                    a->overrideMaterial(NULL,
                                        a->getActNode());
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

    // Now combine all other light sources
    for(UInt32 i = 0; i < vLights.size(); ++i)
    {
        if(vLightStates[i] != 0 &&
           ((_pStage->getGlobalShadowIntensity    () != 0.0 ||
             vLights[i].second->getShadowIntensity() != 0.0   ) &&
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

        Matrix iCPM = pEnv->getCameraProjection();
        iCPM.invert();

        Real32 camNear = pEnv->getCameraNear();
        Real32 camFar  = pEnv->getCameraFar ();

        if(lightCounter > 4)
            renderTimes = UInt32(ceil(Real32(lightCounter) / 4.0f));

        for(UInt32 i = 0; i < renderTimes; ++i)
        {
            GLenum dBuffers = GL_COLOR_ATTACHMENT1_EXT;

            if(_activeFactorMap == 0)
                dBuffers = GL_COLOR_ATTACHMENT1_EXT;
            else
                dBuffers = GL_COLOR_ATTACHMENT2_EXT;

            UInt32  lightOffset = lightCounter - (i * 4);

            if(_shadowChunks.size() == uiMatCount)
            {
                _shadowChunks.push_back(ChunkMaterial::createLocal());
            }

            OSG_ASSERT( uiMatCount < _shadowChunks.size());

            //clear chunk and add Textures
            _shadowChunks[uiMatCount]->clearChunks();

            UInt32  lightNum = 0;
            for(UInt32 j = 0; j < vLights.size(); ++j)
            {
                if(vLightStates[j] != 0)
                {
                    if((_pStage->getGlobalShadowIntensity    () != 0.0 ||
                        vLights[j].second->getShadowIntensity() != 0.0   ) &&
                       vRealPLight[j] == false)
                    {
                        if(lightNum >= (i * 4) && lightNum < ((i + 1) * 4))
                        {
                            _shadowChunks[uiMatCount]->addChunk(
                                vShadowMaps[j].pTexO);
                            _shadowChunks[uiMatCount]->addChunk(
                                vShadowMaps[j].pTexE);
                        }
                        lightNum++;
                    }
                }
            }

            if(lightOffset == 1)
            {
                _shadowChunks[uiMatCount]->addChunk(_shadowSHL);

                if(_activeFactorMap == 0)
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar.size() == uiVarCount)
                {
                    _vShadowSHLVar.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                _shadowChunks[uiMatCount]->addChunk(_depthMapO);

                OSG_ASSERT(uiVarCount < _vShadowSHLVar.size());

                _shadowSHL->addUniformVariable("ProjectionMatrixInv", iCPM   );
                _shadowSHL->addUniformVariable("zNear",               camNear);
                _shadowSHL->addUniformVariable("zFar",                camFar );

                _shadowSHL->addUniformVariable("shadowMap",    0);
                _shadowSHL->addUniformVariable("oldFactorMap", 1);
                _shadowSHL->addUniformVariable("depthMap",     2);
                _shadowSHL->addUniformVariable("firstRun", _firstRun);
                _shadowSHL->addUniformVariable("intensity",
                                               shadowIntensityF[0 + (i * 4)]);
                _shadowSHL->addUniformVariable("texFactor",
                                               texFactorF[0 + (i * 4)]);
                _shadowSHL->addUniformVariable("lightPM",
                                               shadowMatrixF[0 + (i * 4)]);
                _shadowSHL->addUniformVariable("mapSize",
                                               Real32(_pStage->getMapSize()));
                _shadowSHL->addUniformVariable("mapFactor",
                                               Real32(mapFactorF[0 + (i * 4)]));
                ++uiVarCount;
            }

            else if(lightOffset == 2)
            {
                _shadowChunks[uiMatCount]->addChunk(_shadowSHL2);

                if(_activeFactorMap == 0)
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar2.size() == uiVarCount2)
                {
                    _vShadowSHLVar2.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                _shadowChunks[uiMatCount]->addChunk(_depthMapO);

                OSG_ASSERT(uiVarCount2 < _vShadowSHLVar2.size());

                _shadowSHL2->addUniformVariable("ProjectionMatrixInv", iCPM);
                _shadowSHL2->addUniformVariable("zNear",               camNear);
                _shadowSHL2->addUniformVariable("zFar",                camFar );

                _shadowSHL2->addUniformVariable("shadowMap1",   0);
                _shadowSHL2->addUniformVariable("shadowMap2",   1);
                _shadowSHL2->addUniformVariable("oldFactorMap", 2);
                _shadowSHL2->addUniformVariable("depthMap",     3);
                _shadowSHL2->addUniformVariable("firstRun", _firstRun);
                _shadowSHL2->addUniformVariable("intensity1",
                                                shadowIntensityF[0 + (i * 4)]);
                _shadowSHL2->addUniformVariable("intensity2",
                                                shadowIntensityF[1 + (i * 4)]);
                _shadowSHL2->addUniformVariable("texFactor1",
                                                texFactorF[0 + (i * 4)]);
                _shadowSHL2->addUniformVariable("texFactor2",
                                                texFactorF[1 + (i * 4)]);
                _shadowSHL2->addUniformVariable("lightPM1",
                                                shadowMatrixF[0 + (i * 4)]);
                _shadowSHL2->addUniformVariable("lightPM2",
                                                shadowMatrixF[1 + (i * 4)]);
                _shadowSHL2->addUniformVariable("mapSize",
                                                Real32(_pStage->getMapSize()));
                _shadowSHL2->addUniformVariable("mapFactor1",
                                                Real32(mapFactorF[0 + (i * 4)]));
                _shadowSHL2->addUniformVariable("mapFactor2",
                                                Real32(mapFactorF[1 + (i * 4)]));

                ++uiVarCount2;
            }
            else if(lightOffset == 3)
            {
                _shadowChunks[uiMatCount]->addChunk(_shadowSHL3);

                if(_activeFactorMap == 0)
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar3.size() == uiVarCount3)
                {
                    _vShadowSHLVar3.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                _shadowChunks[uiMatCount]->addChunk(_depthMapO);

                OSG_ASSERT(uiVarCount3 < _vShadowSHLVar3.size());

                _shadowSHL3->addUniformVariable("ProjectionMatrixInv", iCPM);
                _shadowSHL3->addUniformVariable("zNear",               camNear);
                _shadowSHL3->addUniformVariable("zFar",                camFar );

                _shadowSHL3->addUniformVariable("shadowMap1",   0);
                _shadowSHL3->addUniformVariable("shadowMap2",   1);
                _shadowSHL3->addUniformVariable("shadowMap3",   2);
                _shadowSHL3->addUniformVariable("oldFactorMap", 3);
                _shadowSHL3->addUniformVariable("depthMap",     4);
                _shadowSHL3->addUniformVariable("firstRun", _firstRun);
                _shadowSHL3->addUniformVariable("intensity1",
                                                shadowIntensityF[0 + (i * 4)]);
                _shadowSHL3->addUniformVariable("intensity2",
                                                shadowIntensityF[1 + (i * 4)]);
                _shadowSHL3->addUniformVariable("intensity3",
                                                shadowIntensityF[2 + (i * 4)]);
                _shadowSHL3->addUniformVariable("texFactor1",
                                                texFactorF[0 + (i * 4)]);
                _shadowSHL3->addUniformVariable("texFactor2",
                                                texFactorF[1 + (i * 4)]);
                _shadowSHL3->addUniformVariable("texFactor3",
                                                texFactorF[2 + (i * 4)]);
                _shadowSHL3->addUniformVariable("lightPM1",
                                                shadowMatrixF[0 + (i * 4)]);
                _shadowSHL3->addUniformVariable("lightPM2",
                                                shadowMatrixF[1 + (i * 4)]);
                _shadowSHL3->addUniformVariable("lightPM3",
                                                shadowMatrixF[2 + (i * 4)]);
                _shadowSHL3->addUniformVariable("mapSize",
                                                Real32(_pStage->getMapSize()));
                _shadowSHL3->addUniformVariable("mapFactor1",
                                                Real32(mapFactorF[0 + (i * 4)]));
                _shadowSHL3->addUniformVariable("mapFactor2",
                                                Real32(mapFactorF[1 + (i * 4)]));
                _shadowSHL3->addUniformVariable("mapFactor3",
                                                Real32(mapFactorF[2 + (i * 4)]));

                ++uiVarCount3;
            }
            else //if(lightCounter == 4)
            {
                _shadowChunks[uiMatCount]->addChunk(_shadowSHL4);

                if(_activeFactorMap == 0)
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMap2O);
                }
                else
                {
                    _shadowChunks[uiMatCount]->addChunk(_shadowFactorMapO);
                }

                if(_vShadowSHLVar4.size() == uiVarCount4)
                {
                    _vShadowSHLVar4.push_back(
                        SimpleSHLVariableChunk::createLocal());
                }

                _shadowChunks[uiMatCount]->addChunk(_depthMapO);

                OSG_ASSERT(uiVarCount4 < _vShadowSHLVar4.size());

                _shadowSHL4->addUniformVariable("ProjectionMatrixInv", iCPM);
                _shadowSHL4->addUniformVariable("zNear",               camNear);
                _shadowSHL4->addUniformVariable("zFar",                camFar );

                _shadowSHL4->addUniformVariable("shadowMap1",   0);
                _shadowSHL4->addUniformVariable("shadowMap2",   1);
                _shadowSHL4->addUniformVariable("shadowMap3",   2);
                _shadowSHL4->addUniformVariable("shadowMap4",   3);
                _shadowSHL4->addUniformVariable("oldFactorMap", 4);
                _shadowSHL4->addUniformVariable("depthMap",     5);
                _shadowSHL4->addUniformVariable("firstRun", _firstRun);
                _shadowSHL4->addUniformVariable("intensity1",
                                                shadowIntensityF[0 + (i * 4)]);
                _shadowSHL4->addUniformVariable("intensity2",
                                                shadowIntensityF[1 + (i * 4)]);
                _shadowSHL4->addUniformVariable("intensity3",
                                                shadowIntensityF[2 + (i * 4)]);
                _shadowSHL4->addUniformVariable("intensity4",
                                                shadowIntensityF[3 + (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor1",
                                                texFactorF[0 + (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor2",
                                                texFactorF[1 + (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor3",
                                                texFactorF[2 + (i * 4)]);
                _shadowSHL4->addUniformVariable("texFactor4",
                                                texFactorF[3 + (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM1",
                                                shadowMatrixF[0 + (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM2",
                                                shadowMatrixF[1 + (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM3",
                                                shadowMatrixF[2 + (i * 4)]);
                _shadowSHL4->addUniformVariable("lightPM4",
                                                shadowMatrixF[3 + (i * 4)]);
                _shadowSHL4->addUniformVariable("mapSize",
                                                Real32(_pStage->getMapSize()));
                _shadowSHL4->addUniformVariable("mapFactor1",
                                                Real32(mapFactorF[0 + (i * 4)]));
                _shadowSHL4->addUniformVariable("mapFactor2",
                                                Real32(mapFactorF[1 + (i * 4)]));
                _shadowSHL4->addUniformVariable("mapFactor3",
                                                Real32(mapFactorF[2 + (i * 4)]));
                _shadowSHL4->addUniformVariable("mapFactor4",
                                                Real32(mapFactorF[3 + (i * 4)]));

                ++uiVarCount4;
            }

            _pStage->pushPartition(a,
                                   RenderPartition::CopyWindow,
                                   RenderPartition::SimpleCallback);
            {
                RenderPartition *pPart = a->getActivePartition();

                Matrix m, t;
                MatrixOrthogonal(m, 0.f, 1.f,
                                    0.f, 1.f,
                                   -1.f, 1.f );

                pPart->setupProjection(m, t);

                pPart->setRenderTarget(_pSceneFBO);
                pPart->setDrawBuffer  ( dBuffers);

                pPart->setViewportDimension(0, 0,
                                            pEnv->getPixelWidth (),
                                            pEnv->getPixelHeight(), true);

                if(_activeFactorMap == 0 && bCA1Cleared == false)
                {
                    pPart->setBackground(_pClearColorBG);
                    bCA1Cleared = true;
                }
                else if(bCA2Cleared == false)
                {
                    pPart->setBackground(_pClearColorBG);
                    bCA2Cleared = true;
                }

                commitChanges();

                a->overrideMaterial(_shadowChunks[uiMatCount], a->getActNode());

                RenderPartition::SimpleDrawCallback cb =
                    boost::bind(&PCF2ShadowMapHandler::doCreateShadowFactorMapFBO,
                                this, _1, uiMatCount);

                pPart->dropFunctor(cb);

                a->overrideMaterial(NULL,                      a->getActNode());
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

void PCF2ShadowMapHandler::doCreateShadowFactorMapFBO(DrawEnv *pEnv,
                                                      UInt32   uiMatCount)
{
    State *pState = _shadowChunks[uiMatCount]->getState();

    pEnv->activateState(pState, NULL);

    glDepthMask(GL_FALSE);

    glBegin(GL_QUADS);
    {
        glTexCoord2f( 0.f,  0.f);
        glVertex3f  (-1.f, -1.f, 1.f);

        glTexCoord2f( 1.f,  0.f);
        glVertex3f  ( 1.f, -1.f, 1.f);

        glTexCoord2f( 1.f,  1.f);
        glVertex3f  ( 1.f,  1.f, 1.f);

        glTexCoord2f( 0.f,  1.f);
        glVertex3f  (-1.f,  1.f, 1.f);
    }
    glEnd();

    glDepthMask(GL_TRUE);

    pEnv->deactivateState();
}

void PCF2ShadowMapHandler::render(RenderAction *a,
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


    if(_pStage->getMapSize() / 3 > _maxPLMapSize)
        _PLMapSize = _maxPLMapSize;
    else
        _PLMapSize = _pStage->getMapSize() / 3;

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
            _shadowSHL->setVertexProgram  (getPCFLightsVS());
            _shadowSHL->setFragmentProgram(getPCF1LightFS(2));

            _shadowSHL2->setVertexProgram  (getPCFLightsVS());
            _shadowSHL2->setFragmentProgram(getPCF2LightFS(2));

            _shadowSHL3->setVertexProgram  (getPCFLightsVS());
            _shadowSHL3->setFragmentProgram(getPCF3LightFS(2));

            _shadowSHL4->setVertexProgram  (getPCFLightsVS());
            _shadowSHL4->setFragmentProgram(getPCF4LightFS(2));

            _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
            _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(2));
        }
        else if(_oldRange <= 0.3999)
        {
            _shadowSHL->setVertexProgram  (getPCFLightsVS());
            _shadowSHL->setFragmentProgram(getPCF1LightFS(3));

            _shadowSHL2->setVertexProgram  (getPCFLightsVS());
            _shadowSHL2->setFragmentProgram(getPCF2LightFS(3));

            _shadowSHL3->setVertexProgram  (getPCFLightsVS());
            _shadowSHL3->setFragmentProgram(getPCF3LightFS(3));

            _shadowSHL4->setVertexProgram  (getPCFLightsVS());
            _shadowSHL4->setFragmentProgram(getPCF4LightFS(3));

            _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
            _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(3));
        }
        else if(_oldRange <= 0.5999)
        {
            _shadowSHL->setVertexProgram  (getPCFLightsVS());
            _shadowSHL->setFragmentProgram(getPCF1LightFS(4));

            _shadowSHL2->setVertexProgram  (getPCFLightsVS());
            _shadowSHL2->setFragmentProgram(getPCF2LightFS(4));

            _shadowSHL3->setVertexProgram  (getPCFLightsVS());
            _shadowSHL3->setFragmentProgram(getPCF3LightFS(4));

            _shadowSHL4->setVertexProgram  (getPCFLightsVS());
            _shadowSHL4->setFragmentProgram(getPCF4LightFS(4));

            _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
            _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(4));
        }
        else if(_oldRange <= 0.7999)
        {
            _shadowSHL->setVertexProgram  (getPCFLightsVS());
            _shadowSHL->setFragmentProgram(getPCF1LightFS(5));

            _shadowSHL2->setVertexProgram  (getPCFLightsVS());
            _shadowSHL2->setFragmentProgram(getPCF2LightFS(5));

            _shadowSHL3->setVertexProgram  (getPCFLightsVS());
            _shadowSHL3->setFragmentProgram(getPCF3LightFS(5));

            _shadowSHL4->setVertexProgram  (getPCFLightsVS());
            _shadowSHL4->setFragmentProgram(getPCF4LightFS(5));

            _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
            _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(5));
        }
        else
        {
            _shadowSHL->setVertexProgram  (getPCFLightsVS());
            _shadowSHL->setFragmentProgram(getPCF1LightFS(6));

            _shadowSHL2->setVertexProgram  (getPCFLightsVS());
            _shadowSHL2->setFragmentProgram(getPCF2LightFS(6));

            _shadowSHL3->setVertexProgram  (getPCFLightsVS());
            _shadowSHL3->setFragmentProgram(getPCF3LightFS(6));

            _shadowSHL4->setVertexProgram  (getPCFLightsVS());
            _shadowSHL4->setFragmentProgram(getPCF4LightFS(6));

            _shadowCubeSHL->setVertexProgram  (getPCFCubeLightVS());
            _shadowCubeSHL->setFragmentProgram(getPCFCubeLightFS(6));
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
