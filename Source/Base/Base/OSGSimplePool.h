/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGSIMPLEPOOL_H_
#define _OSGSIMPLEPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLockPolicies.h"
#include "OSGBaseRefCountPoliciesFwd.h"

#include <iosfwd>
#include <vector>

OSG_BEGIN_NAMESPACE

class PoolDefaultTag;

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

class OSG_BASE_DLLMAPPING SimplePoolBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name            Constructors, Destructor                          */
    /*! \{                                                                 */

             SimplePoolBase(void);
    virtual ~SimplePoolBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Free                                   */
    /*! \{                                                                 */

    void freeAll(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       stat                                   */
    /*! \{                                                                 */

    void printStat(std::ostream &os);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    UInt32 _nextFreeElement;
    UInt32 _numAllocated;
    UInt32 _numReused;

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SimplePoolBase(const SimplePoolBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator=(const SimplePoolBase &source);
};

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

template <class ValueTypeT,
          class PoolTagT        = PoolDefaultTag,
          class RefCountPolicyT = NoRefCountPolicy,
          class LockPolicyT     = NoLockPolicy    >
class SimplePool : public SimplePoolBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef SimplePoolBase   Inherited;
    typedef ValueTypeT       ValueType;
    typedef RefCountPolicyT  RefCountPolicy;
    typedef LockPolicyT      LockPolicy;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimplePool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SimplePool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Create                                    */
    /*! \{                                                                 */

    ValueType *create(void);

    template<class Param0T>
    ValueType *create(Param0T param0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Destroy                                  */
    /*! \{                                                                 */

    void destroyAll(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef          std::vector<ValueType *>  ValueStore;
    typedef typename ValueStore::iterator      ValueStoreIt;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    ValueStore _values;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SimplePool(const SimplePool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SimplePool &source);
};

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

template<class PoolTagT, class LockPolicyT>
class SimplePool<Int32, PoolTagT, LockPolicyT> : public SimplePoolBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef SimplePoolBase    Inherited;
    typedef Int32             ValueType;
    typedef NoRefCountPolicy  RefCountPolicy;
    typedef LockPolicyT       LockPolicy;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimplePool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SimplePool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      create                                  */
    /*! \{                                                                 */

    Int32 create (void       );
    void  release(Int32 uiVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       free                                   */
    /*! \{                                                                 */

//    void freeAll(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       stat                                   */
    /*! \{                                                                 */

    void printStat(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    void initializeValue(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    volatile Int32 _currentValue;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    SimplePool(const SimplePool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SimplePool &source);
};

OSG_END_NAMESPACE

#include "OSGSimplePool.inl"

#endif /* _OSGSIMPLEPOOL_H_ */
