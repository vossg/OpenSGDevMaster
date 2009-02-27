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

#ifndef _OSGATTACHMENTSFIELDS_H_
#define _OSGATTACHMENTSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttachmentFieldTraits.h"
#include "OSGPointerSField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<Attachment *,
                      RecordedRefCountPolicy  > SFRecAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<Attachment *,
                      UnrecordedRefCountPolicy> SFUnrecAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<Attachment *,
                      WeakRefCountPolicy      > SFWeakAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<Attachment *,
                      NoRefCountPolicy        > SFUncountedAttachmentPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFRecAttachmentPtr :
    public PointerSField<Attachment *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecAttachmentPtr :
    public PointerSField<Attachment *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFWeakAttachmentPtr :
    public PointerSField<Attachment *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUncountedAttachmentPtr : 
    public PointerSField<Attachment *,
                         NoRefCountPolicy        > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGATTACHMENTSFIELDS_H_ */
