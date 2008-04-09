
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerMFieldCommon.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class PointerMFieldCommon<AccessHandlerT,NamespaceI>

    Common interface implementation for pointer MFields. This class exists
    only to facilitate code reuse; to actually use the provided ptrStore
    interface use the directly derived classes ( \c ChildPointerMFieldBase,
    \c InternalPointerMFieldBase, \c ParentPointerMFieldBase and
    \c WeakPointerMFieldBase ).
    All non-const functions of this class call static member functions of the
    \c AccessHandlerT template parameter (onAdd, onSub, onReplace), whenever
    values are added, removed or replaced respectively. This is used to
    implement reference counting and child/parent linking.
 */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::PointerMFieldCommon(void)
    : Inherited()
{
}

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::PointerMFieldCommon(
        Self const &source)
    : Inherited()
{
    if(source.getRawStore().size() > 0)
    {
        this->editRawStore().resize(source.getRawStore().size(), NullFC);

        PtrStoreItType sI = this->editRawStore().begin();
        PtrStoreItType sE = this->editRawStore().end  ();

        PtrStoreConstItType sSE = source.getRawStore().begin();

        for(; sI != sE; ++sI, ++sSE)
        {
            AccessHandler::onAdd(this, *sI);

            *sI = *sSE;
        }
    }
}

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::PointerMFieldCommon(
        UInt32 const size)
    : Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class AccessHandlerT, Int32 NamespaceI>
inline
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::~PointerMFieldCommon(void)
{
    PtrStoreItType sI = this->editRawStore().begin();
    PtrStoreItType sE = this->editRawStore().end  ();
    
    for(; sI != sE; ++sI)
        AccessHandler::onSub(this, *sI);
}

/*-------------------------------------------------------------------------*/
/* Store Interface                                                         */

/*! This interface fully handles reference counting and child/parent linking,
    but uses FieldContainerPtr instead of the real pointer type stored in the
    field.

    The biggest caveat with this interface is, when you attempt to use it
    with ParentPointerMField, as that will only give you the pointers,
    \em NOT the child field ids as well. To access those, use the
    functions of ParentPointerMFieldBase, that have a "idStore" instead of
    a "ptrStore" prefix.
 */

/*-------------------------------------------------------------------------*/
/* Reading Values                                                          */

