/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGTime.h"

#include "OSGHDR2Stage.h"
#include "OSGHDR2StageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGChunkMaterial.h"
#include "OSGBlendChunk.h"
#include "OSGDepthChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGImageFunctions.h"
#include "OSGStateOverride.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleSHLFunctions.h"
#include "OSGSimpleSHLVariableChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"

#include "OSGMatrixUtility.h"

#include "OSGGLU.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHDR2StageBase.cpp file.
// To modify it, please change the .fcd file (OSGHDR2Stage.fcd) and
// regenerate the base file.

static Real64 Log2(Real64 number);
static Int32 MipmapLevels(Int32 n);
static std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset);

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 HDR2Stage::_uiFramebufferObjectExt = 
    Window::invalidExtensionID;

UInt32 HDR2Stage::_uiFuncDrawBuffers      =
    Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HDR2Stage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            HDR2Stage::getClassType(), 
            reinterpret_cast<Action::Callback>(&HDR2Stage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            HDR2Stage::getClassType(), 
            reinterpret_cast<Action::Callback>(&HDR2Stage::renderLeave));

        _uiFramebufferObjectExt = 
            Window::registerExtension("GL_ARB_framebuffer_object");

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebufferObjectExt);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HDR2Stage::HDR2Stage(void) :
    Inherited()
{
}

HDR2Stage::HDR2Stage(const HDR2Stage &source) :
    Inherited(source)
{
}

HDR2Stage::~HDR2Stage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HDR2Stage::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HDR2Stage::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                     const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump HDR2Stage NI" << std::endl;
}

/*------------------------------- Draw ------------------------------------*/

Action::ResultE HDR2Stage::renderEnter(Action* action)
{
    RenderAction* a = dynamic_cast<RenderAction*>(action);

    a->disableDefaultPartition();

    Int32 iVPWidth  = a->getActivePartition()->getViewportWidth ();
    Int32 iVPHeight = a->getActivePartition()->getViewportHeight();

    this->beginPartitionGroup(a);
    {
        this->pushPartition(a);
        {
            RenderPartition   *pPart    = a   ->getActivePartition();
            FrameBufferObject *pTarget  = this->getRenderTarget   ();
            Viewarea          *pArea    = a   ->getViewarea       ();
            Camera            *pCam     = a   ->getCamera         ();
            Background        *pBack    = a   ->getBackground     ();
            
            if(pTarget == NULL)
            {
                this->initData(a, iVPWidth, iVPHeight);

                pTarget  = this->getRenderTarget();
            }
            else
            {
                this->updateData(a, iVPWidth, iVPHeight);
            }

            pPart->setRenderTarget(pTarget);
            pPart->getDrawEnv().setTargetBufferFormat(getColorBufferInternalFormat());

#ifdef OSG_DEBUGX
            std::string szMessage("HDR2: RenderPartition\n");
            pPart->setDebugString(szMessage          );
#endif

            if(pArea != NULL)
            {
                pPart->setWindow  (a->getWindow());
                
                if(pTarget != NULL)
                {
#if 0
                    pPart->calcViewportDimension(pArea->getLeft  (),
                                                 pArea->getBottom(),
                                                 pArea->getRight (),
                                                 pArea->getTop   (),
                                                 
                                                 pTarget->getWidth    (),
                                                 pTarget->getHeight   ());
#endif
                    pPart->calcViewportDimension(0.f,
                                                 0.f,
                                                 1.f,
                                                 1.f,
                                                 
                                                 pTarget->getWidth    (),
                                                 pTarget->getHeight   ());

                }
                else
                {
                    pPart->calcViewportDimension(pArea->getLeft  (),
                                                 pArea->getBottom(),
                                                 pArea->getRight (),
                                                 pArea->getTop   (),
                                                 
                                                 a->getWindow()->getWidth (),
                                                 a->getWindow()->getHeight());
                }

                if(pCam != NULL)
                {
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
                    
                    pPart->calcFrustum();
                }
                
                pPart->setBackground(pBack);
            }
            
            this->recurseFromThis(a);
        }
        this->popPartition(a);

        a->getActivePartition()->disable();

        this->pushPartition(a,
                            (RenderPartition::CopyWindow       |
                             RenderPartition::CopyViewportSize |
                             RenderPartition::CopyTarget       ),
                             RenderPartition::SimpleCallback    );
        {
            RenderPartition *pPart  = a->getActivePartition();

#ifdef OSG_DEBUGX
            std::string szMessage("HDR2: PostProcessPartition\n");
            pPart->setDebugString(szMessage          );
#endif

            Matrix m, t;

            m.setIdentity();
            t.setIdentity();
                
            pPart->setupProjection(m, t);

            RenderPartition::SimpleDrawCallback f;

            f = boost::bind(&HDR2Stage::postProcess, this, _1);

            pPart->dropFunctor(f);
        }
        this->popPartition(a);
    }
    this->endPartitionGroup(a);

    return Action::Skip;
}

Action::ResultE HDR2Stage::renderLeave(Action *action)
{
    return Action::Skip;
}

/*------------------------------ Data -------------------------------------*/

void HDR2Stage::initData(RenderAction* pAction,
                         Int32         iVPWidth,
                         Int32         iVPHeight)
{
    HDR2StageDataUnrecPtr pData = pAction->getData<HDR2StageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(iVPWidth, iVPHeight);

        this->setData(pData, _iDataSlotId, pAction);
    }
}

void HDR2Stage::updateData(RenderAction* pAction,
                           Int32         iVPWidth,
                           Int32         iVPHeight)
{
    HDR2StageDataUnrecPtr pData = pAction->getData<HDR2StageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        initData(pAction, iVPWidth, iVPHeight);

        pData = pAction->getData<HDR2StageData *>(_iDataSlotId);

        Camera* pCam = pAction->getCamera();
        if (pCam)
        {
            pData->setZNear(pCam->getNear());
            pData->setZFar (pCam->getFar());
        }
    }
    else
    {
        Camera* pCam = pAction->getCamera();
        if (pCam)
        {
            pData->setZNear(pCam->getNear());
            pData->setZFar (pCam->getFar());
        }

        updateStageData(pData, iVPWidth, iVPHeight);
    }

    
}

/*---------------------------- StageData ----------------------------------*/

HDR2StageDataTransitPtr HDR2Stage::setupStageData(Int32 iPixelWidth,
                                                  Int32 iPixelHeight)
{
    HDR2StageDataUnrecPtr hdrStageData = HDR2StageData::createLocal();

    if(hdrStageData == NULL)
        return HDR2StageDataTransitPtr(NULL);

    hdrStageData->setWidth (iPixelWidth );
    hdrStageData->setHeight(iPixelHeight);

    OSG::Thread::setCurrentLocalFlags();

    setupUBOData        (hdrStageData);
    setupSharedData     (hdrStageData);
    setupRenderTargets  (hdrStageData, iPixelWidth, iPixelHeight);
    setupMaterials      (hdrStageData);

    return HDR2StageDataTransitPtr(hdrStageData);
}

void HDR2Stage::updateStageData(HDR2StageData* pData,
                                Int32          iPixelWidth,
                                Int32          iPixelHeight)
{
    bool resize = false;

    if (iPixelWidth != pData->getWidth() || iPixelHeight != pData->getHeight())
        resize = true;

    pData->setWidth (iPixelWidth );
    pData->setHeight(iPixelHeight);

    updateUBOData      (pData);
    updateSharedData   (pData);

    if (resize)
        updateRenderTargets(pData, iPixelWidth, iPixelHeight);

    updateMaterials    (pData);

    commitChanges();
}

/*------------------------ StageData Details ------------------------------*/

std::size_t HDR2Stage::calcUBOBufferSize()
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float BloomThreshold
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float BloomMagnitude
    ao = align_offset( 4, bo); bo = ao + sizeof(UInt32);   // int   ToneMapTechnique
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Exposure
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float KeyValue
    ao = align_offset( 4, bo); bo = ao + sizeof(UInt32);   // int   AutoExposure
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float WhiteLevel
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ShoulderStrength
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LinearStrength
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LinearAngle
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ToeStrength
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ToeNumerator
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float ToeDenominator
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LinearWhite
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float LumSaturation
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Bias
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Tau
    ao = align_offset( 4, bo); bo = ao + sizeof(Int32);    // int   nTaps
    ao = align_offset( 4, bo); bo = ao + sizeof(Real32);   // float Sigma
    ao = align_offset( 4, bo); bo = ao + sizeof(Int32);    // bool  UseLinChromInterp
    ao = align_offset( 4, bo); bo = ao;                    // padding
    return ao;
}

void HDR2Stage::fillUBOBuffer(std::vector<OSG::UInt8>& buffer)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getBloomThreshold();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getBloomMagnitude();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = getToneMappingMode();
    bo = ao + sizeof(OSG::UInt32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getExposure();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getKeyValue();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = getAutoExposureMode();
    bo = ao + sizeof(OSG::UInt32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getWhiteLevel();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicShoulderStrenght();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicLinearStrength();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicLinearAngle();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicToeStrength();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicToeNumerator();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicToeDenominator();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getFilmicLinearWhite();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getSaturation();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getDragoBias();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getTau();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = getNumTaps();
    bo = ao + sizeof(OSG::Int32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = getBlurGaussSigma();
    bo = ao + sizeof(OSG::Real32);

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = getUseLinChromCorrection();
    bo = ao + sizeof(OSG::Int32);
}

void HDR2Stage::setupUBOData(HDR2StageData* pHDRData)
{
    UniformBufferObjStd140ChunkUnrecPtr uboChunk = UniformBufferObjStd140Chunk::createLocal();
    std::vector<OSG::UInt8> buffer(calcUBOBufferSize());
    fillUBOBuffer(buffer);

    uboChunk->editMFBuffer()->setValues(buffer);
    uboChunk->setUsage(GL_DYNAMIC_DRAW);

    pHDRData->setHdrShaderData(uboChunk);
}

void HDR2Stage::updateUBOData(HDR2StageData* pHDRData)
{
    UniformBufferObjStd140Chunk* uboChunk = pHDRData->getHdrShaderData();
    std::vector<OSG::UInt8> buffer(calcUBOBufferSize());
    fillUBOBuffer(buffer);

    uboChunk->editMFBuffer()->setValues(buffer);
}

void HDR2Stage::setupSharedData(HDR2StageData* pHDRData)
{
    TextureEnvChunkUnrecPtr texEnvChunk = TextureEnvChunk::createLocal();
    texEnvChunk->setEnvMode (GL_REPLACE);
    pHDRData->setSharedTextureEnvChunk(texEnvChunk);

    MaterialChunkUnrecPtr matChunk = MaterialChunk::createLocal();
    matChunk->setLit(false);
    pHDRData->setSharedMaterialChunk(matChunk);
}

void HDR2Stage::updateSharedData(HDR2StageData* pHDRData)
{
}

void HDR2Stage::setupRenderTargets(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    setupSceneRenderTarget          (pData, iPixelWidth, iPixelHeight);
    setupLuminanceRenderTarget      (pData, iPixelWidth, iPixelHeight);
    setupAdaptLuminanceRenderTarget (pData, iPixelWidth, iPixelHeight);

    if (getPerformBloom())
    {
        setupThresholdRenderTarget      (pData, iPixelWidth, iPixelHeight);
        setupScaleRenderTarget          (pData, iPixelWidth, iPixelHeight);
        setupBlurRenderTarget           (pData, iPixelWidth, iPixelHeight);
    }

    setupCompositeRenderTarget      (pData, iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateRenderTargets(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    updateSceneRenderTarget         (pData, iPixelWidth, iPixelHeight);
    updateLuminanceRenderTarget     (pData, iPixelWidth, iPixelHeight);
    updateAdaptLuminanceRenderTarget(pData, iPixelWidth, iPixelHeight);

    if (getPerformBloom())
    {
        updateThresholdRenderTarget     (pData, iPixelWidth, iPixelHeight);
        updateScaleRenderTarget         (pData, iPixelWidth, iPixelHeight);
        updateBlurRenderTarget          (pData, iPixelWidth, iPixelHeight);
    }

    updateCompositeRenderTarget     (pData, iPixelWidth, iPixelHeight);
}

void HDR2Stage::setupMaterials(HDR2StageData* pData)
{
    setupSceneMaterial         (pData);
    setupLuminanceMapMaterial  (pData);
    setupAdaptLuminanceMaterial(pData);

    if (getPerformBloom())
    {
        setupThresholdMaterial     (pData);
        setupScaleMaterial         (pData);
        setupBlurHorizMaterial     (pData);
        setupBlurVertMaterial      (pData);
    }

    setupCompositeMaterial     (pData);
    setupFinalScreenMaterial   (pData);
}

void HDR2Stage::updateMaterials(HDR2StageData* pData)
{
    updateSceneMaterial         (pData);
    updateLuminanceMapMaterial  (pData);
    updateAdaptLuminanceMaterial(pData);

    if (getPerformBloom())
    {
        updateThresholdMaterial     (pData);
        updateScaleMaterial         (pData);
        updateBlurHorizMaterial     (pData);
        updateBlurVertMaterial      (pData);
    }

    updateCompositeMaterial     (pData);
    updateFinalScreenMaterial   (pData);
}

void HDR2Stage::setupSceneRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pSceneFBO = FrameBufferObject::createLocal();
    pSceneFBO->setSize(iPixelWidth, iPixelHeight);

    if (getNumSamples() > 1)
    {
        pSceneFBO->setEnableMultiSample(true);
        pSceneFBO->setColorSamples(getNumSamples());
    }

    ImageUnrecPtr pSceneImg = Image ::createLocal();
    pSceneImg->set(getColorBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getColorBufferType(), false);

    TextureObjChunkUnrecPtr pSceneTexObjChunk = TextureObjChunk::createLocal();
    pSceneTexObjChunk->setImage         (pSceneImg); 
    pSceneTexObjChunk->setMinFilter     (GL_LINEAR);
    pSceneTexObjChunk->setMagFilter     (GL_LINEAR);
    pSceneTexObjChunk->setWrapS         (GL_REPEAT);
    pSceneTexObjChunk->setWrapT         (GL_REPEAT);
    pSceneTexObjChunk->setInternalFormat(getColorBufferInternalFormat());

    ImageUnrecPtr pDepthImg = Image ::createLocal();
    pDepthImg->set(getDepthBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getDepthBufferType(), false);

    TextureObjChunkUnrecPtr pDepthTexObjChunk = TextureObjChunk::createLocal();
    pDepthTexObjChunk->setImage         (pDepthImg); 
    pDepthTexObjChunk->setMinFilter     (GL_LINEAR);
    pDepthTexObjChunk->setMagFilter     (GL_LINEAR);
    pDepthTexObjChunk->setWrapS         (GL_REPEAT);
    pDepthTexObjChunk->setWrapT         (GL_REPEAT);
    pDepthTexObjChunk->setInternalFormat(getDepthBufferInternalFormat());

    TextureBufferUnrecPtr pSceneTexBuffer = TextureBuffer::createLocal();
    TextureBufferUnrecPtr pDepthTexBuffer = TextureBuffer::createLocal();

    pSceneTexBuffer->setTexture(pSceneTexObjChunk);
    pDepthTexBuffer->setTexture(pDepthTexObjChunk);

    pSceneFBO->setColorAttachment(pSceneTexBuffer, 0);
    pSceneFBO->setDepthAttachment(pDepthTexBuffer);

    pSceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setSceneRenderTarget(pSceneFBO);

    setRenderTarget(pSceneFBO);
}

void HDR2Stage::setupLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pInitLuminanceFBO = FrameBufferObject::createLocal();
    pInitLuminanceFBO->setSize(iPixelWidth, iPixelHeight);

    ImageUnrecPtr pInitLuminanceImg = Image ::createLocal();
    pInitLuminanceImg->set(getLumBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getLumBufferType(), false);

    TextureObjChunkUnrecPtr pInitLuminanceTexObjChunk = TextureObjChunk::createLocal();
    pInitLuminanceTexObjChunk->setImage         (pInitLuminanceImg); 
    pInitLuminanceTexObjChunk->setMinFilter     (GL_LINEAR);
    pInitLuminanceTexObjChunk->setMagFilter     (GL_LINEAR);
    pInitLuminanceTexObjChunk->setWrapS         (GL_REPEAT);
    pInitLuminanceTexObjChunk->setWrapT         (GL_REPEAT);
    pInitLuminanceTexObjChunk->setInternalFormat(getLumBufferInternalFormat());

    TextureBufferUnrecPtr pInitLuminanceTexBuffer = TextureBuffer::createLocal();
    pInitLuminanceTexBuffer->setTexture(pInitLuminanceTexObjChunk);

    pInitLuminanceFBO->setColorAttachment(pInitLuminanceTexBuffer, 0);
    pInitLuminanceFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setLuminanceRenderTarget(pInitLuminanceFBO);
}

void HDR2Stage::setupAdaptLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth, iPixelHeight));

    for (UInt32 i = 0; i < 2; ++i)
    {
        FrameBufferObjectUnrecPtr pAdaptLuminanceFBO = FrameBufferObject::createLocal();
        pAdaptLuminanceFBO->setSize(iPixelWidth, iPixelHeight);
        pAdaptLuminanceFBO->setPostProcessOnDeactivate(true);

        ImageUnrecPtr pAdaptLuminanceImg = Image ::createLocal();
        pAdaptLuminanceImg->set(getLumBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, levels, 1, 0.0, 0, getLumBufferType(), false);

        TextureObjChunkUnrecPtr pAdaptLuminanceTexObjChunk = TextureObjChunk::createLocal();
        pAdaptLuminanceTexObjChunk->setImage         (pAdaptLuminanceImg); 
        pAdaptLuminanceTexObjChunk->setMinFilter     (GL_LINEAR_MIPMAP_LINEAR);
        pAdaptLuminanceTexObjChunk->setMagFilter     (GL_LINEAR);
        pAdaptLuminanceTexObjChunk->setWrapS         (GL_REPEAT);
        pAdaptLuminanceTexObjChunk->setWrapT         (GL_REPEAT);
        pAdaptLuminanceTexObjChunk->setInternalFormat(getLumBufferInternalFormat());

        TextureBufferUnrecPtr pAdaptLuminanceTexBuffer = TextureBuffer::createLocal();
        pAdaptLuminanceTexBuffer->setTexture(pAdaptLuminanceTexObjChunk);

        pAdaptLuminanceFBO->setColorAttachment(pAdaptLuminanceTexBuffer, 0);
        pAdaptLuminanceFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

        pData->pushToAdaptLuminanceRenderTarget(pAdaptLuminanceFBO);
    }
}

