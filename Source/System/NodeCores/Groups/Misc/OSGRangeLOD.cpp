/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"

//just for debug
#include <iostream>
//just for debug

#include "OSGRangeLOD.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGRangeLODBase.cpp file.
// To modify it, please change the .fcd file (OSGRangeLOD.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void RangeLOD::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void RangeLOD::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump RangeLOD NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

RangeLOD::RangeLOD(void) :
    Inherited()
{
}

RangeLOD::RangeLOD(const RangeLOD &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

RangeLOD::~RangeLOD(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void RangeLOD::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {

        RenderAction::registerEnterDefault(
            RangeLOD::getClassType(),
            reinterpret_cast<Action::Callback>(&RangeLOD::renderEnter));
    }
}

Action::ResultE RangeLOD::renderEnter(Action *action)
{
    RenderAction  *ra = dynamic_cast<RenderAction *>(action);

    Pnt3f eyepos;

    ra->getActivePartition()->getCameraToWorld().mult(eyepos, eyepos);

    Pnt3f objpos;

    ra->topMatrix().mult(getCenter(), objpos);

    Real32 dist = eyepos.dist(objpos);

    if(dist > getSwitchOut() && dist < getSwitchIn())
    {
        return Action::Continue;
    }
    else
    {
        return Action::Skip;
    }
}
