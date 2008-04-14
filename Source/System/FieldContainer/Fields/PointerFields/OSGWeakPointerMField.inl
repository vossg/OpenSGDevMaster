
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerMField.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* WeakPointerMField<ObjectTypeT,                                          */
/*                   NamespaceI  >                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI> inline 
const FieldType &WeakPointerMField<ObjectTypeT,
                                   NamespaceI >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI> inline
WeakPointerMField<ObjectTypeT,
                  NamespaceI >::WeakPointerMField(void) :
    Inherited()
{
}

template <class ObjectTypeT, Int32 NamespaceI> inline
WeakPointerMField<ObjectTypeT,
                  NamespaceI >::WeakPointerMField(const Self &other) :
    Inherited(other)
{
}

template <class ObjectTypeT, Int32 NamespaceI> inline
WeakPointerMField<ObjectTypeT,
                  NamespaceI >::WeakPointerMField(const UInt32 size) :
    Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI> inline
WeakPointerMField<ObjectTypeT,
                  NamespaceI  >::~WeakPointerMField(void)
{
}


template <class ObjectTypeT, Int32 NamespaceI> inline 
typename WeakPointerMField<ObjectTypeT,
                           NamespaceI  >::Self &
    WeakPointerMField<ObjectTypeT,
                      NamespaceI >::operator =(const Self &source)
{
    this->setValues(source);
    
    return *this;
}

OSG_END_NAMESPACE
