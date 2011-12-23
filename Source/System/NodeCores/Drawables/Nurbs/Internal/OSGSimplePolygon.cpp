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
#ifdef WIN32
#   pragma warning (disable : 985)
#endif

#include <stdio.h>

#include "OSGLog.h"

#include "OSGSimplePolygon.h"
#include "OSGpredicates.h"

OSG_USING_NAMESPACE

#ifndef M_PI
#  define M_PI      3.14159265358979323846
#endif /* M_PI */
#ifndef M_PI_2
#  define M_PI_2        (M_PI * 0.5)
#endif /* M_PI_2 */

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif

/*
 * Converted to use robust predicates, see `predicates.c' and
 * `predicates.h'
 *
 * FIXME: may have some license issues, also must run at first
 * compilation the `predicates_init' calculator, may have trouble
 * on Win32 systems.
 */

/*
 * Public methods
 */

// default constructor
SimplePolygon::SimplePolygon()
{
    vertices.resize(0);
    is_marked = 0;
    validThirdPoints.resize(0);
    v1tp      = -1;
    m_bConvex = false;
}


//! Triangulates the polygon, using RK's constrained method.
/*!
 *  Note that the resulting triangulation will not necessarily be complex,
 *  since it's constrained by the polygon's edges.
 *
 *  Besides triangulating the polygon this method also does:
 *  - insertion of the new polygons (triangles) at the end of
 *    the polygon list.
 *  - setting up marking information for the new polygons.
 *
 *  \param polylist the global list of polygons
 *  \param selfindex the index of this polygon in the global list
 *  \return zero on success, and a negative integer if some error occured.
 */
