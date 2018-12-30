/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include "boost/tuple/tuple_comparison.hpp"

#include "OSGConfig.h"
#include "OSGSimpleCurve.h"

OSG_BEGIN_NAMESPACE

CubicBezierCurve::CubicBezierCurve(
    const OSG::Pnt3f& p0, 
    const OSG::Pnt3f& p1, 
    const OSG::Pnt3f& p2, 
    const OSG::Pnt3f& p3)
{
    p[0] = p0; p[1] = p1; p[2] = p2; p[3] = p3;
}

CubicBezierCurve::CubicBezierCurve(const CubicBezierCurve& rhs)
{
    p[0] = rhs.p[0]; p[1] = rhs.p[1]; p[2] = rhs.p[2]; p[3] = rhs.p[3];
}

OSG::Vec3f CubicBezierCurve::getBinormal(OSG::Real32 t) const
{
    OSG::Vec3f binormal = fst_derivative(t);
    binormal.crossThis(sec_derivative(t));
    binormal.normalize();

    while (OSG::osgAbs(binormal.length() - 1.f) >= OSG::Eps)
    {
        if (t + OSG::Eps <= 1.f)
            t += OSG::Eps;
        else if (t - OSG::Eps >= 0.f)
            t -= OSG::Eps;
        else
            OSG_ASSERT(false);

        binormal = fst_derivative(t);
        binormal.crossThis(sec_derivative(t));
        binormal.normalize();
    }

    return binormal;
}

OSG::Matrix CubicBezierCurve::getFrame(OSG::Real32 t, bool position_only) const
{
    OSG::Matrix mat;
    mat.identity();

    OSG::Vec3f P = (*this)(t).subZero();

    if (position_only)
    {
        mat.setTranslate(P);
    }
    else
    {
        OSG::Vec3f T = getTangent(t);
        OSG::Vec3f N = getNormal(t);
        OSG::Vec3f B = getBinormal(t);
    
#if 0
        OSG::Real32 lT = T.length();
        OSG::Real32 lN = N.length();
        OSG::Real32 lB = B.length();

        OSG::Real32 v1 = T.dot(N);
        OSG::Real32 v2 = T.dot(B);
        OSG::Real32 v3 = N.dot(B);
#endif

        OSG_ASSERT(OSG::osgAbs(T.length() - 1.f) < OSG::Eps);
        OSG_ASSERT(OSG::osgAbs(N.length() - 1.f) < OSG::Eps);
        OSG_ASSERT(OSG::osgAbs(B.length() - 1.f) < OSG::Eps);

        mat.setValue(T,N,B,P);
    }

    return mat;
}

OSG::Real32 CubicBezierCurve::getLength(OSG::UInt32 numSeg) const
{
    OSG_ASSERT(numSeg >= 2);

    OSG::Real32 d = 1.f / numSeg;
    OSG::Real32 t = d;
    OSG::Real32 l = 0.f;

    OSG::Pnt3f p0 = operator()(0.f);

    while (t <= 1.f)
    {
        OSG::Pnt3f p1 = operator()(t);

        l += (p1 - p0).length();
        t += d;
    }

    return l;
}

OSG::Vec3f CubicBezierCurve::fst_derivative(OSG::Real32 t) const
{
    OSG::Vec3f v10 = p[1] - p[0];
    OSG::Vec3f v21 = p[2] - p[1];
    OSG::Vec3f v32 = p[3] - p[2];

    OSG::Real32    e = 1.f - t;
    OSG::Real32 sq_e = e * e;
    OSG::Real32 sq_t = t * t;

    return 3.f * sq_e * v10 + 6.f * e * t * v21 + 3.f * sq_t * v32;
}

OSG::Vec3f CubicBezierCurve::sec_derivative(OSG::Real32 t) const
{
    OSG::Vec3f v210 = p[2] - 2.f * p[1] + p[0].subZero();
    OSG::Vec3f v321 = p[3] - 2.f * p[2] + p[1].subZero();

    OSG::Real32 e = 1.f - t;

    return 6.f * e * v210 + 6.f * t * v321;
}

OSG::Vec3f CubicBezierCurve::thr_devivative(OSG::Real32 t) const
{
    OSG::Vec3f v21 = p[2] - p[1];
    OSG::Vec3f v30 = p[3] - p[0];

    return -18.f * v21 + 6.f * v30;
}


SmoothCubicBezierSpline::SmoothCubicBezierSpline(const std::vector<OSG::Pnt3f>& vKnots)
: knots(vKnots)
, intervals()
, curves()
{
    OSG_ASSERT(knots.size() > 3);

    points_t p1, p2;

    calc_ctrl_pnts(p1, p2);
    
    std::size_t n = knots.size() - 1;

    std::vector<OSG::Real32> lengths(n);
    OSG::Real32 L = 0.f;

    for (std::size_t i = 0; i < n; ++i)
    {
        curves.push_back(CubicBezierCurve(knots[i], p1[i], p2[i], knots[i+1]));

        lengths[i] = curves[i].getLength();
        L += lengths[i];
    }

    OSG_ASSERT(L > 0.f);

    OSG::Real32 d = 1.f / L;

    intervals.resize(n);

    intervals[0] = d * lengths[0];

    for (std::size_t i = 1; i < n-1; ++i)
    {
        intervals[i] = intervals[i-1] + d * lengths[i];
    }

    intervals[n-1] = 1.f;
}

