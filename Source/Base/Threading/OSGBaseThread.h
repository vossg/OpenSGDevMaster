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

/*! \ingroup GrpBaseBaseMultiThreading
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

    BaseThreadCommonBase(const Char8 *szName, UInt32 uiId);

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

/*! \ingroup GrpBaseBaseMultiThreading
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

    BasePThreadBase(const Char8 *szName, UInt32 uiId);

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

/*! \ingroup GrpBaseBaseMultiThreading
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

    BaseSprocBase(const Char8 *szName, UInt32 uiId);

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

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING BaseWinThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

   public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseThreadCommonBase Inherited;

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
    static UInt32 _threadKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
    static __declspec (thread) BaseThread *_pThreadLocal;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static void threadFunc(void *pThreadArg);

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
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

    BaseWinThreadBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseWinThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init             (void                  );
    virtual void shutdown         (void                  );

            void setPid           (void                  );
            void setExternalHandle(Handle pExternalHandle);

            void setupThread      (void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BaseWinThreadBase *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

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
    /*==========================  PRIVATE  ================================*/
   private:

    friend class ThreadManager;

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

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING BaseThread : public BaseThreadBase
{
    /*==========================  PRIVATE  ================================*/

  private:

    typedef BaseThreadBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPThreadType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static       BaseThread   *get         (const Char8 *szName);
    static       BaseThread   *find        (const Char8 *szName);
    static       BaseThread   *create      (      void         );

    static const MPThreadType &getClassType(      void         );

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

    static BaseThread *create            (const Char8 *szName, UInt32 uiId);

    static void        initThreading     (      void                      );
    static void        terminateThreading(      void                      );

    static void        runWorkProc       (      void  *pThread            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThread(const Char8 *szName, UInt32 uiId);

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

void setRefd(BaseThread *&pObject, 
             BaseThread * pNewObject);

OSG_END_NAMESPACE

#define OSGBASETHREAD_HEADER_CVSID "@(#)$Id: $"

#include "OSGBaseThread.inl"

#endif /* _OSGBASETHREAD_H_ */
