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

#include "OSGDistanceLOD.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGDistanceLODBase.cpp file.
// To modify it, please change the .fcd file (OSGDistanceLOD.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void DistanceLOD::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void DistanceLOD::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump DistanceLOD NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DistanceLOD::DistanceLOD(void) :
    Inherited()
{
}

DistanceLOD::DistanceLOD(const DistanceLOD &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DistanceLOD::~DistanceLOD(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void DistanceLOD::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            DistanceLOD::getClassType(),
            reinterpret_cast<Action::Callback>(&DistanceLOD::renderEnter));
    }
}

Action::ResultE DistanceLOD::renderEnter(Action *action)
{
    action->useNodeList();

    Int32 numLevels = action->getNNodes();

    if(numLevels == 0)
        return Action::Continue;

    RenderAction  *ra        = dynamic_cast<RenderAction *>(action);
    Int32          index     = 0;

    const MFReal32 *range = getMFRange();

    Int32 numRanges = range->size32();

    if(numRanges == 0 || numLevels == 1)
    {
        index = 0;
    }
    else
    {
        Pnt3f eyepos;

        ra->getActivePartition()->getCameraToWorld().mult(eyepos, eyepos);

        Pnt3f objpos;

        ra->topMatrix().mult(getCenter(), objpos);

        Real32 dist = eyepos.dist(objpos);

        if(numRanges >= numLevels && numLevels > 1)
            numRanges = numLevels - 1;

        if(dist >= (*range)[numRanges - 1])
        {
            index = numRanges;
        }
        else
        {
            for(index = 0; index < numRanges; ++index)
            {
                if(dist < (*range)[index])
                    break;
            }
        }
    }

    Node *nodePtr = action->getNode(index);

    if(ra->isVisible(nodePtr))
    {
        ra->addNode(nodePtr);
    }

    return Action::Continue;
}
