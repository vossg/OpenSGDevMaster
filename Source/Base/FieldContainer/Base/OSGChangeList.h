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

#ifndef _OSGCHANGELIST_H_
#define _OSGCHANGELIST_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGContainerBase.h"
#include "OSGLog.h"
#include "OSGMemoryObject.h"
#include "OSGThread.h"
#include "OSGStatElemTypes.h"

#include <list>
#include <vector>
#include <deque>

OSG_BEGIN_NAMESPACE

class PThreadBase;
class SprocBase;
class WinThreadBase;
class StatCollector;
class FieldContainer;
template <class ParentT>
class DynFieldContainer;

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct OSG_BASE_DLLMAPPING ContainerChangeEntry
{
    enum EntryType
    {
        Create          = 0x0001,
        AddReference    = 0x0002,
        SubReference    = 0x0004,
        DepSubReference = 0x0008,
        Change          = 0x0010,
        AddField        = 0x0020,
        SubField        = 0x0020
    };

          UInt32      uiEntryDesc;
          UInt32      uiContainerId;         /* The id of the container we
                                                hold changes for. */
    const FieldFlags *pFieldFlags;
          BitVector   whichField;            /* Bit vector of fields have
                                                have changed and need
                                                commited. */
          BitVector  *bvUncommittedChanges;  /* Bit vector of changes that
                                                still need to be committed
                                                for this entry. */
          ChangeList *pList;

    ContainerChangeEntry(void);

    void clear        (ChangeList *pListParent               );
    void commitChanges(UInt32      origin,
                       UInt32      AdditionalChangeOrigin = 0);
    void release      (void                                  );
};

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING ChangeList : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef            std::vector<ContainerChangeEntry>   ChangeEntryStore;
    typedef std::list< std::vector<ContainerChangeEntry> > ChangeEntryPool;

    typedef ChangeEntryPool ::iterator                     ChangeEntryPoolIt;
    typedef ChangeEntryStore::iterator                     ChangeEntryStoreIt;

    typedef            std::vector<ContainerChangeEntry *> ChangedStore;
    typedef            ChangedStore::iterator              ChangedStoreIt;
    typedef            ChangedStore::const_iterator        ChangedStoreConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name Statistics                                                   */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem> statNChangedStoreSize;
    static StatElemDesc<StatIntElem> statNCreatedStoreSize;
    static StatElemDesc<StatIntElem> statNUnCommittedStoreSize;
    static StatElemDesc<StatIntElem> statNPoolSize;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ChangeList *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Commit                                                       */
    /*! \{                                                                 */

    void commitChanges        (UInt32 origin = ChangedOrigin::Commit,
                               UInt32 AdditionalChangeOrigin = 0);
    void commitChangesAndClear(UInt32 origin = ChangedOrigin::Commit,
                               UInt32 AdditionalChangeOrigin = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Apply                                                        */
    /*! \{                                                                 */

    void applyAndClear(void);
    void applyNoClear (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Clear                                                        */
    /*! \{                                                                 */

    void clear(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Merge                                                        */
    /*! \{                                                                 */

    void merge(ChangeList &pOther);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Fill From Current                                            */
    /*! \{                                                                 */

    void fillFromCurrentState(UInt32 uiFieldContainerId = 0,
                              bool   skipPrototypes     = true);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Changed/Created Store                                        */
    /*! \{                                                                 */

    ChangedStoreConstIt begin        (void) const;
    ChangedStoreConstIt end          (void) const;

    ChangedStoreConstIt beginCreated (void) const;
    ChangedStoreConstIt endCreated   (void) const;

    UInt32              getNumCreated(void) const;
    UInt32              getNumChanged(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Misc                                                         */
    /*! \{                                                                 */

    static void setReadWriteDefault(bool bReadWrite = true);

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
    void setAspectTo(UInt32 uiNewAspect);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Delayed SubRef                                               */
    /*! \{                                                                 */

    template<typename RefCountPolicy>
    void addDelayedSubRef    (FieldContainer *pFC);

    void commitDelayedSubRefs(void               );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Statistics                                                   */
    /*! \{                                                                 */

    virtual void dump         (      UInt32    uiIndent = 0,
                               const BitVector bvFlags  = 0) const;

            void dumpListSizes(void                        ) const;

            void fillStatistic(StatCollector *pColl        ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static bool _bReadWriteDefault;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    ChangeEntryPool                     _entryPool;

    ChangeEntryPoolIt                   _currentPoolElement;
    ChangeEntryStoreIt                  _currentEntry;

    ChangedStore                        _changedStore;
    ChangedStore                        _createdStore;

    ChangedStore                        _uncommitedChanges;
    ChangedStore                        _workStore;

    UInt32                              _uiAspect;
    Int32                               _iSubRefLevel;

    bool                                _bExternal;
    bool                                _bReadOnly;

    std::vector<FieldContainer *>       _vDelayedUnrecSubRefs;
    std::vector<FieldContainer *>       _vDelayedRecSubRefs;
    std::vector<FieldContainer *>       _vDelayedWeakSubRefs;
    std::deque <ContainerChangeEntry *> _qFreeElements;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

    ChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~ChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Add Entries                                                  */
    /*! \{                                                                 */

    void addAddRefd   (const UInt32                uiContainerId      );
    void addSubRefd   (const UInt32                uiContainerId,
                             bool                  ignoreLevel = false);
    void addCreated   (const UInt32                uiContainerId,
                             BitVector             bFlags             );
    void addNewField  (const UInt32                uiContainerId,
                             BitVector             bFlags             );
    void addUncommited(      ContainerChangeEntry *pEntry             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Entry Pool                                                   */
    /*! \{                                                                 */

    ContainerChangeEntry *getNewEntry       (void);
    ContainerChangeEntry *getNewCreatedEntry(void);

    ContainerChangeEntry *createNewEntry    (void);
    void                  clearPool         (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name SubRef Level                                                 */
    /*! \{                                                                 */

    void incSubRefLevel(void);
    void decSubRefLevel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Helper                                                       */
    /*! \{                                                                 */

    void doCommitChanges(UInt32 origin,
                         UInt32 AdditionalChangeOrigin = 0);
    void doApply        (bool   bClear                    );
    void doClear        (void                             );

    void setAspect      (UInt32 uiAspect                  );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class  PThreadBase;
    friend class  SprocBase;
    friend class  WinThreadBase;
    friend class  FieldContainer;
    friend struct RecordedRefCountPolicy;
    friend struct ContainerChangeEntry;

    template <class ParentT>
    friend class DynFieldContainer;

    typedef MemoryObject Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChangeList(const ChangeList &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ChangeList &source);
};


/*! \brief Convenience function for committing changes
    \ingroup GrpBaseFieldContainerFuncs
 */
void commitChanges        (UInt32 AdditionalChangeOrigin = 0);
/*! \brief Convenience function for committing changes
    \ingroup GrpBaseFieldContainerFuncs
 */
void commitChangesAndClear(UInt32 AdditionalChangeOrigin = 0);
/*! \brief Convenience function for committing changes
    \ingroup GrpBaseFieldContainerFuncs
 */
void clearChangeList      (void);

OSG_END_NAMESPACE

#include "OSGChangeList.inl"

#endif /* _OSGCHANGELIST_H_ */