void HDR2Stage::setupThresholdRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pThresholdFBO = FrameBufferObject::createLocal();
    pThresholdFBO->setSize(iPixelWidth, iPixelHeight);

    ImageUnrecPtr pThresholdImg = Image ::createLocal();
    pThresholdImg->set(getImageBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pThresholdTexObjChunk = TextureObjChunk::createLocal();
    pThresholdTexObjChunk->setImage         (pThresholdImg); 
    pThresholdTexObjChunk->setMinFilter     (GL_LINEAR);
    pThresholdTexObjChunk->setMagFilter     (GL_LINEAR);
    pThresholdTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pThresholdTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pThresholdTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    TextureBufferUnrecPtr pThresholdTexBuffer = TextureBuffer::createLocal();
    pThresholdTexBuffer->setTexture(pThresholdTexObjChunk);

    pThresholdFBO->setColorAttachment(pThresholdTexBuffer, 0);
    pThresholdFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setThresholdRenderTarget(pThresholdFBO);
}

void HDR2Stage::setupScaleRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    for (UInt32 i = 0; i < 3; ++i)
    {
        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        FrameBufferObjectUnrecPtr pScaleFBO = FrameBufferObject::createLocal();
        pScaleFBO->setSize(w, h);

        ImageUnrecPtr pScaleImg = Image ::createLocal();
        pScaleImg->set(getImageBufferPixelFormat(), w, h, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

        TextureObjChunkUnrecPtr pScaleTexObjChunk = TextureObjChunk::createLocal();
        pScaleTexObjChunk->setImage         (pScaleImg); 
        pScaleTexObjChunk->setMinFilter     (GL_LINEAR);
        pScaleTexObjChunk->setMagFilter     (GL_LINEAR);
        pScaleTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
        pScaleTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
        pScaleTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

        TextureBufferUnrecPtr pScaleTexBuffer = TextureBuffer::createLocal();
        pScaleTexBuffer->setTexture(pScaleTexObjChunk);

        pScaleFBO->setColorAttachment(pScaleTexBuffer, 0);
        pScaleFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

        pData->pushToScaleRenderTarget(pScaleFBO);
    }
}

void HDR2Stage::setupBlurRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    UInt32 w = std::max( iPixelWidth / (1 << 3), 1);
    UInt32 h = std::max(iPixelHeight / (1 << 3), 1);

    FrameBufferObjectUnrecPtr pBlurHorizFBO = FrameBufferObject::createLocal();
    pBlurHorizFBO->setSize(w, h);

    ImageUnrecPtr pBlurHorizImg = Image ::createLocal();
    pBlurHorizImg->set(getImageBufferPixelFormat(), w, h, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pBlurHorizTexObjChunk = TextureObjChunk::createLocal();
    pBlurHorizTexObjChunk->setImage         (pBlurHorizImg); 
    pBlurHorizTexObjChunk->setMinFilter     (GL_LINEAR);
    pBlurHorizTexObjChunk->setMagFilter     (GL_LINEAR);
    pBlurHorizTexObjChunk->setWrapS         (GL_CLAMP_TO_EDGE);
    pBlurHorizTexObjChunk->setWrapT         (GL_CLAMP_TO_EDGE);
    pBlurHorizTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    TextureBufferUnrecPtr pBlurHorizTexBuffer = TextureBuffer::createLocal();
    pBlurHorizTexBuffer->setTexture(pBlurHorizTexObjChunk);

    pBlurHorizFBO->setColorAttachment(pBlurHorizTexBuffer, 0);
    pBlurHorizFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setBlurHorizRenderTarget(pBlurHorizFBO);


    FrameBufferObjectUnrecPtr pBlurVertFBO = FrameBufferObject::createLocal();
    pBlurVertFBO->setSize(w, h);

    TextureBufferUnrecPtr pBlurVertTexBuffer = TextureBuffer::createLocal();
    pBlurVertTexBuffer->setTexture(pData->getScaleTexObjChunk(2));

    pBlurVertFBO->setColorAttachment(pBlurVertTexBuffer, 0);
    pBlurVertFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);

    pData->setBlurVertRenderTarget(pBlurVertFBO);
}

void HDR2Stage::setupCompositeRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObjectUnrecPtr pCompositeFBO = FrameBufferObject::createLocal();
    pCompositeFBO->setSize(iPixelWidth, iPixelHeight);


    ImageUnrecPtr pCompositeImg = Image ::createLocal();
    pCompositeImg->set(getImageBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pCompositeTexObjChunk = TextureObjChunk::createLocal();
    pCompositeTexObjChunk->setImage         (pCompositeImg); 
    pCompositeTexObjChunk->setMinFilter     (GL_LINEAR);
    pCompositeTexObjChunk->setMagFilter     (GL_LINEAR);
    pCompositeTexObjChunk->setWrapS         (GL_REPEAT);
    pCompositeTexObjChunk->setWrapT         (GL_REPEAT);
    pCompositeTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    ImageUnrecPtr pExposureImg = Image ::createLocal();
    pExposureImg->set(getImageBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, 1, 1, 0.0, 0, getImageBufferType(), false);

    TextureObjChunkUnrecPtr pExposureTexObjChunk = TextureObjChunk::createLocal();
    pExposureTexObjChunk->setImage         (pExposureImg); 
    pExposureTexObjChunk->setMinFilter     (GL_LINEAR);
    pExposureTexObjChunk->setMagFilter     (GL_LINEAR);
    pExposureTexObjChunk->setWrapS         (GL_REPEAT);
    pExposureTexObjChunk->setWrapT         (GL_REPEAT);
    pExposureTexObjChunk->setInternalFormat(getImageBufferInternalFormat());

    TextureBufferUnrecPtr pCompositeTexBuffer = TextureBuffer::createLocal();
    TextureBufferUnrecPtr pExposureTexBuffer  = TextureBuffer::createLocal();

    pCompositeTexBuffer->setTexture(pCompositeTexObjChunk);
    pExposureTexBuffer ->setTexture(pExposureTexObjChunk);


    pCompositeFBO->setColorAttachment(pCompositeTexBuffer, 0);
    pCompositeFBO->setColorAttachment(pExposureTexBuffer,  1);
    pCompositeFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0);
    pCompositeFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT1);

    pData->setCompositeRenderTarget(pCompositeFBO);
}

void HDR2Stage::updateSceneRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getSceneRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getLuminanceRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateAdaptLuminanceRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth, iPixelHeight));

    for (UInt32 i = 0; i < 2; ++i)
    {
        FrameBufferObject* pFBO = pData->getAdaptLuminanceRenderTarget(i);

        TextureBuffer* pTexBuffer = dynamic_cast<TextureBuffer*>(pFBO->getColorAttachments(0));
        assert(pTexBuffer);

        TextureObjChunk* pTexObjChunk = pTexBuffer->getTexture();
        assert(pTexObjChunk);

        Image* pImg = pTexObjChunk->getImage();
        assert(pImg);

        pImg->set(getLumBufferPixelFormat(), iPixelWidth, iPixelHeight, 1, levels, 1, 0.0, 0, getLumBufferType(), false);

        pFBO->resizeAll(iPixelWidth, iPixelHeight);
    }
}

void HDR2Stage::updateThresholdRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getThresholdRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::updateScaleRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    for (UInt32 i = 0; i < 3; ++i)
    {
        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        FrameBufferObject* pFBO = pData->getScaleRenderTarget(i);
        pFBO->resizeAll(w, h);
    }
}

void HDR2Stage::updateBlurRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    UInt32 w = std::max( iPixelWidth / (1 << 3), 1);
    UInt32 h = std::max(iPixelHeight / (1 << 3), 1);

    FrameBufferObject* pFBOHoriz = pData->getBlurHorizRenderTarget();
    pFBOHoriz->resizeAll(w, h);

    FrameBufferObject* pFBOVert = pData->getBlurVertRenderTarget();
    pFBOVert->resizeAll(w, h);
}

void HDR2Stage::updateCompositeRenderTarget(
    HDR2StageData* pData,
    Int32          iPixelWidth,
    Int32          iPixelHeight)
{
    FrameBufferObject* pFBO = pData->getCompositeRenderTarget();
    pFBO->resizeAll(iPixelWidth, iPixelHeight);
}

void HDR2Stage::setupSceneMaterial(HDR2StageData* pData)
{
    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    pData->setSceneMaterial(chunkMat);
}

