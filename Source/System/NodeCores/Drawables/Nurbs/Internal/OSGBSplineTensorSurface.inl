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

OSG_BEGIN_NAMESPACE

inline BSplineTensorSurface::BSplineTensorSurface(void) :
    dimension_u   (-1),     //sets invalid value
    dimension_v   (-1),     //sets invalid value
    control_points()
{
    // nothing to do
}

inline BSplineTensorSurface::~BSplineTensorSurface(void)
{
    // nothing to do
}

/*! Returns knots of the basis function in u direction
 */
inline DCTPdvector &BSplineTensorSurface::getKnotVector_U(void)
{
    return basis_function_u.getKnotVector();
}

inline DCTPdvector &BSplineTensorSurface::getKnotVector_V(void)
{
    return basis_function_v.getKnotVector();
}

inline DCTPVec4dmatrix &BSplineTensorSurface::getControlPointMatrix(void)
{
    return control_points;
}

inline int BSplineTensorSurface::getDimension_U(void)
{
    return dimension_u;
}

inline int BSplineTensorSurface::getDimension_V(void)
{
    return dimension_v;
}

inline BSplineBasisFunction &BSplineTensorSurface::getBasisFunctionU(void)
{
    return basis_function_u;
}

inline BSplineBasisFunction &BSplineTensorSurface::getBasisFunctionV(void)
{
    return basis_function_v;
}

OSG_END_NAMESPACE
