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


#ifndef _OSGGeoSimpleGeometry_H_
#define _OSGGeoSimpleGeometry_H_
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
GeometryTransitPtr        makePlaneGeo          (Real32 xsize,
                                                 Real32 ysize,
                                                 UInt16 hor,
                                                 UInt16 vert);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makePlane             (Real32 xsize,
                                                 Real32 ysize,
                                                 UInt16 hor,
                                                 UInt16 vert);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeBoxGeo            (Real32 xsize,
                                                 Real32 ysize,
                                                 Real32 zsize,
                                                 UInt16 hor,
                                                 UInt16 vert,
                                                 UInt16 depth);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeBox               (Real32 xsize,
                                                 Real32 ysize,
                                                 Real32 zsize,
                                                 UInt16 hor,
                                                 UInt16 vert,
                                                 UInt16 depth);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeConeGeo           (Real32 height,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doBottom);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeCone              (Real32 height,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doBottom);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeCylinderGeo       (Real32 height,
                                                 Real32 radius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeCylinder          (Real32 height,
                                                 Real32 radius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeTorusGeo          (Real32 innerRadius,
                                                 Real32 outerRadius,
                                                 UInt16 sides,
                                                 UInt16 rings );


OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeTorus             (Real32 innerRadius,
                                                 Real32 outerRadius,
                                                 UInt16 sides,
                                                 UInt16 rings);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeSphereGeo         (UInt16 depth,
                                                 Real32 radius);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeSphere            (UInt16 depth,
                                                 Real32 radius);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeLatLongSphereGeo  (UInt16 latres,
                                                 UInt16 longres,
                                                 Real32 radius);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeLatLongSphere     (UInt16 latres,
                                                 UInt16 longres,
                                                 Real32 radius);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeLatLongEllipsoidGeo(UInt16 latres,
                                                  UInt16 longres,
                                                  Real32 rSemiMajorAxis,
                                                  Real32 rSemiMinorAxis);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeLatLongEllipsoid   (UInt16 latres,
                                                  UInt16 longres,
                                                  Real32 rSemiMajorAxis,
                                                  Real32 rSemiMinorAxis);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeLatLongEllipsoidGeoSeg(UInt16 latres,
                                                     UInt16 longres,
                                                     Real32 rSemiMajorAxis,
                                                     Real32 rSemiMinorAxis,
                                                     Real32 rStartLatRad,
                                                     Real32 rStartLongRad,
                                                     Real32 rStopLatRad,
                                                     Real32 rStopLongRad );

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeLatLongEllipsoidSeg   (UInt16 latres,
                                                     UInt16 longres,
                                                     Real32 rSemiMajorAxis,
                                                     Real32 rSemiMinorAxis,
                                                     Real32 rStartLatRad,
                                                     Real32 rStartLongRad,
                                                     Real32 rStopLatRad,
                                                     Real32 rStopLongRad );

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr         makeEllipsoidAxisGeo   (UInt16 latres,
                                                  UInt16 longres,
                                                  Real32 rSemiMajorAxis,
                                                  Real32 rSemiMinorAxis);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeEllipsoidAxis      (UInt16 latres,
                                                  UInt16 longres,
                                                  Real32 rSemiMajorAxis,
                                                  Real32 rSemiMinorAxis);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeConicalFrustumGeo (Real32 height,
                                                 Real32 topradius,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeConicalFrustum    (Real32 height,
                                                 Real32 topradius,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);
OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeCoordAxis(Real32 length,
                                        Real32 lineWidth    = 2.0f,
                                        bool   showAxisName = true);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeCoordAxisGeo(Real32 length,
                                           Real32 lineWidth    = 2.0f,
                                           bool   showAxisName = true);

OSG_DRAWABLE_DLLMAPPING
GeometryTransitPtr        makeTeapotGeo(UInt16 depth, 
                                        Real32 rScale = 1.f);

OSG_DRAWABLE_DLLMAPPING
NodeTransitPtr            makeTeapot   (UInt16 depth, 
                                        Real32 rScale = 1.f);

/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGGeoSimpleGeometry_H_ */
