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

#include "OSGRenderActionTask.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::WindowDrawTask
 */

RenderActionTask::RenderActionTask(UInt32 uiType) :
    Inherited(uiType),
    _pBarrier(NULL  )
{
    switch(_uiTypeTask)
    {
        case HandleGLFinish:
        {
            _pBarrier = Barrier::get(NULL, false);
            _pBarrier->setNumWaitFor(2);
        }
        break;

        default:
            break;
    }
}

RenderActionTask::~RenderActionTask(void)
{
    _pBarrier = NULL;
}

void RenderActionTask::execute(HardwareContext *pContext, DrawEnv *pEnv)
{
#ifdef OSG_DEBUG
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT(pWindow != NULL);
#endif

    switch(_uiTypeTask)
    {

        case HandleGLFinish:
        {           
#ifdef OSG_DUMP_RENDERTASK
            fprintf(stderr, "HandleGLFinish\n");
            fflush(stderr);
#endif
            glFinish();

            OSG_ASSERT(_pBarrier != NULL);

            _pBarrier->enter();
        }
        break;

        case HandleGLFinishNoWait:
        {           
#ifdef OSG_DUMP_RENDERTASK
            fprintf(stderr, "HandleGLFinishNoWait\n");
            fflush(stderr);
#endif
            glFinish();
        }
        break;

        default:
            break;
    }
}

void RenderActionTask::waitForBarrier(void)
{
    OSG_ASSERT(_uiTypeTask == HandleGLFinish);
    OSG_ASSERT(_pBarrier   != NULL          );

    _pBarrier->enter();
}

void RenderActionTask::dump(UInt32 uiIndent)
{
    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "RenderActionTask : ");

    switch(_uiTypeTask)
    {
        case HandleGLFinish:
        {           
            fprintf(stderr, "HandleGLFinish\n");
        }
        break;

        case HandleGLFinishNoWait:
        {           
            fprintf(stderr, "HandleGLFinishNoWait\n");
        }
        break;

        default:
        {
            fprintf(stderr, "Unknown\n");
        }
        break;
    }

}

OSG_END_NAMESPACE
