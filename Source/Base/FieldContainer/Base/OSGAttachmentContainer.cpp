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
#include "OSGAttachment.h"
#include "OSGTypeBasePredicates.h"
#include "OSGReflexiveContainerTypePredicates.h"
#include "OSGNameAttachment.h"
#include "OSGStringUtils.h"

#include "boost/bind.hpp"

#include "OSGPointerSField.h"

OSG_BEGIN_NAMESPACE

void AttachmentContainer::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc;

    typedef SFAttachmentObjPtrMap::Description SFDesc;

    pDesc = new SFDesc(
        SFAttachmentObjPtrMap::getClassType(),
        "attachments",
        "List of attachments connected.",
        OSG_RC_FIELD_DESC(Attachments),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Self::editHandleAttachments),
        static_cast<FieldGetMethodSig >(&Self::getHandleAttachments ));

    oType.addInitialDesc(pDesc);
}

AttachmentContainer::TypeObject AttachmentContainer::_type(
    AttachmentContainer::getClassname(),
    Inherited          ::getClassname(),
    NULL,
    0,
    NULL,
    NULL,
    NULL,
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&AttachmentContainer::classDescInserter)),
    false,
    0);

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AttachmentContainer::AttachmentContainer(void) :
     Inherited    (),
    _sfAttachments()
{
}

AttachmentContainer::AttachmentContainer(const AttachmentContainer &source) :
     Inherited    (source),
    _sfAttachments(      )
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
/* Binary access                                                           */

SizeT AttachmentContainer::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        returnValue += _sfAttachments.getBinSize();
    }

    return returnValue;
}

void AttachmentContainer::copyToBin(BinaryDataHandler  &pMem, 
                                    ConstFieldMaskArg   whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _sfAttachments.copyToBin(pMem);
    }
}

