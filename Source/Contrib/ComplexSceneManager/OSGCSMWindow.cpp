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

#include "OSGDrawer.h"
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

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
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


Drawer *CSMWindow::getParent(void) const
{
    return dynamic_cast<Drawer *>(_sfParent.getValue());
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
    
    OSGSceneFileType::the().writeContainer(_pWindow, "/tmp/window.osg");

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

    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->render(pAction);

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

        pThreadLocalWin->render(pAction);

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
