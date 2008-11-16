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

#include "OSGPCSSShadowMapHandler.h"
#include "OSGRenderAction.h"
#include "OSGShadowStage.h"
#include "OSGShadowStageData.h"
#include "OSGSpotLight.h"
#include "OSGDirectionalLight.h"

OSG_BEGIN_NAMESPACE

#include "ShaderCode/OSGPCSSShadowMapShaderCode.cinl"

PCSSShadowMapHandler::PCSSShadowMapHandler(ShadowStage     *pSource,
                                           ShadowStageData *pData  ) :
     Inherited     (pSource, 
                    pData  ),
    _pClearSMapBack(NULL   ),
    _pPoly         (NULL   ),
    _shadowSHL     (NULL   ),
    _firstRun      (1      )
{
    _uiMode = ShadowStage::PCSS_SHADOW_MAP;


    //SHL Chunk 1

    _shadowSHL = SimpleSHLChunk::createLocal();
    _shadowSHL->setVertexProgram  (_pcss_shadow_vp);
    _shadowSHL->setFragmentProgram(_pcss_shadow_fp);


    _pPoly = PolygonChunk::createLocal();

    _unlitMat->addChunk(_pPoly);

    _pClearSMapBack = SolidBackground::createLocal();
    
    _pClearSMapBack->setColor(Color3f(1.f, 1.f, 1.f));
}

PCSSShadowMapHandler::~PCSSShadowMapHandler(void)
{
    _pClearSMapBack  = NULL;
    _pPoly           = NULL;
    _shadowSHL       = NULL;

    _vShadowCmat  .clear();
    _vShadowSHLVar.clear();

}


void PCSSShadowMapHandler::createShadowMapsFBO(DrawEnv *pEnv)
{
    RenderAction *a = dynamic_cast<RenderAction *>(pEnv->getAction());

#ifdef SHADOWCHECK
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
#endif

    // disable all lights more speed
    std::vector<bool> vLocalLightStates;

    const ShadowStageData::LightStore  &vLights      = 
        _pStageData->getLights();

    const ShadowStageData::LStateStore &vLightStates = 
        _pStageData->getLightStates();

    const ShadowStageData::CamStore    &vLCams       =
        _pStageData->getLightCameras();

    const ShadowStageData::StatusStore &vExclActive  =
        _pStageData->getExcludeNodeActive();

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
        if(vLightStates[i] != 0)
        {
            if(_pStage->getGlobalShadowIntensity() != 0.0 ||
               vLights[i].second->getShadowIntensity() != 0.0)
            {
                a->pushPartition();
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
                    
                    pPart->setBackground(_pClearSMapBack);
                    
                    Node *light  = vLights[i].first;
                    Node *parent = light->getParent();
                    
                    if(parent != NULL)
                    {
                        a->pushMatrix(parent->getToWorld());
                    }
                    
                    
                    a->overrideMaterial(_unlitMat, a->getActNode());
                    a->recurse(light);
                    a->overrideMaterial( NULL,       a->getActNode());
                    
                    if(parent != NULL)
                    {
                        a->popMatrix();
                    }
                }
                a->popPartition();
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
            if(vExclActive[i])
            {
                exnode->setTravMask(TypeTraits<UInt32>::BitsSet);
            }
        }
    }


#ifdef SHADOWCHECK
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
#endif
}


void PCSSShadowMapHandler::createColorMapFBO(DrawEnv *pEnv)
{
    RenderAction *a = dynamic_cast<RenderAction *>(pEnv->getAction());

    a->pushPartition((RenderPartition::CopyWindow      |
                      RenderPartition::CopyViewing     |
                      RenderPartition::CopyProjection  |
                      RenderPartition::CopyFrustum     |
                      RenderPartition::CopyNearFar     |
                      RenderPartition::CopyViewportSize),
                     RenderPartition::StateSorting);
    {
        RenderPartition *pPart = a->getActivePartition();

        pPart->setRenderTarget(_pSceneFBO);
        pPart->setDrawBuffer  (GL_COLOR_ATTACHMENT0_EXT);

        Node *parent = a->getActNode()->getParent();

        if(parent != NULL)
        {
            a->pushMatrix(parent->getToWorld());
        }
        
        pPart->setBackground(a->getBackground());

        a->recurseNoNodeCallbacks(a->getActNode());

        if(parent != NULL)
        {
            a->popMatrix();
        }
    }
    a->popPartition();


}

void PCSSShadowMapHandler::createShadowFactorMapFBO(
    DrawEnv      *pEnv,
    UInt32        num,
    UInt32        uiActiveLightCount)
{
    //Finde alle aktiven Lichtquellen

    Real32  activeLights = 0;

    const ShadowStageData::LightStore  &vLights      = 
        _pStageData->getLights();

    const ShadowStageData::LStateStore &vLightStates = 
        _pStageData->getLightStates();

    const ShadowStageData::CamStore    &vLCams       =
        _pStageData->getLightCameras();


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
            if(vLightStates[i]                         != 0 &&
               vLights[i].second->getShadowIntensity() != 0.0)
            {
                activeLights++;
            }
        }
    }

    Real32  shadowIntensity;

    if(_pStage->getGlobalShadowIntensity() != 0.0)
    {
        shadowIntensity = (_pStage->getGlobalShadowIntensity() /
                           activeLights);
    }
    else
    {
        shadowIntensity = 
            (vLights[num].second->getShadowIntensity() /
             activeLights);
    }

    if(vLights[num].second->getShadowIntensity() != 0.0 ||
       _pStage->getGlobalShadowIntensity()     != 0.0)
    {

        Matrix  LVM, LPM, CVM;

        vLCams[num]->getViewing(
            LVM,
            pEnv->getPixelWidth(),
            pEnv->getPixelHeight());

        vLCams[num]->getProjection(
            LPM,
            pEnv->getPixelWidth(),
            pEnv->getPixelHeight());

        CVM = pEnv->getCameraViewing();

        Matrix  iCVM = CVM;
        iCVM.invert();

        Real32  texFactor;

        if(vLights[num].second->getType() == SpotLight::getClassType () ||
           vLights[num].second->getType() == PointLight::getClassType()  )
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

        Real32  lightSize;

        if(vLights[num].second->getType() != DirectionalLight::getClassType())
        {
            lightSize = _pStage->getShadowSmoothness() * 10.0;
        }
        else
        {
            lightSize = _pStage->getShadowSmoothness() / 25.0;
        }

        if(_vShadowCmat.size() == uiActiveLightCount)
        {
            _vShadowCmat.push_back(ChunkMaterial::createLocal());
        }
        
        OSG_ASSERT( uiActiveLightCount < _vShadowCmat.size());

        if(_vShadowSHLVar.size() == uiActiveLightCount)
        {
            _vShadowSHLVar.push_back(SimpleSHLVariableChunk::createLocal());

//            _vShadowSHLVar[uiActiveLightCount]->setSHLChunk(_shadowSHL);
        }

        _shadowSHL->addUniformVariable("shadowMap",    0);
        _shadowSHL->addUniformVariable("oldFactorMap", 1);

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "firstRun", (uiActiveLightCount == 0) ? Int32(1) : Int32(0));

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "intensity", shadowIntensity);

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "texFactor", texFactor);

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "lightPM", shadowMatrix);

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "mapSize",
            Real32(_pStage->getMapSize()));

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "lightSize", Real32(lightSize));

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "xFactor", Real32(xFactor));

        _vShadowSHLVar[uiActiveLightCount]->addUniformVariable(
            "yFactor", Real32(yFactor));


        ShadowStageData::ShadowMapStore &vShadowMaps = 
            _pStageData->getShadowMaps();


        _vShadowCmat[uiActiveLightCount]->clearChunks();

        _vShadowCmat[uiActiveLightCount]->addChunk(
            _shadowSHL);

        _vShadowCmat[uiActiveLightCount]->addChunk(
            _vShadowSHLVar[uiActiveLightCount]);

        _vShadowCmat[uiActiveLightCount]->addChunk(
            vShadowMaps[num].pTexO);

        _vShadowCmat[uiActiveLightCount]->addChunk(
            vShadowMaps[num].pTexE);

        _vShadowCmat[uiActiveLightCount]->addChunk(
            _shadowFactorMapO);

        RenderAction *a = dynamic_cast<RenderAction *>(pEnv->getAction());

        a->pushPartition((RenderPartition::CopyWindow      |
                          RenderPartition::CopyViewing     |
                          RenderPartition::CopyProjection  |
                          RenderPartition::CopyFrustum     |
                          RenderPartition::CopyNearFar     |
                          RenderPartition::CopyViewportSize),
                         RenderPartition::StateSorting);
        {
            RenderPartition *pPart = a->getActivePartition();

            pPart->setRenderTarget(_pSceneFBO);
            pPart->setDrawBuffer  (GL_COLOR_ATTACHMENT1_EXT);
            
            Node *light  = vLights[num].first;
            Node *parent = light->getParent();
            
            if(parent != NULL)
            {
                a->pushMatrix(parent->getToWorld());
            }

            if(uiActiveLightCount == 0)
            {
                pPart->setBackground(_pClearBackground);
            }
                           
            commitChanges();

            a->overrideMaterial(_vShadowCmat[uiActiveLightCount], 
                                 a->getActNode());
            a->recurse(light);
            a->overrideMaterial( NULL,                    
                                 a->getActNode());
            
            if(parent != NULL)
            {
                a->popMatrix();
            }
        }
        a->popPartition();

        _firstRun = 0;
    }
}

