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
#include "OSGAlgorithm.h"

#include "OSGAlgorithmStage.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"

#include "OSGMatrixUtility.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGAlgorithmStageBase.cpp file.
// To modify it, please change the .fcd file (OSGAlgorithmStage.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void AlgorithmStage::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void AlgorithmStage::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AlgorithmStage::AlgorithmStage(void) :
    Inherited()
{
}

AlgorithmStage::AlgorithmStage(const AlgorithmStage &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

AlgorithmStage::~AlgorithmStage(void)
{
}

void AlgorithmStage::execute(DrawEnv *pDrawEnv)
{
    Algorithm *pAlgorithm = getAlgorithm();

    if(pAlgorithm != NULL)
    {
        pAlgorithm->execute(pDrawEnv);
    }
}


/*-------------------------------------------------------------------------*/
/*                               loading                                   */

ActionBase::ResultE AlgorithmStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);


    UInt32 uiCopyOnPush = RenderPartition::CopyVPCamera;

    if(this->getCopyViewing() == true)
    {
        uiCopyOnPush |= RenderPartition::CopyViewing;
    }

    this->pushPartition(a,
                        uiCopyOnPush, 
                        RenderPartition::SimpleCallback);
    {
        RenderPartition *pPart  = a->getActivePartition();

        pPart->setWindow(a->getWindow());

        if(this->getProjectionMode() != AlgorithmStage::Ignore)
        {
            Viewarea *pArea = a->getViewarea();
            
            if(pArea != NULL)
            {
                pPart->calcViewportDimension(pArea->getLeft  (),
                                             pArea->getBottom(),
                                             pArea->getRight (),
                                             pArea->getTop   (),
                                             
                                             a->getWindow()->getWidth (),
                                             a->getWindow()->getHeight());
                
                Matrix m, t;
                
                m.setIdentity();
                t.setIdentity();
                
                switch(this->getProjectionMode())
                {
                    case AlgorithmStage::ZeroOne:
                        MatrixOrthogonal( m,
                                          0.f, 1.f,
                                          0.f, 1.f,
                                         -1.f, 1.f);
            
                        break;

                    case AlgorithmStage::CenterOne:
                        MatrixOrthogonal( m,
                                         -1.f, 1.f,
                                         -1.f, 1.f,
                                         -1.f, 1.f);
            
                        break;

                    case AlgorithmStage::ZeroSize:
                        MatrixOrthogonal( m,
                                          0.f, pPart->getViewportWidth(),
                                          0.f, pPart->getViewportHeight(),
                                         -1.f, 1.f);
            
                        break;

                    case AlgorithmStage::CenterSize:
                    {
                        Real32 rWHalf = 
                            Real32(pPart->getViewportWidth()) / 2.f;
                        Real32 rHHalf = 
                            Real32(pPart->getViewportWidth()) / 2.f;

                        MatrixOrthogonal( m,
                                         -rWHalf, rWHalf,
                                         -rHHalf, rHHalf,
                                         -1.f, 1.f);
                    }
                    break;

                    case AlgorithmStage::StoredMatrix:
                        
                        m = this->getProjectionMatrix();
            
                        break;
                }

                pPart->setSetupMode(RenderPartition::FullSetup);
                pPart->setupProjection(m, t);
            }
            else
            {
                pPart->setSetupMode(RenderPartition::EmptySetup);
            }
        }
        else
        {
            pPart->setSetupMode(RenderPartition::EmptySetup);
        }
         
        RenderPartition::SimpleDrawCallback f;
        
        f = boost::bind(&AlgorithmStage::execute, this, _1);
        
        pPart->dropFunctor(f);

        Algorithm *pAlgorithm = getAlgorithm();
        
        if(pAlgorithm != NULL)
        {
            pAlgorithm->renderEnter(a);
        }
    }
    this->popPartition(a);

    return Action::Skip;
}

ActionBase::ResultE AlgorithmStage::renderLeave(Action *a)
{
    Algorithm *pAlgorithm = getAlgorithm();
    
    if(pAlgorithm != NULL)
    {
        pAlgorithm->renderLeave(a);
    }
    
    return Action::Skip;
}


/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void AlgorithmStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            AlgorithmStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&AlgorithmStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            AlgorithmStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&AlgorithmStage::renderLeave));
    }
}

