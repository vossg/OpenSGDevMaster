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

//construction & destruction
inline BezierCurve2D::BezierCurve2D(void)
    : control_points()
{
}

inline BezierCurve2D::BezierCurve2D(BezierCurve2D const &b) :
    control_points(b.control_points)
{
    // nothing to do
}

inline BezierCurve2D::~BezierCurve2D(void)
{
    // nothing to do
}

inline DCTPVec3dvector& BezierCurve2D::getControlPointVector(void)
{
    return control_points;
}

inline void BezierCurve2D::optimizeDegree(void)
{
//    std::cerr << "reduce degree (2d): " << control_points.size( ) - 1;
    while(reduceDegree())
    {
    }
//    std::cerr << " -> " << control_points.size( ) - 1 << std::endl;
}

OSG_END_NAMESPACE
