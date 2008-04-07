
#ifndef _OSGPARENTPOINTERSFIELDBASE_H_
#define _OSGPARENTPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerSFieldCommon.h"
#include "OSGNoRefCountAccessHandlerDecl.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerSFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class ParentPointerSFieldBase 
    : public PointerSFieldCommon<NoRefCountAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef PointerSFieldCommon<NoRefCountAccessHandler,
                                NamespaceI        > Inherited;
    typedef ParentPointerSFieldBase                 Self;
          
    typedef UInt16                                  IdStoredType;
    typedef UInt16                                 &IdStoredTypeRef;
    typedef UInt16 const                           &IdStoredTypeConstRef;
    
    typedef FieldTraits<IdStoredType,
                        NamespaceI   >              IdBaseTraitsType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ParentPointerSFieldBase(void                        );
    ParentPointerSFieldBase(Self   const      &source   );
    ParentPointerSFieldBase(FieldContainerPtr  ptrValue,
                            IdStoredType       idValue  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name IdStore Interface                                            */
    /*! \{                                                                 */
    
    // reading values
    UInt16 const idStoreGet(void) const;
    
    // changing values
    void idStoreSet  (UInt16 const newId);
    void idStoreClear(void              );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw IdStore Access                                           */
    /*! \{                                                                 */
    
    IdStoredTypeRef      editRawIdStore(void);
    IdStoredTypeConstRef getRawIdStore (void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    UInt32 getBinSize (void                   ) const;
    void   copyToBin  (BinaryDataHandler &pMem) const;
    void   copyFromBin(BinaryDataHandler &pMem);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

    void  syncWith(Self &source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
  
    IdStoredType _childIdValue;
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private: 
};

OSG_END_NAMESPACE

#include "OSGParentPointerSFieldBase.inl"

#endif // _OSGPARENTPOINTERSFIELDBASE_H_
