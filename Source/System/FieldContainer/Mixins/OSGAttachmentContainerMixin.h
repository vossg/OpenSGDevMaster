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

#ifndef _OSGATTACHMENTCONTAINERMIXIN_H_
#define _OSGATTACHMENTCONTAINERMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGAttachmentMapFields.h"
#include "OSGFieldDescriptionBase.h"

OSG_BEGIN_NAMESPACE

//! Brief
//! \ingroup baselib

template <class ParentT>
class AttachmentContainerMixin  : public ParentT
{
    /*==========================  PRIVATE  ================================*/

  private:

    typedef ParentT Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          AttachmentContainerMixin<ParentT> Self;

    typedef typename ParentT::Desc                     Desc;

    typedef typename Desc::AttachmentObjPtr            AttachmentObjPtr;
    typedef typename Desc::AttachmentObj               AttachmentObj;
    typedef typename Desc::SFAttachmentObjPtrMap       SFAttachmentObjPtrMap;
    typedef typename SFAttachmentObjPtrMap::StoredType AttachmentObjPtrMap;
    

    typedef typename AttachmentObjPtrMap::iterator     AttachmentObjPtrMapIt;

    typedef typename Desc::TypeObject                  TypeObject;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    OSG_RC_FIRST_FIELD_DECL(Attachments);

    OSG_RC_LAST_FIELD_DECL (Attachments);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

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

    void             addAttachment (const AttachmentObjPtr   &attachmentP, 
                                          UInt16              binding    = 0);

    void             subAttachment (const AttachmentObjPtr   &attachmentP,
                                          UInt16              binding    = 0);

    AttachmentObjPtr findAttachment(      UInt32              groupId,
                                          UInt16              binding    = 0);

    AttachmentObjPtr findAttachment(const FieldContainerType &type,
                                          UInt16              binding    = 0);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    const SFAttachmentObjPtrMap *getSFAttachments(void) const;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFAttachmentObjPtrMap _sfAttachments;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    AttachmentContainerMixin(void);
    AttachmentContainerMixin(const AttachmentContainerMixin &source);

    virtual ~AttachmentContainerMixin(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    static void classDescInserter(TypeObject &oType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

#ifdef OSG_MT_FIELDCONTAINERPTR
    void execSync  (      Self              *pFrom,
                          ConstFieldMaskArg  whichField,
                          ConstFieldMaskArg  syncMode  ,
                    const UInt32             uiSyncInfo,
                          UInt32             uiCopyOffset);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    void execSync  (      Self              *pFrom,
                          ConstFieldMaskArg  whichField,
                          AspectOffsetStore &oOffsets,
                          ConstFieldMaskArg  syncMode  ,
                    const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const AttachmentContainerMixin &source);
};

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERMIXIN_HEADER_CVSID "@(#)$Id$"

#include "OSGAttachmentContainerMixin.inl"

#endif /* _OSGATTACHMENTCONTAINERMIXIN_H_ */
