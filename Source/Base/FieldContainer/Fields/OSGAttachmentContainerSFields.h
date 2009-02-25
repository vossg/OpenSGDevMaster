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

#ifndef _OSGATTACHMENTCONTAINERSFIELDS_H_
#define _OSGATTACHMENTCONTAINERSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttachmentContainerFieldTraits.h"
#include "OSGPointerSField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<
          AttachmentContainer *,
          RecordedRefCountPolicy     > SFRecAttachmentContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<
          AttachmentContainer *,
          UnrecordedRefCountPolicy   > SFUnrecAttachmentContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<
          AttachmentContainer *,
          WeakRefCountPolicy         > SFWeakAttachmentContainerPtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<
          AttachmentContainer *,
          NoRefCountPolicy           > SFUncountedAttachmentContainerPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFRecAttachmentContainerPtr :
    public PointerSField<AttachmentContainer *,
                         RecordedRefCountPolicy     > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUnrecAttachmentContainerPtr :
    public PointerSField<AttachmentContainer *,
                         UnrecordedRefCountPolicy   > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFWeakAttachmentContainerPtr : 
    public PointerSField<AttachmentContainer *,
                         WeakRefCountPolicy         > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields */
struct SFUncountedAttachmentContainerPtr :
    public PointerSField<AttachmentContainer *,
                         NoRefCountPolicy           > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGATTACHMENTCONTAINERSFIELDS_H_ */
