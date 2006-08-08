/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#define OSG_COMPILECONTAINERFIELDINST

#include <OSGField.h>

#include <OSGSField.h>
#include <OSGSField.ins>

#include <OSGMField.h>
#include <OSGMField.ins>

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"

#endif

#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"

#include "OSGNodeSFields.h"
#include "OSGNodeMFields.h"

#include "OSGNodeCoreSFields.h"
#include "OSGNodeCoreMFields.h"

#include "OSGAttachmentMapSFields.h"

#include "OSGFieldContainerPtr.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<FieldContainerPtr          >::_type(
    "FieldContainerPtr",
    NULL);

DataType FieldTraits<ParentFieldContainerPtr,  1>::_type(
    "ParentFieldContainerPtr",
    NULL);

DataType FieldTraits<NodeCorePtr                >::_type(
    "NodeCorePtr",
    "FieldContainerPtr");

DataType FieldTraits<NodePtr                    >::_type(
    "NodePtr",
    "FieldContainerPtr");

DataType FieldTraits<ParentNodePtr,            1>::_type(
    "ParentNodePtr",
    NULL);

DataType FieldTraits<FieldBundleAttachmentMap   >::_type(
    "FieldBundleAttachmentMap",
    NULL);

DataType FieldTraits<FieldContainerAttachmentMap>::_type(
    "FieldContainerAttachmentMap",
    NULL);
 
OSG_FIELDTRAITS_GETTYPE   (FieldContainerPtr          )
OSG_FIELDTRAITS_GETTYPE_NS(ParentFieldContainerPtr,  1)

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_FIELD_DLLEXPORT_DEF1(SField, FieldContainerPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, FieldContainerPtr);

OSG_FIELD_DLLEXPORT_DEF2(SField, ParentFieldContainerPtr, 1);
OSG_FIELD_DLLEXPORT_DEF2(MField, ParentFieldContainerPtr, 1);

OSG_FIELD_DLLEXPORT_DEF1(SField, NodeCorePtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, NodeCorePtr);

OSG_FIELD_DLLEXPORT_DEF1(SField, NodePtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, NodePtr);

OSG_FIELD_DLLEXPORT_DEF2(SField, ParentNodePtr, 1);
OSG_FIELD_DLLEXPORT_DEF2(MField, ParentNodePtr, 1);

OSG_FIELD_DLLEXPORT_DEF1(SField, FieldBundleAttachmentMap);
OSG_FIELD_DLLEXPORT_DEF1(SField, FieldContainerAttachmentMap);

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";

//    static Char8 cvsid_sfbt_hpp[] = OSGSFBASETYPES_HEADER_CVSID;
//    static Char8 cvsid_mfbt_hpp[] = OSGMFBASETYPES_HEADER_CVSID;
//    static Char8 cvsid_bfdt_hpp[] = OSGBASEFIELDDATATYPE_HEADER_CVSID;
}



