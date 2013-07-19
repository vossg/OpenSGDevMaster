/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#include "OSGPostShaderStage.h"
#include "OSGPostShaderStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"
#include "OSGRenderAction.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGDrawEnv.h"
#include "OSGStateOverride.h"
#include "OSGTextureEnvChunk.h"
#include "OSGGL.h"

#include "OSGMatrixUtility.h"

#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPostShaderStageBase.cpp file.
// To modify it, please change the .fcd file (OSGPostShaderStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 PostShaderStage::_uiFramebuffer_object_extension = 
    Window::invalidExtensionID;

UInt32 PostShaderStage::_extDepthTexture                = 
    Window::invalidExtensionID;

UInt32 PostShaderStage::_uiFuncDrawBuffers              = 
    Window::invalidFunctionID;

const std::string PostShaderStage::ShaderSceneColorTexName  = 
    std::string("PostSceneColorTex");
const std::string PostShaderStage::ShaderSceneDepthTexName  = 
    std::string("PostSceneDepthTex");
const std::string PostShaderStage::ShaderFBOWidthName       = 
    std::string("PostFBOWidth");
const std::string PostShaderStage::ShaderFBOHeightName      = 
    std::string("PostFBOHeight");
const std::string PostShaderStage::ShaderCameraNearName     = 
    std::string("PostCameraNear");
const std::string PostShaderStage::ShaderCameraFarName      = 
    std::string("PostCameraFar");
const std::string PostShaderStage::PrePassXName             = 
    std::string("PostPass");
const std::string PostShaderStage::PostPassXColorTexName    = 
    std::string("ColorTex");
const std::string PostShaderStage::PostPassXColorWidthName  = 
    std::string("Width");
const std::string PostShaderStage::PostPassXColorHeightName = 
    std::string("Height");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PostShaderStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            PostShaderStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&PostShaderStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            PostShaderStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&PostShaderStage::renderLeave));

        _uiFramebuffer_object_extension = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _extDepthTexture      = 
            Window::registerExtension("GL_ARB_depth_texture");

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebuffer_object_extension);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

PostShaderStageDataTransitPtr 
    PostShaderStage::setupStageData(Int32 iPixelWidth,
                                    Int32 iPixelHeight)
{
    PostShaderStageDataTransitPtr returnValue = 
        PostShaderStageData::createLocal();

    if(returnValue == NULL)
        return returnValue;

    OSG::Thread::setCurrentLocalFlags();

    // Scene Target
    FrameBufferObjectUnrecPtr pSceneFBO = FrameBufferObject::createLocal();
        
    //Depth texture
                            _pSceneDepthTex    = TextureObjChunk::createLocal();
    TextureEnvChunkUnrecPtr  pSceneDepthTexEnv = TextureEnvChunk::createLocal();
    ImageUnrecPtr            pDepthImg         = Image          ::createLocal();

    pDepthImg->set(Image::OSG_L_PF, 
                   iPixelWidth, 
                   iPixelHeight,
                   1,
                   1,
                   1,
                   0.0,
                   NULL,
                   Image::OSG_UINT8_IMAGEDATA,
                   false);

    _pSceneDepthTex  ->setImage         (pDepthImg         ); 
    _pSceneDepthTex  ->setMinFilter     (GL_LINEAR         );
    _pSceneDepthTex  ->setMagFilter     (GL_LINEAR         );
    _pSceneDepthTex  ->setWrapS         (GL_CLAMP_TO_EDGE  );
    _pSceneDepthTex  ->setWrapT         (GL_CLAMP_TO_EDGE  );
    _pSceneDepthTex  ->setInternalFormat(GL_DEPTH_COMPONENT);
    _pSceneDepthTex  ->setExternalFormat(GL_DEPTH_COMPONENT);

    pSceneDepthTexEnv->setEnvMode       (GL_REPLACE        );
    
    TextureBufferUnrecPtr pDepthBuffer = TextureBuffer::createLocal();
    //pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );
    
    pDepthBuffer->setTexture(_pSceneDepthTex);

        
    //Color Buffer
                            _pSceneTex     = TextureObjChunk::createLocal();
    TextureEnvChunkUnrecPtr  pSceneTexEnv  = TextureEnvChunk::createLocal();
    ImageUnrecPtr            pImg          = Image          ::createLocal();
    
    pImg->set(Image::OSG_RGB_PF, 
              iPixelWidth, 
              iPixelHeight,
              1,
              1,
              1,
              0.0,
              0,
              Image::OSG_UINT8_IMAGEDATA,
              false);
    
    _pSceneTex  ->setImage         (pImg                  ); 
    _pSceneTex  ->setMinFilter     (GL_LINEAR             );
    _pSceneTex  ->setMagFilter     (GL_LINEAR             );
    _pSceneTex  ->setWrapS         (GL_CLAMP_TO_EDGE      );
    _pSceneTex  ->setWrapT         (GL_CLAMP_TO_EDGE      );
    _pSceneTex  ->setInternalFormat(getColorBufferFormat());

    pSceneTexEnv->setEnvMode       (GL_REPLACE            );
    
    TextureBufferUnrecPtr pSceneTexBuffer   = TextureBuffer::createLocal();
    
    pSceneTexBuffer->setTexture(_pSceneTex);
    

    
    pSceneFBO->setSize(iPixelWidth, iPixelHeight);
    
    pSceneFBO->setColorAttachment(pSceneTexBuffer, 0);
    pSceneFBO->setDepthAttachment(pDepthBuffer      );
    
    pSceneFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    setRenderTarget(pSceneFBO);
    
    // general mat chunk

    //Init all of the render passes
    _vPostProcessPasses.clear();

    UInt32 NumPasses = getNumPasses();

    for(UInt32 i =0; i != NumPasses ; ++i)
    {
        _vPostProcessPasses.push_back(
            RenderPassData::create( getVertexShaders(i),
                                    getFragmentShaders(i),
                                    (i == NumPasses-1),
                                    i,
                                    iPixelWidth,
                                    iPixelHeight,
                                    returnValue.get(),
                                    getPassSizes(i),
                                   _pSceneTex,
                                   _pSceneDepthTex,
                                   _vPostProcessPasses,
                                    pSceneFBO));
    }
    
    OSG::Thread::resetCurrentLocalFlags();

    Thread::getCurrentChangeList()->commitChanges();

    return returnValue;
}

void PostShaderStage::resizeStageData(PostShaderStageData *pData,
                                      Int32                iPixelWidth,
                                      Int32                iPixelHeight)
{

    RenderPassVector::iterator passIt = _vPostProcessPasses.begin();
    //Update the sizes of the passes
    for(; passIt != _vPostProcessPasses.end(); ++passIt)
    {
        (*passIt)->updateSize(iPixelWidth, iPixelHeight, _vPostProcessPasses);
    }

    //Update the image sizes
    _pSceneDepthTex->getImage()->set(Image::OSG_L_PF, 
                                     iPixelWidth, 
                                     iPixelHeight,
                                     1,
                                     1,
                                     1,
                                     0.0,
                                     NULL,
                                     Image::OSG_UINT8_IMAGEDATA,
                                     false);
    
    _pSceneTex->getImage()->set(Image::OSG_RGB_PF, 
                                iPixelWidth, 
                                iPixelHeight,
                                1,
                                1,
                                1,
                                0.0,
                                0,
                                Image::OSG_UINT8_IMAGEDATA,
                                false);

    getRenderTarget()->setSize(iPixelWidth, iPixelHeight);
}

