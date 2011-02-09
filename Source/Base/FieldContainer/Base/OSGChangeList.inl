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

/*-------------------------------------------------------------------------*/
/* ContainerChangeEntry                                                    */

inline
ContainerChangeEntry::ContainerChangeEntry(void) :
    uiEntryDesc         (0   ),
    uiContainerId       (0   ),
    pFieldFlags         (NULL),
    whichField          (0   ),
    bvUncommittedChanges(NULL),
    pList               (NULL)
{
}

inline
void ContainerChangeEntry::clear(ChangeList *pListParent)
{
    uiEntryDesc          = 0;
    uiContainerId        = 0;
    pFieldFlags          = NULL;
    whichField           = 0;
    bvUncommittedChanges = NULL;
    pList                = pListParent;
}

/*-------------------------------------------------------------------------*/
/* Commit                                                                  */

inline
void ChangeList::commitChanges(void)
{
    doCommitChanges();
}

inline
void ChangeList::commitChangesAndClear(void)
{
    doCommitChanges();
    clear          ();
}

/*-------------------------------------------------------------------------*/
/* Apply                                                                   */

inline
void ChangeList::applyAndClear(void)
{
    doApply  (true);
    clearPool(    );
}

inline
void ChangeList::applyNoClear (void)
{
    doApply(false);
}

/*-------------------------------------------------------------------------*/
/* Clear                                                                   */

inline
void ChangeList::clear(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    if(_uiAspect != Thread::getCurrentAspect())
    {
        SWARNING << "ChangeList::clear: Aspects don't match "
                 << _uiAspect << " " << Thread::getCurrentAspect()
                 << std::endl;

        return;
    }
#endif

    doClear  ();
    clearPool();
}

/*-------------------------------------------------------------------------*/
/* Changed/Created Store                                                   */

inline
ChangeList::ChangedStoreConstIt ChangeList::begin(void) const
{
    return _changedStore.begin();
}

inline
ChangeList::ChangedStoreConstIt ChangeList::end(void) const
{
    return _changedStore.end();
}

inline
ChangeList::ChangedStoreConstIt ChangeList::beginCreated(void) const
{
    return _createdStore.begin();
}

inline
ChangeList::ChangedStoreConstIt ChangeList::endCreated(void) const
{
    return _createdStore.end();
}

inline
UInt32 ChangeList::getNumCreated(void) const
{
    return _createdStore.size();
}

inline
UInt32 ChangeList::getNumChanged(void) const
{
    return _changedStore.size();
}

/*-------------------------------------------------------------------------*/
/* Misc                                                                    */

inline
void ChangeList::setReadWriteDefault(bool bReadWrite)
{
    _bReadWriteDefault = bReadWrite;
}

/*-------------------------------------------------------------------------*/
/* Entry Pool                                                              */

inline
ContainerChangeEntry *ChangeList::getNewEntry(void)
{
    ContainerChangeEntry *returnValue = createNewEntry();
    returnValue->clear(this);

    _changedStore.push_back(returnValue);

    return returnValue;
}

inline
ContainerChangeEntry *ChangeList::getNewCreatedEntry(void)
{
    ContainerChangeEntry *returnValue = createNewEntry();
    returnValue->clear(this);

    _createdStore.push_back(returnValue);

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/* SubRef Level                                                            */

inline
void ChangeList::incSubRefLevel(void)
{
    ++_iSubRefLevel;
}

inline
void ChangeList::decSubRefLevel(void)
{
    --_iSubRefLevel;
}

/*-------------------------------------------------------------------------*/
/* Helper                                                                  */

inline
void ChangeList::setAspect(UInt32 uiAspect)
{
    _uiAspect = uiAspect;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

inline
void commitChanges(void)
{
    Thread::getCurrentChangeList()->commitChanges();
}

inline
void commitChangesAndClear(void)
{
    Thread::getCurrentChangeList()->commitChangesAndClear();
}

inline
void clearChangeList(void)
{
    Thread::getCurrentChangeList()->clear();
}


OSG_END_NAMESPACE

