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

OSG_BEGIN_NAMESPACE

inline TrimSegment::TrimSegment(void) :
    trimbeziers(),
    start      (NULL),
    end        (NULL)
{
    // nothing to do
}

inline TrimSegment::TrimSegment(const TrimSegment &ts) :
    trimbeziers(ts.trimbeziers),
    start      (ts.start      ),
    end        (ts.end        )
{
    // nothing to do
}

inline TrimSegment::~TrimSegment(void)
{
    // nothing to do
}


inline DCTPFace::DCTPFace(void) :
    vertices     (),
    edges        (),
#ifdef OSG_UNION_TRI_QUAD
    orig_face    (),
#else
    orig_triangle(),
    orig_quad    (),
#endif
    norm         (),
    id           (),
    trimseg      (),
    faceinfo     ()
{
    // nothing to do
}

inline DCTPFace::~DCTPFace(void)
{
    // nothing to do
}

inline void DCTPFace::AddVertex(DCTPVertex *v)
{
    //FIXME: check for adding existing vertex?
    vertices.push_back(v);
}

inline void DCTPFace::RemoveVertex(DCTPVertex *v)
{
    std::vector<DCTPVertex*> ::iterator ve      = vertices.end();
    bool                                removed = false;

    for(std::vector<DCTPVertex*>::iterator i = vertices.begin(); i != ve; ++i)
    {
        if(*i == v)
        {
            removed = true;
            vertices.erase(i);
            break;
        }
    }

    if(!removed)
        std::cerr << "DCTPFace::RemoveVertex: trying to remove nonexistant vertex..." << std::endl;
}

//to keep the order of the vertices
inline void DCTPFace::ReplaceVertex(DCTPVertex *oldv, DCTPVertex *newv)
{
    std::vector<DCTPVertex*> ::iterator ve       = vertices.end();
    bool                                replaced = false;

    for(std::vector<DCTPVertex*>::iterator i = vertices.begin(); i != ve; ++i)
    {
        if(*i == oldv)
        {
            replaced = true;
            *i       = newv;
            break;
        }
    }

    if(!replaced)
        std::cerr << "DCTPFace::ReplaceVertex: trying to replace nonexistant vertex..." << std::endl;
}

inline void DCTPFace::AddEdge(DCTPEdge *e)
{
    //FIXME: check for adding existing edge?
    edges.push_back(e);
}

inline void DCTPFace::RemoveEdge(DCTPEdge *e)
{
    std::vector<DCTPEdge*> ::iterator ee      = edges.end();
    bool                              removed = false;

    for(std::vector<DCTPEdge*>::iterator i = edges.begin(); i != ee; ++i)
    {
        if(*i == e)
        {
            removed = true;
            edges.erase(i);
            break;
        }
    }

    if(!removed)
        std::cerr << "DCTPFace::RemoveEdge: trying to remove nonexistant edge..." << std::endl;
}

inline void DCTPFace::dump_triangle(void)
{
#ifdef OSG_UNION_TRI_QUAD
//FIXME: operator<< deprecated
//      std::cerr << orig_face[ 0 ]->coords << ' ' << orig_face[ 1 ]->coords << ' ' << orig_face[ 2 ]->coords;
//    if( orig_face[ 3 ] ) std::cerr << ' ' << orig_face[ 3 ]->coords;
    std::cerr << std::endl;
#else
    if(orig_triangle[0])
//        std::cerr << orig_triangle[ 0 ]->coords << ' ' << orig_triangle[ 1 ]->coords
//             << ' ' << orig_triangle[ 2 ]->coords << std::endl;
        else
//        std::cerr << orig_quad[ 0 ]->coords << " " << orig_quad[ 1 ]->coords << " "
//             << orig_quad[ 2 ]->coords << " " << orig_quad[ 3 ]->coords << std::endl;
#endif
}

OSG_END_NAMESPACE
