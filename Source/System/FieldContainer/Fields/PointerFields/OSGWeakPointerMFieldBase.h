
#ifndef _OSGWEAKPOINTERMFIELDBASE_H_
#define _OSGWEAKPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerMFieldCommon.h"
#include "OSGWeakAccessHandlerDecl.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGWeakPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class WeakPointerMFieldBase 
    : public PointerMFieldCommon<WeakAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef PointerMFieldCommon<WeakAccessHandler,
                                NamespaceI        >  Inherited;
    typedef WeakPointerMFieldBase                    Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             WeakPointerMFieldBase(void                );
             WeakPointerMFieldBase(Self   const &source);
    explicit WeakPointerMFieldBase(UInt32 const  size  );
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~WeakPointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGWeakPointerMFieldBase.inl"

#endif // _OSGWEAKPOINTERMFIELDBASE_H_
