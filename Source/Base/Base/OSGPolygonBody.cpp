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

#ifdef OSG_WITH_QHULL
#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <libqhullcpp/RboxPoints.h>
#endif // OSG_WITH_QHULL

#include "OSGConfig.h"
#include "OSGPolygonBody.h"

#include "OSGBoxVolume.h"
#include "OSGFrustumVolume.h"

#include "OSGLineSegment.h"
#include "OSGPlane.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::PolygonBody
*/


/*-------------------------- constructor ----------------------------------*/

PolygonBody::PolygonBody()
: _vertices()
, _polygons()
{
}

PolygonBody::~PolygonBody()
{
    clear();
}

void PolygonBody::add(const VecVerticesT& vertices, const Vec3f& normal)
{
    if (vertices.size() < 3)
        return;

    Polygon* polygon = new Polygon();

    for (std::size_t i = 0; i < vertices.size(); ++i)
        polygon->addUniqueVertex(vertices[i]);

    if (polygon->getNumVertices() < 3)
    {
        delete polygon;
        return;
    }

    polygon->setNormal(normal);
    polygon->orderVertices();

    _polygons.push_back(polygon);
}

void PolygonBody::add(const FrustumVolume& frustum)
{
    Pnt3f nlt, nlb, nrt, nrb, flt, flb, frt, frb;

    frustum.getCorners(nlt, nlb, nrt, nrb, flt, flb, frt, frb);

    add(new Polygon(nlb, nrb, nrt, nlt));   // near polygon ccw
    add(new Polygon(flt, frt, frb, flb));   // far polygon ccw
    add(new Polygon(nlb, nlt, flt, flb));   // left polygon ccw
    add(new Polygon(nrb, frb, frt, nrt));   // right polygon ccw
    add(new Polygon(flb, frb, nrb, nlb));   // bottom polygon ccw
    add(new Polygon(frt, flt, nlt, nrt));   // top polygon ccw
}

void PolygonBody::clip(const Plane& plane)
{
    VecVerticesT isecPnts;

    VecPolygonsT::iterator iter = _polygons.begin();

    for (; iter != _polygons.end(); )
    {
        Polygon* polygon = *iter;
        polygon->clip(plane, isecPnts);

        // all vertices were clipped
        if (polygon->getNumVertices() == 0)
        {
            delete polygon;
            iter = _polygons.erase(iter);
        }
        else
            iter++;
    }

    // add closing polygon
    if (isecPnts.size())
        add(isecPnts, plane.getNormal());
}

void PolygonBody::clip(const BoxVolume& boundingBox)
{
    clip(boundingBox.getPlane(BoxVolume::PLANE_FAR));
    clip(boundingBox.getPlane(BoxVolume::PLANE_NEAR));
    clip(boundingBox.getPlane(BoxVolume::PLANE_BOTTOM));
    clip(boundingBox.getPlane(BoxVolume::PLANE_TOP));
    clip(boundingBox.getPlane(BoxVolume::PLANE_LEFT));
    clip(boundingBox.getPlane(BoxVolume::PLANE_RIGHT));
}

void PolygonBody::clip(const FrustumVolume& frustum)
{
    for (UInt32 i = 0; i < FrustumVolume::PLANE_COUNT; ++i)
    {
        const Plane& plane = frustum.getPlane(static_cast<FrustumVolume::FrustumPlane>(i));
        clip( Plane(plane.getNormal(), plane.getDistanceFromOrigin()) );
    }
}

void PolygonBody::extrude(const Vec3f& direction, const BoxVolume& boundingBox)
{
    createUniqueVertices();

    const Pnt3f& maximum = boundingBox.getMax();
    const Pnt3f& minimum = boundingBox.getMin();

    std::size_t size = getNumVertices();

    for (std::size_t i = 0; i < size; ++i)
        intersect(LineSegment(_vertices[i], direction), minimum, maximum, _vertices);

    // only for debugging
    extrudePolygons(direction, boundingBox);
}

void PolygonBody::extrudePolygons(const Vec3f& direction, const BoxVolume& boundingBox)
{
    Polygon* topPoly = new Polygon();

    const Pnt3f& maximum = boundingBox.getMax();
    const Pnt3f& minimum = boundingBox.getMin();

    for (std::size_t i = 0; i < _polygons.size(); ++i)
    {
        VecVerticesT  uniqueVertices;
        VecVerticesT& vertices = _polygons[i]->getVertices();

        for (std::size_t j = 0, sz = vertices.size(); j < sz; ++j)
        {
            std::size_t oldSz = vertices.size();

            intersect(LineSegment(vertices[j], direction), minimum, maximum, vertices);

            std::size_t newSz = vertices.size();

            if (newSz > oldSz)
                topPoly->addVertex(vertices[newSz-1]);
        }
    }

    _polygons.push_back(topPoly);
}

void PolygonBody::createHull(const Pnt3f& point)
{
    removeVisiblePolygons(point);

    VecLineSegmentsT uniqueEdges;

    // build array with unique edges of all polygons
    for (std::size_t i = 0; i < _polygons.size(); ++i)
    {
        std::size_t size = _polygons[i]->getNumVertices();
        const VecVerticesT& vertices = _polygons[i]->getVertices();

        // add edge from last to first
        addUniqueEdge(uniqueEdges, LineSegment(vertices[size-1], vertices[0] - vertices[size-1]));

        // iterate over the rest
        for (std::size_t j = 0; j < size-1; ++j)
            addUniqueEdge(uniqueEdges, LineSegment(vertices[j], vertices[j+1] - vertices[j]));
    }

    // build a triangle with the point and each of the unique edges
    for (std::size_t i = 0; i < uniqueEdges.size(); ++i)
    {
        LineSegment* line = uniqueEdges[i];

        add(new Polygon(line->getStartPoint(), line->getEndPoint(), point));

        delete uniqueEdges[i];
    }
}

void PolygonBody::createConvexHull(const Pnt3f& point)
{
    createUniqueVertices();

    _vertices.push_back(point);

    createConvexHull(_vertices);
}

void PolygonBody::createConvexHull()
{
    createUniqueVertices();

    createConvexHull(_vertices);
}

void PolygonBody::createUniqueVertices(Real32 tolerance)
{
    _vertices.clear();

    for (std::size_t i = 0; i < _polygons.size(); ++i)
    {
        std::size_t size = _polygons[i]->getNumVertices();
        const VecVerticesT& vertices = _polygons[i]->getVertices();

        for (std::size_t j = 0; j < size; ++j)
            addUniqueVertex(vertices[j], tolerance);
    }
}

void PolygonBody::clear()
{
    for (std::size_t i = 0; i < _polygons.size(); ++i)
        delete _polygons[i];

    _polygons.clear();
    _vertices.clear();
}

void PolygonBody::addUniqueEdge(VecLineSegmentsT& outEdgeList, const LineSegment& line) const
{
    bool addEdge = true;

    for (std::size_t i = 0; i < outEdgeList.size() && addEdge; ++i)
        addEdge = !(outEdgeList[i]->equals(line));

    if (addEdge)
        outEdgeList.push_back(new LineSegment(line.getStartPoint(), line.getDirection()));
}

void PolygonBody::addUniqueVertex(const Pnt3f& vertex, Real32 tolerance)
{
    bool addVertex = true;

    for (std::size_t i = 0; i < _vertices.size() && addVertex; ++i)
        addVertex = !(_vertices[i].equals(vertex, tolerance));

    if (addVertex)
        _vertices.push_back(vertex);
}

void PolygonBody::removeVisiblePolygons(const Pnt3f& point)
{
    for (VecPolygonsT::iterator iter = _polygons.begin(); iter != _polygons.end();)
    {
        Polygon* polygon = *iter;
        // delete degenerated polygons
        if (polygon->getNumVertices() < 3)
        {
            delete polygon;
            iter = _polygons.erase(iter);
            continue;
        }

        // determine polygonPlane and delete polygon if its visible
        Plane plane(
                        polygon->getVertices()[0],
                        polygon->getVertices()[1],
                        polygon->getVertices()[2],
                        Polygon::ccw);

        if (plane.distance(point) > 0.f)
        {
            delete polygon;
            iter = _polygons.erase(iter);
            continue;
        }
        iter++;
    }
}

