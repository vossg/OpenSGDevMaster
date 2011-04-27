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

#include "OSGDisplayFilterStage.h"
#include "OSGRenderAction.h"
#include "OSGMatrixUtility.h"

#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"

#include "OSGResolutionDisplayFilter.h"
#include "OSGColorDisplayFilter.h"
#include "OSGDistortionDisplayFilter.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDisplayFilterStageBase.cpp file.
// To modify it, please change the .fcd file (OSGDisplayFilterStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DisplayFilterStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            DisplayFilterStage::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &DisplayFilterStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            DisplayFilterStage::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &DisplayFilterStage::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DisplayFilterStage::DisplayFilterStage(void) :
    Inherited()
{
}

DisplayFilterStage::DisplayFilterStage(const DisplayFilterStage &source) :
    Inherited(source)
{
}

DisplayFilterStage::~DisplayFilterStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DisplayFilterStage::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DisplayFilterStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DisplayFilterStage NI" << std::endl;
}

DisplayFilterStageDataTransitPtr 
    DisplayFilterStage::setupStageData(Int32 iPixelWidth,
                                       Int32 iPixelHeight)
{
    DisplayFilterStageDataTransitPtr returnValue = 
        DisplayFilterStageData::createLocal();

    if(returnValue == NULL)
        return returnValue;

    // Scene Buffer

    FrameBufferObjectUnrecPtr pFBO     = FrameBufferObject::createLocal();
    RenderBufferUnrecPtr      pDBuffer = RenderBuffer     ::createLocal();
    TextureBufferUnrecPtr     pTBuffer = TextureBuffer    ::createLocal();

    TextureObjChunkUnrecPtr   pTex     = TextureObjChunk  ::createLocal();
    ImageUnrecPtr             pImg     = Image            ::createLocal();

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
    
    pTex    ->setImage         (pImg             ); 
    pTex    ->setMinFilter     (GL_NEAREST       );
    pTex    ->setMagFilter     (GL_NEAREST       );
    pTex    ->setWrapS         (GL_CLAMP_TO_EDGE );
    pTex    ->setWrapT         (GL_CLAMP_TO_EDGE );
    
    pTBuffer->setTexture(pTex);

    pDBuffer->setInternalFormat(GL_DEPTH_COMPONENT24);
 

    pFBO->setSize(iPixelWidth, iPixelHeight);
    
    pFBO->setColorAttachment(pTBuffer, 0);
    pFBO->setDepthAttachment(pDBuffer   );

    pFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

    returnValue->setTarget(pFBO);


    ChunkMaterialUnrecPtr pCMat = ChunkMaterial::createLocal();

    pCMat->addChunk(pTex);

    returnValue->setBaseMaterial(pCMat);

    returnValue->setWidth (iPixelWidth );
    returnValue->setHeight(iPixelHeight);

    commitChanges();

    return returnValue;
}

void DisplayFilterStage::resizeStageData(DisplayFilterStageData *pData,
                                         Int32                   iPixelWidth,
                                         Int32                   iPixelHeight)
{
    FrameBufferObject *pFBO = pData->getTarget();

    if(pFBO == NULL)
        return;

    TextureBuffer *pTexBuffer = 
        dynamic_cast<TextureBuffer *>(pFBO->getColorAttachments(0));

    if(pTexBuffer == NULL)
        return;

    TextureObjChunk *pTex = pTexBuffer->getTexture();

    if(pTex == NULL)
        return;

    Image *pImg = pTex->getImage();

    if(pImg == NULL)
        return;

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

    pFBO->setSize(iPixelWidth, iPixelHeight);

    pData->setWidth (iPixelWidth );
    pData->setHeight(iPixelHeight);

    commitChanges();
}

ActionBase::ResultE DisplayFilterStage::renderEnter(Action *action)
{
    RenderAction *ract = dynamic_cast<RenderAction *>(action);

    if(ract == NULL)
        return Action::Continue;

    DisplayFilterStageDataUnrecPtr pData = 
        ract->getData<DisplayFilterStageData *>(_iDataSlotId);

    DrawEnv &oEnv = ract->getActivePartition()->getDrawEnv();

    bool                      bFilterActive = false;
    RenderPartition::Mode     partMode      = RenderPartition::StateSorting;

    CalibrationPatternFilter *pCalibFilter  = NULL;
    ResolutionDisplayFilter  *pResFilter    = NULL;
    DistortionDisplayFilter  *pDistFilter   = NULL;
    ColorDisplayFilter       *pColFilter    = NULL;
    bool                      bDoDraw       = true;

    if(_mfFilterGroups.size() == 0)
    {
        pCalibFilter = this->getCalibrationPatternFilter();

        pResFilter   = this->getResolutionFilter();

        pColFilter   = this->getColorFilter();

        pDistFilter  = this->getDistortionFilter();

    }
    else
    {
        // Linear search, optimize of needed

        MFFilterGroupsType::const_iterator gIt  = _mfFilterGroups.begin();
        MFFilterGroupsType::const_iterator gEnd = _mfFilterGroups.end  ();

        for(; gIt != gEnd; ++gIt)
        {
            if((*gIt)->matches(oEnv.getDrawerId(),
                               oEnv.getDrawableId()) == true)
            {
                pCalibFilter = (*gIt)->getCalibrationPatternFilter();

                pResFilter   = (*gIt)->getResolutionFilter();

                pColFilter   = (*gIt)->getColorFilter();

                pDistFilter  = (*gIt)->getDistortionFilter();
                
                bDoDraw = 
                    ((*gIt)->matches(this->getActiveGroup(),
                                     oEnv. getDrawableId () == true) ||
                     (this->getActiveGroup()                == -1  )  );

                break;
            }
        }
    }


    if(pCalibFilter != NULL && pCalibFilter->getEnabled() == true)
    {
        if(pData != NULL)
            pData->setCalibFilter(pCalibFilter);
            
        bFilterActive = true;
        partMode      = RenderPartition::SimpleCallback;
    }
    else
    {
        if(pData != NULL)
            pData->setCalibFilter(NULL);
    }

    if(pColFilter               != NULL &&
       pColFilter->getEnabled() == true  )
    {
        if(pData != NULL)
            pData->setColFilter(pColFilter);
        
        bFilterActive = true;
    }
    else
    {
        if(pData != NULL)
        {
            pData->setColFilter(NULL);
            
            ColorDisplayFilter::deactivate(pData);
        }
    }        
    if(pDistFilter               != NULL &&
       pDistFilter->getEnabled() == true  )
    {
        if(pData != NULL)
            pData->setDistFilter(pDistFilter);

        bFilterActive = true;
    }
    else
    {
        if(pData != NULL)
            pData->setDistFilter(NULL);
    }

    
    UInt32 uiTargetWidth  = oEnv.getPixelWidth ();
    UInt32 uiTargetHeight = oEnv.getPixelHeight();

    Int32 iLeft   = oEnv.getPixelLeft  ();
    Int32 iRight  = oEnv.getPixelRight ();
    Int32 iBottom = oEnv.getPixelBottom();
    Int32 iTop    = oEnv.getPixelTop   ();

    if(pResFilter               != NULL &&
       pResFilter->getEnabled() == true  )
    {
        bFilterActive = true;
        
        uiTargetWidth  = UInt32(uiTargetWidth  * pResFilter->getDownScale());
        uiTargetHeight = UInt32(uiTargetHeight * pResFilter->getDownScale());

        iLeft   = Int32(iLeft   * pResFilter->getDownScale());
        iRight  = Int32(iRight  * pResFilter->getDownScale());
        iBottom = Int32(iBottom * pResFilter->getDownScale());
        iTop    = Int32(iTop    * pResFilter->getDownScale());
        
    }

    if(pData == NULL)
    {
        pData = setupStageData(uiTargetWidth,
                               uiTargetHeight);

        if(pData == NULL)
            return Action::Continue;

        this->setData(pData, _iDataSlotId, ract);

        pData->setColFilter  (pColFilter  );
        pData->setDistFilter (pDistFilter );
        pData->setCalibFilter(pCalibFilter);
    }


    if((pData->getWidth () != uiTargetWidth ) ||
       (pData->getHeight() != uiTargetHeight)  )
    {
        resizeStageData(pData, uiTargetWidth, uiTargetHeight);
    }

   


    if(bFilterActive == false)
        return Action::Continue;

    ract->disableDefaultPartition();

    this->beginPartitionGroup(ract);
    {
        this->pushPartition(ract, 0x0000, partMode);
        {
            RenderPartition   *pPart    = ract ->getActivePartition();
            FrameBufferObject *pTarget  = pData->getTarget();
            Viewport          *pPort    = ract ->getViewport();
            Camera            *pCam     = ract ->getCamera  ();
            Background        *pBack    = ract ->getBackground();
            

            pPart->setRenderTarget(pTarget);
            
            if(pPort != NULL)
            {
                pPart->setWindow(ract->getWindow());
                
                if(pTarget != NULL)
                {
                    pPart->calcViewportDimension(iLeft  ,
                                                 iBottom,
                                                 iRight ,
                                                 iTop   ,
                                                 
                                                 pTarget->getWidth    (),
                                                 pTarget->getHeight   ());
                }
                else
                {
                    pPart->calcViewportDimension(
                        pPort->getLeft  (),
                        pPort->getBottom(),
                        pPort->getRight (),
                        pPort->getTop   (),
                        
                        ract->getWindow()->getWidth (),
                        ract->getWindow()->getHeight());
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

            if(pCalibFilter != NULL && pCalibFilter->getEnabled() == true)
            {
                RenderPartition::SimpleDrawCallback f;

                if(bDoDraw == true)
                {
                    f = boost::bind(&DisplayFilterStage::processCalibActive, 
                                    this, _1);
                }
                else
                {
                    f = boost::bind(&DisplayFilterStage::processCalibInactive, 
                                    this, _1);
                }

                pPart->dropFunctor(f);
            }
            else
            {
                this->recurseFromThis(ract);
            }
        }
        this->popPartition(ract);
        
        this->pushPartition(ract,
                            (RenderPartition::CopyWindow      |
                             RenderPartition::CopyViewportSize),
                            RenderPartition::SimpleCallback);
        {
            RenderPartition *pPart  = ract->getActivePartition();

            Matrix m, t;
                
            m.setIdentity();
            t.setIdentity();
                
            MatrixOrthogonal( m,
                              0.f, 1.f,
                              0.f, 1.f,
                             -1.f, 1.f);
            
            pPart->setupProjection(m, t);
                
            RenderPartition::SimpleDrawCallback f;
                
            f = boost::bind(&DisplayFilterStage::postProcess, this, _1);
                
            pPart->dropFunctor(f);
        }
        this->popPartition(ract);
    }
    this->endPartitionGroup(ract);

    return Action::Skip;
}

ActionBase::ResultE DisplayFilterStage::renderLeave(Action *action)
{
    return Action::Skip;
}

void DisplayFilterStage::processCalibActive(DrawEnv *pEnv)
{
    DisplayFilterStageData *pData = 
        pEnv->getData<DisplayFilterStageData *>(_iDataSlotId);

    if(pData == NULL)
        return;

    CalibrationPatternFilter *pCalibFilter = pData->getCalibFilter();

    if(pCalibFilter == NULL)
        return;
        
    pCalibFilter->processActive(pData, pEnv);
}

void DisplayFilterStage::processCalibInactive(DrawEnv *pEnv)
{
    DisplayFilterStageData *pData = 
        pEnv->getData<DisplayFilterStageData *>(_iDataSlotId);

    if(pData == NULL)
        return;

    CalibrationPatternFilter *pCalibFilter = pData->getCalibFilter();

    if(pCalibFilter == NULL)
        return;
        
    pCalibFilter->processInactive(pData, pEnv);
}

void DisplayFilterStage::postProcess(DrawEnv *pEnv)
{
    DisplayFilterStageData *pData = 
        pEnv->getData<DisplayFilterStageData *>(_iDataSlotId);

    if(pData == NULL)
        return;

    ColorDisplayFilter      *pColFilter   = pData->getColFilter ();
    DistortionDisplayFilter *pDistFilter  = pData->getDistFilter();


    ChunkMaterial           *pSourceMat   = pData->getBaseMaterial();
    State                   *pSourceState = pSourceMat->getState();

    glColor3f(1.f, 0.f, 0.f);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glLoadIdentity();

    if(pColFilter != NULL)
    {
        pColFilter->process(pData);
    }
    
    pEnv->activateState(pSourceState, NULL);

    if(pColFilter == NULL)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    if(pDistFilter != NULL)
    {
        pDistFilter->process(pData);
    }
    else
    {
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
    }

    if(pColFilter == NULL)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    pEnv->deactivateState();

    glPopMatrix();
}

OSG_END_NAMESPACE
