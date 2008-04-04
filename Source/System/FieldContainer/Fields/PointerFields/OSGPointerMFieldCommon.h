

#ifndef _OSGPOINTERMFIELDCOMMON_H_
#define _OSGPOINTERMFIELDCOMMON_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointerMFieldBase.h"
#include "OSGBinaryDataHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerMFieldCommon.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <Int32 NamespaceI>
class PointerFieldTraitsBase;


template <class AccessHandlerT,
          Int32 NamespaceI     = 0>
class PointerMFieldCommon : public PointerMFieldBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */

    typedef          AccessHandlerT                      AccessHandler;

    typedef          PointerMFieldBase                   Inherited;
    typedef          PointerMFieldCommon                 Self;

    typedef          PointerFieldTraitsBase<NamespaceI>  PtrBaseTraitsType;

    typedef typename Inherited::StoredType               StoredType;
    typedef typename Inherited::PtrStoreType             PtrStoreType;
    typedef typename Inherited::PtrStoreItType           PtrStoreItType;
    typedef typename Inherited::PtrStoreConstItType      PtrStoreConstItType;

    typedef typename Inherited::size_type                size_type;
    typedef typename Inherited::difference_type          difference_type;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static Int32 const Namespace = NamespaceI;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             PointerMFieldCommon(void                );
             PointerMFieldCommon(Self   const &source);
    explicit PointerMFieldCommon(UInt32 const  size  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~PointerMFieldCommon(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Store Interface                                              */
    /*! \{                                                                 */

    // reading values
    FieldContainerPtr ptrStoreGet(UInt32 const        index) const;
    FieldContainerPtr ptrStoreGet(PtrStoreItType      pos  ) const;
    FieldContainerPtr ptrStoreGet(PtrStoreConstItType pos  ) const;

    // adding values
    void ptrStoreAppend (FieldContainerPtrConst  pNewObj    );
    template <class InputIteratorT>
    void ptrStoreAssign (InputIteratorT          first,
                         InputIteratorT          last       );
    void ptrStoreInsert (UInt32 const            index,
                         FieldContainerPtrConst  pNewObj    );
    void ptrStoreInsert (PtrStoreItType          pos,
                         FieldContainerPtrConst  pNewObj    );
    template <class InputIteratorT>
    void ptrStoreInsert (PtrStoreItType          pos,
                         InputIteratorT          first,
                         InputIteratorT          last       );

    // changing values
    void ptrStoreReplace(UInt32 const            index,
                         FieldContainerPtrConst  pNewObj    );
    void ptrStoreReplace(PtrStoreItType          pos,
                         FieldContainerPtrConst  pNewObj    );

    // removing values
    void ptrStoreErase  (UInt32 const            index      );
    void ptrStoreErase  (PtrStoreItType          pos        );
    void ptrStoreErase  (UInt32 const            beginIndex,
                         UInt32 const            endIndex   );
    void ptrStoreErase  (PtrStoreItType          begin,
                         PtrStoreItType          end        );
    void ptrStoreClear  (void                               );

    // resizing
    void ptrStoreResize (UInt32 const            newSize,
                         FieldContainerPtrConst  pNewObj    );

    // finding values
    Int32               ptrStoreFindIndex(FieldContainerPtrConst pObj) const;
    PtrStoreItType      ptrStoreFind     (FieldContainerPtrConst pObj);
    PtrStoreConstItType ptrStoreFind     (FieldContainerPtrConst pObj) const;
    
    UInt32              ptrStoreSize     (void                       ) const;

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
    /*---------------------------------------------------------------------*/
};

template <class LHSAccessHandlerT,
          Int32 LHSNamespaceI,
          class RHSAccessHandlerT,
          Int32 RHSNamespaceI     >
bool operator==(
    PointerMFieldCommon<LHSAccessHandlerT, LHSNamespaceI> const &lhs,
    PointerMFieldCommon<RHSAccessHandlerT, RHSNamespaceI> const &rhs ); 

OSG_END_NAMESPACE

#include "OSGPointerMFieldCommon.inl"

#endif // _OSGPOINTERMFIELDCOMMON_H_
