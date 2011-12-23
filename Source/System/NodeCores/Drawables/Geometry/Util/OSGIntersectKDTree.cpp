/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGIntersectKDTree.h"

#include "OSGFastTriangleIterator.h"

OSG_BEGIN_NAMESPACE

namespace
{
    const Real32 travCost   =  1.f;
    const Real32 isectCost  = 10.f;
    const Real32 emptyBonus =  0.5f;

    // =======================================================================

    // BBox - axis aligned bounding box (simpler, slightly smaller than BoxVolume)
    //        if constructed from three points (a triangle) it never has
    //        zero extend in x,y, or z (see below).

    struct BBox
    {
        explicit BBox(void                              );
        explicit BBox(const Pnt3f &min, const Pnt3f &max);
        explicit BBox(const Pnt3f &p0,
                      const Pnt3f &p1,
                      const Pnt3f &p2                   );

        void   extendBy(const Pnt3f &p);
        void   extendBy(const BBox  &b);

        Real32 surface (void          ) const;

        Pnt3f _min;
        Pnt3f _max;
    };

    /* explicit */ inline
    BBox::BBox(void)
        : _min(TypeTraits<Real32>::getMax(),
               TypeTraits<Real32>::getMax(),
               TypeTraits<Real32>::getMax() ),
          _max(TypeTraits<Real32>::getMin(),
               TypeTraits<Real32>::getMin(),
               TypeTraits<Real32>::getMin() )
    {
    }

    /* explicit */ inline
    BBox::BBox(const Pnt3f &min, const Pnt3f &max)
        : _min(min),
          _max(max)
    {
    }

    /* explicit */ inline
    BBox::BBox(const Pnt3f &p0,
               const Pnt3f &p1,
               const Pnt3f &p2 )
        : _min(p0),
          _max(p0)
    {
        for(UInt32 i = 0; i < 3; ++i)
        {
            if(p1[i] < _min[i])
                _min[i] = p1[i];
            if(p1[i] > _max[i])
                _max[i] = p1[i];

            if(p2[i] < _min[i])
                _min[i] = p2[i];
            if(p2[i] > _max[i])
                _max[i] = p2[i];
        }

        // We can not allow a bbox of zero extend in any dimension:
        // When selecting the split position we sort end before start
        // edges. If a BBox has zero extend in the split dimension
        // the triangle is not included in any of the two child nodes.
        // Sorting start before end edges could avoid that, but is results
        // in triangles being unnecessarily contained in both children.
        for(UInt32 i = 0; i < 3; ++i)
        {
            Real32 eps = TypeTraits<Real32>::getDefaultEps();

            while(_max[i] - _min[i] <= TypeTraits<Real32>::getDefaultEps())
            {
                _min[i] = _min[i] - eps;
                _max[i] = _max[i] + eps;

                eps *= 2.f;
            }
        }
    }

    inline void
    BBox::extendBy(const Pnt3f &p)
    {
        for(UInt32 i = 0; i < 3; ++i)
        {
            if(p[i] < _min[i])
                _min[i] = p[i];

            if(p[i] > _max[i])
                _max[i] = p[i];
        }
    }

    inline void
    BBox::extendBy(const BBox &b)
    {
        for(UInt32 i = 0; i < 3; ++i)
        {
            if(b._min[i] < _min[i])
                _min[i] = b._min[i];

            if(b._max[i] > _max[i])
                _max[i] = b._max[i];
        }
    }

    inline Real32
    BBox::surface(void) const
    {
        Vec3f diag = _max - _min;

        return 2.f * (diag[0] * diag[1] +
                      diag[0] * diag[2] +
                      diag[1] * diag[2]  );
    }

    typedef std::vector<BBox> BBoxStore;

    // =======================================================================
    
    // TravItem - used during KDTree traversal to keep track of nodes that
    //            still need to be visited.

    struct TravItem
    {
        const IntersectKDTreeNode *_node;
        Real32                     _minT;
        Real32                     _maxT;
    };

    // =======================================================================

    struct BoundEdge
    {
        enum TypeE
        {
            EdgeStart = 1,
            EdgeEnd   = 0
        };

