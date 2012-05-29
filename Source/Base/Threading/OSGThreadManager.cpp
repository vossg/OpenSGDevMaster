/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#if defined(OSG_USE_SPROC)
#include <cerrno>
#endif

#include <iostream>

#include "OSGThreadManager.h"
#include "OSGBaseInitFunctions.h"

#include "OSGThread.h"
#include "OSGAspectPool.h"

OSG_USING_NAMESPACE

ThreadManager    *ThreadManager::_pThreadManager      = NULL;
BaseThreadRefPtr  ThreadManager::_pAppThread          = NULL;

bool              ThreadManager::_bShutdownInProgress = false;

Char8            *ThreadManager::_szAppThreadType     = NULL;


/*-------------------------- Get / Set ------------------------------------*/

void ThreadManager::setAppThreadType(const Char8 *szAppThreadType)
{
    osgStringDup(szAppThreadType, _szAppThreadType);
}


ThreadManager *ThreadManager::the(void)
{
    if(_pThreadManager == NULL)
        _pThreadManager = new ThreadManager();

    return _pThreadManager;
}


BaseThread *ThreadManager::getAppThread(void)
{
    return _pAppThread;
}


/*-------------------- Create Threading Elements --------------------------*/

BaseThreadTransitPtr ThreadManager::getThread(const Char8 *szName,
                                                    UInt32 bGlobal,
                                              const Char8 *szTypeName)
{
    BaseThreadTransitPtr returnValue(NULL);

    _storePLock->acquire();

    returnValue = _sThreadStore.getMPField(szName, szTypeName, bGlobal != 0);

    _storePLock->release();

    return returnValue;
}

BarrierTransitPtr ThreadManager::getBarrier(const Char8 *szName,
                                                  UInt32 bGlobal,
                                            const Char8 *szTypeName)
{
    BarrierTransitPtr returnValue(NULL);

    _storePLock->acquire();

    returnValue = _sBarrierStore.getMPField(szName, szTypeName, bGlobal != 0);

    _storePLock->release();

    return returnValue;
}

CondVarTransitPtr ThreadManager::getCondVar(const Char8 *szName,
                                                  UInt32 bGlobal,
                                            const Char8 *szTypeName)
{
    CondVarTransitPtr returnValue(NULL);

    _storePLock->acquire();

    returnValue = _sCondVarStore.getMPField(szName, szTypeName, bGlobal != 0);

    _storePLock->release();

    return returnValue;
}

LockTransitPtr ThreadManager::getLock(const Char8 *szName,
                                            UInt32 bGlobal,
                                      const Char8 *szTypeName)
{
    LockTransitPtr returnValue(NULL);

    _storePLock->acquire();

    returnValue = _sLockStore.getMPField(szName, szTypeName, bGlobal != 0);

    _storePLock->release();

    return returnValue;
}

LockPoolTransitPtr ThreadManager::getLockPool(const Char8 *szName,
                                                    UInt32 bGlobal,
                                              const Char8 *szTypeName)
{
    LockPoolTransitPtr returnValue(NULL);

    _storePLock->acquire();

    returnValue = _sLockPoolStore.getMPField(szName, szTypeName, bGlobal != 0);

    _storePLock->release();

    return returnValue;
}

SemaphoreTransitPtr ThreadManager::getSemaphore(const Char8 *szName,
                                                      UInt32 bGlobal,
                                                const Char8 *szTypeName)
{
    SemaphoreTransitPtr returnValue(NULL);

    _storePLock->acquire();

    returnValue = _sSemaphoreStore.getMPField(szName, szTypeName, bGlobal != 0);

    _storePLock->release();

    return returnValue;
}

