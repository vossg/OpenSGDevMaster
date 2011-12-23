/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
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

// HalfEdge

inline
void StriperHalfEdgeGraph::HalfEdge::setVertex(
    StriperHalfEdgeGraph::IndexT startVertexIndex,
    StriperHalfEdgeGraph::IndexT
    OSG_CHECK_ARG(endVertexIndex))
{
    _vertexIndex = startVertexIndex;
}

inline
StriperHalfEdgeGraph::IndexT StriperHalfEdgeGraph::HalfEdge::vertexStart(void)
{
    return _vertexIndex;
}

inline
StriperHalfEdgeGraph::IndexT StriperHalfEdgeGraph::HalfEdge::vertexEnd(void)
{
    return next->_vertexIndex;
}

// Triangle

inline
void StriperHalfEdgeGraph::Triangle::init(void)
{
    state = DEGREE_0;
    next = prev = 0;
    halfEdgeVec[0].next = &(halfEdgeVec[1]);
    halfEdgeVec[0].triangle = this;
    halfEdgeVec[1].next = &(halfEdgeVec[2]);
    halfEdgeVec[1].triangle = this;
    halfEdgeVec[2].next = &(halfEdgeVec[0]);
    halfEdgeVec[2].triangle = this;
}

inline
bool StriperHalfEdgeGraph::Triangle::valid (void)
{
    return (state >= DEGREE_0) ? true : false; 
}

inline
void StriperHalfEdgeGraph::Triangle::resetDegreeState(const Int32 type)
{
    state = (halfEdgeVec[0].twin && 
            (halfEdgeVec[0].twin->triangle->state >= type) ? 1 : 0) +
            (halfEdgeVec[1].twin && 
            (halfEdgeVec[1].twin->triangle->state >= type) ? 1 : 0) +
            (halfEdgeVec[2].twin && 
            (halfEdgeVec[2].twin->triangle->state >= type) ? 1 : 0);
}

inline
void StriperHalfEdgeGraph::Triangle::drop(void)
{
    if(halfEdgeVec[0].twin && (halfEdgeVec[0].twin->triangle->state > 0))
        halfEdgeVec[0].twin->triangle->state--;
    if(halfEdgeVec[1].twin && (halfEdgeVec[1].twin->triangle->state > 0))
        halfEdgeVec[1].twin->triangle->state--;
    if(halfEdgeVec[2].twin && (halfEdgeVec[2].twin->triangle->state > 0))
        halfEdgeVec[2].twin->triangle->state--;
}

// TriangleList

inline
StriperHalfEdgeGraph::TriangleList::TriangleList(void)
    : first(0), last(0)
    {
    }

inline
void StriperHalfEdgeGraph::TriangleList::reset(void)
{
    first = 0; last = 0;
}

inline
bool StriperHalfEdgeGraph::TriangleList::empty(void)
{
    return first ? false : true;
}

inline
UInt32 StriperHalfEdgeGraph::TriangleList::countElem(void)
{
    UInt32 count = 0;
    for(Triangle *f = first; f; f = f->next)
        ++count;
    return count;
}

inline
void StriperHalfEdgeGraph::TriangleList::release(Triangle &node)
{
    if(node.next)
    {
        if(node.prev)
        {
            node.next->prev = node.prev;
            node.prev->next = node.next;
        }
        else
        {
            node.next->prev = 0;
            this->first = node.next;
        }
    }
    else
    {
        if(node.prev)
        {
            node.prev->next = 0;
            this->last = node.prev;
        }
        else
        {
            this->first = 0;
            this->last = 0;
        }
    }
    node.next = node.prev = 0;
}

inline
void StriperHalfEdgeGraph::TriangleList::add(Triangle &triangle)
{
    if(last)
    {
        last->next = &triangle;
        triangle.prev = last;
        last = &triangle;
    }
    else
    {
        last = &triangle;
        first = &triangle;
    }
}

inline
void StriperHalfEdgeGraph::TriangleList::paste(TriangleList &list)
{
    if(&list != this)
    {
        if(empty())
        {
            first = list.first;
            last  = list.last;
        }
        else
        {
            if(list.first)
            {
                last->next = list.first;
                list.first->prev = last;
                last = list.last;
            }
        }
        list.first = 0;
        list.last  = 0;
    }
}

// TrianglePool::Chunk

inline
StriperHalfEdgeGraph::TrianglePool::Chunk::Chunk(const UInt32 size)
    : _size(size), _freeElem(size), _next(0) 
{
    _data = new Triangle[size];
}

inline
StriperHalfEdgeGraph::TrianglePool::Chunk::~Chunk(void)
{
    delete [] _data;
    delete _next;
}

inline
UInt32 StriperHalfEdgeGraph::TrianglePool::Chunk::countElem(void)
{
    return ((_size - _freeElem) + (_next ? _next->countElem() : 0));
}

// TrianglePool

inline
StriperHalfEdgeGraph::TrianglePool::TrianglePool(UInt32 chunkSize) 
    : _defaultChunkSize(chunkSize), _first(0), _last(0)
{
}

inline
StriperHalfEdgeGraph::TrianglePool::~TrianglePool(void)
{
    clear();
}

inline
StriperHalfEdgeGraph::Triangle *StriperHalfEdgeGraph::TrianglePool::createTriangle(void)
{
    if(!_first)
    {
        _first = _last = new Chunk(_defaultChunkSize);
    }
    else
    {
        if(_last->_freeElem == 0) 
            _last = _last->_next = new Chunk(_defaultChunkSize);
    }
    return &(_last->_data[_last->_size - _last->_freeElem--]);
}

