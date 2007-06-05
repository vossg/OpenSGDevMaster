/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include <cstdlib>
#include <cstdio>

#include <set>

#include "OSGConfig.h"

#include "OSGGeoFunctions.h"
#include "OSGGeoProperties.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGStriperHalfEdgeGraph.h"

OSG_BEGIN_NAMESPACE

//Helper

//! \ingroup GrpSystemDrawablesGeometryFunctions
//! Multi/Single index dictionary. Only useful for normal calculation
//! {
struct  IndexDic
{
    typedef std::vector<Int32>  Int32Vec;

  public:
    
           Int32     entry     (Int32Vec &indexVec);
    
    const Int32Vec  &entry     (Int32     index   );

           UInt32    entryCount(void              ) const;

  private:

    typedef std::map<Int32Vec, Int32> IndexMap;

    IndexMap _indexMap;

    std::vector<const Int32Vec *> _indexVec;
};

inline 
Int32 IndexDic::entry(Int32Vec &indexVec)
{
    IndexMap::iterator iI = _indexMap.find(indexVec);

    if(iI == _indexMap.end())
    {
        std::pair < IndexMap::iterator, bool > mapRes =
            _indexMap.insert(IndexMap::value_type(indexVec, _indexVec.size()));

        if(mapRes.second)
        {
            iI = mapRes.first;

            _indexVec.push_back(&(iI->first));
        }
        else
        {
            FFATAL(("IndexDic::entry() map insert error\n"));
        }
    }

    return iI->second;
}

inline 
const IndexDic::Int32Vec &IndexDic::entry(Int32 index)
{
    return *(_indexVec[index]);
}

inline 
UInt32 IndexDic::entryCount(void) const
{
    return _indexVec.size();
}
//! }


//------------------------------------------------------------

/*! \ingroup GrpSystemDrawablesGeometryFunctions

Calculate vertex normals for the given geometry. 

It just averages all normals that use a given vertex (as indicated by its
index). It is smart enough to only change the normals that are used by this
Geometry, and tries to reuse indices if they're not shared on other
properties.

\warning This doesn't do anything for nonindexed geometries!

*/
void calcVertexNormals(GeometryPtrArg geo)
{
    typedef std::set<UInt32> IndexSet;

    GeoVectorPropertyPtr   norms;
    GeoIntegralPropertyPtr normsIndex;
    GeoIntegralPropertyPtr posIndex;

    IndexSet               used_indices;

    posIndex = geo->getIndex(Geometry::PositionsIndex);

    if(posIndex == NullFC)
    {
        FWARNING(("calcVertexNormals: Geometry is not indexed, ignored!\n"));
        return;
    }
    
    norms = geo->getNormals();

    if(norms == NullFC)
    {
        norms = GeoVec3fProperty::create();
    }

    norms->resize(geo->getPositions()->size());


    normsIndex = geo->getIndex(Geometry::NormalsIndex);

    // No indices reuse positions
    if(normsIndex == NullFC)
    {
        normsIndex = geo->getIndex(Geometry::PositionsIndex);
    }

    // Shared with something except posIndex, create new
    // Might have side effects on the other instances
    if(normsIndex != posIndex && geo->indexOccurrence(normsIndex) > 1)
    {
        normsIndex = GeoUInt32Property::create();
    }
    
    if(normsIndex != posIndex)
    {
        normsIndex->resize(posIndex->size());

        normsIndex->clear();

        for(UInt32 i = 0; i < posIndex->size(); ++i)
        {
            UInt32 val;

            posIndex->getValue(val, i);
            normsIndex->addValue(val);
        }
    }     

    // problem: not all of the points of the property might be used by this
    // geometry. If the property has more than 1 users, be careful.
    UInt32 idx;

    for(UInt32 i = 0; i < posIndex->size(); ++i)
    {
        posIndex->getValue(idx, i);
        
        norms->setValue(Vec3f(0, 0, 0), idx);
    }

    for(TriangleIterator t  = geo->beginTriangles(); 
                         t != geo->endTriangles  ();
                       ++t)
    {
        Pnt3f p0 = t.getPosition(0);
        Pnt3f p1 = t.getPosition(1);
        Pnt3f p2 = t.getPosition(2);
    
        Plane p(p0, p1, p2);

        Int32 i0 = t.getPositionIndex(0);
        Int32 i1 = t.getPositionIndex(1);
        Int32 i2 = t.getPositionIndex(2);

        Vec3f v;

        norms->getValue(v, i0);
        
        v += p.getNormal();
        norms->setValue(v , i0);


        norms->getValue(v, i1);
        v += p.getNormal();
        
        norms->setValue(v, i1);


        norms->getValue(v, i2);
        v += p.getNormal();
        
        norms->setValue(v, i2 );
    }

    for(UInt32 i = 0; i < posIndex->size(); ++i)
    {
        posIndex->getValue(idx, i);

        Vec3f   n;

        norms->getValue(n, idx);
        n.normalize();
        norms->setValue(n, idx);
    }

    geo->setNormals(norms);
    geo->setIndex(normsIndex, Geometry::NormalsIndex);
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

Calculate vertex normals for the given geometry. Only vertices whose
triangles have an angle less than \a creaseAngle radians to each other are
merged.

\warning This doesn't do anything for nonindexed geometries!

*/
void calcVertexNormals(GeometryPtrArg geo,
                       Real32         creaseAngle)
{
    GeoVectorPropertyPtr   norms;
    GeoVectorPropertyPtr   positions;
    GeoIntegralPropertyPtr normsIndex;
    GeoIntegralPropertyPtr posIndex;

    if(creaseAngle >= Pi)
    {
        calcVertexNormals(geo);
        return;
    }

    // Get the positions property
    if(geo->getProperty(Geometry::PositionsIndex) == NullFC)
    {
        FINFO(("Geo without positions in calcVertexNormals()\n"));
        return;
    }
    else
    {
        positions = geo->getProperty(Geometry::PositionsIndex);
    }

    if(positions->size() < 3)
    {
        FINFO(("Geo with less than 3 positions in calcVertexNormals()\n"));
        return;
    }

    posIndex = geo->getIndex(Geometry::PositionsIndex);

    if(posIndex == NullFC)
    {
        FINFO(("Geo without position index in calcVertexNormals()\n"));
        return;
    }

    norms = geo->getProperty(Geometry::NormalsIndex);

    // Get normal property, create if needed
    if(norms == NullFC)
    {
        norms = GeoVec3fProperty::create();
        
        geo->setProperty(norms, Geometry::NormalsIndex);
    }

    normsIndex = geo->getIndex(Geometry::NormalsIndex);

    // No indices reuse positions
    if(normsIndex == NullFC || geo->indexOccurrence(normsIndex) > 1)
    {
        normsIndex = GeoUInt32Property::create();

        geo->setIndex(normsIndex, Geometry::NormalsIndex);
    }

    UInt32 nind = posIndex->size();
    
    normsIndex->resize(nind);
    
    
    // now calc the normals
    // if creaseAngle is 0, it's simple: every face uses its own.
    if(creaseAngle == 0)
    {
        norms->resize(nind);

        for(UInt32 i = 0; i < nind; ++i)
            normsIndex->setValue(i, i);

        for(TriangleIterator ti = geo->beginTriangles();
                             ti != geo->endTriangles(); 
                           ++ti)
        {
            Vec3f   d1 = ti.getPosition(1) - ti.getPosition(0);
            Vec3f   d2 = ti.getPosition(2) - ti.getPosition(0);

            d1.crossThis(d2);
            d1.normalize();

            norms->setValue(d1, ti.getNormalIndex(0));
            norms->setValue(d1, ti.getNormalIndex(1));
            norms->setValue(d1, ti.getNormalIndex(2));
        }

        return;
    }


    // opt + normal share code (written by jbehr)
    // collect a map from points to faces using this point
    // collect the face normals in a separate vector
    //FLOG (("Run calcVertexNormals(%g)\n", creaseAngle));

    std::vector < Vec3f > faceNormals;
    std::vector < std::vector < UInt32 > > pntFaceDic;

    TriangleIterator ti;
    UInt32 i, pN = positions->size();

    pntFaceDic.resize(pN);

    for(  ti  = geo->beginTriangles(), i = 0; 
          ti != geo->endTriangles(); 
        ++ti, ++i)
    {
        Int32 v0 = ti.getPositionIndex(0);
        Int32 v1 = ti.getPositionIndex(1);
        Int32 v2 = ti.getPositionIndex(2);

        if(v0 != v1 && v0 != v2)
        {
            Vec3f d1 = ti.getPosition(1) - ti.getPosition(0);
            Vec3f d2 = ti.getPosition(2) - ti.getPosition(0);

            d1.crossThis(d2);

            if(d1.squareLength() >= 0)
            {
                d1.normalize();

                faceNormals.push_back(d1);

                pntFaceDic[ti.getPositionIndex(0)].push_back(i);
                pntFaceDic[ti.getPositionIndex(1)].push_back(i);
                pntFaceDic[ti.getPositionIndex(2)].push_back(i);
            }
            else
            {
                faceNormals.push_back(Vec3f(0, 0, 0));
            }
        }
        else
        {
            faceNormals.push_back(Vec3f(0, 0, 0));
        }
    }

    norms->clear();

    Real32 cosCrease = osgCos(creaseAngle);
    Vec3f norm;

    std::vector < UInt32 > normset;
    std::vector < std::map < std::vector < UInt32 > , UInt32 > > normDic;
    std::map < std::vector < UInt32 > , UInt32 >::iterator ndI;

    UInt32 normalIndex = 0;

    normDic.resize(pN);

    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti)
    {
        Int32 tind = ti.getIndex();
        Vec3f faceNorm(faceNormals[tind]);

        if(faceNorm.squareLength() != 0.0)
        {
            for(UInt16 i = 0; i < 3; ++i)
            {
                // calculate the normal: average all different normals
                // that use a point. Simple addition or weighted addition
                // doesn't work, as it depends on the triangulation
                // of the object. :(

                UInt32 p = ti.getPositionIndex(i);
                UInt32 pf, f, fN = pntFaceDic[p].size();
                UInt32 n, nN;

                normset.clear();

                for(f = 0; f < fN; f++)
                {
                    if(((pf = pntFaceDic[p][f]) == tind) ||
                       (faceNorm.dot(faceNormals[pf]) > cosCrease))
                    {
                        normset.push_back(pf);
                    }
                }

                if((nN = normset.size()))
                {
                    // find normal
                    //std::sort ( normset.begin(), normset.end() );
                    ndI = normDic[p].find(normset);

                    if(ndI == normDic[p].end())
                    {
                        norm = faceNormals[normset[0]];

                        for(n = 1; n < nN; ++n)
                            norm += faceNormals[normset[n]];

                        norm.normalize();
                        normalIndex = norms->size();
                        norms->push_back(norm);
                        normDic[p][normset] = normalIndex;
                    }
                    else
                    {
                        normalIndex = ndI->second;
                    }
                }
                else
                {
                    // keep normalIndex
                    FWARNING(("Empty normset for %d faces pos %d: %f/%f/%f\n",
                               fN, i, ti.getPosition(i).x(),
                               ti.getPosition(i).y(), ti.getPosition(i).z()
                            ));
                }

                normsIndex->setValue(normalIndex, ti.getIndex(i));
            }
        }
        else
        {
            // keep normal for degenerated triangle

            normalIndex = norms->size();
            norms->push_back(norm);
            
            normsIndex->setValue(normalIndex, ti.getIndex(0));
            normsIndex->setValue(normalIndex, ti.getIndex(1));
            normsIndex->setValue(normalIndex, ti.getIndex(2));
        }
    }
}