BaseThread  *ThreadManager::findThread(const Char8 *szName)
{
    BaseThread *returnValue = NULL;

    _storePLock->acquire();
    
    returnValue = _sThreadStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

Barrier *ThreadManager::findBarrier(const Char8 *szName)
{
    Barrier *returnValue = NULL;

    _storePLock->acquire();
    
    returnValue = _sBarrierStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

CondVar *ThreadManager::findCondVar(const Char8 *szName)
{
    CondVar *returnValue = NULL;

    _storePLock->acquire();
    
    returnValue = _sCondVarStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

Lock *ThreadManager::findLock(const Char8 *szName)
{
    Lock *returnValue = NULL;

    _storePLock->acquire();
    
    returnValue = _sLockStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

LockPool *ThreadManager::findLockPool(const Char8 *szName)
{
    LockPool *returnValue = NULL;

    _storePLock->acquire();
    
    returnValue = _sLockPoolStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

Semaphore *ThreadManager::findSemaphore(const Char8 *szName)
{
    Semaphore *returnValue = NULL;

    _storePLock->acquire();
    
    returnValue = _sSemaphoreStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

void ThreadManager::dump(void)
{
    ThreadStore::MPFieldMapCIt tI = _sThreadStore._mFieldMap.begin();
    ThreadStore::MPFieldMapCIt tE = _sThreadStore._mFieldMap.end  ();

    for(; tI != tE; ++tI)
    {
        FLOG(("ThreadManager::dump: "
               "thread [%s|%p] is still alive ([%d]). \n", 
               (*tI).first.c_str(),
               (*tI).second,
               (*tI).second->exists()));
    }

    BarrierStore::MPFieldMapCIt bI = _sBarrierStore._mFieldMap.begin();
    BarrierStore::MPFieldMapCIt bE = _sBarrierStore._mFieldMap.end  ();

    for(; bI != bE; ++bI)
    {
        FINFO(("ThreadManager::dump: "
               "barrier [%s|%p] is still alive\n", 
               (*bI).first.c_str(),
               (*bI).second));

    }

    CondVarStore::MPFieldMapCIt cI = _sCondVarStore._mFieldMap.begin();
    CondVarStore::MPFieldMapCIt cE = _sCondVarStore._mFieldMap.end  ();

    for(; cI != cE; ++cI)
    {
        FLOG(("ThreadManager::dump: "
              "condvar [%s|%p] is still alive\n", 
              (*cI).first.c_str(),
              (*cI).second));

    }

    LockStore::MPFieldMapCIt lI = _sLockStore._mFieldMap.begin();
    LockStore::MPFieldMapCIt lE = _sLockStore._mFieldMap.end  ();

    for(; lI != lE; ++lI)
    {
        FLOG(("ThreadManager::dump: "
              "lock [%s|%p] is still alive\n", 
              (*lI).first.c_str(),
              (*lI).second));
    }

    LockPoolStore::MPFieldMapCIt lpI = _sLockPoolStore._mFieldMap.begin();
    LockPoolStore::MPFieldMapCIt lpE = _sLockPoolStore._mFieldMap.end  ();

    for(; lpI != lpE; ++lpI)
    {
        FLOG(("ThreadManager::dump: "
              "lockpool [%s|%p] is still alive\n", 
              (*lpI).first.c_str(),
              (*lpI).second));

    }

    SemaphoreStore::MPFieldMapCIt sI = _sSemaphoreStore._mFieldMap.begin();
    SemaphoreStore::MPFieldMapCIt sE = _sSemaphoreStore._mFieldMap.end  ();

    for(; sI != sE; ++sI)
    {
        FLOG(("ThreadManager::dump: "
              "semaphore [%s|%p] is still alive\n", 
              (*sI).first.c_str(),
              (*sI).second));
    }

    FLOG(
        ("Sizes: ThreadStore: %"PRISize" BarrierStore: %"PRISize
         " CondVarStore: %"PRISize" LockStore: %"PRISize" LockPoolStore: %"
         PRISize" SemaphoreStore: %"PRISize"\n",
         _sThreadStore   ._mFieldMap.size(),
         _sBarrierStore  ._mFieldMap.size(),
         _sCondVarStore  ._mFieldMap.size(),
         _sLockStore     ._mFieldMap.size(),
         _sLockPoolStore ._mFieldMap.size(),
         _sSemaphoreStore._mFieldMap.size()));
}

/*------------------------------- Get -------------------------------------*/

#if defined(OSG_USE_SPROC)
usptr_t *ThreadManager::getArena(void)
{
    return _pArena;
}
#endif

/*------------------------------ Helper -----------------------------------*/

bool ThreadManager::initialize(void)
{
    return the()->init();
}

bool ThreadManager::terminate (void)
{
    bool returnValue = the()->shutdown();

    delete _pThreadManager;

    _pThreadManager = NULL;

    return returnValue;
}

void ThreadManager::remove(BaseThread *pThread)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->acquire();

    _sThreadStore.removeMPField(pThread);
    
    _storePLock->release();
}

void ThreadManager::remove(Barrier *pBarrier)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->acquire();

    _sBarrierStore.removeMPField(pBarrier);
    
    _storePLock->release();
}

void ThreadManager::remove(CondVar *pCondVar)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->acquire();

    _sCondVarStore.removeMPField(pCondVar);
    
    _storePLock->release();
}

void ThreadManager::remove(Lock *pLock)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->acquire();

    _sLockStore.removeMPField(pLock);

    _storePLock->release();
}

void ThreadManager::remove(LockPool *pLockPool)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->acquire();

    _sLockPoolStore.removeMPField(pLockPool);
    
    _storePLock->release();
}

void ThreadManager::remove(Semaphore *pSemaphore)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->acquire();

    _sSemaphoreStore.removeMPField(pSemaphore);
    
    _storePLock->release();
}

