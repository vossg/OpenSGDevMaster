/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGRENDERINGBACKENDFWD_H_
#define _OSGRENDERINGBACKENDFWD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGMultiPool.h"

OSG_BEGIN_NAMESPACE


class  PoolDefaultTag;
class  NoLockPolicy;
class  RenderTreeNode;
class  StateOverride;
class  TreeBuilderBase;
class  RenderAction;
class  RenderPartitionBase;
struct NoRefCountPolicy;

/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef MultiPool< NoRefCountPolicy,
                   NoLockPolicy     >  RenderTreeNodePool;

/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef SimplePool<StateOverride,
                   PoolDefaultTag,
                   NoRefCountPolicy,
                   NoLockPolicy     >  StateOverridePool;

/*! \ingroup GrpSystemRenderingBackendPools
 */

typedef MultiPool< NoRefCountPolicy,
                   NoLockPolicy     >  TreeBuilderPool;

OSG_END_NAMESPACE

#endif /* _OSGRENDERINGBACKENDFWDDEF_H_ */
