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

#include "OSGWindowDrawTask.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::WindowDrawTask
    \ingroup GrpSystemRenderingBackend
 */


WindowDrawTask::WindowDrawTask(TaskType eType) :
     Inherited            (     ),
    _eTaskType            (eType),
    _pBarrier             (NULL ),
    _oInitFunc            (     ),
    _bCreatePrivateContext(false),
    _bReinitExtFunctions  (false)
{
    switch(_eTaskType)
    {
        case WaitAtBarrier:
#ifdef OSG_SWAP_BARRIER
        case Swap:
#endif
        {
            _pBarrier = Barrier::get(NULL, false);
            _pBarrier->setNumWaitFor(2);
        }
        break;

        default:
            break;
    }
}

WindowDrawTask::~WindowDrawTask(void)
{
    _pBarrier = NULL;
}

void WindowDrawTask::execute(DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT(pWindow != NULL);

    switch(_eTaskType)
    {
        case Init:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "Init\n");
            fflush(stderr);
#endif
            if(_bCreatePrivateContext == true)
                pWindow->init();

            pWindow->doActivate();
            pWindow->doFrameInit(_bReinitExtFunctions);
            pWindow->setupGL ();

            if(_oInitFunc)
            {
                _oInitFunc();
            }

            if(pWindow->getKeepContextActive() == false)
                pWindow->doDeactivate();
        }
        break;

        case Activate:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "Activate\n");
            fflush(stderr);
#endif
            if(pWindow->getKeepContextActive() == false)
                pWindow->doActivate();
        }
        break;

        case FrameInit:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "FrameInit\n");
            fflush(stderr);
#endif

            if(pWindow->getKeepContextActive() == false)
                pWindow->doActivate();

            pWindow->doFrameInit();
        }
        break;

        case FrameExit:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "FrameExit\n");
            fflush(stderr);
#endif
            pWindow->doFrameExit();

            if(pWindow->getKeepContextActive() == false)
                pWindow->doDeactivate();
        }
        break;

        case WaitAtBarrier:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "WaitAtBarrier\n");
            fflush(stderr);
#endif
            OSG_ASSERT(_pBarrier != NULL);
            _pBarrier->enter();
        }
        break;

        case Swap:
        {           
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "Swap\n");
            fflush(stderr);
#endif
            pWindow->doSwap();

#ifdef OSG_SWAP_BARRIER
            OSG_ASSERT(_pBarrier != NULL);

            _pBarrier->enter();
#endif
        }
        break;

        case EndThread:
        {
            pWindow->doDeactivate();
            pWindow->_pDrawThread->endRunning();
        }
        break;

        default:
            break;
    }
}

void WindowDrawTask::waitForBarrier(void)
{
    OSG_ASSERT((_eTaskType == WaitAtBarrier) ||
               (_eTaskType == Swap         )  );
    OSG_ASSERT(_pBarrier  != NULL         );

    _pBarrier->enter();
}

void WindowDrawTask::setInitFunc(GLInitFunctor oFunc)
{
    _oInitFunc = oFunc;
}

void WindowDrawTask::setReinitExtFunctions(bool bVal)
{
    _bReinitExtFunctions = bVal;
}

void WindowDrawTask::setCreatePrivateContext(bool bVal)
{
    _bCreatePrivateContext = bVal;
}

void WindowDrawTask::dump(UInt32 uiIndent)
{
    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "WindowDrawTask : ");

    switch(_eTaskType)
    {
        case Init:
        {
            fprintf(stderr, "Init\n");
        }
        break;

        case Activate:
        {
            fprintf(stderr, "Activate\n");
        }
        break;

        case FrameInit:
        {
            fprintf(stderr, "FrameInit\n");
        }
        break;

        case FrameExit:
        {
            fprintf(stderr, "FrameExit\n");
        }
        break;

        case WaitAtBarrier:
        {
            fprintf(stderr, "WaitAtBarrier\n");
        }
        break;

        case Swap:
        {           
            fprintf(stderr, "Swap\n");
        }
        break;

        case EndThread:
        {
            fprintf(stderr, "EndThread\n");
        }
        break;

        default:
        {
            fprintf(stderr, "Unknown\n");
        }
        break;
    }

}




ViewportDrawTask::ViewportDrawTask(Viewport *pPort, TaskType eType) :
     Inherited(     ),
    _eTaskType(eType),
    _pPort    (pPort)
{
}

ViewportDrawTask::~ViewportDrawTask(void)
{
    _pPort = NULL;
}

void ViewportDrawTask::execute(DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT( pWindow != NULL);
    OSG_ASSERT(_pPort   != NULL);

    switch(_eTaskType)
    {
        case Foregrounds:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "Swap\n");
            fflush(stderr);
#endif
            _pPort->renderForegrounds(pWindow);
        }
        break;

        default:
            break;
    }
}

void ViewportDrawTask::dump(UInt32 uiIndent)
{
    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "ViewportDrawTask : ");

    switch(_eTaskType)
    {
        case Foregrounds:
        {
            fprintf(stderr, "Foregrounds\n");
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
