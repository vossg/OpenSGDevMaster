
#ifndef _OSGCHILDPOINTERSFIELD_H_
#define _OSGCHILDPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGChildPointerSFieldBase.h"
#include "OSGPointerFieldConfigs.h"
//#include "OSGEditPointerSFieldHandle.h"
//#include "OSGGetPointerSFieldHandle.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerSField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class ChildPointerSField;

/*-------------------------------------------------------------------------*/
/* ChildSFieldReferenceProxy<ObjectTypeT>                                  */
/*-------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ChildSFieldReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                         ObjectType;
    
    typedef          ChildSFieldReferenceProxy           Self;
            
    typedef          ChildPointerSField<ObjectTypeT, 0>  SFieldType;
    typedef          ChildFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename SFieldType::AccessHandler           AccessHandler;
    
    // store types
    typedef typename SFieldType::StoredType              StoredType;
    
    // std library types
    typedef typename FieldConfig::ValueType              value_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildSFieldReferenceProxy(StoredType * const pValue,
                              SFieldType *       pField );
    ChildSFieldReferenceProxy(Self const        &source );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildSFieldReferenceProxy(void);
    
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
    StoredType *_pValue;
    SFieldType *_pField;
};

/*---------------------------------------------------------------------------*/
/* ChildPointerSField<FieldConfigT>                                          */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class ChildPointerSField : public ChildPointerSFieldBase<NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef ObjectTypeT                              ObjectType;
    
    typedef ChildPointerSFieldBase<NamespaceI >      Inherited;
    typedef ChildPointerSField    <ObjectType,
                                   NamespaceI >      Self;
                                   
    typedef ChildFieldConfig      <ObjectTypeT,
                                   NamespaceI  >     FieldConfig;
    
    typedef typename FieldConfig::ValueType          ValueType;
    typedef typename FieldConfig::ArgumentType       ArgumentType;
    typedef typename FieldConfig::ValueType          value_type;
       
    typedef typename FieldConfig::PtrType            pointer;
    typedef typename FieldConfig::ConstPtrType       const_pointer;
    typedef typename FieldConfig::SFieldRefType      reference;
    typedef typename FieldConfig::SFieldConstRefType const_reference;
    
    typedef typename Inherited::StoredType           StoredType;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                    >  SFieldTraits;
    typedef FieldDescription<SFieldTraits,
                             SingleField,
                             UnrecordedRefCountPolicy,
                             ChildPtrField>  Description;
    
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
        
    static FieldType::Cardinality const fieldCard  = FieldType  ::SINGLE_FIELD;
    static FieldClass             const fieldClass = FieldConfig::fieldClass;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             ChildPointerSField(void              );
             ChildPointerSField(Self const &source);
    explicit ChildPointerSField(ValueType   value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerSField(void);
    
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

#include "OSGChildPointerSField.inl"

#endif // _OSGCHILDPOINTERSFIELD_H_