void PostShaderStage::initData(RenderAction *pAction)
{
    PostShaderStageDataUnrecPtr pData = NULL;

    pData = setupStageData(pAction->getActivePartition()->getViewportWidth (),
                           pAction->getActivePartition()->getViewportHeight());
        
    pData->setWidth (pAction->getActivePartition()->getViewportWidth ());
    pData->setHeight(pAction->getActivePartition()->getViewportHeight());

    this->setData(pData, _iDataSlotId, pAction);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PostShaderStage::postProcess(DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtension(_uiFramebuffer_object_extension) == false ||
       win->hasExtension(_extDepthTexture               ) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

    glColor3f(1.f, 1.f, 1.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();

    PostShaderStageData *pData = 
        pEnv->getData<PostShaderStageData *>(_iDataSlotId);

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

    // PostShader pass
    glDisable(GL_DEPTH_TEST);

    //Render each pass
    RenderPassVector::iterator passIt = _vPostProcessPasses.begin();
    
    for(; passIt != _vPostProcessPasses.end(); ++passIt)
    {
        (*passIt)->draw(pEnv, pData);
    }

    glEnable(GL_DEPTH_TEST);

    pEnv->deactivateState();

    glPopMatrix();
}

Action::ResultE PostShaderStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->disableDefaultPartition();

    this->beginPartitionGroup(a);
    {
        this->pushPartition(a);
        {
            RenderPartition   *pPart    = a->getActivePartition();
            FrameBufferObject *pTarget  = this->getRenderTarget();
            Viewarea          *pArea    = a->getViewarea();
            Camera            *pCam     = a->getCamera  ();
            Background        *pBack    = a->getBackground();
            
            if(pTarget == NULL)
            {
                this->initData(a);

                pTarget  = this->getRenderTarget();
            }

            pPart->setRenderTarget(pTarget);
            
#ifdef OSG_DEBUGX
            std::string szMessage("RenderPartition\n");
            pPart->setDebugString(szMessage          );
#endif

            if(pArea != NULL)
            {
//                pPart->setViewport(pPort         );
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
                
            f = boost::bind(&PostShaderStage::postProcess, this, _1);
                
            pPart->dropFunctor(f);
        }
        this->popPartition(a);
    }
    this->endPartitionGroup(a);

    RenderPassVector::iterator passIt = _vPostProcessPasses.begin();

    //Update the uniform parameters to the shader
    for(; passIt != _vPostProcessPasses.end(); ++passIt)
    {
        (*passIt)->updateUniformVariables(a);
    }

    return Action::Skip;
}

Action::ResultE PostShaderStage::renderLeave(Action *action)
{
    return Action::Skip;
}

/*----------------------- constructors & destructors ----------------------*/

PostShaderStage::PostShaderStage(void) :
     Inherited         (    ),
    _vPostProcessPasses(    ),
    _pSceneTex         (NULL),
    _pSceneDepthTex    (NULL)
{
}

PostShaderStage::PostShaderStage(const PostShaderStage &source) :
     Inherited         (source                    ),
    _vPostProcessPasses(source._vPostProcessPasses),
    _pSceneTex         (source._pSceneTex         ),
    _pSceneDepthTex    (source._pSceneDepthTex    )
{
}

PostShaderStage::~PostShaderStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PostShaderStage::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(this->getRenderTarget() != NULL)
    {
        if((whichField & (ColorBufferFormatFieldMask |
                          VertexShadersFieldMask     |
                          FragmentShadersFieldMask   )))
        {
            this->setRenderTarget(NULL);
        }
    }
}

void PostShaderStage::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump PostShaderStage NI" << std::endl;
}

