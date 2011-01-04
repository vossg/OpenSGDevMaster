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

#include "OSGThread.h"
#include "OSGBaseFunctions.h"
#include "OSGChangeList.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"
#include "OSGBaseInitFunctions.h"

#if ! defined (OSG_USE_PTHREADS) && ! defined (OSG_USE_WINTHREADS)
#include <sys/types.h>
#include <sys/prctl.h>
#include <cerrno>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#endif

OSG_BEGIN_NAMESPACE

const UInt32 ThreadCommonBase::InvalidAspect = 
    TypeTraits<UInt32>::BitsSet;

UInt32 ThreadCommonBase::_uiFallbackAspectId = 0;

/*-------------------------------------------------------------------------*/
/*                                 Set                                     */

void ThreadCommonBase::setChangeList(ChangeList *pChangeList)
{
    OSG::setRefd(_pChangeList, pChangeList);
}

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
void ThreadCommonBase::replaceChangelist(ChangeList *pNewList)
{
    _pChangeList = pNewList;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ThreadCommonBase::ThreadCommonBase(const Char8  *szName,
                                         UInt32  uiId, 
                                         bool    bGlobal) :
    
     Inherited     (szName, 
                    uiId,
                    bGlobal                               ),

    _uiAspectId    (0                                     ),
    _pChangeList   (NULL                                  ),
    _bNamespaceMask(TypeTraits<BitVector>::getOneElement()),
    _bLocalFlags   (TypeTraits<BitVector>::BitsClear      )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ThreadCommonBase::~ThreadCommonBase(void)
{
    OSG::subRef(_pChangeList);
}




#if defined (OSG_USE_PTHREADS)

#ifdef OSG_ENABLE_AUTOINIT_THREADS
void PThreadBase::autoCleanup(void *pData)
{
    UInt32 *pUInt = static_cast<UInt32 *>(pData);

    commitChanges();

    delete pUInt;

    ThreadRefPtr pThread = Thread::getCurrent();

    if(pThread != NULL)
    {
        pThread->shutdown();

        OSG::ThreadManager::the()->remove(pThread);

        pThread = NULL;
    }

#if defined(OSG_PTHREAD_ELF_TLS)
    _pLocalThread = NULL;
#endif
}
#endif

#if defined(OSG_PTHREAD_ELF_TLS)

__thread UInt32      PThreadBase::_uiTLSAspectId     = 0;
__thread ChangeList *PThreadBase::_pTLSChangeList    = NULL;
__thread BitVector   PThreadBase::_bTLSNamespaceMask = 1;
__thread BitVector   PThreadBase::_bTLSLocalFlags    = 
    TypeTraits<BitVector>::BitsClear;

#else

pthread_key_t PThreadBase::_aspectKey;
pthread_key_t PThreadBase::_changeListKey;
pthread_key_t PThreadBase::_namespaceMaskKey;

#endif

pthread_key_t PThreadBase::_localFlagsKey;

/*-------------------------------------------------------------------------*/
/*                               Free                                      */

#if !defined(OSG_PTHREAD_ELF_TLS)
void PThreadBase::freeAspect(void *pAspect)
{
    UInt32 *pUint = static_cast<UInt32 *>(pAspect);

    if(pUint != NULL)
        delete pUint;

    pthread_setspecific(_aspectKey, NULL);  
}

void PThreadBase::freeChangeList(void *pChangeList)
{
    ChangeList **pCl = static_cast<ChangeList **>(pChangeList);

    if(pCl != NULL)
        delete pCl;

    pthread_setspecific(_changeListKey, NULL);  
}

void PThreadBase::freeNamespaceMask(void *pNamespaceMask)
{
    BitVector *pNM = static_cast<BitVector *>(pNamespaceMask);

    if(pNM != NULL)
        delete pNM;

    pthread_setspecific(_namespaceMaskKey, NULL);  
}

void PThreadBase::freeLocalFlags(void *pLocalFlags)
{
    BitVector *pLF = static_cast<BitVector *>(pLocalFlags);

    if(pLF != NULL)
        delete pLF;

    pthread_setspecific(_localFlagsKey, NULL);  
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

PThreadBase::PThreadBase(const Char8   *szName, 
                               UInt32   uiId, 
                               bool     bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

PThreadBase::~PThreadBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

UInt32 PThreadBase::getCurrentAspect(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(_pTLSChangeList == NULL)
    {
        ThreadRefPtr pThread = Thread::get(NULL, true);

        pThread->doAutoInit();
    }
# endif

    return _uiTLSAspectId;
#else
    UInt32 *pUint;

    pUint = static_cast<UInt32 *>(pthread_getspecific(_aspectKey));

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pUint == NULL)
    {
        ThreadRefPtr pThread = Thread::get(NULL, true);

        pThread->doAutoInit();

        pUint = static_cast<UInt32 *>(pthread_getspecific(_aspectKey));
    }
# endif

    return *pUint;
#endif

}

ChangeList *PThreadBase::getCurrentChangeList(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(_pTLSChangeList == NULL)
    {
        ThreadRefPtr pThread = Thread::get(NULL, true);

        pThread->doAutoInit();
    }
# endif

    return _pTLSChangeList;

#else
    ChangeList **pCList;

    pCList = static_cast<ChangeList **>(pthread_getspecific(_changeListKey));

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pCList == NULL)
    {
        ThreadRefPtr pThread = Thread::get(NULL, true);

        pThread->doAutoInit();

        pCList = 
            static_cast<ChangeList **>(pthread_getspecific(_changeListKey));
    }
# endif

    return *pCList;
#endif
}

BitVector PThreadBase::getCurrentNamespaceMask(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _bTLSNamespaceMask;
#else
    BitVector *pBitVec;

    pBitVec = static_cast<BitVector *>(pthread_getspecific(_namespaceMaskKey));

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pBitVec == NULL)
    {
        ThreadRefPtr pThread = Thread::get(NULL, true);

        pThread->doAutoInit();

        pBitVec = 
            static_cast<BitVector *>(pthread_getspecific(_namespaceMaskKey));
    }
# endif

    return *pBitVec;
#endif
}

BitVector PThreadBase::getCurrentLocalFlags(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _bTLSLocalFlags;
#else
    BitVector *pBitVec;

    pBitVec = static_cast<BitVector *>(pthread_getspecific(_localFlagsKey));

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pBitVec == NULL)
    {
        ThreadRefPtr pThread = Thread::get(NULL, true);

        pThread->doAutoInit();

        pBitVec = static_cast<BitVector *>(pthread_getspecific(_localFlagsKey));
    }
# endif

    return *pBitVec;
#endif
}

void PThreadBase::setAspectTo(UInt32 uiNewAspect)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _uiTLSAspectId = uiNewAspect;
#else
    UInt32 *pUint;

    pUint = static_cast<UInt32 *>(pthread_getspecific(_aspectKey));

    *pUint = uiNewAspect;
#endif
}

void PThreadBase::setNamespaceMaskTo(BitVector bNamespaceMask)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSNamespaceMask = bNamespaceMask;
#else
    BitVector *pBitVec;

    pBitVec = static_cast<BitVector *>(pthread_getspecific(_namespaceMaskKey));

    *pBitVec = bNamespaceMask;
#endif
}

void PThreadBase::setLocalFlagsTo(BitVector bFlags)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSLocalFlags = bFlags;
#else
    BitVector *pBitVec;

    pBitVec = static_cast<BitVector *>(pthread_getspecific(_localFlagsKey));

    *pBitVec = bFlags;
#endif
}

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
void PThreadBase::setChangelistTo(ChangeList *pNewList)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _pTLSChangeList = pNewList;
#else
    ChangeList **pChangeList = NULL;

    pChangeList = 
        static_cast<ChangeList **>(pthread_getspecific(_changeListKey));

    *pChangeList = pNewList;
#endif
}
#endif

/*-------------------------------------------------------------------------*/
/*                               Setup                                     */

void PThreadBase::init(void)
{
    if(_bInitialized == true)
        return;

    Inherited::init();

    if(_bInitialized == true)
    {
        setupAspect    ();        
        setupChangeList();   
        setupMasks     ();
        setupLocalFlags();
    }
}

