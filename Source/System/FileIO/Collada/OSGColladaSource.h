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

#ifndef _OSGCOLLADASOURCE_H_
#define _OSGCOLLADASOURCE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaSource.h
    \ingroup GrpLoader
 */

#include <OSGConfig.h>

#ifdef OSG_WITH_COLLADA

#include <OSGFileIODef.h>
#include <OSGColladaElement.h>

#include <OSGTypedGeoVectorProperty.h>

//forward declarations
class domSource;


OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaSource : public ColladaElement
{
  public:
    typedef ColladaElement Inherited;
    typedef ColladaSource  Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;

    static inline ObjTransitPtr create(domSource     *source,
                                       ColladaGlobal *global );
    
    virtual void read(void);
    
    GeoVec3fProperty *getAsVec3fProp(void);
    GeoPnt3fProperty *getAsPnt3fProp(void);
    GeoVec2fProperty *getAsVec2fProp(void);
    
  protected:
             ColladaSource(domSource *source, ColladaGlobal *global);
    virtual ~ColladaSource(void                                    );
    
    GeoVec3fPropertyUnrecPtr _propVec3f;
    GeoPnt3fPropertyUnrecPtr _propPnt3f;
    GeoVec2fPropertyUnrecPtr _propVec2f;
};

typedef ColladaSource::ObjRefPtr     ColladaSourceRefPtr;
typedef ColladaSource::ObjTransitPtr ColladaSourceTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaSource.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADASOURCE_H_
