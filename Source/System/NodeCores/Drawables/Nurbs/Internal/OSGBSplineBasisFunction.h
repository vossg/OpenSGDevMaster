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
#ifndef _OSG_BSPLINEBASISFUNCTION_H_
#define _OSG_BSPLINEBASISFUNCTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>


#include "OSGdctptypes.h"
#include <fstream>
#include <string>
#include <iomanip>

OSG_BEGIN_NAMESPACE

class OSG_DRAWABLE_DLLMAPPING BSplineBasisFunction
{

  public:
    BSplineBasisFunction(); //sets invalid knots, you must set them later
    ~BSplineBasisFunction() {}

    //setup methods
    int setKnotVector(const DCTPdvector &k); //sets knot vector, preventing its increasing feature

    //query methods
    DCTPdvector& getKnotVector()
    {
        return knots;
    };                                            //just take a guess
    void getParameterInterval(double &minpar, double &maxpar); //returns minimal and maximal parameter value

    //I/O support - FIXME: read( char *fname ) outta be supported , etc
    int read(std::istream &infile);
    int write(std::ostream &outfile);

    //some REAL funcionality
    //returns < 0 on error, otherwise the (original) span index into which the knot is inserted
    int    insertKnot(double k); //insert a new knot vector at it's correct point
    double compute(double u, int i, int p); //returns value at u
    int    computeAllNonzero(double u, int p, double *&rpd_n); // computes all nonzero basis functions at u
    int    computeDersBasisFuns(double dU, int iP, double **&rppdDers, int iDepth); // computes all nonzero derivates at u

  protected:
    int CheckKnotPoints(const DCTPdvector &k);
    int findSpan(double &u); //gives the knotspan u is in
    DCTPdvector knots; //the knot vector, see dctptypes.h
//file format constants
    static const char ff_const_1[];
    static const char ff_const_2[];
    static const char ff_const_3[];
};

OSG_END_NAMESPACE

#endif /* _OSG_BSPLINEBASISFUNCTION_H_ */
