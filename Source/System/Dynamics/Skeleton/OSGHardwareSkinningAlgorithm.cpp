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

#include "OSGHardwareSkinningAlgorithm.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHardwareSkinningAlgorithmBase.cpp file.
// To modify it, please change the .fcd file (OSGHardwareSkinningAlgorithm.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string HardwareSkinningAlgorithm::_vpVertexSkinning(
    "#version 120\n"
    "\n"
    "uniform mat4 matBindShape;\n"
    "uniform mat4 matJoints[64];\n"
    ""
    "void calcSkin(inout vec4 pos,    inout vec3 norm,\n"
    "              in    vec4 matIdx, in    vec4 weight)\n"
    "{\n"
    "    float sumW    = dot(weight, vec4(1., 1., 1., 1.));\n"
    "    vec4  inPos   = pos;\n"
    "    vec4  inNorm  = vec4(norm,       0.);\n"
    "    vec4  tmpPos  = vec4(0., 0., 0., 0.);\n"
    "    vec4  tmpNorm = vec4(0., 0., 0., 0.);\n"
    "\n"
    "    for(int i = 0; i < 4; ++i)\n"
    "    {\n"
    "        int  idxJ = int(matIdx[i]);\n"
    "        mat4 matJ = matJoints[idxJ] * matBindShape;\n"
    "\n"
    "        tmpPos  += weight[i] * (matJ * inPos);\n"
    "        tmpNorm += weight[i] * (matJ * inNorm);\n"
    "    }\n"
    "\n"
    "    pos  = tmpPos      / sumW;\n"
    "    norm = tmpNorm.xyz / sumW;\n"
    "}\n"
    );

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HardwareSkinningAlgorithm::initMethod(InitPhase ePhase)
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

HardwareSkinningAlgorithm::HardwareSkinningAlgorithm(void) :
    Inherited()
{
}

HardwareSkinningAlgorithm::HardwareSkinningAlgorithm(const HardwareSkinningAlgorithm &source) :
    Inherited(source)
{
}

HardwareSkinningAlgorithm::~HardwareSkinningAlgorithm(void)
{
}

/*----------------------------- class specific ----------------------------*/

void
HardwareSkinningAlgorithm::adjustVolume(Volume &volume)
{
    SkinnedGeometry *skinGeo = getParent();
    Skeleton        *skel    = skinGeo->getSkeleton();

    skel->adjustVolume(volume);
}

ActionBase::ResultE
HardwareSkinningAlgorithm::renderEnter(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    SkinnedGeometry *skinGeo = getParent();
    Skeleton        *skel    = skinGeo->getSkeleton();
    RenderAction    *ract    =
        boost::polymorphic_downcast<RenderAction *>(action); 


    ShaderProgramChunkUnrecPtr         shCode = getShaderCode();
    ShaderProgramVariableChunkUnrecPtr shData = getShaderData();

    if(shCode == NULL)
    {
        shCode = ShaderProgramChunk::create();
        setShaderCode(shCode);

        ShaderProgramUnrecPtr vp = ShaderProgram::createVertexShader();
        vp->setProgram(_vpVertexSkinning);

        shCode->addShader(vp);
    }

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
            "matJoints",    (*skel->getMFJointMatrices()));
    }

    ract->pushState();
    {
        ract->addOverride(ShaderProgramChunk        ::getStaticClassId(), shCode);
        ract->addOverride(ShaderProgramVariableChunk::getStaticClassId(), shData);

        res = skinGeo->renderActionEnterHandler(ract);
    }
    ract->popState ();

    return res;
}

ActionBase::ResultE
HardwareSkinningAlgorithm::renderLeave(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    SkinnedGeometry *skinGeo = getParent();

    res = skinGeo->renderActionLeaveHandler(action);

    return res;
}

void HardwareSkinningAlgorithm::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HardwareSkinningAlgorithm::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump HardwareSkinningAlgorithm NI" << std::endl;
}

OSG_END_NAMESPACE
