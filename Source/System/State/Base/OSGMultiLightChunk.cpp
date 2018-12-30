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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGQuaternion.h"

#include "OSGGLFuncProtos.h"
#include "OSGBaseFunctions.h"

#include "OSGDrawEnv.h"
#include "OSGNode.h"

#include "OSGMultiLightChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiLightChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiLightChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiLightChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

MultiLight::MultiLight(Type e)
    : position(0.f,0.f,0.f)
    , direction(0.f,0.f,1.f)
    , color(1.f,1.f,1.f)
    , intensity(1.f)
    , ambientIntensity(1.f,1.f,1.f)
    , diffuseIntensity(1.f,1.f,1.f)
    , specularIntensity(1.f,1.f,1.f)
    , attenuation(1.f, 0.0001f, 0.000001f)
    , spotlightAngle(20.f)
    , spotExponent(1.f)
    , innerSuperEllipsesWidth(1.f)
    , innerSuperEllipsesHeight(1.f)
    , outerSuperEllipsesWidth(1.3f)
    , outerSuperEllipsesHeight(1.3f)
    , superEllipsesRoundness(1.f)
    , superEllipsesTwist(0.f)
    , rangeCutOn(0.f)
    , rangeCutOff(1.f)
    , rangeNearZone(0.f)
    , rangeFarZone(0.f)
    , type(e)
    , enabled(true)
    , beacon(NULL)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiLightChunk::MultiLightChunk(void) :
    Inherited(),
    _bUpdateBuffer(false),
    _cameraCB()
{
}

MultiLightChunk::MultiLightChunk(const MultiLightChunk &source) :
    Inherited(source),
    _bUpdateBuffer(false),
    _cameraCB()
{
}

MultiLightChunk::~MultiLightChunk(void)
{
    clearLights();
}

/*----------------------------- class specific ----------------------------*/

void MultiLightChunk::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    //
    // The BeaconMatrixFieldMask is deliberately omitted
    // 
    if((whichField & ( HasWorldToLightSpaceMatrixFieldMask |
                       HasLightToWorldSpaceMatrixFieldMask |
                       HasEyeToLightSpaceMatrixFieldMask |
                       HasLightToEyeSpaceMatrixFieldMask |
                       HasLightPerspectiveMatrixFieldMask |
                       HasInvLightPerspectiveMatrixFieldMask |
                       HasColorFieldMask |
                       HasIntensityFieldMask |
                       HasSeparateIntensitiesFieldMask |
                       HasAttenuationFieldMask |
                       HasRangeCutOnFieldMask |
                       HasRangeCutOffFieldMask |
                       HasRangeNearZoneFieldMask |
                       HasRangeFarZoneFieldMask |
                       HasCosSpotlightAngleFieldMask |
                       HasSpotlightAngleFieldMask |
                       HasSpotExponentFieldMask |
                       HasCinemaLightFieldMask |
                       AutoCalcRangesFieldMask | 
                       PositionFieldMask |
                       DirectionFieldMask |
                       ColorFieldMask |
                       IntensityFieldMask |
                       AmbientIntensityFieldMask |
                       DiffuseIntensityFieldMask |
                       SpecularIntensityFieldMask |
                       AttenuationFieldMask |
                       RangeCutOnFieldMask |
                       RangeCutOffFieldMask |
                       RangeNearZoneFieldMask |
                       RangeFarZoneFieldMask |
                       SpotlightAngleFieldMask |
                       SpotExponentFieldMask |
                       InnerSuperEllipsesWidthFieldMask |
                       InnerSuperEllipsesHeightFieldMask |
                       OuterSuperEllipsesWidthFieldMask |
                       OuterSuperEllipsesHeightFieldMask |
                       SuperEllipsesRoundnessFieldMask |
                       SuperEllipsesTwistFieldMask |
                       TypeFieldMask |
                       EnabledFieldMask |
                       BeaconFieldMask |
                       EyeSpaceFieldMask )) != 0)
    {
        _bUpdateBuffer = true;
    }

    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void MultiLightChunk::onCreate(const MultiLightChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;
}

void MultiLightChunk::onCreateAspect(
    const MultiLightChunk *createAspect,
    const MultiLightChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void MultiLightChunk::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output -------------------------------------*/

void MultiLightChunk::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump MultiLightChunk NI" << std::endl;
}

/*------------------------------ buffer -------------------------------------*/

void MultiLightChunk::transformToWorldSpace(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    const Vec3f& direction_bs, 
    Pnt3f& position_ws, 
    Vec3f& direction_ws) const
{
    Matrix matWsFromBS;
    matWsFromBS.identity();

    if(beacon != NULL)
    {
        beacon->getToWorld(matWsFromBS);
    }
    else
    {
        matWsFromBS.setIdentity();
    }

    matWsFromBS.multFull( position_bs,  position_ws);
    matWsFromBS.multFull(direction_bs, direction_ws);
}

void MultiLightChunk::transformToEyeSpace(
    DrawEnv* pEnv,
    Node* beacon,
    const Pnt3f& position_bs,
    const Vec3f& direction_bs,
    Pnt3f& position_es,
    Vec3f& direction_es) const
{
    Matrix matWsFromBS;

    if(beacon != NULL)
    {
        beacon->getToWorld(matWsFromBS);
    }
    else
    {
        matWsFromBS.setIdentity();
    }

    Matrix mat = pEnv->getCameraViewing();  // matEsFromWs
    mat.mult(matWsFromBS);                  // matEsFromBs

    mat.multFull( position_bs,  position_es);
    mat.multFull(direction_bs, direction_es);
}

