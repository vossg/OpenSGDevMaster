/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#include "OSGConfig.h"
#include "OSGGeoOptimization.h"
#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#include <set>

// #include <boost/functional/hash/hash.hpp>
// #include <tr1/unordered_set>

#define OSG_GEOOPT_VERBOSE 1
#undef  OSG_GEOOPT_VERBOSE

#define OSG_GEOOPT_STATISTICS 1
#undef  OSG_GEOOPT_STATISTICS

OSG_BEGIN_NAMESPACE

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

namespace
{
    // Index Tuple (IT) comparison function objects.
    // There are ITLess, ITHash, ITEqual to allow using
    // std::set<> or std::tr1::unordered_set<>

    struct ITLess
    {
        typedef std::vector<GeoIntegralProperty *> IndexStore;

        explicit ITLess(Geometry *geo);
        ITLess(const ITLess &other);

        bool operator()(UInt32 lhs, UInt32 rhs) const;

        std::ostream &print(std::ostream &os, UInt32 idx);

        Geometry   *_geo;
        IndexStore  _istore;

      private:
        
        void operator =(const ITLess &rhs);
    };

    /* explicit */
    ITLess::ITLess(Geometry *geo)
        : _geo   (geo),
          _istore()
    {
        for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
        {
            GeoIntegralProperty *idx = _geo->getIndex(i);
            bool                 add = true;

            if(idx != NULL)
            {
                for(UInt32 j = 0; add == true && j < _istore.size(); ++j)
                {
                    if(idx == _istore[j])
                        add = false;
                }

                if(add == true)
                    _istore.push_back(idx);
            }
        }
    }

    ITLess::ITLess(const ITLess &other)
        : _geo   (other._geo),
          _istore(other._istore)
    {
        
    }

    bool
    ITLess::operator()(UInt32 lhs, UInt32 rhs) const
    {
        bool retVal = false;

        IndexStore::const_iterator isIt  = _istore.begin();
        IndexStore::const_iterator isEnd = _istore.end  ();

        for(; isIt != isEnd; ++isIt)
        {
            UInt32 valL;
            UInt32 valR;
            (*isIt)->getValue(valL, lhs);
            (*isIt)->getValue(valR, rhs);

            if(valL == valR)
                continue;

            retVal = valL < valR;
            break;
        }

        return retVal;
    }

    std::ostream&
    ITLess::print(std::ostream &os, UInt32 idx)
    {
        IndexStore::const_iterator isIt  = _istore.begin();
        IndexStore::const_iterator isEnd = _istore.end  ();

        os << "(";
        for(; isIt != isEnd; ++isIt)
        {
            UInt32 val;
            (*isIt)->getValue(val, idx);
            os << val << ", ";
        }
        os << ")";

        return os;
    }

    /* ==================================================================== */

#if 0 // disabled for now
    struct ITHash
    {
        typedef std::vector<GeoIntegralProperty *> IndexStore;

        explicit ITHash(Geometry *geo);

        std::size_t operator()(UInt32 idx) const;

        Geometry   *_geo;
        IndexStore  _istore;
    };

    /* explicit */
    ITHash::ITHash(Geometry *geo)
        : _geo   (geo),
          _istore()
    {
        for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
        {
            GeoIntegralProperty *idx = _geo->getIndex(i);
            bool                 add = true;

            if(idx != NULL)
            {
                for(UInt32 j = 0; add == true && j < _istore.size(); ++j)
                {
                    if(idx == _istore[j])
                        add = false;
                }

                if(add == true)
                    _istore.push_back(idx);
            }
        }
    }

    std::size_t
    ITHash::operator()(UInt32 idx) const
    {
        std::size_t retVal = 0;

        IndexStore::const_iterator isIt  = _istore.begin();
        IndexStore::const_iterator isEnd = _istore.end  ();

        for(; isIt != isEnd; ++isIt)
        {
            UInt32 val;
            (*isIt)->getValue(val, idx);

            boost::hash_combine(retVal, val);
        }

        return retVal;
    }

    /* ==================================================================== */

    struct ITEqual
    {
        typedef std::vector<GeoIntegralProperty *> IndexStore;

        explicit ITEqual(Geometry *geo);

        bool operator()(UInt32 lhs, UInt32 rhs) const;

        Geometry   *_geo;
        IndexStore  _istore;
    };

    /* explicit */
    ITEqual::ITEqual(Geometry *geo)
        : _geo   (geo),
          _istore()
    {
        for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
        {
            GeoIntegralProperty *idx = _geo->getIndex(i);
            bool                 add = true;

            if(idx != NULL)
            {
                for(UInt32 j = 0; add == true && j < _istore.size(); ++j)
                {
                    if(idx == _istore[j])
                        add = false;
                }

                if(add == true)
                    _istore.push_back(idx);
            }
        }
    }

