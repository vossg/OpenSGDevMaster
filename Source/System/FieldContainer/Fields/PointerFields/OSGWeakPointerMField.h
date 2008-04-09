

#ifndef _OSGWEAKPOINTERMFIELD_H_
#define _OSGWEAKPOINTERMFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWeakPointerMFieldBase.h"
#include "OSGPointerFieldConfigs.h"
//#include "OSGEditPointerMFieldHandle.h"
//#include "OSGGetPointerMFieldHandle.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerMField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <class ObjectTypeT, Int32 NamespaceI>
class WeakPointerMField;

/*---------------------------------------------------------------------------*/
/* WeakMFieldIterator<ObjectTypeT>                                           */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class WeakMFieldIterator 
    : public WeakPointerMField<ObjectTypeT, 0>::PtrStoreItType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                        ObjectType;
    
    typedef          WeakMFieldIterator                 Self;
    typedef typename WeakPointerMField<ObjectTypeT, 0>::PtrStoreItType
                                                        Inherited;
           
    typedef          WeakPointerMField<ObjectTypeT, 0>  MFieldType;
    typedef          WeakFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename MFieldType::AccessHandler          AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType             StoredType;
    typedef typename MFieldType::PtrStoreType           PtrStoreType;
    typedef typename MFieldType::PtrStoreItType         PtrStoreItType;
    
    // std library typedefs
    typedef typename Inherited::iterator_category       iterator_category;
    typedef typename Inherited::difference_type         difference_type;
    
    typedef typename FieldConfig::ValueType             value_type;
    typedef typename FieldConfig::PtrType               pointer;
    typedef typename FieldConfig::MFieldRefType         reference;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    WeakMFieldIterator(void                            );
    WeakMFieldIterator(Self           const &source    );
    
    WeakMFieldIterator(PtrStoreItType const &storeIter,
                       MFieldType           *pField    );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
                               
    ~WeakMFieldIterator(void);
    
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
typename WeakMFieldIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldIterator<ObjectTypeT> const &lhs,
              WeakMFieldIterator<ObjectTypeT> const &rhs );

template <class ObjectTypeT>
WeakMFieldIterator<ObjectTypeT>
    operator+(
        typename WeakMFieldIterator<ObjectTypeT>::differece_type const offset,
        WeakMFieldIterator<ObjectTypeT>                          const &rhs   );

/*---------------------------------------------------------------------------*/
/* WeakMFieldConstIterator<ObjectTypeT>                                      */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT>
class WeakMFieldConstIterator
    : public WeakPointerMField<ObjectTypeT, 0>::PtrStoreConstItType
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          ObjectTypeT                        ObjectType;
    
    typedef          WeakMFieldConstIterator            Self;
    typedef typename WeakPointerMField<ObjectTypeT, 0>::PtrStoreConstItType
                                                        Inherited;
           
    typedef          WeakPointerMField<ObjectTypeT, 0>  MFieldType;
    typedef          WeakFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename MFieldType::AccessHandler          AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType             StoredType;
    typedef typename MFieldType::PtrStoreType           PtrStoreType;
    typedef typename MFieldType::PtrStoreConstItType    PtrStoreConstItType;
    
    // std library types
    typedef typename Inherited::iterator_category       iterator_category;
    typedef typename Inherited::difference_type         difference_type;
    
    typedef typename FieldConfig::ConstValueType        value_type;
    typedef typename FieldConfig::ConstPtrType          pointer;
    typedef typename FieldConfig::MFieldConstRefType    reference;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    WeakMFieldConstIterator(void                                            );
    WeakMFieldConstIterator(Self                            const &source   );
    WeakMFieldConstIterator(WeakMFieldIterator<ObjectTypeT> const &fieldIter);
    WeakMFieldConstIterator(PtrStoreConstItType             const &storeIter);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
                               
    ~WeakMFieldConstIterator(void);
    
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
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldConstIterator<ObjectTypeT> const &lhs,
              WeakMFieldConstIterator<ObjectTypeT> const &rhs );
              
template <class ObjectTypeT>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldIterator     <ObjectTypeT> const &lhs,
              WeakMFieldConstIterator<ObjectTypeT> const &rhs );

template <class ObjectTypeT>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldConstIterator<ObjectTypeT> const &lhs,
              WeakMFieldIterator     <ObjectTypeT> const &rhs );
              
template <class ObjectTypeT>
WeakMFieldConstIterator<ObjectTypeT>
    operator+(
        typename WeakMFieldConstIterator<ObjectTypeT>::difference_type const  offset,
        WeakMFieldConstIterator<ObjectTypeT>                           const &rhs    );

