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

#include "OSGChangeList.h"
#include "OSGContainerPtrFuncs.h"

#include "OSGFieldContainer.h"
#include "OSGFieldContainerType.h"

#include "OSGStatCollector.h"

#ifdef OSG_ENABLE_VALGRIND_CHECKS
#include <valgrind/memcheck.h>
#endif

OSG_BEGIN_NAMESPACE

#define SILENT
#define SILENT_CPTR

/*-------------------------------------------------------------------------*/
/* ContainerChangeEntry                                                    */


void ContainerChangeEntry::commitChanges(UInt32 origin)
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif
    FieldContainer *pTmp =
        FieldContainerFactory::the()->getContainer(uiContainerId);

    if(pTmp != NULL)
    {
#ifndef SILENT
        FLOG(("Commit id %u : type id %d : %s\n",
              uiContainerId,
              pTmp->getTypeId(), pTmp->getType().getCName()));
#endif

        BitVector tmpChanges;

        if (NULL != bvUncommittedChanges)
        {
#ifdef OSG_ENABLE_MEMORY_DEBUGGING
           OSG_ASSERT(*bvUncommittedChanges != 0xDEADBEEF);
#endif
           tmpChanges             = *bvUncommittedChanges;
           whichField            |= *bvUncommittedChanges;
           *bvUncommittedChanges  = TypeTraits<BitVector>::BitsClear;

           pTmp->changed(tmpChanges, origin, 0);
        }
    }
}

void ContainerChangeEntry::release(void)
{
    if(pList == NULL)
        return;

    if(pList->_bReadOnly == false)
        return;

    ChangeList::ChangedStoreIt cIt = std::find(pList->_changedStore.begin(),
                                               pList->_changedStore.end  (),
                                               this                        );

    if(cIt != pList->_changedStore.end())
    {
        pList->_qFreeElements.push_back(this);

        pList->_changedStore.erase(cIt);
    }

    cIt = std::find(pList->_uncommitedChanges.begin(),
                    pList->_uncommitedChanges.end  (),
                    this                             );

    if(cIt != pList->_uncommitedChanges.end())
    {
        pList->_uncommitedChanges.erase(cIt);
    }

}

/*-------------------------------------------------------------------------*/
/* Statistics                                                              */

StatElemDesc<StatIntElem> ChangeList::statNChangedStoreSize(
    "changedStoreSize",
    "number of elements in the changed store",
    StatElemDescBase::RESET_NEVER);

StatElemDesc<StatIntElem> ChangeList::statNCreatedStoreSize(
    "createdStoreSize",
    "number of elements in the created store",
    StatElemDescBase::RESET_NEVER);

StatElemDesc<StatIntElem> ChangeList::statNUnCommittedStoreSize(
    "uncommittedStoreSize",
    "number of elements in the uncommitted store",
    StatElemDescBase::RESET_NEVER);

StatElemDesc<StatIntElem> ChangeList::statNPoolSize(
    "poolSize",
    "number of elements in the entry pool",
    StatElemDescBase::RESET_NEVER);

#ifdef OSG_ENABLE_DEFAULT_READONLY_CHANGELIST
bool ChangeList::_bReadWriteDefault = false;
#else
bool ChangeList::_bReadWriteDefault = true;
#endif

/*-------------------------------------------------------------------------*/
/* Create                                                                  */