void AttachmentContainer::copyFromBin(BinaryDataHandler &pMem, 
                                      ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        // _sfAttachments.copyFromBin(pMem);

        editSField(AttachmentsFieldMask);

        UInt32 size;

        pMem.getValue(size);

        AttachmentMap::const_iterator mapIt  = _sfAttachments.getValue().begin();
        AttachmentMap::const_iterator mapEnd = _sfAttachments.getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            if((*mapIt).second != NULL)
            {
                if(this->isMTLocal())
                {
                    Thread::getCurrentChangeList()->addDelayedSubRef<
                        RecordedRefCountPolicy>((*mapIt).second);
                }
                else
                {
                    Thread::getCurrentChangeList()->addDelayedSubRef<
                        UnrecordedRefCountPolicy>((*mapIt).second);
                }
            }
        }

        _sfAttachments.getValue().clear();

        for(UInt32 i = 0; i < size; ++i)
        {
            UInt16 binding;
            UInt32 fcId;

            pMem.getValue(binding);
            pMem.getValue(fcId   );

            Attachment *att = dynamic_cast<Attachment *>(
                FieldContainerFactory::the()->getMappedContainer(fcId));

            if(att != NULL)
            {
                UInt32 key = (static_cast<UInt32>(att->getGroupId()) << 16) | binding;

                if(this->isMTLocal())
                {
                    RecordedRefCountPolicy::addRef(att);
                }
                else
                {
                    UnrecordedRefCountPolicy::addRef(att);
                }

                _sfAttachments.getValue().insert(
                    AttachmentMap::value_type(key, att));
            }
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/**
 * Add an attachment at the binding point.
 *
 * \param [in] pAttachment  The FCPtr to attach
 * \param [in] binding      id that is combined with the groupId of the
 *                          attachment to determine the slot in the attachment
 *                          map. 
 *
 * If the derived key (binding | group) matches an existing key this will
 * replace the old entry in the map.
 * The attachment will have this node set as it's parent.
 */

void AttachmentContainer::addAttachment(
    AttachmentObj * const pAttachment,
    UInt16                binding)
{
    UInt32 key;

    if(pAttachment == NULL)
        return;

    key = (UInt32 (pAttachment->getGroupId()) << 16) | binding;

    if(this->isMTLocal())
    {
        RecordedRefCountPolicy::addRef(pAttachment);
    }
    else
    {
        UnrecordedRefCountPolicy::addRef(pAttachment);
    }

    pAttachment->linkParent(this, 
                            AttachmentsFieldId, 
                            Attachment::ParentsFieldId);

    Self::editSField(AttachmentsFieldMask);

    AttachmentObjPtrMapIt fcI = _sfAttachments.getValue().find(key);

    if(fcI != _sfAttachments.getValue().end())
    {
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);

        if(this->isMTLocal())
        {
            RecordedRefCountPolicy::subRef((*fcI).second);
        }
        else
        {
            UnrecordedRefCountPolicy::subRef((*fcI).second);
        }

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
 * \param [in] pAttachment  The FCPtr to detach (needed to get groupId())
 * \param [in] binding      id that is combined with the groupId of the
 *                          attachment to determine the slot in the attachment
 *                          map. 
 *
 * Attempt to find attachment in map using key (binding|groupId).
 * If found, remove it.
 */

void AttachmentContainer::subAttachment(
    AttachmentObj * const pAttachment,
    UInt16                binding)
{
    UInt32 key;

    AttachmentObjPtrMapIt fcI;

    if(pAttachment == NULL)
        return;

    key = (UInt32(pAttachment->getGroupId()) << 16) | binding;

    Self::editSField(AttachmentsFieldMask);

    fcI = _sfAttachments.getValue().find(key);

    if(fcI != _sfAttachments.getValue().end())
    {
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);

        if(this->isMTLocal())
        {
            RecordedRefCountPolicy::subRef((*fcI).second);
        }
        else
        {
            UnrecordedRefCountPolicy::subRef((*fcI).second);
        }

        _sfAttachments.getValue().erase(fcI);
    }
}

void  AttachmentContainer::replaceAttachmentByObj(Attachment * const pOld,
                                                  Attachment * const pNew)
{
    Self::editSField(AttachmentsFieldMask);

    AttachmentObjPtrMapIt fcI = _sfAttachments.getValue().begin();
    AttachmentObjPtrMapIt fcE = _sfAttachments.getValue().end  ();

    for(; fcI != fcE; ++fcI)
    {
        if(fcI->second == pOld)
        {
            { // New
                if(this->isMTLocal())
                {
                    RecordedRefCountPolicy::addRef(pNew);
                }
                else
                {
                    UnrecordedRefCountPolicy::addRef(pNew);
                }
                
                pNew->linkParent(this, 
                                 AttachmentsFieldId, 
                                 Attachment::ParentsFieldId);
            }
            
            { // Old
                pOld->unlinkParent(this, 
                                   Attachment::ParentsFieldId);

                if(this->isMTLocal())
                {
                    RecordedRefCountPolicy::subRef(pOld);
                }
                else
                {
                    UnrecordedRefCountPolicy::subRef(pOld);
                }
            }

            fcI->second = pNew;
        }
    }
}

const AttachmentContainer::SFAttachmentObjPtrMap *
    AttachmentContainer::getSFAttachments(void) const
{
    return &_sfAttachments;
}


void AttachmentContainer::dump(      UInt32    uiIndent,
                               const BitVector bvFlags ) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "attachments " << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    AttachmentObjPtrMapConstIt fcI = this->_sfAttachments.getValue().begin();
    AttachmentObjPtrMapConstIt fcE = this->_sfAttachments.getValue().end  ();

    uiIndent += 4;

    for(; fcI != fcE; ++fcI)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "Key  : " << fcI->first << " | " 
             << "Bind : " << (fcI->first & 0x0000FFFF) << " | "
             << "Type : " << fcI->second->getType().getCName() << " | "
             << "Int  : " << fcI->second->getInternal()
             << std::endl;
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

#ifdef OSG_MT_CPTR_ASPECT
void AttachmentContainer::execSync(
          AttachmentContainer *pFrom,
          ConstFieldMaskArg    whichField,
          AspectOffsetStore   &oOffsets,
          ConstFieldMaskArg    syncMode  ,
    const UInt32               uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
//        _sfAttachments.syncWith(pFrom->_sfAttachments);

        // needs optimizing

        AttachmentMap tmpMap;

        AttachmentObjPtrMapIt fcI = pFrom->_sfAttachments.getValue().begin();
        AttachmentObjPtrMapIt fcE = pFrom->_sfAttachments.getValue().end  ();
        
        while(fcI != fcE)
        {
            Attachment *pAtt = Aspect::convertToCurrent((*fcI).second);

            if(pAtt != NULL)
            {
                tmpMap[(*fcI).first] = pAtt;

                if(this->isMTLocal())
                {
                    RecordedRefCountPolicy::addRef(pAtt);
                }
                else
                {
                    UnrecordedRefCountPolicy::addRef(pAtt);
                }
            }

            ++fcI;
        }

        fcI = _sfAttachments.getValue().begin();
        fcE = _sfAttachments.getValue().end  ();

        while(fcI != fcE)
        {
            if(this->isMTLocal())
            {
                Thread::getCurrentChangeList()->addDelayedSubRef<
                    RecordedRefCountPolicy>((*fcI).second);
            }
            else
            {
                Thread::getCurrentChangeList()->addDelayedSubRef<
                    UnrecordedRefCountPolicy>((*fcI).second);
            }
            
            ++fcI;
        }

        _sfAttachments.setValue(tmpMap);
    }
}
#endif

