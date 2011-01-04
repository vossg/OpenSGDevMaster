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

// Pnt properties
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1ubProperty> >
        _regPnt1ub("GeoPnt1ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2ubProperty> >
        _regPnt2ub("GeoPnt2ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3ubProperty> >
        _regPnt3ub("GeoPnt3ubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4ubProperty> >
        _regPnt4ub("GeoPnt4ubProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1bProperty> >
        _regPnt1b("GeoPnt1bProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2bProperty> >
        _regPnt2b("GeoPnt2bProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3bProperty> >
        _regPnt3b("GeoPnt3bProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4bProperty> >
        _regPnt4b("GeoPnt4bProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1usProperty> >
        _regPnt1us("GeoPnt1usProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2usProperty> >
        _regPnt2us("GeoPnt2usProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3usProperty> >
        _regPnt3us("GeoPnt3usProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4usProperty> >
        _regPnt4us("GeoPnt4usProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1sProperty> >
        _regPnt1s("GeoPnt1sProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2sProperty> >
        _regPnt2s("GeoPnt2sProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3sProperty> >
        _regPnt3s("GeoPnt3sProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4sProperty> >
        _regPnt4s("GeoPnt4sProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1NubProperty> >
        _regPnt1Nub("GeoPnt1NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2NubProperty> >
        _regPnt2Nub("GeoPnt2NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3NubProperty> >
        _regPnt3Nub("GeoPnt3NubProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4NubProperty> >
        _regPnt4Nub("GeoPnt4NubProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1NbProperty> >
        _regPnt1Nb("GeoPnt1NbProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2NbProperty> >
        _regPnt2Nb("GeoPnt2NbProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3NbProperty> >
        _regPnt3Nb("GeoPnt3NbProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4NbProperty> >
        _regPnt4Nb("GeoPnt4NbProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1NusProperty> >
        _regPnt1Nus("GeoPnt1NusProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2NusProperty> >
        _regPnt2Nus("GeoPnt2NusProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3NusProperty> >
        _regPnt3Nus("GeoPnt3NusProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4NusProperty> >
        _regPnt4Nus("GeoPnt4NusProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1NsProperty> >
        _regPnt1Ns("GeoPnt1NsProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2NsProperty> >
        _regPnt2Ns("GeoPnt2NsProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3NsProperty> >
        _regPnt3Ns("GeoPnt3NsProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4NsProperty> >
        _regPnt4Ns("GeoPnt4NsProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1fProperty> >
        _regPnt1f("GeoPnt1fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2fProperty> >
        _regPnt2f("GeoPnt2fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3fProperty> >
        _regPnt3f("GeoPnt3fProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4fProperty> >
        _regPnt4f("GeoPnt4fProperty");

static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt1dProperty> >
        _regPnt1d("GeoPnt1dProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt2dProperty> >
        _regPnt2d("GeoPnt2dProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt3dProperty> >
        _regPnt3d("GeoPnt3dProperty");
static OSBElementRegistrationHelper<
    OSBTypedGeoVectorPropertyElement<GeoPnt4dProperty> >
        _regPnt4d("GeoPnt4dProperty");

} // namespace
