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

#include "OSGFieldContainer.h"
#include "OSGContainerPtrFuncs.h"
#include "OSGStringUtils.h"
#include "OSGNameAttachment.h"
#include "OSGFieldContainerUtils.h"

#include <algorithm>
#include <cctype>

#define SILENT

#define OSG_AREAD(A) static_cast<RefCountStore const volatile &>(A);

OSG_BEGIN_NAMESPACE

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

FieldContainer::TypeObject FieldContainer::_type(
    FieldContainer::getClassname(),
    "ReflexiveContainer",
    "FieldContainer",
    0,
    NULL,
    NULL,
    NULL,
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&FieldContainer::classDescInserter)),
    false,
    0);


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

#define WS30 "                              "

void FieldContainer::dumpFieldInfo(void) const
{
    const TypeObject &oType = this->getType();

    fprintf(stderr, "Dump Container (%s) Field Info\n",
            oType.getCName());

    for(UInt32 i = 1; i <= oType.getNumFieldDescs(); ++i)
    {
        FieldDescriptionBase *pDesc = oType.getFieldDesc(i);

        if(pDesc != NULL)
        {
            UInt32 uiTmp  = (_bvChanged & pDesc->getFieldMask()) != 0x0000;
            UInt32 uiTmp1 = 0x0000;

            fprintf(stderr, WS30"                                  ch : %x\r", 
                    uiTmp);


            uiTmp  = (pDesc->getFlags() & Field::FClusterLocal) != 0x0000;
            uiTmp1 = (_pFieldFlags->_bClusterLocalFlags & 
                       pDesc      ->getFieldMask()       ) == 0x0000;

            fprintf(stderr, WS30"                     cl : %x | %x\r",
                    uiTmp,
                    uiTmp1);


            uiTmp  = (pDesc->getFlags() & Field::FThreadLocal) != 0x0000;
            uiTmp1 = (_pFieldFlags->_bThreadLocalFlags & 
                       pDesc      ->getFieldMask()     ) == 0x0000;

            fprintf(stderr, WS30"        tl : %x | %x\r",
                    uiTmp,
                    uiTmp1);


            fprintf(stderr, "(%d) : %s :\r", 
                    i, 
                    pDesc->getCName());


            fprintf(stderr, "\n");

#if 0
            fprintf(stderr, "0x%016" PRIx64 " 0x%016" PRIx64 "\n",
                    _pFieldFlags->_bClusterLocalFlags,
                    pDesc      ->getFieldMask());
#endif
        }
        else
        {
            fprintf(stderr, "(%d) : NULL\n", i);
        }
    }
}

void FieldContainer::markFieldsThreadLocal(const BitVector bvFieldMasks)
{
    _pFieldFlags->_bThreadLocalFlags &= ~bvFieldMasks;
}

void FieldContainer::unmarkFieldsThreadLocal(const BitVector bvFieldMasks)
{
    _pFieldFlags->_bThreadLocalFlags |= bvFieldMasks;
}

void FieldContainer::markFieldsClusterLocal(const BitVector bvFieldMasks)
{
    _pFieldFlags->_bClusterLocalFlags &= ~bvFieldMasks;
}

void FieldContainer::unmarkFieldsClusterLocal(const BitVector bvFieldMasks)
{
    _pFieldFlags->_bClusterLocalFlags |= bvFieldMasks;
}


void FieldContainer::copyFromBin(BinaryDataHandler  &,
                                 ConstFieldMaskArg   whichField)
{
    editSField(whichField);
}


void FieldContainer::invalidateVolume(void)
{
}

/*! Internal function to establish a link from this container to its parent.
    \warning Do NOT call this function manually, it is reserved for use by the
    system.
    
    \param[in] pParent The parent.
    \param[in] childFieldId Id of the field that holds the
        pointer to \em this.
    \param[in] parentFieldId Id of the field that should store the
        pointer to \em pParent.
    
    \return \c true if the linking succeeded, \c false otherwise.
    
    \dev
        This is normally overridden by generated code.
    \enddev
 */

bool FieldContainer::linkParent(FieldContainer * const pParent,
                                UInt16           const childFieldId,
                                UInt16           const parentFieldId) 
{
    return false;
}

/*! Internal function to remove a link from this container to its parent.
    \warning Do NOT call this function manually, it is reserved for use by the
    system.
    
    \param[in] pParent The parent.
    \param[in] parentFieldId Id of the field (in \c this) that stores the
        pointer to \a pParent.
    
    \return \c true if the unlinking succeeded, \c false otherwise.
    
    \dev
        This is normally overridden by generated code.
    \enddev
 */

bool FieldContainer::unlinkParent(FieldContainer * const pParent,
                                  UInt16           const parentFieldId) 
{
    return false;
}

/*! Internal function to remove a link from this container to a child.
    \warning Do NOT call this function manually, it is reserved for use by the
    system.
    
    \param[in] pChild Child to unlink.
    \param[in] childFieldId Id of the field (in \c this) that holds the
        pointer to \a pChild.
    
    \return \c true if the unlinking succeeded, \c false otherwise.
    
    \dev
        This is normally overridden by generated code.
    \enddev
 */
            
bool FieldContainer::unlinkChild(FieldContainer * const pChild,
                                 UInt16           const childFieldId) 
{
    return false;
}

void FieldContainer::registerChangedContainer(void)
{
#ifndef SILENT
    fprintf(stderr, "reg changed %p 0x%016llx\n",
            _pContainerChanges, _bvChanged);
#endif

    osgSpinLock(&_uiContainerId, SpinLockBit);

#ifdef OSG_DEBUG
    // Check if the container is registered with the FC factory.
    // This catches e.g. cases where fields are modified in the c'tor instead
    // of the onCreate/onCreateAspect functions.
    if(_uiContainerId == 0)
    {
        SWARNING << "FieldContainer::registerChangedContainer called without "
                 << "valid _uiContainerId!"
                 << std::endl;
    }
#endif

    ChangeList* pCL = Thread::getCurrentChangeList();

    if(_pContainerChanges == NULL)
    {
        _pContainerChanges                       = pCL->getNewEntry();

        _pContainerChanges->uiEntryDesc          = ContainerChangeEntry::Change;
        _pContainerChanges->pFieldFlags          = _pFieldFlags;
        _pContainerChanges->uiContainerId        = this->getId();
        _pContainerChanges->bvUncommittedChanges = &_bvChanged;
    }
    else
    {
        if(_pContainerChanges->pList != Thread::getCurrentChangeList())
        {
           std::string name("Unknown Name");

           AttachmentContainer *attachment_container =
               dynamic_cast<AttachmentContainer*>(this);

           if(NULL != attachment_container)
           {
               const Char8 *temp_name = getName(attachment_container);

               if(NULL != temp_name)
               {
                   name = temp_name;
               }
           }

           SWARNING 
               << "Unsafe change from multiple threads for FieldContainer ["
               << getType().getCName() << "]: " << name << std::endl;
        }
    }

    pCL->addUncommited(_pContainerChanges);

    osgSpinLockRelease(&_uiContainerId, SpinLockClearMask);
}

void FieldContainer::registerChangedContainerV(void)
{
    registerChangedContainer();
}


bool FieldContainer::deregister(UInt32 uiContainerId)
{
    bool retVal = false;

    if(GlobalSystemState < PostShutdown)
    {
        retVal = 
            FieldContainerFactory::the()->deregisterContainer(uiContainerId);
    }
    else
    {
        // can not use logging here, it is shut down already
        fprintf(stderr,
                "WARNING: FieldContainer::deregister: Container [%d @ %p] "
                "is alive past OpenSG shutdown!\n", 
                uiContainerId, 
                static_cast<void *>(this));
    }

    return retVal;
}

void FieldContainer::resolveLinks(void)
{
    callChangedFunctors(0, ChangedOrigin::External);
}