void PCSSShadowMapHandler::configureShadowMaps(void)
{
    ShadowStageData::ShadowMapStore &vShadowMaps = _pStageData->getShadowMaps();

    const ShadowStageData::LightStore  &vLights  = _pStageData->getLights();


    UInt32 uiSHMSize = vShadowMaps.size();
    UInt32 uiMapSize = _pStage-> getMapSize ();

    for(UInt32 i = 0; i < uiSHMSize; ++i)
    {
        vShadowMaps[i].pTexO->setCompareMode(GL_NONE     );
        vShadowMaps[i].pTexO->setCompareFunc(GL_LEQUAL   );
        vShadowMaps[i].pTexO->setDepthMode  (GL_LUMINANCE);

        vShadowMaps[i].pTexO->setMinFilter  (GL_NEAREST  );
        vShadowMaps[i].pTexO->setMagFilter  (GL_NEAREST  );

        if(vShadowMaps[i].uiType == 
                                ShadowStageData::ShadowMapElem::ColorShadowMap)
        {
            vShadowMaps[i].pTexO->setInternalFormat(GL_DEPTH_COMPONENT);
            vShadowMaps[i].pTexO->setExternalFormat(GL_DEPTH_COMPONENT);

            if(vLights[i].second->getType() != PointLight::getClassType())
            {
                vShadowMaps[i].pTexO->setWrapS(GL_CLAMP_TO_EDGE);
                vShadowMaps[i].pTexO->setWrapT(GL_CLAMP_TO_EDGE);
            }
            else
            {
                vShadowMaps[i].pTexO->setWrapS(GL_CLAMP_TO_BORDER);
                vShadowMaps[i].pTexO->setWrapT(GL_CLAMP_TO_BORDER);
            }

            vShadowMaps[i].pTexO->setAnisotropy(1.0);

            vShadowMaps[i].pImage->set(Image::OSG_L_PF, 
                                       uiMapSize, uiMapSize, 1, 
                                       1, 1, 0.f, 
                                       NULL,
                                       Image::OSG_UINT8_IMAGEDATA, 
                                       false);

            vShadowMaps[i].pFBO->setDepthAttachment(
                vShadowMaps[i].pFBO->getColorAttachments(0));

            vShadowMaps[i].pFBO->setColorAttachment(NULL, 0);

            vShadowMaps[i].uiType = 
                                ShadowStageData::ShadowMapElem::DepthShadowMap;
        }
    }

    _bShadowMapsConfigured = true;
}

void PCSSShadowMapHandler::render(DrawEnv *pEnv)
{
    glPushAttrib(GL_ENABLE_BIT);

    const ShadowStageData::LightStore  &vLights      = 
        _pStageData->getLights();

    const ShadowStageData::NodeStore   &vTransparents = 
        _pStageData->getTransparents();

    const ShadowStageData::LStateStore &vLightStates = 
        _pStageData->getLightStates();

#ifndef SHADOW_CHECK
    if(_bShadowMapsConfigured == false)
        _pStageData->getShadowMaps().clear();
#endif

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
        initSceneFBO(pEnv, false);

    if(_width  != pEnv->getPixelWidth () ||
       _height != pEnv->getPixelHeight()  )
    {
        updateSceneFBOSize(pEnv, false);
    }

    commitChanges();


    GLfloat globalAmbient[] =
    {
        0.0, 0.0, 0.0, 1.0
    };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    _firstRun = 1;

    if(_pStage->getMapAutoUpdate() == true ||
       _pStage->_trigger_update    == true  )
    {
        _pPoly->setOffsetFill  (true                   );
        _pPoly->setOffsetFactor(_pStage->getOffFactor());
        _pPoly->setOffsetBias  (_pStage->getOffBias  ());

        createColorMapFBO(pEnv);


        //deactivate transparent Nodes
        for(UInt32 t = 0;t < vTransparents.size();++t)
        {
            vTransparents[t]->setTravMask(0);
        }


        createShadowMapsFBO(pEnv);


        // switch on all transparent geos
        for(UInt32 t = 0;t < vTransparents.size();++t)
        {
            vTransparents[t]->setTravMask(TypeTraits<UInt32>::BitsSet);
        }


        UInt32 uiActiveLightCount = 0;

        for(UInt32 i = 0;i < vLights.size();i++)
        {
            if(vLightStates[i] != 0)
            {
                if(_pStage->getGlobalShadowIntensity()   != 0.0 ||
                   vLights[i].second->getShadowIntensity() != 0.0)
                {
                    createShadowFactorMapFBO(pEnv, 
                                             i,
                                             uiActiveLightCount);
                    
                    ++uiActiveLightCount;
                }
            }
        }
        
        _pStage->_trigger_update = false;
    }
    
    setupDrawCombineMap1(pEnv->getAction());
    
    glPopAttrib();
}

OSG_END_NAMESPACE
