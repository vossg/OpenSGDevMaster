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
#include "OSGSkeletonJoint.h"

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
    : Inherited    (    )
    , _rootsChanged(true)
{
}

Skeleton::Skeleton(const Skeleton &source)
    : Inherited    (source)
    , _rootsChanged(true  )
{
}

Skeleton::~Skeleton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void
Skeleton::pushToRoots(Node * const value)
{
    Inherited::pushToRoots(value);

    if(value != NULL)
    {
        value->addChangedFunctor(
            boost::bind(&Skeleton::rootsChanged, this, _1, _2),
            "Skeleton::rootsChanged"                           );
    }
}

void
Skeleton::assignRoots(const MFUnrecNodePtr &value)
{
    Inherited::assignRoots(value);

    MFRootsType::iterator rIt  = _mfRoots.begin();
    MFRootsType::iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
    {
        if((*rIt)->hasChangedFunctor(
               boost::bind(&Skeleton::rootsChanged, this, _1, _2)) == false)
        {
            (*rIt)->addChangedFunctor(
                boost::bind(&Skeleton::rootsChanged, this, _1, _2),
                "Skeleton::rootsChanged"                           );
        }
    }
}

void
Skeleton::removeFromRoots(UInt32 uiIndex)
{
    Node *value = _mfRoots[uiIndex];

    if(value->hasChangedFunctor(
           boost::bind(&Skeleton::rootsChanged, this, _1, _2)) == true)
    {
        value->subChangedFunctor(
            boost::bind(&Skeleton::rootsChanged, this, _1, _2));
    }

    Inherited::removeFromRoots(uiIndex);
}

void
Skeleton::removeObjFromRoots(Node * const value)
{
    if(value->hasChangedFunctor(
           boost::bind(&Skeleton::rootsChanged, this, _1, _2)) == true)
    {
        value->subChangedFunctor(
            boost::bind(&Skeleton::rootsChanged, this, _1, _2));
    }

    Inherited::removeObjFromRoots(value);
}

void
Skeleton::clearRoots(void)
{
    MFRootsType::iterator rIt  = _mfRoots.begin();
    MFRootsType::iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
    {
        if((*rIt)->hasChangedFunctor(
               boost::bind(&Skeleton::rootsChanged, this, _1, _2)) == true)
        {
            (*rIt)->subChangedFunctor(
                boost::bind(&Skeleton::rootsChanged, this, _1, _2));
        }
    }

    Inherited::clearRoots();
}

void Skeleton::changed(ConstFieldMaskArg whichField,
                       UInt32            origin,
                       BitVector         details)
{
    if((RootsFieldMask & whichField) != 0)
    {
        updateJoints();
    }

    Inherited::changed(whichField, origin, details);
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
Skeleton::rootsChanged(FieldContainer *root, BitVector whichField)
{
    if((whichField & Node::VolumeFieldMask) != 0x0000)
    {
        _rootsChanged = true;
    }
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

void
Skeleton::updateJointMatrices(void)
{
    MFRootsType::const_iterator rIt  = _mfRoots.begin();
    MFRootsType::const_iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
        (*rIt)->updateVolume();

    if(_rootsChanged == false)
        return;

    SLOG << "Skeleton::updateJointMatrices" << std::endl;

    OSG_ASSERT(_mfJoints.size() == _mfJointMatrices.size());
    editMField(JointMatricesFieldId, _mfJointMatrices);

    if(_sfCalcNormalMatrices.getValue() == true)
    {
        OSG_ASSERT(_mfJoints.size() == _mfJointNormalMatrices.size());
        editMField(JointNormalMatricesFieldId, _mfJointNormalMatrices);
    }

    MFJointsType::const_iterator jIt  = _mfJoints.begin();
    MFJointsType::const_iterator jEnd = _mfJoints.end  ();

    for(UInt32 i = 0; jIt != jEnd; ++jIt, ++i)
    {
        _mfJointMatrices[i] = (*jIt)->getWorldMatrix();

        if(_sfUseInvBindMatrix.getValue() == true)
            _mfJointMatrices[i].mult((*jIt)->getInvBindMatrix());

        if(_sfCalcNormalMatrices.getValue() == true)
        {
            _mfJointNormalMatrices[i].invertFrom(_mfJointMatrices[i]);
            _mfJointNormalMatrices[i].transpose (                   );
        }
    }

    _rootsChanged = false;
}

Action::ResultE
Skeleton::findJointsEnter(JointStack *jointStack, Node *node)
{
    if(node == NULL || node->getCore() == NULL)
        return Action::Continue;

    SkeletonJoint *joint       = dynamic_cast<SkeletonJoint *>(node->getCore());
    SkeletonJoint *parentJoint = jointStack->empty() ? NULL : jointStack->back();

    if(joint == NULL)
        return Action::Continue;

    Int16 jointId = joint->getJointId();

    if(jointId == SkeletonJoint::INVALID_JOINT_ID)
    {
        SWARNING << "Skeleton::findJointsEnter: SkeletonJoint has "
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

    if(_sfCalcNormalMatrices.getValue() == true)
        mfJointNMats->resize(newSize, Matrix::identity());

    if((*mfJoints)[jointId] != NULL)
    {
        SWARNING << "Skeleton::findJointsEnter: JointId [" << jointId
                 << "] is already used. Ignoring joint." << std::endl;
        return Action::Continue;
    }

    (*mfJoints      )[jointId] = joint;
    (*mfParentJoints)[jointId] = parentJoint;

    jointStack->push_back(joint);

    return Action::Continue;
}

Action::ResultE
Skeleton::findJointsLeave(JointStack *jointStack, Node *node)
{
    if(node == NULL || node->getCore() == NULL)
        return Action::Continue;

    SkeletonJoint *joint = dynamic_cast<SkeletonJoint *>(node->getCore());

    if(joint == NULL)
        return Action::Continue;

    if(joint->getJointId() == SkeletonJoint::INVALID_JOINT_ID)
        return Action::Continue;

    jointStack->pop_back();

    return Action::Continue;
}

OSG_END_NAMESPACE
