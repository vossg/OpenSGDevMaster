/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGSimpleShadowMapEngine.h"

#include "OSGMatrixCamera.h"

#include "OSGMatrixUtility.h"
#include "OSGRenderAction.h"

#include "OSGRenderPartition.h"
#include "OSGFrameBufferObject.h"
#include "OSGGroup.h"
#include "OSGChunkMaterial.h"

#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGBlendChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSimpleShadowMapEngineBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleShadowMapEngine.fcd) and
// regenerate the base file.

#if 0
SimpleShadowMapEngine::EngineData::EngineData(void) :
     Inherited   (      ),
    _pCamera     (NullFC),
    _pTexChunk   (NullFC),
    _pTexBuffer  (NullFC),
    _pLightChunk (NullFC),
    _pBlendChunk (NullFC),
    _pTexGenChunk(NullFC),
    _pPolyChunk  (NullFC)
{
}

SimpleShadowMapEngine::EngineData::~EngineData(void)
{
    OSG::subRef(_pCamera     );
    OSG::subRef(_pTexChunk   );
    OSG::subRef(_pTexBuffer  );
    OSG::subRef(_pLightChunk );
    OSG::subRef(_pBlendChunk );
    OSG::subRef(_pTexGenChunk);
    OSG::subRef(_pPolyChunk  );
}

void SimpleShadowMapEngine::EngineData::setCamera(CameraPtr pCamera)
{
    setRefd(_pCamera, pCamera);
}

CameraPtr SimpleShadowMapEngine::EngineData::getCamera(void)
{
    return _pCamera;
}


void SimpleShadowMapEngine::EngineData::setTextureChunk(
    TextureObjChunkPtr pChunk)
{
    setRefd(_pTexChunk, pChunk);
}

TextureObjChunkPtr SimpleShadowMapEngine::EngineData::getTextureChunk(void)
{
    return _pTexChunk;
}

void SimpleShadowMapEngine::EngineData::setTextureBuffer(
    TextureBufferPtr pBuffer)
{
    setRefd(_pTexBuffer, pBuffer);
}

TextureBufferPtr SimpleShadowMapEngine::EngineData::getTextureBuffer(void)
{
    return _pTexBuffer;
}

void SimpleShadowMapEngine::EngineData::setLightChunk(LightChunkPtr pLight)
{
    setRefd(_pLightChunk, pLight);
}

LightChunkPtr SimpleShadowMapEngine::EngineData::getLightChunk(void)
{
    return _pLightChunk;
}

void SimpleShadowMapEngine::EngineData::setBlendChunk(BlendChunkPtr pBlend)
{
    setRefd(_pBlendChunk, pBlend);
}

BlendChunkPtr SimpleShadowMapEngine::EngineData::getBlendChunk(void)
{
    return _pBlendChunk;
}

void SimpleShadowMapEngine::EngineData::setTexGenChunk(TexGenChunkPtr pTexGen)
{
    setRefd(_pTexGenChunk, pTexGen);
}

TexGenChunkPtr SimpleShadowMapEngine::EngineData::getTexGenChunk(void)
{
    return _pTexGenChunk;
}

void SimpleShadowMapEngine::EngineData::setPolyChunk(PolygonChunkPtr pPoly)
{
    setRefd(_pPolyChunk, pPoly);
}

PolygonChunkPtr SimpleShadowMapEngine::EngineData::getPolyChunk(void)
{
    return _pPolyChunk;
}

#endif


