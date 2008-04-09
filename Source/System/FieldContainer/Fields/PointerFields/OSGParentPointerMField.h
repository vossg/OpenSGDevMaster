
#ifndef _OSGPARENTPOINTERMFIELD_H_
#define _OSGPARENTPOINTERMFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGParentPointerMFieldBase.h"
#include "OSGPointerFieldConfigs.h"
//#include "OSGEditParentPointerMFieldHandle.h"
//#include "OSGGetParentPointerMFieldHandle.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerMField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class ParentPointerMField;

/*---------------------------------------------------------------------------*/
/* ParentMFieldConstIterator<ObjectTypeT>                                    */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ParentMFieldConstIterator
    : public ParentPointerMField<ObjectTypeT, 0>::PtrStoreConstItType
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                            ObjectType;
    
    typedef          ParentMFieldConstIterator              Self;
    typedef typename ParentPointerMField<ObjectTypeT, 0>::PtrStoreConstItType
                                                            Inherited;
                                                            
    typedef          ParentPointerMField<ObjectTypeT, 0>    MFieldType;
    typedef          ParentFieldConfig  <ObjectTypeT, 0>    FieldConfig;
    typedef typename MFieldType::AccessHandler              AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType                 StoredType;
    typedef typename MFieldType::PtrStoreType               PtrStoreType;    
    typedef typename MFieldType::PtrStoreConstItType        PtrStoreConstItType;
    
    typedef typename MFieldType::IdStoredType               IdStoredType;
    typedef typename MFieldType::IdStoreType                IdStoreType;
    typedef typename MFieldType::IdStoreConstItType         IdStoreConstItType;
    
    // std library types
    typedef typename PtrStoreConstItType::iterator_category iterator_category;
    typedef typename PtrStoreConstItType::difference_type   difference_type;
    
    typedef typename FieldConfig::ValueType                 value_type;
    typedef typename FieldConfig::ConstPtrType              pointer;
    typedef typename FieldConfig::MFieldConstRefType        reference;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ParentMFieldConstIterator(void                                );
    ParentMFieldConstIterator(Self                const &source   );
    ParentMFieldConstIterator(PtrStoreConstItType const &storeIt,
                              IdStoreConstItType  const &idStoreIt);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentMFieldConstIterator(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
//    value_type operator* (void) const;
    pointer   operator->(void) const;
    
    Self &operator++(void);
    Self  operator++(int );
    
    Self &operator--(void);
    Self  operator--(int );
    
    reference operator[](difference_type const offset) const;
    
    Self &operator+=(difference_type const offset);
    Self  operator+ (difference_type const offset) const;
    
    Self &operator-=(difference_type const offset);
    Self  operator- (difference_type const offset) const;
    
    value_type   getPtr(void) const;
    IdStoredType getId (void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */
    
    PtrStoreConstItType const &base(void) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    IdStoreConstItType _idStoreIt;
};

template <class ObjectTypeT>
typename ParentMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ParentMFieldConstIterator<ObjectTypeT> const &lhs,
              ParentMFieldConstIterator<ObjectTypeT> const &rhs );

template <class ObjectTypeT>
ParentMFieldConstIterator<ObjectTypeT>
    operator+(typename ParentMFieldConstIterator<ObjectTypeT>::differece_type const offset,
              ParentMFieldConstIterator<ObjectTypeT>                          const &rhs   );

/*---------------------------------------------------------------------------*/
/* ParentMFieldConstReferenceProxy<ObjectTypeT>                              */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ParentMFieldConstReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                         ObjectType;
    
    typedef          ParentMFieldConstReferenceProxy     Self;
    
    typedef          ParentPointerMField<ObjectTypeT, 0> MFieldType;
    typedef          ParentFieldConfig  <ObjectTypeT, 0> FieldConfig;
    typedef typename MFieldType::AccessHandler           AccessHandler;
    
    typedef typename FieldConfig::ValueType              ValueType;
    typedef typename FieldConfig::ValueType              value_type;
    
    // store types
    typedef typename MFieldType::StoredType              StoredType;
    typedef typename MFieldType::PtrStoreType            PtrStoreType;
    typedef typename MFieldType::PtrStoreConstItType     PtrStoreConstItType;
    
    typedef typename MFieldType::IdStoredType            IdStoredType;
    typedef typename MFieldType::IdStoreType             IdStoreType;
    typedef typename MFieldType::IdStoreConstItType      IdStoreConstItType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ParentMFieldConstReferenceProxy(
        PtrStoreConstItType const &storeIt,
        IdStoreConstItType  const &idStoreIt);
    ParentMFieldConstReferenceProxy(Self const &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentMFieldConstReferenceProxy(void);
    
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
    PtrStoreConstItType _storeIt;
    IdStoreConstItType  _idStoreIt;
};

/*---------------------------------------------------------------------------*/
/* ParentPointerMField<ObjectTypeT,                                          */
/*                     NamespaceI  >                                         */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class ParentPointerMField : public ParentPointerMFieldBase<NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          ObjectTypeT                           ObjectType;
        
    typedef          ParentPointerMFieldBase<NamespaceI  > Inherited;
    typedef          ParentPointerMField    <ObjectTypeT,
                                             NamespaceI  > Self;
                                             
    typedef          ParentFieldConfig      <ObjectTypeT,
                                             NamespaceI  > FieldConfig;
    
    typedef typename FieldConfig::ValueType                ValueType;
    typedef typename FieldConfig::ArgumentType             ArgumentType;
    typedef typename FieldConfig::ValueType                value_type;
    
    typedef typename FieldConfig::ConstItType              const_iterator;
    typedef typename FieldConfig::ConstReverseItType       const_reverse_iterator;
    
    typedef typename FieldConfig::ConstPtrType             const_pointer;
    typedef typename FieldConfig::MFieldConstRefType       const_reference;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                     >  MFieldTraits;

    typedef FieldDescription<MFieldTraits,
                             MultiField,
                             NoRefCountPolicy,
                             ParentPtrField>  Description;
    
    // handles
//    typedef          EditParentPointerMFieldHandle<Self>      EditHandle;
//    typedef typename EditParentPointerMFieldHandle<Self>::Ptr EditHandlePtr;
    
//    typedef          GetParentPointerMFieldHandle <Self>      GetHandle;
//    typedef typename GetParentPointerMFieldHandle <Self>::Ptr GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditParentPointerMFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditParentPointerMFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetParentPointerMFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetParentPointerMFieldHandle <Self>::Ptr DynamicGetHandlePtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
        
    static FieldType::Cardinality const fieldCard  = FieldType  ::MULTI_FIELD;
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

             ParentPointerMField(void               );
             ParentPointerMField(Self   const &other);
    explicit ParentPointerMField(UInt32 const  size );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~ParentPointerMField(void); 
              
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Interface                                        */
    /*! \{                                                                 */
    
    const_iterator         begin (void) const;
    const_iterator         end   (void) const;
    
    const_reverse_iterator rbegin(void) const;
    const_reverse_iterator rend  (void) const;

    const_reference        front (void) const;
    const_reference        back  (void) const;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Index Operator                                               */
    /*! \{                                                                 */

    const_reference operator [](UInt32 const index) const;
    
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

#include "OSGParentPointerMField.inl"

#endif // _OSGPARENTPOINTERMFIELD_H_