template <class AccessHandlerT, Int32 NamespaceI>
inline FieldContainerPtr
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreGet(UInt32 const index) const
{
    return AccessHandler::validate(getRawStore()[index]);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline FieldContainerPtr
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreGet(PtrStoreItType pos) const
{
    return AccessHandler::validate(*pos);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline FieldContainerPtr
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreGet(
        PtrStoreConstItType pos) const
{
    return AccessHandler::validate(*pos);
}

/*-------------------------------------------------------------------------*/
/* Adding Values                                                           */

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreAppend(
        FieldContainerPtrConst pNewObj)
{
    AccessHandler::onAdd(this, pNewObj);

    this->editRawStore().push_back(pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
template <class InputIteratorT                  >
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreAssign(
        InputIteratorT first, InputIteratorT last)
{
    PtrStoreItType sI = this->editRawStore().begin();
    PtrStoreItType sE = this->editRawStore().end  ();
    
    InputIteratorT iI = first;
    InputIteratorT iE = last;
    
    for(; (iI != iE) && (sI != sE); ++iI, ++sI)
    {
        AccessHandler::onReplace(this, *sI, *iI);
        *sI = *iI;
    }
    
    if(iI != iE)
    {
        for(; iI != iE; ++iI)
            this->ptrStoreAppend(*iI);
    }
    else if(sI != sE)
    {
        this->ptrStoreErase(sI, sE);
    }
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreInsert(
        UInt32 const index, FieldContainerPtrConst pNewObj)
{
    this->ptrStoreInsert(this->editRawStore().begin() + index, pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreInsert(
        PtrStoreItType pos, FieldContainerPtrConst pNewObj)
{
    AccessHandler::onAdd(this, pNewObj);

    this->editRawStore().insert(pos, pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
template <class InputIteratorT                  >
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreInsert(
        PtrStoreItType pos, InputIteratorT first, InputIteratorT last)
{
    InputIteratorT iI = first;
    InputIteratorT iE = last;

    for(; iI != iE; ++iI)
        AccessHandler::onAdd(this, *iI);

    this->editRawStore().insert(pos, first, last);
}

/*-------------------------------------------------------------------------*/
/* Changing Values                                                         */

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreReplace(
        UInt32 const index, FieldContainerPtrConst pNewObj)
{
    this->ptrStoreReplace(this->editRawStore().begin() + index, pNewObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreReplace(
        PtrStoreItType pos, FieldContainerPtrConst pNewObj)
{
    AccessHandler::onReplace(this, *pos, pNewObj);

    *pos = pNewObj;
}

/*-------------------------------------------------------------------------*/
/* Removing Values                                                         */

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreErase(
        UInt32 const index)
{
    this->ptrStoreErase(this->editRawStore().begin() + index);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreErase(
        PtrStoreItType pos)
{
    AccessHandler::onSub(this, *pos);

    this->editRawStore().erase(pos);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreErase(
        UInt32 const beginIndex, UInt32 const endIndex)
{
    this->ptrStoreErase(this->editRawStore().begin() + beginIndex,
                        this->editRawStore().begin() + endIndex   );
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreErase(
    PtrStoreItType begin, PtrStoreItType end)
{
    for(PtrStoreItType sI = begin; sI != end; ++sI)
        AccessHandler::onSub(this, *sI);

    this->editRawStore().erase(begin, end);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreClear(void)
{
    PtrStoreItType sI = this->editRawStore().begin();
    PtrStoreItType sE = this->editRawStore().end  ();

    for(; sI != sE; ++sI)
        AccessHandler::onSub(this, *sI);

    this->editRawStore().clear();
}

/*-------------------------------------------------------------------------*/
/* Resizing                                                                */

template <class AccessHandlerT, Int32 NamespaceI>
void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreResize(
        UInt32 const newSize, FieldContainerPtrConst pNewObj)
{
    UInt32 oldSize = this->getRawStore().size();

    if(newSize > oldSize)
    {
        this->editRawStore().resize(newSize, pNewObj);

        PtrStoreItType sI = this->editRawStore().begin() + oldSize;
        PtrStoreItType sE = this->editRawStore().end  ();

        for(; sI != sE; ++sI)
            AccessHandler::onAdd(this, *sI);
    }
    else if(newSize < oldSize)
    {
        PtrStoreItType sI = this->editRawStore().begin() + newSize;
        PtrStoreItType sE = this->editRawStore().end  ();

        for(; sI != sE; ++sI)
            AccessHandler::onSub(this, *sI);

        this->editRawStore().resize(newSize);
    }
}

/*-------------------------------------------------------------------------*/
/* Finding Values                                                          */

template <class AccessHandlerT, Int32 NamespaceI>
inline Int32
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreFindIndex(
        FieldContainerPtrConst pOldObj) const
{
    PtrStoreConstItType sI = std::find(this->getRawStore().begin(),
                                       this->getRawStore().end  (), pOldObj);

    if(sI != this->getRawStore().end())
    {
        return std::distance(this->getRawStore().begin(), sI);
    }
    else
    {
        return -1;
    }
}

template <class AccessHandlerT, Int32 NamespaceI>
inline typename PointerMFieldCommon<AccessHandlerT,
                                    NamespaceI     >::PtrStoreItType
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreFind(
        FieldContainerPtrConst pObj)
{
    return std::find(this->editRawStore().begin(),
                     this->editRawStore().end  (), pObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline typename PointerMFieldCommon<AccessHandlerT,
                                    NamespaceI     >::PtrStoreConstItType
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreFind(
        FieldContainerPtrConst pObj) const
{
    return std::find(this->getRawStore().begin(),
                     this->getRawStore().end  (), pObj);
}

template <class AccessHandlerT, Int32 NamespaceI>
inline UInt32
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::ptrStoreSize(void) const
{
    return this->getRawStore().size();
}

/*-------------------------------------------------------------------------*/
/* Std library interface                                                   */

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::reserve(size_type size)
{
    this->editRawStore().reserve(size);
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class AccessHandlerT, Int32 NamespaceI>
inline UInt32
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::getBinSize(void) const
{
    return sizeof(UInt32) +
        PtrBaseTraitsType::getBinSize(&(this->getRawStore().front()),
                                        this->getRawStore().size ()  );
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::copyToBin(
        BinaryDataHandler &pMem) const
{
    UInt32 thisSize = this->getRawStore().size();

    pMem.putValue(thisSize);

    if(thisSize != 0)
    {
        PtrBaseTraitsType::copyToBin(
            pMem, &(this->getRawStore().front()), thisSize);
    }
}

template <class AccessHandlerT, Int32 NamespaceI>
void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::copyFromBin(
        BinaryDataHandler &pMem)
{
    UInt32 thisSize   = this->ptrStoreSize();
    UInt32 sourceSize;

    pMem.getValue(sourceSize);

    if(sourceSize > 0)
    {
        if(sourceSize > thisSize)
        {
            // [0, thisSize[ contains entries that are being replaced
            this->editRawStore().resize(sourceSize);

            PtrStoreItType tI = this->editRawStore().begin();
            PtrStoreItType tE = this->editRawStore().begin() + thisSize;

            for(; tI != tE; ++tI)
            {
                FieldContainerPtr pNewObj;

                PtrBaseTraitsType::copyFromBin  (pMem, pNewObj     );
                AccessHandler    ::onSyncReplace(this, *tI, pNewObj);

                *tI = pNewObj;
            }

            // [thisSize, sourceSize[ contains entries that are added
            PtrBaseTraitsType::copyFromBin(pMem, &(*tI), sourceSize - thisSize);

            tE = this->editRawStore().end();

            for(; tI != tE; ++tI)
                AccessHandler::onSyncAdd(this, *tI);
        }
        else
        {
            // [0, sourceSize[ contains entries that are being replaced
            PtrStoreItType tI = this->editRawStore().begin();
            PtrStoreItType tE = this->editRawStore().begin() + sourceSize;

            for(; tI != tE; ++tI)
            {
                FieldContainerPtr pNewObj;

                PtrBaseTraitsType::copyFromBin  (pMem, pNewObj     );
                AccessHandler    ::onSyncReplace(this, *tI, pNewObj);

                *tI = pNewObj;
            }

            // [sourceSize, thisSize[ contains entries that are being removed
            tE = this->editRawStore().end();

            for(; tI != tE; ++tI)
                AccessHandler::onSyncSub(this, *tI);

            this->editRawStore().resize(sourceSize);
        }
    }
    else
    {
        // [0, thisSize[ contains entries that are being removed
        PtrStoreItType tI = this->editRawStore().begin();
        PtrStoreItType tE = this->editRawStore().end  ();

        for(; tI != tE; ++tI)
            AccessHandler::onSyncSub(this, *tI);

        this->editRawStore().clear();
    }
}

/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

/*! Syncronizes this field with a different Aspect.

    Two things need to be carefully handled here: First, depending on whether
    the size increases or decreases some values are replaced, added or removed
    and their reference count has to be adjusted accordingly.
    Second, the onSync{Add,Sub,Replace} functions of the AccessHandler have to
    be called.
 */
template <class AccessHandlerT, Int32 NamespaceI>
void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::syncWith(
        Self   &source,     ConstFieldMaskArg  syncMode,
        UInt32  uiSyncInfo, AspectOffsetStore &oOffsets )
{
    UInt32 thisSize   = this  ->ptrStoreSize();
    UInt32 sourceSize = source. ptrStoreSize();

    if(sourceSize > 0)
    {
        if(sourceSize > thisSize)
        {
            // [0, thisSize[ contains entries that are being replaced
            this->editRawStore().resize(sourceSize);

            PtrStoreConstItType sI = source.getRawStore().begin();
            PtrStoreConstItType sE = source.getRawStore().end  ();

            PtrStoreItType tI = this->editRawStore().begin();
            PtrStoreItType tE = this->editRawStore().begin() + thisSize;

            for(; tI != tE; ++tI, ++sI)
            {
                FieldContainerPtr pNewObj = convertToCurrentAspect(*sI);

                AccessHandler::onSyncReplace(this, *tI, pNewObj);

                *tI = pNewObj;
            }

            // [thisSize, sourceSize[ contains entries that are added
            for(; sI != sE; ++tI, ++sI)
            {
                FieldContainerPtr pNewObj = convertToCurrentAspect(*sI);
            
                AccessHandler::onSyncAdd(this, pNewObj);

                *tI = pNewObj;
            }
        }
        else
        {        
            // [0, sourceSize[ contains entries that are being replaced
            PtrStoreConstItType sI = source.getRawStore().begin();
            PtrStoreConstItType sE = source.getRawStore().end  ();

            PtrStoreItType tI = this->editRawStore().begin();
            PtrStoreItType tE = this->editRawStore().end  ();

            for(; sI != sE; ++tI, ++sI)
            {
                FieldContainerPtr pNewObj = convertToCurrentAspect(*sI);

                AccessHandler::onSyncReplace(this, *tI, pNewObj);

                *tI = pNewObj;
            }

            // [sourceSize, thisSize[ contains entries that are being removed
            for(; tI != tE; ++tI)
                AccessHandler::onSyncSub(this, *tI);

            this->editRawStore().resize(sourceSize);
        }
    }
    else
    {    
        // [0, thisSize[ contains entries that are being removed
        PtrStoreItType tI = this->editRawStore().begin();
        PtrStoreItType tE = this->editRawStore().end  ();

        for(; tI != tE; ++tI)
            AccessHandler::onSyncSub(this, *tI);

        this->editRawStore().clear();
    }
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::beginEdit(
        UInt32, AspectOffsetStore &)
{
    // nothing to do
}

template <class AccessHandlerT, Int32 NamespaceI>
inline typename PointerMFieldCommon<AccessHandlerT,
                                    NamespaceI     >::Self *
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::resolveShare(
        UInt32, AspectOffsetStore &)
{
    return NULL;
}

template <class AccessHandlerT, Int32 NamespaceI>
inline void
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::terminateShare(
        UInt32, AspectOffsetStore &)
{
    // nothing to do
}

template <class AccessHandlerT, Int32 NamespaceI>
inline bool
    PointerMFieldCommon<AccessHandlerT,
                        NamespaceI     >::isShared(void)
{
    return false;
}

/*-------------------------------------------------------------------------*/
/* Free functions                                                          */

template <class LHSAccessHandlerT,
          Int32 LHSNamespaceI,
          class RHSAccessHandlerT,
          Int32 RHSNamespaceI     >
inline bool
    operator==(
        PointerMFieldCommon<LHSAccessHandlerT, LHSNamespaceI> const &lhs,
        PointerMFieldCommon<RHSAccessHandlerT, RHSNamespaceI> const &rhs )
{
    return lhs.size() == rhs.size() &&
        std::equal(lhs.getRawStore().begin(),
                   lhs.getRawStore().end  (),
                   rhs.getRawStore().begin() );
}

OSG_END_NAMESPACE
