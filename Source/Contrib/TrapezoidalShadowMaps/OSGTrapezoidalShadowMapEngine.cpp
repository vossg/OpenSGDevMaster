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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include "OSGTrapezoidalShadowMapEngine.h"

#include "OSGLine.h"
#include "OSGMaterialChunk.h"
#include "OSGMathMFields.h"
#include "OSGMatrixUtility.h"
#include "OSGColorMaskChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGRenderAction.h"

#include <boost/cast.hpp>

#define OSG_TSME_LIGHTPASS_EXACT 1

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTrapezoidalShadowMapEngineBase.cpp file.
// To modify it, please change the .fcd file (OSGTrapezoidalShadowMapEngine.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

#ifdef OSG_TSME_LIGHTPASS_EXACT

const std::string TrapezoidalShadowMapEngine::_lightPassVPCode(
    "#version 120\n"
    "\n"
    "uniform mat4 TSME_matNT;\n"
    "\n"
    "varying vec4 TSME_plcPos;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    TSME_plcPos = ftransform();\n"
    "    gl_Position = TSME_matNT * TSME_plcPos;\n"
    "}\n"
    );

const std::string TrapezoidalShadowMapEngine::_lightPassFPCode(
    "#version 120\n"
    "\n"
    "const   float TSME_depthEps = 1e-7;\n"
    "\n"
    "uniform float TSME_offsetFactor;\n"
    "uniform float TSME_offsetBias;\n"
    "\n"
    "varying vec4  TSME_plcPos;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    float depth      = 0.5 + 0.5 * (TSME_plcPos.z / TSME_plcPos.w);\n"
    "    float depthSlope = max(abs(dFdx(depth)),\n"
    "                           abs(dFdy(depth)) );\n"
    "    gl_FragDepth     = depth + TSME_offsetFactor * depthSlope\n"
    "                             + TSME_offsetBias   * TSME_depthEps;\n"
    "}\n"
    );

#else

const std::string TrapezoidalShadowMapEngine::_lightPassVPCode(
    "#version 120\n"
    "\n"
    "uniform mat4 TSME_matNT;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    vec4 plcPos = ftransform();\n"
    "    vec4 tcPos  = TSME_matNT * plcPos;\n"
    "    gl_Position = vec4(tcPos.xy, (plcPos.z / plcPos.w) * tcPos.w, tcPos.w);\n"
    "}\n"
    );

const std::string TrapezoidalShadowMapEngine::_lightPassFPCode("");

#endif // OSG_TSME_LIGHTPASS_EXACT

