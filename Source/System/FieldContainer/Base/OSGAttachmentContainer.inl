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

OSG_BEGIN_NAMESPACE

inline
const Char8 *AttachmentContainer::getClassname(void)
{
    return "AttachmentContainer";
}

/**
 * Find an attachment at the binding point.
 *
 * \param groupId  The Group id to search for
 * \param binding  id that is combined with the groupId of the attachment
 *                 to determine the slot in the attachment map.
 *
 * Attempt to find attachment in map using key (binding|groupId).
 * If found, return it, else return NullFC
 */
inline
AttachmentContainer::AttachmentObjPtr
    AttachmentContainer::findAttachment(UInt32 groupId,
                                        UInt16 binding) const
{
    UInt32 key = (UInt32(groupId) << 16) | binding;

    AttachmentObjPtrMapConstIt fcI = _sfAttachments.getValue().find(key);

    if(fcI == _sfAttachments.getValue().end())
    {
        return NullFC;
    }
    else
    {
        return (*fcI).second;
    }
}

/**
 * Find an attachment at the binding point.
 *
 * \param type     FCType used to get groupId
 * \param binding  id that is combined with the groupId of the attachment
 *                 to determine the slot in the attachment map.
 *
 * Attempt to find attachment in map using key (binding|groupId).
 * If found, return it, else return NullFC
 */

inline
AttachmentContainer::AttachmentObjPtr
    AttachmentContainer::findAttachment(
        const FieldContainerType &type,
              UInt16              binding) const
{
    return findAttachment(type.getGroupId(), binding);
}

OSG_ABSTR_FIELD_CONTAINER_INL_DEF(AttachmentContainer)

OSG_END_NAMESPACE
