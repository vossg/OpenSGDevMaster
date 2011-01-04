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

#include "OSGOSBTypedGeoVectorPropertyElement.h"
#include "OSGOSBElementFactoryHelper.h"

#include "OSGTypedGeoVectorProperty.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBTypedGeoVectorPropertyElement                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                                                                         */

namespace {

// Vec properties
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1ubProperty> >
        _regVec1ub("GeoVec1ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2ubProperty> >
        _regVec2ub("GeoVec2ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3ubProperty> >
        _regVec3ub("GeoVec3ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4ubProperty> >
        _regVec4ub("GeoVec4ubProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1bProperty> >
        _regVec1b("GeoVec1bProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2bProperty> >
        _regVec2b("GeoVec2bProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3bProperty> >
        _regVec3b("GeoVec3bProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4bProperty> >
        _regVec4b("GeoVec4bProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1usProperty> >
        _regVec1us("GeoVec1usProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2usProperty> >
        _regVec2us("GeoVec2usProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3usProperty> >
        _regVec3us("GeoVec3usProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4usProperty> >
        _regVec4us("GeoVec4usProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1sProperty> >
        _regVec1s("GeoVec1sProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2sProperty> >
        _regVec2s("GeoVec2sProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3sProperty> >
        _regVec3s("GeoVec3sProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4sProperty> >
        _regVec4s("GeoVec4sProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1NubProperty> >
        _regVec1Nub("GeoVec1NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2NubProperty> >
        _regVec2Nub("GeoVec2NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3NubProperty> >
        _regVec3Nub("GeoVec3NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4NubProperty> >
        _regVec4Nub("GeoVec4NubProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1NbProperty> >
        _regVec1Nb("GeoVec1NbProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2NbProperty> >
        _regVec2Nb("GeoVec2NbProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3NbProperty> >
        _regVec3Nb("GeoVec3NbProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4NbProperty> >
        _regVec4Nb("GeoVec4NbProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1NusProperty> >
        _regVec1Nus("GeoVec1NusProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2NusProperty> >
        _regVec2Nus("GeoVec2NusProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3NusProperty> >
        _regVec3Nus("GeoVec3NusProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4NusProperty> >
        _regVec4Nus("GeoVec4NusProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1NsProperty> >
        _regVec1Ns("GeoVec1NsProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2NsProperty> >
        _regVec2Ns("GeoVec2NsProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3NsProperty> >
        _regVec3Ns("GeoVec3NsProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4NsProperty> >
        _regVec4Ns("GeoVec4NsProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1fProperty> >
        _regVec1f("GeoVec1fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2fProperty> >
        _regVec2f("GeoVec2fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3fProperty> >
        _regVec3f("GeoVec3fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4fProperty> >
        _regVec4f("GeoVec4fProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec1dProperty> >
        _regVec1d("GeoVec1dProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec2dProperty> >
        _regVec2d("GeoVec2dProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec3dProperty> >
        _regVec3d("GeoVec3dProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoVec4dProperty> >
        _regVec4d("GeoVec4dProperty");

// Color properties
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoColor3ubProperty> >
        _regColor3ub("GeoColor3ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoColor4ubProperty> >
        _regColor4ub("GeoColor4ubProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoColor3NubProperty> >
        _regColor3Nub("GeoColor3NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoColor4NubProperty> >
        _regColor4Nub("GeoColor4NubProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoColor3fProperty> >
        _regColor3f("GeoColor3fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoColor4fProperty> >
        _regColor4f("GeoColor4fProperty");

} // namespace