FieldContainer *FieldContainer::findNamedComponent(const Char8 *szName) 
{
    return OSG::findNamedComponent(this, szName);
}

void FieldContainer::subReferenceRecorded(void)
{
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::subReference [%p] [%d] [%s] START - [%d %d]\n",
           this, this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif

    RefCountStore  tmpRefCnt   = osgAtomicExchangeAndAdd(&_iRefCount, -1);
    ChangeList    *pChangeList = Thread::getCurrentChangeList();

    if(tmpRefCnt <= 1)
    {
        pChangeList->incSubRefLevel();

        this->resolveLinks();

        pChangeList->decSubRefLevel();
        pChangeList->addSubRefd    (Inherited::getId());

        osgSpinLock(&_uiContainerId, SpinLockBit);

        RefCountStore tmpWeakRefCnt = OSG_AREAD(_iWeakRefCount);

        _uiContainerId |= DeadContainerBit;

        osgSpinLockRelease(&_uiContainerId, SpinLockClearMask);

        if(tmpWeakRefCnt <= 0)
        {
#ifdef OSG_MT_CPTR_ASPECT
            this->onDestroyAspect(Inherited::getId(), 
                                  Thread::getCurrentAspect());

            if(_pAspectStore->getRefCount() == 1)
            {
                this->deregister(Inherited::getId());
                this->onDestroy (Inherited::getId());
            }

            _pAspectStore->removePtrForAspect(Thread::getCurrentAspect());

            OSG::subRef(_pAspectStore);
            _pAspectStore = NULL;
#else
            this->deregister     (Inherited::getId()   );
            this->onDestroyAspect(Inherited::getId(), 0);
            this->onDestroy      (Inherited::getId()   );
#endif
            
            delete this;
        }
        else
        {
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
            FINFO(
                ("FieldContainer::subReference [%p] [%d] [%s] STOP A [%d %d]\n",
                 this, 
                 this->getId(), 
                 this->getType().getCName(),
                 this->_iRefCount, 
                 this->_iWeakRefCount));
#endif
        }
    }
    else
    {
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
        FINFO(
            ("FieldContainer::subReference [%p] [%d] [%s] STOP B [%d %d]\n",
             this, 
             this->getId(), 
             this->getType().getCName(),
             this->_iRefCount, 
             this->_iWeakRefCount));
#endif

        pChangeList->addSubRefd(Inherited::getId());
    }

}

void FieldContainer::subReferenceUnrecorded(void)
{
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::subReferenceUnrec [%p] [%d] [%s] START - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif

    RefCountStore tmpRefCnt = osgAtomicExchangeAndAdd(&_iRefCount, -1);

    if(tmpRefCnt <= 1)
    {
        this->resolveLinks();

        osgSpinLock(&_uiContainerId, SpinLockBit);

        RefCountStore tmpWeakRefCnt = OSG_AREAD(_iWeakRefCount);

        _uiContainerId |= DeadContainerBit;

        osgSpinLockRelease(&_uiContainerId, SpinLockClearMask);

        if(tmpWeakRefCnt <= 0)
        {
#ifdef OSG_MT_CPTR_ASPECT
            this->onDestroyAspect(Inherited::getId(), 
                                  Thread::getCurrentAspect());
           
            if(_pAspectStore->getRefCount() == 1)
            {
                this->deregister(Inherited::getId());
                this->onDestroy (Inherited::getId());
            }

            _pAspectStore->removePtrForAspect(Thread::getCurrentAspect());
            
            OSG::subRef(_pAspectStore);
            _pAspectStore = NULL;
#else
            this->deregister     (Inherited::getId()   );
            this->onDestroyAspect(Inherited::getId(), 0);
            this->onDestroy      (Inherited::getId()   );
#endif

            delete this;
        }
        else
        {
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
            FINFO(
                ("FieldContainer::subReferenceUnrec [%p] [%d] [%s] "
                 "STOP A [%d %d]\n",
                 this, 
                 this->getId(), 
                 this->getType().getCName(),
                 this->_iRefCount, 
                 this->_iWeakRefCount));
#endif
        }
    }
    else
    {
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
        FINFO(("FieldContainer::subReferenceUnrec [%p] [%d] [%s] "
               "STOP - [%d %d]\n",
               this, 
               this->getId(), 
               this->getType().getCName(),
               this->_iRefCount, 
               this->_iWeakRefCount));
#endif
    }

}

