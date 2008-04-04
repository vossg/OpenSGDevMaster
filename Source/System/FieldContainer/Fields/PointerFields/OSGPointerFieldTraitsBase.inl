
OSG_BEGIN_NAMESPACE

template <Int32 NamespaceI>
inline UInt32
    PointerFieldTraitsBase<NamespaceI>::getBinSize(
        FieldContainerPtrConst)
{
    return sizeof(UInt32);
}

template <Int32 NamespaceI>
inline UInt32
    PointerFieldTraitsBase<NamespaceI>::getBinSize(
        FieldContainerPtrConst *,
        UInt32 const            uiNumObjects)
{
    return sizeof(UInt32) * uiNumObjects;
}

template <Int32 NamespaceI>
inline void
    PointerFieldTraitsBase<NamespaceI>::copyToBin(
        BinaryDataHandler      &pMem,
        FieldContainerPtrConst  pObject)
{
    UInt32 containerId;

    if(pObject == NullFC)
    {
        // containerId = 0 indicates a Null Ptr
        containerId = 0;
    }
    else
    {
        containerId = pObject->getId();
    }

    pMem.putValue(containerId);
}
                             
template <Int32 NamespaceI>
inline void
    PointerFieldTraitsBase<NamespaceI>::copyToBin(
        BinaryDataHandler      &pMem,
        FieldContainerPtrConst *pObjectStore,
        UInt32 const            uiNumObjects )
{
    for(UInt32 i = 0; i < uiNumObjects; i++)
    {
        copyToBin(pMem, pObjectStore[i]);
    }
}

template <Int32 NamespaceI>
inline void
    PointerFieldTraitsBase<NamespaceI>::copyFromBin(
        BinaryDataHandler &pMem, 
        FieldContainerPtr &pObject)
{
    UInt32 containerId;

    pMem.getValue(containerId);

    if(0 != containerId)
    {
        pObject = FieldContainerFactory::the()->getMappedContainer(containerId);
    }
    else
    {
        pObject = NullFC;
    }
}

template <Int32 NamespaceI>
inline void
    PointerFieldTraitsBase<NamespaceI>::copyFromBin(
        BinaryDataHandler &pMem, 
        FieldContainerPtr *pObjectStore,
        UInt32 const       uiNumObjects )
{
    for(UInt32 i = 0; i < uiNumObjects; ++i)
    {
        copyFromBin(pMem, pObjectStore[i]);
    }
}

OSG_END_NAMESPACE
