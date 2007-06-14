/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

OSG_BEGIN_NAMESPACE

#if defined (OSG_USE_PTHREADS)

/*------------------------------- Lock ------------------------------------*/

inline
void PThreadLockBase::acquire(void)
{
    pthread_mutex_lock(&(_pLowLevelLock));
}

inline
void PThreadLockBase::release(void)
{
    pthread_mutex_unlock(&(_pLowLevelLock));
}

inline
bool PThreadLockBase::request(void)
{
    return (pthread_mutex_trylock(&(_pLowLevelLock)) != EBUSY);
}

#endif /* OSG_USE_PTHREADS */


#if defined (OSG_USE_SPROC)

/*------------------------------- Lock ------------------------------------*/

inline
void SprocLockBase::acquire(void)
{
#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
        ussetlock(_pLowLevelLock);
#else
    if(_pLowLevelSema != NULL)
        uspsema(_pLowLevelSema);
#endif
}

inline
void SprocLockBase::release(void)
{
#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
        usunsetlock(_pLowLevelLock);
#else
    if(_pLowLevelSema != NULL)
        usvsema(_pLowLevelSema);
#endif
}

inline
bool SprocLockBase::request(void)
{
    bool  returnValue = false;
    Int32 rc          = 0;

#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
        rc = uscsetlock(_pLowLevelLock, 0);
#else
    if(_pLowLevelSema != NULL)
        rc = uscpsema(_pLowLevelSema);
#endif

    returnValue = (rc == 1);

    return returnValue;
}

#endif /* OSG_USE_SPROC */


#if defined (OSG_USE_WINTHREADS)

/*------------------------------- Lock ------------------------------------*/

inline
void WinThreadLockBase::acquire(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "Lock::acquire %p\n", this);
#endif

#ifdef OSG_WINLOCK_USE_MUTEX
    WaitForSingleObject(_pMutex, INFINITE);
#else
    EnterCriticalSection(&_pCriticalSection);
#endif
}

inline
void WinThreadLockBase::release(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "Lock::release %p\n", this);
#endif

#ifdef OSG_WINLOCK_USE_MUTEX
    ReleaseMutex(_pMutex);
#else
    LeaveCriticalSection(&_pCriticalSection);
#endif
}

inline
bool WinThreadLockBase::request(void)
{
#ifdef OSG_WINLOCK_USE_MUTEX
    DWORD rc;
    rc = WaitForSingleObject(_pMutex, 0);

    if(rc == WAIT_OBJECT_0)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return (TryEnterCriticalSection(&_pCriticalSection) != FALSE);
#endif
}

#endif /* OSG_USE_WINTHREADS */




inline
Lock *Lock::create(void)
{
    return Lock::get(NULL);
}

inline
const MPLockType &Lock::getClassType(void)
{
    return _type;
}

/*------------------------------- Lock ------------------------------------*/

inline
void Lock::acquire(void)
{
    Inherited::acquire();
}

inline
void Lock::release(void)
{
    Inherited::release();
}

inline
bool Lock::request(void)
{
    return Inherited::request();
}

inline
LockPool *LockPool::create(void)
{
    return LockPool::get(NULL);
}

inline
const MPLockPoolType &LockPool::getClassType(void)
{
    return _type;
}

/*------------------------------ Lock -------------------------------------*/

#if defined(OSG_WIN32_ICL) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 171)
#endif

inline
void LockPool::acquire(void *keyP)
{
    _pLocks[(NumericalKeyType(keyP) & uiLockPoolMask) >> 7].acquire();
}

inline
void LockPool::release(void *keyP)
{
    _pLocks[(NumericalKeyType(keyP) & uiLockPoolMask) >> 7].release();
}

inline
bool LockPool::request(void *keyP)
{
    return _pLocks[(NumericalKeyType(keyP) & uiLockPoolMask) >> 7].request();
}

#if defined(OSG_WIN32_ICL) || defined(OSG_LINUX_ICC)
#pragma warning (error : 171)
#endif

OSG_END_NAMESPACE
