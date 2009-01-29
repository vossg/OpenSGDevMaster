/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAGEOMETRY_H_
#define _OSGCOLLADAGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaGeometry.h
    \ingroup GrpLoader
 */

#include <OSGConfig.h>

#ifdef OSG_WITH_COLLADA

#include <OSGFileIODef.h>
#include <OSGColladaInstantiableElement.h>

#include <OSGGeometry.h>
#include <OSGTypedGeoIntegralProperty.h>
#include <OSGGeoVectorProperty.h>

#include <dae/daeDomTypes.h>
#include <dom/domInputLocal.h>
#include <dom/domInputLocalOffset.h>

#include <map>

//forward declarations
class domGeometry;
class domLines;
class domLinestrips;
class domPolygons;
class domPolylists;
class domTriangles;
class domTrifans;
class domTristrips;


OSG_BEGIN_NAMESPACE

// handles a single <geometry> tag
// which may require splitting into multiple OSG::Geometry objects, depending
// on indexing and materials used

// forward declarations
class ColladaInstanceGeometry;


class OSG_FILEIO_DLLMAPPING ColladaGeometry : public ColladaInstantiableElement
{
  public:
    typedef ColladaInstantiableElement      Inherited;
    typedef ColladaGeometry                 Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;

    static inline ObjTransitPtr create(domGeometry   *geo,
                                       ColladaGlobal *global);
    
    virtual void read(void);
    
  protected:
    friend class ColladaInstanceGeometry;
    
    typedef std::pair<std::string,
                      UInt32                        > SemanticSetPair;
    typedef std::pair<GeoVectorPropertyUnrecPtr,
                      GeoIntegralPropertyUnrecPtr   > PropIndexPair;
                      
    typedef std::map <SemanticSetPair, PropIndexPair> SemanticPropIndexMap;
    typedef SemanticPropIndexMap::iterator            SemanticPropIndexMapIt;
    
    typedef std::map <std::string,     PropIndexPair> SourcePropIndexMap;
    typedef SourcePropIndexMap::iterator              SourcePropIndexMapIt;
    
    struct GeometryInfo
    {
        GeometryUnrecPtr     geo;
        SemanticPropIndexMap semanticPropIndexMap;
        SourcePropIndexMap   sourcePropIndexMap;
    };
    
    typedef std::map   <std::string, GeometryInfo *> GeoMap;
    typedef GeoMap::iterator                         GeoMapIt;
    
    typedef std::vector<GeoUInt32Property *        > IndexVec;
    
    
    typedef std::vector<GeometryInfo *             > GeoStore;
    typedef std::map   <std::string, GeoStore      > MatGeoMap;
    typedef MatGeoMap::iterator                      MatGeoMapIt;
    
             ColladaGeometry(domGeometry *geo, ColladaGlobal *global);
    virtual ~ColladaGeometry(void                                   );
    
    inline MatGeoMapIt beginGeo(void);
    inline MatGeoMapIt endGeo  (void);
    
    
    void setupGeometry   (      xsNCName                    matName,
                          const domInputLocal_Array        &vertInputs,
                          const domInputLocalOffset_Array  &inputs,
                                GeoUInt32PropertyUnrecPtr  &lengthsOut,
                                GeoUInt8PropertyUnrecPtr   &typesOut,
                                IndexVec                   &indexVecOut );
    
    UInt32 mapSemanticToGeoProp(const std::string &semantic,
                                      bool         vertexAsPos = false);
    
    void handleLines     (const domInputLocal_Array &vertInputs,
                                domLines            *lines      );
    void handleLinestrips(const domInputLocal_Array &vertInputs,
                                domLinestrips       *linestrips );
    void handlePolygons  (const domInputLocal_Array &vertInputs,
                                domPolygons         *polygons   );
    void handlePolylist  (const domInputLocal_Array &vertInputs,
                                domPolylist         *polylist   );
    void handleTriangles (const domInputLocal_Array &vertInputs,
                                domTriangles        *trianges   );
    void handleTrifans   (const domInputLocal_Array &vertInputs,
                                domTrifans          *trifans    );
    void handleTristrips (const domInputLocal_Array &vertInputs,
                                domTristrips        *tristrips  );
    
    GeoVectorProperty *fillVecProp(UInt32 propIdx, daeURI sourceURI);
    
    GeoMap    _geosMap;
    MatGeoMap _geosByMat;
};

typedef ColladaGeometry::ObjRefPtr     ColladaGeometryRefPtr;
typedef ColladaGeometry::ObjTransitPtr ColladaGeometryTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaGeometry.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAGEOMETRY_H_
