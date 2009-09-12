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

#include "OSGTestMultiPartitionStage.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTestMultiPartitionStageBase.cpp file.
// To modify it, please change the .fcd file (OSGTestMultiPartitionStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TestMultiPartitionStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            TestMultiPartitionStage::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &TestMultiPartitionStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            TestMultiPartitionStage::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &TestMultiPartitionStage::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TestMultiPartitionStage::TestMultiPartitionStage(void) :
    Inherited()
{
}

TestMultiPartitionStage::TestMultiPartitionStage(
    const TestMultiPartitionStage &source) :

    Inherited(source)
{
}

TestMultiPartitionStage::~TestMultiPartitionStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TestMultiPartitionStage::changed(ConstFieldMaskArg whichField, 
                                      UInt32            origin,
                                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TestMultiPartitionStage::dump(      UInt32    ,
                                   const BitVector ) const
{
    SLOG << "Dump TestMultiPartitionStage NI" << std::endl;
}


ActionBase::ResultE TestMultiPartitionStage::renderEnter(Action *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter TestMultiPartStage %p\n", &(*pCore)));
#endif

    RenderAction *a = dynamic_cast<RenderAction *>(action);

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "StartEnter MPTS %s\n",
                this->getMessage().c_str());
    }
#endif

    StageValidator::ValidationStatus eStatus = this->validateOnEnter(a);

    if(eStatus == StageValidator::Run)
    {
        if(this->getUseGroup() == true)
        {
            this->beginPartitionGroup(a);
        }
        else
        {
            this->beginPartitions(a);
        }

        for(Int32 i = 0; i < this->getNumPartitions(); ++i)
        {
            this->pushPartition(a);
            {
#ifdef OSG_DEBUG
                RenderPartition *pPart  = a->getActivePartition();
            
                if(this != NULL && this->getMessage().size() != 0)
                {
                    char szNum[16];
                    
                    std::string szMessage = this->getMessage();
                    
                    sprintf(szNum, "%d", i);
                    
                    szMessage += " | Partition ";
                    szMessage += szNum;
                    
                    pPart->setDebugString(szMessage);
                }
#endif

                this->recurseFromThis(a);
            }
            this->popPartition(a);
        }
        
        if(this->getUseGroup() == true)
        {
            this->endPartitionGroup(a);
        }
        else
        {
            this->endPartitions(a);
        }
    }

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "FinishedEnter MPTS %s\n",
                this->getMessage().c_str());
    }
#endif

    return ActionBase::Continue;
}

ActionBase::ResultE TestMultiPartitionStage::renderLeave(Action *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave TestMultiPartStage %p\n", &(*pCore)));
#endif

    RenderAction      *a      = 
        dynamic_cast<RenderAction *>(action);

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "StartLeave MPTS %s\n",
                this->getMessage().c_str());
    }
#endif

    /*StageValidator::ValidationStatus eStatus = */ this->validateOnLeave(a);

#ifdef OSG_DEBUGX
    a->dumpPartitionList();
#endif
    
    return ActionBase::Continue;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

OSG_END_NAMESPACE