    bool
    ITEqual::operator()(UInt32 lhs, UInt32 rhs) const
    {
        bool retVal = true;

        IndexStore::const_iterator isIt  = _istore.begin();
        IndexStore::const_iterator isEnd = _istore.end  ();

        for(; isIt != isEnd; ++isIt)
        {
            UInt32 valL;
            UInt32 valR;
            (*isIt)->getValue(valL, lhs);
            (*isIt)->getValue(valR, rhs);

            if(valL != valR)
            {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
#endif // disabled for now

    typedef std::set<UInt32, ITLess>                         ITSet;
    //typedef std::tr1::unordered_set<UInt32, ITHash, ITEqual> ITSet;

    /* ==================================================================== */

    typedef std::vector<OSG::GeoVectorPropertyUnrecPtr  > PropertyStore;
    typedef std::vector<OSG::GeoIntegralPropertyUnrecPtr> PropIndexStore;
    typedef std::vector<std::pair<UInt32, UInt32>       > IndexVec;

    void copyIndices(const PropIndexStore &srcIdx,
                           UInt32          srcOffset,
                     const PropIndexStore &dstIdx,
                           UInt32          dstOffset,
                           UInt32          count = 1 )
    {
        OSG_ASSERT(srcIdx.size() == dstIdx.size());

        for(UInt32 i = 0; i < srcIdx.size(); ++i)
        {
            if(dstIdx[i]->size() < (dstOffset + count))
                dstIdx[i]->resize(dstOffset + count);

            for(UInt32 j = 0; j < count; ++j)
            {
                GeoIntegralProperty::MaxTypeT val;
                srcIdx[i]->getValue(val, srcOffset + j);
                dstIdx[i]->setValue(val, dstOffset + j);
            }
        }
    }

    void copyIndexSet(const PropIndexStore      &srcIdx,
                      const std::vector<UInt32> &srcIndices,
                      const PropIndexStore      &dstIdx,
                           UInt32                dstOffset)
    {
        OSG_ASSERT(srcIdx.size() == dstIdx.size());

        UInt32 count = srcIndices.size();

        for(UInt32 i = 0; i < srcIdx.size(); ++i)
        {
            if(dstIdx[i]->size() < (dstOffset + count))
                dstIdx[i]->resize(dstOffset + count);

            for(UInt32 j = 0; j < count; ++j)
            {
                GeoIntegralProperty::MaxTypeT val;

                srcIdx[i]->getValue(val, srcIndices[j]);
                dstIdx[i]->setValue(val, dstOffset + j);
            }
        }
    }

    Real32 polyArea(GeoVectorProperty   *pPos,
                    IndexVec            &vPolyIndex,
                    Int32                len,
                    UInt32               uiXIdx,
                    UInt32               uiYIdx   )
    {
        float A = 0.0f;

        Pnt3f oPntP;
        Pnt3f oPntQ;

        for(Int32 p = len - 1, q = 0; q < len; p = q++)
        {
            pPos->getValue(oPntP, vPolyIndex[p].first);
            pPos->getValue(oPntQ, vPolyIndex[q].first);

            A += oPntP[uiXIdx] * oPntQ[uiYIdx] - oPntQ[uiXIdx] * oPntP[uiYIdx];
        }

        return A*0.5f;
    }

    /* InsideTriangle decides if a point P is Inside of the triangle
       defined by A, B, C.
     */

    bool InsideTriangle(Real32 Ax, Real32 Ay,
                        Real32 Bx, Real32 By,
                        Real32 Cx, Real32 Cy,
                        Real32 Px, Real32 Py)

    {
        Real32 ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
        Real32 cCROSSap, bCROSScp, aCROSSbp;

        ax = Cx - Bx;  ay = Cy - By;
        bx = Ax - Cx;  by = Ay - Cy;
        cx = Bx - Ax;  cy = By - Ay;
        apx= Px - Ax;  apy= Py - Ay;
        bpx= Px - Bx;  bpy= Py - By;
        cpx= Px - Cx;  cpy= Py - Cy;
        
        aCROSSbp = ax * bpy - ay * bpx;
        cCROSSap = cx * apy - cy * apx;
        bCROSScp = bx * cpy - by * cpx;

        return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
    }

    static const float EPSILON = 0.0000000001f;

    bool Snip(GeoVectorProperty *pPos,
              IndexVec          &vPolyIndex,
              Int32              u,
              Int32              v,
              Int32              w,
              Int32              n,
              UInt32             uiXIdx,
              UInt32             uiYIdx    )
    {
        Int32 p;
        Real32 Ax, Ay, Bx, By, Cx, Cy, Px, Py;

        Pnt3f oPnt;

        pPos->getValue(oPnt, vPolyIndex[u].first);

        Ax = oPnt[uiXIdx]; 
        Ay = oPnt[uiYIdx]; 

        pPos->getValue(oPnt, vPolyIndex[v].first);
  
        Bx = oPnt[uiXIdx]; 
        By = oPnt[uiYIdx];

        pPos->getValue(oPnt, vPolyIndex[w].first);
        
        Cx = oPnt[uiXIdx]; 
        Cy = oPnt[uiYIdx];

        if(EPSILON > (((Bx - Ax) * (Cy - Ay)) - ((By - Ay) * (Cx - Ax)))) 
            return false;
    
        for(p = 0; p < n; ++p)
        {
            if((p == u) || (p == v) || (p == w)) 
                continue;

            pPos->getValue(oPnt, vPolyIndex[p].first);

            Px = oPnt[uiXIdx]; 
            Py = oPnt[uiYIdx];

            if(InsideTriangle(Ax, Ay, Bx, By, Cx, Cy, Px, Py)) 
                return false;
        }
        
        return true;
    }

    // Simple polygon triangulation, base on 
    // http://www.flipcode.com/archives/Efficient_Polygon_Triangulation.shtml
    // from John W. Ratcliff 
    
    UInt32 triangulatePoly(      IndexVec       &vPolyIndex,
                           const PropIndexStore &srcIdx,
                           const PropIndexStore &dstIdx,
                                 UInt32         &dstOffset,
                                 UInt32          len,
                                 Geometry       *pGeo     )
    {
        OSG_ASSERT(len >= 3 && pGeo != NULL);

        GeoVectorProperty *pPos = pGeo->getProperty(Geometry::PositionsIndex);

        // figure out the coordinate plane to use:

        Pnt3f oP0;
        Pnt3f oP1;
        Pnt3f oP2;

        pPos->getValue(oP0, vPolyIndex[0].first);
        pPos->getValue(oP1, vPolyIndex[1].first);
        pPos->getValue(oP2, vPolyIndex[2].first);
        
        Vec3f oE0 = oP1 - oP0;
        Vec3f oE1 = oP2 - oP0;

        Vec3f  oN       = oE0.cross(oE1);
        UInt32 uiMaxIdx = oN.maxDimAbs();

        UInt32 uiXIdx = 0;
        UInt32 uiYIdx = 1;

        if(uiMaxIdx == 0)
        {
            uiXIdx = 1;
            uiYIdx = 2;
        }
        else if(uiMaxIdx == 1)
        {
            uiYIdx = 2;
        }

        Real32 fArea = polyArea(pPos,
                                vPolyIndex,
                                len,
                                uiXIdx,
                                uiYIdx);

        bool bReversed = false;

        if(fArea < 0.f)
        {
            std::reverse(vPolyIndex.begin(), vPolyIndex.end());

            bReversed = true;
        }

        Int32 nv = len;

        /*  remove nv-2 Vertices, creating 1 triangle every time */
        Int32 count = 2 * nv;   /* error detection */

        std::vector<UInt32> vTriIndices;

        vTriIndices.resize(3);

        UInt32 returnValue = 0;

        for(Int32 m = 0, v = nv - 1; nv > 2;)
        {

            /* if we loop, it is probably a non-simple polygon */
            if(0 >= (count--))
            {
                //** Triangulate: ERROR - probable bad polygon!
                return 0;
            }

            /* three consecutive vertices in current polygon, <u,v,w> */
            Int32 u = v; 

            if (nv <= u) 
                u = 0;     /* previous */

            v = u + 1; 

            if (nv <= v) 
                v = 0;     /* new v    */

            Int32 w = v + 1; 
            
            if(nv <= w) 
                w = 0;     /* next     */

            if(Snip(pPos,
                    vPolyIndex,
                    u, v, w, 
                    nv, 
                    uiXIdx,
                    uiYIdx)   )
            {
                vTriIndices[0] = vPolyIndex[u].second;
                
                if(bReversed == false)
                {
                    vTriIndices[1] = vPolyIndex[v].second;
                    vTriIndices[2] = vPolyIndex[w].second;
                }
                else
                {
                    vTriIndices[1] = vPolyIndex[w].second;
                    vTriIndices[2] = vPolyIndex[v].second;
                }

                copyIndexSet(srcIdx,
                             vTriIndices,
                             dstIdx,
                             dstOffset  );

                dstOffset += 3;

                ++returnValue;
                ++m;

                /* remove v from remaining polygon */
                for(Int32 s = v, t = v + 1; t < nv; ++s, ++t) 
                    vPolyIndex[s] = vPolyIndex[t]; 

                --nv;

                /* resest error detection counter */
                count = 2 * nv;
            }
        }

        return returnValue;
    }

} // namespace


/* ======================================================================== */

/*! Modifies the Geometry \a geo to use a single index for all
    properties.

    This creates new GeoVectorProperties (of the same type) for all
    properties and creates a new index. The geometry must be (multi) indexed.
*/

void
makeSingleIndexed(Geometry *geo)
{
    if(geo->isSingleIndex() == true)
    {
        SINFO << "Geometry is already single indexed, nothing to do."
              << std::endl;
        return;
    }

    bool hasIndex = false;

    for(UInt32 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) != NULL)
        {
            hasIndex = true;
            break;
        }
    }

    if(hasIndex == false)
    {
        SWARNING << "No index found, aborting."
                 << std::endl;
        return;
    }

    // 1) compute the set of unique index tuples
    //    itSet contains the offset into the geo's indices
    //          for unique index tuples
    //    index contains the new offset for a index tuple
    //
    //    0*  1*  2*  3   4   5*  6   7   8*   *'ed elements are in itSet
    //
    //    x   x   x   x   x   x   x   x   x    idx for prop 0
    //    0   1   2   2   1   3   2   3   4    idx for prop 1
    //    x   x   x   x   x   x   x   x   x    idx for prop 2
    //
    //    0   1   2   2   1   3   2   3   4    contents of index
    //
    //    the comparison function object used for itSet is what
    //    enables the detection of duplicate index tuples

#if defined(OSG_GEOOPT_STATISTICS)
    Time start1 = getSystemTime();
#endif

    typedef std::vector<UInt32> IndexUI32;

    ITSet     itSet((ITLess(geo)));
    //ITSet     itSet(10, ITHash(geo), ITEqual(geo));
    IndexUI32 index;

    GeoIntegralProperty *lengths  = geo->getLengths();
    UInt32               lengthsN = lengths->size32();
    UInt32               k        = 0;

    for(UInt32 i = 0; i < lengthsN; ++i)
    {
        UInt32 len;
        lengths->getValue(len, i);

        for(UInt32 j = 0; j < len; ++j)
        {
            ITSet::const_iterator isIt = itSet.find(k);

            if(isIt != itSet.end())
            {
                // already encountered index tuple
                index.push_back(index[*isIt]);
            }
            else
            {
                // new unique index tuple
                index.push_back(UInt32(itSet.size()));
                itSet.insert(k);
            }

            ++k;
        }
    }

#if defined(OSG_GEOOPT_STATISTICS)
    SLOG << "time to compute unique index tuples: " << (getSystemTime() - start1)
         << std::endl;

    Time start2 = getSystemTime();
#endif

    // 2) rewrite properties
    //
    //    For existing propery propN and its index propNIdx we
    //    fill the new proprty newPropN.
    //    index[*isIt] is the unique index tuple number for *isIt
    //
    //    newPropN[index[*isIt]] = propN[propNIdx[*isIt]]

    PropertyStore   prop;
    PropertyStore   newProp;
    PropIndexStore  propIdx;

    // create new properties
    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getProperty(i) != NULL)
        {
            bool add = true;

            for(UInt32 j = 0; add == true && j < prop.size(); ++j)
            {
                if(prop[j] == geo->getProperty(i))
                    add = false;
            }

            if(add == true)
            {
                // property present, but no index?
                OSG_ASSERT(geo->getIndex(i) != NULL);

                prop   .push_back(geo->getProperty(i));
                propIdx.push_back(geo->getIndex   (i));

                // create new propery of same type
                GeoVectorPropertyUnrecPtr np =
                    dynamic_pointer_cast<GeoVectorProperty>(
                        geo->getProperty(i)->getType().createContainer());
                np->resize(itSet.size());

                newProp.push_back(np);
            }
        }
    }

    // fill new properties
    UInt32 propCount = UInt32(prop.size());

    ITSet::const_iterator isIt  = itSet.begin();
    ITSet::const_iterator isEnd = itSet.end  ();

    for(; isIt != isEnd; ++isIt)
    {
        for(UInt32 i = 0; i < propCount; ++i)
        {
            GeoIntegralProperty::MaxTypeT  idx;
            GeoVectorProperty  ::MaxTypeT  val;

            propIdx[i]->getValue(idx, *isIt);
            prop[i]   ->getValue(val, idx  );

            newProp[i]->setValue(val, index[*isIt]);
        }
    }

    // create new index
    GeoUInt32PropertyUnrecPtr newIdx = GeoUInt32Property::create();
    newIdx->editFieldPtr()->insert(
        newIdx->editFieldPtr()->begin(),
        index.begin(), index.end()      );

    // set new properties and index on geometry
    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getProperty(i) != NULL)
        {
            for(UInt32 j = 0; j < prop.size(); ++j)
            {
                if(prop[j] == geo->getProperty(i))
                {
                    geo->setProperty(newProp[j], i);
                    break;
                }
            }

            geo->setIndex(newIdx, i);
        }
        else
        {
            geo->setIndex(NULL, i);
        }
    }

