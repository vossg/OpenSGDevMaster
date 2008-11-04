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
SimpleReusePool<Int32, PoolTag, LockPolicy>::SimpleReusePool(void) :
    _currentValue   (0),
    _oLockPolicy    ( ),
    _vFreeValueStore( )
{
    initializeValue();
}

template <class PoolTag, class LockPolicy> inline
SimpleReusePool<Int32, PoolTag, LockPolicy>::~SimpleReusePool(void)
{
    
}

template <class PoolTag, class LockPolicy> inline
Int32 SimpleReusePool<Int32, PoolTag, LockPolicy>::create(void)
{
    _oLockPolicy.acquire();

    Int32 returnValue = 0;

    if(_vFreeValueStore.empty() == true)
    {
        returnValue = _currentValue;

        ++_currentValue;

    }
    else
    {
        returnValue = _vFreeValueStore.back();

        _vFreeValueStore.pop_back();
    }

    _oLockPolicy.release();

    return returnValue;
}

template <class PoolTag, class LockPolicy> inline
void SimpleReusePool<Int32, PoolTag, LockPolicy>::release(Int32 iVal)
{
    _oLockPolicy.acquire();

    _vFreeValueStore.push_back(iVal);

    _oLockPolicy.release();
}

    
template <class PoolTag, class LockPolicy> inline
void SimpleReusePool<Int32, PoolTag, LockPolicy>::dumpState(void)
{
    fprintf(stderr, "SimpleReusePool<Int32>::dumpState\n");
    fprintf(stderr, "    cv            : %d\n", _currentValue);
    fprintf(stderr, "    cached values : \n");

    std::deque<Int32>::const_iterator vIt  = _vFreeValueStore.begin();
    std::deque<Int32>::const_iterator vEnd = _vFreeValueStore.end  ();

    for(; vIt != vEnd; ++vIt)
        fprintf(stderr, "        %d\n", *vIt);
}


#if 0

template <class ValueT, class PoolTag, class LockPolicy> inline
ValueT *SimplePool<ValueT, PoolTag, LockPolicy>::create(void)
{
    ValueT *returnValue = NULL;

    if(_currentFreeElement != _elementStore.end())
    {
        returnValue = *_currentFreeElement;

        ++_currentFreeElement;

        returnValue->reset();

        ++_uiReused;
    }
    else
    {
        returnValue = new ValueT();

        _elementStore.push_back(returnValue);

        _currentFreeElement = _elementStore.end();

        ++_uiAllocated;
    }
    
    return returnValue;
}

template <class ValueT, class PoolTag, class LockPolicy> 
template<class ParameterT> inline
ValueT *SimplePool<ValueT, PoolTag, LockPolicy>::create(ParameterT oParam)
{
    ValueT *returnValue = NULL;

    if(_currentFreeElement != _elementStore.end())
    {
        returnValue = *_currentFreeElement;

        ++_currentFreeElement;

        returnValue->reset(oParam);

        ++_uiReused;
    }
    else
    {
        returnValue = new ValueT(oParam);

        _elementStore.push_back(returnValue);

        _currentFreeElement = _elementStore.end();

        ++_uiAllocated;
    }
    
    return returnValue;
}

template <class ValueT, class PoolTag, class LockPolicy> inline
void SimplePool<ValueT, PoolTag, LockPolicy>::freeAll(void)
{
    _currentFreeElement = _elementStore.begin();

    _uiAllocated = 0;
    _uiReused    = 0;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueT, class PoolTag, class LockPolicy> inline
SimplePool<ValueT, PoolTag, LockPolicy>::SimplePool(void) :
    _elementStore      ( ),
    _currentFreeElement( ),
    _uiAllocated       (0),
    _uiReused          (0)
{
    _currentFreeElement = _elementStore.end();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueT, class PoolTag, class LockPolicy> inline
SimplePool<ValueT, PoolTag, LockPolicy>::~SimplePool(void)
{
    for(UInt32 i = 0; i < _elementStore.size(); ++i)
    {
        delete _elementStore[i];
    }
}

template <class ValueT, class PoolTag, class LockPolicy> inline
void SimplePool<ValueT, PoolTag, LockPolicy>::printStat(void)
{
    fprintf(stderr, "\n%d | %d | %d\n", 
            _uiAllocated, 
            _uiReused, 
            _elementStore.size());
}

#endif

OSG_END_NAMESPACE


