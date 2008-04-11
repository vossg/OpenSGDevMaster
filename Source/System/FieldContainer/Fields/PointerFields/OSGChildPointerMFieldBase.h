
#ifndef _OSGCHILDPOINTERMFIELDBASE_H_
#define _OSGCHILDPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerMFieldCommon.h"
#include "OSGChildAccessHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class ChildPointerMFieldBase 
    : public PointerMFieldCommon<UnrecChildAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef PointerMFieldCommon<UnrecChildAccessHandler,
                                NamespaceI             > Inherited;
    typedef ChildPointerMFieldBase                   Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             ChildPointerMFieldBase(void                );
             ChildPointerMFieldBase(Self   const &source);
    explicit ChildPointerMFieldBase(UInt32 const  size  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child Linking Information                                    */
    /*! \{                                                                 */
    
    FieldContainerPtr getEnclosingObject(void                       ) const;
    void              setEnclosingObject(FieldContainerPtrConst pObj);
    
    UInt16 getChildFieldId (void                      ) const;
    void   setChildFieldId (UInt16 const childFieldId );
    
    UInt16 getParentFieldId(void                      ) const;
    void   setParentFieldId(UInt16 const parentFieldId);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
  
    FieldContainerPtr _pEnclosingObj;
    UInt16            _childFieldId;
    UInt16            _parentFieldId;
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private: 
};

OSG_END_NAMESPACE

#include "OSGChildPointerMFieldBase.inl"

#endif // _OSGCHILDPOINTERMFIELDBASE_H_
