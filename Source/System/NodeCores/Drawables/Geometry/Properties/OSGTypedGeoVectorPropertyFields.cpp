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

#define OSG_COMPILETYPEDGEOVECTORPROPFIELDINST

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

#include "OSGTypedGeoVectorPropertyFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<GeoPnt3fPropertyPtr>::_type(
    "GeoPnt3fPropertyPtr",
    "GeoVectorPropertyPtr");

DataType FieldTraits<GeoVec3fPropertyPtr>::_type(
    "GeoVec3fPropertyPtr",
    "GeoVectorPropertyPtr");

DataType FieldTraits<GeoColor4fPropertyPtr>::_type(
    "GeoColor4fPropertyPtr",
    "GeoVectorPropertyPtr");

OSG_FIELDTRAITS_GETTYPE(GeoPnt3fPropertyPtr)
OSG_FIELDTRAITS_GETTYPE(GeoVec3fPropertyPtr)
OSG_FIELDTRAITS_GETTYPE(GeoColor4fPropertyPtr)

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, GeoPnt3fPropertyPtr, 0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, GeoPnt3fPropertyPtr, 0);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, GeoVec3fPropertyPtr, 0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, GeoVec3fPropertyPtr, 0);

OSG_SFIELDTYPE_INST(FieldContainerPtrSField, GeoColor4fPropertyPtr, 0);
OSG_MFIELDTYPE_INST(FieldContainerPtrMField, GeoColor4fPropertyPtr, 0);

OSG_FIELD_DLLEXPORT_DEF2(FieldContainerPtrSField,
                         GeoPnt3fPropertyPtr, 
                         0);

OSG_FIELD_DLLEXPORT_DEF2(FieldContainerPtrMField,
                         GeoPnt3fPropertyPtr, 
                         0);


OSG_FIELD_DLLEXPORT_DEF2(FieldContainerPtrSField,
                         GeoVec3fPropertyPtr, 
                         0);

OSG_FIELD_DLLEXPORT_DEF2(FieldContainerPtrMField,
                         GeoVec3fPropertyPtr, 
                         0);


OSG_FIELD_DLLEXPORT_DEF2(FieldContainerPtrSField,
                         GeoColor4fPropertyPtr, 
                         0);

OSG_FIELD_DLLEXPORT_DEF2(FieldContainerPtrMField,
                         GeoColor4fPropertyPtr, 
                         0);
OSG_END_NAMESPACE

OSG_USING_NAMESPACE
