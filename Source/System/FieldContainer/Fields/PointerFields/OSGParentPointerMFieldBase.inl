
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
inline
    ParentPointerMFieldBase<NamespaceI>::ParentPointerMFieldBase(void)
    
    : Inherited    (),
      _childIdStore()
{
    // nothing to do
}

template <Int32 NamespaceI>
inline
    ParentPointerMFieldBase<NamespaceI>::ParentPointerMFieldBase(
        Self const &source)
        
    : Inherited    (source              ),
      _childIdStore(source._childIdStore)
{
    // nothing to do
}

template <Int32 NamespaceI>
inline
    ParentPointerMFieldBase<NamespaceI>::ParentPointerMFieldBase(
        UInt32 const size)
    
    : Inherited    (size),
      _childIdStore(size)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
inline
    ParentPointerMFieldBase<NamespaceI>::~ParentPointerMFieldBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* IdStore Interface                                                       */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */
    
template <Int32 NamespaceI>
inline UInt16 const
    ParentPointerMFieldBase<NamespaceI>::idStoreGet(UInt32 const index) const
{
    return _childIdStore[index];
}
    
template <Int32 NamespaceI>
inline UInt16 const
    ParentPointerMFieldBase<NamespaceI>::idStoreGet(IdStoreItType pos) const
{
    return *pos;
}    
    
template <Int32 NamespaceI>
inline UInt16 const
    ParentPointerMFieldBase<NamespaceI>::idStoreGet(
        IdStoreConstItType pos) const
{
    return *pos;
}
    
/*-------------------------------------------------------------------------*/
/* Adding Values                                                           */

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreAppend(UInt16 const newId)
{
    _childIdStore.push_back(newId);
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreInsert(
        UInt32 const index, UInt16 const newId)
{
    _childIdStore.insert(_childIdStore.begin() + index, newId);
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreInsert(
        IdStoreItType pos, UInt16 const newId)
{
    _childIdStore.insert(pos, newId);
}

template <Int32 NamespaceI    >
template <class InputIteratorT>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreInsert(
        IdStoreItType pos, InputIteratorT first, InputIteratorT last)
{
    _childIdStore.insert(pos, first, last);
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreReplace(
        UInt32 const index, UInt16 const newId)
{
    IdStoreItType sI = _childIdStore.begin() + index;
    
    *sI = newId;
}
                         
template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreReplace(
        IdStoreItType pos, UInt16 const newId)
{
    *pos = newId;
}

/*-------------------------------------------------------------------------*/
/* Removing Values                                                         */

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreErase(UInt32 const index)
{
    idStoreErase(_childIdStore.begin() + index);
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreErase(IdStoreItType pos)
{
    _childIdStore.erase(pos);
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreErase(
        UInt32 const beginIndex, UInt32 const endIndex)
{
    idStoreErase(_childIdStore.begin() + beginIndex,
                 _childIdStore.begin() + endIndex   );
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreErase(
        IdStoreItType begin, IdStoreItType end)
{
    _childIdStore.erase(begin, end);
}
    
template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::idStoreClear(void)
{
    _childIdStore.clear();
}

/*-------------------------------------------------------------------------*/
/* Finding Values                                                          */

template <Int32 NamespaceI>
inline Int32
    ParentPointerMFieldBase<NamespaceI>::idStoreFindIndex(
        UInt16 const fieldId) const
{
    IdStoreConstItType sI = std::find(_childIdStore.begin(),
                                      _childIdStore.end  (), fieldId);
                                  
    if(sI != _childIdStore.end())
    {
        return std::distance(_childIdStore.begin(), sI);
    }
    else
    {
        return -1;
    }
}

template <Int32 NamespaceI>
inline typename ParentPointerMFieldBase<NamespaceI>::IdStoreItType
    ParentPointerMFieldBase<NamespaceI>::idStoreFind(UInt16 const fieldId)
{
    return std::find(_childIdStore.begin(),
                     _childIdStore.end  (), fieldId);
}

template <Int32 NamespaceI>
inline typename ParentPointerMFieldBase<NamespaceI>::IdStoreConstItType
    ParentPointerMFieldBase<NamespaceI>::idStoreFind(
        UInt16 const fieldId) const
{
    return std::find(_childIdStore.begin(),
                     _childIdStore.end  (), fieldId);
}

/*-------------------------------------------------------------------------*/
/* Raw IdStore Access                                                      */

template <Int32 NamespaceI>
inline typename ParentPointerMFieldBase<NamespaceI>::IdStoreType &
    ParentPointerMFieldBase<NamespaceI>::editRawIdStore(void)
{
    return _childIdStore;
}
    
template <Int32 NamespaceI>
inline typename ParentPointerMFieldBase<NamespaceI>::IdStoreType const &
    ParentPointerMFieldBase<NamespaceI>::getRawIdStore (void) const
{
    return _childIdStore;
}

/*-------------------------------------------------------------------------*/
/* Std library interface                                                   */

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::reserve(size_type size)
{
    this->editRawStore  ().reserve(size);
    this->editRawIdStore().reserve(size);
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <Int32 NamespaceI>
inline UInt32
    ParentPointerMFieldBase<NamespaceI>::getBinSize(void) const
{
    return Inherited::getBinSize() +
        IdBaseTraitsType::getBinSize(&(this->getRawIdStore().front()),
                                       this->getRawIdStore().size ()  );
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::copyToBin(
        BinaryDataHandler &pMem) const
{
    UInt32 thisSize = this->getRawIdStore().size();

    Inherited::copyToBin(pMem);
    
    if(thisSize > 0)
    {
        IdBaseTraitsType::copyToBin(
            pMem, &(this->getRawIdStore().front()), thisSize);
    }
}

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::copyFromBin(
        BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);

    UInt32 newSize = this->ptrStoreSize();
    
    this->editRawIdStore().clear();
    
    if(newSize > 0)
    {
        this->editRawIdStore().resize(newSize);
        
        IdBaseTraitsType::copyFromBin(
            pMem, &(this->editRawIdStore().front()), newSize);
    }
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::syncWith(
        Self   &source,     ConstFieldMaskArg   syncMode,
        UInt32  uiSyncInfo, AspectOffsetStore  &oOffsets )
{
    Inherited::syncWith(source, syncMode, uiSyncInfo, oOffsets);
    
    _childIdStore = source._childIdStore;
}
                         
template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::beginEdit(
        UInt32, AspectOffsetStore &)
{
    // nothing to do
}
                         
template <Int32 NamespaceI>
inline typename ParentPointerMFieldBase<NamespaceI>::Self *
    ParentPointerMFieldBase<NamespaceI>::resolveShare(
        UInt32 uiAspect, AspectOffsetStore &oOffsets)
{
    return Inherited::resolveShare(uiAspect, oOffsets);
}        
        
template <Int32 NamespaceI>
inline void
    ParentPointerMFieldBase<NamespaceI>::terminateShare(
        UInt32, AspectOffsetStore &)
{
    // nothing to do
}
                         
template <Int32 NamespaceI>
inline bool
    ParentPointerMFieldBase<NamespaceI>::isShared(void)
{
    return Inherited::isShared();
}

OSG_END_NAMESPACE

