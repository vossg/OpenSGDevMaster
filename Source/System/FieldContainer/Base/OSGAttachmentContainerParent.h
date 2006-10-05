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

#ifndef _OSGATTACHMENTCONTAINERPARENT_H_
#define _OSGATTACHMENTCONTAINERPARENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttachmentContainerMixin.h"
#include "OSGContainerMixinHead.h"

OSG_BEGIN_NAMESPACE

struct ContainerAttachmentContainerDesc;

/** Base class type for AttachmentContainers.
 * This type pulls in the mixins needed to create an AttachmentContainer.
 */
typedef AttachmentContainerMixin<
          ContainerMixinHead     <
              ContainerAttachmentContainerDesc > >
                  ContainerAttachmentContainerParent;

/**
 * Traits class use for creating AttachmentContainer using ContainerMixinHead
 * and AttachmentContainerMixin.
 */
struct ContainerAttachmentContainerDesc
{
    typedef FieldContainer                          ParentT;

    typedef FieldContainer::TypeObject              TypeObject;

    typedef FieldContainerAttachment                AttachmentObj;
    typedef FieldContainerAttachmentPtr             AttachmentObjPtr;
    typedef SFFieldContainerAttachmentPtrMap        SFAttachmentObjPtrMap;
};

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERPARENT_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGATTACHMENTCONTAINERPARENT_H_ */