ChangeList *ChangeList::create(void)
{
    ChangeList *returnValue = new ChangeList;

    returnValue->_uiAspect  = Thread::getCurrentAspect();

    returnValue->_bExternal = true;

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/* Merge                                                                   */

void ChangeList::merge(ChangeList &other)
{
    ChangedStoreConstIt cIt  = other._createdStore.begin();
    ChangedStoreConstIt cEnd = other._createdStore.end  ();

    while(cIt != cEnd)
    {
        ContainerChangeEntry *pEntry = getNewCreatedEntry();

        pEntry->uiEntryDesc   = (*cIt)->uiEntryDesc;
        pEntry->uiContainerId = (*cIt)->uiContainerId;
        pEntry->whichField    = (*cIt)->whichField;
        pEntry->pList         = this;

        ++cIt;
    }

    cIt  = other._changedStore.begin();
    cEnd = other._changedStore.end  ();

    while(cIt != cEnd)
    {
        if((*cIt)->uiEntryDesc == ContainerChangeEntry::AddReference   ||
           (*cIt)->uiEntryDesc == ContainerChangeEntry::SubReference   ||
           (*cIt)->uiEntryDesc == ContainerChangeEntry::DepSubReference )
        {
            ContainerChangeEntry *pEntry = getNewEntry();

            pEntry->uiEntryDesc   = (*cIt)->uiEntryDesc;
            pEntry->uiContainerId = (*cIt)->uiContainerId;
            pEntry->pList         = this;
        }
        else if((*cIt)->uiEntryDesc == ContainerChangeEntry::Change)
        {
            ContainerChangeEntry *pEntry = getNewEntry();

            pEntry->uiEntryDesc   = ContainerChangeEntry::Change;
            pEntry->pFieldFlags   = (*cIt)->pFieldFlags;
            pEntry->uiContainerId = (*cIt)->uiContainerId;
            pEntry->whichField    = (*cIt)->whichField;
            pEntry->pList         = this;
        }

        ++cIt;
    }
}

/*-------------------------------------------------------------------------*/
/* Fill From Current                                                       */

/*! Fills this changelist with entries that represent the current state of
    the system starting at the container with the given id.
    Prototypes are skipped unless skipPrototypes is false.

    For every container a 'Create' entry and a 'Change' entry (marking all fields
    as modified) is added and as many 'AddReference' entries as the ref count
    of the container.
 */
void ChangeList::fillFromCurrentState(UInt32 uiFieldContainerId,
                                      bool   skipPrototypes     )
{
    this->clear();

    FieldContainerFactory::the()->lockStore();

    FieldContainerFactoryBase::ContainerStoreConstIt sIt  =
        FieldContainerFactory::the()->beginStore();
    FieldContainerFactoryBase::ContainerStoreConstIt sEnd =
        FieldContainerFactory::the()->endStore();

    for(; sIt != sEnd; ++sIt)
    {
        if((*sIt).first < uiFieldContainerId)
            continue;

        FieldContainer *pFC = (*sIt).second->getPtr();

        if(pFC == NULL)
            continue;

        // skip prototypes - unless requested
        if(skipPrototypes == true &&
           (pFC->getType().getPrototype() == pFC  ||
            pFC->getType().getPrototype() == NULL   ))
        {
            continue;
        }

        this->addCreated((*sIt).first, TypeTraits<BitVector>::BitsClear);

        for(Int32 j = 0; j < pFC->getRefCount(); ++j)
            this->addAddRefd((*sIt).first);

        ContainerChangeEntry *pEntry = this->getNewEntry();

        pEntry->uiEntryDesc   = ContainerChangeEntry::Change;
        pEntry->pFieldFlags   = pFC->getFieldFlags();
        pEntry->uiContainerId = (*sIt).first;
        pEntry->whichField    = FieldBits::AllFields;
        pEntry->pList         = this;
    }

    FieldContainerFactory::the()->unlockStore();
}

/*-------------------------------------------------------------------------*/
/* Misc                                                                    */

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
void ChangeList::setAspectTo(UInt32 uiNewAspect)
{
    _uiAspect = uiNewAspect;
}
#endif

/*-------------------------------------------------------------------------*/
/* Delayed SubRef                                                          */

template<> OSG_DLL_EXPORT
void ChangeList::addDelayedSubRef<NoRefCountPolicy>(FieldContainer *)
{
}

template<> OSG_DLL_EXPORT
void ChangeList::addDelayedSubRef<RecordedRefCountPolicy>(FieldContainer *pFC)
{
    _vDelayedRecSubRefs.push_back(pFC);
}

template<> OSG_DLL_EXPORT
void ChangeList::addDelayedSubRef<UnrecordedRefCountPolicy>(
    FieldContainer *pFC)
{
    _vDelayedUnrecSubRefs.push_back(pFC);
}

template<> OSG_DLL_EXPORT
void ChangeList::addDelayedSubRef<WeakRefCountPolicy>(FieldContainer *pFC)
{
    _vDelayedWeakSubRefs.push_back(pFC);
}

void ChangeList::commitDelayedSubRefs(void)
{
#ifndef SILENT
    FLOG(("Committing delayed sub refs unrec/rec/weak %u/%u/%u\n"
          _vDelayedUnrecSubRefs.size(),
          _vDelayedRecSubRefs.size(),
          _vDelayedWeakSubRefs.size()));
#endif

    // Unrec
    std::vector<FieldContainer *>::      iterator vIt  =
        _vDelayedUnrecSubRefs.begin();

    std::vector<FieldContainer *>::const_iterator vEnd =
        _vDelayedUnrecSubRefs.end  ();

    while(vIt != vEnd)
    {
        UnrecordedRefCountPolicy::subRef(*vIt);

        ++vIt;
    }

    _vDelayedUnrecSubRefs.clear();

    // Rec
    vIt  = _vDelayedRecSubRefs.begin();
    vEnd = _vDelayedRecSubRefs.end  ();

    while(vIt != vEnd)
    {
        RecordedRefCountPolicy::subRef(*vIt);

        ++vIt;
    }

    _vDelayedRecSubRefs.clear();


    // Weak
    vIt  = _vDelayedWeakSubRefs.begin();
    vEnd = _vDelayedWeakSubRefs.end  ();

    while(vIt != vEnd)
    {
        WeakRefCountPolicy::subRef(*vIt);

        ++vIt;
    }

    _vDelayedWeakSubRefs.clear();
}

/*-------------------------------------------------------------------------*/
/* Statistics                                                              */

void ChangeList::dump(      UInt32    uiIndent,
                      const BitVector bvFlags ) const
{
    ChangedStoreConstIt cIt  = _createdStore.begin();
    ChangedStoreConstIt cEnd = _createdStore.end  ();

    fprintf(stderr, "CL created dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        std::string szTmp("Unknown");

        if(pTmp != NULL)
        {
            szTmp.assign(pTmp->getType().getName());
        }

        fprintf(stderr, "CE : %u %u | %s\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                szTmp.c_str());

        ++cIt;
    }

    cIt  = _changedStore.begin();
    cEnd = _changedStore.end  ();

    fprintf(stderr, "CL changed dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        std::string szTmp("Unknown");

        if(pTmp != NULL)
        {
            szTmp.assign(pTmp->getType().getName());
        }

        BitVector tmpChanges = 0xDEADBEEF;

        if((*cIt)->bvUncommittedChanges != NULL && pTmp != NULL)
        {
            tmpChanges = *((*cIt)->bvUncommittedChanges);
        }

        fprintf(stderr,
                "CE : %u %u 0x%016"PRIx64" 0x%016"PRIx64" (%p|%p) | %s\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                tmpChanges,
                (*cIt)->whichField,
                (*cIt),
                (*cIt)->bvUncommittedChanges,
                szTmp.c_str());

        ++cIt;
    }

    cIt  = _uncommitedChanges.begin();
    cEnd = _uncommitedChanges.end  ();

    fprintf(stderr, "CL uncommited dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        std::string szTmp("Unknown");

        if(pTmp != NULL)
        {
            szTmp.assign(pTmp->getType().getCName());
        }

        BitVector tmpChanges = 0xDEADBEEF;

        if((*cIt)->bvUncommittedChanges != NULL && pTmp != NULL)
        {
            tmpChanges = *((*cIt)->bvUncommittedChanges);
        }

        fprintf(stderr,
                "CE : %u %u 0x%016"PRIx64" 0x%016"PRIx64" (%p|%p) | %s\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                tmpChanges,
                (*cIt)->whichField,
                (*cIt),
                (*cIt)->bvUncommittedChanges,
                szTmp.c_str());

        ++cIt;
    }

    cIt  = _workStore.begin();
    cEnd = _workStore.end  ();

    fprintf(stderr, "CL workstore dump\n");

    while(cIt != cEnd)
    {
        for(UInt32 i = 0; i < uiIndent + 4; ++i)
        {
            fprintf(stderr, " ");
        }

        FieldContainer *pTmp =
            FieldContainerFactory::the()->getContainer((*cIt)->uiContainerId);

        BitVector tmpChanges = 0xDEADBEEF;

        if((*cIt)->bvUncommittedChanges != NULL && pTmp != NULL)
        {
            tmpChanges = *((*cIt)->bvUncommittedChanges);
        }

        fprintf(stderr, "CE : %u %u 0x%016"PRIx64" 0x%016"PRIx64"\n",
                (*cIt)->uiEntryDesc,
                (*cIt)->uiContainerId,
                tmpChanges,
                (*cIt)->whichField);

        ++cIt;
    }
}

void ChangeList::dumpListSizes(void) const
{
    fprintf(stderr, "CL : CH_S : %"PRISize" | CR_S : %"PRISize" | UC_S : %"
            PRISize" | P_S %"PRISize"\n",
            _changedStore.size(),
            _createdStore.size(),
            _uncommitedChanges.size(),
            _entryPool.size() * 32 );
}

void ChangeList::fillStatistic(StatCollector *pColl) const
{
    if(pColl == NULL)
        return;

    pColl->getElem(statNChangedStoreSize    )->set(_changedStore     .size());
    pColl->getElem(statNCreatedStoreSize    )->set(_createdStore     .size());
    pColl->getElem(statNUnCommittedStoreSize)->set(_uncommitedChanges.size());
    pColl->getElem(statNPoolSize            )->set(_entryPool.size() * 32   );

}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ChangeList::ChangeList(void) :
     Inherited           (                   ),
    _entryPool           (                   ),
    _currentPoolElement  (                   ),
    _currentEntry        (                   ),
    _changedStore        (                   ),
    _createdStore        (                   ),
    _uncommitedChanges   (                   ),
    _workStore           (                   ),
    _uiAspect            (                  0),
    _iSubRefLevel        (                  0),
    _bExternal           (false              ),
    _bReadOnly           (!_bReadWriteDefault),
    _vDelayedUnrecSubRefs(                   ),
    _vDelayedRecSubRefs  (                   ),
    _vDelayedWeakSubRefs (                   ),
    _qFreeElements       (                   )
{
    _entryPool.push_back(ChangeEntryStore());

    _currentPoolElement = _entryPool.begin();

    _currentPoolElement->resize(32);

    _currentEntry = _currentPoolElement->begin();
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

ChangeList::~ChangeList(void)
{
}

/*-------------------------------------------------------------------------*/
/* Add Entries                                                             */

void ChangeList::addAddRefd(const UInt32 uiContainerId)
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    FLOG(("Add AddRef id %u\n", uiContainerId));
#endif

    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::AddReference;
    pEntry->uiContainerId = uiContainerId;
    pEntry->pList         = this;
}

void ChangeList::addSubRefd(const UInt32 uiContainerId,
                                  bool   ignoreLevel  )
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    FLOG(("Add SubRef id %u\n", uiContainerId));
#endif

    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewEntry();

    if(_iSubRefLevel == 0 || ignoreLevel == true)
    {
        pEntry->uiEntryDesc   = ContainerChangeEntry::SubReference;
    }
    else
    {
        pEntry->uiEntryDesc   = ContainerChangeEntry::DepSubReference;
    }

    pEntry->uiContainerId = uiContainerId;
    pEntry->pList         = this;
}

void ChangeList::addCreated(const UInt32    uiContainerId,
                                  BitVector bFlags       )
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    FieldContainer *fcPtr =
        FieldContainerFactory::the()->getContainer(uiContainerId);

    FLOG(("Add Create id %u : type id %d : %s\n",
          uiContainerId,
          fcPtr != NULL ? fcPtr->getTypeId() : -1,
          fcPtr != NULL ? fcPtr->getType  ().getCName() : "Unknown"));
#endif

    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewCreatedEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::Create;
    pEntry->uiContainerId = uiContainerId;
    pEntry->whichField    = bFlags;
}

