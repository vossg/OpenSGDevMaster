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

#include "OSGField.h"

#include "OSGSField.h"
#include "OSGSField.ins"

#include "OSGMField.h"
#include "OSGMField.ins"

#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"

#include "OSGAttachmentContainerSFields.h"
#include "OSGAttachmentContainerMFields.h"

#include "OSGNodeSFields.h"
#include "OSGNodeMFields.h"

#include "OSGMemoryObjectSFields.h"
#include "OSGMemoryObjectMFields.h"

#include "OSGHardwareContextDataSFields.h"
#include "OSGHardwareContextDataMFields.h"

#include "OSGChangedFunctorSFields.h"
#include "OSGChangedFunctorMFields.h"

#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

DataType FieldTraits<FieldContainer          *>::_type(
    "FieldContainerPtr",
    NULL);

DataType FieldTraits<FieldContainer          *>::_mapType(
    "FieldContainerPtrMap",
    NULL);

DataType FieldTraits<AttachmentContainer     *>::_type(
    "AttachmentContainerPtr",
    "FieldContainerPtr");

DataType FieldTraits<Node                   *>::_type(
    "NodePtr",
    "AttachmentContainerPtr");

DataType FieldTraits<ChangedFunctorCallback  >::_type(
    "ChangedFunctorCallback",
    NULL);
 
DataType FieldTraits<MemoryObject           *>::_type(
    "MemoryObjectPtr",
    NULL);

DataType FieldTraits<HardwareContextData    *>::_type(
    "HardwareContextDataPtr",
    "MemoryObjectPtr");

OSG_FIELDTRAITS_GETTYPE(FieldContainer         *)
OSG_FIELDTRAITS_GETTYPE(AttachmentContainer    *)
OSG_FIELDTRAITS_GETTYPE(Node                   *)
OSG_FIELDTRAITS_GETTYPE(ChangedFunctorCallback  )
OSG_FIELDTRAITS_GETTYPE(MemoryObject           *)
OSG_FIELDTRAITS_GETTYPE(HardwareContextData    *)

DataType &FieldTraits< FieldContainer *>::getMapType(void)
{                                                           
    return _mapType;
}

DataType &FieldTraits< FieldContainer *, 1 >::getType(void)
{                                                           
    return FieldTraits<FieldContainer *, 0>::getType();
}

DataType &FieldTraits< Node *, 1 >::getType(void)
{                                                           
    return FieldTraits<Node *, 0>::getType();
}

// FieldContainer

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           FieldContainer *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           FieldContainer *, 
                           0);

// Node

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           Node *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           Node *, 
                           0);

// AttachmentContainer

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           AttachmentContainer *, 
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           AttachmentContainer *, 
                           0);

// NodeChildNode
OSG_EXPORT_PTR_MFIELD(ChildPointerMField,
                      Node *,
                      UnrecordedRefCountPolicy, 
                      1);


// ParentFieldContainer

OSG_SFIELDTYPE_INST(ParentPointerSField,
                    FieldContainer *, 
                    NoRefCountPolicy,
                    1);
OSG_MFIELDTYPE_INST(ParentPointerMField, 
                    FieldContainer *, 
                    NoRefCountPolicy,
                    1);

OSG_FIELD_DLLEXPORT_DEF3(ParentPointerSField, 
                         FieldContainer *, 
                         NoRefCountPolicy,
                         1);
OSG_FIELD_DLLEXPORT_DEF3(ParentPointerMField, 
                         FieldContainer *, 
                         NoRefCountPolicy,
                         1);


OSG_SFIELDTYPE_INST_X(ParentPointerSField,
                      Node *,
                      NoRefCountPolicy,
                      1);
OSG_MFIELDTYPE_INST_X(ParentPointerMField,
                      Node *,
                      NoRefCountPolicy,
                      1);

OSG_FIELD_DLLEXPORT_DEF3(ParentPointerSField,
                         Node *,
                         NoRefCountPolicy,
                         1);
OSG_FIELD_DLLEXPORT_DEF3(ParentPointerMField,
                         Node *,
                         NoRefCountPolicy,
                         1);

// ChangeFunctor

OSG_FIELD_DLLEXPORT_DEF1(SField, ChangedFunctorCallback);
OSG_FIELD_DLLEXPORT_DEF1(MField, ChangedFunctorCallback);

// MemoryObject

OSG_EXPORT_PTR_SFIELD(MemObjPointerSField,
                      MemoryObject *, 
                      MemObjRefCountPolicy,
                      0);
OSG_EXPORT_PTR_MFIELD(MemObjPointerMField, 
                      MemoryObject *, 
                      MemObjRefCountPolicy,
                      0);

// HardwareContextData

OSG_EXPORT_PTR_SFIELD(MemObjPointerSField,
                      HardwareContextData *, 
                      MemObjRefCountPolicy,
                      0);
OSG_EXPORT_PTR_MFIELD(MemObjPointerMField, 
                      HardwareContextData *, 
                      MemObjRefCountPolicy,
                      0);

OSG_END_NAMESPACE
