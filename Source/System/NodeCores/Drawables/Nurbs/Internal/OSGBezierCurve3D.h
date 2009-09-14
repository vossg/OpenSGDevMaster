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
#ifndef _OSG_BEZIERCURVE3D_H_
#define _OSG_BEZIERCURVE3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

//#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <deque>
#include "OSGdctptypes.h"

OSG_BEGIN_NAMESPACE

class BezierCurve3D;

typedef std::vector<BezierCurve3D>  bezier3dvector;
typedef std::vector<bezier3dvector> bezier3dmatrix;
typedef std::deque<BezierCurve3D>   bezier3ddeque;
typedef std::vector<bezier3ddeque>  bezier3ddequevector;

class OSG_DRAWABLE_DLLMAPPING BezierCurve3D
{
  protected:
    int approximate_sub(std::vector<double> &vertices, double delta, double min, double max, unsigned char strategy);

    DCTPVec4dvector control_points; //control points of the curve

//     static std::vector<std::vector<std::vector<double> > > m_svvvdCreateMatrix;
    Vec4d computewdeCasteljau4D(double t, int &error); //compute curve at parameter value t

  public:
    static const unsigned char SUBDIVISION           = 1;
    static const unsigned char MIDPOINT_SUBDIVISION  = 0;
    static const unsigned char ARBITRARY_SUBDIVISION = 1;

    static const unsigned char DISTANCE       = 2;
    static const unsigned char POINT_DISTANCE = 0;
    static const unsigned char LINE_DISTANCE  = 2;
    inline  BezierCurve3D(void);
    inline ~BezierCurve3D(void);

    //setup functions
    int setControlPointVector(const DCTPVec4dvector& cps); //ok, acts like its name says

    //query functions
    inline DCTPVec4dvector& getControlPointVector(void);

    //some REAL functionality
    Vec3d computewdeCasteljau(double t, int &error); //compute curve at parameter value t
    Vec3d computeLinearApproximation(double t, int &error); //ok like its name sayz
    int   midPointSubDivision(bezier3dvector &newbeziers); //subdivide curve at midpoint into two new curves
    int   midPointSubDivision(BezierCurve3D &newcurve); //subdivide curve at midpoint into two new curves
    int   subDivision(double t, bezier3dvector &newbeziers); //subdivide curvee at t into two new curves
    int   subDivision(double t, BezierCurve3D &newcurve);
    int   approximate(std::vector<double> &vertices, double delta, unsigned char strategy = MIDPOINT_SUBDIVISION | POINT_DISTANCE); // approximate curve linearly with given maximum tolerance
    int   createCurve(DCTPVec4dvector &points); // generate a (rational) bezier curve through these points
    bool  reduceDegree(double tol = DCTP_EPS);

    inline void optimizeDegree(void);
};

OSG_END_NAMESPACE

#include "OSGBezierCurve3D.inl"

#endif //BezierCurve3D.h
