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

#include "OSGCSMDrawer.h"
#include "OSGCSMWindow.h"
#include "OSGRenderAction.h"

#include "OSGOSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 CSMWindow::_extMultiSample       = Window::invalidExtensionID;
UInt32 CSMWindow::_extNVMultiSampleHint = Window::invalidExtensionID;
UInt32 CSMWindow::FuncIdSampleCoverage  = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extMultiSample        = 
            Window::registerExtension("GL_ARB_multisample");

        _extNVMultiSampleHint  = 
            Window::registerExtension("GL_NV_multisample_filter_hint");

        FuncIdSampleCoverage   = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glSampleCoverageARB",
            _extMultiSample);
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMWindow::CSMWindow(void) :
    Inherited   (    ),
    _pWindow    (NULL),
    _bFirstFrame(true)
{
}

CSMWindow::CSMWindow(const CSMWindow &source) :
    Inherited   (source),
    _pWindow    (NULL  ),
    _bFirstFrame(true  )
{
}

CSMWindow::~CSMWindow(void)
{
}

void CSMWindow::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pWindow = NULL;
}

void CSMWindow::reshape(Int32 w, 
                        Int32 h)
{
    if(_pWindow != NULL)
    {
        _pWindow->resize(w, h);
    }
}

void CSMWindow::mouse(Int32 iButton, 
                      Int32 iState,
                      Int32 iModifier,
                      Int32 x,       
                      Int32 y)
{
    editMouseData().setData( iButton, 
                             iState,  
                             0x0001 << iModifier,
                             x, 
                             y,
                            _pWindow);

    commitChanges();
}

void CSMWindow::motion(Int32 x, 
                       Int32 y)
{
    editMouseData().setData(x, y, _pWindow);
}


CSMDrawer *CSMWindow::getParent(void) const
{
    return dynamic_cast<CSMDrawer *>(_sfParent.getValue());
}

FieldContainer *CSMWindow::findNamedComponent(const Char8 *szName) const
{
    return NULL;
}


/*----------------------------- class specific ----------------------------*/

void CSMWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CSMWindow NI" << std::endl;
}

bool CSMWindow::init(void)
{
    bool returnValue = true;

    MFUnrecCSMViewportPtr::const_iterator vIt  = getMFViewports()->begin();
    MFUnrecCSMViewportPtr::const_iterator vEnd = getMFViewports()->end  ();

    while(vIt != vEnd)
    {
        returnValue = (*vIt)->init();

        if(returnValue == false)
        {
            break;
        }

        ++vIt;
    }

    if(_pWindow != NULL && returnValue == true)
    {
        vIt  = getMFViewports()->begin();
        vEnd = getMFViewports()->end  ();

        while(vIt != vEnd)
        {
            _pWindow->addPort((*vIt)->getPort());

            ++vIt;
        }
    }

    if(_mfIgnoreExtensions.size() == 1 && _mfIgnoreExtensions[0] == "ALL")
    {
        const char *gl_extensions = 
            reinterpret_cast<const char*> (glGetString(GL_EXTENSIONS));

        fprintf(stderr, "Ignoring %s\n", gl_extensions);

        OSG::Window::ignoreExtensions(gl_extensions);
    }
    else if(_mfIgnoreExtensions.size() > 0)
    {
        MFString::const_iterator sIt  = _mfIgnoreExtensions.begin();
        MFString::const_iterator sEnd = _mfIgnoreExtensions.end  ();

        for(; sIt != sEnd; ++sIt)
        {
            OSG::Window::ignoreExtensions((*sIt).c_str());
        }
    }

    //OSGSceneFileType::the().writeContainer(_pWindow, "/tmp/window.osg");

    return returnValue;
}