void PolygonBody::intersect(
    const LineSegment& line,
    const Pnt3f& min,
    const Pnt3f& max,
    VecVerticesT& vertices)
{
    const Vec3f& dir   = line.getDirection();
    const Pnt3f& point = line.getStartPoint();

    Real32 t1 = 0.f;
    Real32 t2 = std::numeric_limits<Real32>::infinity();

    bool intersect =
        clip(-dir.x(), point.x()-min.x(), t1, t2) && clip(dir.x(), max.x()-point.x(), t1, t2) &&
        clip(-dir.y(), point.y()-min.y(), t1, t2) && clip(dir.y(), max.y()-point.y(), t1, t2) &&
        clip(-dir.z(), point.z()-min.z(), t1, t2) && clip(dir.z(), max.z()-point.z(), t1, t2);

    if (!intersect)
        return;

    Pnt3f newPoint;
    intersect = false;

    if (t1 >= 0.f)
    {
        newPoint = point + t1 * dir;
        intersect = true;
    }

    if (t2 >= 0.f)
    {
        newPoint = point + t2 * dir;
        intersect = true;
    }

    if (intersect)
        vertices.push_back(newPoint);
}

bool PolygonBody::clip(Real32 p, Real32 q, Real32& u1, Real32& u2) const
{
    if (p < 0.f)
    {
        Real32 r = q / p;
        if (r > u2)
            return false;
        else
        {
            if (r > u1)
            {
                u1 = r;
            }
            return true;
        }
    }
    else
    {
        if (p > 0.f)
        {
            Real32 r = q / p;
            if (r < u1)
                return false;
            else
            {
                if (r < u2)
                {
                    u2 = r;
                }
                return true;
            }
        }
        else
            return q >= 0.f;
    }
}

void PolygonBody::createConvexHull(const VecVerticesT& vertices)
{
#ifdef OSG_WITH_QHULL
    if (vertices.size() < 5)
        return;

    orgQhull::RboxPoints rPoints;
    rPoints.setDimension(3);

    for (std::size_t i = 0; i < vertices.size(); ++i)
    {
        rPoints.append(static_cast<double>(vertices[i].x()));
        rPoints.append(static_cast<double>(vertices[i].y()));
        rPoints.append(static_cast<double>(vertices[i].z()));
    }

    clear();

    // QJn: joggle each input coordniate by a random number in the range [-n,n]
    // Qt: triangulate result
    orgQhull::Qhull convexHull(rPoints, "QJ0.0001Qt");

    std::vector<orgQhull::QhullFacet> triangles = convexHull.facetList().toStdVector();

    for (std::size_t i = 0; i < triangles.size(); ++i)
    {
        orgQhull::QhullPoint first  = triangles[i].vertices()[0].point();
        orgQhull::QhullPoint second = triangles[i].vertices()[1].point();
        orgQhull::QhullPoint third  = triangles[i].vertices()[2].point();

        double* nCoords = triangles[i].hyperplane().coordinates();
        Vec3f  normal(static_cast<float>(nCoords[0]), static_cast<float>(nCoords[1]), static_cast<float>(nCoords[2]));
        normal.normalize();

        Pnt3f v0(static_cast<float>( first[0]), static_cast<float>( first[1]), static_cast<float>( first[2]));
        Pnt3f v1(static_cast<float>(second[0]), static_cast<float>(second[1]), static_cast<float>(second[2]));
        Pnt3f v2(static_cast<float>( third[0]), static_cast<float>( third[1]), static_cast<float>( third[2]));

        Plane plane(v0, v1, v2, Polygon::ccw);

        Polygon* polygon = new Polygon();
        polygon->addVertex(v0);

        if (normal.dot(plane.getNormal()) > 0.f)
        {
            polygon->addVertex(v1);
            polygon->addVertex(v2);
        }
        else
        {
            polygon->addVertex(v2);
            polygon->addVertex(v1);
        }
        polygon->setNormal(normal);

        _polygons.push_back(polygon);
    }
#else
    assert(false);
#endif // OSG_WITH_QHULL
}


OSG_END_NAMESPACE
