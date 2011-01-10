/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGCubeMapGenerator.h"
#include "OSGCubeMapGeneratorStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGRenderAction.h"
#include "OSGPerspectiveCamera.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCubeMapGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGCubeMapGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CubeMapGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            CubeMapGenerator::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &CubeMapGenerator::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            CubeMapGenerator::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &CubeMapGenerator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CubeMapGenerator::CubeMapGenerator(void) :
    Inherited()
{
}

CubeMapGenerator::CubeMapGenerator(const CubeMapGenerator &source) :
    Inherited(source)
{
}

CubeMapGenerator::~CubeMapGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CubeMapGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CubeMapGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CubeMapGenerator NI" << std::endl;
}

ActionBase::ResultE CubeMapGenerator::renderEnter(Action *action)
{
    static Matrix transforms[] = 
    { 
        Matrix( 1,  0,  0,  0,
                0, -1,  0,  0,
                0,  0, -1,  0,
                0,  0,  0,  1),
        
        Matrix(-1,  0,  0,  0,
                0, -1,  0,  0,
                0,  0,  1,  0,
                0,  0,  0,  1),
        
        Matrix( 1,  0,  0,  0,
                0,  0, -1,  0,
                0,  1,  0,  0,
                0,  0,  0,  1),
        
        Matrix( 1,  0,  0,  0,
                0,  0,  1,  0,
                0, -1,  0,  0,
                0,  0,  0,  1),
        
        Matrix( 0,  0, -1,  0,
                0, -1,  0,  0,
               -1,  0,  0,  0,
                0,  0,  0,  1),
        
        Matrix( 0,  0,  1,  0,
                0, -1,  0,  0,
                1,  0,  0,  0,
                0,  0,  0,  1)
    };

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Action::ResultE  returnValue = Action::Continue;

    Background      *pBack    = a->getBackground();

    Viewport        *pPort    = a->getViewport();

    Node            *pActNode = a->getActNode();

    CubeMapGeneratorStageData *pData = 
        a->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = this->initData(a);
    }

    TraversalValidator::ValidationStatus eStatus = this->validateOnEnter(a);

    if(eStatus == TraversalValidator::Run)
    {
        this->beginPartitionGroup(a);
        {
            FrameBufferObject *pTarget  = this->getRenderTarget();
                
            if(pTarget == NULL)
            {
                pTarget  = pData->getRenderTarget();
            }

            Pnt3f oOrigin;

            if(this->getOriginMode() == CubeMapGenerator::UseStoredValue)
            {
                oOrigin = this->getOrigin();
            }
            else if(this->getOriginMode() == CubeMapGenerator::UseBeacon)
            {
                fprintf(stderr, "CubemapGen::UseBeacon NYI\n");
            }
            else if(this->getOriginMode() == 
                                       CubeMapGenerator::UseCurrentVolumeCenter)
            {
                BoxVolume oWorldVol;

                commitChanges();

                pActNode->updateVolume();
                
                pActNode->getWorldVolume(oWorldVol);
                
                oWorldVol.getCenter(oOrigin);
            }
            else if(this->getOriginMode() == 
                                       CubeMapGenerator::UseParentsVolumeCenter)
            {
                fprintf(stderr, "CubemapGen::UseParentsCenter NYI\n");
            }

            Camera *pCam = pData->getCamera();

            pActNode->setTravMask(0);

            for(UInt32 i = 0; i < 6; ++i)
            {
                this->pushPartition(a);
                {
                    RenderPartition   *pPart    = a->getActivePartition();
                
                    pPart->setVolumeDrawing(false);

                    pPart->setRenderTarget(pTarget       );
                    pPart->setWindow      (a->getWindow());

                    pPart->calcViewportDimension(0,
                                                 0,
                                                 1,
                                                 1,
                                                 this->getWidth (),
                                                 this->getHeight());
                
                    Matrix m, t;
            
                    // set the projection
                    pCam->getProjection          (m, 
                                                  pPart->getViewportWidth (), 
                                                  pPart->getViewportHeight());
                
                    pCam->getProjectionTranslation(t, 
                                                   pPart->getViewportWidth (), 
                                                   pPart->getViewportHeight());
                
                    pPart->setupProjection(m, t);
            
                    m = transforms[i];
            
                    m[3][0] = oOrigin[0];
                    m[3][1] = oOrigin[1];
                    m[3][2] = oOrigin[2];

                    m.invert();

                    pPart->setupViewing(m);
            
                    pPart->setNear     (pCam->getNear());
                    pPart->setFar      (pCam->getFar ());
                    
                    pPart->calcFrustum();
                
                    if(this->getBackground() == NULL)
                    {
                        pPart->setBackground(pBack);
                    }
                    else
                    {
                        pPart->setBackground(this->getBackground());
                    }
                
                    if(this->getRoot() != NULL)
                    {
                        this->recurse(a, this->getRoot());
                    }
                    else
                    {
                        this->recurse(a, pPort->getRoot());
                    }

                    pPart->setDrawBuffer(GL_COLOR_ATTACHMENT0_EXT + i);

#ifdef OSG_DEBUGX
                    std::string szMessage("CubeX\n");
                    pPart->setDebugString(szMessage          );
#endif
                }
                this->popPartition(a);
            }

            pActNode->setTravMask(~0);
        }
        this->endPartitionGroup(a);
    }

    OSG_ASSERT(pActNode == a->getActNode());

    returnValue = Inherited::renderEnter(action);

    action->useNodeList(false);

    return returnValue;
}

