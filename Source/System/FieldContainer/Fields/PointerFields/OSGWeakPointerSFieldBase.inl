
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
inline
    WeakPointerSFieldBase<NamespaceI>::WeakPointerSFieldBase(void)
    : Inherited()
{
}

template <Int32 NamespaceI>
inline
    WeakPointerSFieldBase<NamespaceI>::WeakPointerSFieldBase(
        Self const &source)
    : Inherited(source)
{
}

template <Int32 NamespaceI>
inline
    WeakPointerSFieldBase<NamespaceI>::WeakPointerSFieldBase(
        FieldContainerPtrConst value)
    : Inherited(value)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
inline
    WeakPointerSFieldBase<NamespaceI>::~WeakPointerSFieldBase(void)
{
    // nothing to do
}

OSG_END_NAMESPACE
