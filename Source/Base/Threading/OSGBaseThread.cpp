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

#include <iostream>

#include "OSGBaseThread.h"
#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

#if ! defined (OSG_USE_PTHREADS) && ! defined (OSG_USE_WINTHREADS)
#define _SGI_MP_SOURCE
#include <sys/types.h>
#include <sys/prctl.h>
#include <cerrno>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#endif

#if defined (OSG_USE_PTHREADS)
#include <signal.h>
#endif

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------



/*--------------------------- Constructors --------------------------------*/

BaseThreadCommonBase::BaseThreadCommonBase(const Char8  *szName,
                                                 UInt32  uiId, 
                                                 bool    bGlobal) :

     Inherited   (szName, bGlobal),
    _uiThreadId  (uiId           ),
    _bInitialized(false          )
{
}

/*---------------------------- Destructor ---------------------------------*/

BaseThreadCommonBase::~BaseThreadCommonBase(void)
{
}



#if defined (OSG_USE_PTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined(OSG_PTHREAD_ELF_TLS)
__thread BaseThread *BasePThreadBase::_pLocalThread = NULL;
#else
pthread_key_t BasePThreadBase::_threadKey;
#endif


BaseThread *BasePThreadBase::getCurrent(void)
{
#ifdef OSG_PTHREAD_ELF_TLS
# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(_pLocalThread == NULL)
    {
        BaseThreadRefPtr pThread = dynamic_pointer_cast<BaseThread>(
            ThreadManager::the()->getThread(NULL, true, "OSGThread"));

        pThread->doAutoInit();
    }
# endif
    return _pLocalThread;
#else
    BaseThread **pThread;

    pThread = static_cast<BaseThread **>(pthread_getspecific(_threadKey));

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pThread == NULL)
    {
        BaseThreadRefPtr pT = dynamic_pointer_cast<BaseThread>(
            ThreadManager::the()->getThread(NULL, true, "OSGThread"));

        pT->doAutoInit();

        pThread = static_cast<BaseThread **>(pthread_getspecific(_threadKey));
    }
#endif

    return *pThread;
#endif
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void *BasePThreadBase::threadFunc(void *pThreadArg)
{
    void **pArgs = static_cast<void **>(pThreadArg);

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            static_cast<BaseThread *>(pArgs[2])->init();

            if(pArgs[0] != NULL)
            {
                ThreadFuncF fThreadFunc = ThreadFuncF(pArgs[0]);

                fThreadFunc(pArgs[1]);
            }

            static_cast<BaseThread *>(pArgs[2])->shutdown();
        }
    }

    return NULL;
}

#if !defined(OSG_PTHREAD_ELF_TLS)
void BasePThreadBase::freeThread(void *pThread)
{
    BaseThread **pT = static_cast<BaseThread **>(pThread);

    if(pT != NULL)
    {
        if(*pT != NULL)
            OSG::subRef(*pT);

        delete pT;
    }

    pthread_setspecific(_threadKey, NULL);
}
#endif

/*--------------------------- Constructors --------------------------------*/

