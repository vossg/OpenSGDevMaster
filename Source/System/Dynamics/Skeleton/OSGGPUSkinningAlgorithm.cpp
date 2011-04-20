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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGGPUSkinningAlgorithm.h"
#include "OSGGPUSkinningDataAttachment.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGPUSkinningAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGGPUSkinningAlgorithm.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string GPUSkinningAlgorithm::_vpVertexSkinning(
    "#version 120\n"
    "\n"
    "uniform mat4 matBindShape;\n"
    "uniform mat4 matJoints[70];\n"
    ""
    "void calcSkin(inout vec4 vertPos,  inout vec3 vertNorm,\n"
    "              in    vec4 jointIdx, in    vec4 jointWeight)\n"
    "{\n"
    "    float sumWinv = 1. / dot(jointWeight, vec4(1., 1., 1., 1.));\n"
    "    vec4  inNorm  = vec4(vertNorm,   0.);\n"
    "    vec4  tmpPos  = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpNorm = vec4(0., 0., 0., 0.);\n"
    "\n"
    "    for(int i = 0; i < 4; ++i)\n"
    "    {\n"
    "        int  idxJ = int(jointIdx[i]);\n"
    "\n"
    "        if(idxJ >= 0)\n"
    "        {\n"
    "            mat4 matJ = matJoints[idxJ] * matBindShape;\n"
    "\n"
    "            tmpPos  += jointWeight[i] * (matJ * vertPos);\n"
    "            tmpNorm += jointWeight[i] * (matJ * inNorm);\n"
    "        }\n"
    "    }\n"
    "\n"
    "    vertPos  = sumWinv * tmpPos;\n"
    "    vertNorm = sumWinv * tmpNorm.xyz;\n"
    "}\n"
    "\n"
    "void calcSkin(inout vec4 vertPos,     inout vec3 vertNorm,\n"
    "              inout vec3 vertTangent,\n"
    "              in    vec4 jointIdx,    in    vec4 jointWeight  )\n"
    "{\n"
    "    float sumWinv     = 1. / dot(jointWeight, vec4(1., 1., 1., 1.));\n"
    "    vec4  inNorm      = vec4(vertNorm,     0.);\n"
    "    vec4  inTangent   = vec4(vertTangent,  0.);\n"
    "    vec4  tmpPos      = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpNorm     = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpTangent  = vec4(0., 0., 0., 0.);\n"
    "\n"
    "    for(int i = 0; i < 4; ++i)\n"
    "    {\n"
    "        int  idxJ = int(jointIdx[i]);\n"
    "\n"
    "        if(idxJ >= 0)\n"
    "        {\n"
    "            mat4 matJ = matJoints[idxJ] * matBindShape;\n"
    "\n"
    "            tmpPos      += jointWeight[i] * (matJ * vertPos);\n"
    "            tmpNorm     += jointWeight[i] * (matJ * inNorm);\n"
    "            tmpTangent  += jointWeight[i] * (matJ * inTangent);\n"
    "        }\n"
    "    }\n"
    "\n"
    "    vertPos      = sumWinv * tmpPos;\n"
    "    vertNorm     = sumWinv * tmpNorm.xyz;\n"
    "    vertTangent  = sumWinv * tmpTangent.xyz;\n"
    "}\n"
    "\n"
    "void calcSkin(inout vec4 vertPos,     inout vec3 vertNorm,\n"
    "              inout vec3 vertTangent, inout vec3 vertBinormal,\n"
    "              in    vec4 jointIdx,    in    vec4 jointWeight  )\n"
    "{\n"
    "    float sumWinv     = 1. / dot(jointWeight, vec4(1., 1., 1., 1.));\n"
    "    vec4  inNorm      = vec4(vertNorm,     0.);\n"
    "    vec4  inTangent   = vec4(vertTangent,  0.);\n"
    "    vec4  inBinormal  = vec4(vertBinormal, 0.);\n"
    "    vec4  tmpPos      = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpNorm     = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpTangent  = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpBinormal = vec4(0., 0., 0., 0.);\n"
    "\n"
    "    for(int i = 0; i < 4; ++i)\n"
    "    {\n"
    "        int  idxJ = int(jointIdx[i]);\n"
    "\n"
    "        if(idxJ >= 0)\n"
    "        {\n"
    "            mat4 matJ = matJoints[idxJ] * matBindShape;\n"
    "\n"
    "            tmpPos      += jointWeight[i] * (matJ * vertPos);\n"
    "            tmpNorm     += jointWeight[i] * (matJ * inNorm);\n"
    "            tmpTangent  += jointWeight[i] * (matJ * inTangent);\n"
    "            tmpBinormal += jointWeight[i] * (matJ * inBinormal);\n"
    "        }\n"
    "    }\n"
    "\n"
    "    vertPos      = sumWinv * tmpPos;\n"
    "    vertNorm     = sumWinv * tmpNorm.xyz;\n"
    "    vertTangent  = sumWinv * tmpTangent.xyz;\n"
    "    vertBinormal = sumWinv * tmpBinormal.xyz;\n"
    "}\n"
    );

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GPUSkinningAlgorithm::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GPUSkinningAlgorithm::GPUSkinningAlgorithm(void) :
    Inherited()
{
}

