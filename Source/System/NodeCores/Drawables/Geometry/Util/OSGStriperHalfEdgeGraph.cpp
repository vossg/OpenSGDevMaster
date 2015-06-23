/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

// System declarations
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <map>

#include "OSGGL.h"

// Application declarations


// Class declarations
#include "OSGStriperHalfEdgeGraph.h"


using namespace std;

OSG_USING_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

// Static Class Varible implementations: 

//----------------------------------------------------------------------
// Method: HalfEdgeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Default Constructor
//----------------------------------------------------------------------
StriperHalfEdgeGraph::StriperHalfEdgeGraph (void)
{
}

//----------------------------------------------------------------------
// Method: HalfEdgeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Copy Constructor
//----------------------------------------------------------------------
StriperHalfEdgeGraph::StriperHalfEdgeGraph(
    const StriperHalfEdgeGraph &OSG_CHECK_ARG(obj))
{
    SWARNING << "Run HalfEdgeGraph copy constructor; not impl.\n" << endl;
}

//----------------------------------------------------------------------
// Method: ~HalfEdgeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
StriperHalfEdgeGraph::~StriperHalfEdgeGraph (void )
{
    clear();
}

//----------------------------------------------------------------------
// Method: ~HalfEdgeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
bool StriperHalfEdgeGraph::Triangle::verify (void)
{
    bool retCode = true;
    Triangle *neighbor[3];

    neighbor[0] = halfEdgeVec[0].twin ? halfEdgeVec[0].twin->triangle : 0;
    neighbor[1] = halfEdgeVec[1].twin ? halfEdgeVec[1].twin->triangle : 0;
    neighbor[2] = halfEdgeVec[2].twin ? halfEdgeVec[2].twin->triangle : 0;

    if ( ( neighbor[0] &&
           ( (neighbor[0] == neighbor[1] ) ||
             (neighbor[0] == neighbor[2] ) 
             ) 
           ) ||
         ( neighbor[1] &&
           ( (neighbor[1] == neighbor[0] ) ||
             (neighbor[1] == neighbor[2] ) ) 
           ) ||
         ( neighbor[2] &&
           ( (neighbor[2] == neighbor[0] ) ||
             (neighbor[2] == neighbor[1] ) ) 
           )
         )
    {
        FINFO(("StriperHalfEdgeGraph::Triangle::verify: Neighbor linked more "
               "than once: %p/%p/%p\n", static_cast<void *>(neighbor[0]),
                                        static_cast<void *>(neighbor[1]),
                                        static_cast<void *>(neighbor[2])));
        retCode = false;
    }

    if((halfEdgeVec[0].vertexStart() == halfEdgeVec[1].vertexStart()) ||
       (halfEdgeVec[0].vertexStart() == halfEdgeVec[2].vertexStart()) ||
       (halfEdgeVec[1].vertexStart() == halfEdgeVec[2].vertexStart()))
    {
        SINFO << "StriperHalfEdgeGraph::Triangle::verify: "
              << "Invalid collapsed Triangle" 
              << endl;
        retCode = false;
    }

    if((halfEdgeVec[0].triangle != this) ||
       (halfEdgeVec[1].triangle != this) ||
       (halfEdgeVec[2].triangle != this))
    {
        SINFO << "StriperHalfEdgeGraph::Triangle::verify: Invalid halfEdge->"
              << "triangle pointer" << endl;
        retCode = false;
    }

    if((halfEdgeVec[0].next != &halfEdgeVec[1]) ||
       (halfEdgeVec[1].next != &halfEdgeVec[2]) ||
       (halfEdgeVec[2].next != &halfEdgeVec[0]))
    {
        SINFO << "StriperHalfEdgeGraph::Triangle::verify: Edge next link error" 
              << endl;
        retCode = false;
    }

    return retCode;
}

//----------------------------------------------------------------------
// Method: reserve
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
void StriperHalfEdgeGraph::reserve(UInt32 vertexNum, UInt32 triangleNum, 
                                   UInt32 reserveEdges )
{
    UInt32 i;

    _trianglePool.setChunkSize(triangleNum);
    _edgeLinkVec.resize(vertexNum); 

    if(reserveEdges > 0)
    {
        for(i = 0; i < vertexNum; ++i)
            _edgeLinkVec[i].reserve(reserveEdges);
    }
}

//----------------------------------------------------------------------
// Method: verify
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
bool StriperHalfEdgeGraph::verify (bool verbose)
{
    bool retCode = true;
    UInt32 i, n;
    Triangle *triangle, *nt0, *nt1, *nt2;
    Int32 triangleState[4];
    Int32 invalidTriangles = 0;
    Int32 halfEdgeCount = 0;
    map< Int32, Int32 > connectionMap;
    map< Int32, Int32 >::iterator connectionI;
    Int32 connectionCount;
    bool validTri = false;

    for(i = 0; i < 4; ++i)
        triangleState[i] = 0;

    for( i = 0, triangle = _validTriangleBag.first; 
         triangle; 
         i++, triangle = triangle->next)
    {
        // Looks strange (GV)
        if((triangle->verify() && (triangle->state >= 0)) || 
           (triangle->state <= 3))
        {
            triangleState[triangle->state]++;
            validTri = true;
        }
        else
        {
            ++invalidTriangles;
            validTri = false;
        }

        if ( verbose ) 
        {
            nt0 = triangle->halfEdgeVec[0].twin ? 
              triangle->halfEdgeVec[0].twin->triangle : 0;
            nt1 = triangle->halfEdgeVec[1].twin ? 
              triangle->halfEdgeVec[1].twin->triangle : 0;
            nt2 = triangle->halfEdgeVec[2].twin ? 
              triangle->halfEdgeVec[2].twin->triangle : 0;
            
            FINFO ( ( "HEG: Triangle %p: %d %d %d, %p %p %p: %s\n",
                      static_cast<void *>(triangle), 
                      triangle->halfEdgeVec[0].vertexStart(),
                      triangle->halfEdgeVec[1].vertexStart(),
                      triangle->halfEdgeVec[2].vertexStart(),
                      static_cast<void *>(nt0),
                      static_cast<void *>(nt1),
                      static_cast<void *>(nt2),
                      (validTri ? "VALID" : "INVALID" ) ) );
        }
    }

    SINFO << "HEG: linked triangle count " << _validTriangleBag.countElem()
          << endl;
    SINFO << "HEG: invalid triangle " << invalidTriangles 
          << endl;
    SINFO << "HEG: nonmanifold split: " << _invalidTriangleBag.countElem() 
          << endl;

    SINFO << "HEG: triangle state: "
          << triangleState[0]
          << "/"
          << triangleState[1]
          << "/"
          << triangleState[2]
          << "/"
          << triangleState[3]
          << endl;
    
    n = UInt32(_edgeLinkVec.size());
    halfEdgeCount = 0;
    for (i = 0; i < n; ++i)
    {
        connectionCount = UInt32(_edgeLinkVec[i].size());

        halfEdgeCount += connectionCount;
        if (connectionMap.find(connectionCount) == connectionMap.end())
            connectionMap[connectionCount] = 1;
        else
            connectionMap[connectionCount]++;

        if (verbose) 
        {
            HalfEdgeLink::iterator lI;
            for ( lI = _edgeLinkVec[i].begin(); 
                  lI != _edgeLinkVec[i].end(); ++lI )
            {  
              FINFO (( "HEG: HalfEdge %p: %d to %d, twin: %p\n",
                       static_cast<void *>(lI->second),
                       lI->second->vertexStart(),
                       lI->second->vertexEnd(),
                       static_cast<void *>(lI->second->twin)));
            }
        }
    }
    for(connectionI = connectionMap.begin();
        connectionI != connectionMap.end(); ++connectionI)
    {
      SINFO << "HEG: Connection: " << connectionI->first << '/' 
            << connectionI->second << ' ' << std::endl;
    }

    SINFO << "HEG: HalfEdgeCount: " << halfEdgeCount << endl;

    return retCode;
}

//----------------------------------------------------------------------
// Method: calcOptPrim
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
UInt32 StriperHalfEdgeGraph::calcOptPrim(UInt32 extIteration,
                                         bool doStrip, bool doFan,
                                         UInt32 minFanTriangles)
{
    Int32 iteration = extIteration;
    bool sample = iteration > 1 ? true : false;
    bool checkRevOrder = sample;
    TriangleList degreeBag[4];
    TriangleList *fList = 0;
    Int32 cost = 0, sampleCost = 0;
    Int32 stripCost = 0, revCost = 0, fanCost = 0, triCost = 0;
    Int32 bestCost = 0, worstCost = 0, lowDegree;
    UInt32 i, n;
    WalkCase walkCase = START;
    Triangle *triangle, *next;
    HalfEdge *twin = 0, *gateEdge = 0, *halfEdge = 0;
    bool doMainLoop = true;
    UInt32 seed = 1, bestSeed = 1;
    Int32 mostDegree = 3;
    UInt32 triangleLeft = _trianglePool.countElem();
    srand(1);

    if(doFan)
    {
        n = UInt32(_edgeLinkVec.size());
        fanCost = 0;

        // find fans 
        for(i = 0; i < n; ++i)
        {
            if((_edgeLinkVec[i].size() >= minFanTriangles) &&
               (gateEdge = _edgeLinkVec[i][0].second) &&
               (gateEdge->triangle->valid()))
            {
                for(halfEdge = gateEdge->next->next->twin;
                    (halfEdge && halfEdge->triangle->valid() &&
                    (halfEdge != gateEdge));
                    halfEdge = halfEdge->next->next->twin)
                    ;
                if(halfEdge == gateEdge)
                {
                    // fan is closed; mark every triangle          
                    triangle = 0;
                    fList = new TriangleList;
                    for(halfEdge = gateEdge;
                        !triangle || (halfEdge != gateEdge);
                        halfEdge = halfEdge->next->next->twin)
                    {
                        triangle = halfEdge->triangle;
                        _validTriangleBag.release(*triangle);
                        triangle->drop();
                        triangle->state = FAN_PART;
                        fList->add(*triangle);
                    }
                    _fanBag.push_back(Primitive(i,fList));
                    fanCost += (UInt32(_edgeLinkVec[i].size()) + 2);
                    triangleLeft -= UInt32(_edgeLinkVec[i].size());
                }
            }
        }
    }

    if(doStrip && iteration)
    {
        // push every triangle into the according degree bag
        degreeBag[mostDegree].paste(_validTriangleBag);
        for(triangle = degreeBag[mostDegree].first; triangle; triangle = next)
        {
            next = triangle->next;
            if(triangle->valid())
            {
                if(triangle->state != mostDegree)
                {
                    degreeBag[mostDegree].release(*triangle);
                    _validTriangleBag.release(*triangle);
                    degreeBag[triangle->state].add( *triangle);
                }
            }
            else
            {
                SWARNING << "INVALID TRIANGLE IN VALID TRIANGLE BAG\n" << endl;
            }
        }

        for(iteration--; iteration >= 0; iteration--)
        {
            seed = iteration ? rand() : bestSeed;
            srand (seed);

            fList = 0;
            cost = 0;
            doMainLoop = true;
            walkCase = START;

            // run the main loop
            while(doMainLoop)
            {
                switch(walkCase)
                {
                    case START:
                        stripCost = 0;
                        triangle = 0;

                        for(lowDegree = 1; lowDegree < 4; ++lowDegree)
                        {
                            if((degreeBag[lowDegree].empty() == false))
                            {
                                if(sample)
                                {
                                    // pick a random triangle
                                    n = degreeBag[lowDegree].countElem() - 1;
                                    i = Int32(float(n)*rand()/float(RAND_MAX));
                                    triangle = degreeBag[lowDegree].first;
                                    while (i--) 
                                        triangle = triangle->next;
                                }
                                else
                                {
                                    // pick the first triangle
                                    triangle = degreeBag[lowDegree].first;
                                }
                                break;
                            }
                        }

                        if(triangle)
                        {
                            // create the new list
                            fList = new TriangleList;

                            // find the best neighbour
                            gateEdge = 0;
                            for (i = 0; i < 3; ++i)
                            {
                                if((twin = triangle->halfEdgeVec[i].twin) && 
                                    (twin->triangle->state > 0))
                                {
                                    if(twin->next->next->twin &&
                                       (twin->next->next->twin->triangle->state > 0))
                                    {
                                        gateEdge = &triangle->halfEdgeVec[i];
                                        break;
                                    }
                                    else
                                    {
                                        if(twin->next->twin &&
                                           (twin->next->twin->triangle->state > 0))
                                        {
                                            gateEdge = &triangle->halfEdgeVec[i];
                                        }
                                        else
                                        {
                                            if((twin->triangle->state > 0))
                                                gateEdge = &triangle->halfEdgeVec[i];
                                        }
                                    }
                                }
                            }

                            // release and store the first triangle
                            dropOutTriangle (*triangle,degreeBag);
                            fList->add(*triangle);
                            stripCost += 3;

                            // set the next step
                            if(gateEdge)
                            {
                                walkCase = LEFT;
                                ++stripCost;
                            }
                            else
                            {
                                walkCase = FINISH;
                            }
                        }
                        else
                        {
                            doMainLoop = false;
                        }
                    break;

                    case LEFT:
                        gateEdge = gateEdge->twin;
                        triangle = gateEdge->triangle;

                        // find the next gate
                        if(triangle->state == DEGREE_0)
                        {
                            gateEdge = 0;
                            walkCase = FINISH;
                        }
                        else
                        {
                            if((twin = gateEdge->next->next->twin) && 
                               (twin->triangle->state > 0))
                            {
                                gateEdge = gateEdge->next->next;
                                ++stripCost;
                                walkCase = RIGHT;
                            }
                            else
                            {
                                gateEdge = gateEdge->next;
                                stripCost += 2;
                                walkCase = LEFT;
                            }
                        }
                        // store the current triangle
                        dropOutTriangle (*triangle,degreeBag);
                        fList->add(*triangle);
                    break;

                    case RIGHT:
                        gateEdge = gateEdge->twin;
                        triangle = gateEdge->triangle;

                        // find the next gate
                        if(triangle->state == DEGREE_0)
                        {
                            gateEdge = 0;
                            walkCase = FINISH;
                        }
                        else
                        {
                            if((twin = gateEdge->next->twin) &&
                               (twin->triangle->state > 0))
                            {
                                gateEdge = gateEdge->next;
                                ++stripCost;
                                walkCase = LEFT;
                            }
                            else
                            {
                                gateEdge = gateEdge->next->next;
                                stripCost += 2;
                                walkCase = RIGHT;
                            }
                        }
                        // store the current triangle
                        dropOutTriangle (*triangle,degreeBag);
                        fList->add(*triangle);
                    break;

                    case FINISH:
                        // try to reverse the strip
                        if(checkRevOrder &&
                           (revCost = calcStripCost(*fList,true)) &&
                           (revCost < stripCost))
                        {
                            _stripBag.push_back(Primitive(1,fList));
                            cost += revCost;
                        }
                        else
                        {
                            _stripBag.push_back(Primitive(0,fList));
                            cost += stripCost;
                        }
                        walkCase = START;
                        fList = 0;
                    break;
                }
            }

            if(sample)
            {
                sampleCost = cost + (degreeBag[0].countElem() * 3) + fanCost;
                if(!bestCost || (sampleCost < bestCost))
                {
                    bestCost = sampleCost;
                    bestSeed = seed;
                }
                if(sampleCost > worstCost)
                    worstCost = sampleCost;

                SINFO << " cost/best/worst: " 
                      << sampleCost << '/' << bestCost << '/' << worstCost
                      << endl;
            }

            if(iteration)
            {
                // reinit the four degree bags
                degreeBag[mostDegree].paste(degreeBag[0]);
                n = UInt32(_stripBag.size());
                for(i = 0; i < n; ++i)
                {
                    degreeBag[mostDegree].paste(*_stripBag[i].second);
                    delete _stripBag[i].second;
                }
                _stripBag.clear();
                for(triangle = degreeBag[mostDegree].first; triangle; 
                    triangle = next)
                {
                    next = triangle->next;
                    triangle->resetDegreeState(STRIP_PART);
                    if (triangle->valid())
                    {
                        if(triangle->state != mostDegree)
                        {
                            degreeBag[mostDegree].release(*triangle);
                            degreeBag[triangle->state].add(*triangle);
                        }
                    }
                    else
                    {
                        SWARNING << "INVALID TRIANGLE IN REINIT\n" << endl;
                        SWARNING << triangle->state << endl;
                    }
                }
            }
        }
    }
    else
    {
        // push every valid triangle in degree 0; we don't strip anything
        degreeBag[0].paste(_validTriangleBag);
    }

    if(sample)
    {
        SWARNING << "range: " 
             << bestCost << '/' << worstCost << ' '
             << float(100 * (worstCost-bestCost))/float(bestCost) << '%'
             << endl;
    }

    // collect isolated triangles  
    degreeBag[0].paste(_invalidTriangleBag);  
    triCost = degreeBag[0].countElem() * 3;
    if(triCost)
    {
        fList = new TriangleList;  
        fList->paste(degreeBag[0]);
        _triBag.push_back(Primitive(0,fList));
    }

    return (cost + fanCost + triCost);
}

