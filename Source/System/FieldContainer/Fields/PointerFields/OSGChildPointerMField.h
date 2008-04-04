

#ifndef _OSGCHILDPOINTERMFIELD_H_
#define _OSGCHILDPOINTERMFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGChildPointerMFieldBase.h"
#include "OSGPointerFieldConfigs.h"
#include "OSGEditPointerMFieldHandle.h"
#include "OSGGetPointerMFieldHandle.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerMField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class ChildPointerMField;

template <class ObjectTypeT>
class ChildMFieldConstIterator;


/*---------------------------------------------------------------------------*/
/* ChildMFieldIterator<ObjectTypeT>                                          */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ChildMFieldIterator 
    : public ChildPointerMField<ObjectTypeT, 0>::PtrStoreItType
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                           ObjectType;
    
    typedef          ChildMFieldIterator                   Self;
    typedef typename ChildPointerMField<ObjectTypeT, 0>::PtrStoreItType
                                                           Inherited;
           
    typedef          ChildPointerMField<ObjectTypeT, 0>    MFieldType;
    typedef          ChildFieldConfig  <ObjectTypeT, 0>    FieldConfig;
    typedef typename MFieldType::AccessHandler             AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType                StoredType;
    typedef typename MFieldType::PtrStoreType              PtrStoreType;
    typedef typename MFieldType::PtrStoreItType            PtrStoreItType;
    
    // std library typedefs
    typedef typename Inherited::iterator_category          iterator_category;
    typedef typename Inherited::difference_type            difference_type;
    
    typedef typename FieldConfig::ValueType                value_type;
    typedef typename FieldConfig::PtrType                  pointer;
    typedef typename FieldConfig::MFieldRefType            reference;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildMFieldIterator(void                            );
    ChildMFieldIterator(Self           const &source    );
       
    ChildMFieldIterator(PtrStoreItType const &storeIter,
                        MFieldType           *pField    );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
                               
    ~ChildMFieldIterator(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
    reference operator* (void                        ) const;
    pointer   operator->(void                        ) const;
    
    reference operator[](difference_type const offset) const;
    
    Self &operator++(void);
    Self  operator++(int );
    
    Self &operator--(void);
    Self  operator--(int );
    
    Self &operator+=(difference_type const offset);
    Self  operator+ (difference_type const offset) const;
    
    Self &operator-=(difference_type const offset);
    Self  operator- (difference_type const offset) const;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */
    
    PtrStoreItType const &base(void) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    MFieldType  *_pField;
};

template <class ObjectTypeT>
typename ChildMFieldIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldIterator<ObjectTypeT> const &lhs,
              ChildMFieldIterator<ObjectTypeT> const &rhs );

template <class ObjectTypeT>
ChildMFieldIterator<ObjectTypeT>
    operator+(
        typename ChildMFieldIterator<ObjectTypeT>::differece_type const offset,
        ChildMFieldIterator<ObjectTypeT>                          const &rhs   );

/*---------------------------------------------------------------------------*/
/* ChildMFieldConstIterator<ObjectTypeT>                                     */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ChildMFieldConstIterator
    : public ChildPointerMField<ObjectTypeT, 0>::PtrStoreConstItType
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                           ObjectType;
    
    typedef          ChildMFieldConstIterator              Self;
    typedef typename ChildPointerMField<ObjectTypeT, 0>::PtrStoreConstItType
                                                           Inherited;
           
    typedef          ChildPointerMField<ObjectTypeT, 0>    MFieldType;
    typedef          ChildFieldConfig  <ObjectTypeT, 0>    FieldConfig;
    typedef typename MFieldType::AccessHandler             AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType                StoredType;
    typedef typename MFieldType::PtrStoreType              PtrStoreType;
    typedef typename MFieldType::PtrStoreConstItType       PtrStoreConstItType;
    
    // std library types
    typedef typename Inherited::iterator_category          iterator_category;
    typedef typename Inherited::difference_type            difference_type;
    
    typedef typename FieldConfig::ConstValueType           value_type;
    typedef typename FieldConfig::ConstPtrType             pointer;
    typedef typename FieldConfig::MFieldConstRefType       reference;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildMFieldConstIterator(void                                             );
    ChildMFieldConstIterator(Self                             const &source   );
    ChildMFieldConstIterator(ChildMFieldIterator<ObjectTypeT> const &fieldIter);
    ChildMFieldConstIterator(PtrStoreConstItType              const &storeIter);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
                               
    ~ChildMFieldConstIterator(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Operators                                                    */
    /*! \{                                                                 */
    
    reference operator* (void                        ) const;
    pointer   operator->(void                        ) const;
    
    reference operator[](difference_type const offset) const;
    
    Self &operator++(void);
    Self  operator++(int );
    
    Self &operator--(void);
    Self  operator--(int );
    
    Self &operator+=(difference_type const offset);
    Self  operator+ (difference_type const offset) const;
    
    Self &operator-=(difference_type const offset);
    Self  operator- (difference_type const offset) const;
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Base                                                         */
    /*! \{                                                                 */
    
    PtrStoreConstItType const &base(void) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
};