void FieldContainer::subWeakReference(void)
{
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::subWeakReference [%p] [%d] [%s] START - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif

    osgSpinLock(&_uiContainerId, SpinLockBit);

    RefCountStore tmpWeakRefCnt = osgAtomicExchangeAndAdd(&_iWeakRefCount, -1);

#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::subWeakReference [%p] [%d] [%s] STOP - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif

    if((0x0000 != (_uiContainerId & DeadContainerBit)) && tmpWeakRefCnt <= 1)
    {
        osgSpinLockRelease(&_uiContainerId, SpinLockClearMask);
        
        this->resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
        this->onDestroyAspect(Inherited::getId(), Thread::getCurrentAspect());

        if(_pAspectStore->getRefCount() == 1)
        {
            this->deregister(Inherited::getId());
            this->onDestroy (Inherited::getId());
        }

        _pAspectStore->removePtrForAspect(Thread::getCurrentAspect());

        OSG::subRef(_pAspectStore);
        _pAspectStore = NULL;
#else
        this->deregister     (Inherited::getId()   );
        this->onDestroyAspect(Inherited::getId(), 0);
        this->onDestroy      (Inherited::getId()   );
#endif

        delete this;
    }
    else
    {
        osgSpinLockRelease(&_uiContainerId, SpinLockClearMask);
    }
}

void FieldContainer::subReferenceUnresolved(void)
{
    RefCountStore tmpRefCnt = osgAtomicExchangeAndAdd(&_iRefCount, -1);

    if(tmpRefCnt <= 1)
    {
        Thread::getCurrentChangeList()->addSubRefd(Inherited::getId());

#ifdef OSG_MT_CPTR_ASPECT
        this->onDestroyAspect(Inherited::getId(), Thread::getCurrentAspect());

        if(_pAspectStore->getRefCount() == 1)
        {
            this->deregister(Inherited::getId());
            this->onDestroy (Inherited::getId());
        }

        _pAspectStore->removePtrForAspect(Thread::getCurrentAspect());

        OSG::subRef(_pAspectStore);
        _pAspectStore = NULL;
#else
        this->deregister     (Inherited::getId()   );
        this->onDestroyAspect(Inherited::getId(), 0);
        this->onDestroy      (Inherited::getId()   );
#endif

        delete this;
    }
    else
    {
        Thread::getCurrentChangeList()->addSubRefd(Inherited::getId());
    }
}

/*---------------------------------------------------------------------*/
/*! \name Container cloning                                            */
/*! \{                                                                 */

