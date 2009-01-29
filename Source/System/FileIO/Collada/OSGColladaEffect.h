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

#ifndef _OSGCOLLADAEFFECT_H_
#define _OSGCOLLADAEFFECT_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaGeometry.h
    \ingroup GrpLoader
 */

#include <OSGConfig.h>

#ifdef OSG_WITH_COLLADA

#include <OSGFileIODef.h>
#include <OSGColladaElement.h>

#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>

#include <dom/domCommon_color_or_texture_type.h>
#include <dom/domCommon_float_or_param_type.h>
#include <dom/domCommon_transparent_type.h>

// forward declarations
class domEffect;
class domFx_surface_common;
class domFx_sampler2D_common;
class domProfile_COMMON;
class domProfile_GLSL;
class domProfile_CG;


OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaEffect : public ColladaElement
{
  public:
    typedef ColladaElement  Inherited;
    typedef ColladaEffect   Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    typedef domCommon_color_or_texture_type::domColor   DomColor;
    typedef domCommon_color_or_texture_type::domTexture DomTexture;
    typedef domCommon_float_or_param_type               DomFloat;

    static inline ObjTransitPtr create(domEffect     *effect,
                                       ColladaGlobal *global );

    virtual void read(void);
    
    inline ChunkMaterial        *getMaterial  (void                  );
           domFx_surface_common *getSurface   (const std::string &ref);
           UInt32                getTexBinding(const std::string &ref);
    
  protected:
             ColladaEffect(domEffect *effect, ColladaGlobal *global);
    virtual ~ColladaEffect(void                                    );
    
    typedef std::map<std::string,
                     domFx_surface_common *  > SurfaceMap;
    typedef std::map<std::string,
                     domFx_sampler2D_common *> SamplerMap;
    
    void handleCommonProfile(domProfile_COMMON *profCommon);
    void handleGLSLProfile  (domProfile_GLSL   *profGLSL  );
    void handleCGProfile    (domProfile_CG     *profCG    );
    
    inline void   setTexCoordMapping(      UInt32       texCoord,
                                     const std::string &mappedTC );
    inline Real32 computeLuminance  (Real32 colR, Real32 colG, Real32 colB);
    
    template <class TechTypeT>
    void setupSimpleColorAndTex    (TechTypeT   tech,
                                    DomFloat   *shininess   = NULL,
                                    DomColor   *specularCol = NULL,
                                    DomTexture *specularTex = NULL );

    template <class TechTypeT>
    void setupSimpleSpecColorAndTex(TechTypeT   tech               );
    
    MaterialChunkTransitPtr handleSimpleColor(DomColor          *diffuse,
                                              DomColor          *ambient,
                                              DomColor          *specular,
                                              DomColor          *emission,
                                              DomColor          *transparent,
                                              domFx_opaque_enum  opaqueMode,
                                              Real32             shininess,
                                              Real32             transparency);
    inline void fillElements(
        domCommon_color_or_texture_type                *colTexIn,
        domCommon_color_or_texture_type::domColorRef   &colOut,
        domCommon_color_or_texture_type::domTextureRef &texOut   );
    inline void fillElements(
        domCommon_transparent_type                     *colTexIn,
        domCommon_color_or_texture_type::domColorRef   &colOut,
        domCommon_color_or_texture_type::domTextureRef &texOut   );
    ChunkMaterialUnrecPtr    _material;
    std::vector<std::string> _texCoordMapping;
    SurfaceMap               _surfaceMap;
    SamplerMap               _samplerMap;
};

typedef ColladaEffect::ObjRefPtr     ColladaEffectRefPtr;
typedef ColladaEffect::ObjTransitPtr ColladaEffectTransitPtr;

OSG_END_NAMESPACE

#include <OSGColladaEffect.inl>

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAEFFECT_H_