void ChangeList::addNewField(const UInt32    uiContainerId,
                                   BitVector bFlags       )
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(uiContainerId);
#endif

#ifndef SILENT
    FieldContainer *fcPtr =
        FieldContainerFactory::the()->getContainer(uiContainerId);

    FLOG(("Add NewField id %u : type id %d : %s\n",
          uiContainerId,
          fcPtr != NULL ? fcPtr->getTypeId() : -1,
          fcPtr != NULL ? fcPtr->getType  ().getCName() : "Unknown"));
#endif

    if(_bReadOnly == true)
        return;

    ContainerChangeEntry *pEntry = getNewCreatedEntry();

    pEntry->uiEntryDesc   = ContainerChangeEntry::AddField;
    pEntry->uiContainerId = uiContainerId;
    pEntry->whichField    = bFlags;
}

void ChangeList::addUncommited(ContainerChangeEntry *pEntry)
{
    OSG_ASSERT(NULL != pEntry);

#ifndef SILENT
    FLOG(("Add Uncommited id %u\n", pEntry->uiContainerId));
#endif

    _uncommitedChanges.push_back(pEntry);
}

/*-------------------------------------------------------------------------*/
/* Entry Pool                                                              */


ContainerChangeEntry *ChangeList::createNewEntry(void)
{
    if(_qFreeElements.empty() == false)
    {
        ContainerChangeEntry *returnValue = _qFreeElements.back();

        _qFreeElements.pop_back();

        return returnValue;
    }

    if(_currentEntry == _currentPoolElement->end())
    {
        ++_currentPoolElement;

        if(_currentPoolElement == _entryPool.end())
        {
            _entryPool.push_back(ChangeEntryStore());

              _currentPoolElement = _entryPool.end();
            --_currentPoolElement;

              _currentPoolElement->resize(32);
        }

        _currentEntry = _currentPoolElement->begin();
    }

    ContainerChangeEntry *returnValue = &(*_currentEntry);

    ++_currentEntry;

    return returnValue;
}

