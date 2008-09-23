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

#ifndef _OSGCOLLADAINSTANCEGEOMETRY_H_
#define _OSGCOLLADAINSTANCEGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaInstanceGeometry.h
    \ingroup GrpLoader
 */

#include <OSGConfig.h>

#ifdef OSG_WITH_COLLADA

#include <OSGFileIODef.h>
#include <OSGColladaInstanceElement.h>
#include <OSGColladaGeometry.h>

#include <map>

// forward declarations
class domInstance_geometry;


OSG_BEGIN_NAMESPACE

// forward declarations
class ChunkMaterial;


class OSG_FILEIO_DLLMAPPING ColladaInstanceGeometry
    : public ColladaInstanceElement
{
  public:
    typedef ColladaInstanceElement                  Inherited;
    typedef ColladaInstanceGeometry                 Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(domInstance_geometry *instGeo,
                                       ColladaGlobal        *global  );
    
    virtual void           read          (void);
            NodeTransitPtr createInstance(void);
    
  protected:
    typedef std::map<std::string, ChunkMaterial *> MaterialMap;
    typedef MaterialMap::iterator                  MaterialMapIt;

    typedef std::map<std::string,
                     std::vector<UInt32>         > TexBindingsMap;
      
      
             ColladaInstanceGeometry(domInstance_geometry *instGeo,
                                     ColladaGlobal        *global  );
    virtual ~ColladaInstanceGeometry(void                          );
    
    void updateGeoTexBindings(ColladaGeometry::GeometryInfo *geoInfo);
    
    MaterialMap    _matMap;
    TexBindingsMap _texBindingsMap;
    
    NodeUnrecPtr   _node;
};

typedef ColladaInstanceGeometry::ObjRefPtr     ColladaInstanceGeometryRefPtr;
typedef ColladaInstanceGeometry::ObjTransitPtr ColladaInstanceGeometryTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaInstanceGeometry.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEGEOMETRY_H_
