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
#include "OSGAttachmentContainerParent.h"
#include "OSGFieldContainerAttachment.h"

OSG_BEGIN_NAMESPACE

/**
* An AttachmentContainer is a field container that can store attachments to other
* FieldContainers.
* \ingroup baselib
*/
class OSG_SYSTEM_DLLMAPPING AttachmentContainer :
    public ContainerAttachmentContainerParent
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    typedef ContainerAttachmentContainerParent                  Inherited;


    typedef PointerBuilder<AttachmentContainer>::ObjPtr         ObjPtr;
    typedef PointerBuilder<AttachmentContainer>::ObjPtrConst    ObjPtrConst;
    typedef PointerBuilder<AttachmentContainer>::ObjConstPtr    ObjConstPtr;

    typedef PointerBuilder<AttachmentContainer>::ObjPtrArg      ObjPtrArg;
    typedef PointerBuilder<AttachmentContainer>::ObjConstPtrArg ObjConstPtrArg;
    typedef PointerBuilder<AttachmentContainer>::ObjPtrConstArg ObjPtrConstArg;

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

    static void   classDescInserter(TypeObject &oType);
    static Char8 *getClassname     (void             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

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

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const AttachmentContainer &source);
};

typedef AttachmentContainer::ObjPtr         AttachmentContainerPtr;
typedef AttachmentContainer::ObjPtrConst    AttachmentContainerPtrConst;
typedef AttachmentContainer::ObjConstPtr    AttachmentContainerConstPtr;

typedef AttachmentContainer::ObjPtrArg      AttachmentContainerPtrArg;
typedef AttachmentContainer::ObjConstPtrArg AttachmentContainerConstPtrArg;
typedef AttachmentContainer::ObjPtrConstArg AttachmentContainerPtrConstArg;

typedef RefPtr<AttachmentContainerPtr>      AttachmentContainerRefPtr;

OSG_SYSTEM_DLLMAPPING
void
cloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<std::string>                &cloneTypeNames,
    const std::vector<std::string>                &ignoreTypeNames   =
        std::vector<std::string>(),
    const std::vector<std::string>                &cloneGroupNames   =
        std::vector<std::string>(),
    const std::vector<std::string>                &ignoreGroupNames  =
        std::vector<std::string>()                                    );

OSG_SYSTEM_DLLMAPPING
void
cloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<UInt16>                     &cloneGroupIds,
    const std::vector<UInt16>                     &ignoreGroupIds    =
        std::vector<UInt16>()                                         );

OSG_SYSTEM_DLLMAPPING
void
cloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::string                             &cloneTypesString,
    const std::string                             &ignoreTypesString =
        std::string()                                                 );

OSG_SYSTEM_DLLMAPPING
void
cloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<const FieldContainerType *> &cloneTypes        =
        std::vector<const FieldContainerType *>(),
    const std::vector<const FieldContainerType *> &ignoreTypes       =
        std::vector<const FieldContainerType *>(),
    const std::vector<UInt16>                     &cloneGroupIds     =
        std::vector<UInt16>(),
    const std::vector<UInt16>                     &ignoreGroupIds    =
        std::vector<UInt16>()                                         );

OSG_SYSTEM_DLLMAPPING
void
deepCloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<std::string>                &cloneTypeNames,
    const std::vector<std::string>                &ignoreTypeNames   =
        std::vector<std::string>(),
    const std::vector<std::string>                &cloneGroupNames   =
        std::vector<std::string>(),
    const std::vector<std::string>                &ignoreGroupNames  =
        std::vector<std::string>()                                    );

OSG_SYSTEM_DLLMAPPING
void
deepCloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<UInt16>                     &cloneGroupIds,
    const std::vector<UInt16>                     &ignoreGroupIds    =
        std::vector<UInt16>()                                         );

OSG_SYSTEM_DLLMAPPING
void
deepCloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::string                             &cloneTypesString,
    const std::string                             &ignoreTypesString =
        std::string()                                                 );

OSG_SYSTEM_DLLMAPPING
void
deepCloneAttachments(
          AttachmentContainerPtrConstArg           src,
          AttachmentContainerPtrArg                dst,
    const std::vector<const FieldContainerType *> &shareTypes        =
        std::vector<const FieldContainerType *>(),
    const std::vector<const FieldContainerType *> &ignoreTypes       =
        std::vector<const FieldContainerType *>(),
    const std::vector<UInt16>                     &shareGroupIds     =
        std::vector<UInt16>(),
    const std::vector<UInt16>                     &ignoreGroupIds    =
        std::vector<UInt16>()                                         );

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINER_HEADER_CVSID "@(#)$Id$"

#include "OSGAttachmentContainer.inl"

#endif /* _OSGATTACHMENTCONTAINER_H_ */