void PThreadBase::shutdown(void)
{
    Inherited::shutdown();

#if !defined(OSG_PTHREAD_ELF_TLS)

    UInt32 *pUint;

    pUint = static_cast<UInt32 *>(pthread_getspecific(_aspectKey));

    delete pUint;

    pthread_setspecific(_aspectKey, NULL);  


    ChangeList **pCList;

    pCList = static_cast<ChangeList **>(pthread_getspecific(_changeListKey));

    delete pCList;

    pthread_setspecific(_changeListKey, NULL);  


    BitVector *pBitVec;

    pBitVec = static_cast<BitVector *>(pthread_getspecific(_namespaceMaskKey));

    delete pBitVec;

    pthread_setspecific(_namespaceMaskKey, NULL);  

    pBitVec = static_cast<BitVector *>(pthread_getspecific(_localFlagsKey));

    delete pBitVec;

    pthread_setspecific(_localFlagsKey, NULL);  

#endif
}


void PThreadBase::setupAspect(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _uiTLSAspectId  = Inherited::_uiAspectId;
#else
    UInt32 *pUint = new UInt32;

    *pUint = Inherited::_uiAspectId;

    pthread_setspecific(_aspectKey, static_cast<void *>(pUint));  
#endif
}

void PThreadBase::setupChangeList(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    if(Inherited::_pChangeList == NULL)
    {
        _pTLSChangeList = new ChangeList;

        Inherited::setChangeList(_pTLSChangeList);
    }
    else
    {
        _pTLSChangeList = Inherited::_pChangeList;
        
        _pTLSChangeList->clear();
    }
    
    _pTLSChangeList->setAspect(Inherited::_uiAspectId);
#else
    ChangeList **pChangeList = new ChangeList *;

    if(Inherited::_pChangeList == NULL)
    {
        *pChangeList = new ChangeList;

        Inherited::setChangeList(*pChangeList);
    }
    else
    {
        *pChangeList = Inherited::_pChangeList;
        
        (*pChangeList)->clear();
    }

    (*pChangeList)->setAspect(Inherited::_uiAspectId);
    pthread_setspecific(_changeListKey, static_cast<void *>(pChangeList));  
#endif
}

void PThreadBase::setupMasks(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSNamespaceMask = Inherited::_bNamespaceMask;
#else
    BitVector *pBitVec = new BitVector;

    *pBitVec = Inherited::_bNamespaceMask;

    pthread_setspecific(_namespaceMaskKey, static_cast<void *>(pBitVec));  
#endif
}

void PThreadBase::setupLocalFlags(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSLocalFlags = Inherited::_bLocalFlags;
#else
    BitVector *pBitVec = new BitVector;

    *pBitVec = Inherited::_bLocalFlags;

    pthread_setspecific(_localFlagsKey, static_cast<void *>(pBitVec));  
#endif
}

void PThreadBase::doAutoInit(void)
{
    this->setAspect         (_uiFallbackAspectId);

    this->init();

#if defined(OSG_PTHREAD_ELF_TLS)
    UInt32 *pUint = new UInt32;

    *pUint = 0;

    pthread_setspecific(_localFlagsKey, static_cast<void *>(pUint));  
#endif
}

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SprocBase::SprocBase(const Char8  *szName,
                           UInt32  uiId, 
                           bool    bGlobal) :    
    Inherited(szName, uiId, bGlobal)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SprocBase::~SprocBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */


/*-------------------------------------------------------------------------*/
/*                               Setup                                     */

void SprocBase::init(void)
{
    if(_bInitialized == true)
        return; 

   Inherited::init();

    if(_bInitialized == true)
    {
        setAspectInternal      (this->_uiAspectId);
        setupChangeListInternal();
    }
}

void SprocBase::setupAspect(UInt32 uiAspect)
{
    ((OSGProcessData *) PRDA->usr_prda.fill)->_uiAspectId = uiAspect;
}

void SprocBase::setupChangeListInternal(void)
{
    if(Inherited::_pChangeList == NULL)
    {
        ((OSGProcessData *) PRDA->usr_prda.fill)->_pChangeList = 
            new ChangeList();

        Inherited::setChangeList(
            ((OSGProcessData *) PRDA->usr_prda.fill)->_pChangeList);
    }
    else
    {
        ((OSGProcessData *) PRDA->usr_prda.fill)->_pChangeList = 
            Inherited::_pChangeList;

        Inherited::_pChangeList->clear();
    }

    Inherited::_pChangeList->setAspect(Inherited::_uiAspectId);
}

