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

    _sfSkeleton.getValue()->renderEnter(ract);
    _sfSkeleton.getValue()->renderLeave(ract);

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

    if(res != Action::Continue)
        return res;

    if(testFlag(SG_FLAG_DEBUG) == true)
    {
        res = renderDebug(ract);
    }
    else if(testFlag(SG_FLAG_HARDWARE) == true)
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
    // XXX TODO correct volume calculation

    volume.setValid   ();
    volume.setInfinite();
}

void SkinnedGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkinnedGeometry NI" << std::endl;
}

Action::ResultE
SkinnedGeometry::renderDebug(RenderAction *ract)
{
    SLOG << "SkinnedGeometry::renderDebug" << std::endl;

    const Skeleton::MFJointsType        *joints       =
        _sfSkeleton.getValue()->getMFJoints();
    const Skeleton::MFJointMatricesType *jointMats    =
        _sfSkeleton.getValue()->getMFJointMatrices();
    const Skeleton::MFParentJointsType  *parentJoints =
        _sfSkeleton.getValue()->getMFParentJoints();

    UInt32        numJoints(joints->size());
    PositionStore positions(4 * numJoints );
    IndexStore    indices;

    for(UInt32 i = 0; i < numJoints; ++i)
    {
        (*jointMats)[i].mult(Pnt3f(0.f,  0.f,  0.f ), positions[4 * i + 0]);
        (*jointMats)[i].mult(Pnt3f(0.5f, 0.f,  0.f ), positions[4 * i + 1]);
        (*jointMats)[i].mult(Pnt3f(0.f,  0.5f, 0.f ), positions[4 * i + 2]);
        (*jointMats)[i].mult(Pnt3f(0.f,  0.f,  0.5f), positions[4 * i + 3]);

        SLOG << "positions[" << i << "] " << positions[4 * i + 0] << std::endl;

        if((*parentJoints)[i] != NULL)
        {
            indices.push_back(4 * i                                + 0);
            indices.push_back(4 * (*parentJoints)[i]->getJointId() + 0);

            SLOG << "indices[" << (indices.size() - 2) << "] " << indices[indices.size() - 2] << "\n";
            SLOG << "indices[" << (indices.size() - 1) << "] " << indices[indices.size() - 1]
                 << std::endl;
        }

        indices.push_back(4 * i + 0);
        indices.push_back(4 * i + 1);
        indices.push_back(4 * i + 0);
        indices.push_back(4 * i + 2);
        indices.push_back(4 * i + 0);
        indices.push_back(4 * i + 3);
    }

    Material::DrawFunctor  drawFunc = 
        boost::bind(&SkinnedGeometry::drawDebug,
                    this, positions, indices, _1);
    PrimeMaterial         *primeMat = getDefaultUnlitMaterial();
    State                 *state    = primeMat->getState();
    
    ract->dropFunctor(drawFunc, state, primeMat->getSortKey());
}

Action::ResultE
SkinnedGeometry::drawDebug(
    const PositionStore &positions,
    const IndexStore    &indices,   DrawEnv *drawEnv)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &(positions.front())); 

    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT,
                   &(indices.front())                        );

    glDisableClientState(GL_VERTEX_ARRAY);
}

Action::ResultE
SkinnedGeometry::renderHardware(RenderAction *ract)
{
    SWARNING << "SkinnedGeometry::renderHardware: NIY"
             << std::endl;
}

Action::ResultE
SkinnedGeometry::renderSoftware(RenderAction *ract)
{
    SWARNING << "SkinnedGeometry::renderSoftware: NIY"
             << std::endl;
}

OSG_END_NAMESPACE
