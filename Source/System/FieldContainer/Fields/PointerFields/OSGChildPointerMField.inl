

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ChildMFieldIterator<ObjectTypeT>                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline 
    ChildMFieldIterator<ObjectTypeT>::ChildMFieldIterator(void)
    
    : Inherited(    ),
      _pField  (NULL)
{
}
    
template <class ObjectTypeT>
inline 
    ChildMFieldIterator<ObjectTypeT>::ChildMFieldIterator(Self const &source)
    
    : Inherited(source        ),
      _pField  (source._pField)
{
}
    
template <class ObjectTypeT>
inline 
    ChildMFieldIterator<ObjectTypeT>::ChildMFieldIterator(
        PtrStoreItType const &storeIter,  MFieldType *pField)
    
    : Inherited(storeIter),
      _pField  (pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline 
    ChildMFieldIterator<ObjectTypeT>::~ChildMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::reference
    ChildMFieldIterator<ObjectTypeT>::operator* (void) const
{
    return reference(*this, _pField);
}

/*! 
    \warning Do NOT attempt to write to this field through the pointer
    returned by this function, it will break the reference counting.
 */
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::pointer
    ChildMFieldIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}

template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::reference
    ChildMFieldIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return reference(*this + offset, _pField);
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self &
    ChildMFieldIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self
    ChildMFieldIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self &
    ChildMFieldIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self
    ChildMFieldIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self &
    ChildMFieldIterator<ObjectTypeT>::operator+=(difference_type const offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self
    ChildMFieldIterator<ObjectTypeT>::operator+ (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self &
    ChildMFieldIterator<ObjectTypeT>::operator-=(difference_type const offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::Self
    ChildMFieldIterator<ObjectTypeT>::operator- (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename ChildMFieldIterator<ObjectTypeT>::PtrStoreItType const &
    ChildMFieldIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT>
typename ChildMFieldIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldIterator<ObjectTypeT> const &lhs,
              ChildMFieldIterator<ObjectTypeT> const &rhs )
{
    return std::distance<
        typename ChildMFieldIterator<ObjectTypeT>::StoreItType
                         >(lhs, rhs);
}

template <class ObjectTypeT>
ChildMFieldIterator<ObjectTypeT>
    operator+(
        typename ChildMFieldIterator<ObjectTypeT>::differece_type const offset,
        ChildMFieldIterator<ObjectTypeT>                          const &rhs   )
{
    return ChildMFieldIterator<ObjectTypeT>(rhs) += offset;
}

/*-------------------------------------------------------------------------*/
/* ChildMFieldConstIterator<ObjectTypeT>                            */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline 
    ChildMFieldConstIterator<ObjectTypeT>::ChildMFieldConstIterator(void)
    
    : Inherited()
{
}
    
template <class ObjectTypeT>
inline 
    ChildMFieldConstIterator<ObjectTypeT>::ChildMFieldConstIterator(
        Self const &source)
    
    : Inherited(source)
{
}
    
template <class ObjectTypeT>
inline
    ChildMFieldConstIterator<ObjectTypeT>::ChildMFieldConstIterator(
        ChildMFieldIterator<ObjectTypeT> const &fieldIter)
        
    : Inherited(fieldIter.base())
{
}

template <class ObjectTypeT>
inline 
    ChildMFieldConstIterator<ObjectTypeT>::ChildMFieldConstIterator(
        PtrStoreConstItType const &storeIter)
    
    : Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline 
    ChildMFieldConstIterator<ObjectTypeT>::~ChildMFieldConstIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::reference
    ChildMFieldConstIterator<ObjectTypeT>::operator* (void) const
{
    return reinterpret_cast<reference>(this->Inherited::operator*());
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::pointer
    ChildMFieldConstIterator<ObjectTypeT>::operator->(void) const
{
    return reinterpret_cast<pointer>(this->Inherited::operator->());
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::reference
    ChildMFieldConstIterator<ObjectTypeT>::operator[](
        difference_type const offset) const
{
    return *(*this + offset);
}

template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self &
    ChildMFieldConstIterator<ObjectTypeT>::operator++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self
    ChildMFieldConstIterator<ObjectTypeT>::operator++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self &
    ChildMFieldConstIterator<ObjectTypeT>::operator--(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self
    ChildMFieldConstIterator<ObjectTypeT>::operator--(int)
{
    Self retVal = *this;
    
    this->Inherited::oprator--();
    
    return retVal;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self &
    ChildMFieldConstIterator<ObjectTypeT>::operator+=(
        difference_type const offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self
    ChildMFieldConstIterator<ObjectTypeT>::operator+ (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self &
    ChildMFieldConstIterator<ObjectTypeT>::operator-=(
        difference_type const offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::Self
    ChildMFieldConstIterator<ObjectTypeT>::operator- (
        difference_type const offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT>
inline typename ChildMFieldConstIterator<ObjectTypeT>::PtrStoreConstItType const &
    ChildMFieldConstIterator<ObjectTypeT>::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT>
typename ChildMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldConstIterator<ObjectTypeT> const &lhs,
              ChildMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename ChildMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename ChildMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}
              
template <class ObjectTypeT>
typename ChildMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldIterator     <ObjectTypeT> const &lhs,
              ChildMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename ChildMFieldIterator<ObjectTypeT>::
               PtrStoreItType(lhs) -
           typename ChildMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}

template <class ObjectTypeT>
typename ChildMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldConstIterator<ObjectTypeT> const &lhs,
              ChildMFieldIterator     <ObjectTypeT> const &rhs )
{
    return typename ChildMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename ChildMFieldIterator<ObjectTypeT>::
               PtrStoreItType(rhs);
}             
              
template <class ObjectTypeT>
ChildMFieldConstIterator<ObjectTypeT>
    operator+(
        typename ChildMFieldConstIterator<ObjectTypeT>::difference_type const offset,
        ChildMFieldConstIterator<ObjectTypeT>                           const &rhs   )
{
    return ChildMFieldConstIterator<ObjectTypeT>(rhs) += offset;
}

/*-------------------------------------------------------------------------*/
/* ChildMFieldReferenceProxy<ObjectTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    ChildMFieldReferenceProxy<ObjectTypeT>::ChildMFieldReferenceProxy(
        PtrStoreItType const &storeIter, MFieldType *pField)

    : _storeIter(storeIter),
      _pField   (pField   )
{
}

template <class ObjectTypeT>
    ChildMFieldReferenceProxy<ObjectTypeT>::ChildMFieldReferenceProxy(
        Self const &source)
    
    : _storeIter(source._storeIter),
      _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    ChildMFieldReferenceProxy<ObjectTypeT>::~ChildMFieldReferenceProxy(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    ChildMFieldReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
    return detail::void_cast<value_type>(AccessHandler::validate(*_storeIter));
}
            
template <class ObjectTypeT>
inline  typename ChildMFieldReferenceProxy<ObjectTypeT>::value_type
     ChildMFieldReferenceProxy<ObjectTypeT>::operator->(void) const
{
    return detail::void_cast<value_type>(AccessHandler::validate(*_storeIter));
}
    
template <class ObjectTypeT>
inline void
     ChildMFieldReferenceProxy<ObjectTypeT>::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        _pField, *_storeIter, detail::void_cast<StoredType>(newValue));
    
    *_storeIter = detail::void_cast<StoredType>(newValue);
}

/*-------------------------------------------------------------------------*/
/* ChildPointerMField<ObjectTypeT,                                         */
/*                    NamespaceI  >                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::ChildPointerMField(void)
    : Inherited()
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::ChildPointerMField(Self const &other)
    : Inherited(other)
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::ChildPointerMField(UInt32 const size)
    : Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::~ChildPointerMField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::begin(void)
{
    return iterator(this->editRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::end(void)
{
    return iterator(this->editRawStore().end(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::rbegin(void)
{
    return reverse_iterator(this->end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::rend(void)
{
    return reverse_iterator(this->begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::begin(void) const
{
    return const_iterator(this->getRawStore().begin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::end(void) const
{
    return const_iterator(this->getRawStore().end());
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::rbegin(void) const
{
    return const_reverse_iterator(this->cend());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::rend(void) const
{
    return const_reverse_iterator(this->cbegin());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::reference
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::front(void)
{
    return reference(this->editRawStore().begin(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_reference
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::front(void) const
{
    return this->template getStore<ValueType>().front();
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::reference
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::back(void)
{
    return reference(this->editRawStore().end() - 1, this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_reference
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::back(void) const
{
    return this->template getStore<ValueType>().back();
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
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
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::assign(
        InputIteratorT first, InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}
   
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::insert(
        iterator pos, ValueType value)
{
    this->ptrStoreInsert(pos.base(), detail::void_cast<FieldContainerPtr>(value));
}

template <class ObjectTypeT,   Int32 NamespaceI>
template <class InputIteratorT                 >
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::insert(
        iterator pos, InputIteratorT first, InputIteratorT last)
{
    this->ptrStoreInsert(pos.base(), first, last);
}
 
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::erase(iterator pos)
{
    this->ptrStoreErase(pos.base());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::erase(
        iterator first, iterator last)
{
    this->ptrStoreErase(first.base(), last.base());
}
    
template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::find(ValueType value)
{
    return iterator(this->ptrStoreFind(detail::void_cast<FieldContainerPtr>(value)),
                    this                                                            );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_iterator
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::find(ValueType value) const
{
    return const_iterator(
        this->ptrStoreFind(detail::void_cast<FieldContainerPtr>(value)),
        this                                                            );
}

template <class ObjectTypeT, Int32 NamespaceI>
inline Int32
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::findIndex(ValueType value) const
{
    return this->ptrStoreFindIndex(detail::void_cast<FieldContainerPtr>(value));
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::push_back(ValueType value)
{
    this->ptrStoreAppend(detail::void_cast<FieldContainerPtr>(value));
}
   
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::resize(size_t newSize, ValueType value)
{
    this->ptrStoreResize(newSize, detail::void_cast<FieldContainerPtr>(value));
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::clear(void)
{
    this->ptrStoreClear();
}
                               
#ifdef OSG_1_COMPAT
template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::addValue(ValueType value)
{
    this->push_back(value);
}
#endif

/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::reference
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::operator [](UInt32 const index)
{
    return reference(this->editRawStore().begin() + index, this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::const_reference
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::operator [](UInt32 const index) const
{
    return this->template getStore<ValueType>()[index];
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::setValues(Self const &source)
{
    this->assign(source.begin(), source.end());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::Self &
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::operator=(Self const &source)
{
    this->setValues(source);
    
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Value Access                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                                   NamespaceI  >::ValueStoreType const &
    ChildPointerMField<ObjectTypeT,
                       NamespaceI  >::getValues(void) const
{
    return this->template getStore<ValueType>();
}

OSG_END_NAMESPACE