void MultiLightChunk::calcDirectionalLightMatrices(
    DrawEnv* pEnv,
    Node* beacon, 
    const Vec3f& direction_bs,
    Matrix& matLSFromWS,
    Matrix& matLSFromES) const
{
    if(beacon)
        beacon->getToWorld(matLSFromWS);    // matWsFromBS;

    Matrix     matLightDir;
    Quaternion rotLightDir(Vec3f(0.f, 0.f, 1.f), direction_bs);
    matLightDir.setRotate(rotLightDir);

    matLSFromWS.mult        (matLightDir);
    matLSFromWS.invert      (           );  // WS -> LS

    Matrix matWsFromEs = pEnv->getCameraToWorld();
    matLSFromES = matLSFromWS;
    matLSFromES.mult(matWsFromEs);
}

void MultiLightChunk::calcPointLightMatrices(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    Matrix& matLSFromWS,
    Matrix& matLSFromES) const
{
    if(beacon)
        beacon->getToWorld(matLSFromWS);    // matWsFromBS;

    Matrix matLightPos;
    matLightPos.setTranslate(position_bs);

    matLSFromWS.mult        (matLightPos);
    matLSFromWS.invert      (           );  // WS -> LS

    Matrix matWsFromEs = pEnv->getCameraToWorld();
    matLSFromES = matLSFromWS;
    matLSFromES.mult(matWsFromEs);
}

void MultiLightChunk::calcSpotLightMatrices(
    DrawEnv* pEnv,
    Node* beacon, 
    const Pnt3f& position_bs, 
    const Vec3f& direction_bs, 
    Matrix& matLSFromWS,
    Matrix& matLSFromES) const
{
    if(beacon)
        beacon->getToWorld(matLSFromWS);    // matWsFromBS;

    Matrix matLightPos;
    matLightPos.setTranslate(position_bs);

    Matrix     matLightDir;
    Quaternion rotLightDir(Vec3f(0.f, 0.f, 1.f), -direction_bs);
    matLightDir.setRotate(rotLightDir);

    matLSFromWS.mult        (matLightPos);
    matLSFromWS.mult        (matLightDir);
    matLSFromWS.invert      (           );  // WS -> LS

    Matrix matWsFromEs = pEnv->getCameraToWorld();
    matLSFromES = matLSFromWS;
    matLSFromES.mult(matWsFromEs);
}

void MultiLightChunk::calcPointLightRange(
    DrawEnv*    pEnv,
    const Vec3f attenuation,
    Real32      threshold,
    Real32&     outNear,
    Real32&     outFar) const
{
    Real32 defaultNear = pEnv->getCameraNear();
    Real32 defaultFar  = pEnv->getCameraFar();

    outNear = defaultNear;
    outFar  = defaultFar;

    Real32 q = attenuation[2];
    Real32 l = attenuation[1];
    Real32 c = attenuation[0];

    if (osgAbs(q) > TypeTraits<Real32>::getDefaultEps())
    {
        Real32 D = l*l - 4.f * q * (c - 1.f/threshold);

        if (D >= 0)
        {
                    D = osgSqrt(D);

            Real32 r1 = - l + D / (2.f * q);
            Real32 r2 = - l - D / (2.f * q);

            if (r1 > 0.f && r2 > 0.f)
            {
                outFar = osgMin(r1, r2);
            }
            else if (r1 > 0.f)
            {
                outFar = r1;
            }
            else if (r2 > 0.f)
            {
                outFar = r2;
            }
        }
    }
    else if(osgAbs(l) > TypeTraits<Real32>::getDefaultEps())
    {
        Real32 r = (1.f/threshold - c)/l;

        if (r > 0.f)
        {
            outFar = r;
        }
    }
}

