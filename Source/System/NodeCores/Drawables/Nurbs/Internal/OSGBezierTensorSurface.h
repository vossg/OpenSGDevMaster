/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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
#ifndef _OSG_BEZIERTENSORSURFACE_H_
#define _OSG_BEZIERTENSORSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "OSGdctptypes.h"
#include "OSGBezierCurve3D.h"

OSG_BEGIN_NAMESPACE

class BezierTensorSurface;

typedef std::vector<BezierTensorSurface> beziersurfacevector;
typedef std::vector<beziersurfacevector> beziersurfacematrix;


class OSG_DRAWABLE_DLLMAPPING BezierTensorSurface
{
  protected:
    DCTPVec4dmatrix control_points; //control points of the surface

  public:
    inline  BezierTensorSurface(void                          );
    inline  BezierTensorSurface(const DCTPVec4dmatrix     &cps);
    inline  BezierTensorSurface(const BezierTensorSurface &bts);
    inline ~BezierTensorSurface(void                          );

    //setup functions
    int setControlPointMatrix(const DCTPVec4dmatrix& cps); //ok, acts like its name says

    //query functions
    inline DCTPVec4dmatrix& getControlPointMatrix(void);

    //some REAL functionality
    Vec3d computewdeCasteljau(Vec2d uv, int &error); //compute curve at parameter value t
    Vec3d computeLinearApproximation(Vec2d uv, int &error); //ok like its name sayz
    int   midPointSubDivision(beziersurfacematrix &newbeziers); //subdivide surface at midpoint into 4 bezier surfaces
    int   midPointSubDivision(beziersurfacevector &newbeziers); //subdivide surface at midpoint into 4 bezier surfaces
    int   midPointSubDivisionU(BezierTensorSurface &newsurface);
    int   midPointSubDivisionV(BezierTensorSurface &newsurface);
};

OSG_END_NAMESPACE

#include <OSGBezierTensorSurface.inl>

#endif //BezierTensorSurface.h
