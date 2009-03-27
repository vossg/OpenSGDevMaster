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

template <class PoolTag, class LockPolicy> inline
void SimplePool<Int32, PoolTag, LockPolicy>::release(Int32)
{
}

    
template <class PoolTag, class LockPolicy> inline
void SimplePool<Int32, PoolTag, LockPolicy>::printStat(void)
{
    fprintf(stderr, "\n%d\n", _currentValue());
}

template <class ValueT, 
          class PoolTag, 
          class RefCountPolicy, 
          class LockPolicy> inline
ValueT *SimplePool<ValueT, PoolTag, RefCountPolicy, LockPolicy>::create(void)
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

        RefCountPolicy::addRef(returnValue);

        _elementStore.push_back(returnValue);

        _currentFreeElement = _elementStore.end();

        ++_uiAllocated;
    }
    
    return returnValue;
}

template <class ValueT, 
          class PoolTag, 
          class RefCountPolicy, 
          class LockPolicy>
template<class ParameterT> inline
ValueT *SimplePool<ValueT, 
                   PoolTag, 
                   RefCountPolicy, 
                   LockPolicy    >::create(ParameterT oParam)
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

        RefCountPolicy::addRef(returnValue);

        _elementStore.push_back(returnValue);

        _currentFreeElement = _elementStore.end();

        ++_uiAllocated;
    }
    
    return returnValue;
}

template <class ValueT, 
          class PoolTag, 
          class RefCountPolicy, 
          class LockPolicy> inline
void SimplePool<ValueT, PoolTag, RefCountPolicy, LockPolicy>::freeAll(void)
{
    _currentFreeElement = _elementStore.begin();

    _uiAllocated = 0;
    _uiReused    = 0;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueT, 
          class PoolTag, 
          class RefCountPolicy, 
          class LockPolicy> inline
SimplePool<ValueT, PoolTag, RefCountPolicy, LockPolicy>::SimplePool(void) :
    _elementStore      ( ),
    _currentFreeElement( ),
    _uiAllocated       (0),
    _uiReused          (0)
{
    _currentFreeElement = _elementStore.end();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueT, 
          class PoolTag, 
          class RefCountPolicy, 
          class LockPolicy> inline
SimplePool<ValueT, PoolTag, RefCountPolicy, LockPolicy>::~SimplePool(void)
{
    for(UInt32 i = 0; i < _elementStore.size(); ++i)
    {
        RefCountPolicy::subRef(_elementStore[i]);
//        delete _elementStore[i];
    }
}

template <class ValueT, 
          class PoolTag, 
          class RefCountPolicy, 
          class LockPolicy> inline
void SimplePool<ValueT, PoolTag, RefCountPolicy, LockPolicy>::printStat(void)
{
    fprintf(stderr, "\n%d | %d | %d\n", 
            _uiAllocated, 
            _uiReused, 
            _elementStore.size());
}

OSG_END_NAMESPACE
