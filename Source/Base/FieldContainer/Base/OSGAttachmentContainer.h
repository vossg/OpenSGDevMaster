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

#ifndef _OSGATTACHMENTCONTAINER_H_
#define _OSGATTACHMENTCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainer.h"
#include "OSGAttachmentMapSFields.h"

OSG_BEGIN_NAMESPACE

class BasicFieldConnector;
class Attachment;

/*! An AttachmentContainer is a field container that can store attachments to 
    other FieldContainers.
    \ingroup GrpBaseFieldContainerBase
    \ingroup GrpLibOSGBase
 */
class OSG_BASE_DLLMAPPING AttachmentContainer : public FieldContainer
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef FieldContainer                      Inherited;
    typedef Inherited::TypeObject               TypeObject;
    typedef AttachmentContainer                 Self;

    typedef Attachment                          AttachmentObj;
    typedef Attachment                         *AttachmentObjCPtr;
    typedef SFAttachmentPtrMap                  SFAttachmentObjPtrMap;

    typedef SFAttachmentObjPtrMap::StoredType   AttachmentObjPtrMap;
    typedef AttachmentObjPtrMap::iterator       AttachmentObjPtrMapIt;
    typedef AttachmentObjPtrMap::const_iterator AttachmentObjPtrMapConstIt;

    
    OSG_GEN_INTERNALPTR(AttachmentContainer);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_ABSTR_FIELD_CONTAINER_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_RC_FIRST_FIELD_DECL(Attachments);
    OSG_RC_LAST_FIELD_DECL (Attachments);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual FieldContainer *findNamedComponent(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg   whichField);
    virtual void   copyToBin  (BinaryDataHandler  &pMem,
                               ConstFieldMaskArg   whichField);
    virtual void   copyFromBin(BinaryDataHandler  &pMem,
                               ConstFieldMaskArg   whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void             addAttachment         (Attachment * const pAttachment,
                                            UInt16             binding    = 0);

    void             subAttachment         (Attachment * const pAttachment,
                                            UInt16             binding    = 0);

    void             replaceAttachmentByObj(Attachment * const pOld,
                                            Attachment * const pNew          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    Attachment *findAttachment(      UInt32             groupId,
                                     UInt16             binding = 0) const;

    Attachment *findAttachment(const FieldContainerType &type,
                                     UInt16              binding= 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    const SFAttachmentObjPtrMap *getSFAttachments(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

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
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFAttachmentObjPtrMap _sfAttachments;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    AttachmentContainer(void);
    AttachmentContainer(const AttachmentContainer &source);

    virtual ~AttachmentContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    void execSync  (      AttachmentContainer *pFrom,
                          ConstFieldMaskArg    whichField,
                          AspectOffsetStore   &oOffsets,
                          ConstFieldMaskArg    syncMode  ,
                    const UInt32               uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    EditFieldHandlePtr editHandleAttachments(void);
    GetFieldHandlePtr  getHandleAttachments (void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const AttachmentContainer &source);
};

OSG_GEN_CONTAINERPTR(AttachmentContainer);

OSG_BASE_DLLMAPPING
void cloneAttachments(
          OSG::AttachmentContainer const *         src,
          OSG::AttachmentContainer       *         dst,
    const std::vector<std::string>                &cloneTypeNames,

    const std::vector<std::string>                &ignoreTypeNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                &cloneGroupNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                &ignoreGroupNames  =
              std::vector<std::string>()                              );

OSG_BASE_DLLMAPPING
void cloneAttachments(
          OSG::AttachmentContainer const *              src,
          OSG::AttachmentContainer       *              dst,
    const std::vector<OSG::UInt16>                     &cloneGroupIds,

    const std::vector<OSG::UInt16>                     &ignoreGroupIds    =
              std::vector<OSG::UInt16>()                                   );

OSG_BASE_DLLMAPPING
void cloneAttachments(
          OSG::AttachmentContainer const *         src,
          OSG::AttachmentContainer       *         dst,
    const std::string                             &cloneTypesString,

    const std::string                             &ignoreTypesString =
              std::string()                                           );

OSG_BASE_DLLMAPPING
void cloneAttachments(
          OSG::AttachmentContainer const *              src,
          OSG::AttachmentContainer       *              dst,

    const std::vector<const OSG::ReflexiveContainerType *> &cloneTypes    =
              std::vector<const OSG::ReflexiveContainerType *>(),

    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes       =
              std::vector<const OSG::ReflexiveContainerType *>(),

    const std::vector<OSG::UInt16>                     &cloneGroupIds     =
              std::vector<OSG::UInt16>(),

    const std::vector<OSG::UInt16>                     &ignoreGroupIds    =
              std::vector<OSG::UInt16>()                                   );

OSG_BASE_DLLMAPPING
void deepCloneAttachments(
          OSG::AttachmentContainer const *              src,
          OSG::AttachmentContainer       *              dst,
    const std::vector<std::string>                &cloneTypeNames,

    const std::vector<std::string>                &ignoreTypeNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                &cloneGroupNames   =
              std::vector<std::string>(),

    const std::vector<std::string>                &ignoreGroupNames  =
              std::vector<std::string>()                              );

OSG_BASE_DLLMAPPING
void deepCloneAttachments(
          OSG::AttachmentContainer const *              src,
          OSG::AttachmentContainer       *              dst,
    const std::vector<OSG::UInt16>                     &cloneGroupIds,

    const std::vector<OSG::UInt16>                     &ignoreGroupIds    =
              std::vector<OSG::UInt16>()                                    );

OSG_BASE_DLLMAPPING
void deepCloneAttachments(
          OSG::AttachmentContainer const *              src,
          OSG::AttachmentContainer       *              dst,
    const std::string                             &cloneTypesString,

    const std::string                             &ignoreTypesString =
              std::string()                                           );

OSG_BASE_DLLMAPPING
void deepCloneAttachments(
          OSG::AttachmentContainer const *              src,
          OSG::AttachmentContainer       *              dst,

    const std::vector<const OSG::ReflexiveContainerType *> &shareTypes    =
              std::vector<const OSG::ReflexiveContainerType *>(),

    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes   =
              std::vector<const OSG::ReflexiveContainerType *>(),

    const std::vector<OSG::UInt16>                     &shareGroupIds     =
              std::vector<OSG::UInt16>(),

    const std::vector<OSG::UInt16>                     &ignoreGroupIds    =
              std::vector<OSG::UInt16>()                                   );

OSG_END_NAMESPACE

#include "OSGAttachmentContainer.inl"

#endif /* _OSGATTACHMENTCONTAINER_H_ */
