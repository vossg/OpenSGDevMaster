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
#ifndef _OSG_DCTPVERTEX_H_
#define _OSG_DCTPVERTEX_H_
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


class DCTPFace;
class DCTPEdge;

class OSG_DRAWABLE_DLLMAPPING DCTPVertex
{
  public:
    DCTPVertex()
    {
        vertexinfo = NULL;
    }
    ~DCTPVertex() {}


    std::vector<DCTPEdge*> edges;
    std::vector<DCTPFace*> faces;
#ifdef OSG_INTEGER_MESH
    vec3i coords;
#else
    Vec3d coords;
#endif
    unsigned long id; // unique id of this vertex
    unsigned long node_id; // uniqe ID of the surface graph node
    void         *vertexinfo;

    void RemoveFace(DCTPFace *f)
    {
        std::vector<DCTPFace*>::iterator fe     = faces.end();
        bool                             erased = false;

        for(std::vector<DCTPFace*>::iterator i = faces.begin(); i != fe; ++i)
            if( (*i) == f)
            {
//        faces.erase( i );
                *i = faces[faces.size() - 1];
                faces.pop_back();
                erased = true;
                break;
            }

        if(!erased)
        {
            std::cerr << "DCTPVertex::RemoveFace: trying to remove nonexistant face..." << std::endl;
        }
    }
    void AddFace(DCTPFace *f)
    {
        std::vector<DCTPFace*>::iterator fe    = faces.end();
        bool                             found = false;

        for(std::vector<DCTPFace*>::iterator i = faces.begin(); i != fe; ++i)
            if( (*i) == f)
            {
                found = true; break;
            }

        if(!found)
            faces.push_back(f);
    }
    void RemoveEdge(DCTPEdge *e)
    {
        std::vector<DCTPEdge*>::iterator ee     = edges.end();
        bool                             erased = false;

        for(std::vector<DCTPEdge*>::iterator i = edges.begin(); i != ee; ++i)
            if( (*i) == e)
            {
//        edges.erase( i );
                *i = edges[edges.size() - 1];
                edges.pop_back();
                erased = true;
                break;
            }

        if(!erased)
            std::cerr << "DCTPVertex::RemoveEdge: trying to remove nonexistant edge..." << std::endl;
    }

    struct DCTPVertexless
    {
        bool operator()(DCTPVertex* v1, DCTPVertex* v2) const
        {
//    std::cerr << "comparing: " << v1->coords << " and" << std::endl;
//    std::cerr << "           " << v2->coords << std::endl;
//    std::cerr << "pointers:  " << v1 << " and" << std::endl;
//    std::cerr << "           " << v2 << std::endl;
//    bool k = v1->coords < v2->coords;
//    std::cerr << "result:    " << k << std::endl;
//    return k;
//    return (v1->coords < v2->coords);
            return DCTPVecIsLesser(v1->coords, v2->coords);
        }
    };

};

typedef std::set<DCTPVertex*, DCTPVertex::DCTPVertexless> dctpvertexset;

typedef std::vector<DCTPVertex*>      dctpvertexvector;
typedef std::vector<dctpvertexvector> dctpvertexmatrix;

OSG_END_NAMESPACE

#endif // DCTPVertex.h
