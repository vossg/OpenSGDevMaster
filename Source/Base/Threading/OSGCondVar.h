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

#ifndef _OSGCONDVAR_H_
#define _OSGCONDVAR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGMPBase.h"

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined,  check your system/compiler combination"
#endif

#if defined (OSG_USE_PTHREADS)
#include <pthread.h>
#include <cerrno>
#endif

#if defined (OSG_USE_SPROC)
#include <ulocks.h>
#endif

#include <boost/mpl/if.hpp>

OSG_BEGIN_NAMESPACE

template <class MPFieldT>
class MPFieldStore;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING CondVarCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPBase  Inherited;

            UInt32 _uiCondVarId;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CondVarCommonBase(void);
    CondVarCommonBase(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~CondVarCommonBase(void); 
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    CondVarCommonBase  (const CondVarCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const CondVarCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_PTHREADS)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class PThreadCondVarBase : public CondVarCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef CondVarCommonBase Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadCondVarBase(void);
    PThreadCondVarBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadCondVarBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Construction                                */
    /*! \{                                                                 */

    bool init    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Destruction                                 */
    /*! \{                                                                 */

    void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   CondVar                                    */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    bool wait(const float seconds = -1.0);
    void signal();
    void broadcast();

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // XXX: We should make it so we can pass in a mutex some way.
    //CondVarCommonBase
    pthread_mutex_t _pLowLevelLock;
    pthread_cond_t _pLowLevelCondVar;

    /*!\brief prohibit default function (move to 'public' if needed) */
    PThreadCondVarBase(const PThreadCondVarBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PThreadCondVarBase &source);
};

typedef PThreadCondVarBase CondVarBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_SPROC)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class SprocCondVarBase : public CondVarCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef CondVarCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocCondVarBase(void);
    SprocCondVarBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocCondVarBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    bool init    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void shutdown(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    CondVar                                   */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    bool wait(const float seconds = -1.0);
    void signal();
    void broadcast();

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

#define OSG_SPROC_USE_LOCK
#ifdef OSG_SPROC_USE_LOCK
    ulock_t  _pLowLevelLock;
#else
    usema_t *_pLowLevelSema;
#endif

    /*!\brief prohibit default function (move to 'public' if needed) */
    SprocCondVarBase(const SprocCondVarBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SprocCondVarBase &source);
};

typedef SprocCondVarBase CondVarBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_WINTHREADS)

//#if _WIN32_WINNT < 0x0400
#define OSG_WINLOCK_USE_MUTEX
//#endif

typedef struct
{
  int waiters_count_;
  // Number of waiting threads.

  CRITICAL_SECTION waiters_count_lock_;
  // Serialize access to <waiters_count_>.

  HANDLE sema_;
  // Semaphore used to queue up threads waiting for the condition to
  // become signaled. 

  HANDLE waiters_done_;
  // An auto-reset event used by the broadcast/signal thread to wait
  // for all the waiting thread(s) to wake up and be released from the
  // semaphore. 

  size_t was_broadcast_;
  // Keeps track of whether we were broadcasting or signaling.  This
  // allows us to optimize the code if we're just signaling.
} pthread_cond_t;

typedef HANDLE pthread_mutex_t;

int 
pthread_cond_init (pthread_cond_t *cv, void* dummy);
int
pthread_cond_wait (pthread_cond_t *cv, 
                   pthread_mutex_t *external_mutex);
int
pthread_cond_signal (pthread_cond_t *cv);

int
pthread_cond_broadcast (pthread_cond_t *cv);

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING WinThreadCondVarBase : public CondVarCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef CondVarCommonBase Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadCondVarBase(void);
    WinThreadCondVarBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WinThreadCondVarBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */
    
    bool init    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void shutdown(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       CondVar                                */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    bool wait(const float seconds = -1.0);
    void signal();
    void broadcast();
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

#ifdef OSG_WINLOCK_USE_MUTEX
    Handle  _pMutex;
#else
    CRITICAL_SECTION _pCriticalSection;
#endif

   int waiters_count_;
   // Number of waiting threads.

   CRITICAL_SECTION waiters_count_lock_;
   // Serialize access to <waiters_count_>.

   HANDLE sema_;
   // Semaphore used to queue up threads waiting for the condition to
   // become signaled. 

   HANDLE waiters_done_;
   // An auto-reset event used by the broadcast/signal thread to wait
   // for all the waiting thread(s) to wake up and be released from the
   // semaphore. 

   // Keeps track of whether we were broadcasting or signaling.  This
   // allows us to optimize the code if we're just signaling.
   size_t was_broadcast_;


    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadCondVarBase(const WinThreadCondVarBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadCondVarBase &source);
};

typedef WinThreadCondVarBase CondVarBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING CondVar : public CondVarBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPCondVarType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static       CondVar       *get         (const Char8 *szName);
    static       CondVar       *find        (const Char8 *szName);

    static       CondVar       *create      (      void         );

    static const MPCondVarType &getClassType(      void         ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       CondVar                                */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    bool wait(const float seconds = -1.0);
    void signal();
    void broadcast();
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef CondVarBase    Inherited;

    static  MPCondVarType _type;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static CondVar *create(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CondVar(void);
    CondVar(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~CondVar(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class MPFieldStore<CondVar>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    CondVar(const CondVar &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const CondVar &source);
};

OSG_END_NAMESPACE

#define OSGCONDVAR_HEADER_CVSID "@(#)$Id$"

#include "OSGCondVar.inl"

#endif /* _OSGCONDVAR_H_ */
