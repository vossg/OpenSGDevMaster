/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: Alexander Lang                                                 *
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

#include "OSGDepthPeelingStage.h"
#include "OSGDepthPeelingStageData.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGTextureBuffer.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGImageFunctions.h"
#include "OSGStateOverride.h"
#include "OSGDepthChunk.h"
#include "OSGTextureEnvChunk.h"

#include "OSGMatrixUtility.h"

#include "OSGSimpleSHLChunk.h"
#include "OSGShaderProgramChunk.h"

#include <string>

#define GL_DEPTH_COMPONENT32F 0x8CAC

namespace
{
    const bool IS_PING    = true;   //see ping-ponging
    const bool IS_PONG    = false;
    const bool IS_FINAL   = true;
    const bool IS_INITIAL = true;
    const bool DONTCARE   = false;

    const char* blendFS =
        "uniform sampler2D uSampler;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = texture2D(uSampler, gl_TexCoord[0].xy);\n"
        "}";

    const char* blendFinalFS =
        "uniform sampler2D uSampler;\n"
        "void main()\n"
        "{\n"
        "    vec4 frontColor = texture2D(uSampler, gl_TexCoord[0].xy);\n"
        "    vec3 backColor  = vec3(0.0, 0.0, 0.0);\n"
        "    gl_FragColor = vec4(frontColor.rgb + backColor * frontColor.a, 1.0);\n"
        "}";

}

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDepthPeelingStageBase.cpp file.
// To modify it, please change the .fcd file (OSGDepthPeelingStage.fcd) and
// regenerate the base file.

UInt32 DepthPeelingStage::_uiFramebufferObjectExt =
    Window::invalidExtensionID;

UInt32 DepthPeelingStage::_uiFuncDrawBuffers      =
    Window::invalidFunctionID;

UInt32 DepthPeelingStage::_uiDepthBufferFloatExt  =
    Window::invalidExtensionID;

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DepthPeelingStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            DepthPeelingStage::getClassType(),
            reinterpret_cast<Action::Callback>(
                &DepthPeelingStage::renderEnter));

        RenderAction::registerLeaveDefault(
            DepthPeelingStage::getClassType(),
            reinterpret_cast<Action::Callback>(
                &DepthPeelingStage::renderLeave));

        _uiFramebufferObjectExt =
            Window::registerExtension("GL_EXT_framebuffer_object");

        _uiDepthBufferFloatExt =
            Window::registerExtension("GL_ARB_depth_buffer_float");

//        Window::registerConstant(GL_DEPTH_COMPONENT32F);

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

DepthPeelingStage::DepthPeelingStage(void) :
    Inherited()
{
}

DepthPeelingStage::DepthPeelingStage(const DepthPeelingStage &source) :
    Inherited(source)
{
}

DepthPeelingStage::~DepthPeelingStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DepthPeelingStage::changed(ConstFieldMaskArg whichField,
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DepthPeelingStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DepthPeelingStage NI" << std::endl;
}


Action::ResultE DepthPeelingStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->disableDefaultPartition();

    Int32 iVPWidth  = a->getActivePartition()->getViewportWidth ();
    Int32 iVPHeight = a->getActivePartition()->getViewportHeight();

    //Initial stage (fill depth buffer)
    this->beginPartitionGroup(a);
    {
        setupRenderScene(a, iVPWidth, iVPHeight, IS_INITIAL, DONTCARE);

        //Peel & Blend Stage
        Int32 numLayers = (getNumPasses() - 1) * 2;

        for (Int32 i=0; i < numLayers; ++i)
        {
            if (i % 2 == 0)
            {
                setupRenderScene(a, iVPWidth, iVPHeight, !IS_INITIAL, IS_PONG);
                setupPostProcess(a, !IS_FINAL, IS_PONG);
            }
            else
            {
                setupRenderScene(a, iVPWidth, iVPHeight, !IS_INITIAL, IS_PING);
                setupPostProcess(a, !IS_FINAL, IS_PING);
            }
        }
        //Final stage: draw quad to default framebuffer
        setupPostProcess(a, IS_FINAL, DONTCARE);
    }
    this->endPartitionGroup(a);

    return Action::Skip;
}