std::size_t MultiLightChunk::calcLightBufferSize() const
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    OSG_ASSERT(check_invariant());

    //struct Light
    //{
    //    mat4  worldToLightSpaceMatrix;
    //    mat4  lightToWorldSpaceMatrix;
    //    mat4  eyeToLightSpaceMatrix;
    //    mat4  lightToEyeSpaceMatrix;
    //    mat4  lightPerspectiveMatrix
    //    mat4  InvLightPerspectiveMatrix;
    //    vec3  position;
    //    vec3  direction;
    //    vec3  color;
    //    vec3  ambientIntensity;
    //    vec3  diffuseIntensity;
    //    vec3  specularIntensity;
    //    float intensity;
    //    float constantAttenuation;
    //    float linearAttenuation;
    //    float quadraticAttenuation;
    //    float rangeCutOn;
    //    float rangeCutOff;
    //    float rangeNearZone;
    //    float rangeFarZone;
    //    float cosSpotlightAngle;
    //    float spotlightAngle;
    //    float spotExponent;
    //    float innerSuperEllipsesWidth;
    //    float innerSuperEllipsesHeight;
    //    float outerSuperEllipsesWidth;
    //    float outerSuperEllipsesHeight;
    //    float superEllipsesRoundness;
    //    float superEllipsesTwist;
    //    int   type;
    //    bool  enabled;
    //};

    if (getHasWorldToLightSpaceMatrix())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f); // Matrix  worldToLightSpaceMatrix
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao;
    }

    if (getHasLightToWorldSpaceMatrix())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f); // Matrix  lightToWorldSpaceMatrix
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao;
    }

    if (getHasEyeToLightSpaceMatrix())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f); // Matrix  eyeToLightSpaceMatrix
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao;
    }

    if (getHasLightToEyeSpaceMatrix())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f); // Matrix  lightToEyeSpaceMatrix
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao;
    }

    if (getHasLightPerspectiveMatrix())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f); // Matrix  lightPerspectiveMatrix
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao;
    }

    if (getHasInvLightPerspectiveMatrix())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f); // Matrix  invLightPerspectiveMatrix
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao + sizeof(OSG::Vec4f);
        ao = alignOffset(16, bo); bo = ao;
    }

    ao = alignOffset(16, bo); bo = ao + sizeof(Pnt3f);         // Pnt3f   position
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);         // Vec3f   direction

    if (getHasColor())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Color3f);   // Color3f color
    }

    if (getHasSeparateIntensities())
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);     // Vec3f   ambientIntensity
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);     // Vec3f   diffuseIntensity
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);     // Vec3f   specularIntensity
    }

    if (getHasIntensity())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  intensity
    }

    if (getHasAttenuation())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  constantAttenuation
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  linearAttenuation
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  quadraticAttenuation
    }

    if (getHasRangeCutOn())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeCutOn
    }

    if (getHasRangeCutOff())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeCutOff
    }

    if (getHasRangeNearZone())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeNearZone
    }

    if (getHasRangeFarZone())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  rangeFarZone
    }

    if (getHasCosSpotlightAngle() || (!getHasCosSpotlightAngle() && !getHasSpotlightAngle()))
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  cosSpotlightAngle
    }

    if (getHasSpotlightAngle())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  spotlightAngle
    }

    if (getHasSpotExponent())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);     // Real32  spotExponent
    }

    if (getHasCinemaLight())
    {
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  innerSuperEllipsesWidth
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  innerSuperEllipsesHeight
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  outerSuperEllipsesWidth
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  outerSuperEllipsesHeight
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  superEllipsesRoundness
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);    // Real32  superEllipsesTwist
    }

    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);         // UInt8   type
    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);         // bool    enabled

    ao = alignOffset(16, bo); bo = ao;                         // padding

    ao *= numLights();         bo = ao;                        // array
    ao = alignOffset(16, bo); bo = ao;                         // padding

    return ao;
}

