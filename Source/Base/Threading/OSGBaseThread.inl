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

inline
bool BaseThreadCommonBase::isInitialized(void)
{
    return _bInitialized;
}


#if defined (OSG_USE_PTHREADS)

/*---------------------------- Blocking -----------------------------------*/

inline
void BasePThreadBase::block(void)
{
    pthread_mutex_lock  (_pBlockMutex);
    pthread_cond_wait   (_pBlockCond, _pBlockMutex);
    pthread_mutex_unlock(_pBlockMutex);
}

inline
void BasePThreadBase::unblock(void)
{
    pthread_cond_broadcast(_pBlockCond);
}

/*------------------------------ Helper -----------------------------------*/

inline
bool BasePThreadBase::exists(void)
{
    return true;
}

inline
void BasePThreadBase::terminate(void)
{
    if(_pThreadDesc != NULL)
        pthread_cancel(*_pThreadDesc);
}

inline
void BasePThreadBase::kill(void)
{
    if(_pThreadDesc != NULL) 
        pthread_cancel(*_pThreadDesc);
}


#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

/*------------------------------- Get -------------------------------------*/

inline
BaseThread *BaseSprocBase::getCurrent(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->_pThread;
}

/*---------------------------- Blocking -----------------------------------*/

inline
void BaseSprocBase::block(void)
{
    blockproc(_pid);
}

inline
void BaseSprocBase::unblock(void)
{
    unblockproc(_pid);
}

/*------------------------------ Helper -----------------------------------*/

inline
bool BaseSprocBase::exists(void)
{
    bool returnValue = false;

    returnValue = (prctl(PR_ISBLOCKED, _pid) != -1);

    return returnValue;
}


inline
void BaseSprocBase::terminate(void)
{
    ::kill(_pid, SIGTERM);
}

inline
void BaseSprocBase::kill(void)
{
    ::kill(_pid, SIGKILL);
}

#endif /* OSG_USE_SPROC */




#if defined (OSG_USE_WINTHREADS)

/*----------------------------- Blocking ----------------------------------*/

inline
void BaseWinThreadBase::block(void)
{
    SuspendThread(_pThreadHandle);
}

inline
void BaseWinThreadBase::unblock(void)
{
    ResumeThread(_pExternalHandle);
}

/*----------------------------- Helper ------------------------------------*/

inline
bool BaseWinThreadBase::exists(void)
{
    bool  returnValue = false;
    DWORD rc          = 0;

    if(BaseWinThreadBase::getCurrentInternal() == this)
    {
        GetExitCodeThread( _pThreadHandle,
                          &rc            );
    }
    else
    {
        GetExitCodeThread( _pExternalHandle,
                          &rc              );
    }

    returnValue = (rc == STILL_ACTIVE);

    return returnValue;
}


inline
void BaseWinThreadBase::terminate(void)
{
    if(BaseWinThreadBase::getCurrentInternal() == this)
    {
        TerminateThread(_pThreadHandle,   0);
    }
    else
    {
        TerminateThread(_pExternalHandle, 0);
    }
}

inline
void BaseWinThreadBase::kill(void)
{
    if(BaseWinThreadBase::getCurrentInternal() == this)
    {
        TerminateThread(_pThreadHandle,   0);
    }
    else
    {
        TerminateThread(_pExternalHandle, 0);
    }
}

#endif /* OSG_USE_WINTHREADS */


inline
BaseThread::ObjTransitPtr BaseThread::create(void)
{
    return BaseThread::get(NULL, false);
}

inline
const MPThreadType &BaseThread::getClassType(void)
{
    return _type;
}

/*------------------------------- Get -------------------------------------*/

inline
BaseThread *BaseThread::getCurrent(void)
{
    return Inherited::getCurrent();
}

/*------------------------------ Join -------------------------------------*/

inline
void BaseThread::join(BaseThread *pThread)
{
    Inherited::join(pThread);
}

/*------------------------------- Run -------------------------------------*/


inline
void BaseThread::run(void)
{
    Inherited::runFunction(runWorkProc, this);
}

inline
bool BaseThread::runFunction(ThreadFuncF  fThreadFunc,
                             void        *pThreadArg)
{
    return Inherited::runFunction(fThreadFunc, pThreadArg);
}

/*----------------------------- Blocking ----------------------------------*/

inline
void BaseThread::block(void)
{
    Inherited::block();
}

inline
void BaseThread::unblock(void)
{
    Inherited::unblock();
}

/*----------------------------- Helper ------------------------------------*/

inline
bool BaseThread::exists(void)
{
    return Inherited::exists();
}

inline
void BaseThread::terminate(void)
{
    Inherited::terminate();
}

inline
void BaseThread::kill(void)
{
    Inherited::kill();
}

OSG_END_NAMESPACE

