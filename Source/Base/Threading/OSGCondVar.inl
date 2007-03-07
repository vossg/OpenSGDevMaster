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

/*------------------------------- CondVar ---------------------------------*/

inline
void PThreadCondVarBase::acquire(void)
{
    pthread_mutex_lock(&(_pLowLevelLock));
}

inline
void PThreadCondVarBase::release(void)
{
    pthread_mutex_unlock(&(_pLowLevelLock));
}

inline
bool PThreadCondVarBase::request(void)
{
    return (pthread_mutex_trylock(&(_pLowLevelLock)) != EBUSY);
}

inline
void PThreadCondVarBase::signal()
{
    const int result = pthread_cond_signal(&(_pLowLevelCondVar));
    //assert(result == 0);
    //boost::ignore_unused_variable_warning(result);
}

inline
void PThreadCondVarBase::broadcast()
{
    const int result = pthread_cond_broadcast(&(_pLowLevelCondVar));
    //assert(result == 0);
    //boost::ignore_unused_variable_warning(result);
}

#endif /* OSG_USE_PTHREADS */


#if defined (OSG_USE_SPROC)

/*------------------------------- CondVar ---------------------------------*/

inline
void SprocCondVarBase::acquire(void)
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
void SprocCondVarBase::release(void)
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
bool SprocCondVarBase::request(void)
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

/*------------------------------- CondVar ---------------------------------*/

inline
void WinThreadCondVarBase::acquire(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "CondVar::acquire %p\n", this);
#endif

#ifdef OSG_WINLOCK_USE_MUTEX
    WaitForSingleObject(_pMutex, INFINITE);
#else
    EnterCriticalSection(&_pCriticalSection);
#endif
}

inline
void WinThreadCondVarBase::release(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "CondVar::release %p\n", this);
#endif

#ifdef OSG_WINLOCK_USE_MUTEX
    ReleaseMutex(_pMutex);
#else
    LeaveCriticalSection(&_pCriticalSection);
#endif
}

inline
bool WinThreadCondVarBase::request(void)
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
CondVar *CondVar::create(void)
{
    return CondVar::get(NULL);
}

inline
const MPCondVarType &CondVar::getClassType(void)
{
    return _type;
}

/*------------------------------- CondVar ---------------------------------*/

inline
void CondVar::acquire(void)
{
    Inherited::acquire();
}

inline
void CondVar::release(void)
{
    Inherited::release();
}

inline
bool CondVar::request(void)
{
    return Inherited::request();
}

inline
bool CondVar::wait(const float seconds)
{
    return Inherited::wait(seconds);
}

inline
void CondVar::signal(void)
{
    return Inherited::signal();
}

inline
void CondVar::broadcast(void)
{
    return Inherited::broadcast();
}

/*------------------------------ CondVar ----------------------------------*/

#if defined(OSG_WIN32_ICL) || defined(OSG_LINUX_ICC)
#pragma warning (error : 171)
#endif

OSG_END_NAMESPACE

#define OSGCONDVAR_INLINE_CVSID "@(#)$Id$"

