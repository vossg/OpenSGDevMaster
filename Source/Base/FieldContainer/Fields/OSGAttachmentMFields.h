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

#ifndef _OSGATTACHMENTMFIELDS_H_
#define _OSGATTACHMENTMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttachmentFieldTraits.h"
#include "OSGPointerMField.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<Attachment *,
                      RecordedRefCountPolicy  >  MFRecAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<Attachment *,
                      UnrecordedRefCountPolicy>  MFUnrecAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<Attachment *,
                      WeakRefCountPolicy      >  MFWeakAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<Attachment *,
                      NoRefCountPolicy        >  MFUncountedAttachmentPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFRecAttachmentPtr :
    public PointerMField<Attachment *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecAttachmentPtr :
    public PointerMField<Attachment *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFWeakAttachmentPtr :
    public PointerMField<Attachment *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUncountedAttachmentPtr :
    public PointerMField<Attachment *,
                         NoRefCountPolicy        > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGATTACHMENTMFIELDS_H_ */
