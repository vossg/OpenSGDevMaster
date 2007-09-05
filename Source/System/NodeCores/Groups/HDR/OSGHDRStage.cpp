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

#include <OSGConfig.h>

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGHDRStage.h"
#include "OSGHDRStageData.h"

#include "OSGRenderTraversalActionBase.h"

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
#include "OSGSHLFunctions.h"

OSG_USING_NAMESPACE

/*! \class osg::HDRStage

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

ActionBase::ResultE HDRStage::render(Action *action)
{
/*
    DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    da->useNodeList();
    
    if(da->isVisible(getCPtr(getSubTreeRoot())))
        da->addNode(getSubTreeRoot());
 */

    return Action::Continue;
}


/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void HDRStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&HDRStage::render));

        _uiFramebuffer_object_extension = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebuffer_object_extension);
    }
}

HDRStageDataP HDRStage::setupStageData(Int32 iPixelWidth,
                                       Int32 iPixelHeight)
{
    HDRStageDataP returnValue = HDRStageData::create();

    if(returnValue == NULL)
        return returnValue;


    // Scene Target

    FrameBufferObjectPtr pSceneFBO    = FrameBufferObject::create();

    RenderBufferPtr      pDepthBuffer = RenderBuffer     ::create();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

        
    TextureObjChunkPtr pSceneTex     = TextureObjChunk::create();
    TextureEnvChunkPtr pSceneTexEnv  = TextureEnvChunk::create();
    ImagePtr           pImg          = Image          ::create();
    
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
    pSceneTex   ->setWrapS         (GL_REPEAT        );
    pSceneTex   ->setWrapT         (GL_REPEAT        );
    pSceneTex   ->setInternalFormat(getBufferFormat());

    pSceneTexEnv->setEnvMode       (GL_REPLACE       );
    
    TextureBufferPtr pSceneTexBuffer   = TextureBuffer::create();
    
    pSceneTexBuffer->setTexture(pSceneTex);
    

    
    pSceneFBO->setSize(iPixelWidth, iPixelHeight);
    
    pSceneFBO->setColorAttachment(pSceneTexBuffer, 0);
    pSceneFBO->setDepthAttachment(pDepthBuffer      );
    
    pSceneFBO->editDrawBuffers().push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    setRenderTarget(pSceneFBO);
    



    // Shrink Target (w/2, h/2)

    FrameBufferObjectPtr pShrinkFBO     = FrameBufferObject::create();

    TextureObjChunkPtr   pShrinkTex     = TextureObjChunk::create();
    TextureEnvChunkPtr   pShrinkTexEnv  = TextureEnvChunk::create();
                         pImg           = Image          ::create();
    
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
    pShrinkTex   ->setWrapS         (GL_REPEAT        );
    pShrinkTex   ->setWrapT         (GL_REPEAT        );
    pShrinkTex   ->setInternalFormat(getBufferFormat());

    pShrinkTexEnv->setEnvMode       (GL_REPLACE       );
    
    TextureBufferPtr pShrinkTexBuffer   = TextureBuffer::create();
    
    pShrinkTexBuffer->setTexture(pShrinkTex);
    

    
    pShrinkFBO->setSize(iPixelWidth / 2, iPixelHeight / 2);
    
    pShrinkFBO->setColorAttachment(pShrinkTexBuffer, 0);
    
    pShrinkFBO->editDrawBuffers().push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    returnValue->setShrinkRenderTarget(pShrinkFBO);





    // blur (w/4, h/4)


    FrameBufferObjectPtr pBlurFBO     = FrameBufferObject::create();

    TextureObjChunkPtr   pBlurTex1    = TextureObjChunk  ::create();
    TextureEnvChunkPtr   pBlurTex1Env = TextureEnvChunk  ::create();
    
    
    pImg = Image::create();
    
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
    pBlurTex1   ->setWrapS         (GL_REPEAT        );
    pBlurTex1   ->setWrapT         (GL_REPEAT        );
    pBlurTex1   ->setInternalFormat(getBufferFormat());

    pBlurTex1Env->setEnvMode       (GL_REPLACE       );
    
    TextureBufferPtr pBlurTexBuffer1 = TextureBuffer::create();
    
    pBlurTexBuffer1->setTexture(pBlurTex1);
    
    
    
    TextureObjChunkPtr pBlurTex2    = TextureObjChunk::create();
    TextureEnvChunkPtr pBlurTex2Env = TextureEnvChunk::create();
    
    
    pImg = Image::create();

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
    pBlurTex2   ->setWrapS         (GL_REPEAT        );
    pBlurTex2   ->setWrapT         (GL_REPEAT        );
    pBlurTex2   ->setInternalFormat(getBufferFormat());

    pBlurTex2Env->setEnvMode       (GL_REPLACE       );
    
    TextureBufferPtr pBlurTexBuffer2 = TextureBuffer::create();

    pBlurTexBuffer2->setTexture(pBlurTex2);


    pBlurFBO->setSize(iPixelWidth  / 4,
                      iPixelHeight / 4);
    
    pBlurFBO->setColorAttachment(pBlurTexBuffer1,  0);
    pBlurFBO->setColorAttachment(pBlurTexBuffer2,  1);
    
    returnValue->setBlurRenderTarget(pBlurFBO);


    // general mat chunk


    MaterialChunkPtr pMatChunk = MaterialChunk::create();
        
    pMatChunk->setLit(false);




    // tone map material

    ChunkMaterialPtr    pTonemapMat  = ChunkMaterial  ::create();
    
    pTonemapMat->addChunk(pMatChunk         );
    pTonemapMat->addChunk(pSceneTex,       0);
    pTonemapMat->addChunk(pSceneTexEnv,    0);
    pTonemapMat->addChunk(pBlurTex1,       1);
    pTonemapMat->addChunk(pBlurTex1Env,    1);

    SHLChunkPtr pTonemapShader = generateHDRFragmentProgram();
    
    pTonemapShader->setUniformParameter("sceneTex",     0);
    pTonemapShader->setUniformParameter("blurTex",      1);
    pTonemapShader->setUniformParameter("blurAmount",   getBlurAmount  ());
    pTonemapShader->setUniformParameter("exposure",     getExposure    ());
    pTonemapShader->setUniformParameter("effectAmount", getEffectAmount());
    pTonemapShader->setUniformParameter("gamma",        getGamma       ());
    
    pTonemapMat->addChunk(pTonemapShader, 0);
    
    returnValue->setToneMappingMaterial(pTonemapMat);




    // Shrink material

    ChunkMaterialPtr pShrinkMat = ChunkMaterial::create();
    
    pShrinkMat->addChunk(pMatChunk   );
    
    pShrinkMat->addChunk(pSceneTex,     0);
    pShrinkMat->addChunk(pSceneTexEnv,  0);

    
    SHLChunkPtr pShrinkShader = generate2DShrinkHalfFilterFP();
        
    pShrinkShader->setUniformParameter("inputTex", 0);
    
    pShrinkMat->addChunk(pShrinkShader, 0);
    
    returnValue->setShrinkMaterial(pShrinkMat);




    // Blur material

    ChunkMaterialPtr pBlurMat = ChunkMaterial::create();
    
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
    SHLChunkPtr pHBlurShader = generate1DConvolutionFilterFP(getBlurWidth(), 
                                                             false, 
                                                             true, 
                                                             iPixelWidth  / 2, 
                                                             iPixelHeight / 2);

   
    pHBlurShader->setUniformParameter("inputTex", 0);

    returnValue->setHBlurShader(pHBlurShader);

    
    
    // VBlur Override


    SHLChunkPtr pVBlurShader = generate1DConvolutionFilterFP(getBlurWidth(),  
                                                             true, 
                                                             true, 
                                                             iPixelWidth  / 2, 
                                                             iPixelHeight / 2);
    
    pVBlurShader->setUniformParameter("inputTex", 1);
    
    returnValue->setVBlurShader(pVBlurShader);


    Thread::getCurrentChangeList()->commitChanges();

    return returnValue;
}

