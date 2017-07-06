/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           * * This library is free software; you can redistribute it and/or modify it   *
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

#ifndef _OSGMULTILIGHTCHUNK_H_
#define _OSGMULTILIGHTCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiLightChunkBase.h"

OSG_BEGIN_NAMESPACE

struct OSG_SYSTEM_DLLMAPPING  MultiLight
{
    enum Type
    {
        POINT_LIGHT = 1,
        DIRECTIONAL_LIGHT = 2,
        SPOT_LIGHT = 3,
        CINEMA_LIGHT = 4
    };

    enum Layout {
         SIMPLE_LAYOUT = 0x01,  // Color,Intensity,RangeCutOff
          RANGE_LAYOUT = 0x02,  // RangeCutOn, RangeCutOff
           ZONE_LAYOUT = 0x04,  // RangeNearZone, RangeFarZone
         OPENGL_LAYOUT = 0x08,  // Ambient-, Diffuse-, Specular Intensity, Attenuation
         CINEMA_LAYOUT = 0x10   // SuperEllipses
    };

    explicit MultiLight(Type e);

    Pnt3f       position;
    Vec3f       direction;
    Color3f     color;
    Real32      intensity;
    Vec3f       ambientIntensity;
    Vec3f       diffuseIntensity;
    Vec3f       specularIntensity;
    Vec3f       attenuation;
    Real32      spotlightAngle;
    Real32      spotExponent;
    Real32      innerSuperEllipsesWidth;
    Real32      innerSuperEllipsesHeight;
    Real32      outerSuperEllipsesWidth;
    Real32      outerSuperEllipsesHeight;
    Real32      superEllipsesRoundness;
    Real32      superEllipsesTwist;
    Real32      rangeCutOn;
    Real32      rangeCutOff;
    Real32      rangeNearZone;
    Real32      rangeFarZone;
    Type        type;
    bool        enabled;
    NodeRefPtr  beacon;
};

/*! \brief MultiLightChunk class. See \ref
           PageSystemMultiLightChunk for a description.
*/