        BoundEdge(void                                 );
        BoundEdge(Real32 pos, UInt32 triIdx, TypeE type);

        Real32 _pos;
        UInt32 _triIdx;
        TypeE  _type;
    };

    inline
    BoundEdge::BoundEdge(void)
        : _pos   (),
          _triIdx(),
          _type  (EdgeStart)
    {
    }

    inline
    BoundEdge::BoundEdge(Real32 pos, UInt32 triIdx, TypeE type)
        : _pos   (pos),
          _triIdx(triIdx),
          _type  (type)
    {
    }

    inline bool
    operator<(const BoundEdge &lhs, const BoundEdge &rhs)
    {
        bool result;

        if(lhs._pos == rhs._pos)
        {
            result = (lhs._type < rhs._type);
        }
        else
        {
            result = (lhs._pos < rhs._pos);
        }

        return result;
    }

    // =======================================================================

    // BuildState - keeps a bunch of "global" variables for buildTree() and
    //              avoids passing them as individual arguments.

    struct BuildState
    {
        UInt32                 _maxDepth;
        UInt32                 _maxTri;
        BBoxStore              _triBounds;

        std::vector<BoundEdge> _edges[3];
        std::vector<UInt32   > _trisBelow;
        std::vector<UInt32   > _trisAbove;

        MFIntersectKDTreeNode *_mfNodes;
        MFUInt32              *_mfTriIndices;
    };

    // =======================================================================

    // recursively constructs a KDTree

