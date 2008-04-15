

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
    

    typedef          PointerSFieldBase                   Inherited;
    typedef          PointerSFieldCommon                 Self;

    typedef typename Inherited::const_value              const_value;

    typedef typename Inherited::StoredType               StoredType;

    typedef          AccessHandlerT                      AccessHandler;

    typedef          FieldTraitsFCPtrBase<
                         FieldContainerPtr, 
                         NamespaceI       >              PtrBaseTraitsType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constants                                                    */
    /*! \{                                                                 */
    
    static const Int32 Namespace = NamespaceI;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
             PointerSFieldCommon(      void               );
             PointerSFieldCommon(const Self        &source);
    explicit PointerSFieldCommon(      const_value  value );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~PointerSFieldCommon(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Store Interface                                              */
    /*! \{                                                                 */
    
    const_value ptrStoreGet  (void               ) const;
    
    void        ptrStoreSet  (const_value pNewObj);
    void        ptrStoreClear(void               );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Binary IO                                                    */
    /*! \{                                                                 */

    void copyFromBin(BinaryDataHandler &pMem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name MT Sync                                                      */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void syncWith(Self &source);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Self &source);
};

OSG_END_NAMESPACE

#include "OSGPointerSFieldCommon.inl"

#endif // _OSGPOINTERSFIELDCOMMON_H_
