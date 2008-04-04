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

#include "OSGFieldContainerAttachmentSFields.h"
#include "OSGFieldContainerAttachmentMFields.h"

#include "OSGAttachmentContainerSFields.h"
#include "OSGAttachmentContainerMFields.h"

#include "OSGNodeSFields.h"
#include "OSGNodeMFields.h"

#include "OSGNodeCoreSFields.h"
#include "OSGNodeCoreMFields.h"

#define OSG_SFIELDTYPE_INST2(CLASSNAME, T1, T2)          \
template<>                                               \
FieldType CLASSNAME< T1 , T2 >::_fieldType(              \
    SFieldTraits::getSName(),                            \
    SFieldTraits::getSPName(),                           \
    SFieldTraits::getType (),                            \
    FieldType::SINGLE_FIELD)

OSG_BEGIN_NAMESPACE

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, 
                    FieldContainerPtr, 
                    RecordedRefCounts,
                    0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, 
                    FieldContainerPtr, 
                    RecordedRefCounts,
                    0);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, 
                    NodePtr, 
                    RecordedRefCounts,
                    0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, 
                    NodePtr, 
                    RecordedRefCounts,
                    0);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, 
                    NodePtr, 
                    NoRefCounts,
                    1);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, 
                    NodeCorePtr, 
                    RecordedRefCounts,
                    0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, 
                    NodeCorePtr, 
                    RecordedRefCounts,
                    0);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, 
                    AttachmentContainerPtr, 
                    RecordedRefCounts,
                    0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, 
                    AttachmentContainerPtr, 
                    RecordedRefCounts,
                    0);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, 
                    FieldContainerAttachmentPtr, 
                    RecordedRefCounts,
                    0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, 
                    FieldContainerAttachmentPtr, 
                    RecordedRefCounts,
                    0);

OSG_SFIELDTYPE_INST(FieldContainerPtrParentSField,
                    FieldContainerPtr, 
                    NoRefCounts,
                    1);
OSG_MFIELDTYPE_INST(FieldContainerPtrParentMField, 
                    FieldContainerPtr, 
                    NoRefCounts,
                    1);

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<FieldContainerPtr          >::_type(
    "FieldContainerPtr",
    NULL);

DataType FieldTraits<FieldContainerAttachmentPtr>::_type(
    "FieldContainerAttachmentPtr",
    "FieldContainerPtr");

DataType FieldTraits<AttachmentContainerPtr     >::_type(
    "AttachmentContainerPtr",
    "FieldContainerPtr");

DataType FieldTraits<NodeCorePtr                >::_type(
    "NodeCorePtr",
    "AttachmentContainerPtr");

DataType FieldTraits<NodePtr                    >::_type(
    "NodePtr",
    "AttachmentContainerPtr");

DataType FieldTraits<ChangedFunctorCallback     >::_type(
    "ChangedFunctorCallback",
    NULL);
 
OSG_FIELDTRAITS_GETTYPE   (FieldContainerPtr          )

OSG_FIELDTRAITS_GETTYPE   (FieldContainerAttachmentPtr)
OSG_FIELDTRAITS_GETTYPE   (AttachmentContainerPtr     )
OSG_FIELDTRAITS_GETTYPE   (NodeCorePtr                )
OSG_FIELDTRAITS_GETTYPE   (NodePtr                    )
OSG_FIELDTRAITS_GETTYPE   (ChangedFunctorCallback     )

DataType &FieldTraits< FieldContainerPtr, 1 >::getType(void)
{                                                           
    return FieldTraits<FieldContainerPtr, 0>::getType();
}

DataType &FieldTraits< NodePtr, 1 >::getType(void)
{                                                           
    return FieldTraits<NodePtr, 0>::getType();
}

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_FIELD_DLLEXPORT_DEF3(FieldContainerPtrSField, 
                         FieldContainerPtr, 
                         RecordedRefCounts,
                         0);
OSG_FIELD_DLLEXPORT_DEF3(FieldContainerPtrMField, 
                         FieldContainerPtr, 
                         RecordedRefCounts,
                         0);

OSG_FIELD_DLLEXPORT_DEF3(FieldContainerPtrParentSField, 
                         FieldContainerPtr, 
                         NoRefCounts,
                         1);
OSG_FIELD_DLLEXPORT_DEF3(FieldContainerPtrParentMField, 
                         FieldContainerPtr, 
                         NoRefCounts,
                         1);

OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrSField, FieldContainerAttachmentPtr);
OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrMField, FieldContainerAttachmentPtr);

OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrSField, NodeCorePtr);
OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrMField, NodeCorePtr);

OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrSField, NodePtr);
OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrMField, NodePtr);

OSG_FIELD_DLLEXPORT_DEF3(FieldContainerPtrSField, 
                         NodePtr,
                         NoRefCounts,
                         1);

//OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrSField, NodeRefPtr);
//OSG_FIELD_DLLEXPORT_DEF1(FieldContainerPtrMField, NodeRefPtr, );

OSG_FIELD_DLLEXPORT_DEF1(SField, ChangedFunctorCallback);
OSG_FIELD_DLLEXPORT_DEF1(MField, ChangedFunctorCallback);

OSG_END_NAMESPACE
