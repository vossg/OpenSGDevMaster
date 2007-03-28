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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerAttachment.h"

OSG_USING_NAMESPACE

void AttachmentContainer::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);
}

AttachmentContainer::TypeObject AttachmentContainer::_type(
    AttachmentContainer::getClassname(),
    Inherited          ::getClassname(),
    NULL,
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &AttachmentContainer::classDescInserter,
    false,
    0);

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
/*                              Cloning                                    */

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are shared, only if
    an attachment's type name is in \a cloneTypeNames or if it belongs to a
    group in \a cloneGroupNames it is cloned. If an attachment's type is in
    \a ignoreTypeNames or belongs to a group in \a ignoreGroupNames it is
    ignored altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] cloneTypeNames List of type names that are cloned.
    \param[in] ignoreTypeNames List of type names that are ignored.
    \param[in] cloneGroupNames List of group names that are cloned.
    \param[in] ignoreGroupNames LIst of group names that are ignored.
 */
void
OSG::cloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::vector<std::string>       &cloneTypeNames,
    const std::vector<std::string>       &ignoreTypeNames,
    const std::vector<std::string>       &cloneGroupNames,
    const std::vector<std::string>       &ignoreGroupNames)
{
    std::vector<const FieldContainerType *> cloneTypes;
    std::vector<const FieldContainerType *> ignoreTypes;
    std::vector<UInt16>                     cloneGroupIds;
    std::vector<UInt16>                     ignoreGroupIds;

    appendTypesVector (cloneTypeNames,   cloneTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(cloneGroupNames,  cloneGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    OSG::cloneAttachments(src, dst, cloneTypes,    ignoreTypes,
                                    cloneGroupIds, ignoreGroupIds);
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are shared, only if
    an attachment belongs to a group in \a cloneGroupIds it is cloned. If the
    attachment belongs to a group in \a ignoreGroupIds it is ignored altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] cloneGroupIds List of group ids, whose members are cloned.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
 */
void
OSG::cloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::vector<UInt16>            &cloneGroupIds,
    const std::vector<UInt16>            &ignoreGroupIds)
{
    std::vector<const FieldContainerType *> cloneTypes;
    std::vector<const FieldContainerType *> ignoreTypes;

    OSG::cloneAttachments(src, dst, cloneTypes,    ignoreTypes,
                                    cloneGroupIds, ignoreGroupIds);
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are shared, only if
    an attachment's type is in the comma separated string of type names
    \a cloneTypesString it is cloned. If the type is in the comma separated
    string of type names \a ignoreTypesString the attachment is ignored
    altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] cloneTypesString Comma separated string of type names that are
        cloned instead of shared.
    \param[in] ignoreTypesString Comma separated string of type names that are
        ignored.
 */
void
OSG::cloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::string                    &cloneTypesString,
    const std::string                    &ignoreTypesString)
{
    std::vector<const FieldContainerType *> cloneTypes;
    std::vector<const FieldContainerType *> ignoreTypes;
    std::vector<UInt16>                     cloneGroupIds;
    std::vector<UInt16>                     ignoreGroupIds;

    appendTypesString(cloneTypesString,  cloneTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    OSG::cloneAttachments(src, dst, cloneTypes,    ignoreTypes,
                                    cloneGroupIds, ignoreGroupIds);
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are shared, only if
    an attachment's type is in \a cloneTypes or belongs to a group in
    \a cloneGroupIds it is cloned. If the type is in \a ignoreTypes or belongs
    to a group in \a ignoreGroupIds it is ignored altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] cloneTypes List of types to clone instead of share.
    \param[in] ignoreTypes List of types to ignore.
    \param[in] cloneGroupIds List of group ids, whose members are cloned.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
 */
void
OSG::cloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<const FieldContainerType *> &cloneTypes,
    const std::vector<const FieldContainerType *> &ignoreTypes,
    const std::vector<UInt16>                     &cloneGroupIds,
    const std::vector<UInt16>                     &ignoreGroupIds)
{
    const FieldContainerType   &type     = dst->getType();
    const FieldDescriptionBase *fDesc    = type.getFieldDesc("attachments");
    const UInt32                fieldId  = fDesc->getFieldId();
    const Field                *srcField = src->getField("attachments");

    fDesc->shareValuesV(srcField, fieldId, dst, cloneTypes,    ignoreTypes,
                                                cloneGroupIds, ignoreGroupIds);
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are cloned, only if
    an attachment's type name is in \a shareTypeNames or if it belongs to a
    group in \a shareGroupNames it is shared. If an attachment's type is in
    \a ignoreTypeNames or belongs to a group in \a ignoreGroupNames it is
    ignored altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] cloneTypeNames List of type names that are shareed.
    \param[in] ignoreTypeNames List of type names that are ignored.
    \param[in] cloneGroupNames List of group names that are shareed.
    \param[in] ignoreGroupNames LIst of group names that are ignored.
 */
