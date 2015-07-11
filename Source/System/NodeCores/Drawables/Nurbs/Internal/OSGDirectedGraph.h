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
#ifndef _OSG_DIRECTEDGRAPH_H_
#define _OSG_DIRECTEDGRAPH_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"


#include <iostream>
#include <fstream>
#include <iomanip>

#include "OSGdctptypes.h"

OSG_BEGIN_NAMESPACE

template <class T1>
class OSG_DRAWABLE_DLLMAPPING DirectedEdge
{
  public:
    bool direction; // true if directed
    int  from; // starting node
    int  to; // ending node
    bool valid;
    T1   edgeinfo;

    typedef std::vector <DirectedEdge<T1> > edgevector;

    DirectedEdge(void): 
        direction(true), from(0), to(0), valid(false), edgeinfo() {}
};


template <class T0>
class OSG_DRAWABLE_DLLMAPPING DirectedNode
{
  public:
    DCTPivector edges; // vector (pointers) of edges going to/from this node
    T0          nodeinfo;

    typedef std::vector <DirectedNode<T0> > nodevector;

    DirectedNode(void) : edges(), nodeinfo() {}
};

template <class T0, class T1>
class OSG_DRAWABLE_DLLMAPPING DirectedGraph
{

  public:
    DirectedGraph();
    // copy constructor
    DirectedGraph(const DirectedGraph &d) :
        nodes  (d.nodes  ),
        edges  (d.edges  ),
        invalid(d.invalid)
    {
    }
    ~DirectedGraph() {}

    int               AddNode(T0 &n); // add a new node
    int               AddEdge(T1 &t, int from, int to, bool direction); // add a new (possibly directed) edge
    int               DeleteEdge(int edgeidx); // delete edge specified by the index
    DCTPivector &     getEdges(int n); // get all edges (indexes) from a node
    DirectedNode<T0>& getNode(int nodeindex, int &error); // get one node
    DirectedEdge<T1>& getEdge(int edgeindex, int &error); // get one edge
    bool              getEdgeDirection(int edgeindex, int &error); // get one edge's direction
    int               setEdgeDirection(int edgeindex, int to); // set the direction of an edge
    int               changeEdgeDirection(int edgeindex); // change (invert) the direction of an edge
    int               FindNode(T0 &nodeinfo);
    int               FindEdge(int from, int to);

    bool isInvalid(void);


//private:

    typename DirectedNode<T0>::nodevector nodes;
    typename DirectedEdge<T1>::edgevector edges;
    bool invalid;
};

OSG_END_NAMESPACE

#include "OSGDirectedGraph.inl"

#endif // DirectedGraph.h
