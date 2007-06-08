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

#define  GL_GLEXT_PROTOTYPES

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

#include "OSGRenderTraversalAction.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGImageFunctions.h"
#include "OSGSHLChunk.h"
#include "OSGStateOverride.h"
#include "OSGTextureEnvChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::HDRStage

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void HDRStage::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
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
    }
}

HDRStageDataP HDRStage::setupStageData(void)
{
    HDRStageDataP returnValue = HDRStageData::create();

    if(returnValue == NULL)
        return returnValue;

    FrameBufferObjectPtr pSceneFBO    = FrameBufferObject::create();

    RenderBufferPtr      pDepthBuffer = RenderBuffer     ::create();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

        
    TextureObjChunkPtr pSceneTex     = TextureObjChunk::create();
    TextureEnvChunkPtr pSceneTexEnv  = TextureEnvChunk::create();
    ImagePtr           pImg          = Image          ::create();
    
    pImg->set(Image::OSG_RGB_PF, 
              800, 
              800,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pSceneTex   ->setImage    (pImg      ); 
    pSceneTex   ->setMinFilter(GL_LINEAR );
    pSceneTex   ->setMagFilter(GL_LINEAR );
    pSceneTex   ->setWrapS    (GL_REPEAT );
    pSceneTex   ->setWrapT    (GL_REPEAT );
    pSceneTexEnv->setEnvMode  (GL_REPLACE);
    
    TextureBufferPtr pSceneTexBuffer   = TextureBuffer::create();
    
    pSceneTexBuffer->setTexture(pSceneTex);
    

    
    pSceneFBO->setSize(800, 800);
    
    pSceneFBO->setColorAttachment(pSceneTexBuffer, 0);
    pSceneFBO->setDepthAttachment(pDepthBuffer      );
    
    pSceneFBO->editDrawBuffers().push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    setRenderTarget(pSceneFBO);
    




    FrameBufferObjectPtr pBlurFBO     = FrameBufferObject::create();
    
    TextureObjChunkPtr   pBlurTex1    = TextureObjChunk  ::create();
    TextureEnvChunkPtr   pBlurTex1Env = TextureEnvChunk  ::create();
    
    
    pImg = Image::create();
    
    pImg->set(Image::OSG_RGB_PF, 
              400, 
              400,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pBlurTex1   ->setImage    (pImg      ); 
    pBlurTex1   ->setMinFilter(GL_LINEAR );
    pBlurTex1   ->setMagFilter(GL_LINEAR );
    pBlurTex1   ->setWrapS    (GL_REPEAT );
    pBlurTex1   ->setWrapT    (GL_REPEAT );
    pBlurTex1Env->setEnvMode  (GL_REPLACE);
    
    TextureBufferPtr pBlurTexBuffer1 = TextureBuffer::create();
    
    pBlurTexBuffer1->setTexture(pBlurTex1);
    
    
    
    TextureObjChunkPtr pBlurTex2    = TextureObjChunk::create();
    TextureEnvChunkPtr pBlurTex2Env = TextureEnvChunk::create();
    
    
    pImg = Image::create();

    pImg->set(Image::OSG_RGB_PF, 
              400, 
              400,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_FLOAT32_IMAGEDATA,
              false);
    
    pBlurTex2   ->setImage    (pImg      ); 
    pBlurTex2   ->setMinFilter(GL_LINEAR );
    pBlurTex2   ->setMagFilter(GL_LINEAR );
    pBlurTex2   ->setWrapS    (GL_REPEAT );
    pBlurTex2   ->setWrapT    (GL_REPEAT );
    pBlurTex2Env->setEnvMode  (GL_REPLACE);
    
    TextureBufferPtr pBlurTexBuffer2 = TextureBuffer::create();

    pBlurTexBuffer2->setTexture(pBlurTex2);


    pBlurFBO->setSize(400, 400);
    
    pBlurFBO->setColorAttachment(pBlurTexBuffer1, 0);
    pBlurFBO->setColorAttachment(pBlurTexBuffer2, 1);
    
    
    returnValue->setBlurRenderTarget(pBlurFBO);



    MaterialChunkPtr pMatChunk = MaterialChunk::create();
        
    pMatChunk->setLit(false);




    ChunkMaterialPtr    pTonemapMat  = ChunkMaterial  ::create();
    
    TextureObjChunkPtr  pGammaTex    = TextureObjChunk::create();
    TextureEnvChunkPtr  pGammaTexEnv = TextureEnvChunk::create();
    
    pImg = Image::create();
    
    createGamma(pImg, 256, 1.0 / 2.2);
    
    pGammaTex   ->setImage    (pImg      ); 
    pGammaTex   ->setMinFilter(GL_LINEAR );
    pGammaTex   ->setMagFilter(GL_LINEAR );
    pGammaTex   ->setWrapS    (GL_CLAMP_TO_EDGE);
    pGammaTex   ->setWrapT    (GL_CLAMP_TO_EDGE);
    pGammaTexEnv->setEnvMode  (GL_REPLACE);
    
    
    TextureObjChunkPtr pVignetteTex    = TextureObjChunk::create();
    TextureEnvChunkPtr pVignetteTexEnv = TextureEnvChunk::create();
    
    pImg = Image::create();

    createVignette(pImg, 800, 800, 0.25 * 800, 0.7 * 800);
    
    pVignetteTex   ->setImage    (pImg      ); 
    pVignetteTex   ->setMinFilter(GL_LINEAR );
    pVignetteTex   ->setMagFilter(GL_LINEAR );
    pVignetteTex   ->setWrapS    (GL_CLAMP_TO_EDGE);
    pVignetteTex   ->setWrapT    (GL_CLAMP_TO_EDGE);
    pVignetteTexEnv->setEnvMode  (GL_REPLACE);
    
    pTonemapMat->addChunk(pMatChunk         );
    pTonemapMat->addChunk(pSceneTex,       0);
    pTonemapMat->addChunk(pSceneTexEnv,    0);
    pTonemapMat->addChunk(pGammaTex,       1);
    pTonemapMat->addChunk(pGammaTexEnv,    1);
    pTonemapMat->addChunk(pVignetteTex,    2);
    pTonemapMat->addChunk(pVignetteTexEnv, 2);
    pTonemapMat->addChunk(pBlurTex1,       3);
    pTonemapMat->addChunk(pBlurTex1Env,    3);
    
    
    SHLChunkPtr pTonemapShader = SHLChunk::create();
    
    if(!pTonemapShader->readFragmentProgram("hdr.fp"))
        fprintf(stderr, "Couldn't read fragment program 'Earth.fp'\n");
    
    pTonemapShader->setUniformParameter("sceneTex",    0);
    pTonemapShader->setUniformParameter("gammaTex",    1);
    pTonemapShader->setUniformParameter("vignetteTex", 2);
    pTonemapShader->setUniformParameter("blurTex",     3);
    pTonemapShader->setUniformParameter("blurAmount",  0.2f);
    pTonemapShader->setUniformParameter("fExposure", 0.1f);
    
    pTonemapMat->addChunk(pTonemapShader, 0);
    
    returnValue->setToneMappingMaterial(pTonemapMat);





    ChunkMaterialPtr pBlurMat = ChunkMaterial::create();
    
    pBlurMat->addChunk(pMatChunk   );
    
    pBlurMat->addChunk(pSceneTex,    0);
    pBlurMat->addChunk(pSceneTexEnv, 0);
    pBlurMat->addChunk(pBlurTex1,    1);
    pBlurMat->addChunk(pBlurTex1Env, 1);
    pBlurMat->addChunk(pBlurTex2,    2);
    pBlurMat->addChunk(pBlurTex2Env, 2);

    
    SHLChunkPtr pShrinkShader = SHLChunk::create();
    
    if(!pShrinkShader->readFragmentProgram("shrink.fp"))
        fprintf(stderr, "Couldn't read fragment program 'shrink.fp'\n");
    
    pShrinkShader->setUniformParameter("inputTex", 0);
    
    pBlurMat->addChunk(pShrinkShader, 0);
    
    returnValue->setBlurMaterial(pBlurMat);




    SHLChunkPtr pHBlurShader = SHLChunk::create();
    
    if(!pHBlurShader->readFragmentProgram("hblur.fp"))
        fprintf(stderr, "Couldn't read fragment program 'hblur.fp'\n");
    
    pHBlurShader->setUniformParameter("inputTex", 1);
    
    returnValue->setHBlurShader(pHBlurShader);
    
    
    
    SHLChunkPtr pVBlurShader = SHLChunk::create();
    
    if(!pVBlurShader->readFragmentProgram("vblur.fp"))
        fprintf(stderr, "Couldn't read fragment program 'vblur.fp'\n");
    
    pVBlurShader->setUniformParameter("inputTex", 2);
    
    returnValue->setVBlurShader(pVBlurShader);

    Thread::getCurrentChangeList()->commitChanges();


    fprintf(stderr, "Create Data %p\n", returnValue);

    return returnValue;
}


void HDRStage::postProcess(DrawEnv *pEnv)
{
    Pnt2f p1(0.25, 0.25);
    Pnt2f p2(0.75, 0.25);
    Pnt2f p3(0.75, 0.75);
    Pnt2f p4(0.25, 0.75);
    
    glColor3f(1.f, 1.f, 1.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    RenderTraversalActionBase *pAction = pEnv->getRTAction();

    if(pAction == NULL)
        return;


    HDRStageDataP pData = pAction->getData<HDRStageData *>(_iDataSlotId);

    fprintf(stderr, "Retrieved data %p\n", pData);

    if(pData == NULL)
    {
        pData = setupStageData();
        
        this->setData(pData, _iDataSlotId, pAction);
//        pAction->setData(pData, _iDataSlotId);
    }

    fprintf(stderr, "Got data %p\n", pData);


    FrameBufferObjectPtr pBlurTarget = pData->getBlurRenderTarget();

    pBlurTarget->editDrawBuffers().clear();

    pBlurTarget->editDrawBuffers().push_back(GL_COLOR_ATTACHMENT0_EXT);

    pBlurTarget->activate(pEnv);

    glViewport(0, 0, 400, 400);

    ChunkMaterialPtr pBLM = pData->getBlurMaterial();

    StateOverride oOverride;        
    StateOverride oOverride1;        

   if(pBLM != NullFC)
    {
        State *pBlurState = getCPtr(pBLM->getState());
        
        if(pBlurState != NULL)
        {
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

            GLenum aDrawBuffers[] = { GL_COLOR_ATTACHMENT1_EXT };

            oOverride.addOverride(pData->getHBlurShader()->getClassId(), 
                                  getCPtr(pData->getHBlurShader()));


            pEnv->activateState(pBlurState, &oOverride);
            
#ifndef WIN32
            glDrawBuffers(1, aDrawBuffers);
#endif


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
            

            oOverride1.addOverride(pData->getVBlurShader()->getClassId(), 
                                   getCPtr(pData->getVBlurShader()));


            pEnv->activateState(pBlurState, &oOverride1);

            aDrawBuffers[0] = GL_COLOR_ATTACHMENT0_EXT;

#ifndef WIN32
            glDrawBuffers(1, aDrawBuffers);
#endif
            
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

            pEnv->deactivateState();
        }
    }

    pBlurTarget->deactivate(pEnv);

    glViewport(0, 0, 800, 800);

    ChunkMaterialPtr pTCM = pData->getToneMappingMaterial();

    if(pTCM != NullFC)
    {
        State *pTState = getCPtr(pTCM->getState());
        
        if(pTState != NULL)
        {
            pEnv->activateState(pTState, NULL);
            
            glBegin(GL_QUADS);
            {
                glTexCoord2f(0.00, 0.00);
                glVertex2f  (0.05, 0.05);
                
                glTexCoord2f(1.00, 0.00);
                glVertex2f  (0.95, 0.05);
                
                glTexCoord2f(1.00, 1.00);
                glVertex2f  (0.95, 0.95);
                
                glTexCoord2f(0.00, 1.00);
                glVertex2f  (0.05, 0.95);
            }
            glEnd();
            
            pEnv->deactivateState();
        }
    }

    glPopMatrix();
}


#if 0
FrameBufferObjectPtrConst HDRStage::getRenderTarget(void) 
{
    return _sfRenderTarget.getValue();
}
#endif

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGHDRSTAGE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGHDRSTAGE_INLINE_CVSID;
}

    

