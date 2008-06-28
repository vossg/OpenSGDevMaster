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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGThread.cpp
    \ingroup GrpSystemMultithreading
 */
#endif

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGThread.h"
#include "OSGBaseFunctions.h"
#include "OSGChangeList.h"
#ifndef OSG_WINCE
#include "OSGThreadManager.h"
#endif
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

OSG_USING_NAMESPACE

#ifndef OSG_WINCE

const UInt32 ThreadCommonBase::InvalidAspect = 
    TypeTraits<UInt32>::BitsSet;

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
                                         UInt32  uiId) :
    
     Inherited     (szName, 
                    uiId                                  ),

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
pthread_key_t PThreadBase::_localFlagsKey;
#endif

/*-------------------------------------------------------------------------*/
/*                               Free                                      */

#if !defined(OSG_PTHREAD_ELF_TLS)
void PThreadBase::freeAspect(void *pAspect)
{
    UInt32 *pUint = (UInt32 *) pAspect;

    if(pUint != NULL)
        delete pUint;
}

void PThreadBase::freeChangeList(void *pChangeList)
{
    ChangeList **pCl = (ChangeList **) pChangeList;

    if(pCl != NULL)
        delete pCl;
}

void PThreadBase::freeNamespaceMask(void *pNamespaceMask)
{
    BitVector *pNM = (BitVector *) pNamespaceMask;

    if(pNM != NULL)
        delete pNM;
}

void PThreadBase::freeLocalFlags(void *pLocalFlags)
{
    BitVector *pLF = (BitVector *) pLocalFlags;

    if(pLF != NULL)
        delete pLF;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

PThreadBase::PThreadBase(const Char8   *szName, 
                               UInt32   uiId) :
    Inherited(szName, uiId)
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
    return _uiTLSAspectId;
#else
    UInt32 *pUint;

    pUint = (UInt32 *) pthread_getspecific(_aspectKey);

    return *pUint;
#endif

}

ChangeList *PThreadBase::getCurrentChangeList(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _pTLSChangeList;
#else
    ChangeList **pCList;

    pCList = (ChangeList **) pthread_getspecific(_changeListKey);

    return *pCList;
#endif
}

BitVector PThreadBase::getCurrentNamespaceMask(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _bTLSNamespaceMask;
#else
    BitVector *pBitVec;

    pBitVec = (BitVector *) pthread_getspecific(_namespaceMaskKey);

    return *pBitVec;
#endif
}

BitVector PThreadBase::getCurrentLocalFlags(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    return _bTLSLocalFlags;
#else
    BitVector *pBitVec;

    pBitVec = (BitVector *) pthread_getspecific(_localFlagsKey);

    return *pBitVec;
#endif
}

void PThreadBase::setAspectTo(UInt32 uiNewAspect)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _uiTLSAspectId = uiNewAspect;
#else
    UInt32 *pUint;

    pUint = (UInt32 *) pthread_getspecific(_aspectKey);

    *pUint = uiNewAspect;
#endif
}

void PThreadBase::setNamespaceMaskTo(BitVector bNamespaceMask)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSNamespaceMask = bNamespaceMask;
#else
    BitVector *pBitVec;

    pBitVec = (BitVector *) pthread_getspecific(_namespaceMaskKey);

    *pBitVec = bNamespaceMask;
#endif
}

void PThreadBase::setLocalFlagsTo(BitVector bFlags)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSLocalFlags = bFlags;
#else
    BitVector *pBitVec;

    pBitVec = (BitVector *) pthread_getspecific(_localFlagsKey);

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

    pChangeList = (ChangeList **) pthread_getspecific(_changeListKey);

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

    pUint = (UInt32 *) pthread_getspecific(_aspectKey);

    delete pUint;

    pthread_setspecific(_aspectKey, NULL);  


    ChangeList **pCList;

    pCList = (ChangeList **) pthread_getspecific(_changeListKey);

    delete pCList;

    pthread_setspecific(_changeListKey, NULL);  


    BitVector *pBitVec;

    pBitVec = (BitVector *) pthread_getspecific(_namespaceMaskKey);

    delete pBitVec;

    pthread_setspecific(_namespaceMaskKey, NULL);  

    pBitVec = (BitVector *) pthread_getspecific(_localFlagsKey);

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

    pthread_setspecific(_aspectKey, (void *) pUint);  
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
    pthread_setspecific(_changeListKey, (void *) pChangeList);  
#endif
}

void PThreadBase::setupMasks(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSNamespaceMask = Inherited::_bNamespaceMask;
#else
    BitVector *pBitVec = new BitVector;

    *pBitVec = Inherited::_bNamespaceMask;

    pthread_setspecific(_namespaceMaskKey, (void *) pBitVec);  
#endif
}

void PThreadBase::setupLocalFlags(void)
{
#if defined(OSG_PTHREAD_ELF_TLS)
    _bTLSLocalFlags = Inherited::_bLocalFlags;
#else
    BitVector *pBitVec = new BitVector;

    *pBitVec = Inherited::_bLocalFlags;

    pthread_setspecific(_localFlagsKey, (void *) pBitVec);  
#endif
}

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SprocBase::SprocBase(const Char8  *szName,
                           UInt32  uiId) :    
    Inherited(szName, uiId)
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
                                   UInt32  uiId) :
    Inherited(szName, uiId)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

WinThreadBase::~WinThreadBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

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

#endif /* OSG_USE_WINTHREADS */




MPThreadType Thread::_type("OSGThread", 
                           "OSGBaseThread", 
                           reinterpret_cast<CreateThreadF >(Thread::create),
                           static_cast<InitThreadingF>(Thread::initThreading));

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

Thread *Thread::get(const Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->getThread(szName, "OSGThread");

    return dynamic_cast<Thread *>(pThread);
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

Thread *Thread::create(const Char8 *szName, UInt32 uiId)
{
    return new Thread(szName, uiId);
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

#if defined(OSG_USE_PTHREADS) && !defined(OSG_PTHREAD_ELF_TLS)
    int rc; 

    rc = pthread_key_create(&(Thread::_aspectKey), NULL); 
//                              Thread::freeAspect);

    FFASSERT((rc == 0), 1, ("Failed to create pthread aspect key\n");)

    rc = pthread_key_create(&(Thread::_changeListKey), NULL); 
//                              Thread::freeChangeList);

    FFASSERT((rc == 0), 1, ("Failed to create pthread changelist key\n");)
#endif

#if defined(OSG_USE_WINTHREADS) && defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)       
    Thread::_aspectKey     = TlsAlloc();

    FFASSERT((Thread::_aspectKey != 0xFFFFFFFF), 1, 
             ("Failed to alloc aspect key local storage\n");)

    Thread::_changeListKey = TlsAlloc();

    FFASSERT((Thread::_changeListKey != 0xFFFFFFFF), 1, 
             ("Failed to alloc changelist key local storage\n");)
#endif

    ThreadManager::setAppThreadType("OSGThread");

    addPostFactoryInitFunction(clearInitChanges);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Thread::Thread(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
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

ExternalThread *ExternalThread::get(const Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->getThread(szName, 
                                                          "OSGExternalThread");

    return dynamic_cast<ExternalThread *>(pThread);
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
                                             UInt32 uiId)
{
    return new ExternalThread(szName, uiId);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ExternalThread::ExternalThread(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ExternalThread::~ExternalThread(void)
{
}

#else
ChangeList *Thread::getCurrentChangeList(void)
{
    static ChangeList *theList = NULL;

    if(theList == NULL)
    {
		theList = ChangeList::create();
    }

    return theList;
}
#endif