#if defined(OSG_GEOOPT_STATISTICS)
    SLOG << "time to rewrite properties: " << (getSystemTime() - start2)
         << std::endl;
#endif
}

/* ======================================================================== */

/*! Converts all "face" primitives (triangles strips/fans, quads, quad strips,
    polygons) to triangle lists. 

    This modifies the types and lengths of the geometry and replaces indices
    with new ones.

    Assumes valid OpenGL conforming convex primitives
 */

void makeIndexedTriangles(Geometry *geo,
                          bool      bKeepLowerDimPrimitives)
{
#if defined(OSG_GEOOPT_STATISTICS)
    Time start = getSystemTime();
#endif

    // 1) find unique index properties used by the geometry and create
    //    new ones of the same size (if necessary the new indices are
    //    grown by the copyIndices() helper function)

    PropIndexStore oldIdx;
    PropIndexStore newIdx;

    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) != NULL)
        {
            bool add = true;

            for(UInt32 j = 0; add == true && j < oldIdx.size(); ++j)
            {
                if(geo->getIndex(i) == oldIdx[j])
                    add = false;
            }

            if(add == true)
            {
                oldIdx.push_back(geo->getIndex(i));

                newIdx.push_back(GeoUInt32Property::create());
                newIdx.back()->resize(oldIdx.back()->size());
            }
        }
    }

    GeoIntegralProperty *oldTypes   = geo->getTypes  ();
    GeoIntegralProperty *oldLengths = geo->getLengths();

    if(oldTypes->size() != oldLengths->size())
    {
        SWARNING << "Types and Lengths have inconsistent size, aborting."
                 << std::endl;
        return;
    }

    // 2a) loop over all primitives first copying those that can
    //     not be converted to GL_TRIANGLES (e.g. lines, points,
    //     unknown primitives).
    //     This allows group all primitives that can be converted
    //     to be grouped into one GL_TRIANGLES primitive at
    //     the end.

    GeoIntegralPropertyUnrecPtr newTypes   =
        dynamic_pointer_cast<GeoIntegralProperty>(
            oldTypes->getType().createContainer());
    GeoIntegralPropertyUnrecPtr newLengths =
        dynamic_pointer_cast<GeoIntegralProperty>(
            oldLengths->getType().createContainer());

    bool   doSecondPass = false;
    UInt32 primCount    = oldTypes->size32();
    UInt32 srcOffset    = 0;
    UInt32 dstOffset    = 0;

    if(bKeepLowerDimPrimitives == true)
    {
        for(UInt32 i = 0; i < primCount; ++i)
        {
            UInt32 type = oldTypes  ->getValue(i);
            UInt32 len  = oldLengths->getValue(i);

            switch(type)
            {
                case GL_POINTS:
                case GL_LINES:
                case GL_LINE_LOOP:
                case GL_LINE_STRIP:
                {
                    // not a "face" primitive, copy indices unchanged
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, len);
                    srcOffset += len;
                    dstOffset += len;

                    newTypes  ->push_back(type);
                    newLengths->push_back(len );
                }
                break;

                case GL_TRIANGLES:
                case GL_TRIANGLE_STRIP:
                case GL_TRIANGLE_FAN:
                case GL_POLYGON:
                case GL_QUADS:
                case GL_QUAD_STRIP:
                {
                    // these can be converted, we handle them later
                    doSecondPass = true;
                }
                break;
                
                default:
                {
                    // unknown primitive, copy indices unchanged
                    SWARNING << "Unknown primitive type " << type
                             << " copying indices unchanged." << std::endl;
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, len);
                    srcOffset += len;
                    dstOffset += len;
                    
                    newTypes  ->push_back(type);
                    newLengths->push_back(len );
                }
                break;
            }
        }
    }
    else
    {
        doSecondPass = true;
    }

    // 2b) if we encountered any primitive that can be converted,
    //     do a second pass over all primitives handling only the
    //     ones that can be converted.

    if(doSecondPass == true)
    {
        GLenum lastPrim = GL_NONE;

        for(UInt32 i = 0; i < primCount; ++i)
        {
            UInt32 lengthsCount = newLengths->size32();
            UInt32 type         = oldTypes  ->getValue(i);
            UInt32 len          = oldLengths->getValue(i);

            switch(type)
            {
            case GL_TRIANGLES:
            {
                // already tris, copy indices unchanged
                copyIndices(oldIdx, srcOffset, newIdx, dstOffset, len);
                srcOffset += len;
                dstOffset += len;

                if(lastPrim == GL_TRIANGLES)
                {
                    newLengths->setValue(
                        newLengths->getValue(lengthsCount - 1) + len,
                        lengthsCount - 1);
                }
                else
                {
                    newTypes  ->push_back(GL_TRIANGLES);
                    newLengths->push_back(len);
                    lastPrim = GL_TRIANGLES;
                }
            }
            break;
            case GL_TRIANGLE_STRIP:
            {
                if(len < 3)
                {
                    SWARNING << "Encountered degenerate TRIANGLE_STRIP,"
                             << " aborting."
                             << std::endl;
                    return;
                }
                copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                srcOffset += 3;
                dstOffset += 3;

                for(UInt32 j = 3; j < len; ++j)
                {
                    if(j % 2 == 0)
                    {
                        copyIndices(oldIdx, srcOffset-2, newIdx, dstOffset  );
                        copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset+1);
                        copyIndices(oldIdx, srcOffset,   newIdx, dstOffset+2);
                    }
                    else
                    {
                        copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset  );
                        copyIndices(oldIdx, srcOffset-2, newIdx, dstOffset+1);
                        copyIndices(oldIdx, srcOffset,   newIdx, dstOffset+2);
                    }

                    srcOffset += 1;
                    dstOffset += 3;
                }

                if(lastPrim == GL_TRIANGLES)
                {
                    newLengths->setValue(
                        newLengths->getValue(lengthsCount - 1) + 3 * (len - 2),
                        lengthsCount - 1);
                }
                else
                {
                    newTypes  ->push_back(GL_TRIANGLES);
                    newLengths->push_back(3 * (len - 2));
                    lastPrim = GL_TRIANGLES;
                }
            }
            break;
            case GL_TRIANGLE_FAN:
            case GL_POLYGON:
            {
                if(len < 3)
                {
                    SWARNING << "Encountered degenerate TRIANGLE_FAN "
                             << "or POLYGON, aborting."
                             << std::endl;
                    return;
                }
                UInt32 firstSrcOffset = srcOffset;
                copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                srcOffset += 3;
                dstOffset += 3;

                for(UInt32 j = 3; j < len; ++j)
                {
                    copyIndices(oldIdx, firstSrcOffset, newIdx, dstOffset  );
                    copyIndices(oldIdx, srcOffset-1,    newIdx, dstOffset+1);
                    copyIndices(oldIdx, srcOffset,      newIdx, dstOffset+2);

                    srcOffset += 1;
                    dstOffset += 3;
                }

                if(lastPrim == GL_TRIANGLES)
                {
                    newLengths->setValue(
                        newLengths->getValue(lengthsCount - 1) + 3 * (len - 2),
                        lengthsCount - 1);
                }
                else
                {
                    newTypes  ->push_back(GL_TRIANGLES);
                    newLengths->push_back(3 * (len - 2));
                    lastPrim = GL_TRIANGLES;
                }
            }
            break;
            case GL_QUADS:
            {
                if(len < 4 || len % 4 != 0)
                {
                    SWARNING << "Encountered degenerate QUADS, aborting."
                             << std::endl;
                    return;
                }
                for(UInt32 j = 0; j < len / 4; ++j)
                {
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                    srcOffset += 3;
                    dstOffset += 3;
                    copyIndices(oldIdx, srcOffset-3, newIdx, dstOffset  );
                    copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset+1);
                    copyIndices(oldIdx, srcOffset,   newIdx, dstOffset+2);
                    srcOffset += 1;
                    dstOffset += 3;
                }

                if(lastPrim == GL_TRIANGLES)
                {
                    newLengths->setValue(
                        newLengths->getValue(lengthsCount - 1) + 3 * (len / 2),
                        lengthsCount - 1);
                }
                else
                {
                    newTypes  ->push_back(GL_TRIANGLES);
                    newLengths->push_back(3 * (len / 2));
                    lastPrim = GL_TRIANGLES;
                }
            }
            break;
            case GL_QUAD_STRIP:
            {
                if(len < 4 || len % 2 != 0)
                {
                    SWARNING << "Encountered degenerate QUAD_STRIP, aborting."
                             << std::endl;
                    return;
                }
                copyIndices(oldIdx, srcOffset,   newIdx, dstOffset  );
                copyIndices(oldIdx, srcOffset+2, newIdx, dstOffset+1);
                copyIndices(oldIdx, srcOffset+1, newIdx, dstOffset+2);
                srcOffset += 1;
                dstOffset += 3;
                copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                srcOffset += 3;
                dstOffset += 3;

                for(UInt32 j = 4; j < len; j += 2)
                {
                    copyIndices(oldIdx, srcOffset-2, newIdx, dstOffset  );
                    copyIndices(oldIdx, srcOffset,   newIdx, dstOffset+1);
                    copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset+2);
                    dstOffset += 3;
                    copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset, 3);
                    srcOffset += 2;
                    dstOffset += 3;
                }

                if(lastPrim == GL_TRIANGLES)
                {
                    newLengths->setValue(
                        newLengths->getValue(lengthsCount - 1) + 3 * (len - 2),
                        lengthsCount - 1);
                }
                else
                {
                    newTypes  ->push_back(GL_TRIANGLES);
                    newLengths->push_back(3 * (len - 2));
                    lastPrim = GL_TRIANGLES;
                }
            }
            break;
            }
        }
    }

    geo->setTypes  (newTypes  );
    geo->setLengths(newLengths);

    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) != NULL)
        {
            for(UInt32 j = 0; j < oldIdx.size(); ++j)
            {
                if(geo->getIndex(i) == oldIdx[j])
                {
                    geo->setIndex(newIdx[j], i);
                    break;
                }
            }
        }
    }