GPUSkinningAlgorithm::GPUSkinningAlgorithm(const GPUSkinningAlgorithm &source) :
    Inherited(source)
{
}

GPUSkinningAlgorithm::~GPUSkinningAlgorithm(void)
{
}

/*----------------------------- class specific ----------------------------*/

void
GPUSkinningAlgorithm::adjustVolume(Volume &volume)
{
    if(_sfSkeleton.getValue() != NULL)
        _sfSkeleton.getValue()->adjustVolume(volume);
}

ActionBase::ResultE
GPUSkinningAlgorithm::renderEnter(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    SkinnedGeometry *skinGeo = getSkin    ();
    Skeleton        *skel    = getSkeleton();
    RenderAction    *ract    =
        boost::polymorphic_downcast<RenderAction *>(action); 

    OSG_ASSERT(skinGeo != NULL);
    OSG_ASSERT(skel    != NULL);

    GPUSkinningDataAttachmentUnrecPtr data = getGPUSkinningData(skel);

    if(data == NULL)
    {
        data = GPUSkinningDataAttachment::create();
        skel->addAttachment(data);
    }

    skel->renderEnter(action, skinGeo);

    ShaderProgramChunkUnrecPtr         shCode = data->getShaderCode();
    ShaderProgramVariableChunkUnrecPtr shData = getShaderData();

    if(shCode == NULL)
    {
        shCode = ShaderProgramChunk::create();
        data->setShaderCode(shCode);

        ShaderProgramUnrecPtr vp = ShaderProgram::createVertexShader();
        vp->setProgram(_vpVertexSkinning);

        shCode->addShader(vp);

        vp->addUniformVariable(
            "matJoints",    (*skel->getMFJointMatrices()));
    }
    else if(data->getDataValid() == false)
    {
        ShaderProgram *vp = shCode->getVertexShader(0);

        vp->updateUniformVariable(
            "matJoints",    (*skel->getMFJointMatrices()));

        data->setDataValid(true);
    }

    if(shData == NULL)
    {
        shData = ShaderProgramVariableChunk::create();
        setShaderData(shData);

        shData->addUniformVariable(
            "matBindShape", skinGeo->getBindShapeMatrix());
    }
    else
    {
        shData->updateUniformVariable(
            "matBindShape", skinGeo->getBindShapeMatrix());
    }

    ract->pushState();
    {
        ract->addOverride(ShaderProgramChunk        ::getStaticClassId(),
                          shCode                                         );
        ract->addOverride(ShaderProgramVariableChunk::getStaticClassId(),
                          shData                                         );

        res = skinGeo->renderActionEnterHandler(ract);
    }
    ract->popState ();

    return res;
}

