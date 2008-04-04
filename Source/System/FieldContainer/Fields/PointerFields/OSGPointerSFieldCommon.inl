
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerSFieldCommon.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class PointerSFieldCommon<AccessHandlerT,NamespaceI>

 */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::PointerSFieldCommon(void)
    : Inherited()
{
    // nothing to do
}

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::PointerSFieldCommon(
        Self const &source)
    
    : Inherited(source)
{
    AccessHandler::onAdd(this, _fieldValue);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::PointerSFieldCommon(
        FieldContainerPtrConst value)
    
    : Inherited(value)
{
    AccessHandler::onAdd(this, _fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::~PointerSFieldCommon(void)
{
    AccessHandler::onSub(this, _fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Store Interface                                                         */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class AccessHandlerT, Int32 NamespaceI>
inline FieldContainerPtr
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreGet(void) const
{
    return AccessHandler::validate(_fieldValue);
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreSet(
        FieldContainerPtrConst pNewObj)
{
    AccessHandler::onReplace(this, _fieldValue, pNewObj);
    
    _fieldValue = pNewObj;
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreClear(void)
{
    AccessHandler::onSub(this, _fieldValue);
    
    _fieldValue = NullFC;
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class AccessHandlerT, Int32 NamespaceI>
inline UInt32
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::getBinSize(void) const
{
    return PtrBaseTraitsType::getBinSize(_fieldValue);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::copyToBin(
        BinaryDataHandler &pMem) const
{
    PtrBaseTraitsType::copyToBin(pMem, _fieldValue);
}
        
template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::copyFromBin(
        BinaryDataHandler &pMem)
{
    FieldContainerPtr pNewObj;
    
    PtrBaseTraitsType::copyFromBin  (pMem, pNewObj             );
    AccessHandler    ::onSyncReplace(this, _fieldValue, pNewObj);
    
    _fieldValue = pNewObj;
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerSFieldCommon<AccessHandlerT,
                        NamespaceI     >::syncWith(Self &source)
{
    FieldContainerPtr pNewObj = convertToCurrentAspect(source.ptrStoreGet());
    
    AccessHandler::onSyncReplace(this, _fieldValue, pNewObj);
    
    _fieldValue = pNewObj;
}

/*-------------------------------------------------------------------------*/
/* Free functions                                                          */

template <class LHSAccessHandlerT,
          Int32 LHSNamespaceI,
          class RHSAccessHandlerT,
          Int32 RHSNamespaceI     >
inline bool
    operator==(
        PointerSFieldCommon<LHSAccessHandlerT, LHSNamespaceI> const &lhs,
        PointerSFieldCommon<RHSAccessHandlerT, RHSNamespaceI> const &rhs )
{
    return lhs.ptrStoreGet() == rhs.ptrStoreGet();
}

OSG_END_NAMESPACE
