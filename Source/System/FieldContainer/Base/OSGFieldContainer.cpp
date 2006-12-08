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

#include "OSGFieldContainer.h"
#include "OSGContainerPtrFuncs.h"

#include <algorithm>
#include <cctype>

#define SILENT

OSG_USING_NAMESPACE

void FieldContainer::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;

    pDesc = new MFChangedFunctorCallback::Description(
        MFChangedFunctorCallback::getClassType(),
        "changedCallbacks",
        "List of callback functors to notify of changes.",
        OSG_RC_FIELD_DESC(FieldContainer::ChangedCallbacks),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&FieldContainer::invalidEditField),
        static_cast<FieldGetMethodSig >(&FieldContainer::invalidGetField ));

    oType.addInitialDesc(pDesc);
}

FieldContainer::TypeObject FieldContainer::_type(true,
    FieldContainer::getClassname(),
    NULL,
    NULL,
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &FieldContainer::classDescInserter,
    false);


FieldContainer::TypeObject &FieldContainer::getType(void)
{
    return _type;
}

const FieldContainer::TypeObject &FieldContainer::getType(void) const
{
    return _type;
}

void FieldContainer::dump(      UInt32    uiIndent,
                          const BitVector bvFlags ) const
{
    indentLog(uiIndent, PLOG);

    PLOG << "FieldContainer : "
         << getType().getName()
         << std::endl;
}

void FieldContainer::pushToField(      FieldContainerPtrConstArg pNewElement,
                                 const UInt32                    uiFieldId  )
{

}

void FieldContainer::insertIntoMField(
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId  )
{
}

void FieldContainer::replaceInMField(
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId )
{
}

void FieldContainer::replaceInMField(
          FieldContainerPtrConstArg pOldElement,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId  )
{
}

void FieldContainer::removeFromMField(const UInt32 uiIndex,
                                      const UInt32 uiFieldId)
{
}

void FieldContainer::removeFromMField(
          FieldContainerPtrConstArg pElement,
    const UInt32                    uiFieldId)
{
}

void FieldContainer::clearField(const UInt32 uiFieldId)
{
}

void FieldContainer::copyFromBin(BinaryDataHandler  &,
                                 ConstFieldMaskArg   whichField)
{
    editSField(whichField);
}


void FieldContainer::invalidateVolume(void)
{
}

void FieldContainer::registerChangedContainer(void)
{
    FieldContainerPtr thisP = getPtr();

#ifndef SILENT
    fprintf(stderr, "reg changed %p 0x%016llx\n",
            _pContainerChanges, _bvChanged);
#endif

    if(_pContainerChanges == NULL)
    {
        _pContainerChanges =
            Thread::getCurrentChangeList()->getNewEntry(_bvChanged);

        _pContainerChanges->uiEntryDesc   = ContainerChangeEntry::Change;
        _pContainerChanges->pFieldFlags   = _pFieldFlags;
        _pContainerChanges->uiContainerId = getContainerId(thisP);
    }

    Thread::getCurrentChangeList()->addUncommited(_pContainerChanges);
}

void FieldContainer::registerChangedContainerV(void)
{
    registerChangedContainer();
}


bool FieldContainer::deregister(UInt32 uiContainerId)
{
    return FieldContainerFactory::the()->deregisterContainer(uiContainerId);
}

void FieldContainer::resolveLinks(void)
{
    callChangedFunctors(0);
}

/*-------------------------------------------------------------------------*/
/*                              Cloning                                    */

/*! Fills \a types with the type objects corresponding to the types named in
    \a typeNames. This is a helper function for deepClone.
    The elements of \a typeNames must be names of FieldContainer types, if a
    type name is not found there is no type object inserted into \a types, i.e.
    \a types may be shorter than \a typeNames.

    \param[in] typeNames FieldContainer type names.
    \param[out] types Type objects corresponding to \a typeNames.
 */
