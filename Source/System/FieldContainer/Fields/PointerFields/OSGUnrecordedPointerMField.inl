
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerMField.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* UnrecordedMFieldIterator<ObjectTypeT>                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline 
    UnrecordedMFieldIterator<ObjectTypeT>::UnrecordedMFieldIterator(void)
    
    : Inherited(    ),
      _pField  (NULL)
{
}
    
template <class ObjectTypeT>
inline 
    UnrecordedMFieldIterator<ObjectTypeT>::UnrecordedMFieldIterator(
        Self const &source)
    
    : Inherited(source        ),
      _pField  (source._pField)
{
}
    
template <class ObjectTypeT>
inline 
    UnrecordedMFieldIterator<ObjectTypeT>::UnrecordedMFieldIterator(
        PtrStoreItType const &storeIter,  MFieldType *pField)
    
    : Inherited(storeIter),
      _pField  (pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline 
    UnrecordedMFieldIterator<ObjectTypeT>::~UnrecordedMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::reference
    UnrecordedMFieldIterator<ObjectTypeT>::operator* (void) const
{
    return reference(*this, _pField);
}

/*! 
    \warning Do NOT attempt to write to this field through the pointer
    returned by this function, it will break the reference counting.
 */
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::pointer
    UnrecordedMFieldIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}

template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::reference
    UnrecordedMFieldIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return reference(*this + offset, _pField);
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self &
    UnrecordedMFieldIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self
    UnrecordedMFieldIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self &
    UnrecordedMFieldIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self
    UnrecordedMFieldIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self &
    UnrecordedMFieldIterator<ObjectTypeT>::operator+=(
        difference_type const offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self
    UnrecordedMFieldIterator<ObjectTypeT>::operator+ (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self &
    UnrecordedMFieldIterator<ObjectTypeT>::operator-=(
        difference_type const offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::Self
    UnrecordedMFieldIterator<ObjectTypeT>::operator- (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename UnrecordedMFieldIterator<ObjectTypeT>::PtrStoreItType const &
    UnrecordedMFieldIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT>
typename UnrecordedMFieldIterator<ObjectTypeT>::difference_type
    operator-(UnrecordedMFieldIterator<ObjectTypeT> const &lhs,
              UnrecordedMFieldIterator<ObjectTypeT> const &rhs )
{
    return std::distance<
        typename UnrecordedMFieldIterator<ObjectTypeT>::StoreItType
                         >(lhs, rhs);
}

template <class ObjectTypeT>
UnrecordedMFieldIterator<ObjectTypeT>
    operator+(typename UnrecordedMFieldIterator<ObjectTypeT>::differece_type const offset,
              UnrecordedMFieldIterator<ObjectTypeT>                          const &rhs   )
{
    return UnrecordedMFieldIterator<ObjectTypeT>(rhs) += offset;
}

/*-------------------------------------------------------------------------*/
/* UnrecordedMFieldConstIterator<ObjectTypeT>                              */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline 
    UnrecordedMFieldConstIterator<ObjectTypeT>::UnrecordedMFieldConstIterator(
        void)
    
    : Inherited()
{
}
    
template <class ObjectTypeT>
inline 
    UnrecordedMFieldConstIterator<ObjectTypeT>::UnrecordedMFieldConstIterator(
        Self const &source)
    
    : Inherited(source)
{
}

template <class ObjectTypeT>
inline
    UnrecordedMFieldConstIterator<ObjectTypeT>::UnrecordedMFieldConstIterator(
        UnrecordedMFieldIterator<ObjectTypeT> const &fieldIter)
    
    : Inherited(fieldIter.base())
{
}

template <class ObjectTypeT>
inline 
    UnrecordedMFieldConstIterator<ObjectTypeT>::UnrecordedMFieldConstIterator(
        PtrStoreConstItType const &storeIter)
    
    : Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline 
    UnrecordedMFieldConstIterator<ObjectTypeT>::~UnrecordedMFieldConstIterator(
        void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::reference
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator* (void) const
{
    return reinterpret_cast<reference>(this->Inherited::operator*());
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::pointer
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::reference
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return *(*this + offset);
}

template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self &
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self &
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::oprator--();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self &
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator+=(
        difference_type const offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator+ (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self &
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator-=(
        difference_type const offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::Self
    UnrecordedMFieldConstIterator<ObjectTypeT>::operator- (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename UnrecordedMFieldConstIterator<ObjectTypeT>::PtrStoreConstItType const &
    UnrecordedMFieldConstIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT>
typename UnrecordedMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(UnrecordedMFieldConstIterator<ObjectTypeT> const &lhs,
              UnrecordedMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename UnrecordedMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename UnrecordedMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}
              
template <class ObjectTypeT>
typename UnrecordedMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(UnrecordedMFieldIterator     <ObjectTypeT> const &lhs,
              UnrecordedMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename UnrecordedMFieldIterator<ObjectTypeT>::
               PtrStoreItType(lhs) -
           typename UnrecordedMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}

template <class ObjectTypeT>
typename UnrecordedMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(UnrecordedMFieldConstIterator<ObjectTypeT> const &lhs,
              UnrecordedMFieldIterator     <ObjectTypeT> const &rhs )
{
    return typename UnrecordedMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename UnrecordedMFieldIterator<ObjectTypeT>::
               PtrStoreItType(rhs);
}             
              
template <class ObjectTypeT>
UnrecordedMFieldConstIterator<ObjectTypeT>
    operator+(typename UnrecordedMFieldConstIterator<ObjectTypeT>::difference_type const offset,
              UnrecordedMFieldConstIterator<ObjectTypeT>                           const &rhs   )
{
    return UnrecordedMFieldConstIterator<ObjectTypeT>(rhs) += offset;
}

/*-------------------------------------------------------------------------*/
/* UnrecordedMFieldReferenceProxy<ObjectTypeT>                             */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    UnrecordedMFieldReferenceProxy<ObjectTypeT>::UnrecordedMFieldReferenceProxy(
        PtrStoreItType const &storeIter, MFieldType *pField)

    : _storeIter(storeIter),
      _pField   (pField   )
{
}

template <class ObjectTypeT>
    UnrecordedMFieldReferenceProxy<ObjectTypeT>::UnrecordedMFieldReferenceProxy(
        Self const &source)
    
    : _storeIter(source._storeIter),
      _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    UnrecordedMFieldReferenceProxy<ObjectTypeT>::~UnrecordedMFieldReferenceProxy(
        void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    UnrecordedMFieldReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
//    return detail::void_cast<value_type>(AccessHandler::validate(*_storeIter));
    return AccessHandler::validate(*_storeIter);
}
            
template <class ObjectTypeT>
inline  typename UnrecordedMFieldReferenceProxy<ObjectTypeT>::value_type
     UnrecordedMFieldReferenceProxy<ObjectTypeT>::operator->(void) const
{
//    return detail::void_cast<value_type>(AccessHandler::validate(*_storeIter));
    return AccessHandler::validate(*_storeIter);
}
    
template <class ObjectTypeT>
inline void
     UnrecordedMFieldReferenceProxy<ObjectTypeT>::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        _pField, *_storeIter, newValue);
    
    *_storeIter = newValue;
}

/*-------------------------------------------------------------------------*/
/* UnrecordedPointerMField<ObjectTypeT,                                    */
/*                         NamespaceI  >                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerMField(void)
    : Inherited()
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerMField(
        Self const &other)
        
    : Inherited(other)
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerMField(
        UInt32 const size)
        
    : Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::~UnrecordedPointerMField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::begin(void)
{
    return iterator(this->editRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::end(void)
{
    return iterator(this->editRawStore().end(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::reverse_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::rbegin(void)
{
    return reverse_iterator(this->end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::reverse_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::rend(void)
{
    return reverse_iterator(this->begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::begin(void) const
{
    return const_iterator(this->getRawStore().begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::end(void) const
{
    return const_iterator(this->getRawStore().end());
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_reverse_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_reverse_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::reference
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::front(void)
{
    return reference(this->editRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_reference
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::front(void) const
{
    return this->template getStore<ValueType>().front();
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::reference
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::back(void)
{
    return reference(this->editRawStore().end() - 1, this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_reference
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::back(void) const
{
    return this->template getStore<ValueType>().back();
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
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
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::assign(
        InputIteratorT first, InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}
   
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::insert(
        iterator pos, ValueType value)
{
    this->ptrStoreInsert(pos.base(), value);
}

template <class ObjectTypeT,   Int32 NamespaceI>
template <class InputIteratorT                 >
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::insert(
        iterator pos, InputIteratorT first, InputIteratorT last)
{
    this->ptrStoreInsert(pos.base(), first, last);
}
 
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::erase(iterator pos)
{
    this->ptrStoreErase(pos.base());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::erase(
        iterator first, iterator last)
{
    this->ptrStoreErase(first.base(), last.base());
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::find(ValueType value)
{
    return iterator(this->ptrStoreFind(value),
                    this                                                            );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_iterator
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::find(ValueType value) const
{
    return const_iterator(
        this->ptrStoreFind(value),
        this                                                            );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline Int32
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::findIndex(ValueType value) const
{
    return this->ptrStoreFindIndex(value);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::push_back(ValueType value)
{
    this->ptrStoreAppend(value);
}
   
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::resize(size_t newSize, ValueType value)
{
    this->ptrStoreResize(newSize, value);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::clear(void)
{
    this->ptrStoreClear();
}
                               
#ifdef OSG_1_COMPAT
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::addValue(ValueType value)
{
    this->push_back(value);
}
#endif

/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::reference
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::operator [](UInt32 const index)
{
    return reference(this->editRawStore().begin() + index, this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::const_reference
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::operator [](UInt32 const index) const
{
    return this->template getStore<ValueType>()[index];
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::setValues(Self const &source)
{
    this->assign(source.begin(), source.end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::Self &
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::operator=(Self const &source)
{
    this->setValues(source);
    
    return *this;
}

OSG_END_NAMESPACE
