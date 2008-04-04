
#ifndef _OSGPOINTERSFIELDBASE_H_
#define _OSGPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGField.h"
#include "OSGContainerForwards.h"
#include "OSGEditPointerSFieldBaseHandle.h"
#include "OSGGetPointerSFieldBaseHandle.h"


#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerSFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

class PointerSFieldBase : public Field
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef Field             Inherited;
    typedef PointerSFieldBase Self;
    
    // storage
    typedef FieldContainerPtr StoredType;
    
    typedef StoredType       &StoredTypeRef;
    typedef StoredType const &StoredTypeConstRef;
    
    // handles
    typedef EditSFieldHandle<PointerSFieldBase>      EditHandle;
    typedef EditSFieldHandle<PointerSFieldBase>::Ptr EditHandlePtr;
    
    typedef GetSFieldHandle <PointerSFieldBase>      GetHandle;
    typedef GetSFieldHandle <PointerSFieldBase>::Ptr GetHandlePtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             PointerSFieldBase(void                          );
             PointerSFieldBase(Self const             &source);
    explicit PointerSFieldBase(FieldContainerPtrConst  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~PointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw Store Access                                             */
    /*! \{                                                                 */
    
    StoredTypeRef      editRawStore(void);
    StoredTypeConstRef getRawStore (void) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
    
    StoredType _fieldValue;
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGPointerSFieldBase.inl"

#endif // _OSGPOINTERSFIELDBASE_H_