#endif /* OSG_USE_SPROC */




#if defined (OSG_USE_WINTHREADS)

#if defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
UInt32 WinThreadBase::_aspectKey        = 0;
UInt32 WinThreadBase::_changeListKey    = 0;
UInt32 WinThreadBase::_namespaceMaskKey = 0;
UInt32 WinThreadBase::_localFlagsKey    = 0;
#else
__declspec (thread) UInt32      WinThreadBase::_uiAspectLocal       = 0;
__declspec (thread) ChangeList *WinThreadBase::_pChangeListLocal    = NULL;
__declspec (thread) BitVector   WinThreadBase::_bNamespaceMaskLocal = 1;
__declspec (thread) BitVector   WinThreadBase::_bLocalFlagsLocal    =
    TypeTraits<BitVector>::BitsClear;
#endif

/*-------------------------------------------------------------------------*/
/*                               Free                                      */

#if defined (OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
void WinThreadBase::freeAspect(void)
{
    UInt32 *pUint;

    pUint = (UInt32 *) TlsGetValue(_aspectKey);

    delete pUint;
}

void WinThreadBase::freeChangeList(void)
{
    ChangeList **pCList;

    pCList = (ChangeList **) TlsGetValue(_changeListKey);

    delete pCList;
}

void WinThreadBase::freeNamespaceMask(void)
{
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_namespaceMaskKey);

    delete pBitVec;
}

void WinThreadBase::freeLocalFlags(void)
{
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_localFlagsKey);

    delete pBitVec;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

WinThreadBase::WinThreadBase(const Char8  *szName,
                                   UInt32  uiId, 
                                   bool    bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

WinThreadBase::~WinThreadBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

UInt32 WinThreadBase::getCurrentAspect(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint;

    pUint = (UInt32 *) TlsGetValue(_aspectKey);

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pUint == NULL)
    {
        Thread *pThread = Thread::get(NULL);

        pThread->doAutoInit();

        pUint = (UInt32 *) TlsGetValue(_aspectKey);
    }
# endif

    return *pUint;
#else
    return _uiAspectLocal;
#endif
}

ChangeList *WinThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    ChangeList **pCList;

    pCList = (ChangeList **) TlsGetValue(_changeListKey);

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pCList == NULL)
    {
        Thread *pThread = Thread::get(NULL);

        pThread->doAutoInit();

        pCList = (ChangeList **) TlsGetValue(_changeListKey);
    }
# endif

    return *pCList;
#else
# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(_pChangeListLocal == NULL)
    {
        Thread *pThread = Thread::get(NULL);

        pThread->doAutoInit();
    }
# endif

    return _pChangeListLocal;
#endif
}

BitVector WinThreadBase::getCurrentNamespaceMask(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_namespaceMaskKey);

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pBitVec == NULL)
    {
        Thread *pThread = Thread::get(NULL);

        pThread->doAutoInit();

        pBitVec = (BitVector *) TlsGetValue(_namespaceMaskKey);
    }
# endif

    return *pBitVec;
#else
    return _bNamespaceMaskLocal;
#endif
}

BitVector WinThreadBase::getCurrentLocalFlags(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_localFlagsKey);

# ifdef OSG_ENABLE_AUTOINIT_THREADS
    if(pBitVec == NULL)
    {
        Thread *pThread = Thread::get(NULL);

        pThread->doAutoInit();

        pBitVec = (BitVector *) TlsGetValue(_localFlagsKey);
    }
# endif

    return *pBitVec;
#else
    return _bLocalFlagsLocal;
#endif
}

/*-------------------------------------------------------------------------*/
/*                               Setup                                     */

void WinThreadBase::init(void)
{
    if(_bInitialized == true)
        return;

    Inherited::init();

    if(_bInitialized == true)
    {
        setupAspect    ();
        setupChangeList();        
        setupMasks     ();
        setupLocalFlags();
    }
}

void WinThreadBase::shutdown(void)
{
    Inherited::shutdown();

#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint;

    pUint = static_cast<UInt32 *>(TlsGetValue(_aspectKey));

    delete pUint;

    TlsSetValue(_aspectKey, NULL);


    ChangeList **pCList;

    pCList = (ChangeList **) TlsGetValue(_changeListKey);

    delete pCList;

    TlsSetValue(_changeListKey, NULL);


    BitVector *pBitVec;

    pBitVec = (BitVector *) TlsGetValue(_namespaceMaskKey);

    delete pBitVec;

    TlsSetValue(_namespaceMaskKey, NULL);


    pBitVec = (BitVector *) TlsGetValue(_localFlagsKey);

    delete pBitVec;

    TlsSetValue(_localFlagsKey, NULL);
#endif
}

void WinThreadBase::setupAspect(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint = new UInt32;

    *pUint = Inherited::_uiAspectId;

    TlsSetValue(_aspectKey, pUint);
#else
    _uiAspectLocal = Inherited::_uiAspectId;
#endif
}

void WinThreadBase::setupChangeList(void)
{
#if defined (OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    ChangeList **pChangeList = new ChangeList *;

   if(Inherited::_pChangeList == NULL)
    {
        *pChangeList = new ChangeList;

        Inherited::setChangeList(*pChangeList);
    }
    else
    {
        *pChangeList = Inherited::_pChangeList;
        
        (*pChangeList)->clear();
    }

    (*pChangeList)->setAspect(Inherited::_uiAspectId);
    TlsSetValue(_changeListKey, pChangeList);
#else
    if(Inherited::_pChangeList == NULL)
    {
        _pChangeListLocal = new ChangeList;
        Inherited::setChangeList(_pChangeListLocal);
    }
    else
    {
        _pChangeListLocal = Inherited::_pChangeList;

        _pChangeListLocal->clear();
    }

    _pChangeListLocal->setAspect(Inherited::_uiAspectId);
#endif
}

void WinThreadBase::setupMasks(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec = new BitVector;

    *pBitVec = Inherited::_bNamespaceMask;

    TlsSetValue(_namespaceMaskKey, pBitVec);
#else
    _bNamespaceMaskLocal = Inherited::_bNamespaceMask;
#endif
}

void WinThreadBase::setupLocalFlags(void)
{
#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BitVector *pBitVec = new BitVector;

    *pBitVec = Inherited::_bLocalFlags;

    TlsSetValue(_localFlagsKey, pBitVec);
#else
    _bLocalFlagsLocal = Inherited::_bLocalFlags;
#endif
}

void WinThreadBase::doAutoInit(void)
{
    this->init();

    this->setAspect           (_uiFallbackAspectId);

    WinThreadBase::setAspectTo(_uiFallbackAspectId);
}

#endif /* OSG_USE_WINTHREADS */




MPThreadType Thread::_type("OSGThread", 
                           "OSGBaseThread", 
                           reinterpret_cast<CreateThreadF >(Thread::create),
                           static_cast<InitThreadingF>(Thread::initThreading));

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

Thread::ObjTransitPtr Thread::get(const Char8 *szName, bool bGlobal)
{
    BaseThreadTransitPtr pThread = 
        ThreadManager::the()->getThread(szName,
                                        bGlobal,
                                        "OSGThread");

    return dynamic_pointer_cast<Thread>(pThread);
}

Thread *Thread::find(const Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<Thread *>(pThread);
}

bool Thread::runFunction(ThreadFuncF  fThreadFunc, 
                         UInt32       uiAspectId,
                         void        *pThreadArg)
{
    if(uiAspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "OSGPTB : invalid aspect id" << std::endl;
        return false;
    }

    Inherited::setAspect(uiAspectId);

    return Inherited::runFunction(fThreadFunc, pThreadArg);
}

void Thread::run(UInt32 uiAspectId)
{
    this->runFunction(runWorkProc, uiAspectId, this);
}


/*-------------------------------------------------------------------------*/
/*                               Setup                                     */

Thread *Thread::create(const Char8 *szName, UInt32 uiId, bool bGlobal)
{
    return new Thread(szName, uiId, bGlobal);
}

