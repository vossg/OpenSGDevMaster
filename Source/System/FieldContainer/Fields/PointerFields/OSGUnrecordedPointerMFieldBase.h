
#ifndef _OSGUNRECORDEDPOINTERMFIELDBASE_H_
#define _OSGUNRECORDEDPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerMFieldCommon.h"
#include "OSGPointerAccessHandler.h"

#if 0
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class UnrecordedPointerMFieldBase 
    : public PointerMFieldCommon<UnrecordedAccessHandler, 0>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

  protected:
       
    typedef PointerMFieldCommon<UnrecordedAccessHandler,
                                NamespaceI              >  Inherited;
    typedef UnrecordedPointerMFieldBase                    Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    UnrecordedPointerMFieldBase(void                );
    UnrecordedPointerMFieldBase(UInt32 const  size  );
    UnrecordedPointerMFieldBase(Self   const &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~UnrecordedPointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGUnrecordedPointerMFieldBase.inl"

#endif

#endif // _OSGUNRECORDEDPOINTERMFIELDBASE_H_