int SimplePolygon::triangulate(DCTPVec2dvector &globalverts, simplepolygonvector &polylist)
{
#ifdef OSG_TRIANGULATE_CONVEX
    if( (!is_marked) && (m_bConvex) )
    {
//		std::cerr <<"triangulating convex: " <<vertices.size() << std::endl;
        switch(vertices.size() )
        {
        case 0:
        case 1:
        case 2:
            return 0;
        case 3:
        {
            polylist.push_back(*this);
        }
            return 0;
        }

        unsigned int       ui_prev;
        unsigned int       ui_mid;
        unsigned int       ui_next;
        const unsigned int cui_vertex_cnt = UInt32(vertices.size());
        SimplePolygon      cl_poly;

        ui_mid = 0;

        for(ui_prev = 1; ui_prev < cui_vertex_cnt; ++ui_prev)
        {
            if(globalverts[vertices[ui_prev]][1] < globalverts[vertices[ui_mid]][1])
            {
                ui_mid = ui_prev;
            }
            else if( (globalverts[vertices[ui_prev]][1] == globalverts[vertices[ui_mid]][1]) &&
                     (globalverts[vertices[ui_prev]][0] < globalverts[vertices[ui_mid]][0]) )
            {
                ui_mid = ui_prev;
            }
        }

        ui_prev = (ui_mid + cui_vertex_cnt - 1) % cui_vertex_cnt;
        ui_next = (ui_mid + 1) % cui_vertex_cnt;

        cl_poly.vertices.resize(3);
        cl_poly.is_marked   = is_marked;
        cl_poly.vertices[0] = vertices[ui_mid];
        cl_poly.vertices[1] = vertices[ui_next];
        cl_poly.vertices[2] = vertices[ui_prev];

        ui_prev = (ui_prev + cui_vertex_cnt - 1) % cui_vertex_cnt;
        ui_next = (ui_next + 1) % cui_vertex_cnt;

        while(cl_poly.vertices[1] != cl_poly.vertices[2])
        {
            polylist.push_back(cl_poly);
            if(globalverts[vertices[ui_prev]][1] < globalverts[vertices[ui_next]][1])
            {
                cl_poly.vertices[0] = cl_poly.vertices[2];
                cl_poly.vertices[2] = vertices[ui_prev];
                ui_prev             = (ui_prev + cui_vertex_cnt - 1) % cui_vertex_cnt;
            }
            else if( (globalverts[vertices[ui_prev]][1] == globalverts[vertices[ui_next]][1]) &&
                     (globalverts[vertices[ui_prev]][0] < globalverts[vertices[ui_next]][0]) )
            {
                cl_poly.vertices[0] = cl_poly.vertices[2];
                cl_poly.vertices[2] = vertices[ui_prev];
                ui_prev             = (ui_prev + cui_vertex_cnt - 1) % cui_vertex_cnt;
            }
            else
            {
                cl_poly.vertices[0] = cl_poly.vertices[1];
                cl_poly.vertices[1] = vertices[ui_next];
                ui_next             = (ui_next + 1) % cui_vertex_cnt;
            }
        }
        return 0;
    }
#endif

//  std::cerr << " triangulate in, size: " << vertices.size() << std::endl;
    switch(vertices.size() )
    {
    case 0:
    case 1:
    case 2:
        return 0;
    case 3:
    {
        polylist.push_back(*this);
//				SimplePolygon p;
//				p.vertices = vertices;
//				p.is_marked = is_marked;
//				std::cerr << "adding polygon of 3 vertices into the list..." << std::endl;
//				polylist.push_back( p ); // FIXME, this is not too elegant
//				std::cerr << "triangulate out!!!" << std::endl;
    }
        return 0;
    case 4:
    {
        const int     ci_v1     = vertices[0];
        const int     ci_v2     = vertices[1];
        const int     ci_v3     = vertices[2];
        const int     ci_v4     = vertices[3];
        const double  cd_sdist1 = (globalverts[ci_v1] - globalverts[ci_v3]).squareLength();
        const double  cd_sdist2 = (globalverts[ci_v2] - globalverts[ci_v4]).squareLength();
        double        ad_pa[2];
        double        ad_pb[2];
        double        ad_pc[2];
        double        ad_pd[2];
        SimplePolygon p;

        p.vertices.resize(3);
        p.is_marked = is_marked;

        ad_pa[0] = globalverts[ci_v1][0];
        ad_pa[1] = globalverts[ci_v1][1];
        ad_pb[0] = globalverts[ci_v2][0];
        ad_pb[1] = globalverts[ci_v2][1];
        ad_pc[0] = globalverts[ci_v3][0];
        ad_pc[1] = globalverts[ci_v3][1];
        ad_pd[0] = globalverts[ci_v4][0];
        ad_pd[1] = globalverts[ci_v4][1];

        if(cd_sdist1 - cd_sdist2 < DCTP_EPS)
        {
/*					const double cd_r1 = orient2d( ad_pa, ad_pb, ad_pc );
                    const double cd_r2 = orient2d( ad_pa, ad_pb, ad_pd );
                    if( ( ( cd_r1 <= 0.0 ) && ( cd_r2 <= 0.0 ) ) ||
                        ( ( cd_r1 >= 0.0 ) && ( cd_r2 >= 0.0 ) ) )*/
            if( (orient2d(ad_pa, ad_pb, ad_pc) <= 0.0) ||
                (orient2d(ad_pa, ad_pd, ad_pc) >= 0.0) ||
                (incircle(ad_pa, ad_pb, ad_pc, ad_pd) > 0.0) )
            {
                p.vertices[0] = ci_v1;
                p.vertices[1] = ci_v2;
                p.vertices[2] = ci_v4;
                polylist.push_back(p);
                p.vertices[0] = ci_v2;
                p.vertices[1] = ci_v3;
                p.vertices[2] = ci_v4;
                polylist.push_back(p);
//						std::cerr << globalverts[ ci_v1 ] << globalverts[ ci_v2 ] << globalverts[ ci_v3 ] << globalverts[ ci_v4 ] << std::endl;
            }
            else
            {
                p.vertices[0] = ci_v1;
                p.vertices[1] = ci_v2;
                p.vertices[2] = ci_v3;
                polylist.push_back(p);
                p.vertices[0] = ci_v1;
                p.vertices[1] = ci_v3;
                p.vertices[2] = ci_v4;
                polylist.push_back(p);
            }
        }
        else
        {
//					const double cd_r1 = orient2d( ad_pc, ad_pd, ad_pa );
//					const double cd_r2 = orient2d( ad_pc, ad_pd, ad_pb );
//					if( ( ( cd_r1 <= 0.0 ) && ( cd_r2 <= 0.0 ) ) ||
//						( ( cd_r1 >= 0.0 ) && ( cd_r2 >= 0.0 ) ) )
            if( (orient2d(ad_pb, ad_pc, ad_pd) <= 0.0) ||
                (orient2d(ad_pb, ad_pa, ad_pd) >= 0.0) ||
                (incircle(ad_pa, ad_pb, ad_pd, ad_pc) > 0.0) )
            {
                p.vertices[0] = ci_v1;
                p.vertices[1] = ci_v2;
                p.vertices[2] = ci_v3;
                polylist.push_back(p);
                p.vertices[0] = ci_v1;
                p.vertices[1] = ci_v3;
                p.vertices[2] = ci_v4;
                polylist.push_back(p);
//						std::cerr << globalverts[ ci_v1 ] << globalverts[ ci_v2 ] << globalverts[ ci_v3 ] << globalverts[ ci_v4 ] << std::endl;
            }
            else
            {
                p.vertices[0] = ci_v1;
                p.vertices[1] = ci_v2;
                p.vertices[2] = ci_v4;
                polylist.push_back(p);
                p.vertices[0] = ci_v2;
                p.vertices[1] = ci_v3;
                p.vertices[2] = ci_v4;
                polylist.push_back(p);
            }
        }
    }
        return 0;
    }

    // recalc valid third points!
    v1tp = -1;
    validThirdPoints.resize(vertices.size() );

    SimplePolygon poly;
    int           i2, i3; // this is an index into the vertices[] vector
    int           err;
    DCTPivector   verts; //p1verts, p2verts, p3verts;
    int           i;
    int           j;
    // pseudo random (reproduces same triangulation)
    int offs = (int( globalverts[vertices[0]][0] * vertices.size() ) ) % vertices.size();

/*  for( i = 0; i < vertices.size( ); ++i )
  {
    std::cerr << globalverts[ vertices[ i ] ][0] << ",";
    std::cerr << globalverts[ vertices[ i ] ][1] << std::endl;
  }*/

    for(j = 0; j < int(vertices.size()); j++)
    {
        i = (j + offs) % vertices.size();
//    v1 = vertices[ i ];
        if(i == int(vertices.size()) - 1)
            i2 = 0; //v2 = vertices [ 0 ];
        else
            i2 = i + 1; //v2 = vertices[ i + 1 ];
        err = findThirdPoint(globalverts, i, i2, i3);
        if(err)
            return err;
        if(i3 >= 0)
        {
            // build p1
            int k = i2; // !!!
            verts.resize(0);
            while(k != i3)
            {
//        std::cerr << " k: " << k;
                verts.push_back(vertices[k]);
                k++; if(k == int(vertices.size()) )
                    k = 0;
            } // while k
            verts.push_back(vertices[k]);   // record the last one aswell
//      std::cerr << " k: " << k << std::endl;
            poly.vertices  = verts;
            poly.is_marked = is_marked;
//      std::cerr << "calling p1... " << std::endl;
            err = poly.triangulate(globalverts, polylist);
            if(err)
                return err;
            // build p2
            verts.resize(3);
            verts[0]       = vertices[i];
            verts[1]       = vertices[i2];
            verts[2]       = vertices[i3];
            poly.vertices  = verts;
            poly.is_marked = is_marked;
//      std::cerr << "adding p2 to the list..." << std::endl;
            polylist.push_back(poly);
            // build p3
            k = i3;
            verts.resize(0);
            while(k != i)
            {
                verts.push_back(vertices[k]);
                k++; if(k == int(vertices.size()) )
                    k = 0;
            } // while k
            verts.push_back(vertices[k]);   // record the last one aswell
            poly.vertices  = verts;
            poly.is_marked = is_marked;
//      std::cerr << "calling p3... " << std::endl;
            err = poly.triangulate(globalverts, polylist);
            if(err)
                return err;
//      std::cerr << "triangulate out!!!" << std::endl;
            return 0;
        } // if
    } // for i

/*  SWARNING << "triangulate out WITH ERROR!!!" << endLog;

  for( i = 0; i < vertices.size( ); ++i )
  {
    std::cerr << globalverts[ vertices[ i ] ][0] << ",";
    std::cerr << globalverts[ vertices[ i ] ][1] << std::endl;
  }*/

//  char x[ 256 ];
//  gets( x );

    return -1;
}