void HDR2Stage::setupLuminanceMapMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genLuminanceMapShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());
    chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);
    chunkMat->addChunk(shaderChunk);

    pData->setLuminanceMapShader(shaderChunk);
    pData->setLuminanceMapMaterial(chunkMat);
}

void HDR2Stage::setupAdaptLuminanceMaterial(HDR2StageData* pData)
{
    pData->setCurrentTime(getTimeStampMsecs(getTimeStamp()));
    pData->setLastTime   (pData->getCurrentTime());

    SimpleSHLChunkUnrecPtr shaderChunk = genAdaptLuminanceShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("TimeDelta", 0.01f);
    shaderChunk->addUniformVariable("AdjustLuminance", getAdjustLuminance());
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(
        !pData->getCurrentAdaptLuminanceIdx()), 0);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

    chunkMat->addChunk(pData->getLuminanceTexObjChunk(), 1);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 1);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);
    chunkMat->addChunk(shaderChunk);

    pData->setAdaptLuminanceShader(shaderChunk);
    pData->setAdaptLuminanceMaterial(chunkMat);
}

void HDR2Stage::setupThresholdMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunkUnrecPtr shaderChunk = genThresholdShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("InputTex2", 2);
    shaderChunk->addUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->addUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->addUniformVariable("FilterBackground", !getBloomBackground());
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 1);

    chunkMat->addChunk(pData->getDepthTexObjChunk(), 2);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 2);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);

    chunkMat->addChunk(shaderChunk);

    pData->setThresholdShader(shaderChunk);
    pData->setThresholdMaterial(chunkMat);
}

void HDR2Stage::setupScaleMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genScaleShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    pData->setScaleShader(shaderChunk);

    // 0 : down scale /2
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());

        chunkMat->addChunk(pData->getThresholdTexObjChunk(), 0);
        chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 1 : down scale /4
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());

        chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
        chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 2 : down scale /8
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());

        chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
        chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 3 : up scale / 4
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());

        chunkMat->addChunk(pData->getBlurVertTexObjChunk(), 0);
        chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }

    // 4 : up scale / 2
    {
        ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
        chunkMat->addChunk(pData->getSharedMaterialChunk());

        chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
        chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

        chunkMat->addChunk(shaderChunk);
        
        pData->pushToScaleMaterial(chunkMat);
    }
}

void HDR2Stage::setupBlurHorizMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genBloomBlurShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("Direction", Vec2f(1.f,0.f));
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getBlurVertTexObjChunk(), 0);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);

    chunkMat->addChunk(shaderChunk);

    pData->setBlurHorizShader(shaderChunk);
    pData->setBlurHorizMaterial(chunkMat);
}

void HDR2Stage::setupBlurVertMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genBloomBlurShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("Direction", Vec2f(0.f, 1.f));
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getBlurHorizTexObjChunk(), 0);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);

    chunkMat->addChunk(shaderChunk);

    pData->setBlurVertShader(shaderChunk);
    pData->setBlurVertMaterial(chunkMat);
}

void HDR2Stage::setupCompositeMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunkUnrecPtr shaderChunk = genCompositeShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);

    if (getPerformBloom())
        shaderChunk->addUniformVariable("InputTex2", 2);

    shaderChunk->addUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->addUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->addUniformBlock("HDRShaderDataBlock", 0);

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 1);

    if (getPerformBloom())
    {
        chunkMat->addChunk(pData->getScaleTexObjChunk(0), 2);
        chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 2);
    }

    chunkMat->addChunk(shaderChunk);

    chunkMat->addChunk(pData->getHdrShaderData(), 0);

    pData->setCompositeShader(shaderChunk);
    pData->setCompositeMaterial(chunkMat);
}

void HDR2Stage::setupFinalScreenMaterial(HDR2StageData* pData)
{
    SimpleSHLChunkUnrecPtr shaderChunk = genFinalScreenShader();
    shaderChunk->addUniformVariable("InputTex0", 0);
    shaderChunk->addUniformVariable("InputTex1", 1);
    shaderChunk->addUniformVariable("CarryDepth", getCarryDepth());
    shaderChunk->addUniformVariable("LinearizeDepth", getTarget() == LINEARIZED_DEPTH_TEXTURE);
    shaderChunk->addUniformVariable("zNear", pData->getZNear());
    shaderChunk->addUniformVariable("zFar",  pData->getZFar());
    
    shaderChunk->addUniformVariable("Gamma", getApplyGamma());
    shaderChunk->addUniformVariable("AccurateGamma", getAccurateGamma());

    ChunkMaterialUnrecPtr chunkMat = ChunkMaterial::createLocal();

    chunkMat->addChunk(shaderChunk);
    chunkMat->addChunk(pData->getSharedMaterialChunk());

    DepthChunkUnrecPtr depthChunk = DepthChunk::createLocal();
    if (!getForceBackground())
        depthChunk->setFunc(GL_ALWAYS);
    else
        depthChunk->setFunc(GL_LESS);

    depthChunk->setEnable(true);
    depthChunk->setReadOnly(false);
    chunkMat->addChunk(depthChunk);

    switch (getTarget())
    {
        case SCENE_TEXTURE:
            chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
            break;
        case LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getLuminanceTexObjChunk(), 0);
            break;
        case ADAPTED_LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 0);
            break;
        case THRESHOLD_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getThresholdTexObjChunk(), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case BLURRED_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case COMPOSITE_TEXTURE:
            chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case EXPOSURE_TEXTURE:
            chunkMat->addChunk(pData->getExposureTexObjChunk(), 0);
            break;
        case DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;
        case LINEARIZED_DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;

        case DOWN_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
        case DOWN_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case DOWN_SCALED_2:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case BLUR_TEXTURE:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case UPSCALED_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case UPSCALED_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
    }
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 0);

    chunkMat->addChunk(pData->getDepthTexObjChunk(), 1);
    chunkMat->addChunk(pData->getSharedTextureEnvChunk(), 1);

    pData->setFinalScreenShader(shaderChunk);
    pData->setFinalScreenMaterial(chunkMat);
}

void HDR2Stage::updateSceneMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateLuminanceMapMaterial(HDR2StageData* pData)
{
    SimpleSHLChunk* shaderChunk = pData->getLuminanceMapShader();
    shaderChunk->updateUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
}

void HDR2Stage::updateAdaptLuminanceMaterial(HDR2StageData* pData)
{
    pData->setCurrentTime(getTimeStampMsecs(getTimeStamp()));
    Real32 dt = pData->getTimeDeltaInSeconds();
    pData->setLastTime(pData->getCurrentTime());

    SimpleSHLChunk* shaderChunk = pData->getAdaptLuminanceShader();
    shaderChunk->updateUniformVariable("TimeDelta", dt);
    shaderChunk->updateUniformVariable("AdjustLuminance", getAdjustLuminance());

    ChunkMaterial* chunkMat = pData->getAdaptLuminanceMaterial();

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(!pData->getCurrentAdaptLuminanceIdx()), 0);
}

void HDR2Stage::updateThresholdMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunk* shaderChunk = pData->getThresholdShader();
    shaderChunk->updateUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->updateUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());
    shaderChunk->updateUniformVariable("FilterBackground", !getBloomBackground());

    ChunkMaterial* chunkMat = pData->getThresholdMaterial();

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
}

void HDR2Stage::updateScaleMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateBlurHorizMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateBlurVertMaterial(HDR2StageData* pData)
{
}

void HDR2Stage::updateCompositeMaterial(HDR2StageData* pData)
{
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    //iPixelWidth  = osgNextPower2(iPixelWidth);
    //iPixelHeight = osgNextPower2(iPixelHeight);

    Int32 levels = MipmapLevels(std::max(iPixelWidth,iPixelHeight));

    if (getMipmapLevel() >= 0)
        levels = getMipmapLevel();

    SimpleSHLChunk* shaderChunk = pData->getCompositeShader();

    shaderChunk->updateUniformVariable("Level", static_cast<float>(levels));
    shaderChunk->updateUniformVariable("Use_ITU_R_BT_709", getUse_ITU_R_BT_709());

    ChunkMaterial* chunkMat = pData->getCompositeMaterial();

    chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 1);
}

