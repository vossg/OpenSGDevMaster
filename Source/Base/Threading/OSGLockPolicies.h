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

#ifndef _OSGLOCKPOLICIES_H_
#define _OSGLOCKPOLICIES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGBaseInitFunctions.h"

#include "OSGLock.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class NoLockPolicy
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    NoLockPolicy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NoLockPolicy(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    NoLockPolicy(const  NoLockPolicy &source);
    void operator =(const NoLockPolicy &source);
};


/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class SingleLockPolicy
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    SingleLockPolicy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SingleLockPolicy(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    LockRefPtr _pLock;

   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SingleLockPolicy(const  SingleLockPolicy &source);
    void operator =(const SingleLockPolicy &source);
};


/*! \ingroup GrpBaseMultiThreading
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class SingleStaticInitLockPolicy
{

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    SingleStaticInitLockPolicy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SingleStaticInitLockPolicy(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void acquire(void);
    void release(void);
    bool request(void);
 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    LockRefPtr _pLock;

    bool init    (void);
    bool shutdown(void);

   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SingleStaticInitLockPolicy(const  SingleStaticInitLockPolicy &source);
    void operator =(const SingleStaticInitLockPolicy &source);
};

OSG_END_NAMESPACE

#include "OSGLockPolicies.inl"

#endif /* _OSGLOCKPOLICIES_H_ */
