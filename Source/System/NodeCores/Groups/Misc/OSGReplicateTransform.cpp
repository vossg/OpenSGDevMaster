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

#include "OSGReplicateTransform.h"
#include "OSGVolume.h"
#include "OSGIntersectAction.h"

#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGReplicateTransformBase.cpp file.
// To modify it, please change the .fcd file (OSGReplicateTransform.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ReplicateTransform::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ReplicateTransform::intersectEnter));
        
        IntersectAction::registerLeaveDefault( 
            getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ReplicateTransform::intersectLeave));
       
        RenderAction::registerEnterDefault(
            ReplicateTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ReplicateTransform::renderEnter));

        RenderAction::registerLeaveDefault(
            ReplicateTransform::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ReplicateTransform::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ReplicateTransform::calcMatrix(const Matrix &mToWorld)
{
    Matrix prevValue = _invWorld;

    _invWorld.invertFrom(mToWorld);

    if(getTarget() != NULL)
    {
        _invWorld.mult(getTarget()->getToWorld());
    }

    if(_invWorld != prevValue)
    {
        invalidateVolume();
    }
}

void ReplicateTransform::accumulateMatrix(Matrix &result)
{
    result.mult(_invWorld);
}

void ReplicateTransform::adjustVolume(Volume &volume)
{
    volume.transform(_invWorld);
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

ActionBase::ResultE ReplicateTransform::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    calcMatrix(pAction->topMatrix());

    pAction->pushVisibility();

    pAction->pushMatrix(_invWorld);

    return Action::Continue;
}

ActionBase::ResultE ReplicateTransform::renderLeave(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

ActionBase::ResultE ReplicateTransform::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = _invWorld;

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

ActionBase::ResultE ReplicateTransform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = _invWorld;

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ReplicateTransform::ReplicateTransform(void) :
     Inherited(),
    _invWorld ()
{
    _invWorld.setIdentity();
}

ReplicateTransform::ReplicateTransform(const ReplicateTransform &source) :
     Inherited(source          ),
    _invWorld (source._invWorld)
{
}

ReplicateTransform::~ReplicateTransform(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ReplicateTransform::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    if(whichField & TargetFieldMask)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin, details);
}

void ReplicateTransform::dump(      UInt32    ,
                              const BitVector ) const
{
    SLOG << "Dump ReplicateTransform NI" << std::endl;
}

OSG_END_NAMESPACE