static bool clearInitChanges(void)
{
//    OSG::Thread::getCurrentChangeList()->commitChangesAndClear();

    OSG::Thread::getCurrentChangeList()->clear();

    return true;
}

void Thread::initThreading(void)
{
    FINFO(("Thread::initThreading\n"))

#if defined(OSG_USE_PTHREADS)
# if !defined(OSG_PTHREAD_ELF_TLS)
    int rc; 

    rc = pthread_key_create(&(Thread::_aspectKey), //NULL); 
                              Thread::freeAspect);

    FFASSERT((rc == 0), 1, ("Failed to create pthread aspect key\n");)

    rc = pthread_key_create(&(Thread::_changeListKey), //NULL); 
                              Thread::freeChangeList);

    FFASSERT((rc == 0), 1, ("Failed to create pthread changelist key\n");)

    rc = pthread_key_create(&(Thread::_namespaceMaskKey), // NULL); 
                              Thread::freeNamespaceMask);

    FFASSERT((rc == 0), 1, ("Failed to create pthread namespaceMask key\n");)

    rc = pthread_key_create(&(Thread::_localFlagsKey), //NULL); 
                              Thread::freeLocalFlags);

    FFASSERT((rc == 0), 1, ("Failed to create pthread localFlags key\n");)
# else
#  ifdef OSG_ENABLE_AUTOINIT_THREADS
    int rcd = pthread_key_create(&(Thread::_localFlagsKey), 
                                 Thread::autoCleanup);

    FFASSERT((rcd == 0), 1, ("Failed to create pthread dummy aspect key\n");)
#  endif
# endif
#endif

#if defined(OSG_USE_WINTHREADS) && defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    Thread::_aspectKey     = TlsAlloc();

    FFASSERT((Thread::_aspectKey != 0xFFFFFFFF), 1, 
             ("Failed to alloc aspect key local storage\n");)

    Thread::_changeListKey = TlsAlloc();

    FFASSERT((Thread::_changeListKey != 0xFFFFFFFF), 1, 
             ("Failed to alloc changelist key local storage\n");)

    Thread::_namespaceMaskKey = TlsAlloc();

    FFASSERT((Thread::_namespaceMaskKey != 0xFFFFFFFF), 1, 
             ("Failed to alloc namespace key local storage\n");)

    Thread::_localFlagsKey = TlsAlloc();

    FFASSERT((Thread::_localFlagsKey != 0xFFFFFFFF), 1, 
             ("Failed to alloc localflags key local storage\n");)
#endif

    ThreadManager::setAppThreadType("OSGThread");

    addPostFactoryInitFunction(clearInitChanges);
}

