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

#ifndef _OSGTHREAD_H_
#define _OSGTHREAD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGContainerForwards.h"

#include "OSGBaseThread.h"

#include <utility>

#include "OSGBaseTypes.h"

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined, check your system/compiler combination"
#endif

#ifdef OSG_USE_PTHREADS
#   ifdef OSG_USE_SPROC
#       error  "PTHREAD and SPROC threading models defined. This is a bug!"
#   endif
#   ifdef OSG_USE_WINTHREADS
#       error  "PTHREAD and WINTHREADS threading models defined. This is a bug!"
#   endif
#elif defined(OSG_USE_SPROC)
#   ifdef OSG_USE_WINTHREADS
#       error  "SPROC and WINTHREADS threading models defined. This is a bug!"
#   endif
#endif

OSG_BEGIN_NAMESPACE

class Thread;
class ChangeList;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING ThreadCommonBase : public BaseThread
{
    /*==========================  PUBLIC  =================================*/

  public :

    static const UInt32 InvalidAspect;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    UInt32      getAspect       (void);
    ChangeList *getChangeList   (void);
    BitVector   getNamespaceMask(void);
    BitVector   getLocalFlags   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    static void setFallbackAspectId(UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
    void replaceChangelist(ChangeList *pNewList);
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseThread Inherited;

    static UInt32 _uiFallbackAspectId;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32      _uiAspectId;
    ChangeList *_pChangeList;
    BitVector   _bNamespaceMask;
    BitVector   _bLocalFlags;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ThreadCommonBase(      void                                    );
    ThreadCommonBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ThreadCommonBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setAspect       (UInt32      uiAspectId    );
    void setChangeList   (ChangeList *pChangeList   );
    void setNamespaceMask(BitVector   bNamespaceMask);
    void setLocalFlags   (BitVector   bFlags        );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;
    friend class Thread;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ThreadCommonBase(const ThreadCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class PThreadBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadCommonBase Inherited;

#ifdef OSG_ENABLE_AUTOINIT_THREADS
    static void autoCleanup(void *);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#if defined(OSG_PTHREAD_ELF_TLS)
    static __thread UInt32      _uiTLSAspectId;
    static __thread ChangeList *_pTLSChangeList;
    static __thread BitVector   _bTLSNamespaceMask;
    static __thread BitVector   _bTLSLocalFlags;
#else
    static pthread_key_t  _aspectKey;
    static pthread_key_t  _changeListKey;
    static pthread_key_t  _namespaceMaskKey;
#endif
    static pthread_key_t  _localFlagsKey;

#if !defined(OSG_PTHREAD_ELF_TLS)
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Free                                     */
    /*! \{                                                                 */

    static void  freeAspect       (void *pAspect       );
    static void  freeChangeList   (void *pChangeList   );
    static void  freeNamespaceMask(void *pNamespaceMask);
    static void  freeLocalFlags   (void *pLocalFlags   );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32       getCurrentAspect       (void);
    static ChangeList  *getCurrentChangeList   (void);
    static BitVector    getCurrentNamespaceMask(void);
    static BitVector    getCurrentLocalFlags   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Setup                                   */
    /*! \{                                                                 */

    virtual void init           (void);
    virtual void shutdown       (void);

            void setupAspect    (void);
            void setupChangeList(void);
            void setupMasks     (void);
            void setupLocalFlags(void);

    virtual void doAutoInit     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

    static void setAspectTo       (UInt32      uiNewAspect   );
    static void setNamespaceMaskTo(BitVector   bNamespaceMask);
    static void setLocalFlagsTo   (BitVector   bNamespaceMask);
#ifdef OSG_THREAD_DEBUG_SETASPECTTO
    static void setChangelistTo   (ChangeList *pNewList      );
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    PThreadBase(const PThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PThreadBase &source);
};

typedef PThreadBase ThreadBase;

OSG_GEN_MEMOBJPTR(ThreadBase);

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class SprocBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadCommonBase Inherited;

    struct OSGProcessData : public ProcessData
    {
        UInt32      _uiAspectId;
        ChangeList *_pChangeList;
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32      getCurrentAspect    (void);
    static ChangeList *getCurrentChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Setup                                   */
    /*! \{                                                                 */

    virtual void init           (void           );

            void setupAspect    (UInt32 uiAspect);
            void setupChangeList(void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

    static void setAspectTo(UInt32 uiNewAspect);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    SprocBase(const SprocBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SprocBase &source);
};

typedef SprocBase ThreadBase;

OSG_GEN_MEMOBJPTR(ThreadBase);

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

#ifdef OSG_ENABLE_AUTOINIT_THREADS
static void doThreadInit(void);
#endif

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class WinThreadBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#if defined(OSG_WIN32_ASPECT_USE_LOCALSTORAGE)
    static UInt32 _aspectKey;
    static UInt32 _changeListKey;
    static UInt32 _namespaceMaskKey;
    static UInt32 _localFlagsKey;
#else
    static __declspec (thread) UInt32      _uiAspectLocal;
    static __declspec (thread) ChangeList *_pChangeListLocal;
    static __declspec (thread) BitVector   _bNamespaceMaskLocal;
    static __declspec (thread) BitVector   _bLocalFlagsLocal;
#endif

#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Free                                   */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    static void freeAspect       (void);

    OSG_BASE_DLLMAPPING 
    static void freeChangeList   (void);

    OSG_BASE_DLLMAPPING 
    static void freeNamespaceMask(void);

    OSG_BASE_DLLMAPPING 
    static void freeLocalFlags   (void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    static UInt32      getCurrentAspect    (void);

    OSG_BASE_DLLMAPPING 
    static ChangeList *getCurrentChangeList(void);

    OSG_BASE_DLLMAPPING 
    static BitVector    getCurrentNamespaceMask(void);

    OSG_BASE_DLLMAPPING
    static BitVector    getCurrentLocalFlags   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    WinThreadBase(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual ~WinThreadBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    virtual void init            (void);

    OSG_BASE_DLLMAPPING
    virtual void shutdown       (void);

            OSG_BASE_DLLMAPPING 
            void setupAspect     (void);

            OSG_BASE_DLLMAPPING 
            void setupChangeList (void);

            OSG_BASE_DLLMAPPING 
            void setupMasks      (void);

            OSG_BASE_DLLMAPPING 
            void setupLocalFlags(void);

    OSG_BASE_DLLMAPPING 
    virtual void doAutoInit     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING 
    static void setAspectTo       (UInt32      uiNewAspect   );

    OSG_BASE_DLLMAPPING 
    static void setNamespaceMaskTo(BitVector   bNamespaceMask);

    OSG_BASE_DLLMAPPING
    static void setLocalFlagsTo   (BitVector   bLocalFlags   );

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
    OSG_BASE_DLLMAPPING
    static void setChangelistTo   (ChangeList *pNewList      );
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;
#ifdef OSG_ENABLE_AUTOINIT_THREADS
    friend void doThreadInit(void);
#endif

    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadBase(const WinThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadBase &source);
};

typedef WinThreadBase ThreadBase;

OSG_GEN_MEMOBJPTR(ThreadBase);

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING Thread : public ThreadBase
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadBase Inherited;
    typedef Thread     Self;

    /*==========================  PUBLIC  =================================*/

  public :

    typedef      MPThreadType Type;

    OSG_GEN_INTERNAL_MEMOBJPTR(Thread);

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32      getCurrentAspect           (      void             );
    static ChangeList *getCurrentChangeList       (      void             );

    static BitVector   getCurrentNamespaceMask    (      void             );
    static void        setCurrentNamespaceMask    (      BitVector  bMask );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    static void      setCurrentLocalFlags  (BitVector  bFlags = FCLocal::All);
    static void      resetCurrentLocalFlags(void                            );
    static BitVector getCurrentLocalFlags  (void                            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    static ThreadBase    *getCurrent(      void              );


    static ObjTransitPtr  get       (const Char8     *szName,
                                           bool       bGlobal);
    static Thread        *find      (const Char8     *szName );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    void run        (UInt32       uiAspectId);

    bool runFunction(ThreadFuncF  fThreadFunc, 
                     UInt32       uiAspectId,
                     void        *pThreadArg);

    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
    static void setAspectTo    (UInt32      uiNewAspect);
    static void setChangelistTo(ChangeList *pNewList   );
#endif

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static MPThreadType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static Thread *create            (const Char8 *szName, 
                                            UInt32 uiId,
                                            bool   bGlobal = false);

    static void    initThreading     (      void                      );
    static void    terminateThreading(      void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Thread(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Thread(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    Thread(const Thread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Thread &source);
};

OSG_GEN_MEMOBJPTR(Thread);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING ExternalThread : public ThreadBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    typedef MPThreadType Type;

    OSG_GEN_INTERNAL_MEMOBJPTR(ExternalThread);

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static ObjTransitPtr   get (const Char8 *szName,
                                      bool   bGlobal);
    static ExternalThread *find(const Char8 *szName );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void initialize(UInt32 uiAspectId);
    void shutdown  (void             );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static MPThreadType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static ExternalThread *create(const Char8 *szName, 
                                        UInt32 uiId,
                                        bool   bGlobal = false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ExternalThread(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ExternalThread(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ExternalThread(const ExternalThread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ExternalThread &source);
};

OSG_GEN_MEMOBJPTR(ExternalThread);

OSG_END_NAMESPACE

#include "OSGThread.inl"

#endif /* _OSGTHREAD_H_ */