ActionBase::ResultE
GPUSkinningAlgorithm::renderLeave(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    SkinnedGeometry *skinGeo = getSkin();
    Skeleton        *skel    = getSkeleton();

    skel->renderLeave(action, skinGeo);

    res = skinGeo->renderActionLeaveHandler(action);

    return res;
}

ActionBase::ResultE
GPUSkinningAlgorithm::intersectEnter(Action *action)
{
    SkinnedGeometry *skinGeo = getSkin();

    return skinGeo->intersect(action);
}

GPUSkinningAlgorithm::RenderModeE
GPUSkinningAlgorithm::getRenderMode(void) const
{
    return SkinnedGeometry::RMSkinnedGPU;
}

void GPUSkinningAlgorithm::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if((SkeletonFieldMask & whichField) != 0    &&
       _sfSkeleton.getValue()           != NULL   )
    {
        if(_sfSkeleton.getValue()->hasChangedFunctor(boost::bind(
               &GPUSkinningAlgorithm::skeletonChanged,
               this, _1, _2                                )) == false)
        {
            _sfSkeleton.getValue()->addChangedFunctor(boost::bind(
                &GPUSkinningAlgorithm::skeletonChanged,
                this, _1, _2                                ),
                "GPUSkinningAlgorithm::skeletonChanged"  );
        }
    }

    Inherited::changed(whichField, origin, details);
}

void GPUSkinningAlgorithm::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GPUSkinningAlgorithm NI" << std::endl;
}

void
GPUSkinningAlgorithm::skeletonChanged(FieldContainer    *fc,
                                      ConstFieldMaskArg  whichField)
{
    if(((Skeleton::JointMatricesFieldMask      |
         Skeleton::JointNormalMatricesFieldMask) & whichField) != 0)
    {
        OSG_ASSERT(fc == _sfSkeleton.getValue());

        GPUSkinningDataAttachment *data =
            getGPUSkinningData(_sfSkeleton.getValue());

        if(data != NULL)
            data->setDataValid(false);
    }
}

void
GPUSkinningAlgorithm::resolveLinks(void)
{
    if(_sfSkeleton.getValue() != NULL)
    {
        _sfSkeleton.getValue()->subChangedFunctor(boost::bind(
            &GPUSkinningAlgorithm::skeletonChanged,
            this, _1, _2                                ));
    }

    Inherited::resolveLinks();
}

#if 0
// renderEnter code that does not work because of problems with the
// way ProgVars are handled and how uniform locations are invalidated

    ShaderProgramChunkUnrecPtr         shCode = getShaderCode();
    ShaderProgramVariableChunkUnrecPtr shData = getShaderData();

    if(shCode == NULL)
    {
        shCode = ShaderProgramChunk::create();
        setShaderCode(shCode);

        ShaderProgramUnrecPtr vp = ShaderProgram::createVertexShader();
        vp->setProgram(_vpVertexSkinning);

        shCode->addShader(vp);


        vp->addUniformVariable(
            "matBindShape", skinGeo->getBindShapeMatrix());
        vp->addUniformVariable(
            "matJoints",    (*skel->getMFJointMatrices()));
    }
    else
    {
        ShaderProgram *vp = shCode->getVertexShader(0);

        vp->updateUniformVariable(
            "matBindShape", skinGeo->getBindShapeMatrix());
        vp->updateUniformVariable(
            "matJoints",    (*skel->getMFJointMatrices()));
    }

#if 0
    if(shData == NULL)
    {
        shData = ShaderProgramVariableChunk::create();
        setShaderData(shData);

        shData->addUniformVariable(
            "matBindShape", skinGeo->getBindShapeMatrix());
        shData->addUniformVariable(
            "matJoints",    (*skel->getMFJointMatrices()));
    }
    else
    {
        shData->updateUniformVariable(
            "matBindShape", skinGeo->getBindShapeMatrix());
        shData->updateUniformVariable(
            "matJoints",    (*skel->getMFJointMatrices()));
    }
#endif
#endif

OSG_END_NAMESPACE
