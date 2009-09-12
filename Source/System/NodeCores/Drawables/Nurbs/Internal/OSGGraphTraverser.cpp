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

#include <OSGLog.h>

#include "OSGGraphTraverser.h"
#include "OSGpredicates.h"
#include "OSGNurbsPatchSurface.h"    // for defines...

OSG_USING_NAMESPACE


#ifdef WIN32
#pragma warning (disable : 985)
#endif

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif


/***********************************************************/
void GraphTraverser::Initialize(DirectedGraph<Vec2d, unsigned char>& gg, bool
                                usedelaunaytri)
{
    g = &gg;
    unsigned int ee = g->nodes.size();
    globalverts.resize(ee);

    for(unsigned int i = 0; i < ee; ++i)
        globalverts[i] = g->nodes[i].nodeinfo;

    usedelaunay = usedelaunaytri;
    polys.clear();
}



int GraphTraverser::triangulatePolygon(DCTPivector& nodes, bool bConvex)
{
#ifdef OSG_NURBS_DEBUG
    unsigned int i;
#endif

    SimplePolygon actpoly;
    actpoly.vertices  = nodes;
    actpoly.is_marked = !usedelaunay;
#ifdef OSG_TRIANGULATE_CONVEX
    if(bConvex)
    {
        actpoly.m_bConvex = bConvex;
//	std::cerr <<"convex bcoz of bConvex" << std::endl;
    }
    else if(nodes.size() > 4)
    {
        actpoly.m_bConvex = actpoly.isConvex(globalverts);
//	std::cerr <<"isconvex: " <<actpoly.m_bConvex << std::endl;
    }
//  std::cerr << "convex: " << actpoly.m_bConvex << std::endl;
#endif

/*
  if( !m_bTriangulate )
  {
      polys.push_back( actpoly );
      return 0;
  }
*/
//  std::cerr << "calling triangulate... polyno:" << polys.size() << std::endl;
//  std::cerr << "calling triangulate... nodes:" << nodes.size() << std::endl;
    std::vector<SimplePolygon> newpolys;

    int err =  actpoly.triangulate(globalverts, newpolys);
    if( (err) && (usedelaunay) )
    {
        // delaunay didn't work, so try any triangulation
        newpolys.clear();
        actpoly.is_marked = 1;
        err               = actpoly.triangulate(globalverts, newpolys);
    }
    if(err)
    {
        // simple triagulation didn't work, so try to fix polygon
        newpolys.clear();
        actpoly.fixAndTriangulate(globalverts, newpolys);
    }
    polys.insert(polys.end(), newpolys.begin(), newpolys.end() );
#ifdef OSG_NURBS_DEBUG
    if(err)
    {
//    std::cerr <<"polyno after error: " << polys.size() << std::endl;
//DEBUG
        //check for duplicated vertices passed to triangulate
        DCTPVec2dset                              vset;
        std::set <int>                            iset;
        std::pair<DCTPVec2dset::iterator, bool>   siv;
        std::pair<std::set <int>::iterator, bool> niv;
        unsigned int                              k = nodes.size();
        std::cerr << "nodeids:";

        for(i = 0; i < k; ++i)
            std::cerr << " " << nodes[i];

        std::cerr << std::endl;

        for(i = 0; i < k; ++i)
        {
            siv = vset.insert(globalverts[nodes[i]]);
            if(!siv.second)
            {
                std::cerr << "duplicate vertex passed: " << globalverts[nodes[i]] << " i: " << i << std::endl;;
            }
            niv = iset.insert(nodes[i]);
            if(!niv.second)
            {
                std::cerr << "duplicate vertex index passed: " << nodes[i] << " i: " << i << std::endl;
            }
        } // for

//DEBUG END

/*    std::cerr << "Dumping info: " << std::endl;
    std::cerr.precision( 16 );
    std::cerr << nodes.size() << std::endl;
    for ( unsigned int i = 0; i < nodes.size(); ++i ) {
      std::cerr.precision( 16 );
      std::cerr  << globalverts[ nodes[ i ] ] << std::endl;
    }
    std::cerr << std::endl;*/

//    throw GraphTraverserError( GraphTraverserError::ERR_TRIANGULATE );
    } //if err
#endif /* OSG_NURBS_DEBUG */

//  std::cerr << " we have now: " << polys.size() << " triangles." << std::endl;
//  std::cerr <<"triangulate out " << std::endl;
    return 0;
}

int GraphTraverser::getADirectedEdge(void)
{
    static bool beenhere = false;
    if(!beenhere)
        beenhere = true;
    unsigned int e     = g->edges.size();
    bool         found = false;

    for(unsigned int i = 0; i < e; ++i)
        if(g->edges[i].direction && g->edges[i].valid)
        {
            e = i; found = true; break;
        }

    if(!found && !beenhere)
    {
        std::cerr << "No trimming thingie found!" << std::endl;
        throw GraphTraverserError(ERR_NO_TRIMMING);
//		abort();
    }
    else if(!found)
        return -1;
//        writeBoundary( e );
    return e;
}

