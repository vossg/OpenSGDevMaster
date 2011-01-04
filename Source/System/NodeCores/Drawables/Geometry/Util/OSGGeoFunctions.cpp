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
#include "OSGGeoPropertyFactory.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGStriperHalfEdgeGraph.h"
#include "OSGPrimeMaterial.h"

// #include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                   Merge helper struct                        */
/*! \{                                                                 */

/*! \ingroup GrpDrawablesGeometryUtils
    \nohierarchy
 */
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

/*! \ingroup GrpDrawablesGeometryUtils
    \nohierarchy
    memory comparison
 */
template <class TypeT>
struct memless
{
    bool operator ()(const TypeT &a, const TypeT &b) const
    {
        if(a.second && b.second)
        {
            if(a.second == b.second)
            {
                return (memcmp(a.first, b.first, a.second) < 0) ? true : false;
            }
            else
            {
                FFATAL(("a.memSize != b.memSize in memless::operator()\n"));
            }
        }
        else
        {
            FFATAL(("memSize is NULL in memless::operator()\n"));
        }
        return false;
    }
};

/*! \}                                                                 */
/*---------------------------------------------------------------------*/



/*! \ingroup GrpDrawablesGeometryUtils

  Calculate vertex normals for the given geometry. 

  It just averages all normals that use a given vertex (as indicated by its
  index). It is smart enough to only change the normals that are used by this
  Geometry, and tries to reuse indices if they're not shared on other
  properties.

  \warning This doesn't do anything for nonindexed geometries!

 */