template <class ObjectTypeT>
typename ChildMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldConstIterator<ObjectTypeT> const &lhs,
              ChildMFieldConstIterator<ObjectTypeT> const &rhs );
              
template <class ObjectTypeT>
typename ChildMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldIterator     <ObjectTypeT> const &lhs,
              ChildMFieldConstIterator<ObjectTypeT> const &rhs );

template <class ObjectTypeT>
typename ChildMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(ChildMFieldConstIterator<ObjectTypeT> const &lhs,
              ChildMFieldIterator     <ObjectTypeT> const &rhs );
              
template <class ObjectTypeT>
ChildMFieldConstIterator<ObjectTypeT>
    operator+(
        typename ChildMFieldConstIterator<ObjectTypeT>::difference_type const  offset,
        ChildMFieldConstIterator<ObjectTypeT>                           const &rhs    );

/*-------------------------------------------------------------------------*/
/* ChildMFieldReferenceProxy<ObjectTypeT>                                  */
/*-------------------------------------------------------------------------*/

template <class ObjectTypeT>
class ChildMFieldReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                         ObjectType;
    
    typedef          ChildMFieldReferenceProxy           Self;
            
    typedef          ChildPointerMField<ObjectTypeT, 0>  MFieldType;
    typedef          ChildFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename MFieldType::AccessHandler           AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType              StoredType;
    typedef typename MFieldType::PtrStoreType            PtrStoreType;    
    typedef typename MFieldType::PtrStoreItType          PtrStoreItType;
    typedef typename MFieldType::PtrStoreConstItType     PtrStoreConstItType;
    
    // std library types
    typedef typename FieldConfig::ValueType              value_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildMFieldReferenceProxy(PtrStoreItType const &storeIter,
                              MFieldType           *pField    );
    ChildMFieldReferenceProxy(Self const           &source    );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildMFieldReferenceProxy(void);
    
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
    PtrStoreItType  _storeIter;
    MFieldType     *_pField;
};