const std::string TrapezoidalShadowMapEngine::_pointFPCode(
    "#version 120\n"
    "\n"
    "#define TSME_PCF 1\n"
    "\n"
    "#extension GL_EXT_gpu_shader4 : require\n"
    "#extension GL_EXT_gpu_shader4 : enable\n"
    "\n"
    "uniform samplerCubeShadow TSME_texShadow;\n"
    "uniform vec2              TSME_texShadowSizeInv;\n"
    "\n"
    "uniform mat4              TSME_matEyeToLight;\n"
    "uniform mat4              TSME_matLightProj;\n"
    "uniform mat4              TSME_matNT[6];\n"
    "\n"
    "vec2 TSME_offsetFactors[16] = vec2[](\n"
    "        vec2(-1.5, -1.5),\n"
    "        vec2( 1.5, -1.5),\n"
    "        vec2(-1.5,  1.5),\n"
    "        vec2( 1.5,  1.5),\n"
    "\n"
    "        vec2(-0.5,  1.5),\n"
    "        vec2( 0.5,  1.5),\n"
    "        vec2(-1.0,  1.0),\n"
    "        vec2( 1.0,  1.0),\n"
    "        vec2(-1.5,  0.5),\n"
    "        vec2( 1.5,  0.5),\n"
    "\n"
    "        vec2(-1.5, -0.5),\n"
    "        vec2( 1.5, -0.5),\n"
    "        vec2(-1.0, -1.0),\n"
    "        vec2( 1.0, -1.0),\n"
    "        vec2(-0.5, -1.5),\n"
    "        vec2( 0.5, -1.5) \n"
    "    );\n"
    "\n"
    "vec4 OSG_SSME_FP_calcShadow(in vec4 fragPos)\n"
    "{\n"
    "    vec4 shadow   = vec4(0., 0., 0., 0.);\n"
    "    vec4 lcPos    = TSME_matEyeToLight * fragPos;\n"
    "    vec4 lcAbsPos = abs(lcPos);\n"
    "    vec4 plcPos;\n"
    "    vec4 tcPos;\n"
    "    vec4 pcfOffset0;\n"
    "    vec4 pcfOffset1;\n"
    "\n"
    "    if(lcAbsPos.x > lcAbsPos.y && lcAbsPos.x > lcAbsPos.z)\n"
    "    {\n"
    "        pcfOffset0 = vec4(0., 0.,                      TSME_texShadowSizeInv.x, 0.);\n"
    "        pcfOffset1 = vec4(0., TSME_texShadowSizeInv.y, 0.                     , 0.);\n"
    "\n"
    "        if(lcPos.x >= 0.)\n"
    "        {\n"
    "            plcPos = vec4(-1, -1, -1, 1)  * lcPos.zyxw;\n"
    "            plcPos = TSME_matLightProj    * plcPos;\n"
    "            tcPos  = TSME_matNT[4]        * plcPos;\n"
    "            tcPos  = tcPos / tcPos.w;\n"
    "            tcPos  = vec4(-1, -1, -1, 1)  * tcPos.zyxw;\n"
    "            tcPos.x = 1.;\n"
    "        }\n"
    "        else\n"
    "        {\n"
    "            plcPos = vec4( 1, -1,  1, 1)  * lcPos.zyxw;\n"
    "            plcPos = TSME_matLightProj    * plcPos;\n"
    "            tcPos  = TSME_matNT[5]        * plcPos;\n"
    "            tcPos  = tcPos / tcPos.w;\n"
    "            tcPos  = vec4( 1, -1,  1, 1)  * tcPos.zyxw;\n"
    "            tcPos.x = -1.;\n"
    "        }\n"
    "    }\n"
    "    else if(lcAbsPos.y > lcAbsPos.x && lcAbsPos.y > lcAbsPos.z)\n"
    "    {\n"
    "        pcfOffset0 = vec4(TSME_texShadowSizeInv.x, 0., 0.,                      0.);\n"
    "        pcfOffset1 = vec4(0.,                      0., TSME_texShadowSizeInv.y, 0.);\n"
    "\n"
    "        if(lcPos.y >= 0.)\n"
    "        {\n"
    "            plcPos = vec4( 1,  1, -1, 1)  * lcPos.xzyw;\n"
    "            plcPos = TSME_matLightProj    * plcPos;\n"
    "            tcPos  = TSME_matNT[2]        * plcPos;\n"
    "            tcPos  = tcPos / tcPos.w;\n"
    "            tcPos  = vec4( 1, -1,  1, 1)  * tcPos.xzyw;\n"
    "            tcPos.y = 1.;\n"
    "        }\n"
    "        else\n"
    "        {\n"
    "            plcPos = vec4( 1, -1,  1, 1)  * lcPos.xzyw;\n"
    "            plcPos = TSME_matLightProj    * plcPos;\n"
    "            tcPos  = TSME_matNT[3]        * plcPos;\n"
    "            tcPos  = tcPos / tcPos.w;\n"
    "            tcPos  = vec4( 1,  1, -1, 1)  * tcPos.xzyw;\n"
    "            tcPos.y = -1.;\n"
    "        }\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        pcfOffset0 = vec4(TSME_texShadowSizeInv.x, 0.,                      0., 0.);\n"
    "        pcfOffset1 = vec4(0.,                      TSME_texShadowSizeInv.y, 0., 0.);\n"
    "\n"
    "        if(lcPos.z >= 0.)\n"
    "        {\n"
    "            plcPos = vec4( 1, -1, -1, 1)  * lcPos;\n"
    "            plcPos = TSME_matLightProj    * plcPos;\n"
    "            tcPos  = TSME_matNT[0]        * plcPos;\n"
    "            tcPos  = tcPos / tcPos.w;\n"
    "            tcPos  = vec4( 1, -1, -1, 1)  * tcPos;\n"
    "            tcPos.z = 1.;\n"
    "        }\n"
    "        else\n"
    "        {\n"
    "            plcPos = vec4(-1, -1,  1, 1)  * lcPos;\n"
    "            plcPos = TSME_matLightProj    * plcPos;\n"
    "            tcPos  = TSME_matNT[1]        * plcPos;\n"
    "            tcPos  = tcPos / tcPos.w;\n"
    "            tcPos  = vec4(-1, -1,  1, 1)  * tcPos;\n"
    "            tcPos.z = -1.;\n"
    "        }\n"
    "    }\n"
    "\n"
    "    plcPos = plcPos / plcPos.w;\n"
    "    plcPos = 0.5 + 0.5 * plcPos;\n"
    "\n"
    "#ifndef TSME_PCF\n"
    "    shadow = shadowCube(TSME_texShadow, vec4(tcPos.xyz, plcPos.z));\n"
    "#else\n"
    "    vec4 lookupBase = vec4(tcPos.xyz, plcPos.z);\n"
    "    vec4 lookup;\n"
    "\n"
    "    for(int i = 0; i < 4; ++i)\n"
    "    {\n"
    "        lookup =  TSME_offsetFactors[i].x * pcfOffset0 +\n"
    "                  TSME_offsetFactors[i].y * pcfOffset1 + lookupBase;\n"
    "        shadow += shadowCube(TSME_texShadow, lookup);\n"
    "    }\n"
    "\n"
    "    if((shadow.x - 4.0) * shadow.x == 0.0)\n"
    "    {\n"
    "        shadow *= 0.25;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        for(int i = 4; i < 16; ++i)\n"
    "        {\n"
    "            lookup =  TSME_offsetFactors[i].x * pcfOffset0 +\n"
    "                      TSME_offsetFactors[i].y * pcfOffset1 + lookupBase;\n"
    "            shadow += shadowCube(TSME_texShadow, lookup);\n"
    "        }\n"
    "\n"
    "        shadow *= 1.0 / 16.0;\n"
    "    }\n"
    "#endif // TSME_PCF\n"
    "\n"
    "    return shadow;\n"
    "}\n"
    );

const std::string TrapezoidalShadowMapEngine::_spotFPCode(
    "#version 120\n"
    "\n"
    "#define TSME_PCF 1\n"
    "\n"
    "uniform sampler2DShadow TSME_texShadow;\n"
    "uniform vec2            TSME_texShadowSizeInv;\n"
    "\n"
    "uniform mat4            TSME_matEyeToLight;\n"  
    "uniform mat4            TSME_matLightProj;\n"
    "uniform mat4            TSME_matNT;\n"
    "\n"
    "vec2 TSME_offsetFactors[16] = vec2[](\n"
    "        vec2(-1.5, -1.5),\n"
    "        vec2( 1.5, -1.5),\n"
    "        vec2(-1.5,  1.5),\n"
    "        vec2( 1.5,  1.5),\n"
    "\n"
    "        vec2(-0.5,  1.5),\n"
    "        vec2( 0.5,  1.5),\n"
    "        vec2(-1.0,  1.0),\n"
    "        vec2( 1.0,  1.0),\n"
    "        vec2(-1.5,  0.5),\n"
    "        vec2( 1.5,  0.5),\n"
    "\n"
    "        vec2(-1.5, -0.5),\n"
    "        vec2( 1.5, -0.5),\n"
    "        vec2(-1.0, -1.0),\n"
    "        vec2( 1.0, -1.0),\n"
    "        vec2(-0.5, -1.5),\n"
    "        vec2( 0.5, -1.5) \n"
    "    );\n"
    "\n"
    "vec4 OSG_SSME_FP_calcShadow(in vec4 ecFragPos)\n"
    "{\n"
    "    vec4 shadow = vec4(0., 0., 0., 0.);\n"
    "    vec4 plcPos = TSME_matLightProj * TSME_matEyeToLight * ecFragPos;\n"
    "    vec4 tcPos  = TSME_matNT        * plcPos;\n"
    "\n"
    "    plcPos = plcPos / plcPos.w;\n"
    "    plcPos = 0.5 + 0.5 * plcPos;\n"
    "    tcPos  = tcPos / tcPos.w;\n"
    "    tcPos  = 0.5 + 0.5 * tcPos;\n"
    "\n"
    "    vec3 lookupBase = vec3(tcPos.xy, plcPos.z);\n"
    "    vec3 lookup;\n"
    "\n"
    "#ifndef TSME_PCF\n"
    "    shadow = shadow2D(TSME_texShadow, lookupBase);\n"
    "#else\n"
    "    for(int i = 0; i < 4; ++i)\n"
    "    {\n"
    "        lookup =  vec3(TSME_offsetFactors[i].x * TSME_texShadowSizeInv.x,\n"
    "                       TSME_offsetFactors[i].y * TSME_texShadowSizeInv.y,\n"
    "                       0.0) + lookupBase;\n"
    "        shadow += shadow2D(TSME_texShadow, lookup);\n"
    "    }\n"
    "\n"
    "    if((shadow.x - 4.) * shadow.x == 0)\n"
    "    {\n"
    "        shadow *= 0.25;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        for(int i = 4; i < 16; ++i)\n"
    "        {\n"
    "            lookup =  vec3(TSME_offsetFactors[i].x * TSME_texShadowSizeInv.x,\n"
    "                           TSME_offsetFactors[i].y * TSME_texShadowSizeInv.y,\n"
    "                           0.0) + lookupBase;\n"
    "            shadow += shadow2D(TSME_texShadow, lookup);\n"
    "        }\n"
    "\n"
    "        shadow *= 1.0 / 16.0;\n"
    "    }\n"
    "#endif\n"
    "\n"
    "    return shadow;\n"
    "}\n"
    );

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TrapezoidalShadowMapEngine::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TrapezoidalShadowMapEngine::TrapezoidalShadowMapEngine(void) :
    Inherited()
{
}

TrapezoidalShadowMapEngine::TrapezoidalShadowMapEngine(const TrapezoidalShadowMapEngine &source) :
    Inherited(source)
{
}

TrapezoidalShadowMapEngine::~TrapezoidalShadowMapEngine(void)
{
}

/*----------------------------- class specific ----------------------------*/

ActionBase::ResultE TrapezoidalShadowMapEngine::runOnEnter(
    Light *light, LightTypeE eType, RenderAction *ract)
{
    BitVector      passMask = ract->getPassMask             (            );
    TSMEngineData *data     = ract->getData<TSMEngineData *>(_iDataSlotId);

    if(data == NULL)
    {
        TSMEngineDataUnrecPtr newData = TSMEngineData::createLocal();
        this->setData(newData, _iDataSlotId, ract);
        
        data = newData;
    }

    if(passMask != 0x0000)
    {
        // already generating a shadow map for another light source?
        if((passMask & bvLightPassMask) != 0x0000)
        {
            this->recurseFrom(ract, light);

            handleEnter(light, eType, ract, data);
        }
    }
    else
    {
        ract->addPassMask(bvLightPassMask);
        handleEnter(light, eType, ract, data);
        ract->subPassMask(bvLightPassMask);
    }

    return Action::Continue;
}

ActionBase::ResultE TrapezoidalShadowMapEngine::runOnLeave(
    Light *light, LightTypeE eType, RenderAction *ract)
{
    return Action::Continue;
}

void TrapezoidalShadowMapEngine::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TrapezoidalShadowMapEngine::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TrapezoidalShadowMapEngine NI" << std::endl;
}

void TrapezoidalShadowMapEngine::handleEnter(
    Light *light, LightTypeE eType, RenderAction *ract, TSMEngineData *data)
{
    Inherited::updateShadowTexChunk   (data);
    Inherited::updateBackground       (data);

    UInt32 parentTravMask = ract->getTravMask();
    ract->setTravMask(_sfShadowTravMask.getValue());

    switch(eType)
    {
    case Point:
    {
        PointLight *pointL =
            boost::polymorphic_downcast<PointLight *>(light);

        handlePointLightEnter(pointL, ract, data);
    }
    break;

    case Directional:
    {
        DirectionalLight *dirL =
            boost::polymorphic_downcast<DirectionalLight *>(light);
        
        handleDirectionalLightEnter(dirL, ract, data);
    }
    break;

    case Spot:
    {
        SpotLight *spotL =
            boost::polymorphic_downcast<SpotLight *>(light);

        handleSpotLightEnter(spotL, ract, data);
    }
    break;

    default:
    {
        FWARNING(("TrapezoidalShadowMapEngine::handleEnter: Unknown "
                  "light type [%u]\n", eType));
    }
    break;
    }

    ract->setTravMask(parentTravMask);
}

void TrapezoidalShadowMapEngine::handlePointLightEnter(
    PointLight *pointL, RenderAction *ract, TSMEngineData *data)
{
    RenderPartition *parentPart = ract->getActivePartition();
    
    Matrix  matEyeToWorld(parentPart->getCameraToWorld());  
    Matrix  matLightProj;

    Real32  shadowNear = (getShadowNear() != 0.f ? 
                          getShadowNear()       : 
                          parentPart->getNear()  );
    Real32  shadowFar  = (getShadowFar () != 0.f ?
                          getShadowFar ()       :
                          parentPart->getFar()   );

    Inherited::calcPointLightRange(
        pointL, 0.01f,
        shadowNear, shadowFar, shadowNear, shadowFar);

    MatrixPerspective(matLightProj, Pi / 4.f, 1.f,
                      shadowNear, shadowFar       );
    
    Matrix    matWorldToLight;
    Matrix    matEyeToLight;
    MFMatrix  mfMatNT;

    mfMatNT.resize(6);

    Inherited::calcPointLightMatrices(matWorldToLight, matEyeToLight,
                                      pointL,          matEyeToWorld );

    Inherited::updatePointLightShadowTexImage  (data);
    Inherited::updatePointLightShadowTexBuffers(data);
    Inherited::updatePointLightRenderTargets   (data);

    Int32          shadowTexUnit = (this->getForceTextureUnit() >= 0) ?
                                    this->getForceTextureUnit()       : 7;
    ShaderProgram *shadowFP      = this->getShadowFragmentProgram();

    if(shadowFP == NULL)
    {
        ShaderProgramUnrecPtr newShadowFP = ShaderProgram::createLocal();
        newShadowFP->setShaderType(GL_FRAGMENT_SHADER);
        newShadowFP->setProgram   (_pointFPCode      );
        
        newShadowFP->addUniformVariable("TSME_matEyeToLight", matEyeToLight);
        newShadowFP->addUniformVariable("TSME_matLightProj",  matLightProj );
        newShadowFP->addUniformVariable("TSME_matNT",         mfMatNT      );
        newShadowFP->addUniformVariable("TSME_texShadow",     shadowTexUnit);
        newShadowFP->addUniformVariable("TSME_texShadowSizeInv",
                                        Vec2f(1.f / getWidth (), 
                                              1.f / getHeight() )          );
        
        this->setShadowFragmentProgram(newShadowFP);
        shadowFP = newShadowFP;
    }
    else
    {
        shadowFP->updateUniformVariable("TSME_matEyeToLight", matEyeToLight);
        shadowFP->updateUniformVariable("TSME_matLightProj",  matLightProj );
    }

    const FrustumVolume &eyeFrust = parentPart->getFrustum();

    for(UInt16 faceIdx = 0; faceIdx < 6; ++faceIdx)
    {
        Matrix matWorldToLightFace (matWorldToLight         );
        matWorldToLightFace.multLeft(_matCubeFaceInv[faceIdx]);

        Matrix matLightFull(matWorldToLightFace);
        matLightFull.multLeft(matLightProj);

        FrustumVolume lightFrust;
        Matrix        matNT;

        lightFrust.setPlanes(matLightFull);

        bool matNTValid = 
            calcTrapezoidalTransform(mfMatNT[faceIdx],
                                     matEyeToWorld,    matLightFull,
                                     eyeFrust,         lightFrust   );

        if(matNTValid == false)
        {
            // setup a minimal partition to clear the cube face

            commitChanges();

            this->pushPartition(ract,
                                RenderPartition::CopyNothing,
                                RenderPartition::SimpleCallback);
            {
                RenderPartition   *part   = ract->getActivePartition(       );
                Window            *win    = ract->getWindow         (       );
                FrameBufferObject *target = data->getRenderTargets  (faceIdx);
                Background        *back   = data->getBackground     (       );

                part->setSetupMode(RenderPartition::ViewportSetup  |
                                   RenderPartition::BackgroundSetup );

                part->setRenderTarget(target);
                part->setWindow      (win   );

                part->calcViewportDimension(0.f, 0.f, 1.f, 1.f,
                                            target->getWidth (),
                                            target->getHeight() );
                
                part->setBackground(back);

                RenderPartition::SimpleDrawCallback emptyCubeFaceDraw =
                    boost::bind(
                        &TrapezoidalShadowMapEngine::emptyCubeFaceDrawFunc,
                        this, _1);

                part->dropFunctor(emptyCubeFaceDraw);
            }
            this->popPartition(ract);
        }
        else
        {
            updateLightPassMaterial(data, faceIdx, mfMatNT[faceIdx]);
        
            commitChanges();

            this->pushPartition(ract);
            {
                RenderPartition   *part   = ract->getActivePartition(       );
                Window            *win    = ract->getWindow         (       );
                FrameBufferObject *target = data->getRenderTargets  (faceIdx);
                Background        *back   = data->getBackground     (       );

                part->setRenderTarget(target);
                part->setWindow      (win   );

                part->calcViewportDimension(0.f, 0.f, 1.f, 1.f,
                                            target->getWidth (),
                                            target->getHeight() );

                part->setupProjection(matLightProj, Matrix::identity());
                part->setupViewing   (matWorldToLightFace             );

                part->setNear        (parentPart->getNear());
                part->setFar         (parentPart->getFar ());
            
                part->setFrustum     (lightFrust           );
                
                part->setBackground  (back                 );

                part->overrideMaterial(data->getLightPassMaterials(faceIdx),
                                       ract->getActNode           (       ) );

                this->recurseFrom(ract, pointL);
                ract->useNodeList(false       );

                part->overrideMaterial(NULL,
                                       ract->getActNode           (       ) );
            }
            this->popPartition(ract);
        }
    }

    shadowFP->updateUniformVariable("TSME_matNT", mfMatNT);
}

void TrapezoidalShadowMapEngine::handleDirectionalLightEnter(
    DirectionalLight *dirL, RenderAction *ract, TSMEngineData *data)
{
    FWARNING(("TrapezoidalShadowMapEngine::handleDirectionalLightEnter: NIY\n"));
}

void TrapezoidalShadowMapEngine::handleSpotLightEnter(
    SpotLight *spotL, RenderAction *ract, TSMEngineData *data)
{
    RenderPartition *parentPart = ract->getActivePartition();

    Matrix matEyeToWorld(parentPart->getCameraToWorld());
    Matrix matWorldToLight;
    Matrix matEyeToLight;

    Inherited::calcSpotLightMatrices(matWorldToLight, matEyeToLight,
                                     spotL,           matEyeToWorld );

    Matrix matLightProj;
    Matrix matLightFull(matWorldToLight);

    Real32  shadowNear = (getShadowNear() != 0.f ? 
                          getShadowNear()       : 
                          parentPart->getNear()  );
    Real32  shadowFar  = (getShadowFar () != 0.f ?
                          getShadowFar ()       :
                          parentPart->getFar()   );

    Inherited::calcPointLightRange(
        spotL, 0.01f,
        shadowNear, shadowFar, shadowNear, shadowFar);

    MatrixPerspective(matLightProj,
                      spotL->getSpotCutOff(), 1.f,
                      shadowNear, shadowFar       );

    matLightFull.multLeft(matLightProj);

    Inherited::updateShadowTexImage  (data);
    Inherited::updateShadowTexBuffers(data);
    Inherited::updateRenderTargets   (data);

    const FrustumVolume &eyeFrust   = parentPart->getFrustum();
          FrustumVolume  lightFrust;
          Matrix         matNT;

    lightFrust.setPlanes(matLightFull);

    bool matNTValid = calcTrapezoidalTransform(matNT,
                                               matEyeToWorld, matLightFull,
                                               eyeFrust,      lightFrust   );

    if(matNTValid == false)
        return;

//    Real32         cosSpotCutOff = osgCos(spotL->getSpotCutOff());

    Int32          shadowTexUnit = (this->getForceTextureUnit() >= 0) ?
                                    this->getForceTextureUnit()       : 7;
    ShaderProgram *shadowFP      = this->getShadowFragmentProgram();

    if(shadowFP == NULL)
    {
        ShaderProgramUnrecPtr newShadowFP = ShaderProgram::createLocal();
        newShadowFP->setShaderType(GL_FRAGMENT_SHADER);
        newShadowFP->setProgram   (_spotFPCode       );

        newShadowFP->addUniformVariable("TSME_matEyeToLight", matEyeToLight);
        newShadowFP->addUniformVariable("TSME_matLightProj",  matLightProj );
        newShadowFP->addUniformVariable("TSME_matNT",         matNT        );
        newShadowFP->addUniformVariable("TSME_texShadow",     shadowTexUnit);
        newShadowFP->addUniformVariable("TSME_texShadowSizeInv",
                                        Vec2f(1.f / getWidth (), 
                                              1.f / getHeight() )          );

        this->setShadowFragmentProgram(newShadowFP);
        shadowFP = newShadowFP;
    }
    else
    {
        shadowFP->updateUniformVariable("TSME_matEyeToLight", matEyeToLight);
        shadowFP->updateUniformVariable("TSME_matLightProj",  matLightProj );
        shadowFP->updateUniformVariable("TSME_matNT",         matNT        );
    }

    updateLightPassMaterial(data, 0, matNT);

    commitChanges();
    
    this->pushPartition(ract);
    {
        RenderPartition   *part   = ract->getActivePartition( );
        Window            *win    = ract->getWindow         ( );
        FrameBufferObject *target = data->getRenderTargets  (0);
        Background        *back   = data->getBackground     ( );

        part->setRenderTarget(target);
        part->setWindow      (win   );

        part->calcViewportDimension(0.f, 0.f, 1.f, 1.f,
                                    target->getWidth (),
                                    target->getHeight() );

        part->setupProjection(matLightProj, Matrix::identity());
        part->setupViewing   (matWorldToLight                 );
        
        part->setNear        (parentPart->getNear());
        part->setFar         (parentPart->getFar ());

        part->setFrustum     (lightFrust           );

        part->setBackground  (back                 );

        part->overrideMaterial(data->getLightPassMaterials(0),
                               ract->getActNode           ( ) );

        this->recurseFrom(ract, spotL);
        ract->useNodeList(false      );

        part->overrideMaterial(NULL,
                               ract->getActNode           ( ) );
    }
    this->popPartition(ract);
}

/*! Calculate the vertices (\a intVerts) and center (\a intCenter) of
    the intersection of \a fA and \a fB.
 */
void TrapezoidalShadowMapEngine::intersectFrusta(
    const FrustumVolume      &fA,       const FrustumVolume &fB,
          std::vector<Pnt3f> &intVerts,       Pnt3f         &intCenter)
{
    const Plane *planes[12];

    intVerts.clear  (  );
    intVerts.reserve(16);
  
    for(UInt32 i = 0; i < 6; ++i)
    {
        planes[i    ] = &(fA.getPlanes()[i]);
        planes[6 + i] = &(fB.getPlanes()[i]);
    }

    // take all combinations of 3 planes -- but avoid choosing planes
    // we know to be parallel (i.e. near and far of the same frustum), or
    // that are known to intersect outside the frustum (i.e top/bottom,
    // left/right).

    for(UInt32 i = 0; i < 12; ++i)
    {
        // choose initial value of j such that it avoids near and far of fA
        for(UInt32 j = osgMax<UInt32>(2, i + 1); j < 12; ++j)
        {
            // near/far are parallel,
            // left/right always intersect outside the frustum,
            // top/bottom always intersect outside the frustum
            if((i == 6 && j == 7) ||
               (i == 2 && j == 3) || (i ==  8 && j ==  9) ||
               (i == 4 && j == 5) || (i == 10 && j == 11)   )
                continue;

            Line intLine;
            if(planes[i]->intersect(*planes[j], intLine) == false)
                continue;

            for(UInt32 k = j + 1; k < 12; ++k)
            {
                // near/far are parallel,
                // left/right always intersect outside the frustum,
                // top/bottom always intersect outside the frustum
                if((j == 6 && k == 7) ||
                   (j == 2 && k == 3) || (j ==  8 && k ==  9) ||
                   (j == 4 && k == 5) || (j == 10 && k == 11)   )
                    continue;

                Pnt3f intPoint;
                if(planes[k]->intersectInfinite(intLine, intPoint) == false)
                    continue;

                bool intPointValid = true;

                // check the intersection point against all planes to ensure
                // it is in both frusta
                for(UInt32 m = 0; m < 12; ++m)
                {
                    // intPoint is the intersection of planes i, j, k, so
                    // we don't have to test against those
                    if(m == i || m == j || m == k)
                        continue;

                    if(planes[m]->isInHalfSpace(intPoint) == false)
                    {
                        intPointValid = false;
                        break;
                    }
                }

                if(intPointValid == true)
                {
                    intCenter += intPoint.subZero();
                    intVerts.push_back(intPoint);
                }
            }
        }
    }

    intCenter /= intVerts.size();
}

