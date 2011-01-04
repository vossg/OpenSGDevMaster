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

#include <stdlib.h>
#include <stdio.h>

#include <sstream>
#include <fstream>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGHDRStage.h"
#include "OSGHDRStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGImageFunctions.h"
#include "OSGStateOverride.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleSHLFunctions.h"

#include "OSGMatrixUtility.h"

OSG_USING_NAMESPACE

/*! \class OSG::HDRStage

*/

UInt32 HDRStage::_uiFramebuffer_object_extension = 
    Window::invalidExtensionID;

UInt32 HDRStage::_uiFuncDrawBuffers              =
    Window::invalidFunctionID;

typedef void   (OSG_APIENTRY *GLDrawBuffersEXTProcT)(
          GLsizei  n, 
    const GLenum  *buffers);

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void HDRStage::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void HDRStage::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

HDRStage::HDRStage(void) :
     Inherited  (  )
{
}

HDRStage::HDRStage(const HDRStage &source) :
     Inherited  (source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

HDRStage::~HDRStage(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

ActionBase::ResultE HDRStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->disableDefaultPartition();

    this->beginPartitionGroup(a);
    {
        this->pushPartition(a);
        {
            RenderPartition   *pPart    = a->getActivePartition();
            FrameBufferObject *pTarget  = this->getRenderTarget();
            Viewport          *pPort    = a->getViewport();
            Camera            *pCam     = a->getCamera  ();
            Background        *pBack    = a->getBackground();
            
            if(pTarget == NULL)
            {
                this->initData(pPort, a);

                pTarget  = this->getRenderTarget();
            }

            pPart->setRenderTarget(pTarget);
            
#ifdef OSG_DEBUGX
            std::string szMessage("RenderPartition\n");
            pPart->setDebugString(szMessage          );
#endif

            if(pPort != NULL)
            {
//                pPart->setViewport(pPort         );
                pPart->setWindow  (a->getWindow());
                
                if(pTarget != NULL)
                {
                    pPart->calcViewportDimension(pPort->getLeft  (),
                                                 pPort->getBottom(),
                                                 pPort->getRight (),
                                                 pPort->getTop   (),
                                                 
                                                 pTarget->getWidth    (),
                                                 pTarget->getHeight   ());
                }
                else
                {
                    pPart->calcViewportDimension(pPort->getLeft  (),
                                                 pPort->getBottom(),
                                                 pPort->getRight (),
                                                 pPort->getTop   (),
                                                 
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
        
        this->pushPartition(a,
                            (RenderPartition::CopyWindow      |
                             RenderPartition::CopyViewportSize),
                            RenderPartition::SimpleCallback    );
        {
            RenderPartition *pPart  = a->getActivePartition();

#ifdef OSG_DEBUGX
            std::string szMessage("PostProcessPartition\n");
            pPart->setDebugString(szMessage          );
#endif
           
            Matrix m, t;
                
            m.setIdentity();
            t.setIdentity();
                
            MatrixOrthogonal( m,
                              0.f, 1.f,
                              0.f, 1.f,
                             -1.f, 1.f);
            
            pPart->setupProjection(m, t);
                
            RenderPartition::SimpleDrawCallback f;
                
            f = boost::bind(&HDRStage::postProcess, this, _1);
                
            pPart->dropFunctor(f);
        }
        this->popPartition(a);
    }
    this->endPartitionGroup(a);

    return Action::Skip;
}

ActionBase::ResultE HDRStage::renderLeave(Action *action)
{
    return Action::Skip;
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void HDRStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            HDRStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&HDRStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            HDRStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&HDRStage::renderLeave));

        _uiFramebuffer_object_extension = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebuffer_object_extension);
    }
}

HDRStageDataTransitPtr HDRStage::setupStageData(Int32 iPixelWidth,
                                                Int32 iPixelHeight)
{
    HDRStageDataTransitPtr returnValue = HDRStageData::createLocal();

    if(returnValue == NULL)
        return returnValue;

    OSG::Thread::setCurrentLocalFlags();

    // Scene Target

    FrameBufferObjectUnrecPtr pSceneFBO    = FrameBufferObject::createLocal();

    RenderBufferUnrecPtr      pDepthBuffer = RenderBuffer     ::createLocal();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

        
    TextureObjChunkUnrecPtr pSceneTex     = TextureObjChunk::createLocal();
    TextureEnvChunkUnrecPtr pSceneTexEnv  = TextureEnvChunk::createLocal();
    ImageUnrecPtr           pImg          = Image          ::createLocal();
    
    pImg->set(Image::OSG_RGB_PF, 
              iPixelWidth, 
              iPixelHeight,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pSceneTex   ->setImage         (pImg             ); 
    pSceneTex   ->setMinFilter     (GL_LINEAR        );
    pSceneTex   ->setMagFilter     (GL_LINEAR        );
    pSceneTex   ->setWrapS         (GL_CLAMP_TO_EDGE );
    pSceneTex   ->setWrapT         (GL_CLAMP_TO_EDGE );
    pSceneTex   ->setInternalFormat(getBufferFormat());

    pSceneTexEnv->setEnvMode       (GL_REPLACE       );
    
    TextureBufferUnrecPtr pSceneTexBuffer   = TextureBuffer::createLocal();
    
    pSceneTexBuffer->setTexture(pSceneTex);
    

    
    pSceneFBO->setSize(iPixelWidth, iPixelHeight);
    
    pSceneFBO->setColorAttachment(pSceneTexBuffer, 0);
    pSceneFBO->setDepthAttachment(pDepthBuffer      );
    
    pSceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    setRenderTarget(pSceneFBO);
    



    // Shrink Target (w/2, h/2)

    FrameBufferObjectUnrecPtr pShrinkFBO     = FrameBufferObject::createLocal();

    TextureObjChunkUnrecPtr   pShrinkTex     = TextureObjChunk::createLocal();
    TextureEnvChunkUnrecPtr   pShrinkTexEnv  = TextureEnvChunk::createLocal();
                              pImg           = Image          ::createLocal();
    
    pImg->set(Image::OSG_RGB_PF, 
              iPixelWidth  / 2, 
              iPixelHeight / 2,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pShrinkTex   ->setImage         (pImg             ); 
    pShrinkTex   ->setMinFilter     (GL_LINEAR        );
    pShrinkTex   ->setMagFilter     (GL_LINEAR        );
    pShrinkTex   ->setWrapS         (GL_CLAMP_TO_EDGE );
    pShrinkTex   ->setWrapT         (GL_CLAMP_TO_EDGE );
    pShrinkTex   ->setInternalFormat(getBufferFormat());

    pShrinkTexEnv->setEnvMode       (GL_REPLACE       );
    
    TextureBufferUnrecPtr pShrinkTexBuffer   = TextureBuffer::createLocal();
    
    pShrinkTexBuffer->setTexture(pShrinkTex);
    

    
    pShrinkFBO->setSize(iPixelWidth / 2, iPixelHeight / 2);
    
    pShrinkFBO->setColorAttachment(pShrinkTexBuffer, 0);
    
    pShrinkFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    returnValue->setShrinkRenderTarget(pShrinkFBO);





    // blur (w/4, h/4)


    FrameBufferObjectUnrecPtr pBlurFBO     = FrameBufferObject::createLocal();

    TextureObjChunkUnrecPtr   pBlurTex1    = TextureObjChunk  ::createLocal();
    TextureEnvChunkUnrecPtr   pBlurTex1Env = TextureEnvChunk  ::createLocal();
    
    
    pImg = Image::createLocal();
    
    pImg->set(Image::OSG_RGB_PF, 
              iPixelWidth  / 4,
              iPixelHeight / 4,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pBlurTex1   ->setImage         (pImg             ); 
    pBlurTex1   ->setMinFilter     (GL_LINEAR        );
    pBlurTex1   ->setMagFilter     (GL_LINEAR        );
    pBlurTex1   ->setWrapS         (GL_CLAMP_TO_EDGE );
    pBlurTex1   ->setWrapT         (GL_CLAMP_TO_EDGE );
    pBlurTex1   ->setInternalFormat(getBufferFormat());

    pBlurTex1Env->setEnvMode       (GL_REPLACE       );
    
    TextureBufferUnrecPtr pBlurTexBuffer1 = TextureBuffer::createLocal();
    
    pBlurTexBuffer1->setTexture(pBlurTex1);
    
    
    
    TextureObjChunkUnrecPtr pBlurTex2    = TextureObjChunk::createLocal();
    TextureEnvChunkUnrecPtr pBlurTex2Env = TextureEnvChunk::createLocal();
    
    
    pImg = Image::createLocal();

    pImg->set(Image::OSG_RGB_PF, 
              iPixelWidth  / 4,
              iPixelHeight / 4,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pBlurTex2   ->setImage         (pImg             ); 
    pBlurTex2   ->setMinFilter     (GL_LINEAR        );
    pBlurTex2   ->setMagFilter     (GL_LINEAR        );
    pBlurTex2   ->setWrapS         (GL_CLAMP_TO_EDGE );
    pBlurTex2   ->setWrapT         (GL_CLAMP_TO_EDGE );
    pBlurTex2   ->setInternalFormat(getBufferFormat());

    pBlurTex2Env->setEnvMode       (GL_REPLACE       );
    
    TextureBufferUnrecPtr pBlurTexBuffer2 = TextureBuffer::createLocal();

    pBlurTexBuffer2->setTexture(pBlurTex2);


    pBlurFBO->setSize(iPixelWidth  / 4,
                      iPixelHeight / 4);
    
    pBlurFBO->setColorAttachment(pBlurTexBuffer1,  0);
    pBlurFBO->setColorAttachment(pBlurTexBuffer2,  1);
    
    returnValue->setBlurRenderTarget(pBlurFBO);


    // general mat chunk


    MaterialChunkUnrecPtr pMatChunk = MaterialChunk::createLocal();
        
    pMatChunk->setLit(false);




    // tone map material

    ChunkMaterialUnrecPtr    pTonemapMat  = ChunkMaterial  ::createLocal();
    
    pTonemapMat->addChunk(pMatChunk         );
    pTonemapMat->addChunk(pSceneTex,       0);
    pTonemapMat->addChunk(pSceneTexEnv,    0);
    pTonemapMat->addChunk(pBlurTex1,       1);
    pTonemapMat->addChunk(pBlurTex1Env,    1);

    SimpleSHLChunkUnrecPtr pTonemapShader = generateHDRFragmentProgram();
    
    pTonemapShader->addUniformVariable("sceneTex",     0);
    pTonemapShader->addUniformVariable("blurTex",      1);
    pTonemapShader->addUniformVariable("blurAmount",   getBlurAmount  ());
    pTonemapShader->addUniformVariable("exposure",     getExposure    ());
    pTonemapShader->addUniformVariable("effectAmount", getEffectAmount());
    pTonemapShader->addUniformVariable("gamma",        getGamma       ());
    
    pTonemapMat->addChunk(pTonemapShader, 0);
    
    returnValue->setToneMappingMaterial(pTonemapMat);




    // Shrink material

    ChunkMaterialUnrecPtr pShrinkMat = ChunkMaterial::createLocal();
    
    pShrinkMat->addChunk(pMatChunk   );
    
    pShrinkMat->addChunk(pSceneTex,     0);
    pShrinkMat->addChunk(pSceneTexEnv,  0);

    SimpleSHLChunkUnrecPtr pShrinkShader = generate2DShrinkHalfFilterFP();
        
    pShrinkShader->addUniformVariable("inputTex", 0);
    
    pShrinkMat->addChunk(pShrinkShader, 0);
    
    returnValue->setShrinkMaterial(pShrinkMat);




    // Blur material

    ChunkMaterialUnrecPtr pBlurMat = ChunkMaterial::createLocal();
    
    pBlurMat->addChunk(pMatChunk   );
    
    pBlurMat->addChunk(pShrinkTex,    0);
    pBlurMat->addChunk(pShrinkTexEnv, 0);
    pBlurMat->addChunk(pBlurTex1,     1);
    pBlurMat->addChunk(pBlurTex1Env,  1);
    pBlurMat->addChunk(pBlurTex2,     2);
    pBlurMat->addChunk(pBlurTex2Env,  2);

    pBlurMat->addChunk(pShrinkShader, 0);
    
    returnValue->setBlurMaterial(pBlurMat);


    // generate blur fragment programs
    SimpleSHLChunkUnrecPtr pHBlurShader = 
        generate1DConvolutionFilterFP(getBlurWidth(), 
                                      false, 
                                      true, 
                                      iPixelWidth  / 2, 
                                      iPixelHeight / 2);
    
   
    pHBlurShader->addUniformVariable("inputTex", 0);

    returnValue->setHBlurShader(pHBlurShader);

    
    
    // VBlur Override


    SimpleSHLChunkUnrecPtr pVBlurShader = 
        generate1DConvolutionFilterFP(getBlurWidth(),  
                                      true, 
                                      true, 
                                      iPixelWidth  / 2, 
                                      iPixelHeight / 2);
    
    pVBlurShader->addUniformVariable("inputTex", 1);
    
    returnValue->setVBlurShader(pVBlurShader);

    OSG::Thread::resetCurrentLocalFlags();

    Thread::getCurrentChangeList()->commitChanges();

    return returnValue;
}

void HDRStage::resizeStageData(HDRStageData *pData,
                               Int32         iPixelWidth,
                               Int32         iPixelHeight)
{
    FWARNING(("HDRStage resize not implemented ==> wrong results\n"));
}

void HDRStage::postProcess(DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtension(_uiFramebuffer_object_extension) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

    GLDrawBuffersEXTProcT glDrawBuffersEXTProc =
        reinterpret_cast<GLDrawBuffersEXTProcT>(
            win->getFunction(_uiFuncDrawBuffers));

    glColor3f(1.f, 1.f, 1.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    HDRStageData *pData = pEnv->getData<HDRStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        return;
    }

    if((pData->getWidth () != pEnv->getPixelWidth() ) ||
       (pData->getHeight() != pEnv->getPixelHeight())  )
    {
        resizeStageData(pData, 
                        pEnv->getPixelWidth(),
                        pEnv->getPixelHeight());
    }
    

    // Shrink to w/2 h/2

    FrameBufferObject *pShrinkTarget = pData->getShrinkRenderTarget();
    ChunkMaterial     *pSHM          = pData->getShrinkMaterial();


    pShrinkTarget->activate(pEnv);

    glViewport(0,
               0, 
               pEnv->getPixelWidth () / 2,
               pEnv->getPixelHeight() / 2);


    State *pShrinkState = pSHM->getState();

    pEnv->activateState(pShrinkState, NULL);
    
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.00, 0.00);
        glVertex2f  (0.00, 0.00);
        
        glTexCoord2f(1.00, 0.00);
        glVertex2f  (1.00, 0.00);
        
        glTexCoord2f(1.00, 1.00);
        glVertex2f  (1.00, 1.00);
        
        glTexCoord2f(0.00, 1.00);
        glVertex2f  (0.00, 1.00);
    }
    glEnd();

    pShrinkTarget->deactivate(pEnv);


    // Shrink to w/4 h/4

    FrameBufferObject *pBlurTarget = pData->getBlurRenderTarget();

    pBlurTarget->editMFDrawBuffers()->clear();

    pBlurTarget->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

    pBlurTarget->activate(pEnv);

    glViewport(0,
               0, 
               pEnv->getPixelWidth () / 4,
               pEnv->getPixelHeight() / 4);

    ChunkMaterial    *pBLM       = pData->getBlurMaterial();

    State            *pBlurState = pBLM->getState();

    pEnv->activateState(pBlurState, NULL);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.00, 0.00);
        glVertex2f  (0.00, 0.00);
        
        glTexCoord2f(1.00, 0.00);
        glVertex2f  (1.00, 0.00);
        
        glTexCoord2f(1.00, 1.00);
        glVertex2f  (1.00, 1.00);
        
        glTexCoord2f(0.00, 1.00);
        glVertex2f  (0.00, 1.00);
    }
    glEnd();

    // HBlur

    StateOverride oOverride;        

    GLenum aDrawBuffers[] = { GL_COLOR_ATTACHMENT1_EXT };

    oOverride.addOverride(pData->getHBlurShader()->getClassId(), 
                          pData->getHBlurShader());


    pEnv->activateState(pBlurState, &oOverride);
            
    glDrawBuffersEXTProc(1, aDrawBuffers);


    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.00, 0.00);
        glVertex2f  (0.00, 0.00);
        
        glTexCoord2f(1.00, 0.00);
        glVertex2f  (1.00, 0.00);
        
        glTexCoord2f(1.00, 1.00);
        glVertex2f  (1.00, 1.00);
        
        glTexCoord2f(0.00, 1.00);
        glVertex2f  (0.00, 1.00);
    }
    glEnd();



    // VBlur
           
    StateOverride oOverride1;        

    oOverride1.addOverride(pData->getVBlurShader()->getClassId(), 
                           pData->getVBlurShader());
    

    pEnv->activateState(pBlurState, &oOverride1);

    aDrawBuffers[0] = GL_COLOR_ATTACHMENT0_EXT;
    
    glDrawBuffersEXTProc(1, aDrawBuffers);
    
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.00, 0.00);
        glVertex2f  (0.00, 0.00);
        
        glTexCoord2f(1.00, 0.00);
        glVertex2f  (1.00, 0.00);
        
        glTexCoord2f(1.00, 1.00);
        glVertex2f  (1.00, 1.00);
        
        glTexCoord2f(0.00, 1.00);
        glVertex2f  (0.00, 1.00);
    }
    glEnd();
    
    
    pBlurTarget->deactivate(pEnv);



    // Tonemap pass

    glDisable(GL_DEPTH_TEST);

    glViewport(pEnv->getPixelLeft  (), 
               pEnv->getPixelBottom(),
               pEnv->getPixelWidth (),
               pEnv->getPixelHeight());

    ChunkMaterial *pTCM = pData->getToneMappingMaterial();

    State *pTState = pTCM->getState();
        
    pEnv->activateState(pTState, NULL);
            
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.00, 0.00);
        glVertex2f  (0.00, 0.00);
        
        glTexCoord2f(1.00, 0.00);
        glVertex2f  (1.00, 0.00);
        
        glTexCoord2f(1.00, 1.00);
        glVertex2f  (1.00, 1.00);
        
        glTexCoord2f(0.00, 1.00);
        glVertex2f  (0.00, 1.00);
    }
    glEnd();

    glEnable(GL_DEPTH_TEST);
            
    pEnv->deactivateState();


    glPopMatrix();
}