PostShaderStage::RenderPassData::RenderPassData(
    const std::string         &       szVertexProgram,
    const std::string         &       szFragmentProgram,
          bool                        isLastPass,
          UInt32                      uiIndex,
          Int32                       iPixelWidth,
          Int32                       iPixelHeight,
          PostShaderStageData *       pStageData,
    const Vec2f               &       vFBOSize,
          TextureObjChunk     * const pSceneColorTex,
          TextureObjChunk     * const pSceneDepthTex,
    const RenderPassVector    &       vPasses,
          FrameBufferObject   * const pSceneFBO) : 

    _pShader                (NULL      ),
    _pFBO                   (NULL      ),
    _pOutputTexture         (NULL      ),
    _bIsLassPass            (isLastPass),
    _uiIndex                (uiIndex   ),
    _vFBOSize               (vFBOSize  ),
    _vWidthRefs             (          ),
    _vHeightRefs            (          ),

    _bShaderHasSceneColorTex(false     ),
    _bShaderHasSceneDepthTex(false     ),
    _bShaderHasFBOWidth     (false     ),
    _bShaderHasFBOHeight    (false     ),
    _bShaderHasCameraNear   (false     ),
    _bShaderHasCameraFar    (false     )
{
    //If this pass is not the last
    if(!_bIsLassPass)
    {
        _pFBO = FrameBufferObject::createLocal();

        _pOutputTexture                  = TextureObjChunk::createLocal();
        TextureEnvChunkUnrecPtr pTexEnv  = TextureEnvChunk::createLocal();
        ImageUnrecPtr           pImg     = Image          ::createLocal();
        
        pImg->set(Image::OSG_RGB_PF, 
                  static_cast<Real32>(iPixelWidth)  * _vFBOSize.x() , 
                  static_cast<Real32>(iPixelHeight) * _vFBOSize.y(),
                  1,
                  1,
                  1,
                  0.0,
                  0,
                  Image::OSG_UINT8_IMAGEDATA,
                  false);
        
        _pOutputTexture   ->setImage         (pImg             ); 
        _pOutputTexture   ->setMinFilter     (GL_LINEAR        );
        _pOutputTexture   ->setMagFilter     (GL_LINEAR        );
        _pOutputTexture   ->setWrapS         (GL_CLAMP_TO_EDGE );
        _pOutputTexture   ->setWrapT         (GL_CLAMP_TO_EDGE );
        _pOutputTexture   ->setInternalFormat(GL_RGB           );

        pTexEnv->setEnvMode       (GL_REPLACE       );
        
        TextureBufferUnrecPtr pTexBuffer   = TextureBuffer::createLocal();
        
        pTexBuffer->setTexture(_pOutputTexture);
        
        _pFBO->setSize(static_cast<Real32>(iPixelWidth)  * _vFBOSize.x(),
                       static_cast<Real32>(iPixelHeight) * _vFBOSize.y());
        _pFBO->setColorAttachment(pTexBuffer, 0);
        _pFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

        pStageData->pushToRenderTargets(_pFBO);

        OSG_ASSERT(pStageData->getMFRenderTargets()->size() == _uiIndex + 1);
    }
    else
    {
        _pFBO = pSceneFBO;
    }

    //Update the flags on what uniforms are present
    _bShaderHasSceneColorTex = 
        ((szFragmentProgram.find(
              PostShaderStage::ShaderSceneColorTexName) != std::string::npos) ||
         (szVertexProgram  .find(
              PostShaderStage::ShaderSceneColorTexName) != std::string::npos));

    _bShaderHasSceneDepthTex = 
        ((szFragmentProgram.find(
              PostShaderStage::ShaderSceneDepthTexName) != std::string::npos) ||
         (szVertexProgram  .find(
              PostShaderStage::ShaderSceneDepthTexName) != std::string::npos));

    _bShaderHasFBOWidth = 
        ((szFragmentProgram.find(
              PostShaderStage::ShaderFBOWidthName) != std::string::npos) ||
         (szVertexProgram  .find(
              PostShaderStage::ShaderFBOWidthName) != std::string::npos));

    _bShaderHasFBOHeight = 
        ((szFragmentProgram.find(
              PostShaderStage::ShaderFBOHeightName) != std::string::npos) ||
         (szVertexProgram  .find(
              PostShaderStage::ShaderFBOHeightName) != std::string::npos));

    _bShaderHasCameraNear = 
        ((szFragmentProgram.find(
              PostShaderStage::ShaderCameraNearName) != std::string::npos) ||
         (szVertexProgram  .find(
              PostShaderStage::ShaderCameraNearName) != std::string::npos));

    _bShaderHasCameraFar = 
        ((szFragmentProgram.find(
              PostShaderStage::ShaderCameraFarName) != std::string::npos) ||
         (szVertexProgram  .find(
              PostShaderStage::ShaderCameraFarName) != std::string::npos));

    //Create the material used by this pass
    ChunkMaterialUnrecPtr pPostShaderMat = ChunkMaterial::createLocal();

    UInt16 uiTextureId = 0;

    _pShader = SimpleSHLChunk::createLocal();

    TextureEnvChunkUnrecPtr pGenericTexEnv  = TextureEnvChunk::createLocal();

    pGenericTexEnv->setEnvMode(GL_REPLACE);

    //Scene Color Texture
    if(_bShaderHasSceneColorTex)
    {
         pPostShaderMat->addChunk(pSceneColorTex,  uiTextureId);
         pPostShaderMat->addChunk(pGenericTexEnv,  uiTextureId);

        _pShader->addUniformVariable(
            PostShaderStage::ShaderSceneColorTexName.c_str(), uiTextureId);

        ++uiTextureId;
    }
    //Scene Depth Texture
    if(_bShaderHasSceneDepthTex)
    {
         pPostShaderMat->addChunk(pSceneDepthTex, uiTextureId);
         pPostShaderMat->addChunk(pGenericTexEnv, uiTextureId);

        _pShader->addUniformVariable(
            PostShaderStage::ShaderSceneDepthTexName.c_str(), uiTextureId);

        ++uiTextureId;
    }

    _vHeightRefs.clear();
    _vWidthRefs .clear();

    //Preceding passes variables
    std::string szVariableName;

    RenderPassVector::const_iterator passIt = vPasses.begin();

    for(; passIt != vPasses.end(); ++passIt)
    {
        szVariableName = (*passIt)->getOutputTextureName();

        if((szFragmentProgram.find(szVariableName) != std::string::npos) ||
           (szVertexProgram  .find(szVariableName) != std::string::npos)  )
        {
             pPostShaderMat->addChunk((*passIt)->getOutputTexture(), 
                                      uiTextureId);

             pPostShaderMat->addChunk(pGenericTexEnv, uiTextureId);

            _pShader->addUniformVariable(szVariableName.c_str(), uiTextureId);

            ++uiTextureId;
        }

        szVariableName = (*passIt)->getWidthName();

        if((szFragmentProgram.find(szVariableName) != std::string::npos) ||
           (szVertexProgram  .find(szVariableName) != std::string::npos)  )
        {
            _pShader->addUniformVariable<Real32>(
                szVariableName.c_str(),
                (*passIt)->getOutputTexture()->getImage()->getWidth());

            _vWidthRefs.push_back((*passIt)->getIndex());
        }

        szVariableName = (*passIt)->getHeightName();

        if((szFragmentProgram.find(szVariableName) != std::string::npos) ||
           (szVertexProgram  .find(szVariableName) != std::string::npos)  )
        {
            _pShader->addUniformVariable<Real32>(
                szVariableName.c_str(),
                (*passIt)->getOutputTexture()->getImage()->getHeight());

            _vHeightRefs.push_back((*passIt)->getIndex());
        }
    }

    MaterialChunkUnrecPtr pMatChunk = MaterialChunk::createLocal();

    pMatChunk     ->setLit(false);
    pPostShaderMat->addChunk(pMatChunk);

    _pShader->setVertexProgram  (szVertexProgram);
    _pShader->setFragmentProgram(szFragmentProgram);
    
    //Add the uniform parameters
    _pShader->addUniformVariable(ShaderFBOWidthName  .c_str(), 0.0f);
    _pShader->addUniformVariable(ShaderFBOHeightName .c_str(), 0.0f);
    _pShader->addUniformVariable(ShaderCameraNearName.c_str(), 0.0f);
    _pShader->addUniformVariable(ShaderCameraFarName .c_str(), 1.0f);
    
    pPostShaderMat->addChunk(_pShader, 0);
    
    pStageData->pushToShaderMaterials(pPostShaderMat);

    OSG_ASSERT(pStageData->getMFShaderMaterials()->size() == _uiIndex + 1);
}

