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

#include <iostream>
#include "OSGLock.h"
#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

LockCommonBase::LockCommonBase(void) :
     Inherited(NULL, true),
    _uiLockId (0   )
{
}

LockCommonBase::LockCommonBase(const Char8  *szName,
                                     UInt32  uiId, 
                                     bool    bGlobal):
     Inherited(szName, bGlobal),
    _uiLockId (uiId  )
{
}

/*---------------------------- Destructor ---------------------------------*/

LockCommonBase::~LockCommonBase(void)
{
}



#if defined (OSG_USE_PTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

PThreadLockBase::PThreadLockBase(void):
     Inherited    (),
    _pLowLevelLock()
{
}

PThreadLockBase::PThreadLockBase(const Char8  *szName,
                                       UInt32  uiId, 
                                       bool    bGlobal) :
    Inherited    (szName, uiId, bGlobal),
    _pLowLevelLock()
{
}

/*---------------------------- Destructor ---------------------------------*/

PThreadLockBase::~PThreadLockBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool PThreadLockBase::init(void)
{
    pthread_mutexattr_t lockAttr;
    
    pthread_mutexattr_init(&lockAttr);
    
    pthread_mutexattr_settype(&lockAttr, PTHREAD_MUTEX_RECURSIVE);
    
    pthread_mutex_init(&(_pLowLevelLock), &lockAttr);
    
    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void PThreadLockBase::shutdown(void)
{
    pthread_mutex_destroy(&(_pLowLevelLock));
}


#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

SprocLockBase::SprocLockBase(void):
     Inherited    (    ),
#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock(NULL)
#else
    _pLowLevelSema(NULL)
#endif
{
}

SprocLockBase::SprocLockBase(const Char8  *szName,
                                   UInt32  uiId  ):
     Inherited    (szName, uiId),
    _pLowLevelLock(NULL        )
#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock(NULL        )
#else
    _pLowLevelSema(NULL        )
#endif
{
}

/*---------------------------- Destructor ---------------------------------*/

SprocLockBase::~SprocLockBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool SprocLockBase::init(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return false;

    if(pThreadManager->getArena() == NULL)
        return false;

#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock = usnewlock(pThreadManager->getArena());

    if(_pLowLevelLock == NULL)
        return false;

    usinitlock(_pLowLevelLock);

#else
    _pLowLevelSema = usnewsema(pThreadManager->getArena(), 1);

    if(_pLowLevelSema == NULL)
        return false;

    usinitsema(_pLowLevelSema, 1);
    usctlsema (_pLowLevelSema, CS_RECURSIVEON, NULL);
#endif

    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void SprocLockBase::shutdown(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return;

    if(pThreadManager->getArena() == NULL)
        return;

#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
    {
        usfreelock(_pLowLevelLock, pThreadManager->getArena());
    
        _pLowLevelLock = NULL;
    }
#else
    if(_pLowLevelSema != NULL)
    {
        usfreesema(_pLowLevelSema, pThreadManager->getArena());

        _pLowLevelSema = NULL;
    }
#endif
}

/*------------------------------- Lock ------------------------------------*/

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

WinThreadLockBase::WinThreadLockBase(void) :
       Inherited(    )
#ifdef OSG_WINLOCK_USE_MUTEX
    , _pMutex   (NULL)
#endif
{
}

WinThreadLockBase::WinThreadLockBase(const Char8  *szName,
                                           UInt32  uiId, 
                                           bool    bGlobal) :
    Inherited(szName, uiId, bGlobal)
#ifdef OSG_WINLOCK_USE_MUTEX
    , _pMutex   (NULL        )
#endif
{
}

/*---------------------------- Destructor ---------------------------------*/

WinThreadLockBase::~WinThreadLockBase(void)
{
}

/*-------------------------- Construction ---------------------------------*/

bool WinThreadLockBase::init(void)
{
#ifdef OSG_WINLOCK_USE_MUTEX
    _pMutex = CreateMutex( NULL,     // no security attributes
                           FALSE,    // initially not owned
                          _szName);  // name of mutex

    if(_pMutex == NULL)
    {
        return false;
    }

    return true;
#else
    InitializeCriticalSection(&_pCriticalSection);

    return true;
#endif
}

/*-------------------------- Destruction ----------------------------------*/

void WinThreadLockBase::shutdown(void)
{
#ifdef OSG_WINLOCK_USE_MUTEX
    if(_pMutex != NULL)
    {
        CloseHandle(_pMutex);
        _pMutex = NULL;
    }
#else
    DeleteCriticalSection(&_pCriticalSection);
#endif
}

#endif /* OSG_USE_WINTHREADS */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPLockType Lock::_type("OSGLock", "OSGMPBase", &Lock::create);

/*------------------------------- Get -------------------------------------*/

Lock::ObjTransitPtr Lock::get(const Char8 *szName, bool bGlobal)
{
    return ThreadManager::the()->getLock(szName, bGlobal, "OSGLock");
}

Lock *Lock::find(const Char8 *szName)
{
    return ThreadManager::the()->findLock(szName);
}


/*------------------------------ Create -----------------------------------*/

Lock *Lock::create(const Char8 *szName, UInt32 uiId, bool bGlobal)
{
    Lock *returnValue = NULL;

    returnValue = new Lock(szName, uiId, bGlobal);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }

    return returnValue;
}

/*--------------------------- Constructors --------------------------------*/

Lock::Lock(void) :
    Inherited()
{
}

Lock::Lock(const Char8 *szName, UInt32 uiId, bool bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*---------------------------- Destructor ---------------------------------*/

Lock::~Lock(void)
{
    _bGlobal = false;

    ThreadManager::the()->remove(this);

    shutdown();
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPLockPoolType LockPool::_type("OSGLockPool", "OSGMPBase", &LockPool::create);

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

LockPool::ObjTransitPtr LockPool::get(const Char8 *szName, bool bGlobal)
{
    return ThreadManager::the()->getLockPool(szName, 
                                             bGlobal,
                                             "OSGLockPool");
}

LockPool *LockPool::find(const Char8 *szName)
{
    return ThreadManager::the()->findLockPool(szName);
}

/*------------------------------ Create -----------------------------------*/

LockPool *LockPool::create(const Char8 *szName, 
                                 UInt32 uiId, 
                                 bool   bGlobal)
{
    LockPool *returnValue = NULL;

    returnValue = new LockPool(szName, uiId, bGlobal);

    if(returnValue->init() == false)
    {
        returnValue = NULL;
    }

    return returnValue;
}

/*--------------------------- Constructors --------------------------------*/

LockPool::LockPool(const Char8  *szName,
                         UInt32  uiId, 
                         bool    bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*---------------------------- Destructor ---------------------------------*/

LockPool::~LockPool(void)
{
    _bGlobal = false;

    ThreadManager::the()->remove(this);

    shutdown();
}

/*--------------------------- Construction --------------------------------*/

bool LockPool::init(void)
{
    bool   returnValue = true;
    Char8 *pTmp;

    pTmp = new Char8[strlen(_szName) + 6];

    for(UInt32 i = 0; i < uiLockPoolSize; i++)
    {
#ifdef OSG_DEBUG_LOCK_STAT
        _pLockStats[i] = 0;
#endif
        sprintf(pTmp, "%s%u\n", _szName, i);

        osgStringDup(pTmp, _pLocks[i]._szName);

        returnValue &= _pLocks[i].init();
    }

    delete [] pTmp;

    return returnValue;
}

/*--------------------------- Destruction ---------------------------------*/

void LockPool::shutdown(void)
{
}

