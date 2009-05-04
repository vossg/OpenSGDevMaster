/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADALIGHT_H_
#define _OSGCOLLADALIGHT_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaLight.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGColladaInstantiableElement.h"
#include "OSGLight.h"

#include <dom/domLight.h>

OSG_BEGIN_NAMESPACE

// forward declarations
class ColladaInstanceLight;


class OSG_FILEIO_DLLMAPPING ColladaLight : public ColladaInstantiableElement
{
  public:
    typedef ColladaInstantiableElement              Inherited;
    typedef ColladaLight                            Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(domLight      *light,
                                       ColladaGlobal *global);
    
    virtual void   read    (void);

    inline  Light *getLight(void) const;
    
  protected:
    friend class ColladaInstanceLight;

    typedef domLight::domTechnique_common             domTechnique_common;
    typedef domLight::domTechnique_commonRef          domTechnique_commonRef;

    typedef domTechnique_common   ::domAmbient        domAmbient;
    typedef domTechnique_common   ::domAmbientRef     domAmbientRef;

    typedef domTechnique_common   ::domDirectional    domDirectional;
    typedef domTechnique_common   ::domDirectionalRef domDirectionalRef;

    typedef domTechnique_common   ::domPoint          domPoint;
    typedef domTechnique_common   ::domPointRef       domPointRef;

    typedef domTechnique_common   ::domSpot           domSpot;
    typedef domTechnique_common   ::domSpotRef        domSpotRef;
   
    void handleAmbient    (domAmbient     *ambientL    );
    void handleDirectional(domDirectional *directionalL);
    void handlePoint      (domPoint       *pointL      );
    void handleSpot       (domSpot        *spotL       );

             ColladaLight(domLight *light, ColladaGlobal *global);
    virtual ~ColladaLight(void                                  );

    LightUnrecPtr _light;
};

typedef ColladaLight::ObjRefPtr     ColladaLightRefPtr;
typedef ColladaLight::ObjTransitPtr ColladaLightTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaLight.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADALIGHT_H_
