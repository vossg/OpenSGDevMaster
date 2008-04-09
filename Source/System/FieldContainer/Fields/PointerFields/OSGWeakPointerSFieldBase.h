
#ifndef _OSGWEAKPOINTERSFIELDBASE_H_
#define _OSGWEAKPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerSFieldCommon.h"
#include "OSGPointerAccessHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerSFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class WeakPointerSFieldBase 
    : public PointerSFieldCommon<WeakAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
  protected:

    typedef PointerSFieldCommon<WeakAccessHandler,
                                NamespaceI        > Inherited;
    typedef WeakPointerSFieldBase                   Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             WeakPointerSFieldBase(void                          );
             WeakPointerSFieldBase(Self const             &source);
    explicit WeakPointerSFieldBase(FieldContainerPtrConst  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~WeakPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*==========================  PRIVATE  ================================*/
  private: 
};

OSG_END_NAMESPACE

#include "OSGWeakPointerSFieldBase.inl"

#endif // _OSGWEAKPOINTERSFIELDBASE_H_
