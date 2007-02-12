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

#ifndef _OSGFIELDCONTAINERATTACHMENT_H_
#define _OSGFIELDCONTAINERATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainer.h"
#include "OSGAttachmentMixin.h"
#include "OSGContainerMixinHead.h"
#include "OSGFieldContainerFields.h"

OSG_BEGIN_NAMESPACE

struct FieldContainerAttachmentDesc;

typedef AttachmentMixin< 
          ContainerMixinHead<
              FieldContainerAttachmentDesc > > FieldContainerAttachmentParent;

struct FieldContainerAttachmentDesc
{
    typedef FieldContainer             ParentT;

    typedef FieldContainer::TypeObject TypeObject;

    typedef MFParentFieldContainerPtr  ParentField;

    typedef FieldContainerPtr          ParentPtr;
    typedef FieldContainerPtrConst     ParentPtrConst;
};

//! Brief
//! \ingroup baselib

class OSG_SYSTEM_DLLMAPPING FieldContainerAttachment : 
    public FieldContainerAttachmentParent
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef PointerBuilder<
              FieldContainerAttachment>::ObjPtr         ObjPtr;
    typedef PointerBuilder<
              FieldContainerAttachment>::ObjConstPtr    ObjConstPtr;
    typedef PointerBuilder<
              FieldContainerAttachment>::ObjPtrConst    ObjPtrConst;

    typedef PointerBuilder<
              FieldContainerAttachment>::ObjPtrArg      ObjPtrArg;
    typedef PointerBuilder<
              FieldContainerAttachment>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerBuilder<
              FieldContainerAttachment>::ObjPtrConstArg ObjPtrConstArg;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_ABSTR_FIELD_CONTAINER_DECL;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static TypeObject _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FieldContainerAttachment(void);
    FieldContainerAttachment(const FieldContainerAttachment &source);

    virtual ~FieldContainerAttachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   MT Destruction                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef FieldContainerAttachmentParent Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerAttachment &source);
};

typedef FieldContainerAttachment::ObjPtr         FieldContainerAttachmentPtr;

typedef FieldContainerAttachment::ObjPtrConst    
    FieldContainerAttachmentPtrConst;

typedef FieldContainerAttachment::ObjConstPtr    
    FieldContainerAttachmentConstPtr;


typedef FieldContainerAttachment::ObjPtrArg 
    FieldContainerAttachmentPtrArg;

typedef FieldContainerAttachment::ObjConstPtrArg 
    FieldContainerAttachmentConstPtrArg;

typedef FieldContainerAttachment::ObjPtrConstArg 
    FieldContainerAttachmentPtrConstArg;

typedef RefPtr<FieldContainerAttachmentPtr>     
    FieldContainerAttachmentRefPtr;

#ifdef OSG_1_COMPAT
typedef FieldContainerAttachment            Attachment;

typedef FieldContainerAttachmentPtr         AttachmentPtr;
typedef FieldContainerAttachmentPtrConst    AttachmentPtrConst;
typedef FieldContainerAttachmentConstPtr    AttachmentConstPtr;

typedef FieldContainerAttachmentPtrArg      AttachmentPtrArg;
typedef FieldContainerAttachmentConstPtrArg AttachmentConstPtrArg;
typedef FieldContainerAttachmentPtrConstArg AttachmentPtrConstArg;

typedef FieldContainerAttachmentRefPtr      AttachmentRefPtr;
#endif

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERATTACHMENT_HEADER_CVSID "@(#)$Id$"

#include "OSGFieldContainerAttachment.inl"

#endif /* _OSGFIELDCONTAINERATTACHMENT_H_ */
