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

#include "OSGInsertTestTask.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGInsertTestTaskBase.cpp file.
// To modify it, please change the .fcd file (OSGInsertTestTask.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void InsertTestTask::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InsertTestTask::InsertTestTask(void) :
    Inherited()
{
}

InsertTestTask::InsertTestTask(const InsertTestTask &source) :
    Inherited(source)
{
}

InsertTestTask::~InsertTestTask(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InsertTestTask::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    if(0x0000 != (whichField & TriggerFieldMask))
    {
        fprintf(stderr, "got trigger %p\n", _sfWindow.getValue());

        if(_sfWindow.getValue() != NULL)
        {
            TestDrawTaskRefPtr pTask = new TestDrawTask(TestDrawTask::TaskA);

            _sfWindow.getValue()->queueTask(pTask);
        }
    }

    Inherited::changed(whichField, origin, details);
}

void InsertTestTask::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump InsertTestTask NI" << std::endl;
}




TestDrawTask::TestDrawTask(TestTaskType eType) :
     Inherited(     ),
    _eTaskType(eType)
{
}

TestDrawTask::~TestDrawTask(void)
{
}

void TestDrawTask::execute(DrawEnv *pEnv)
{
    switch(_eTaskType)
    {
        case TaskA:
        {
            fprintf(stderr, "TaskA\n");
            fflush(stderr);

            int i;

            glGetIntegerv(GL_ACCUM_ALPHA_BITS, &i);
        }
        break;

        case TaskB:
        {
            fprintf(stderr, "TaskB\n");
            fflush(stderr);
        }
        break;

        default:
            break;
    }
}

void TestDrawTask::dump(UInt32 uiIndent)
{
    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "TestDrawTask : ");

    switch(_eTaskType)
    {
        case TaskA:
        {
            fprintf(stderr, "TaskA\n");
        }
        break;
        case TaskB:
        {
            fprintf(stderr, "TaskB\n");
        }
        break;

        default:
        {
            fprintf(stderr, "unknown test task\n");
        }
        break;
    }

}

OSG_END_NAMESPACE
