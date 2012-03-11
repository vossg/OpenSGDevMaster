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

#include "OSGTestStage.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTestStageBase.cpp file.
// To modify it, please change the .fcd file (OSGTestStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TestStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            TestStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&TestStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            TestStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&TestStage::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TestStage::TestStage(void) :
    Inherited()
{
}

TestStage::TestStage(const TestStage &source) :
    Inherited(source)
{
}

TestStage::~TestStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TestStage::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TestStage::enterCB(DrawEnv *pEnv)
{
    fprintf(stderr, "TestStage Part Enter\n");
}

void TestStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TestStage NI" << std::endl;
}


Action::ResultE TestStage::renderEnter(Action *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter TestStage %p\n", &(*pCore)));
#endif

    RenderAction *a = dynamic_cast<RenderAction *>(action);

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "StartEnter TS %s\n",
                this->getMessage().c_str());
    }
#endif
    
    Stage::ValidationStatus eStatus = this->validateOnEnter(a);

    if(eStatus == TraversalValidator::Run)
    {
        this->pushPartition(a);
        {
#ifdef OSG_DEBUG
            RenderPartition *pPart  = a->getActivePartition();

            if(this != NULL && this->getMessage().size() != 0)
            {
                pPart->setDebugString(this->getMessage());
            }
#endif
        }
    }

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "FinishedEnter TS %s\n",
                this->getMessage().c_str());
    }
#endif

    return Action::Continue;
}

Action::ResultE TestStage::renderLeave(Action *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave TestStage %p\n", &(*pCore)));
#endif

    RenderAction *a = dynamic_cast<RenderAction *>(action);

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "StartLeave TS %s\n",
                this->getMessage().c_str());
    }
#endif

    TraversalValidator::ValidationStatus eStatus = this->validateOnLeave(a);

    if(eStatus == TraversalValidator::Run)
    {
        this->popPartition(a);
    }

#ifdef OSG_DEBUGX
    if(this != NULL && this->getMessage().size() != 0)
    {
        fprintf(stderr, "FinishedLeave TS %s\n",
                this->getMessage().c_str());
    }

    a->dumpPartitionList();
#endif

    return Action::Continue;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

OSG_END_NAMESPACE
