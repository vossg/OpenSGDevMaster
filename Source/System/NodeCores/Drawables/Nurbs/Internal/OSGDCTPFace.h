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
#ifndef _OSG_DCTPFACE_H_
#define _OSG_DCTPFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGDrawableDef.h>
#include <OSGConfig.h>


#include <iostream>
#include <fstream>
#include <iomanip>

#include "OSGBezierCurve2D.h"
#include "OSGdctptypes.h"

OSG_BEGIN_NAMESPACE
#define OSG_UNION_TRI_QUAD

//class DCTPVertex;
OSG_END_NAMESPACE
#include "OSGDCTPVertex.h"

OSG_BEGIN_NAMESPACE
class DCTPEdge;

class OSG_DRAWABLE_DLLMAPPING TrimSegment
{
  public:
    inline  TrimSegment(void                 );
    inline  TrimSegment(const TrimSegment &ts);
    inline ~TrimSegment(void                 );

    bezier2dvector  trimbeziers;
    DCTPVertex     *start;
    DCTPVertex     *end;
};

class OSG_DRAWABLE_DLLMAPPING DCTPFace
{
  public:
    inline  DCTPFace(void);
    inline ~DCTPFace(void);

    std::vector<DCTPVertex*> vertices;
    std::vector<DCTPEdge*>   edges;

#ifdef OSG_UNION_TRI_QUAD
    DCTPVertex* orig_face[4];
#else
    DCTPVertex* orig_triangle[3];
    DCTPVertex* orig_quad[4];
#endif
    double                   norm;
    unsigned long            id;
    std::vector<TrimSegment> trimseg;
    void                    *faceinfo;

    inline void AddVertex    (DCTPVertex *v                     );
    inline void RemoveVertex (DCTPVertex *v                     );
    inline void ReplaceVertex(DCTPVertex *oldv, DCTPVertex *newv);

    inline void AddEdge   (DCTPEdge *e);
    inline void RemoveEdge(DCTPEdge *e);

    inline void dump_triangle(void);
};

typedef std::vector<DCTPFace*> dctpfacevector;

OSG_END_NAMESPACE

#include <OSGDCTPFace.inl>

#endif // DCTPFace.h
