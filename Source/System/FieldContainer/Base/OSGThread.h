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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGThread.h
    \ingroup GrpSystemMultithreading
 */
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"

#ifndef OSG_WINCE

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

#endif

OSG_BEGIN_NAMESPACE

#ifndef OSG_WINCE

class Thread;
class ChangeList;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemMultithreading
 */

class OSG_SYSTEM_DLLMAPPING ThreadCommonBase : public BaseThread
{
    /*==========================  PUBLIC  =================================*/

  public :

    static const UInt32 InvalidAspect;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    UInt32      getAspect    (void);
    ChangeList *getChangeList(void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BaseThread Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32      _uiAspectId;
    ChangeList *_pChangeList;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ThreadCommonBase(      void                      );
    ThreadCommonBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ThreadCommonBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setAspect    (UInt32      uiAspectId);
    void setChangeList(ChangeList *pChangeList);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ThreadCommonBase(const ThreadCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

/*! \ingroup GrpSystemMultithreading
 */

class PThreadBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#if defined(OSG_PTHREAD_ELF_TLS)
    static __thread UInt32      _uiTLSAspectId;
    static __thread ChangeList *_pTLSChangeList;
#else
    static pthread_key_t  _aspectKey;
    static pthread_key_t  _changeListKey;
#endif

#if !defined(OSG_PTHREAD_ELF_TLS)
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Free                                     */
    /*! \{                                                                 */

    static void  freeAspect    (void *pAspect);
    static void  freeChangeList(void *pChangeList);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32       getCurrentAspect    (void);
    static ChangeList  *getCurrentChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadBase(const Char8 *szName, UInt32 uiId);

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

    static void setAspectTo(UInt32 uiNewAspect);

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

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

/*! \ingroup GrpSystemMultithreading
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

    SprocBase(const Char8 *szName, UInt32 uiId);

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

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

/*! \ingroup GrpSystemMultithreading
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
#else
    static __declspec (thread) UInt32      _uiAspectLocal;
    static __declspec (thread) ChangeList *_pChangeListLocal;
#endif

#ifdef OSG_WIN32_ASPECT_USE_LOCALSTORAGE
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Free                                   */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    static void freeAspect    (void);
    OSG_SYSTEM_DLLMAPPING 
    static void freeChangeList(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    static UInt32      getCurrentAspect    (void);
    OSG_SYSTEM_DLLMAPPING 
    static ChangeList *getCurrentChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    WinThreadBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual ~WinThreadBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    virtual void init            (void);

            OSG_SYSTEM_DLLMAPPING 
            void setupAspect     (void);
            OSG_SYSTEM_DLLMAPPING 
            void setupChangeList (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

    OSG_SYSTEM_DLLMAPPING 
    static void setAspectTo(UInt32 uiNewAspect);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadBase(const WinThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadBase &source);
};

typedef WinThreadBase ThreadBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemMultithreading
 */

class OSG_SYSTEM_DLLMAPPING Thread : public ThreadBase
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef ThreadBase Inherited;
    typedef Thread     Self;

    /*==========================  PUBLIC  =================================*/

  public :

    typedef      MPThreadType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32      getCurrentAspect    (      void         );
    static ChangeList *getCurrentChangeList(      void         );
    
    static Thread     *getCurrent          (      void         );


    static Thread     *get                 (const Char8 *szName);
    static Thread     *find                (const Char8 *szName);

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
    static void setAspectTo(UInt32 uiNewAspect);
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

    static Thread *create       (const Char8 *szName, UInt32 uiId);

    static void    initThreading(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Thread(const Char8 *szName, UInt32 uiId);

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



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemMultithreading
 */

class OSG_SYSTEM_DLLMAPPING ExternalThread : public ThreadBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    typedef MPThreadType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static ExternalThread *get       (const Char8 *szName);
    static ExternalThread *find      (const Char8 *szName);

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

    static ExternalThread *create       (const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ExternalThread(const Char8 *szName, UInt32 uiId);

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

#else /* OSG_WIN_CE */

class ChangeList;

class OSG_SYSTEM_DLLMAPPING Thread
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Thread     Self;

    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static ChangeList *getCurrentChangeList(void);

    static UInt32      getCurrentAspect    (void)
    {
        return 1;
    }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Debug                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Thread(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Thread(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    Thread(const Thread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Thread &source);
};
#endif /* OSG_WIN_CE  */

OSG_END_NAMESPACE

#ifndef OSG_WINCE
#include "OSGThread.inl"
#endif

#endif /* _OSGTHREAD_H_ */
