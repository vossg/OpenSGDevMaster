
#ifndef _OSGUNRECORDEDPOINTERSFIELDBASE_H_
#define _OSGUNRECORDEDPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerSFieldCommon.h"
#include "OSGUnrecordedAccessHandlerDecl.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGUnrecordedPointerSFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class UnrecordedPointerSFieldBase 
    : public PointerSFieldCommon<UnrecordedAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef PointerSFieldCommon<UnrecordedAccessHandler,
                                NamespaceI              > Inherited;
    typedef UnrecordedPointerSFieldBase                   Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             UnrecordedPointerSFieldBase(void                          );
             UnrecordedPointerSFieldBase(Self const             &source);
    explicit UnrecordedPointerSFieldBase(FieldContainerPtrConst  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~UnrecordedPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*==========================  PRIVATE  ================================*/
  private: 
};

OSG_END_NAMESPACE

#include "OSGUnrecordedPointerSFieldBase.inl"

#endif // _OSGUNRECORDEDPOINTERSFIELDBASE_H_
