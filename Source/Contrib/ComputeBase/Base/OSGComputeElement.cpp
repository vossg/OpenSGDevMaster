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

#if 0
#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"
#endif

#include "OSGComputeElement.h"

#if 0
#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"
#endif

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGComputeElementBase.cpp file.
// To modify it, please change the .fcd file (OSGComputeElement.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void ComputeElement::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void ComputeElement::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ComputeElement::ComputeElement(void) :
    Inherited()
{
}

ComputeElement::ComputeElement(const ComputeElement &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ComputeElement::~ComputeElement(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

ActionBase::ResultE ComputeElement::renderEnter(Action *action)
{
#if 0
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    RenderPartition   *pParentPart = a->getActivePartition();
    FrameBufferObject *pTarget     = this->getRenderTarget();

    if(pTarget == NULL && this->getInheritedTarget() == true)
    {
        pTarget = pParentPart->getRenderTarget();
    }

    a->pushPartition();

    RenderPartition   *pPart    = a->getActivePartition();
    Viewport          *pPort    = a->getViewport();
    Camera            *pCam     = a->getCamera  ();
    Background        *pBack    = a->getBackground();
    
    pPart->setRenderTarget(pTarget);

    if(pPort != NULL)
    {
//        pPart->setViewport(pPort         );
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
    }

    pPart->setBackground(pBack);
#endif

    return ActionBase::Continue;
}

ActionBase::ResultE ComputeElement::renderLeave(Action *action)
{
#if 0
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    a->popPartition();
#endif

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ComputeElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#if 0
        RenderAction::registerEnterDefault(
            Stage::getClassType(), 
            reinterpret_cast<Action::Callback>(&Stage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            Stage::getClassType(), 
            reinterpret_cast<Action::Callback>(&Stage::renderLeave));
#endif
    }
}
