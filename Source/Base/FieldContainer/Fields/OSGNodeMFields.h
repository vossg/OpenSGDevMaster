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

#ifndef _OSGNODEMFIELDS_H_
#define _OSGNODEMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNodeFieldTraits.h"
#include "OSGPointerMField.h"
#include "OSGParentPointerMField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField      <Node *,
                            RecordedRefCountPolicy  > MFRecNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField      <Node *,
                            UnrecordedRefCountPolicy> MFUnrecNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField      <Node *,
                            WeakRefCountPolicy      > MFWeakNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField      <Node *,
                            NoRefCountPolicy        > MFUncountedNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef ChildPointerMField <Node *,
                            UnrecordedRefCountPolicy,
                            1                       > MFUnrecChildNodePtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef ParentPointerMField<Node *,
                            NoRefCountPolicy,
                            1                       > MFParentNodePtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFRecNodePtr :
    public PointerMField      <Node *,
                               RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFUnrecNodePtr :
    public PointerMField      <Node *,
                               UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFWeakNodePtr :
    public PointerMField      <Node *,
                               WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFUncountedNodePtr :
    public PointerMField      <Node *,
                               NoRefCountPolicy        > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFUnrecChildNodePtr :
    public ChildPointerMField <Node *,
                               UnrecordedRefCountPolicy,
                               1                       > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFParentNodePtr :
    public ParentPointerMField<Node *,
                               NoRefCountPolicy,
                               1                       > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGNODEMFIELDS_H_ */