void calcVertexNormals(Geometry *geo)
{
    GeoVectorPropertyUnrecPtr   norms;
    GeoIntegralPropertyUnrecPtr normsIndex;
    GeoIntegralPropertyUnrecPtr posIndex;

    posIndex = geo->getIndex(Geometry::PositionsIndex);

    if(posIndex == NULL)
    {
        FWARNING(("calcVertexNormals: Geometry is not indexed, ignored!\n"));
        return;
    }
    
    norms = geo->getNormals();

    if(norms == NULL)
    {
        norms = GeoVec3fProperty::create();
    }

    norms->resize(geo->getPositions()->size());


    normsIndex = geo->getIndex(Geometry::NormalsIndex);

    // No indices reuse positions
    if(normsIndex == NULL)
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

            posIndex  ->getValue(val, i);
            normsIndex->addValue(val   );
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


/*! \ingroup GrpDrawablesGeometryUtils

  Calculate vertex normals for the given geometry. Only vertices whose
  triangles have an angle less than \a creaseAngle radians to each other are
  merged.

  \warning This doesn't do anything for nonindexed geometries!

 */
void calcVertexNormals(Geometry *geo,
                       Real32    creaseAngle)
{
    GeoVectorPropertyUnrecPtr   norms;
    GeoVectorPropertyUnrecPtr   positions;
    GeoIntegralPropertyUnrecPtr normsIndex;
    GeoIntegralPropertyUnrecPtr posIndex;

    if(creaseAngle >= Pi)
    {
        calcVertexNormals(geo);
        return;
    }

    // Get the positions property
    if(geo->getProperty(Geometry::PositionsIndex) == NULL)
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

    if(posIndex == NULL)
    {
        FINFO(("Geo without position index in calcVertexNormals()\n"));
        return;
    }

    norms = geo->getProperty(Geometry::NormalsIndex);

    // Get normal property, create if needed
    if(norms == NULL)
    {
        norms = GeoVec3fProperty::create();
        
        geo->setProperty(norms, Geometry::NormalsIndex);
    }

    normsIndex = geo->getIndex(Geometry::NormalsIndex);

    // No indices reuse positions
    if(normsIndex == NULL || geo->indexOccurrence(normsIndex) > 1)
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
        UInt32 tind = ti.getIndex();
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

/*! \ingroup GrpDrawablesGeometryUtils
 */

void calcFaceNormals(Geometry *geo)
{
    FFATAL(("calcFaceNormals:: NYI!\n"));
}

/*! \ingroup GrpDrawablesGeometryUtils
 */

void calcVertexTangentsProp(Geometry *geo,
                            UInt32    srcTexProp,
                            UInt32    srcNormalProp,
                            UInt32    dstPropTan,
                            UInt32    dstPropBin)
{
    GeoVec4fPropertyUnrecPtr  tangentP;
    GeoVec4fPropertyUnrecPtr  binormalP;
    GeoUInt32PropertyUnrecPtr tanBinIndexP;

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

    GeoIntegralProperty *posIdx  = geo->getIndex(Geometry::PositionsIndex);
        
    // HACK but without indices it crashes
    if(posIdx == NULL || posIdx->size() == 0) 
    {
        FFATAL(("Geo without pos indices in calcVertexTangents()\n"));
        return;
    }
    
    GeoVectorProperty *positions = geo->getPositions();
    
    // Get the positions property
    if(positions == NULL) 
    {
        FFATAL(("Geo without positions in calcVertexTangents()\n"));
        return;
    }

    GeoVectorProperty *srcTexCoords = geo->getProperty(srcTexProp);
    
    // Get the positions property
    if(srcTexCoords == NULL) 
    {
        FFATAL(("Geo without srcTexCoords in calcVertexTangents()\n"));
        return;
    }

    GeoVectorProperty *srcNormals = geo->getProperty(srcNormalProp);
    
    // Get the positions property
    if(srcNormals == NULL) 
    {
        FFATAL(("Geo without srcNormals in calcVertexTangents()\n"));
        return;
    }
    
    UInt32 posIdxCount  = posIdx->size();

    tangentP     = GeoVec4fProperty::create();
    binormalP    = GeoVec4fProperty::create();
    
    tanBinIndexP = GeoUInt32Property::create();
    tanBinIndexP->resize(posIdxCount);

    geo->setProperty(tangentP,     dstPropTan);
    geo->setIndex   (tanBinIndexP, dstPropTan);

    geo->setProperty(binormalP,    dstPropBin);
    geo->setIndex   (tanBinIndexP, dstPropBin);

    TriangleIterator tI;
    IndexDic indexDic;
    Int32 k, v[3];
    Vec4f vect(0, 0, 0, 0);
    
    UInt32             propSize = 0;
    std::vector<Int32> indexVec;

    indexVec.resize(3);    
    
    // Size of properties is number of unique index tuples, which requires
    // looking at all of them - we take a best effort guess here and resize
    // in the loop below
    tangent .resize(posIdxCount, Vec3f::Null);
    binormal.resize(posIdxCount, Vec3f::Null);
    normal  .resize(posIdxCount, Vec3f::Null);

    Int32 i = 0;

    for(  tI  = geo->beginTriangles(), i = 0; 
          tI != geo->endTriangles(); 
        ++tI, ++i) 
    {       
        for(k = 0; k < 3; ++k) 
        {
            indexVec[0] = tI.getPropertyIndex(Geometry::PositionsIndex, k);
            indexVec[1] = tI.getPropertyIndex(srcNormalProp,            k);
            indexVec[2] = tI.getPropertyIndex(srcTexProp,               k);

            v[k]        = indexDic.entry(indexVec);

            if(v[k] > Int32(propSize))
                propSize = v[k];
        }

        // resize properties if inital guess was too small
        if(propSize >= tangent.size())
        {
            tangent .resize(1.5f * tangent .size() + 1, Vec3f::Null);
            binormal.resize(1.5f * binormal.size() + 1, Vec3f::Null);
            normal  .resize(1.5f * normal  .size() + 1, Vec3f::Null);
        }

        // second, calculate tangent and binormal for every tri
        Vec2f t0, t1, t2, tex1, tex2;
        Vec3f edge1, edge2, sdir, tdir;
        
        t0 = tI.getTexCoords(srcTexProp, 0);
        t1 = tI.getTexCoords(srcTexProp, 1);
        t2 = tI.getTexCoords(srcTexProp, 2);
        
        edge1 = tI.getPosition(1) - tI.getPosition(0),
        edge2 = tI.getPosition(2) - tI.getPosition(0);

        tex1 = t1 - t0;
        tex2 = t2 - t0;
        
        Real32 invDet = (tex1[0]*tex2[1] - tex2[0]*tex1[1]);

        if(invDet != 0.0f)
        {
            invDet = 1.0f / invDet;
        }
        else
        {
            invDet = 0.0f;
        }

        sdir = invDet * (tex2[1]*edge1 - tex1[1]*edge2);    // tangent
        tdir = invDet * (tex1[0]*edge2 - tex2[0]*edge1);    // binormal
        
        for(k = 0; k < 3; ++k) 
        {
            tangent [v[k]] += sdir;
            binormal[v[k]] += tdir;
            normal  [v[k]]  = tI.getNormal(srcNormalProp, k);

            tanBinIndexP->setValue(v[k], tI.getIndex(k)); 
        }
    }

    // adjust size - resizing above may have been to big
    if(tangent.size() > propSize)
    {
        tangent .resize(propSize);
        binormal.resize(propSize);
        normal  .resize(propSize);
    }
    
    // orthogonalize vectors (Gram-Schmidt) and calc handedness    
    Vec3f T, B, N;

    Real32 sign = 0;

    tangentP ->clear();
    binormalP->clear();

    for(UInt32 i = 0; i < tangent.size(); i++) 
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

/*! \ingroup GrpDrawablesGeometryUtils
 */

void calcVertexTangents(Geometry *geo,
                        UInt32    srcTexIndex,
                        UInt32    dstPropTan,
                        UInt32    dstPropBin)
{
    calcVertexTangentsProp(geo,
                           srcTexIndex + Geometry::TexCoordsIndex,
                           Geometry::NormalsIndex,
                           dstPropTan,
                           dstPropBin);
}

/*! \ingroup GrpDrawablesGeometryUtils
 */

void calcVertexTexCoordsProp2D(Geometry *geo,
                               UInt32    propIndex)
{
    struct Key 
    {
        Real32 value;
        Int32 pos;
    } key[3], rem;

    Int32 S = -1, T = -1, n = 3, i, j; 
    Real32 sDenom, tDenom, sMin, tMin;
    
    GeoIntegralPropertyUnrecPtr ip   = geo->getIndices  ();
    GeoVectorPropertyUnrecPtr   posP = geo->getPositions();
    GeoVectorPropertyUnrecPtr   texP;

    if(posP == NULL || !posP->size() || ip == NULL || !ip->size())
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
        Node *node = dynamic_cast<Node *>(*pnI);

        if(node != NULL)
        {
            BoxVolume &bVol = node->editVolume(true);

            Pnt3f min, max;

            bVol.getBounds(min, max);
    
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

void calcVertexTexCoords(Geometry *geo,
                         UInt32    texIndex)
{
    calcVertexTexCoordsProp2D(geo, texIndex + Geometry::TexCoordsIndex);
}

/*! \ingroup GrpDrawablesGeometryUtils

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

Int32 setIndexFromVRMLData(     Geometry       *geoPtr,
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

    GeoVectorPropertyUnrecPtr   posPtr;
    GeoVectorPropertyUnrecPtr   normalPtr;
    GeoVectorPropertyUnrecPtr   colorPtr;
    GeoVectorPropertyUnrecPtr   texCoordsPtr;
    GeoIntegralPropertyUnrecPtr lensPtr;
    GeoIntegralPropertyUnrecPtr geoTypePtr;

    GeoIntegralPropertyUnrecPtr posIndexPtr  = NULL;

    Int32 index, i, pi, typei, primitiveN = 0, vN = 0;
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
//    UInt32 uiNumTextures = 0;

    IndexBagP indexBag[4] =
    {
        &coordIndex,
        &normalIndex,
        &colorIndex,
        &texCoordIndex
    };

    GeoIntegralPropertyUnrecPtr indexOutBag[4] =
    {
        NULL,
        NULL,
        NULL,
        NULL
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
    pN = ((posPtr == NULL) ? 0 : posPtr->getSize());

    normalPtr = geoPtr->getNormals();
    nN = ((normalPtr == NULL) ? 0 : normalPtr->getSize());

    colorPtr = geoPtr->getColors();
    cN = ((colorPtr == NULL) ? 0 : colorPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords();
    tN = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords1();
    tN1 = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords2();
    tN2 = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords3();
    tN3 = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

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
                    FWARNING(("Not enough normal index (%"PRISize",%d)\n", 
                              normalIndex.size(), piN));
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
                    FWARNING(("Not enough color index (%"PRISize",%d)\n", 
                              colorIndex.size(), piN));
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
                FWARNING(("Not enough texCoord index (%"PRISize",%d)\n", 
                          texCoordIndex.size(), piN));
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

    if(posIndexPtr == NULL)
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
        
        if(indexOutBag[i] != NULL)
        {
            indexOutBag[i]->clear();
        }
    }

    lensPtr = geoPtr->getLengths();

    if(lensPtr == NULL)
    {
        lensPtr = GeoUInt32Property::create();
    }
    else
    {
        lensPtr->clear();
    }

    geoTypePtr = geoPtr->getTypes();

    if(geoTypePtr == NULL)
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
                                            if(indexOutBag[typei] == NULL)
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
           (indexOutBag[i] == NULL          || indexOutBag[i]->size() == 0            )   )
        {
            geoPtr->setIndex(posIndexPtr, indexOutBagID[i]);
        }
        else if(indexOutBag[i] != NULL && indexOutBag[i]->size() != 0)
        {
            geoPtr->setIndex(indexOutBag[i], indexOutBagID[i]);
        }
    }

    return triCount;
}


/*! \ingroup GrpDrawablesGeometryUtils

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

Int32 setIndexFromIndexedX3DData ( Geometry           *geoPtr,
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

    GeoVectorPropertyUnrecPtr   posPtr;
    GeoVectorPropertyUnrecPtr   normalPtr;
    GeoVectorPropertyUnrecPtr   colorPtr;
    GeoVectorPropertyUnrecPtr   texCoordsPtr;

    GeoIntegralPropertyUnrecPtr lensPtr;
    GeoIntegralPropertyUnrecPtr geoTypePtr;
    GeoIntegralPropertyUnrecPtr posIndexPtr  = NULL;

    //bool faceSet = (primitiveType == GL_POLYGON);
    Int32 index, pi, typei, primitiveN = 0, vN = 0;
    Int32 pType = 0, localPType;
    Int32 maxPType = 0; //  = (faceSet ? 5 : 3);
    Int32 minPType = 0; //  = (faceSet ? 3 : 2);
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

    IndexBagP indexBag[4] =
    {
        &coordIndex,
        &normalIndex,
        &colorIndex,
        &texCoordIndex
    };

    GeoIntegralPropertyUnrecPtr indexOutBag[4] =
    {
        NULL,
        NULL,
        NULL,
        NULL
    };

    UInt16 indexOutBagID[4] =
    {
        Geometry::PositionsIndex,
        Geometry::NormalsIndex,
        Geometry::ColorsIndex,
        Geometry::TexCoordsIndex
    };

    static const UInt32 uiNumTexCoords = 8;

    UInt32 texCoordN[uiNumTexCoords] =
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };

    UInt16 texCoordIdx[uiNumTexCoords] =
    {
        Geometry::TexCoordsIndex,
        Geometry::TexCoords1Index,
        Geometry::TexCoords2Index,
        Geometry::TexCoords3Index,
        Geometry::TexCoords4Index,
        Geometry::TexCoords5Index,
        Geometry::TexCoords6Index,
        Geometry::TexCoords7Index
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
    pN = ((posPtr == NULL) ? 0 : posPtr->getSize());

    normalPtr = geoPtr->getNormals();
    nN = ((normalPtr == NULL) ? 0 : normalPtr->getSize());

    colorPtr = geoPtr->getColors();
    cN = ((colorPtr == NULL) ? 0 : colorPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords();
    tN = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());
    texCoordN[0] = tN;

    texCoordsPtr = geoPtr->getTexCoords1();
    texCoordN[1] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords2();
    texCoordN[2] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords3();
    texCoordN[3] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords4();
    texCoordN[4] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords5();
    texCoordN[5] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords6();
    texCoordN[6] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords7();
    texCoordN[7] = ((texCoordsPtr == NULL) ? 0 : texCoordsPtr->getSize());

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
            for(Int32 i = 0; i <= piN; i++)
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
                for(Int32 i = 0; i < piN; i++)
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
                    FWARNING(("Not enough normal index (%"PRISize",%d)\n", 
                              normalIndex.size(), piN));
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
                for(Int32 i = 0; i < piN; i++)
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
                    FWARNING(("Not enough color index (%"PRISize",%d)\n", 
                              colorIndex.size(), piN));
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
            for(Int32 i = 0; i < piN; i++)
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
                FWARNING(("Not enough texCoord index (%"PRISize",%d)\n", 
                          texCoordIndex.size(), piN));
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

    if(posIndexPtr == NULL)
    {
        posIndexPtr = GeoUInt32Property::create();
    }
    else
    {
        posIndexPtr->clear();
    }

    for(Int32 i = 1; i < 4; ++i)
    { 
        indexOutBag[i] = geoPtr->getIndex(indexOutBagID[i]);
        
        if(indexOutBag[i] != NULL)
        {
            indexOutBag[i]->clear();
        }
    }

    for(UInt32 i = 0; i < uiNumTexCoords; ++i)
    {
        geoPtr->setIndex(NULL, texCoordIdx[i]);
    }

    lensPtr = geoPtr->getLengths();

    if(lensPtr == NULL)
    {
        lensPtr = GeoUInt32Property::create();
    }
    else
    {
        lensPtr->clear();
    }

    geoTypePtr = geoPtr->getTypes();

    if(geoTypePtr == NULL)
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

            for(Int32 i = 0; i <= piN; i++)
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
                                    if(indexOutBag[typei] == NULL)
                                    {
                                        indexOutBag[typei] = 
                                            GeoUInt32Property::create();
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
           (indexOutBag[i] == NULL          || indexOutBag[i]->size() == 0            )   )
        {
            geoPtr->setIndex(posIndexPtr, indexOutBagID[i]);
        }
        else if(indexOutBag[i] != NULL && indexOutBag[i]->size() != 0)
        {
            geoPtr->setIndex(indexOutBag[i], indexOutBagID[i]);
        }
        else if(indexOutBag[i] != NULL && indexOutBag[i]->size() == 0)
        {
            geoPtr->setIndex(NULL, indexOutBagID[i]);
        }
    }

    for(UInt32 i = 1; i < uiNumTexCoords; ++i)
    {
        if(texCoordN[i] != 0)
        {
            if((indexType  [3] == VERTEX_COORD_IT || 
                indexType  [3] == VERTEX_DUP_IT) &&
               (indexOutBag[3] == NULL            || 
                indexOutBag[3]->size() == 0            )   )
            {
                geoPtr->setIndex(posIndexPtr, texCoordIdx[i]);
            }
            else if(indexOutBag[3] != NULL && indexOutBag[3]->size() != 0)
            {
                geoPtr->setIndex(indexOutBag[3], texCoordIdx[i]);
            }
        }
    }

    
    for(UInt32 i = 1; i < 4; ++i)
    {
        indexOutBag[i] = NULL;
    }

    return triCount;
}

/*! \ingroup GrpDrawablesGeometryUtils
 */
Int32 createOptimizedPrimitives(Geometry *geo,
                                UInt32    iteration,
                                bool      createStrips,
                                bool      createFans,
                                UInt32    minFanEdgeCount,
                                bool      colorCode,
                                bool      stitchStrips   )
{
    if (geo == NULL)
    {
        return 0;
    }

    StriperHalfEdgeGraph graph;

    UInt32 cost            = 0;
    UInt32 startCost       = 0;
    UInt32 bestCost        = 0;
    UInt32 worstCost       = 0;
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

    GeoVectorProperty *posPtr = geo->getPositions();

    UInt32 pN = ((posPtr == NULL) ? 0 : posPtr->getSize());

    GeoIntegralProperty *posIndexPtr = 
        geo->getIndex(Geometry::PositionsIndex);

    // Calculate startCost.
    if(posIndexPtr == NULL)
    {
        startCost = pN;
    }
    else
    {
        startCost = posIndexPtr->size();
    }

    // Leave early if we have no indices or positions.
    if (pN == 0 || posIndexPtr == NULL)
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

                for(UInt32 j = 0; j < indexMapSize; j++)
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
        GeoIntegralPropertyUnrecPtr lensPtr;
        GeoIntegralPropertyUnrecPtr geoTypePtr;

        // check/create the indexPtr/lengthsPtr/geoTypePtr

        lensPtr = geo->getLengths();

        if(lensPtr == NULL)
        {
            lensPtr = OSG::GeoUInt32Property::create();

            geo->setLengths(lensPtr);
        }

        geoTypePtr = geo->getTypes();

        if(geoTypePtr == NULL)
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
                                for(UInt32 j = 0; j < 1+windingCorrection; ++j)
                                {
                                    for(UInt32 k = 0; k < indexMapSize; ++k)
                                    {
                                        oGeoIndexBag[k].first->push_back(
                                            indexDic.entry(
                                                lastTriStripIndex)[k]);
                                    }
                                }
                                for(UInt32 k = 0; k < indexMapSize; ++k)
                                {
                                    oGeoIndexBag[k].first->push_back(
                                        indexDic.entry(primIndex[i][0])[k]);
                                }
                            }
                            else
                            {
                                for(UInt32 j = 0; j < 1+windingCorrection; ++j)
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
                        for(UInt32 k = 0; k < indexMapSize; ++k)
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

/*! \ingroup GrpDrawablesGeometryUtils
 */

void createConvexPrimitives(Geometry *geo)
{
    FFATAL(("createConvexPrimitives:: NYI!\n"));
}

/*! Adjusts the indices of \a geoPtr such that data is as much as possible
    reused.

    \ingroup GrpDrawablesGeometryUtils
 */
Int32 createSharedIndex(Geometry *geoPtr)
{
    UInt32 indexSharedCount = 0, dataRemapCount = 0, indexRemapCount = 0;
    UInt32 iN, index, si, sN;
    UInt32 indexBlock = 0, masterDSize;

    GeoVectorProperty *masterProp = NULL, *slaveProp = NULL;

    const UInt8 *masterData;

    std::vector<UInt32       > slaveDSizeVec;
    std::vector<const UInt8 *> slaveDataVec;

    // data pointer and size pair
    typedef std::pair<const UInt8 *, UInt32> Mem;

    Mem masterMem;

    std::map<Mem, UInt32, memless<Mem> >           memMap;
    std::map<Mem, UInt32, memless<Mem> >::iterator mmI;

    GeoIntegralProperty *indexPtr;

    const UChar8 *dataElem;

    std::vector < Int32 > indexRemap;

    Geometry::IndexBag indexBag;

    if(geoPtr != NULL)
    {
        if(geoPtr->getPositions() != NULL)
        {
            // check/create indexPtr
            iN = geoPtr->getPositions()->size();

            indexBag = geoPtr->getUniqueIndexBag();

            if(indexBag.size() == 0)
            {
#if 0
                indexPtr = GeoIndicesUI32::create();
                indexPtr->resize(iN);

                for(i = 0; i < iN; i++)
                    indexPtr->setValue(i, i);

                beginEditCP(geoPtr);
                {
                    geoPtr->setIndices(indexPtr);
                }

                endEditCP(geoPtr);
#else
                FNOTICE(("non indexed geo not handled in createSharedIndex()\n"));
                return 0;
#endif
            }
        }
        else
        {
            FNOTICE(("Invalid geoPtr->getPositions() in createSharedIndex()\n"));
            return 0;
        }
    }
    else
    {
        FNOTICE(("Invalid geoPtr in createSharedIndex()\n"));
        return 0;
    }


    // reset stat counter
    indexSharedCount = 0;
    dataRemapCount   = 0;
    indexRemapCount  = 0;
    
    // iterator over all index properties
    for(UInt32 i = 0; i < indexBag.size(); ++i)
    {
        // first property indexed by index i is the master property
        masterProp = geoPtr->getProperty(indexBag[i].second[0]);
        masterData = masterProp->getData();

        if(masterProp != NULL && masterData != NULL)
        {
            // calc master data element size
            masterDSize = 
                masterProp->getFormatSize() *
                masterProp->getDimension () +
                masterProp->getStride    ();

            // all other properties indexed by index i are slave properties
            // find and store slave property data and sizes
            slaveDataVec .clear();
            slaveDSizeVec.clear();

            // store pointers to data and sizes of slave properties
            for(UInt32 j = 1; j < indexBag[i].second.size(); ++j)
            {
                slaveProp = geoPtr->getProperty(indexBag[i].second[j]);
                
                // there may be no property to the index
                if(slaveProp == NULL)
                    continue;
                
                if(slaveProp->getData() != NULL)
                {
                    slaveDataVec .push_back(slaveProp->getData      ()  );
                    slaveDSizeVec.push_back(slaveProp->getFormatSize() *
                                            slaveProp->getDimension ()  );
                }
                else
                {
                    FWARNING(("createSharedIndex: slaveProp %d has no data!\n", 
                              indexBag[i].second[j]));
                }
            }

            indexPtr = indexBag[i].first;       // index i  

            sN       = slaveDataVec. size();    // number of slave properties
            iN       = indexPtr    ->size();    // number of indices

            memMap.clear();

            indexRemap.clear();
            indexRemap.resize(masterProp->size(), -1);

            masterMem.second = 
                masterProp->getFormatSize() * masterProp->getDimension();

            for(UInt32 j = 0; j < iN; ++j)
            {
                index = indexPtr->getValue(j);

                if(indexRemap[index] >= 0)
                {
                    if(indexRemap[index] == Int32(index))
                    {
                        indexSharedCount++;
                    }
                    else
                    {
                        indexPtr->setValue(indexRemap[index], j);
                        indexRemapCount++;
                    }
                }
                else
                {
                    // find/include the data block
                    dataElem = masterData + (index * masterDSize);

                    masterMem.first = dataElem;

                    mmI = memMap.find(masterMem);

                    if(mmI == memMap.end())
                    {
                        // index not found; store new data/index
                        memMap    [masterMem] = index;
                        indexRemap[index    ] = index;
                    }
                    else
                    {
                        // data found; check slave property
                        for(si = 0; si < sN; si++)
                        {
                            if(memcmp(slaveDataVec[si] + (index       * slaveDSizeVec[si]),
                                      slaveDataVec[si] + (mmI->second * slaveDSizeVec[si]),
                                      slaveDSizeVec[si]))
                                break;
                        }
                        
                        if(si == sN)
                        {
                            // no or valid slave data; remap the index
                            indexPtr->setValue(mmI->second, j);

                            indexRemap[index] = mmI->second;
                            dataRemapCount++;
                        }
                        else
                        {
                            // invalid slave data; cannot remap index
                            indexRemap[index] = index;
                        }
                    }
                }
            }
        }
        else
        {
            FWARNING(("Invalid masterProp %p, block: %d\n",
                      masterProp, indexBlock));
        }
        
        FINFO(("Create sharedIndex: %d pass; "
               "data/index remap: %d/%d \n",
               indexBlock, dataRemapCount,
               indexRemapCount));
    }

    return indexRemapCount + dataRemapCount;
}

Int32 createSingleIndex(Geometry *geo)
{
    FFATAL(("createSingleIndex:: NYI!\n"));
    return -1;
}


/*! \ingroup GrpDrawablesGeometryUtils

  Calculate some basic statistics of the Geometry. 
 */
UInt32 calcPrimitiveCount(Geometry *geo,
                          UInt32   &triangle,
                          UInt32   &line,
                          UInt32   &point)
{
    GeoIntegralProperty *geoTypePtr;
    GeoIntegralProperty *lensPtr;

    UInt32 lN, tN, len, type;

    // TODO; should we really reset the values ?
    triangle = line = point = 0;

    if(geo == NULL)
    {
        FINFO(("No geo in calcPrimitiveCount\n"));
        return 0;
    }

    lensPtr = geo->getLengths();

    lN = (lensPtr == NULL) ? 0 : lensPtr->getSize();
    
    
    geoTypePtr = geo->getTypes();

    tN = (geoTypePtr == NULL) ? 0 : geoTypePtr->getSize();

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
            GeoVectorProperty *pos = geo->getPositions();
            
            if(pos == NULL)
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

/*! \ingroup GrpDrawablesGeometryUtils

  Create a geometry of the vertex normals of the object. Useful for Visualizing
  the normals. 

  \warning It does not check whether the normals are actually vertex normals,
  it just uses them as if.

 */
NodeTransitPtr calcVertexNormalsGeo(Geometry *geo, 
                                    Real32    length)
{
    GeoPnt3fPropertyUnrecPtr pnts = GeoPnt3fProperty::create();

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

    GeoIntegralPropertyUnrecPtr type = GeoUInt8Property::create();

    type->push_back(GL_LINES);

    GeoIntegralPropertyUnrecPtr lens = GeoUInt32Property::create();

    lens->push_back(pnts->getSize());

    GeometryUnrecPtr g = Geometry::create();

    g->setTypes    (type                     );
    g->setLengths  (lens                     );
    g->setPositions(pnts                     );
    g->setMaterial (getDefaultUnlitMaterial());

    return makeNodeFor(g);
}

/*! \ingroup GrpDrawablesGeometryUtils
 */
void updateVertexNormalsGeo(      Geometry *pGeo, 
                                  Real32    length,
                            const Geometry *pRefGeo)
{
    GeoPnt3fProperty *pnts = 
        dynamic_cast<GeoPnt3fProperty *>(
            pGeo->getProperty(Geometry::PositionsIndex));

    GeoIntegralProperty *type = pGeo->getTypes();
    GeoIntegralProperty *lens = pGeo->getLengths();

    if(pnts == NULL || type == NULL || lens == NULL)
        return;

    pnts->clear();
    type->clear();
    lens->clear();

    // calculate

    PrimitiveIterator pi(pRefGeo);

    if(1 /* no easy way to check right now */ )
    {
        for(pi  = pRefGeo->beginPrimitives(); 
            pi != pRefGeo->endPrimitives  (); ++pi)
        {
            for(UInt32 k = 0; k < pi.getLength(); k++)
            {
                pnts->push_back(pi.getPosition(k));
                pnts->push_back(pi.getPosition(k) + length * pi.getNormal(k));
            }
        }
    }

    type->push_back(GL_LINES);

    lens->push_back(pnts->getSize());
}


/*! \ingroup GrpDrawablesGeometryUtils

  Create a geometry of the face normals of the object. Useful for Visualizing
  the normals. 

  \warning It does not check whether the normals are actually face normals,
  it just uses them as if.

 */
NodeTransitPtr calcFaceNormalsGeo(Geometry *geo, 
                                  Real32    length)
{
    NodeTransitPtr            p     = Node::create();
    GeometryUnrecPtr          g     = Geometry::create();
    GeoPnt3fPropertyUnrecPtr  pnts  = GeoPnt3fProperty::create();
    GeoUInt32PropertyUnrecPtr index = GeoUInt32Property::create();
    GeoUInt8PropertyUnrecPtr  type  = GeoUInt8Property::create();
    GeoUInt32PropertyUnrecPtr lens  = GeoUInt32Property::create();

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

    g->setTypes    (type                     );
    g->setLengths  (lens                     );
    g->setIndices  (index                    );
    g->setPositions(pnts                     );
    g->setMaterial (getDefaultUnlitMaterial());

    p->setCore(g);

    return p;
}

/*! \ingroup GrpDrawablesGeometryUtils
 */
void separateProperties(Geometry *geo)
{
    FFATAL(("separateProperties: not implemented yet!\n"));
}


/*! \ingroup GrpDrawablesGeometryUtils
 */
void mergeGeometries(std::vector<Node *> &nodes,
                     std::vector<Node *> &results)
{
    FFATAL(("mergeGeometries: not implemented yet!\n"));
}



namespace
{
    // this anonymous namespace contains functions that are implementation
    // details for geometry merging

/*! Returns the format to be used when merging a property of \a format1 with
    one of \a format2.
 */
UInt32 calcMergeFormat(UInt32 format1, UInt32 format2)
{
    UInt32 format = GL_BYTE ;

    switch(format1)
    {
    case GL_BYTE:
        switch(format2)
        {
        case GL_BYTE:           format = GL_BYTE;           break;
        case GL_UNSIGNED_BYTE:  format = GL_SHORT;          break;
        case GL_SHORT:          format = GL_SHORT;          break;
        case GL_UNSIGNED_SHORT: format = GL_INT;            break;
        case GL_INT:            format = GL_INT;            break;
        case GL_UNSIGNED_INT:   format = GL_INT;            break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        
        }
    break;
    
    case GL_UNSIGNED_BYTE:
        switch(format2)
        {
        case GL_BYTE:           format = GL_SHORT;          break;
        case GL_UNSIGNED_BYTE:  format = GL_UNSIGNED_BYTE;  break;
        case GL_SHORT:          format = GL_SHORT;          break;
        case GL_UNSIGNED_SHORT: format = GL_UNSIGNED_SHORT; break;
        case GL_INT:            format = GL_INT;            break;
        case GL_UNSIGNED_INT:   format = GL_UNSIGNED_INT;   break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;
    
    case GL_SHORT:
        switch(format2)
        {
        case GL_BYTE:           format = GL_SHORT;          break;
        case GL_UNSIGNED_BYTE:  format = GL_SHORT;          break;
        case GL_SHORT:          format = GL_SHORT;          break;
        case GL_UNSIGNED_SHORT: format = GL_INT;            break;
        case GL_INT:            format = GL_INT;            break;
        case GL_UNSIGNED_INT:   format = GL_INT;            break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;
    
    case GL_UNSIGNED_SHORT:
        switch(format2)
        {
        case GL_BYTE:           format = GL_INT;            break;
        case GL_UNSIGNED_BYTE:  format = GL_UNSIGNED_SHORT; break;
        case GL_SHORT:          format = GL_INT;            break;
        case GL_UNSIGNED_SHORT: format = GL_UNSIGNED_SHORT; break;
        case GL_INT:            format = GL_INT;            break;
        case GL_UNSIGNED_INT:   format = GL_UNSIGNED_INT;   break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;
    
    case GL_INT:
        switch(format2)
        {
        case GL_BYTE:           format = GL_INT;            break;
        case GL_UNSIGNED_BYTE:  format = GL_INT;            break;
        case GL_SHORT:          format = GL_INT;            break;
        case GL_UNSIGNED_SHORT: format = GL_INT;            break;
        case GL_INT:            format = GL_INT;            break;
        case GL_UNSIGNED_INT:   format = GL_INT;            break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;
    
    case GL_UNSIGNED_INT:
        switch(format2)
        {
        case GL_BYTE:           format = GL_INT;            break;
        case GL_UNSIGNED_BYTE:  format = GL_UNSIGNED_INT;   break;
        case GL_SHORT:          format = GL_INT;            break;
        case GL_UNSIGNED_SHORT: format = GL_UNSIGNED_INT;   break;
        case GL_INT:            format = GL_INT;            break;
        case GL_UNSIGNED_INT:   format = GL_UNSIGNED_INT;   break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;
    
    case GL_FLOAT:
        switch(format2)
        {
        case GL_BYTE:           format = GL_FLOAT;          break;
        case GL_UNSIGNED_BYTE:  format = GL_FLOAT;          break;
        case GL_SHORT:          format = GL_FLOAT;          break;
        case GL_UNSIGNED_SHORT: format = GL_FLOAT;          break;
        case GL_INT:            format = GL_FLOAT;          break;
        case GL_UNSIGNED_INT:   format = GL_FLOAT;          break;
        
        case GL_FLOAT:          format = GL_FLOAT;          break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;
    
    case GL_DOUBLE:
        switch(format2)
        {
        case GL_BYTE:           format = GL_DOUBLE;         break;
        case GL_UNSIGNED_BYTE:  format = GL_DOUBLE;         break;
        case GL_SHORT:          format = GL_DOUBLE;         break;
        case GL_UNSIGNED_SHORT: format = GL_DOUBLE;         break;
        case GL_INT:            format = GL_DOUBLE;         break;
        case GL_UNSIGNED_INT:   format = GL_DOUBLE;         break;
        
        case GL_FLOAT:          format = GL_DOUBLE;         break;
        case GL_DOUBLE:         format = GL_DOUBLE;         break;
        }
    break;   
    }
    
    return format;
}

/*! Determines a format to store the combination of \a prop1 and \a prop2.
    If \a combineValues is \c true the contents are scanned to ensure the
    determined format can store the sum of the largest entries.
 */
void calcMergePropertyType(
    const GeoIntegralProperty *prop1,
    const GeoIntegralProperty *prop2,
          bool                 combineValues,
          UInt32              &format        )
{
    UInt32 form1 = prop1->getFormat();
    UInt32 form2 = prop2->getFormat();
    
    format = calcMergeFormat(form1, form2);
    
    if(combineValues && format != GL_INT && format != GL_UNSIGNED_INT)
    {
        Int64 max1 = TypeTraits<Int64>::getMin();
        Int64 max2 = TypeTraits<Int64>::getMin();
        
        for(UInt32 i = 0; i < prop1->size(); ++i)
        {
            if(max1 < prop1->getValue<Int64>(i))
                max1 = prop1->getValue<Int64>(i);
        }
        
        for(UInt32 i = 0; i < prop2->size(); ++i)
        {
            if(max2 < prop2->getValue<Int64>(i))
                max2 = prop2->getValue<Int64>(i);
        }
        
        if(format        == GL_BYTE                   && 
           (max1 + max2) >  TypeTraits<Int8>::getMax()  )
        {
            format = GL_SHORT;
        }
        else if(format        == GL_UNSIGNED_BYTE           &&
                (max1 + max2) >  TypeTraits<UInt8>::getMax()  )
        {
            format = GL_UNSIGNED_SHORT;
        }
        else if(format        == GL_SHORT                   &&
                (max1 + max2) >  TypeTraits<Int16>::getMax()  )
        {
            format = GL_INT;
        }
        else if(format        == GL_UNSIGNED_SHORT           &&
                (max1 + max2) >  TypeTraits<UInt16>::getMax()  )
        {
            format = GL_UNSIGNED_INT;
        }
    }
}

/*! Determines a format to store the combination of \a prop1 and \a prop2.
 */
void calcMergePropertyType(
    const GeoVectorProperty *prop1, 
    const GeoVectorProperty *prop2,
          UInt32            &format,  UInt32 &dim,
          UInt32            &vecType, UInt32 &normalize)
{
    UInt32 dim1       = prop1->getDimension ();
    UInt32 dim2       = prop2->getDimension ();
    UInt32 form1      = prop1->getFormat    ();
    UInt32 form2      = prop2->getFormat    ();
    UInt32 vecType1   = prop1->getVectorType();
    UInt32 vecType2   = prop2->getVectorType();
    bool   normalize1 = prop1->getNormalize ();
    bool   normalize2 = prop2->getNormalize ();
    
    format = calcMergeFormat(form1, form2);
    dim    = osgMax         (dim1,  dim2 );
    
    if(vecType1 != vecType2)
    {
        FWARNING(("calcMergePropertyType: Can not merge properties with "
                  "conflicting vecTypes.\n"));
    }
    else
    {
        vecType = vecType1;
    }
    
    if(normalize1 != normalize2)
    {
        FWARNING(("calcMergePropertyType: Can not merge normalizing and "
                  "non-normalizing property.\n"));
    }
    else
    {
        normalize = normalize1;
    }
}

/*! Merges integral properties by appending \a src1Prop and \a src2Prop to a
    new property.
    \note It is intended to merge the types and length properties.
 */
GeoIntegralPropertyTransitPtr mergeIntegralProp(
    const GeoIntegralProperty *src1Prop,
    const GeoIntegralProperty *src2Prop )
{
    GeoIntegralPropertyTransitPtr dstProp;
    UInt32                        dstFormat;
    
    calcMergePropertyType(src1Prop, src2Prop, false, dstFormat);
    dstProp = GeoPropertyFactory::the()->create(dstFormat);
    
    UInt32 szSrc1 = src1Prop->size();
    UInt32 szSrc2 = src2Prop->size();

    // TODO: Optimize for matching src and dst types by not using generic interface
    for(UInt32 i = 0; i < szSrc1; ++i)
        dstProp->addValue(src1Prop->getValue(i));
        
    for(UInt32 i = 0; i < szSrc2; ++i)
        dstProp->addValue(src2Prop->getValue(i));
    
    return dstProp;
}

class IndexMap
{
  public:
    UInt32 get(UInt32 idx            ) const;
    void   set(UInt32 idx, UInt32 val);

  private:
    typedef std::vector<UInt32> IMap;
    
    IMap _iMap;
};

inline
UInt32 IndexMap::get(UInt32 idx) const
{
    UInt32 returnValue;

    if(idx >= _iMap.size())
        returnValue = TypeTraits<UInt32>::getMax();
    else
        returnValue = _iMap[idx];
        
    return returnValue;
}

inline
void IndexMap::set(UInt32 idx, UInt32 val)
{
    if(idx >= _iMap.size())
        _iMap.resize(idx + 1, TypeTraits<UInt32>::getMax());
        
    _iMap[idx] = val;
}


/*! Copies and rewrites the index \a srcIdx to \a dstIdx storing the mapping
    between old and new indices in \a idxMap.
    This function must be called with a correct type argument.
    
    \warning \a dstIdx is expected to have sufficient storage allocated.
 */
template <class DescTypeT> inline
void copyIndex(      GeoIntegralProperty *dstIdx,
               const GeoIntegralProperty *srcIdx,
                     UInt32               srcSz,
                     IndexMap            &idxMap,
                     UInt32              &offset,
                     UInt32               dstOffset)
{
    typedef          TypedGeoIntegralProperty<DescTypeT> TypedProp;
    typedef typename TypedProp::StoredType               StoredType;
    typedef typename TypedProp::StoredFieldType          StoredField;
    
          TypedProp   *typedDst = dynamic_cast<      TypedProp *>(dstIdx);
    const TypedProp   *typedSrc = dynamic_cast<const TypedProp *>(srcIdx);
          StoredField &dstF     = typedDst->editField();
    const StoredField &srcF     = typedSrc->getField ();
    
    for(UInt32 i = 0; i < srcSz; ++i)
    {
        StoredType si = srcF[i];
        UInt32     di = idxMap.get(si);

        if(di == TypeTraits<UInt32>::getMax())
        {
            di = offset++;
            idxMap.set(si, di);
        }
        
        dstF[i + dstOffset] = di;
    }
}


/*! Copies and rewrites the index \a srcIdx to \a dstIdx storing the mapping
    between old and new indices in \a idxMap.
    
    \warning \a dstIdx is expected to have sufficient storage allocated.
 */
inline
void copyIndex(      GeoIntegralProperty *dstIdx,
               const GeoIntegralProperty *srcIdx,
                     UInt32               srcSz,
                     IndexMap            &idxMap,
                     UInt32              &offset,
                     UInt32               dstOffset)
{
    UInt32 dstFormat = dstIdx->getFormat();
    UInt32 srcFormat = srcIdx->getFormat();

    if(dstFormat == srcFormat)
    {
        // if the types are equal, use more efficient copying
    
        switch(srcFormat)
        {
        case GL_UNSIGNED_BYTE:
            copyIndex<GeoUInt8PropertyDesc>(
                dstIdx, srcIdx, srcSz, idxMap, offset, dstOffset);
        break;
        
        case GL_UNSIGNED_SHORT:
            copyIndex<GeoUInt16PropertyDesc>(
                dstIdx, srcIdx, srcSz, idxMap, offset, dstOffset);
        break;
        
        case GL_UNSIGNED_INT:
            copyIndex<GeoUInt32PropertyDesc>(
                dstIdx, srcIdx, srcSz, idxMap, offset, dstOffset);
        break;
        }
        
    }
    else
    {
        // fallback to using the generic interface
    
        typedef GeoIntegralProperty::MaxTypeT IndexType;
    
        for(UInt32 i = 0; i < srcSz; ++i)
        {
            IndexType si = srcIdx->getValue<IndexType>(i);
            IndexType di = idxMap.get(si);
            
            if(di == TypeTraits<UInt32>::getMax())
            {
                di = offset++;
                idxMap.set(si, di);
            }
            
            dstIdx->setValue(di, i + dstOffset);
        }
    }
}

/*! Copies from \a srcProp to \a dstProp the first srcSz values and stores them
    at positions starting at \a dstOffset.
    This function must be called with a correct type argument.
    
    \warning \a dstProp is expected to have sufficient storage allocated.
 */
template <class DescTypeT> inline
void copyIntegral(      GeoIntegralProperty *dstProp,
                  const GeoIntegralProperty *srcProp,
                        UInt32               srcSz,
                        UInt32               dstOffset)
{
    typedef          TypedGeoIntegralProperty<DescTypeT> TypedProp;
    typedef typename TypedProp::StoredFieldType          StoredField;
    
          TypedProp   *typedDst = dynamic_cast<      TypedProp *>(dstProp);
    const TypedProp   *typedSrc = dynamic_cast<const TypedProp *>(srcProp);
          StoredField &dstF     = typedDst->editField();
    const StoredField &srcF     = typedSrc->getField ();
    
    for(UInt32 i = 0; i < srcSz; ++i)
        dstF[dstOffset + i] = srcF[i];
}

/*! Copies from \a srcProp to \a dstProp the first srcSz values and stores them
    at positions starting at \a dstOffset.
    
    \warning \a dstProp is expected to have sufficient storage allocated.
 */
inline
void copyIntegral(      GeoIntegralProperty *dstProp,
                  const GeoIntegralProperty *srcProp,
                        UInt32               srcSz,
                        UInt32               dstOffset)
{
    UInt32 dstFormat = dstProp->getFormat();
    UInt32 srcFormat = srcProp->getFormat();

    if(dstFormat == srcFormat)
    {
        // if the types are equal, use more efficient copying
    
        switch(srcFormat)
        {
        case GL_UNSIGNED_BYTE:
            copyIntegral<GeoUInt8PropertyDesc>(
                dstProp, srcProp, srcSz, dstOffset);
        break;
        
        case GL_UNSIGNED_SHORT:
            copyIntegral<GeoUInt16PropertyDesc>(
                dstProp, srcProp, srcSz, dstOffset);
        break;
        
        case GL_UNSIGNED_INT:
            copyIntegral<GeoUInt32PropertyDesc>(
                dstProp, srcProp, srcSz, dstOffset);
        break;
        }
    }
    else
    {
        // fallback to using the generic interface

        typedef GeoIntegralProperty::MaxTypeT ValueType;
    
        for(UInt32 i = 0; i < srcSz; ++i)
            dstProp->setValue(srcProp->getValue<ValueType>(i), dstOffset + i);
    }
}

template <class DescTypeT> inline
void copyVectorMapped(      GeoVectorProperty   *dstProp, 
                      const GeoVectorProperty   *srcProp,
                      const GeoIntegralProperty *srcIdx,
                            UInt32               srcSz,
                      const IndexMap            &idxMap  )
{
    typedef          GeoIntegralProperty::MaxTypeT     IndexType;
    typedef          TypedGeoVectorProperty<DescTypeT> TypedProp;
    typedef typename TypedProp::StoredType             StoredType;
    typedef typename TypedProp::StoredFieldType        StoredField;
    
          TypedProp   *typedDst = dynamic_cast<      TypedProp *>(dstProp);
    const TypedProp   *typedSrc = dynamic_cast<const TypedProp *>(srcProp);
          StoredField &dstF     = typedDst->editField();
    const StoredField &srcF     = typedSrc->getField ();
    
    for(UInt32 i = 0; i < srcSz; ++i)
    {
        IndexType si = srcIdx->getValue<IndexType>(i);
        IndexType di = idxMap .get(si);
        
        dstF[di] = srcF[si];
    }
}

/*! Copies from \a srcProp to \a dstProp values indexed by the first \a srcSz
    indices from \a srcIdx. The values are stored at the positions indicated
    by \a idxMap.
    
    \warning \a dstProp is expected to have sufficient storage allocated.
 */
inline
void copyVectorMapped(      GeoVectorProperty   *dstProp, 
                      const GeoVectorProperty   *srcProp,
                      const GeoIntegralProperty *srcIdx,
                            UInt32               srcSz,
                      const IndexMap            &idxMap  )
{
    UInt32 dstFormat  = dstProp->getFormat    ();
    UInt32 dstDim     = dstProp->getDimension ();
    UInt32 dstVecType = dstProp->getVectorType();
    
    UInt32 srcFormat  = srcProp->getFormat    ();
    UInt32 srcDim     = srcProp->getDimension ();
    UInt32 srcVecType = srcProp->getVectorType();

    if(dstFormat == srcFormat && dstFormat == GL_FLOAT)
    {
        if(dstVecType == srcVecType &&
           dstVecType == GeoProperty::VectorTypePoint)
        {
            if(dstDim == srcDim && dstDim == 1)
            {
                copyVectorMapped<GeoPnt1fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
            else if(dstDim == srcDim && dstDim == 2)
            {
                copyVectorMapped<GeoPnt2fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
            else if(dstDim == srcDim && dstDim == 3)
            {
                copyVectorMapped<GeoPnt3fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
            else if(dstDim == srcDim && dstDim == 4)
            {
                copyVectorMapped<GeoPnt4fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
        }
        else if(dstVecType == srcVecType &&
                dstVecType == GeoProperty::VectorTypeVector)
        {
            if(dstDim == srcDim && dstDim == 1)
            {
                copyVectorMapped<GeoVec1fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
            else if(dstDim == srcDim && dstDim == 2)
            {
                copyVectorMapped<GeoVec2fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
            else if(dstDim == srcDim && dstDim == 3)
            {
                copyVectorMapped<GeoVec3fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
            else if(dstDim == srcDim && dstDim == 4)
            {
                copyVectorMapped<GeoVec4fPropertyDesc>(
                    dstProp, srcProp, srcIdx, srcSz, idxMap);
                return;
            }
        }
    }
    
    // if we get to this point: fallback to using the generic interface
    
    typedef GeoIntegralProperty::MaxTypeT IndexType;
    typedef GeoVectorProperty  ::MaxTypeT ValueType;
    
    for(UInt32 i = 0; i < srcSz; ++i)
    {
        IndexType si = srcIdx->getValue<IndexType>(i);
        IndexType di = idxMap .get(si);
        
        dstProp->setValue(srcProp->getValue<ValueType>(si), di);
    }
}

// TODO: Optimize copyVector like the above.

/*! Copies from \a srcProp to \a dstProp the first \a srcSz values and stores
    them at positions starting at \a dstOffset.

    \warning \a dstProp is expected to have sufficient storage allocated.
 */
inline
void copyVector(      GeoVectorProperty *dstProp,
                const GeoVectorProperty *srcProp,
                      UInt32             srcSz,
                      UInt32             dstOffset)
{
    // fallback to using the generic interface

    typedef GeoVectorProperty::MaxTypeT ValueType;

    for(UInt32 i = 0; i < srcSz; ++i)
        dstProp->setValue(srcProp->getValue<ValueType>(i), dstOffset + i);
}

void mergeGeoTypes(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    GeoIntegralPropertyUnrecPtr dstTypes;
    UInt32                      dstFormat;

    calcMergePropertyType(srcGeo1->getSFTypes()->getValue(),
                          srcGeo2->getSFTypes()->getValue(), false, dstFormat);
    dstTypes = GeoPropertyFactory::the()->create(dstFormat);
    
    UInt32 src1Sz = srcGeo1->getSFTypes()->getValue()->size();
    UInt32 src2Sz = srcGeo2->getSFTypes()->getValue()->size();
    
    dstTypes->resize(src1Sz + src2Sz);
    
    copyIntegral(dstTypes, srcGeo1->getSFTypes()->getValue(), src1Sz, 0     );
    copyIntegral(dstTypes, srcGeo2->getSFTypes()->getValue(), src2Sz, src1Sz);
    
    dstGeo->setTypes(dstTypes);
}

void mergeGeoLengths(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    GeoIntegralPropertyUnrecPtr dstLengths;
    UInt32                      dstFormat;
    
    calcMergePropertyType(srcGeo1->getSFLengths()->getValue(),
                          srcGeo2->getSFLengths()->getValue(), false, dstFormat);
    dstLengths = GeoPropertyFactory::the()->create(dstFormat);
    
    UInt32 src1Sz = srcGeo1->getSFLengths()->getValue()->size();
    UInt32 src2Sz = srcGeo2->getSFLengths()->getValue()->size();
    
    dstLengths->resize(src1Sz + src2Sz);
    
    copyIntegral(dstLengths, srcGeo1->getSFLengths()->getValue(), src1Sz, 0     );
    copyIntegral(dstLengths, srcGeo2->getSFLengths()->getValue(), src2Sz, src1Sz);
    
    dstGeo->setLengths(dstLengths);
}

// The following functions are implementing merges between all different 
// indexing variants for geometries.
// The last four letters indicate the indexing that is assumed for the
// arguments. NI - non indexed, SI - single indexed, MI - multi indexed


/*! Merge geometry \a srcGeo1 and \a srcGeo2 into \a dstGeo, assuming they have
    the same set of properties and both are unindexed.
 */
void mergeGeoNINI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    FDEBUG(("mergeGeoNINI: srcGeo1 [%p] srcGeo2 [%p]\n", srcGeo1, srcGeo2));
    
    mergeGeoTypes  (dstGeo, srcGeo1, srcGeo2);
    mergeGeoLengths(dstGeo, srcGeo1, srcGeo2);
                          
    // count number of _used_ property elements                      
    UInt32 src1Used = 0;
    UInt32 src2Used = 0;
    
    for(UInt32 i = 0; i < srcGeo1->getSFLengths()->getValue()->size(); ++i)
        src1Used += srcGeo1->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    for(UInt32 i = 0; i < srcGeo2->getSFLengths()->getValue()->size(); ++i)
        src2Used += srcGeo2->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    const Geometry::MFPropertiesType  *src1PropF = srcGeo1->getMFProperties ();
    const Geometry::MFPropertiesType  *src2PropF = srcGeo2->getMFProperties ();
    
    UInt32 szProp = osgMin(src1PropF->size(), src2PropF->size());
    
    for(UInt32 i = 0; i < szProp; ++i)
    {
        const GeoVectorProperty *src1Prop = (*src1PropF)[i];
        const GeoVectorProperty *src2Prop = (*src2PropF)[i];
        
        FFASSERT(!((src1Prop != NULL) ^ (src2Prop != NULL)), 1,
                 ("mergeGeoNINI: Inconsistent properties!\n");)
        
        if(src1Prop == NULL || src2Prop == NULL)
            continue;
    
        UInt32 dstFormat;
        UInt32 dstDim;
        UInt32 dstVecType;
        UInt32 dstNorm;
        
        calcMergePropertyType(src1Prop, src2Prop,
                              dstFormat, dstDim, dstVecType, dstNorm);
        GeoVectorPropertyUnrecPtr dstProp =
            GeoPropertyFactory::the()->create(dstFormat,  dstDim,
                                              dstVecType, dstNorm != 0);
        
        dstProp->resize(src1Used + src2Used);
        
        copyVector(dstProp, src1Prop, src1Used, 0       );
        copyVector(dstProp, src2Prop, src2Used, src1Used);
                    
        dstGeo->setProperty(dstProp, i);
    }
    
}

/*! Merge geometry \a srcGeo1 and \a srcGeo2 into \a dstGeo, assuming they have
    the same set of properties and \a srcGeo1 is not indexed, \a srcGeo2 is
    single indexed. The result \a dstGeo will be single indexed.
 */
void mergeGeoNISI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    FDEBUG(("mergeGeoNISI: srcGeo1 [%p] srcGeo2 [%p]\n", srcGeo1, srcGeo2));
    
    typedef GeoVectorProperty::MaxTypeT ValueType;

    // 1. merge types and lengths
    mergeGeoTypes  (dstGeo, srcGeo1, srcGeo2);
    mergeGeoLengths(dstGeo, srcGeo1, srcGeo2);
    
    // 2. merge properties
    
    // find number of _used_ properties/indices in both geometries
    UInt32 src1Used = 0;
    UInt32 src2Used = 0;
    
    for(UInt32 i = 0; i < srcGeo1->getSFLengths()->getValue()->size(); ++i)
        src1Used += srcGeo1->getSFLengths()->getValue()->getValue<UInt32>(i);
    
    for(UInt32 i = 0; i < srcGeo2->getSFLengths()->getValue()->size(); ++i)
        src2Used += srcGeo2->getSFLengths()->getValue()->getValue<UInt32>(i);
    
    // get index bag for single indexed geo
    Geometry::IndexBag src2IBag = srcGeo2->getUniqueIndexBag();
    
    FFASSERT(src2IBag.size() == 1, 1, ("mergeGeoNISI: Not single indexed!\n");)
    
    const GeoIntegralProperty *src2Idx = src2IBag[0].first;
    
    // create new index - be conservative and use UInt32 indices
    GeoIntegralPropertyUnrecPtr dstIdx = 
        GeoPropertyFactory::the()->create(GL_UNSIGNED_INT);
    
    // allocate storage
    dstIdx->resize(src1Used + src2Used);
        
    // populate index with entries for srcGeo1
    for(UInt32 i = 0; i < src1Used; ++i)
        dstIdx->setValue(i, i);
    
    IndexMap idxMap;
    UInt32   offset = src1Used;
    copyIndex(dstIdx, src2Idx, src2Used, idxMap, offset, src1Used);
    
    // copy each property
    for(UInt32 i = 0; i < src2IBag[0].second.size(); ++i)
    {
        const GeoVectorProperty *src1Prop =
            srcGeo1->getProperty(src2IBag[0].second[i]);
        const GeoVectorProperty *src2Prop =
            srcGeo2->getProperty(src2IBag[0].second[i]);
                
        FFASSERT(!((src1Prop != NULL) ^ (src2Prop != NULL)), 1,
                 ("mergeGeoNISI: Inconsistent properties!\n");)
        
        if(src1Prop == NULL || src2Prop == NULL)
            continue;
        
        UInt32 dstFormat;
        UInt32 dstDim;
        UInt32 dstVecType;
        UInt32 dstNorm;
        
        // create destination property
        calcMergePropertyType(src1Prop, src2Prop,
                              dstFormat, dstDim, dstVecType, dstNorm);
        GeoVectorPropertyUnrecPtr dstProp =
            GeoPropertyFactory::the()->create(dstFormat,  dstDim,
                                              dstVecType, dstNorm != 0);
        
        // allocate storage
        dstProp->resize(offset);
               
        copyVector      (dstProp, src1Prop, src1Used, 0               );
        copyVectorMapped(dstProp, src2Prop, src2Idx,  src2Used, idxMap);
        
        dstGeo->setProperty(dstProp, src2IBag[0].second[i]);
        dstGeo->setIndex   (dstIdx,  src2IBag[0].second[i]);
    }
}

inline
void mergeGeoSINI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    mergeGeoNISI(dstGeo, srcGeo2, srcGeo1);
}

/*! Merge geometry \a srcGeo1 and \a srcGeo2 into \a dstGeo, assuming they
    have the same set of properties and \a srcGeo1 is not indexed, \a srcGeo2 is
    multi indexed. The result \a dstGeo will be multi indexed.
 */
void mergeGeoNIMI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    FDEBUG(("mergeGeoNIMI: srcGeo1 [%p] srcGeo2 [%p]\n", srcGeo1, srcGeo2));
    
    // 1. merge types and lengths
    mergeGeoTypes  (dstGeo, srcGeo1, srcGeo2);
    mergeGeoLengths(dstGeo, srcGeo1, srcGeo2);
    
    // 2. merge properties
            
    // find number of _used_ properties/indices in both geometries
    UInt32 src1Used = 0;
    UInt32 src2Used = 0;
    
    for(UInt32 i = 0; i < srcGeo1->getSFLengths()->getValue()->size(); ++i)
        src1Used += srcGeo1->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    for(UInt32 i = 0; i < srcGeo2->getSFLengths()->getValue()->size(); ++i)
        src2Used += srcGeo2->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    // get index bag for multi indexed geo
    Geometry::IndexBag src2IBag = srcGeo2->getUniqueIndexBag();
    
    for(UInt32 i = 0; i < src2IBag.size(); ++i)
    {
        const GeoIntegralProperty *src2Idx = src2IBag[i].first;
    
        // create new index - be conservative and use UInt32 indices
        GeoIntegralPropertyUnrecPtr dstIdx = 
            GeoPropertyFactory::the()->create(GL_UNSIGNED_INT);
        
        // allocate storage
        dstIdx->resize(src1Used + src2Used);
        
        // populate index with entries for srcGeo1
        for(UInt32 j = 0; j < src1Used; ++j)
            dstIdx->setValue(j, j);
            
        IndexMap idxMap;
        UInt32   offset = src1Used;
        copyIndex(dstIdx, src2Idx, src2Used, idxMap, offset, src1Used);
        
        // copy properties indexed by this index
        for(UInt32 j = 0; j < src2IBag[i].second.size(); ++j)
        {
            const GeoVectorProperty *src1Prop =
                srcGeo1->getProperty(src2IBag[i].second[j]);
            const GeoVectorProperty *src2Prop =
                srcGeo2->getProperty(src2IBag[i].second[j]);
            
            FFASSERT(!((src1Prop != NULL) ^ (src2Prop != NULL)), 1,
                 ("mergeGeoNIMI: Inconsistent properties!\n");)
        
            if(src1Prop == NULL || src2Prop == NULL)
                continue;
            
            UInt32 dstFormat;
            UInt32 dstDim;
            UInt32 dstVecType;
            UInt32 dstNorm;
            
            // create destination property
            calcMergePropertyType(src1Prop, src2Prop,
                                  dstFormat, dstDim, dstVecType, dstNorm);
            GeoVectorPropertyUnrecPtr dstProp =
                GeoPropertyFactory::the()->create(dstFormat,  dstDim,
                                                  dstVecType, dstNorm != 0);
            
            // allocate storage
            dstProp->resize(offset);
                    
            copyVector      (dstProp, src1Prop, src1Used, 0               );
            copyVectorMapped(dstProp, src2Prop, src2Idx,  src2Used, idxMap);
            
            dstGeo->setProperty(dstProp, src2IBag[i].second[j]);
            dstGeo->setIndex   (dstIdx,  src2IBag[i].second[j]);
        }
    }
}

inline
void mergeGeoMINI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    mergeGeoNIMI(dstGeo, srcGeo2, srcGeo1);
}

/*! Merge geometry \a srcGeo1 and \a srcGeo2 into \a dstGeo, assuming they have
    the same set of properties and both are single indexed.
 */
void mergeGeoSISI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    FDEBUG(("mergeGeoSISI: srcGeo1 [%p] srcGeo2 [%p]\n", srcGeo1, srcGeo2));
    
    // 1. merge types and lengths
    mergeGeoTypes  (dstGeo, srcGeo1, srcGeo2);
    mergeGeoLengths(dstGeo, srcGeo1, srcGeo2);
    
    // 2. merge properties
            
    // find number of _used_ indices in both geometries
    UInt32 src1Used = 0;
    UInt32 src2Used = 0;
    
    for(UInt32 i = 0; i < srcGeo1->getSFLengths()->getValue()->size(); ++i)
        src1Used += srcGeo1->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    for(UInt32 i = 0; i < srcGeo2->getSFLengths()->getValue()->size(); ++i)
        src2Used += srcGeo2->getSFLengths()->getValue()->getValue<UInt32>(i);

    const GeoIntegralProperty *src1Idx = NULL;
    const GeoIntegralProperty *src2Idx = NULL;
    
    for(UInt32 i = 0; i < srcGeo1->getMFPropIndices()->size(); ++i)
    {
        if((*srcGeo1->getMFPropIndices())[i] != NULL)
        {
            src1Idx = (*srcGeo1->getMFPropIndices())[i];
            break;
        }
    }
    
    for(UInt32 i = 0; i < srcGeo2->getMFPropIndices()->size(); ++i)
    {
        if((*srcGeo2->getMFPropIndices())[i] != NULL)
        {
            src2Idx = (*srcGeo2->getMFPropIndices())[i];
            break;
        }
    }
    
    // create new index
    UInt32   dstIdxFormat;
    calcMergePropertyType(src1Idx, src2Idx, true, dstIdxFormat);
    GeoIntegralPropertyUnrecPtr dstIdx = 
        GeoPropertyFactory::the()->create(dstIdxFormat);
    
    dstIdx->resize(src1Used + src2Used);
        
    // copy index values to destination
    IndexMap idxMap1;
    IndexMap idxMap2;
    UInt32   offset = 0;
    copyIndex(dstIdx, src1Idx, src1Used, idxMap1, offset, 0       );
    copyIndex(dstIdx, src2Idx, src2Used, idxMap2, offset, src1Used);
    
    // copy each property
    UInt32 minPropSz = osgMin(srcGeo1->getMFProperties()->size(),
                              srcGeo2->getMFProperties()->size() );
    
    for(UInt32 i = 0; i < minPropSz; ++i)
    {
        const GeoVectorProperty *src1Prop = srcGeo1->getProperty(i);
        const GeoVectorProperty *src2Prop = srcGeo2->getProperty(i);
        
        // skip missing properties
        if(src1Prop == NULL || src2Prop == NULL)
            continue;
        
        UInt32 dstFormat;
        UInt32 dstDim;
        UInt32 dstVecType;
        UInt32 dstNorm;
        
        // create destination property
        calcMergePropertyType(src1Prop, src2Prop,
                              dstFormat, dstDim, dstVecType, dstNorm);
        GeoVectorPropertyUnrecPtr dstProp = 
            GeoPropertyFactory::the()->create(dstFormat,  dstDim,
                                              dstVecType, dstNorm != 0);
        
        // allocate storage
        dstProp->resize(offset);
        
        // copy property values - only those referenced by an index are copied
        // and stored to the new position indicated by idxMap
        copyVectorMapped(dstProp, src1Prop, src1Idx, src1Used, idxMap1);
        copyVectorMapped(dstProp, src2Prop, src2Idx, src2Used, idxMap2);
        
        dstGeo->setProperty(dstProp, i);
        dstGeo->setIndex   (dstIdx,  i);
    }
}   

/*! Merge geometry \a srcGeo1 and \a srcGeo2 into \a dstGeo, assuming they have
    the same set of properties and \a srcGeo1 is single indexed, \a srcGeo2 is
    multi indexed. The result \a dstGeo will be multi indexed.
 */
void mergeGeoSIMI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    FDEBUG(("mergeGeoSIMI: srcGeo1 [%p] srcGeo2 [%p]\n", srcGeo1, srcGeo2));
    
    // 1. merge types and lengths
    mergeGeoTypes  (dstGeo, srcGeo1, srcGeo2);
    mergeGeoLengths(dstGeo, srcGeo1, srcGeo2);
    
    // 2. merge properties
            
    // find number of _used_ indices in both geometries
    UInt32 src1Used = 0;
    UInt32 src2Used = 0;
    
    for(UInt32 i = 0; i < srcGeo1->getSFLengths()->getValue()->size(); ++i)
        src1Used += srcGeo1->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    for(UInt32 i = 0; i < srcGeo2->getSFLengths()->getValue()->size(); ++i)
        src2Used += srcGeo2->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    // get indices sorted by the properties they index
    Geometry::IndexBag src1IBag = srcGeo1->getUniqueIndexBag();
    Geometry::IndexBag src2IBag = srcGeo2->getUniqueIndexBag();
    
    for(UInt32 i = 0; i < src2IBag.size(); ++i)
    {
        const GeoIntegralProperty *src1Idx = src1IBag[0].first;
        const GeoIntegralProperty *src2Idx = src2IBag[i].first;
    
        // create new index
        UInt32   dstIdxFormat;
        calcMergePropertyType(src1Idx, src2Idx, true, dstIdxFormat);
        GeoIntegralPropertyUnrecPtr dstIdx = 
            GeoPropertyFactory::the()->create(dstIdxFormat);
        
        // allocate storage
        dstIdx->resize(src1Used + src2Used);
        
        // copy index values to destination
        IndexMap idxMap1;
        IndexMap idxMap2;
        UInt32   offset = 0;
        copyIndex(dstIdx, src1Idx, src1Used, idxMap1, offset, 0       );
        copyIndex(dstIdx, src2Idx, src2Used, idxMap2, offset, src1Used);
        
        // copy properties indexed by this index
        for(UInt32 j = 0; j < src2IBag[i].second.size(); ++j)
        {
            const GeoVectorProperty *src1Prop =
                srcGeo1->getProperty(src2IBag[i].second[j]);
            const GeoVectorProperty *src2Prop =
                srcGeo2->getProperty(src2IBag[i].second[j]);
            
            FFASSERT(!((src1Prop != NULL) ^ (src2Prop != NULL)), 1,
                     ("mergeGeoSIMI: Inconsistent properties!");)
        
            if(src1Prop == NULL || src2Prop == NULL)
                continue;
        
            UInt32 dstFormat;
            UInt32 dstDim;
            UInt32 dstVecType;
            UInt32 dstNorm;
            
            // create destination property
            calcMergePropertyType(src1Prop, src2Prop,
                                  dstFormat, dstDim, dstVecType, dstNorm);
            GeoVectorPropertyUnrecPtr dstProp =
                GeoPropertyFactory::the()->create(dstFormat,  dstDim,
                                                  dstVecType, dstNorm != 0);
            
            // allocate storage
            dstProp->resize(offset);
                    
            copyVectorMapped(dstProp, src1Prop, src1Idx, src1Used, idxMap1);
            copyVectorMapped(dstProp, src2Prop, src2Idx, src2Used, idxMap2);
            
            dstGeo->setProperty(dstProp, src2IBag[i].second[j]);
            dstGeo->setIndex   (dstIdx,  src2IBag[i].second[j]);
        }
    }
}

inline
void mergeGeoMISI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    mergeGeoSIMI(dstGeo, srcGeo2, srcGeo1);
}

/*! Merge geometry \a srcGeo1 and \a srcGeo2 into \a dstGeo, assuming they have
    the same set of properties and both are multi indexed.
 */
void mergeGeoMIMI(
    Geometry *dstGeo, const Geometry *srcGeo1, const Geometry *srcGeo2)
{
    FDEBUG(("mergeGeoMIMI: srcGeo1 [%p] srcGeo2 [%p]\n", srcGeo1, srcGeo2));
    
    // 1. merge types and lengths
    mergeGeoTypes  (dstGeo, srcGeo1, srcGeo2);
    mergeGeoLengths(dstGeo, srcGeo1, srcGeo2);
    
    // 2. merge properties
            
    // find number of _used_ indices in both geometries
    UInt32 src1Used = 0;
    UInt32 src2Used = 0;
    
    for(UInt32 i = 0; i < srcGeo1->getSFLengths()->getValue()->size(); ++i)
        src1Used += srcGeo1->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    for(UInt32 i = 0; i < srcGeo2->getSFLengths()->getValue()->size(); ++i)
        src2Used += srcGeo2->getSFLengths()->getValue()->getValue<UInt32>(i);
        
    // get indices sorted by the properties they index
    Geometry::IndexBag src1IBag = srcGeo1->getUniqueIndexBag();
    Geometry::IndexBag src2IBag = srcGeo2->getUniqueIndexBag();
    
    // Property N may be indexed by different indices in both geometries.
    // We build a 2D map (mipMap) that is indexed by i1, i2 and gives the list
    // of properties that is indexed by the concatenation of indices
    // src1IBag[i1].first and src2IBag[i2].first
    
    typedef std::vector<std::vector< std::vector<UInt32> > > MergedIndexPropMap;
    
    MergedIndexPropMap mipMap;
    mipMap.resize(src1IBag.size());
    
    // find indices that index the same property
    for(UInt32 i1 = 0; i1 < src1IBag.size(); ++i1)
    {
        mipMap[i1].resize(src2IBag.size());
    
        for(UInt32 j1 = 0; j1 < src1IBag[i1].second.size(); ++j1)
        {
            for(UInt32 i2 = 0; i2 < src2IBag.size(); ++i2)
            {
                for(UInt32 j2 = 0; j2 < src2IBag[i2].second.size(); ++j2)
                {
                    if(src1IBag[i1].second[j1] == src2IBag[i2].second[j2])
                    {
                        mipMap[i1][i2].push_back(src1IBag[i1].second[j1]);
                    }
                }
            }
        }
    }
    
    // iterate over mipMap concatenating corresponding indices and copy
    // the indexed properties.
    
    for(UInt32 i1 = 0; i1 < mipMap.size(); ++i1)
    {
        for(UInt32 i2 = 0; i2 < mipMap[i1].size(); ++i2)
        {
            if(mipMap[i1][i2].empty())
                continue;
            
            const GeoIntegralProperty *src1Idx = src1IBag[i1].first;
            const GeoIntegralProperty *src2Idx = src2IBag[i2].first;
            
            // create new index
            UInt32   dstIdxFormat;
            calcMergePropertyType(src1Idx, src2Idx, true, dstIdxFormat);
            GeoIntegralPropertyUnrecPtr dstIdx =
                GeoPropertyFactory::the()->create(dstIdxFormat);
            
            // allocate storage
            dstIdx->resize(src1Used + src2Used);
        
            // copy index values to destination
            IndexMap idxMap1;
            IndexMap idxMap2;
            UInt32   offset = 0;
            copyIndex(dstIdx, src1Idx, src1Used, idxMap1, offset, 0       );
            copyIndex(dstIdx, src2Idx, src2Used, idxMap2, offset, src1Used);
            
            for(UInt32 j = 0; j < mipMap[i1][i2].size(); ++j)
            {
                const GeoVectorProperty *src1Prop =
                        srcGeo1->getProperty(mipMap[i1][i2][j]);
                const GeoVectorProperty *src2Prop =
                        srcGeo2->getProperty(mipMap[i1][i2][j]);
                
                if(src1Prop == NULL || src2Prop == NULL)
                    continue;
                
                UInt32 dstFormat;
                UInt32 dstDim;
                UInt32 dstVecType;
                UInt32 dstNorm;
                
                // create destination property
                calcMergePropertyType(src1Prop, src2Prop,
                                      dstFormat, dstDim, dstVecType, dstNorm);
                GeoVectorPropertyUnrecPtr dstProp =
                    GeoPropertyFactory::the()->create(dstFormat,  dstDim,
                                                      dstVecType, dstNorm != 0);
                
                // allocate storage
                dstProp->resize(offset);
                        
                copyVectorMapped(dstProp, src1Prop, src1Idx, src1Used, idxMap1);
                copyVectorMapped(dstProp, src2Prop, src2Idx, src2Used, idxMap2);
                
                dstGeo->setProperty(dstProp, mipMap[i1][i2][j]);
                dstGeo->setIndex   (dstIdx,  mipMap[i1][i2][j]);
            }
        }
    }
}

} // namespace


/*! Returns whether the two geometries \a geo1 and \a geo2 can be merged, based
    on the properties and indexing they use.
    Geometries are mergeable if they have the same set of properties.
    
    \warning Materials are not considered in this function!

    \ingroup GrpDrawablesGeometryUtils
 */
bool mergeableGeo(const Geometry *geo1, const Geometry *geo2)
{
    if(geo1->getTypes() == NULL || geo2->getTypes() == NULL)
    {
        SWARNING << "mergeableGeo: Geometry without types, can not merge."
                 << std::endl;

        return false;
    }

    if(geo1->getLengths() == NULL || geo2->getLengths() == NULL)
    {
        SWARNING << "mergeableGeo: Geometry without lengths, can not merge."
                 << std::endl;

        return false;
    }

    const Geometry::MFPropertiesType &prop1 = *(geo1->getMFProperties());
    const Geometry::MFPropertiesType &prop2 = *(geo2->getMFProperties());
    
    // number of properties may differ, but additional entries must be NULL.
    // first compare common entries
    UInt32 minSize = osgMin(prop1.size(), prop2.size());
    UInt32 maxSize = osgMax(prop1.size(), prop2.size());
    UInt32 i;
    
    // common entries must either be both present or both absent
    for(i = 0; i < minSize; ++i)
    {
        if((prop1[i] != NULL) ^ (prop2[i] != NULL))
            return false;
    }
    
    // additional entries must be NULL
    for(; i < maxSize; ++i)
    {
        if(i < prop1.size() && prop1[i] != NULL)
            return false;
            
        if(i < prop2.size() && prop2[i] != NULL)
            return false;
    }
    
    // geometries have the same properties, now check indexing
    
    UInt32 szIBag1 = geo1->getUniqueIndexBag().size();
    UInt32 szIBag2 = geo2->getUniqueIndexBag().size();
    
    if(szIBag1 == 0 && szIBag2 == 0)
    {
        // no index +   no index    ->  no index
        return true;
    }
    else if(szIBag1 == 1 && szIBag2 == 1)
    {
        // single   +   single      ->  single
        return true;
    }
    else if(szIBag1 > 1 && szIBag2 > 1)
    {
        // multi    +   multi       ->  multi
        return true;
    }
    else if(szIBag1 == 0 && szIBag2 == 1)
    {
        // no index +   single      -> single
        return true;
    }
    else if(szIBag1 == 1 && szIBag2 == 0)
    {
        // single   +   no index    -> single
        return true;
    }
    else if(szIBag1 > 1 && szIBag2 == 0)
    {
        // multi    +   no index    -> multi
        return true;
    }
    else if(szIBag1 == 0 && szIBag2 > 1)
    {
        // no index +   multi       -> multi
        return true;
    }
    else if(szIBag1 == 1 && szIBag2 > 1)
    {
        // single   +   multi       -> multi
        return true;
    }
    else if(szIBag1 > 1 && szIBag2 == 1)
    {
        // multi    +   single      -> multi
        return true;
    }
    
    // should not happen
    FWARNING(
        ("mergeableGeo: Unrecognized indexing. Geometry may be invalid.\n"));
    
    return false;
}

/*! Attempts to merge \a geo1 and \a geo2 and returns the merged geometry or a
    NULL pointer if  merging is not possible.
    
    \warning Materials are not considered in this function!

    \ingroup GrpDrawablesGeometryUtils
 */
GeometryTransitPtr mergeGeo(const Geometry *geo1, const Geometry *geo2)
{
    GeometryUnrecPtr returnValue;

    if(geo1->getTypes() == NULL || geo2->getTypes() == NULL)
    {
        SWARNING << "mergeGeo: Geometry without types, can not merge."
                 << std::endl;

        return GeometryTransitPtr();
    }

    if(geo1->getLengths() == NULL || geo2->getLengths() == NULL)
    {
        SWARNING << "mergeGeo: Geometry without lengths, can not merge."
                 << std::endl;

        return GeometryTransitPtr();
    }

    const Geometry::MFPropertiesType &prop1 = *(geo1->getMFProperties());
    const Geometry::MFPropertiesType &prop2 = *(geo2->getMFProperties());
    
    // number of properties may differ, but additional entries must be NULL.
    // first compare common entries
    UInt32 minSize = osgMin(prop1.size(), prop2.size());
    UInt32 maxSize = osgMax(prop1.size(), prop2.size());
    UInt32 i;
    
    // common entries must either be both present or both absent
    for(i = 0; i < minSize; ++i)
    {
        if((prop1[i] != NULL) ^ (prop2[i] != NULL))
        {
            FWARNING(("mergeGeo: Geometries have different properties, "
                      "can not merge.\n"));
                      
            return GeometryTransitPtr();
        }
    }
    
    // additional entries must be NULL
    for(; i < maxSize; ++i)
    {
        if(i < prop1.size() && prop1[i] != NULL)
        {
            FWARNING(("mergeGeo: Geometries have different properties, "
                      "can not merge.\n"));
        
            return GeometryTransitPtr();
        }
            
        if(i < prop2.size() && prop2[i] != NULL)
        {
            FWARNING(("mergeGeo: Geometries have different properties, "
                      "can not merge.\n"));
            
            return GeometryTransitPtr();
        }
    }
    
    // geometries have the same properties, now check indexing
    
    UInt32 szIBag1 = geo1->getUniqueIndexBag().size();
    UInt32 szIBag2 = geo2->getUniqueIndexBag().size();
    
    if(szIBag1 == 0 && szIBag2 == 0)
    {
        // no index +   no index    ->  no index
        returnValue = Geometry::create();
        mergeGeoNINI(returnValue, geo1, geo2);
    }
    else if(szIBag1 == 1 && szIBag2 == 1)
    {
        // single   +   single      ->  single
        returnValue = Geometry::create();
        mergeGeoSISI(returnValue, geo1, geo2);
    }
    else if(szIBag1 > 1 && szIBag2 > 1)
    {
        // multi    +   multi       ->  multi
        returnValue = Geometry::create();
        mergeGeoMIMI(returnValue, geo1, geo2);
    }
    else if(szIBag1 == 0 && szIBag2 == 1)
    {
        // no index +   single      -> single
        returnValue = Geometry::create();
        mergeGeoNISI(returnValue, geo1, geo2);
    }
    else if(szIBag1 == 1 && szIBag2 == 0)
    {
        // single   +   no index    -> single
        returnValue = Geometry::create();
        mergeGeoSINI(returnValue, geo1, geo2);
    }
    else if(szIBag1 > 1 && szIBag2 == 0)
    {
        // multi    +   no index    -> multi
        returnValue = Geometry::create();
        mergeGeoMINI(returnValue, geo1, geo2);
    }
    else if(szIBag1 == 0 && szIBag2 > 1)
    {
        // no index +   multi       -> multi
        returnValue = Geometry::create();
        mergeGeoNIMI(returnValue, geo1, geo2);
    }
    else if(szIBag1 == 1 && szIBag2 > 1)
    {
        // single   +   multi       -> multi
        returnValue = Geometry::create();
        mergeGeoSIMI(returnValue, geo1, geo2);
    }
    else if(szIBag1 > 1 && szIBag2 == 1)
    {
        // multi    +   single      -> multi
        returnValue = Geometry::create();
        mergeGeoMISI(returnValue, geo1, geo2);
    }
    
    return GeometryTransitPtr(returnValue);
}

/*! \ingroup GrpDrawablesGeometryUtils
 */

void setVBOUsageOnPropertyProtos(bool bVal)
{
    DerivedFieldContainerTypeIterator dtIt =
        FieldContainerFactory::the()->begin(GeoProperty::getClassType());

    DerivedFieldContainerTypeIterator dtEnd = 
        FieldContainerFactory::the()->end();

    while(dtIt != dtEnd)
    {
        FieldContainer *pProto = dtIt->getPrototype();

        if(pProto != NULL)
        {
            GeoProperty *pProp = dynamic_cast<GeoProperty *>(pProto);
        
            OSG_ASSERT(pProp != NULL);

            pProp->setUseVBO(bVal);
        
        }   

        ++dtIt;
    }
}

OSG_END_NAMESPACE

