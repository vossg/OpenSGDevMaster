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

#include "OSGSkeletonJoint.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonJointBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeletonJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonJoint::initMethod(InitPhase ePhase)
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

SkeletonJoint::SkeletonJoint(void) :
    Inherited()
{
}

SkeletonJoint::SkeletonJoint(const SkeletonJoint &source) :
    Inherited(source)
{
}

SkeletonJoint::~SkeletonJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkeletonJoint::addChild(SkeletonJoint *joint)
{
    if(_sfSkeleton.getValue() != NULL)
    {
        _sfSkeleton.getValue()->addJoint(joint, this);
    }
    else
    {
        SWARNING << "SkeletonJoint::addChild: Joint 'this' ["
                 << this << "] has no Skeleton. Ignored." << std::endl;
    }
}

void SkeletonJoint::subChild(SkeletonJoint *joint)
{
    if(_sfSkeleton.getValue() != NULL)
    {
        _sfSkeleton.getValue()->subJoint(joint);
    }
    else
    {
        SWARNING << "SkeletonJoint::subChild: Joint 'this' ["
                 << this << "] has no Skeleton. Ignored." << std::endl;
    }
}

void SkeletonJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(whichField & (MatrixFieldMask        | 
                     InvBindMatrixFieldMask  ) != 0)
    {
        markNeedRecalc();
    }

    Inherited::changed(whichField, origin, details);
}

void SkeletonJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonJoint NI" << std::endl;
}


void SkeletonJoint::addChildInternal(SkeletonJoint *joint)
{
    editMField(ChildrenFieldMask, _mfChildren);
    _mfChildren.push_back(joint);
}

void SkeletonJoint::subChildInternal(SkeletonJoint *joint)
{
    MFChildrenType::iterator jointIt = _mfChildren.find(joint);

    if(jointIt != _mfChildren.end())
    {
        editMField(ChildrenFieldMask, _mfChildren);
        _mfChildren.erase(jointIt);
    }
}

void SkeletonJoint::markNeedRecalc(void)
{
    if(_needRecalc == false)
    {
        _needRecalc = true;

        MFChildrenType::iterator childIt  = _mfChildren.begin();
        MFChildrenType::iterator childEnd = _mfChildren.end  ();

        for(; childIt != childEnd; ++childIt)
            (*childIt)->markNeedRecalc();
    }
}

OSG_END_NAMESPACE