/*
 * Protected methods.
 */

//! Try to find a suitable third point for (i1, i2)
/*!
 *  `i1' and `i2' must already be an edge of the polygon, and the third point `i3'
 *  will be a point of the polygon which is different from `i1' and `i2'.
 *  The polygon's lines must not cross each other. These are actually all indices
 *  into the `globalverts' vector.
 *
 *  \param globalverts global vertices vector
 *  \param i1 first point
 *  \param i2 second point (must form an edge with the first point)
 *  \param i3 suitable third point, or -1 if there's no suitable third point
 *            for (i1, i2 ) can't be found
 *  \return zero on success, and a negative integer if some error occured.
 *
 *  FIXME: the semantics were changed so the above comments are not 100%
 *  FIXME: correct. TODO: Check with Michael. :)
 */
int SimplePolygon::findThirdPoint(DCTPVec2dvector &globalverts, int i1, int i2, int &i3)
{
    if(is_marked)
    {
//		std::cerr << "no delauney check" << std::endl;
        i3 = getThirdPoint(globalverts, i1, i2, 0);
        return 0;
    }

    unsigned int       i;
    const unsigned int vsize = UInt32(vertices.size());

//  std::cerr << "searching third point for " << i1 << ", " << i2 << std::endl;

    for(i = 0; i < vsize; ++i)
    {
        i3 = getThirdPoint(globalverts, i1, i2, i);
        if(i3 == -1)
        {
//      std::cerr << "no third points left." << std::endl;
            return 0;
        }
        if(isDelaunay(globalverts, i1, i2, i3) == 0)
        {
//      std::cerr << "third point found: " << i3 << std::endl;
            return 0;
        }
    }

    i3 = -1;
    return 0;

/*  i3 = -1;
  for (int i = 0; i < (int) vertices.size(); i++ ) {
    if ( ( i != i1 ) && ( i != i2 ) ) {
      if ( isInsidePolygon( globalverts, i1, i2, i ) == 0 ) {
        if ( isDelaunay( globalverts, i1, i2, i ) == 0 ) {
           i3 = i;
//           std::cerr << "Third point for " << i1 << " " << i2 << " is: " << i3 << std::endl;
           return 0;
        }
      }
    }
  } //for i*/

//  std::cerr << "No third point for " << i1 << " " << i2 << " ." << std::endl;

//  return 0;
}

//! Is the triangle formed by the vertices (i1, i2, i3) inside the polygon ?
/*!
 *  `i1' and `i2' must already be an edge of the polygon, and the third point `i3'
 *  be a point of the polygon different from `i1' and `i2'. The polygon's lines
 *  must not cross each other.
 *
 *  \param globalverts global vertices vector
 *  \param i1 first point
 *  \param i2 second point (must form an edge with the first point)
 *  \param i3 third point
 *  \return 1 if not inside <BR>
 *          0 if inside <BR>
 *          and a negative value if an error happened.
 */
