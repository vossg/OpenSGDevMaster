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
#ifndef _OSG_SIMPLEPOLYGON_H_
#define _OSG_SIMPLEPOLYGON_H_

#include <iostream>
#include "OSGDrawableDef.h"
#include "OSGdctptypes.h"

OSG_BEGIN_NAMESPACE

#define OSG_TRIANGULATE_CONVEX

class SimplePolygon;

typedef std::vector <SimplePolygon> simplepolygonvector;

class OSG_DRAWABLE_DLLMAPPING SimplePolygon
{
  public:
    SimplePolygon();
    // copy constructor
    SimplePolygon(const SimplePolygon &p)
    {
        vertices  = p.vertices;
        is_marked = p.is_marked;
        v1tp      = -1;
        m_bConvex = p.m_bConvex;
    }
    ~SimplePolygon() {};

    DCTPivector vertices; // vertices. edges are from [n - 1, n] plus [vertices.size() - 1, 0], always ordered clockwise.
    // these are pointers into a global vertices table
    int          is_marked; // 0 if delauney != 0 else
    DCTPivector  validThirdPoints; // valid third points for actual edge
    unsigned int numThirdPoints; // actual number of valid third points
    int          maxCalculated; // max. third point tested
    int          v1tp, v2tp;   // actual first edge
    bool         m_bConvex;

    int triangulate(DCTPVec2dvector &globalverts, simplepolygonvector &polylist); //triangulates the polygon, using RK's method.
    // inserts the new polygons (triangles) at the end of the polygon list.
    // also sets up marking information for the new polygons.
  protected:
//  bool checkOrient( const DCTPVec3dvector &crclSpaceVerts, const DCTPVec3dvector &crclNormals ) const; // check if triangle has correct orientation
//  bool checkOrient( const DCTPVec3dvector &crclSpaceVerts, const DCTPVec3dvector &crclNormals, int i1, int i2, int i3 ) const; // check if triangle has correct orientation
    int findThirdPoint(DCTPVec2dvector &globalverts, int i1, int i2, int &i3); // try to find a suitable third point for (v1, v2)
    int isInsidePolygon(DCTPVec2dvector &globalverts, int i1, int i2, int i3) const; // is the triangle formed by the vertices (v1, v2, v3) inside the polygon ?
    int doIntersect(DCTPVec2dvector &globalverts, int v1, int v2, int p1, int p2) const; // do the two polylines (v1, v2) and (p1, p2) intersect ?
    int isInsideCircumCircle(DCTPVec2dvector &globalverts, int v1, int v2, int v3, int p) const; // is the point `p' inside the circumcircle of the triangle (v1, v2, v3) ?
    int isDelaunay(DCTPVec2dvector &globalverts, int v1, int v2, int v3); // is the triangle formed by the vertices (v1, v2, v3) a Delaunay triangle (with regard to this polygon ?

    // next three routines return 0 if done, !=0 if need to run again
    int removeLinearPoints(DCTPVec2dvector &globalverts, const Vec2d min, const Vec2d max); // remove linear points on polygon O(n)
    int splitPolygon(DCTPVec2dvector &globalverts, simplepolygonvector &polylist, const Vec2d min, const Vec2d max); // check for double vertices and split polygon in two O(nlogn)
    int intersectPolygon(DCTPVec2dvector &globalverts, simplepolygonvector &polylist); // check if polygon intersects itself and split in two O(n^2)
  public:
    bool isReversed(DCTPVec2dvector &globalverts); // check if polygon is reversed => ignore it O(n)
    bool isConvex(DCTPVec2dvector &globalverts);
    // stuff to fix invalid polygons
    int fixAndTriangulate(DCTPVec2dvector &globalverts, simplepolygonvector &polylist); // fix the polygon and triangulate the resulting valid polygons
  protected:
    double getAngle(Vec2d dir); // calculate angle between dir and (1,0) FIXME: should go to Vec2d
    int    getMinMax(DCTPVec2dvector &globalverts, Vec2d &min, Vec2d &max);

    inline int getThirdPoint(DCTPVec2dvector &globalverts, int v1, int v2, unsigned int index)
    {
        const unsigned int vsize  = UInt32(vertices.size());
        const unsigned int hsize1 = ( (vsize - 1) >> 1);
        const unsigned int h2size = (hsize1 << 1);

//    std::cerr << v1 << "," << v2 << " " << index << std::endl;

        if( (v1 != v1tp) || (v2 != v2tp) )
        {
            maxCalculated  = int(hsize1);
            numThirdPoints = 0;
            v1tp           = v1;
            v2tp           = v2;
        }
        while(index >= numThirdPoints)
        {
            if( (maxCalculated >= int(vsize) ) || (maxCalculated < 0) )
            {
//        std::cerr << "No valid third point " << v1 << "," << v2 << " " << index << std::endl;
                return -1;
            }
//      std::cerr << "Testing " << v1 << "," << v2 << "," << maxCalculated << std::endl;
            // FIXME: should also check if any point is on the edge
            // FIXME: of the triangle [v1, v2, maxCalculated]
            // FIXME: that is on the edges [v1, maxCalculated]
            // FIXME: or [v2, maxCalculated]
            if( (maxCalculated != v1) && (maxCalculated != v2) &&
                (isInsidePolygon(globalverts, v1, v2, maxCalculated) == 0) )
            {
                validThirdPoints[numThirdPoints] = maxCalculated;
                ++numThirdPoints;
            }
            maxCalculated = h2size - maxCalculated;
            if(maxCalculated >= int(hsize1) )
            {
                ++maxCalculated;
            }
        }
//    std::cerr << "valid third point " << v1 << "," << v2 << " " << index << " = " << validThirdPoints[ index ] << std::endl;
        return validThirdPoints[index];
    }

};

OSG_END_NAMESPACE




#endif // SimplePolygon.h