void
OSG::appendTypesVector(const std::vector<std::string>                &typeNames,
                             std::vector<const FieldContainerType *> &types     )
{
    const FieldContainerType *pType;

    std::vector<std::string>::const_iterator namesIt  = typeNames.begin();
    std::vector<std::string>::const_iterator namesEnd = typeNames.end();

    for(; namesIt != namesEnd; ++namesIt)
    {
        pType = FieldContainerFactory::the()->findType(namesIt->c_str());

        if(pType)
            types.push_back(pType);
    }
}

/*! Fills \a groupIds with the group ids of the groups in \a groupNames.
    This is a helper function for deepClone.
    The elements of \a groupNames must be names of groups, if a group name is
    not found there is no group id inserted into \a groupIds, i.e.
    \a groupIds may be shorter than \a groupNames.

    \param[in] groupNames Names of groups.
    \param[out] groupIds Ids of the groups in \a groupNames.
 */
void
OSG::appendGroupsVector(const std::vector<std::string> &groupNames,
                              std::vector<UInt16>      &groupIds   )
{
    UInt16 groupId;

    std::vector<std::string>::const_iterator namesIt  = groupNames.begin();
    std::vector<std::string>::const_iterator namesEnd = groupNames.end();

    for(; namesIt != namesEnd; ++namesIt)
    {
        groupId = FieldContainerFactory::the()->findGroupId(namesIt->c_str());

        if(groupId != 0)
            groupIds.push_back(groupId);
    }
}

/*! Fills \a types with the type objects corresponding to the types named in
    \a typesString. This is a helper function for deepClone.
    \a typesString is a comma separated string of FieldContainer type names.

    \param[in] typesString String of comma separated FieldContainer type names.
    \param[out] types Type objects corresponding to elements of \a typesString.
 */
void
OSG::appendTypesString(const std::string                             &typesString,
                             std::vector<const FieldContainerType *> &types       )
{
    const FieldContainerType *pType;
    string_token_iterator     tokenIt(typesString, ", ");
    string_token_iterator     tokenEnd;

    for(; tokenIt != tokenEnd; ++tokenIt)
    {
        pType = FieldContainerFactory::the()->findType((*tokenIt).c_str());

        if(pType)
            types.push_back(pType);
    }
}

/*! Creates a deep copy of \a src, i.e. all fields of \a src are copied, if
    they contain pointers to other FieldContainers these are cloned as well.
    The remaining parameters allow the selection of certain types that are
    either not cloned at all or are shared between \a src and the copy.

    \param[in] src FieldContainer to clone.
    \param[in] shareTypeNames Names of types that should be shared
        instead of cloned.
    \param[in] ignoreTypeNames Names of types that should be ignored.
    \param[in] shareGroupNames Names of type groups that should be shared
        instead of cloned.
    \param[in] ignoreGroupNames Names of type groups that should be ignored.
    \return deep copy of \a src.
 */
