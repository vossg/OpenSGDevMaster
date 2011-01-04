/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
 //  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGTypedGeoVectorProperty.h"

#include "OSGTypedGeoVectorPropertyFuncs.ins"

#include "OSGTypedGeoVectorProperty.ins"

OSG_BEGIN_NAMESPACE

/*
OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(TypedGeoVectorProperty,
                                    GeoPropertyDesc)

#define OSG_EXPORT_PROP(DESC)                           \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(TypedGeoVectorProperty, DESC) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(TypedGeoVectorProperty, DESC)   \
   template class OSG_DLL_EXPORT TypedGeoVectorProperty<DESC>;
*/


OSG_EXPORT_PROP(GeoVec1fPropertyDesc)
OSG_EXPORT_PROP(GeoVec2fPropertyDesc)
OSG_EXPORT_PROP(GeoVec3fPropertyDesc)
OSG_EXPORT_PROP(GeoVec4fPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1fPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2fPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3fPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4fPropertyDesc)

OSG_END_NAMESPACE
