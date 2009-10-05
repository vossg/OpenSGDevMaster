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

#include "OSGWindowDrawThread.h"
#include "OSGThreadManager.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType WindowDrawThread::_type(
    "OSGWindowDrawThread",
    "OSGThread",
    static_cast<CreateThreadF>(WindowDrawThread::create),
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

WindowDrawThread *WindowDrawThread::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<WindowDrawThread *>(pThread);
}

WindowDrawThread *WindowDrawThread::get(Char8 *szName) 
{
    BaseThread *pThread = 
        ThreadManager::the()->getThread(szName,
                                        "OSGWindowDrawThread");

    return dynamic_cast<WindowDrawThread *>(pThread);
}



BaseThread *WindowDrawThread::create(const Char8  *szName, 
                                           UInt32  uiId)
{
    return new WindowDrawThread(szName, uiId);
}

WindowDrawThread::WindowDrawThread(const Char8 *szName, UInt32 uiId) :
      Inherited (szName, 
                 uiId  ),
     _bRunning  (false ),
     _oEnv      (      ),
     _qTaskQueue(      )
{
}

WindowDrawThread::~WindowDrawThread(void)
{
}

void WindowDrawThread::workProc(void)
{
    _bRunning = true;

    while(_bRunning == true)
    {
        DrawTaskRefPtr pNextTask = _qTaskQueue.popTask();

        pNextTask->execute(&_oEnv);
    }
}

void WindowDrawThread::dumpTasks(void)
{
    _qTaskQueue.dumpQueue();
}

void WindowDrawThread::runTasks (void)
{
    _qTaskQueue.runAndClearQueue(&_oEnv);
}

OSG_END_NAMESPACE