BasePThreadBase::BasePThreadBase(const Char8  *szName,
                                       UInt32  uiId, 
                                       bool    bGlobal) :
    Inherited  (szName, uiId, bGlobal),

    _pThreadDesc(NULL),
    _pBlockCond (NULL),
    _pBlockMutex(NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BasePThreadBase::~BasePThreadBase(void)
{
    delete _pThreadDesc;

    _pThreadDesc = NULL;
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

void BasePThreadBase::setupThread(void)
{
#ifdef OSG_PTHREAD_ELF_TLS
    _pLocalThread = static_cast<BaseThread *>(this);
#else
    BaseThread **pThread = new BaseThread *;

    *pThread = static_cast<BaseThread *>(this);

    pthread_setspecific(_threadKey, static_cast<void *>(pThread));
#endif
}

void BasePThreadBase::setupBlockCond(void)
{
    _pBlockCond  = new pthread_cond_t;
    _pBlockMutex = new pthread_mutex_t;

    pthread_cond_init (_pBlockCond, NULL);
    pthread_mutex_init(_pBlockMutex, NULL);
}

void BasePThreadBase::doAutoInit(void)
{
}

void BasePThreadBase::init(void)
{
    if(_bInitialized == true)
        return;

    setupThread    ();
    setupBlockCond ();

    _bInitialized = true;
}

void BasePThreadBase::shutdown(void)
{
    if(_bInitialized == false)
        return;

    pthread_cond_destroy (_pBlockCond);
    pthread_mutex_destroy(_pBlockMutex);

    delete _pBlockCond;
    delete _pBlockMutex;

#if !defined(OSG_PTHREAD_ELF_TLS)
    BaseThread **pThread;

    pThread = static_cast<BaseThread **>(pthread_getspecific(_threadKey));

    delete pThread;

    pthread_setspecific(_threadKey, NULL);
#else
    _pLocalThread = NULL;
#endif

    // TODO release key value, block cond

    _bInitialized = false;
}

/*------------------------------ Join -------------------------------------*/

void BasePThreadBase::join(BasePThreadBase *pThread)
{
    if(pThread != NULL && pThread->_pThreadDesc != NULL)
    {
        pthread_join(*(pThread->_pThreadDesc), NULL);

        delete pThread->_pThreadDesc;

        pThread->_pThreadDesc = NULL;
    }
}

/*------------------------------- Run -------------------------------------*/

// This workaround was brought to you by gcc 2.95.3

bool BasePThreadBase::runFunction(ThreadFuncF  fThreadFunc,
                                  void        *pThreadArg)
{
    bool  returnValue = true;
    Int32 rc          = 0;

    _bInitialized     = false;

    if(fThreadFunc != NULL)
    {
       if(_pThreadDesc == NULL)
            _pThreadDesc = new pthread_t;

        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &rc);

#if __GNUC__ < 4
        _pThreadData[0] = (void *)(fThreadFunc);
#else
        _pThreadData[0] = reinterpret_cast<void *>(fThreadFunc);
#endif
        _pThreadData[1] =                          pThreadArg;
        _pThreadData[2] = static_cast     <void *>(this       );
       	
        rc = pthread_create(_pThreadDesc,
                            NULL,
                            BasePThreadBase::threadFunc,
                            static_cast<void *>(&_pThreadData));

        if(rc != 0)
        {
            SFATAL << "OSGPTB : pthread_create failed" << std::endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "OSGPTB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

/*------------------------------ Dump -------------------------------------*/

void BasePThreadBase::print(void)
{
    fprintf(stderr, "OSGPThreadBase -%s-%d-\n", _szName, _uiThreadId);
}

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*------------------------------ Helper -----------------------------------*/

void BaseSprocBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            ((BaseThread *) pArgs[2])->init();

            ((BaseThread *) pArgs[2])->setPid();

            if(pArgs[0] != NULL)
            {
                ThreadFuncF threadFuncF = (ThreadFuncF) pArgs[0];

                threadFuncF(pArgs[1]);
            }
        }
    }
}

/*--------------------------- Constructors --------------------------------*/

BaseSprocBase::BaseSprocBase(const Char8  *szName,
                                   UInt32  uiId  ) :
    Inherited(szName, uiId),

    _pid     (NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/*---------------------------- Destructor ---------------------------------*/

BaseSprocBase::~BaseSprocBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

void BaseSprocBase::init(void)
{
    if(_bInitialized == true)
        return;

    setCurrentInternal((BaseThread *) this);

    _bInitialized = true;
}

void BaseSprocBase::shutdown(void)
{
    _bInitialized = false;
}

void BaseSprocBase::setPid(void)
{
    _pid = getpid();
}

void BaseSprocBase::setCurrentInternal(BaseThread *pThread)
{
    ((ProcessData *) PRDA->usr_prda.fill)->_pThread  = pThread;
}


/*------------------------------ Join -------------------------------------*/

void BaseSprocBase::join(BaseSprocBase *pThread)
{
    if(pThread != NULL)
        waitpid(pThread->_pid, NULL, 0);
}

/*------------------------------- Run -------------------------------------*/

// This workaround was brought to you by gcc 2.95.3

bool BaseSprocBase::runFunction(ThreadFuncF  fThreadFunc,
                                void        *pThreadArg)
{
    bool  returnValue = true;
    Int32 rc          = 0;

    _bInitialized     = false;

    if(fThreadFunc != NULL)
    {
        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        rc = sproc(BaseSprocBase::threadFunc, PR_SALL, (void *) _pThreadData);

        if(rc == -1)
        {
            SFATAL << "OSGSPB : sproc thread failed. Reason: " 
                   << strerror(errno) << std::endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "OSGSPB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

/*------------------------------- Dump ------------------------------------*/

void BaseSprocBase::print(void)
{
    fprintf(stderr, "OSGSprocBase -%s-%d-\n", _szName, _uiThreadId);
}

#endif /* OSG_USE_SPROC */




#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
UInt32 BaseWinThreadBase::_threadKey = 0;
#else
__declspec (thread) BaseThread *BaseWinThreadBase::_pThreadLocal     = NULL;
#endif

/*------------------------------ Helper -----------------------------------*/

void BaseWinThreadBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            ((BaseThread *) pArgs[2])->init();

            ((BaseWinThreadBase *) pArgs[2])->setPid();

            if(pArgs[0] != NULL)
            {
                ThreadFuncF threadFuncF = (ThreadFuncF) pArgs[0];
                
                threadFuncF(pArgs[1]);
            }

            static_cast<BaseThread *>(pArgs[2])->shutdown();
        }
    }
}

/*--------------------------- Constructors --------------------------------*/

BaseWinThreadBase::BaseWinThreadBase(const Char8  *szName,
                                           UInt32  uiId, 
                                           bool    bGlobal) :
     Inherited       (szName, uiId, bGlobal),

    _pThreadHandle   (NULL),
    _pExternalHandle (NULL),
    _uiNativeThreadId(0   )
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/*---------------------------- Destructor ---------------------------------*/

BaseWinThreadBase::~BaseWinThreadBase(void)
{
}

BaseThread *BaseWinThreadBase::getCurrent(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BaseThread **pThread;

    pThread = static_cast<BaseThread **>(TlsGetValue(_threadKey));

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pThread == NULL)
    {
        BaseWinThreadBase *pT = dynamic_cast<BaseThread *>(
            ThreadManager::the()->getThread(NULL, "OSGThread"));

        pT->doAutoInit();

        pThread = (BaseThread **) TlsGetValue(_threadKey);
    }
#endif

    return *pThread;
#else
# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(_pThreadLocal == NULL)
    {
        BaseWinThreadBase *pThread = dynamic_cast<BaseThread *>(
            ThreadManager::the()->getThread(NULL, "OSGThread"));

        pThread->doAutoInit();
    }
# endif

    return _pThreadLocal;
#endif
}


BaseThread *BaseWinThreadBase::getCurrentInternal(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BaseThread **pThread;

    pThread = static_cast<BaseThread **>(TlsGetValue(_threadKey));

    return (pThread != NULL) ? *pThread : NULL;
#else
    return _pThreadLocal;
#endif
}

/*--------------------------- Construction --------------------------------*/

void BaseWinThreadBase::init(void)
{
    if(_bInitialized == true)
        return;

    setupThread();

    _bInitialized = true;
}

void BaseWinThreadBase::shutdown(void)
{
    if(_bInitialized == false)
        return;

    // TODO delet key value

#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BaseThread **pThread = static_cast<BaseThread **>(TlsGetValue(_threadKey));

    delete pThread;

    TlsSetValue(_threadKey, NULL);
#else
    _pThreadLocal = NULL;
#endif
    
    _bInitialized = false;
}

void BaseWinThreadBase::setPid(void)
{
    _pThreadHandle    = GetCurrentThread  ();
    _uiNativeThreadId = GetCurrentThreadId();
}

void BaseWinThreadBase::setExternalHandle(Handle pExternalHandle)
{
    _pExternalHandle = pExternalHandle;
}


void BaseWinThreadBase::setupThread(void)
{
#if defined (OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    BaseThread **pThread = new BaseThread *;

    *pThread = (BaseThread *) this;

    TlsSetValue(_threadKey, pThread);
#else
    _pThreadLocal = (BaseThread *) this;
#endif
}

void BaseWinThreadBase::doAutoInit(void)
{
}

/*------------------------------ Join -------------------------------------*/

void BaseWinThreadBase::join(BaseWinThreadBase *pThread)
{
    if(pThread != NULL)
        WaitForSingleObject(pThread->_pExternalHandle, INFINITE);
}

/*------------------------------- Run -------------------------------------*/

// This workaround was brought to you by gcc 2.95.3

bool BaseWinThreadBase::runFunction(ThreadFuncF  fThreadFunc,
                                    void        *pThreadArg)
{
    bool   returnValue = true;
    Handle rc          = 0;
    DWord  tmp;

    _bInitialized      = false;

    if(fThreadFunc != NULL)
    {
        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        rc = CreateThread(NULL,
                          0,
                          (LPTHREAD_START_ROUTINE) BaseThreadBase::threadFunc,
                          _pThreadData,
                          0,
                          &tmp);

        this->setExternalHandle(rc);

        if(rc == NULL)
        {
            SFATAL << "OSGWTB : sproc thread failed. Reason: "  
                   << strerror(errno) << std::endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "OSGWTB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

/*------------------------------- Dump ------------------------------------*/

void BaseWinThreadBase::print(void)
{
    fprintf(stderr, "OSGWinThreadBase -%s-%u-\n", _szName, _uiThreadId);
}

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPThreadType BaseThread::_type("OSGBaseThread",
                               "OSGMPBase",
                               &BaseThread::create,
                               BaseThread::initThreading);


/*------------------------------- Dump ------------------------------------*/

void BaseThread::print(void)
{
    Inherited::print();
}

/*------------------------------- Get -------------------------------------*/

BaseThread::ObjTransitPtr BaseThread::get(const Char8 *szName, bool   bGlobal)
{
    return ThreadManager::the()->getThread(szName, bGlobal, "OSGBaseThread");
}

BaseThread *BaseThread::find(const Char8 *szName)
{
    return ThreadManager::the()->findThread(szName);
}

/*------------------------------ Helper -----------------------------------*/

BaseThread *BaseThread::create(const Char8 *szName, UInt32 uiId, bool bGlobal)
{
    return new BaseThread(szName, uiId, bGlobal);
}

void BaseThread::initThreading(void)
{
    FINFO(("BaseThread::initThreading\n"))

#if defined(OSG_USE_PTHREADS) && !defined(OSG_PTHREAD_ELF_TLS)
    int rc;

    rc = pthread_key_create(&(BaseThread::_threadKey), 
                              BaseThread::freeThread);

    FFASSERT((rc == 0), 1, ("Failed to create pthread thread key\n");)
#endif

#if defined(OSG_USE_WINTHREADS) && defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    BaseThread::_threadKey     = TlsAlloc();

    FFASSERT((BaseThread::_threadKey != 0xFFFFFFFF), 1,
             ("Failed to alloc thread key local storage\n");)
#endif
}

void BaseThread::terminateThreading(void)
{
    FINFO(("BaseThread::terminateThreading\n"));

#if defined(OSG_USE_PTHREADS) && !defined(OSG_PTHREAD_ELF_TLS)
    int rc;

    rc = pthread_key_delete(BaseThread::_threadKey);

    FFASSERT((rc == 0), 1, ("Failed to destroy pthread thread key\n"););
#endif

#if defined(OSG_USE_WINTHREADS) && defined (OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    if(BaseThread::_threadKey != 0xFFFFFFFF)
    {
        TlsFree(BaseThread::_threadKey);

        BaseThread::_threadKey = 0xFFFFFFFF;
    }
#endif
}

void BaseThread::runWorkProc(void  *pThread)
{
    if(pThread != NULL)
    {
        static_cast<BaseThread *>(pThread)->workProc();
    }
}

/*--------------------------- Constructors --------------------------------*/

BaseThread::BaseThread(const Char8 *szName, UInt32 uiId, bool bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*---------------------------- Destructor ---------------------------------*/

BaseThread::~BaseThread(void)
{
    shutdown();

    _bGlobal = false;

    ThreadManager::the()->remove(this);

    if(this != ThreadManager::getAppThread())
        terminate();
}

/*------------------------------- Workproc --------------------------------*/

void BaseThread::workProc(void)
{
}
