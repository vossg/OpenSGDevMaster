/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#ifndef _OSGATTACHMENTCONTAINERMFIELDS_H_
#define _OSGATTACHMENTCONTAINERMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttachmentContainerFieldTraits.h"
#include "OSGPointerMField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<
          AttachmentContainer *,
          RecordedRefCountPolicy     > MFRecAttachmentContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<
          AttachmentContainer *,
          UnrecordedRefCountPolicy   > MFUnrecAttachmentContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<
          AttachmentContainer *,
          WeakRefCountPolicy         > MFWeakAttachmentContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<
          AttachmentContainer *,
          NoRefCountPolicy           > MFUncountedAttachmentContainerPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFRecAttachmentContainerPtr :
    public PointerMField<AttachmentContainer *,
                         RecordedRefCountPolicy     > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFUnrecAttachmentContainerPtr :
    public PointerMField<AttachmentContainer *,
                         UnrecordedRefCountPolicy   > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFWeakAttachmentContainerPtr :
    public PointerMField<AttachmentContainer *,
                         WeakRefCountPolicy         > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields */
struct MFUncountedAttachmentContainerPtr :
    public PointerMField<AttachmentContainer *,
                         NoRefCountPolicy           > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGATTACHMENTCONTAINERMFIELDS_H_ */
