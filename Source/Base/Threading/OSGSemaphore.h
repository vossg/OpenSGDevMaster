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

#ifndef _OSGSEMAPHORE_H_
#define _OSGSEMAPHORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGMPBase.h"
#include "OSGRefCountPtr.h"

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined,  check your system/compiler combination"
#endif

#if defined (OSG_USE_PTHREADS)
#include <semaphore.h>
#include <cerrno>
#endif

#if defined (OSG_USE_SPROC)
#include <semaphore.h>
#endif

#include <boost/mpl/if.hpp>

OSG_BEGIN_NAMESPACE

template <class MPFieldT>
class MPFieldStore;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING SemaphoreCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPBase  Inherited;

            UInt32 _uiSemaphoreId;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SemaphoreCommonBase(void);
    SemaphoreCommonBase(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SemaphoreCommonBase(void); 
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SemaphoreCommonBase  (const SemaphoreCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const SemaphoreCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_PTHREADS)

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class PThreadSemaphoreBase : public SemaphoreCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SemaphoreCommonBase Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadSemaphoreBase(void);
    PThreadSemaphoreBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadSemaphoreBase(void); 

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
    /*! \name                   Semaphore                                  */
    /*! \{                                                                 */

    void wait(void);
    void post(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    
    sem_t _pLowLevelSemaphore;

    /*!\brief prohibit default function (move to 'public' if needed) */
    PThreadSemaphoreBase(const PThreadSemaphoreBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PThreadSemaphoreBase &source);
};

typedef PThreadSemaphoreBase SemaphoreBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_SPROC)

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class SprocSemaphoreBase : public SemaphoreCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SemaphoreCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocSemaphoreBase(void);
    SprocSemaphoreBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocSemaphoreBase(void); 

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
    /*! \name                    Semaphore                                 */
    /*! \{                                                                 */

    void wait(void);
    void post(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    usema_t *_pLowLevelSema;

    /*!\brief prohibit default function (move to 'public' if needed) */
    SprocSemaphoreBase(const SprocSemaphoreBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SprocSemaphoreBase &source);
};

typedef SprocSemaphoreBase SemaphoreBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_WINTHREADS)

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING WinThreadSemaphoreBase : public SemaphoreCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SemaphoreCommonBase Inherited;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadSemaphoreBase(void);
    WinThreadSemaphoreBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WinThreadSemaphoreBase(void); 

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
    /*! \name                     Semaphore                                */
    /*! \{                                                                 */

    void wait(void);
    void post(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    Handle  _pSemaphore;
  
    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadSemaphoreBase(const WinThreadSemaphoreBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadSemaphoreBase &source);
};

typedef WinThreadSemaphoreBase SemaphoreBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING Semaphore : public SemaphoreBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPSemaphoreType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static       Semaphore       *get         (const Char8 *szName);
    static       Semaphore       *find        (const Char8 *szName);

    static       Semaphore       *create      (      void         );

    static const MPSemaphoreType &getClassType(      void         ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Semaphore                                 */
    /*! \{                                                                 */

    void wait(void);
    void post(void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef SemaphoreBase    Inherited;

    static  MPSemaphoreType _type;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static Semaphore *create(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Semaphore(void);
    Semaphore(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Semaphore(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class MPFieldStore<Semaphore>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    Semaphore(const Semaphore &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Semaphore &source);
};

typedef RefCountPtr<Semaphore,
                    MemObjRefCountPolicy> SemaphoreRefPtr;




OSG_END_NAMESPACE

#include "OSGSemaphore.inl"

#endif /* _OSGSEMAPHORE_H_ */
