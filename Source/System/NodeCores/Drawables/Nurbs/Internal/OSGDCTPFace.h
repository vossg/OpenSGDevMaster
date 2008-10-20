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
    TrimSegment()
    {
        start = end = NULL;
    }
    TrimSegment(const TrimSegment &ts)
    {
        trimbeziers = ts.trimbeziers;
        start       = ts.start;
        end         = ts.end;
    }
    ~TrimSegment() {}
    bezier2dvector trimbeziers;
    DCTPVertex    *start;
    DCTPVertex    *end;
};

class OSG_DRAWABLE_DLLMAPPING DCTPFace
{
  public:
    DCTPFace()
    {
    }
    ~DCTPFace() {}

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
    void AddVertex(DCTPVertex *v)
    {
        //FIXME: check for adding existing vertex?
        vertices.push_back(v);
    }
    void RemoveVertex(DCTPVertex *v)
    {
        std::vector<DCTPVertex*> ::iterator ve      = vertices.end();
        bool                                removed = false;

        for(std::vector<DCTPVertex*>::iterator i = vertices.begin(); i != ve; ++i)
            if(*i == v)
            {
                removed = true;
                vertices.erase(i);
                break;
            }

        if(!removed)
            std::cerr << "DCTPFace::RemoveVertex: trying to remove nonexistant vertex..." << std::endl;
    }
    //to keep the order of the vertices
    void ReplaceVertex(DCTPVertex *oldv, DCTPVertex *newv)
    {
        std::vector<DCTPVertex*> ::iterator ve       = vertices.end();
        bool                                replaced = false;

        for(std::vector<DCTPVertex*>::iterator i = vertices.begin(); i != ve; ++i)
            if(*i == oldv)
            {
                replaced = true;
                *i       = newv;
                break;
            }

        if(!replaced)
            std::cerr << "DCTPFace::ReplaceVertex: trying to replace nonexistant vertex..." << std::endl;
    }
    void AddEdge(DCTPEdge *e)
    {
        //FIXME: check for adding existing edge?
        edges.push_back(e);
    }
    void RemoveEdge(DCTPEdge *e)
    {
        std::vector<DCTPEdge*> ::iterator ee      = edges.end();
        bool                              removed = false;

        for(std::vector<DCTPEdge*>::iterator i = edges.begin(); i != ee; ++i)
            if(*i == e)
            {
                removed = true;
                edges.erase(i);
                break;
            }

        if(!removed)
        {
            std::cerr << "DCTPFace::RemoveEdge: trying to remove nonexistant edge..." << std::endl;
        }
    }
    void dump_triangle(void)
    {
#ifdef OSG_UNION_TRI_QUAD
//FIXME: operator<< deprecated
//      std::cerr << orig_face[ 0 ]->coords << ' ' << orig_face[ 1 ]->coords << ' ' << orig_face[ 2 ]->coords;
//	  if( orig_face[ 3 ] ) std::cerr << ' ' << orig_face[ 3 ]->coords;
        std::cerr << std::endl;
#else
        if(orig_triangle[0])
//        std::cerr << orig_triangle[ 0 ]->coords << ' ' << orig_triangle[ 1 ]->coords
//             << ' ' << orig_triangle[ 2 ]->coords << std::endl;
            else
//		  std::cerr << orig_quad[ 0 ]->coords << " " << orig_quad[ 1 ]->coords << " "
//			   << orig_quad[ 2 ]->coords << " " << orig_quad[ 3 ]->coords << std::endl;
#endif
    }

};

typedef std::vector<DCTPFace*> dctpfacevector;

OSG_END_NAMESPACE

#endif // DCTPFace.h
