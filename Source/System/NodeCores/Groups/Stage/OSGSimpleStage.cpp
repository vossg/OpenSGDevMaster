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

#include <sstream>
#include <fstream>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGSimpleStage.h"

#include "OSGBackground.h"
#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSimpleStageBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleStage.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void SimpleStage::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void SimpleStage::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SimpleStage::SimpleStage(void) :
    Inherited()
{
}

SimpleStage::SimpleStage(const SimpleStage &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SimpleStage::~SimpleStage(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

ActionBase::ResultE SimpleStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    RenderPartition   *pParentPart = a   ->getActivePartition();
    Window            *pWin        = a   ->getWindow         ();
    FrameBufferObject *pTarget     = this->getRenderTarget   ();
    Camera            *pCam        = this->getCamera         ();
    Background        *pBack       = this->getBackground     ();

    if(pTarget == NULL && this->getInheritedTarget() == true)
    {
        pTarget = pParentPart->getRenderTarget();
    }

    if(pCam == NULL)
    {
        SWARNING << "SimpleStage::renderEnter: No camera!" << std::endl;
    }

    this->pushPartition(a);
    
    RenderPartition   *pPart   = a->getActivePartition();
    
    setupPartition(pPart, pWin, pTarget, pCam, pBack);

    Inherited::addCallbacks(pPart);

    return ActionBase::Continue;
}

ActionBase::ResultE SimpleStage::renderLeave(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    this->popPartition(a);

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */


/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void SimpleStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SimpleStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&SimpleStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            SimpleStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&SimpleStage::renderLeave));
    }
}

void SimpleStage::setupPartition(
    RenderPartition *pPart, Window     *pWin, FrameBufferObject *pTarget,
    Camera          *pCam,  Background *pBack                            )
{
    pPart->setRenderTarget(pTarget);
    pPart->setWindow      (pWin   );

    if(pTarget != NULL)
    {
        pPart->calcViewportDimension(this->getLeft  (),
                                     this->getBottom(),
                                     this->getRight (),
                                     this->getTop   (),

                                     pTarget->getWidth    (),
                                     pTarget->getHeight   ());
    }
    else if(pWin != NULL)
    {
        pPart->calcViewportDimension(this->getLeft  (),
                                     this->getBottom(),
                                     this->getRight (),
                                     this->getTop   (),

                                     pWin->getWidth   (),
                                     pWin->getHeight  ());
    }
    else
    {
        SWARNING << "SimpleStage::setupPartition: No target or window."
                 << std::endl;
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

        pPart->getDrawEnv().setTileFullSize(pCam->tileGetFullSize());
        pPart->getDrawEnv().setTileRegion  (pCam->tileGetRegion  ());

        pPart->setupProjection(m, t);

        pCam->getViewing(m,
                         pPart->getViewportWidth (),
                         pPart->getViewportHeight());

        pPart->setupViewing(m              );

        pPart->setNear     (pCam->getNear());
        pPart->setFar      (pCam->getFar ());

        pPart->calcFrustum (               );
    }

    pPart->setBackground(pBack);
}