/*! \class OSG::SimpleShadowMapEngine
*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void SimpleShadowMapEngine::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void SimpleShadowMapEngine::dump(      UInt32    uiIndent, 
                                 const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SimpleShadowMapEngine::SimpleShadowMapEngine(void) :
    Inherited(    )
{
}

SimpleShadowMapEngine::SimpleShadowMapEngine(
    const SimpleShadowMapEngine &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SimpleShadowMapEngine::~SimpleShadowMapEngine(void)
{
}


/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void SimpleShadowMapEngine::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void SimpleShadowMapEngine::lightRenderEnter(LightPtr      pLight,
                                             RenderAction *pAction)
{
    if(pLight->getOn() == false)
        return;

    StateChunkPtr pChunk          = pLight->getChunk();
    
    UInt32        uiSlot          = pChunk->getClassId();
    
    Int32         iLightIndex     = pAction->allocateLightIndex();

    LightChunkPtr pLightChunk     = dynamic_cast<LightChunkPtr>(pChunk);

//    Color4f tmpVal(0.0, 0.0, 0.0, 1.0);
    
//    pLightChunk->setAmbient(tmpVal);
 
    
    if(iLightIndex >= 0)
    {
        pAction->addOverride(uiSlot + iLightIndex, getCPtr(pChunk));
    }
    else
    {
        SWARNING << "maximum light source limit ("
                 << -iLightIndex
                 << ") is reached" 
                 << " skipping light sources!"
                 << std::endl;
    }
}

void SimpleShadowMapEngine::setupCamera(LightPtr      pLight,
                                        LightTypeE    eType,
                                        RenderAction *pAction,
                                        EngineData   *pEngineData)
{
    if(eType == Directional)
    {
        DirectionalLightPtr pDLight = 
            dynamic_cast<DirectionalLightPtr>(pLight);

        MatrixCameraPtr pCam = 
            dynamic_cast<MatrixCameraPtr>(pEngineData->getCamera());
        
        if(pCam == NullFC)
        {
            pCam = MatrixCamera::create();
            
            pEngineData->setCamera(pCam);
        }
        
        
        Vec3f   diff;
        Pnt3f   center;
        Matrix  transMatrix;
        NodePtr pNode = pAction->getActNode();
        
//        tmpDir = DirectionalLightPtr::dcast(_lights[i]);
        
        diff = (pNode->getVolume().getMax() -
                pNode->getVolume().getMin());
        
        Real32 sceneWidth = diff.length() * 0.5f;
        // Not final values. May get tweaked in the future
        
        Real32 sceneHeight = diff.length() * 0.5f;
        
        pNode->getVolume().getCenter(center);
        
        Vec3f lightdir = pDLight->getDirection();
        
        if(pLight->getBeacon() != NullFC)
        {
            Matrix m = pLight->getBeacon()->getToWorld();
            
            m.mult(lightdir);
        }
        
        MatrixLookAt(transMatrix,
                     center + lightdir,
                     center,
                     Vec3f(0,1,0));
        
        transMatrix.invert();
        
        Matrix proMatrix;
        
        proMatrix.setIdentity();
        
        MatrixOrthogonal( proMatrix,
                         -sceneWidth,   sceneWidth, -sceneHeight,
                          sceneHeight, -sceneWidth,  sceneWidth);
        
        
        pCam->setProjectionMatrix(proMatrix  );
        pCam->setModelviewMatrix (transMatrix);
    }
    else if(eType == Point)
    {
        PointLightPtr pPLight = dynamic_cast<PointLightPtr>(pLight);

        MatrixCameraPtr pCam = 
            dynamic_cast<MatrixCameraPtr>(pEngineData->getCamera());
        
        if(pCam == NullFC)
        {
            pCam = MatrixCamera::create();
            
            pEngineData->setCamera(pCam);
        }
        
        Real32  angle;
        Vec3f   dist;
        Pnt3f   center;
        Vec3f   diff;
        
        Matrix  transMatrix;
        
        NodePtr pNode = pAction->getActNode();
        
        
        pNode->getVolume().getCenter(center);
        
        Pnt3f lightpos = pPLight->getPosition();
        
        if(pLight->getBeacon() != NullFC)
        {
            Matrix m = pLight->getBeacon()->getToWorld();
            
            m.mult(lightpos);
        }
        
        
        MatrixLookAt(transMatrix,
                     lightpos,
                     center,
                     Vec3f(0,1,0));
        
        transMatrix.invert();
        
        
        diff = (pNode->getVolume().getMax() -
                pNode->getVolume().getMin());
        
        dist  = lightpos - center;
        
        angle = atan((diff.length() * 0.5) / dist.length());
        
        Matrix proMatrix;
        
        proMatrix.setIdentity();
        
        MatrixPerspective( proMatrix,
                           2.f * angle,
                           1,
                           1,
                           1000);
        
        
        pCam->setProjectionMatrix(proMatrix  );
        pCam->setModelviewMatrix (transMatrix);    
    }
}

void SimpleShadowMapEngine::setupLightChunk(LightPtr      pLight,
                                            LightTypeE    eType,
                                            RenderAction *pAction,
                                            EngineData   *pEngineData)
{
    if(eType == Directional)
    {
        DirectionalLightPtr pDLight = 
            dynamic_cast<DirectionalLightPtr>(pLight);

        LightChunkPtr pChunk = pEngineData->getLightChunk();

        if(pChunk == NullFC)
        {
            pChunk = LightChunk::create();
            
            pEngineData->setLightChunk(pChunk);
        }
        
        Color4f tmpVal(0.0, 0.0, 0.0, 1.0);
        
        pChunk->setSpecular(tmpVal);
        
        tmpVal.setValuesRGBA(0.2, 0.2, 0.2, 1.0);
        
        pChunk->setDiffuse (tmpVal);
        
        tmpVal.setValuesRGBA(0.0, 0.0, 0.0, 1.0);
        
        pChunk->setAmbient (tmpVal);
        
        Vec4f dir(pDLight->getDirection());
        
        dir[3] = 0;
        
        pChunk->setPosition(dir);
        
        pChunk->setBeacon(pLight->getBeacon());
    }
    else if(eType == Point)
    {
        PointLightPtr pPLight = dynamic_cast<PointLightPtr>(pLight);

        LightChunkPtr pChunk = pEngineData->getLightChunk();
        
        if(pChunk == NullFC)
        {
            pChunk = LightChunk::create();
            
            pEngineData->setLightChunk(pChunk);
        }
        
        Color4f tmpVal(0.0, 0.0, 0.0, 1.0);
        
        pChunk->setSpecular(tmpVal);
        
        tmpVal.setValuesRGBA(this->getShadowColor()[0], 
                             this->getShadowColor()[1],
                             this->getShadowColor()[2],
                             this->getShadowColor()[3]);
        
        pChunk->setDiffuse (tmpVal);
        
        tmpVal.setValuesRGBA(0.0, 0.0, 0.0, 1.0);
        
        pChunk->setAmbient (tmpVal);
        
        Vec4f pos(pPLight->getPosition());
        
        pos[3] = 1;
        
        pChunk->setPosition(pos);
        
        pChunk->setBeacon(pLight->getBeacon());
    }
}


void SimpleShadowMapEngine::doLightPass(LightPtr      pLight,
                                        RenderAction *pAction,
                                        EngineData   *pEngineData)
{
    pAction->pushPartition();

    RenderPartition   *pPart   = pAction->getActivePartition();
    Viewport          *pPort   = pAction->getViewport       ();
    Background        *pBack   = pAction->getBackground     ();

    FrameBufferObject *pTarget = getCPtr(this->getRenderTarget());

    if(pTarget == NULL)
    {
        FrameBufferObjectPtr pFBO = FrameBufferObject::create();

        pFBO->setWidth (this->getWidth ());
        pFBO->setHeight(this->getHeight());

        setRenderTarget(pFBO);

        pTarget = getCPtr(pFBO);
    }

    TextureObjChunkPtr pTexChunk = pEngineData->getTexChunk();
    

    TextureBufferPtr pTexBuffer = pEngineData->getTexBuffer();

    if(pTexBuffer == NullFC)
    {
        pTexBuffer = TextureBuffer::create();
        
        pEngineData->setTexBuffer     (pTexBuffer);

        pTexBuffer->setTexture        (pTexChunk );
        pTarget   ->setDepthAttachment(pTexBuffer);
    }

    PolygonChunkPtr pPoly = pEngineData->getPolyChunk();

    if(pPoly == NullFC)
    {
        pPoly = PolygonChunk::create();
        
        pPoly->setOffsetBias  (this->getOffsetBias  ());
        pPoly->setOffsetFactor(this->getOffsetFactor());
        pPoly->setOffsetFill  (true                   );

        pEngineData->setPolyChunk(pPoly);
    }

    pPart->setRenderTarget(pTarget);

    if(pPort != NULL)
    {
        CameraPtr pCam = pEngineData->getCamera();

//        pPart->setViewport(pPort         );
        pPart->setWindow  (pAction->getWindow());

        pPart->calcViewportDimension(pPort->getLeft  (),
                                     pPort->getBottom(),
                                     pPort->getRight (),
                                     pPort->getTop   (),
                                     
                                     pTarget->getWidth    (),
                                     pTarget->getHeight   ());

        Matrix m, t;
        
        // set the projection
        pCam->getProjection          (m, 
                                      pPart->getViewportWidth (), 
                                      pPart->getViewportHeight());
        
        pCam->getProjectionTranslation(t, 
                                       pPart->getViewportWidth (), 
                                       pPart->getViewportHeight());
        
        
        pPart->setupProjection(m, t);
        
        pCam->getViewing(m, 
                         pPart->getViewportWidth (),
                         pPart->getViewportHeight());
        
        
        pPart->setupViewing(m);

        pPart->setNear     (pCam->getNear());
        pPart->setFar      (pCam->getFar ());
        
        pPart->calcFrustum ();

        pPart->setBackground(pBack);
    }

    NodePtr pActNode = pAction->getActNode();

    pAction->overrideMaterial(getCPtr(_pLightPassMat), pActNode);

    pAction->pushState();

    UInt32 uiPolySlot  = pPoly->getClassId();

    pAction->addOverride     (uiPolySlot,     getCPtr(pPoly));

//    lightRenderEnter(pLight, pAction);

    pAction->recurceNoNodeCallbacks(pActNode);

    pAction->popState();

    pAction->overrideMaterial(NULL, pActNode);

    pAction->popPartition();
}

void SimpleShadowMapEngine::doAmbientPass(LightPtr      pLight,
                                          RenderAction *pAction,
                                          EngineData   *pEngineData)
{
    pAction->pushPartition((RenderPartition::CopyViewing      |
                            RenderPartition::CopyProjection   |
                            RenderPartition::CopyViewport     | 
                            RenderPartition::CopyWindow       |
                            RenderPartition::CopyViewportSize |
                            RenderPartition::CopyFrustum      |
                            RenderPartition::CopyNearFar      ));
    
    LightChunkPtr pChunk = pEngineData->getLightChunk();

    UInt32        uiSlot      = pChunk->getClassId();
    
    Int32         iLightIndex = pAction->allocateLightIndex();
    
    pAction->pushState();
    
    if(iLightIndex >= 0)
    {
        pAction->addOverride(uiSlot + iLightIndex, getCPtr(pChunk));
    }
    else
    {
        SWARNING << "maximum light source limit ("
                 << -iLightIndex
                 << ") is reached" 
                 << " skipping light sources!"
                 << std::endl;
    }
    
    pAction->recurceNoNodeCallbacks(pAction->getActNode());

    pAction->popState();
    
    pAction->popPartition ();
}

void SimpleShadowMapEngine::doFinalPass(LightPtr      pLight,
                                        RenderAction *pAction,
                                        EngineData   *pEngineData)
{
    pAction->pushPartition((RenderPartition::CopyViewing      |
                            RenderPartition::CopyProjection   |
                            RenderPartition::CopyViewport     | 
                            RenderPartition::CopyWindow       |
                            RenderPartition::CopyViewportSize |
                            RenderPartition::CopyFrustum      |
                            RenderPartition::CopyNearFar      ));
    
    FrameBufferObject *pTarget = getCPtr(this->getRenderTarget());

    if(pTarget == NULL)
    {
        FrameBufferObjectPtr pFBO = FrameBufferObject::create();

        pFBO->setWidth (this->getWidth ());
        pFBO->setHeight(this->getHeight());

        setRenderTarget(pFBO);

        pTarget = getCPtr(pFBO);
    }

    BlendChunkPtr pBlender      = pEngineData->getBlendChunk();

    if(pBlender == NullFC)
    {
        pBlender = BlendChunk::create();
        
        pBlender->setSrcFactor(GL_ONE);
        pBlender->setDestFactor(GL_ONE);
        pBlender->setAlphaFunc(GL_GEQUAL);
        pBlender->setAlphaValue(0.99);
        
        pEngineData->setBlendChunk(pBlender);
    }


    Matrix4f projectionMatrix, viewMatrix, biasMatrix;
    
    biasMatrix.setIdentity();
    biasMatrix.setScale(0.5);
    biasMatrix.setTranslate(0.5,0.5,0.5);
    
    MatrixCameraPtr pCam = dynamic_cast<MatrixCameraPtr>(
        pEngineData->getCamera());

    pCam->getProjection(projectionMatrix,
                        this->getWidth (),
                        this->getHeight());
    
    pCam->getViewing   (viewMatrix,
                        this->getWidth (),
                        this->getHeight());

    Matrix textureMatrix = biasMatrix;
    textureMatrix.mult(projectionMatrix);
    textureMatrix.mult(viewMatrix);
    
    textureMatrix.transpose();
    Vec4f ps = textureMatrix[0];
    Vec4f pt = textureMatrix[1];
    Vec4f pr = textureMatrix[2];
    Vec4f pq = textureMatrix[3];
    
    TexGenChunkPtr pTexGen = pEngineData->getTexGenChunk();

    if(pTexGen == NullFC)
    {
        pTexGen = TexGenChunk::create();
        
        pEngineData->setTexGenChunk(pTexGen);
        
        NodePtr dummy = makeCoredNode<Group>();
        
        pTexGen->setSBeacon(dummy);
        pTexGen->setTBeacon(dummy);
        pTexGen->setRBeacon(dummy);
        pTexGen->setQBeacon(dummy);
        
        pTexGen->setGenFuncS(GL_EYE_LINEAR);
        pTexGen->setGenFuncT(GL_EYE_LINEAR);
        pTexGen->setGenFuncR(GL_EYE_LINEAR);
        pTexGen->setGenFuncQ(GL_EYE_LINEAR);
    }

    pTexGen->setGenFuncSPlane(ps);
    pTexGen->setGenFuncTPlane(pt);
    pTexGen->setGenFuncRPlane(pr);
    pTexGen->setGenFuncQPlane(pq);
    
    TextureObjChunkPtr pTexChunk = pEngineData->getTexChunk();

    if(pTexChunk == NullFC)
    {
        pTexChunk = TextureObjChunk::create();
        
        pEngineData->setTexChunk(pTexChunk);

        ImagePtr pImage = Image::create();
        
            // creates a image without allocating main memory.
        
        pImage->set(Image::OSG_L_PF,
                    pTarget->getWidth (), 
                    pTarget->getHeight(),
                    1, 
                    1, 
                    1, 
                    0, 
                    NULL,
                    Image::OSG_UINT8_IMAGEDATA, 
                    false);
        
        
        pTexChunk->setImage         (pImage);
        pTexChunk->setInternalFormat(GL_DEPTH_COMPONENT32);
        pTexChunk->setExternalFormat(GL_DEPTH_COMPONENT);
        pTexChunk->setMinFilter     (GL_LINEAR);
        pTexChunk->setMagFilter     (GL_LINEAR);
        pTexChunk->setWrapS         (GL_CLAMP_TO_BORDER);
        pTexChunk->setWrapT         (GL_CLAMP_TO_BORDER);
//        pTexChunk->setEnvMode       (GL_MODULATE);
        pTexChunk->setTarget        (GL_TEXTURE_2D);
        
        pTexChunk->setCompareMode(GL_COMPARE_R_TO_TEXTURE);
        pTexChunk->setCompareFunc(GL_LEQUAL);
        pTexChunk->setDepthMode  (GL_INTENSITY);
    }

    pAction->pushState();

    UInt32 uiBlendSlot  = pBlender ->getClassId();
    UInt32 uiTexSlot    = pTexChunk->getClassId();
    UInt32 uiTexGenSlot = pTexGen  ->getClassId();
    
    if(this->getForceTextureUnit() != -1)
    {
        uiTexSlot    += this->getForceTextureUnit();
        uiTexGenSlot += this->getForceTextureUnit();
    }
    else
    {
        uiTexSlot    += 3;
        uiTexGenSlot += 3;
    }

    pAction->addOverride(uiBlendSlot,  getCPtr(pBlender ));
    pAction->addOverride(uiTexSlot,    getCPtr(pTexChunk));
    pAction->addOverride(uiTexGenSlot, getCPtr(pTexGen  ));
    
    lightRenderEnter(pLight, pAction);

    pAction->recurceNoNodeCallbacks(pAction->getActNode());
 
    pAction->popState();

    pAction->popPartition ();
}


ActionBase::ResultE SimpleShadowMapEngine::runOnEnter(
    LightPtr      pLight,
    LightTypeE    eType,
    RenderAction *pAction)
{
    EngineData *pEngineData = 
        pAction->getData<SimpleShadowMapEngineData *>(_iDataSlotId);

    if(pEngineData == NULL)
    {
        pEngineData = EngineData::create();

        this->setData(pEngineData, _iDataSlotId, pAction);
//        pAction->setData(pEngineData, _iDataSlotId);
    }

    BitVector bvMask = pAction->getPassMask() & (bvLightPassMask   |
                                                 bvAmbientPassMask |
                                                 bvDiffusePassMask );

/*
    fprintf(stderr, "%p %llu %llu | %llu %llu %llu\n",
            this,
            bvMask,
            (bvLightPassMask   |
             bvAmbientPassMask |
             bvDiffusePassMask ),
            bvLightPassMask,
            bvAmbientPassMask,
            bvDiffusePassMask);
 */

    if(0x0000 != bvMask)
    {
        if(0x0000 != (bvMask & bvDiffusePassMask))
        {
            pAction->recurceNoNodeCallbacks(pAction->getActNode());
            
            setupCamera    (pLight, eType, pAction, pEngineData);
            doFinalPass    (pLight,  pAction, pEngineData);
        }

        if(0x0000 != (bvMask & bvAmbientPassMask))
        {
            pAction->recurceNoNodeCallbacks(pAction->getActNode());
            
            setupLightChunk(pLight, eType, pAction, pEngineData);
        }

        if(0x0000 != (bvMask & bvLightPassMask))
        {
            pAction->recurceNoNodeCallbacks(pAction->getActNode());
            
            doLightPass    (pLight,        pAction, pEngineData);
        }
    }
    else
    {
        setupCamera    (pLight, eType, pAction, pEngineData);
        setupLightChunk(pLight, eType, pAction, pEngineData);

        pAction->addPassMask(bvDiffusePassMask);
        doFinalPass    (pLight,        pAction, pEngineData);
        pAction->subPassMask(bvDiffusePassMask);
        
        pAction->addPassMask(bvAmbientPassMask);
        doAmbientPass  (pLight,        pAction, pEngineData);
        pAction->subPassMask(bvAmbientPassMask);

        
        pAction->addPassMask(bvLightPassMask);
        doLightPass    (pLight,        pAction, pEngineData);
        pAction->subPassMask(bvLightPassMask);
                
    }

    return ActionBase::Skip;
}

ActionBase::ResultE SimpleShadowMapEngine::runOnLeave(
    LightPtr      pLight,
    LightTypeE    eType,
    RenderAction *pAction)
{
    return ActionBase::Continue;
}

