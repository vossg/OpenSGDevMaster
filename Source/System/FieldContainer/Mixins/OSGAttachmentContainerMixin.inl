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


template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc;

    typedef typename SFAttachmentObjPtrMap::Description SFDesc;

    pDesc = new SFDesc(
        SFAttachmentObjPtrMap::getClassType(),
        "attachments",
        "List of attachments connected.",
        OSG_RC_FIELD_DESC(Self::Attachments),
        false,
        Field::SFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&Self::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&Self::getSFAttachments),
        NULL);

    oType.addInitialDesc(pDesc);
}


template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::addAttachment(
    const AttachmentObjPtr &pAttachment,
          UInt16            binding)
{
    UInt32 key;

    if(pAttachment == NullFC)
        return;

    key = (UInt32 (pAttachment->getGroupId()) << 16) | binding;

    addRef(pAttachment);

    pAttachment->addParent(Inherited::getPtr());

    Self::editSField(AttachmentsFieldMask);

    AttachmentObjPtrMapIt fcI = _sfAttachments.getValue().find(key);

    if(fcI != _sfAttachments.getValue().end())
    {
        (*fcI).second->subParent(Inherited::getPtr());

        subRef((*fcI).second);

        (*fcI).second = pAttachment;
    }
    else
    {
        _sfAttachments.getValue()[key] = pAttachment;
    }
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::subAttachment(
    const AttachmentObjPtr &pAttachment,
          UInt16            binding)
{
    UInt32 key;

    AttachmentObjPtrMapIt fcI;

    if(pAttachment == NullFC)
        return;

    key = (UInt32(pAttachment->getGroupId()) << 16) | binding;

    Self::editSField(AttachmentsFieldMask);

    fcI = _sfAttachments.getValue().find(key);

    if(fcI != _sfAttachments.getValue().end())
    {

        (*fcI).second->subParent(Inherited::getPtr());

        subRef((*fcI).second);

        _sfAttachments.getValue().erase(fcI);
    }
}

template <class ParentT> inline
typename AttachmentContainerMixin<ParentT>::AttachmentObjPtr
    AttachmentContainerMixin<ParentT>::findAttachment(UInt32 groupId,
                                                      UInt16 binding)
{
    UInt32 key = (UInt32(groupId) << 16) | binding;

    AttachmentObjPtrMapIt fcI = _sfAttachments.getValue().find(key);

    if(fcI == _sfAttachments.getValue().end())
    {
        return NullFC;
    }
    else
    {
        return (*fcI).second;
    }
}

template <class ParentT> inline
typename AttachmentContainerMixin<ParentT>::AttachmentObjPtr
    AttachmentContainerMixin<ParentT>::findAttachment(
        const FieldContainerType &type,
              UInt16              binding)
{
    return findAttachment(type.getGroupId(), binding);
}

template <class ParentT> inline
const typename AttachmentContainerMixin<ParentT>::SFAttachmentObjPtrMap *
    AttachmentContainerMixin<ParentT>::getSFAttachments(void) const
{
    return &_sfAttachments;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
AttachmentContainerMixin<ParentT>::AttachmentContainerMixin(void) :
     Inherited    (),
    _sfAttachments()
{
}

template <class ParentT> inline
AttachmentContainerMixin<ParentT>::AttachmentContainerMixin(
    const AttachmentContainerMixin &source) :

     Inherited    (source               ),
    _sfAttachments(source._sfAttachments)
{
}

template <class ParentT> inline
AttachmentContainerMixin<ParentT>::~AttachmentContainerMixin(void)
{
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::dump(      UInt32    uiIndent,
                                             const BitVector bvFlags ) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "attachments " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo,
          UInt32             uiCopyOffset)
{
    Inherited::execSync(pFrom, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _sfAttachments.syncWith(pFrom->_sfAttachments);
    }
}
#endif
#ifdef OSG_MT_CPTR_ASPECT
template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
                             AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _sfAttachments.syncWith(pFrom->_sfAttachments);
    }
}
#endif

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERMIXIN_INLINE_CVSID "@(#)$Id$"

