
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
inline
    UnrecordedPointerSFieldBase<NamespaceI>::UnrecordedPointerSFieldBase(void)
    : Inherited()
{
}

template <Int32 NamespaceI>
inline
    UnrecordedPointerSFieldBase<NamespaceI>::UnrecordedPointerSFieldBase(
        Self const &source)
    : Inherited(source)
{
}

template <Int32 NamespaceI>
inline
    UnrecordedPointerSFieldBase<NamespaceI>::UnrecordedPointerSFieldBase(
        FieldContainerPtrConst value)
    : Inherited(value)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
inline
    UnrecordedPointerSFieldBase<NamespaceI>::~UnrecordedPointerSFieldBase(void)
{
    // nothing to do
}

OSG_END_NAMESPACE
