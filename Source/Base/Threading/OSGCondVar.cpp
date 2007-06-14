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

// If we are on windows and not WinCE, then target Windows NT 4.0
#if defined (WIN32) && !defined(_WIN32_WINNT) && !defined(_WIN32_WCE)
#define _WIN32_WINNT 0x0400
#endif

#include "OSGConfig.h"

#include <iostream>

#include "OSGCondVar.h"

#include "OSGBaseFunctions.h"

#include "OSGThreadManager.h"

#include <OSGLog.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

CondVarCommonBase::CondVarCommonBase(void) :
     Inherited(NULL),
    _uiCondVarId (0   )
{
}

CondVarCommonBase::CondVarCommonBase(const Char8  *szName,
                                           UInt32  uiId  ):
     Inherited(szName),
    _uiCondVarId (uiId  )
{
}

/*---------------------------- Destructor ---------------------------------*/

CondVarCommonBase::~CondVarCommonBase(void)
{
}



#if defined (OSG_USE_PTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

PThreadCondVarBase::PThreadCondVarBase(void):
     Inherited    (),
    _pLowLevelCondVar()
{
}

PThreadCondVarBase::PThreadCondVarBase(const Char8  *szName,
                                             UInt32  uiId  ) :
     Inherited    (szName, uiId),
    _pLowLevelLock(),
    _pLowLevelCondVar()
{
}

/*---------------------------- Destructor ---------------------------------*/