void HDR2Stage::updateFinalScreenMaterial(HDR2StageData* pData)
{
    SimpleSHLChunk* shaderChunk = pData->getFinalScreenShader();

    shaderChunk->updateUniformVariable("CarryDepth", getCarryDepth());
    shaderChunk->updateUniformVariable("LinearizeDepth", getTarget() == LINEARIZED_DEPTH_TEXTURE);
    shaderChunk->updateUniformVariable("zNear", pData->getZNear());
    shaderChunk->updateUniformVariable("zFar",  pData->getZFar());
    shaderChunk->updateUniformVariable("Gamma", getApplyGamma());
    shaderChunk->updateUniformVariable("AccurateGamma", getAccurateGamma());

    ChunkMaterial* chunkMat = pData->getFinalScreenMaterial();

    DepthChunkUnrecPtr depthChunk = DepthChunk::createLocal();
    if (!getForceBackground())
        depthChunk->setFunc(GL_ALWAYS);
    else
        depthChunk->setFunc(GL_LESS);

    depthChunk->setEnable(true);
    depthChunk->setReadOnly(false);
    chunkMat->addChunk(depthChunk);

    switch (getTarget())
    {
        case SCENE_TEXTURE:
            chunkMat->addChunk(pData->getSceneTexObjChunk(), 0);
            break;
        case LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getLuminanceTexObjChunk(), 0);
            break;
        case ADAPTED_LUMINANCE_TEXTURE:
            chunkMat->addChunk(pData->getAdaptLuminanceTexObjChunk(pData->getCurrentAdaptLuminanceIdx()), 0);
            break;
        case THRESHOLD_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getThresholdTexObjChunk(), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case BLURRED_TEXTURE:
            if (getPerformBloom())
                chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            else
                chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case COMPOSITE_TEXTURE:
            chunkMat->addChunk(pData->getCompositeTexObjChunk(), 0);
            break;
        case EXPOSURE_TEXTURE:
            chunkMat->addChunk(pData->getExposureTexObjChunk(), 0);
            break;
        case DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;
        case LINEARIZED_DEPTH_TEXTURE:
            chunkMat->addChunk(pData->getDepthTexObjChunk(), 0);
            break;

        case DOWN_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
        case DOWN_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case DOWN_SCALED_2:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case BLUR_TEXTURE:
            chunkMat->addChunk(pData->getScaleTexObjChunk(2), 0);
            break;
        case UPSCALED_SCALED_0:
            chunkMat->addChunk(pData->getScaleTexObjChunk(1), 0);
            break;
        case UPSCALED_SCALED_1:
            chunkMat->addChunk(pData->getScaleTexObjChunk(0), 0);
            break;
    }
}

/*---------------------------- postProcess --------------------------------*/

void HDR2Stage::postProcess(DrawEnv *pEnv)
{
    UInt32  uiActiveFBO = pEnv->getActiveFBO();
    Window* win         = pEnv->getWindow();

    HDR2StageData* pData = pEnv->getData<HDR2StageData*>(_iDataSlotId);
    if(pData == NULL)
    {
        return;
    }

    if(win->hasExtOrVersion(_uiFramebufferObjectExt, 0x0300, 0x0200) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", 
                 static_cast<void *>(win)));
        return;        
    }

    OSGGETGLFUNCBYID_GL3( glDrawBuffers,
                          osgGlDrawBuffers,
                         _uiFuncDrawBuffers,
                          win);

    glColor3f(1.f, 1.f, 1.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();


    Real32 proj_matrix[16], model_matrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);
    glGetFloatv(GL_MODELVIEW_MATRIX, model_matrix);

    calcAvgLuminance(pEnv, pData);

    if (getPerformBloom())
        bloomBlur(pEnv, pData);

    composite(pEnv, pData);

    if(uiActiveFBO != 0)
    {
        FrameBufferObject::activateFBOById(pEnv, uiActiveFBO);
    }

    drawToFinalTarget(pEnv, pData);

    pEnv->deactivateState();

    glPopMatrix();

    UInt32 currIdx = pData->getCurrentAdaptLuminanceIdx();
    pData->setCurrentAdaptLuminanceIdx(!currIdx);
}