#if defined(OSG_GEOOPT_STATISTICS)
    SLOG << "time to rewrite types/len/indices: " << (getSystemTime() - start)
         << std::endl;
#endif
}

/* checks and creates explicit index properties if not present */

void createExplicitIndex(Geometry *geo)
{
    bool hasIndex = false;

    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) != NULL)
        {
            hasIndex = true;
            break;
        }
    }

    if(hasIndex == false)
    {
        GeoVectorProperty *pPos = geo->getProperty(Geometry::PositionsIndex);

        if(pPos == NULL)
        {
            fprintf(stderr, "no positions, abort\n");
            return;
        }

        GeoUInt32PropertyUnrecPtr pNewIdx = GeoUInt32Property::create();

        pNewIdx->editField().reserve(pPos->size());

        for(SizeT i = 0; i < pPos->size(); ++i)
        {
            pNewIdx->push_back(i);
        }
        
        for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
        {
            if(geo->getProperty(i) != NULL)
            {
                if(geo->getProperty(i)->size() != pPos->size())
                {
                    SWARNING << "inconsitent property sizes, interesting "
                             << "things might happen ;)" 
                             << std::endl;
                }

                geo->setIndex(pNewIdx, i);
            }
        }
    }

}

/*! Converts all "face" primitives (triangles strips/fans, quads, quad strips,
    polygons) to triangle lists. 

    This modifies the types and lengths of the geometry and replaces indices
    with new ones.

    Does not assume valid, OpenGL conforming convex GL_POLYGON and GL_QUADS
    primitives.

    GL_QUAD_STRIPs are assumed to contain convex primitives.
 */

void makeIndexedTrianglesConcave(Geometry *geo, 
                                 bool      bKeepLowerDimPrimitives)
{
#if defined(OSG_GEOOPT_STATISTICS)
    Time start = getSystemTime();
#endif

    // 1) find unique index properties used by the geometry and create
    //    new ones of the same size (if necessary the new indices are
    //    grown by the copyIndices() helper function)

    PropIndexStore oldIdx;
    PropIndexStore newIdx;

    createExplicitIndex(geo);

    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) != NULL)
        {
            bool add = true;

            for(UInt32 j = 0; add == true && j < oldIdx.size(); ++j)
            {
                if(geo->getIndex(i) == oldIdx[j])
                    add = false;
            }

            if(add == true)
            {
                oldIdx.push_back(geo->getIndex(i));

                newIdx.push_back(GeoUInt32Property::create());
                newIdx.back()->resize(oldIdx.back()->size());
            }
        }
    }                

    GeoIntegralProperty *oldTypes   = geo->getTypes  ();
    GeoIntegralProperty *oldLengths = geo->getLengths();
    
    if(oldTypes == NULL || oldLengths == NULL)
    {
        SWARNING << "Either no Types and Lengths, aborting."
                 << std::endl;
        return;
    }

    if(oldTypes->size() != oldLengths->size())
    {
        SWARNING << "Types and Lengths have inconsistent size, aborting."
                 << std::endl;
        return;
    }

    // 2a) loop over all primitives first copying those that can
    //     not be converted to GL_TRIANGLES (e.g. lines, points,
    //     unknown primitives).
    //     This allows group all primitives that can be converted
    //     to be grouped into one GL_TRIANGLES primitive at
    //     the end.

    GeoIntegralPropertyUnrecPtr newTypes   =
        dynamic_pointer_cast<GeoIntegralProperty>(
            oldTypes->getType().createContainer());
    GeoIntegralPropertyUnrecPtr newLengths =
        dynamic_pointer_cast<GeoIntegralProperty>(
            oldLengths->getType().createContainer());

    bool   doSecondPass = false;
    UInt32 primCount    = oldTypes->size32();
    UInt32 srcOffset    = 0;
    UInt32 dstOffset    = 0;

    if(bKeepLowerDimPrimitives == true)
    {
        for(UInt32 i = 0; i < primCount; ++i)
        {
            UInt32 type = oldTypes  ->getValue(i);
            UInt32 len  = oldLengths->getValue(i);

            switch(type)
            {
                case GL_POINTS:
                case GL_LINES:
                case GL_LINE_LOOP:
                case GL_LINE_STRIP:
                {
                    // not a "face" primitive, copy indices unchanged
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, len);
                    srcOffset += len;
                    dstOffset += len;
                
                    newTypes  ->push_back(type);
                    newLengths->push_back(len );
                }
                break;

                case GL_TRIANGLES:
                case GL_TRIANGLE_STRIP:
                case GL_TRIANGLE_FAN:
                case GL_POLYGON:
                case GL_QUADS:
                case GL_QUAD_STRIP:
                {
                    // these can be converted, we handle them later
                    doSecondPass = true;
                }
                break;

                default:
                {
                    // unknown primitive, copy indices unchanged
                    SWARNING << "Unknown primitive type " << type
                             << " copying indices unchanged." << std::endl;
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, len);
                    srcOffset += len;
                    dstOffset += len;
                    
                    newTypes  ->push_back(type);
                    newLengths->push_back(len );
                }
                break;
            }
        }
    }
    else
    {
        doSecondPass = true;
    }

    // 2b) if we encountered any primitive that can be converted,
    //     do a second pass over all primitives handling only the
    //     ones that can be converted.

    if(doSecondPass == true)
    {
        GLenum lastPrim = GL_NONE;

        IndexVec vPolyIndex;

        for(UInt32 i = 0; i < primCount; ++i)
        {
            UInt32 lengthsCount = newLengths->size32();
            UInt32 type         = oldTypes  ->getValue(i);
            UInt32 len          = oldLengths->getValue(i);

            switch(type)
            {
                case GL_TRIANGLES:
                {
                    // already tris, copy indices unchanged
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, len);
                    srcOffset += len;
                    dstOffset += len;
                    
                    if(lastPrim == GL_TRIANGLES)
                    {
                        newLengths->setValue(
                            newLengths->getValue(lengthsCount - 1) + len,
                            lengthsCount - 1);
                    }
                    else
                    {
                        newTypes  ->push_back(GL_TRIANGLES);
                        newLengths->push_back(len);
                        lastPrim = GL_TRIANGLES;
                    }
                }
                break;

                case GL_TRIANGLE_STRIP:
                {
                    if(len < 3)
                    {
                        SWARNING << "Encountered degenerate TRIANGLE_STRIP,"
                                 << " aborting."
                                 << std::endl;
                        return;
                    }
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                    srcOffset += 3;
                    dstOffset += 3;

                    for(UInt32 j = 3; j < len; ++j)
                    {
                        if(j % 2 == 0)
                        {
                            copyIndices(oldIdx, srcOffset-2, 
                                        newIdx, dstOffset  );
                            copyIndices(oldIdx, srcOffset-1, 
                                        newIdx, dstOffset+1);
                            copyIndices(oldIdx, srcOffset,   
                                        newIdx, dstOffset+2);
                        }
                        else
                        {
                            copyIndices(oldIdx, srcOffset-1, 
                                        newIdx, dstOffset  );
                            copyIndices(oldIdx, srcOffset-2, 
                                        newIdx, dstOffset+1);
                            copyIndices(oldIdx, srcOffset,   
                                        newIdx, dstOffset+2);
                        }

                        srcOffset += 1;
                        dstOffset += 3;
                    }

                    if(lastPrim == GL_TRIANGLES)
                    {
                        newLengths->setValue(
                            newLengths->getValue(
                                lengthsCount - 1) + 3 * (len - 2),
                            lengthsCount - 1);
                    }
                    else
                    {
                        newTypes  ->push_back(GL_TRIANGLES);
                        newLengths->push_back(3 * (len - 2));
                        lastPrim = GL_TRIANGLES;
                    }
                }
                break;

                case GL_TRIANGLE_FAN:
                {
                    if(len < 3)
                    {
                        SWARNING << "Encountered degenerate TRIANGLE_FAN, "
                                 << "aborting."
                                 << std::endl;
                        return;
                    }

                    UInt32 firstSrcOffset = srcOffset;
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                    srcOffset += 3;
                    dstOffset += 3;

                    for(UInt32 j = 3; j < len; ++j)
                    {
                        copyIndices(oldIdx, firstSrcOffset, 
                                    newIdx, dstOffset  );
                        copyIndices(oldIdx, srcOffset-1,    
                                    newIdx, dstOffset+1);
                        copyIndices(oldIdx, srcOffset,      
                                    newIdx, dstOffset+2);
                        
                        srcOffset += 1;
                        dstOffset += 3;
                    }

                    if(lastPrim == GL_TRIANGLES)
                    {
                        newLengths->setValue(
                            newLengths->getValue(
                                lengthsCount - 1) + 3 * (len - 2),
                            lengthsCount - 1);
                    }
                    else
                    {
                        newTypes  ->push_back(GL_TRIANGLES);
                        newLengths->push_back(3 * (len - 2));
                        lastPrim = GL_TRIANGLES;
                    }
                }
                break;

                case GL_POLYGON:
                {
                    if(len < 3)
                    {
                        SWARNING << "Encountered degenerate "
                                 << "POLYGON, aborting."
                                 << std::endl;
                        return;
                    }

                    vPolyIndex.resize(len);

                    for(UInt32 j = 0; j < len; ++j)
                    {
                        oldIdx[0]->getValue(vPolyIndex[j].first, srcOffset + j);

                        vPolyIndex[j].second = srcOffset + j;
                    }

                    UInt32 res = triangulatePoly(vPolyIndex, 

                                                 oldIdx,

                                                 newIdx, 
                                                 dstOffset,

                                                 len,
                                                 geo       );

                    srcOffset += len;

                    if(lastPrim == GL_TRIANGLES)
                    {
                        newLengths->setValue(
                            newLengths->getValue(
                                lengthsCount - 1) + 3 * res,
                            lengthsCount - 1);
                    }
                    else
                    {
                        newTypes  ->push_back(GL_TRIANGLES);
                        newLengths->push_back(3 * res);
                        lastPrim = GL_TRIANGLES;
                    }
                }
                break;

                case GL_QUADS:
                {
                    if((len < 4 || len % 4 != 0))
                    {
                        SWARNING << "Encountered degenerate QUADS, aborting."
                                 << std::endl;
                        return;
                    }

                    vPolyIndex.resize(4);

                    for(UInt32 k = 0; k < len; k += 4)
                    {
                        for(UInt32 j = 0; j < 4; ++j)
                        {
                            oldIdx[0]->getValue(vPolyIndex[j].first, 
                                                srcOffset + j);

                            vPolyIndex[j].second = srcOffset + j;
                        }

                        UInt32 res = triangulatePoly(vPolyIndex, 

                                                     oldIdx,

                                                     newIdx, 
                                                     dstOffset,

                                                     4,
                                                     geo       );

                        srcOffset += 4;

                        if(lastPrim == GL_TRIANGLES)
                        {
                            newLengths->setValue(
                                newLengths->getValue(
                                    lengthsCount - 1) + 3 * res,
                                lengthsCount - 1);
                        }
                        else
                        {
                            newTypes  ->push_back(GL_TRIANGLES);
                            newLengths->push_back(3 * res);
                            lastPrim = GL_TRIANGLES;
                        }

                        lengthsCount = newLengths->size32();
                    }
                }
                break;

                case GL_QUAD_STRIP:
                {
                    if(len < 4 || len % 2 != 0)
                    {
                        SWARNING << "Encountered degenerate QUAD_STRIP, "
                                 << "aborting."
                                 << std::endl;
                        return;
                    }

                    copyIndices(oldIdx, srcOffset,   newIdx, dstOffset  );
                    copyIndices(oldIdx, srcOffset+2, newIdx, dstOffset+1);
                    copyIndices(oldIdx, srcOffset+1, newIdx, dstOffset+2);
                    srcOffset += 1;
                    dstOffset += 3;
                    copyIndices(oldIdx, srcOffset, newIdx, dstOffset, 3);
                    srcOffset += 3;
                    dstOffset += 3;
                    
                    for(UInt32 j = 4; j < len; j += 2)
                    {
                        copyIndices(oldIdx, srcOffset-2, newIdx, dstOffset  );
                        copyIndices(oldIdx, srcOffset,   newIdx, dstOffset+1);
                        copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset+2);
                        dstOffset += 3;
                        copyIndices(oldIdx, srcOffset-1, newIdx, dstOffset, 3);
                        srcOffset += 2;
                        dstOffset += 3;
                    }
                    
                    if(lastPrim == GL_TRIANGLES)
                    {
                        newLengths->setValue(
                            newLengths->getValue(
                                lengthsCount - 1) + 3 * (len - 2),
                            lengthsCount - 1);
                    }
                    else
                    {
                        newTypes  ->push_back(GL_TRIANGLES);
                        newLengths->push_back(3 * (len - 2));
                        lastPrim = GL_TRIANGLES;
                    }
                }
                break;
            }
        }
    }

    geo->setTypes  (newTypes  );
    geo->setLengths(newLengths);

    for(UInt16 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) != NULL)
        {
            for(UInt32 j = 0; j < oldIdx.size(); ++j)
            {
                if(geo->getIndex(i) == oldIdx[j])
                {
                    geo->setIndex(newIdx[j], i);
                    break;
                }
            }
        }
    }

#if defined(OSG_GEOOPT_STATISTICS)
    SLOG << "time to rewrite types/len/indices: " << (getSystemTime() - start)
         << std::endl;
#endif
}

/* ======================================================================== */

namespace
{
    // Helper types and functions for makeOptimizedIndex().

    const UInt32 ModelledVertexCacheSize =  32;
    const Real32 CachePosScorePower      =  1.5f;
    const Real32 ValenceScoreScale       =  2.0f;
    const Real32 ValenceScorePower       = -0.5f;

    struct VertexInfo
    {
        typedef std::vector<UInt32> IndexStore;

        VertexInfo(void);

        UInt32     _cachePos;
        Real32     _score;
        UInt32     _totalValence;
        UInt32     _remValence;
        IndexStore _triIndices;
    };

    VertexInfo::VertexInfo(void)
        : _cachePos    (TypeTraits<UInt32>::getMax()),
          _score       (0.f),
          _totalValence(0),
          _remValence  (0),
          _triIndices  ()
    {
    }

    typedef std::vector<VertexInfo> VertexInfoStore;

    /* ==================================================================== */

    struct TriangleInfo
    {
        TriangleInfo(void);

        Real32 _score;
        UInt32 _vertIndices[3];
        bool   _added;
    };

    TriangleInfo::TriangleInfo(void)
        : _score      (0.f),
          _vertIndices(),
          _added      (false)
    {
    }

    typedef std::vector<TriangleInfo> TriangleInfoStore;

    /* ==================================================================== */

    // Calculate a vertex' score, based on _remValence
    // and _cachePos.
    // Then update triangles that use the vertex, by adding
    // the change in score to their score and keeping track
    // of the one with the highest score.
    void
    updateVertexScore(VertexInfo        &vi,
                      TriangleInfoStore &tis,
                      Real32            &bestTriScore,
                      UInt32            &bestTriIndex )
    {
        Real32 oldScore = vi._score;

        if(vi._remValence > 0)
        {
            // base score based on position in cache
            if(vi._cachePos == TypeTraits<UInt32>::getMax())
            {
                vi._score = 0.f;
            }
            else if(vi._cachePos < 3)
            {
                vi._score = 0.75f;
            }
            else
            {
                const Real32 scale = 1.f / (ModelledVertexCacheSize - 3);
                vi._score = scale * (vi._cachePos - 3);
                vi._score = std::pow(1.f - vi._score, CachePosScorePower);
            }

            // boost for having low valence
            vi._score  += ValenceScoreScale * std::pow(vi._remValence,
                                                       ValenceScorePower);
        }
        else
        {
            vi._score = 0.f;
        }

        Real32 deltaScore = vi._score - oldScore;

#if defined(OSG_GEOOPT_VERBOSE)
        SLOG << "update score: score " << vi._score
             << " cache pos " << vi._cachePos
             << " totalValence " << vi._totalValence
             << " remValence " << vi._remValence
             << std::endl;
#endif

        // update triangles
        for(UInt32 i = 0; i < vi._remValence; ++i)
        {
            UInt32 triIdx = vi._triIndices[i];

            tis[triIdx]._score += deltaScore;

#if defined(OSG_GEOOPT_VERBOSE)
            SLOG << "  updating tri " << triIdx
                 << " score " << tis[triIdx]._score;
#endif

            // we don't need to check tis[triIdx]._added
            // because the vertex we are updating has
            // it among the first _remValence ones,
            // so it was not added yet.
            if(tis[triIdx]._score > bestTriScore)
            {
#if defined(OSG_GEOOPT_VERBOSE)
                PLOG << " new best";
#endif

                bestTriScore = tis[triIdx]._score;
                bestTriIndex = triIdx;
            }

#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << std::endl;
#endif
        }
    }

    /* ==================================================================== */

    // updates vertex info when triangle usedTriIndex is
    // added - reduces _remValence by one and shuffles
    // _triIndices around to ensure the ones belonging
    // to not-yet-added triangles come first
    void
    updateUsedVertex(VertexInfo &vi, UInt32 usedTriIndex)
    {
        for(UInt32 j = 0; j < vi._remValence; ++j)
        {
            if(vi._triIndices[j] == usedTriIndex)
            {
                // move tri index back, so first vi._remValence many
                // are the ones that still need to be added
                std::swap(vi._triIndices[j               ],
                          vi._triIndices[vi._remValence-1] );
                break;
            }
        }

        vi._remValence -= 1;
    }

    /* ==================================================================== */

    // Comparison function object for the LRU cache,
    // sorts VertexInfos by making NULL less than every non-NULL
    // one, and sort non-NULL ones by their _cachePos.
    // This ensures we move the 3 NULL slots for the current
    // triangles vertices to the front.
    struct LRULess
    {
        bool operator()(VertexInfo *lhs, VertexInfo *rhs);
    };

    bool
    LRULess::operator()(VertexInfo *lhs, VertexInfo *rhs)
    {
        bool retVal = false;

        if(lhs == rhs)
        {
            retVal = false;
        }
        else if(lhs == NULL)
        {
            retVal = true;
        }
        else if(rhs == NULL)
        {
            retVal = false;
        }
        else
        {
            retVal = lhs->_cachePos < rhs->_cachePos;
        }

        return retVal;
    }

    /* ==================================================================== */

#if defined(OSG_GEOOPT_STATISTICS)
    void
    calcCacheMissCount(Geometry *geo, UInt32 &missCount, UInt32 &hitCount)
    {
        typedef std::list<UInt32> LRUCache;

        GeoIntegralProperty *types    = geo->getTypes  ();
        GeoIntegralProperty *lengths  = geo->getLengths();
        GeoIntegralProperty *propIdx0 = geo->getIndex(0);

        UInt32   k         = 0;
        UInt32   lruSize   = 0;
        LRUCache lru;

        for(UInt32 i = 0; i < types->size(); ++i)
        {
            GLenum type = types  ->getValue(i);
            UInt32 len  = lengths->getValue(i);

            if(type != GL_TRIANGLES)
            {
                k += len;
                continue;
            }

            for(UInt32 j = 0; j < len; ++j, ++k)
            {
                UInt32 idx = propIdx0->getValue(k);

                LRUCache::iterator lruIt = std::find(lru.begin(), lru.end(), idx);

                if(lruIt != lru.end())
                {
                    ++hitCount;
                    lru.erase(lruIt);
                }
                else
                {
                    ++missCount;
                    ++lruSize;
                }

                lru.push_front(idx);

                while(lruSize > ModelledVertexCacheSize)
                {
                    lru.pop_back();
                    --lruSize;
                }
            }
        }
    }
#endif
} // namespace

