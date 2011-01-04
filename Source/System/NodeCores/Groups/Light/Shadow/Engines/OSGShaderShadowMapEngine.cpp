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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGShaderShadowMapEngine.h"

#include "OSGMatrixUtility.h"
#include "OSGSolidBackground.h"
#include "OSGColorMaskChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGRenderAction.h"
#include "OSGShaderProgram.h"

#include "OSGBlendChunk.h"
#include "OSGDepthChunk.h"

#include "OSGGL.h"

#include <boost/cast.hpp>

#include <strstream>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderShadowMapEngineBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderShadowMapEngine.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Matrix ShaderShadowMapEngine::_matCubeFaceInv[6] =
{
    Matrix( 1,  0,  0,  0,   // + Z
            0, -1,  0,  0,
            0,  0, -1,  0,
            0,  0,  0,  1),
        
    Matrix(-1,  0,  0,  0,   // - Z
            0, -1,  0,  0,
            0,  0,  1,  0,
            0,  0,  0,  1),
        
    Matrix( 1,  0,  0,  0,   // + Y
            0,  0,  1,  0,
            0, -1,  0,  0,
            0,  0,  0,  1),

    Matrix( 1,  0,  0,  0,   // - Y
            0,  0, -1,  0,
            0,  1,  0,  0,
            0,  0,  0,  1),
    
    Matrix( 0,  0, -1,  0,   // + X
            0, -1,  0,  0,
           -1,  0,  0,  0,
            0,  0,  0,  1),
        
    Matrix( 0,  0,  1,  0,   // - X
            0, -1,  0,  0,
            1,  0,  0,  0,
            0,  0,  0,  1),
};

const GLenum ShaderShadowMapEngine::_cubeFaceTargets[6] =
{
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
};

const std::string ShaderShadowMapEngine::_pointFPCode(
    "#version 120\n"
    "\n"
    "#extension GL_EXT_gpu_shader4 : require\n"
    "#extension GL_EXT_gpu_shader4 : enable\n"
    "\n"
    "uniform samplerCubeShadow SSME_texShadow;\n"
    "\n"
    "uniform mat4              SSME_matEyeToLight;\n"
    "uniform mat4              SSME_matLightProj;\n"
    "\n"
    "vec4 OSG_SSME_FP_calcShadow(in vec4 ecFragPos)\n"
    "{\n"
    "    vec4 shadow   = vec4(0., 0., 0., 0.);\n"
    "    vec4 lcPos    = SSME_matEyeToLight * ecFragPos;\n"
    "    vec4 lcAbsPos = abs(lcPos);\n"
    "    vec4 plcPos;\n"
    "\n"
    "    if(lcAbsPos.x > lcAbsPos.y && lcAbsPos.x > lcAbsPos.z)\n"
    "    {\n"
    "        if(lcPos.x >= 0.)\n"
    "            plcPos = vec4(-1, -1, -1, 1) * lcPos.zyxw;\n"
    "        else\n"
    "            plcPos = vec4( 1, -1,  1, 1) * lcPos.zyxw;\n"
    "    }\n"
    "    else if(lcAbsPos.y > lcAbsPos.x && lcAbsPos.y > lcAbsPos.z)\n"
    "    {\n"
    "        if(lcPos.y >= 0.)\n"
    "            plcPos = vec4( 1,  1, -1, 1) * lcPos.xzyw;\n"
    "        else\n"
    "            plcPos = vec4( 1, -1,  1, 1) * lcPos.xzyw;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        if(lcPos.z >= 0.)\n"
    "            plcPos = vec4( 1, -1, -1, 1) * lcPos;\n"
    "        else\n"
    "            plcPos = vec4(-1, -1,  1, 1) * lcPos;\n"
    "    }\n"
    "\n"
    "    plcPos = SSME_matLightProj * plcPos;\n"
    "    plcPos = plcPos / plcPos.w;\n"
    "    plcPos = 0.5 + 0.5 * plcPos;\n"
    "\n"
    "    shadow = shadowCube(SSME_texShadow, vec4(lcPos.xyz, plcPos.z));\n"
    "\n"
    "    return shadow;\n"
    "}\n");

const std::string ShaderShadowMapEngine::_dirFPCode(
    "#version 120\n"
    "\n"
    "uniform sampler2DShadow   SSME_texShadow;\n"
    "\n"
    "uniform mat4              SSME_matEyeToLight;\n"
    "uniform mat4              SSME_matLightProj;\n"
    "\n"
    "vec4 OSG_SSME_FP_calcShadow(in vec4 ecFragPos)\n"
    "{\n"
    "    vec4 lcPos    = SSME_matEyeToLight * ecFragPos;\n"
    "    vec4 plcPos   = SSME_matLightProj  * lcPos;\n"
    "\n"
    "    plcPos = plcPos / plcPos.w;\n"
    "    plcPos = 0.5 + 0.5 * plcPos;\n"
    "\n"
    "    return shadow2D(SSME_texShadow, plcPos.xyz);\n"
    "}\n");

const std::string ShaderShadowMapEngine::_spotFPCode(
    "#version 120\n"
    "\n"
    "uniform sampler2DShadow   SSME_texShadow;\n"
    "\n"
    "uniform mat4              SSME_matEyeToLight;\n"
    "uniform mat4              SSME_matLightProj;\n"
    "\n"
    "vec4 OSG_SSME_FP_calcShadow(in vec4 ecFragPos)\n"
    "{\n"
    "    vec4 lcPos  = SSME_matEyeToLight * ecFragPos;\n"
    "    vec4 plcPos = SSME_matLightProj  * lcPos;\n"
    "\n"
    "    plcPos      = plcPos / plcPos.w;\n"
    "    plcPos      = 0.5 + 0.5 * plcPos;\n"
    "\n"
    "    return shadow2D(SSME_texShadow, plcPos.xyz);\n"
    "}\n");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderShadowMapEngine::initMethod(InitPhase ePhase)
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

ShaderShadowMapEngine::ShaderShadowMapEngine(void) :
    Inherited()
{
}

ShaderShadowMapEngine::ShaderShadowMapEngine(const ShaderShadowMapEngine &source) :
    Inherited(source)
{
}

ShaderShadowMapEngine::~ShaderShadowMapEngine(void)
{
}

/*----------------------------- class specific ----------------------------*/

ActionBase::ResultE ShaderShadowMapEngine::runOnEnter(
    Light *light, LightTypeE eType, RenderAction *ract)
{
    BitVector      bvMask = ract->getPassMask             (            );
    SSMEngineData *data   = ract->getData<SSMEngineData *>(_iDataSlotId);

    if(data == NULL)
    {
        SSMEngineDataUnrecPtr newData = SSMEngineData::createLocal();
        this->setData(newData, _iDataSlotId, ract);

        data = newData;
    }

    if(0x0000 != bvMask)
    {
        // already generating a shadow map for another light source
        if(0x0000 != (bvMask & bvLightPassMask))
        {
            this->recurseFrom(ract, light);

            handleEnter(light, eType, ract, data);
        }
    }
    else
    {
        // first light source to generate a shadow map
        ract->addPassMask(bvLightPassMask);
            handleEnter(light, eType, ract, data);
        ract->subPassMask(bvLightPassMask);
    }

    // continue rendering normally
    return Action::Continue;
}

ActionBase::ResultE ShaderShadowMapEngine::runOnLeave(
    Light *light, LightTypeE eType, RenderAction *ract)
{
    return Action::Continue;
}

void ShaderShadowMapEngine::changed(ConstFieldMaskArg whichField,
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderShadowMapEngine::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderShadowMapEngine NI" << std::endl;
}

void ShaderShadowMapEngine::handleEnter(
    Light *light, LightTypeE eType, RenderAction *ract, SSMEngineData *data)
{
    updateShadowTexChunk   (data);
    updateLightPassMaterial(data);
    updateBackground       (data);

    UInt32 parentTravMask = ract->getTravMask();
    ract->setTravMask(_sfShadowTravMask.getValue());

    // call specific handler for light type
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
        FWARNING(("ShaderShadowMapEngine::handleEnter: Unknown "
                  "light type [%u]\n", eType));
    }
    break;
    }

    ract->setTravMask(parentTravMask);
}

void ShaderShadowMapEngine::handlePointLightEnter(
    PointLight *pointL, RenderAction *ract, SSMEngineData *data)
{
    RenderPartition *parentPart = ract->getActivePartition();

    Matrix matEyeToWorld(parentPart->getCameraToWorld());
    Matrix matLightProj;

    Real32 lightNear;
    Real32 lightFar;

    calcPointLightRange(pointL, 0.001f,
                        parentPart->getNear(), parentPart->getFar(),
                        lightNear,             lightFar             );

    MatrixPerspective(matLightProj, Pi / 4.f, 1.f,
                      lightNear, lightFar         );

    Matrix matWorldToLight;
    Matrix matEyeToLight;

    calcPointLightMatrices(matWorldToLight, matEyeToLight,
                           pointL,          matEyeToWorld );

    updatePointLightShadowTexImage  (data);
    updatePointLightShadowTexBuffers(data);
    updatePointLightRenderTargets   (data);

    Int32 shadowTexUnit = (this->getForceTextureUnit() > 0) ?
                           this->getForceTextureUnit()      : 7;

    ShaderProgram *shadowFP = this->getShadowFragmentProgram();

    if(shadowFP == NULL)
    {
        ShaderProgramUnrecPtr newShadowFP = ShaderProgram::createLocal();
        newShadowFP->setShaderType(GL_FRAGMENT_SHADER);
        newShadowFP->setProgram   (_pointFPCode      );

        newShadowFP->addUniformVariable("SSME_matEyeToLight", matEyeToLight);
        newShadowFP->addUniformVariable("SSME_matLightProj",  matLightProj );
        newShadowFP->addUniformVariable("SSME_texShadow",     shadowTexUnit);

        this->setShadowFragmentProgram(newShadowFP);
        shadowFP = newShadowFP;
    }
    else
    {
        shadowFP->updateUniformVariable("SSME_matEyeToLight", matEyeToLight);
        shadowFP->updateUniformVariable("SSME_matLightProj",  matLightProj );
    }

    commitChanges();

    // schedule rendering of cube faces
    for(UInt16 i = 0; i < 6; ++i)
    {
        Matrix matWorldToLightFace(matWorldToLight);
        matWorldToLightFace.multLeft(_matCubeFaceInv[i]);

        this->pushPartition(ract);
        {
            RenderPartition   *part   = ract->getActivePartition( );
            Window            *win    = ract->getWindow         ( );
            FrameBufferObject *target = data->getRenderTargets  (i);
            Background        *back   = data->getBackground     ( );

            part->setRenderTarget(target);
            part->setWindow      (win   );

            part->calcViewportDimension(0.f, 0.f, 1.f, 1.f,
                                        target->getWidth (),
                                        target->getHeight() );

            part->setupProjection(matLightProj, Matrix::identity());
            part->setupViewing   (matWorldToLightFace             );

            part->setNear        (parentPart->getNear());
            part->setFar         (parentPart->getFar ());

            part->calcFrustum    (                     );

            part->setBackground  (back                 );

            // force material for shadow map generation
            part->overrideMaterial(data->getLightPassMaterials(0),
                                   ract->getActNode           ( ) );

            this->recurseFrom(ract, pointL);
            ract->useNodeList(false       );

            // undo override
            part->overrideMaterial(NULL,
                                   ract->getActNode           ( ) );
        }
        this->popPartition(ract);
    }
}

void ShaderShadowMapEngine::handleDirectionalLightEnter(
    DirectionalLight *dirL, RenderAction *ract, SSMEngineData *data)
{
    RenderPartition *parentPart = ract      ->getActivePartition();
    FrustumVolume    camFrust   = parentPart->getFrustum        ();

    Matrix matEyeToWorld  (parentPart->getCameraToWorld());
    Matrix matWorldToLight;
    Matrix matEyeToLight;

    calcDirectionalLightMatrices(matWorldToLight, matEyeToLight,
                                 dirL,            matEyeToWorld );

    // place light camera outside the scene bounding box:
    //  - project camera frustum and scene bounding box into a
    //    coordinate system where the directional light shines
    //    along the -z axis.
    //  - compute 2 AABBs that contain the projected frustum and
    //    scene BB
    //  - width and height of the ortho projection are determined from
    //    the frustum AABB, while near and far are determined by the
    //    scene AABB (offscreen objects cast shadows into the view volume)
          Pnt3f      camVerts  [10];
          Pnt3f      sceneVerts[10];
    const Matrix    &matSceneToWorld = ract->topMatrix ();
          BoxVolume  sceneBB         = ract->getActNode()->getVolume();

    camFrust.getCorners(camVerts  [0], camVerts  [1],
                        camVerts  [2], camVerts  [3],
                        camVerts  [4], camVerts  [5],
                        camVerts  [6], camVerts  [7] );
    sceneBB .getCorners(sceneVerts[0], sceneVerts[1],
                        sceneVerts[2], sceneVerts[3],
                        sceneVerts[4], sceneVerts[5],
                        sceneVerts[6], sceneVerts[7] );

    camVerts  [8].setValues(TypeTraits<Real32>::getMax(),
                            TypeTraits<Real32>::getMax(),
                            TypeTraits<Real32>::getMax() );
    camVerts  [9].setValues(TypeTraits<Real32>::getMin(),
                            TypeTraits<Real32>::getMin(),
                            TypeTraits<Real32>::getMin() );
    sceneVerts[8].setValues(TypeTraits<Real32>::getMax(),
                            TypeTraits<Real32>::getMax(),
                            TypeTraits<Real32>::getMax() );
    sceneVerts[9].setValues(TypeTraits<Real32>::getMin(),
                            TypeTraits<Real32>::getMin(),
                            TypeTraits<Real32>::getMin() );

    for(UInt32 i = 0; i < 8; ++i)
    {
        matWorldToLight.mult(camVerts  [i], camVerts  [i]);

        matSceneToWorld.mult(sceneVerts[i], sceneVerts[i]);
        matWorldToLight.mult(sceneVerts[i], sceneVerts[i]);

        camVerts  [8][0] = osgMin(camVerts  [8][0], camVerts  [i][0]);
        camVerts  [9][0] = osgMax(camVerts  [9][0], camVerts  [i][0]);
        camVerts  [8][1] = osgMin(camVerts  [8][1], camVerts  [i][1]);
        camVerts  [9][1] = osgMax(camVerts  [9][1], camVerts  [i][1]);

        sceneVerts[8][0] = osgMin(sceneVerts[8][0], sceneVerts[i][0]);
        sceneVerts[9][0] = osgMax(sceneVerts[9][0], sceneVerts[i][0]);
        sceneVerts[8][1] = osgMin(sceneVerts[8][1], sceneVerts[i][1]);
        sceneVerts[9][1] = osgMax(sceneVerts[9][1], sceneVerts[i][1]);
        sceneVerts[8][2] = osgMin(sceneVerts[8][2], sceneVerts[i][2]);
        sceneVerts[9][2] = osgMax(sceneVerts[9][2], sceneVerts[i][2]);
    }

    // these points are the corners of the ortho shadow view volume
    Pnt3f lightMin(osgMax(camVerts[8][0], sceneVerts[8][0]),
                   osgMax(camVerts[8][1], sceneVerts[8][1]),
                   -sceneVerts[9][2]);
    
    Pnt3f lightMax(osgMin(camVerts[9][0], sceneVerts[9][0]),
                   osgMin(camVerts[9][1], sceneVerts[9][1]),
                   -sceneVerts[8][2]);

    // enlarge by 2% in x, y, z direction
    lightMin[0] -= (lightMax[0] - lightMin[0]) * 0.01f;
    lightMin[1] -= (lightMax[1] - lightMin[1]) * 0.01f; 
    lightMin[2] -= (lightMax[2] - lightMin[2]) * 0.01f;

    lightMax[0] += (lightMax[0] - lightMin[0]) * 0.01f;
    lightMax[1] += (lightMax[1] - lightMin[1]) * 0.01f;
    lightMax[2] += (lightMax[2] - lightMin[2]) * 0.01f;

    Matrix matLightProj;
    Matrix matLightProjTrans;

    MatrixOrthogonal(matLightProj,
                     lightMin[0], lightMax[0],
                     lightMin[1], lightMax[1],
                     lightMin[2], lightMax[2] );

    updateShadowTexImage  (data);
    updateShadowTexBuffers(data);
    updateRenderTargets   (data);

    Int32 shadowTexUnit = (this->getForceTextureUnit() > 0) ?
                           this->getForceTextureUnit()      : 7;

    ShaderProgram *shadowFP = this->getShadowFragmentProgram();

    if(shadowFP == NULL)
    {
        ShaderProgramUnrecPtr newShadowFP = ShaderProgram::createLocal();
        newShadowFP->setShaderType(GL_FRAGMENT_SHADER);
        newShadowFP->setProgram   (_dirFPCode        );

        newShadowFP->addUniformVariable("SSME_matEyeToLight", matEyeToLight);
        newShadowFP->addUniformVariable("SSME_matLightProj",  matLightProj );
        newShadowFP->addUniformVariable("SSME_texShadow",     shadowTexUnit);

        this->setShadowFragmentProgram(newShadowFP);
        shadowFP = newShadowFP;
    }
    else
    {
        shadowFP->updateUniformVariable("SSME_matEyeToLight", matEyeToLight);
        shadowFP->updateUniformVariable("SSME_matLightProj",  matLightProj );
    }

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

        part->setupProjection(matLightProj, matLightProjTrans);
        part->setupViewing   (matWorldToLight                );

        part->setNear        (parentPart->getNear());
        part->setFar         (parentPart->getFar ());

        part->calcFrustum    (                     );

        part->setBackground  (back                 );

        // force material for shadow map generation
        part->overrideMaterial(data->getLightPassMaterials(0),
                               ract->getActNode           ( ) );

        this->recurseFrom(ract, dirL);
        ract->useNodeList(false     );

        // undo override
        part->overrideMaterial(NULL,
                               ract->getActNode           ( ) );
    }
    this->popPartition(ract);
}

void ShaderShadowMapEngine::handleSpotLightEnter(
    SpotLight *spotL, RenderAction *ract, SSMEngineData *data)
{
    RenderPartition *parentPart    = ract->getActivePartition();
//    Real             cosSpotCutOff = osgCos(spotL->getSpotCutOff());

    Matrix matEyeToWorld  (parentPart->getCameraToWorld());
    Matrix matWorldToLight;
    Matrix matEyeToLight;

    calcSpotLightMatrices(matWorldToLight, matEyeToLight, 
                          spotL,           matEyeToWorld );

    Real32  lightNear;
    Real32  lightFar;

    calcPointLightRange(spotL, 0.001f,
                        parentPart->getNear(), parentPart->getFar(),
                        lightNear,             lightFar             );

    if(getShadowNear() != 0.f)
    {
        lightNear = getShadowNear();
    }

    if(getShadowFar() != 0.f)
    {
        lightFar  = getShadowFar();
    }

    Matrix matLightProj;
    Matrix matLightProjTrans;

    MatrixPerspective(matLightProj, 
                      spotL->getSpotCutOff(), 1.f,
                      lightNear, lightFar         );
    
    updateShadowTexImage  (data);
    updateShadowTexBuffers(data);
    updateRenderTargets   (data);

    Int32          shadowTexUnit = (this->getForceTextureUnit() > 0) ?
                                    this->getForceTextureUnit()      : 7;
    ShaderProgram *shadowFP      = this->getShadowFragmentProgram();

    if(shadowFP == NULL)
    {
        ShaderProgramUnrecPtr newShadowFP = ShaderProgram::createLocal();
        newShadowFP->setShaderType(GL_FRAGMENT_SHADER);
        newShadowFP->setProgram   (_spotFPCode       );

        newShadowFP->addUniformVariable("SSME_matEyeToLight", matEyeToLight);
        newShadowFP->addUniformVariable("SSME_matLightProj",  matLightProj );
        newShadowFP->addUniformVariable("SSME_texShadow",     shadowTexUnit);

        this->setShadowFragmentProgram(newShadowFP);
        shadowFP = newShadowFP;
    }
    else
    {
        shadowFP->updateUniformVariable("SSME_matEyeToLight", matEyeToLight);
        shadowFP->updateUniformVariable("SSME_matLightProj",  matLightProj );
    }

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

        part->setupProjection(matLightProj, matLightProjTrans);
        part->setupViewing   (matWorldToLight                );

        part->setNear        (parentPart->getNear());
        part->setFar         (parentPart->getFar ());

        part->calcFrustum    (                     );

        part->setBackground  (back                 );

        // force material for shadow map generation
        part->overrideMaterial(data->getLightPassMaterials(0),
                               ract->getActNode           ( ) );

        this->recurseFrom(ract, spotL);
        ract->useNodeList(false      );

        // undo override
        part->overrideMaterial(NULL,
                               ract->getActNode           ( ) );
    }
    this->popPartition(ract);
}

/*! Calculates \a matWorldToLight and \a matEyeToLight for a directional light
    \a dirL and inverse viewing matrix \a matEyeToWorld.
*/
void ShaderShadowMapEngine::calcDirectionalLightMatrices(
          Matrix           &matWorldToLight,
          Matrix           &matEyeToLight,
    const DirectionalLight *dirL,
    const Matrix           &matEyeToWorld)
{
    if(dirL->getBeacon() != NULL)
        dirL->getBeacon()->getToWorld(matWorldToLight);

    Quaternion rotLightDir  (Vec3f(0.f, 0.f, 1.f), dirL->getDirection());
    Matrix     matLightDir;
    matLightDir.setRotate(rotLightDir);
    
    matWorldToLight.mult  (matLightDir);
    matWorldToLight.invert(           );

    matEyeToLight = matWorldToLight;
    matEyeToLight.mult(matEyeToWorld);
}

void ShaderShadowMapEngine::calcPointLightMatrices(
          Matrix     &matWorldToLight,
          Matrix     &matEyeToLight,
    const PointLight *pointL,
    const Matrix     &matEyeToWorld)
{
    if(pointL->getBeacon() != NULL)
        pointL->getBeacon()->getToWorld(matWorldToLight);

    Matrix matLightPos;
    matLightPos    .setTranslate(pointL->getPosition());
    matWorldToLight.mult        (matLightPos          );
    matWorldToLight.invert      (                     );

    matEyeToLight = matWorldToLight;
    matEyeToLight.mult(matEyeToWorld);
}

/*! Calculates \a matWorldToLight and \a matEyeToLight for a spot light
    \a spotL and inverse viewing matrix \a matEyeToWorld.
*/
void ShaderShadowMapEngine::calcSpotLightMatrices(
          Matrix    &matWorldToLight,
          Matrix    &matEyeToLight,
    const SpotLight *spotL, 
    const Matrix    &matEyeToWorld)
{
    if(spotL->getBeacon() != NULL)
        spotL->getBeacon()->getToWorld(matWorldToLight);

    Matrix matLightPos;
    matLightPos.setTranslate(spotL->getPosition());

    Matrix     matLightDir;
    Quaternion rotLightDir(Vec3f(0.f, 0.f, 1.f), -spotL->getDirection());
    matLightDir.setRotate(rotLightDir);

    matWorldToLight.mult  (matLightPos);
    matWorldToLight.mult  (matLightDir);
    matWorldToLight.invert(           );

    matEyeToLight = matWorldToLight;
    matEyeToLight.mult(matEyeToWorld);
}

void ShaderShadowMapEngine::calcPointLightRange(
    const PointLight *pointL,      Real32  lightThreshold,
          Real32      defaultNear, Real32  defaultFar,
          Real32     &outNear,     Real32 &outFar         )
{
    outNear = defaultNear;
    outFar  = defaultFar;

    Real32 kQ = pointL->getQuadraticAttenuation();
    Real32 kL = pointL->getLinearAttenuation   ();
    Real32 kC = pointL->getConstantAttenuation ();

    if(osgAbs(kQ) > TypeTraits<Real32>::getDefaultEps())
    {
        Real32 det = kL * kL  - 4.f * kQ * (kC - 1.f / lightThreshold);

        if(det >= 0)
        {
            det       = osgSqrt(det);
            Real32 r1 = - kL + det / (2.f * kQ);
            Real32 r2 = - kL - det / (2.f * kQ);

            if(r1 > 0.f && r2 > 0.f)
            {
                outFar = osgMin(r1, r2);
            }
            else if(r1 > 0.f)
            {
                outFar = r1;
            }
            else if(r2 > 0.f)
            {
                outFar = r2;
            }
        }
    }
    else if(osgAbs(kL) > TypeTraits<Real32>::getDefaultEps())
    {
        Real32 r = (1.f / lightThreshold - kC) / kL;

        if(r > 0.f)
        {
            outFar = r;
        }
    }
}

