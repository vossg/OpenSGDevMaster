/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGGeoSimpleLightGeometry_H_
#define _OSGGeoSimpleLightGeometry_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGNode.h"
#include "OSGDrawableDef.h"
#include "OSGGeometry.h"


OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                   Construction functions                     */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr          makeSpot                (Real32 R,
                                                 Real32 angle,
                                                 UInt32 slices,
                                                 UInt32 sides);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr      makeSpotGeo             (Real32 R,
                                                 Real32 angle,
                                                 UInt32 slices,
                                                 UInt32 sides);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr          makeCinema              (Real32 a,
                                                 Real32 b,
                                                 Real32 r,
                                                 Real32 theta,
                                                 Real32 h,
                                                 UInt32 slices,
                                                 UInt32 sides);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr      makeCinemaGeo           (Real32 a,
                                                 Real32 b,
                                                 Real32 r,
                                                 Real32 theta,
                                                 Real32 h,
                                                 UInt32 slices,
                                                 UInt32 sides);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr          makeFrustumVolume       (const Pnt3f& nlt,
                                                 const Pnt3f& nlb,
                                                 const Pnt3f& nrt,
                                                 const Pnt3f& nrb,
                                                 const Pnt3f& flt,
                                                 const Pnt3f& flb,
                                                 const Pnt3f& frt,
                                                 const Pnt3f& frb);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr      makeFrustumVolumeGeo    (const Pnt3f& nlt,
                                                 const Pnt3f& nlb,
                                                 const Pnt3f& nrt,
                                                 const Pnt3f& nrb,
                                                 const Pnt3f& flt,
                                                 const Pnt3f& flb,
                                                 const Pnt3f& frt,
                                                 const Pnt3f& frb);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr          makeFrustumVolume       (const FrustumVolume& vol);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr      makeFrustumVolumeGeo    (const FrustumVolume& vol);

/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGGeoSimpleLightGeometry_H_ */
