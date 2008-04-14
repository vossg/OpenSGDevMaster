

#ifndef _OSGWEAKPOINTERMFIELD_H_
#define _OSGWEAKPOINTERMFIELD_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGPointerMField.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerMField.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/
/* WeakPointerMField<FieldConfigT>                                           */
/*---------------------------------------------------------------------------*/

template <class ObjectTypeT,
          Int32 NamespaceI  = 0>
class WeakPointerMField : public PointerMField<ObjectTypeT,
                                               WeakRefCountPolicy,
                                               NamespaceI        >
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

  protected:

    typedef ObjectTypeT                               ObjectType;

    typedef PointerMField<ObjectTypeT,
              WeakRefCountPolicy,
              NamespaceI        > Inherited;

    typedef WeakPointerMField    <ObjectTypeT,
                                  NamespaceI  >       Self;
    
    
    typedef ObjectTypeT * ValueType;
    typedef ObjectTypeT * const ArgumentType;
    typedef ObjectTypeT * value_type;


    
    typedef ValueType *pointer;
    typedef ArgumentType *const_pointer;

    typedef ValueType const                             &const_reference; 

    typedef typename Inherited::size_type             size_type;
    typedef typename Inherited::difference_type       difference_type;
    
    typedef FieldTraits     <ValueType,
                             NamespaceI                   >  MFieldTraits;
    typedef FieldDescription<MFieldTraits,
                             FieldType::MultiField,
                             WeakRefCountPolicy,
                             FieldType::PtrField>  Description;
    
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
        
    static FieldType::Cardinality const fieldCard = FieldType::MultiField;
    static FieldType::Class       const Class     = FieldType::PtrField;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Class Type                                                   */
    /*! \{                                                                 */

    static FieldType const &getClassType(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */

             WeakPointerMField(      void          );
             WeakPointerMField(const Self    &other);
    explicit WeakPointerMField(const UInt32  size  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    ~WeakPointerMField(void); 
       
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name String/Stream IO (Input)                                     */
    /*! \{                                                                 */
    
   /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Assignment                                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    static FieldType _fieldType;

    Self &operator =(const Self &source);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include "OSGWeakPointerMField.inl"

#endif // _OSGWEAKPOINTERMFIELD_H_
