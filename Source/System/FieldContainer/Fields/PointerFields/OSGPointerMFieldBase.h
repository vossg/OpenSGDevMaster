
#ifndef _OSGPOINTERMFIELDBASE_H_
#define _OSGPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGField.h"
#include "OSGContainerForwards.h"
#include "OSGEditPointerMFieldBaseHandle.h"
#include "OSGGetPointerMFieldBaseHandle.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif


OSG_BEGIN_NAMESPACE

class PointerMFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef Field                                   Inherited;
    typedef PointerMFieldBase                       Self;
    
    // storage
    typedef FieldContainerPtr                       StoredType;
    typedef std::allocator<StoredType>              AllocatorType;
    
    typedef MFieldVector<StoredType, AllocatorType> PtrStoreType;
    typedef PtrStoreType::iterator                  PtrStoreItType;
    typedef PtrStoreType::const_iterator            PtrStoreConstItType;
    
    typedef PtrStoreType::const_iterator            const_iterator;
    typedef PtrStoreType::const_reverse_iterator    const_reverse_iterator;
    typedef PtrStoreType::const_reference           const_reference;
    typedef PtrStoreType::size_type                 size_type;
    typedef PtrStoreType::difference_type           difference_type;
    
    template <class TargetStoredTypeT>
    struct rebindStore
    {
        typedef typename 
            AllocatorType::template rebind<TargetStoredTypeT>::other
                TargetAllocatorType;
    
        typedef MFieldVector<TargetStoredTypeT,
                             TargetAllocatorType> type;
    };

    // handles
    typedef EditMFieldHandle<PointerMFieldBase>      EditHandle;
    typedef EditMFieldHandle<PointerMFieldBase>::Ptr EditHandlePtr;
    
    typedef GetMFieldHandle <PointerMFieldBase>      GetHandle;
    typedef GetMFieldHandle <PointerMFieldBase>::Ptr GetHandlePtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             PointerMFieldBase(void                );
             PointerMFieldBase(Self   const &source);
    explicit PointerMFieldBase(UInt32 const  size  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~PointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std Library Const Interface                                  */
    /*! \{                                                                 */
    
    const_iterator         begin (void) const;
    const_iterator         end   (void) const;
    
    const_reverse_iterator rbegin(void) const;
    const_reverse_iterator rend  (void) const;
    
    bool      empty   (void) const;
    size_type size    (void) const;
    size_type max_size(void) const;
    size_type capacity(void) const;
    
    const_reference operator[](UInt32 const index);
    const_reference at        (UInt32 const index);
    
    const_reference front     (void              ) const;
    const_reference back      (void              ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw Store Access                                             */
    /*! \{                                                                 */
    
    PtrStoreType       &editRawStore(void);
    PtrStoreType const &getRawStore (void) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    PtrStoreType _ptrStore;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Cast Store Access                                            */
    /*! \{                                                                 */
    
    template <class TargetStoredTypeT>
    typename rebindStore<TargetStoredTypeT>::type       &editStore(void);
    
    template <class TargetStoredTypeT>
    typename rebindStore<TargetStoredTypeT>::type const &getStore (void) const;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGPointerMFieldBase.inl"

#endif // _OSGPOINTERMFIELDBASE_H_
