
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ParentMFieldConstIterator<ObjectTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    ParentMFieldConstIterator<ObjectTypeT>::ParentMFieldConstIterator(void)

    : Inherited (),
      _idStoreIt()
{
}

template <class ObjectTypeT>
inline
    ParentMFieldConstIterator<ObjectTypeT>::ParentMFieldConstIterator(
        Self const &source)
        
    : Inherited (source           ),
      _idStoreIt(source._idStoreIt)
{
}

template <class ObjectTypeT>
inline
    ParentMFieldConstIterator<ObjectTypeT>::ParentMFieldConstIterator(
        PtrStoreConstItType const &storeIt, IdStoreConstItType const &idStoreIt)
    
    : Inherited (storeIt  ),
      _idStoreIt(idStoreIt)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    ParentMFieldConstIterator<ObjectTypeT>::~ParentMFieldConstIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

#if 0
template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::reference
    ParentMFieldConstIterator<ObjectTypeT>::operator*(void) const
{
    return reference(*this, _idStoreIt);
}
#endif

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::pointer
    ParentMFieldConstIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self &
    ParentMFieldConstIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    ++_idStoreIt;
    
    return *this;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self
    ParentMFieldConstIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    ++_idStoreIt;
    
    return retVal;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self &
    ParentMFieldConstIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    --_idStoreIt;
    
    return *this;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self
    ParentMFieldConstIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();
    --_idStoreIt;
    
    return retVal;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::reference
    ParentMFieldConstIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return reference(*this + offset, _idStoreIt + offset);
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self &
    ParentMFieldConstIterator<ObjectTypeT>::operator+=(
        difference_type const offset)
{
    this->Inherited::operator+=(offset);
    _idStoreIt += offset;
    
    return *this;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self
    ParentMFieldConstIterator<ObjectTypeT>::operator+(
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self &
    ParentMFieldConstIterator<ObjectTypeT>::operator-=(
        difference_type const offset)
{
    this->Inherited::operator-=(offset);
    _idStoreIt -= offset;
    
    return *this;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::Self
    ParentMFieldConstIterator<ObjectTypeT>::operator-(
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::value_type
    ParentMFieldConstIterator<ObjectTypeT>::getPtr(void) const
{
    return AccessHandler::validate(this->Inherited::operator*());
}

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::IdStoredType
    ParentMFieldConstIterator<ObjectTypeT>::getId (void) const
{
    return *_idStoreIt;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename ParentMFieldConstIterator<ObjectTypeT>::PtrStoreConstItType const &
    ParentMFieldConstIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* ParentMFieldConstReferenceProxy<ObjectTypeT>                            */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    ParentMFieldConstReferenceProxy<ObjectTypeT>::ParentMFieldConstReferenceProxy(
        PtrStoreConstItType const &storeIt, IdStoreConstItType const &idStoreIt)
        
    : _storeIt  (storeIt  ),
      _idStoreIt(idStoreIt)
{
}

template <class ObjectTypeT>
inline
    ParentMFieldConstReferenceProxy<ObjectTypeT>::ParentMFieldConstReferenceProxy(
        Self const &source)
    
    : _storeIt  (source._storeIt  ),
      _idStoreIt(source._idStoreIt)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    ParentMFieldConstReferenceProxy<ObjectTypeT>::~ParentMFieldConstReferenceProxy(
        void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    ParentMFieldConstReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
    return AccessHandler::validate(*_storeIt);
}
          
template <class ObjectTypeT>
inline typename ParentMFieldConstReferenceProxy<ObjectTypeT>::value_type
    ParentMFieldConstReferenceProxy<ObjectTypeT>::operator->(void) const
{
    return AccessHandler::validate(*_storeIt);
}


template <class ObjectTypeT>
inline typename ParentMFieldConstReferenceProxy<ObjectTypeT>::value_type
    ParentMFieldConstReferenceProxy<ObjectTypeT>::getPtr(void) const
{
    return AccessHandler::validate(*_storeIt);
}    
    
template <class ObjectTypeT>
inline typename ParentMFieldConstReferenceProxy<ObjectTypeT>::IdStoredType
    ParentMFieldConstReferenceProxy<ObjectTypeT>::getId (void) const
{
    return *_idStoreIt;
}

/*-------------------------------------------------------------------------*/
/* ParentPointerMField<ObjectTypeT,                                        */
/*                     NamespaceI  >                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::ParentPointerMField(void)
    
    : Inherited(),
      _childIdStore()
{
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::ParentPointerMField(Self const &source)
    
    : Inherited(source),
      _childIdStore(source._childIdStore)
{
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::ParentPointerMField(UInt32 const size)
    
    : Inherited(size),
      _childIdStore(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::~ParentPointerMField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_iterator
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::begin(void) const
{
    return const_iterator(this->getRawStore  ().begin(),
                          this->getRawIdStore().begin() );
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_iterator
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::end(void) const
{
    return const_iterator(this->getRawStore  ().end(),
                          this->getRawIdStore().end() );
}
    
template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_reverse_iterator
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_reverse_iterator
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_reference
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::front (void) const
{
    return const_reference(this->getRawStore  ().begin(),
                           this->getRawIdStore().begin() );
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_reference
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::back  (void) const
{
    return const_reference(this->getRawStore  ().end() - 1,
                           this->getRawIdStore().end() - 1 );
}

/*-------------------------------------------------------------------------*/
/* IdStore Interface                                                       */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */
    
template <class ObjectTypeT, Int32 NamespaceI>
inline UInt16 const
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreGet(UInt32 const index) const
{
    return _childIdStore[index];
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline UInt16 const
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreGet(IdStoreItType pos) const
{
    return *pos;
}    
    
template <class ObjectTypeT, Int32 NamespaceI>
inline UInt16 const
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreGet(
        IdStoreConstItType pos) const
{
    return *pos;
}
    
/*-------------------------------------------------------------------------*/
/* Adding Values                                                           */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreAppend(UInt16 const newId)
{
    _childIdStore.push_back(newId);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreInsert(
        UInt32 const index, UInt16 const newId)
{
    _childIdStore.insert(_childIdStore.begin() + index, newId);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreInsert(
        IdStoreItType pos, UInt16 const newId)
{
    _childIdStore.insert(pos, newId);
}

template <class ObjectTypeT, Int32 NamespaceI    >
template <class InputIteratorT>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreInsert(
        IdStoreItType pos, InputIteratorT first, InputIteratorT last)
{
    _childIdStore.insert(pos, first, last);
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreReplace(
        UInt32 const index, UInt16 const newId)
{
    IdStoreItType sI = _childIdStore.begin() + index;
    
    *sI = newId;
}
                         
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreReplace(
        IdStoreItType pos, UInt16 const newId)
{
    *pos = newId;
}

/*-------------------------------------------------------------------------*/
/* Removing Values                                                         */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreErase(UInt32 const index)
{
    idStoreErase(_childIdStore.begin() + index);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreErase(IdStoreItType pos)
{
    _childIdStore.erase(pos);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreErase(
        UInt32 const beginIndex, UInt32 const endIndex)
{
    idStoreErase(_childIdStore.begin() + beginIndex,
                 _childIdStore.begin() + endIndex   );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreErase(
        IdStoreItType begin, IdStoreItType end)
{
    _childIdStore.erase(begin, end);
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreClear(void)
{
    _childIdStore.clear();
}

/*-------------------------------------------------------------------------*/
/* Finding Values                                                          */

template <class ObjectTypeT, Int32 NamespaceI>
inline Int32
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreFindIndex(
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

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerMField<ObjectTypeT, NamespaceI>::IdStoreItType
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreFind(UInt16 const fieldId)
{
    return std::find(_childIdStore.begin(),
                     _childIdStore.end  (), fieldId);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerMField<ObjectTypeT, NamespaceI>::IdStoreConstItType
    ParentPointerMField<ObjectTypeT, NamespaceI>::idStoreFind(
        UInt16 const fieldId) const
{
    return std::find(_childIdStore.begin(),
                     _childIdStore.end  (), fieldId);
}

/*-------------------------------------------------------------------------*/
/* Raw IdStore Access                                                      */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerMField<ObjectTypeT, NamespaceI>::IdStoreType &
    ParentPointerMField<ObjectTypeT, NamespaceI>::editRawIdStore(void)
{
    return _childIdStore;
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerMField<ObjectTypeT, NamespaceI>::IdStoreType const &
    ParentPointerMField<ObjectTypeT, NamespaceI>::getRawIdStore (void) const
{
    return _childIdStore;
}

/*-------------------------------------------------------------------------*/
/* Std library interface                                                   */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::reserve(size_type size)
{
    this->editRawStore  ().reserve(size);
    this->editRawIdStore().reserve(size);
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class ObjectTypeT, Int32 NamespaceI>
inline UInt32
    ParentPointerMField<ObjectTypeT, NamespaceI>::getBinSize(void) const
{
    return Inherited::getBinSize() +
        IdBaseTraitsType::getBinSize(&(this->getRawIdStore().front()),
                                       this->getRawIdStore().size ()  );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::copyToBin(
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

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::copyFromBin(
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

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::syncWith(
        Self   &source,     ConstFieldMaskArg   syncMode,
        UInt32  uiSyncInfo, AspectOffsetStore  &oOffsets )
{
    Inherited::syncWith(source, syncMode, uiSyncInfo, oOffsets);
    
    _childIdStore = source._childIdStore;
}
                         
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::beginEdit(
        UInt32, AspectOffsetStore &)
{
    // nothing to do
}
                         
template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerMField<ObjectTypeT, NamespaceI>::Self *
    ParentPointerMField<ObjectTypeT, NamespaceI>::resolveShare(
        UInt32 uiAspect, AspectOffsetStore &oOffsets)
{
    return Inherited::resolveShare(uiAspect, oOffsets);
}        
        
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerMField<ObjectTypeT, NamespaceI>::terminateShare(
        UInt32, AspectOffsetStore &)
{
    // nothing to do
}
                         
template <class ObjectTypeT, Int32 NamespaceI>
inline bool
    ParentPointerMField<ObjectTypeT, NamespaceI>::isShared(void)
{
    return Inherited::isShared();
}

/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline typename ParentPointerMField<ObjectTypeT,
                                    NamespaceI  >::const_reference
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::operator [](UInt32 const index) const
{
    return const_reference(this->getRawStore  ().begin() + index,
                           this->getRawIdStore().begin() + index );
}

OSG_END_NAMESPACE