//----------------------------------------------------------------------
// Method: calcStripCost
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
Int32 StriperHalfEdgeGraph::calcStripCost(TriangleList &strip, bool rev)
{
    Triangle *triangle = rev ? strip.last : strip.first, *nextTriangle;
    HalfEdge /* *firstEdge, */ *halfEdge, *gate;
    WalkCase walkCase;
    Int32 cost = 0;

    if (triangle)
    {
        cost = 3;
        if ((nextTriangle = rev ? triangle->prev : triangle->next))
        {
            gate = findGateEdge(triangle,nextTriangle);
            //firstEdge = gate->next->next;
            ++cost;
            walkCase = LEFT;
            for(triangle = nextTriangle; 
                (nextTriangle = (rev ? triangle->prev : triangle->next));
                triangle = nextTriangle)
            {
                halfEdge = gate->twin;
                gate = findGateEdge(triangle,nextTriangle); 
                if (walkCase == RIGHT)
                {
                    // RIGHT
                    if(halfEdge->next == gate)
                    {
                        ++cost;
                        walkCase = LEFT;
                    }
                    else
                    {
                        // swap; walkCase stays RIGHT;
                        cost += 2;
                    }
                }
                else
                {
                    // LEFT
                    if(halfEdge->next->next == gate)
                    {
                        ++cost;
                        walkCase = RIGHT;
                    }
                    else
                    {
                        // swap; walkCase stays LEFT;
                        cost += 2;
                    }
                }
            }
        }
    }

    return cost;
}

