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

#include <OSGField.h>

#include <OSGSField.h>
#include <OSGSField.ins>

#include <OSGMField.h>
#include <OSGMField.ins>

#include "OSGTypedGeoIntegralPropertyFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<GeoUInt8Property  *>::_type(
    "GeoUInt8PropertyPtr",
    "GeoIntegralPropertyPtr");

DataType FieldTraits<GeoUInt32Property *>::_type(
    "GeoUInt32PropertyPtr",
    "GeoIntegralPropertyPtr");

OSG_FIELDTRAITS_GETTYPE(GeoUInt8Property  *)
OSG_FIELDTRAITS_GETTYPE(GeoUInt32Property *)

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           GeoUInt8Property *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           GeoUInt8Property *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           GeoUInt32Property *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           GeoUInt32Property *, 
                           0);

OSG_END_NAMESPACE

OSG_USING_NAMESPACE
