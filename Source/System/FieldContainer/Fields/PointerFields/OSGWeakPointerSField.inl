

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* WeakSFieldReferenceProxy<ObjectTypeT>                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    WeakSFieldReferenceProxy<ObjectTypeT>::WeakSFieldReferenceProxy(
        FieldContainerPtr *pValue)

    : _pValue(pValue)
{
    // nothing to do
}

template <class ObjectTypeT>
    WeakSFieldReferenceProxy<ObjectTypeT>::WeakSFieldReferenceProxy(
        Self const &source)
    
    : _pValue(source._pValue)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    WeakSFieldReferenceProxy<ObjectTypeT>::~WeakSFieldReferenceProxy(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    WeakSFieldReferenceProxy<ObjectTypeT>::operator value_type(void) const
{
//    return detail::void_cast<value_type>(AccessHandler::validate(*_pValue));
    return AccessHandler::validate(*_pValue);
}

template <class ObjectTypeT>
inline  typename WeakSFieldReferenceProxy<ObjectTypeT>::value_type
     WeakSFieldReferenceProxy<ObjectTypeT>::operator->(void) const
{
//    return detail::void_cast<value_type>(AccessHandler::validate(*_pValue));
    return AccessHandler::validate(*_pValue);
}

template <class ObjectTypeT>
inline void
     WeakSFieldReferenceProxy<ObjectTypeT>::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        static_cast<SFieldType *>(0),
        *_pValue,
        newValue);
    
    *_pValue = newValue;
}

/*-------------------------------------------------------------------------*/
/* WeakPointerSField<ObjectTypeT,                                          */
/*                   NamespaceI  >                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::WeakPointerSField(void)
    : Inherited()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::WeakPointerSField(Self const &source)
    : Inherited(source)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::WeakPointerSField(ValueType value)
    : Inherited(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::~WeakPointerSField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerSField<ObjectTypeT,
                                  NamespaceI  >::reference
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::editValue(void)
{
    return reference(&this->editRawStore());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename WeakPointerSField<ObjectTypeT,
                                  NamespaceI  >::const_reference
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::getValue(void) const
{
    return reinterpret_cast<const_reference>(this->getRawStore());
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::setValue(ValueType value)
{
    this->ptrStoreSet(value);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::setValue(Self const &source)
{
    this->ptrStoreSet(source.ptrStoreGet());
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    WeakPointerSField<ObjectTypeT,
                      NamespaceI  >::operator =(Self const &other)
{
    this->ptrStoreSet(other.ptrStoreGet());
}

OSG_END_NAMESPACE
