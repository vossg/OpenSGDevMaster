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

#ifndef _OSGBASETHREAD_H_
#define _OSGBASETHREAD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGMPBase.h"

#ifdef OSG_USE_PTHREADS
#include <pthread.h>
#endif

#include <utility>

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined, check your system/compiler combination"
#endif

#if defined (OSG_USE_PTHREADS) && defined (OSG_USE_SPROC)
#error "PTHREAD and SPROC defined, check your system/compiler combination"
#endif

#if defined (OSG_USE_WINTHREADS) && defined (OSG_USE_SPROC)
#error "Winthreads and SPROC defined, check your system/compiler combination"
#endif

OSG_BEGIN_NAMESPACE

class BaseThread;

template <class MPFieldT>
class MPFieldStore;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING BaseThreadCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef void (*ThreadFuncF)(void *pThreadArg);

    bool isInitialized(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPBase  Inherited;

            UInt32 _uiThreadId;
            bool   _bInitialized;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThreadCommonBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BaseThreadCommonBase(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseThreadCommonBase(const BaseThreadCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class BasePThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseThreadCommonBase  Inherited;

#if defined(OSG_PTHREAD_ELF_TLS)
    static  __thread BaseThread    *_pLocalThread;
#else
    static           pthread_key_t  _threadKey;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    static void *threadFunc(void *pThreadArg);

#if !defined(OSG_PTHREAD_ELF_TLS)
    static void  freeThread(void *pThread   );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void            *_pThreadData[3];
    pthread_t       *_pThreadDesc;

    pthread_cond_t  *_pBlockCond;
    pthread_mutex_t *_pBlockMutex;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BasePThreadBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BasePThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init          (void);
    virtual void shutdown      (void);

            void setupThread   (void);
            void setupBlockCond(void);

    virtual void doAutoInit    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BasePThreadBase *threadP);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    bool runFunction(ThreadFuncF  fThreadFunc,
                     void        *pThreadArg );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    void block  (void);
    void unblock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool exists   (void);

    void terminate(void);
    void kill     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BasePThreadBase(const BasePThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BasePThreadBase &source);
};

typedef BasePThreadBase BaseThreadBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class BaseSprocBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseThreadCommonBase Inherited;

    /*! \hideinhierarchy
     */

    struct ProcessData
    {
        BaseThread *_pThread;
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    static void threadFunc(void *pThreadArgP);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void  *_pThreadData[3];
    pid_t  _pid;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseSprocBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseSprocBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init              (void               );
    virtual void shutdown          (void               );

            void setPid            (void               );
            void setCurrentInternal(BaseThread *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BaseSprocBase *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    bool runFunction(ThreadFuncF  fThreadFunc,
                     void        *pThreadArg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    void block    (void);
    void unblock  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool exists   (void);

    void terminate(void);
    void kill     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseSprocBase(const BaseSprocBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseSprocBase &source);
};

typedef BaseSprocBase BaseThreadBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

#ifdef OSG_ENABLE_AUTOINIT_THREADS
static void doThreadCleanup(void);
#endif

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class BaseWinThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

   public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseThreadCommonBase Inherited;

#if defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    static UInt32 _threadKey;
#else
    static __declspec (thread) BaseThread *_pThreadLocal;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    static void threadFunc(void *pThreadArg);

#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    OSG_BASE_DLLMAPPING 
    static void freeThread(void            );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void   *_pThreadData[3];

    Handle  _pThreadHandle;
    Handle  _pExternalHandle;
    UInt32  _uiNativeThreadId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    BaseWinThreadBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual ~BaseWinThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual void init             (void                  );
    OSG_BASE_DLLMAPPING 
    virtual void shutdown         (void                  );

            OSG_BASE_DLLMAPPING 
            void setPid           (void                  );
            OSG_BASE_DLLMAPPING 
            void setExternalHandle(Handle pExternalHandle);

            OSG_BASE_DLLMAPPING 
            void setupThread      (void                  );

    OSG_BASE_DLLMAPPING 
    virtual void doAutoInit       (void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    static BaseThread *getCurrent(void);

    OSG_BASE_DLLMAPPING 
    static BaseThread *getCurrentInternal(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    static void join(BaseWinThreadBase *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    bool runFunction(ThreadFuncF fThreadFunc,
                     void        *pThreadArg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    void block  (void);
    OSG_BASE_DLLMAPPING 
    void unblock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    bool exists   (void);

    OSG_BASE_DLLMAPPING 
    void terminate(void);
    OSG_BASE_DLLMAPPING 
    void kill     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    void print(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
   private:

    friend class ThreadManager;
#ifdef OSG_ENABLE_AUTOINIT_THREADS
    friend void doThreadCleanup(void);
#endif

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseWinThreadBase(const BaseWinThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseWinThreadBase &source);
};

typedef BaseWinThreadBase BaseThreadBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING BaseThread : public BaseThreadBase
{
    /*==========================  PRIVATE  ================================*/

  private:

    typedef BaseThreadBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPThreadType Type;

    OSG_GEN_INTERNAL_MEMOBJPTR(BaseThread);

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static       ObjTransitPtr  get         (const Char8 *szName,
                                                   bool   bGlobal);
    static       BaseThread    *find        (const Char8 *szName );
    static       ObjTransitPtr  create      (      void          );

    static const MPThreadType  &getClassType(      void          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BaseThread *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    void run        (void                   );

    bool runFunction(ThreadFuncF fThreadFunc,
                     void        *pThreadArg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    void block  (void);
    void unblock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    bool exists   (void);

    void terminate(void);
    void kill     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static MPThreadType _type;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static BaseThread *create            (const Char8 *szName, 
                                                UInt32 uiId, 
                                                bool   bGlobal);

    static void        initThreading     (      void          );
    static void        terminateThreading(      void          );

    static void        runWorkProc       (      void  *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThread(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseThread(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Workproc                                */
    /*! \{                                                                 */

    virtual void workProc(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseThread(const BaseThread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseThread &source);
};

OSG_GEN_MEMOBJPTR(BaseThread);

OSG_END_NAMESPACE

#include "OSGBaseThread.inl"

#endif /* _OSGBASETHREAD_H_ */