void
OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg   src,
          AttachmentContainerPtrArg        dst,
    const std::vector<std::string>        &shareTypeNames,
    const std::vector<std::string>        &ignoreTypeNames,
    const std::vector<std::string>        &shareGroupNames,
    const std::vector<std::string>        &ignoreGroupNames)
{
    std::vector<const FieldContainerType *> shareTypes;
    std::vector<const FieldContainerType *> ignoreTypes;
    std::vector<UInt16>                     shareGroupIds;
    std::vector<UInt16>                     ignoreGroupIds;

    appendTypesVector (shareTypeNames,   shareTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(shareGroupNames,  shareGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    OSG::deepCloneAttachments(src, dst, shareTypes,    ignoreTypes,
                                        shareGroupIds, ignoreGroupIds);
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are cloned, only if
    an attachment belongs to a group in \a shareGroupIds it is shared. If the
    attachment belongs to a group in \a ignoreGroupIds it is ignored altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] shareGroupIds List of group ids, whose members are shared.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
 */
void
OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::vector<UInt16>            &shareGroupIds,
    const std::vector<UInt16>            &ignoreGroupIds)
{
    std::vector<const FieldContainerType *> shareTypes;
    std::vector<const FieldContainerType *> ignoreTypes;

    OSG::deepCloneAttachments(src, dst, shareTypes,    ignoreTypes,
                                        shareGroupIds, ignoreGroupIds);
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are cloned, only if
    an attachment's type is in the comma separated string of type names
    \a shareTypesString it is shared. If the type is in the comma separated
    string of type names \a ignoreTypesString the attachment is ignored
    altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] shareTypesString Comma separated string of type names that are
        shared instead of shared.
    \param[in] ignoreTypesString Comma separated string of type names that are
        ignored.
 */
void
OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg  src,
          AttachmentContainerPtrArg       dst,
    const std::string                    &shareTypesString,
    const std::string                    &ignoreTypesString)
{
    std::vector<const FieldContainerType *> shareTypes;
    std::vector<const FieldContainerType *> ignoreTypes;
    std::vector<UInt16>                     shareGroupIds;
    std::vector<UInt16>                     ignoreGroupIds;

    appendTypesString(shareTypesString,  shareTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    OSG::deepCloneAttachments(src, dst, shareTypes,    ignoreTypes,
                                        shareGroupIds, ignoreGroupIds);
}

/*! Add the attachments of \a src to \a dst. By default attachments are cloned.
    If the type of an attachment is in \a shareTypes or belongs to a group in
    \a shareGroupIds the attachment is shared instead. If the type of an
    attachment is in \a ignoreTypes or belongs to a group in \a ignoreGroupIds
    the attachment is neither cloned nor shared.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] shareTypes list of types to share.
    \param[in] ignoreTypes list of types to ignore.
    \param[in] shareGroupIds list of group ids, whose members are shared.
    \param[in] ignoreGroupIds list of group ids, whose members are ignored.
 */
void
OSG::deepCloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<const FieldContainerType *> &shareTypes,
    const std::vector<const FieldContainerType *> &ignoreTypes,
    const std::vector<UInt16>                     &shareGroupIds,
    const std::vector<UInt16>                     &ignoreGroupIds)
{
    const FieldContainerType   &type     = dst->getType();
    const FieldDescriptionBase *fDesc    = type.getFieldDesc("attachments");
    const UInt32                fieldId  = fDesc->getFieldId();
    const Field                *srcField = src->getField("attachments");

    fDesc->cloneValuesV(srcField, fieldId, dst, shareTypes,    ignoreTypes,
                                                shareGroupIds, ignoreGroupIds);
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