    void
    buildTree(BuildState &state,    const BBox   &bounds,
              UInt32      triCount,       UInt32 *triIdx,
              UInt32     *trisBelow,      UInt32 *trisAbove,
              UInt32      depth,          UInt32  badRefines)
    {
        UInt32 currNode = state._mfNodes->size32();

        state._mfNodes->push_back(IntersectKDTreeNode());

        // create leaf if only few triangles are left or
        // maxDepth is reached
        if(triCount <= state._maxTri ||
           depth    == 0               )
        {
            (*state._mfNodes)[currNode].setLeaf(triCount, state._mfTriIndices->size32());

            for(UInt32 i = 0; i < triCount; ++i)
                state._mfTriIndices->push_back(triIdx[i]);

            return;
        }

        // Choose split axis position for interior node
        Int32  bestAxis   = -1;
        Int32  bestOffset = -1;
        Real32 bestCost   = TypeTraits<Real32>::getMax();
        Real32 oldCost    = isectCost * triCount;
        Real32 totalSA    = bounds.surface();
        Real32 invTotalSA = 1.f / totalSA;
        Vec3f  d          = bounds._max - bounds._min;

        UInt32 retries    = 0;
        UInt32 axis       = d.maxDim();

        while(true)
        {
            // init edges and sort
            for(UInt32 i = 0; i < triCount; ++i)
            {
                UInt32      ti   = triIdx[i];
                const BBox &bbox = state._triBounds[ti];
              
                state._edges[axis][2*i    ] = BoundEdge(bbox._min[axis], ti, BoundEdge::EdgeStart);
                state._edges[axis][2*i + 1] = BoundEdge(bbox._max[axis], ti, BoundEdge::EdgeEnd  );
            }

            std::sort(state._edges[axis].begin(),
                      state._edges[axis].begin() + 2 * triCount);

            // find best split position along axis
            UInt32 belowCount = 0;
            UInt32 aboveCount = triCount;

            for(UInt32 i = 0; i < 2 * triCount; ++i)
            {
                if(state._edges[axis][i]._type == BoundEdge::EdgeEnd)
                    --aboveCount;

                Real32 edgeT = state._edges[axis][i]._pos;

                if(edgeT > bounds._min[axis] &&
                   edgeT < bounds._max[axis]   )
                {
                    // compute cost for splitting here
                    UInt32 otherAxis0 = (axis + 1) % 3;
                    UInt32 otherAxis1 = (axis + 2) % 3;

                    Real32 belowSA = 2.f * (d[otherAxis0] * d[otherAxis1] +
                                            (edgeT - bounds._min[axis]) *
                                            (d[otherAxis0] + d[otherAxis1]));
                    Real32 aboveSA = 2.f * (d[otherAxis0] * d[otherAxis1] +
                                            (bounds._max[axis] - edgeT) *
                                            (d[otherAxis0] + d[otherAxis1]));

                    Real32 belowP  = belowSA * invTotalSA;
                    Real32 aboveP  = aboveSA * invTotalSA;
                    Real32 eb      = (belowCount == 0 || aboveCount == 0) ? emptyBonus : 0.f;
                    Real32 cost    =
                        travCost + isectCost * (1.f - eb) * (belowP * belowCount +
                                                             aboveP * aboveCount  );

                    if(cost < bestCost)
                    {
                        bestCost   = cost;
                        bestAxis   = axis;
                        bestOffset = i;
                    }
                }

                if(state._edges[axis][i]._type == BoundEdge::EdgeStart)
                    ++belowCount;
            }

            OSG_ASSERT(belowCount == triCount && aboveCount == 0);

            // retry on pathological cases
            if(bestAxis == -1 && retries < 2)
            {
                ++retries;
                axis = (axis+1) % 3;
                continue;
            }

            // split does not improve cost - accept and hope child nodes
            // can do better
            if(bestCost > oldCost)
                ++badRefines;

            // accept bad split and create leaf for small number of triangles or
            // if splitting does not improve cost
            if((bestCost > 4.f * oldCost && triCount < 16) ||
               bestAxis   == -1 ||
               badRefines >=  3   )
            {
                (*state._mfNodes)[currNode].setLeaf(triCount, state._mfTriIndices->size32());

                for(UInt32 i = 0; i < triCount; ++i)
                    state._mfTriIndices->push_back(triIdx[i]);

                return;
            }

            break;
        }

        // classify triangles with respect to split
        UInt32 belowCount = 0;
        UInt32 aboveCount = 0;

        for(Int32 i = 0; i < bestOffset; ++i)
        {
            if(state._edges[bestAxis][i]._type == BoundEdge::EdgeStart)
                trisBelow[belowCount++] = state._edges[bestAxis][i]._triIdx;
        }

        for(UInt32 i = bestOffset+1; i < 2 * triCount; ++i)
        {
            if(state._edges[bestAxis][i]._type == BoundEdge::EdgeEnd)
                trisAbove[aboveCount++] = state._edges[bestAxis][i]._triIdx;
        }

        // recurse to child nodes
        Real32 splitPos    = state._edges[bestAxis][bestOffset]._pos;
        BBox   belowBounds = bounds;
        BBox   aboveBounds = bounds;
        belowBounds._max[bestAxis] = splitPos;
        aboveBounds._min[bestAxis] = splitPos;

        // build tree for triangles below split plane
        buildTree(state, belowBounds, belowCount,
                  trisBelow, trisBelow, trisAbove + triCount,
                  depth - 1, badRefines);

        // initialize interior node
        (*state._mfNodes)[currNode].setInterior(static_cast<IntersectKDTreeNode::FlagsE>(bestAxis),
                                                state._mfNodes->size32(), splitPos);

        // build tree for triangles above split plane
        buildTree(state, aboveBounds, aboveCount,
                  trisAbove, trisBelow, trisAbove + triCount,
                  depth - 1, badRefines);
    }

