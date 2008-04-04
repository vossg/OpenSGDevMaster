

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* UnrecordedSFieldReferenceProxy<ObjectTypeT>                             */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    UnrecordedSFieldReferenceProxy<ObjectTypeT>::UnrecordedSFieldReferenceProxy(
        FieldContainerPtr *pValue)

    : _pValue(pValue)
{
    // nothing to do
}

template <class ObjectTypeT>
    UnrecordedSFieldReferenceProxy<ObjectTypeT>::UnrecordedSFieldReferenceProxy(
        Self const &source)
    
    : _pValue(source._pValue)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    UnrecordedSFieldReferenceProxy<ObjectTypeT>::~UnrecordedSFieldReferenceProxy(
        void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    UnrecordedSFieldReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
    return detail::void_cast<value_type>(AccessHandler::validate(*_pValue));
}
            
template <class ObjectTypeT>
inline  typename UnrecordedSFieldReferenceProxy<ObjectTypeT>::value_type
     UnrecordedSFieldReferenceProxy<ObjectTypeT>::operator->(void) const
{
    return detail::void_cast<value_type>(AccessHandler::validate(*_pValue));
}
    
template <class ObjectTypeT>
inline void
     UnrecordedSFieldReferenceProxy<ObjectTypeT>::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        static_cast<SFieldType *>(0),
        *_pValue,
        detail::void_cast<StoredType>(newValue));
    
    *_pValue = detail::void_cast<StoredType>(newValue);
}

/*-------------------------------------------------------------------------*/
/* UnrecordedPointerSField<ObjectTypeT,                                    */
/*                         NamespaceI  >                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerSField(void)
    : Inherited()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerSField(
        Self const &source)
    
    : Inherited(source)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerSField(
        ValueType value)
    
    : Inherited(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::~UnrecordedPointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerSField<ObjectTypeT,
                                        NamespaceI  >::reference
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::editValue(void)
{
    return reference(&this->editRawStore());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerSField<ObjectTypeT,
                                        NamespaceI  >::const_reference
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::getValue(void) const
{
    return reinterpret_cast<const_reference>(this->getRawStore());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::setValue(ValueType value)
{
    this->ptrStoreSet(value);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::setValue(Self const &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    UnrecordedPointerSField<ObjectTypeT,
                            NamespaceI  >::operator =(Self const &other)
{
    this->ptrStoreSet(other.ptrStoreGet());
}

OSG_END_NAMESPACE
