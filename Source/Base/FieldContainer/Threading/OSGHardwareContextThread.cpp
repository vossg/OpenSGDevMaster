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

#include "OSGHardwareContextThread.h"
#include "OSGThreadManager.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType HardwareContextThread::_type(
    "OSGHardwareContextThread",
    "OSGThread",
    static_cast<CreateThreadF>(HardwareContextThread::create),
    NULL);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

HardwareContextThread *HardwareContextThread::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<HardwareContextThread *>(pThread);
}

HardwareContextThread::ObjTransitPtr HardwareContextThread::get(Char8 *szName,
                                                                bool   bGlobal) 
{
    BaseThreadTransitPtr pThread = 
        ThreadManager::the()->getThread(szName,
                                        bGlobal,
                                        "OSGHardwareContextThread");

    return dynamic_pointer_cast<HardwareContextThread>(pThread);
}



BaseThread *HardwareContextThread::create(const Char8  *szName, 
                                                UInt32  uiId,
                                                bool    bGlobal)
{
    return new HardwareContextThread(szName, uiId, bGlobal);
}

HardwareContextThread::HardwareContextThread(const Char8 *szName, 
                                                   UInt32 uiId,
                                                   bool   bGlobal) :
     Inherited (szName, 
                uiId  ,
                bGlobal),
    _bRunning  (false  ),
    _pEnv      (NULL   ),
    _qTaskQueue(       ),
    _pContext  (NULL   )
{
}

HardwareContextThread::~HardwareContextThread(void)
{
}

void HardwareContextThread::workProc(void)
{
    _bRunning = true;

    while(_bRunning == true)
    {
        HardwareContextTaskRefPtr pNextTask = _qTaskQueue.popTask();

        pNextTask->execute(_pContext, _pEnv);
    }
}

void HardwareContextThread::dumpTasks(void)
{
    _qTaskQueue.dumpQueue();
}

void HardwareContextThread::runTasks (void)
{
    _qTaskQueue.runAndClearQueue(_pContext, _pEnv);
}

void HardwareContextThread::setContext(HardwareContext *pContext)
{
    _pContext = pContext;
}

OSG_END_NAMESPACE
