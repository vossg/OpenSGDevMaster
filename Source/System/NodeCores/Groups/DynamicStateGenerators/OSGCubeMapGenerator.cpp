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

#include <OSGConfig.h>

#include "OSGCubeMapGenerator.h"
#include "OSGCubeMapGeneratorStageData.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureEnvChunk.h"
#include "OSGTexGenChunk.h"
#include "OSGRenderAction.h"

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

    Camera          *pCam     = a->getCamera();
    Background      *pBack    = a->getBackground();

    Viewport        *pPort    = a->getViewport();

    Node            *pActNode = a->getActNode();

    a->beginPartitionGroup();
    {
        FrameBufferObject *pTarget  = this->getRenderTarget();
                
        if(pTarget == NULL)
        {
            this->initData(a);
            
            pTarget  = this->getRenderTarget();
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
            DynamicVolume oWorldVol;

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

        for(UInt32 i = 0; i < 6; ++i)
        {
            a->pushPartition();
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
                
                Camera            *pCam     = a->getCamera  ();

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

               
                pActNode->setTravMask(0);
                
                if(this->getRoot() != NULL)
                {
                    a->recurse(this->getRoot());
                }
                else
                {
                    a->recurse(pPort->getRoot());
                }

                pActNode->setTravMask(~0);

                pPart->setDrawBuffer(GL_COLOR_ATTACHMENT0_EXT + i);

#ifdef OSG_DEBUGX
                std::string szMessage("CubeX\n");
                pPart->setDebugString(szMessage          );
#endif
            }
            a->popPartition();
        }
    }
    a->endPartitionGroup();

    OSG_ASSERT(pActNode == a->getActNode());

    returnValue = Inherited::renderEnter(action);

    action->useNodeList(false);

    return returnValue;
}

ActionBase::ResultE CubeMapGenerator::renderLeave(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Action::ResultE returnValue = Action::Continue;

    returnValue = Inherited::renderLeave(action);

    return returnValue;
}


CubeMapGeneratorStageDataTransitPtr CubeMapGenerator::setupStageData(
    RenderActionBase *pAction)
{
    CubeMapGeneratorStageDataTransitPtr returnValue = 
        CubeMapGeneratorStageData::createLocal();
    
    if(returnValue == NULL)
        return returnValue;

    FrameBufferObjectUnrecPtr pCubeTarget  = FrameBufferObject::createLocal();

    RenderBufferUnrecPtr      pDepthBuffer = RenderBuffer     ::createLocal();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

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
        pCubeTex   ->setWrapS         (GL_REPEAT         );
        pCubeTex   ->setWrapT         (GL_REPEAT         );
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

    TexGenChunkUnrecPtr     pCubeTexGen  = NULL;

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        pCubeTexGen = TexGenChunk::createLocal();

        pCubeTexGen->setGenFuncS(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncT(GL_REFLECTION_MAP);
        pCubeTexGen->setGenFuncR(GL_REFLECTION_MAP);
        
        pCubeTexGen->setSBeacon(pAction->getActNode());
        pCubeTexGen->setTBeacon(pAction->getActNode());
        pCubeTexGen->setRBeacon(pAction->getActNode());
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

        pCubeTarget->setSize           (getWidth (),
                                        getHeight());
        pCubeTarget->setColorAttachment(pCubeTexBuffer,    i);
        pCubeTarget->setDepthAttachment(pDepthBuffer        );
        
        setRenderTarget(pCubeTarget);
    }

    if(0x0000 != (_sfSetupMode.getValue() & OverrideTex))
    {
        this->addChunk(pCubeTex,
                       getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexEnv))
    {
        this->addChunk(pCubeTexEnv,
                       getTexUnit());
    }

    if(0x0000 != (_sfSetupMode.getValue() & SetupTexGen))
    {
        this->addChunk(pCubeTexGen,
                       getTexUnit());
    }

    return returnValue;
}

void CubeMapGenerator::initData(RenderActionBase *pAction)
{
    CubeMapGeneratorStageDataUnrecPtr pData = 
        pAction->getData<CubeMapGeneratorStageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = setupStageData(pAction);
        
        this->setData(pData, _iDataSlotId, pAction);
    }
}


OSG_END_NAMESPACE