/*-------------------------------------------------------------------------*/
/* WeakMFieldReferenceProxy<ObjectTypeT>                                   */
/*-------------------------------------------------------------------------*/

template <class ObjectTypeT>
class WeakMFieldReferenceProxy
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

   
    typedef          ObjectTypeT                        ObjectType;
    
    typedef          WeakMFieldReferenceProxy           Self;
            
    typedef          WeakPointerMField<ObjectTypeT, 0>  MFieldType;
    typedef          WeakFieldConfig  <ObjectTypeT, 0>  FieldConfig;
    typedef typename MFieldType::AccessHandler          AccessHandler;
    
    // store types
    typedef typename MFieldType::StoredType             StoredType;
    typedef typename MFieldType::PtrStoreType           PtrStoreType;    
    typedef typename MFieldType::PtrStoreItType         PtrStoreItType;
    typedef typename MFieldType::PtrStoreConstItType    PtrStoreConstItType;
    
    // std library types
    typedef typename FieldConfig::ValueType             value_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    WeakMFieldReferenceProxy(PtrStoreItType const &storeIter,
                             MFieldType           *pField    );
    WeakMFieldReferenceProxy(Self const           &source    );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~WeakMFieldReferenceProxy(void);
    
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
/* WeakPointerMField<FieldConfigT>                                           */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class WeakPointerMField : public WeakPointerMFieldBase<NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

  protected:

    typedef ObjectTypeT                               ObjectType;
    
    typedef WeakPointerMFieldBase<NamespaceI  >       Inherited;
    typedef WeakPointerMField    <ObjectTypeT,
                                  NamespaceI  >       Self;
    
    typedef WeakFieldConfig      <ObjectTypeT,
                                  NamespaceI  >       FieldConfig;
    
    typedef typename FieldConfig::ValueType           ValueType;
    typedef typename FieldConfig::ArgumentType        ArgumentType;
    typedef typename FieldConfig::ValueType           value_type;
    
    typedef typename FieldConfig::ItType              iterator;
    typedef typename FieldConfig::ConstItType         const_iterator;
    typedef typename FieldConfig::ReverseItType       reverse_iterator;
    typedef typename FieldConfig::ConstReverseItType  const_reverse_iterator;
    
    typedef typename FieldConfig::PtrType             pointer;
    typedef typename FieldConfig::ConstPtrType        const_pointer;
    typedef typename FieldConfig::MFieldRefType       reference;
    typedef typename FieldConfig::MFieldConstRefType  const_reference;

    typedef typename Inherited::size_type             size_type;
    typedef typename Inherited::difference_type       difference_type;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                   >  MFieldTraits;
    typedef FieldDescription<MFieldTraits,
                             MultiField,
                             WeakRefCountPolicy,
                             PtrField>  Description;
    
    // handles
//    typedef          EditPointerMFieldHandle<Self>      EditHandle;
//    typedef typename EditPointerMFieldHandle<Self>::Ptr EditHandlePtr;
    
//    typedef          GetPointerMFieldHandle <Self>      GetHandle;
//    typedef typename GetPointerMFieldHandle <Self>::Ptr GetHandlePtr;
    
    // handles for dynamic fields -- XXX TODO
//    typedef          EditPointerMFieldHandle<Self>      DynamicEditHandle;
//    typedef typename EditPointerMFieldHandle<Self>::Ptr DynamicEditHandlePtr;
    
//    typedef          GetPointerMFieldHandle <Self>      DynamicGetHandle;
//    typedef typename GetPointerMFieldHandle <Self>::Ptr DynamicGetHandlePtr;
    
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

             WeakPointerMField(void               );
             WeakPointerMField(Self   const &other);
    explicit WeakPointerMField(UInt32 const  size );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~WeakPointerMField(void); 
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name String/Stream IO (Input)                                     */
    /*! \{                                                                 */
    
//     void addValueFromCString(const Char8             *str  );
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Interface                                        */
    /*! \{                                                                 */
    
    iterator               begin (void);
    iterator               end   (void);

    reverse_iterator       rbegin(void);
    reverse_iterator       rend  (void);

    const_iterator         begin (void) const;
    const_iterator         end   (void) const;
    
    const_reverse_iterator rbegin(void) const;
    const_reverse_iterator rend  (void) const;

    reference              front (void);
    const_reference        front (void) const;

    reference              back  (void);
    const_reference        back  (void) const;
    
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

#include "OSGWeakPointerMField.inl"

#endif // _OSGWEAKPOINTERMFIELD_H_
