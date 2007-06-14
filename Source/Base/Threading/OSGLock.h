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

#ifndef _OSGLOCK_H_
#define _OSGLOCK_H_
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

static const UInt32 uiLockPoolSize = 32;

template <class MPFieldT>
class MPFieldStore;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING LockCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPBase  Inherited;

            UInt32 _uiLockId;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LockCommonBase(void);
    LockCommonBase(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~LockCommonBase(void); 
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    LockCommonBase  (const LockCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const LockCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_PTHREADS)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class PThreadLockBase : public LockCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef LockCommonBase Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadLockBase(void);
    PThreadLockBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadLockBase(void); 

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
    /*! \name                   Lock                                       */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    
    friend class LockPool;

    pthread_mutex_t _pLowLevelLock;

    /*!\brief prohibit default function (move to 'public' if needed) */
    PThreadLockBase(const PThreadLockBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PThreadLockBase &source);
};

typedef PThreadLockBase LockBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_SPROC)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class SprocLockBase : public LockCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef LockCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocLockBase(void);
    SprocLockBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocLockBase(void); 

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
    /*! \name                    Lock                                      */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class LockPool;

#define OSG_SPROC_USE_LOCK
#ifdef OSG_SPROC_USE_LOCK
    ulock_t  _pLowLevelLock;
#else
    usema_t *_pLowLevelSema;
#endif

    /*!\brief prohibit default function (move to 'public' if needed) */
    SprocLockBase(const SprocLockBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SprocLockBase &source);
};

typedef SprocLockBase LockBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_WINTHREADS)

#if _WIN32_WINNT < 0x0400
#define OSG_WINLOCK_USE_MUTEX
#endif

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING WinThreadLockBase : public LockCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef LockCommonBase Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadLockBase(void);
    WinThreadLockBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WinThreadLockBase(void); 

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
    /*! \name                       Lock                                   */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class LockPool;

#ifdef OSG_WINLOCK_USE_MUTEX
    Handle  _pMutex;
#else
    CRITICAL_SECTION _pCriticalSection;
#endif
  
    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadLockBase(const WinThreadLockBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadLockBase &source);
};

typedef WinThreadLockBase LockBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING Lock : public LockBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPLockType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static       Lock       *get         (const Char8 *szName);
    static       Lock       *find        (const Char8 *szName);

    static       Lock       *create      (      void         );

    static const MPLockType &getClassType(      void         ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Lock                                   */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef LockBase    Inherited;

    static  MPLockType _type;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static Lock *create(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Lock(void);
    Lock(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Lock(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class LockPool;
    friend class MPFieldStore<Lock>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    Lock(const Lock &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Lock &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING LockPool : public LockCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPLockPoolType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static       LockPool       *get         (const Char8 *szName);
    static       LockPool       *find        (const Char8 *szName);
    static       LockPool       *create      (      void         );
    static const MPLockPoolType &getClassType(      void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Lock                                       */
    /*! \{                                                                 */

    void acquire(void *keyP);
    void release(void *keyP);
    bool request(void *keyP);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef LockCommonBase  Inherited;

    static  MPLockPoolType _type;

            Lock           _pLocks    [uiLockPoolSize];

#ifdef OSG_DEBUG_LOCK_STAT
            UInt32         _pLockStats[uiLockPoolSize];
#endif

    struct ErrorCouldNotMatchSize {};

    typedef 
        boost::mpl::if_<boost::mpl::bool_<(sizeof(void *) == sizeof(UInt32))>,
                        UInt32,
                        ErrorCouldNotMatchSize>::type NumericalKeyType32;

    typedef 
        boost::mpl::if_<boost::mpl::bool_<(sizeof(void *) == sizeof(UInt64))>,
                        UInt64,
                        NumericalKeyType32>::type NumericalKeyType;
    
    /*---------------------------------------------------------------------*/
    /*! \name                      Create                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    static const NumericalKeyType uiLockPoolMask = 0x0f80;

    static LockPool *create(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    LockPool(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~LockPool(void);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    bool init(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void shutdown(void);
        
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class MPFieldStore<LockPool>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    LockPool(const LockPool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const LockPool &source);
};

OSG_END_NAMESPACE

#include "OSGLock.inl"

#endif /* _OSGLOCK_H_ */