void GraphTraverser::handleEdge(int eid, int to_nid, int &from_nid /* double& ang*/)
{
//        int from_nid;
    if(g->edges[eid].to == to_nid)
        from_nid = g->edges[eid].from;
    else
        from_nid = g->edges[eid].to;
/*        Vec2d edge_vect =
                g->nodes[ from_nid ].nodeinfo - g->nodes[ to_nid ].nodeinfo;
        ang = osgATan2( edge_vect[1], edge_vect[0] );
        if ( ang < 0.0 ) ang = 2 * M_PI + ang;*/
    if(g->edges[eid].direction)
        g->DeleteEdge(eid);
    else
        g->setEdgeDirection(eid, from_nid);
}

int GraphTraverser::getOtherEnd(int eid, int nid)
{
    DirectedEdge<unsigned char>& e = g->edges[eid];

    if(e.to == nid)
    {
//			std::cerr << "following edge reversed " << eid << " -> " << e.from << std::endl;
        return e.from;
    }
    else
    {
//			std::cerr << "following edge " << eid << " -> " << e.to << std::endl;
        return e.to;
    }
}

int GraphTraverser::getOutGoingEdge(int nid)
{
    DCTPivector::iterator ee = g->nodes[nid].edges.end();

    for(DCTPivector::iterator i = g->nodes[nid].edges.begin();
        i != ee; ++i)
        if(g->edges[*i].direction &&
           g->edges[*i].from == nid)
            return *i;

    return -1;
}

int GraphTraverser::Traverse(void)
{

    //first find a directed edge
    bool b_convex;
    int  edgeID = getADirectedEdge();
    while(edgeID != -1)
    {
        b_convex = (g->edges[edgeID].edgeinfo == 0);
        int         start_node = g->edges[edgeID].from;
        int         leave      = -1, act_node = g->edges[edgeID].to;
        int         last_node;
        DCTPivector node_ids;
        node_ids.push_back(start_node);
        node_ids.push_back(act_node);
        while(edgeID != -1)
        {
            if(g->edges[edgeID].edgeinfo)
                b_convex = false;
            handleEdge(edgeID, act_node, last_node);
            edgeID = getNextEdge(act_node, last_node);
            if(edgeID == -1)
                break;
//			std::cerr << "edgeID: " << edgeID << " g->edges[edgeID]: " << (void*) &g->edges[ edgeID ] << std::endl;
//			std::cerr << "g->edges[ edgeID ].direction: " << g->edges[ edgeID ].direction << std::endl;
            if(!g->edges[edgeID].direction && leave < 0)
                leave = act_node;
            act_node = getOtherEnd(edgeID, act_node);
            if(start_node == act_node)     //a polygon finished
            {
                if(g->edges[edgeID].edgeinfo)
                    b_convex = false;
                handleEdge(edgeID, start_node, last_node);
                triangulatePolygon(node_ids, b_convex);
                b_convex = true;
                node_ids.clear();
//				std::cerr << " act_node: " << act_node << " start_node: " << start_node << " leave: " << leave << std::endl;
                start_node = leave; leave = -1;
                if(start_node != -1)
                {
                    node_ids.push_back(start_node);
                    edgeID   = getOutGoingEdge(start_node);
                    act_node = getOtherEnd(edgeID, start_node);
//					std::cerr << "new actnode: " << act_node << std::endl;
                    node_ids.push_back(act_node);
                }
                else
                    edgeID = -1;
            }
            else
            {
                const int ci_size2 = node_ids.size() - 2;
                if(ci_size2 >= 0)
                {
                    if(node_ids[ci_size2] == act_node)
                    {
                        // went in a dead end => delete last two nodes
                        node_ids.resize(ci_size2);
                    }
                }
                node_ids.push_back(act_node);
            }
        }
        edgeID = getADirectedEdge();
    }
    return 0;
}