void HDR2Stage::calcAvgLuminance(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // render luminance map
    //
    FrameBufferObject* pLuminanceRenderTarget = pData->getLuminanceRenderTarget();
    ChunkMaterial*     pLuminanceMapMaterial  = pData->getLuminanceMapMaterial();

    pLuminanceRenderTarget->activate(pEnv);

    State* pLuminanceState = pLuminanceMapMaterial->getState();

    pEnv->activateState(pLuminanceState, NULL);
    
    this->renderQuad();

    pLuminanceRenderTarget->deactivate(pEnv);

    //
    // calculate average log luminance map with mipmap generation
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    Int32 w = iPixelWidth;//Int32 w = osgNextPower2(iPixelWidth);
    Int32 h = iPixelHeight;//Int32 h = osgNextPower2(iPixelHeight);

    glViewport(0, 0, w, h);

    UInt32 idx = pData->getCurrentAdaptLuminanceIdx();

    FrameBufferObject* pAdaptLuminanceRenderTarget = pData->getAdaptLuminanceRenderTarget(idx);
    ChunkMaterial*     pAdaptLuminanceMapMaterial  = pData->getAdaptLuminanceMaterial();

    pAdaptLuminanceRenderTarget->activate(pEnv);

    State* pAdaptLuminanceState = pAdaptLuminanceMapMaterial->getState();

    pEnv->activateState(pAdaptLuminanceState, NULL);
    
    this->renderQuad();

    pAdaptLuminanceRenderTarget->deactivate(pEnv);

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Run threshold shader on scene render result
    //
    FrameBufferObject* pThresholdRenderTarget = pData->getThresholdRenderTarget();
    ChunkMaterial*     pThresholdMaterial     = pData->getThresholdMaterial();

    pThresholdRenderTarget->activate(pEnv);

    State* pThresholdState = pThresholdMaterial->getState();

    pEnv->activateState(pThresholdState, NULL);

    this->renderQuad();

    pThresholdRenderTarget->deactivate(pEnv);

    switch (getTarget())
    {
        case DOWN_SCALED_0:
            bloomBlur_DOWN_SCALED_0(pEnv, pData);
            return;
        case DOWN_SCALED_1:
            bloomBlur_DOWN_SCALED_1(pEnv, pData);
            return;
        case DOWN_SCALED_2:
            bloomBlur_DOWN_SCALED_2(pEnv, pData);
            return;
        case BLUR_TEXTURE:
            bloomBlur_BLUR_TEXTURE(pEnv, pData);
            return;
        case UPSCALED_SCALED_0:
            bloomBlur_UP_SCALED_0(pEnv, pData);
            return;
        case UPSCALED_SCALED_1:
            bloomBlur_UP_SCALED_1(pEnv, pData);
            return;
    }

    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    //
    // Upscale blurred result
    //
    for (Int32 i = 1; i >= 0; --i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i+2);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

//########################################################################################################################
void HDR2Stage::bloomBlur_DOWN_SCALED_0(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 1; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_DOWN_SCALED_1(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 2; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_DOWN_SCALED_2(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_BLUR_TEXTURE(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_UP_SCALED_0(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    //
    // Upscale blurred result
    //
    for (Int32 i = 1; i >= 1; --i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i+2);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

void HDR2Stage::bloomBlur_UP_SCALED_1(DrawEnv* pEnv, HDR2StageData* pData)
{
    //
    // Downscale threshold result
    //
    Int32 iPixelWidth  = pData->getWidth();
    Int32 iPixelHeight = pData->getHeight();

    for (Int32 i = 0; i < 3; ++i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(
            iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    //
    // Blur downscaled result
    //
    FrameBufferObject* pBlurHorizRenderTarget  = pData->getBlurHorizRenderTarget();
    FrameBufferObject* pBlurVertRenderTarget   = pData->getBlurVertRenderTarget();

    ChunkMaterial*     pBlurHorizMaterial = pData->getBlurHorizMaterial();
    ChunkMaterial*     pBlurVertMaterial  = pData->getBlurVertMaterial();

    for (Int32 i = 0; i < 4; ++i)
    {
        //
        // Horizontal pass: pData->getBlurVertTexObjChunk() is equal to pData->getScaleTexObjChunk(2) by design!
        //
        pBlurHorizRenderTarget->activate(pEnv);

        State* pBlurHorizState = pBlurHorizMaterial->getState();

        pEnv->activateState(pBlurHorizState, NULL);
    
        this->renderQuad();

        pBlurHorizRenderTarget->deactivate(pEnv);

        //
        // Vertical pass
        //
        pBlurVertRenderTarget->activate(pEnv);

        State* pBlurVertState = pBlurVertMaterial->getState();

        pEnv->activateState(pBlurVertState, NULL);
    
        this->renderQuad();

        pBlurVertRenderTarget->deactivate(pEnv);
    }

    //
    // Upscale blurred result
    //
    for (Int32 i = 1; i >= 0; --i)
    {

        UInt32 w = std::max( iPixelWidth / (1 << (i+1)), 1);
        UInt32 h = std::max(iPixelHeight / (1 << (i+1)), 1);

        glViewport(0, 0, w, h);

        FrameBufferObject* pScaleRenderTarget = pData->getScaleRenderTarget(i);
        ChunkMaterial*     pScaleMaterial     = pData->getScaleMaterial(i+2);

        pScaleRenderTarget->activate(pEnv);

        State* pScaleState = pScaleMaterial->getState();

        pEnv->activateState(pScaleState, NULL);
    
        this->renderQuad();

        pScaleRenderTarget->deactivate(pEnv);
    }

    glViewport(0, 0, iPixelWidth, iPixelHeight);
}

//########################################################################################################################

void HDR2Stage::composite(DrawEnv* pEnv, HDR2StageData* pData)
{
    FrameBufferObject* pCompositeRenderTarget = pData->getCompositeRenderTarget();
    ChunkMaterial*     pCompositeMaterial     = pData->getCompositeMaterial();

    pCompositeRenderTarget->activate(pEnv);

    State* pCompositeState = pCompositeMaterial->getState();

    pEnv->activateState(pCompositeState, NULL);

    this->renderQuad();

    pCompositeRenderTarget->deactivate(pEnv);
}

void HDR2Stage::drawToFinalTarget(DrawEnv* pEnv, HDR2StageData* pData)
{
    ChunkMaterial* pFinalScreenMaterial = pData->getFinalScreenMaterial();

    State* pFinalScreenState = pFinalScreenMaterial->getState();

    pEnv->activateState(pFinalScreenState, NULL);

    glViewport(pEnv->getPixelLeft  (), 
               pEnv->getPixelBottom(),
               pEnv->getPixelWidth (),
               pEnv->getPixelHeight());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    this->renderQuad();
}

/*-------------------------- Shader Toolbox -------------------------------*/

void HDR2Stage::genBlockHDRShaderData(std::stringstream& ost)
{
    ost << "layout (std140) uniform HDRShaderDataBlock"                                 << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float BloomThreshold;"                                                  << std::endl;
    ost << "    float BloomMagnitude;"                                                  << std::endl;
    ost << "    int   ToneMapTechnique;"                                                << std::endl;
    ost << "    float Exposure;"                                                        << std::endl;
    ost << "    float KeyValue;"                                                        << std::endl;
    ost << "    int   AutoExposure;"                                                    << std::endl;
    ost << "    float WhiteLevel;"                                                      << std::endl;
    ost << "    float ShoulderStrength;"                                                << std::endl;
    ost << "    float LinearStrength;"                                                  << std::endl;
    ost << "    float LinearAngle;"                                                     << std::endl;
    ost << "    float ToeStrength;"                                                     << std::endl;
    ost << "    float ToeNumerator;"                                                    << std::endl;
    ost << "    float ToeDenominator;"                                                  << std::endl;
    ost << "    float LinearWhite;"                                                     << std::endl;
    ost << "    float LumSaturation;"                                                   << std::endl;
    ost << "    float Bias;"                                                            << std::endl;
    ost << "    float Tau;"                                                             << std::endl;
    ost << "    int   nTaps;"                                                           << std::endl;
    ost << "    float Sigma;"                                                           << std::endl;
    ost << "    bool  UseLinChromInterp;"                                               << std::endl;
    ost << "} hdrShaderData;"                                                           << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetPrimaryInputColor(std::stringstream& ost)
{
    ost << "vec3 GetPrimaryInputColor(sampler2D sampler)"                               << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).rgb;"                                 << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncCalcLuminance(std::stringstream& ost)
{
    ost << "float CalcLuminance(vec3 color)"                                            << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    if (Use_ITU_R_BT_709)"                                                  << std::endl;
    ost << "        return max(dot(color, vec3(0.2126, 0.7152, 0.0722)), 0.0001);"      << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        return max(dot(color, vec3(0.299, 0.587, 0.114)), 0.0001);"         << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetLastLumValue(std::stringstream& ost)
{
    ost << "float GetLastLumValue(sampler2D sampler)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).x;"                                   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetCurrLumValue(std::stringstream& ost)
{
    ost << "float GetCurrLumValue(sampler2D sampler)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).x;"                                   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncLog10(std::stringstream& ost)
{
    ost << "const float inv_log_10 = 1.0 / log(10.0);"                                  << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "float Log10(float x)"                                                       << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return inv_log_10 * log(x);"                                            << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncPow(std::stringstream& ost)
{
    ost << "vec3 Pow(vec3 x, float v)"                                                  << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return pow(x, vec3(v));"                                                << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetAvgLuminance(std::stringstream& ost)
{
    ost << "float GetAvgLuminance(sampler2D sampler)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec2 texCoord = gl_FragCoord.xy / "                                     << std::endl;
    ost << "                       vec2(textureSize(sampler, int(Level)));"             << std::endl;
    ost << "    float avgLum  = textureLod(sampler, texCoord, Level).x;"                << std::endl;
    ost << "    return exp(avgLum);"                                                    << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetDepthValue(std::stringstream& ost)
{
    ost << "float GetDepthValue(sampler2D sampler)"                                     << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float depth = texture2D(sampler, TexCoord).x;"                          << std::endl;
    ost << "    return depth;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncCalcExposedColor(std::stringstream& ost)
{
    ost << "vec3 CalcExposedColor(vec3 color, float avgLuminance,"                      << std::endl;
    ost << "                      float threshold, out float exposure)"                 << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    exposure = 0;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (hdrShaderData.AutoExposure  >= 1"                                   << std::endl;
    ost << "      && hdrShaderData.AutoExposure <= 2)"                                  << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        avgLuminance = max(avgLuminance, 0.001);"                           << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "        float keyValue = 0;"                                                << std::endl;
    ost << "        if (hdrShaderData.AutoExposure == 1)"                               << std::endl;
    ost << "            keyValue = hdrShaderData.KeyValue;"                             << std::endl;
    ost << "        else if (hdrShaderData.AutoExposure == 2)"                          << std::endl;
    ost << "            keyValue = 1.03 - (2.0 / (2 + Log10(avgLuminance + 1)));"       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "        float linearExposure = (keyValue / avgLuminance);"                  << std::endl;
    ost << "        exposure = log2(max(linearExposure, 0.0001));"                      << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        exposure = hdrShaderData.Exposure;"                                 << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    exposure -= threshold;"                                                 << std::endl;
    ost << "    return max(exp2(exposure) * color, 0.0);"                               << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncColorCorrection(std::stringstream& ost)
{
    ost << "vec3 ColorCorrection(vec3 color, float pixelLuminance)"                     << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    if (hdrShaderData.UseLinChromInterp)"                                   << std::endl;
    ost << "        return ( (color / pixelLuminance - 1 ) * "                          << std::endl;
    ost << "                hdrShaderData.LumSaturation + 1 );"                         << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        return Pow(color/pixelLuminance, hdrShaderData.LumSaturation);"     << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncU2Func(std::stringstream& ost)
{
    ost << "vec3 U2Func(vec3 x)"                                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float A = hdrShaderData.ShoulderStrength;"                              << std::endl;
    ost << "    float B = hdrShaderData.LinearStrength;"                                << std::endl;
    ost << "    float C = hdrShaderData.LinearAngle;"                                   << std::endl;
    ost << "    float D = hdrShaderData.ToeStrength;"                                   << std::endl;
    ost << "    float E = hdrShaderData.ToeNumerator;"                                  << std::endl;
    ost << "    float F = hdrShaderData.ToeDenominator;"                                << std::endl;
    ost << "    return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F)) - E/F;"                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapLogarithmic(std::stringstream& ost)
{
    ost << "vec3 ToneMapLogarithmic(vec3 color)"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = Log10(1 + pixelLuminance) / "               << std::endl;
    ost << "                                Log10(1 + hdrShaderData.WhiteLevel);"       << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapExponential(std::stringstream& ost)
{
    ost << "vec3 ToneMapExponential(vec3 color)"                                        << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = 1 - exp(-pixelLuminance / "                 << std::endl;
    ost << "                                hdrShaderData.WhiteLevel);"                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapDragoLogarithmic(std::stringstream& ost)
{
    ost << "vec3 ToneMapDragoLogarithmic(vec3 color)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = Log10(1 + pixelLuminance);"                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    toneMappedLuminance /= Log10(1 + hdrShaderData.WhiteLevel);"            << std::endl;
    ost << "    toneMappedLuminance /= Log10(2 + 8 * ("                                 << std::endl;
    ost << "        pow( (pixelLuminance / hdrShaderData.WhiteLevel),"                  << std::endl;
    ost << "             Log10(hdrShaderData.Bias) / Log10(0.5))));"                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapReinhard(std::stringstream& ost)
{
    ost << "vec3 ToneMapReinhard(vec3 color)"                                           << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = pixelLuminance / (pixelLuminance + 1);"     << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapReinhardModified(std::stringstream& ost)
{
    ost << "vec3 ToneMapReinhardModified(vec3 color)"                                   << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float pixelLuminance      = CalcLuminance(color);"                      << std::endl;
    ost << "    float toneMappedLuminance = pixelLuminance * (1.0 + pixelLuminance / "  << std::endl;
    ost << "        (hdrShaderData.WhiteLevel * hdrShaderData.WhiteLevel)) / "          << std::endl;
    ost << "        (1.0 + pixelLuminance);"                                            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return toneMappedLuminance * ColorCorrection(color, pixelLuminance);"   << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicALU(std::stringstream& ost)
{
    ost << "vec3 ToneMapFilmicALU(vec3 color)"                                          << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    color = max(vec3(0), color - 0.004);"                                   << std::endl;
    ost << "    color = (color * (6.2 * color + 0.5)) / "                               << std::endl;
    ost << "            (color * (6.2 * color + 1.7)+ 0.06);"                           << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    // result has 1/2.2 baked in"                                           << std::endl;
    ost << "    return Pow(color, 2.2);"                                                << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMapFilmicU2(std::stringstream& ost)
{
    ost << "vec3 ToneMapFilmicU2(vec3 color)"                                           << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 numerator   = U2Func(color);"                                      << std::endl;
    ost << "    vec3 denominator = U2Func(vec3(hdrShaderData.LinearWhite));"            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return numerator / denominator;"                                        << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncToneMap(std::stringstream& ost)
{
    ost << "vec3 ToneMap(vec3 color, float avgLuminance,"                               << std::endl;
    ost << "             float threshold, out float exposure)"                          << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    color = CalcExposedColor(color, avgLuminance, threshold, exposure);"    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (hdrShaderData.ToneMapTechnique == 0)"                               << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        // Do nothing!"                                                     << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 1)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapLogarithmic(color);"                                 << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 2)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapExponential(color);"                                 << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 3)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapDragoLogarithmic(color);"                            << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 4)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapReinhard(color);"                                    << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 5)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapReinhardModified(color);"                            << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 6)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapFilmicALU(color);"                                   << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else if (hdrShaderData.ToneMapTechnique == 7)"                          << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        color = ToneMapFilmicU2(color);"                                    << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        // Do nothing!"                                                     << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return color;"                                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncCalcGaussianWeight(std::stringstream& ost)
{
    ost << "float CalcGaussianWeight(int sampleDist, float sigma)"                                                                          << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float twoSigma2 = 2.0 * sigma * sigma;"                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float g = 1.0 / sqrt(3.1415926 * twoSigma2);"                           << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return (g * exp(-(sampleDist * sampleDist) / twoSigma2));"              << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGetBloomColor(std::stringstream& ost)
{
    ost << "vec3 GetBloomColor(sampler2D sampler)"                                      << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return texture(sampler, TexCoord).rgb;"                                 << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncGammaCorrection(std::stringstream& ost)
{
    //
    // Mixed type power function
    //
    genFuncPow(ost);

    //
    // Gamma correction functions
    //
    ost << "vec3 ApproximationSRGBToLinear(vec3 sRGBCol)"                               << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return Pow(sRGBCol, 2.2);"                                              << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 ApproximationLinearToSRGB(vec3 linearCol)"                             << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    return Pow(linearCol, 1.0 / 2.2);"                                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "float toLinear(float x)"                                                    << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float lo = x / 12.92;"                                                  << std::endl;
    ost << "    float hi = pow((x + 0.055) / 1.055, 2.4);"                              << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return (x <= 0.04045) ? lo : hi;"                                       << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "float toSRGB(float x)"                                                      << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float lo = x * 12.92;"                                                  << std::endl;
    ost << "    float hi = (pow(abs(x), 1.0/2.4) * 1.055) - 0.055;"                     << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    return (x <= 0.0031308) ? lo : hi;"                                     << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 AccurateSRGBToLinear(vec3 sRGBCol)"                                    << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 linearRGB = vec3( toLinear(sRGBCol.r),"                            << std::endl;
    ost << "                           toLinear(sRGBCol.g),"                            << std::endl;
    ost << "                           toLinear(sRGBCol.b) );"                          << std::endl;
    ost << "    return linearRGB;"                                                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "vec3 AccurateLinearToSRGB(vec3 linearCol)"                                  << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 sRGB = vec3( toSRGB(linearCol.r),"                                 << std::endl;
    ost << "                      toSRGB(linearCol.g),"                                 << std::endl;
    ost << "                      toSRGB(linearCol.b) );"                               << std::endl;
    ost << "    return sRGB;"                                                           << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFuncLinearizeZ(std::stringstream& ost)
{
    ost << "float LinearizeZ(float depth)"                                              << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float zLinear = 2.0 * zNear  "                                          << std::endl;
    ost << "                    / (zFar + zNear - depth * (zFar - zNear));"             << std::endl;
    ost << "    return zLinear;"                                                        << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genSharedCode(std::stringstream& ost)
{
    //
    // Logarithm to base 10 currently missing form GLSL
    //
    genFuncLog10(ost);

    //
    // Mixed type power function
    //
    genFuncPow(ost);

    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Samples average luminace value from given texture at given mip map level
    //
    genFuncGetAvgLuminance(ost);

    //
    // Approximates luminance from an RGB value
    //
    genFuncCalcLuminance(ost);

    //
    // Determines the color based on exposure settings
    //
    genFuncCalcExposedColor(ost);

    //
    // Perform color correction in tone mapping
    //
    // R. Mantiuk et al
    // Color correction for tone mapping
    // https://www.cs.ubc.ca/~heidrich/Papers/EG.09_1.pdf
    //
    genFuncColorCorrection(ost);

    //
    // Logarithmic mapping
    //
    // Adaptive Logarithmic Mapping for Displaying High Contrast Scenes
    // F. Drago, K. Myszkowski, T. Annen, and N. Chiba
    // In Eurographics 2003 
    // http://resources.mpi-inf.mpg.de/tmo/logmap/logmap.pdf
    //
    genFuncToneMapLogarithmic(ost);

    //
    // Exponential mapping
    //
    genFuncToneMapExponential(ost);

    //
    // Drago's Logarithmic mapping
    //
    // Adaptive Logarithmic Mapping for Displaying High Contrast Scenes
    // F. Drago, K. Myszkowski, T. Annen, and N. Chiba
    // In Eurographics 2003 
    // http://resources.mpi-inf.mpg.de/tmo/logmap/logmap.pdf
    //
    genFuncToneMapDragoLogarithmic(ost);

    //
    // Applies Reinhard's basic tone mapping operator
    //
    // Photographic Tone Reproduction for Digital Images
    // Erik Reinhard, Michael Stark, Peter Shirley, James Ferwerda
    // http://www.cmap.polytechnique.fr/~peyre/cours/x2005signal/hdr_photographic.pdf
    //
    genFuncToneMapReinhard(ost);

    //
    // Applies Reinhard's modified tone mapping operator
    //
    // Photographic Tone Reproduction for Digital Images
    // Erik Reinhard, Michael Stark, Peter Shirley, James Ferwerda
    // http://www.cmap.polytechnique.fr/~peyre/cours/x2005signal/hdr_photographic.pdf
    //
    genFuncToneMapReinhardModified(ost);

    //
    // Applies the filmic curve from John Hable's presentation
    //
    // http://filmicgames.com/archives/75
    // http://de.slideshare.net/ozlael/hable-john-uncharted2-hdr-lighting slide 53ff
    //
    genFuncToneMapFilmicALU(ost);

    //
    // Function used by the Uncharte2D tone mapping curve
    //
    genFuncU2Func(ost);

    //
    // Applies the Uncharted 2 filmic tone mapping curve
    //
    // http://filmicgames.com/archives/75
    // http://de.slideshare.net/ozlael/hable-john-uncharted2-hdr-lighting slide 53ff
    //
    genFuncToneMapFilmicU2(ost);

    //
    // Applies exposure and tone mapping to the specific color, and applies
    // the threshold to the exposure value. 
    //
    genFuncToneMap(ost);
}

void HDR2Stage::genCommonVertexShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) in vec2 vPosition;"                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "out vec2 TexCoord;"                                                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "const vec2 madd = vec2(0.5, 0.5);"                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec4 vPos = vec4(vPosition.x, vPosition.y, 0, 1);"                      << std::endl;
    ost << "    gl_Position = vPos;"                                                    << std::endl;
    ost << "    TexCoord    = vPos.xy * madd + madd;"                                   << std::endl;
    ost << "}"                                                                          << std::endl;
}

void HDR2Stage::genLuminanceMapFragmentShader(std::stringstream& ost)
{
    //
    // This shader takes the input fragment color and writes
    // the calculated luminance. 
    //
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;"                                               << std::endl;
    ost << "uniform bool      Use_ITU_R_BT_709;"                                        << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) out float FragColor;   // only red channel"            << std::endl;
    ost << ""                                                                           << std::endl;
    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Approximates luminance from an RGB value
    //      http://www.poynton.com/PDFs/ColorFAQ.pdf
    //      http://www.poynton.com/PDFs/coloureq.pdf
    //
    genFuncCalcLuminance(ost);

    //
    // Creates the luminance map for the scene
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 color  = GetPrimaryInputColor(InputTex0);"                         << std::endl;
    ost << "    float lum   = CalcLuminance(color);"                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor   = lum;"                                                     << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genAdaptLuminanceFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Last luminance map"                      << std::endl;
    ost << "uniform sampler2D InputTex1;    // Current luminance map"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform float TimeDelta;        // timer.DeltaSecondsF()"                   << std::endl;
    ost << "uniform bool  AdjustLuminance;"                                              << std::endl;
    ost << ""                                                                           << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) out float FragColor;"                                  << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Sample the last luminance value
    //
    genFuncGetLastLumValue(ost);

    //
    // Sample the current luminance value
    //
    genFuncGetCurrLumValue(ost);

    //
    // Slowly adjusts the scene luminance based on the previous scene luminance
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float currLum = GetCurrLumValue(InputTex1);"                            << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    float adaptedLum;"                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (AdjustLuminance)"                                                   << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float lastLum = exp(GetLastLumValue(InputTex0));"                   << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "        // Adapt the luminance using Pattanaik's technique"                 << std::endl;
    ost << "        adaptedLum = lastLum + (currLum - lastLum)"                         << std::endl;
    ost << "                         * (1.0 - exp(-TimeDelta * hdrShaderData.Tau));"    << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        adaptedLum = currLum;"                                              << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor = log(adaptedLum);"                                           << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genThresholdFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                     << std::endl;
    ost << "uniform sampler2D InputTex1;    // Average luminance map"                   << std::endl;
    ost << "uniform sampler2D InputTex2;    // Depth map"                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform float     Level;  // Mipmap level"                                  << std::endl;
    ost << "uniform bool      Use_ITU_R_BT_709;"                                        << std::endl;
    ost << "uniform bool      FilterBackground;"                                        << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;"                                  << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Sample the depth value
    //
    genFuncGetDepthValue(ost);

    genSharedCode(ost);

    //
    // Uses a lower exposure to produce a value suitable for a bloom pass
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float avgLuminance = GetAvgLuminance(InputTex1);"                       << std::endl;
    ost << "    vec3 color         = GetPrimaryInputColor(InputTex0);"                  << std::endl;
    ost << "    float depth        = GetDepthValue(InputTex2);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    // calculated by the ToneMap function, not used here"                   << std::endl;
    ost << "    float exposure = 0;"                                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    color = ToneMap(color, avgLuminance,"                                   << std::endl;
    ost << "                     hdrShaderData.BloomThreshold, exposure);"              << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (FilterBackground && depth == 1.0)"                                  << std::endl;
    ost << "        FragColor = vec4(0.0);"                                             << std::endl;
    ost << "    else"                                                                   << std::endl;
    ost << "        FragColor = vec4(color, 1.0);"                                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genScaleFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                         << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                         << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                    << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "in vec2 TexCoord;"                                                         << std::endl;
    ost << ""                                                                          << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;"                                 << std::endl;
    ost << ""                                                                          << std::endl;
    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Uses hw bilinear filtering for upscaling or downscaling
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3 color = GetPrimaryInputColor(InputTex0);"                          << std::endl;
    ost << "    FragColor = vec4(color, 1.0);"                                          << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genBloomBlurFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;"                                               << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform vec2      Direction;    // {(1.0, 0.0), (0.0, 1.0)}"                << std::endl;
    ost << ""                                                                           << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout(location = 0) out vec4 FragColor;"                                   << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Calculates the gaussian blur weight for a given distance and sigmas
    //
    genFuncCalcGaussianWeight(ost);

    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec2 rcpSize = 1.0 / vec2(textureSize(InputTex0, 0).xy);"               << std::endl;
    ost << "    vec2 offset  = Direction * rcpSize;"                                    << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    vec3 color = vec3(0);"                                                  << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    for(int i = -hdrShaderData.nTaps; i <= hdrShaderData.nTaps; ++i)"       << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float weight = CalcGaussianWeight(i, hdrShaderData.Sigma);"         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "        vec2 texCoord = TexCoord + i*offset;"                               << std::endl;
    ost << "        color += weight * texture(InputTex0, texCoord).rgb;"                << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor = vec4(color, 1);"                                            << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genCompositeFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                     << std::endl;
    ost << "uniform sampler2D InputTex1;    // Average luminance map"                   << std::endl;
    if (getPerformBloom())
    {
    ost << "uniform sampler2D InputTex2;    // Bloom map"                               << std::endl;
    }
    ost << ""                                                                           << std::endl;
    ost << "uniform float     Level;        // Luminance Mip Map Level"                 << std::endl;
    ost << "uniform bool      Use_ITU_R_BT_709;"                                        << std::endl;
    ost << ""                                                                           << std::endl;

    genBlockHDRShaderData(ost);

    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;      // final color"              << std::endl;
    ost << "layout (location = 1) out vec3 AvgLuminance;   // exposure map"             << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Sample the bloom map
    //
    if (getPerformBloom())
        genFuncGetBloomColor(ost);

    genSharedCode(ost);

    //
    // Applies exposure and tone mapping to the input combined with bloom pass result
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    float avgLuminance = GetAvgLuminance(InputTex1);"                       << std::endl;
    ost << "    vec3 color         = GetPrimaryInputColor(InputTex0);"                  << std::endl;
    if (getPerformBloom())
    {
    ost << "    vec3 bloom         = GetBloomColor(InputTex2);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    bloom *= hdrShaderData.BloomMagnitude;"                                 << std::endl;
    }
    ost << ""                                                                           << std::endl;
    ost << "    float exposure = 0;         // calculated by the ToneMap function"      << std::endl;
    ost << "    const float threshold = 0;"                                             << std::endl;
    ost << ""                                                                           << std::endl;
    if (getPerformBloom())
    {
    ost << "    color = color + bloom;"                                                 << std::endl;
    }
    ost << "    color = ToneMap(color, avgLuminance, threshold, exposure);"             << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor    = vec4(color, 1.0);"                                       << std::endl;
    ost << "    AvgLuminance = vec3(avgLuminance, avgLuminance, avgLuminance);"         << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

void HDR2Stage::genFinalScreenFragmentShader(std::stringstream& ost)
{
    ost << "#version 330 compatibility"                                                 << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "#extension GL_ARB_separate_shader_objects: enable"                          << std::endl;
    ost << "#extension GL_ARB_uniform_buffer_object:   enable"                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform sampler2D InputTex0;    // Primary color input"                     << std::endl;
    ost << "uniform sampler2D InputTex1;    // Depth value input"                       << std::endl;
    ost << "uniform bool CarryDepth;"                                                   << std::endl;
    ost << "uniform bool LinearizeDepth;"                                               << std::endl;
    ost << "uniform float zNear;"                                                       << std::endl;
    ost << "uniform float zFar;"                                                        << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "uniform bool Gamma;"                                                        << std::endl;
    ost << "uniform bool AccurateGamma;"                                                << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "in vec2 TexCoord;"                                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "layout (location = 0) out vec4 FragColor;"                                  << std::endl;
    ost << ""                                                                           << std::endl;

    //
    // Sample the primary input color
    //
    genFuncGetPrimaryInputColor(ost);

    //
    // Sample the depth value
    //
    genFuncGetDepthValue(ost);
    genFuncLinearizeZ(ost);

    //
    // Bunch of gamma correction functions
    //
    genFuncGammaCorrection(ost);

    //
    // Write color and depth to screen buffer
    //
    ost << "void main()"                                                                << std::endl;
    ost << "{"                                                                          << std::endl;
    ost << "    vec3  color = GetPrimaryInputColor(InputTex0);"                         << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (LinearizeDepth)"                                                    << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float zLinear = LinearizeZ(color.x);"                               << std::endl;
    ost << "        color = vec3(zLinear);"                                             << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (Gamma)"                                                             << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        if (AccurateGamma)"                                                 << std::endl;
    ost << "            color = AccurateLinearToSRGB(color);"                           << std::endl;
    ost << "        else"                                                               << std::endl;
    ost << "            color = ApproximationLinearToSRGB(color);"                      << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    FragColor = vec4(color, 1.0);"                                          << std::endl;
    ost << ""                                                                           << std::endl;
    ost << "    if (CarryDepth)"                                                        << std::endl;
    ost << "    {"                                                                      << std::endl;
    ost << "        float depth  = GetDepthValue(InputTex1);"                           << std::endl;
    ost << "        gl_FragDepth = depth;"                                              << std::endl;
    ost << "    }"                                                                      << std::endl;
    ost << "}"                                                                          << std::endl;
    ost                                                                                 << std::endl;
}

SimpleSHLChunkTransitPtr HDR2Stage::genLuminanceMapShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genLuminanceMapFragmentShader(frag);

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genAdaptLuminanceShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genAdaptLuminanceFragmentShader(frag);


    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genThresholdShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genThresholdFragmentShader(frag);

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genScaleShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genScaleFragmentShader(frag);

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genBloomBlurShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genBloomBlurFragmentShader(frag);

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genCompositeShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genCompositeFragmentShader(frag);

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

SimpleSHLChunkTransitPtr HDR2Stage::genFinalScreenShader()
{
    SimpleSHLChunkTransitPtr simpleSHLChunk = SimpleSHLChunk::createLocal();

    std::stringstream vert, frag;

    genCommonVertexShader(vert);
    genFinalScreenFragmentShader(frag);

    simpleSHLChunk->setVertexProgram(vert.str());
    simpleSHLChunk->setFragmentProgram(frag.str());

    return simpleSHLChunk;
}

static Real64 Log2(Real64 number)
{
    return log(number)/log(2.0);
}

static Int32 MipmapLevels(Int32 n)
{
    return static_cast<Int32>(1.0 + floor(Log2(n)));
}

static std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset)
{
    return base_alignment * ((base_alignment + base_offset - 1) / base_alignment);
}

OSG_END_NAMESPACE