//----------------------------------------------------------------------
// Method: fillPrimFromStrip
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
Int32 StriperHalfEdgeGraph::fillIndexFromStrip(
    std::vector<StriperHalfEdgeGraph::IndexT> &indexVec,
    TriangleList &strip, bool rev)
{
    Triangle *triangle = rev ? strip.last : strip.first, *nextTriangle;
    HalfEdge *firstEdge, *halfEdge, *gate;
    WalkCase walkCase;
    StriperHalfEdgeGraph::IndexT vertex;
    Int32 cost = 0;

    if (triangle)
    {
        cost = 3;
        indexVec.reserve(32); // find better value
        indexVec.resize(3);
        if((nextTriangle = (rev ? triangle->prev : triangle->next)))
        {
            ++cost;
            gate = findGateEdge(triangle,nextTriangle);
            firstEdge = gate->next->next;
            indexVec.push_back(vertex = gate->twin->next->vertexEnd());

            walkCase = LEFT;
            for(triangle = nextTriangle; 
                (nextTriangle = (rev ? triangle->prev : triangle->next));
                triangle = nextTriangle)
            {
                halfEdge = gate->twin;
                gate = findGateEdge(triangle,nextTriangle); 
                if(walkCase == RIGHT)
                {
                    // RIGHT
                    if(halfEdge->next == gate)
                    {
                        indexVec.push_back(vertex = gate->twin->next->vertexEnd());
                        walkCase = LEFT;
                        ++cost;
                    }
                    else
                    {
                        // swap; walkCase stays RIGHT;
                        indexVec.back() = gate->vertexEnd();
                        indexVec.push_back(gate->vertexStart());              
                        indexVec.push_back(vertex = gate->twin->next->vertexEnd());
                        cost += 2;
                    }
                }
                else
                {
                    // LEFT
                    if (halfEdge->next->next == gate)
                    {
                        indexVec.push_back(vertex = gate->twin->next->vertexEnd());
                        walkCase = RIGHT;
                        ++cost;
                    }
                    else
                    {
                        // swap; walkCase stays LEFT;
                        indexVec.back() = gate->vertexStart();
                        indexVec.push_back(gate->vertexEnd());
                        indexVec.push_back(vertex = gate->twin->next->vertexEnd());
                        cost += 2;
                    }
                }
            }
        }
        else 
        {
            firstEdge = &triangle->halfEdgeVec[0];
        }

        indexVec[0] = vertex = firstEdge->vertexStart();
        indexVec[1] = vertex = firstEdge->next->vertexStart();
        indexVec[2] = vertex = firstEdge->next->next->vertexStart();
    }

    return cost;
}

//----------------------------------------------------------------------
// Method: fillPrimFromFan
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
Int32 StriperHalfEdgeGraph::fillIndexFromFan(
    std::vector<StriperHalfEdgeGraph::IndexT> &indexVec,
    HalfEdge &firstEdge )
{
    Int32 count = 0;
    HalfEdge *halfEdge(&firstEdge);
    HalfEdge *gateEdge = 0;
    
    if(halfEdge)
    {
        count = 3;
        indexVec.resize(2);
        indexVec[0] = halfEdge->vertexStart();
        indexVec[1] = halfEdge->vertexEnd();
        for(gateEdge = halfEdge->next->next->twin;
            gateEdge != halfEdge;
            gateEdge = gateEdge->next->next->twin)
        {
            indexVec.push_back(gateEdge->vertexEnd());
            ++count;
        }
        indexVec.push_back(halfEdge->vertexEnd());
    }
    else
    {
        SWARNING << "Invalid fac in fillIndexFromFan()" << endl;
    }
    return count;
}