int GraphTraverser::getNextEdge(const int nodeid, const int previd /*const double& in_angle*/)
{
    Vec2d prev_vect = g->nodes[previd].nodeinfo;
    Vec2d node_vect = g->nodes[nodeid].nodeinfo;
    int   en        = g->nodes[nodeid].edges.size();   //numbah o' 3dg4z

    if(en == 1)         //most common case, along trimming curves over faces
    {
        int e0 = g->nodes[nodeid].edges[0];
/*                if ( g->edges[ e0 ].from == nodeid &&
                     g->edges[ e0 ].direction )
                {
//					std::cerr << "tracing along graph " << nodeid << " -> " << e0 << std::endl;
                    return e0;
                }*/
        if( (g->edges[e0].from == nodeid) ||
            (g->edges[e0].to == nodeid) )
        {
            return e0;
        }
        std::cerr << "Error " << nodeid << " <-> " << g->edges[e0].from << " -> " << g->edges[e0].to << std::endl;
        std::cerr << "Error in GraphTraverser::getNextEdge()." << std::endl;
        throw GraphTraverserError(ERR_GETNEXTEDGE);
//                abort();
    }

    DCTPivector eid;     //edge ids
//        dvector ea; //edge angles

    DCTPivector::iterator ee = g->nodes[nodeid].edges.end();

    for(DCTPivector::iterator iv = g->nodes[nodeid].edges.begin();
        iv != ee; ++iv)
    {
        DirectedEdge<unsigned char>& act_edge = g->edges[*iv];
        if( ( (!act_edge.direction) || (act_edge.to != nodeid) ) &&
            ( (act_edge.from != nodeid) || (act_edge.to != previd) ) &&
            ( (act_edge.to != nodeid) || (act_edge.from != previd) ) )
        {
            eid.push_back(*iv);
/*                DirectedNode< Vec2d > *nptr;
                if ( act_edge.to == nodeid )
                        nptr = &( g->nodes[ act_edge.from ] );
                else nptr = &( g->nodes[ act_edge.to ] );
                Vec2d v = nptr->nodeinfo - node_vect;
                double tmp = osgATan2( v[1], v[0] );
                if ( tmp < 0.0 ) tmp = 2 * M_PI + tmp;
                ea.push_back( tmp );
                std::cerr << tmp << ", ";*/
        }
    }

//		std::cerr << std::endl;
    //DEBUG:
    if(/*eid.size() != ea.size() ||*/ eid.size() == 0)
    {
//          std::cerr << "eid.size(): " << eid.size() << " ea.size(): " << ea.size() << std::endl;
//          throw GraphTraverserError( ERR_ZERO_SIZE );
        return -1;
    }
    //END DEBUG
    double       a[2], b[2], c[2], d[2];
    unsigned int eae      = eid.size();
    int          leftmost = 0;
//		std::cerr << prev_vect << " -> " << node_vect << std::endl;
    a[0] = prev_vect[0];
    a[1] = prev_vect[1];
    b[0] = node_vect[0];
    b[1] = node_vect[1];
    if(g->edges[eid[0]].to == nodeid)
    {
        c[0] = g->nodes[g->edges[eid[0]].from].nodeinfo[0];
        c[1] = g->nodes[g->edges[eid[0]].from].nodeinfo[1];
    }
    else
    {
        c[0] = g->nodes[g->edges[eid[0]].to].nodeinfo[0];
        c[1] = g->nodes[g->edges[eid[0]].to].nodeinfo[1];
    }
//		std::cerr << node_vect << " -> (" << c[ 0 ] << ", " << c[ 1 ] << ")" << std::endl;
    double orient = orient2d(a, b, c);

//        std::cerr << "in_angle: " << in_angle << std::endl;
    for(unsigned int i = 1; i < eae; ++i)
    {
//			std::cerr << "checking edge " << i << std::endl;
        if(g->edges[eid[i]].to == nodeid)
        {
            d[0] = g->nodes[g->edges[eid[i]].from].nodeinfo[0];
            d[1] = g->nodes[g->edges[eid[i]].from].nodeinfo[1];
        }
        else
        {
            d[0] = g->nodes[g->edges[eid[i]].to].nodeinfo[0];
            d[1] = g->nodes[g->edges[eid[i]].to].nodeinfo[1];
        }
//			std::cerr << node_vect << " -> (" << d[ 0 ] << ", " << d[ 1 ] << ")" << std::endl;
        double tmp = orient2d(a, b, d);
//			std::cerr << orient << " " << tmp << std::endl;
        // fails, if both are = 0.0, but next test would fail too...
//			std::cerr << orient2d( b, c, d ) << std::endl;
        if( (orient < 0.0) || (tmp > 0.0) )
        {
            if( ( (tmp > 0.0) && (orient <= 0.0) ) ||
                ( (tmp == 0.0) && (orient < 0.0) ) ||
                (orient2d(b, c, d) > 0.0) )
            {
//					std::cerr << b[ 0 ] << ", " << b[ 1 ] << std::endl;
//					std::cerr << c[ 0 ] << ", " << c[ 1 ] << std::endl;
//					std::cerr << d[ 0 ] << ", " << d[ 1 ] << std::endl;
//                  std::cerr << "found better edge!" << std::endl;
                orient   = tmp;
                leftmost = i;
                c[0]     = d[0];
                c[1]     = d[1];
//					std::cerr << node_vect << " -> (" << c[ 0 ] << ", " << c[ 1 ] << ")" << std::endl;
            }
        }
/*			double tmp = ea[ i ] - in_angle;
//			std::cerr << " tmp before" << tmp << "ea[i]: " << ea[i] << std::endl;
            if ( tmp < 0.0 ) tmp = 2 * M_PI + tmp;
//			std::cerr << "tmp: " << tmp << "angle: " << angle << std::endl;
            if ( tmp > angle ) { leftmost = i; angle = tmp; }*/
    }

//		if ( leftmost == -1 ) throw GraphTraverserError( GraphTraverserError::ERR_ALL_ZERO );
//		std::cerr << "leftmost: " << leftmost << "eae: " << eae << std::endl;
//		std::cerr << "going left on graph " << nodeid << " -> " << eid[ leftmost ] << std::endl;
    return eid[leftmost];
}