PThreadCondVarBase::~PThreadCondVarBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool PThreadCondVarBase::init(void)
{
    pthread_mutexattr_t lockAttr;
    
    pthread_mutexattr_init(&lockAttr);
    
    pthread_mutexattr_settype(&lockAttr, PTHREAD_MUTEX_RECURSIVE);
    
    pthread_mutex_init(&(_pLowLevelLock), &lockAttr);

    // Initialize the condition variable.
    pthread_cond_init(&(_pLowLevelCondVar), NULL);

    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void PThreadCondVarBase::shutdown(void)
{
    pthread_mutex_destroy(&(_pLowLevelLock));
    pthread_cond_destroy(&(_pLowLevelCondVar));
}

bool PThreadCondVarBase::wait(const Int32 timeToWait)
{
    bool result(true);

    // Wait indefinitely on the condition variable.
    if(timeToWait < 0)
    {
         const int retcode = pthread_cond_wait(&(_pLowLevelCondVar), &(_pLowLevelLock));

         // If pthread_cond_wait(3) returned non-zero status, then we throw
         // an exception. Otherwise, we return true.
         if(retcode != 0)
         {
             return false;
         }
    }
    // Wait for no longer than the given timeout period to acquire the lock
    // on the condition variable.
    else
    {
        struct timeval  now;                // The current time
        struct timespec abs_timeout;        // The absolute time of the timeout

        const UInt64 UsecsPerSec(1000000);

        // Calculate the absolute time for wait timeout
        gettimeofday(&now, NULL);

        UInt64 abs_secs = now.tv_sec +
            static_cast<long> (timeToWait / 1000);
        UInt64 abs_usecs = now.tv_usec +
            static_cast<long>((timeToWait % 1000) * 1000);

        if(abs_usecs > UsecsPerSec)    // Have extra seconds
        {
            abs_secs += abs_usecs / UsecsPerSec;    // Get the number of seconds
            abs_usecs = abs_usecs % UsecsPerSec;
        }

        abs_timeout.tv_sec = abs_secs;
        abs_timeout.tv_nsec = 1000 * (abs_usecs);
        OSG_ASSERT(abs_timeout.tv_nsec < Int64(UsecsPerSec * 1000) &&
                   "Nano seconds out of range (greater then one second).");

        const int retcode = pthread_cond_timedwait(&(_pLowLevelCondVar),
                                                   &(_pLowLevelLock),
                                                   &abs_timeout);

        // Successful completion: return true.
        if( 0 == retcode )
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }

    return result;
}


#endif /* OSG_USE_PTHREADS */


#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

SprocCondVarBase::SprocCondVarBase(void):
     Inherited    (    ),
#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock(NULL)
#else
    _pLowLevelSema(NULL)
#endif
{
}

SprocCondVarBase::SprocCondVarBase(const Char8  *szName,
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

SprocCondVarBase::~SprocCondVarBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool SprocCondVarBase::init(void)
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

void SprocCondVarBase::shutdown(void)
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

/*------------------------------- CondVar ---------------------------------*/

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x0400

int pthread_cond_init(pthread_cond_t *cv, void *dummy)
{
    cv->waiters_count_ = 0;
    cv->was_broadcast_ = 0;
    cv->sema_ = CreateSemaphore(NULL,       // no security
                                 0,          // initially 0
                                 0x7fffffff, // max count
                                 NULL);      // unnamed 
    InitializeCriticalSection(&cv->waiters_count_lock_);
    cv->waiters_done_ = CreateEvent (NULL,  // no security
                                     FALSE, // auto-reset
                                     FALSE, // non-signaled initially
                                     NULL); // unnamed
    return 0;
}

int pthread_cond_wait(pthread_cond_t *cv, 
                      pthread_mutex_t *external_mutex)
{
    // Avoid race conditions.
    EnterCriticalSection(&cv->waiters_count_lock_);
    cv->waiters_count_++;
    LeaveCriticalSection(&cv->waiters_count_lock_);

    // This call atomically releases the mutex and waits on the
    // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
    // are called by another thread.
    ::SignalObjectAndWait(*external_mutex, cv->sema_, INFINITE, FALSE);

    // Reacquire lock to avoid race conditions.
    EnterCriticalSection(&cv->waiters_count_lock_);

    // We're no longer waiting...
    cv->waiters_count_--;

    // Check to see if we're the last waiter after <pthread_cond_broadcast>.
    int last_waiter = cv->was_broadcast_ && cv->waiters_count_ == 0;

    LeaveCriticalSection(&cv->waiters_count_lock_);

    // If we're the last waiter thread during this particular broadcast
    // then let all the other threads proceed.
    if(last_waiter)
    {
        // This call atomically signals the <waiters_done_> event and waits until
        // it can acquire the <external_mutex>.  This is required to ensure fairness. 
        ::SignalObjectAndWait(cv->waiters_done_, *external_mutex, INFINITE, FALSE);
    }
    else
    {
        // Always regain the external mutex since that's the guarantee we
        // give to our callers. 
        //WaitForSingleObject (*external_mutex);
        WaitForSingleObject(cv->waiters_done_, INFINITE);
    }

    return 0;
}

int pthread_cond_signal(pthread_cond_t *cv)
{
    EnterCriticalSection(&cv->waiters_count_lock_);
    int have_waiters = cv->waiters_count_ > 0;
    LeaveCriticalSection(&cv->waiters_count_lock_);

    // If there aren't any waiters, then this is a no-op.  
    if(have_waiters)
    {
        ReleaseSemaphore(cv->sema_, 1, 0);
    }
    return 0;
}

int pthread_cond_broadcast (pthread_cond_t *cv)
{
    // This is needed to ensure that <waiters_count_> and <was_broadcast_> are
    // consistent relative to each other.
    EnterCriticalSection(&cv->waiters_count_lock_);
    int have_waiters = 0;

    if(cv->waiters_count_ > 0)
    {
        // We are broadcasting, even if there is just one waiter...
        // Record that we are broadcasting, which helps optimize
        // <pthread_cond_wait> for the non-broadcast case.
        cv->was_broadcast_ = 1;
        have_waiters = 1;
    }

    if(have_waiters)
    {
        // Wake up all the waiters atomically.
        ReleaseSemaphore(cv->sema_, cv->waiters_count_, 0);

        LeaveCriticalSection(&cv->waiters_count_lock_);

        // Wait for all the awakened threads to acquire the counting
        // semaphore. 
        WaitForSingleObject(cv->waiters_done_, INFINITE);
        // This assignment is okay, even without the <waiters_count_lock_> held 
        // because no other waiter threads can wake up to access it.
        cv->was_broadcast_ = 0;
    }
    else
    {
        LeaveCriticalSection(&cv->waiters_count_lock_);
    }

  return 0;
}

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

WinThreadCondVarBase::WinThreadCondVarBase(void) :
       Inherited(    )
    , _pMutex   (NULL)
{
}

WinThreadCondVarBase::WinThreadCondVarBase(const Char8  *szName,
                                           UInt32  uiId  ) :
       Inherited(szName, uiId)
    , _pMutex   (NULL        )
{
}

/*---------------------------- Destructor ---------------------------------*/

WinThreadCondVarBase::~WinThreadCondVarBase(void)
{
}

/*-------------------------- Construction ---------------------------------*/

bool WinThreadCondVarBase::init(void)
{
#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x0400
    _pMutex = CreateMutex(NULL,     // no security attributes
                          FALSE,    // initially not owned
                          _szName);  // name of mutex

    if(_pMutex == NULL)
    {
        return false;
    }

    waiters_count_ = 0;
    was_broadcast_ = 0;
    sema_ = CreateSemaphore(NULL,       // no security
                            0,          // initially 0
                            0x7fffffff, // max count
                            NULL);      // unnamed 
    InitializeCriticalSection(&waiters_count_lock_);
    waiters_done_ = CreateEvent(NULL,  // no security
                                FALSE, // auto-reset
                                FALSE, // non-signaled initially
                                NULL); // unnamed
    return true;
#else
    OSG_ASSERT(false && "CondVar::init() Not implemented for versions of Windows < 4.0");
    return false;
#endif
}

bool WinThreadCondVarBase::wait(const Int32 timeToWait)
{
#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x0400
    // Avoid race conditions.
    EnterCriticalSection (&waiters_count_lock_);
    waiters_count_++;
    LeaveCriticalSection (&waiters_count_lock_);

    // This call atomically releases the mutex and waits on the
    // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
    // are called by another thread.
    SignalObjectAndWait(_pMutex, sema_, INFINITE, FALSE);

    // Reacquire lock to avoid race conditions.
    EnterCriticalSection(&waiters_count_lock_);

    // We're no longer waiting...
    waiters_count_--;

    // Check to see if we're the last waiter after <pthread_cond_broadcast>.
    int last_waiter = was_broadcast_ && waiters_count_ == 0;

    LeaveCriticalSection(&waiters_count_lock_);

    // XXX: Need to use timeToWait.

    // If we're the last waiter thread during this particular broadcast
    // then let all the other threads proceed.
    if(last_waiter)
    {
        // This call atomically signals the <waiters_done_> event and waits until
        // it can acquire the <external_mutex>.  This is required to ensure fairness. 
        SignalObjectAndWait(waiters_done_, _pMutex, INFINITE, FALSE);
    }
    else
    {
        // Always regain the external mutex since that's the guarantee we
        // give to our callers. 
        WaitForSingleObject(_pMutex, INFINITE);
    }
#else
    OSG_ASSERT(false && "CondVar::wait() Not implemented for versions of Windows < 4.0");
#endif
    return 0;
}

void WinThreadCondVarBase::signal()
{
#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x0400
    EnterCriticalSection(&waiters_count_lock_);
    int have_waiters = waiters_count_ > 0;
    LeaveCriticalSection(&waiters_count_lock_);

    // If there aren't any waiters, then this is a no-op.  
    if(have_waiters)
    {
        ReleaseSemaphore(sema_, 1, 0);
    }
#else
    OSG_ASSERT(false && "CondVar::signal() Not implemented for versions of Windows < 4.0");
#endif
}

void WinThreadCondVarBase::broadcast()
{
#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x0400
    // This is needed to ensure that <waiters_count_> and <was_broadcast_> are
    // consistent relative to each other.
    EnterCriticalSection(&waiters_count_lock_);
    int have_waiters = 0;

    if(waiters_count_ > 0)
    {
        // We are broadcasting, even if there is just one waiter...
        // Record that we are broadcasting, which helps optimize
        // <pthread_cond_wait> for the non-broadcast case.
        was_broadcast_ = 1;
        have_waiters = 1;
    }

    if(have_waiters)
    {
        // Wake up all the waiters atomically.
        ReleaseSemaphore(sema_, waiters_count_, 0);

        LeaveCriticalSection(&waiters_count_lock_);

        // Wait for all the awakened threads to acquire the counting
        // semaphore. 
        WaitForSingleObject(waiters_done_, INFINITE);
        // This assignment is okay, even without the <waiters_count_lock_> held 
        // because no other waiter threads can wake up to access it.
        was_broadcast_ = 0;
    }
    else
    {
        LeaveCriticalSection(&waiters_count_lock_);
    }
#else
    OSG_ASSERT(false && "CondVar::broadcast() Not implemented for versions of Windows < 4.0");
#endif
}

/*-------------------------- Destruction ----------------------------------*/

void WinThreadCondVarBase::shutdown(void)
{
#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x0400
    if(_pMutex != NULL)
    {
        CloseHandle(_pMutex);
    }
    if(sema_ != NULL)
    {
        CloseHandle(sema_);
    }
    DeleteCriticalSection(&waiters_count_lock_);
    if(waiters_done_ != NULL)
    {
        CloseHandle(waiters_done_);
    }
#else
    OSG_ASSERT(false && "CondVar::shutdown() Not implemented for versions of Windows < 4.0");
#endif
}

#endif /* OSG_USE_WINTHREADS */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPCondVarType CondVar::_type("OSGCondVar", "OSGMPBase", &CondVar::create);

/*------------------------------- Get -------------------------------------*/

CondVar *CondVar::get(const Char8 *szName)
{
    return ThreadManager::the()->getCondVar(szName, "OSGCondVar");
}

CondVar *CondVar::find(const Char8 *szName)
{
    return ThreadManager::the()->findCondVar(szName);
}


/*------------------------------ Create -----------------------------------*/

CondVar *CondVar::create(const Char8 *szName, UInt32 uiId)
{
    CondVar *returnValue = NULL;

    returnValue = new CondVar(szName, uiId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }

    return returnValue;
}

/*--------------------------- Constructors --------------------------------*/

CondVar::CondVar(void) :
    Inherited()
{
}

CondVar::CondVar(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
{
}

/*---------------------------- Destructor ---------------------------------*/

CondVar::~CondVar(void)
{
    ThreadManager::the()->removeCondVar(this);

    shutdown();
}