/*---------------------------------------------------------------------------*/
/* ChildPointerMField<FieldConfigT>                                          */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class ChildPointerMField : public ChildPointerMFieldBase<NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef ObjectTypeT                              ObjectType;
    
    typedef ChildPointerMFieldBase<NamespaceI  >     Inherited;
    typedef ChildPointerMField    <ObjectTypeT,
                                   NamespaceI  >     Self;
    
    typedef ChildFieldConfig      <ObjectTypeT,
                                   NamespaceI  >     FieldConfig;
    
    typedef typename FieldConfig::ValueType          ValueType;
    typedef typename FieldConfig::ArgumentType       ArgumentType;
    typedef typename FieldConfig::ValueType          value_type;
    
    typedef typename FieldConfig::ItType             iterator;
    typedef typename FieldConfig::ConstItType        const_iterator;
    typedef typename FieldConfig::ReverseItType      reverse_iterator;
    typedef typename FieldConfig::ConstReverseItType const_reverse_iterator;
    
    typedef typename FieldConfig::PtrType            pointer;
    typedef typename FieldConfig::ConstPtrType       const_pointer;
    typedef typename FieldConfig::MFieldRefType      reference;
    typedef typename FieldConfig::MFieldConstRefType const_reference;

    typedef typename Inherited::StoredType           StoredType;
    typedef typename Inherited::size_type            size_type;
    typedef typename Inherited::difference_type      difference_type;
    
    typedef typename Inherited::template rebindStore<ValueType>::type
                                                     ValueStoreType;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                    >  MFieldTraits;
    typedef FieldDescription<MFieldTraits,
                             FieldType::MULTI_FIELD,
                             FieldType::CHILD_POINTER_FIELD>  Description;
                                      
    // handles
    typedef          EditPointerMFieldHandle<Self>      EditHandle;
    typedef typename EditPointerMFieldHandle<Self>::Ptr EditHandlePtr;
    
    typedef          GetPointerMFieldHandle <Self>      GetHandle;
    typedef typename GetPointerMFieldHandle <Self>::Ptr GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
    typedef          EditPointerMFieldHandle<Self>      DynamicEditHandle;
    typedef typename EditPointerMFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
    typedef          GetPointerMFieldHandle <Self>      DynamicGetHandle;
    typedef typename GetPointerMFieldHandle <Self>::Ptr DynamicGetHandlePtr;
                             
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
        
    static FieldType::Cardinality const fieldCard  = FieldType  ::MULTI_FIELD;
    static FieldType::Class       const fieldClass = FieldConfig::fieldClass;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

             ChildPointerMField(void               );
             ChildPointerMField(Self   const &other);
    explicit ChildPointerMField(UInt32 const  size );
    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~ChildPointerMField(void); 
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name String/Stream IO (Input)                                     */
    /*! \{                                                                 */
    
//     void addValueFromCString(const Char8             *str  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Interface                                        */
    /*! \{                                                                 */
    
    iterator               begin  (void);
    iterator               end    (void);

    reverse_iterator       rbegin (void);
    reverse_iterator       rend   (void);

    const_iterator         begin  (void) const;
    const_iterator         end    (void) const;
    
    const_reverse_iterator rbegin (void) const;
    const_reverse_iterator rend   (void) const;
    
    reference              front  (void);
    const_reference        front  (void) const;

    reference              back   (void);
    const_reference        back   (void) const;
    
    void           assign   (size_type      newSize,
                             ValueType      value   = ValueType());
    template <class InputIteratorT>
    void           assign   (InputIteratorT first,
                             InputIteratorT last                 );
   
#if 0
    iterator       insert   (iterator       pos,
                             ValueType      value                );
#else
    void           insert   (iterator       pos,
                             ValueType      value                );
#endif
    template <class InputIteratorT>
    void           insert   (iterator       pos, 
                             InputIteratorT first,
                             InputIteratorT last                 );
 
#if 0
    iterator       erase    (iterator       pos                  );
    iterator       erase    (iterator       first,
                             iterator       last                 );
#else
    void           erase    (iterator       pos                  );
    void           erase    (iterator       first,
                             iterator       last                 );
#endif
    
    iterator       find     (ValueType      value                );
    const_iterator find     (ValueType      value                ) const;
    Int32          findIndex(ValueType      value                ) const;

    void           push_back(ValueType      value                );
   
    void           resize   (size_t         newSize,
                             ValueType      value   = ValueType());
    void           clear    (void                                );
                               
#ifdef OSG_1_COMPAT
    void           addValue (ValueType      value                );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Index Operator                                               */
    /*! \{                                                                 */

          reference operator [](UInt32 const index);
    const_reference operator [](UInt32 const index) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */

    void   setValues (Self const &source);
    Self & operator =(Self const &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Value Access                                                 */
    /*! \{                                                                 */
    
    ValueStoreType const &getValues(void) const;
    
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

#include "OSGChildAccessHandler.h"

#include "OSGChildPointerMField.inl"

#endif // _OSGCHILDPOINTERMFIELD_H_
