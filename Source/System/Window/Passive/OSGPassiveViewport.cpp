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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGForeground.h"
#include "OSGPassiveViewport.h"

#include "OSGRenderActionBase.h"
#include "OSGPassiveWindow.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::PassiveViewport
    \ingroup GrpSystemWindowViewports

A PassiveViewport is a basic Viewport for integration into other OpenGL
programs. See \ref PageSystemWindowViewports for a description.

*/

/*----------------------- constructors & destructors ----------------------*/

PassiveViewport::PassiveViewport(void) :
     Inherited      (    ),
    _pDeactivateTask(NULL)
{
}

PassiveViewport::PassiveViewport(const PassiveViewport &source) :
     Inherited      (source),
    _pDeactivateTask(NULL  )
{
}

PassiveViewport::~PassiveViewport(void)
{
    _pDeactivateTask = NULL;
}

/*----------------------------- class specific ----------------------------*/

void PassiveViewport::initMethod (InitPhase ePhase)
{
}

void PassiveViewport::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PassiveViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PassiveViewport NI" << std::endl;
}

void PassiveViewport::render(RenderActionBase *action)
{
#if 1 // Have to check GV
    if ( getCamera() == NULL )
    {
        SWARNING << "Viewport::render: no camera!" << std::endl;
        return;
    }
    if ( getBackground() == NULL )
    {
        SWARNING << "Viewport::render: no background!" << std::endl;
        return;
    }
    if ( getRoot() == NULL )
    {
        SWARNING << "Viewport::render: no root!" << std::endl;
        return;
    }
    if ( action->getWindow() == NULL)
    {
        SWARNING << "Viewport::render: no window!" << std::endl;
        return;
    }

    Window *pWin  = action->getWindow();

    if((pWin->getDrawMode() & Window::PartitionDrawMask) == 
                                                 Window::ParallelPartitionDraw)
    {
        if(_pDeactivateTask == NULL)
        {
            _pDeactivateTask = 
                new WindowDrawTask(WindowDrawTask::DeactivateAndWait);
        }

        pWin->_pContextThread->queueTask(_pDeactivateTask);

        _pDeactivateTask->waitForBarrier();

        pWin->doActivate();
    }

    GLint vp[4];

    glGetIntegerv(GL_VIEWPORT, vp);

    setLeft      (Real32(vp[0])           );
    setBottom    (Real32(vp[1])           );
    setRight     (Real32(vp[0] + vp[2] - 1));
    setTop       (Real32(vp[1] + vp[3] - 1)); 

    if((pWin->getDrawMode() & Window::PartitionDrawMask) == 
                                                 Window::ParallelPartitionDraw)
    {
        pWin->doDeactivate();

        pWin->_pContextThread->queueTask(pWin->_pActivateTask);
    }
#endif

    Inherited::render(action);
}

bool PassiveViewport::isPassive(void)
{
    return true;
}