void ShaderShadowMapEngine::updateShadowTexChunk(SSMEngineData *data)
{
    TextureObjChunk *bufTex = data->getShadowTexChunk();
    
    if(bufTex == NULL)
    {
        TextureObjChunkUnrecPtr newBufTex = TextureObjChunk::createLocal();
        newBufTex->setMinFilter     (GL_LINEAR              );
        newBufTex->setMagFilter     (GL_LINEAR              );
        newBufTex->setWrapS         (GL_CLAMP_TO_EDGE       );
        newBufTex->setWrapT         (GL_CLAMP_TO_EDGE       );
        newBufTex->setWrapR         (GL_CLAMP_TO_EDGE       );
        newBufTex->setScale         (false                  );
        newBufTex->setInternalFormat(GL_DEPTH_COMPONENT24   );
        newBufTex->setExternalFormat(GL_DEPTH_COMPONENT     );
        newBufTex->setCompareMode   (GL_COMPARE_R_TO_TEXTURE);
        newBufTex->setCompareFunc   (GL_LESS                );
        newBufTex->setDepthMode     (GL_LUMINANCE           );

        data->setShadowTexChunk(newBufTex);
        this->setShadowTexChunk(newBufTex);
    }
}

void ShaderShadowMapEngine::updateLightPassMaterial(SSMEngineData *data)
{
    if(data->getMFLightPassMaterials()->empty() == true)
    {
        MaterialChunkUnrecPtr newMatChunk = MaterialChunk::createLocal();
        newMatChunk->setLit          (false  );
        newMatChunk->setColorMaterial(GL_NONE);

        ColorMaskChunkUnrecPtr newCMaskChunk = ColorMaskChunk::create();
        newCMaskChunk->setMaskR(false);
        newCMaskChunk->setMaskG(false);
        newCMaskChunk->setMaskB(false);
        newCMaskChunk->setMaskA(false);

        PolygonChunkUnrecPtr newPolyChunk = PolygonChunk::createLocal();
        newPolyChunk->setOffsetFill  (true                   );
        newPolyChunk->setOffsetFactor(this->getOffsetFactor());
        newPolyChunk->setOffsetBias  (this->getOffsetBias  ());

        ChunkMaterialUnrecPtr newLightPassMat = ChunkMaterial::createLocal();
        newLightPassMat->addChunk(newMatChunk  );
        newLightPassMat->addChunk(newCMaskChunk);
        newLightPassMat->addChunk(newPolyChunk );

        data->editMFLightPassMaterials()->push_back(newLightPassMat);
    }
}

void ShaderShadowMapEngine::updateBackground(SSMEngineData *data)
{
    Background *back = data->getBackground();

    if(back == NULL)
    {
        SolidBackgroundUnrecPtr newBack = SolidBackground::createLocal();
        newBack->setClearColor(false);

        data->setBackground(newBack);
    }
}

void ShaderShadowMapEngine::updatePointLightShadowTexImage(SSMEngineData *data)
{
    Image           *bufImg = data->getShadowTexImage();
    TextureObjChunk *bufTex = data->getShadowTexChunk();

    FASSERT((bufTex != NULL), false)

    if(bufImg == NULL)
    {
        ImageUnrecPtr newBufImg = Image::createLocal();
        newBufImg->set(Image::OSG_L_PF,
                       this->getWidth (),
                       this->getHeight(),
                       1,
                       1,
                       1,
                       0.,
                       NULL,
                       Image::OSG_UINT8_IMAGEDATA,
                       false,
                       6);

        bufTex->setImage         (newBufImg);
        data  ->setShadowTexImage(newBufImg);

        bufImg = newBufImg;
    }

    if((bufImg->getWidth () != this->getWidth ()) ||
       (bufImg->getHeight() != this->getHeight())   )
    {
        bufImg->setWidth (this->getWidth ());
        bufImg->setHeight(this->getHeight());
    }
}

