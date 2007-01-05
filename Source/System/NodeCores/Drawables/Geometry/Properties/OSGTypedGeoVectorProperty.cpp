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

#define OSG_COMPILENAMEDGEOPROPINST

#include <cstdlib>
#include <cstdio>

#include "OSGTypedGeoVectorProperty.h"


#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

//#include "OSGTypedGeoVectorPropertyFuncs.ins"

#endif

#include "OSGTypedGeoVectorProperty.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

#define OSG_EXPORT_PROP(DESC)                           \
template <> OSG_DLL_EXPORT                              \
TypedGeoVectorProperty< DESC >::TypeObject &            \
    TypedGeoVectorProperty< DESC >::getType(void)       \
{                                                       \
    return _type;                                       \
}                                                       \
                                                        \
template <> OSG_DLL_EXPORT                              \
const TypedGeoVectorProperty< DESC >::TypeObject &      \
    TypedGeoVectorProperty< DESC >::getType(void) const \
{                                                       \
    return _type;                                       \
}                                                       \
                                                        \
template <> OSG_DLL_EXPORT                              \
TypedGeoVectorProperty< DESC >::TypeObject &            \
    TypedGeoVectorProperty< DESC >::getClassType(void)  \
{                                                       \
    return _type;                                       \
}


OSG_EXPORT_PROP(GeoVec1ubPropertyDesc)
OSG_EXPORT_PROP(GeoVec2ubPropertyDesc)
OSG_EXPORT_PROP(GeoVec3ubPropertyDesc)
OSG_EXPORT_PROP(GeoVec4ubPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1ubPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2ubPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3ubPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4ubPropertyDesc)

OSG_EXPORT_PROP(GeoVec1NubPropertyDesc)
OSG_EXPORT_PROP(GeoVec2NubPropertyDesc)
OSG_EXPORT_PROP(GeoVec3NubPropertyDesc)
OSG_EXPORT_PROP(GeoVec4NubPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1NubPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2NubPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3NubPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4NubPropertyDesc)


OSG_EXPORT_PROP(GeoVec1bPropertyDesc)
OSG_EXPORT_PROP(GeoVec2bPropertyDesc)
OSG_EXPORT_PROP(GeoVec3bPropertyDesc)
OSG_EXPORT_PROP(GeoVec4bPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1bPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2bPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3bPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4bPropertyDesc)

OSG_EXPORT_PROP(GeoVec1NbPropertyDesc)
OSG_EXPORT_PROP(GeoVec2NbPropertyDesc)
OSG_EXPORT_PROP(GeoVec3NbPropertyDesc)
OSG_EXPORT_PROP(GeoVec4NbPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1NbPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2NbPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3NbPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4NbPropertyDesc)


OSG_EXPORT_PROP(GeoVec1usPropertyDesc)
OSG_EXPORT_PROP(GeoVec2usPropertyDesc)
OSG_EXPORT_PROP(GeoVec3usPropertyDesc)
OSG_EXPORT_PROP(GeoVec4usPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1usPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2usPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3usPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4usPropertyDesc)

OSG_EXPORT_PROP(GeoVec1NusPropertyDesc)
OSG_EXPORT_PROP(GeoVec2NusPropertyDesc)
OSG_EXPORT_PROP(GeoVec3NusPropertyDesc)
OSG_EXPORT_PROP(GeoVec4NusPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1NusPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2NusPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3NusPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4NusPropertyDesc)


OSG_EXPORT_PROP(GeoVec1sPropertyDesc)
OSG_EXPORT_PROP(GeoVec2sPropertyDesc)
OSG_EXPORT_PROP(GeoVec3sPropertyDesc)
OSG_EXPORT_PROP(GeoVec4sPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1sPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2sPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3sPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4sPropertyDesc)

OSG_EXPORT_PROP(GeoVec1NsPropertyDesc)
OSG_EXPORT_PROP(GeoVec2NsPropertyDesc)
OSG_EXPORT_PROP(GeoVec3NsPropertyDesc)
OSG_EXPORT_PROP(GeoVec4NsPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1NsPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2NsPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3NsPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4NsPropertyDesc)

#ifndef OSG_WINCE
OSG_EXPORT_PROP(GeoVec1fPropertyDesc)
OSG_EXPORT_PROP(GeoVec2fPropertyDesc)
OSG_EXPORT_PROP(GeoVec3fPropertyDesc)
OSG_EXPORT_PROP(GeoVec4fPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1fPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2fPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3fPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4fPropertyDesc)
#endif

#ifdef OSG_WINCE
OSG_EXPORT_PROP(GeoVec1fxPropertyDesc)
OSG_EXPORT_PROP(GeoVec2fxPropertyDesc)
OSG_EXPORT_PROP(GeoVec3fxPropertyDesc)
OSG_EXPORT_PROP(GeoVec4fxPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1fxPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2fxPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3fxPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4fxPropertyDesc)
#endif

#ifndef OSG_WINCE
OSG_EXPORT_PROP(GeoVec1dPropertyDesc)
OSG_EXPORT_PROP(GeoVec2dPropertyDesc)
OSG_EXPORT_PROP(GeoVec3dPropertyDesc)
OSG_EXPORT_PROP(GeoVec4dPropertyDesc)

OSG_EXPORT_PROP(GeoPnt1dPropertyDesc)
OSG_EXPORT_PROP(GeoPnt2dPropertyDesc)
OSG_EXPORT_PROP(GeoPnt3dPropertyDesc)
OSG_EXPORT_PROP(GeoPnt4dPropertyDesc)
#endif

OSG_EXPORT_PROP(GeoColor3ubPropertyDesc)
OSG_EXPORT_PROP(GeoColor4ubPropertyDesc)
OSG_EXPORT_PROP(GeoColor3NubPropertyDesc)
OSG_EXPORT_PROP(GeoColor4NubPropertyDesc)

OSG_EXPORT_PROP(GeoColor3fPropertyDesc)
OSG_EXPORT_PROP(GeoColor4fPropertyDesc)

OSG_END_NAMESPACE
