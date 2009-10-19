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

Skeleton::Skeleton(void) :
    Inherited()
{
}

Skeleton::Skeleton(const Skeleton &source) :
    Inherited(source)
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
    }

    Inherited::changed(whichField, origin, details);
}

/*! RenderAction enter callback.

  \note This callback is not registered with the RenderAction, but instead
   must be called by an object that uses this Skeleton (e.g. SkinnedGeometry).
 */
Action::ResultE
Skeleton::renderEnter(RenderAction *ract)
{
    // joints are relative to the skeletons coordinate system
    // which is applied as part of OpenGL's model matrix.
    // Therefore we need to cancel the current model matrix
    // before visiting the joint hierarchies

    Matrixr matModelInv;
    matModelInv.invertFrom(ract->topMatrix());

    ract->pushMatrix (matModelInv);
    ract->useNodeList(           );

    MFRootsType::const_iterator rIt  = _mfRoots.begin();
    MFRootsType::const_iterator rEnd = _mfRoots.end  ();

    for(; rIt != rEnd; ++rIt)
    {
        SLOG << "Skeleton::renderEnter: Adding root [" << *rIt << "]" << std::endl;

        ract->addNode(*rIt);
    }

    return Action::Continue;
}

/*! RenderAction leave callback.

  \note This callback is not registered with the RenderAction, but instead
   must be called by an object that uses this Skeleton (e.g. SkinnedGeometry).
 */
Action::ResultE
Skeleton::renderLeave(RenderAction *ract)
{
    ract->popMatrix();

    return Action::Continue;
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

    SkeletonJoint *joint       = dynamic_cast<SkeletonJoint *>(node->getCore());
    SkeletonJoint *parentJoint = jointStack->empty() ? NULL : jointStack->back();

    if(joint == NULL)
        return Action::Continue;

    Int16 jointId = joint->getJointId();

    SLOG << "Skeleton::findJointsEnter: [" << joint << "][" << jointId
         << "] parent [" << parentJoint << "][" << (parentJoint != NULL ? parentJoint->getJointId() : -1)
         << "]" << std::endl;

    if(joint->getSkeleton() != NULL)
    {
        SWARNING << "Skeleton::findJointsEnter: Found SkeletonJoint ["
                 << joint << "][" << jointId << "] already owned by a "
                 << "Skeleton. Ignoring joint." << std::endl;
        return Action::Continue;
    }

    if(jointId == SkeletonJoint::INVALID_JOINT_ID)
    {
        SWARNING << "Skeleton::findJointsEnter: SkeletonJoint has "
                 << "invalid joint id. Ignoring joint." << std::endl;
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

    jointStack->pop_back();

    return Action::Continue;
}

OSG_END_NAMESPACE
