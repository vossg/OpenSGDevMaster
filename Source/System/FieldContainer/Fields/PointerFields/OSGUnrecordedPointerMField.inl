
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerMField.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* UnrecordedPointerMField<ObjectTypeT,                                    */
/*                         NamespaceI  >                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline FieldType const &
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerMField(void)
    : Inherited()
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerMField(
        Self const &other)
        
    : Inherited(other)
{
}

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::UnrecordedPointerMField(
        UInt32 const size)
        
    : Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, Int32 NamespaceI>
inline
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::~UnrecordedPointerMField(void)
{
}


template <class ObjectTypeT, Int32 NamespaceI>
inline typename UnrecordedPointerMField<ObjectTypeT,
                                        NamespaceI  >::Self &
    UnrecordedPointerMField<ObjectTypeT,
                            NamespaceI  >::operator=(Self const &source)
{
    this->setValues(source);
    
    return *this;
}

OSG_END_NAMESPACE
