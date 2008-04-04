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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChangeList.h
    \ingroup GrpSystemMultithreading
 */
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGMemoryObject.h"
#include "OSGThread.h"
#include "OSGStatElemTypes.h"

#include <list>
#include <vector>

OSG_BEGIN_NAMESPACE

class PThreadBase;
class SprocBase;
class WinThreadBase;
class StatCollector;
class FieldContainer;

/*! \ingroup GrpSystemMultithreading
 */

struct OSG_SYSTEM_DLLMAPPING ContainerChangeEntry
{
    enum EntryType
    {
        Create          = 0x0001,
        AddReference    = 0x0002,
        SubReference    = 0x0004,
        DepSubReference = 0x0008,
        Change          = 0x0010
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

    ContainerChangeEntry()        
    {
        uiEntryDesc   = 0;
        uiContainerId = 0;
        pFieldFlags   = NULL;
        whichField    = 0;
        bvUncommittedChanges = NULL;
    }    

    void operator =(const ContainerChangeEntry &)
    {
    }

    void clear(void)
    {
        uiEntryDesc   = 0;
        uiContainerId = 0;
        pFieldFlags   = NULL;
        whichField    = 0;
        bvUncommittedChanges = NULL;
    }

    void commitChanges(void);
};

/*! \ingroup GrpSystemMultithreading
 */

class OSG_SYSTEM_DLLMAPPING ChangeList : public MemoryObject
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
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    static StatElemDesc<StatIntElem> statNChangedStoreSize;
    static StatElemDesc<StatIntElem> statNCreatedStoreSize;
    static StatElemDesc<StatIntElem> statNUnCommittedStoreSize;
    static StatElemDesc<StatIntElem> statNPoolSize;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    void fillFromCurrentState(UInt32 uiFieldContainerId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    static ChangeList *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void commitChanges        (void);
    void commitChangesAndClear(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    void applyAndClear(void);
    void applyNoClear (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    void clear(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    void merge(ChangeList &pOther);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    ChangedStoreConstIt begin(void) const;
    ChangedStoreConstIt end  (void) const;

    ChangedStoreConstIt beginCreated(void) const;
    ChangedStoreConstIt endCreated  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    UInt32 getNumCreated  (void) const;
    UInt32 getNumDestroyed(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    static void setReadWriteDefault(void);
#endif

#ifdef OSG_THREAD_DEBUG_SETASPECTTO
    void setAspectTo(UInt32 uiNewAspect);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    template<typename RefCountPolicy>
    void addSyncAddRef  (FieldContainerPtr pFC);

    void clearSyncAddRef(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump         (      UInt32    uiIndent = 0,
                               const BitVector bvFlags  = 0) const;

            void dumpListSizes(void                        ) const;

            void fillStatistic(StatCollector *pColl        ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

    typedef void (ContainerChangeEntry::*CommitFunction)(void);

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    ChangeEntryPool                _entryPool;

    ChangeEntryPoolIt              _currentPoolElement;
    ChangeEntryStoreIt             _currentEntry;

    ChangedStore                   _changedStore;
    ChangedStore                   _createdStore;

    ChangedStore                   _uncommitedChanges;
    ChangedStore                   _workStore;

    UInt32                         _uiAspect;
    Int32                          _iSubRefLevel;

    bool                           _bExternal;
    
    std::vector<FieldContainerPtr> _vSyncUnrecAddRef;
    std::vector<FieldContainerPtr> _vSyncRecAddRef;
    std::vector<FieldContainerPtr> _vSyncWeakAddRef;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void addAddRefd  (const UInt32 uiContainerId);
    void addSubRefd  (const UInt32 uiContainerId,
                            bool   ignoreLevel = false);

    void addCreated  (const UInt32    uiContainerId,
                            BitVector bFlags       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    ContainerChangeEntry *getNewEntry       (void         );
    ContainerChangeEntry *getNewCreatedEntry(void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void addUncommited(ContainerChangeEntry *pEntry);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void incSubRefLevel(void);
    void decSubRefLevel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */


    ContainerChangeEntry *createNewEntry(void         );

    void                 doApply        (bool bClear  );
    void                 doClear        (void         );
    void                 clearPool      (void         );



    template<CommitFunction func>
    void doCommitChanges(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    void setAspect(UInt32 uiAspectId);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class  PThreadBase;
    friend class  SprocBase;
    friend class  WinThreadBase;
    friend class  FieldContainer;
    friend struct RecordedRefCounts;

    typedef MemoryObject Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChangeList(const ChangeList &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ChangeList &source);
};


/*! Convenience function for committing changes */
void commitChanges        (void);
void commitChangesAndClear(void);
void clearChangeList      (void);

OSG_END_NAMESPACE

#include "OSGChangeList.inl"

#endif /* _OSGCHANGELIST_H_ */
