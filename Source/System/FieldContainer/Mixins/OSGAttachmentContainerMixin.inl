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

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::pushToField(
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId   )
{
    Inherited::pushToField(pNewElement, uiFieldId);

    if(uiFieldId == AttachmentsFieldId)
    {
        addAttachment(cast_dynamic<AttachmentObjPtr>(pNewElement));
    }
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::insertIntoMField(
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId   )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);
    
    FWARNING(("AttachmentContainerMixin::insertIntoMField: NIY\n"));
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::replaceInMField (
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId   )
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);

    FWARNING(("AttachmentContainerMixin::replaceInMField: NIY\n"));
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::replaceInMField (
          FieldContainerPtrConstArg pOldElement,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);
    
    FWARNING(("AttachmentContainerMixin::replaceInMField: NIY\n"));
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::removeFromMField(
    const UInt32                    uiIndex,
    const UInt32                    uiFieldId )
{
    Inherited::removeFromMField(uiIndex, uiFieldId);
    
    FWARNING(("AttachmentContainerMixin::removeFromMField: NIY\n"));
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::removeFromMField(
          FieldContainerPtrConstArg pElement,
    const UInt32                    uiFieldId )
{
    Inherited::removeFromMField(pElement, uiFieldId);
    
    FWARNING(("AttachmentContainerMixin::removeFromMField: NIY\n"));
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::clearField(
    const UInt32                    uiFieldId )
{
    Inherited::clearField(uiFieldId);
    
    FWARNING(("AttachmentContainerMixin::clearField: NIY\n"));
}

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

template <class ParentT> inline
UInt32 AttachmentContainerMixin<ParentT>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        returnValue += _sfAttachments.getBinSize();
    }

    return returnValue;
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::copyToBin(
    BinaryDataHandler  &pMem, ConstFieldMaskArg whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _sfAttachments.copyToBin(pMem);
    }
}

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::copyFromBin(
    BinaryDataHandler &pMem, ConstFieldMaskArg whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _sfAttachments.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/**
 * Add an attachment at the binding point.
 *
 * \param pAttachment  The FCPtr to attach
 * \param binding      id that is combined with the groupId of the attachment
 *                     to determine the slot in the attachment map.
 * If the derived key (binding | group) matches an existing key this will
 * replace the old entry in the map.
 * The attachment will have this node set as it's parent.
 */
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

/**
 * Erase the attachment at the binding point.
 *
 * \param pAttachment  The FCPtr to detach (needed to get groupId())
 * \param binding      id that is combined with the groupId of the attachment
 *                     to determine the slot in the attachment map.
 *
 * Attempt to find attachment in map using key (binding|groupId).
 * If found, remove it.
 */
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

template <class ParentT> inline
void AttachmentContainerMixin<ParentT>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AttachmentObjPtrMapIt fcI = _sfAttachments.getValue().begin();
    AttachmentObjPtrMapIt fcE = _sfAttachments.getValue().end  ();

    while(fcI != fcE)
    {
        (*fcI).second->subParent(Inherited::getPtr());

        subRef((*fcI).second);

        ++fcI;
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERMIXIN_INLINE_CVSID "@(#)$Id$"