class OSG_SYSTEM_DLLMAPPING MultiLightChunk : public MultiLightChunkBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiLightChunkBase Inherited;
    typedef MultiLightChunk     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Interface                               */
    /*! \{                                                                 */

          UInt32               addLight                     (MultiLight::Type eType);
          UInt32               addLight                     (const MultiLight& light);
          void                 updateLight                  (const UInt32 idx, const MultiLight& light);
          void                 removeLight                  (const UInt32 idx);
          void                 clearLights                  ();
          UInt32               numLights                    () const;
          void                 setLayoutType                (UInt32 layout);

    const Pnt3f               &getPosition                  (const UInt32 idx) const;
    const Vec3f               &getDirection                 (const UInt32 idx) const;
    const Color3f             &getColor                     (const UInt32 idx) const;
          Real32               getIntensity                 (const UInt32 idx) const;
    const Vec3f               &getAmbientIntensity          (const UInt32 idx) const;
    const Vec3f               &getDiffuseIntensity          (const UInt32 idx) const;
    const Vec3f               &getSpecularIntensity         (const UInt32 idx) const;
    const Vec3f               &getAttenuation               (const UInt32 idx) const;
          Real32               getRange                     (const UInt32 idx) const;
          Real32               getSpotlightAngle            (const UInt32 idx) const;
          Real32               getSpotExponent              (const UInt32 idx) const;
          Real32               getInnerSuperEllipsesWidth   (const UInt32 idx) const;
          Real32               getInnerSuperEllipsesHeight  (const UInt32 idx) const;
          Real32               getOuterSuperEllipsesWidth   (const UInt32 idx) const;
          Real32               getOuterSuperEllipsesHeight  (const UInt32 idx) const;
          Real32               getSuperEllipsesRoundness    (const UInt32 idx) const;
          Real32               getSuperEllipsesTwist        (const UInt32 idx) const;
          Real32               getRangeCutOn                (const UInt32 idx) const;
          Real32               getRangeCutOff               (const UInt32 idx) const;
          Real32               getRangeNearZone             (const UInt32 idx) const;
          Real32               getRangeFarZone              (const UInt32 idx) const;
          UInt8                getType                      (const UInt32 idx) const;
          bool                 getEnabled                   (const UInt32 idx) const;
          Node*                getBeacon                    (const UInt32 idx) const;

          void                 setPosition                  (const UInt32 idx, const Pnt3f& position);
          void                 setDirection                 (const UInt32 idx, const Vec3f& direction);
          void                 setColor                     (const UInt32 idx, const Color3f& color);
          void                 setIntensity                 (const UInt32 idx, Real32 intensity);
          void                 setAmbientIntensity          (const UInt32 idx, const Vec3f& intensity);
          void                 setDiffuseIntensity          (const UInt32 idx, const Vec3f& intensity);
          void                 setSpecularIntensity         (const UInt32 idx, const Vec3f& intensity);
          void                 setAttenuation               (const UInt32 idx, const Vec3f& attenuation);
          void                 setRange                     (const UInt32 idx, Real32 range);
          void                 setSpotlightAngle            (const UInt32 idx, Real32 angle);
          void                 setSpotExponent              (const UInt32 idx, Real32 exponent);
          void                 setInnerSuperEllipsesWidth   (const UInt32 idx, Real32 width);
          void                 setInnerSuperEllipsesHeight  (const UInt32 idx, Real32 height);
          void                 setOuterSuperEllipsesWidth   (const UInt32 idx, Real32 width);
          void                 setOuterSuperEllipsesHeight  (const UInt32 idx, Real32 height);
          void                 setSuperEllipsesRoundness    (const UInt32 idx, Real32 roundness);
          void                 setSuperEllipsesTwist        (const UInt32 idx, Real32 twist);
          void                 setRangeCutOn                (const UInt32 idx, Real32 cutOn);
          void                 setRangeCutOff               (const UInt32 idx, Real32 cutOff);
          void                 setRangeNearZone             (const UInt32 idx, Real32 nearZone);
          void                 setRangeFarZone              (const UInt32 idx, Real32 farZone);
          void                 setType                      (const UInt32 idx, MultiLight::Type eType);
          void                 setEnabled                   (const UInt32 idx, bool flag);
          void                 setBeacon                    (const UInt32 idx, Node* const beacon);

          void                 changedBeacon                ();

          std::string          getLightProgSnippet          () const;

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
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate   (DrawEnv    *pEnv,
                             UInt32      index = 0);

    virtual void changeFrom (DrawEnv    *pEnv,
                             StateChunk *pOld,
                             UInt32      index = 0);

    virtual void deactivate (DrawEnv    *pEnv,
                             UInt32      index = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             OpenGL handling                                  */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    bool   _bUpdateBuffer;

    ChangedFunctor  _cameraCB;

    // Variables should all be in MultiLightChunkBase.

    void onCreate      (const MultiLightChunk *source      = NULL);
    void onCreateAspect(const MultiLightChunk *createAspect,
                        const MultiLightChunk *source      = NULL);
    void onDestroy     (      UInt32           uiContainerId     );

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightChunk(void);
    MultiLightChunk(const MultiLightChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiLightChunkBase;

    /*---------------------------------------------------------------------*/
    /*! \name                         buffer                               */
    /*! \{                                                                 */
    void    transformToWorldSpace           (DrawEnv* pEnv,
                                             Node* beacon, 
                                             const Pnt3f& position_bs, 
                                             const Vec3f& direction_bs, 
                                             Pnt3f& position_ws, 
                                             Vec3f& direction_ws) const;

    void    transformToEyeSpace             (DrawEnv* pEnv,
                                             Node* beacon, 
                                             const Pnt3f& position_bs, 
                                             const Vec3f& direction_bs, 
                                             Pnt3f& position_es, 
                                             Vec3f& direction_es) const;

    void    calcDirectionalLightMatrices    (DrawEnv* pEnv,
                                             Node* beacon, 
                                             const Vec3f& direction_bs, 
                                             Matrix& matLSFromWS,
                                             Matrix& matLSFromES) const;

    void    calcPointLightMatrices          (DrawEnv* pEnv,
                                             Node* beacon, 
                                             const Pnt3f& position_bs, 
                                             Matrix& matLSFromWS,
                                             Matrix& matLSFromES) const;

    void    calcSpotLightMatrices           (DrawEnv* pEnv,
                                             Node* beacon, 
                                             const Pnt3f& position_bs, 
                                             const Vec3f& direction_bs, 
                                             Matrix& matLSFromWS,
                                             Matrix& matLSFromES) const;

    void    calcPointLightRange             (DrawEnv* pEnv,
                                             const Vec3f attenuation,
                                             Real32 threshold,
                                             Real32& outNear,
                                             Real32& outFar) const;

    std::size_t         calcLightBufferSize     () const;
    std::vector<UInt8>  createLightBuffer       (DrawEnv* pEnv) const;
    void                createLightState        (DrawEnv* pEnv);
    void                updateLightState        (DrawEnv* pEnv);

    /*! \}                                                                 */

    bool        check_invariant() const;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiLightChunk &source);
};

typedef MultiLightChunk *MultiLightChunkP;

OSG_END_NAMESPACE

#include "OSGMultiLightChunkBase.inl"
#include "OSGMultiLightChunk.inl"

#endif /* _OSGMULTILIGHTCHUNK_H_ */
