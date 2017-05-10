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

#include <cmath>
#include <cassert>

#include "OSGConfig.h"
#include "OSGPolygon.h"

#include "OSGLineSegment.h"
#include "OSGPlane.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Polygon
     A polygon consiting of arbitrarily points.
*/


/*-------------------------- constructor ----------------------------------*/

Polygon::Polygon(void)
: _vertices()
, _normal()
{
}

Polygon::Polygon(const  Polygon& rhs)
: _vertices(rhs._vertices)
, _normal(rhs._normal)
{
}

Polygon::Polygon(
    const Pnt3f& p0,
    const Pnt3f& p1,
    const Pnt3f& p2)
: _vertices()
, _normal()
{
    addVertex(p0);
    addVertex(p1);
    addVertex(p2);
}

Polygon::Polygon(
    const Pnt3f& p0,
    const Pnt3f& p1,
    const Pnt3f& p2,
    const Pnt3f& p3)
: _vertices()
, _normal()
{
    addVertex(p0);
    addVertex(p1);
    addVertex(p2);
    addVertex(p3);
}

Polygon::~Polygon()
{
}

Polygon& Polygon::operator=(const Polygon& rhs)
{
    if (&rhs == this)
        return *this;

    _vertices = rhs._vertices;
    _normal   = rhs._normal;

    return *this;
}

void Polygon::addUniqueVertex(const Pnt3f& vertex, Real32 tolerance)
{
    VecVerticesT::const_iterator iter = _vertices.begin();
    VecVerticesT::const_iterator end  = _vertices.end();

    for(; iter != end; ++iter)
    {
        const Pnt3f& p = *iter;
        if (p.equals(vertex, tolerance))
            return;
    }

    addVertex(vertex);
}

void Polygon::setNormal(const Vec3f& normal)
{
    if (normal.squareLength() == 0.f)
        return;

    _normal = normal;
    _normal.normalize();
}

void Polygon::reverseVertices()
{
    if (_vertices.size() > 2)
        std::reverse(_vertices.begin(), _vertices.end());
}

void Polygon::orderVertices(VertexOrder order)
{
    for (std::size_t i = 1, sz = _vertices.size(); i < sz; ++i)
    {
        for (std::size_t j = i + 1; j < sz; ++j)
        {
            Vec3f v_i = _vertices[i]-_vertices[0];
            Vec3f v_j = _vertices[j]-_vertices[0];

            Vec3f v_k = v_i.cross(v_j);
            if (order == ccw)
            {
                if (v_k.dot(_normal) < 0.f)
                    std::swap(_vertices[i],_vertices[j]);
            }
            else
            {
                if (v_k.dot(_normal) > 0.f)
                    std::swap(_vertices[i],_vertices[j]);
            }
        }
    }
}

void Polygon::clip(const Plane& plane, VecVerticesT& intersectionPnts)
{
    std::size_t sz = _vertices.size();

    if (sz < 3) return;

    VecVerticesT vertices;

    for (std::size_t i = 0; i < sz; ++i)
    {
        std::size_t j = (i + 1) % sz;

        bool currClip = plane.isInHalfSpace(_vertices[i]);
        bool nextClip = plane.isInHalfSpace(_vertices[j]);

        // the segment is completetly discarded
        if (currClip && nextClip)
            continue;

        LineSegment segment(_vertices[i], _vertices[j]);

        if (currClip || nextClip)
        {
            Pnt3f pnt;
            if (plane.intersect(segment, pnt))
            {
                vertices.push_back(pnt);
                intersectionPnts.push_back(pnt);
            }
        }

        if (nextClip)
            continue;

        vertices.push_back(_vertices[j]);
    }

    _vertices.clear();

    if (vertices.size() > 2)
        _vertices = vertices;
}

OSG_END_NAMESPACE