void CSMWindow::render(RenderAction *pAction)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window* pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    OSG::Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->activate ();
    pThreadLocalWin->frameInit();

    if(_sfRequestSamples.getValue() > 0)
    {
        if(_sfEnableFSAA.getValue() == true)
        {
            glEnable(GL_MULTISAMPLE_ARB);

            if(pThreadLocalWin->hasExtension(_extNVMultiSampleHint) == true)
            {
                glHint(GL_MULTISAMPLE_FILTER_HINT_NV,
                       _sfFsaaHint.getValue());
            }
        }
        else
        {
            glDisable(GL_MULTISAMPLE_ARB);
        }
    }

    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->renderAllViewports(pAction);

        pAction->setFrustumCulling(true);
    }
    else
    {
#if 0
        if(_bSceneWireframe == true || _bSceneDoubleSided == true)
        {
            pThreadLocalWin->activate();

            if(_bSceneWireframe == true)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            
            if(_bSceneDoubleSided == true)
                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
        }
#endif        

        pThreadLocalWin->renderAllViewports(pAction);

#if 0
        if(_bSceneWireframe == true || _bSceneDoubleSided == true)
        {
            pThreadLocalWin->activate();

            if(_bSceneWireframe == true)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            if(_bSceneDoubleSided == true)
                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
        }
#endif
    }

    if(_sfRequestSamples.getValue() > 0)
    {
        if(_sfEnableFSAA.getValue() == true)
        {
            glDisable(GL_MULTISAMPLE_ARB);
        }
    }    
    
    pThreadLocalWin->swap     ();
    pThreadLocalWin->frameExit();
}

void CSMWindow::frameRenderActivate(RenderAction *pAction)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->activate          (       );
    pThreadLocalWin->frameInit         (       );

    if(_sfRequestSamples.getValue() > 0)
    {
        if(_sfEnableFSAA.getValue() == true)
        {
            glEnable(GL_MULTISAMPLE_ARB);

            if(pThreadLocalWin->hasExtension(_extNVMultiSampleHint) == true)
            {
                glHint(GL_MULTISAMPLE_FILTER_HINT_NV,
                       _sfFsaaHint.getValue());
            }
        }
        else
        {
            glDisable(GL_MULTISAMPLE_ARB);
        }
    }

    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->renderAllViewports(pAction);

        pAction->setFrustumCulling(true);
    }
    else
    {
        pThreadLocalWin->renderAllViewports(pAction);
    }

    if(_sfRequestSamples.getValue() > 0)
    {
        if(_sfEnableFSAA.getValue() == true)
        {
            glDisable(GL_MULTISAMPLE_ARB);
        }
    }

    pThreadLocalWin->deactivate        (       );
}

void CSMWindow::frameSwapActivate(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->activate  ();
    pThreadLocalWin->swap      ();
    pThreadLocalWin->frameExit ();
    pThreadLocalWin->deactivate();
}

void CSMWindow::frameExit(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->activate  ();
    pThreadLocalWin->frameExit ();
    pThreadLocalWin->deactivate();
}

void CSMWindow::activate(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->activate();
}

void CSMWindow::frameRender(RenderAction *pAction)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

//    fprintf(stderr, "%p %p\n", pThreadLocalWin, _pWindow.get());

    pThreadLocalWin->frameInit();

    if(_sfRequestSamples.getValue() > 0)
    {
        if(_sfEnableFSAA.getValue() == true)
        {
            glEnable(GL_MULTISAMPLE_ARB);

            if(pThreadLocalWin->hasExtension(_extNVMultiSampleHint) == true)
            {
                glHint(GL_MULTISAMPLE_FILTER_HINT_NV,
                       _sfFsaaHint.getValue());
            }
        }
        else
        {
            glDisable(GL_MULTISAMPLE_ARB);
        }
    }

    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->renderAllViewports(pAction);

        pAction->setFrustumCulling(true);
    }
    else
    {
        pThreadLocalWin->renderAllViewports(pAction);
    }

    if(_sfRequestSamples.getValue() > 0)
    {
        if(_sfEnableFSAA.getValue() == true)
        {
            glDisable(GL_MULTISAMPLE_ARB);
        }
    }
}

void CSMWindow::frameSwap(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->swap     ();
    pThreadLocalWin->frameExit();
}

void CSMWindow::deactivate(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    pThreadLocalWin->deactivate();
}

void CSMWindow::shutdown(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        convertToCurrentAspect<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    Inherited::resolveLinks();
    pThreadLocalWin->resolveLinks();
}

OSG_END_NAMESPACE
