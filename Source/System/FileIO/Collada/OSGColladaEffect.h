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

#ifndef _OSGCOLLADAEFFECT_H_
#define _OSGCOLLADAEFFECT_H_

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstantiableElement.h"
#include "OSGColladaElementFactoryHelper.h"
#include "OSGColladaSampler2D.h"
#include "OSGColladaSurface.h"
#include "OSGMaterial.h"

#include <dom/domImage.h>
#include <dom/domFx_sampler2D_common.h>
#include <dom/domFx_surface_common.h>
#include <dom/domCommon_color_or_texture_type.h>
#include <dom/domCommon_float_or_param_type.h>
#include <dom/domCommon_transparent_type.h>

// forward decl
class domProfile_COMMON;
class domProfile_GLSL;
class domProfile_CG;
class domEffect;
class domInstance_effect;


OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceEffect;
class ChunkMaterial;
class MaterialChunk;
class BlendChunk;
OSG_GEN_CONTAINERPTR(BlendChunk);

class DepthChunk;
OSG_GEN_CONTAINERPTR(DepthChunk);


class OSG_FILEIO_DLLMAPPING ColladaEffect : public ColladaInstantiableElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstantiableElement Inherited;
    typedef ColladaEffect              Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaEffect);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Create                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void      read          (void                            );
    virtual Material *createInstance(ColladaInstanceElement *instElem);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    daeElement     *findDOMParam(const std::string &name) const;
    ColladaElement *findParam   (const std::string &name) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    // <sampler2D> DOM and loader objects
    struct ParamSampler2D
    {
        ColladaSampler2DRefPtr    colSampler2D;
        domFx_sampler2D_commonRef sampler2D;
    };

    // <surface> DOM and loader objects
    struct ParamSurface
    {
        ColladaSurfaceRefPtr    colSurface;
        domFx_surface_commonRef surface;
    };

    typedef std::map<std::string, ParamSampler2D> ParamSampler2DMap;
    typedef ParamSampler2DMap::iterator           ParamSampler2DMapIt;
    typedef ParamSampler2DMap::const_iterator     ParamSampler2DMapConstIt;
    
    typedef std::map<std::string, ParamSurface  > ParamSurfaceMap;
    typedef ParamSurfaceMap::iterator             ParamSurfaceMapIt;
    typedef ParamSurfaceMap::const_iterator       ParamSurfaceMapConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

             ColladaEffect(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaEffect(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Profile Handlers                                             */
    /*! \{                                                                 */

    virtual void      readProfileCommon(domProfile_COMMON *prof);
    virtual void      readProfileGLSL  (domProfile_GLSL   *prof);
    virtual void      readProfileCG    (domProfile_CG     *prof);

    virtual MaterialTransitPtr createInstanceProfileCommon(
        domProfile_COMMON  *prof,       domEffect *effect,
        domInstance_effect *instEffect                    );
    virtual MaterialTransitPtr createInstanceProfileGLSL(
        domProfile_GLSL    *prof,       domEffect *effect,
        domInstance_effect *instEffect                    );
    virtual MaterialTransitPtr createInstanceProfileCG(
        domProfile_CG      *prof,       domEffect *effect,
        domInstance_effect *instEffect                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    void handleProfileCommonEmission(
        domCommon_color_or_texture_type *emission,
        MaterialChunk                   *matChunk     );
    void handleProfileCommonAmbient(
        domCommon_color_or_texture_type *ambient,
        ColladaInstanceEffect           *colInstEffect,
        ChunkMaterial                   *mat,
        MaterialChunk                   *matChunk,
        BlendChunkUnrecPtr              &blendChunk,
        DepthChunkUnrecPtr              &depthChunk,
        UInt32                          &texCount     );
    void handleProfileCommonDiffuse(
        domCommon_color_or_texture_type *diffuse,
        ColladaInstanceEffect           *colInstEffect,
        ChunkMaterial                   *mat,
        MaterialChunk                   *matChunk,
        BlendChunkUnrecPtr              &blendChunk,
        DepthChunkUnrecPtr              &depthChunk,
        UInt32                          &texCount     );
    void handleProfileCommonSpecular(
        domCommon_color_or_texture_type *specular,
        MaterialChunk                   *matChunk     );

    void readImageArray(const domImage_Array &images);
    void fillColorParamTex  (
        domCommon_color_or_texture_type                *colTex,
        domCommon_color_or_texture_type::domColorRef   &colOut,
        domCommon_color_or_texture_type::domParamRef   &paramOut,
        domCommon_color_or_texture_type::domTextureRef &texOut     );
    void fillColorParamTex  (
        domCommon_transparent_type                     *colTex,
        domCommon_color_or_texture_type::domColorRef   &colOut,
        domCommon_color_or_texture_type::domParamRef   &paramOut,
        domCommon_color_or_texture_type::domTextureRef &texOut     );
    void fillFloatParam     (
        domCommon_float_or_param_type                  *floatParam,
        domCommon_float_or_param_type::domFloatRef     &floatOut,
        domCommon_float_or_param_type::domParamRef     &paramOut   );

    void addTexture(const std::string     &texId,
                    const std::string     &tcSemantic,
                    ColladaInstanceEffect *colInstEffect,
                    ColladaSampler2D      *colSampler2D,
                    ChunkMaterial         *mat,
                    GLenum                 envMode,
                    UInt32                &texCount       );

    Real32 luminance(const Color4f &col);

    static ColladaElementRegistrationHelper _regHelper;

    ParamSampler2DMap _sampler2DParams;
    ParamSurfaceMap   _surfaceParams;
};

OSG_GEN_MEMOBJPTR(ColladaEffect);

OSG_END_NAMESPACE

// #include "OSGColladaEffect.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAEFFECT_H_
