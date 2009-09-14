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
#ifndef _OSG_GRAPHTRAVERSER_H_
#define _OSG_GRAPHTRAVERSER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "OSGDirectedGraph.h"
#include "OSGSimplePolygon.h"

OSG_BEGIN_NAMESPACE

static const int ERR_NO_TRIMMING = -1;
static const int ERR_GETNEXTEDGE = -2;
static const int ERR_ZERO_SIZE   = -3;
static const int ERR_ALL_ZERO    = -4;
static const int ERR_TRIANGULATE = -5;

class OSG_DRAWABLE_DLLMAPPING GraphTraverserError
{
  public:
    int errtype;

    GraphTraverserError()
    {
    }
    ~GraphTraverserError() {}
    GraphTraverserError(int t)
    {
        errtype = t;
    }
};

class OSG_DRAWABLE_DLLMAPPING GraphTraverser
{
    DirectedGraph<Vec2d, unsigned char>* g;
    simplepolygonvector                  polys;
    DCTPVec2dvector                      globalverts;
    bool                                 usedelaunay;

  public:
    GraphTraverser()
    {
    }
    ~GraphTraverser() {}
    void Initialize(DirectedGraph<Vec2d, unsigned char>& gg, bool
                    usedelaunaytri);
    int  getNextEdge(const int nodeid, const int previd /*const double& in_angle*/);
    int  Traverse(void);
    int  triangulatePolygon(DCTPivector& nodes, bool bConvex);
    int  getADirectedEdge(void);
    void handleEdge(int eid, int to_nid, int &from_nid /* double& ang*/);
    int  getOtherEnd(int eid, int nid);
    int  getOutGoingEdge(int nid);


    simplepolygonvector* getPolys()
    {
        return &polys;
    }
    DCTPVec2dvector* getVertices()
    {
        return &globalverts;
    }
};

OSG_END_NAMESPACE

#endif
