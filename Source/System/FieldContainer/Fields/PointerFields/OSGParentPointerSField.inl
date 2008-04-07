

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ParentSFieldConstReferenceProxy<ObjectTypeT>                            */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT>
inline
    ParentSFieldConstReferenceProxy<ObjectTypeT>::ParentSFieldConstReferenceProxy(
        StoredType   const * const pPtrValue,
        IdStoredType const * const pIdValue  )

    : _pPtrValue(pPtrValue),
      _pIdValue (pIdValue )
{
    // nothing to do
}

template <class ObjectTypeT>
inline
    ParentSFieldConstReferenceProxy<ObjectTypeT>::ParentSFieldConstReferenceProxy(
        Self const &source)
    
    : _pPtrValue(source._pPtrValue),
      _pIdValue (source._pIdValue )
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT>
inline
    ParentSFieldConstReferenceProxy<ObjectTypeT>::~ParentSFieldConstReferenceProxy(
        void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT>
inline
    ParentSFieldConstReferenceProxy<ObjectTypeT>::operator value_type(
        void) const
{
    return AccessHandler::validate(*_pPtrValue);
}

template <class ObjectTypeT>
inline typename ParentSFieldConstReferenceProxy<ObjectTypeT>::value_type
    ParentSFieldConstReferenceProxy<ObjectTypeT>::operator->(void) const
{
    return AccessHandler::validate(*_pPtrValue);
}

template <class ObjectTypeT>
inline typename ParentSFieldConstReferenceProxy<ObjectTypeT>::value_type
    ParentSFieldConstReferenceProxy<ObjectTypeT>::getPtr(void) const
{
    return AccessHandler::validate(*_pPtrValue);
}

template <class ObjectTypeT>
inline typename ParentSFieldConstReferenceProxy<ObjectTypeT>::IdStoredType
    ParentSFieldConstReferenceProxy<ObjectTypeT>::getId(void) const
{
    return *_pIdValue;
}

/*-------------------------------------------------------------------------*/
/* ParentPointerSField<ObjectTypeT,                                        */
/*                     NamespaceI  >                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::ParentPointerSField(void)
    : Inherited()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::ParentPointerSField(Self const &source)
    : Inherited(source)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::ParentPointerSField(
        ValueType ptrValue, IdStoredType idValue)
    
    : Inherited(ptrValue, idValue)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::~ParentPointerSField(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Access                                                                  */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerSField<ObjectTypeT,
                                    NamespaceI  >::const_reference
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::getValue(void) const
{
    return const_reference(&this->getRawStore(), &this->getRawIdStore());
}

/*-------------------------------------------------------------------------*/
/* Comparison                                                              */

// template <class ObjectTypeT, Int32 NamespaceI>
// inline bool
//     ParentPointerSField<ObjectTypeT,
//                         NamespaceI  >::operator==(Self const &other)
// {   
// }

OSG_END_NAMESPACE