    // Fills pnts with positions of split planes (to be rendered as GL_QUADS)
    void
    doBuildSplitPlanePositions(const BBox                              &bounds,
                               const MFIntersectKDTreeNode             *mfNodes,
                                     UInt32                             currNode,
                                     UInt32                             depth,
                                     GeoPnt3fProperty::StoredFieldType *pnts)
    {
        typedef IntersectKDTreeNode KDNode;

        const KDNode *node = &(*mfNodes)[currNode];

        if(node->isLeaf() || depth == 0)
            return;

        Real32 split = node->getSplit    ();
        UInt32 axisS = node->getSplitAxis();
        UInt32 axis0 = (axisS + 1) % 3;
        UInt32 axis1 = (axisS + 2) % 3;

        BBox belowBounds = bounds;
        BBox aboveBounds = bounds;

        belowBounds._max[axisS] = split;
        aboveBounds._min[axisS] = split;

        Pnt3f p;
        p[axisS] = split;
        p[axis0] = bounds._min[axis0];
        p[axis1] = bounds._min[axis1];
        pnts->push_back(p);

        p[axis0] = bounds._min[axis0];
        p[axis1] = bounds._max[axis1];
        pnts->push_back(p);

        p[axis0] = bounds._max[axis0];
        p[axis1] = bounds._max[axis1];
        pnts->push_back(p);

        p[axis0] = bounds._max[axis0];
        p[axis1] = bounds._min[axis1];
        pnts->push_back(p);

        doBuildSplitPlanePositions(belowBounds, mfNodes,
                                   currNode+1, depth-1, pnts            );
        doBuildSplitPlanePositions(aboveBounds, mfNodes,
                                   node->getChildOffset(), depth-1, pnts);
    }

} // namespace

/*! Builds a KDTree from geo by filling mfNodes and mfTriIndices.
  If maxDepth is negative a suitable maximum depth is automatically
  determined.
 */

void
buildIntersectKDTree(Geometry              *geo,
                     Int32                  maxDepth,
                     MFIntersectKDTreeNode *mfNodes,
                     MFUInt32              *mfTriIndices)
{
    BuildState           state;
    FastTriangleIterator triIt(geo);

    UInt32              triCount = 0;
    std::vector<UInt32> tris;
    BBox                bounds;

    mfNodes     ->clear();
    mfTriIndices->clear();

    // record BBox for every triangle and overall volume
    for(; !triIt.isAtEnd(); ++triIt)
    {
        ++triCount;
        tris            .push_back(triIt.getIndex());
        state._triBounds.push_back(
            BBox(triIt.getPropertyValue<Pnt3f>(Geometry::PositionsIndex, 0),
                 triIt.getPropertyValue<Pnt3f>(Geometry::PositionsIndex, 1),
                 triIt.getPropertyValue<Pnt3f>(Geometry::PositionsIndex, 2) ));
        bounds.extendBy(state._triBounds.back());
    }

    if(triCount == 0)
    {
        SWARNING << "buildIntersectKDTree: geometry does not contain any "
                 << "triangles, ignored."
                 << std::endl;
        return;
    }

    if(maxDepth < 0)
    {
        state._maxDepth = osgRound2Int(8 + 1.3f * osgLog2Int(triCount));
    }
    else
    {
        state._maxDepth = maxDepth;
    }

    for(UInt32 i = 0; i < 3; ++i)
        state._edges[i].resize(2 * triCount);

    state._maxTri       = 5;
    state._trisBelow.resize(                      triCount);
    state._trisAbove.resize((state._maxDepth+1) * triCount);
    state._mfNodes      = mfNodes;
    state._mfTriIndices = mfTriIndices;

    // call recursive build function
    buildTree(state, bounds, triCount,
              &tris.front(), &state._trisBelow.front(), &state._trisAbove.front(),
              state._maxDepth, 0);
}

/*! Fills pnts with corners points of the split planes of the
    KDTree with nodes mfNodes.
 */
void
buildSplitPlanePositions(const BoxVolume             &bounds,
                         const MFIntersectKDTreeNode *mfNodes,
                               UInt32                 maxDepth,
                               GeoPnt3fProperty      *pnts     )
{
    GeoPnt3fProperty::StoredFieldType *p = pnts->editFieldPtr();

    BBox bbox(bounds.getMin(), bounds.getMax());

    Vec3f diag = bbox._max - bbox._min;
    diag[0] = osgMax(diag[0], 0.5f);
    diag[1] = osgMax(diag[1], 0.5f);
    diag[2] = osgMax(diag[2], 0.5f);

    bbox._min -= 0.1f * diag;
    bbox._max += 0.1f * diag;

    doBuildSplitPlanePositions(bbox, mfNodes, 0, maxDepth, p);
}

/*! Returns if ray intersects geo using the KDTree described by
    mfNodes and mfTriIndices to accelerate the test.
    If there is an intersection closestHitT contains the distance
    along the ray of the closest hit, hitNormal the normal
    at the intersection point and hitTriangle the index of the
    intersected triangle.
 */
