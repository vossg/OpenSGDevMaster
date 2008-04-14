

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerMFieldBase<AccessHandlerT, 
                       NamespaceI    >::ChildPointerMFieldBase(
                           const FieldContainerPtr  pParent,
                                 UInt16             usParentFieldPos) : 
     Inherited    (                ),
    _pEnclosingObj(pParent         ),
    _childFieldId (0xFFFF          ),
    _parentFieldId(usParentFieldPos)
{
}


/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <typename AccessHandlerT, Int32 NamespaceI> inline
ChildPointerMFieldBase<AccessHandlerT, 
                       NamespaceI    >::~ChildPointerMFieldBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child Linking Information                                               */

template <typename AccessHandlerT, Int32 NamespaceI> inline 
FieldContainerPtr 
    ChildPointerMFieldBase<AccessHandlerT, 
                           NamespaceI    >::getEnclosingObject(void) const
{
    return _pEnclosingObj;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerMFieldBase<AccessHandlerT, 
                            NamespaceI    >::setEnclosingObject(
                                const FieldContainerPtr pObj)
{
    _pEnclosingObj = pObj;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
UInt16 ChildPointerMFieldBase<AccessHandlerT, 
                              NamespaceI    >::getChildFieldId(void) const
{
    return _childFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerMFieldBase<AccessHandlerT, 
                            NamespaceI    >::setChildFieldId(
                                const UInt16 childFieldId)
{
    _childFieldId = childFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
UInt16 ChildPointerMFieldBase<AccessHandlerT, 
                              NamespaceI    >::getParentFieldPos(void) const
{
    return _parentFieldId;
}

template <typename AccessHandlerT, Int32 NamespaceI> inline 
void ChildPointerMFieldBase<AccessHandlerT, 
                            NamespaceI    >::setParentFieldId(
                                const UInt16 parentFieldId)
{
    _parentFieldId = parentFieldId;
}

OSG_END_NAMESPACE
