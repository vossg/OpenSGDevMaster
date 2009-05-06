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

#if !defined(WIN32)
#include <boost/version.hpp>

#if BOOST_VERSION < 103900
#include <boost/detail/sp_counted_base.hpp>
#else
#include <boost/smart_ptr/detail/sp_counted_base.hpp>
#endif

#else
#pragma intrinsic( _InterlockedExchangeAdd )
#pragma intrinsic( _InterlockedIncrement )
#pragma intrinsic( _InterlockedDecrement )
#pragma intrinsic( _InterlockedAnd )
#pragma intrinsic( _InterlockedOr )
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
#if __GNUC__ >= 4 && __GNUC_MINOR__ >=2
    for(UInt32 tmpVal = __sync_fetch_and_or(pLock, uiMask); 
        (tmpVal & uiMask) != 0x0000; 
        tmpVal = __sync_fetch_and_or(pLock, uiMask));
#endif
}

inline
void osgSpinLockRelease(UInt32 *pLock, UInt32 uiInvMask)
{
#if __GNUC__ >= 4 && __GNUC_MINOR__ >=2
    __sync_fetch_and_and(pLock, uiInvMask);
#endif
}

#else // !defined(WIN32)

inline 
RefCountStore osgAtomicExchangeAndAdd(RefCountStore *pValue, 
                                      RefCountStore  rcDelta)
{
#if 0
    RefCountStore ret = *pValue;
    
    *pValue += rcDelta;
    
    return ret;
#endif

    return _InterlockedExchangeAdd(pValue, rcDelta);
}

inline 
void osgAtomicIncrement(RefCountStore *pValue)
{
#if 0
    ++(*pValue);
#endif
    
    _InterlockedIncrement(pValue);
}

inline 
void osgAtomicDecrement(RefCountStore *pValue)
{
#if 0
    ++(*pValue);
#endif
    
    _InterlockedDecrement(pValue);
}

inline
void osgSpinLock(UInt32 *pLock, UInt32 uiMask)
{
    for(UInt32 tmpVal = _InterlockedOr((long *) pLock, uiMask); 
        (tmpVal & uiMask) != 0x0000; 
        tmpVal = _InterlockedOr((long *) pLock, uiMask));
}

inline
void osgSpinLockRelease(UInt32 *pLock, UInt32 uiInvMask)
{
    _InterlockedAnd((long *) pLock, uiInvMask);
}

#endif

OSG_END_NAMESPACE

#endif // _OSGATOMIC_H_
