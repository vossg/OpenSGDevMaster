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
#ifndef _OSG_BSPLINETENSORSURFACE_H_
#define _OSG_BSPLINETENSORSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>
#include <OSGVector.h>


#include "OSGdctptypes.h"
#include "OSGBSplineBasisFunction.h"
#include "OSGBezierTensorSurface.h"

OSG_BEGIN_NAMESPACE

class OSG_DRAWABLE_DLLMAPPING BSplineTensorSurface
{
  protected:
    DCTPVec4dmatrix      control_points; //control points of the surface
    int                  dimension_u, dimension_v; //dimension of the surface in u and v directions
    BSplineBasisFunction basis_function_u; //placeholder for the u knots & facility to easily compute 'em
    BSplineBasisFunction basis_function_v; //placeholder for the v knots & facility to easily compute 'em

    //file format constants
    static const char ff_const_1[];
    static const char ff_const_2[];
    static const char ff_const_3[];
    static const char ff_const_4[];
    static const char ff_const_5[];

    int CheckKnotPoints(const DCTPdvector& knots, int dim); //check whether knots has a right format
    // delete a knot which is on a 'bezier' curve, i.e. [0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3] -> [0 0 0 0 1 1 1 2 2 2 3 3 3 3]
    // must have a multiplicity of (at least) dimension + 1, and its associated control point also must have a multiplicity of (at least) 2.
    int deleteBezierKnot_U(double k);
    int deleteBezierKnot_V(double k);

    void RatSurfaceDerivs(DCTPVec4dmatrix &rclHomDerivs, DCTPVec3dmatrix &rclEuclidDerivs);

  public:
    inline  BSplineTensorSurface(void);
    inline ~BSplineTensorSurface(void);

    //setup functions
    // FIXME: the setup interface is very rigid, maybe it should allow knot & dimension setting alone, eg. to resize dimension, etc
    // FIXME: and insertion of knots
    int  setKnotsAndDimension(const DCTPdvector& knots_u, int dim_u, const DCTPdvector& knots_v, int dim_v); //ok, acts like its name says
    void setControlPointMatrix(const DCTPVec4dmatrix &cps); //set control point vector

    //query functions
    inline DCTPdvector      &getKnotVector_U      (void);
    inline DCTPdvector      &getKnotVector_V      (void);
    inline DCTPVec4dmatrix  &getControlPointMatrix(void);
    inline int               getDimension_U       (void);
    inline int               getDimension_V       (void);

    void getParameterInterval_U(double &minpar, double &maxpar); //returns minimal and maximal parameter value
    void getParameterInterval_V(double &minpar, double &maxpar); //returns minimal and maximal parameter value

    inline BSplineBasisFunction &getBasisFunctionU(void);
    inline BSplineBasisFunction &getBasisFunctionV(void);

    //I/O support - FIXME: read( char *fname ) outta be supported , etc
    int read(std::istream &infile);
    int write(std::ostream &outfile);

    //some REAL functionality
    Vec3d compute(Vec2d uv, int &error); //compute curve at parameter value t
    Vec4d compute4D(Vec2d uv, int &error); //compute curve at parameter value t
    Vec3d computeNormal(Vec2d clUV, int &riError, Vec3d &rclPos); // compute normal at uv
    Vec3f computeNormal(Vec2d clUV, int &riError, Pnt3f &rclPos); // compute normal at uv
    Vec3d computeNormalTex(Vec2d &rclUV,
                           int &riError, Vec3d &rclPos, Vec2d &rclTexCoord,
                           const std::vector<std::vector<Pnt2f> > *cpvvclTexCP);    // compute normal at uv
    void compute(std::vector<Vec2d> &rvclUV, std::vector<Pnt3f> &rvclPos);     //compute curve at parameter value uv
    void computeNormal(std::vector<Vec2d> &rvclUV,
                       std::vector<Pnt3f> &rvclPos,
                       std::vector<Vec3f> &rvclNorm);   // compute normal at uv
    void computeNormalforTrimming(std::vector<Vec2d> &rvclUV,
                                  std::vector<Vec3d> &rvclNorm,
                                  std::vector<Vec3d> *pvclPos = NULL);   // compute normal at uv

    void computeNormalTex(std::vector<Vec2d> &                    rvclUV,
                          std::vector<Pnt3f> &                    rvclPos,
                          std::vector<Vec3f> &                    rvclNorm,
                          std::vector<Pnt2f> &                    rvclTexCoord,
                          const std::vector<std::vector<Pnt2f> > *cpvvclTexCP);    // compute normal at uv
    void computeTex(std::vector<Vec2d> &                    rvclUV,
                    std::vector<Pnt3f> &                    rvclPos,
                    std::vector<Pnt2f> &                    rvclTexCoord,
                    const std::vector<std::vector<Vec2d> > *cpvvclTexCP);
    void computeTexforTrimming(std::vector<Vec2d> &                    rvclUV,
                               std::vector<Vec2d> &                    rvclTexCoord,
                               const std::vector<std::vector<Vec2d> > *cpvvclTexCP);

    int insertKnot_U(double k); // insert a new knot into U (recalculates control points and u knotvector)
    int insertKnot_V(double k); // insert a new knot into V (recalculates control points and v knotvector)

    // convert curve into Bezier form.
    int makeBezier(beziersurfacematrix &beziers, DCTPdvector &upars, DCTPdvector &vpars);
    int getSplitParams(DCTPdvector &upars, DCTPdvector &vpars);

    //subdivide surface at midpoint into 4 bspline surfaces
    int midPointSubDivision(std::vector<std::vector<BSplineTensorSurface> > &rvvcl_newbspline);
    int midPointSubDivisionU(std::vector<BSplineTensorSurface> &rvcl_newbspline);
    int midPointSubDivisionV(std::vector<BSplineTensorSurface> &rvcl_newbspline);
    int subDivisionU(std::vector<BSplineTensorSurface> &rvcl_newbspline, double dSplit);
    int subDivisionV(std::vector<BSplineTensorSurface> &rvcl_newbspline, double dSplit);

  protected:
    void correctDers(const Vec2d cclUV, const Vec3d cclPos, Vec3d &rclDU, Vec3d &rclDV);

};

OSG_END_NAMESPACE

#include <OSGBSplineTensorSurface.inl>

#endif //BSplineTensorSurface.h
