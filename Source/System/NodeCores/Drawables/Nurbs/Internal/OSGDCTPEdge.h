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
#ifndef _OSG_DCTPEDGE_H_
#define _OSG_DCTPEDGE_H_
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

/*
 * This define decides whether to use a std::set for storing the edges of the
 * mesh, or just use a std::vector. We originally thought using a set speeds
 * up some operations, but in practice for large models the vector data
 * structure actually works better (faster).
 *
 * Please note that if you decide to use a set, the "sorting" of the edges is
 * based on the lexicographic sort of the physical addresses of their vertices,
 * which means that you might get some edges "reversed" in the mesh from
 * the same input data. Due to the nature of the graph-traversing algorithm,
 * (it starts by searching a direted edge) you might get slightly different
 * different triangulations for the same surface in different runs.
 *
 * (Our) default is not to use a set (i.e. to use a vector).
 */
#define OSG_NO_EDGE_SET


class DCTPVertex;
OSG_END_NAMESPACE
//class DCTPFace;
#include "OSGDCTPFace.h"

OSG_BEGIN_NAMESPACE

class OSG_DRAWABLE_DLLMAPPING DCTPEdge
{
  public:
    inline  DCTPEdge(DCTPVertex * vx1, DCTPVertex * vx2, int orient);
    inline ~DCTPEdge(void                                          );

    inline void getVertices(DCTPVertex *&vx1, DCTPVertex *&vx2);
    inline void setVertices(DCTPVertex * vx1, DCTPVertex * vx2);

    inline void AddFace   (DCTPFace *f);
    inline void RemoveFace(DCTPFace *f);

  private:
    DCTPVertex *v1;
    DCTPVertex *v2;

  public:
    dctpfacevector faces;

  public:
    int orientation; // >0: first vertex->second vertex
                     // 0: not oriented
                     // <0: second vertec->first vertex
    unsigned long id; // unique id of this edge
    void         *edgeinfo;

#ifndef OSG_NO_EDGE_SET
    struct DCTPEdgeless
    {
        inline bool operator()(DCTPEdge *e1, DCTPEdge *e2) const;
    };
#endif


  private:

    DCTPEdge(const DCTPEdge &other);
    void operator =(const DCTPEdge &rhs);
};

#ifdef OSG_NO_EDGE_SET
typedef std::vector<DCTPEdge*                        > dctpedgevector;
#else
typedef std::set   <DCTPEdge*, DCTPEdge::DCTPEdgeless> dctpedgeset;
#endif

OSG_END_NAMESPACE

#include "OSGDCTPEdge.inl"

#endif // DCTPEdge.h
