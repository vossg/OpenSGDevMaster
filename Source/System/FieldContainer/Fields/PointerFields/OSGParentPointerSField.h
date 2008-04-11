
#ifndef _OSGPARENTPOINTERSFIELD_H_
#define _OSGPARENTPOINTERSFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointerSFieldCommon.h"
#include "OSGPointerAccessHandler.h"

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
//    typedef          ParentFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename SFieldType::AccessHandler            AccessHandler;
        
    typedef ObjectTypeT * ValueType;
    typedef ObjectTypeT * value_type;
//    typedef typename FieldConfig::ValueType               ValueType;
//    typedef typename FieldConfig::ValueType               value_type;
    
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
class ParentPointerSField
    : public PointerSFieldCommon<NoRefCountAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          ObjectTypeT                           ObjectType;
        
    typedef          PointerSFieldCommon    <NoRefCountAccessHandler,
                                             NamespaceI  > Inherited;
    typedef          ParentPointerSField    <ObjectTypeT,
                                             NamespaceI  > Self;
                                             
//    typedef          ParentFieldConfig      <ObjectTypeT,
//                                             NamespaceI  > FieldConfig;
    
    typedef ObjectTypeT * ValueType;
    typedef ObjectTypeT * const ArgumentType;
    typedef ObjectTypeT * value_type;

//    typedef typename FieldConfig::ValueType                ValueType;
//    typedef typename FieldConfig::ArgumentType             ArgumentType;
//    typedef typename FieldConfig::ValueType                value_type;
        
//    typedef typename FieldConfig::ConstPtrType             const_pointer;
//    typedef typename FieldConfig::SFieldConstRefType       const_reference;

    typedef ArgumentType *const_pointer;
    typedef ParentSFieldConstReferenceProxy<ObjectType>   const_reference; 
    
    typedef UInt16                                  IdStoredType;
    typedef UInt16                                 &IdStoredTypeRef;
    typedef UInt16 const                           &IdStoredTypeConstRef;
    
    typedef FieldTraits<IdStoredType >              IdBaseTraitsType;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                     >  SFieldTraits;
    typedef FieldDescription<SFieldTraits,
                             FieldType::SingleField,
                             NoRefCountPolicy,
                             FieldType::ParentPtrField  >  Description;
    
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
    static FieldType::Class       const Class      = FieldType::ParentPtrField;
    
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
    /*! \name IdStore Interface                                            */
    /*! \{                                                                 */
    
    // reading values
    UInt16 const idStoreGet(void) const;
    
    // changing values
    void idStoreSet  (UInt16 const newId);
    void idStoreClear(void              );

     /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw IdStore Access                                           */
    /*! \{                                                                 */
    
    IdStoredTypeRef      editRawIdStore(void);
    IdStoredTypeConstRef getRawIdStore (void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

    void  syncWith(Self &source);
    
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
    
    static FieldType    _fieldType;
           IdStoredType _childIdValue;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include "OSGParentPointerSField.inl"

#endif // _OSGPARENTPOINTERSFIELD_H_
