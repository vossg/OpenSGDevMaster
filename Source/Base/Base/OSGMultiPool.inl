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

OSG_BEGIN_NAMESPACE

/*! \class MultiPool

MultiPool is a pool class that can handle multiple, different types of
elements. It is useful for managing a pool where it's not clear which of
a variety of types might be used. Other than that it is very similar to
SimplePool.

Internally there is a SimplePool for each type that is to be allocated from
the MultiPool and a map from std::type_info* to an index indentifying the
pool for each type.
To achieve highest performance types should be registered with registerType()
first before creating objects of that type. The return value of registerType()
should then be passed to create() to avoid looking up the correct pool for
the given type.

It is possible to make multiple calls to registerType() with the same type
argument, all calls return the same pool index. The first call to
unregisterType() will destroy (not only free) all objects of the given type.

*/

template <class RefCountPolicyT,
          class LockPolicyT     >
inline bool
MultiPool<RefCountPolicyT, LockPolicyT>::TypeInfoCmp::operator()(
    const std::type_info *lhs, const std::type_info *rhs) const
{
    return lhs->before(*rhs);
}


template <class RefCountPolicyT,
          class LockPolicyT     >
MultiPool<RefCountPolicyT, LockPolicyT>::MultiPool(void)
  : _typeIdxMap()
  , _pools     ()
{
}

template <class RefCountPolicyT,
          class LockPolicyT     >
MultiPool<RefCountPolicyT, LockPolicyT>::~MultiPool(void)
{
    PoolStoreIt pIt  = _pools.begin();
    PoolStoreIt pEnd = _pools.end  ();
    
    for(; pIt != pEnd; ++pIt)
    {
        delete (*pIt);
    }
}

template <class RefCountPolicyT,
          class LockPolicyT     >
template <class ValueTypeT      >
UInt32
MultiPool<RefCountPolicyT, LockPolicyT>::registerType(void)
{
    typedef typename SimplePoolTypeBuilder<ValueTypeT>::Type SimplePoolType;

    UInt32       retVal = _pools.size();
    TypeIdxMapIt tIt    = _typeIdxMap.find(&typeid(ValueTypeT));

    if(tIt != _typeIdxMap.end())
    {
        retVal = (*tIt).second;
    }
    else
    {
        _pools     .push_back(new SimplePoolType);
        _typeIdxMap.insert   (
            typename TypeIdxMap::value_type(&typeid(ValueTypeT),
                                            retVal             ));
    }

    return retVal;
}

template <class RefCountPolicyT,
          class LockPolicyT     >
template <class ValueTypeT      >
void
MultiPool<RefCountPolicyT, LockPolicyT>::unregisterType(void)
{
    typedef typename SimplePoolTypeBuilder<ValueTypeT>::Type SimplePoolType;

    TypeIdxMapIt tIt = _typeIdxMap.find(&typeid(ValueTypeT));

    if(tIt != _typeIdxMap.end())
    {
        SimplePoolType *pool = getTypedPool<ValueTypeT>((*tIt).second);

        pool->destroyAll();

        _pools[(*tIt).second] = NULL;
        _typeIdxMap.erase(tIt);

        delete pool;
    }
}

template <class RefCountPolicyT,
          class LockPolicyT     >
template <class ValueTypeT      >
inline ValueTypeT *
MultiPool<RefCountPolicyT, LockPolicyT>::create(void)
{
    typedef typename SimplePoolTypeBuilder<ValueTypeT>::Type SimplePoolType;

    UInt32          poolIdx = registerType<ValueTypeT>();
    SimplePoolType *pool    = getTypedPool<ValueTypeT>(poolIdx);

    return pool->create();
}

template <class RefCountPolicyT,
          class LockPolicyT     >
template <class ValueTypeT      >
inline ValueTypeT *
MultiPool<RefCountPolicyT, LockPolicyT>::create(UInt32 poolIdx)
{
    typedef typename SimplePoolTypeBuilder<ValueTypeT>::Type SimplePoolType;

    SimplePoolType *pool = getTypedPool<ValueTypeT>(poolIdx);

    return pool->create();
}

template <class RefCountPolicyT,
          class LockPolicyT     >
inline void
MultiPool<RefCountPolicyT, LockPolicyT>::freeAll(void)
{
    PoolStoreIt pIt  = _pools.begin();
    PoolStoreIt pEnd = _pools.end  ();
    
    for(; pIt != pEnd; ++pIt)
    {
        (*pIt)->freeAll();
    }
}

template <class RefCountPolicyT,
          class LockPolicyT     >
template <class ValueTypeT      >
inline
typename MultiPool<RefCountPolicyT,
                   LockPolicyT     >::template SimplePoolTypeBuilder<ValueTypeT>::Type *
MultiPool<RefCountPolicyT, LockPolicyT>::getTypedPool(UInt32 poolIdx)
{
    typedef typename SimplePoolTypeBuilder<ValueTypeT>::Type SimplePoolType;

    return dynamic_cast<SimplePoolType *>(_pools[poolIdx]);
}


OSG_END_NAMESPACE