void HDRStage::resizeStageData(HDRStageDataP pData,
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
        (GLDrawBuffersEXTProcT) win->getFunction(_uiFuncDrawBuffers);

    glColor3f(1.f, 1.f, 1.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    RenderTraversalActionBase *pAction = pEnv->getRTAction();

    if(pAction == NULL)
        return;


    HDRStageDataP  pData     = pAction->getData<HDRStageData *>(_iDataSlotId);

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

    FrameBufferObjectPtr pShrinkTarget = pData->getShrinkRenderTarget();
    ChunkMaterialPtr     pSHM          = pData->getShrinkMaterial();


    pShrinkTarget->activate(pEnv);

    glViewport(0,
               0, 
               pEnv->getPixelWidth () / 2,
               pEnv->getPixelHeight() / 2);


    State *pShrinkState = getCPtr(pSHM->getState());

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

    FrameBufferObjectPtr pBlurTarget = pData->getBlurRenderTarget();

    pBlurTarget->editDrawBuffers().clear();

    pBlurTarget->editDrawBuffers().push_back(GL_COLOR_ATTACHMENT0_EXT);

    pBlurTarget->activate(pEnv);

    glViewport(0,
               0, 
               pEnv->getPixelWidth () / 4,
               pEnv->getPixelHeight() / 4);

    ChunkMaterialPtr  pBLM       = pData->getBlurMaterial();

    State            *pBlurState = getCPtr(pBLM->getState());

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
                          getCPtr(pData->getHBlurShader()));


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
                           getCPtr(pData->getVBlurShader()));
    

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
               pEnv->getPixelRight (),
               pEnv->getPixelTop   ());

    ChunkMaterialPtr pTCM = pData->getToneMappingMaterial();

    State *pTState = getCPtr(pTCM->getState());
        
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

void HDRStage::initData(Viewport                  *pViewport,
                        RenderTraversalActionBase *pAction  )
{
    HDRStageDataP pData = pAction->getData<HDRStageData *>(_iDataSlotId);

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

SHLChunkPtr HDRStage::generateHDRFragmentProgram(void)
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

    SHLChunkPtr returnValue = SHLChunk::create();

    returnValue->setFragmentProgram(ost.str());

    return returnValue;
}
