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

#define OSG_COMPILETYPEDGEOINTEGRALPROPFIELDINST

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

#include "OSGTypedGeoIntegralPropertyFields.h"

#include "OSGSFieldAdaptor.ins"
#include "OSGMFieldAdaptor.ins"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<GeoUInt8PropertyPtr>::_type(
    "GeoUInt8PropertyPtr",
    "GeoIntegralPropertyPtr");

DataType FieldTraits<GeoUInt32PropertyPtr>::_type(
    "GeoUInt32PropertyPtr",
    "GeoIntegralPropertyPtr");

OSG_FIELDTRAITS_GETTYPE(GeoUInt8PropertyPtr)
OSG_FIELDTRAITS_GETTYPE(GeoUInt32PropertyPtr)

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_FIELD_DLLEXPORT_DEF2(SFieldAdaptor, 
                         GeoUInt8PropertyPtr, 
                         SFFieldContainerPtr);

OSG_FIELD_DLLEXPORT_DEF2(MFieldAdaptor, 
                         GeoUInt8PropertyPtr, 
                         MFFieldContainerPtr);


OSG_FIELD_DLLEXPORT_DEF2(SFieldAdaptor, 
                         GeoUInt32PropertyPtr, 
                         SFFieldContainerPtr);

OSG_FIELD_DLLEXPORT_DEF2(MFieldAdaptor, 
                         GeoUInt32PropertyPtr, 
                         MFFieldContainerPtr);

OSG_END_NAMESPACE

OSG_USING_NAMESPACE