void calcFaceNormals(GeometryPtrArg geo)
{
    FFATAL(("calcFaceNormals:: NYI!\n"));
}


void calcVertexTangentsProp(GeometryPtrArg geo,
                            UInt32         srcTexProp,
                            UInt32         srcNormalProp,
                            UInt32         dstPropTan,
                            UInt32         dstPropBin)
{
    GeoVec4fPropertyPtr  tangentP;
    GeoVec4fPropertyPtr  binormalP;
    GeoUInt32PropertyPtr tanBinIndexP;

    std::vector<Vec3f> tangent, binormal, normal;

    // can't eval what combination was meant
    if( (srcTexProp    >  Geometry::LastIndex) || 
        (srcNormalProp >  Geometry::LastIndex) || 
        (dstPropTan    >  Geometry::LastIndex) ||
        (dstPropBin    >  Geometry::LastIndex) ||
        (dstPropTan    == dstPropBin         ) ||

        (dstPropTan    == srcTexProp         ) ||
        (dstPropTan    == srcNormalProp      ) ||

        (dstPropBin    == srcTexProp         ) ||
        (dstPropBin    == srcNormalProp      ) ||

        (srcTexProp    == srcNormalProp      )  ) 
    {
        FFATAL(("Index set %d %d %d %d not supported in "
                "calcVertexTangents()\n",
                srcTexProp,
                srcNormalProp,
                dstPropTan,
                dstPropBin));
        return;
    }

    GeoIntegralPropertyPtr posIdx = geo->getIndex(Geometry::PositionsIndex);
        
    // HACK but without indices it crashes
    if(posIdx == NullFC || posIdx->size() == 0) 
    {
        FFATAL(("Geo without pos indices in calcVertexTangents()\n"));
        return;
    }
    
    GeoVectorPropertyPtr positions = geo->getPositions();
    
    // Get the positions property
    if(positions == NullFC) 
    {
        FFATAL(("Geo without positions in calcVertexTangents()\n"));
        return;
    }

    GeoVectorPropertyPtr srcTexCoords = geo->getProperty(srcTexProp);
    
    // Get the positions property
    if(srcTexCoords == NullFC) 
    {
        FFATAL(("Geo without srcTexCoords in calcVertexTangents()\n"));
        return;
    }

    GeoVectorPropertyPtr srcNormals = geo->getProperty(srcNormalProp);
    
    // Get the positions property
    if(srcNormals == NullFC) 
    {
        FFATAL(("Geo without srcNormals in calcVertexTangents()\n"));
        return;
    }


    UInt32 nind = posIdx->size();
    
    tangentP  = GeoVec4fProperty::create();
    binormalP = GeoVec4fProperty::create();
    
    tanBinIndexP = GeoUInt32Property::create();

    tanBinIndexP->resize(nind);

    geo->setProperty(tangentP,     dstPropTan);
    geo->setIndex   (tanBinIndexP, dstPropTan);

    geo->setProperty(binormalP,    dstPropBin);
    geo->setIndex   (tanBinIndexP, dstPropBin);

    TriangleIterator tI;
    IndexDic indexDic;
    Int32 i, k, index, v[3];
    Vec4f vect(0, 0, 0, 0);
    
    std::vector<Int32>indexVec;

    indexVec.resize(3);    
    
  
    // init property arrays
    for(i = 0; i < nind; i++) 
    {
        tangent .push_back(Vec3f::Null);
        binormal.push_back(Vec3f::Null);
        normal  .push_back(Vec3f::Null);    
    }
    
    for(  tI  = geo->beginTriangles(), i = 0; 
          tI != geo->endTriangles(); 
        ++tI, ++i) 
    {       
        for(k = 0; k < 3; k++) 
        {
            indexVec[0] = tI.getPropertyIndex(Geometry::PositionsIndex, k);
            indexVec[1] = tI.getPropertyIndex(srcNormalProp,            k);
            indexVec[2] = tI.getPropertyIndex(srcTexProp,               k);

            v[k] = indexDic.entry(indexVec);
        }

        // second, calculate tangent and binormal for every tri
        Int32 v0 = tI.getPositionIndex(0),
              v1 = tI.getPositionIndex(1),
              v2 = tI.getPositionIndex(2);

        Vec2f t0, t1, t2, tex1, tex2;
        Vec3f edge1, edge2, sdir, tdir;
        
        t0 = tI.getTexCoords(srcTexProp, 0);
        t1 = tI.getTexCoords(srcTexProp, 1);
        t2 = tI.getTexCoords(srcTexProp, 2);
        
        edge1 = tI.getPosition(1) - tI.getPosition(0),
        edge2 = tI.getPosition(2) - tI.getPosition(0);

        tex1 = t1 - t0;
        tex2 = t2 - t0;
        
        Real32 invDet = 1.0 / (tex1[0]*tex2[1] - tex2[0]*tex1[1]);
        sdir = invDet * (tex2[1]*edge1 - tex1[1]*edge2);    // tangent
        tdir = invDet * (tex1[0]*edge2 - tex2[0]*edge1);    // binormal
        
        for(k = 0; k < 3; k++) 
        {
            tangent [v[k]] += sdir;
            binormal[v[k]] += tdir;
            normal  [v[k]]  = tI.getNormal(srcNormalProp, k);

            tanBinIndexP->setValue(v[k], tI.getIndex(k)); 
        }
    }
    
    // orthogonalize vectors (Gram-Schmidt) and calc handedness    
    Vec3f T, B, N;

    Real32 sign = 0, l1, l2;

    tangentP ->clear();
    binormalP->clear();

    for(i = 0; i < nind; i++) 
    {
        T = tangent [i];
        B = binormal[i];
        N = normal  [i];    // must be normalized: n*n = 1

        sign = ((N.cross(T)).dot(B) < 0) ? -1 : 1;
        
        T = T - N.dot(T) * N;

        T.normalize();

        B = B - N.dot(B) * N - T.dot(B) * T;

        B.normalize(); 
        
        vect.setValues(T[0], T[1], T[2], sign);

        tangentP->editField().push_back(vect); 
        
        vect.setValues(B[0], B[1], B[2], sign);

        binormalP->editField().push_back(vect); 
    }
}

void calcVertexTangents(GeometryPtrArg geo,
                        UInt32         srcTexIndex,
                        UInt32         dstPropTan,
                        UInt32         dstPropBin)
{
    calcVertexTangentsProp(geo,
                           srcTexIndex + Geometry::TexCoordsIndex,
                           Geometry::NormalsIndex,
                           dstPropTan,
                           dstPropBin);
}

void calcVertexTexCoordsProp2D(GeometryPtr geo,
                               UInt32      propIndex)
{
    struct Key 
    {
        Real32 value;
        Int32 pos;
    } key[3], rem;

    Int32 S = -1, T = -1, n = 3, i, j; 
    Real32 sDenom, tDenom, sMin, tMin;
    
    GeoIntegralPropertyPtr ip   = geo->getIndices  ();
    GeoVectorPropertyPtr   posP = geo->getPositions();
    GeoVectorPropertyPtr   texP;

    if(posP == NullFC || !posP->size() || ip == NullFC || !ip->size())
    {
        FFATAL(("Geo without indices/ positions in calcVertexTexCoords()\n"));
        return;
    }

    if(propIndex > Geometry::LastIndex)
    {
        FFATAL(("invalid propIndex %d in calcVertexTexCoords()\n",
               propIndex));
        return;
    }
    
    MFParentFieldContainerPtr::const_iterator pnI;

    for(  pnI  = geo->getMFParents()->begin();
          pnI != geo->getMFParents()->end  ();
        ++pnI)
    {
        NodePtr node = cast_dynamic<NodePtr>(*pnI);

        if(node != NullFC)
        {
            DynamicVolume &dVol = node->editVolume(true);

            Pnt3f min, max;

            dVol.getBounds(min, max);
    
            Vec3f dia(max - min);

            for(i = 0; i < 3; i++)
            {
                key[i].value = dia[i];
                key[i].pos   = i;
            }
    
            for(i = 1; i < n; i++)
            {
                for(j = n-1; j >= i; j--)
                {
                    if (key[j-1].value > key[j].value)
                    {
                        rem      = key[j];
                        key[j]   = key[j-1];
                        key[j-1] = rem;
                    }
                }
            }
    
            S = key[2].pos;
            T = key[1].pos;

            sDenom = dia[S];
            tDenom = dia[T];

            sMin = min[S];
            tMin = min[T];
    
            break;
        }
    }

    if(S < 0 || T < 0)
    {
        FFATAL(("Geo without parents in calcVertexTexCoords()\n"));
        return;
    }

    texP = GeoPnt2fProperty::create();

    geo->setProperty(texP, propIndex);
    geo->setIndex   (ip,   propIndex);

    Pnt3f point;
    Vec2f texCoord;

    Int32 len = posP->size();

    texP->resize(len);

    for(i = 0; i < len; i++)
    {
        posP->getValue(point, i);
        
        texCoord[0] = (point[S] - sMin) / sDenom;
        texCoord[1] = (point[T] - tMin) / tDenom;
        
        texP->setValue(texCoord, i);
    }
}