void ChangeList::clearPool(void)
{
    _currentPoolElement = _entryPool          .begin();
    _currentEntry       = _currentPoolElement->begin();

    _changedStore     .clear();
    _createdStore     .clear();
    _uncommitedChanges.clear();

    _qFreeElements.clear();
}

/*-------------------------------------------------------------------------*/
/* Helper                                                                  */

void ChangeList::doCommitChanges(UInt32 origin)
{
    if(_workStore.empty() == false)
    {
        SFATAL << "Work store is non-empty, concurrent commit in progress."
               << std::endl;
    }

    const UInt32 loopLimit    = 25;
    UInt32       loopCount    = 0;
    bool         loopDetected = false;

    _workStore.clear();

    while((_uncommitedChanges.empty() == false) &&
          (loopDetected               == false)   )
    {
        _workStore        .swap (_uncommitedChanges);
        _uncommitedChanges.clear();

        ChangedStore::iterator       changesIt  = _workStore.begin();
        ChangedStore::const_iterator changesEnd = _workStore.end  ();

        while(changesIt != changesEnd)
        {
            OSG_ASSERT(NULL != (*changesIt));

            if((*changesIt)->uiEntryDesc == ContainerChangeEntry::Change)
            {
                (*changesIt)->commitChanges(origin);
            }

            ++changesIt;
        }

        _workStore.clear();

        if(loopCount++ > loopLimit)
        {
           loopDetected = true;

           SFATAL << "Loop detected while committing changes after "
                  << loopLimit << " iterations."
                  << std::endl;
        }
    }
}

