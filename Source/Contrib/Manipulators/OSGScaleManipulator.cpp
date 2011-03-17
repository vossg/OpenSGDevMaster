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

#include "OSGScaleManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ScaleManipulator
 * The ScaleHandle is used for scaleing objects. It consist of three axis
 * which can be picked and scaled and one center box to scale freely in 3D.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScaleManipulator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ScaleManipulator::intersectEnter));

        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &ScaleManipulator::intersectLeave));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&ScaleManipulator::renderEnter));

        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&ScaleManipulator::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScaleManipulator::ScaleManipulator(void) :
    Inherited()
{
}

ScaleManipulator::ScaleManipulator(const ScaleManipulator &source) :
    Inherited(source)
{
}

ScaleManipulator::~ScaleManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScaleManipulator::changed(ConstFieldMaskArg whichField,
                               UInt32            origin,
                               BitVector         details   )
{
    Inherited::changed(whichField, origin, details);
}

void ScaleManipulator::dump(      UInt32    uiIndent,
                            const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

NodeTransitPtr ScaleManipulator::makeHandleGeo()
{
    return makeCylinder(0.75f, 0.1f, 12, true, true, true);
}

void ScaleManipulator::doMovement(      Transform    *t,
                                  const Int32         coord,
                                  const Real32        value,
                                  const Vec3f        &translation,
                                  const Quaternion   &rotation,
                                  const Vec3f        &scaleFactor,
                                  const Quaternion   &scaleOrientation)
{
    Vec3f scale(1.0f, 1.0f, 1.0f);

    if(getUniform() == true)
    {
        scale += Vec3f(value, value, value);
    }
    else
    {
        scale[coord] += value;
    }

    Matrix ma, mb, mc, md, me;

    ma.setTranslate(-translation       );
    mb.setRotate   ( rotation.inverse());
    mc.setScale    ( scale             );
    md.setRotate   ( rotation          );
    me.setTranslate( translation       );

    t->editMatrix().multLeft(ma);
    t->editMatrix().multLeft(mb);
    t->editMatrix().multLeft(mc);
    t->editMatrix().multLeft(md);
    t->editMatrix().multLeft(me);
}
