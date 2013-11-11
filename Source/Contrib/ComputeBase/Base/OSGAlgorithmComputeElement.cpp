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

#include "OSGAlgorithmComputeElement.h"
#include "OSGAlgorithmComputeElementData.h"

#include "OSGComputeAlgorithm.h"

#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"

#include "OSGMatrixUtility.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGAlgorithmComputeElementBase.cpp file.
// To modify it, please change the .fcd file (OSGAlgorithmComputeElement.fcd)
// and regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void AlgorithmComputeElement::changed(ConstFieldMaskArg whichField, 
                                      UInt32            origin,
                                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void 
    AlgorithmComputeElement::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump AlgorithmComputeElement NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AlgorithmComputeElement::AlgorithmComputeElement(void) :
    Inherited()
{
}

AlgorithmComputeElement::AlgorithmComputeElement(
    const AlgorithmComputeElement &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

AlgorithmComputeElement::~AlgorithmComputeElement(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */

Action::ResultE AlgorithmComputeElement::renderEnter(Action *action)
{
    RenderAction     *a     = dynamic_cast<RenderAction *>(action);
    ComputeAlgorithm *pAlgo = this->getAlgorithm();

    if(pAlgo != NULL)
    {
        AlgorithmComputeElementData *pData    = 
            a->getData<AlgorithmComputeElementData *>(_iDataSlotId);

        if(pData == NULL)
        {
            AlgorithmComputeElementDataUnrecPtr pDataNew = 
                AlgorithmComputeElementData::create();
        
            this->setData(pDataNew.get(), _iDataSlotId, a);
            
            pData = pDataNew;
        }

        ComputeAlgorithmDrawTask *pTask = pData->getTask();

        if(pTask == NULL)
        {
            pTask = new ComputeAlgorithmDrawTask(
                pAlgo,
                ComputeAlgorithmDrawTask::Algorithm);

            pData->setTask(pTask);
        }


        a->getWindow()->queueTaskFromDrawer(pTask);
    }

    return Action::Continue;
}

Action::ResultE AlgorithmComputeElement::renderLeave(Action *a)
{
    return Action::Continue;
}


/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void AlgorithmComputeElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            AlgorithmComputeElement::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &AlgorithmComputeElement::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            AlgorithmComputeElement::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &AlgorithmComputeElement::renderLeave));
    }
}

OSG_END_NAMESPACE
