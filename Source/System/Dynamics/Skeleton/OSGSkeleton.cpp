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

#include "OSGSkeleton.h"
#include "OSGAction.h"
#include "OSGBaseSkeletonJoint.h"
#include "OSGIntersectAction.h"

// debug only
#include "OSGFieldContainerUtils.h"

#include <boost/bind.hpp>
#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeleton.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Skeleton::initMethod(InitPhase ePhase)
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

Skeleton::Skeleton(void)
    : Inherited          ()
    , _jointMatricesValid(false)
{
}

Skeleton::Skeleton(const Skeleton &source)
    : Inherited          (source)
    , _jointMatricesValid(false)
{
}

Skeleton::~Skeleton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Skeleton::changed(ConstFieldMaskArg whichField,
                       UInt32            origin,
                       BitVector         details)
{
    if((RootsFieldMask & whichField) != 0)
    {
        updateJoints();
        _jointMatricesValid = false;
    }

    if(((UseInvBindMatrixFieldMask |
         JointsChangedFieldMask     ) & whichField) != 0)
    {
        _jointMatricesValid = false;
    }  

    Inherited::changed(whichField, origin, details);
}

Action::ResultE
Skeleton::renderEnter(Action *action, NodeCore *parent)
{
    if(_jointMatricesValid == false)
    {
        BaseSkeletonJoint::JointTraverser jt(this);

        TraverseEnterFunctor enterFunc =
            boost::bind(&BaseSkeletonJoint::JointTraverser::enter, &jt, _1);
        TraverseLeaveFunctor leaveFunc =
            boost::bind(&BaseSkeletonJoint::JointTraverser::leave, &jt, _1, _2);

        MFRootsType::const_iterator rIt  = _mfRoots.begin();
        MFRootsType::const_iterator rEnd = _mfRoots.end  ();

        for(; rIt != rEnd; ++rIt)
            traverse(*rIt, enterFunc, leaveFunc);

        _jointMatricesValid = true;
    }

    return Action::Continue;
}

Action::ResultE
Skeleton::renderLeave(Action *action, NodeCore *parent)
{
    return Action::Continue;
}

Action::ResultE
Skeleton::intersectEnter(Action *action, NodeCore *parent)
{
    if(_jointMatricesValid == false)
    {
        BaseSkeletonJoint::JointTraverser jt(this);

        TraverseEnterFunctor enterFunc =
            boost::bind(&BaseSkeletonJoint::JointTraverser::enter, &jt, _1);
        TraverseLeaveFunctor leaveFunc =
            boost::bind(&BaseSkeletonJoint::JointTraverser::leave, &jt, _1, _2);

        MFRootsType::const_iterator rIt  = _mfRoots.begin();
        MFRootsType::const_iterator rEnd = _mfRoots.end  ();

        for(; rIt != rEnd; ++rIt)
            traverse(*rIt, enterFunc, leaveFunc);

        _jointMatricesValid = true;
    }

    return Action::Continue;
}

Action::ResultE
Skeleton::animBindEnter(Action *action, NodeCore *parent)
{
    action->useNodeList(true);

    MFRootsType::const_iterator rIt  = _mfRoots.begin();
    MFRootsType::const_iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
        action->addNode(*rIt);

    this->recurseFrom(action, parent);

    return Action::Continue;
}

void
Skeleton::adjustVolume(Volume &volume)
{
    MFRootsType::const_iterator rIt  = _mfRoots.begin();
    MFRootsType::const_iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
    {
        (*rIt)->updateVolume();
        volume.extendBy((*rIt)->getVolume());
    }
}

void Skeleton::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Skeleton NI" << std::endl;
}

void
Skeleton::updateJoints(void)
{
    editMFJoints             ()->clear();
    editMFParentJoints       ()->clear();
    editMFJointMatrices      ()->clear();
    editMFJointNormalMatrices()->clear();

    JointStack jointStack;

    TraverseEnterFunctor enterFunc =
        boost::bind(&Skeleton::findJointsEnter, this, &jointStack, _1);
    TraverseLeaveFunctor leaveFunc =
        boost::bind(&Skeleton::findJointsLeave, this, &jointStack, _1);

    MFRootsType::const_iterator rIt  = _mfRoots.begin();
    MFRootsType::const_iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
        traverse(*rIt, enterFunc, leaveFunc);
}

Action::ResultE
Skeleton::findJointsEnter(JointStack *jointStack, Node *node)
{
    if(node == NULL || node->getCore() == NULL)
        return Action::Continue;

    BaseSkeletonJoint *joint       = dynamic_cast<BaseSkeletonJoint *>(node->getCore());
    BaseSkeletonJoint *parentJoint = jointStack->empty() ? NULL : jointStack->back();

    if(joint == NULL)
        return Action::Continue;

    Int16 jointId = joint->getJointId();

    if(jointId == BaseSkeletonJoint::INVALID_JOINT_ID)
    {
        SWARNING << "Skeleton::findJointsEnter: Joint has "
                 << "invalid joint id. Ignoring joint." << std::endl;
        return Action::Continue;
    }

    if(joint->getSkeleton() != NULL)
    {
        if(joint->getSkeleton() != this)
        {
            SWARNING << "Skeleton::findJointsEnter: Found SkeletonJoint ["
                     << joint << "][" << jointId << "] already owned by a "
                     << "Skeleton. Ignoring joint." << std::endl;
        }

        // joint already owned by this skeleton - ok, the skeleton may be
        // shared between multiple SkinnedGeometry and already scanned for
        // joints
        jointStack->push_back(joint);

        return Action::Continue;
    }

    MFJointsType              *mfJoints       = editMFJoints             ();
    MFParentJointsType        *mfParentJoints = editMFParentJoints       ();
    MFJointMatricesType       *mfJointMat     = editMFJointMatrices      ();
    MFJointNormalMatricesType *mfJointNMats   = editMFJointNormalMatrices();
    UInt32                     newSize        =
        osgMax<UInt32>(mfJoints->size(), jointId + 1);

    mfJoints      ->resize(newSize, NULL              );
    mfParentJoints->resize(newSize, NULL              );
    mfJointMat    ->resize(newSize, Matrix::identity());
    mfJointNMats  ->resize(newSize, Matrix::identity());

    if((*mfJoints)[jointId] != NULL)
    {
        SWARNING << "Skeleton::findJointsEnter: JointId [" << jointId
                 << "] is already used. Ignoring joint." << std::endl;
        return Action::Continue;
    }

    mfJoints      ->replace(jointId, joint      );
    mfParentJoints->replace(jointId, parentJoint);

    jointStack->push_back(joint);

    return Action::Continue;
}

Action::ResultE
Skeleton::findJointsLeave(JointStack *jointStack, Node *node)
{
    if(node == NULL || node->getCore() == NULL)
        return Action::Continue;

    BaseSkeletonJoint *joint = dynamic_cast<BaseSkeletonJoint *>(node->getCore());

    if(joint == NULL)
        return Action::Continue;

    if(joint->getJointId() == BaseSkeletonJoint::INVALID_JOINT_ID)
        return Action::Continue;

    jointStack->pop_back();

    return Action::Continue;
}

OSG_END_NAMESPACE
