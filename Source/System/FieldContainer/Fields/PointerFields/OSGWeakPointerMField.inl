
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerMField.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* WeakMFieldIterator<ObjectTypeT>                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline 
    WeakMFieldIterator<ObjectTypeT>::WeakMFieldIterator(void)
    
    : Inherited(    ),
      _pField  (NULL)
{
}
    
template <class ObjectTypeT>
inline 
    WeakMFieldIterator<ObjectTypeT>::WeakMFieldIterator(Self const &source)
    
    : Inherited(source        ),
      _pField  (source._pField)
{
}
    
template <class ObjectTypeT>
inline 
    WeakMFieldIterator<ObjectTypeT>::WeakMFieldIterator(
        PtrStoreItType const &storeIter,  MFieldType *pField)
    
    : Inherited(storeIter),
      _pField  (pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline 
    WeakMFieldIterator<ObjectTypeT>::~WeakMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::reference
    WeakMFieldIterator<ObjectTypeT>::operator* (void) const
{
    return reference(*this, _pField);
}

/*! 
    \warning Do NOT attempt to write to this field through the pointer
    returned by this function, it will break the reference counting.
 */
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::pointer
    WeakMFieldIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}

template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::reference
    WeakMFieldIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return reference(*this + offset, _pField);
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self &
    WeakMFieldIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self
    WeakMFieldIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self &
    WeakMFieldIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self
    WeakMFieldIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self &
    WeakMFieldIterator<ObjectTypeT>::operator+=(
        difference_type const offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self
    WeakMFieldIterator<ObjectTypeT>::operator+ (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self &
    WeakMFieldIterator<ObjectTypeT>::operator-=(
        difference_type const offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::Self
    WeakMFieldIterator<ObjectTypeT>::operator- (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename WeakMFieldIterator<ObjectTypeT>::PtrStoreItType const &
    WeakMFieldIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT>
typename WeakMFieldIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldIterator<ObjectTypeT> const &lhs,
              WeakMFieldIterator<ObjectTypeT> const &rhs )
{
    return std::distance<
        typename WeakMFieldIterator<ObjectTypeT>::StoreItType
                         >(lhs, rhs);
}

template <class ObjectTypeT>
WeakMFieldIterator<ObjectTypeT>
    operator+(typename WeakMFieldIterator<ObjectTypeT>::differece_type const offset,
              WeakMFieldIterator<ObjectTypeT>                          const &rhs   )
{
    return WeakMFieldIterator<ObjectTypeT>(rhs) += offset;
}

/*-------------------------------------------------------------------------*/
/* WeakMFieldConstIterator<ObjectTypeT>                                    */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline 
    WeakMFieldConstIterator<ObjectTypeT>::WeakMFieldConstIterator(void)
    
    : Inherited()
{
}
    
template <class ObjectTypeT>
inline 
    WeakMFieldConstIterator<ObjectTypeT>::WeakMFieldConstIterator(
        Self const &source)
    
    : Inherited(source)
{
}
    
template <class ObjectTypeT>
inline
    WeakMFieldConstIterator<ObjectTypeT>::WeakMFieldConstIterator(
        WeakMFieldIterator<ObjectTypeT> const &fieldIter)
    
    : Inherited(fieldIter.base())
{
}

template <class ObjectTypeT>
inline 
    WeakMFieldConstIterator<ObjectTypeT>::WeakMFieldConstIterator(
        PtrStoreConstItType const &storeIter)
    
    : Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline 
    WeakMFieldConstIterator<ObjectTypeT>::~WeakMFieldConstIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::reference
    WeakMFieldConstIterator<ObjectTypeT>::operator* (void) const
{
    return reinterpret_cast<reference>(this->Inherited::operator*());
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::pointer
    WeakMFieldConstIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::reference
    WeakMFieldConstIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return *(*this + offset);
}

template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self &
    WeakMFieldConstIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self
    WeakMFieldConstIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self &
    WeakMFieldConstIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self
    WeakMFieldConstIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::oprator--();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self &
    WeakMFieldConstIterator<ObjectTypeT>::operator+=(
        difference_type const offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self
    WeakMFieldConstIterator<ObjectTypeT>::operator+ (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self &
    WeakMFieldConstIterator<ObjectTypeT>::operator-=(
        difference_type const offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::Self
    WeakMFieldConstIterator<ObjectTypeT>::operator- (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename WeakMFieldConstIterator<ObjectTypeT>::PtrStoreConstItType const &
    WeakMFieldConstIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldConstIterator<ObjectTypeT> const &lhs,
              WeakMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}
              
template <class ObjectTypeT>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldIterator     <ObjectTypeT> const &lhs,
              WeakMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename WeakMFieldIterator<ObjectTypeT>::
               PtrStoreItType(lhs) -
           typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}

template <class ObjectTypeT>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldConstIterator<ObjectTypeT> const &lhs,
              WeakMFieldIterator     <ObjectTypeT> const &rhs )
{
    return typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename WeakMFieldIterator<ObjectTypeT>::
               PtrStoreItType(rhs);
}             
              
template <class ObjectTypeT>
WeakMFieldConstIterator<ObjectTypeT>
    operator+(typename WeakMFieldConstIterator<ObjectTypeT>::difference_type const offset,
              WeakMFieldConstIterator<ObjectTypeT>                           const &rhs   )
{
    return WeakMFieldConstIterator<ObjectTypeT>(rhs) += offset;
}

/*-------------------------------------------------------------------------*/
/* WeakMFieldReferenceProxy<ObjectTypeT>                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    WeakMFieldReferenceProxy<ObjectTypeT>::WeakMFieldReferenceProxy(
        PtrStoreItType const &storeIter, MFieldType *pField)

    : _storeIter(storeIter),
      _pField   (pField   )
{
}

template <class ObjectTypeT>
    WeakMFieldReferenceProxy<ObjectTypeT>::WeakMFieldReferenceProxy(
        Self const &source)
    
    : _storeIter(source._storeIter),
      _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    WeakMFieldReferenceProxy<ObjectTypeT>::~WeakMFieldReferenceProxy(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    WeakMFieldReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
//    return detail::void_cast<value_type>(AccessHandler::validate(*_storeIter));
    return AccessHandler::validate(*_storeIter);
}
            
template <class ObjectTypeT>
inline  typename WeakMFieldReferenceProxy<ObjectTypeT>::value_type
     WeakMFieldReferenceProxy<ObjectTypeT>::operator->(void) const
{
//    return detail::void_cast<value_type>(AccessHandler::validate(*_storeIter));
    return AccessHandler::validate(*_storeIter);
}
    
template <class ObjectTypeT>
inline void
     WeakMFieldReferenceProxy<ObjectTypeT>::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        _pField, *_storeIter, newValue);
    
    *_storeIter = newValue;
}

/*-------------------------------------------------------------------------*/
/* WeakPointerMField<ObjectTypeT,                                          */
/*                   NamespaceI  >                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::WeakPointerMField(void)
    : Inherited()
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::WeakPointerMField(Self const &other)
        
    : Inherited(other)
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::WeakPointerMField(UInt32 const size)
        
    : Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::~WeakPointerMField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::begin(void)
{
    return iterator(this->editRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::end(void)
{
    return iterator(this->editRawStore().end(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::reverse_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::rbegin(void)
{
    return reverse_iterator(this->end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::reverse_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::rend(void)
{
    return reverse_iterator(this->begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::begin(void) const
{
    return const_iterator(this->getRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::end(void) const
{
    return const_iterator(this->getRawStore().end(), this);
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_reverse_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_reverse_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::reference
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::front(void)
{
    return reference(this->editRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_reference
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::front(void) const
{
    return this->template getStore<ValueType>().front();
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::reference
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::back(void)
{
    return reference(this->editRawStore().end() - 1, this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_reference
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::back(void) const
{
    return this->template getStore<ValueType>().back();
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::assign(
        size_type newSize, ValueType value)
{
    this->ptrStoreClear();
    
    for(size_type i = 0; i < newSize; ++i)
        this->ptrStoreAppend(value);
}

template <class ObjectTypeT,   Int32 NamespaceI>
template <class InputIteratorT                 >
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::assign(
        InputIteratorT first, InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}
   
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::insert(
        iterator pos, ValueType value)
{
    this->ptrStoreInsert(pos.base(), value);
}

template <class ObjectTypeT,   Int32 NamespaceI>
template <class InputIteratorT                 >
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::insert(
        iterator pos, InputIteratorT first, InputIteratorT last)
{
    this->ptrStoreInsert(pos.base(), first, last);
}
 
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::erase(iterator pos)
{
    this->ptrStoreErase(pos.base());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::erase(
        iterator first, iterator last)
{
    this->ptrStoreErase(first.base(), last.base());
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::find(ValueType value)
{
    return iterator(this->ptrStoreFind(value),
                    this                                                            );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_iterator
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::find(ValueType value) const
{
    return const_iterator(
        this->ptrStoreFind(value),
        this                                                            );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline Int32
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::findIndex(ValueType value) const
{
    return this->ptrStoreFindIndex(value);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::push_back(ValueType value)
{
    this->ptrStoreAppend(value);
}
   
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::resize(size_t newSize, ValueType value)
{
    this->ptrStoreResize(newSize, value);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::clear(void)
{
    this->ptrStoreClear();
}
                               
#ifdef OSG_1_COMPAT
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::addValue(ValueType value)
{
    this->push_back(value);
}
#endif

/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::reference
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::operator [](UInt32 const index)
{
    return reference(this->editRawStore().begin() + index, this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::const_reference
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::operator [](UInt32 const index) const
{
    return this->template getStore<ValueType>()[index];
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::setValues(Self const &source)
{
    this->assign(source.begin(), source.end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerMField<ObjectTypeT,
                                  NamespaceI  >::Self &
    WeakPointerMField<ObjectTypeT,
                      NamespaceI  >::operator=(Self const &source)
{
    this->setValues(source);
    
    return *this;
}

OSG_END_NAMESPACE
