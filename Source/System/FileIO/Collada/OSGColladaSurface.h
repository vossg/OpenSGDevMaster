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

#ifndef _OSGCOLLADASURFACE_H_
#define _OSGCOLLADASURACE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaSurface.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGColladaElement.h"

#include "OSGTextureObjChunk.h"

// forward declarations
class domFx_surface_common;


OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaSurface : public ColladaElement
{
  public:
    typedef ColladaElement                          Inherited;
    typedef ColladaSurface                          Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(domFx_surface_common *surface,
                                       ColladaGlobal        *global  );
    
    virtual void read   (void);

    inline TextureObjChunk *getTexObj(void);
    
  protected:
             ColladaSurface(domFx_surface_common *surface,
                            ColladaGlobal        *global  );
    virtual ~ColladaSurface(void                          );

    TextureObjChunkUnrecPtr _texObj;
};

typedef ColladaSurface::ObjRefPtr     ColladaSurfaceRefPtr;
typedef ColladaSurface::ObjTransitPtr ColladaSurfaceTransitPtr;

OSG_END_NAMESPACE

#include "OSGColladaSurface.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADASURFACE_H_