void AttachmentContainer::resolveLinks(void)
{
    Inherited::resolveLinks();

    Self::editSField(AttachmentsFieldMask);

    AttachmentObjPtrMapIt fcI = _sfAttachments.getValue().begin();
    AttachmentObjPtrMapIt fcE = _sfAttachments.getValue().end  ();

    while(fcI != fcE)
    {
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);


        if(this->isMTLocal())
        {
            RecordedRefCountPolicy::subRef((*fcI).second);
        }
        else
        {
            UnrecordedRefCountPolicy::subRef((*fcI).second);
        }

        ++fcI;
    }

    _sfAttachments.getValue().clear();
}

EditFieldHandlePtr AttachmentContainer::editHandleAttachments(void) 
{
    SFAttachmentObjPtrMap::EditHandlePtr returnValue(
        new  SFAttachmentObjPtrMap::EditHandle(
             &_sfAttachments, 
             this->getType().getFieldDesc(AttachmentsFieldId),
             this));

    returnValue->setAddMethod(boost::bind(&AttachmentContainer::addAttachment,
                                          this,
                                          _1,
                                          _2));

    returnValue->setReplaceMethod(
        boost::bind(&AttachmentContainer::replaceAttachmentByObj,
                                          this,
                                          _1,
                                          _2));

    editSField(AttachmentsFieldMask);

    return returnValue;
}

