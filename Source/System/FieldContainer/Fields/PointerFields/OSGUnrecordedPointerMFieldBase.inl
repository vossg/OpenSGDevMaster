
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <Int32 NamespaceI>
    UnrecordedPointerMFieldBase<NamespaceI>::UnrecordedPointerMFieldBase(void)
    
    : Inherited()
{
}

template <Int32 NamespaceI>
    UnrecordedPointerMFieldBase<NamespaceI>::UnrecordedPointerMFieldBase(
        UInt32 const size)
    
    : Inherited(size)
{
}
    
template <Int32 NamespaceI>
    UnrecordedPointerMFieldBase<NamespaceI>::UnrecordedPointerMFieldBase(
        Self const &source)
    
    : Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <Int32 NamespaceI>
    UnrecordedPointerMFieldBase<NamespaceI>::~UnrecordedPointerMFieldBase(void)
{
    // nothing to do
}

OSG_END_NAMESPACE
