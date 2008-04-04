

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ChildSFieldReferenceProxy<ObjectTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    ChildSFieldReferenceProxy<ObjectTypeT>::ChildSFieldReferenceProxy(
        StoredType * const value, SFieldType *pField)

    : _pValue(value ),
      _pField(pField)
{
    // nothing to do
}

template <class ObjectTypeT>
    ChildSFieldReferenceProxy<ObjectTypeT>::ChildSFieldReferenceProxy(
        Self const &source)
    
    : _pValue(source._pValue),
      _pField(source._pField)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    ChildSFieldReferenceProxy<ObjectTypeT>::~ChildSFieldReferenceProxy(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    ChildSFieldReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
    return detail::void_cast<value_type>(AccessHandler::validate(*_pValue));
}
            
template <class ObjectTypeT>
inline  typename ChildSFieldReferenceProxy<ObjectTypeT>::value_type
     ChildSFieldReferenceProxy<ObjectTypeT>::operator->(void) const
{
    return detail::void_cast<value_type>(AccessHandler::validate(*_pValue));
}
    
template <class ObjectTypeT>
inline void
     ChildSFieldReferenceProxy<ObjectTypeT>::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        _pField, *_pValue, detail::void_cast<StoredType>(newValue));
    
    *_pValue = detail::void_cast<StoredType>(newValue);
}

/*-------------------------------------------------------------------------*/
/* ChildPointerSField<ObjectTypeT,                                         */
/*                    NamespaceI  >                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::ChildPointerSField(void)
    : Inherited()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::ChildPointerSField(Self const &source)
    : Inherited(source)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::ChildPointerSField(ValueType value)
    : Inherited(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::~ChildPointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerSField<ObjectTypeT,
                                   NamespaceI  >::reference
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::editValue(void)
{
    return reference(&this->editRawStore(), this);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ChildPointerSField<ObjectTypeT,
                                   NamespaceI  >::const_reference
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::getValue(void) const
{
    return reinterpret_cast<const_reference>(this->getRawStore());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::setValue(ValueType value)
{
    this->ptrStoreSet(detail::void_cast<StoredType>(value));
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::setValue(Self const &source)
{
    this->ptrStoreSet(detail::void_cast<StoredType>(source.ptrStoreGet()));
}

/*-------------------------------------------------------------------------*/
/* Comparison                                                              */

// template <class ObjectTypeT, Int32 NamespaceI>
// inline bool
//     ChildPointerSField<ObjectTypeT,
//                        NamespaceI  >::operator==(Self const &other)
// {   
// }

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ChildPointerSField<ObjectTypeT,
                       NamespaceI  >::operator =(Self const &other)
{   
    this->ptrStoreSet(other.ptrStoreGet());
}

OSG_END_NAMESPACE
