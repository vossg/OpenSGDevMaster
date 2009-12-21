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

#include "OSGConfig.h"

#include "OSGHardwareContextTask.h"

#include "OSGMField.ins"

OSG_BEGIN_NAMESPACE

/*! \class OSG::HardwareContextTask
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

HardwareContextTask::HardwareContextTask(UInt32 uiTaskType) :
     Inherited (          ),
    _uiTypeTask(uiTaskType)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

HardwareContextTask::~HardwareContextTask(void)
{
}


//virtual void execute(DrawEnv *pEnv);



/*! \class OSG::HardwareContextTask
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

HardwareContextTaskQueue::HardwareContextTaskQueue(void) :
    _qTaskStore(    ),
    _pStoreLock(NULL),
    _pStoreSema(NULL)
{
    _pStoreLock = Lock     ::get(NULL, false);
    _pStoreSema = Semaphore::get(NULL, false);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

HardwareContextTaskQueue::~HardwareContextTaskQueue(void)
{
    _qTaskStore.clear();
    
    _pStoreLock = NULL;
    _pStoreSema = NULL;
}

void HardwareContextTaskQueue::queueTask(HardwareContextTask *pTask)
{
    if(pTask != NULL)
    {
        _pStoreLock->acquire();
        
        _qTaskStore.push_back(pTask);

        _pStoreLock->release();

        _pStoreSema->post();
    }

    
}

void HardwareContextTaskQueue::queueTaskFront(HardwareContextTask *pTask)
{
    if(pTask != NULL)
    {
        _pStoreLock->acquire();
        
        _qTaskStore.push_front(pTask);

        _pStoreLock->release();

        _pStoreSema->post();
    }

    
}

HardwareContextTaskTransitPtr HardwareContextTaskQueue::popTask(void)
{
    _pStoreSema->wait();

    _pStoreLock->acquire();

    OSG_ASSERT(_qTaskStore.size() != 0);

    HardwareContextTaskTransitPtr returnValue(_qTaskStore.front());

    _qTaskStore.pop_front();

    _pStoreLock->release();

    return returnValue;
}

void HardwareContextTaskQueue::dumpQueue(void)
{
    TaskStore::const_iterator qIt  = _qTaskStore.begin();
    TaskStore::const_iterator qEnd = _qTaskStore.end  ();

    fprintf(stderr, "Dumping task queue\n");
    fprintf(stderr, "------------------\n");

    for(; qIt != qEnd; ++qIt)
    {
        (*qIt)->dump(4);
    }
}

void HardwareContextTaskQueue::runAndClearQueue(HardwareContext *pContext, 
                                                DrawEnv         *pEnv    )
{
    TaskStore::const_iterator qIt  = _qTaskStore.begin();
    TaskStore::const_iterator qEnd = _qTaskStore.end  ();

    for(; qIt != qEnd; ++qIt)
    {
        (*qIt)->execute(pContext, pEnv);
    }

    _qTaskStore.clear();
}

DataType FieldTraits<HardwareContextTaskRefPtr>::_type(
    "HardwareContextTaskRefPtr", NULL);

OSG_FIELDTRAITS_GETTYPE(HardwareContextTaskRefPtr)

OSG_FIELD_DLLEXPORT_DEF1(MField, HardwareContextTaskRefPtr);


OSG_END_NAMESPACE


