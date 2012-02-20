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

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline 
RefCountStore osgAtomicExchangeAndAdd(RefCountStore *pValue, 
                                      RefCountStore  rcDelta)
{
    return boost::detail::atomic_exchange_and_add(pValue, rcDelta);
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline 
void osgAtomicIncrement(RefCountStore *pValue)
{
    boost::detail::atomic_increment(pValue);
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline 
void osgAtomicDecrement(RefCountStore *pValue)
{
    __asm__
    (
        "lock\n\t"
        "decl %0":
        "=m"( *pValue ): // output (%0)
        "m"( *pValue ): // input (%1)
        "cc" // clobbers
    );
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline
void osgSpinLock(UInt32 *pLock, UInt32 uiMask)
{
#if __GNUC__ >= 4 && __GNUC_MINOR__ >=2
    for(UInt32 tmpVal = __sync_fetch_and_or(pLock, uiMask); 
        (tmpVal & uiMask) != 0x0000; 
        tmpVal = __sync_fetch_and_or(pLock, uiMask)) ;
#endif
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline
void osgSpinLockRelease(UInt32 *pLock, UInt32 uiInvMask)
{
#if __GNUC__ >= 4 && __GNUC_MINOR__ >=2
    __sync_and_and_fetch(pLock, uiInvMask);
#endif
}

#else // !defined(WIN32)

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline 
RefCountStore osgAtomicExchangeAndAdd(RefCountStore *pValue, 
                                      RefCountStore  rcDelta)
{
    return _InterlockedExchangeAdd(pValue, rcDelta);
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline 
void osgAtomicIncrement(RefCountStore *pValue)
{
    _InterlockedIncrement(pValue);
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline 
void osgAtomicDecrement(RefCountStore *pValue)
{
    _InterlockedDecrement(pValue);
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline
void osgSpinLock(UInt32 *pLock, UInt32 uiMask)
{
    for(UInt32 tmpVal = _InterlockedOr((long *) pLock, uiMask); 
        (tmpVal & uiMask) != 0x0000; 
        tmpVal = _InterlockedOr((long *) pLock, uiMask));
}

/*! \ingroup GrpBaseBaseAtomicFn
 */

inline
void osgSpinLockRelease(UInt32 *pLock, UInt32 uiInvMask)
{
    _InterlockedAnd((long *) pLock, uiInvMask);
}

#endif

OSG_END_NAMESPACE

#endif // _OSGATOMIC_H_
