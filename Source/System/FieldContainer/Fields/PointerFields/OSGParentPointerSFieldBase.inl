
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
inline
    ParentPointerSFieldBase<NamespaceI>::ParentPointerSFieldBase(void)
    
    : Inherited    (),
      _childIdValue()
{
    // nothing to do
}

template <Int32 NamespaceI>
inline
    ParentPointerSFieldBase<NamespaceI>::ParentPointerSFieldBase(
        Self const &source)
        
    : Inherited    (source              ),
      _childIdValue(source._childIdValue)
{
    // nothing to do
}

template <Int32 NamespaceI>
inline
    ParentPointerSFieldBase<NamespaceI>::ParentPointerSFieldBase(
        FieldContainerPtrConst ptrValue, IdStoredType idValue)
    
    : Inherited    (ptrValue),
      _childIdValue(idValue )
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
inline
    ParentPointerSFieldBase<NamespaceI>::~ParentPointerSFieldBase(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* IdStore Interface                                                       */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <Int32 NamespaceI>
inline UInt16 const
    ParentPointerSFieldBase<NamespaceI>::idStoreGet(void) const
{
    return _childIdValue;
}
    
/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <Int32 NamespaceI>
inline void
    ParentPointerSFieldBase<NamespaceI>::idStoreSet(UInt16 const newId)
{
    _childIdValue = newId;
}

template <Int32 NamespaceI>
inline void
    ParentPointerSFieldBase<NamespaceI>::idStoreClear(void)
{
    _childIdValue = 0;
}

/*-------------------------------------------------------------------------*/
/* Raw IdStore Access                                                      */

template <Int32 NamespaceI>
inline typename ParentPointerSFieldBase<NamespaceI>::IdStoredTypeRef
    ParentPointerSFieldBase<NamespaceI>::editRawIdStore(void)
{
    return _childIdValue;
}

template <Int32 NamespaceI>
inline typename ParentPointerSFieldBase<NamespaceI>::IdStoredTypeConstRef
    ParentPointerSFieldBase<NamespaceI>::getRawIdStore (void) const
{
    return _childIdValue;
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <Int32 NamespaceI>
inline UInt32
    ParentPointerSFieldBase<NamespaceI>::getBinSize(void) const
{
    return
        Inherited::getBinSize() + IdBaseTraitsType::getBinSize(_childIdValue);
}

template <Int32 NamespaceI>
inline void
    ParentPointerSFieldBase<NamespaceI>::copyToBin(
        BinaryDataHandler &pMem) const
{
    Inherited::copyToBin(pMem);
    
    IdBaseTraitsType::copyToBin(pMem, _childIdValue);
}

template <Int32 NamespaceI>
inline void 
    ParentPointerSFieldBase<NamespaceI>::copyFromBin(
        BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
    
    IdBaseTraitsType::copyFromBin(pMem, _childIdValue);
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

template <Int32 NamespaceI>
inline void 
    ParentPointerSFieldBase<NamespaceI>::syncWith(Self &source)
{
    Inherited::syncWith(source);
    
    _childIdValue = source._childIdValue;
}

OSG_END_NAMESPACE
