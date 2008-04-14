
#ifndef _OSGCHILDPOINTERSFIELDBASE_H_
#define _OSGCHILDPOINTERSFIELDBASE_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGPointerSFieldCommon.h"
#include "OSGChildAccessHandler.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChildPointerSFieldBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


template <typename AccessHandlerT,
          Int32    NamespaceI = 0>
class ChildPointerSFieldBase 
    : public PointerSFieldCommon<AccessHandlerT, NamespaceI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Public Types                                                 */
    /*! \{                                                                 */
       
    typedef       PointerSFieldCommon   <AccessHandlerT,
                                         NamespaceI    > Inherited;
    typedef       ChildPointerSFieldBase                 Self;
    
    typedef const FieldContainerPtr                      const_value;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors                                                 */
    /*! \{                                                                 */
    
    ChildPointerSFieldBase(const FieldContainerPtr  pParent,
                                 UInt16             usParentFieldPos);

    ChildPointerSFieldBase(      const_value        value,
                           const FieldContainerPtr  pParent,
                                 UInt16             usParentFieldPos);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */
    
    ~ChildPointerSFieldBase(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Child Linking Information                                    */
    /*! \{                                                                 */
    
    FieldContainerPtr getEnclosingObject(      void                   ) const;
    void              setEnclosingObject(const FieldContainerPtr pObj );
    
    UInt16            getChildFieldId   (      void                   ) const;
    void              setChildFieldId   (const UInt16 childFieldId    );
    
    UInt16            getParentFieldPos (      void                   ) const;
    void              setParentFieldPos (const UInt16 usParentFieldPos);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Members                                                      */
    /*! \{                                                                 */
  
    FieldContainerPtr _pEnclosingObj;
    UInt16            _childFieldId;
    UInt16            _usParentFieldPos;
  
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private: 

    template<typename RefCountPolicyT>
    friend class ChildAccessHandler;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChildPointerSFieldBase(const Self &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator = (const Self &source);
};

OSG_END_NAMESPACE

#include "OSGChildPointerSFieldBase.inl"

#endif // _OSGCHILDPOINTERSFIELDBASE_H_
