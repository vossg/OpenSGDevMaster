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

void Skeleton::addJoint(SkeletonJoint *joint, SkeletonJoint *jointParent)
{
    if(joint->getJointId() == SkeletonJoint::AUTO_ID_END)
        joint->setJointId(_mfJoints.size());

    editMField(JointsFieldMask,        _mfJoints       );
    editMField(JointMatricesFieldMask, _mfJointMatrices);

    _mfJoints       .resize(osgMax<UInt32>(joint          ->getJointId() + 1,
                                           _mfJoints       .size      () + 1),
                            NULL                                             );
    _mfJointMatrices.resize(osgMax<UInt32>(joint          ->getJointId() + 1,
                                          _mfJointMatrices .size      () + 1),
                            Matrix::identity()                               );

    OSG_ASSERT(_mfJoints[joint->getJointId()] == NULL);

    _mfJoints       [joint->getJointId()] = joint;
    _mfJointMatrices[joint->getJointId()].setIdentity();

    if(jointParent != NULL)
        jointParent->addChildInternal(joint);
}

SkeletonJoint *Skeleton::addNewJoint(SkeletonJoint *jointParent, Int16 jointId)
{
    SkeletonJointUnrecPtr newJoint = SkeletonJoint::create();
    newJoint->setJointId(jointId);

    addJoint(newJoint, jointParent);

    return newJoint;
}

void Skeleton::subJoint(SkeletonJoint *joint)
{
    OSG_ASSERT(joint                != NULL);
    OSG_ASSERT(joint->getSkeleton() == this);

    SkeletonJoint *jointParent = joint->getParent();
    
    if(jointParent != NULL)
        jointParent->subChildInternal(joint);

    editMField(JointsFieldMask,        _mfJoints       );
    editMField(JointMatricesFieldMask, _mfJointMatrices);

    _mfJointMatrices[joint->getJointId()].setIdentity();
    _mfJoints       [joint->getJointId()] = NULL;
}

void Skeleton::subJoint(Int16 jointId)
{
    OSG_ASSERT(jointId < _mfJoints.size());

    SkeletonJoint *joint       = _mfJoints[jointId];
    SkeletonJoint *jointParent = joint->getParent();

    if(jointParent != NULL)
        jointParent->subChildInternal(joint);
  
    editMField(JointsFieldMask,        _mfJoints       );
    editMField(JointMatricesFieldMask, _mfJointMatrices);
  
    _mfJointMatrices[jointId].setIdentity();
    _mfJoints       [jointId] = NULL;
}

void Skeleton::fill(DrawableStatsAttachment *pStat)
{
    MFMeshesType::const_iterator meshIt  = _mfMeshes.begin();
    MFMeshesType::const_iterator meshEnd = _mfMeshes.end  ();

    for(; meshIt != meshEnd; ++meshIt)
    {
        (*meshIt)->fill(pStat);
    }
}


void Skeleton::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if((whichField & MeshesFieldMask) != 0x0000)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin, details);
}

void Skeleton::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Skeleton NI" << std::endl;
}

void Skeleton::adjustVolume(Volume &volume)
{
    MFMeshesType::const_iterator meshIt  = _mfMeshes.begin();
    MFMeshesType::const_iterator meshEnd = _mfMeshes.end  ();

    for(; meshIt != meshEnd; ++meshIt)
    {
        (*meshIt)->adjustVolume(volume);
    }
}

/*! Updates the joint matrices for all joints attached to the skeleton.
    Returns true if any joint matrix was recomputed, false otherwise.
 */
bool Skeleton::updateJointMatrices(void)
{
    bool                  retVal  = false;

    MFJointsType::iterator jointIt  = _mfJoints.begin();
    MFJointsType::iterator jointEnd = _mfJoints.end  ();

    for(; jointIt != jointEnd; ++jointIt)
    {
        if((*jointIt)->getNeedRecalc() == true)
        {
            retVal = true;
            updateJointMatrix(*jointIt);
        }
    }

    return retVal;
}

/*! Updates a single joint matrix for the given joint. If necessary
    this will also update the matrix of the parent joint (recursively).
 */
void Skeleton::updateJointMatrix(SkeletonJoint *joint)
{
    editMField(JointMatricesFieldMask, _mfJointMatrices);

    SkeletonJoint *jointParent = joint->getParent();
    Int16          jointId     = joint->getJointId();

    if(jointParent != NULL)
    { 
        if(jointParent->getNeedRecalc() == true)
            updateJointMatrix(jointParent);

        Int16  jointParentId = jointParent->getJointId();

        _mfJointMatrices[jointId] = _mfJointMatrices[jointParentId];
        _mfJointMatrices[jointId].mult(joint->getMatrix       ());
        _mfJointMatrices[jointId].mult(joint->getInvBindMatrix());
    }
    else
    {
        _mfJointMatrices[jointId] =    joint->getMatrix       ();
        _mfJointMatrices[jointId].mult(joint->getInvBindMatrix());
    }

    joint->setNeedRecalc(false);
}


OSG_END_NAMESPACE
