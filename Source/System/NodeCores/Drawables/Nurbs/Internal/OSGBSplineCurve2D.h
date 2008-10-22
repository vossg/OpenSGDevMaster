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
#ifndef _OSG_BSPLINECURVE2D_H_
#define _OSG_BSPLINECURVE2D_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>


#include "OSGdctptypes.h"
#include "OSGBSplineBasisFunction.h"
#include "OSGBezierCurve2D.h"

OSG_BEGIN_NAMESPACE

class OSG_DRAWABLE_DLLMAPPING BSplineCurve2D
{
  protected:
    DCTPVec3dvector      control_points; //control points of the curve
    int                  dimension; //dimension of the B-spline (degree)
    BSplineBasisFunction basis_function; //placeholder for the knots & facility to easily compute 'em

    //file format constants
    static const char ff_const_1[];
    static const char ff_const_2[];
    static const char ff_const_3[];
    static const char ff_const_4[];

    int CheckKnotPoints(const DCTPdvector& knots, int dim); //check whether knots has a right format

    // delete a knot which is on a 'bezier' curve, i.e. [0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3] -> [0 0 0 0 1 1 1 2 2 2 3 3 3 3]
    // must have a multiplicity of (at least) dimension + 1, and its associated control point also must have a multiplicity of (at least) 2.
    int deleteBezierKnot(double k);


  public:
    inline  BSplineCurve2D(void);
    inline ~BSplineCurve2D(void);

    //setup functions
    // FIXME: the setup interface is very rigid, maybe it should allow knot & dimension setting alone, eg. to resize dimension, etc
    int  setKnotsAndDimension(const DCTPdvector& knots, int dim); //ok, acts like its name says
    void setControlPointVector(const DCTPVec3dvector &cps); //set control point vector

    //query functions
    inline DCTPdvector&     getKnotVector        (void); //return knot points of basis functions
    inline DCTPVec3dvector& getControlPointVector(void);
    inline int              getDimension         (void);

    void getParameterInterval(double &minpar, double &maxpar); //returns minimal and maximal parameter value

    //I/O support - FIXME: read( char *fname ) outta be supported , etc
    int read(std::istream &infile);
    int write(std::ostream &outfile);

    //some REAL functionality
    Vec2d compute(double t, int &error); // compute curve at parameter value t
    int   insertKnot(double k); // insert a new knot (recalculates control points and knotvector)

    // convert curve into Bezier form.
    int makeBezier(bezier2dvector &beziers, DCTPdvector &pars);
};

OSG_END_NAMESPACE

#include <OSGBSplineCurve2D.inl>

#endif //BSplineCurve2D.h