int SimplePolygon::isInsidePolygon(DCTPVec2dvector &globalverts, int i1, int i2, int i3) const
{
    double    dres;
    const int size = UInt32(vertices.size());
    const int vi1  = vertices[i1];
    const int vi2  = vertices[i2];
    const int vi3  = vertices[i3];
    const int prev = vertices[(size + i1 - 1) % size];
    const int next = vertices[(i2 + 1) % size];

    // the third (i3) point must lie to the left of the edge (i2, next)
    // (NOT! on the edge) to be inside
    double p2[2], p3[2], pn[2];
    p3 [0] = globalverts[vi3][0];
    p3 [1] = globalverts[vi3][1];
    p2 [0] = globalverts[vi2][0];
    p2 [1] = globalverts[vi2][1];
    pn [0] = globalverts[next][0];
    pn [1] = globalverts[next][1];

    if(vi3 != next)
    {
        dres = orient2d(p3, p2, pn);
//	  std::cerr << "next edge test: " << dres << std::endl;

        if(dres < 0.0)
            return 1;
    }

    // the third (i3) point must also lie to the left of the edge (prev, i1)
    // (NOT! on the edge) to be inside
    double p1[2], pp[2];
    pp [0] = globalverts[prev][0];
    pp [1] = globalverts[prev][1];
    p1 [0] = globalverts[vi1][0];
    p1 [1] = globalverts[vi1][1];

    if(vi3 != prev)
    {
        dres = orient2d(p3, pp, p1);
//	  std::cerr << "prev edge test: " << dres << std::endl;

        if(dres < 0.0)
            return 1;
    }

    // the third (i3) point must also lie to the left of the edge (i1, i2)
    // (NOT! on the edge) to be inside

    dres = orient2d(p3, p1, p2);
//  std::cerr << "actual edge test: " << dres << std::endl;

    if(dres <= 0.0)
        return 1;

//  if( m_bConvex ) return 0;	// don't need intersection test for convex polygons

    // the triangle is not completely outside the polygon, we have to
    // go for the intersection test.
    // FIXME/TODO: use bounding boxes to speed up testing:
    // only test with those edges that are at least partially in the
    // bounding box of the triangle to be tested

    int           res;
    int           j = size - 1;
    Vec2d         min, max;
    unsigned char test, ptest;

    min = max = globalverts[vi1];
    if(min[0] > globalverts[vi2][0])
        min[0] = globalverts[vi2][0];
    else if(max[0] < globalverts[vi2][0])
        max[0] = globalverts[vi2][0];
    if(min[1] > globalverts[vi2][1])
        min[1] = globalverts[vi2][1];
    else if(max[1] < globalverts[vi2][1])
        max[1] = globalverts[vi2][1];
    if(min[0] > globalverts[vi3][0])
        min[0] = globalverts[vi3][0];
    else if(max[0] < globalverts[vi3][0])
        max[0] = globalverts[vi3][0];
    if(min[1] > globalverts[vi3][1])
        min[1] = globalverts[vi3][1];
    else if(max[1] < globalverts[vi3][1])
        max[1] = globalverts[vi3][1];

    const Vec2d &pj = globalverts[vertices[j]];
    test = 0;
    if(pj[0] - max[0] > DCTP_EPS)
        test |= 0x01;
    if(min[0] - pj[0] > DCTP_EPS)
        test |= 0x02;
    if(pj[1] - max[1] > DCTP_EPS)
        test |= 0x04;
    if(min[1] - pj[1] > DCTP_EPS)
        test |= 0x08;

    for(int i = 0; i < size; i++)
    {
        ptest = test;
        test  = 0;
        const Vec2d &pi = globalverts[vertices[i]];
        if(pi[0] - max[0] > DCTP_EPS)
            test |= 0x01;
        if(min[0] - pi[0] > DCTP_EPS)
            test |= 0x02;
        if(pi[1] - max[1] > DCTP_EPS)
            test |= 0x04;
        if(min[1] - pi[1] > DCTP_EPS)
            test |= 0x08;
        if( (test & ptest) == 0)
        {
//      std::cerr << "checking: " << v1 << " " << v3 << " and i: " << i << std::endl;
            res = doIntersect(globalverts, i1, i3, j, i);
            if(res)
                return res;     // either intersection or error
            res = doIntersect(globalverts, i2, i3, j, i);
            if(res)
                return res;     // see above
        }
        j = i;
    }

    return 0;
}


//! Do the two polylines (v1, v2) and (p1, p2) intersect (apart from the corners) ?
/*!
 *  The polylines must be different.
 *
 *  \param globalverts global vertices vector
 *  \param v1 the first polyline
 *  \param v2
 *  \param p1 the second polyline
 *  \param p2
 *
 *  \return  0 if they don't intersect <BR>
 *           1 if they do <BR>
 */
int SimplePolygon::doIntersect(DCTPVec2dvector &globalverts, int v1, int v2, int p1, int p2) const
{
    // check if they share vertices
    if(v1 == p1 || v1 == p2 || v2 == p1 || v2 == p2)
        return 0;

    double    pa[2];
    double    pb[2];
    double    pc[2];
    double    pd[2];
    const int vv1 = vertices[v1];
    const int vv2 = vertices[v2];
    const int vp1 = vertices[p1];
    const int vp2 = vertices[p2];

    pa[0] = globalverts[vv1][0];
    pa[1] = globalverts[vv1][1];
    pb[0] = globalverts[vv2][0];
    pb[1] = globalverts[vv2][1];
    pc[0] = globalverts[vp1][0];
    pc[1] = globalverts[vp1][1];
    pd[0] = globalverts[vp2][0];
    pd[1] = globalverts[vp2][1];

    const double r1 = orient2d(pa, pc, pd);
    const double r2 = orient2d(pb, pc, pd);
    if( (r1 < 0.0) && (r2 < 0.0) )
    {
        return 0;
    }
    if( (r1 > 0.0) && (r2 > 0.0) )
    {
        return 0;
    }

    const double r3 = orient2d(pc, pa, pb);
    const double r4 = orient2d(pd, pa, pb);
    if( (r3 < 0.0) && (r4 < 0.0) )
    {
        return 0;
    }
    if( (r3 > 0.0) && (r4 > 0.0) )
    {
        return 0;
    }
    return 1;

    // do intersect??
    /*
     * r1 and r2 must have different signs ( <0, >0, =0 ) AND
     * r3 and r4 must also have different signs in suffice intersection of
     * the two lines.
     */
/*  bool s1 = ( !(( r1 < 0  &&  r2 < 0 ) || ( r1 > 0  && r2 > 0 )) );
  bool s2 = ( !(( r3 < 0  &&  r4 < 0 ) || ( r3 > 0  && r4 > 0 )) );

  if ( s1  && s2 ) return 1;
  else return 0;*/

}

