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

#ifndef _OSGMULTIPOOL_H_
#define _OSGMULTIPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSimplePool.h"

#include <vector>
#include <map>
#include <typeinfo>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBasePools
    \ingroup GrpBaseBase
    \ingroup GrpLibOSGBase
    \nohierarchy
    \brief Pool that can store different types.
 */

template <class RefCountPolicyT = NoRefCountPolicy,
          class LockPolicyT     = NoLockPolicy     >
class MultiPool
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef RefCountPolicyT   RefCountPolicy;
    typedef LockPolicyT       LockPolicy;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Constructors, Destructor                         */
    /*! \{                                                                 */

     MultiPool(void);
    ~MultiPool(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Register                                 */
    /*! \{                                                                 */

    template <class ValueTypeT>
    UInt32 registerType(void);

    template <class ValueTypeT>
    void unregisterType(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Create                                  */
    /*! \{                                                                 */

    template <class ValueTypeT>
    ValueTypeT *create (void);

    template <class ValueTypeT>
    ValueTypeT *create (UInt32 typeIdx);

    void        freeAll(void);


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    /*! \nohierarchy
     */

    struct TypeInfoCmp
    {
        bool operator()(const std::type_info* lhs,
                        const std::type_info* rhs) const;
    };

    typedef          std::map   <const std::type_info *, UInt32,
                                 TypeInfoCmp                   > TypeIdxMap;
    typedef typename TypeIdxMap::iterator                        TypeIdxMapIt;

    typedef          std::vector<SimplePoolBase *              > PoolStore;
    typedef typename PoolStore::iterator                         PoolStoreIt;

    struct MultiPoolTag;

    /*! \nohierarchy
     */

    template <class ValueTypeT>
    struct SimplePoolTypeBuilder
    {
        typedef SimplePool<ValueTypeT,
                           MultiPoolTag,
                           RefCountPolicyT,
                           LockPolicyT     > Type;
    };

    template <class ValueTypeT>
    typename SimplePoolTypeBuilder<
               ValueTypeT>::Type *getTypedPool(UInt32 poolIdx);

    TypeIdxMap _typeIdxMap;
    PoolStore  _pools;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    MultiPool(const MultiPool &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const MultiPool &source);
};

OSG_END_NAMESPACE

#include "OSGMultiPool.inl"

#endif /* _OSGMULTIPOOL_H_ */