std::vector<UInt8> MultiLightChunk::createLightBuffer(DrawEnv* pEnv) const
{
    std::size_t size = calcLightBufferSize();

    std::vector<UInt8> buffer(size);

    UInt32 num_lights = numLights();

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (UInt32 idx = 0; idx < num_lights; ++idx)
    {
        Pnt3f position;
        Vec3f direction;
        
        Real32  cosSpotlightAngle = 1.f;
        Real32  spotlightAngle    = 0.f;

        switch (getType(idx))
        {
            case MultiLight::POINT_LIGHT:
                break;
            case MultiLight::DIRECTIONAL_LIGHT:
                break;
            case MultiLight::SPOT_LIGHT:
                cosSpotlightAngle = osgCos(osgDegree2Rad(getSpotlightAngle(idx)));
                spotlightAngle    = osgDegree2Rad(getSpotlightAngle(idx));
                break;
            case MultiLight::CINEMA_LIGHT:
                break;
        }

        Real32  cutOnRange = getHasRangeCutOn () ? getRangeCutOn (idx) : pEnv->getCameraNear();
        Real32 cutOffRange = getHasRangeCutOff() ? getRangeCutOff(idx) : pEnv->getCameraFar();

        if (getAutoCalcRanges() && getHasAttenuation())
        {
            const Real32 threshold = 0.001f;
            calcPointLightRange(pEnv, getAttenuation(idx), threshold, cutOnRange, cutOffRange);
        }

        if (getEyeSpace())
        {
            transformToEyeSpace(
                    pEnv, getBeacon(idx), 
                    getPosition(idx), getDirection(idx), 
                    position, direction);
        }
        else
        {
            transformToWorldSpace(
                    pEnv, getBeacon(idx), 
                    getPosition(idx), getDirection(idx), 
                    position, direction);
        }

        Matrix matLSFromWS, matWSFromLS, matLSFromES, matESFromLS;
        if (getHasWorldToLightSpaceMatrix() || getHasLightToWorldSpaceMatrix() || getHasEyeToLightSpaceMatrix() || getHasLightToEyeSpaceMatrix())
        {
            switch (getType(idx))
            {
                case MultiLight::POINT_LIGHT:
                    calcPointLightMatrices(pEnv, getBeacon(idx), getPosition(idx), matLSFromWS, matLSFromES);
                    break;
                case MultiLight::DIRECTIONAL_LIGHT:
                    calcDirectionalLightMatrices(pEnv, getBeacon(idx), getDirection(idx), matLSFromWS, matLSFromES);
                    break;
                case MultiLight::SPOT_LIGHT:
                case MultiLight::CINEMA_LIGHT:
                    calcSpotLightMatrices(pEnv, getBeacon(idx), getPosition(idx), getDirection(idx), matLSFromWS, matLSFromES);
                    break;
            }
        }

        if (getHasWorldToLightSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromWS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasLightToWorldSpaceMatrix())
        {
            matLSFromWS.inverse(matWSFromLS);

            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matWSFromLS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasEyeToLightSpaceMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLSFromES[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasLightToEyeSpaceMatrix())
        {
            matLSFromES.inverse(matESFromLS);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matESFromLS[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        Matrix matLightPerspProj, matInvLightPerspProj;
        if (getHasLightPerspectiveMatrix() || getHasInvLightPerspectiveMatrix())
        {
            switch (getType(idx))
            {
                case MultiLight::POINT_LIGHT:
                    MatrixPerspective(matLightPerspProj, Pi / 4.f, 1.f, cutOnRange, cutOffRange);
                    break;
                case MultiLight::DIRECTIONAL_LIGHT:
                    break;
                case MultiLight::SPOT_LIGHT:
                    MatrixPerspective(matLightPerspProj, cosSpotlightAngle, 1.f, cutOnRange, cutOffRange);
                    break;
                case MultiLight::CINEMA_LIGHT:
                    {
                        Real32 s = osgMax(osgMax(getInnerSuperEllipsesWidth(idx), getInnerSuperEllipsesHeight(idx)),
                                          osgMax(getOuterSuperEllipsesWidth(idx), getOuterSuperEllipsesHeight(idx)));

                        Real32 a = osgATan(s/1.f);
                        cosSpotlightAngle = cos(a);
                        spotlightAngle    = a;

                        MatrixPerspective(matLightPerspProj, cosSpotlightAngle, 1.f, cutOnRange, cutOffRange);
                    }
                    break;
            }
        }

        if (getHasLightPerspectiveMatrix())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLightPerspProj[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLightPerspProj[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLightPerspProj[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matLightPerspProj[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        if (getHasInvLightPerspectiveMatrix())
        {
            matLightPerspProj.inverse(matInvLightPerspProj);

            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvLightPerspProj[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvLightPerspProj[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvLightPerspProj[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &matInvLightPerspProj[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
        }

        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &position [0], sizeof(Pnt3f)); bo = ao + sizeof(Pnt3f);
        ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &direction[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);

        if (getHasColor())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getColor(idx)[0], sizeof(Color3f)); bo = ao + sizeof(Color3f);
        }

        if (getHasSeparateIntensities())
        {
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getAmbientIntensity (idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getDiffuseIntensity (idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &getSpecularIntensity(idx)[0], sizeof(Vec3f)); bo = ao + sizeof(Vec3f);
        }

        if (getHasIntensity())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getIntensity(idx); bo = ao + sizeof(Real32);
        }

        if (getHasAttenuation())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getAttenuation(idx)[0]; bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getAttenuation(idx)[1]; bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getAttenuation(idx)[2]; bo = ao + sizeof(Real32);
        }

        if (getHasRangeCutOn())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cutOnRange; bo = ao + sizeof(Real32);
        }

        if (getHasRangeCutOff())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cutOffRange; bo = ao + sizeof(Real32);
        }

        if (getHasRangeNearZone())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getRangeNearZone(idx); bo = ao + sizeof(Real32);
        }

        if (getHasRangeFarZone())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getRangeFarZone (idx); bo = ao + sizeof(Real32);
        }

        if (getHasCosSpotlightAngle() || (!getHasCosSpotlightAngle() && !getHasSpotlightAngle()))
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = cosSpotlightAngle; bo = ao + sizeof(Real32);
        }

        if (getHasSpotlightAngle())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = spotlightAngle; bo = ao + sizeof(Real32);
        }

        if (getHasSpotExponent())
        {
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getSpotExponent(idx); bo = ao + sizeof(Real32);
        }

        if (getHasCinemaLight())
        {
            OSG::Real32 twistAngle = osgDegree2Rad(getSuperEllipsesTwist(idx));

            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getInnerSuperEllipsesWidth (idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getInnerSuperEllipsesHeight(idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getOuterSuperEllipsesWidth (idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getOuterSuperEllipsesHeight(idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = getSuperEllipsesRoundness  (idx); bo = ao + sizeof(Real32);
            ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = twistAngle;                       bo = ao + sizeof(Real32);
        }

        ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = Int32(getType(idx)); bo = ao + sizeof(Int32);
        ao = alignOffset( 4, bo); *(reinterpret_cast<bool* >(&buffer[0] + ao)) = getEnabled(idx);     bo = ao + sizeof(Int32);

        ao = alignOffset(16, bo); bo = ao;    // padding
    }

    return buffer;
}

void MultiLightChunk::createLightState(DrawEnv* pEnv)
{
    std::vector<UInt8> buffer = createLightBuffer(pEnv);
    editMFBuffer()->setValues(buffer);
}

void MultiLightChunk::updateLightState(DrawEnv* pEnv)
{
    std::vector<UInt8> buffer = createLightBuffer(pEnv);
    editMFBuffer()->setValues(buffer);

    setLastCamNear   (pEnv->getCameraNear());
    setLastCamFar    (pEnv->getCameraFar());
    setLastCamToWorld(pEnv->getCameraToWorld());

    for (std::size_t idx = 0; idx < _mfBeacon.size(); ++idx)
    {
        Matrix matWsFromBS;
        Node* beacon = getBeacon(UInt32(idx));
        if (beacon)
        {
            beacon->getToWorld(matWsFromBS);

            editMField(BeaconMatrixFieldMask, _mfBeaconMatrix);
            _mfBeaconMatrix[idx] = matWsFromBS;
        }
    }

    _bUpdateBuffer = false;
}

/*------------------------------ activate -----------------------------------*/

void MultiLightChunk::activate(DrawEnv *pEnv, UInt32 index)
{
    if (getLastCamNear   () != pEnv->getCameraNear() ||
        getLastCamFar    () != pEnv->getCameraFar()  ||
        getLastCamToWorld() != pEnv->getCameraToWorld())
    {
        _bUpdateBuffer = true;
    } 
    else
    {
        for (std::size_t idx = 0; idx < _mfBeacon.size(); ++idx)
        {
            Matrix matWsFromBS;
            Node* beacon = getBeacon(UInt32(idx));
            if (beacon)
            {
                beacon->getToWorld(matWsFromBS);

                if (matWsFromBS != _mfBeaconMatrix[idx])
                {
                    _bUpdateBuffer = true;
                    break;
                }
            }
        }
    }

    if (_bUpdateBuffer)
        updateLightState(pEnv);

    Inherited::activate(pEnv, index);
}

/*------------------------------ deactivate ---------------------------------*/

void MultiLightChunk::deactivate(DrawEnv *pEnv, UInt32 index)
{
    Inherited::deactivate(pEnv, index);
}

/*------------------------------ changeFrom ---------------------------------*/

void MultiLightChunk::changeFrom(DrawEnv    *pEnv,
                                 StateChunk *old,
                                 UInt32      index )
{
    Inherited::changeFrom(pEnv, old, index);
}

/*------------------------------ interface ----------------------------------*/

UInt32 MultiLightChunk::addLight(MultiLight::Type eType)
{
    if (!check_invariant())
        clearLights();

    editMField(PositionFieldMask,           _mfPosition);
    editMField(DirectionFieldMask,          _mfDirection);
    editMField(SpotlightAngleFieldMask,     _mfSpotlightAngle);
    editMField(TypeFieldMask,               _mfType);
    editMField(EnabledFieldMask,            _mfEnabled);
    editMField(BeaconFieldMask,             _mfBeacon);
    editMField(BeaconMatrixFieldMask,       _mfBeaconMatrix);

    _mfPosition.        push_back(Pnt3f(0.f,0.f,0.f));
    _mfDirection.       push_back(Vec3f(0.f,0.f,1.f));
    _mfSpotlightAngle.  push_back(45.f);
    _mfType.            push_back(eType);
    _mfEnabled.         push_back(false);
                        pushToBeacon(NULL);
    _mfBeaconMatrix.    push_back(Matrix());

    if (getHasSeparateIntensities())
    {
        editMField(AmbientIntensityFieldMask,   _mfAmbientIntensity);
        editMField(DiffuseIntensityFieldMask,   _mfDiffuseIntensity);
        editMField(SpecularIntensityFieldMask,  _mfSpecularIntensity);

        _mfAmbientIntensity. push_back(Vec3f(1.f,1.f,1.f));
        _mfDiffuseIntensity. push_back(Vec3f(1.f,1.f,1.f));
        _mfSpecularIntensity.push_back(Vec3f(1.f,1.f,1.f));
    }

    if (getHasColor())
    {
        editMField(ColorFieldMask,          _mfColor);
        _mfColor.push_back(Vec3f(1.f,1.f,1.f));
    }

    if (getHasIntensity())
    {
        editMField(IntensityFieldMask,      _mfIntensity);
        _mfIntensity.push_back(1.f);
    }

    if (getHasAttenuation())
    {
        editMField(AttenuationFieldMask,    _mfAttenuation);
        _mfAttenuation.push_back(Vec3f(1.f,0.f,0.f));
    }

    if (getHasRangeCutOn())
    {
        editMField(RangeCutOnFieldMask,     _mfRangeCutOn);
        _mfRangeCutOn.push_back(0.f);
    }

    if (getHasRangeCutOff())
    {
        editMField(RangeCutOffFieldMask,    _mfRangeCutOff);
        _mfRangeCutOff.push_back(0.f);
    }

    if (getHasRangeNearZone())
    {
        editMField(RangeNearZoneFieldMask,  _mfRangeNearZone);
        _mfRangeNearZone.push_back(0.f);
    }

    if (getHasRangeFarZone())
    {
        editMField(RangeFarZoneFieldMask,   _mfRangeFarZone);
        _mfRangeFarZone.push_back(0.f);
    }

    if (getHasSpotExponent())
    {
        editMField(SpotExponentFieldMask,   _mfSpotExponent);
        _mfSpotExponent.push_back(1.f);
    }

    if (getHasCinemaLight())
    {
        editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
        editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
        editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
        editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
        editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
        editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);

        _mfInnerSuperEllipsesWidth. push_back(1.f);
        _mfInnerSuperEllipsesHeight.push_back(1.f);
        _mfOuterSuperEllipsesWidth. push_back(1.f);
        _mfOuterSuperEllipsesHeight.push_back(1.f);
        _mfSuperEllipsesRoundness.  push_back(0.f);
        _mfSuperEllipsesTwist.      push_back(0.f);
    }

    OSG_ASSERT(check_invariant());

    return UInt32(_mfPosition.size() - 1);
}

UInt32 MultiLightChunk::addLight(const MultiLight& light)
{
    if (!check_invariant())
        clearLights();

    editMField(PositionFieldMask,           _mfPosition);
    editMField(DirectionFieldMask,          _mfDirection);
    editMField(SpotlightAngleFieldMask,     _mfSpotlightAngle);
    editMField(TypeFieldMask,               _mfType);
    editMField(EnabledFieldMask,            _mfEnabled);
    editMField(BeaconFieldMask,             _mfBeacon);
    editMField(BeaconMatrixFieldMask,       _mfBeaconMatrix);

    _mfPosition.        push_back(light.position);
    _mfDirection.       push_back(light.direction);
    _mfSpotlightAngle.  push_back(light.spotlightAngle);
    _mfType.            push_back(light.type);
    _mfEnabled.         push_back(light.enabled);
                        pushToBeacon(light.beacon);
    _mfBeaconMatrix.    push_back(Matrix());

    if (getHasSeparateIntensities())
    {
        editMField(AmbientIntensityFieldMask,   _mfAmbientIntensity);
        editMField(DiffuseIntensityFieldMask,   _mfDiffuseIntensity);
        editMField(SpecularIntensityFieldMask,  _mfSpecularIntensity);

        _mfAmbientIntensity. push_back(light.ambientIntensity);
        _mfDiffuseIntensity. push_back(light.diffuseIntensity);
        _mfSpecularIntensity.push_back(light.specularIntensity);
    }

    if (getHasColor())
    {
        editMField(ColorFieldMask,          _mfColor);
        _mfColor.push_back(light.color);
    }

    if (getHasIntensity())
    {
        editMField(IntensityFieldMask,      _mfIntensity);
        _mfIntensity.push_back(light.intensity);
    }

    if (getHasAttenuation())
    {
        editMField(AttenuationFieldMask,    _mfAttenuation);
        _mfAttenuation.push_back(light.attenuation);
    }

    if (getHasRangeCutOn())
    {
        editMField(RangeCutOnFieldMask,     _mfRangeCutOn);
        _mfRangeCutOn.push_back(light.rangeCutOn);
    }

    if (getHasRangeCutOff())
    {
        editMField(RangeCutOffFieldMask,    _mfRangeCutOff);
        _mfRangeCutOff.push_back(light.rangeCutOff);
    }

    if (getHasRangeNearZone())
    {
        editMField(RangeNearZoneFieldMask,  _mfRangeNearZone);
        _mfRangeNearZone.push_back(light.rangeNearZone);
    }

    if (getHasRangeFarZone())
    {
        editMField(RangeFarZoneFieldMask,   _mfRangeFarZone);
        _mfRangeFarZone.push_back(light.rangeFarZone);
    }

    if (getHasSpotExponent())
    {
        editMField(SpotExponentFieldMask,   _mfSpotExponent);
        _mfSpotExponent.push_back(light.spotExponent);
    }

    if (getHasCinemaLight())
    {
        editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
        editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
        editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
        editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
        editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
        editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);

        _mfInnerSuperEllipsesWidth. push_back(light.innerSuperEllipsesWidth);
        _mfInnerSuperEllipsesHeight.push_back(light.innerSuperEllipsesHeight);
        _mfOuterSuperEllipsesWidth. push_back(light.outerSuperEllipsesWidth);
        _mfOuterSuperEllipsesHeight.push_back(light.outerSuperEllipsesHeight);
        _mfSuperEllipsesRoundness.  push_back(light.superEllipsesRoundness);
        _mfSuperEllipsesTwist.      push_back(light.superEllipsesTwist);
    }

    OSG_ASSERT(check_invariant());

    return UInt32(_mfPosition.size() - 1);
}

void MultiLightChunk::updateLight(const UInt32 idx, const MultiLight& light)
{
    setPosition         (idx, light.position);
    setDirection        (idx, light.direction);
    setSpotlightAngle   (idx, light.spotlightAngle);
    setType             (idx, light.type);
    setEnabled          (idx, light.enabled);
    setBeacon           (idx, light.beacon);

    if (getHasSeparateIntensities())
    {
        setAmbientIntensity (idx, light.ambientIntensity);
        setDiffuseIntensity (idx, light.diffuseIntensity);
        setSpecularIntensity(idx, light.specularIntensity);
    }

    if (getHasColor())
    {
        setColor(idx, light.color);
    }

    if (getHasIntensity())
    {
        setIntensity(idx, light.intensity);
    }

    if (getHasAttenuation())
    {
        setAttenuation(idx, light.attenuation);
    }

    if (getHasRangeCutOn())
    {
        setRangeCutOn(idx, light.rangeCutOn);
    }

    if (getHasRangeCutOff())
    {
        setRangeCutOff(idx, light.rangeCutOff);
    }

    if (getHasRangeNearZone())
    {
        setRangeNearZone(idx, light.rangeNearZone);
    }

    if (getHasRangeFarZone())
    {
        setRangeFarZone(idx, light.rangeFarZone);
    }

    if (getHasSpotExponent())
    {
        setSpotExponent(idx, light.spotExponent);
    }

    if (getHasCinemaLight())
    {
        setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
        setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
        setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
        setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
        setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
        setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
    }
}

void MultiLightChunk::removeLight(const UInt32 idx)
{
    OSG_ASSERT(check_invariant());

    if (idx >= _mfPosition.size())
        return;

    editMField(PositionFieldMask,           _mfPosition);
    editMField(DirectionFieldMask,          _mfDirection);
    editMField(SpotlightAngleFieldMask,     _mfSpotlightAngle);
    editMField(TypeFieldMask,               _mfType);
    editMField(EnabledFieldMask,            _mfEnabled);
    editMField(BeaconFieldMask,             _mfBeacon);
    editMField(BeaconMatrixFieldMask,       _mfBeaconMatrix);

    _mfPosition.        erase(idx);
    _mfDirection.       erase(idx);
    _mfSpotlightAngle.  erase(idx);
    _mfType.            erase(idx);
    _mfEnabled.         erase(idx);
    _mfBeacon.          erase(idx);
    _mfBeaconMatrix.    erase(idx);

    if (getHasSeparateIntensities())
    {
        editMField(AmbientIntensityFieldMask,   _mfAmbientIntensity);
        editMField(DiffuseIntensityFieldMask,   _mfDiffuseIntensity);
        editMField(SpecularIntensityFieldMask,  _mfSpecularIntensity);

        _mfAmbientIntensity. erase(idx);
        _mfDiffuseIntensity. erase(idx);
        _mfSpecularIntensity.erase(idx);
    }

    if (getHasColor())
    {
        editMField(ColorFieldMask,          _mfColor);
        _mfColor.erase(idx);
    }

    if (getHasIntensity())
    {
        editMField(IntensityFieldMask,      _mfIntensity);
        _mfIntensity.erase(idx);
    }

    if (getHasAttenuation())
    {
        editMField(AttenuationFieldMask,    _mfAttenuation);
        _mfAttenuation.erase(idx);
    }

    if (getHasRangeCutOn())
    {
        editMField(RangeCutOnFieldMask,     _mfRangeCutOn);
        _mfRangeCutOn.erase(idx);
    }

    if (getHasRangeCutOff())
    {
        editMField(RangeCutOffFieldMask,    _mfRangeCutOff);
        _mfRangeCutOff.erase(idx);
    }

    if (getHasRangeNearZone())
    {
        editMField(RangeNearZoneFieldMask,  _mfRangeNearZone);
        _mfRangeNearZone.erase(idx);
    }

    if (getHasRangeFarZone())
    {
        editMField(RangeFarZoneFieldMask,   _mfRangeFarZone);
        _mfRangeFarZone.erase(idx);
    }

    if (getHasSpotExponent())
    {
        editMField(SpotExponentFieldMask,   _mfSpotExponent);
        _mfSpotExponent.erase(idx);
    }

    if (getHasCinemaLight())
    {
        editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
        editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
        editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
        editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
        editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
        editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);

        _mfInnerSuperEllipsesWidth. erase(idx);
        _mfInnerSuperEllipsesHeight.erase(idx);
        _mfOuterSuperEllipsesWidth. erase(idx);
        _mfOuterSuperEllipsesHeight.erase(idx);
        _mfSuperEllipsesRoundness.  erase(idx);
        _mfSuperEllipsesTwist.      erase(idx);
    }
   
    OSG_ASSERT(check_invariant());
}

void MultiLightChunk::clearLights()
{
    editMField(PositionFieldMask,                   _mfPosition);
    editMField(DirectionFieldMask,                  _mfDirection);
    editMField(ColorFieldMask,                      _mfColor);
    editMField(IntensityFieldMask,                  _mfIntensity);
    editMField(AmbientIntensityFieldMask,           _mfAmbientIntensity);
    editMField(DiffuseIntensityFieldMask,           _mfDiffuseIntensity);
    editMField(SpecularIntensityFieldMask,          _mfSpecularIntensity);
    editMField(AttenuationFieldMask,                _mfAttenuation);
    editMField(RangeCutOnFieldMask,                 _mfRangeCutOn);
    editMField(RangeCutOffFieldMask,                _mfRangeCutOff);
    editMField(RangeNearZoneFieldMask,              _mfRangeNearZone);
    editMField(RangeFarZoneFieldMask,               _mfRangeFarZone);
    editMField(SpotlightAngleFieldMask,             _mfSpotlightAngle);
    editMField(SpotExponentFieldMask,               _mfSpotExponent);
    editMField(InnerSuperEllipsesWidthFieldMask,    _mfInnerSuperEllipsesWidth);
    editMField(InnerSuperEllipsesHeightFieldMask,   _mfInnerSuperEllipsesHeight);
    editMField(OuterSuperEllipsesWidthFieldMask,    _mfOuterSuperEllipsesWidth);
    editMField(OuterSuperEllipsesHeightFieldMask,   _mfOuterSuperEllipsesHeight);
    editMField(SuperEllipsesRoundnessFieldMask,     _mfSuperEllipsesRoundness);
    editMField(SuperEllipsesTwistFieldMask,         _mfSuperEllipsesTwist);
    editMField(TypeFieldMask,                       _mfType);
    editMField(EnabledFieldMask,                    _mfEnabled);
    editMField(BeaconFieldMask,                     _mfBeacon);
    editMField(BeaconMatrixFieldMask,               _mfBeaconMatrix);

    _mfPosition.                clear();
    _mfDirection.               clear();
    _mfColor.                   clear();
    _mfIntensity.               clear();
    _mfAmbientIntensity.        clear();
    _mfDiffuseIntensity.        clear();
    _mfSpecularIntensity.       clear();
    _mfAttenuation.             clear();
    _mfRangeCutOn.              clear();
    _mfRangeCutOff.             clear();
    _mfRangeNearZone.           clear();
    _mfRangeFarZone.            clear();
    _mfSpotlightAngle.          clear();
    _mfSpotExponent.            clear();
    _mfInnerSuperEllipsesWidth. clear();
    _mfInnerSuperEllipsesHeight.clear();
    _mfOuterSuperEllipsesWidth. clear();
    _mfOuterSuperEllipsesHeight.clear();
    _mfSuperEllipsesRoundness.  clear();
    _mfSuperEllipsesTwist.      clear();
    _mfType.                    clear();
    _mfEnabled.                 clear();
    _mfBeacon.                  clear();
    _mfBeaconMatrix.            clear();
}

void MultiLightChunk::setLayoutType(UInt32 layout)
{
    setHasColor                     (false);
    setHasIntensity                 (false);
    setHasSeparateIntensities       (false);
    setHasAttenuation               (false);
    setHasRangeCutOn                (false);
    setHasRangeCutOff               (false);
    setHasRangeNearZone             (false);
    setHasRangeFarZone              (false);
    setHasCosSpotlightAngle         (true);
    setHasSpotlightAngle            (false);
    setHasSpotExponent              (false);
    setHasCinemaLight               (false);

    if (layout & MultiLight::SIMPLE_LAYOUT)
    {
        setHasColor                 (true);
        setHasIntensity             (true);
        setHasRangeCutOff           (true);
    }

    if (layout & MultiLight::RANGE_LAYOUT)
    {
        setHasRangeCutOn            (true);
        setHasRangeCutOff           (true);
    }

    if (layout & MultiLight::ZONE_LAYOUT)
    {
        setHasRangeNearZone         (true);
        setHasRangeFarZone          (true);
    }

    if (layout & MultiLight::OPENGL_LAYOUT)
    {
        setHasSeparateIntensities   (true);
        setHasAttenuation           (true);
        setHasSpotExponent          (true);
    }

    if (layout & MultiLight::CINEMA_LAYOUT)
    {
        setHasCinemaLight           (true);
    }

    clearLights();
}

std::string MultiLightChunk::getLightProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl <<     "//"
    << endl <<     "// The supported light types"
    << endl <<     "//"
    << endl <<     "const int POINT_LIGHT       = " << MultiLight::POINT_LIGHT       << ";"
    << endl <<     "const int DIRECTIONAL_LIGHT = " << MultiLight::DIRECTIONAL_LIGHT << ";"
    << endl <<     "const int SPOT_LIGHT        = " << MultiLight::SPOT_LIGHT        << ";"
    << endl <<     "const int CINEMA_LIGHT      = " << MultiLight::CINEMA_LIGHT      << ";"
    << endl <<     ""
    << endl <<     "//"
    << endl <<     "// The multi light type declaration"
    << endl <<     "//"
    << endl <<     "struct Light"
    << endl <<     "{"
    ;
    if (getHasWorldToLightSpaceMatrix())
    {
        ost
        << endl << "    mat4  worldToLightSpaceMatrix;"
        ;
    }

    if (getHasLightToWorldSpaceMatrix())
    {
        ost
        << endl << "    mat4  lightToWorldSpaceMatrix;"
        ;
    }

    if (getHasEyeToLightSpaceMatrix())
    {
        ost
        << endl << "    mat4  eyeToLightSpaceMatrix;"
        ;
    }

    if (getHasLightToEyeSpaceMatrix())
    {
        ost
        << endl << "    mat4  lightToEyeSpaceMatrix;"
        ;
    }

    if (getHasLightPerspectiveMatrix())
    {
        ost
        << endl << "    mat4  lightPerspectiveMatrix;"
        ;
    }

    if (getHasInvLightPerspectiveMatrix())
    {
        ost
        << endl << "    mat4  invLightPerspectiveMatrix;"
        ;
    }
    ost 
    << endl <<     "    vec3  position;                 // in " << (getEyeSpace() ? "eye" : "world") << " space"
    << endl <<     "    vec3  direction;                // in " << (getEyeSpace() ? "eye" : "world") << " space"
    ;
    if (getHasColor())
    {
        ost
        << endl << "    vec3  color;"
        ;
    }

    if (getHasSeparateIntensities())
    {
        ost
        << endl << "    vec3  ambientIntensity;"
        << endl << "    vec3  diffuseIntensity;"
        << endl << "    vec3  specularIntensity;"
        ;
    }

    if (getHasIntensity())
    {
        ost
        << endl << "    float intensity;"
        ;
    }

    if (getHasAttenuation())
    {
        ost
        << endl << "    float constantAttenuation;"
        << endl << "    float linearAttenuation;"
        << endl << "    float quadraticAttenuation;"
        ;
    }

    if (getHasRangeCutOn())
    {
        ost
        << endl << "    float rangeCutOn;"
        ;
    }

    if (getHasRangeCutOff())
    {
        ost
        << endl << "    float rangeCutOff;"
        ;
    }

    if (getHasRangeNearZone())
    {
        ost
        << endl << "    float rangeNearZone;"
        ;
    }

    if (getHasRangeFarZone())
    {
        ost
        << endl << "    float rangeFarZone;"
        ;
    }

    if (getHasCosSpotlightAngle() || (!getHasCosSpotlightAngle() && !getHasSpotlightAngle()))
    {
        ost
        << endl << "    float cosSpotlightAngle;"
        ;
    }

    if (getHasSpotlightAngle())
    {
        ost
        << endl << "    float spotlightAngle;           // in radians"
        ;
    }

    if (getHasSpotExponent())
    {
        ost
        << endl << "    float spotExponent;"
        ;
    }

    if (getHasCinemaLight())
    {
        ost
        << endl << "    float innerSuperEllipsesWidth;  // a" 
        << endl << "    float innerSuperEllipsesHeight; // b"
        << endl << "    float outerSuperEllipsesWidth;  // A"
        << endl << "    float outerSuperEllipsesHeight; // B"
        << endl << "    float superEllipsesRoundness;   // r"
        << endl << "    float superEllipsesTwist;       // // twist angle theta in radians"
        ;
    }
    ost
    << endl <<     "    int   type;                     // specific type of light: POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT or CINEMA_LIGHT"
    << endl <<     "    bool  enabled;                  // on/off state of light"
    << endl <<     "};"
    << endl <<     ""
    << endl <<     "layout (std430) buffer " << getLightBlockName()
    << endl <<     "{"
    << endl <<     "    Light light[];"
    << endl <<     "} " << getLightVariableName() << ";"
    << endl
    ;

    return ost.str();
}

OSG_END_NAMESPACE