SmoothCubicBezierSpline::SmoothCubicBezierSpline(const SmoothCubicBezierSpline& rhs)
: knots(rhs.knots)
, intervals(rhs.intervals)
, curves(rhs.curves)
{
}

SmoothCubicBezierSpline& SmoothCubicBezierSpline::operator=(const SmoothCubicBezierSpline& rhs)
{
    if (this != &rhs)
    {
        knots     = rhs.knots;
        intervals = rhs.intervals;
        curves    = rhs.curves;
    }
    return *this;
}

OSG::Real32 SmoothCubicBezierSpline::getLength(OSG::UInt32 numSeg) const
{
    OSG::Real32 l = 0.f;
    BOOST_FOREACH(const CubicBezierCurve& c, curves)
    {
        l += c.getLength(numSeg);
    }
    return l;
}

void SmoothCubicBezierSpline::calc_ctrl_pnts(points_t& p1, points_t& p2) const
{
    namespace tp = boost::tuples;
    typedef tp::tuple<OSG::Real32, OSG::Real32, OSG::Real32> tuple_t;
    typedef std::vector<tuple_t> tuples_t;

    std::size_t n = knots.size()-1;

    p1.resize(n);
    p2.resize(n);

    tuples_t a(n), b(n), c(n), d(n);

    a[0] = tp::make_tuple(0.f, 0.f, 0.f);
    b[0] = tp::make_tuple(2.f, 2.f, 2.f);
    c[0] = tp::make_tuple(1.f, 1.f, 1.f);
    d[0] = tp::make_tuple(
        knots[0].x() + 2.f * knots[1].x(),
        knots[0].y() + 2.f * knots[1].y(),
        knots[0].z() + 2.f * knots[1].z());

    for (std::size_t i = 1; i < n-1; ++i)
    {
        a[i] = tp::make_tuple(1.f, 1.f, 1.f);
        b[i] = tp::make_tuple(4.f, 4.f, 4.f);
        c[i] = tp::make_tuple(1.f, 1.f, 1.f);
        d[i] = tp::make_tuple(
            4.f * knots[i].x() + 2.f * knots[i+1].x(),
            4.f * knots[i].y() + 2.f * knots[i+1].y(),
            4.f * knots[i].z() + 2.f * knots[i+1].z());
    }

    a[n-1] = tp::make_tuple(2.f, 2.f, 2.f);
    b[n-1] = tp::make_tuple(7.f, 7.f, 7.f);
    c[n-1] = tp::make_tuple(0.f, 0.f, 0.f);
    d[n-1] = tp::make_tuple(
        8.f * knots[n-1].x() + 2.f * knots[n].x(),
        8.f * knots[n-1].y() + 2.f * knots[n].y(),
        8.f * knots[n-1].z() + 2.f * knots[n].z());

    for (std::size_t i = 1; i < n; ++i)
    {
        tuple_t m = tp::make_tuple(
            a[i].get<0>() / b[i-1].get<0>(),
            a[i].get<1>() / b[i-1].get<1>(),
            a[i].get<2>() / b[i-1].get<2>());

            b[i] = tp::make_tuple(
                b[i].get<0>() - m.get<0>() * c[i-1].get<0>(),
                b[i].get<1>() - m.get<1>() * c[i-1].get<1>(),
                b[i].get<2>() - m.get<2>() * c[i-1].get<2>());

            d[i] = tp::make_tuple(
                d[i].get<0>() - m.get<0>() * d[i-1].get<0>(),
                d[i].get<1>() - m.get<1>() * d[i-1].get<1>(),
                d[i].get<2>() - m.get<2>() * d[i-1].get<2>());
    }

    p1[n-1].setValues(
        d[n-1].get<0>() / b[n-1].get<0>(),
        d[n-1].get<1>() / b[n-1].get<1>(),
        d[n-1].get<2>() / b[n-1].get<2>());

    for (long long i = n-2; i >= 0; --i)
    {
        p1[i].setValues(
            (d[i].get<0>() - c[i].get<0>() * p1[i+1].x()) / b[i].get<0>(),
            (d[i].get<1>() - c[i].get<1>() * p1[i+1].y()) / b[i].get<1>(),
            (d[i].get<2>() - c[i].get<2>() * p1[i+1].z()) / b[i].get<2>());
    }

    for (std::size_t i = 0; i < n-1; ++i)
    {
        p2[i].setValues(
            2.f * knots[i+1].x() - p1[i+1].x(),
            2.f * knots[i+1].y() - p1[i+1].y(),
            2.f * knots[i+1].z() - p1[i+1].z());
    }

    p2[n-1].setValues(
            0.5f * knots[n].x() - p1[n-1].x(),
            0.5f * knots[n].y() - p1[n-1].y(),
            0.5f * knots[n].z() - p1[n-1].z());
}

OSG_END_NAMESPACE
