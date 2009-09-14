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
#ifndef _OSG_BEZIERCURVE2D_H_
#define _OSG_BEZIERCURVE2D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

#include "OSGdctptypes.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <deque>

OSG_BEGIN_NAMESPACE

class BezierCurve2D;
typedef std::vector<BezierCurve2D>  bezier2dvector;
typedef std::vector<bezier2dvector> bezier2dmatrix;
typedef std::deque<BezierCurve2D>   bezier2ddeque;
typedef std::vector<bezier2ddeque>  bezier2ddequevector;

class OSG_DRAWABLE_DLLMAPPING BezierCurve2D
{
  protected:
    DCTPVec3dvector control_points; //control points of the curve

    double pointLineDistancewNormal(Vec3d p, Vec2d a, Vec2d n);
    int    minMaxIntersection(DCTPdvector &res, double s, double e);
    int    approximate_sub(DCTPVec2dvector &vertices, double delta);
//  int approximateLength_sub( DCTPVec2dvector &vertices, double delta);
    double homogeniousDistanceSquared(Vec3d v1, Vec3d v2);

    void   CalculateDerivativeCurve();
    void   CalculateNOverIVector(std::vector<double> &NOverI, const unsigned int n) const;
    void   CalculatePolyDerivCurve(BezierCurve2D &DerivativeCurve) const;
    void   CrossMultiply(BezierCurve2D &OtherCurve);
    void   SquareWeight(std::vector<double> &Squared) const;
    double CalculateSupinumSquared() const;
    void   CalculateDifferenceCurve(const BezierCurve2D &Other, BezierCurve2D &Diff) const;
    void   DegreeElevate();
    void   AddNthHermitePoints(Vec3d d0, Vec3d d1);

  public:
    inline  BezierCurve2D(void                  );
    inline  BezierCurve2D(const BezierCurve2D &b);
    inline ~BezierCurve2D(void                  );

    //setup functions
    int setControlPointVector(const DCTPVec3dvector& cps); //ok, acts like its name says

    //query functions
    inline DCTPVec3dvector& getControlPointVector(void);

    //some REAL functionality
    Vec2d computewdeCasteljau(double t, int &error); //compute curve at parameter value t
    Vec2d computeLinearApproximation(double t, int &error); //ok like its name sayz
    int   midPointSubDivision(bezier2dvector &newbeziers); //subdivide curve at midpoint into two new curves
    int   midPointSubDivision(BezierCurve2D &newcurve); //subdivide curve at midpoint into two new curves
    int   subDivision(double t, bezier2dvector &newbeziers); //subdivide curvee at t into two new curves
    int   subDivision(double t, BezierCurve2D &newcurve); //subdivide curvee at t into two new curves
    int   intersection(DCTPdvector &res, Vec2d a, Vec2d b); // calculate intersection of curve with polyline (a, b)
    int   intersection(DCTPdvector &res, double a, bool horiz); // calculate intersection of curve with line (a)
    int   approximate(DCTPVec2dvector &vertices, double delta); // approximate curve linearly with given maximum tolerance
//  int approximateLength( DCTPVec2dvector &vertices, double delta); // approximate curve linearly with given maximum tolerance
    bool reduceDegree(double tol = DCTP_EPS); //try to degree reduce the curve
    // computing degree of a nonrational curve with eps. error
    unsigned int computeNonratApproximationDegree(double eps) const;

    inline void optimizeDegree(void);
};

OSG_END_NAMESPACE

#include "OSGBezierCurve2D.inl"

#endif //BezierCurve2D.h