GetFieldHandlePtr AttachmentContainer::getHandleAttachments(void) const
{
    SFAttachmentObjPtrMap::GetHandlePtr returnValue(
        new  SFAttachmentObjPtrMap::GetHandle(
             &_sfAttachments, 
             this->getType().getFieldDesc(AttachmentsFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}




/*---------------------------------------------------------------------*/
/*! \name Attachment Container cloning                                 */
/*! \{                                                                 */

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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void cloneAttachments(
          OSG::AttachmentContainer const *src,
          OSG::AttachmentContainer       *dst,
    const std::vector<std::string>       &cloneTypeNames,
    const std::vector<std::string>       &ignoreTypeNames,
    const std::vector<std::string>       &cloneGroupNames,
    const std::vector<std::string>       &ignoreGroupNames)
{
    std::vector<const ReflexiveContainerType *> cloneTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         cloneGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesVector (cloneTypeNames,   cloneTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(cloneGroupNames,  cloneGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    cloneAttachments(src, dst, cloneTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void cloneAttachments(
          OSG::AttachmentContainer const      *src,
          OSG::AttachmentContainer            *dst,
    const std::vector<OSG::UInt16>            &cloneGroupIds,
    const std::vector<OSG::UInt16>            &ignoreGroupIds)
{
    std::vector<const ReflexiveContainerType *> cloneTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;

    cloneAttachments(src, dst, cloneTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void cloneAttachments(
          OSG::AttachmentContainer const *src,
          OSG::AttachmentContainer       *dst,
    const std::string                    &cloneTypesString,
    const std::string                    &ignoreTypesString)
{
    std::vector<const ReflexiveContainerType *> cloneTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         cloneGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesString(cloneTypesString,  cloneTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    cloneAttachments(src, dst, cloneTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void cloneAttachments(
          OSG::AttachmentContainer const                   *src,
          OSG::AttachmentContainer                         *dst,
    const std::vector<const OSG::ReflexiveContainerType *> &cloneTypes,
    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes,
    const std::vector<OSG::UInt16>                         &cloneGroupIds,
    const std::vector<OSG::UInt16>                         &ignoreGroupIds)
{
#if 0
    const FieldContainerType   &type     = dst->getType();
    const FieldDescriptionBase *fDesc    = type.getFieldDesc("attachments");
    const UInt32                fieldId  = fDesc->getFieldId();
    const Field                *srcField = src->getField("attachments");

    fDesc->shareValuesV(srcField, fieldId, dst, cloneTypes,    ignoreTypes,
                                                cloneGroupIds, ignoreGroupIds);
#else
    const SFAttachmentPtrMap *pAttMap =
        src->getSFAttachments();

    AttachmentMap::const_iterator mapIt  = pAttMap->getValue().begin();
    AttachmentMap::const_iterator mapEnd = pAttMap->getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        AttachmentUnrecPtr att       = mapIt->second;
        UInt16             uiBinding = UInt16(mapIt->first &
                                              0x0000FFFF    );

        if(att != NULL)
        {
            const FieldContainerType &attType = att->getType();

            // test if att type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                attType                ) &&
               !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                ignoreTypes.end(),
                                                attType                )   )
            {
                // test if att should cloned
                if(TypePredicates::typeInGroupIds (cloneGroupIds.begin(),
                                                   cloneGroupIds.end(),
                                                   attType               ) ||
                   TypePredicates::typeDerivedFrom(cloneTypes.begin(),
                                                   cloneTypes.end(),
                                                   attType               )   )
                {
                    att = dynamic_pointer_cast<Attachment>(
                        OSG::deepClone(att, cloneTypes,    ignoreTypes,
                                            cloneGroupIds, ignoreGroupIds));
                }
            }
        }

        dst->addAttachment(att, uiBinding);
    }
#endif
}

/*! Adds the attachments of \a src to \a dst, overwriting existing attachments
    of the same type and binding. By default attachments are cloned, only if
    an attachment's type name is in \a shareTypeNames or if it belongs to a
    group in \a shareGroupNames it is shared. If an attachment's type is in
    \a ignoreTypeNames or belongs to a group in \a ignoreGroupNames it is
    ignored altogether.

    \param[in] src AttachmentContainer whose attachments are cloned.
    \param[out] dst AttachmentContainer where cloned attachments are added.
    \param[in] shareTypeNames List of type names that are shareed.
    \param[in] ignoreTypeNames List of type names that are ignored.
    \param[in] shareGroupNames List of group names that are shareed.
    \param[in] ignoreGroupNames LIst of group names that are ignored.

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void deepCloneAttachments(
          OSG::AttachmentContainer const  *src,
          OSG::AttachmentContainer        *dst,
    const std::vector<std::string>        &shareTypeNames,
    const std::vector<std::string>        &ignoreTypeNames,
    const std::vector<std::string>        &shareGroupNames,
    const std::vector<std::string>        &ignoreGroupNames)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         shareGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesVector (shareTypeNames,   shareTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(shareGroupNames,  shareGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    deepCloneAttachments(src, dst, shareTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void deepCloneAttachments(
          OSG::AttachmentContainer const      *src,
          OSG::AttachmentContainer            *dst,
    const std::vector<OSG::UInt16>            &shareGroupIds,
    const std::vector<OSG::UInt16>            &ignoreGroupIds)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;

    deepCloneAttachments(src, dst, shareTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void deepCloneAttachments(
          OSG::AttachmentContainer const *src,
          OSG::AttachmentContainer       *dst,
    const std::string                    &shareTypesString,
    const std::string                    &ignoreTypesString)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         shareGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesString(shareTypesString,  shareTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    deepCloneAttachments(src, dst, shareTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso AttachmentContainer
 */

void deepCloneAttachments(
          OSG::AttachmentContainer const                   *src,
          OSG::AttachmentContainer                         *dst,
    const std::vector<const OSG::ReflexiveContainerType *> &shareTypes,
    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes,
    const std::vector<OSG::UInt16>                         &shareGroupIds,
    const std::vector<OSG::UInt16>                         &ignoreGroupIds)
{
#if 0
    const FieldContainerType   &type     = dst->getType();
    const FieldDescriptionBase *fDesc    = type.getFieldDesc("attachments");
    const UInt32                fieldId  = fDesc->getFieldId();
    const Field                *srcField = src->getField("attachments");

    fDesc->cloneValuesV(srcField, fieldId, dst, shareTypes,    ignoreTypes,
                                                shareGroupIds, ignoreGroupIds);
#else
    const SFAttachmentPtrMap *pAttMap =
        src->getSFAttachments();

    AttachmentMap::const_iterator mapIt  = pAttMap->getValue().begin();
    AttachmentMap::const_iterator mapEnd = pAttMap->getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        AttachmentUnrecPtr att       = mapIt->second;
        UInt16             uiBinding = UInt16(mapIt->first &
                                              0x0000FFFF    );

        if(att != NULL)
        {
            const FieldContainerType &attType = att->getType();

            // test if att type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                attType                ) &&
               !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                ignoreTypes.end(),
                                                attType                )   )
            {
                // test if att should cloned
                if(!TypePredicates::typeInGroupIds (shareGroupIds.begin(),
                                                    shareGroupIds.end(),
                                                    attType               ) &&
                   !TypePredicates::typeDerivedFrom(shareTypes.begin(),
                                                    shareTypes.end(),
                                                    attType               )   )
                {
                    att = dynamic_pointer_cast<Attachment>(
                        OSG::deepClone(att, shareTypes,    ignoreTypes,
                                            shareGroupIds, ignoreGroupIds));
                }
            }
        }

        dst->addAttachment(att, uiBinding);
    }
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