void HDRStage::initData(Viewport         *pViewport,
                        RenderActionBase *pAction  )
{
    HDRStageDataUnrecPtr pData = pAction->getData<HDRStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pViewport->getPixelWidth(),
                               pViewport->getPixelHeight());
        
        pData->setWidth (pViewport->getPixelWidth ());
        pData->setHeight(pViewport->getPixelHeight());

        this->setData(pData, _iDataSlotId, pAction);
    }
}

#define OSGHDRL << std::endl

SimpleSHLChunkTransitPtr HDRStage::generateHDRFragmentProgram(void)
{
    std::ostringstream ost;

    ost << "uniform sampler2D sceneTex;"                                 OSGHDRL
        << "uniform sampler2D blurTex;"                                  OSGHDRL
        << "uniform float     exposure;"                                 OSGHDRL
        << "uniform float     blurAmount;"                               OSGHDRL
        << "uniform float     effectAmount;"                             OSGHDRL
        << "uniform float     gamma;"                                    OSGHDRL
        << ""                                                            OSGHDRL
        << "float vignette(vec2 pos, float inner, float outer)"          OSGHDRL
        << "{"                                                           OSGHDRL
        << "    float r = length(pos);"                                  OSGHDRL
        << ""                                                            OSGHDRL
        << "    r = 1.0 - smoothstep(inner, outer, r);"                  OSGHDRL
        << ""                                                            OSGHDRL
        << "    return r;"                                               OSGHDRL
        << "}"                                                           OSGHDRL
        << ""                                                            OSGHDRL
        << "// radial blur"                                              OSGHDRL
        << "vec4 radial(sampler2D tex,"                                  OSGHDRL
        << "            vec2      texcoord,"                             OSGHDRL
        << "            int       samples,"                              OSGHDRL
        << "            float     startScale = 1.0,"                     OSGHDRL
        << "            float     scaleMul   = 0.9)"                     OSGHDRL
        << "{"                                                           OSGHDRL
        << "    vec4 c     = vec4(0., 0., 0., 0.);"                      OSGHDRL
        << "    float  scale = startScale;"                              OSGHDRL
        << ""                                                            OSGHDRL
        << "    for(int i=0; i<samples; i++) "                           OSGHDRL
        << "    {"                                                       OSGHDRL
        << "        vec2 uv = ((texcoord - 0.5)*scale)+0.5;"             OSGHDRL
        << "        vec4 s  = texture2D(tex, uv);"                       OSGHDRL
        << ""                                                            OSGHDRL
        << "        c += s;"                                             OSGHDRL
        << ""                                                            OSGHDRL
        << "        scale *= scaleMul;"                                  OSGHDRL
        << "    }"                                                       OSGHDRL
        << ""                                                            OSGHDRL
        << "    c /= float(samples);"                                    OSGHDRL
        << ""                                                            OSGHDRL
        << "    return c;"                                               OSGHDRL
        << "}"                                                           OSGHDRL
        << ""                                                            OSGHDRL
        << "void main(void)"                                             OSGHDRL
        << "{"                                                           OSGHDRL
        << "    vec4 scene   = texture2D(sceneTex, gl_TexCoord[0].xy);"  OSGHDRL
        << "    vec4 blurred = texture2D(blurTex,  gl_TexCoord[0].xy);"  OSGHDRL
        << "	vec4 effect  = radial   (blurTex,  gl_TexCoord[0].xy, "  OSGHDRL
        << "                             30, 1.0, 0.95);"                OSGHDRL
        << ""                                                            OSGHDRL
        << "    vec4 c = mix(scene, blurred, blurAmount);"               OSGHDRL
        << ""                                                            OSGHDRL
        << "	c += effect * effectAmount;"                             OSGHDRL
        << ""                                                            OSGHDRL
        << "    // exposure"                                             OSGHDRL
        << "    c = c * exposure;"                                       OSGHDRL
        << ""                                                            OSGHDRL
        << "    // vignette effect"                                      OSGHDRL
        << "    c *= vignette(gl_TexCoord[0].xy * 2.0 - 1.0, 0.7, 1.5);" OSGHDRL
        << ""                                                            OSGHDRL
        << "    // gamma correction"                                     OSGHDRL
        << "    c.rgb = pow(c.rgb, vec3(gamma));"                        OSGHDRL
        << ""                                                            OSGHDRL
        << "    gl_FragColor = c;"                                       OSGHDRL
        << "}"                                                           OSGHDRL
        << "";

    SimpleSHLChunkTransitPtr returnValue = SimpleSHLChunk::createLocal();

    returnValue->setFragmentProgram(ost.str());

    return returnValue;
}