//! Is the point `p' inside the circumcircle of the triangle (v1, v2, v3) ?
/*!
 *  \param globalverts global vertices vector
 *  \param v1 first vertex
 *  \param v2 second vertex
 *  \param v3 third vertex
 *  \param p the point
 *  \return 0 if not inside <BR>
 *          1 if inside <BR>
 */
int SimplePolygon::isInsideCircumCircle(DCTPVec2dvector &globalverts, int v1, int v2, int v3, int p) const
{
    double pa[2], pb[2], pc[2], pd[2];

    pa [0] = globalverts[vertices[v1]][0];
    pa [1] = globalverts[vertices[v1]][1];
    pb [0] = globalverts[vertices[v2]][0];
    pb [1] = globalverts[vertices[v2]][1];
    pc [0] = globalverts[vertices[v3]][0];
    pc [1] = globalverts[vertices[v3]][1];
    pd [0] = globalverts[vertices[p]][0];
    pd [1] = globalverts[vertices[p]][1];
    // check for order of (pa, pb, pc) they must be in counterclockwise order
    double order = orient2d(pa, pb, pc);
    double dres;
    if(order < 0.0)  // clockwise order -> change order
        dres = incircle(pa, pc, pb, pd);
    else
        dres = incircle(pa, pb, pc, pd);

    //std::cerr << pa[ 0 ] << "," << pa[ 1 ] << " ";
    //std::cerr << pb[ 0 ] << "," << pb[ 1 ] << " ";
    //std::cerr << pc[ 0 ] << "," << pc[ 1 ] << " ";
    //std::cerr << pd[ 0 ] << "," << pd[ 1 ] << std::endl;
    //std::cerr << "Inside Circumcircle: " << dres << std::endl;   // >0 if inside

    if(dres <= 0)
        return 0;
    else
        return 1;
}

//! Is the triangle formed by the vertices (v1, v2, v3) a Delaunay triangle (with regard to this polygon ?
/*!
 *  \param globalverts global vertices vector
 *  \param v1 first vertex
 *  \param v2 second vertex
 *  \param v3 third vertex
 *
 *  \return 0 if Delaunay <BR>
 *          1 if not Delaunay <BR>
 *          and a negative value if an error happened.
 */
int SimplePolygon::isDelaunay(DCTPVec2dvector &globalverts, int v1, int v2, int v3)
{
    unsigned int       i;
    int                v4, ret;
    const unsigned int vsize = UInt32(vertices.size());

    for(i = 0; i < vsize; ++i)
    {
        v4 = getThirdPoint(globalverts, v1, v2, i);
        if(v4 == -1)
        {
            return 0;
        }
        if(v3 != v4)
        {
            ret = isInsideCircumCircle(globalverts, v1, v2, v3, v4);
//      std::cerr << "Inside circle test " << v1 << "," << v2 << "," << v3 << "," << v4 << " = " << ret << std::endl;
            if(ret)
            {
                return ret;
            }
        }
    }

/*  int res;
  for( int i = 0; i < ( int ) vertices.size( ); ++i )
  {
    if( ( i != v1 ) && ( i != v2 ) && ( i != v3 ) )
    {
//      std::cerr << "check " << v1 << "," << v2 << "," << v3;
//      std::cerr << " <-> " << v1 << "," << v2 << "," << i << std::endl;
      res = isInsideCircumCircle( globalverts, v1, v2, v3, i );
      // note: the Delaunay criterium is only for _visible_ vertices,
      // we have to check that too.
      if( ( res != 0 ) && ( isInsidePolygon( globalverts, v1, v2, i ) == 0 ) )
        return res;
    }
  }*/
    return 0;
}

//! Fixes the polygon (splits it if necessary) and call triangulation.
/*!
 *  Note that this has complexity O(n^2) but should not count since
 *  triangulation has O(n^3).
 *
 *  \param globalverts the global vertices vector
 *  \param polylist the global list of polygons
 *  \return zero on success, and a negative integer if some error occured.
 */
int SimplePolygon::fixAndTriangulate(DCTPVec2dvector &globalverts, simplepolygonvector &polylist)
{
    Vec2d min, max;

    if(getMinMax(globalverts, min, max) )
    {
//    std::cerr << "Ignoring degenerate polygon..." << std::endl;
        return -1;
    }
//  while( removeLinearPoints( globalverts, min, max ) ) { }
    while(splitPolygon(globalverts, polylist, min, max) )
    {
    }
    while(intersectPolygon(globalverts, polylist) )
    {
    }
    if(isReversed(globalverts) )
    {
//    std::cerr << "Ignoring reversed polygon." << std::endl;
        return 0; // no error here...
    }

    // Ok, we have a valid polygon, so triangulate it.
    triangulate(globalverts, polylist);
    return 0;
}

//! Removes linear points from the polygon.
/*!
 *  Note that this has complexity O(n).
 *
 *  \param globalverts the global vertices vector
 *  \return zero on success, and a negative integer if some error occured.
 */
