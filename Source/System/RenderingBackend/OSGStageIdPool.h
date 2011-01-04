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

#ifndef _OSGSTAGEIDPOOL_H_
#define _OSGSTAGEIDPOOL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTaggedSingletonHolder.h"
#include "OSGSimpleReusePool.h"

OSG_BEGIN_NAMESPACE

struct StageIdPoolTag;

/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef SimpleReusePool<Int32, 
                        StageIdPoolTag, 
                        SingleLockPolicy> StageIdPoolBase;

template<> inline
void SimpleReusePool<Int32, 
                     StageIdPoolTag, 
                     SingleLockPolicy  >::initializeValue(void)
{
    _currentValue = 0;
}

/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef TaggedSingletonHolder<StageIdPoolBase, 
                              StageIdPoolTag > StageIdPool;

OSG_END_NAMESPACE

#endif /* _OSGSTAGEIDPOOL_H_ */