UInt32 ThreadManager::registerThreadType(MPThreadType *pType)
{
    return _sThreadStore.registerMPType(pType);
}

UInt32 ThreadManager::registerBarrierType(MPBarrierType *pType)
{
    return _sBarrierStore.registerMPType(pType);
}

UInt32 ThreadManager::registerCondVarType(MPCondVarType *pType)
{
    return _sCondVarStore.registerMPType(pType);
}

UInt32 ThreadManager::registerLockType(MPLockType *pType)
{
    return _sLockStore.registerMPType(pType);
}

UInt32 ThreadManager::registerLockPoolType(MPLockPoolType *pType)
{
    return _sLockPoolStore.registerMPType(pType);
}

UInt32 ThreadManager::registerSemaphoreType(MPSemaphoreType *pType)
{
    return _sSemaphoreStore.registerMPType(pType);
}

#ifdef __sgi
#pragma set woff 1209
#endif

bool ThreadManager::init(void)
{
    bool returnValue = true;

    FDEBUG(("OSGThreadManager init\n"))

#if defined(OSG_USE_SPROC)
    usconfig(CONF_AUTOGROW,   1);
    usconfig(CONF_INITUSERS, 20);
    usconfig(CONF_INITSIZE, 10 * 1048576);
    usconfig(CONF_CHMOD, 0666);

    _pArena = usinit("/dev/zero");

    if(_pArena == NULL)
    {
        SFATAL << "OSGTM : could not initialize arena " << errno << std::endl;
        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got arena " << _pArena << std::endl;
    }
#endif

    _storePLock = _sLockStore.getMPField("OSGTMStoreLock", "OSGLock", true);
    
    if(_storePLock == NULL)
    {
        SFATAL << "OSGTM : could not get table lock" << std::endl;

        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got table lock " << _storePLock << std::endl;
    }

    if(_szAppThreadType == NULL)
    {
        FINFO(("OSGTM : create -OSGBaseThread- app thread\n"));

        _pAppThread = getThread("OSGAppThread", true, "OSGBaseThread");
    }
    else
    {
        FINFO(("OSGTM : create -%s- app thread\n", _szAppThreadType));

        _pAppThread = getThread("OSGAppThread", true, _szAppThreadType);
    }

    FFASSERT((_pAppThread != NULL), 1, 
             ("OSGTM : could not get application thread \n"););
             

    FINFO(("OSGTM : got application thread %p\n", _pAppThread.get()));

    AspectPool::the()->get("AppThreadAspect");

    _pAppThread->init();

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

bool ThreadManager::shutdown(void)
{
    FDEBUG(("OSGThreadManager shutdown\n"))

    _bShutdownInProgress = true;

    _pAppThread->shutdown();

    _pAppThread = NULL;

#ifdef OSG_DEBUG

    ThreadStore::MPFieldMapCIt tI = _sThreadStore._mFieldMap.begin();
    ThreadStore::MPFieldMapCIt tE = _sThreadStore._mFieldMap.end  ();

    for(; tI != tE; ++tI)
    {
        if(tI->first != "OSGAppThread")
        {
            FWARNING(("ThreadManager::shutdown: "
                      "thread [%s|%p] is still alive ([%d]). \n", 
                      (*tI).first.c_str(),
                      (*tI).second,
                      (*tI).second->exists()));
        }
    }

    BarrierStore::MPFieldMapCIt bI = _sBarrierStore._mFieldMap.begin();
    BarrierStore::MPFieldMapCIt bE = _sBarrierStore._mFieldMap.end  ();

    for(; bI != bE; ++bI)
    {
        FWARNING(("ThreadManager::shutdown: "
                  "barrier [%s|%p] is still alive\n", 
                  (*bI).first.c_str(),
                  (*bI).second));

    }

    CondVarStore::MPFieldMapCIt cI = _sCondVarStore._mFieldMap.begin();
    CondVarStore::MPFieldMapCIt cE = _sCondVarStore._mFieldMap.end  ();

    for(; cI != cE; ++cI)
    {
        FWARNING(("ThreadManager::shutdown: "
                  "condvar [%s|%p] is still alive\n", 
                  (*cI).first.c_str(),
                  (*cI).second));

    }

    LockStore::MPFieldMapCIt lI = _sLockStore._mFieldMap.begin();
    LockStore::MPFieldMapCIt lE = _sLockStore._mFieldMap.end  ();

    for(; lI != lE; ++lI)
    {
        if(lI->first != "OSGTMStoreLock"    &&
           lI->first != "OSG::Log::_pLogLock"  )
        {
            FWARNING(("ThreadManager::shutdown: "
                      "lock [%s|%p] is still alive\n", 
                      (*lI).first.c_str(),
                      (*lI).second));
        }
    }

    LockPoolStore::MPFieldMapCIt lpI = _sLockPoolStore._mFieldMap.begin();
    LockPoolStore::MPFieldMapCIt lpE = _sLockPoolStore._mFieldMap.end  ();

    for(; lpI != lpE; ++lpI)
    {
        FWARNING(("ThreadManager::shutdown: "
                  "lockpool [%s|%p] is still alive\n", 
                  (*lpI).first.c_str(),
                  (*lpI).second));

    }

    SemaphoreStore::MPFieldMapCIt sI = _sSemaphoreStore._mFieldMap.begin();
    SemaphoreStore::MPFieldMapCIt sE = _sSemaphoreStore._mFieldMap.end  ();

    for(; sI != sE; ++sI)
    {
        FWARNING(("ThreadManager::shutdown: "
                  "semaphore [%s|%p] is still alive\n", 
                  (*sI).first.c_str(),
                  (*sI).second));
    }

#endif

    FDEBUG(
        ("Sizes: ThreadStore: %"PRISize" BarrierStore: %"PRISize
         " CondVarStore: %"PRISize" LockStore: %"PRISize" LockPoolStore: %"
         PRISize" SemaphoreStore: %"PRISize"\n",
         _sThreadStore   ._mFieldMap.size(),
         _sBarrierStore  ._mFieldMap.size(),
         _sCondVarStore  ._mFieldMap.size(),
         _sLockStore     ._mFieldMap.size(),
         _sLockPoolStore ._mFieldMap.size(),
         _sSemaphoreStore._mFieldMap.size()));
          
    _sThreadStore   .clear();
    _sBarrierStore  .clear();
    _sCondVarStore  .clear();
    _sLockStore     .clear();
    _sLockPoolStore .clear();
    _sSemaphoreStore.clear();

    Thread::terminateThreading();

#if defined(OSG_USE_SPROC)
    if(_pArena != NULL)
        usdetach(_pArena);
#endif

    return true;
}

/*--------------------------- Constructors --------------------------------*/

ThreadManager::ThreadManager(void) :
    _sThreadStore   (    ),
    _sBarrierStore  (    ),
    _sCondVarStore  (    ),
    _sLockStore     (    ),
    _sLockPoolStore (    ),
    _sSemaphoreStore(    ),

    _storePLock     (NULL)
{
#if defined(OSG_USE_SPROC)
    _pArena = NULL;
#endif
}

/*---------------------------- Destructo ----------------------------------*/

ThreadManager::~ThreadManager(void)
{
    delete [] _szAppThreadType;
}

