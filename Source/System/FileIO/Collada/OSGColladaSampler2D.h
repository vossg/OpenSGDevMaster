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

#ifndef _OSGCOLLADASAMPLER2D_H_
#define _OSGCOLLADASAMPLER2D_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaSampler2D.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGColladaElement.h"

#include "OSGTextureObjChunk.h"

// forward declarations
class domFx_sampler2D_common;


OSG_BEGIN_NAMESPACE

// forward declarations
class ColladaEffect;


class OSG_FILEIO_DLLMAPPING ColladaSampler2D : public ColladaElement
{
  public:
    typedef ColladaElement                          Inherited;
    typedef ColladaSampler2D                        Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(domFx_sampler2D_common *sampler,
                                       ColladaGlobal          *global  );
    
    virtual void read(void);
    
    inline TextureObjChunk *getTexObj(void                    );
    inline void             setEffect(ColladaEffect *colEffect);

  protected:
             ColladaSampler2D(domFx_sampler2D_common *sampler,
                              ColladaGlobal          *global  );
    virtual ~ColladaSampler2D(void                            );
    
    TextureObjChunkUnrecPtr   _texObj;
    ColladaEffect            *_colEffect;
};

typedef ColladaSampler2D::ObjRefPtr     ColladaSampler2DRefPtr;
typedef ColladaSampler2D::ObjTransitPtr ColladaSampler2DTransitPtr;

OSG_END_NAMESPACE

#include "OSGColladaSampler2D.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADASAMPLER2D_H_