Action::ResultE DepthPeelingStage::renderLeave(Action *action)
{
    return Action::Skip;
}

void DepthPeelingStage::initData(RenderAction *a,
                                 Int32         iVPWidth,
                                 Int32         iVPHeight)
{
    DepthPeelingStageDataUnrecPtr pData =
        a->getData<DepthPeelingStageData *>(_iDataSlotId);

    if(!pData)
    {
        pData = setupStageData(iVPWidth,
                               iVPHeight);

        pData->setWidth (iVPWidth );
        pData->setHeight(iVPHeight);

        this->setData(pData, _iDataSlotId, a);
    }
}

void DepthPeelingStage::updateData(RenderAction *a,
                                   Int32         iVPWidth,
                                   Int32         iVPHeight)
{
    DepthPeelingStageDataUnrecPtr pData =
        a->getData<DepthPeelingStageData *>(_iDataSlotId);

    if(!pData)
    {
        initData(a, iVPWidth, iVPHeight);
    }
    else if((pData->getWidth () != iVPWidth ) ||
            (pData->getHeight() != iVPHeight)  )
    {
        resizeStageData(pData,
                        iVPWidth,
                        iVPHeight);

        pData->setWidth (iVPWidth );
        pData->setHeight(iVPHeight);
    }
}

void
DepthPeelingStage::setupRenderScene(RenderAction* a,
                                    Int32         iVPWidth,
                                    Int32         iVPHeight,
                                    bool          isInitial,
                                    bool          isPing    )
{
    this->pushPartition(a);
    {
        RenderPartition   *pPart   = a->getActivePartition();
        FrameBufferObject *pTarget = NULL;
        Viewarea          *pArea   = a->getViewarea       ();
        Camera            *pCam    = a->getCamera         ();
        Background        *pBack   = NULL;


        DepthPeelingStageDataUnrecPtr pData =
            a->getData<DepthPeelingStageData *>(_iDataSlotId);

        if(!pData)
        {
            this->initData(a, iVPWidth, iVPHeight);
        }
        else
        {
            this->updateData(a, iVPWidth, iVPHeight);
        }
        pData = a->getData<DepthPeelingStageData *>(_iDataSlotId);

        if (isInitial)
        {
            pTarget = pData->getBlendFBO();
            pBack   = a->getBackground  ();
        }
        else
        {
            if (isPing)
                pTarget = pData->getPeelPingFBO();
            else
                pTarget = pData->getPeelPongFBO();

            pBack = pData->getBackground();
        }
        pPart->setRenderTarget(pTarget);

        if(pArea != NULL)
        {
            pPart->setWindow  (a->getWindow());

            if(pTarget != NULL)
            {
                pPart->calcViewportDimension(pArea->getLeft  (),
                                                pArea->getBottom(),
                                                pArea->getRight (),
                                                pArea->getTop   (),

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

        pPart->addSetupModeBit(RenderPartition::BackgroundSetup);

        pPart->pushState();
        if (!isInitial)
        {
            FrameBufferObject* fbo           =
                isPing ? pData->getPeelPongFBO() : pData->getPeelPingFBO();
            TextureBuffer*     texbuf        =
                static_cast<TextureBuffer *>(fbo->getDepthAttachment());
            TextureObjChunk*   depthTexChunk = texbuf->getTexture();

            pPart->addOverride(depthTexChunk->getClassId() + getDepthTexUnit(),
                               depthTexChunk                                   );
            pPart->addOverride(pData->getSpvIsPeelChunk()->getClassId(),
                               pData->getSpvIsPeelChunk()               );
        }
        else
        {
            pPart->addOverride(pData->getSpvIsInitialChunk()->getClassId(),
                               pData->getSpvIsInitialChunk()               );
        }

        pPart->addOverride(pData->getDepthChunk()->getClassId(),
                           pData->getDepthChunk()               );

        this->recurseFromThis(a);
        a->useNodeList(false);

        pPart->popState();
    }
    this->popPartition(a);
}

void
DepthPeelingStage::setupPostProcess(RenderAction* a, bool isFinal, bool isPing)
{
    this->pushPartition(a,
                        (RenderPartition::CopyWindow      |
                         RenderPartition::CopyViewportSize),
                         RenderPartition::SimpleCallback    );
    {
        RenderPartition *pPart  = a->getActivePartition();

        Matrix m, t;

        m.setIdentity();
        t.setIdentity();

        MatrixOrthogonal( m,
                            0.f, 1.f,
                            0.f, 1.f,
                            -1.f, 1.f);

        pPart->setupProjection(m, t);

        RenderPartition::SimpleDrawCallback f;

        if (!isFinal)
            f = boost::bind(&DepthPeelingStage::postProcess, this, _1, isPing);
        else
            f = boost::bind(&DepthPeelingStage::postProcessFinal, this, _1);

        pPart->dropFunctor(f);
    }
    this->popPartition(a);
}

void DepthPeelingStage::postProcess(DrawEnv *pEnv, bool isPing)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtOrVersion(_uiFramebufferObjectExt, 0x0300, 0x0200) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;
    }

    DepthPeelingStageData *pData =
        pEnv->getData<DepthPeelingStageData *>(_iDataSlotId);

    if(!pData)
        return;

    FrameBufferObject *pBlendFBO  = pData->getBlendFBO();
    pBlendFBO->activate(pEnv);

    ChunkMaterial *pMaterial;
    if (isPing)
        pMaterial = pData->getPeelPingMaterial();
    else
        pMaterial = pData->getPeelPongMaterial();

    pEnv->activateState(pMaterial->getState(), NULL);

    drawQuad();

    pEnv->deactivateState();

    pBlendFBO->deactivate(pEnv);
}

void
DepthPeelingStage::postProcessFinal(DrawEnv *pEnv)
{
    DepthPeelingStageData *pData =
        pEnv->getData<DepthPeelingStageData *>(_iDataSlotId);

    if(!pData)
        return;

    State *pBlendFinalState = pData->getBlendFinalMaterial()->getState();

    pEnv->activateState(pBlendFinalState, NULL);

    drawQuad();

    pEnv->deactivateState();
}

void DepthPeelingStage::drawQuad(void)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.f, 0.f);
        glVertex2f  (0.f, 0.f);

        glTexCoord2f(1.f, 0.f);
        glVertex2f  (1.f, 0.f);

        glTexCoord2f(1.f, 1.f);
        glVertex2f(1.f, 1.f);

        glTexCoord2f(0.f, 1.f);
        glVertex2f  (0.f, 1.f);
    }
    glEnd();

    glPopMatrix();
}

