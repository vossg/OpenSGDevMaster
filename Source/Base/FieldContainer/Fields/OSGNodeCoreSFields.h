/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGNODECORESFIELDS_H_
#define _OSGNODECORESFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNodeCoreFieldTraits.h"
#include "OSGPointerSField.h"
#include "OSGChildPointerSField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField     <NodeCore *, 
                           RecordedRefCountPolicy  > SFRecNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField     <NodeCore *, 
                           UnrecordedRefCountPolicy> SFUnrecNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField     <NodeCore *, 
                           WeakRefCountPolicy      > SFWeakNodeCorePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField     <NodeCore *, 
                           NoRefCountPolicy        > SFUncountedNodeCorePtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef ChildPointerSField<NodeCore *, 
                           UnrecordedRefCountPolicy,
                           1                       > SFUnrecChildNodeCorePtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFRecNodeCorePtr : 
    public PointerSField     <NodeCore *, 
                              RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUnrecNodeCorePtr :
    public PointerSField     <NodeCore *, 
                              UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFWeakNodeCorePtr :
    public PointerSField     <NodeCore *, 
                              WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUncountedNodeCorePtr :
    public PointerSField     <NodeCore *, 
                              NoRefCountPolicy        > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUnrecChildNodeCorePtr :
    public ChildPointerSField<NodeCore *, 
                              UnrecordedRefCountPolicy,
                              1                       > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGNODECORESFIELDS_H_ */
