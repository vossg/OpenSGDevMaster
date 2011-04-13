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

#include "OSGBaseSkeletonJoint.h"
#include "OSGTransform.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBaseSkeletonJointBase.cpp file.
// To modify it, please change the .fcd file (OSGBaseSkeletonJoint.fcd) and
// regenerate the base file.

BaseSkeletonJoint::JointTraverser::JointTraverser(Skeleton *skel) :
    _skel     (skel),
    _topMatrix(),
    _matStack ()
{
    _matStack.reserve(skel->getMFJointMatrices()->size());
}

void BaseSkeletonJoint::JointTraverser::pushMatrix(const Matrix &m)
{
    _matStack.push_back(_topMatrix);

    _topMatrix.mult(m);
}

void BaseSkeletonJoint::JointTraverser::popMatrix(void)
{
    OSG_ASSERT(_matStack.empty() == false);

    _topMatrix = _matStack.back();
    _matStack.pop_back();
}

const Matrix &BaseSkeletonJoint::JointTraverser::topMatrix(void) const
{
    return _topMatrix;
}

Action::ResultE BaseSkeletonJoint::JointTraverser::enter(Node * const node)
{
    Action::ResultE  retVal = Action::Continue;
    NodeCore        *core   = node->getCore();

    if(core->getType().isDerivedFrom(Transform::getClassType()))
    {
        Transform *xform = boost::polymorphic_downcast<Transform *>(core);

        pushMatrix(xform->getMatrix());
    }
    else if(core->getType().isDerivedFrom(BaseSkeletonJoint::getClassType()))
    {
        BaseSkeletonJoint *joint =
            boost::polymorphic_downcast<BaseSkeletonJoint *>(core);

        retVal = joint->jointUpdateEnter(this);
    }

    return retVal;
}

Action::ResultE BaseSkeletonJoint::JointTraverser::leave(Node * const    node,
                                                         Action::ResultE res  )
{
    Action::ResultE  retVal = Action::Continue;
    NodeCore        *core   = node->getCore();

    if(core->getType().isDerivedFrom(Transform::getClassType()))
    {
        popMatrix();
    }
    else if(core->getType().isDerivedFrom(BaseSkeletonJoint::getClassType()))
    {
        BaseSkeletonJoint *joint =
            boost::polymorphic_downcast<BaseSkeletonJoint *>(core);

        retVal = joint->jointUpdateLeave(this);
    }

    return retVal;
}

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Int16 BaseSkeletonJoint::INVALID_JOINT_ID = -1;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BaseSkeletonJoint::initMethod(InitPhase ePhase)
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

BaseSkeletonJoint::BaseSkeletonJoint(void) :
    Inherited()
{
}

BaseSkeletonJoint::BaseSkeletonJoint(const BaseSkeletonJoint &source) :
    Inherited(source)
{
}

BaseSkeletonJoint::~BaseSkeletonJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BaseSkeletonJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BaseSkeletonJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BaseSkeletonJoint NI" << std::endl;
}

OSG_END_NAMESPACE
