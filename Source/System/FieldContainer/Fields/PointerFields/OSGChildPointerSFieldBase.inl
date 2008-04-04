
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
inline
    ChildPointerSFieldBase<NamespaceI>::ChildPointerSFieldBase(void)
    : Inherited     (    ),
      _pEnclosingObj(NULL),
      _childFieldId (0   ),
      _parentFieldId(0   )
{
}

template <Int32 NamespaceI>
inline
    ChildPointerSFieldBase<NamespaceI>::ChildPointerSFieldBase(
        Self const &source)
    : Inherited     (source               ),
      _pEnclosingObj(source._pEnclosingObj),
      _childFieldId (source._childFieldId ),
      _parentFieldId(source._parentFieldId)
{
}

template <Int32 NamespaceI>
inline
    ChildPointerSFieldBase<NamespaceI>::ChildPointerSFieldBase(
        FieldContainerPtrConst value)
    : Inherited     (value),
      _pEnclosingObj(NULL ),
      _childFieldId (0    ),
      _parentFieldId(0    )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
inline
    ChildPointerSFieldBase<NamespaceI>::~ChildPointerSFieldBase(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Child Linking Information                                               */

template <Int32 NamespaceI>
inline FieldContainerPtr
    ChildPointerSFieldBase<NamespaceI>::getEnclosingObject(void) const
{
    return _pEnclosingObj;
}

template <Int32 NamespaceI>
inline void
    ChildPointerSFieldBase<NamespaceI>::setEnclosingObject(
        FieldContainerPtrConst pObj)
{
    _pEnclosingObj = pObj;
}

template <Int32 NamespaceI>
inline UInt16
    ChildPointerSFieldBase<NamespaceI>::getChildFieldId(void) const
{
    return _childFieldId;
}

template <Int32 NamespaceI>
inline void
    ChildPointerSFieldBase<NamespaceI>::setChildFieldId(
        UInt16 const childFieldId)
{
    _childFieldId = childFieldId;
}

template <Int32 NamespaceI>
inline UInt16
    ChildPointerSFieldBase<NamespaceI>::getParentFieldId(void) const
{
    return _parentFieldId;
}

template <Int32 NamespaceI>
inline void
    ChildPointerSFieldBase<NamespaceI>::setParentFieldId(
        UInt16 const parentFieldId)
{
    _parentFieldId = parentFieldId;
}

OSG_END_NAMESPACE
