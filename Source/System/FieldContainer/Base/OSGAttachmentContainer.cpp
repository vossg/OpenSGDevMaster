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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerAttachment.h"

OSG_USING_NAMESPACE

void AttachmentContainer::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);
}

AttachmentContainer::TypeObject AttachmentContainer::_type(true,
    AttachmentContainer::getClassname(),
    Inherited          ::getClassname(),
    NULL,
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &AttachmentContainer::classDescInserter,
    false);

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AttachmentContainer::AttachmentContainer(void) :
    Inherited()
{
}

AttachmentContainer::AttachmentContainer(const AttachmentContainer &source) :
    Inherited(source)
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

AttachmentContainer::~AttachmentContainer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

OSG_ABSTR_FIELD_CONTAINER_DEF(AttachmentContainer)

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */


/** Deep clone of attachements. */
void OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::vector<std::string>       &share)
{
    const FieldContainerType   &type     = dst->getType();

    const FieldDescriptionBase *fdesc    = type.getFieldDesc("attachments");

    const Field                *srcField = src->getField("attachments");

          BitVector             mask     = fdesc->getFieldMask();

    fdesc->cloneValuesV(srcField, mask, share, dst);
}

void OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::vector<UInt16>            &shareGroupIds)
{
    std::vector<std::string> share;

    fillGroupShareList(shareGroupIds, share);

    OSG::deepCloneAttachments(src, dst, share);
}

// shareString is a comma separated FieldContainer type list
// e.g. "Material, Geometry"
void OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::string                    &shareString)
{
    std::vector<std::string> share;

    splitShareString(shareString, share);

    OSG::deepCloneAttachments(src, dst, share);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGATTACHMENTCONTAINER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGATTACHMENTCONTAINER_INLINE_CVSID;
}

