
#ifndef _OSGPARENTPOINTERSFIELD_H_
#define _OSGPARENTPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGParentPointerSFieldBase.h"
#include "OSGPointerFieldConfigs.h"
//#include "OSGEditParentPointerSFieldHandle.h"
//#include "OSGGetParentPointerSFieldHandle.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerSField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class ParentPointerSField;

/*---------------------------------------------------------------------------*/
/* ParentSFieldConstReferenceProxy<ObjectTypeT>                              */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ParentSFieldConstReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                          ObjectType;
    
    typedef          ParentSFieldConstReferenceProxy      Self;
    
    typedef          ParentPointerSField<ObjectTypeT, 0>  SFieldType;
    typedef          ParentFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename SFieldType::AccessHandler            AccessHandler;
        
    typedef typename FieldConfig::ValueType               ValueType;
    typedef typename FieldConfig::ValueType               value_type;
    
    // store types
    typedef typename SFieldType::StoredType               StoredType;
    typedef typename SFieldType::IdStoredType             IdStoredType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ParentSFieldConstReferenceProxy(
        StoredType   const * const pPtrValue,
        IdStoredType const * const pIdValue  );
    ParentSFieldConstReferenceProxy(Self const &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentSFieldConstReferenceProxy(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
               operator value_type(void) const;
    value_type operator->         (void) const;
    
    value_type   getPtr(void) const;
    IdStoredType getId (void) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    StoredType   const *_pPtrValue;
    IdStoredType const *_pIdValue;
};

/*---------------------------------------------------------------------------*/
/* ParentPointerSField<ObjectTypeT,                                          */
/*                     NamespaceI  >                                         */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class ParentPointerSField : public ParentPointerSFieldBase<NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          ObjectTypeT                           ObjectType;
        
    typedef          ParentPointerSFieldBase<NamespaceI  > Inherited;
    typedef          ParentPointerSField    <ObjectTypeT,
                                             NamespaceI  > Self;
                                             
    typedef          ParentFieldConfig      <ObjectTypeT,
                                             NamespaceI  > FieldConfig;
    
    typedef typename FieldConfig::ValueType                ValueType;
    typedef typename FieldConfig::ArgumentType             ArgumentType;
    typedef typename FieldConfig::ValueType                value_type;
        
    typedef typename FieldConfig::ConstPtrType             const_pointer;
    typedef typename FieldConfig::SFieldConstRefType       const_reference;
    
    typedef typename Inherited::IdStoredType               IdStoredType;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                     >  SFieldTraits;
    typedef FieldDescription<SFieldTraits,
                             SingleField,
                             NoRefCountPolicy,
                             ParentPtrField  >  Description;
    
    // handles
//    typedef          EditParentPointerSFieldHandle<Self>      EditHandle;
//    typedef typename EditParentPointerSFieldHandle<Self>::Ptr EditHandlePtr;
    
//    typedef          GetParentPointerSFieldHandle <Self>      GetHandle;
//    typedef typename GetParentPointerSFieldHandle <Self>::Ptr GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditParentPointerSFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditParentPointerSFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetParentPointerSFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetParentPointerSFieldHandle <Self>::Ptr DynamicGetHandlePtr;
    
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

    ParentPointerSField(void                          );
    ParentPointerSField(Self const   &other           );
    ParentPointerSField(ValueType     ptrValue,
                        IdStoredType  idValue = 0x0000);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~ParentPointerSField(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */
    
    const_reference getValue(void) const;
        
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

#include "OSGParentPointerSField.inl"

#endif // _OSGPARENTPOINTERSFIELD_H_
