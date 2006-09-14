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

#ifndef _OSGDYNAMICATTACHMENTMIXIN_H_
#define _OSGDYNAMICATTACHMENTMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGDynamicAttachmentMixin.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include "OSGSystemDef.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Template to build simple attachment classes which store an arbitrary
//! number of fields.
//! \ingroup GrpSystemFieldContainer

template <class AttachmentDescT>
class DynFieldAttachment : public AttachmentDescT::Parent
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename AttachmentDescT::Parent              Inherited;
    typedef typename AttachmentDescT::Parent              ParentContainer;

    typedef          DynFieldAttachment<AttachmentDescT>  Self;

    typedef typename PointerBuilder<Self>::ObjPtr         ObjPtr;
    typedef typename PointerBuilder<Self>::ObjPtrConst    ObjPtrConst;
    typedef typename PointerBuilder<Self>::ObjConstPtr    ObjConstPtr;

    typedef typename PointerBuilder<Self>::ObjPtrArg      ObjPtrArg;
    typedef typename PointerBuilder<Self>::ObjConstPtrArg ObjConstPtrArg;
    typedef typename PointerBuilder<Self>::ObjPtrConstArg ObjPtrConstArg;

    typedef typename AttachmentDescT::ParentPtr           ParentPtrType;

    typedef typename Inherited::TypeObject                TypeObject;
    typedef typename TypeObject::InitPhase                InitPhase;

    typedef          PointerBuilder<Self>                 PtrType;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_TMPL_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

    UInt32 addField(const FieldDescriptionBase &fieldDesc);
    void   subField(      UInt32                fieldId  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

    const Field *getDynamicField      (       UInt32  index ) const;
          Field *editDynamicField     (       UInt32  index );

    const Field *getDynamicFieldByName (const Char8  *szName) const;
          Field *editDynamicFieldByName(const Char8  *szName);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Clone                                   */
    /*! \{                                                                 */

    FieldContainerPtr emptyCopy(void);
    FieldContainerPtr clone    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    TypeObject           _localType;

    std::vector<Field *> _dynFieldsV;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DynFieldAttachment(      void                      );
    DynFieldAttachment(const DynFieldAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynFieldAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void execSyncV(      FieldContainer     &oFrom,
                                 ConstFieldMaskArg   whichField,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo,
                                 UInt32              uiCopyOffset);

            void execSync (      DynFieldAttachment *pFrom,
                                 ConstFieldMaskArg   whichField,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo,
                                 UInt32              uiCopyOffset);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    virtual void execBeginEditV(ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);

            void execBeginEdit (ConstFieldMaskArg whichField, 
                                UInt32            uiAspect,
                                UInt32            uiContainerSize);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
 
  private:

    friend class FieldContainer;
    
    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    /*!\brief prohibit default functions (move to 'public' if needed) */
    void operator =(const DynFieldAttachment &source);
};

OSG_END_NAMESPACE

#include "OSGDynamicAttachmentMixin.inl"

#define OSGDYNAMICATTACHMENTMIXIN_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGDYNAMICATTACHMENTMIXIN_H_ */
