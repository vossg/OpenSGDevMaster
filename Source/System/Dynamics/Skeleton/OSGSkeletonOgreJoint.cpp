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

#include "OSGSkeletonOgreJoint.h"
#include "OSGAnimBindAction.h"
#include "OSGRenderAction.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonOgreJointBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeletonOgreJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonOgreJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        AnimBindAction::registerEnterDefault(
            SkeletonOgreJoint::getClassType(),
            reinterpret_cast<Action::Callback>(&SkeletonOgreJoint::animBindEnter));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkeletonOgreJoint::SkeletonOgreJoint(void) :
    Inherited      (),
    _accumTranslate(0.f, 0.f, 0.f),
    _accumScale    (1.f, 1.f, 1.f),
    _accumRotate   ()
{
}

SkeletonOgreJoint::SkeletonOgreJoint(const SkeletonOgreJoint &source) :
    Inherited      (source),
    _accumTranslate(source._accumTranslate),
    _accumScale    (source._accumScale),
    _accumRotate   (source._accumRotate)
{
}

SkeletonOgreJoint::~SkeletonOgreJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkeletonOgreJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(((TranslateFieldMask        |
         RotateFieldMask           |
         ScaleFieldMask            |
         OffsetTranslateFieldMask  |
         OffsetScaleFieldMask      |
         OffsetRotateFieldMask     |
         InvBindTranslateFieldMask |
         InvBindScaleFieldMask     |
         InvBindRotateFieldMask     ) & whichField) != 0x0000)
    {
        invalidateVolume();

        if(_sfSkeleton.getValue() != NULL)
            _sfSkeleton.getValue()->editSFJointsChanged();
    }

    Inherited::changed(whichField, origin, details);
}

Action::ResultE
SkeletonOgreJoint::jointUpdateEnter(JointTraverser *jt)
{
    Action::ResultE  res  = Action::Continue;
    Skeleton        *skel = getSkeleton();

#ifdef OSG_DEBUG
    if(_sfJointId.getValue() == INVALID_JOINT_ID)
    {
        SWARNING << "SkeletonOgreJoint::jointUpdateEnter: "
                 << "Joint has invalid jointId. Ignoring." << std::endl;
        return res;
    }
    
    if(skel == NULL)
    {
        SWARNING << "SkeletonOgreJoint::jointUpdateEnter: "
                 << "Joint has no skeleton. Ignoring." << std::endl;
        return res;
    }
#endif

    Int16                          jointId     = getJointId();
    Skeleton::MFJointMatricesType *jointMats   =
        skel->editMFJointMatrices();
    SkeletonOgreJoint             *parentJoint =
        dynamic_cast<SkeletonOgreJoint *>(skel->getParentJoints(jointId));

    if(parentJoint != NULL)
    {
        _accumRotate = parentJoint->_accumRotate;
        _accumRotate.mult(getRotate      ());
        _accumRotate.mult(getOffsetRotate());

        _accumScale = parentJoint->_accumScale;
        _accumScale[0] *= getScale()[0] * getOffsetScale()[0];
        _accumScale[1] *= getScale()[1] * getOffsetScale()[1];
        _accumScale[2] *= getScale()[2] * getOffsetScale()[2];

        _accumTranslate = getTranslate() + getOffsetTranslate();
        _accumTranslate[0] *= parentJoint->_accumScale[0];
        _accumTranslate[1] *= parentJoint->_accumScale[1];
        _accumTranslate[2] *= parentJoint->_accumScale[2];

        parentJoint->_accumRotate.multVec(_accumTranslate, _accumTranslate);
        _accumTranslate += parentJoint->_accumTranslate;   
    }
    else
    {
        _accumRotate    = getRotate();
        _accumRotate.mult(getOffsetRotate());

        _accumScale     = getScale();
        _accumScale[0] *= getOffsetScale()[0];
        _accumScale[1] *= getOffsetScale()[1];
        _accumScale[2] *= getOffsetScale()[2];

        _accumTranslate = getTranslate() + getOffsetTranslate();
    }

    Quaternion jointRotate   (_accumRotate   );
    Vec3f      jointTranslate(_accumTranslate);
    Vec3f      jointScale    (_accumScale    );

    if(skel->getUseInvBindMatrix() == true)
    {
        jointRotate.mult(getInvBindRotate());
        jointScale[0]  *= getInvBindScale()[0];
        jointScale[1]  *= getInvBindScale()[1];
        jointScale[2]  *= getInvBindScale()[2];

        jointTranslate[0] = jointScale[0] * getInvBindTranslate()[0];
        jointTranslate[1] = jointScale[1] * getInvBindTranslate()[1];
        jointTranslate[2] = jointScale[2] * getInvBindTranslate()[2];

        jointRotate.multVec(jointTranslate, jointTranslate);

        jointTranslate += _accumTranslate;
    }

    Matrix matJoint;
    matJoint.setTransform(jointTranslate, jointRotate, jointScale);

    (*jointMats)[jointId] = matJoint;

    return res;
}

Action::ResultE
SkeletonOgreJoint::jointUpdateLeave(JointTraverser *jt)
{
    return Action::Continue;
}

Action::ResultE
SkeletonOgreJoint::animBindEnter(Action *action)
{
    Action::ResultE  res     = Action::Continue;
    AnimBindAction  *bindAct =
        boost::polymorphic_downcast<AnimBindAction *>(action);

    bindAct->bindFields(this);

    return res;
}

void
SkeletonOgreJoint::accumulateMatrix(Matrix &result)
{
    // XXX TODO
}

void
SkeletonOgreJoint::adjustVolume(Volume &volume)
{
    volume.setValid();
}

void SkeletonOgreJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonOgreJoint NI" << std::endl;
}

OSG_END_NAMESPACE
