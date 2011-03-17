/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEMANIPULATORSLIB

#include "OSGConfig.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

#include "OSGRotateManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::RotateManipulator
 * The MoveHandle is used for moving objects. It consist of three axis which
 * can be picked and translated and one center box to translate freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RotateManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &RotateManipulator::renderLeave));
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RotateManipulator::RotateManipulator(void) :
    Inherited()
{
}

RotateManipulator::RotateManipulator(const RotateManipulator &source) :
    Inherited(source)
{
}

RotateManipulator::~RotateManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RotateManipulator::changed(ConstFieldMaskArg whichField,
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void RotateManipulator::dump(      UInt32    uiIndent,
                             const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr RotateManipulator::makeHandleGeo()
{
    return makeSphere(2, 0.2f);
}

void RotateManipulator::doMovement(      Transform    *t,
                                   const Int32         coord,
                                   const Real32        value,
                                   const Vec3f        &translation,
                                   const Quaternion   &rotation,
                                   const Vec3f        &scaleFactor,
                                   const Quaternion   &scaleOrientation)
{
    Vec3f axis(0.0f, 0.0f, 0.0f);
    axis[coord] = 1.0;
    const Quaternion rot(axis, value);

    Matrix ma, mb, mc, md, me;

    ma.setTranslate(-translation        );
    mb.setRotate   ( rotation.inverse() );
    mc.setRotate   ( rot                );
    md.setRotate   ( rotation           );
    me.setTranslate( translation        );
    t->editMatrix().multLeft(ma);
    t->editMatrix().multLeft(mb);
    t->editMatrix().multLeft(mc);
    t->editMatrix().multLeft(md);
    t->editMatrix().multLeft(me);
}
