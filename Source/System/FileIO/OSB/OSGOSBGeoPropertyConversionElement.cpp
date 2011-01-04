/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#include "OSGOSBGeoPropertyConversionElement.h"
#include "OSGOSBElementFactoryHelper.h"

#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBGeoPropertyConversionElement                                        */
/*-------------------------------------------------------------------------*/

namespace {

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt2sProperty> >
        _regPos2s("GeoPositions2s");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt3sProperty> >
        _regPos3s("GeoPositions3s");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt4sProperty> >
        _regPos4s("GeoPositions4s");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt2fProperty> >
        _regPos2f("GeoPositions2f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt3fProperty> >
        _regPos3f("GeoPositions3f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt4fProperty> >
        _regPos4f("GeoPositions4f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt2dProperty> >
        _regPos2d("GeoPositions2d");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt3dProperty> >
        _regPos3d("GeoPositions3d");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoPnt4dProperty> >
        _regPos4d("GeoPositions4d");

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec3sProperty> >
        _regNorm3s("GeoNormals3s");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec3fProperty> >
        _regNorm3f("GeoNormals3f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec3bProperty> >
        _regNorm3b("GeoNormals3b");

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoColor3fProperty> >
        _regCol3f("GeoColors3f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoColor4fProperty> >
        _regCol4f("GeoColors4f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoColor3ubProperty> >
        _regCol3ub("GeoColors3ub");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoColor4ubProperty> >
        _regCol4ub("GeoColors4ub");

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec1fProperty> >
        _regTexCoord1f("GeoTexCoords1f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec2fProperty> >
        _regTexCoord2f("GeoTexCoords2f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec3fProperty> >
        _regTexCoord3f("GeoTexCoords3f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec4fProperty> >
        _regTexCoord4f("GeoTexCoords4f");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec1dProperty> >
        _regTexCoord1d("GeoTexCoords1d");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec2dProperty> >
        _regTexCoord2d("GeoTexCoords2d");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec3dProperty> >
        _regTexCoord3d("GeoTexCoords3d");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoVec4dProperty> >
        _regTexCoord4d("GeoTexCoords4d");

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt8Property> >
        _regTypesUI8("GeoPTypesUI8");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt16Property> >
        _regTypesUI16("GeoPTypesUI16");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt32Property> >
        _regTypesUI32("GeoPTypesUI32");

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt8Property> >
        _regLengthsUI8("GeoPLengthsUI8");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt16Property> >
        _regLenghtsUI16("GeoPLengthsUI16");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt32Property> >
        _regLengthsUI32("GeoPLengthsUI32");

static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt8Property> >
        _regIndicesUI8("GeoIndicesUI8");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt16Property> >
        _regIndicesUI16("GeoIndicesUI16");
static OSBElementRegistrationHelper<
    OSBGeoPropertyConversionElement<GeoUInt32Property> >
        _regIndicesUI32("GeoIndicesUI32");

} // namespace