DepthPeelingStageDataTransitPtr
    DepthPeelingStage::setupStageData(Int32 iPixelWidth,
                                      Int32 iPixelHeight)
{
    DepthPeelingStageDataTransitPtr returnValue =
        DepthPeelingStageData::createLocal();

    if(returnValue == NULL)
        return returnValue;

    OSG::Thread::setCurrentLocalFlags();

    //Depth, Blend chunks and Background in Data?
    DepthChunkUnrecPtr pDepthOffChunk = DepthChunk::createLocal();
    pDepthOffChunk->setEnable(false);

    DepthChunkUnrecPtr pDepthOnChunk = DepthChunk::createLocal();
    pDepthOnChunk->setEnable(true);

    returnValue->setDepthChunk(pDepthOnChunk);

    ShaderProgramVariableChunkUnrecPtr pSPVChunk1 =
        ShaderProgramVariableChunk::createLocal();
    pSPVChunk1->addUniformVariable("uIsPeelPass", true);

    returnValue->setSpvIsPeelChunk(pSPVChunk1);

    ShaderProgramVariableChunkUnrecPtr pSPVChunk2 =
        ShaderProgramVariableChunk::createLocal();
    pSPVChunk2->addUniformVariable("uIsPeelPass", false);

    returnValue->setSpvIsInitialChunk(pSPVChunk2);

    BlendChunkUnrecPtr pBlendChunk = BlendChunk::createLocal();
    pBlendChunk->setSrcFactor(GL_DST_ALPHA);
    pBlendChunk->setDestFactor(GL_ONE);
    pBlendChunk->setAlphaSrcFactor(GL_ZERO);
    pBlendChunk->setAlphaDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    pBlendChunk->setEquation(GL_FUNC_ADD);

    SolidBackgroundUnrecPtr pSolidBackground = SolidBackground::createLocal();
    pSolidBackground->setColor(Color3f(0.f, 0.f, 0.f));
    pSolidBackground->setAlpha(0.f);
    returnValue->setBackground(pSolidBackground);

    SimpleSHLChunkUnrecPtr pQuadShader = SimpleSHLChunk::createLocal();
    pQuadShader->setFragmentProgram(std::string(blendFS));
    pQuadShader->addUniformVariable("uSampler", 0);

    //2 FBOs (Ping-Pong)
    FrameBufferObjectUnrecPtr pPeelFBOs[2];
    TextureBufferUnrecPtr pPeelColorTexBuffers[2];
    TextureBufferUnrecPtr pPeelDepthTexBuffers[2];

    TextureObjChunkUnrecPtr pColorTexs[2];
    ImageUnrecPtr           pColorImgs[2];

    TextureObjChunkUnrecPtr pDepthTexs[2];
    ImageUnrecPtr           pDepthImgs[2];

    for (int i=0; i<2; ++i)
    {
        //Color textures
        pColorTexs[i]     = TextureObjChunk::createLocal();
        pColorImgs[i]     = Image          ::createLocal();

        pColorImgs[i]->set(Image::OSG_RGBA_PF,
                  iPixelWidth,
                  iPixelHeight,
                  1,
                  1,
                  1,
                  0.0,
                  0,
                  Image::OSG_FLOAT32_IMAGEDATA,
                  false);

        pColorTexs[i]   ->setImage         (pColorImgs[i]   );
        pColorTexs[i]   ->setMinFilter     (GL_NEAREST       );
        pColorTexs[i]   ->setMagFilter     (GL_NEAREST       );
        pColorTexs[i]   ->setWrapS         (GL_CLAMP_TO_EDGE );
        pColorTexs[i]   ->setWrapT         (GL_CLAMP_TO_EDGE );
        pColorTexs[i]   ->setInternalFormat(GL_RGBA8);

        pPeelColorTexBuffers[i]   = TextureBuffer::createLocal();
        pPeelColorTexBuffers[i]->setTexture(pColorTexs[i]);

        //Depth textures
        pDepthTexs[i]      = TextureObjChunk::createLocal();
        pDepthImgs[i]      = Image          ::createLocal();

        pDepthImgs[i]->set(Image::OSG_DEPTH_PF,
                  iPixelWidth,
                  iPixelHeight,
                  1,
                  1,
                  1,
                  0.0,
                  0,
                  Image::OSG_FLOAT32_IMAGEDATA,
                  false);

        pDepthTexs[i]   ->setImage         (pDepthImgs[i]   );
        pDepthTexs[i]   ->setMinFilter     (GL_NEAREST       );
        pDepthTexs[i]   ->setMagFilter     (GL_NEAREST       );
        pDepthTexs[i]   ->setWrapS         (GL_CLAMP_TO_EDGE );
        pDepthTexs[i]   ->setWrapT         (GL_CLAMP_TO_EDGE );
        pDepthTexs[i]   ->setInternalFormat(GL_DEPTH_COMPONENT32F);
        pDepthTexs[i]   ->setExternalFormat(GL_DEPTH_COMPONENT);

        pPeelDepthTexBuffers[i] = TextureBuffer::createLocal();
        pPeelDepthTexBuffers[i]->setTexture(pDepthTexs[i]);

        pPeelFBOs[i] = FrameBufferObject::createLocal();

        pPeelFBOs[i]->setSize(iPixelWidth, iPixelHeight);
        pPeelFBOs[i]->setColorAttachment(pPeelColorTexBuffers[i], 0);
        pPeelFBOs[i]->setDepthAttachment(pPeelDepthTexBuffers[i]);
        pPeelFBOs[i]->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

        //Peel material for Quad (!)
        ChunkMaterialUnrecPtr pPeelMat  = ChunkMaterial  ::createLocal();
        pPeelMat->addChunk(pQuadShader, 0);
        pPeelMat->addChunk(pColorTexs[i],     0);
        pPeelMat->addChunk(pDepthOffChunk);
        pPeelMat->addChunk(pBlendChunk);

        if (i == 0)
        {
            returnValue->setPeelPingFBO(pPeelFBOs[i]);
            returnValue->setPeelPingMaterial(pPeelMat);
        }
        else
        {
            returnValue->setPeelPongFBO(pPeelFBOs[i]);
            returnValue->setPeelPongMaterial(pPeelMat);
        }
    }

    // The final color blend target
    FrameBufferObjectUnrecPtr pBlendFBO      = FrameBufferObject::createLocal();

    //Color texture
    TextureObjChunkUnrecPtr   pBlendColorTex = TextureObjChunk::createLocal();
    ImageUnrecPtr             pBlendColorImg = Image          ::createLocal();

    pBlendColorImg->set(Image::OSG_RGBA_PF,
              iPixelWidth,
              iPixelHeight,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);

    pBlendColorTex->setImage         (pBlendColorImg   );
    pBlendColorTex->setMinFilter     (GL_NEAREST       );
    pBlendColorTex->setMagFilter     (GL_NEAREST       );
    pBlendColorTex->setWrapS         (GL_CLAMP_TO_EDGE );
    pBlendColorTex->setWrapT         (GL_CLAMP_TO_EDGE );
    pBlendColorTex->setInternalFormat(GL_RGBA8);

    TextureBufferUnrecPtr pBlendColorTexBuffer   = TextureBuffer::createLocal();
    pBlendColorTexBuffer->setTexture(pBlendColorTex);

    TextureBufferUnrecPtr pBlendDepthTexBuffer   = TextureBuffer::createLocal();
    pBlendDepthTexBuffer->setTexture(pDepthTexs[0]);

    pBlendFBO->setSize(iPixelWidth, iPixelHeight);
    pBlendFBO->setColorAttachment(pBlendColorTexBuffer, 0);
    pBlendFBO->setDepthAttachment(pBlendDepthTexBuffer);

    pBlendFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

    returnValue->setBlendFBO(pBlendFBO);

    // Blend Final Material
    ChunkMaterialUnrecPtr pBlendFinalMat = ChunkMaterial::createLocal();

    pBlendFinalMat->addChunk(pDepthOffChunk);
    pBlendFinalMat->addChunk(pBlendColorTex,     0);

    SimpleSHLChunkUnrecPtr pBlendFinalShader = SimpleSHLChunk::createLocal();
    pBlendFinalShader->setFragmentProgram(std::string(blendFinalFS));
    pBlendFinalShader->addUniformVariable("uSampler", 0);

    pBlendFinalMat->addChunk(pBlendFinalShader, 0);
    returnValue->setBlendFinalMaterial(pBlendFinalMat);

    OSG::Thread::resetCurrentLocalFlags();

    Thread::getCurrentChangeList()->commitChanges();

    return returnValue;
}

void DepthPeelingStage::resizeStageData(DepthPeelingStageData *pData,
                                        Int32                  iPixelWidth,
                                        Int32                  iPixelHeight)
{
    FrameBufferObject *pSceneFBO = pData->getBlendFBO();

    pSceneFBO->resizeAll(iPixelWidth, iPixelHeight);


    FrameBufferObject *pPeelPingFBO = pData->getPeelPingFBO();

    pPeelPingFBO->resizeAll(iPixelWidth, iPixelHeight);

    FrameBufferObject *pPeelPongFBO = pData->getPeelPongFBO();

    pPeelPongFBO->resizeAll(iPixelWidth, iPixelHeight);

    commitChanges();
}

OSG_END_NAMESPACE
