
#ifndef _OSGUNRECORDEDPOINTERSFIELD_H_
#define _OSGUNRECORDEDPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointerSFieldCommon.h"
#include "OSGPointerAccessHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerSField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class UnrecordedPointerSField;

/*-------------------------------------------------------------------------*/
/* UnrecordedSFieldReferenceProxy<ObjectTypeT>                             */
/*-------------------------------------------------------------------------*/

template <class ObjectTypeT>
class UnrecordedSFieldReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                              ObjectType;
    
    typedef          UnrecordedSFieldReferenceProxy           Self;
    
    typedef          UnrecordedPointerSField<ObjectTypeT, 0>  SFieldType;
//    typedef          UnrecordedFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename SFieldType::AccessHandler                AccessHandler;
    
    // store types
    typedef typename SFieldType::StoredType                   StoredType;
    
    // std library types
    typedef ObjectTypeT * value_type;
//    typedef typename FieldConfig::ValueType                   value_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    explicit UnrecordedSFieldReferenceProxy(FieldContainerPtr *pValue);
             UnrecordedSFieldReferenceProxy(Self const        &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~UnrecordedSFieldReferenceProxy(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
               operator value_type(void) const;
    value_type operator->         (void) const;
    
    void operator=(value_type newValue);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    FieldContainerPtr *_pValue;
};

/*---------------------------------------------------------------------------*/
/* UnrecordedPointerSField<FieldConfigT>                                     */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class UnrecordedPointerSField : 
    public PointerSFieldCommon<UnrecordedAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
  protected:

    typedef ObjectTypeT                                   ObjectType;
    
    typedef PointerSFieldCommon<UnrecordedAccessHandler, 
                                        NamespaceI>       Inherited;
    typedef UnrecordedPointerSField    <ObjectType,
                                        NamespaceI >      Self;
    
//    typedef UnrecordedFieldConfig      <ObjectTypeT,
//                                        NamespaceI  >     FieldConfig;
    
//    typedef typename FieldConfig::ValueType               ValueType;
//    typedef typename FieldConfig::ArgumentType            ArgumentType;
//    typedef typename FieldConfig::ValueType               value_type;

    typedef ObjectTypeT * ValueType;
    typedef ObjectTypeT * const ArgumentType;
    typedef ObjectTypeT * value_type;
    
    typedef ValueType *pointer;
    typedef ArgumentType *const_pointer;

//    typedef typename FieldConfig::PtrType                 pointer;
//    typedef typename FieldConfig::ConstPtrType            const_pointer;

    typedef UnrecordedSFieldReferenceProxy<ObjectType>   reference;
    typedef ValueType const                             &const_reference; 

//    typedef typename FieldConfig::SFieldRefType           reference;
//    typedef typename FieldConfig::SFieldConstRefType      const_reference;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                         >  SFieldTraits;
    typedef FieldDescription<SFieldTraits,
                             FieldType::SingleField,
                             UnrecordedRefCountPolicy,
                             FieldType::PtrField                >  Description;
                             
    // handles
//    typedef          EditPointerSFieldHandle<Self>      EditHandle;
//    typedef typename EditPointerSFieldHandle<Self>::Ptr EditHandlePtr;
    
//    typedef          GetPointerSFieldHandle <Self>      GetHandle;
//    typedef typename GetPointerSFieldHandle <Self>::Ptr GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditPointerSFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditPointerSFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetPointerSFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetPointerSFieldHandle <Self>::Ptr DynamicGetHandlePtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static FieldType::Cardinality const fieldCard  = FieldType::SingleField;
    static FieldType::Class       const Class      = FieldType::PtrField;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             UnrecordedPointerSField(void              );
             UnrecordedPointerSField(Self const &source);
    explicit UnrecordedPointerSField(ValueType   value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~UnrecordedPointerSField(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    reference       editValue(void           );
    const_reference getValue (void           ) const;
    
    void            setValue (ValueType   value );
    void            setValue (Self const &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */

    void operator = (Self const &source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType _fieldType;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGUnrecordedPointerSField.inl"

#endif // _OSGUNRECORDEDPOINTERSFIELD_H_
