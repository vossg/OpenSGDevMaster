
#ifndef _OSGPARENTPOINTERMFIELDBASE_H_
#define _OSGPARENTPOINTERMFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerMFieldCommon.h"
#include "OSGNoRefCountAccessHandlerDecl.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerMFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <Int32 NamespaceI = 0>
class ParentPointerMFieldBase 
    : public PointerMFieldCommon<NoRefCountAccessHandler, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          PointerMFieldCommon<NoRefCountAccessHandler,
                                         NamespaceI        > Inherited;
    typedef          ParentPointerMFieldBase                 Self;
          
    typedef          UInt16                                  IdStoredType;
    typedef          MFieldVector<IdStoredType>              IdStoreType;
    typedef typename IdStoreType::iterator                   IdStoreItType;
    typedef typename IdStoreType::const_iterator             IdStoreConstItType;
    
    typedef          FieldTraits<IdStoredType,
                                 NamespaceI   >              IdBaseTraitsType;
    
    typedef typename Inherited::size_type                    size_type;
    typedef typename Inherited::difference_type              difference_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             ParentPointerMFieldBase(void                );
             ParentPointerMFieldBase(Self   const &source);
    explicit ParentPointerMFieldBase(UInt32 const  size  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ParentPointerMFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name IdStore Interface                                            */
    /*! \{                                                                 */
    
    // reading values
    UInt16 const idStoreGet(UInt32 const       index) const;
    UInt16 const idStoreGet(IdStoreItType      pos  ) const;
    UInt16 const idStoreGet(IdStoreConstItType pos  ) const;
  
    // adding values
    void  idStoreAppend (UInt16 const   newId     );
    void  idStoreInsert (UInt32 const   index,
                         UInt16 const   newId     );
    void  idStoreInsert (IdStoreItType  pos,
                         UInt16 const   newId     );
    template <class InputIteratorT>
    void  idStoreInsert (IdStoreItType  pos,
                         InputIteratorT first,
                         InputIteratorT last      );
    // changing values
    void  idStoreReplace(UInt32 const  index,
                         UInt16 const  newId      );
    void  idStoreReplace(IdStoreItType pos,
                         UInt16 const  newId      );
    
    // removing values
    void  idStoreErase  (UInt32 const  index      );
    void  idStoreErase  (IdStoreItType pos        );
    void  idStoreErase  (UInt32 const  beginIndex,
                         UInt32 const  endIndex   );
    void  idStoreErase  (IdStoreItType begin,
                         IdStoreItType end        );
    void  idStoreClear  (void                     );
    
    // finding values
    Int32              idStoreFindIndex(UInt16 const fieldId) const;
    IdStoreItType      idStoreFind     (UInt16 const fieldId);
    IdStoreConstItType idStoreFind     (UInt16 const fieldId) const;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Raw IdStore Access                                           */
    /*! \{                                                                 */
    
    IdStoreType       &editRawIdStore(void);
    IdStoreType const &getRawIdStore (void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Std library interface                                        */
    /*! \{                                                                 */
    
    void reserve(size_type size);
    
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

    void  syncWith      (Self               &source, 
                         ConstFieldMaskArg   syncMode,
                         UInt32              uiSyncInfo,
                         AspectOffsetStore  &oOffsets    );
    void  beginEdit     (UInt32              uiAspect,
                         AspectOffsetStore  &oOffsets    );
    Self *resolveShare  (UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );
    void  terminateShare(UInt32              uiAspect, 
                         AspectOffsetStore  &oOffsets    );
    bool  isShared      (void                            );
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
  
    IdStoreType _childIdStore;
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private: 
};

OSG_END_NAMESPACE

#include "OSGParentPointerMFieldBase.inl"

#endif // _OSGPARENTPOINTERMFIELDBASE_H_