/*! Optimize the index of triangle lists for the post-transform
  vertex cache.
  Based on "Post-Transform Cache Optimization for Indexed Triangle
  Lists" by Tom Forsyth, see
  http://home.comcast.net/~tom_forsyth/papers/fast_vertex_cache_opt.html

  Only works on GL_TRIANGLES primitives in the geometry and requires
  the geometry to be single indexed.
*/

void
makeOptimizedIndex(Geometry *geo)
{
    if(geo->isSingleIndex() == false)
    {
        SWARNING << "Only single indexed geometries can be optimized."
                 << std::endl;
        return;
    }

    GeoIntegralProperty *types   = geo->getTypes  ();
    GeoIntegralProperty *lengths = geo->getLengths();

    if(types->size() != lengths->size())
    {
        SWARNING << "Types and Lengths have inconsistent size, aborting."
                 << std::endl;
        return;
    }

    VertexInfoStore   vis;
    TriangleInfoStore tis;

    GeoVectorProperty           *prop0      = geo->getProperty(0);
    GeoIntegralPropertyUnrecPtr  propIdx0   = geo->getIndex   (0);
    GeoIntegralPropertyUnrecPtr  newPropIdx = GeoUInt32Property::create();

    if(prop0 == NULL || propIdx0 == NULL)
    {
        SWARNING << "No property 0 (positions) or index on geometry, "
                 << "aborting."
                 << std::endl;
        return;
    }

    newPropIdx->resize(propIdx0->size());

    // 1a) Initialize VertexInfos and TriangleInfos
    //     First go over geometry and find all GL_TRIANGLES primitives.
    //     For each triangle store the 3 vertices it uses,
    //     increment the valence counters of the vertices and
    //     add the triangle to the list of triangles the vertex belongs to

    vis.resize(prop0->size());

    UInt32 triCount = 0;
    UInt32 k        = 0;

    // loop over all primitives
    for(UInt32 i = 0; i < types->size(); ++i)
    {
        UInt32 type = types  ->getValue(i);
        UInt32 len  = lengths->getValue(i);

        // skip non triangles
        if(type != GL_TRIANGLES)
        {
            k += len;
            continue;
        }

        if(len % 3 != 0)
        {
            SWARNING << "Encountered degenerate GL_TRIANGLES, aborting."
                     << std::endl;
            return;
        }

        // loop over triangles
        tis.resize(triCount + len / 3);

        for(UInt32 j = 0; j < len; j += 3)
        {
            // update vertices used by triangle
            UInt32 idx0 = propIdx0->getValue(k++);
            UInt32 idx1 = propIdx0->getValue(k++);
            UInt32 idx2 = propIdx0->getValue(k++);

            if(idx0 == idx1 || idx0 == idx2 || idx1 == idx2)
                continue;

            vis[idx0]._totalValence += 1;
            vis[idx0]._remValence   += 1;
            vis[idx0]._triIndices.push_back(triCount);

            vis[idx1]._totalValence += 1;
            vis[idx1]._remValence   += 1;
            vis[idx1]._triIndices.push_back(triCount);

            vis[idx2]._totalValence += 1;
            vis[idx2]._remValence   += 1;
            vis[idx2]._triIndices.push_back(triCount);

            // record vertices used by triangle
            tis[triCount]._vertIndices[0] = idx0;
            tis[triCount]._vertIndices[1] = idx1;
            tis[triCount]._vertIndices[2] = idx2;

            triCount += 1;
        }
    }

    if(triCount == 0)
    {
        SINFO << "Geometry does not contain any GL_TRIANGLES, ignoring."
              << std::endl;
        return;
    }

#if defined(OSG_GEOOPT_STATISTICS)
    UInt32 preMissCount = 0;
    UInt32 preHitCount  = 0;
    calcCacheMissCount(geo, preMissCount, preHitCount);
#endif

    // 1b) Complete initialization by going over VertexInfos
    //     calculating the initial score and update triangles scores
    //     on the way.
    //     Also keep track of the triangle with the highest score
    //     to have a starting point for the main loop.

    Real32 bestTriScore = 0.f;
    UInt32 bestTriIndex = 0;

    VertexInfoStore::iterator viIt  = vis.begin();
    VertexInfoStore::iterator viEnd = vis.end  ();

    for(; viIt != viEnd; ++viIt)
    {
        updateVertexScore(*viIt, tis, bestTriScore, bestTriIndex);
    }

#if defined(OSG_GEOOPT_VERBOSE)
    SLOG << "post init: bestTriScore " << bestTriScore
         << " bestTriIndex " << bestTriIndex
         << std::endl;
#endif

    // 2) Main loop.
    //    Add triangles to index based on their score, update
    //    the LRU cache and affected scores after each step
    //    while keeping track of the triangle with the highest score.
    //    The triangle with highest score is only an approximation,
    //    because only tris with vertices in the LRU are considered.
    //    See the paper for more info.

    typedef std::vector<VertexInfo *> LRUType;
    LRUType lru(ModelledVertexCacheSize + 3, NULL);
    UInt32  lruSize = 0;

    for(UInt32 i = 0; i < triCount; ++i)
    {
#if defined(OSG_GEOOPT_VERBOSE)
        SLOG << "=== tri i " << i << " of " << triCount << " ==="
             << std::endl;
#endif

        // it's possible that all vertices in the cache belong
        // to triangles that are already added (very rare case).
        // Scan all triangles to find the best.
        if(bestTriScore             == 0.f  ||
           tis[bestTriIndex]._added == true   )
        {
#if defined(OSG_GEOOPT_VERBOSE)
            SLOG << "  no valid triangle with vertices in cache"
                 << " performing full search." << std::endl;
#endif

            bestTriScore = 0.f;
            bestTriIndex = 0;

            for(UInt32 j = 0; j < triCount; ++j)
            {
                if(tis[j]._added == false        &&
                   tis[j]._score >  bestTriScore   )
                {
                    bestTriScore = tis[j]._score;
                    bestTriIndex = j;
                }
            }
        }

        // Pick the triangle with the highest score and add it to the index
        TriangleInfo &bestTri = tis[bestTriIndex];

        newPropIdx->setValue(bestTri._vertIndices[0], i * 3    );
        newPropIdx->setValue(bestTri._vertIndices[1], i * 3 + 1);
        newPropIdx->setValue(bestTri._vertIndices[2], i * 3 + 2);

        VertexInfo &v0 = vis[bestTri._vertIndices[0]];
        VertexInfo &v1 = vis[bestTri._vertIndices[1]];
        VertexInfo &v2 = vis[bestTri._vertIndices[2]];

        updateUsedVertex(v0, bestTriIndex);
        updateUsedVertex(v1, bestTriIndex);
        updateUsedVertex(v2, bestTriIndex);

        bestTri._added = true;

#if defined(OSG_GEOOPT_VERBOSE)
        SLOG << "  adding best tri " << bestTriIndex
             << " with score " << bestTriScore;
#endif

        // if vertices of the added triangle are already
        // in the cache we clear out their entries and
        // keep track of how much the cache grows
        UInt32 lruGrow = 3;

        if(v0._cachePos != TypeTraits<UInt32>::getMax())
        {
#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << " v0 " << bestTri._vertIndices[0]
                 << " in cache (" << v0._cachePos << ")";
#endif
            lru[v0._cachePos]  = NULL;
            lruGrow           -= 1;
        }
        else
        {
#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << " v0 " << bestTri._vertIndices[0];
#endif
        }

        if(v1._cachePos != TypeTraits<UInt32>::getMax())
        {
#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << " v1 " << bestTri._vertIndices[1]
                 << " in cache (" << v1._cachePos << ")";
#endif
            lru[v1._cachePos]  = NULL;
            lruGrow           -= 1;
        }
        else
        {
#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << " v1 " << bestTri._vertIndices[1];
#endif
        }

        if(v2._cachePos != TypeTraits<UInt32>::getMax())
        {
#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << " v2 " << bestTri._vertIndices[2]
                 << " in cache (" << v2._cachePos << ")";
#endif
            lru[v2._cachePos]  = NULL;
            lruGrow           -= 1;
        }
        else
        {
#if defined(OSG_GEOOPT_VERBOSE)
            PLOG << " v2 " << bestTri._vertIndices[2];
#endif
        }

#if defined(OSG_GEOOPT_VERBOSE)
        PLOG << std::endl;
#endif

        // make sure there are lruGrow NULL entries after the
        // current size
        for(UInt32 j = lruSize; j < lruSize + lruGrow; ++j)
            lru[j] = NULL;

        // sort cache entries, moving NULL entries to the front,
        // other entries remain sorted by their _cachePos.
        std::sort(lru.begin(), lru.begin() + lruSize + lruGrow,
                  LRULess()                                       );

        OSG_ASSERT(lru[0] == NULL && lru[1] == NULL && lru[2] == NULL);

        // put the three used vertices at front of cache
        lru[2] = &v0;
        lru[1] = &v1;
        lru[0] = &v2;

        // update cache, setting correct position for entries
        // and recalculate score, keeping track of best triangle
        bestTriScore = 0.f;
        bestTriIndex = 0;

        for(UInt32 j = 0; j < lruSize + lruGrow; ++j)
        {
            if(j < ModelledVertexCacheSize)
            {
#if defined(OSG_GEOOPT_VERBOSE)
                SLOG << "  update cache j " << j << std::endl;
#endif

                lru[j]->_cachePos = j;
            }
            else
            {
#if defined(OSG_GEOOPT_VERBOSE)
                SLOG << "  update cache j " << j
                     << " -> evicted" << std::endl;
#endif

                lru[j]->_cachePos = TypeTraits<UInt32>::getMax();
            }

            updateVertexScore(*lru[j], tis, bestTriScore, bestTriIndex);
        }

        lruSize = osgMin(lruSize + lruGrow, ModelledVertexCacheSize);

#if defined(OSG_GEOOPT_VERBOSE)
        SLOG << "  new cache size " << lruSize
             << " lruGrow " << lruGrow
             << std::endl;
#endif
    }

    // set the new index on the geometry
    for(UInt32 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getIndex(i) == propIdx0)
        {
            geo->setIndex(newPropIdx, i);
        }
    }

#if defined(OSG_GEOOPT_STATISTICS)
    UInt32 postMissCount = 0;
    UInt32 postHitCount  = 0;
    calcCacheMissCount(geo, postMissCount, postHitCount);

    SLOG << "preMissCount " << preMissCount
         << " preHitCount " << preHitCount
         << " pre ACMR " << (Real32(preMissCount) / triCount)
         << " triCount " << triCount
         << std::endl;
    SLOG << "postMissCount " << postMissCount
         << " postHitCount " << postHitCount
         << " post ACMR " << (Real32(postMissCount) / triCount)
         << " triCount " << triCount
         << std::endl;
    SLOG << "old idx size " << propIdx0->size()
         << " new idx size " << newPropIdx->size()
         << std::endl;
#endif
}

/* ======================================================================== */

namespace
{
    // Helper types and functions for makeOptimizedProperties().

    // A pair of indices. Used to record a change from oldIdx to newIdx.
    struct IndexRemap
    {
        explicit IndexRemap(UInt32 oldIdx, UInt32 newIdx);

        UInt32 _oldIdx;
        UInt32 _newIdx;
    };

    /* explicit */
    IndexRemap::IndexRemap(UInt32 oldIdx, UInt32 newIdx)
        : _oldIdx(oldIdx),
          _newIdx(newIdx)
    {
    }

    // Comparison function object for IndexRemap, allows them to be used in
    // associative containers (std::set, std::map).
    // Only the old index is used for comparison.
    struct IndexRemapLess
    {
        bool operator()(const IndexRemap &lhs, const IndexRemap &rhs) const;
    };

    bool
    IndexRemapLess::operator()(const IndexRemap &lhs,
                               const IndexRemap &rhs ) const
    {
        return (lhs._oldIdx < rhs._oldIdx);
    }

    typedef std::set<IndexRemap, IndexRemapLess>  IndexRemapSet;

    // Copies property values from srcOffset in srcProps to destOffset
    // in the corresponding dstProps.
    void
    copyProperties(const PropertyStore &srcProps,
                   UInt32               srcOffset,
                   const PropertyStore &dstProps,
                   UInt32               dstOffset )
    {
        OSG_ASSERT(srcProps.size() == dstProps.size());

        for(UInt32 i = 0; i < srcProps.size(); ++i)
        {
            GeoVectorProperty::MaxTypeT val;
            srcProps[i]->getValue(val, srcOffset);
            dstProps[i]->setValue(val, dstOffset);
        }
    }

} // namespace

/*! Optimize properties of the geometry for the pre-transform vertex
    cache.
    Creates new properties that store values in the order referenced
    by the index (without duplicates) and creates a new index for
    the reordered properties. This does not change the order
    primitives are drawn in, so previos post-transform vertex cache
    optimizations are preserved.

    Requires the geometry to be single indexed.
 */

void
makeOptimizedProperties(Geometry *geo)
{
    if(geo->isSingleIndex() == false)
    {
        SWARNING << "Only single indexed geometries can be optimized."
                 << std::endl;
        return;
    }

    GeoIntegralProperty *types   = geo->getTypes  ();
    GeoIntegralProperty *lengths = geo->getLengths();

    if(types->size() != lengths->size())
    {
        SWARNING << "Types and Lengths have inconsistent size, aborting."
                 << std::endl;
        return;
    }

    GeoIntegralPropertyUnrecPtr propIdx0 = geo->getIndex(0);

    if(propIdx0 == NULL)
    {
        SWARNING << "No index for property 0 (positions), aborting."
                 << std::endl;
        return;
    }

    // create new properties of the same type as existing ones

    PropertyStore               prop;
    PropertyStore               newProp;
    GeoIntegralPropertyUnrecPtr newPropIdx = GeoUInt32Property::create();

    newPropIdx->resize(propIdx0->size());

    for(UInt32 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getProperty(i) != NULL)
        {
            bool add = true;

            for(UInt32 j = 0; add == true && j < prop.size(); ++j)
            {
                if(prop[j] == geo->getProperty(i))
                    add = false;
            }

            if(add == true)
            {
                // create new propery of same type
                GeoVectorPropertyUnrecPtr np =
                    dynamic_pointer_cast<GeoVectorProperty>(
                        geo->getProperty(i)->getType().createContainer());
                np->resize(geo->getProperty(i)->size());

                prop   .push_back(geo->getProperty(i));
                newProp.push_back(np);
            }
        }
    }

    // reorder properties
    // go through the index, filling the properties in the order
    // of access through the index.
    // idxSet is used to keep track of already added properties
    // and the new value to be stored in the index for accessing it.

    IndexRemapSet idxSet;

    UInt32 idxOffset  = 0;
    UInt32 propOffset = 0;

    for(UInt32 i = 0; i < lengths->size(); ++i)
    {
        UInt32 len = lengths->getValue(i);

        for(UInt32 j = 0; j < len; ++j, ++idxOffset)
        {
            UInt32 idx = propIdx0->getValue(idxOffset);

            IndexRemap                    ir(idx, propOffset);
            IndexRemapSet::const_iterator isIt = idxSet.find(ir);

            if(isIt == idxSet.end())
            {
                 // first use of this idx
                idxSet.insert(ir);

                // copy properties to new position
                copyProperties(prop, idx, newProp, propOffset);

                // write new position to index
                newPropIdx->setValue(propOffset, idxOffset);

                ++propOffset;
            }
            else
            {
                // idx occured previously, only record
                // new position in index
                newPropIdx->setValue((*isIt)._newIdx, idxOffset);
            }
        }
    }

    // set new properties and index on geometry

    for(UInt32 i = 0; i <= Geometry::LastIndex; ++i)
    {
        if(geo->getProperty(i) != NULL)
        {
            for(UInt32 j = 0; j < prop.size(); ++j)
            {
                if(geo->getProperty(i) == prop[j])
                {
                    geo->setProperty(newProp[j], i);
                    geo->setIndex   (newPropIdx, i);
                }
            }
        }
    }
}

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic pop
#endif

OSG_END_NAMESPACE
