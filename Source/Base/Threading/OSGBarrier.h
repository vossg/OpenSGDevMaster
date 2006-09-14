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

#ifndef _OSGBARRIER_H_
#define _OSGBARRIER_H_
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
#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)
#include <ulocks.h>
#endif /* OSG_USE_SPROC */

OSG_BEGIN_NAMESPACE

template <class MPFieldT>
class MPFieldStore;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING BarrierCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MPBase Inherited;

             UInt32  _uiBarrierId;
    volatile UInt32  _uiNumWaitFor;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BarrierCommonBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~BarrierCommonBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setNumWaitFor(UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    BarrierCommonBase(const BarrierCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BarrierCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_PTHREADS)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class PThreadBarrierBase : public BarrierCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BarrierCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadBarrierBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadBarrierBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    bool init    (       void        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void shutdown(       void        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Enter                                    */
    /*! \{                                                                 */

    void enter   (void               );
    void enter   (UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    pthread_mutex_t _pLockOne;
    pthread_cond_t  _pWakeupCondition[2];
    UInt32          _uiCount;
    UInt32          _uiCurrentCond;

    /*!\brief prohibit default function (move to 'public' if needed) */
    PThreadBarrierBase(const PThreadBarrierBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PThreadBarrierBase &source);
};

typedef PThreadBarrierBase BarrierBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_SPROC)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class SprocBarrierBase : public BarrierCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BarrierCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocBarrierBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocBarrierBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    bool init    (void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void shutdown(void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Enter                                   */
    /*! \{                                                                 */

    void enter   (void               );
    void enter   (UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    barrier_t *_pBarrier;

    /*!\brief prohibit default function (move to 'public' if needed) */
    SprocBarrierBase(const SprocBarrierBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SprocBarrierBase &source);
};

typedef SprocBarrierBase BarrierBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_WINTHREADS)

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING WinThreadBarrierBase : public BarrierCommonBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadBarrierBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WinThreadBarrierBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    bool init    (void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void shutdown(void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Enter                                   */
    /*! \{                                                                 */

    void enter   (void               );
    void enter   (UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef BarrierCommonBase Inherited;

             Handle _pMutex1;
             Handle _pBarrierSema;
    volatile UInt32 _uiNumWaiters;

    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadBarrierBase(const WinThreadBarrierBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadBarrierBase &source);
};

typedef WinThreadBarrierBase BarrierBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMultiThreading
 */

class OSG_BASE_DLLMAPPING Barrier : public BarrierBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MPBarrierType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static       Barrier       *get         (const Char8 *szName);
    static       Barrier       *find        (const Char8 *szName);

    static       Barrier       *create      (      void         );

    static const MPBarrierType &getClassType(      void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Enter                                   */
    /*! \{                                                                 */
    
    void setNumWaitFor(UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Enter                                   */
    /*! \{                                                                 */

    void enter(void               );
    void enter(UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef BarrierBase Inherited;

    static MPBarrierType _type;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Barrier(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Barrier(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static Barrier *create(const Char8  *szName,
                                 UInt32  uiId);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class MPFieldStore<Barrier>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    Barrier(const Barrier &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Barrier &source);
};

OSG_END_NAMESPACE

#define OSGBARRIER_HEADER_CVSID "@(#)$Id$"

#include "OSGBarrier.inl"

#endif /* _OSGBARRIER_H_ */