int SimplePolygon::removeLinearPoints(DCTPVec2dvector &globalverts, const Vec2d min, const Vec2d max)
{
    int         oldNum = UInt32(vertices.size());
    int         newNum = 0;
    DCTPivector newPoints(oldNum); // waste some memory to have linear time
    int         i;
    int         last = oldNum - 1;

//  std::cerr << "Removing linear points... " << oldNum << std::endl;

    // insert nonlienaer points in new array
    for(i = 0; i < oldNum; ++i)
    {
        Vec2d p = globalverts[vertices[i]];
        // check for double vertices
        if(DCTPVecIsNotEqual(p, globalverts[vertices[last]]) )
        {
            Vec2d pp = globalverts[vertices[last]];
            Vec2d pn = globalverts[vertices[(i + 1) % oldNum]];

            if( ( (p[0] - min[0] < DCTP_EPS) && (pn[0] - min[0] < DCTP_EPS) ) ||
                ( (p[1] - min[1] < DCTP_EPS) && (pn[1] - min[1] < DCTP_EPS) ) ||
                ( (max[0] - p[0] < DCTP_EPS) && (max[0] - pn[0] < DCTP_EPS) ) ||
                ( (max[1] - p[1] < DCTP_EPS) && (max[1] - pn[1] < DCTP_EPS) ) )
            {
                newPoints[newNum] = vertices[i];
                ++newNum;
                last = i;
            }
            else
            {
                double d1[2], d2[2], d3[2];
                d1[0] = pp[0];
                d1[1] = pp[1];
                d2[0] = p[0];
                d2[1] = p[1];
                d3[0] = pn[0];
                d3[1] = pn[1];
                if(orient2d(d1, d2, d3) != 0)
                {
                    newPoints[newNum] = vertices[i];
                    ++newNum;
                    last = i;
                }
/*        else if( ( pp[1] != pn[1] ) && ( pp[0] != pn[0] ) )
        {
          std::cerr << "removing point " <<std::endl;
          std::cerr << pp[0] << "," << pp[1] << std::endl;
          std::cerr << "(" << p[0] << "," << p[1] << ")" << std::endl;
          std::cerr << pn[0] << "," << pn[1] << std::endl;
          char x[ 256 ];
          gets( x );
        }*/
            }
        }
    }

//  std::cerr << newNum << " points left." << std::endl;

    // copy new points
    if(newNum != oldNum)
    {
        vertices.resize(newNum);

        for(i = 0; i < newNum; ++i)
        {
            vertices[i] = newPoints[i];
        }

        return 1;
    }

    return 0;
}

int SimplePolygon::splitPolygon(DCTPVec2dvector &globalverts, simplepolygonvector &polylist, const Vec2d min, const Vec2d max)
{
    DCTPVec2dset                            vset;
    std::pair<DCTPVec2dset::iterator, bool> siv;
    int                                     oldNum = UInt32(vertices.size());
    int                                     i1;

//  std::cerr << "Removing double vertices... " << oldNum << std::endl;

    for(i1 = 0; i1 < oldNum; ++i1)
    {
        siv = vset.insert(globalverts[vertices[i1]]);
        if(!siv.second)
        {
            // here we need to split the polygon and start with the new ones again.
            int           i;
            DCTPivector   newPoints(oldNum); // waste some memory to have nlogn time
            int           newNum = 0;
            int           i2     = 0;
            SimplePolygon poly;

            // copy points before first intersection
            while(DCTPVecIsNotEqual(globalverts[vertices[i2]], globalverts[vertices[i1]]) )
            {
                newPoints[i2] = vertices[i2];
                ++i2;
            }
            newNum = i2;

//      std::cerr << i2 << " = " << i1 << std::endl;

            // construct new polygon
            poly.vertices.resize(i1 - i2);

            for(i = i2; i < i1; ++i)
            {
                poly.vertices[i - i2] = vertices[i];
//        std::cerr << vertices[ i ] << " ";
            }

//      std::cerr << std::endl;

            // copy points from second intersection to the end
            for(i = i1; i < oldNum; ++i)
            {
                newPoints[newNum] = vertices[i];
                ++newNum;
            }

            // copy new points back to polygon
            vertices.resize(newNum);

            for(i = 0; i < newNum; ++i)
            {
                vertices[i] = newPoints[i];
//        std::cerr << vertices[ i ] << " ";
            }

//      std::cerr << std::endl;

            // triangulate the new polygon
//      std::cerr << oldNum << " split in " << vertices.size() << "," << poly.vertices.size() << std::endl;
            // need to check for new liear points
//      while( poly.removeLinearPoints( globalverts, min, max ) ) { }
            while(poly.intersectPolygon(globalverts, polylist) )
            {
            }
            if(poly.isReversed(globalverts) )
            {
//        std::cerr << "Ignoring reversed polygon." << std::endl;
            }
            else
            {
                // Ok, we have a valid polygon, so triangulate it.
                poly.triangulate(globalverts, polylist);
            }

            // need to check for new liear points
//      while( removeLinearPoints( globalverts, min, max ) ) { }
            // check if there are other double vertices
            return 1;
        }
    }

    // polygon had no double vertices so we are finished
    return 0;
}