void TrapezoidalShadowMapEngine::updateLightPassMaterial(
    TSMEngineData *data, UInt16 faceIdx, const Matrix &matNT)
{
    if(data->getMFLightPassMaterials()->size() < 6)
        data->editMFLightPassMaterials()->resize(6, NULL);

    ChunkMaterial *lightPassMat = data->getLightPassMaterials(faceIdx);

    if(lightPassMat == NULL)
    {
        ColorMaskChunkUnrecPtr newCMaskChunk = ColorMaskChunk::create();
        newCMaskChunk->setMaskR(false);
        newCMaskChunk->setMaskG(false);
        newCMaskChunk->setMaskB(false);
        newCMaskChunk->setMaskA(false);

#ifdef OSG_TSME_LIGHTPASS_EXACT

        ShaderProgramUnrecPtr newLightPassVP = ShaderProgram::createLocal();
        newLightPassVP->setShaderType(GL_VERTEX_SHADER);
        newLightPassVP->setProgram   (_lightPassVPCode);
        newLightPassVP->addUniformVariable("TSME_matNT", matNT);

        ShaderProgramUnrecPtr newLightPassFP = ShaderProgram::createLocal();
        newLightPassFP->setShaderType(GL_FRAGMENT_SHADER);
        newLightPassFP->setProgram   (_lightPassFPCode  );
        newLightPassFP->addUniformVariable("TSME_offsetFactor", getOffsetFactor());
        newLightPassFP->addUniformVariable("TSME_offsetBias",   getOffsetBias  ());

        ShaderProgramChunkUnrecPtr newLightPassSHChunk =
            ShaderProgramChunk::createLocal();
        newLightPassSHChunk->addVertexShader  (newLightPassVP);
        newLightPassSHChunk->addFragmentShader(newLightPassFP);

        ChunkMaterialUnrecPtr  newLightPassMat = ChunkMaterial::createLocal();
        newLightPassMat->addChunk(newCMaskChunk      );
        newLightPassMat->addChunk(newLightPassSHChunk);

        lightPassMat = newLightPassMat;
        data->editMFLightPassMaterials()->replace(faceIdx, newLightPassMat);

#else
        
        PolygonChunkUnrecPtr newPolyChunk = PolygonChunk::createLocal();
        newPolyChunk->setOffsetFill  (true             );
        newPolyChunk->setOffsetFactor(getOffsetFactor());
        newPolyChunk->setOffsetBias  (getOffsetBias  ());

        ShaderProgramUnrecPtr newLightPassVP = ShaderProgram::createLocal();
        newLightPassVP->setShaderType     (GL_VERTEX_SHADER   );
        newLightPassVP->setProgram        (_lightPassVPCode   );
        newLightPassVP->addUniformVariable("TSME_matNT", matNT);

        ShaderProgramChunkUnrecPtr newLightPassSHChunk =
            ShaderProgramChunk::createLocal();
        newLightPassSHChunk->addVertexShader(newLightPassVP);

        ChunkMaterialUnrecPtr  newLightPassMat = ChunkMaterial::createLocal();
        newLightPassMat->addChunk(newCMaskChunk      );
        newLightPassMat->addChunk(newPolyChunk       );
        newLightPassMat->addChunk(newLightPassSHChunk);

        lightPassMat = newLightPassMat;
        (*data->editMFLightPassMaterials())[faceIdx] = newLightPassMat;

#endif

        
    }
    else
    {
        ShaderProgramChunk *lightPassSHChunk =
            dynamic_cast<ShaderProgramChunk *>(
                lightPassMat->find(ShaderProgramChunk::getClassType()));
    
        if(lightPassSHChunk != NULL)
        {
            ShaderProgram *lightPassVP = lightPassSHChunk->getVertexShader(0);
            lightPassVP->updateUniformVariable("TSME_matNT", matNT);
        }
    }
}

/*! Calculates the trapezoidal transformation matrix \a matNT that transforms
    post projection light space so that shadow map resolution in the
    "foreground" is maximized.
    The major steps are:
      - compute the intersection of eyeFrust and lightFrust
      - construct a trapezoid that contains the intersection
      - determine the transformation that maps this trapezoid to the
        (-1, 1) square

    Returns \c true if the transform was computed, \c false otherwise (e.g. if
    the intersection of eyeFrust and lightFrust is empty).
    
    For details see "T. Martin, T.-S. Tan: Anti-aliasing and Continuity
                     with Trapezoidal Shadow Maps" 
 */
