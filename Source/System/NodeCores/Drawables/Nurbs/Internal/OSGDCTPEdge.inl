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

inline DCTPEdge::DCTPEdge(DCTPVertex * vx1, DCTPVertex * vx2, int orient)
{
#ifndef OSG_NO_EDGE_SET
    faces.clear();
    if(vx1 < vx2)
    {
        v1          = vx1;
        v2          = vx2;
        orientation = orient;
    }
    else
    {
        v1          = vx2;
        v2          = vx1;
        orientation = -orient;
    }
#else
    v1          = vx1;
    v2          = vx2;
    orientation = orient;
#endif /* OSG_NO_EDGE_SET */

    edgeinfo = NULL;
}

inline DCTPEdge::~DCTPEdge(void)
{
    // nothing to do
}

inline void DCTPEdge::getVertices(DCTPVertex* & vx1, DCTPVertex* & vx2)
{
    vx1 = v1;
    vx2 = v2;
}

inline void DCTPEdge::setVertices(DCTPVertex* vx1, DCTPVertex*  vx2)
{
#ifndef OSG_NO_EDGE_SET
    if(vx1 < vx2)
    {
        v1 = vx1;
        v2 = vx2;
    }
    else
    {
        v1 = vx2;
        v2 = vx1;
    }
#else
    v1 = vx1;
    v2 = vx2;
#endif /* OSG_NO_EDGE_SET */
}

inline void DCTPEdge::AddFace(DCTPFace *f)
{
    //    std::cerr << v1->coords << " " << v2->coords << f << std::endl;
    //FIXME: shouldn't warn always...
    //FIXME: check for adding existing face?
    if((faces.size() != 0) && (faces[0] == f))
        return;

    if(faces.size() >= 2)
    {
        if(faces[1] == f)
            return;

        std::cerr << "DCTPEdge::AddFace: third (nonmanifold) face supplied... " << faces.size() + 1 << std::endl;
        // FIXME: operator<< deprecated
        //      std::cerr << "I am: " << v1->coords << ' ' << v2->coords << std::endl;
        std::cerr << "The already existing triangles:\n";

        for(unsigned int i = 0; i < faces.size(); ++i)
        {
            std::cerr << "Ptr: " << static_cast<void*>(faces[i]) << ' ';
            faces[i]->dump_triangle();
        }

        std::cerr << "And the new one:\n";
        std::cerr << "Ptr: " << static_cast<void*>(f) << ' '; f->dump_triangle();
    }

    faces.push_back(f);
}

inline void DCTPEdge::RemoveFace(DCTPFace *f)
{
    dctpfacevector::iterator fe      = faces.end();
    bool                     removed = false;

    for(dctpfacevector::iterator i = faces.begin(); i != fe; ++i)
    {
        if(*i == f)
        {
            removed = true;
            faces.erase(i);
            break;
        }
    }

    if(!removed)
    {
        std::cerr << "DCTPEdge::RemoveFace: trying to remove nonexistant face..." << std::endl;
    }
}

#ifndef OSG_NO_EDGE_SET
inline bool DCTPEdge::DCTPEdgeless::operator ()(
    DCTPEdge *e1, DCTPEdge *e2) const
{
    DCTPVertex *e1v1;
    DCTPVertex *e1v2;
    DCTPVertex *e2v1;
    DCTPVertex *e2v2;
    e1->        getVertices(e1v1, e1v2);
    e2->        getVertices(e2v1, e2v2);

    if((e1v1 < e2v1) || (e1v1 == e2v1 && e1v2 < e2v2))
        return true;
    else
        return false;
}
#endif

OSG_END_NAMESPACE