void ShaderShadowMapEngine::updateShadowTexImage(SSMEngineData *data)
{
    Image           *bufImg = data->getShadowTexImage();
    TextureObjChunk *bufTex = data->getShadowTexChunk();

    FASSERT((bufTex != NULL), false)

    if(bufImg == NULL)
    {
        ImageUnrecPtr newBufImg = Image::createLocal();
        newBufImg->set(Image::OSG_L_PF,
                       this->getWidth (),
                       this->getHeight(),
                       1,
                       1,
                       1,
                       0.,
                       NULL,
                       Image::OSG_UINT8_IMAGEDATA,
                       false,
                       1);

        bufTex->setImage         (newBufImg);
        data  ->setShadowTexImage(newBufImg);

        bufImg = newBufImg;
    }

    if((bufImg->getWidth () != this->getWidth ()) ||
       (bufImg->getHeight() != this->getHeight())   )
    {
        bufImg->setWidth (this->getWidth ());
        bufImg->setHeight(this->getHeight());
    }
}

void ShaderShadowMapEngine::updatePointLightShadowTexBuffers(
    SSMEngineData *data)
{
    TextureObjChunk *bufTex = data->getShadowTexChunk();

    if(data->getMFShadowTexBuffers()->empty() == true)
    {
        for(UInt16 i = 0; i < 6; ++i)
        {
            TextureBufferUnrecPtr newBuf = TextureBuffer::createLocal();
            newBuf->setTexture  (bufTex             );
            newBuf->setTexTarget(_cubeFaceTargets[i]);

            data->editMFShadowTexBuffers()->push_back(newBuf);
        }
    }
}

void ShaderShadowMapEngine::updateShadowTexBuffers(SSMEngineData *data)
{
    TextureObjChunk *bufTex = data->getShadowTexChunk();

    if(data->getMFShadowTexBuffers()->empty() == true)
    {
        TextureBufferUnrecPtr newBuf = TextureBuffer::createLocal();
        newBuf->setTexture  (bufTex       );
        newBuf->setTexTarget(GL_TEXTURE_2D);

        data->editMFShadowTexBuffers()->push_back(newBuf);
    }
}

void ShaderShadowMapEngine::updatePointLightRenderTargets(SSMEngineData *data)
{
    if(data->getMFRenderTargets()->empty() == true)
    {
        for(UInt16 i = 0; i < 6; ++i)
        {
            FrameBufferObjectUnrecPtr newTarget =
                FrameBufferObject::createLocal();
            newTarget->setWidth          (this->getWidth           ( ));
            newTarget->setHeight         (this->getHeight          ( ));
            newTarget->setDepthAttachment(data->getShadowTexBuffers(i));

            data->editMFRenderTargets()->push_back(newTarget);
        }
    }
    else
    {
        for(UInt16 i = 0; i < 6; ++i)
        {
            FrameBufferObject *target = data->getRenderTargets(i);

            if((target->getWidth () != this->getWidth ()) ||
               (target->getHeight() != this->getHeight())   )
            {
                target->setWidth (this->getWidth ());
                target->setHeight(this->getHeight());
            }
        }
    }
}

void ShaderShadowMapEngine::updateRenderTargets(SSMEngineData *data)
{
    if(data->getMFRenderTargets()->empty() == true)
    {
        FrameBufferObjectUnrecPtr newTarget =
            FrameBufferObject::createLocal();
        newTarget->setWidth          (this->getWidth           ( ));
        newTarget->setHeight         (this->getHeight          ( ));
        newTarget->setDepthAttachment(data->getShadowTexBuffers(0));

        data->editMFRenderTargets()->push_back(newTarget);
    }
    else
    {
        FrameBufferObject *target = data->getRenderTargets(0);

        if((target->getWidth () != this->getWidth ()) ||
           (target->getHeight() != this->getHeight())   )
        {
            target->setWidth (this->getWidth ());
            target->setHeight(this->getHeight());
        }
    }
}

OSG_END_NAMESPACE
