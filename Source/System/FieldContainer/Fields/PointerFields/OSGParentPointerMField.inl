
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
    
    : Inherited()
{
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::ParentPointerMField(Self const &source)
    
    : Inherited(source)
{
}

template <class ObjectTypeT,
          Int32 NamespaceI  >
inline
    ParentPointerMField<ObjectTypeT,
                        NamespaceI  >::ParentPointerMField(UInt32 const size)
    
    : Inherited(size)
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
