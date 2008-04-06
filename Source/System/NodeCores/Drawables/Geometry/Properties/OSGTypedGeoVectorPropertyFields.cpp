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

OSG_EXPORT_PTR_SFIELD_FULL(FieldContainerPtrSField, 
                           GeoPnt3fPropertyPtr, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(FieldContainerPtrMField, 
                           GeoPnt3fPropertyPtr, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(FieldContainerPtrSField, 
                           GeoVec3fPropertyPtr, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(FieldContainerPtrMField, 
                           GeoVec3fPropertyPtr, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(FieldContainerPtrSField, 
                           GeoColor4fPropertyPtr, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(FieldContainerPtrMField, 
                           GeoColor4fPropertyPtr, 
                           0);

OSG_END_NAMESPACE

OSG_USING_NAMESPACE
