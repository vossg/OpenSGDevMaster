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

#include "OSGMoveManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MoveManipulator
 * The MoveHandle is used for moving objects. It consist of three axis which
 * can be picked and translated and one center box to translate freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MoveManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MoveManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MoveManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MoveManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&MoveManipulator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MoveManipulator::MoveManipulator(void) :
    Inherited()
{
}

MoveManipulator::MoveManipulator(const MoveManipulator &source) :
    Inherited(source)
{
}

MoveManipulator::~MoveManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MoveManipulator::changed(ConstFieldMaskArg whichField,
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MoveManipulator::dump(      UInt32    uiIndent,
                           const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr MoveManipulator::makeHandleGeo()
{
    return makeCone(0.75f, 0.1f, 12, true, true);
}

void MoveManipulator::doMovement(      Transform    *t,
                                 const Int32         coord,
                                 const Real32        value,
                                 const Vec3f        &translation,
                                 const Quaternion   &rotation,
                                 const Vec3f        &scaleFactor,
                                 const Quaternion   &scaleOrientation)
{
    Vec3f trans(0.0f, 0.0f, 0.0f);
    trans[coord] = value;

    Matrix ma, mb, mc, md, me;

    ma.setTranslate( -translation        );
    mb.setRotate   (  rotation.inverse() );
    mc.setTransform(  trans              );
    md.setRotate   (  rotation           );
    me.setTranslate(  translation        );
    t->editMatrix().multLeft(ma);
    t->editMatrix().multLeft(mb);
    t->editMatrix().multLeft(mc);
    t->editMatrix().multLeft(md);
    t->editMatrix().multLeft(me);
}