ActionBase::ResultE CubeMapGenerator::renderLeave(Action *action)
{
    Action::ResultE returnValue = Action::Continue;

    returnValue = Inherited::renderLeave(action);

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    this->validateOnLeave(a);

    return returnValue;
}


CubeMapGeneratorStageDataTransitPtr CubeMapGenerator::setupStageData(
    RenderActionBase *pAction)
{
    CubeMapGeneratorStageDataTransitPtr returnValue = 
        CubeMapGeneratorStageData::createLocal();
    
    if(returnValue == NULL)
        return returnValue;

    FrameBufferObjectUnrecPtr pCubeTarget  = NULL;
    RenderBufferUnrecPtr      pDepthBuffer = NULL;

    if(this->getRenderTarget() == NULL)
    {
        pCubeTarget  = FrameBufferObject::createLocal();
        pDepthBuffer = RenderBuffer     ::createLocal();

        pDepthBuffer->setInternalFormat (GL_DEPTH_COMPONENT24);

        pCubeTarget ->setDepthAttachment(pDepthBuffer        );

        returnValue ->setRenderTarget   (pCubeTarget         );
    }
    else
    {
        pCubeTarget = this->getRenderTarget();
    }

    TextureObjChunkUnrecPtr   pCubeTex     = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexture))
    {
        pCubeTex = TextureObjChunk::createLocal();

        ImageUnrecPtr pImg = Image::createLocal();
    
        pImg->set(Image::OSG_RGB_PF, 
                  getWidth (), 
                  getHeight(),
                  1,
                  1,
                  1,
                  0.0,
                  0,
                  Image::OSG_UINT8_IMAGEDATA,
                  false,
                  6);
        
        pCubeTex   ->setImage         (pImg              ); 
        pCubeTex   ->setMinFilter     (GL_LINEAR         );
        pCubeTex   ->setMagFilter     (GL_LINEAR         );
        pCubeTex   ->setWrapS         (GL_CLAMP_TO_EDGE  );
        pCubeTex   ->setWrapT         (GL_CLAMP_TO_EDGE  );
        pCubeTex   ->setWrapR         (GL_CLAMP_TO_EDGE  );
        pCubeTex   ->setInternalFormat(getTextureFormat());
    }
    else
    {
        pCubeTex = _sfTexture.getValue();
    }

    TextureEnvChunkUnrecPtr pCubeTexEnv  = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        pCubeTexEnv = TextureEnvChunk::createLocal();
        
        pCubeTexEnv->setEnvMode       (GL_REPLACE       );
    }

    TexGenChunkUnrecPtr           pCubeTexGen   = NULL;
    TextureTransformChunkUnrecPtr pCubeTexTrans = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        pCubeTexGen = TexGenChunk::createLocal();

        pCubeTexGen->setGenFuncS(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncT(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncR(GL_REFLECTION_MAP);

        pCubeTexTrans = TextureTransformChunk::createLocal();

        pCubeTexTrans->setUseCameraBeacon(true);
    }


    static GLenum targets[6] = 
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
    };

    for(UInt32 i = 0; i < 6; ++i)
    {
        TextureBufferUnrecPtr pCubeTexBuffer = TextureBuffer::createLocal();
    
        pCubeTexBuffer->setTexture  (pCubeTex  );
        pCubeTexBuffer->setTexTarget(targets[i]);

        pCubeTarget->setColorAttachment(pCubeTexBuffer,    i);
    }

    pCubeTarget->setSize(getWidth (),
                         getHeight());

    if(0x0000 != (_sfSetupMode.getValue() & OverrideTex))
    {
        returnValue->addChunk(pCubeTex,
                              getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        returnValue->addChunk(pCubeTexEnv,
                              getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        returnValue->addChunk(pCubeTexGen,
                              getTexUnit());
        returnValue->addChunk(pCubeTexTrans,
                              getTexUnit());

        returnValue->setTexTransform(pCubeTexTrans);
    }

    if(this->getCamera() == NULL)
    {
        PerspectiveCameraUnrecPtr pCam = PerspectiveCamera::createLocal();

        pCam->setNear(pAction->getCamera()->getNear());
        pCam->setFar (pAction->getCamera()->getFar ());
        
        pCam->setFov (osgDegree2Rad(90.f));

        returnValue->setCamera(pCam);
    }

    return returnValue;
}

CubeMapGeneratorStageData *CubeMapGenerator::initData(RenderActionBase *pAction)
{
    CubeMapGeneratorStageDataUnrecPtr pData = 
        pAction->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction);
        
        this->setData(pData, _iDataSlotId, pAction);
    }

    return pData;
}


OSG_END_NAMESPACE
