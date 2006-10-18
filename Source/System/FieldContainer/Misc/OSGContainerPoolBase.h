/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class ContainerPool
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGCONTAINERPOOLBASE_H_
#define _OSGCONTAINERPOOLBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGBaseTypes.h"

#include "OSGFieldContainerAttachment.h" // Parent

#include "OSGStringFields.h" // Name type
#include "OSGFieldContainerFields.h" // Containers type

#include "OSGContainerPoolFields.h"

OSG_BEGIN_NAMESPACE

class ContainerPool;

//! \brief ContainerPool Base Class.

class OSG_SYSTEM_DLLMAPPING ContainerPoolBase : public FieldContainerAttachment
{
  public:

    typedef FieldContainerAttachment Inherited;
    typedef FieldContainerAttachment ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    typedef PointerFwdBuilder<FieldContainerAttachmentPtr, 
                              FieldContainerAttachmentConstPtr, 
                              ContainerPool>::ObjPtr         ObjPtr;
    typedef PointerFwdBuilder<FieldContainerAttachmentPtr, 
                              FieldContainerAttachmentConstPtr, 
                              ContainerPool>::ObjPtrConst    ObjPtrConst;
    typedef PointerFwdBuilder<FieldContainerAttachmentPtr, 
                              FieldContainerAttachmentConstPtr,
                              ContainerPool>::ObjConstPtr    ObjConstPtr;
    typedef PointerFwdBuilder<FieldContainerAttachmentPtr, 
                              FieldContainerAttachmentConstPtr,
                              ContainerPool>::ObjPtrArg      ObjPtrArg;
    typedef PointerFwdBuilder<FieldContainerAttachmentPtr, 
                              FieldContainerAttachmentConstPtr,
                              ContainerPool>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerFwdBuilder<FieldContainerAttachmentPtr, 
                              FieldContainerAttachmentConstPtr,
                              ContainerPool>::ObjPtrConstArg ObjPtrConstArg;

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        NameFieldId = Inherited::NextFieldId,
        ContainersFieldId = NameFieldId + 1,
        NextFieldId = ContainersFieldId + 1
    };

    static const OSG::BitVector NameFieldMask = 
        (TypeTraits<BitVector>::One << NameFieldId);
    static const OSG::BitVector ContainersFieldMask = 
        (TypeTraits<BitVector>::One << ContainersFieldId);
    static const OSG::BitVector NextFieldMask = 
        (TypeTraits<BitVector>::One << NextFieldId);


    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void); 
    static UInt32              getClassTypeId (void); 
    static UInt16              getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void); 
    virtual const FieldContainerType &getType         (void) const; 

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */


#ifdef OSG_1_COMPAT
           SFString *getSFName(void);
#endif
           SFString *editSFName(void);
     const SFString *getSFName (void) const;
     const MFFieldContainerPtr *getMFContainers (void) const;


#ifdef OSG_1_COMPAT
           std::string &getName(void);
#endif
           std::string &editName(void);
     const std::string &getName (void) const;

           FieldContainerPtrConst getContainers(const UInt32 index) const;
     const MFFieldContainerPtr &getContainers(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

     void setName(const std::string &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    virtual void pushToField     (      FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void insertIntoMField(const UInt32                    uiIndex, 
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void replaceInMField (const UInt32                    uiIndex,
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                        FieldContainerPtrConstArg pNewElement, 
                                  const UInt32                    uiFieldId  );

    virtual void removeFromMField(const UInt32                    uiIndex, 
                                  const UInt32                    uiFieldId  );
    
    virtual void removeFromMField(      FieldContainerPtrConstArg pElement, 
                                  const UInt32                    uiFieldId  );

    virtual void clearField      (const UInt32                    uiFieldId  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void pushToContainers           (FieldContainerPtrConstArg value   );
    void insertIntoContainers      (UInt32                uiIndex,
                                    FieldContainerPtrConstArg value   );
    void replaceInContainers  (UInt32                uiIndex,
                                    FieldContainerPtrConstArg value   );
    void replaceInContainers (FieldContainerPtrConstArg pOldElem,
                                    FieldContainerPtrConstArg pNewElem);
    void removeFromContainers (UInt32                uiIndex );
    void removeFromContainers(FieldContainerPtrConstArg value   );
    void clearContainers            (void                          );

 

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
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ContainerPoolPtr create     (void); 
    static  ContainerPoolPtr createEmpty(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr shallowCopy(void) const; 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFString _sfName;
    MFFieldContainerPtr _mfContainers;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ContainerPoolBase(void);
    ContainerPoolBase(const ContainerPoolBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ContainerPoolBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const ContainerPool *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_FIELDCONTAINERPTR
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);

            void execSync (      ContainerPoolBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo,
                                 UInt32             uiCopyOffset);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      ContainerPoolBase *pFrom,
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
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainerPtr createAspectCopy(void) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ContainerPoolBase &source);
};

typedef ContainerPoolBase *ContainerPoolBaseP;

/** Type specific RefPtr type for ContainerPool. */
typedef RefPtr<ContainerPoolPtr> ContainerPoolRefPtr;

typedef osgIF<
    ContainerPoolBase::isNodeCore,

    CoredNodePtr<ContainerPool>,
    FieldContainer::attempt_to_create_CoredNodePtr_on_non_NodeCore_FC>::_IRet

        ContainerPoolNodePtr;

OSG_END_NAMESPACE

#define OSGCONTAINERPOOLBASE_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGCONTAINERPOOLBASE_H_ */
