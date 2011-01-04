/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGTRAPEZOIDALSHADOWMAPENGINE_H_
#define _OSGTRAPEZOIDALSHADOWMAPENGINE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTrapezoidalShadowMapEngineBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TrapezoidalShadowMapEngine class. See \ref
           PageGroupTrapezoidalShadowMapEngine for a description.
*/

class OSG_CONTRIBTRAPEZOIDALSHADOWMAPS_DLLMAPPING TrapezoidalShadowMapEngine 
    : public TrapezoidalShadowMapEngineBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TrapezoidalShadowMapEngineBase Inherited;
    typedef TrapezoidalShadowMapEngine     Self;

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

    // Variables should all be in TrapezoidalShadowMapEngineBase.

    typedef ShaderShadowMapEngineData         TSMEngineData;
    typedef ShaderShadowMapEngineDataUnrecPtr TSMEngineDataUnrecPtr;

    static const std::string _lightPassVPCode;
    static const std::string _lightPassFPCode;

    static const std::string _pointFPCode;
    static const std::string _spotFPCode;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TrapezoidalShadowMapEngine(void);
    TrapezoidalShadowMapEngine(const TrapezoidalShadowMapEngine &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TrapezoidalShadowMapEngine(void);

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
                                     TSMEngineData    *data   );
    void handlePointLightEnter      (PointLight       *pointL,
                                     RenderAction     *ract,
                                     TSMEngineData    *data   );
    void handleDirectionalLightEnter(DirectionalLight *dirL,
                                     RenderAction     *ract,
                                     TSMEngineData    *data   );
    void handleSpotLightEnter       (SpotLight        *spotL,
                                     RenderAction     *ract,
                                     TSMEngineData    *data   );

    void intersectFrusta        (const FrustumVolume      &fA,
                                 const FrustumVolume      &fB,
                                       std::vector<Pnt3f> &intVerts,
                                       Pnt3f              &intCenter);
    void updateLightPassMaterial(      TSMEngineData      *data,
                                       UInt16              faceIdx,
                                 const Matrix             &matNT    );


    bool calcTrapezoidalTransform(      Matrix        &matNT,
                                  const Matrix        &matEyeToWorld,
                                  const Matrix        &matLightFull,
                                  const FrustumVolume &eyeFrust,
                                  const FrustumVolume &lightFrust    );

    void emptyCubeFaceDrawFunc   (      DrawEnv       *drawEnv       );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TrapezoidalShadowMapEngineBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TrapezoidalShadowMapEngine &source);
};

typedef TrapezoidalShadowMapEngine *TrapezoidalShadowMapEngineP;

OSG_END_NAMESPACE

#include "OSGTrapezoidalShadowMapEngineBase.inl"
#include "OSGTrapezoidalShadowMapEngine.inl"

#endif /* _OSGTRAPEZOIDALSHADOWMAPENGINE_H_ */