bool TrapezoidalShadowMapEngine::calcTrapezoidalTransform(
          Matrix        &matNT,
    const Matrix        &matEyeToWorld, 
    const Matrix        &matLightFull,
    const FrustumVolume &eyeFrust,
    const FrustumVolume &lightFrust    )
{
    // obtain post proj. light space eye position
    Pnt3f eyePos;
    matEyeToWorld.mult    (eyePos, eyePos);
    matLightFull .multFull(eyePos, eyePos);

    // intersect eye and light frusta, get vertices and center of intersection
    std::vector<Pnt3f> intVerts;
    Pnt3f              intCenter;
    intersectFrusta(eyeFrust, lightFrust, intVerts, intCenter);

    if(intVerts.empty() == true)
        return false;

    // xform intCenter and intVerts to post proj. light space
    matLightFull.multFull(intCenter, intCenter);

    std::vector<Pnt3f>::iterator ivIt  = intVerts.begin();
    std::vector<Pnt3f>::iterator ivEnd = intVerts.end  ();

    for(; ivIt != ivEnd; ++ivIt)
        matLightFull.multFull(*ivIt, *ivIt);
    
    Pnt2f eyePos2D   (eyePos   [0], eyePos   [1]);
    Pnt2f intCenter2D(intCenter[0], intCenter[1]);

    // center line, normal, direction and distance from origin
    Vec2f clDir (intCenter2D - eyePos2D);
    clDir.normalize();
    Vec2f clNorm(-clDir[1], clDir[0]);

    // distance of the center line from the origin
    Real32 clDist = clNorm.dot(eyePos2D.subZero());

    // compute top and base lines:
    //  - project intVerts onto the center line.
    //  - top line is perpendicular to center line and goes through the
    //    projected point closest to eyePos
    //  - base line is perpendicular to center line and goes through the
    //    projected point farthest from eyePos

    Pnt2f  tlBase;
    Pnt2f  blBase;
    Real32 topDist  = TypeTraits<Real32>::getMax();
    Real32 baseDist = TypeTraits<Real32>::getMin();

    std::vector<Pnt3f>::const_iterator ivCIt  = intVerts.begin();
    std::vector<Pnt3f>::const_iterator ivCEnd = intVerts.end  ();

    for(; ivCIt != ivCEnd; ++ivCIt)
    {
        Pnt2f ivPnt((*ivCIt)[0], (*ivCIt)[1]);
        
        ivPnt = ivPnt - (clNorm.dot(ivPnt) - clDist) * clNorm;

        Real32 dist = (ivPnt - eyePos2D).squareLength();
        dist *= osgSgn(clDir.dot(ivPnt - eyePos2D));

        if(dist < topDist)
        {
            topDist = dist;
            tlBase  = ivPnt;
        }
        
        if(dist > baseDist)
        {
            baseDist = dist;
            blBase   = ivPnt;
        }
    }

    topDist  = osgSgn(topDist ) * osgSqrt(osgAbs(topDist ));
    baseDist = osgSgn(baseDist) * osgSqrt(osgAbs(baseDist));

    // compute side lines:
    //  - choose focusPnt (everything closer to the near plane is mapped to
    //    80% of the shadow map) - here we just take the point at 0.7 between
    //    tlBase and blBase
    //  - find a point (trapTip, q in the paper) on center line such that
    //    focusPnt is mapped the 80% line in the shadow map
    //  - choose lines through q that touch the convex hull of intVerts

    ivCIt  = intVerts.begin();
    ivCEnd = intVerts.end  ();

//    Real32  centerDist = (intCenter2D - eyePos2D).length();

    Real32  lambda     = baseDist   - topDist;
    Real32  delta      = 0.5f * lambda;
    Real32  xi         = -0.6f;
    Real32  eta        = ((lambda * delta) + (lambda * delta * xi)) /
                         (lambda - 2.f * delta - lambda * xi      );
    Pnt2f  trapTip    = tlBase - (eta   * clDir);
    Pnt2f  focusPnt   = tlBase + (delta * clDir);

    // on both sides of the center line, find the point in intVerts that has
    // the smallest |cosine| (largest angle) between clDir and the vector
    // from trapTip to intVerts[i]
    Pnt2f  posPnt;
    Real32 posCos = 1.f;
    Pnt2f  negPnt;
    Real32 negCos = 1.f;

    for(UInt32 i = 0; ivCIt != ivCEnd; ++ivCIt, ++i)
    {
        Pnt2f ivPnt((*ivCIt)[0], (*ivCIt)[1]);
   
        Vec2f  v       = ivPnt - trapTip;
        v.normalize();
        Real32 currCos = osgAbs(clDir.dot(v));

        if(clNorm.dot(v) >= 0.f)
        {
            if(currCos <= posCos)
            {
                posPnt = ivPnt;
                posCos = currCos;
            }
        }
        else
        {
            if(currCos <= negCos)
            {
                negPnt = ivPnt;
                negCos = currCos;
            }
        }
    }

    // compute corners of trapezoid:
    Pnt2f  trapVerts [4];
    Pnt2f  extraVerts[2];
    Real32 posTan = osgTan(osgACos(posCos));
    Real32 negTan = osgTan(osgACos(negCos));

    trapVerts[0] = blBase - ((eta + lambda) * negTan * clNorm);
    trapVerts[1] = blBase + ((eta + lambda) * posTan * clNorm);
    trapVerts[2] = tlBase + ( eta           * posTan * clNorm);
    trapVerts[3] = tlBase - ( eta           * negTan * clNorm);

    extraVerts[0] = focusPnt + ((eta + delta) * posTan * clNorm);
    extraVerts[1] = focusPnt - ((eta + delta) * negTan * clNorm);

    // == xform trapezoid to unit square ==

    // M1 = R * T1  -- translate center of top line to origin and rotate
    Vec2f u = 0.5f * (trapVerts[2].subZero() + trapVerts[3].subZero());
    Vec2f v =         trapVerts[3]           - trapVerts[2];
    v.normalize();

    matNT.setValue( v[0],  v[1], 0.f, -(u[0] * v[0] + u[1] * v[1]),
                   -v[1],  v[0], 0.f,  (u[0] * v[1] - u[1] * v[0]),
                    0.f,   0.f,  1.f,  0.f,
                    0.f,   0.f,  0.f,  1.f);

    // M2 = T2 * M1  -- translate tip to origin
    matNT[3][0] = - (matNT[0][0] * trapTip[0] + matNT[1][0] * trapTip[1]);
    matNT[3][1] = - (matNT[0][1] * trapTip[0] + matNT[1][1] * trapTip[1]);

    // M3 = H * M2  -- shear to make it symmetric wrt to the y axis
    //    v = M2 * u
    v[0] = matNT[0][0] * u[0] + matNT[1][0] * u[1] + matNT[3][0];
    v[1] = matNT[0][1] * u[0] + matNT[1][1] * u[1] + matNT[3][1];
  
    Real32 a = - v[0] / v[1];
    
    //    matNT[*][0] : = mat[*][0] + a * mat[*][1]
    matNT[0][0] += a * matNT[0][1];
    matNT[1][0] += a * matNT[1][1];
    matNT[2][0] += a * matNT[2][1];
    matNT[3][0] += a * matNT[3][1];

    // M4 = S1 * M3  -- scale to make sidelines orthogonal and 
    //                  top line is at y == 1
    //    v = 1 / (M3 * t2)
    v[0] = 1.f / (matNT[0][0] * trapVerts[2][0] + matNT[1][0] * trapVerts[2][1] + matNT[3][0]);
    v[1] = 1.f / (matNT[0][1] * trapVerts[2][0] + matNT[1][1] * trapVerts[2][1] + matNT[3][1]);

    matNT[0][0] *= v[0];    matNT[0][1] *= v[1];
    matNT[1][0] *= v[0];    matNT[1][1] *= v[1];
    matNT[2][0] *= v[0];    matNT[2][1] *= v[1];
    matNT[3][0] *= v[0];    matNT[3][1] *= v[1];
    
    // M5 = N * M4  -- turn trapezoid into rectangle
    matNT[0][3] = matNT[0][1];
    matNT[1][3] = matNT[1][1];
    matNT[2][3] = matNT[2][1];
    matNT[3][3] = matNT[3][1];
    matNT[3][1] += 1.f;

    // M6 = T3 * M5  -- translate center to origin
    //    u = "M5 * t0"  - only y and w coordinates
    //    v = "M5 * t2"  - only y and w coordinates
    u[0] = matNT[0][1] * trapVerts[0][0] + matNT[1][1] * trapVerts[0][1] + matNT[3][1];
    u[1] = matNT[0][3] * trapVerts[0][0] + matNT[1][3] * trapVerts[0][1] + matNT[3][3];
    v[0] = matNT[0][1] * trapVerts[2][0] + matNT[1][1] * trapVerts[2][1] + matNT[3][1];
    v[1] = matNT[0][3] * trapVerts[2][0] + matNT[1][3] * trapVerts[2][1] + matNT[3][3];
    a    = - 0.5f * (u[0] / u[1] + v[0] / v[1]);

    matNT[0][1] += matNT[0][3] * a;
    matNT[1][1] += matNT[1][3] * a;
    matNT[2][1] += matNT[2][3] * a;
    matNT[3][1] += matNT[3][3] * a;

    // M7 = S2 * M6  -- scale to fill -1/+1 square
    //    u = "M6 * t0"  - only y and w coordinates
    u[0] = matNT[0][1] * trapVerts[0][0] + matNT[1][1] * trapVerts[0][1] + matNT[3][1];
    u[1] = matNT[0][3] * trapVerts[0][0] + matNT[1][3] * trapVerts[0][1] + matNT[3][3];
    a    = -u[1] / u[0];

    matNT[0][1] *= a;
    matNT[1][1] *= a;
    matNT[2][1] *= a;
    matNT[3][1] *= a;

    return true;
}

