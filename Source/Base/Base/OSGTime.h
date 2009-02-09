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

#ifndef _OSGTIME_H_
#define _OSGTIME_H_
#ifdef __sgi
#pragma once
#endif

#ifndef WIN32
#include <sys/time.h>
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseBaseTypes
 *  \brief OSGTime
 *
 *   Time supplies two time measurement methods.
 *   
 *   The first is the system time (getSystemTime()). It is measured in
 *   seconds and started at an unspecified start point, so it's only
 *   useful for relative measurements. It has limited resolution (~20 ms on
 *   Windows, better on Linux), but will not wrap around in a reasonable
 *   timeframe.
 *
 *   The second is the time stamp (getTimeStamp()). It is measured in an
 *   unspecified integer unit, but the number of time stamp ticks per second
 *   can be inquired via getTimeStampFreq(), or a number of TimeStamp ticks
 *   can be converted to milliseconds using getTimeStampMsecs(). It has at
 *   least the same resolution as the system time, but can be much higher. 
 *   Currently it is only higher on Intel/AMD CPUs. It can be used to measure
 *   very short time periods, but should not be used for long measurements.
 *
 */
typedef Real64 Time;

/*! \ingroup GrpBaseBaseBaseTypes
 */
typedef Int64  TimeStamp;

/*---------------------------------------------------------------------*/
/*! \name Time functions                                               */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Time getSystemTime        (void                 );

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::TimeStamp getTimeStamp    (void                 );

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::TimeStamp getTimeStampFreq(void                 );

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real64    getTimeStampMsecs(OSG::TimeStamp ticks);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGTime.inl"

#endif /* _OSGTIME_H_ */