void ChangeList::doApply(bool bClear)
{
    if(_bReadOnly == true)
    {
        FWARNING(("Read-only changelist, can not apply\n"));
        return;
    }

    UInt32      srcAspect = _uiAspect;
    UInt32      dstAspect = Thread::getCurrentAspect();
    ChangeList *pDstCL    = Thread::getCurrentChangeList();

#ifdef OSG_MT_CPTR_ASPECT
    FieldContainer      *pSrc  = NULL;
    FieldContainer      *pDst  = NULL;

    ChangedStoreConstIt  ccIt  = _createdStore.begin();
    ChangedStoreConstIt  ccEnd = _createdStore.end  ();

    while(ccIt != ccEnd)
    {
        if((*ccIt)->uiEntryDesc != ContainerChangeEntry::Create)
        {
            ++ccIt;
            continue;
        }

        AspectStoreP pHandler =
            FieldContainerFactory::the()->getContainerHandler(
                (*ccIt)->uiContainerId);

        if(pHandler == NULL)
        {
#ifndef SILENT_CPTR
            FWARNING(("CL apply: Aspect store NULL, id %u\n",
                      (*ccIt)->uiContainerId));
#endif
            ++ccIt;
            continue;
        }

        pSrc = pHandler->getPtr(srcAspect);
        pDst = pHandler->getPtr(dstAspect);

        if(pSrc == NULL)
        {
#ifndef SILENT_CPTR
            FWARNING(("CL apply: Src NULL, id %u\n",
                      (*ccIt)->uiContainerId));
#endif
            ++ccIt;
            continue;
        }

        if(pDst == NULL)
        {
            if(0x0000 == ((*ccIt)->whichField & FCLocal::MTMask))
            {
                pDst = pSrc->getType().createAspectCopy(pSrc,
                                                        (*ccIt)->uiContainerId);

#ifndef SILENT_CPTR
                FLOG(("CL apply: Setup aspect store, id %u %p\n",
                      (*ccIt)->uiContainerId,
                      pDst));
#endif

                if(pDst != NULL)
                    pDst->setupAspectStore(pHandler);

#ifndef SILENT_CPTR
                pHandler->dump();
#endif
            }
        }

        ++ccIt;
    }

#ifndef SILENT_CPTR
    FLOG(("CL apply: src aspect %u -> dst aspect %u\n",
          srcAspect, dstAspect));
#endif

    ChangedStoreIt      cIt      = _changedStore.begin();
    ChangedStoreConstIt cEnd     = _changedStore.end  ();

    BitVector           syncMode = 0;
    AspectOffsetStore   oOffsets;

    while(cIt != cEnd)
    {
        AspectStoreP pHandler =
            FieldContainerFactory::the()->getContainerHandler(
                (*cIt)->uiContainerId);

        if(pHandler == NULL)
        {
            ++cIt;
            continue;
        }

        pSrc = pHandler->getPtr(srcAspect);
        pDst = pHandler->getPtr(dstAspect);

#ifndef SILENT_CPTR
        FLOG(("CL apply: process changes, id %u, src %p %s, dst %p %s\n",
              (*cIt)->uiContainerId,
              pSrc,
              pSrc != NULL ? pSrc->getType().getCName() : "null",
              pDst,
              pDst != NULL ? pDst->getType().getCName() : "null"));
#endif

        if(pDst == NULL &&
           pSrc != NULL)
        {
            if((pSrc->getFieldFlags()->_bNamespaceMask & FCLocal::MTMask) !=
               TypeTraits<BitVector>::BitsClear             )
            {
                pDst = pSrc->getType().createAspectCopy(pSrc,
                                                        (*cIt)->uiContainerId);

                if(pDst != NULL)
                {
                    pDst->setupAspectStore(pHandler);
                }

#ifndef SILENT_CPTR
                pHandler->dump();
#endif
            }
            else
            {
                ++cIt;
                continue;
            }
        }

#ifndef SILENT_CPTR
        FLOG(("CL apply: process changes, id %u, src %p %s, dst %p %s "
              "| src aspect %u dst aspect %u | store %p\n",
              (*cIt)->uiContainerId,
              pSrc,
              pSrc != NULL ? pSrc->getType().getCName() : "null",
              pDst,
              pDst != NULL ? pDst->getType().getCName() : "null",
              srcAspect, dstAspect, pHandler));
#endif

        if((*cIt)->uiEntryDesc == ContainerChangeEntry::Change)
        {
            if(pSrc != NULL && pDst != NULL) // be safe for now
            {
                BitVector mask = ((*cIt)->whichField &
                                  pSrc->getFieldFlags()->_bThreadLocalFlags);

                if(mask != 0x0000)
                {
                    pHandler->fillOffsetArray(oOffsets, pDst);

#ifndef SILENT_CPTR
                    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); ++i)
                    {
                        fprintf(stderr, "offset %u %d\n", i, oOffsets[i]);
                    }
#endif

                    UInt32 uiSInfo = (srcAspect << 24) |
                                     (dstAspect << 16);

                    pDst->execSyncV(*pSrc,
                                    mask,
                                    oOffsets,
                                    syncMode,
                                    uiSInfo);
                }

                if(bClear == true)
                {
                    pSrc->clearChangeEntry(*cIt);
                }
            }
        }
        else if((*cIt)->uiEntryDesc == ContainerChangeEntry::AddReference)
        {
#ifndef SILENT_CPTR
            FLOG(("CL apply: Add ref, id %u, type id %u %s\n",
                  (*cIt)->uiContainerId,
                  pDst != NULL ? pDst->getTypeId()          : -1,
                  pDst != NULL ? pDst->getType().getCName() : "null"));
#endif

            UnrecordedRefCountPolicy::addRef(pDst);
        }
        else if((*cIt)->uiEntryDesc == ContainerChangeEntry::SubReference)
        {
#ifndef SILENT_CPTR
            FLOG(("CL apply: Sub ref, id %u, type id %u %s\n",
                  (*cIt)->uiContainerId,
                  pDst != NULL ? pDst->getTypeId()          : -1,
                  pDst != NULL ? pDst->getType().getCName() : "null"));
#endif

            if(pDst != NULL)
            {
                pDstCL->addDelayedSubRef<UnrecordedRefCountPolicy>(pDst);
            }
        }

        ++cIt;
    }

    pDstCL->commitChanges       (ChangedOrigin::Sync);
    pDstCL->commitDelayedSubRefs();

#endif
}

void ChangeList::doClear(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    UInt32 srcAspect = _uiAspect;
    UInt32 dstAspect = Thread::getCurrentAspect();

    if(srcAspect != dstAspect)
    {
        FWARNING(("CL clear: aspects do not match. src %u dst %u\n",
                  srcAspect, dstAspect));
        return;
    }

    ChangedStoreIt       cIt  = _changedStore.begin();
    ChangedStoreConstIt  cEnd = _changedStore.end  ();

    FieldContainer      *pDst = NULL;

    while(cIt != cEnd)
    {
        AspectStoreP pHandler =
            FieldContainerFactory::the()->getContainerHandler(
                (*cIt)->uiContainerId);

        if(pHandler == NULL)
        {
            ++cIt;
            continue;
        }

        pDst = pHandler->getPtr(dstAspect);

        if(pDst != NULL)
        {
            pDst->clearChangeEntry(*cIt);
        }

        ++cIt;
    }
#endif
}

OSG_END_NAMESPACE
