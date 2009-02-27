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

#ifndef _OSGFIELDCONTAINERMFIELDS_H_
#define _OSGFIELDCONTAINERMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"

#include "OSGFieldContainerFieldTraits.h"

#include "OSGPointerMField.h"
#include "OSGParentPointerMField.h"
#include "OSGChildPointerMField.h"

#include "OSGFieldContainerMFieldHandle.h"  

#include "OSGRefCountPolicies.h"

OSG_BEGIN_NAMESPACE


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<FieldContainer *,
                      RecordedRefCountPolicy  > MFRecFieldContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<FieldContainer *,
                      UnrecordedRefCountPolicy> MFUnrecFieldContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<FieldContainer *,
                      WeakRefCountPolicy      > MFWeakFieldContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<FieldContainer *,
                      NoRefCountPolicy        > MFUncountedFieldContainerPtr;


/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef 
    ParentPointerMField<FieldContainer *, 
                        NoRefCountPolicy,
                        1                > MFParentFieldContainerPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFRecFieldContainerPtr : 
    public PointerMField<FieldContainer *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecFieldContainerPtr :
    public PointerMField<FieldContainer *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFWeakFieldContainerPtr : 
    public PointerMField<FieldContainer *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUncountedFieldContainerPtr :
    public : PointerMField<FieldContainer *,
                           NoRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFParentFieldContainerPtr :
    public ParentPointerMField<FieldContainer *, 
                               NoRefCountPolicy,
                               1                 > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#include "OSGFieldContainerMFields.inl"

#endif /* _OSGFIELDCONTAINERMFIELDS_H_ */
