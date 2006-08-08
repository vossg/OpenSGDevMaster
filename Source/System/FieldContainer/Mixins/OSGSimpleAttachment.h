/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGSIMPLEATTACHMENT_H_
#define _OSGSIMPLEATTACHMENT_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerAttachment.h"

OSG_BEGIN_NAMESPACE

//! Template to build simple attachment classes which store only one field.
//! \ingroup GrpSystemFieldContainer

template <class AttachmentDescT>
class SimpleAttachment : public FieldContainerAttachment
{
    /*=========================  PROTECTED  ===============================*/

  public:

    typedef FieldContainerAttachment Inherited;
    typedef FieldContainerAttachment ParentContainer;

  protected:

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          AttachmentDescT                   Desc;
    typedef typename Desc::FieldTypeT                  StoredFieldType;

    typedef          SimpleAttachment<AttachmentDescT> Self;

    typedef typename PointerBuilder  <Self>::ObjPtr         ObjPtr;
    typedef typename PointerBuilder  <Self>::ObjConstPtr    ObjConstPtr;
    typedef typename PointerBuilder  <Self>::ObjPtrConst    ObjPtrConst;
  
    typedef typename PointerBuilder  <Self>::ObjPtrArg      ObjPtrArg;
    typedef typename PointerBuilder  <Self>::ObjConstPtrArg ObjConstPtrArg;
    typedef typename PointerBuilder  <Self>::ObjPtrConstArg ObjPtrConstArg;
  
    enum 
    { 
        SimpleFieldId     = Inherited::NextFieldId, 
        NextFieldId       = SimpleFieldId + 1
    };

    static const BitVector SimpleFieldMask = Inherited::NextFieldMask;
    static const BitVector NextFieldMask   = SimpleFieldMask << 1;


#if 0
    struct EditSField
    {

        static void editField(
            ConstFieldMaskArg                                 whichField, 
            StoredFieldType &,
            Self *thisP) inline
        {
            thisP->editSField(whichField);
        }
    };
    
    struct EditMField
    {
        static void editField(ConstFieldMaskArg  whichField, 
                              StoredFieldType   &field, 
                              Self              *thisP     ) inline
        {
            thisP->editMField(whichField, field);
        }
    };

    struct EditError
    {
    };


    typedef typename osgIF<
              StoreFieldType::isSField == true,
              EditSField,
              EditError                       >::_IRet EditSFieldResult;

    typedef typename osgIF<
              StoreFieldType::isSField == true,
              EditMField,
              EditSFieldResult                >::_IRet EditFieldResult;

    typedef typename StoredFieldType::StoredType ValueType;

    template<class ValueT>
    void editField(SField<ValueT, StoredFieldTypeNamespace> &field);

    template<>
    void editField< SField<ValueType, StoredFieldType::Namespace> >(
        SField<ValueType, StoredFieldTypeNamespace> &field)
        {
        }
#endif

   

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_TMPL_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          StoredFieldType *editFieldPtr(void);
    const StoredFieldType *getFieldPtr (void) const;

          StoredFieldType &editField   (void);
    const StoredFieldType &getField    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);

    virtual void   copyToBin  (BinaryDataHandler &pMem, 
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem, 
                               ConstFieldMaskArg  whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    StoredFieldType _field;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleAttachment(void);
    SimpleAttachment(const SimpleAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjPtr createAspectCopy(void) const;
#endif


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

#ifdef OSG_MT_FIELDCONTAINERPTR
    virtual void execSyncV(      FieldContainer     &oFrom,
                                 ConstFieldMaskArg   whichField,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo,
                                 UInt32              uiCopyOffset);

            void execSync (      SimpleAttachment   *pFrom,
                                 ConstFieldMaskArg   whichField,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo,
                                 UInt32              uiCopyOffset);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    OSG_SYSTEM_DLLMAPPING 
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

    OSG_SYSTEM_DLLMAPPING 
            void execSync (      SimpleAttachment  *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

#if 0
    virtual void execBeginEditV(ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);

            void execBeginEdit (ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    
    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    /*! \brief prohibit default functions (move to 'public' if needed) */
    SimpleAttachment &operator =(const SimpleAttachment &source);
};

OSG_END_NAMESPACE

#include "OSGSimpleAttachment.inl"

#endif /* _OSGSIMPLEATTACHMENT_H_ */
