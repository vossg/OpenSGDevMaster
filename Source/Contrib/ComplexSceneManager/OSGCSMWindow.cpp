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

#include "OSGConfig.h"

#include "OSGCSMDrawer.h"
#include "OSGCSMWindow.h"
#include "OSGRenderAction.h"

#include "OSGOSGSceneFileType.h"
#include "OSGNameAttachment.h"
#include "OSGComplexSceneManager.h"
#include "OSGStatisticsForeground.h"

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
    Inherited    (     ),
    _pWindow     ( NULL),
    _pStatFG     ( NULL),
    _bFirstFrame ( true),
    _oTouchBlob  (     ),
    _uiTouchMode (    0),
    _bMouseActive(false)
{
}

CSMWindow::CSMWindow(const CSMWindow &source) :
    Inherited    (source),
    _pWindow     (NULL  ),
    _pStatFG     (NULL  ),
    _bFirstFrame (true  ),
    _oTouchBlob  (      ),
    _uiTouchMode (     0),
    _bMouseActive(false )
{
}

CSMWindow::~CSMWindow(void)
{
}

void CSMWindow::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pWindow = NULL;
    _pStatFG = NULL;
}

void CSMWindow::reshape(Int32 w, 
                        Int32 h)
{
    if(_pWindow != NULL)
    {
        this->setSize(Vec2f(w, h));

        _pWindow->resize(w, h);
    }
}

void CSMWindow::mouse(Int32 iButton, 
                      Int32 iState,
                      Int32 iModifier,
                      Int32 x,       
                      Int32 y)
{
    if(UInt32(iState) == MouseData::ButtonDown)
    {
        _bMouseActive = true;
    }
    else
    {
        _bMouseActive = false;
    }

    if(_sfMouseAsMTouch.getValue() == true)
    {
        if(UInt32(iState) == MouseData::ButtonDown)
        {
            editMTouchData().addCursor(0, x, y, MTouchData::WindowAbs);
        }
        else
        {
            editMTouchData().removeCursor(0);

            if(_uiTouchMode == 1)
            {
                editMTouchData().removeCursor(1);
            }
        }

        commitChanges();

        _sfMTouchData.getValue().clear();

        _uiTouchMode = 0;
    }
    else
    {
        editMouseData().setData( iButton, 
                                 iState,  
                                 iModifier,
                                 x, 
                                 y,
                                _pWindow);

        commitChanges();
    }
}

void CSMWindow::motion(Int32 x, 
                       Int32 y,
                       Int32 iModifier)
{
    if(_bMouseActive == false)
        return;

    if(_sfMouseAsMTouch.getValue() == true)
    {
        if(_uiTouchMode == 0)
        {
            if(0x0000 != (iModifier & MouseData::CtrlActive))
            {
                _uiTouchMode = 1;

                editMTouchData().updateCursor(0, 
                                              _oTouchBlob._vPosition[0], 
                                              _oTouchBlob._vPosition[1], 
                                              _oTouchBlob._uiCoordSys  );

                editMTouchData().updateCursor(1, x, y, MTouchData::WindowAbs);
            }
            else
            {
                editMTouchData().updateCursor(0, x, y, MTouchData::WindowAbs);

                _oTouchBlob._vPosition.setValues(x, y, 0);
                _oTouchBlob._uiCoordSys = MTouchData::WindowAbs;
            }
        }
        else
        {
            if(0x0000 != (iModifier & MouseData::CtrlActive))
            {
                editMTouchData().updateCursor(0, 
                                              _oTouchBlob._vPosition[0], 
                                              _oTouchBlob._vPosition[1], 
                                              _oTouchBlob._uiCoordSys  );

                editMTouchData().updateCursor(1, x, y, MTouchData::WindowAbs);
            }
            else
            {
                _uiTouchMode = 0;

                editMTouchData().updateCursor(0, x, y, MTouchData::WindowAbs);
                editMTouchData().removeCursor(1);
                                            
                _oTouchBlob._vPosition.setValues(x, y, 0);
                _oTouchBlob._uiCoordSys = MTouchData::WindowAbs;
            }
        }

        commitChanges();

        _sfMTouchData.getValue().clear();
    }
    else
    {
        editMouseData().setData(x, y, _pWindow);
    }
}

