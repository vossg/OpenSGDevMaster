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

#ifdef OSG_WITH_CUDA
#include <cuda_runtime_api.h>
#include <cuda_gl_interop.h>
#endif

OSG_BEGIN_NAMESPACE

/*! \class OSG::WindowDrawTask
    \ingroup GrpSystemRenderingBackend
 */


WindowDrawTask::WindowDrawTask(UInt32 uiType) :
     Inherited            (uiType),
    _pBarrier             (NULL  ),
    _oInitFunc            (      ),
    _bCreatePrivateContext(false ),
    _bReinitExtFunctions  (false)
{
    switch(_uiTypeTask)
    {
        case WaitAtBarrier:
        case DeactivateAndWait:
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

void WindowDrawTask::execute(HardwareContext *pContext, DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT(pWindow != NULL);

    switch(_uiTypeTask)
    {
        case Init:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "Init\n");
            fflush(stderr);
#endif
            if(_bCreatePrivateContext == true)
                pWindow->init();

            pWindow->doActivate   ();
            pWindow->doFrameInit  (_bReinitExtFunctions);
            pWindow->setupGL      ();
            pWindow->setOpenGLInit();

            if(_oInitFunc)
            {
                _oInitFunc();
            }
        }
        break;

        case Activate:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "Activate\n");
            fflush(stderr);
#endif
            pWindow->doActivate();
        }
        break;

        case FrameInit:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "FrameInit\n");
            fflush(stderr);
#endif

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

            commitChangesAndClear();
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

        case DeactivateAndWait:
        {
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "DeactivateAndWait\n");
            fflush(stderr);
#endif
            pWindow->doDeactivate();

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
#ifdef OSG_DUMP_WINTASK
            fprintf(stderr, "EndThread\n");
            fflush(stderr);
#endif
            pWindow->doFrameExit();
            
#ifdef OSG_WITH_CUDA
            if(0x0000 != (pWindow->getInitState() & 
                          HardwareContext::CudaInitialized))
            {
                cudaThreadExit();
            }
#endif
            pWindow->doDeactivate();
            pWindow->_pContextThread->endRunning();
        }
        break;

        default:
            break;
    }
}

void WindowDrawTask::waitForBarrier(void)
{
    OSG_ASSERT((_uiTypeTask == WaitAtBarrier    ) ||
               (_uiTypeTask == Swap             ) ||
               (_uiTypeTask == DeactivateAndWait)  );

    OSG_ASSERT(_pBarrier    != NULL                );

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

    switch(_uiTypeTask)
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

        case DeactivateAndWait:
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




ViewportDrawTask::ViewportDrawTask(Viewport *pPort, UInt32 uiType) :
     Inherited(uiType),
    _pPort    (pPort )
{
}

ViewportDrawTask::~ViewportDrawTask(void)
{
    _pPort = NULL;
}

void ViewportDrawTask::execute(HardwareContext *pContext, DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT( pWindow != NULL);
    OSG_ASSERT(_pPort   != NULL);

    switch(_uiTypeTask)
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

    switch(_uiTypeTask)
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


CallbackDrawTask::CallbackDrawTask(UInt32 uiType) :
     Inherited(uiType),
    _fCallback(      )
{
}

CallbackDrawTask::CallbackDrawTask(const CallbackFunctor &fCallback, 
                                         UInt32            uiType  ) :
     Inherited (uiType   ),
    _fCallback (fCallback)
{
}

CallbackDrawTask::~CallbackDrawTask(void)
{
}

void CallbackDrawTask::execute(HardwareContext *pContext, DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    OSG_ASSERT( pWindow != NULL);
    OSG_ASSERT(_fCallback      );

    switch(_uiTypeTask)
    {
        case Callback:
        {
            Inherited::setupContext(pWindow);

            _fCallback(pContext, pEnv);

            Inherited::finalizeContext(pWindow);
            
            if(_bBarrierActive == true)
                _pBarrier->enter();
        }
        break;

        default:
            break;
    }
}

void CallbackDrawTask::setCallback(const CallbackFunctor &fCallback)
{
    _fCallback = fCallback;
}


void CallbackDrawTask::dump(UInt32 uiIndent)
{
    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "CallbackDrawTask : ");

    switch(_uiTypeTask)
    {
        case Callback:
        {
            fprintf(stderr, "Callback, barrier active : %d\n",
                    UInt32(_bBarrierActive));
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