int SimplePolygon::intersectPolygon(DCTPVec2dvector &globalverts, simplepolygonvector &polylist)
{
    int           oldNum = UInt32(vertices.size());
    int           i1, i2;
    Vec2d         min, max;
    Vec2d         p3, p4;
    unsigned char test, ptest;

//  std::cerr << "Removing intersections... " << oldNum << std::endl;

    for(i2 = 2; i2 < oldNum; ++i2)
    {
        const Vec2d &p1 = globalverts[vertices[i2]];
        const Vec2d &p2 = globalverts[vertices[(i2 + 1) % oldNum]];

        min = max = p1;
        if(min[0] > p2[0])
            min[0] = p2[0];
        else if(max[0] < p2[0])
            max[0] = p2[0];
        if(min[1] > p2[1])
            min[1] = p2[1];
        else if(max[1] < p2[1])
            max[1] = p2[1];

        const unsigned int start = (i2 == oldNum - 1) ? 1 : 0;

        p4   = globalverts[vertices[start]];
        test = 0;
        if(p4[0] - max[0] > DCTP_EPS)
            test |= 0x01;
        if(min[0] - p4[0] > DCTP_EPS)
            test |= 0x02;
        if(p4[1] - max[1] > DCTP_EPS)
            test |= 0x04;
        if(min[1] - p4[1] > DCTP_EPS)
            test |= 0x08;

        for(i1 = start; i1 < i2 - 1; ++i1)
        {
            p3    = p4;
            p4    = globalverts[vertices[i1 + 1]];
            ptest = test;
            test  = 0;
            if(p4[0] - max[0] > DCTP_EPS)
                test |= 0x01;
            if(min[0] - p4[0] > DCTP_EPS)
                test |= 0x02;
            if(p4[1] - max[1] > DCTP_EPS)
                test |= 0x04;
            if(min[1] - p4[1] > DCTP_EPS)
                test |= 0x08;
            if( (test & ptest) == 0)
            {
//         std::cerr << i1 << "," << i1 + 1 << " overlaps " << i2 << "," << i2 + 1 << std::endl;
                // the bounding boxes overlap
                int    iip       = -1;
                bool   intersect = false;
                double d1[2]     = { p1[0], p1[1] };
                double d2[2]     = { p2[0], p2[1] };
                double d3[2]     = { p3[0], p3[1] };
                double d4[2]     = { p4[0], p4[1] };

                if( (orient2d(d1, d2, d3) == 0.0) &&
                    (orient2d(d1, d2, d4) == 0.0) )
                {
                    // the lines are colinear => ... p1 p4 ... ; p2 ... p3
                    intersect = true;
                }
                else
                {
                    if(doIntersect(globalverts, i1, i1 + 1, i2, (i2 + 1) % oldNum) )
                    {
                        // the lines intersect => ... p1 ip p4 ... ; ip p2 ... p3
                        Vec2d  v1 = p2 - p1;
                        Vec2d  v2 = p4 - p3;
                        Vec2d  pp = p3 - p1;
                        double a  = pp[0] * v2[1] - pp[1] * v2[0];
                        double b  = v1[0] * v2[1] - v1[1] * v2[0];
                        Vec2d  ip = p1 + v1 * (a / b);

                        if(DCTPVecIsEqual(ip, p1) )
                        {
                            iip = vertices[i1];
                        }
                        else if(DCTPVecIsEqual(ip, p2) )
                        {
                            iip = vertices[i1 + 1];
                        }
                        else if(DCTPVecIsEqual(ip, p3) )
                        {
                            iip = vertices[i2];
                        }
                        else if(DCTPVecIsEqual(ip, p4) )
                        {
                            iip = vertices[(i2 + 1) % oldNum];
                        }
                        else
                        {
                            iip = UInt32(globalverts.size());
                            globalverts.resize(iip + 1);
                            globalverts[iip] = ip;
                        }

//			std::cerr << p1[0] << "," << p1[1] << " - " << p2[0] << "," << p2[1] << std::endl;
//			std::cerr << p3[0] << "," << p3[1] << " - " << p4[0] << "," << p4[1] << std::endl;
//			std::cerr << globalverts[ iip ][0] << "," << globalverts[ iip ][1] << " - " << std::endl;
                        intersect = true;
                    }
                }
                if(intersect)
                {
                    int           i;
                    int           newNum;
                    DCTPivector   newPoints(oldNum);
                    SimplePolygon poly;

//          std::cerr << i1 << "," << i1 + 1 << " intersects " << i2 << "," << i2 + 1 << std::endl;

                    // copy points 0 ... i1
                    for(i = 0; i <= i1; ++i)
                    {
                        newPoints[i] = vertices[i];
                    }

                    newNum = i;

                    // copy iip's
                    if(iip >= 0)
                    {
                        if( (iip != vertices[i1]) &&
                            (iip != vertices[(i2 + 1) % oldNum]) )
                        {
                            newPoints[newNum] = iip;
                            ++newNum;
                        }
                        if( (iip != vertices[i2]) &&
                            (iip != vertices[i1 + 1]) )
                        {
                            poly.vertices.resize(i2 + 1 - i1);
                            poly.vertices[i2 - i1] = iip;
                        }
                        else
                        {
                            poly.vertices.resize(i2 - i1);
                        }
                    }
                    else
                    {
                        poly.vertices.resize(i2 - i1);
                    }

                    // copy i1+1 ... i2
                    for(i = 0; i < i2 - i1; ++i)
                    {
                        poly.vertices[i] = vertices[i1 + i + 1];
                    }

                    // copy i2+1 ... n
                    for(i = i2 + 1; i < oldNum; ++i)
                    {
                        newPoints[newNum] = vertices[i];
                        ++newNum;
                    }

                    // copy new points back to polygon
                    vertices.resize(newNum);

                    for(i2 = 0; i2 < newNum; ++i2)
                    {
                        vertices[i2] = newPoints[i2];
                    }

//          std::cerr << "split in " << newNum << "," << poly.vertices.size() << std::endl;

                    // triangulate the new polygon
                    while(poly.intersectPolygon(globalverts, polylist) )
                    {
                    }
                    if(poly.isReversed(globalverts) )
                    {
//            std::cerr << "Ignoring reversed polygon." << std::endl;
                    }
                    else
                    {
                        // Ok, we have a valid polygon, so triangulate it.
                        poly.triangulate(globalverts, polylist);
                    }

                    // check if there are other intersections
                    return 1;
                }
            }
        }
    }

    // polygon had no intersections so we are finished
    return 0;
}

