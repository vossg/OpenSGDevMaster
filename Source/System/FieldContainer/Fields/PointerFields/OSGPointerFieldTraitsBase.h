
#ifndef _OSGPOINTERFIELDTRAITSBASE_H_
#define _OSGPOINTERFIELDTRAITSBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerFieldTraitsBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

template <Int32 NamespaceI = 0>
class PointerFieldTraitsBase : public FieldTraitsBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Public Type Information/Constants                            */
    /*! \{                                                                 */
    
    typedef FieldDescriptionBase FieldDescParent;
    
    static const bool isPointerField = true;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */
    
    static UInt32 getBinSize(FieldContainerPtrConst  pObject      );
    static UInt32 getBinSize(FieldContainerPtrConst *pObjectStore,
                             UInt32 const            uiNumObjects );
    
    static void copyToBin   (BinaryDataHandler      &pMem, 
                             FieldContainerPtrConst  pObject      ); 
    static void copyToBin   (BinaryDataHandler      &pMem, 
                             FieldContainerPtrConst *pObjectStore,
                             UInt32 const            uiNumObjects );
    
    static void copyFromBin(BinaryDataHandler       &pMem, 
                            FieldContainerPtr       &pObject      );
    static void copyFromBin(BinaryDataHandler       &pMem, 
                            FieldContainerPtr       *pObjectStore,
                            UInt32 const             uiNumObjects );
                            
    /*! \}                                                                 */
    /*========================  PROTECTED  ================================*/
  protected:
};

OSG_END_NAMESPACE

#include "OSGPointerFieldTraitsBase.inl"

#endif // _OSGPOINTERFIELDTRAITSBASE_H_
