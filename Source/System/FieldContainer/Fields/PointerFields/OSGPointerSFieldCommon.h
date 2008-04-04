

#ifndef _OSGPOINTERSFIELDCOMMON_H_
#define _OSGPOINTERSFIELDCOMMON_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGPointerSFieldBase.h"
#include "OSGBinaryDataHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerSFieldCommon.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// forward declarations
template <Int32 NamespaceI>
class PointerFieldTraitsBase;


template <class AccessHandlerT,
          Int32 NamespaceI     = 0>
class PointerSFieldCommon : public PointerSFieldBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
    
    typedef          AccessHandlerT                      AccessHandler;

    typedef          PointerSFieldBase                   Inherited;
    typedef          PointerSFieldCommon                 Self;

    typedef          PointerFieldTraitsBase<NamespaceI>  PtrBaseTraitsType;
    
    typedef typename Inherited::StoredType               StoredType;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static Int32 const Namespace = NamespaceI;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             PointerSFieldCommon(void                          );
             PointerSFieldCommon(Self const             &source);
    explicit PointerSFieldCommon(FieldContainerPtrConst  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~PointerSFieldCommon(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Store Interface                                              */
    /*! \{                                                                 */
    
    // reading values
    FieldContainerPtr ptrStoreGet(void) const;
    
    // changing values
    void ptrStoreSet  (FieldContainerPtrConst pNewObj);
    void ptrStoreClear(void                          );
    
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

    void syncWith(Self &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

template <class LHSAccessHandlerT,
          Int32 LHSNamespaceI,
          class RHSAccessHandlerT,
          Int32 RHSNamespaceI     >
bool operator==(
    PointerSFieldCommon<LHSAccessHandlerT, LHSNamespaceI> const &lhs,
    PointerSFieldCommon<RHSAccessHandlerT, RHSNamespaceI> const &rhs ); 

OSG_END_NAMESPACE

#include "OSGPointerSFieldCommon.inl"

#endif // _OSGPOINTERSFIELDCOMMON_H_