void CSMWindow::addMTouchCursor(Int32  iCursorId,
                                Int32  x,
                                Int32  y,
                                UInt32 uiCoordSys)
{
    editMTouchData().addCursor(iCursorId, 
                               x, 
                               y, 
                               uiCoordSys);
}

void CSMWindow::updateMTouchCursor(Int32  iCursorId,
                                   Int32  x,
                                   Int32  y,
                                   UInt32 uiCoordSys)
{
    editMTouchData().updateCursor(iCursorId, 
                                  x, 
                                  y, 
                                  uiCoordSys);
}

void CSMWindow::removeMTouchCursor(Int32 iCursorId)
{
    editMTouchData().removeCursor(iCursorId);
}

void CSMWindow::commitMTouchCursors(void)
{
    commitChanges();

    _sfMTouchData.getValue().clear();
}

CSMDrawer *CSMWindow::getParent(void) const
{
    return dynamic_cast<CSMDrawer *>(_sfParent.getValue());
}

void CSMWindow::queueTask(DrawTask *pTask)
{
    if(_pWindow != NULL)
    {
        _pWindow->queueTask(pTask);
    }
}

FieldContainer *CSMWindow::findNamedComponent(const Char8 *szName)
{
    if(_sfRenderOptions.getValue() != NULL)
    {
        const Char8 *szTmpName = OSG::getName(_sfRenderOptions.getValue());

        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return _sfRenderOptions.getValue();
        }
    }

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

Vec2f CSMWindow::translateScreenCoordinatesRel(Real32 rX,
                                               Real32 rY)
{
    Vec2f returnValue(0.f, 0.f);

    return returnValue;
}

Vec2i CSMWindow::translateGlobalCoordinatesRel(Real32 rX,
                                               Real32 rY)
{
    Vec2i returnValue(0, 0);

    return returnValue;
}

Vec2i CSMWindow::translateGlobalCoordinatesAbs(Int32  iX,
                                               Int32  iY)
{
    Vec2i returnValue(0, 0);

    return returnValue;
}

Vec2f CSMWindow::translateToScreenCoordinatesAbs(Real32 rX,
                                                 Real32 rY)
{
    Vec2f returnValue(0.f, 0.f);

    return returnValue;
}

bool CSMWindow::init(void)
{
    bool returnValue = true;

    MFUnrecCSMViewportPtr::const_iterator vIt  = getMFViewports()->begin();
    MFUnrecCSMViewportPtr::const_iterator vEnd = getMFViewports()->end  ();

    while(vIt != vEnd)
    {
        returnValue = (*vIt)->init(this);

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

        for(; vIt != vEnd; ++vIt)
        {
            CSMViewport::ViewportStoreConstIt pIt  = (*vIt)->beginViewports();
            CSMViewport::ViewportStoreConstIt pEnd = (*vIt)->endViewports  ();

            for(; pIt != pEnd; ++pIt)
            {
                _pWindow->addPort((*pIt));
            }
        }

        fprintf(stderr, "foo %p %d\n",
                ComplexSceneManager::the()->getDrawManager(),
                UInt32(ComplexSceneManager::the()->
                           getDrawManager()->getParallel()));

#ifndef __APPLE__
        UInt32 uiDrawMode = this->getPartitionDrawMode();
#else
        UInt32 uiDrawMode = Window::SequentialPartitionDraw;

        FWARNING(("Detected apple, only sequential draw mode available\n"));
#endif

        if(ComplexSceneManager::the()->getDrawManager()->getParallel() == true)
        {
            uiDrawMode |= Window::ParallelDrawer;
        }
        else
        {
            uiDrawMode |= Window::StdDrawer;
        }

        _pWindow->setRenderOptions    (this->getRenderOptions());
        _pWindow->setPartitionDrawMode(uiDrawMode              );
        _pWindow->setDrawerType       (uiDrawMode              );

        _pWindow->setIgnoreAllExtensions(this->getIgnoreAllExtensions());

        MFString::const_iterator ieIt  = _mfIgnoreExtensions.begin();
        MFString::const_iterator ieEnd = _mfIgnoreExtensions.end  ();

        for(; ieIt != ieEnd; ++ieIt)
        {
            Window::ignoreExtensions(ieIt->c_str());
        }
    }
    
//    OSGSceneFileType::the().writeContainer(_pWindow, "/tmp/window.osg");

    if(this->getDumpContainer() == true)
    {
        FieldContainerFactory::the()->dump();
    }

    return returnValue;
}