void Thread::terminateThreading(void)
{
    Inherited::terminateThreading();

    FINFO(("Thread::terminateThreading\n"));

#if defined(OSG_USE_PTHREADS)
# if !defined(OSG_PTHREAD_ELF_TLS)
    int rc; 

    rc = pthread_key_delete(Thread::_aspectKey);

    FFASSERT((rc == 0), 1, ("Failed to destroy pthread aspect key\n");)

    rc = pthread_key_delete(Thread::_changeListKey);

    FFASSERT((rc == 0), 1, ("Failed to destroy pthread changelist key\n");)

    rc = pthread_key_delete(Thread::_namespaceMaskKey);

    FFASSERT((rc == 0), 1, ("Failed to destroy pthread namespaceMask key\n");)

    rc = pthread_key_delete(Thread::_localFlagsKey);

    FFASSERT((rc == 0), 1, ("Failed to destroy pthread localFlags key\n");)
# else
#  ifdef OSG_ENABLE_AUTOINIT_THREADS
    int rcd = pthread_key_delete(Thread::_localFlagsKey);

    FFASSERT((rcd == 0), 1, ("Failed to destroy pthread dummy aspect key\n");)
#  endif
# endif
#endif

#if defined(OSG_USE_WINTHREADS) && defined (OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    if(Thread::_aspectKey != 0xFFFFFFFF)
    {
        TlsFree(Thread::_aspectKey);

        Thread::_aspectKey = 0xFFFFFFFF;
    }

    if(Thread::_changeListKey != 0xFFFFFFFF)
    {
        TlsFree(Thread::_changeListKey);

        Thread::_changeListKey = 0xFFFFFFFF;
    }

    if(Thread::_namespaceMaskKey != 0xFFFFFFFF)
    {
        TlsFree(Thread::_namespaceMaskKey);

        Thread::_namespaceMaskKey = 0xFFFFFFFF;
    }

    if(Thread::_localFlagsKey != 0xFFFFFFFF)
    {
        TlsFree(Thread::_localFlagsKey);

        Thread::_localFlagsKey = 0xFFFFFFFF;
    }
#endif
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Thread::Thread(const Char8 *szName, UInt32 uiId, bool bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Thread::~Thread(void)
{
}




MPThreadType ExternalThread::_type(
    "OSGExternalThread", 
    "OSGMPBase", 
    reinterpret_cast<CreateThreadF>(ExternalThread::create),
    NULL);

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

ExternalThread::ObjTransitPtr ExternalThread::get(const Char8 *szName, 
                                                        bool   bGlobal)
{
    BaseThreadTransitPtr pThread = 
        ThreadManager::the()->getThread(szName, 
                                        bGlobal,
                                        "OSGExternalThread");

    return dynamic_pointer_cast<ExternalThread>(pThread);
}

ExternalThread *ExternalThread::find(const Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<ExternalThread *>(pThread);
}

void ExternalThread::initialize(UInt32 uiAspectId)
{
    if(_bInitialized == true)
        return;

    Inherited::setAspect(uiAspectId);
    
    this->init();    
}

void ExternalThread::shutdown(void)
{
    Inherited::shutdown();
}

/*-------------------------------------------------------------------------*/
/*                               Setup                                     */

ExternalThread *ExternalThread::create(const Char8 *szName, 
                                             UInt32 uiId, 
                                             bool   bGlobal)
{
    return new ExternalThread(szName, uiId, bGlobal);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ExternalThread::ExternalThread(const Char8 *szName, 
                                     UInt32 uiId, 
                                     bool   bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ExternalThread::~ExternalThread(void)
{
}

#if defined(OSG_ENABLE_AUTOINIT_THREADS) && defined(WIN32)
static void doThreadCleanup(void)
{
    BaseThread *pThread = NULL;

#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    BaseThread **pT =  
		static_cast<BaseThread **>(
            TlsGetValue(BaseWinThreadBase::_threadKey));

    if(pT != NULL)
    {
        pThread = *pT;
    }
#else
    pThread =  BaseThread::_pThreadLocal;
#endif

    if(pThread != NULL)
    {
        pThread->shutdown();

        OSG::subRef(pThread);
    }
}

void doThreadInit(void)
{
#ifndef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    WinThreadBase::_uiAspectLocal = WinThreadBase::_uiFallbackAspectId;
#endif
}
#endif

OSG_END_NAMESPACE

#if defined(OSG_ENABLE_AUTOINIT_THREADS) && defined(WIN32)
#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

BOOL WINAPI DllMain(HINSTANCE hinstDLL, // DLL module handle
                    DWORD fdwReason,    // reason called
                    LPVOID lpvReserved) // reserved
{ 
//    LPVOID lpvData; 
//    BOOL fIgnore; 
    
    switch (fdwReason) 
    { 
        // The DLL is loading due to process 
        // initialization or a call to LoadLibrary. 
 
        case DLL_PROCESS_ATTACH: 
             break;

        // The attached process creates a new thread. 
 
        case DLL_THREAD_ATTACH: 
            OSG::doThreadInit();
            break; 
 
        // The thread of the attached process terminates.
 
        case DLL_THREAD_DETACH: 
            OSG::doThreadCleanup();
        break; 
 
        // DLL unload due to process termination or FreeLibrary. 
 
        case DLL_PROCESS_DETACH: 
            break; 
 
        default: 
            break; 
    } 
 
    return TRUE; 

    UNREFERENCED_PARAMETER(hinstDLL); 
    UNREFERENCED_PARAMETER(lpvReserved); 
}

#ifdef __cplusplus    // If used by C++ code, 
}          // we need to export the C interface
#endif

#endif
