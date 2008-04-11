

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
    : Inherited(),
      _childIdValue()
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::ParentPointerSField(Self const &source)
    : Inherited(source),
      _childIdValue(source._childIdValue)
{
    // nothing to do
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    ParentPointerSField<ObjectTypeT,
                        NamespaceI  >::ParentPointerSField(
        ValueType ptrValue, IdStoredType idValue)
    
    : Inherited(ptrValue),
      _childIdValue(idValue )
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
/* IdStore Interface                                                       */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class ObjectTypeT, Int32 NamespaceI>
inline UInt16 const
    ParentPointerSField<ObjectTypeT, NamespaceI>::idStoreGet(void) const
{
    return _childIdValue;
}
    
/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerSField<ObjectTypeT, NamespaceI>::idStoreSet(UInt16 const newId)
{
    _childIdValue = newId;
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerSField<ObjectTypeT, NamespaceI>::idStoreClear(void)
{
    _childIdValue = 0;
}

/*-------------------------------------------------------------------------*/
/* Raw IdStore Access                                                      */

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerSField<ObjectTypeT, NamespaceI>::IdStoredTypeRef
    ParentPointerSField<ObjectTypeT, NamespaceI>::editRawIdStore(void)
{
    return _childIdValue;
}

template <class ObjectTypeT, Int32 NamespaceI>
inline typename ParentPointerSField<ObjectTypeT, NamespaceI>::IdStoredTypeConstRef
    ParentPointerSField<ObjectTypeT, NamespaceI>::getRawIdStore (void) const
{
    return _childIdValue;
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class ObjectTypeT, Int32 NamespaceI>
inline UInt32
    ParentPointerSField<ObjectTypeT, NamespaceI>::getBinSize(void) const
{
    return
        Inherited::getBinSize() + IdBaseTraitsType::getBinSize(_childIdValue);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void
    ParentPointerSField<ObjectTypeT, NamespaceI>::copyToBin(
        BinaryDataHandler &pMem) const
{
    Inherited::copyToBin(pMem);
    
    IdBaseTraitsType::copyToBin(pMem, _childIdValue);
}

template <class ObjectTypeT, Int32 NamespaceI>
inline void 
    ParentPointerSField<ObjectTypeT, NamespaceI>::copyFromBin(
        BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
    
    IdBaseTraitsType::copyFromBin(pMem, _childIdValue);
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

template <class ObjectTypeT, Int32 NamespaceI>
inline void 
    ParentPointerSField<ObjectTypeT, NamespaceI>::syncWith(Self &source)
{
    Inherited::syncWith(source);
    
    _childIdValue = source._childIdValue;
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
