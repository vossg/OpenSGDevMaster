
#ifndef _OSGCHILDPOINTERSFIELDBASE_H_
#define _OSGCHILDPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerSFieldCommon.h"
#include "OSGChildAccessHandlerDecl.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerSFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class ChildPointerSFieldBase 
    : public PointerSFieldCommon<ChildAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef PointerSFieldCommon<ChildAccessHandler,
                                NamespaceI         > Inherited;
    typedef ChildPointerSFieldBase                   Self;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             ChildPointerSFieldBase(void                          );
             ChildPointerSFieldBase(Self const             &source);
    explicit ChildPointerSFieldBase(FieldContainerPtrConst  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerSFieldBase(void);
    
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

#include "OSGChildPointerSFieldBase.inl"

#endif // _OSGCHILDPOINTERSFIELDBASE_H_
