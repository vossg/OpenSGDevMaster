
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
    WeakPointerMFieldBase<NamespaceI>::WeakPointerMFieldBase(void)
    
    : Inherited()
{
}
    
template <Int32 NamespaceI>
    WeakPointerMFieldBase<NamespaceI>::WeakPointerMFieldBase(Self const &source)
    
    : Inherited(source)
{
}

template <Int32 NamespaceI>
    WeakPointerMFieldBase<NamespaceI>::WeakPointerMFieldBase(UInt32 const size)
    
    : Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
    WeakPointerMFieldBase<NamespaceI>::~WeakPointerMFieldBase(void)
{
    // nothing to do
}

OSG_END_NAMESPACE