// Dummy draw function.
void TrapezoidalShadowMapEngine::emptyCubeFaceDrawFunc(DrawEnv *drawEnv)
{
}

#if 0
void TrapezoidalShadowMapEngine::calcJitterTexture(
    Image *img,
    UInt32 blockSizeX,   UInt32 blockSizeY,
    UInt32 angleSectors, UInt32 distSectors)
{
    UInt32 zSize = angleSector * distSectors / 2;

    img->set(OSG_RGBA_PF,
             blockSizeX,
             blockSizeY,
             zSize,
             1,
             1,
             0.0,
             NULL,
             OSG_UINT8_IMAGEDATA,
             true,
             1);

    Real32 sizeCellU = 1.f / angleSectors;
    Real32 sizeCellV = 1.f / distSectors;

    UInt8 *pPixel = img->editData(0, 0, 0);

    for(UInt32 zPos = 0; zPos < zSize; ++zPos)
    {
        Real32 cell0U = sizeCellU *                    (2 * zPos % angleSectors);
        Real32 cell0V = sizeCellV * (distSectors - 1 - (2 * zPos / angleSectors));
        Real32 cell1U = sizeCellU * (1               + (2 * zPos % angleSectors));
        Real32 cell1V = sizeCellV * (distSectors - 1 - (2 * zPos / angleSectors));

        Real32 grid0U =       sizeCellU *  (2 * zPos % blockSizeX);
        Real32 grid0V = 1.f - sizeCellV *  (2 * zPos / blockSizeY);
        Real32 grid1U =       sizeCellU * ((2 * zPos % blockSizeX) + 1);
        Real32 grid1V = 1.f - sizeCellV *  (2 * zPos / blockSizeY);

        for(UInt32 xPos = 0; xPos < blockSizeX; ++xPos)
        {
            for(UInt32 yPos = 0; yPos < blockSizeY; ++yPos)
            {
                
            }
        }
    }
}
#endif

OSG_END_NAMESPACE