/*! Fills \a types with the type objects corresponding to the types named in
    \a typeNames. This is a helper function for deepClone.
    The elements of \a typeNames must be names of FieldContainer types, if a
    type name is not found there is no type object inserted into \a types, i.e.
    \a types may be shorter than \a typeNames.

    \param[in] typeNames FieldContainer type names.
    \param[out] types Type objects corresponding to \a typeNames.

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

void appendTypesVector(
    const std::vector<std::string>                         &typeNames,
          std::vector<const OSG::ReflexiveContainerType *> &types     )
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

void appendGroupsVector(const std::vector<std::string> &groupNames,
                              std::vector<OSG::UInt16> &groupIds   )
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

void appendTypesString(
    const std::string                                      &typesString,
          std::vector<const OSG::ReflexiveContainerType *> &types       )
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

FieldContainerTransitPtr deepClone(
          FieldContainer const      *src,
    const std::vector<std::string>  &shareTypeNames,
    const std::vector<std::string>  &ignoreTypeNames,
    const std::vector<std::string>  &shareGroupNames,
    const std::vector<std::string>  &ignoreGroupNames)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         shareGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesVector (shareTypeNames,   shareTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(shareGroupNames,  shareGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    return deepClone(src, shareTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

FieldContainerTransitPtr deepClone(
          FieldContainer const      *src,
    const std::vector<OSG::UInt16>       &shareGroupIds,
    const std::vector<OSG::UInt16>       &ignoreGroupIds)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;

    return deepClone(src, shareTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

FieldContainerTransitPtr deepClone(      
          OSG::FieldContainer const  *src,
    const std::string                &shareTypesString,
    const std::string                &ignoreTypesString)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         shareGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesString(shareTypesString,  shareTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    return deepClone(src, shareTypes,    ignoreTypes,
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

    \ingroup GrpBaseFieldContainerFuncs
    \relatesalso FieldContainer
 */

FieldContainerTransitPtr deepClone(
          OSG::FieldContainer const                        *src,
    const std::vector<const OSG::ReflexiveContainerType *> &shareTypes,
    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes,
    const std::vector<OSG::UInt16>                         &shareGroupIds,
    const std::vector<OSG::UInt16>                         &ignoreGroupIds)
{
    if(src == NULL)
        return FieldContainerTransitPtr(NULL);

    const FieldContainerType &fcType  = src->getType();
    FieldContainerTransitPtr  fcClone = fcType.createContainer();

    UInt32 fCount = osgMin(fcType            .getNumFieldDescs(),
                           fcClone->getType().getNumFieldDescs() );

    for(UInt32 i = 1; i <= fCount; ++i)
    {
        const FieldDescriptionBase *fDesc = fcType.getFieldDesc(i);

        if(fDesc->isInternal())
            continue;

        GetFieldHandlePtr  srcField = src    ->getField (i);
        EditFieldHandlePtr dstField = fcClone->editField(i);

        if(dstField == NULL || dstField->isValid() == false ||
           srcField == NULL || srcField->isValid() == false)
        {
            continue;
        }

        if(srcField->isPointerField() == false)
        {
            dstField->copyValues(srcField);
        }
        else
        {
            // get type info for values stored in field
            const DataType &contentType = srcField->getType().getContentType();

            // check if it's a "pointer to FC" type (needed, because
            // AttachmentMap also passes the above isPointerType() check)
            const PointerType *pointerType =
                dynamic_cast<const PointerType *>(&contentType);

            // punt, share if it is something that is not "pointer to FC"
            if(pointerType == NULL)
            {
                dstField->shareValues(srcField);
                continue;
            }

            // get type info for pointed-to FC type
            const ReflexiveContainerType *rcType =
                dynamic_cast<const ReflexiveContainerType *>(
                    &pointerType->getContentType());

            // punt, share if it is something that is not derived from RC
            if(rcType == NULL)
            {
                dstField->shareValues(srcField);
                continue;
            }

            // check if type should be ignored
            if(!TypePredicates::typeInGroupIds(
                    ignoreGroupIds.begin(),
                    ignoreGroupIds.end  (), *rcType) &&
               !TypePredicates::typeDerivedFrom(
                    ignoreTypes.begin(),
                    ignoreTypes.end  (), *rcType)      )
            {
                // check if type should by shared
                if(TypePredicates::typeInGroupIds(
                        shareGroupIds.begin(),
                        shareGroupIds.end  (), *rcType) ||
                   TypePredicates::typeDerivedFrom(
                        shareTypes.begin(),
                        shareTypes.end  (), *rcType)      )
                {
                    dstField->shareValues(srcField);
                }
                else
                {
                    dstField->cloneValues(srcField,
                                          shareTypes,
                                          ignoreTypes,
                                          shareGroupIds,
                                          ignoreGroupIds);
                }
            }
        }
    }

    return fcClone;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