bool SimplePolygon::isReversed(DCTPVec2dvector &globalverts)
{
    unsigned int       ui_vertex;
    unsigned int       ui_upperleft;
    const unsigned int cui_vertex_cnt = UInt32(vertices.size());
    double             ad_p[2];
    double             ad_v[2];
    double             ad_n[2];

    ui_upperleft = 0;

    for(ui_vertex = 1; ui_vertex < cui_vertex_cnt; ++ui_vertex)
    {
        if(globalverts[vertices[ui_vertex]][1] < globalverts[vertices[ui_upperleft]][1])
        {
            ui_upperleft = ui_vertex;
        }
        else if( (globalverts[vertices[ui_vertex]][1] == globalverts[vertices[ui_upperleft]][1]) &&
                 (globalverts[vertices[ui_vertex]][0] < globalverts[vertices[ui_upperleft]][0]) )
        {
            ui_upperleft = ui_vertex;
        }
    }

    ad_p[0] = globalverts[vertices[(ui_upperleft + cui_vertex_cnt - 1) % cui_vertex_cnt]][0];
    ad_p[1] = globalverts[vertices[(ui_upperleft + cui_vertex_cnt - 1) % cui_vertex_cnt]][1];
    ad_v[0] = globalverts[vertices[ui_upperleft]][0];
    ad_v[1] = globalverts[vertices[ui_upperleft]][1];
    ad_n[0] = globalverts[vertices[(ui_upperleft + 1) % cui_vertex_cnt]][0];
    ad_n[1] = globalverts[vertices[(ui_upperleft + 1) % cui_vertex_cnt]][1];

    return (orient2d(ad_p, ad_v, ad_n) <= 0.0);
}

bool SimplePolygon::isConvex(DCTPVec2dvector &globalverts)
{
    unsigned int       ui_next;
    const unsigned int cui_vertex_cnt = UInt32(vertices.size());
    double             ad_p[2];
    double             ad_v[2];
    double             ad_n[2];

    ad_p[0] = globalverts[vertices[cui_vertex_cnt - 2]][0];
    ad_p[1] = globalverts[vertices[cui_vertex_cnt - 2]][1];
    ad_v[0] = globalverts[vertices[cui_vertex_cnt - 1]][0];
    ad_v[1] = globalverts[vertices[cui_vertex_cnt - 1]][1];

    for(ui_next = 0; ui_next < cui_vertex_cnt; ++ui_next)
    {
//		std::cerr <<"ui_next:" << ui_next << std::endl;
        ad_n[0] = globalverts[vertices[ui_next]][0];
        ad_n[1] = globalverts[vertices[ui_next]][1];
        // previous, current, and next vertices must be in
        // counterclockwise order for the polygon to be convex
        // (because our tessellator always gives CCW polygons)
        if(orient2d(ad_p, ad_v, ad_n) < 0.0)
        {
//			std::cerr << ad_p[ 0 ] << " " << ad_p[ 1 ] << std::endl;
//			std::cerr << ad_v[ 0 ] << " " << ad_v[ 1 ] << std::endl;
//			std::cerr << ad_n[ 0 ] << " " << ad_n[ 1 ] << std::endl << std::endl;
            // not convex
            return false;
        }
        ad_p[0] = ad_v[0];
        ad_p[1] = ad_v[1];
        ad_v[0] = ad_n[0];
        ad_v[1] = ad_n[1];
    }

//	std::cerr << "convex" << std::endl;
    return true;
}

// FIXME: should go to Vec2d
double SimplePolygon::getAngle(Vec2d dir)
{
    if(osgAbs(dir[0]) < DCTP_EPS)
    {
        return (dir[1] > 0.0) ? M_PI_2 : -M_PI_2;
    }
    if(dir[0] > 0.0)
    {
        return osgATan(dir[1] / dir[0]);
    }
    else
    {
        double ret = M_PI + osgATan(dir[1] / dir[0]);
        return (ret < M_PI) ? ret : (ret - 2.0 * M_PI);
    }
}

int SimplePolygon::getMinMax(DCTPVec2dvector &globalverts, Vec2d &min, Vec2d &max)
{
    if(vertices.size() == 0)
    {
        return -1;
    }
    min = max = globalverts[vertices[0]];

    for(unsigned int i = 1; i < vertices.size(); ++i)
    {
        Vec2d p = globalverts[vertices[i]];
        if(min[0] > p[0])
        {
            min[0] = p[0];
        }
        else if(max[0] < p[0])
        {
            max[0] = p[0];
        }
        if(min[1] > p[1])
        {
            min[1] = p[1];
        }
        else if(max[1] < p[1])
        {
            max[1] = p[1];
        }
    }

    return 0;
}