void calcVertexTexCoords(GeometryPtr geo,
                         UInt32      texIndex)
{
    calcVertexTexCoordsProp2D(geo, texIndex + Geometry::TexCoordsIndex);
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    setIndexFromVRMLData creates an OSG::Geometry's interleaved index data
    from VRML-style separate indices, see \ref PageSystemGeoFunctionsMakeGeo
    for a description.

    \a coordIndex, \a normalIndex, \a colorIndex and \a texCoordIndex are
    VRML97-style indices. \a ccw sets whether poylgons are defined
    counter-clockwise or clockwise, \a normalPerVertex and \a colorPerVertex
    specify bindings, and \a faceSet defines whether a VRML IndexedFaceSet or
    an IndexedLineSet is being generated. See the VRML97 specification at
    http://www.vrml.org/XXX for details.

    Note: the \a convex and \a createNormals parameters are ignored right now!
*/

Int32 setIndexFromVRMLData(     GeometryPtrArg  geoPtr,
                           std::vector<Int32>  &coordIndex,
                           std::vector<Int32>  &normalIndex,
                           std::vector<Int32>  &colorIndex,
                           std::vector<Int32>  &texCoordIndex,
                                bool            convex, 
                                bool            ccw,
                                bool            normalPerVertex, 
                                bool            colorPerVertex,
                                bool            createNormal, 
                                bool            faceSet        )
{
    /** define the bag type */
    typedef std::vector<Int32>  *IndexBagP;

    /** defines the Index Types */
    enum IndexType
    {
        UNKNOWN_IT          = 0,
        EMPTY_IT,
        VERTEX_COORD_IT,
        VERTEX_IT,
        VERTEX_DUP_IT,
        VERTEX_CREATE_IT,
        PRIMITIVE_IT,
        PRIMITIVE_INDEX_IT,
        PRIMITIVE_CREATE_IT
    };

    /** holds the Index types as str, mainly for log/debug outputs */
#ifdef OSG_DEBUG
    static const char *indexTypeStr[] =
    {
        "UNKNOWN_IT",
        "EMPTY_IT",
        "VERTEX_COORD_IT",
        "VERTEX_IT",
        "VERTEX_DUP_IT",
        "VERTEX_CREATE_IT",
        "PRIMTIVE_IT",
        "PRIMITIVE_INDEX_IT",
        "PRIMITIVE_CREATE_IT"
    };
#endif

    GeoVectorPropertyPtr   posPtr;
    GeoVectorPropertyPtr   normalPtr;
    GeoVectorPropertyPtr   colorPtr;
    GeoVectorPropertyPtr   texCoordsPtr;
    GeoIntegralPropertyPtr lensPtr;
    GeoIntegralPropertyPtr geoTypePtr;

    GeoIntegralPropertyPtr posIndexPtr  = NullFC;

    Int32 index, i, pi, typei, mapi, primitiveN = 0, vN = 0;
    Int32 pType = 0, localPType;
    Int32 maxPType = (faceSet ? 5 : 3);
    Int32 minPType = (faceSet ? 3 : 2);
    Int32 beginIndex, endIndex, step, len, sysPType = 0;
    Int32 piN = 0, ciN = 0, niN = 0, tiN = 0;
    Int32 pN = 0, nN = 0, cN = 0, tN = 0, tN1 = 0, tN2 = 0, tN3 = 0;
    IndexType indexType[4];
    IndexType &coordIT = indexType[0];
    IndexType &normalIT = indexType[1];
    IndexType &colorIT = indexType[2];
    IndexType &textureIT = indexType[3];
    Int32 primitiveTypeCount[6];
    UInt32 triCount = 0;
//    Int16 indexMap[4], indexMapID[4];
    UInt32 uiNumTextures = 0;

    IndexBagP indexBag[4] =
    {
        &coordIndex,
        &normalIndex,
        &colorIndex,
        &texCoordIndex
    };

    GeoIntegralPropertyPtr indexOutBag[4] =
    {
        NullFC,
        NullFC,
        NullFC,
        NullFC
    };

    UInt16 indexOutBagID[4] =
    {
        Geometry::PositionsIndex,
        Geometry::NormalsIndex,
        Geometry::ColorsIndex,
        Geometry::TexCoordsIndex
    };

    //----------------------------------------------------------------------
    // init
    coordIT = VERTEX_IT;
//    indexMap[0] = Geometry::MapPosition;

    //----------------------------------------------------------------------
    // get the property pointer and element count
    posPtr = geoPtr->getPositions();
    pN = ((posPtr == NullFC) ? 0 : posPtr->getSize());

    normalPtr = geoPtr->getNormals();
    nN = ((normalPtr == NullFC) ? 0 : normalPtr->getSize());

    colorPtr = geoPtr->getColors();
    cN = ((colorPtr == NullFC) ? 0 : colorPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords();
    tN = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords1();
    tN1 = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords2();
    tN2 = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords3();
    tN3 = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    FDEBUG(("vertex attrib count P/N/C/T: %d/%d/%d/%d\n", pN, nN, cN, tN));

    //----------------------------------------------------------------------
    // check the vertex index and count the primitives
    primitiveN = index = 0;

    for(pType = 0; pType < 6; pType++)
        primitiveTypeCount[pType] = 0;

    if(!pN)
    {
        FWARNING(("No points in OSG::setIndexFromVRMLData()\n"));
        return 0;
    }
    else
    {
        piN = coordIndex.size();

        if(piN)
        {
            for(i = 0; i <= piN; i++)
            {
                index = (i == piN) ? -1 : coordIndex[i];

                if((index < 0) && vN)
                {
                    primitiveTypeCount[(vN > maxPType) ? maxPType : vN]++;
                    primitiveN++;
                    vN = 0;
                }
                else
                {
                    if(index >= pN && i != piN)
                    {
                        FWARNING(("Point index (%d/%d) out of range\n", 
                                  index, pN));

                        coordIndex[i] = 0;
                    }

                    vN++;
                }
            }
        }
        else
        {
            FWARNING(("No coordIndex in OSG::setIndexFromVRMLData()\n"));
            return 0;
        }
    }

    //----------------------------------------------------------------------
    // check the normal index

    normalIT = UNKNOWN_IT;

    niN = normalIndex.size();

    if(nN)
    {               // have normal elements
        if(normalPerVertex)
        {
            // normal per vertex
            if(niN >= piN)
            {
                // valid normal index number
                for(i = 0; i < piN; i++)
                {   // check if normal index equals the coord index
                    if(normalIndex[i] != coordIndex[i])
                    {
                        normalIT = VERTEX_IT;
                        break;
                    }
                }

                if(normalIT == UNKNOWN_IT)
                {
                    // if equal than delete unneeded normal index
                    normalIT = VERTEX_DUP_IT;
                }
            }
            else
            {
                // no or not enough normal index
                normalIT = VERTEX_COORD_IT;
                if(niN)
                {
                    FWARNING(("Not enough normal index (%d,%d)\n", normalIndex.
                                                     size(), piN));
                    normalIndex.clear();
                }
            }
        }
        else
        {
            // normal per primitive
            if(niN >= primitiveN)
            {
                // use one normal index per primitive
                normalIT = PRIMITIVE_INDEX_IT;
            }
            else
            {
                if(nN >= primitiveN)
                {
                    // use one normal per primitive
                    normalIT = PRIMITIVE_IT;
                }
                else
                {
                    FINFO(("not enough normal index (%d,%d)\n", 
                           nN, primitiveN));
                }
            }
        }
    }
    else
    {
        /* not yet !!!
if (createNormal)
  if (normalPerVertex)
    normalIT = VERTEX_CREATE_IT;
  else
    normalIT = PRIMITIVE_CREATE_IT;
else
*/
        normalIT = EMPTY_IT;
    }

    //----------------------------------------------------------------------
    // check the color index

    colorIT = UNKNOWN_IT;

    ciN = colorIndex.size();

    if(cN)
    {               // have color elements
        if(colorPerVertex)
        {
            // color per vertex
            if(ciN >= piN)
            {
                // valid color index number
                for(i = 0; i < piN; i++)
                {   // check if color index equals the coord index
                    if(colorIndex[i] != coordIndex[i])
                    {
                        colorIT = VERTEX_IT;
                        break;
                    }
                }

                if(colorIT == UNKNOWN_IT)
                {
                    // if equal than delete unneeded color index
                    colorIT = VERTEX_DUP_IT;
                }
            }
            else
            {
                // no or not enough color index
                colorIT = VERTEX_COORD_IT;
                if(ciN)
                {
                    FWARNING(("Not enough color index (%d,%d)\n", colorIndex.
                                                     size(), piN));
                    colorIndex.clear();
                }
            }
        }
        else
        {
            // color per primitive
            if(ciN >= primitiveN)
            {
                // use one color index per primitive
                colorIT = PRIMITIVE_INDEX_IT;
            }
            else
            {
                if(cN >= primitiveN)
                {
                    // use one color per primitive
                    colorIT = PRIMITIVE_IT;
                }
                else
                {
                    FINFO(("not enough color index (%d,%d)\n", 
                           cN, primitiveN));
                }
            }
        }
    }
    else
    {
        colorIT = EMPTY_IT;
    }

    //----------------------------------------------------------------------
    // check the texture index

    textureIT = UNKNOWN_IT;
    tiN = texCoordIndex.size();
    if(tN)
    {               // have texture elemnts
        if(tiN >= piN)
        {
            // valid texture index number
            for(i = 0; i < piN; i++)
            {       // check if texture index equals the coord index
                if(texCoordIndex[i] != coordIndex[i])
                {
                    textureIT = VERTEX_IT;
                    break;
                }
            }

            if(textureIT == UNKNOWN_IT)
            {
                // if equal than delete unneeded texture index
                textureIT = VERTEX_DUP_IT;
            }
        }
        else
        {
            // no or not enough texture index
            textureIT = VERTEX_COORD_IT;
            if(ciN)
            {
                FWARNING(("Not enough texCoord index (%d,%d)\n", texCoordIndex.
                                             size(), piN));
                texCoordIndex.clear();
            }
        }
    }
    else
    {
        textureIT = EMPTY_IT;
    }

    if(faceSet)
    {
        FDEBUG(("primitiveN:  %d, 0/%d 1/%d 2/%d 3/%d 4/%d poly/%d\n",
                           primitiveN, primitiveTypeCount[0],
                           primitiveTypeCount[1], primitiveTypeCount[2],
                           primitiveTypeCount[3], primitiveTypeCount[4],
                           primitiveTypeCount[5]));
    }
    else
    {
        FDEBUG(("primitiveN:  %d, 0/%d 1/%d 2/%d 3/%d\n", primitiveN,
                           primitiveTypeCount[0], primitiveTypeCount[1],
                           primitiveTypeCount[2], primitiveTypeCount[3]));
    }

    FDEBUG(("IndexType: coord: %s, color: %s, normal: %s, texture: %s \n",
                   indexTypeStr[coordIT], indexTypeStr[colorIT], indexTypeStr[
                   normalIT], indexTypeStr[textureIT]));

    //----------------------------------------------------------------------
    // check/create the indexPtr/lengthsPtr/geoTypePtr
    posIndexPtr = geoPtr->getIndex(Geometry::PositionsIndex);

    if(posIndexPtr == NullFC)
    {
        posIndexPtr = GeoUInt32Property::create();
    }
    else
    {
        posIndexPtr->clear();
    }

    for(i = 1; i < 4; ++i)
    { 
        indexOutBag[i] = geoPtr->getIndex(indexOutBagID[i]);
        
        if(indexOutBag[i] != NullFC)
        {
            indexOutBag[i]->clear();
        }
    }

    lensPtr = geoPtr->getLengths();

    if(lensPtr == NullFC)
    {
        lensPtr = GeoUInt32Property::create();
    }
    else
    {
        lensPtr->clear();
    }

    geoTypePtr = geoPtr->getTypes();

    if(geoTypePtr == NullFC)
    {
        geoTypePtr = GeoUInt8Property::create();
    }
    else
    {
        geoTypePtr->clear();
    }

    //----------------------------------------------------------------------
    // set lens/geoType/index/mapping the index mapping
    
    geoPtr->setLengths(lensPtr   );
    geoPtr->setTypes  (geoTypePtr);

    geoPtr->setIndex(posIndexPtr, Geometry::PositionsIndex);

    //----------------------------------------------------------------------
    // create index face/line data

    for(pType = minPType; pType <= maxPType; pType++)
    {
        // check for the pType count
        if(primitiveTypeCount[pType])
        {
            // calc len/sysPType
            if(faceSet)
            {
                if(pType < 5)
                {
                    len = primitiveTypeCount[pType] * pType;

                    sysPType = (pType == 3) ? GL_TRIANGLES : GL_QUADS;
                }
                else
                {
                    sysPType = 0;
                }
            }
            else
            { 
                if(pType == 2)
                {
                    len = primitiveTypeCount[pType] * pType;
                    sysPType = GL_LINES;
                }
                else
                {
                    sysPType = 0;
                }
            }

            // set len/sysPType
            if(sysPType)
            {
                lensPtr->push_back(len);

                geoTypePtr->push_back(sysPType);
            }

            primitiveN = 0;
            beginIndex = endIndex = -1;

            for(i = 0; i <= piN; i++)
            {
                if(((i == piN) && (coordIndex[i - 1] >= 0)) ||
                   ((i < piN) && (coordIndex[i] < 0)))
                {
                    len = i - beginIndex;

                    if(ccw)
                    {
                        endIndex = i;
                        step = 1;
                    }
                    else
                    {
                        endIndex = beginIndex - 1;

                        beginIndex = i - 1;

                        step = -1;
                    }

                    localPType = (len > maxPType) ? maxPType : len;

                    if((beginIndex >= 0) && (localPType == pType))
                    {
                        if(len >= maxPType)
                        {
                            sysPType = faceSet ? GL_POLYGON : GL_LINE_STRIP;

                            lensPtr->push_back(len);

                            geoTypePtr->push_back(sysPType);
                        }

                        // add index data
                        for(pi = beginIndex; pi != endIndex; pi += step)
                        {
                            posIndexPtr->push_back(coordIndex[pi]);
 
                                for(typei = 1; typei <= 3; typei++)
                                {
                                        index = -1;

                                        switch(indexType[typei])
                                        {
                                            case UNKNOWN_IT:
                                            case EMPTY_IT:
                                            case VERTEX_COORD_IT:
                                                break;

                                            case VERTEX_IT:
                                            {
                                                index = (*indexBag[typei])[pi];
                                            }
                                                break;
                                            case PRIMITIVE_IT:
                                            {
                                                index = primitiveN;
                                            }
                                                break;
                                            case PRIMITIVE_INDEX_IT:
                                            {
                                                index = (*indexBag[typei])[
                                                    primitiveN];
                                            }
                                            break;

                                            default:    //X_CREATE_IT
                                            break;
                                        }

                                        if(index != -1)
                                        {
                                            if(indexOutBag[typei] == NullFC)
                                            {
                                                indexOutBag[typei] = GeoUInt32Property::create();
                                            }
                                            
                                            indexOutBag[typei]->push_back(index);
                                        }

                                    }
                                    
                        }

                        triCount += len - 2;
                    }

                    primitiveN++;
                    beginIndex = endIndex = -1;
                }
                else if(beginIndex < 0)
                {
                    beginIndex = i;
                }
            }
        }
    }


    for(UInt32 i = 1; i < 4; ++i)
    {
        if((indexType  [i] == VERTEX_COORD_IT || indexType  [i]         == VERTEX_DUP_IT) &&
           (indexOutBag[i] == NullFC          || indexOutBag[i]->size() == 0            )   )
        {
            geoPtr->setIndex(posIndexPtr, indexOutBagID[i]);
        }
        else if(indexOutBag[i] != NullFC && indexOutBag[i]->size() != 0)
        {
            geoPtr->setIndex(indexOutBag[i], indexOutBagID[i]);
        }
    }

    return triCount;
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

    setIndexFromIndexedX3DData creates an OSG::Geometry's interleaved index data
    from X3D-style separate indices, see \ref PageSystemGeoFunctionsMakeGeo
    for a description.
    
    The \a primitiveType defines the GL-Primtive (e.g. GL_LINE, GL_TRIANGLE_STRIP,
    GL_POLYGON) which should be used.

    \a coordIndex, \a normalIndex, \a colorIndex and \a texCoordIndex are
    X3D-style indices. \a ccw sets whether poylgons are defined
    counter-clockwise or clockwise, \a normalPerVertex and \a colorPerVertex
    specify bindings. See the X3D specification at
    http://www.web3d.org for details.

    Note: the \a convex and \a createNormals parameters are ignored right now!
*/

Int32 setIndexFromIndexedX3DData ( GeometryPtr geoPtr,
                                   std::vector<Int32> &coordIndex,
                                   std::vector<Int32> &normalIndex,
                                   std::vector<Int32> &colorIndex,
                                   std::vector<Int32> &texCoordIndex,
                                   Int32 primitiveType, 
                                   bool convex, 
                                   bool ccw,
                                   bool normalPerVertex, 
                                   bool colorPerVertex,
                                   bool createNormal )
{
    /** define the bag type */
    typedef std::vector<Int32>  *IndexBagP;

    /** defines the Index Types */
    enum IndexType
    {
        UNKNOWN_IT          = 0,
        EMPTY_IT,
        VERTEX_COORD_IT,
        VERTEX_IT,
        VERTEX_DUP_IT,
        VERTEX_CREATE_IT,
        PRIMITIVE_IT,
        PRIMITIVE_INDEX_IT,
        PRIMITIVE_CREATE_IT
    };

    /** holds the Index types as str, mainly for log/debug outputs */
    static const char *indexTypeStr[] =
    {
        "UNKNOWN_IT",
        "EMPTY_IT",
        "VERTEX_COORD_IT",
        "VERTEX_IT",
        "VERTEX_DUP_IT",
        "VERTEX_CREATE_IT",
        "PRIMTIVE_IT",
        "PRIMITIVE_INDEX_IT",
        "PRIMITIVE_CREATE_IT"
    };

    GeoVectorPropertyPtr   posPtr;
    GeoVectorPropertyPtr   normalPtr;
    GeoVectorPropertyPtr   colorPtr;
    GeoVectorPropertyPtr   texCoordsPtr;

    GeoIntegralPropertyPtr lensPtr;
    GeoIntegralPropertyPtr geoTypePtr;
    GeoIntegralPropertyPtr posIndexPtr  = NullFC;

    //bool faceSet = (primitiveType == GL_POLYGON);
    Int32 index, i, pi, typei, mapi, primitiveN = 0, vN = 0;
    Int32 pType = 0, localPType;
    Int32 maxPType; //  = (faceSet ? 5 : 3);
    Int32 minPType; //  = (faceSet ? 3 : 2);
    Int32 beginIndex, endIndex, step, len, sysPType = 0;
    Int32 piN = 0, ciN = 0, niN = 0, tiN = 0;
    Int32 pN = 0, nN = 0, cN = 0, tN = 0;
    IndexType indexType[4];
    IndexType &coordIT = indexType[0];
    IndexType &normalIT = indexType[1];
    IndexType &colorIT = indexType[2];
    IndexType &textureIT = indexType[3];
    Int32 primitiveTypeCount[6];
    UInt32 triCount = 0;
    Int16 indexMap[4], indexMapID[4];
    UInt32 uiNumTextures = 0;

    IndexBagP indexBag[4] =
    {
        &coordIndex,
        &normalIndex,
        &colorIndex,
        &texCoordIndex
    };

    GeoIntegralPropertyPtr indexOutBag[4] =
    {
        NullFC,
        NullFC,
        NullFC,
        NullFC
    };

    UInt16 indexOutBagID[4] =
    {
        Geometry::PositionsIndex,
        Geometry::NormalsIndex,
        Geometry::ColorsIndex,
        Geometry::TexCoordsIndex
    };

    UInt32 texCoordN[4] =
    {
        0,
        0,
        0,
        0,
    };

    UInt16 texCoordIdx[4] =
    {
        Geometry::TexCoordsIndex,
        Geometry::TexCoords1Index,
        Geometry::TexCoords2Index,
        Geometry::TexCoords3Index
    };

    //----------------------------------------------------------------------
    // init
    coordIT = VERTEX_IT;

    //----------------------------------------------------------------------
    // set maxPType and minPTypr from primitiveType
    switch (primitiveType) 
    {
        case GL_POINTS:
            minPType = 1;
            maxPType = 1;
            break;
        case GL_LINES:
            minPType = 2;
            maxPType = 3;
            break;
        case GL_LINE_STRIP:
            minPType = 2;
            maxPType = 3;
            break;
        case GL_LINE_LOOP:
            minPType = 2;
            maxPType = 3;
            break;
        case GL_TRIANGLES:
            minPType = 3;
            maxPType = 3;
            break;
        case GL_TRIANGLE_STRIP:
            minPType = 3;
            maxPType = 3;
            break;
        case GL_TRIANGLE_FAN:
            minPType = 3;
            maxPType = 3;
            break;
        case GL_QUADS:
            minPType = 3;
            maxPType = 4;
            break;
        case GL_QUAD_STRIP:    
            minPType = 3;
            maxPType = 4;
            break;
        case GL_POLYGON:
            minPType = 3;
            maxPType = 5;
            break;
        default:
            FFATAL (( "Can not fill index; Invalid primitiveType: %d\n",
                      primitiveType ));
            break;
    }
      
    //----------------------------------------------------------------------
    // get the property pointer and element count
    posPtr = geoPtr->getPositions();
    pN = ((posPtr == NullFC) ? 0 : posPtr->getSize());

    normalPtr = geoPtr->getNormals();
    nN = ((normalPtr == NullFC) ? 0 : normalPtr->getSize());

    colorPtr = geoPtr->getColors();
    cN = ((colorPtr == NullFC) ? 0 : colorPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords();
    tN = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());
    texCoordN[0] = tN;

    texCoordsPtr = geoPtr->getTexCoords1();
    texCoordN[1] = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords2();
    texCoordN[2] = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords3();
    texCoordN[3] = ((texCoordsPtr == NullFC) ? 0 : texCoordsPtr->getSize());

    FDEBUG(("vertex attrib count P/N/C/T: %d/%d/%d/%d\n", pN, nN, cN, tN));

    //----------------------------------------------------------------------
    // check the vertex index and count the primitives
    primitiveN = index = 0;

    for(pType = 0; pType < 6; pType++)
        primitiveTypeCount[pType] = 0;

    if(!pN)
    {
        FINFO(("No points in OSG::setIndexFromVRMLData()\n"));
        return 0;
    }
    else
    {
        piN = coordIndex.size();

        if(piN)
        {
            for(i = 0; i <= piN; i++)
            {
                index = (i == piN) ? -1 : coordIndex[i];

                if((index < 0) && vN)
                {
                    primitiveTypeCount[(vN > maxPType) ? maxPType : vN]++;
                    primitiveN++;
                    vN = 0;
                }
                else
                {
                    if(index >= pN && i != piN)
                    {
                        FWARNING(("Point index (%d/%d) out of range", index, pN));
                        coordIndex[i] = 0;
                    }

                    vN++;
                }
            }
        }
        else
        {
            FWARNING(("No coordIndex in OSG::setIndexFromVRMLData()\n"));
            return 0;
        }
    }

    //----------------------------------------------------------------------
    // check the normal index

    normalIT = UNKNOWN_IT;

    niN = normalIndex.size();

    if(nN)
    {               // have normal elements
        if(normalPerVertex)
        {
            // normal per vertex
            if(niN >= piN)
            {
                // valid normal index number
                for(i = 0; i < piN; i++)
                {   // check if normal index equals the coord index
                    if(normalIndex[i] != coordIndex[i])
                    {
                        normalIT = VERTEX_IT;
                        break;
                    }
                }

                if(normalIT == UNKNOWN_IT)
                {
                    // if equal than delete unneeded normal index
                    normalIT = VERTEX_DUP_IT;
                }
            }
            else
            {
                // no or not enough normal index
                normalIT = VERTEX_COORD_IT;

                if(niN)
                {
                    FWARNING(("Not enough normal index (%d,%d)\n", normalIndex.
                                                     size(), piN));
                    normalIndex.clear();
                }
            }
        }
        else
        {
            // normal per primitive
            if(niN >= primitiveN)
            {
                // use one normal index per primitive
                normalIT = PRIMITIVE_INDEX_IT;
            }
            else
            {
                if(nN >= primitiveN)
                {
                    // use one normal per primitive
                    normalIT = PRIMITIVE_IT;
                }
                else
                {
                    FINFO(("not enough normal index (%d,%d)\n", nN, primitiveN));
                }
            }
        }
    }
    else
    {
        /* not yet !!!
if (createNormal)
  if (normalPerVertex)
    normalIT = VERTEX_CREATE_IT;
  else
    normalIT = PRIMITIVE_CREATE_IT;
else
*/
        normalIT = EMPTY_IT;
    }

    //----------------------------------------------------------------------
    // check the color index
    colorIT = UNKNOWN_IT;
    ciN = colorIndex.size();
    if(cN)
    {               // have color elements
        if(colorPerVertex)
        {
            // color per vertex
            if(ciN >= piN)
            {
                // valid color index number
                for(i = 0; i < piN; i++)
                {   // check if color index equals the coord index
                    if(colorIndex[i] != coordIndex[i])
                    {
                        colorIT = VERTEX_IT;
                        break;
                    }
                }

                if(colorIT == UNKNOWN_IT)
                {
                    // if equal than delete unneeded color index
                    colorIT = VERTEX_DUP_IT;
                }
            }
            else
            {
                // no or not enough color index
                colorIT = VERTEX_COORD_IT;
                if(ciN)
                {
                    FWARNING(("Not enough color index (%d,%d)\n", colorIndex.
                                                     size(), piN));
                    colorIndex.clear();
                }
            }
        }
        else
        {
            // color per primitive
            if(ciN >= primitiveN)
            {
                // use one color index per primitive
                colorIT = PRIMITIVE_INDEX_IT;
            }
            else
            {
                if(cN >= primitiveN)
                {
                    // use one color per primitive
                    colorIT = PRIMITIVE_IT;
                }
                else
                {
                    FINFO(("not enough color index (%d,%d)\n", cN, primitiveN));
                }
            }
        }
    }
    else
    {
        colorIT = EMPTY_IT;
    }

    //----------------------------------------------------------------------
    // check the texture index
    textureIT = UNKNOWN_IT;
    tiN = texCoordIndex.size();
    if(tN)
    {               // have texture elemnts
        if(tiN >= piN)
        {
            // valid texture index number
            for(i = 0; i < piN; i++)
            {       // check if texture index equals the coord index
                if(texCoordIndex[i] != coordIndex[i])
                {
                    textureIT = VERTEX_IT;
                    break;
                }
            }

            if(textureIT == UNKNOWN_IT)
            {
                // if equal than delete unneeded texture index
                textureIT = VERTEX_DUP_IT;
            }
        }
        else
        {
            // no or not enough texture index
            textureIT = VERTEX_COORD_IT;
            if(tiN)
            {
                FWARNING(("Not enough texCoord index (%d,%d)\n", texCoordIndex.
                                             size(), piN));
                texCoordIndex.clear();
            }
        }
    }
    else
    {
        textureIT = EMPTY_IT;
    }

    FNOTICE (( "primitiveN:  %d, %d, 0/%d 1/%d 2/%d 3/%d 4/%d 5/%d\n",
            primitiveType,
            primitiveN, primitiveTypeCount[0],
            primitiveTypeCount[1], primitiveTypeCount[2],
            primitiveTypeCount[3], primitiveTypeCount[4],
            primitiveTypeCount[5]));
    
    FNOTICE (( "IndexType: coord: %s, color: %s, normal: %s, texture: %s \n",
            indexTypeStr[coordIT], indexTypeStr[colorIT], 
            indexTypeStr[normalIT], indexTypeStr[textureIT]));

    //----------------------------------------------------------------------
    // check/create the indexPtr/lengthsPtr/geoTypePtr

    posIndexPtr = geoPtr->getIndex(Geometry::PositionsIndex);

    if(posIndexPtr == NullFC)
    {
        posIndexPtr = GeoUInt32Property::create();
    }
    else
    {
        posIndexPtr->clear();
    }

    for(i = 1; i < 4; ++i)
    { 
        indexOutBag[i] = geoPtr->getIndex(indexOutBagID[i]);
        
        if(indexOutBag[i] != NullFC)
        {
            indexOutBag[i]->clear();
        }

        geoPtr->setIndex(NullFC, texCoordIdx[i]);
    }


    lensPtr = geoPtr->getLengths();

    if(lensPtr == NullFC)
    {
        lensPtr = GeoUInt32Property::create();
    }
    else
    {
        lensPtr->clear();
    }

    geoTypePtr = geoPtr->getTypes();

    if(geoTypePtr == NullFC)
    {
        geoTypePtr = GeoUInt8Property::create();
    }
    else
    {
        geoTypePtr->clear();
    }

    //----------------------------------------------------------------------
    // set lens/geoType/index/mapping the index mapping

    geoPtr->setLengths(lensPtr);
    geoPtr->setTypes(geoTypePtr);

    geoPtr->setIndex(posIndexPtr, Geometry::PositionsIndex);

    //----------------------------------------------------------------------
    // create index face/line data

    for(pType = minPType; pType <= maxPType; pType++)
    {
        // check for the pType count
        if(primitiveTypeCount[pType])
        {
            // calc len/sysPType
          
            if(pType < maxPType)
            {
                len = primitiveTypeCount[pType] * pType;

                switch (pType) 
                {
                  case 1:
                      sysPType = GL_POINTS;
                      break;
                    case 2:
                        sysPType = GL_LINES;
                        break;
                    case 3:
                        sysPType = GL_TRIANGLES;
                        break;
                    case 4:
                        sysPType = GL_QUADS;
                        break;
                }
            }
            else
            { 
                sysPType = 0;
            }

            // set len/sysPType
            if(sysPType)
            {
                lensPtr->push_back(len);

                geoTypePtr->push_back(sysPType);
            }

            primitiveN = 0;
            beginIndex = endIndex = -1;

            for(i = 0; i <= piN; i++)
            {
                if(((i == piN) && (coordIndex[i - 1] >= 0)) ||
                                   ((i < piN) && (coordIndex[i] < 0)))
                {
                    len = i - beginIndex;

                    if(ccw)
                    {
                        endIndex = i;
                        step = 1;
                    }
                    else
                    {
                        endIndex = beginIndex - 1;
                        beginIndex = i - 1;
                        step = -1;
                    }

                    localPType = (len > maxPType) ? maxPType : len;

                    if((beginIndex >= 0) && (localPType == pType))
                    {
                        if(len >= maxPType)
                        {
                            sysPType = primitiveType;

                            lensPtr->push_back(len);
                            geoTypePtr->push_back(sysPType);
                        }

                        // add index data
                        for(pi = beginIndex; pi != endIndex; pi += step)
                        {
                            posIndexPtr->push_back(coordIndex[pi]);

                            for(typei = 1; typei <= 3; typei++)
                            {
                                index = -1;

                                switch(indexType[typei])
                                {
                                    case UNKNOWN_IT:
                                    case EMPTY_IT:
                                    case VERTEX_COORD_IT:
                                    case VERTEX_DUP_IT:
                                        break;
                                    case VERTEX_IT:
                                        index = (*indexBag[typei])[pi];
                                        break;
                                    case PRIMITIVE_IT:
                                        index = primitiveN;
                                        break;
                                    case PRIMITIVE_INDEX_IT:
                                        index = (*indexBag[typei])[primitiveN];
                                        break;
                                    default:                        //X_CREATE_IT
                                        break;
                                }

                                        
                                if(index != -1)
                                {
                                    if(indexOutBag[typei] == NullFC)
                                    {
                                        indexOutBag[typei] = GeoUInt32Property::create();
                                        addRef(indexOutBag[typei]);
                                    }
                                    
                                    indexOutBag[typei]->push_back(index);
                                }
                            }
                            
                        }

                        triCount += len - 2;
                    }

                    primitiveN++;
                    beginIndex = endIndex = -1;
                }
                else if(beginIndex < 0)
                {
                    beginIndex = i;
                }
            }
        }
    }

    for(UInt32 i = 1; i < 4; ++i)
    {
        if((indexType  [i] == VERTEX_COORD_IT || indexType  [i]         == VERTEX_DUP_IT) &&
           (indexOutBag[i] == NullFC          || indexOutBag[i]->size() == 0            )   )
        {
            geoPtr->setIndex(posIndexPtr, indexOutBagID[i]);
        }
        else if(indexOutBag[i] != NullFC && indexOutBag[i]->size() != 0)
        {
            geoPtr->setIndex(indexOutBag[i], indexOutBagID[i]);
        }
        else if(indexOutBag[i] != NullFC && indexOutBag[i]->size() == 0)
        {
            geoPtr->setIndex(NullFC, indexOutBagID[i]);
        }
    }

    for(UInt32 i = 1; i < 4; ++i)
    {
        if(texCoordN[i] != 0)
        {
            if((indexType  [3] == VERTEX_COORD_IT || indexType  [3]         == VERTEX_DUP_IT) &&
               (indexOutBag[3] == NullFC          || indexOutBag[3]->size() == 0            )   )
            {
                geoPtr->setIndex(posIndexPtr, texCoordIdx[i]);
            }
            else if(indexOutBag[3] != NullFC && indexOutBag[3]->size() != 0)
            {
                geoPtr->setIndex(indexOutBag[3], texCoordIdx[i]);
            }
        }
    }

    
    for(UInt32 i = 1; i < 4; ++i)
    {
        subRef(indexOutBag[i]);
    }

    return triCount;
}


Int32 createOptimizedPrimitives(GeometryPtrArg  geo,
                                UInt32          iteration,
                                bool            createStrips,
                                bool            createFans,
                                UInt32          minFanEdgeCount,
                                bool            colorCode,
                                bool            stitchStrips   )
{
    if (geo == NullFC)
    {
        return 0;
    }

    StriperHalfEdgeGraph graph;

    UInt32 cost            = 0;
    UInt32 startCost       = 0;
    UInt32 bestCost        = 0;
    UInt32 worstCost       = 0;
    UInt32 best            = 0;
    UInt32 triN            = 0;
    UInt32 lineN           = 0;
    UInt32 pointN          = 0;
    Int32  invalidTriCount = 0;

    Time time;
    Time inputT;
    Time optimizeT;
    Time outputT;


    Geometry::IndexBag oGeoIndexBag = geo->getUniqueIndexBag();


    UInt32   indexMapSize = oGeoIndexBag.size();
    bool     remapIndex   = (indexMapSize > 1) ? true : false;

    IndexDic indexDic;


    calcPrimitiveCount(geo, triN, lineN, pointN);

    GeoVectorPropertyPtr    posPtr = geo->getPositions();

    UInt32 pN = ((posPtr == OSG::NullFC) ? 0 : posPtr->getSize());

    GeoIntegralPropertyPtr posIndexPtr = 
        geo->getIndex(Geometry::PositionsIndex);

    // Calculate startCost.
    if(posIndexPtr == NullFC)
    {
        startCost = pN;
    }
    else
    {
        startCost = posIndexPtr->size();
    }

    // Leave early if we have no indices or positions.
    if (pN == 0 || posIndexPtr == NullFC)
    {
        return 0;
    }

    FDEBUG(("GeoOpt: start/tri cost: %d/%d imp: %d tri/line/point: %d/%d/%d\n",
            startCost, (triN * 3), indexMapSize, triN, lineN, pointN));

    inputT = getSystemTime();

    invalidTriCount = 0;
    
    if (!remapIndex && (pN > (triN * 3))) 
    {
        FINFO(("Force index remap for unusual vertex/tri count: %d/%d\n",
               pN, triN ));

        indexMapSize = 1;
        remapIndex = true;
    }

    if(remapIndex)
    {
        graph.reserve(triN * 3, triN, 8);

        std::vector < Int32 > indexVec(indexMapSize);

        UInt32 triCount = 0;

        for(TriangleIterator tI = geo->beginTriangles(); 
            (triCount < triN) && (tI != geo->endTriangles());
            ++tI)
        {
            Int32 v[3];

            for(Int32 i = 0; i < 3; i++)
            {
                Int32 index = tI.getIndex(i);

                for(Int32 j = 0; j < indexMapSize; j++)
                {
                    indexVec[j] = oGeoIndexBag[j].first->getValue(index);
                }

                v[i] = indexDic.entry(indexVec);
            }

            invalidTriCount += graph.addTriangle(v[0], v[1], v[2]) ? 0 : 1;

            ++triCount;
        }

        FDEBUG(("Multi-index dic entry: %d/%d\n", indexDic.entryCount(),
                                (triN * 3)));
    }
    else
    {
        graph.reserve(osgMin(pN, triN * 3), triN, 8);

        UInt32 triCount = 0;

        for(TriangleIterator tI = geo->beginTriangles(); 
            (triCount < triN) && (tI != geo->endTriangles());
            ++tI)
        {
            invalidTriCount += 
                graph.addTriangle(tI.getPositionIndex(0),
                                  tI.getPositionIndex(1),
                                  tI.getPositionIndex(2)) ? 0 : 1;
            ++triCount;
        }
    }


    if(invalidTriCount)
    {
        FNOTICE(("%d invalid tri during halfegde construction found\n",
                                 invalidTriCount));
    }

#ifdef OSG_DEBUG
    graph.verify();
#endif

    time      = getSystemTime();
    inputT    = time - inputT;
    optimizeT = time;
    bestCost  = triN * 3 + 1;
    worstCost = 0;

    cost = graph.calcOptPrim(iteration, 
                             createStrips, 
                             createFans, 
                             minFanEdgeCount);

    if(cost)
    {
        if(cost < bestCost)
            bestCost = cost;

        if(cost > worstCost)
            worstCost = cost;
    }
    else
    {
        bestCost = worstCost = 0;
    }

    // valid result
    if(bestCost && (bestCost < startCost))
    {
        GeoIntegralPropertyPtr lensPtr;
        GeoIntegralPropertyPtr geoTypePtr;

        // check/create the indexPtr/lengthsPtr/geoTypePtr

        lensPtr = geo->getLengths();

        if(lensPtr == OSG::NullFC)
        {
            lensPtr = OSG::GeoUInt32Property::create();

            geo->setLengths(lensPtr);
        }

        geoTypePtr = geo->getTypes();

        if(geoTypePtr == OSG::NullFC)
        {
            geoTypePtr = OSG::GeoUInt8Property::create();

            geo->setTypes(geoTypePtr);
        }


        time      = getSystemTime();
        optimizeT = time - optimizeT;
        outputT   = time;

        lensPtr   ->clear();
        geoTypePtr->clear();
        
        for(UInt32 i = 0; i < indexMapSize; ++i)
        {
            oGeoIndexBag[i].first->clear();
        }


        FDEBUG(("Start graph.getPrimitive() loop (triN: %d)\n", triN));

        UInt32 numPrimitives = graph.primitiveCount();

        std::vector< std::vector<UInt32> > primIndex(numPrimitives);

        const Int32 typeVec[] = 
        {
            GL_TRIANGLES, 
            GL_TRIANGLE_STRIP, 
            GL_TRIANGLE_FAN 
        };

        const Int32 typeN = sizeof(typeVec) / sizeof(Int32);

        cost = 0;

        for(Int32 t = 0; t < typeN; ++t)
        {
            UInt32 triCount = 0;

            bool   stitch              = false;
            UInt32 windingCorrection   = 0;
            UInt32 lastTriStripIndex   = 0;
            UInt32 totalTriStripLength = 0;

            for(Int32 i = 0; i < Int32(numPrimitives); ++i)
            {
                graph.getPrimitive(primIndex[i], typeVec[t]);

                const Int32 n = primIndex[i].size();

                cost += n;

                if(!n)
                {
                    break;
                }

                if(typeVec[t] == GL_TRIANGLES)
                {
                    triCount += (n / 3);
                }
                else if (typeVec[t] == GL_TRIANGLE_STRIP)
                {
                    if (stitchStrips)
                    {
                        if (stitch)
                        {
                            // add the previous index and the first of the
                            // new one, but make sure winding is still correct.
                            if(remapIndex)
                            {
                                for (int j = 0; j < 1 + windingCorrection; ++j)
                                {
                                    for (int k = 0; k < indexMapSize; ++k)
                                    {
                                        oGeoIndexBag[k].first->push_back(
                                            indexDic.entry(
                                                lastTriStripIndex)[k]);
                                    }
                                }
                                for (int k = 0; k < indexMapSize; ++k)
                                {
                                    oGeoIndexBag[k].first->push_back(
                                        indexDic.entry(primIndex[i][0])[k]);
                                }
                            }
                            else
                            {
                                for (int j = 0; j < 1 + windingCorrection; ++j)
                                {
                                    posIndexPtr->push_back(lastTriStripIndex);
                                }

                                posIndexPtr->push_back(primIndex[i][0]);
                            }

                            totalTriStripLength += 2 + windingCorrection;
                        }

                        stitch = true;
                        windingCorrection = n % 2;
                        lastTriStripIndex = primIndex[i][n - 1];
                    }
                    else
                    {
                        lensPtr   ->push_back(n);
                        geoTypePtr->push_back(typeVec[t]);
                    }
                }
                else
                {
                    lensPtr   ->push_back(n);
                    geoTypePtr->push_back(typeVec[t]);
                }

                if(remapIndex)
                {
                    for(Int32 j = 0; j < n; ++j)
                    {
                        for(Int32 k = 0; k < indexMapSize; ++k)
                        {
                            Int32 index = indexDic.entry(primIndex[i][j])[k];
                            oGeoIndexBag[k].first->push_back(index);
                        }
                    }
                }
                else
                {
                    for(Int32 j = 0; j < n; ++j)
                    {
                        posIndexPtr->push_back(primIndex[i][j]);
                    }
                }

                totalTriStripLength += n;
            }

            if(triCount && typeVec[t] == GL_TRIANGLES)
            {
                lensPtr   ->push_back(triCount * 3);
                geoTypePtr->push_back(GL_TRIANGLES);
            }

            if(stitchStrips && totalTriStripLength &&
               typeVec[t] == GL_TRIANGLE_STRIP)
            {
                lensPtr   ->push_back(totalTriStripLength);
                geoTypePtr->push_back(GL_TRIANGLE_STRIP);
            }
        }

        time    = getSystemTime();
        outputT = time - outputT;

        FNOTICE(("Graph in/opt/out timing: %g/%g/%g \n", inputT, optimizeT,
                                outputT));

        if(cost != bestCost)
        {
            FWARNING(("cost != bestCost: %d/%d; we lost some nodes !\n",
                                       cost, bestCost));
        }
        else
        {
            FINFO(("OptResult: %2g%%, Sampling (%di): cost %d/%d \n",
                                        double(double(bestCost) / double(
                                            startCost) * 100.0
                                ), iteration, bestCost, worstCost));
        }
    }
    else
    {
        FINFO(("startCost (%d) <= bestCost (%d), triCost(%d); keep geo data\n",
               startCost, bestCost, (triN * 3)));
    }

    return bestCost;
}

void createConvexPrimitives(GeometryPtrArg  geo)
{
    FFATAL(("createConvexPrimitives:: NYI!\n"));
}

Int32 createSharedIndex(GeometryPtrArg geoPtr)
{
    FFATAL(("createSharedIndex:: NYI!\n"));
    return -1;
}

Int32 createSingleIndex(GeometryPtrArg  geo)
{
    FFATAL(("createSingleIndex:: NYI!\n"));
    return -1;
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

Calculate some basic statistics of the Geometry. 

*/
UInt32 calcPrimitiveCount(GeometryPtrArg  geo,
                          UInt32         &triangle,
                          UInt32         &line,
                          UInt32         &point)
{
    GeoIntegralPropertyPtr geoTypePtr;
    GeoIntegralPropertyPtr lensPtr;

    UInt32 lN, tN, len, type;

    // TODO; should we really reset the values ?
    triangle = line = point = 0;

    if(geo == NullFC)
    {
        FINFO(("No geo in calcPrimitiveCount\n"));
        return 0;
    }

    lensPtr = geo->getLengths();

    lN = (lensPtr == NullFC) ? 0 : lensPtr->getSize();
    
    
    geoTypePtr = geo->getTypes();

    tN = (geoTypePtr == NullFC) ? 0 : geoTypePtr->getSize();

    if((tN == 0) || (lN != 0 && tN != lN) || (lN == 0 && tN != 1))
    {
        return 0;
    }

    for(UInt32 i = 0; i < geoTypePtr->size(); ++i)
    {
        geoTypePtr->getValue(type, i);

        if(lN != 0)
        {
            lensPtr->getValue(len, i);
        }
        else
        {
            GeoVectorPropertyPtr pos = geo->getPositions();
            
            if(pos == NullFC)
            {
                FINFO(("calcPrimitiveCount: no Points!\n"));
                return 0;
            }
            
            len = pos->size();
        }
        
        switch(type)
        {
            case GL_POINTS:
                point += len;
                break;
            case GL_LINES:
                line += len / 2;
                break;
            case GL_LINE_LOOP:
                line += len;
                break;
            case GL_LINE_STRIP:
                line += len - 1;
                break;
            case GL_TRIANGLES:
                triangle += len / 3;
                break;
            case GL_TRIANGLE_STRIP:
                triangle += len - 2;
                break;
            case GL_TRIANGLE_FAN:
                triangle += len - 2;
                break;
            case GL_QUADS:
                triangle += len / 2;
                break;
            case GL_QUAD_STRIP:
                triangle += len - 2;
                break;
            case GL_POLYGON:
                triangle += len - 2;
                break;
            default:
                FWARNING(("calcPrimitiveCount(): Invalid geoType: %d\n", 
                          type));
                break;
        }
        
    }

    return triangle + line + point;
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

Create a geometry of the vertex normals of the object. Useful for Visualizing
the normals. 

\warning It does not check whether the normals are actually vertex normals,
it just uses them as if.

*/
NodePtr calcVertexNormalsGeo(GeometryPtrArg  geo, 
                             Real32          length)
{
    GeoPnt3fPropertyPtr pnts = GeoPnt3fProperty::create();

    // calculate

    PrimitiveIterator pi(geo);

    if(1 /* no easy way to check right now */ )
    {
        for(pi = geo->beginPrimitives(); pi != geo->endPrimitives(); ++pi)
        {
            for(UInt32 k = 0; k < pi.getLength(); k++)
            {
                pnts->push_back(pi.getPosition(k));
                pnts->push_back(pi.getPosition(k) + length * pi.getNormal(k));
            }
        }
    }
    else
    {
        Pnt3f center(0, 0, 0);

        for(pi = geo->beginPrimitives(); pi != geo->endPrimitives(); ++pi)
        {
            for(UInt32 k = 0; k < pi.getLength(); k++)
            {
                center[0] += pi.getPosition(k)[0];
                center[1] += pi.getPosition(k)[1];
                center[2] += pi.getPosition(k)[2];
            }

            pnts->push_back(center);
            pnts->push_back(center + length * pi.getNormal(0));
        }
    }

    GeoIntegralPropertyPtr type = GeoUInt8Property::create();

    type->push_back(GL_LINES);

    GeoIntegralPropertyPtr lens = GeoUInt32Property::create();

    lens->push_back(pnts->getSize());

    GeometryPtr g = Geometry::create();

    g->setTypes    (type);
    g->setLengths  (lens);
    g->setPositions(pnts);

    return makeNodeFor(g);
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

Create a geometry of the face normals of the object. Useful for Visualizing
the normals. 

\warning It does not check whether the normals are actually face normals,
it just uses them as if.

*/
NodePtr calcFaceNormalsGeo(GeometryPtrArg  geo, 
                           Real32          length)
{
    NodePtr              p     = Node::create();
    GeometryPtr          g     = Geometry::create();
    GeoPnt3fPropertyPtr  pnts  = GeoPnt3fProperty::create();
    GeoUInt32PropertyPtr index = GeoUInt32Property::create();
    GeoUInt8PropertyPtr  type  = GeoUInt8Property::create();
    GeoUInt32PropertyPtr lens  = GeoUInt32Property::create();

    // calculate

    FaceIterator faceIter = geo->beginFaces();
    Pnt3f center;

    for(; faceIter != geo->endFaces(); ++faceIter)
    {
        center[0] = 0;
        center[1] = 0;
        center[2] = 0;

        for(UInt16 i = 0; i < faceIter.getLength(); ++i)
        {
            center[0] += faceIter.getPosition(i)[0] / faceIter.getLength();
            center[1] += faceIter.getPosition(i)[1] / faceIter.getLength();
            center[2] += faceIter.getPosition(i)[2] / faceIter.getLength();
        }

        pnts->push_back(center);

        switch(faceIter.getType())
        {
            case GL_TRIANGLE_STRIP:
                pnts->push_back(center + length * faceIter.getNormal(2));
                break;
            case GL_TRIANGLE_FAN:
                pnts->push_back(center + length * faceIter.getNormal(2));
                break;
            case GL_QUAD_STRIP:
                pnts->push_back(center + length * faceIter.getNormal(3));
                break;
            default:
                //does not matter which point's normal
                pnts->push_back(center + length * faceIter.getNormal(0));
                break;
        }
    }

    for(UInt32 i = 0; i < pnts->getSize(); i++)
        index->push_back(i);

    type->push_back(GL_LINES);

    lens->push_back(index->getSize());

    g->setTypes    (type );
    g->setLengths  (lens );
    g->setIndices  (index);
    g->setPositions(pnts );

    p->setCore(g);

    return p;
}


OSG_DRAWABLE_DLLMAPPING 
void    separateProperties      (GeometryPtrArg  geo)
{
    FFATAL(("separateProperties: not implemented yet!\n"));
}


OSG_DRAWABLE_DLLMAPPING 
void mergeGeometries(std::vector<NodePtr> &nodes,
                     std::vector<NodePtr> &results)
{
    FFATAL(("mergeGeometries: not implemented yet!\n"));
}

OSG_END_NAMESPACE