void PostShaderStage::RenderPassData::updateUniformVariables(
    RenderAction *action)
{
    if(_bShaderHasFBOWidth)
    {
        _pShader->updateUniformVariable(
            PostShaderStage::ShaderFBOWidthName.c_str(),
            static_cast<Real32>(_pFBO->getWidth()));
    }

    if(_bShaderHasFBOHeight)
    {
        _pShader->updateUniformVariable(
            PostShaderStage::ShaderFBOHeightName.c_str(),
            static_cast<Real32>(_pFBO->getHeight()));
    }

    if(_bShaderHasCameraNear)
    {
        _pShader->updateUniformVariable(
            PostShaderStage::ShaderCameraNearName.c_str(),
            action->getCamera()->getNear());
    }

    if(_bShaderHasCameraFar)
    {
        _pShader->updateUniformVariable(
            PostShaderStage::ShaderCameraFarName.c_str(),
            action->getCamera()->getFar());
    }
}

void PostShaderStage::RenderPassData::updateSize(      
          Int32             iPixelWidth,
          Int32             iPixelHeight,
    const RenderPassVector &vPasses     )
{
    if(!_bIsLassPass)
    {
        _pOutputTexture->getImage()->set(
            Image::OSG_RGB_PF, 
            static_cast<Real32>(iPixelWidth)  * _vFBOSize.x(), 
            static_cast<Real32>(iPixelHeight) * _vFBOSize.y(),
            1,
            1,
            1,
            0.0,
            0,
            Image::OSG_UINT8_IMAGEDATA,
            false);
        
        _pFBO->setSize(static_cast<Real32>(iPixelWidth)  * _vFBOSize.x(),
                       static_cast<Real32>(iPixelHeight) * _vFBOSize.y());
    }

    //Update references to preceding passes
    for(UInt32 i = 0; i < _vWidthRefs.size() ; ++i)
    {
        _pShader->updateUniformVariable<Real32>(
            vPasses[_vWidthRefs[i]]->getWidthName().c_str(),
            vPasses[
                _vWidthRefs[i]]->getOutputTexture()->getImage()->getWidth());
    }

    for(UInt32 i = 0; i < _vHeightRefs.size() ; ++i)
    {
        _pShader->updateUniformVariable<Real32>(
            vPasses[_vHeightRefs[i]]->getHeightName().c_str(),
            vPasses[
                _vHeightRefs[i]]->getOutputTexture()->getImage()->getHeight());
    }
}

