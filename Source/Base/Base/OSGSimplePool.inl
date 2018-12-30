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

template <class PoolTag, class LockPolicy> inline
SimplePool<Int32, PoolTag, LockPolicy>::SimplePool(void) :
    Inherited    ( ),
    _currentValue(0)
{
    initializeValue();
}

template <class PoolTag, class LockPolicy> inline
SimplePool<Int32, PoolTag, LockPolicy>::~SimplePool(void)
{
}

template <class PoolTag, class LockPolicy> inline
Int32 SimplePool<Int32, PoolTag, LockPolicy>::create(void)
{
    Int32 returnValue = _currentValue;

    ++_currentValue;

    return returnValue;
}

#ifndef OSG_DOXYGEN_IGNORE_RECOG_PROBS
template <class PoolTag, class LockPolicy> inline
void SimplePool<Int32, PoolTag, LockPolicy>::release(Int32 uiVal)
{
}


template <class PoolTag, class LockPolicy> inline
void SimplePool<Int32, PoolTag, LockPolicy>::printStat(void)
{
    fprintf(stderr, "\n%d\n", _currentValue);
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT,
          class PoolTagT,
          class RefCountPolicyT,
          class LockPolicyT     >
SimplePool<ValueTypeT,      PoolTagT,
           RefCountPolicyT, LockPolicyT>::SimplePool(void) :
    Inherited(),
    _values  ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT,
          class PoolTagT,
          class RefCountPolicyT,
          class LockPolicyT     >
SimplePool<ValueTypeT,      PoolTagT,
           RefCountPolicyT, LockPolicyT>::~SimplePool(void)
{
    destroyAll();
}

/*-------------------------------------------------------------------------*/
/*                                Create                                   */

template <class ValueTypeT,
          class PoolTagT,
          class RefCountPolicyT,
          class LockPolicyT     >
inline
typename SimplePool<ValueTypeT,      PoolTagT,
                    RefCountPolicyT, LockPolicyT>::ValueType *
SimplePool<ValueTypeT,      PoolTagT,
           RefCountPolicyT, LockPolicyT>::create(void)
{
    ValueType *retVal = NULL;

    if(_nextFreeElement < _values.size())
    {
        retVal = _values[_nextFreeElement];
        retVal->reset();

        ++_nextFreeElement;
        ++_numReused;
    }
    else
    {
        retVal = new ValueType();
        RefCountPolicy::addRef(retVal);

        _values.push_back(retVal);

        _nextFreeElement = UInt32(_values.size());
        ++_numAllocated;
    }

    return retVal;
}

template <class ValueTypeT,
          class PoolTagT,
          class RefCountPolicyT,
          class LockPolicyT     >
template <class Param0T         >
inline
typename SimplePool<ValueTypeT,      PoolTagT,
                    RefCountPolicyT, LockPolicyT>::ValueType *
SimplePool<ValueTypeT,      PoolTagT,
           RefCountPolicyT, LockPolicyT>::create(Param0T param0)
{
    ValueType *retVal = NULL;

    if(_nextFreeElement < _values.size())
    {
        retVal = _values[_nextFreeElement];
        retVal->reset(param0);

        ++_nextFreeElement;
        ++_numReused;
    }
    else
    {
        retVal = new ValueType(param0);
        RefCountPolicy::addRef(retVal);

        _values.push_back(retVal);

        _nextFreeElement = UInt32(_values.size());
        ++_numAllocated;
    }

    return retVal;
}

template <class ValueTypeT,
          class PoolTagT,
          class RefCountPolicyT,
          class LockPolicyT     >
void
SimplePool<ValueTypeT,      PoolTagT,
           RefCountPolicyT, LockPolicyT>::destroyAll(void)
{
    ValueStoreIt vIt  = _values.begin();
    ValueStoreIt vEnd = _values.end  ();

    if(RefCountPolicy::NotCounting == true)
    {
        for(; vIt != vEnd; ++vIt)
        {
            delete *vIt;
        }
    }
    else
    {
        for(; vIt != vEnd; ++vIt)
        {
            RefCountPolicy::subRef(*vIt);
        }
    }

    _values.clear();
}

OSG_END_NAMESPACE
