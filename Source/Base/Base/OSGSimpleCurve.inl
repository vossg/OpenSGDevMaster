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

inline CubicBezierCurve& CubicBezierCurve::operator=(const CubicBezierCurve& rhs)
{
    if (this != &rhs)
    {
        p[0] = rhs.p[0]; p[1] = rhs.p[1]; p[2] = rhs.p[2]; p[3] = rhs.p[3];
    }
    return *this;
}

inline OSG::Pnt3f CubicBezierCurve::operator()(OSG::Real32 t) const
{
    OSG_ASSERT(0.f <= t && t <= 1.f);

    OSG::Real32    e = 1.f - t;
    OSG::Real32 sq_e = e * e;
    OSG::Real32 sq_t = t * t;

    return      e * sq_e * p[0]
        + 3.f * t * sq_e * p[1].subZero()
        + 3.f * sq_t * e * p[2].subZero()
              + t * sq_t * p[3].subZero();
}

inline OSG::Vec3f CubicBezierCurve::getTangent(OSG::Real32 t) const
{
    OSG::Vec3f tangent = fst_derivative(t);
    tangent.normalize();

    return tangent;
}

inline OSG::Vec3f CubicBezierCurve::getNormal(OSG::Real32 t) const
{
    OSG::Vec3f normal = getBinormal(t);
    normal.crossThis(getTangent(t));
    normal.normalize();

    return normal;
}

inline OSG::Pnt3f SmoothCubicBezierSpline::operator()(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx](t_(t, idx));
}

inline OSG::Vec3f SmoothCubicBezierSpline::getTangent(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx].getTangent(t_(t, idx));
}

inline OSG::Vec3f SmoothCubicBezierSpline::getNormal(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx].getNormal(t_(t, idx));
}

inline OSG::Vec3f SmoothCubicBezierSpline::getBinormal(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx].getBinormal(t_(t, idx));
}

inline OSG::Matrix SmoothCubicBezierSpline::getFrame(OSG::Real32 t, bool position_only) const
{
    std::size_t idx = index(t);
    return curves[idx].getFrame(t_(t, idx), position_only);
}

inline std::size_t SmoothCubicBezierSpline::index(OSG::Real32 t) const
{
    OSG_ASSERT(0.f <= t && t <= 1.f);

    std::vector<OSG::Real32>::const_iterator iter = std::lower_bound(intervals.begin(), intervals.end(), t);
    std::size_t r = iter - intervals.begin();
    return r;
}

inline OSG::Real32 SmoothCubicBezierSpline::t_(OSG::Real32 t, std::size_t idx) const
{
    OSG_ASSERT(idx < intervals.size());

    OSG::Real32 t0 = 0.f;
    OSG::Real32 t1 = 1.f;

    if (idx > 0) 
        t0 = intervals[idx-1];

    t1 = intervals[idx];

    OSG::Real32 r = (t - t0) / (t1 - t0);

    return r;
}

OSG_END_NAMESPACE

