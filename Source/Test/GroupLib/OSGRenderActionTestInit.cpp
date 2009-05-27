/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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
#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGRenderAction.h"

#include "OSGMaterialDrawable.h"

#include "OSGTestStage.h"
#include "OSGTestMultiPartitionStage.h"


#define OSG_DUMP_TRAVERSAL

OSG_BEGIN_NAMESPACE


ActionBase::ResultE TestStageRenderEnter(NodeCore * const pCore,
                                         Action   *       action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter TestStage %p\n", &(*pCore)));
#endif

    RenderAction *a      = dynamic_cast<RenderAction *>(action);
    TestStage    *pStage = dynamic_cast<TestStage    *>(pCore);

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "StartEnter TS %s\n",
                pStage->getMessage().c_str());
    }
#endif
    
    Stage::ValidationStatus eStatus = pStage->validateOnEnter(a);

    if(eStatus == StageValidator::Run)
    {
        pStage->pushPartition(a);
        {
            RenderPartition *pPart  = a->getActivePartition();

#ifdef OSG_DEBUG
            if(pStage != NULL && pStage->getMessage().size() != 0)
            {
                pPart->setDebugString(pStage->getMessage());
            }
#endif
        }
    }

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "FinishedEnter TS %s\n",
                pStage->getMessage().c_str());
    }
#endif

    return ActionBase::Continue;
}

ActionBase::ResultE TestStageRenderLeave(NodeCore * const pCore,
                                         Action   *       action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave TestStage %p\n", &(*pCore)));
#endif

    RenderAction *a      = dynamic_cast<RenderAction *>(action);
    TestStage    *pStage = dynamic_cast<TestStage    *>(pCore);

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "StartLeave TS %s\n",
                pStage->getMessage().c_str());
    }
#endif

    StageValidator::ValidationStatus eStatus = pStage->validateOnLeave(a);

    if(eStatus == StageValidator::Run)
    {
        pStage->popPartition(a);
    }

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "FinishedLeave TS %s\n",
                pStage->getMessage().c_str());
    }

    a->dumpPartitionList();
#endif

    return ActionBase::Continue;
}


ActionBase::ResultE TestMultiPartStageRenderEnter(NodeCore * const pCore,
                                                  Action   *       action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter TestMultiPartStage %p\n", &(*pCore)));
#endif

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    TestMultiPartitionStage *pStage = 
        dynamic_cast<TestMultiPartitionStage *>(pCore);

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "StartEnter MPTS %s\n",
                pStage->getMessage().c_str());
    }
#endif

    StageValidator::ValidationStatus eStatus = pStage->validateOnEnter(a);

    if(eStatus == StageValidator::Run)
    {
        if(pStage->getUseGroup() == true)
        {
            pStage->beginPartitionGroup(a);
        }
        else
        {
            pStage->beginPartitions(a);
        }

        for(UInt32 i = 0; i < pStage->getNumPartitions(); ++i)
        {
            pStage->pushPartition(a);
            {
                RenderPartition *pPart  = a->getActivePartition();
            
#ifdef OSG_DEBUG
                if(pStage != NULL && pStage->getMessage().size() != 0)
                {
                    char szNum[16];
                    
                    std::string szMessage = pStage->getMessage();
                    
                    sprintf(szNum, "%d", i);
                    
                    szMessage += " | Partition ";
                    szMessage += szNum;
                    
                    pPart->setDebugString(szMessage);
                }
#endif

#warning  "TestMultiPartStageRenderEnter recurse call DISABLED!!!"
//                recurseFromThis(a);
            }
            pStage->popPartition(a);
        }
        
        if(pStage->getUseGroup() == true)
        {
            pStage->endPartitionGroup(a);
        }
        else
        {
            pStage->endPartitions(a);
        }
    }

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "FinishedEnter MPTS %s\n",
                pStage->getMessage().c_str());
    }
#endif

    return ActionBase::Continue;
}

ActionBase::ResultE TestMultiPartStageRenderLeave(NodeCore * const pCore,
                                                  Action   *       action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave TestMultiPartStage %p\n", &(*pCore)));
#endif

    RenderAction      *a      = 
        dynamic_cast<RenderAction *>(action);

    TestMultiPartitionStage *pStage = 
        dynamic_cast<TestMultiPartitionStage *>(pCore);

#ifdef OSG_DEBUGX
    if(pStage != NULL && pStage->getMessage().size() != 0)
    {
        fprintf(stderr, "StartLeave MPTS %s\n",
                pStage->getMessage().c_str());
    }
#endif

    StageValidator::ValidationStatus eStatus = pStage->validateOnLeave(a);

#ifdef OSG_DEBUGX
    a->dumpPartitionList();
#endif
    
    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                   init                                  */

bool RenderActionGroupTestInitialize(void)
{
    RenderAction::registerEnterDefault(
        TestStage::getClassType(), 
              TestStageRenderEnter);

    RenderAction::registerLeaveDefault( 
        TestStage::getClassType(), 
              TestStageRenderLeave);

    RenderAction::registerEnterDefault(
        TestMultiPartitionStage::getClassType(), 
              TestMultiPartStageRenderEnter);

    RenderAction::registerLeaveDefault( 
        TestMultiPartitionStage::getClassType(), 
              TestMultiPartStageRenderLeave);

    return true;
}

struct RenderActionGroupTestInit
{
    RenderActionGroupTestInit(void) 
    { 
        addPostFactoryInitFunction(RenderActionGroupTestInitialize); 
    }
};

static RenderActionGroupTestInit initGroupTestDummy;

OSG_END_NAMESPACE





/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */
