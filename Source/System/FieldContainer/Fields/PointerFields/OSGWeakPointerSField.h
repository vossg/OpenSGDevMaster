
#ifndef _OSGWEAKPOINTERSFIELD_H_
#define _OSGWEAKPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointerSFieldCommon.h"
#include "OSGPointerAccessHandler.h"
#include "OSGPointerFieldConfigs.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerSField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class WeakPointerSField;

/*-------------------------------------------------------------------------*/
/* WeakSFieldReferenceProxy<ObjectTypeT>                                   */
/*-------------------------------------------------------------------------*/

template <class ObjectTypeT>
class WeakSFieldReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                        ObjectType;
    
    typedef          WeakSFieldReferenceProxy           Self;
    
    typedef          WeakPointerSField<ObjectTypeT, 0>  SFieldType;
    typedef          WeakFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename SFieldType::AccessHandler          AccessHandler;
    
    // store types
    typedef typename SFieldType::StoredType             StoredType;
    
    // std library types
    typedef typename FieldConfig::ValueType             value_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    explicit WeakSFieldReferenceProxy(FieldContainerPtr *pValue);
             WeakSFieldReferenceProxy(Self const        &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~WeakSFieldReferenceProxy(void);
    
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
/* WeakPointerSField<FieldConfigT>                                           */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class WeakPointerSField : 
    public PointerSFieldCommon<WeakAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
  protected:

    typedef ObjectTypeT                               ObjectType;
    
    typedef PointerSFieldCommon  <WeakAccessHandler, 
                                  NamespaceI       >  Inherited;
    typedef WeakPointerSField    <ObjectType,
                                  NamespaceI >        Self;
    
    typedef WeakFieldConfig      <ObjectTypeT,
                                  NamespaceI  >       FieldConfig;
    
    typedef typename FieldConfig::ValueType           ValueType;
    typedef typename FieldConfig::ArgumentType        ArgumentType;
    typedef typename FieldConfig::ValueType           value_type;
    
    typedef typename FieldConfig::PtrType             pointer;
    typedef typename FieldConfig::ConstPtrType        const_pointer;
    typedef typename FieldConfig::SFieldRefType       reference;
    typedef typename FieldConfig::SFieldConstRefType  const_reference;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                   >  SFieldTraits;
    typedef FieldDescription<SFieldTraits,
                             FieldType::SingleField,
                             WeakRefCountPolicy,
                             FieldType::PtrField          >  Description;
    
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
    
    static FieldType::Cardinality const fieldCard  = FieldType  ::SingleField;
    static FieldType::Class       const Class      = FieldConfig::fieldClass;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

             WeakPointerSField(void              );
             WeakPointerSField(Self const &source);

    explicit WeakPointerSField(ValueType   value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~WeakPointerSField(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

  protected:
    
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

#include "OSGWeakPointerSField.inl"

#endif // _OSGWEAKPOINTERSFIELD_H_