void CSMWindow::render(RenderAction *pAction)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window               *pThreadLocalWin    = 
        Aspect::convertToCurrent<Window               *>(_pWindow.get());
    StatisticsForeground *pThreadLocalStatFG = 
        Aspect::convertToCurrent<StatisticsForeground *>(_pStatFG      );
#else
    Window               *pThreadLocalWin    = _pWindow;
    StatisticsForeground *pThreadLocalStatFG = _pStatFG;
#endif

    if(pThreadLocalWin == NULL)
        return;

    if(pThreadLocalStatFG != NULL)
    {
        if(pThreadLocalStatFG->getActive() == true)
        {
            pAction->setStatCollector(pThreadLocalStatFG->getCollector());
            pAction->setUseGLFinish  (true);
        }
        else
        {
            pAction->setStatCollector(NULL );
            pAction->setUseGLFinish  (false);
        }
    }

//    fprintf(stderr, "csmwin::render %p\n", pThreadLocalStatFG);

#if 0
    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->render(pAction);

        pAction->setFrustumCulling(true);
    }
    else
    {
        pThreadLocalWin->render(pAction);
    }
#else
    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->renderNoFinish(pAction);

        pAction->setFrustumCulling(true);
    }
    else
    {
        pThreadLocalWin->renderNoFinish(pAction);
    }

    pThreadLocalWin->frameFinish();
#endif
}

void CSMWindow::frameRenderNoFinish(RenderAction *pAction)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window               *pThreadLocalWin    = 
        Aspect::convertToCurrent<Window               *>(_pWindow.get());
    StatisticsForeground *pThreadLocalStatFG = 
        Aspect::convertToCurrent<StatisticsForeground *>(_pStatFG      );
#else
    Window               *pThreadLocalWin    = _pWindow;
    StatisticsForeground *pThreadLocalStatFG = _pStatFG;
#endif

    if(pThreadLocalWin == NULL)
        return;

    if(pThreadLocalStatFG != NULL)
    {
        if(pThreadLocalStatFG->getActive() == true)
        {
            pAction->setStatCollector(pThreadLocalStatFG->getCollector());
        }
        else
        {
            pAction->setStatCollector(NULL);
        }
    }

    if(_bFirstFrame == true)
    {
        _bFirstFrame = false;

        pAction->setFrustumCulling(false);

        pThreadLocalWin->renderNoFinish(pAction);

        pAction->setFrustumCulling(true);
    }
    else
    {
        pThreadLocalWin->renderNoFinish(pAction);
    }
}

void CSMWindow::frameFinish(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        Aspect::convertToCurrent<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    if(pThreadLocalWin == NULL)
        return;

    pThreadLocalWin->frameFinish();
}

void CSMWindow::frameExit(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        Aspect::convertToCurrent<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    if(pThreadLocalWin == NULL)
        return;

    pThreadLocalWin->runFrameExit();
}

void CSMWindow::shutdown(void)
{
#ifdef OSG_MT_CPTR_ASPECT
    Window *pThreadLocalWin = 
        Aspect::convertToCurrent<Window *>(_pWindow.get());
#else
    Window *pThreadLocalWin = _pWindow;
#endif

    Inherited::resolveLinks();

    if(pThreadLocalWin == NULL)
        return;

    pThreadLocalWin->resolveLinks();
}

void CSMWindow::postSync(void)
{
    if(_pWindow != NULL)
    {
        _pWindow->clearDrawTasks();
    }
}

bool CSMWindow::requestStereoVisual(void)
{
    bool returnValue = false;

    MFUnrecCSMViewportPtr::const_iterator vIt  = getMFViewports()->begin();
    MFUnrecCSMViewportPtr::const_iterator vEnd = getMFViewports()->end  ();

    for(; vIt != vEnd; ++vIt)
    {
        returnValue = (*vIt)->needsStereoVisual();

        if(returnValue == true)
        {
            break;
        }
    }

    return returnValue;
}

OSG_END_NAMESPACE
