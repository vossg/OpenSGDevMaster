
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerSFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class PointerSFieldBase
 */
 
/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

inline
    PointerSFieldBase::PointerSFieldBase(void)
    
    : Inherited  (),
      _fieldValue()
{
    // nothing to do
}

inline
    PointerSFieldBase::PointerSFieldBase(Self const &source)
    
    : Inherited  (source            ),
      _fieldValue(source._fieldValue)
{
    // nothing to do
}

inline
    PointerSFieldBase::PointerSFieldBase(FieldContainerPtrConst value)
    
    : Inherited  (     ),
      _fieldValue(value)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

inline
    PointerSFieldBase::~PointerSFieldBase(void)
{
    // nothing to do
}

/*-------------------------------------------------------------------------*/
/* Raw Store Access                                                        */

inline PointerSFieldBase::StoredTypeRef
    PointerSFieldBase::editRawStore(void)
{
    return _fieldValue;
}

inline PointerSFieldBase::StoredTypeConstRef
    PointerSFieldBase::getRawStore(void) const
{
    return _fieldValue;
}

OSG_END_NAMESPACE