inline
void StriperHalfEdgeGraph::TrianglePool::clear(void)
{
    delete _first;
    _first = _last = 0;
}

inline
UInt32 StriperHalfEdgeGraph::TrianglePool::countElem(void)
{
    return (_first ? _first->countElem() : 0);
}

inline
void StriperHalfEdgeGraph::TrianglePool::setChunkSize(UInt32 chunkSize)
{
    _defaultChunkSize = chunkSize;
}

// HalfEdgeGraph

inline
void StriperHalfEdgeGraph::dropOutTriangle(Triangle &triangle, 
                                           TriangleList *degreeBag)
{
    HalfEdge *twin;
    degreeBag[triangle.state].release(triangle);
    triangle.state = STRIP_PART;

    if((twin = triangle.halfEdgeVec[0].twin) && (twin->triangle->state > 0))
    {
        degreeBag[twin->triangle->state--].release(*twin->triangle);
        degreeBag[twin->triangle->state].add(*twin->triangle);
    }

    if((twin = triangle.halfEdgeVec[1].twin) && (twin->triangle->state > 0))
    {
        degreeBag[twin->triangle->state--].release(*twin->triangle);
        degreeBag[twin->triangle->state].add(*twin->triangle);
    }

    if((twin = triangle.halfEdgeVec[2].twin) && (twin->triangle->state > 0))
    {
        degreeBag[twin->triangle->state--].release(*twin->triangle);
        degreeBag[twin->triangle->state].add(*twin->triangle);
    }
}

inline
StriperHalfEdgeGraph::HalfEdge *StriperHalfEdgeGraph::getHalfEdge(
    UInt32 startVertexIndex,
    UInt32 endVertexIndex)
{
    UInt32 i, n = UInt32(_edgeLinkVec.size());
    const HalfEdgeLink *edgeLink((startVertexIndex < n) ?
        &_edgeLinkVec[startVertexIndex] : 0);

    HalfEdge *halfEdge = 0;

    if (edgeLink && (n = UInt32(edgeLink->size())))
    {
        for (i = 0; i < n; ++i)
        {
            if ((*edgeLink)[i].first == endVertexIndex)
            {
                halfEdge = (*edgeLink)[i].second;
                break;
            }
        }
    }

    return halfEdge;
}

inline
void StriperHalfEdgeGraph::addHalfEdge(HalfEdge &halfEdge, 
                                       UInt32 startVertexIndex,
                                       UInt32 endVertexIndex)
{
    UInt32 n = UInt32(_edgeLinkVec.size());
    bool     validIndex(startVertexIndex < n);
    HalfEdge *twin(validIndex ?
        getHalfEdge(endVertexIndex, startVertexIndex) : 0);

    halfEdge.setVertex(startVertexIndex,endVertexIndex);

    if(validIndex == false)
        _edgeLinkVec.resize(startVertexIndex * 2);

    _edgeLinkVec[startVertexIndex].
        push_back(std::pair<StriperHalfEdgeGraph::IndexT,HalfEdge*>(
                      endVertexIndex,
                      &halfEdge));

    if((halfEdge.twin = twin))
    {
        twin->twin = &halfEdge;
        halfEdge.triangle->state++;
        twin->triangle->state++;
    }
} 

inline
StriperHalfEdgeGraph::HalfEdge *StriperHalfEdgeGraph::findGateEdge(
    Triangle *triangleOut,
    Triangle *triangleIn)
{
    StriperHalfEdgeGraph::HalfEdge *halfEdge = 0;

    if(triangleOut && triangleIn)
        if(!(halfEdge = triangleOut->halfEdgeVec[0].twin) || 
            (halfEdge->triangle != triangleIn))
            if(!(halfEdge = triangleOut->halfEdgeVec[1].twin) || 
                (halfEdge->triangle != triangleIn))
                if(!(halfEdge = triangleOut->halfEdgeVec[2].twin) || 
                    (halfEdge->triangle != triangleIn))
                    halfEdge = 0;

    return halfEdge ? halfEdge->twin : 0;
}

inline
bool StriperHalfEdgeGraph::addTriangle(StriperHalfEdgeGraph::IndexT v0,
                                       StriperHalfEdgeGraph::IndexT v1,
                                       StriperHalfEdgeGraph::IndexT v2)
{
    Triangle *triangle = 0;
    
    if ((v0 != v1) && (v0 != v2) && (v2 != v1))
    {
        // create new triangle
        triangle = _trianglePool.createTriangle();
        triangle->init();
        
        // reg edges
        if (!getHalfEdge(v0,v1) && !getHalfEdge(v1,v2) && !getHalfEdge(v2,v0))
        {
            addHalfEdge(triangle->halfEdgeVec[0],v0,v1);
            addHalfEdge(triangle->halfEdgeVec[1],v1,v2);
            addHalfEdge(triangle->halfEdgeVec[2],v2,v0);
            _validTriangleBag.add(*triangle);
            return true;
        }
        else
        {
            triangle->halfEdgeVec[0].setVertex(v0,v1);
            triangle->halfEdgeVec[1].setVertex(v1,v2);
            triangle->halfEdgeVec[2].setVertex(v2,v0);
            triangle->state = INVALID;
            _invalidTriangleBag.add(*triangle);
            return false;
        }
    }
    return false;
}

inline
UInt32 StriperHalfEdgeGraph::triangleCount(void)
{
    return _trianglePool.countElem();
}

inline
UInt32 StriperHalfEdgeGraph::primitiveCount(void)
{
    return UInt32(_stripBag.size() + _fanBag.size() + _triBag.size());
}

OSG_END_NAMESPACE