void PostShaderStage::RenderPassData::draw(
    DrawEnv            *        pEnv,
    PostShaderStageData * const pStageData)
{
    if(!_bIsLassPass)
    {
        pStageData->getRenderTargets(_uiIndex)->activate(pEnv);

        glViewport(pEnv->getPixelLeft  (), 
                   pEnv->getPixelBottom(),
                   pEnv->getPixelLeft () +
                   pStageData->getRenderTargets(_uiIndex)->getWidth(),
                   pEnv->getPixelBottom() +
                   pStageData->getRenderTargets(_uiIndex)->getHeight());
    }
    else
    {
        glViewport(pEnv->getPixelLeft  (), 
                   pEnv->getPixelBottom(),
                   pEnv->getPixelRight (),
                   pEnv->getPixelHeight());
    }


    pEnv->activateState(pStageData->getShaderMaterials(_uiIndex)->getState(), 
                        NULL);

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
            
    if(!_bIsLassPass)
    {
        pStageData->getRenderTargets(_uiIndex)->deactivate(pEnv);
    }
}

PostShaderStage::RenderPassDataPtr
PostShaderStage::RenderPassData::create(
    const std::string         &       szVertexProgram,
    const std::string         &       szFragmentProgram,
          bool                        bIsLastPass,
          UInt32                      uiIndex,
          Int32                       iPixelWidth,
          Int32                       iPixelHeight,
          PostShaderStageData *       pStageData,
    const Vec2f               &       vFBOSize,
          TextureObjChunk     * const pSceneColorTex,
          TextureObjChunk     * const pSceneDepthTex,
    const RenderPassVector    &       vPasses,
          FrameBufferObject   * const pSceneFBO)
{
    return RenderPassDataPtr(new RenderPassData(szVertexProgram,
                                                szFragmentProgram,
                                                bIsLastPass,
                                                uiIndex,
                                                iPixelWidth,
                                                iPixelHeight,
                                                pStageData,
                                                vFBOSize,
                                                pSceneColorTex,
                                                pSceneDepthTex,
                                                vPasses,
                                                pSceneFBO));
}

OSG_END_NAMESPACE
