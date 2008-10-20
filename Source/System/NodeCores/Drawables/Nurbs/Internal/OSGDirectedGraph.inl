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
//#include "DirectedGraph.h"
#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

// default constructor
template <typename T0, typename T1>
DirectedGraph<T0, T1>::DirectedGraph()
{
  invalid = true;
}

// add a new node
// returns node index 
template <typename T0, typename T1>
int DirectedGraph<T0, T1>::AddNode( T0 &n )
{
  DirectedNode<T0> nn;
  nn.nodeinfo = n;
  nodes.push_back( nn );
  return nodes.size() - 1;
} 

// add a new (possibly directed) edge 
// returns edge index or -1
template <typename T0, typename T1>
int DirectedGraph<T0, T1>::AddEdge( T1 &t, int from, int to, bool direction)
{
  if ( from < 0 || from >= nodes.size() ||
       to < 0 || to >= nodes.size() ) return -1;

  DirectedEdge<T1> e;
  int eidx;
  e.edgeinfo = t;
  e.from = from;
  e.to = to;
  e.direction = direction;
  e.valid = true; //DEBUG
  edges.push_back( e );
  eidx = edges.size() - 1;

  nodes[ from ].edges.push_back( eidx );
  nodes[ to ].edges.push_back( eidx );  
  return eidx;
}

// delete edge specified by index
template <typename T0, typename T1>
int DirectedGraph<T0, T1>::DeleteEdge( int edgeidx )
{
  if ( edgeidx < 0 || edgeidx >= edges.size() )
    return -1;

  // note: we don't need to actually erase from here
//  edges.erase( edgeidx );

  edges[ edgeidx ].valid = false;

  DirectedNode<T0> &fromnode = nodes[ edges [ edgeidx ].from ];
  DCTPivector::iterator nee = fromnode.edges.end();
  DCTPivector::iterator i;
  for( i = fromnode.edges.begin(); i != nee; ++i )
    if ( *i == edgeidx ) {
      fromnode.edges.erase( i );
      break;
    }

  DirectedNode<T0> &tonode = nodes[ edges [ edgeidx ].to ];
  nee = tonode.edges.end();
  for( i = tonode.edges.begin(); i != nee; ++i )
    if ( *i == edgeidx ) {
      tonode.edges.erase( i );
      break;
    }

  return 0;
}




template <typename T0, typename T1>
DCTPivector & DirectedGraph<T0, T1>::getEdges( int n ) // get all edges (indexes) from a node
{
  return &nodes.edges;
}

// get one node
template <typename T0, typename T1>
DirectedNode<T0>& DirectedGraph<T0, T1>::getNode( int nodeindex, int &error )
{
  error = 0;
  if ( nodeindex < 0 || nodeindex >= nodes.size() ) {
    error = -1;
    return NULL;
  }
  return &nodes[ nodeindex ] ;
}

// get one edge
template <typename T0, typename T1>
DirectedEdge<T1>& DirectedGraph<T0, T1>::getEdge( int edgeindex, int &error )
{
  error = 0;
  if ( edgeindex < 0 || edgeindex >= edges.size() ) {
    error = -1;
    return NULL;
  }
  return &edges[ edgeindex ] ;
}

// get one edge's direction
template <typename T0, typename T1>
bool DirectedGraph<T0, T1>::getEdgeDirection( int edgeindex, int &error )
{
  error = 0;
  if ( edgeindex < 0 || edgeindex >= edges.size() ) {
    error = -1;
    return NULL;
  }

  return edges[ edgeindex ].orientation;
}

// set the direction of an edge
template <typename T0, typename T1>
int DirectedGraph<T0, T1>::setEdgeDirection( int edgeindex, int to )
{
  if ( edgeindex < 0 || edgeindex >= edges.size() ) return -1;

  if ( edges[ edgeindex ].from != to && edges[ edgeindex ].to != to )
    return -1;
  if ( edges[ edgeindex ].to != to ) {
    int tmp = edges[ edgeindex ].to;
    edges[ edgeindex ].to = to;
    edges[ edgeindex ].from = tmp;
  }
  edges[ edgeindex ].direction = true;
  return 0;
}

// change (invert) the direction of an edge
template <typename T0, typename T1>
int DirectedGraph<T0, T1>::changeEdgeDirection( int edgeindex )
{
  if ( edgeindex < 0 || edgeindex >= edges.size() )
    return -1;
  if ( !edges[ edgeindex ].orientation )
    return -1;

  int tmp = edges[ edgeindex ].to;
  edges[ edgeindex ].to = edges[ edgeindex ].from;
  edges[ edgeindex ].from = tmp;

  return 0;
}

template <typename T0, typename T1>
bool DirectedGraph<T0, T1>::isInvalid( void )
{
  return invalid;
}

template <typename T0, typename T1>
int DirectedGraph<T0, T1>::FindNode( T0 &nodeinfo )
{
	for( unsigned int i = 0; i < nodes.size( ); ++i )
	{
		if( nodes[ i ].nodeinfo == nodeinfo ) return i;
	}

	return -1;
}

template <typename T0, typename T1>
int DirectedGraph<T0, T1>::FindEdge( int from, int to )
{
	for( unsigned int i = 0; i < edges.size( ); ++i )
	{
//		std::cerr << "checking edge from " << edges[ i ].from << " to " << edges[ i ].to << std::endl;
		if( ( edges[ i ].from == from ) &&
			( edges[ i ].to == to ) ) return i;
		if( ( edges[ i ].from == to ) &&
			( edges[ i ].to == from ) ) return i;
	}

	return -1;
}

OSG_END_NAMESPACE
