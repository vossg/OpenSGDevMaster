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

#include "OSGConfig.h"
#include "OSGSkinnedGeometry.h"
#include "OSGPrimeMaterial.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkinnedGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGSkinnedGeometry.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string SkinnedGeometry::_vpVertexSkinning(
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
    "        int  index = int(matIdx[i]);\n"
    "        mat4 matJ  = matJoints[index] * matBindShape;\n"
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

void SkinnedGeometry::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SkinnedGeometry::getClassType(),
            reinterpret_cast<Action::Callback>(&SkinnedGeometry::renderEnter));
        RenderAction::registerLeaveDefault(
            SkinnedGeometry::getClassType(),
            reinterpret_cast<Action::Callback>(&SkinnedGeometry::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkinnedGeometry::SkinnedGeometry(void) :
    Inherited()
{
}

SkinnedGeometry::SkinnedGeometry(const SkinnedGeometry &source) :
    Inherited(source)
{
}

SkinnedGeometry::~SkinnedGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkinnedGeometry::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    if((FlagsFieldMask & whichField) != 0)
    {
        if(testFlag(SGFlagDebug) == false)
        {
            _debugDrawPos.clear();
            _debugDrawIdx.clear();

            if(_sfSkeleton.getValue() != NULL)
                _sfSkeleton.getValue()->setUseInvBindMatrix(true);
        }
        else
        {
            if(_sfSkeleton.getValue() != NULL)
                _sfSkeleton.getValue()->setUseInvBindMatrix(false);
        }

        invalidateVolume();
    }

    Inherited::changed(whichField, origin, details);
}

Action::ResultE
SkinnedGeometry::renderEnter(Action *action)
{
    if(_sfSkeleton.getValue() == NULL)
    {
        SWARNING << "SkinnedGeometry::renderEnter: No skeleton." << std::endl;

        return Action::Continue;
    }

    Action::ResultE  res  = Action::Continue;
    RenderAction    *ract =
        boost::polymorphic_downcast<RenderAction *>(action);

    return res;
}

Action::ResultE
SkinnedGeometry::renderLeave(Action *action)
{
    if(_sfSkeleton.getValue() == NULL)
    {
        SWARNING << "SkinnedGeometry::renderLeave: No skeleton." << std::endl;

        return Action::Continue;
    }

    Action::ResultE  res  = Action::Continue;
    RenderAction    *ract =
        boost::polymorphic_downcast<RenderAction *>(action);

    if(testFlag(SGFlagUnskinned) == true)
    {
        ract->pushMatrix(_sfBindShapeMatrix.getValue());
        res = Inherited::renderActionEnterHandler(ract);
        ract->popMatrix();
    }
    else if(testFlag(SGFlagDebug) == true)
    {
        res = renderDebug(ract);
    }
    else if(testFlag(SGFlagHardware) == true)
    {
        res = renderHardware(ract);
    }
    else
    {
        res = renderSoftware(ract);
    }

    return res;
}

void
SkinnedGeometry::fill(DrawableStatsAttachment *drawStats)
{
    Inherited::fill(drawStats);
}

void SkinnedGeometry::adjustVolume(Volume & volume)
{
    if(_sfSkeleton.getValue()    != NULL  &&
       testFlag(SGFlagUnskinned) == false   )
    {
        _sfSkeleton.getValue()->adjustVolume(volume);

        SLOG << "SkinnedGeometry::adjustVolume: Using Skeleton vol "
             << std::endl;
    }
    else
    {
        Inherited::adjustVolume(volume                       );
        volume.transform       (_sfBindShapeMatrix.getValue());

        SLOG << "SkinnedGeometry::adjustVolume: Using Mesh vol "
             << std::endl;
    }
}

void SkinnedGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkinnedGeometry NI" << std::endl;
}

