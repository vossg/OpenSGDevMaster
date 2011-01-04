/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2009 by the OpenSG Forum                   *
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

#ifndef _OSGSHADERSHADOWMAPENGINE_H_
#define _OSGSHADERSHADOWMAPENGINE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGShaderShadowMapEngineBase.h"

#include "OSGShaderShadowMapEngineData.h"
#include "OSGLight.h"
#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGShaderProgramChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief ShaderShadowMapEngine class. See \ref
           PageEffectGroupsShaderShadowMapEngine for a description.
    \ingroup GrpGroupLightShadowEnginesObj
    \ingroup GrpLibOSGGroup
    \includebasedoc
*/

class OSG_GROUP_DLLMAPPING ShaderShadowMapEngine : 
    public ShaderShadowMapEngineBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ShaderShadowMapEngineBase Inherited;
    typedef ShaderShadowMapEngine     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                       Render                                 */
    /*! \{                                                                 */

    virtual ActionBase::ResultE runOnEnter(Light        *light,
                                           LightTypeE    eType,
                                           RenderAction *ract);
    virtual ActionBase::ResultE runOnLeave(Light        *light,
                                           LightTypeE    eType,
                                           RenderAction *ract);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ShaderShadowMapEngineBase.

    typedef ShaderShadowMapEngineData           SSMEngineData;
    typedef ShaderShadowMapEngineDataUnrecPtr   SSMEngineDataUnrecPtr;

    static const Matrix      _matCubeFaceInv [6];
    static const GLenum      _cubeFaceTargets[6];
    
    static const std::string _pointFPCode;
    static const std::string _dirFPCode;
    static const std::string _spotFPCode;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShaderShadowMapEngine(void);
    ShaderShadowMapEngine(const ShaderShadowMapEngine &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShaderShadowMapEngine(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Render Helper                               */
    /*! \{                                                                 */

    void handleEnter                (Light            *light,
                                     LightTypeE        eType,
                                     RenderAction     *ract,
                                     SSMEngineData    *data   );
    void handlePointLightEnter      (PointLight       *pointL,
                                     RenderAction     *ract,
                                     SSMEngineData    *data   );
    void handleDirectionalLightEnter(DirectionalLight *dirL,
                                     RenderAction     *ract,
                                     SSMEngineData    *data   );
    void handleSpotLightEnter       (SpotLight        *spotL,
                                     RenderAction     *ract,
                                     SSMEngineData    *data   );

    void calcDirectionalLightMatrices(      Matrix           &matWorldToLight,
                                            Matrix           &matEyeToLight,
                                      const DirectionalLight *dirL, 
                                      const Matrix           &matEyeToWorld   );
    void calcPointLightMatrices      (      Matrix           &matWorldToLight,
                                            Matrix           &matEyeToLight,
                                      const PointLight       *pointL, 
                                      const Matrix           &matEyeToWorld   );
    void calcSpotLightMatrices       (      Matrix           &matWorldToLight,
                                            Matrix           &matEyeToLight,
                                      const SpotLight        *spotL, 
                                      const Matrix           &matEyeToWorld   );

    void calcPointLightRange         (const PointLight       *pointL,
                                            Real32            lightThreshold,
                                            Real32            defaultNear,
                                            Real32            defaultFar,
                                            Real32           &outNear,
                                            Real32           &outFar          );

    void updateShadowTexChunk            (SSMEngineData *data);
    void updateLightPassMaterial         (SSMEngineData *data);
    void updateBackground                (SSMEngineData *data);

    void updatePointLightShadowTexImage  (SSMEngineData *data);
    void updateShadowTexImage            (SSMEngineData *data);

    void updatePointLightShadowTexBuffers(SSMEngineData *data);
    void updateShadowTexBuffers          (SSMEngineData *data);

    void updatePointLightRenderTargets   (SSMEngineData *data);
    void updateRenderTargets             (SSMEngineData *data);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ShaderShadowMapEngineBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ShaderShadowMapEngine &source);
};

typedef ShaderShadowMapEngine *ShaderShadowMapEngineP;

OSG_END_NAMESPACE

#include "OSGShaderShadowMapEngineBase.inl"
#include "OSGShaderShadowMapEngine.inl"

#endif /* _OSGSHADERSHADOWMAPENGINE_H_ */