OSG_SYSTEM_DLLMAPPING
FieldContainerPtr
OSG::deepClone(      FieldContainerPtrConstArg  src,
               const std::vector<std::string>  &shareTypeNames,
               const std::vector<std::string>  &ignoreTypeNames,
               const std::vector<std::string>  &shareGroupNames,
               const std::vector<std::string>  &ignoreGroupNames)
{
    std::vector<const FieldContainerType *> shareTypes;
    std::vector<const FieldContainerType *> ignoreTypes;
    std::vector<UInt16>                     shareGroupIds;
    std::vector<UInt16>                     ignoreGroupIds;

    appendTypesVector (shareTypeNames,   shareTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(shareGroupNames,  shareGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    return OSG::deepClone(src, shareTypes,    ignoreTypes,
                               shareGroupIds, ignoreGroupIds);
}

/*! Creates a deep copy of \a src, i.e. all fields of \a src are copied, if
    they contain pointers to other FieldContainers these are cloned as well.
    The remaining parameters allow the selection of certain types that are
    either not cloned at all or are shared between \a src and the copy.

    \param[in] src FieldContainer to clone.
    \param[in] shareGroupIds Type groups that should be shared instead
        of cloned.
    \param[in] ignoreGroupIds Type groups that should be ignored.
    \return deep copy of \a src.
 */
FieldContainerPtr
OSG::deepClone(      FieldContainerPtrConstArg  src,
               const std::vector<UInt16>       &shareGroupIds,
               const std::vector<UInt16>       &ignoreGroupIds)
{
    std::vector<const FieldContainerType *> shareTypes;
    std::vector<const FieldContainerType *> ignoreTypes;

    return OSG::deepClone(src, shareTypes,    ignoreTypes,
                               shareGroupIds, ignoreGroupIds);
}

/*! Creates a deep copy of \a src, i.e. all fields of \a src are copied, if
    they contain pointers to other FieldContainers these are cloned as well.
    The remaining parameters allow the selection of certain types that are
    either not cloned at all or are shared between \a src and the copy.

    \param[in] src FieldContainer to clone.
    \param[in] shareTypesString Comma separated string of type names that
        should be shared instead of cloned.
    \param[in] ignoreTypesString Comma separated string of type names that
        should be ignored.
    \return deep copy of \a src.
 */
FieldContainerPtr
OSG::deepClone(      FieldContainerPtrConstArg  src,
               const std::string               &shareTypesString,
               const std::string               &ignoreTypesString)
{
    std::vector<const FieldContainerType *> shareTypes;
    std::vector<const FieldContainerType *> ignoreTypes;
    std::vector<UInt16>                     shareGroupIds;
    std::vector<UInt16>                     ignoreGroupIds;

    appendTypesString(shareTypesString,  shareTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    return OSG::deepClone(src, shareTypes,    ignoreTypes,
                               shareGroupIds, ignoreGroupIds);
}

/*! Creates a deep copy of \a src, i.e. all fields of \a src are copied, if
    they contain pointers to other FieldContainers these are cloned as well.
    The remaining parameters allow the selection of certain types that are
    either not cloned at all or are shared between \a src and the copy.

    \param[in] src FieldContainer to clone.
    \param[in] shareTypes Types that should be shared instead of cloned.
    \param[in] ignoreTypes Types that should be ignored.
    \param[in] shareGroupIds Type groups that should be shared instead
        of cloned.
    \param[in] ignoreGroupIds Type groups that should be ignored.
    \return deep copy of \a src.
 */
FieldContainerPtr
OSG::deepClone(
               FieldContainerPtrConstArg                src,
         const std::vector<const FieldContainerType *> &shareTypes,
         const std::vector<const FieldContainerType *> &ignoreTypes,
         const std::vector<UInt16>                     &shareGroupIds,
         const std::vector<UInt16>                     &ignoreGroupIds)
{
    if(src == NullFC)
        return NullFC;

    const FieldContainerType &fcType  = src->getType();
    FieldContainerPtr         fcClone = fcType.createContainer();

    UInt32 fCount = osgMin(fcType            .getNumFieldDescs(),
                           fcClone->getType().getNumFieldDescs() );

    for(UInt32 i = 1; i <= fCount; ++i)
    {
        const FieldDescriptionBase *fDesc = fcType.getFieldDesc(i);

        if(fDesc->isInternal())
            continue;

        const UInt32  fieldId  = fDesc  ->getFieldId();
        const Field  *srcField = src    ->getField (i);
              Field  *dstField = fcClone->editField(i);

        if(dstField != NULL)
        {
            fDesc->copyValues(srcField, dstField);
        }
        else
        {
            fDesc->cloneValuesV(srcField, fieldId, fcClone,
                                shareTypes,    ignoreTypes,
                                shareGroupIds, ignoreGroupIds);
        }
    }

    return fcClone;
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
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINER_INLINE_CVSID;
}