bool
intersectIntersectKDTree(const Line                  &ray,
                         const BoxVolume             &bounds,
                               Geometry              *geo,
                         const MFIntersectKDTreeNode *mfNodes,
                         const MFUInt32              *mfTriIndices,
                               Real32                &closestHitT,
                               Vec3f                 &hitNormal,
                               UInt32                &hitTriangle,
                               UInt32                *numTris     )
{
    typedef IntersectKDTreeNode KDNode;

    const Pnt3f &rayP = ray.getPosition ();
    const Vec3f &rayD = ray.getDirection();

    // determine where ray enters/leaves bounding volume
    Real32 boundMinT;
    Real32 boundMaxT;

    if(bounds.intersect(ray, boundMinT, boundMaxT) == false)
        return false;

    boundMaxT = osgMin(boundMaxT, closestHitT);

    // keep track of relevant part of the ray that can intersect
    // with the KDTree
    // Real32 rayMinT = boundMinT - 10.f * Eps;
    Real32 rayMaxT = boundMaxT + 10.f * Eps;
    Vec3f  invDir(1.f / rayD[0],
                  1.f / rayD[1],
                  1.f / rayD[2] );

    const UInt32         maxItems = 64;
    UInt32               currItem =  0;
    TravItem             items[maxItems];
    FastTriangleIterator triIt(geo);

    UInt32        triTests = 0;
    bool          hit  = false;
    const KDNode *node = &(*mfNodes)[0];

    while(node != NULL)
    {
        // stop if ray ends before current node bounds
        if(rayMaxT < boundMinT)
            break;

        if(!node->isLeaf())
        {
            // interior node
            UInt32 axis   = node->getSplitAxis();
            Real32 splitT = (node->getSplit() - rayP[axis]) * invDir[axis];

            const KDNode *child0;
            const KDNode *child1;

            bool belowFirst = (rayP[axis] <  node->getSplit()                     ) ||
                              (rayP[axis] == node->getSplit() && rayD[axis] <= 0.f);

            if(belowFirst)
            {
                child0 = node + 1;
                child1 = &(*mfNodes)[node->getChildOffset()];
            }
            else
            {
                child0 = &(*mfNodes)[node->getChildOffset()];
                child1 = node + 1;
            }

            if(splitT > boundMaxT || splitT <= 0.f)
            {
                node = child0;
            }
            else if(splitT < boundMinT)
            {
                node = child1;
            }
            else
            {
                items[currItem]._node = child1;
                items[currItem]._minT = splitT;
                items[currItem]._maxT = boundMaxT;
                ++currItem;

                node       = child0;
                boundMaxT  = splitT;
            }
        }
        else
        {
            // leaf node
            UInt32 triCount  = node->getTriCount ();
            UInt32 triOffset = node->getTriOffset();

            for(UInt32 i = 0; i < triCount; ++i)
            {
                UInt32 triIdx = (*mfTriIndices)[triOffset + i];
                Real32 triT;

                triIt.seek(triIdx);

                ++triTests;

                if(ray.intersect(triIt.getPropertyValue<Pnt3f>(Geometry::PositionsIndex, 0),
                                 triIt.getPropertyValue<Pnt3f>(Geometry::PositionsIndex, 1),
                                 triIt.getPropertyValue<Pnt3f>(Geometry::PositionsIndex, 2),
                                 triT, &hitNormal     ))
                {
                    if(triT >= 0.f && triT < closestHitT)
                    {
                        hit         = true;
                        hitTriangle = triIdx;
                        rayMaxT     = triT;
                        closestHitT = triT;
                    }
                }
            }

            // process todo items
            if(currItem > 0)
            {
                --currItem;

                node      = items[currItem]._node;
                boundMinT = items[currItem]._minT;
                boundMaxT = items[currItem]._maxT;
            }
            else
            {
                break;
            }
        }
    }

    if(numTris != NULL)
        *numTris = triTests;

    return hit;
}

OSG_END_NAMESPACE
