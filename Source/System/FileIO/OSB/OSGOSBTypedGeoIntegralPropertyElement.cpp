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

#include "OSGOSBTypedGeoIntegralPropertyElement.h"
#include "OSGOSBElementFactoryHelper.h"

#include "OSGTypedGeoIntegralProperty.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBTypedGeoIntegralPropertyElement                                     */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                                                                         */

namespace {

static OSBElementRegistrationHelper<
    OSBTypedGeoIntegralPropertyElement<GeoUInt8Property> >
        _regUInt8("GeoUInt8Property");
static OSBElementRegistrationHelper<
    OSBTypedGeoIntegralPropertyElement<GeoUInt16Property> >
        _regUInt16("GeoUInt16Property");
static OSBElementRegistrationHelper<
    OSBTypedGeoIntegralPropertyElement<GeoUInt32Property> >
        _regUInt32("GeoUInt32Property");

} // namespace