//----------------------------------------------------------------------
// Method: calcEdgeLines
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
Int32 StriperHalfEdgeGraph::getPrimitive(
    vector<StriperHalfEdgeGraph::IndexT> &indexVec,
    Int32 type)
{
    UInt32 i = 0, n = 0;
    Triangle *triangle;
    std::vector<Primitive> *bag = 0;
    
    indexVec.clear();
    
    // fan
    if(!bag && (n = UInt32(_fanBag.size())) &&
       ((type == GL_TRIANGLE_FAN) || !type))
    {
        i = n - 1;
        bag = &_fanBag;
        fillIndexFromFan(indexVec, 
                         *_edgeLinkVec[_fanBag[i].first][0].second);
        type = GL_TRIANGLE_FAN;
    }
    
    // strip
    if(!bag && (n = UInt32(_stripBag.size())) &&
       ((type == GL_TRIANGLE_STRIP) || !type))
    {
        i = n - 1;
        bag = &_stripBag;
        fillIndexFromStrip(indexVec, *_stripBag[i].second,
                           _stripBag[i].first ? true : false );
        type = GL_TRIANGLE_STRIP;
    }
    
    // tri
    if(!bag && (n = UInt32(_triBag.size())) &&
       ((type == GL_TRIANGLES) || !type))
    {
        bag = &_triBag;
        if (_triBag[0].second->empty() == false)
        {
            n = _triBag[0].second->countElem() * 3;
            indexVec.resize(n);
            i = 0;
            for(triangle = _triBag[0].second->first; triangle; 
                triangle = triangle->next )
            {
                indexVec[i++] = triangle->halfEdgeVec[0].vertexStart();
                indexVec[i++] = triangle->halfEdgeVec[1].vertexStart();
                indexVec[i++] = triangle->halfEdgeVec[2].vertexStart();
            }
        }
        type = GL_TRIANGLES;
        i = 0;
    }
    
    if(bag)
    {
        _invalidTriangleBag.paste(*((*bag)[i].second));
        delete (*bag)[i].second;
        if (i)
            bag->resize(i);
        else
            bag->clear();
    }
    else
    {
        type = 0;
    }
    return type;
}

//----------------------------------------------------------------------
// Method: calcEdgeLines
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
Int32 StriperHalfEdgeGraph::calcEgdeLines(
    vector<StriperHalfEdgeGraph::IndexT> & indexVec,
    bool codeBorder )
{
    UInt32 i, nN, j, nE, halfEdgeCount = 0;
    StriperHalfEdgeGraph::IndexT startVertexIndex, endVertexIndex;
    HalfEdge *halfEdge;
    bool isBorder;

    indexVec.clear();
    nN = UInt32(_edgeLinkVec.size());
    for (i = 0; i < nN; ++i)
    {
        nE = UInt32(_edgeLinkVec[i].size());
        for ( j = 0; j < nE; ++j)
        {
            halfEdge = _edgeLinkVec[i][j].second;
            startVertexIndex = halfEdge->vertexStart();
            endVertexIndex = halfEdge->vertexEnd();

            if ((isBorder = (halfEdge->twin == 0)) || (startVertexIndex <
                endVertexIndex))
            {
                indexVec.push_back(startVertexIndex);
                indexVec.push_back(endVertexIndex);
                if(codeBorder)
                    indexVec.push_back(isBorder ? 0 : 1);
                ++halfEdgeCount;
            }
        }
    }
    return halfEdgeCount;
}

//----------------------------------------------------------------------
// Method: 
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
void StriperHalfEdgeGraph::clear(void)
{
    UInt32 i,n;
    
    _edgeLinkVec.clear();
    _trianglePool.clear();
    
    n = UInt32(_stripBag.size());
    for(i = 0; i < n; ++i)
        delete _stripBag[i].second;
    _stripBag.clear();
    
    n = UInt32(_fanBag.size());
    for(i = 0; i < n; ++i)
        delete _fanBag[i].second;
    _fanBag.clear();
    
    n = UInt32(_triBag.size());
    for(i = 0; i < n; ++i)
        delete _triBag[i].second;
    _triBag.clear();
}

#endif  // remove from all but dev docs
