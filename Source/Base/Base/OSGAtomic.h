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

#ifndef _OSGATOMIC_H_
#define _OSGATOMIC_H_


#include "OSGBaseTypes.h"

#ifdef WIN32
#include <boost/detail/interlocked.hpp>

// boost before 1.34.0 does not have BOOST_INTERLOCKED_EXCHANGE_ADD
#ifndef BOOST_INTERLOCKED_EXCHANGE_ADD
#define BOOST_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd
#endif

#else
#include <boost/detail/sp_counted_base.hpp>
#endif

OSG_BEGIN_NAMESPACE

#if !defined(WIN32)

inline 
RefCountStore osgAtomicExchangeAndAdd(RefCountStore *pValue, 
                                      RefCountStore  rcDelta)
{
#if 0
    RefCountStore ret = *pValue;
    
    *pValue += rcDelta;
    
    return ret;
#endif

    return boost::detail::atomic_exchange_and_add(pValue, rcDelta);
}

inline 
void osgAtomicIncrement(RefCountStore *pValue)
{
#if 0
    ++(*pValue);
#endif

    boost::detail::atomic_increment(pValue);
}

inline 
void osgAtomicDecrement(RefCountStore *pValue)
{
#if 0
    --(*pValue);
#endif

    __asm__
    (
        "lock\n\t"
        "decl %0":
        "=m"( *pValue ): // output (%0)
        "m"( *pValue ): // input (%1)
        "cc" // clobbers
    );
}

inline
void osgSpinLock(UInt32 *pLock, UInt32 uiMask)
{
    //while(__sync_xor_and_fetch(pLock, 0x80000000) != 0x80000000);

    UInt32 uiRef = 
        (static_cast<UInt32 const volatile &>(*pLock) | uiMask);

    while(__sync_xor_and_fetch(pLock, uiMask) != uiRef);
}

inline
void osgSpinLockRelease(UInt32 *pLock, UInt32 uiInvMask)
{
    __sync_fetch_and_and(pLock, uiInvMask);
}

#else

inline 
RefCountStore osgAtomicExchangeAndAdd(RefCountStore *pValue, 
                                      RefCountStore  rcDelta)
{
#if 0
    RefCountStore ret = *pValue;
    
    *pValue += rcDelta;
    
    return ret;
#endif

    return BOOST_INTERLOCKED_EXCHANGE_ADD(pValue, rcDelta);
}

inline 
void osgAtomicIncrement(RefCountStore *pValue)
{
#if 0
    ++(*pValue);
#endif
    
    BOOST_INTERLOCKED_INCREMENT(pValue);
}

inline 
void osgAtomicDecrement(RefCountStore *pValue)
{
#if 0
    ++(*pValue);
#endif
    
    BOOST_INTERLOCKED_DECREMENT(pValue);
}

inline
void osgSpinLock(UInt32 *pLock, UInt32 uiMask)
{
/*
    UInt32 uiRef = 
        (static_cast<UInt32 const volatile &>(*pLock) | uiMask);

    while(__sync_xor_and_fetch(pLock, uiMask) != uiRef);
 */
}

inline
void osgSpinLockRelease(UInt32 *pLock, UInt32 uiInvMask)
{
//    __sync_fetch_and_and(pLock, uiInvMask);
}

#endif

OSG_END_NAMESPACE

#endif // _OSGATOMIC_H_
