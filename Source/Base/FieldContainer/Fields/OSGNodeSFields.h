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

#ifndef _OSGNODESFIELDS_H_
#define _OSGNODESFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNodeFieldTraits.h"
#include "OSGPointerSField.h"
#include "OSGParentPointerSField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField      <Node *,
                            RecordedRefCountPolicy  > SFRecNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField      <Node *,
                            UnrecordedRefCountPolicy> SFUnrecNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField      <Node *,
                            WeakRefCountPolicy      > SFWeakNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField      <Node *,
                            NoRefCountPolicy        > SFUncountedNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef ChildPointerSField <Node *,
                            UnrecordedRefCountPolicy,
                            1                       > SFUnrecChildNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef ParentPointerSField<Node *,
                            NoRefCountPolicy,
                            1                       > SFParentNodePtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFRecNodePtr :
    public PointerSField      <Node *,
                               RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUnrecNodePtr :
    public PointerSField      <Node *,
                               UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFWeakNodePtr :
    public PointerSField      <Node *,
                               WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUncountedNodePtr :
    public PointerSField      <Node *,
                               NoRefCountPolicy        > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUnrecChildNodePtr :
    public ChildPointerSField <Node *,
                               UnrecordedRefCountPolicy,
                               1                       > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFParentNodePtr :
    public ParentPointerSField<Node *,
                               NoRefCountPolicy,
                               1                       > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGNODESFIELDS_H_ */
