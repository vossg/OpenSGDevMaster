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

OSG_END_NAMESPACE


