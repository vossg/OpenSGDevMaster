

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
inline
    ChildPointerMFieldBase<NamespaceI>::ChildPointerMFieldBase(void)
    : Inherited     (    ),
      _pEnclosingObj(NULL),
      _childFieldId (0   ),
      _parentFieldId(0   )
{
}

template <Int32 NamespaceI>
inline
    ChildPointerMFieldBase<NamespaceI>::ChildPointerMFieldBase(
        Self const &source)
    : Inherited     (source                  ),
      _pEnclosingObj(source._pEnclosingObject),
      _childFieldId (source._childFieldId    ),
      _parentFieldId(source._parentFieldId   )
{
}

template <Int32 NamespaceI>
inline
    ChildPointerMFieldBase<NamespaceI>::ChildPointerMFieldBase(
        UInt32 const size)
    : Inherited     (size),
      _pEnclosingObj(NULL),
      _childFieldId (0   ),
      _parentFieldId(0   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
inline
    ChildPointerMFieldBase<NamespaceI>::~ChildPointerMFieldBase(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Child Linking Information                                               */

template <Int32 NamespaceI>
inline FieldContainerPtr
    ChildPointerMFieldBase<NamespaceI>::getEnclosingObject(void) const
{
    return _pEnclosingObj;
}

template <Int32 NamespaceI>
inline void
    ChildPointerMFieldBase<NamespaceI>::setEnclosingObject(
        FieldContainerPtrConst pObj)
{
    _pEnclosingObj = pObj;
}

template <Int32 NamespaceI>
inline UInt16
    ChildPointerMFieldBase<NamespaceI>::getChildFieldId(void) const
{
    return _childFieldId;
}

template <Int32 NamespaceI>
inline void
    ChildPointerMFieldBase<NamespaceI>::setChildFieldId(
        UInt16 const childFieldId)
{
    _childFieldId = childFieldId;
}

template <Int32 NamespaceI>
inline UInt16
    ChildPointerMFieldBase<NamespaceI>::getParentFieldId(void) const
{
    return _parentFieldId;
}

template <Int32 NamespaceI>
inline void
    ChildPointerMFieldBase<NamespaceI>::setParentFieldId(
        UInt16 const parentFieldId)
{
    _parentFieldId = parentFieldId;
}

OSG_END_NAMESPACE