Action::ResultE
SkinnedGeometry::renderDebug(RenderAction *ract)
{
    const Skeleton::MFJointsType        *joints       =
        _sfSkeleton.getValue()->getMFJoints();
    const Skeleton::MFJointMatricesType *jointMats    =
        _sfSkeleton.getValue()->getMFJointMatrices();
    const Skeleton::MFParentJointsType  *parentJoints =
        _sfSkeleton.getValue()->getMFParentJoints();

    Real32 axisLen   = 1.f;
    UInt32 numJoints = joints->size();

    _debugDrawPos.resize(4 * numJoints);
    _debugDrawIdx.clear (             );

    for(UInt32 i = 0; i < numJoints; ++i)
    {
        (*jointMats)[i].mult(Pnt3f(0.f,  0.f,  0.f ), _debugDrawPos[4 * i + 0]);

        if((*parentJoints)[i] != NULL)
        {
            _debugDrawIdx.push_back(4 * i                                + 0);
            _debugDrawIdx.push_back(4 * (*parentJoints)[i]->getJointId() + 0);

            Vec3f vec = _debugDrawPos[4 * i                                + 0] -
                        _debugDrawPos[4 * (*parentJoints)[i]->getJointId() + 0];

            axisLen = 0.2f * vec.length();
        }
        else
        {
            axisLen = 1.f;
        }

        (*jointMats)[i].mult(Pnt3f(axisLen, 0.f,     0.f    ), _debugDrawPos[4 * i + 1]);
        (*jointMats)[i].mult(Pnt3f(0.f,     axisLen, 0.f    ), _debugDrawPos[4 * i + 2]);
        (*jointMats)[i].mult(Pnt3f(0.f,     0.f,     axisLen), _debugDrawPos[4 * i + 3]);

//         _debugDrawIdx.push_back(4 * i + 0);
//         _debugDrawIdx.push_back(4 * i + 1);
//         _debugDrawIdx.push_back(4 * i + 0);
//         _debugDrawIdx.push_back(4 * i + 2);
//         _debugDrawIdx.push_back(4 * i + 0);
//         _debugDrawIdx.push_back(4 * i + 3);
    }

    Material::DrawFunctor  drawFunc = 
        boost::bind(&SkinnedGeometry::drawDebug, this, _1);
    PrimeMaterial         *primeMat = getDefaultUnlitMaterial();
    State                 *state    = primeMat->getState();
    
    ract->dropFunctor(drawFunc, state, primeMat->getSortKey());

    return Action::Continue;
}

Action::ResultE
SkinnedGeometry::drawDebug(DrawEnv *drawEnv)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &(_debugDrawPos.front())); 

    glDrawElements(GL_LINES, _debugDrawIdx.size(), GL_UNSIGNED_INT,
                   &(_debugDrawIdx.front())                        );

    glDisableClientState(GL_VERTEX_ARRAY);
}

Action::ResultE
SkinnedGeometry::renderHardware(RenderAction *ract)
{
    Action::ResultE                     res    = Action::Continue;
    Skeleton                           *skel   = getSkeleton  ();
    ShaderProgramChunkUnrecPtr          shCode = getShaderCode();
    ShaderProgramVariableChunkUnrecPtr  shData = getShaderData();

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
            "matBindShape", _sfBindShapeMatrix.getValue());
        shData->addUniformVariable(
            "matJoints", *(skel->getMFJointMatrices()));
    }
    else
    {
        shData->updateUniformVariable(
            "matJoints", *(skel->getMFJointMatrices()));
    }

    ract->pushState();

    ract->addOverride(ShaderProgramChunk        ::getStaticClassId(), shCode);
    ract->addOverride(ShaderProgramVariableChunk::getStaticClassId(), shData);

    res = Inherited::renderActionEnterHandler(ract);

    ract->popState();

    return res;
}

Action::ResultE
SkinnedGeometry::renderSoftware(RenderAction *ract)
{
    SWARNING << "SkinnedGeometry::renderSoftware: NIY"
             << std::endl;
}

OSG_END_NAMESPACE
