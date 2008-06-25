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
#include "OSGRenderAction.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Drawer::initMethod(InitPhase ePhase)
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

Drawer::Drawer(void) :
     Inherited      (     ),
    _pAction        (NULL ),
    _pDrawThread    (NULL ),
    _pSyncFromThread(NULL ),
    _pSyncBarrier   (NULL ),
    _pSwapBarrier   (NULL ),

    _uiSyncCount    (0    ),
    _uiSwapCount    (0    ),
    _bParallel      (false),
    _bRun           (false)
{
}

Drawer::Drawer(const Drawer &source) :
     Inherited      (source),
    _pAction        (NULL  ),
    _pDrawThread    (NULL  ),
    _pSyncFromThread(NULL ),
    _pSyncBarrier   (NULL  ),
    _pSwapBarrier   (NULL  ),

    _uiSyncCount    (0     ),
    _uiSwapCount    (0     ),
    _bParallel      (false ),
    _bRun           (false)
{
}

Drawer::~Drawer(void)
{
    delete _pAction;
}

void Drawer::setSyncFromThread(Thread *pThread)
{
    _pSyncFromThread = pThread;
}

void Drawer::setSyncBarrier(Barrier *pSyncBarrier)
{
    _pSyncBarrier = pSyncBarrier;
}

void Drawer::setSwapBarrier(Barrier *pSwapBarrier)
{
    _pSwapBarrier = pSwapBarrier;
}

void Drawer::setSyncCount(UInt32 uiSyncCount)
{
    _uiSyncCount = uiSyncCount;
}

void Drawer::setSwapCount(UInt32 uiSwapCount)
{
    _uiSwapCount = uiSwapCount;
}

void Drawer::setParallel(bool bParallel)
{
    _bParallel = bParallel;
}

/*----------------------------- class specific ----------------------------*/

void Drawer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Drawer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Drawer NI" << std::endl;
}

bool Drawer::init(void)
{
    bool returnValue = true;

    MFUnrecChildCSMWindowPtr::const_iterator wIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator wEnd = getMFWindows()->end  ();

    while(wIt != wEnd)
    {
        returnValue = (*wIt)->init();

        if(returnValue == false)
            break;

        ++wIt;
    };

    _pAction = RenderAction::create();

    if(_bParallel == true)
    {
        _pDrawThread  = DrawThread ::get(NULL);

        OSG_ASSERT(_pDrawThread     != NULL);
        OSG_ASSERT(_pSyncBarrier    != NULL);
        OSG_ASSERT(_pSyncFromThread != NULL);

        addRef(_pDrawThread );

        _pDrawThread->setDrawer(this);
        _pDrawThread->run(_sfAspect.getValue());
    }

//    _pAction->setFrustumCulling(false);

    return returnValue;
}

void Drawer::endDrawThread (void)
{
    if(_bParallel == true)
    {
        _pDrawThread->setRunning(false);
    }
}

void Drawer::shutdown(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->shutdown();

        ++winIt;
    }
}

void Drawer::joinDrawThread(void)
{
    if(_bParallel == true)
    {
        Thread::join(_pDrawThread);

        subRef(_pDrawThread);

        _pDrawThread = NULL;
    }
}

void Drawer::frame(Time oTime, UInt32 uiFrame)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->render(_pAction);
        
        ++winIt;
    }
}

FieldContainer *Drawer::findNamedComponent(const Char8 *szName) const
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = _mfWindows.begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = _mfWindows.end  ();

    const Char8               *szTmpName   = NULL;

    while(winIt != winEnd)
    {
        szTmpName = OSG::getName(*winIt);
            
        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return *winIt;
        }
        else
        {
/*
            FieldContainer *tmpVal = (*drawerIt)->findNamedComponent(szName);
                
            if(tmpVal != NULL)
                return tmpVal;
 */
        }
        
        ++winIt;
    }
    
    return NULL;
}


void Drawer::runParallel(void)
{
    fprintf(stderr, "Drawer run par\n");

    _bRun = true;

    for(UInt32 i = 0; i < 10; ++i)
    {
        _pSyncBarrier->enter(_uiSyncCount);

        _pSyncFromThread->getChangeList()->applyNoClear();

        _pSyncBarrier->enter(_uiSyncCount);

        Thread::getCurrentChangeList()->commitChangesAndClear();
    }

    if(_pSwapBarrier == NULL)
    {
        fprintf(stderr, "Running without swap lock\n");
        fflush (stderr);

        if(_mfWindows.size() == 1)
        {
            fprintf(stderr, "Running with one windw\n");
            fflush (stderr);

            this->activate();

            while(_bRun == true)
            {
                _pSyncBarrier->enter(_uiSyncCount);

                _pSyncFromThread->getChangeList()->applyNoClear();

                _pSyncBarrier->enter(_uiSyncCount);
                
                Thread::getCurrentChangeList()->commitChangesAndClear();

                if(_bRun == false)
                {
                    //this->deactivate();
                    break;
                }

                this->frameRender(            );
                this->frameSwap  (            );
            }
        }
        else
        {
            fprintf(stderr, "Running with n-windws\n");
            fflush (stderr);

            while(_bRun == true)
            {
                _pSyncBarrier->enter               (_uiSyncCount);

                _pSyncFromThread->getChangeList()->applyNoClear();

                _pSyncBarrier->enter               (_uiSyncCount);

                Thread::getCurrentChangeList()->commitChangesAndClear();

                if(_bRun == false)
                    break;

                this->frameRenderActivate(            );
                this->frameSwapActivate  (            );
            }
        }
    }
    else
    {
        fprintf(stderr, "Running with swap lock\n");
        fflush (stderr);

        if(_mfWindows.size() == 1)
        {
            fprintf(stderr, "Running with one windw\n");
            fflush (stderr);

            this->activate();

            while(_bRun == true)
            {
                _pSyncBarrier->enter       (_uiSyncCount);

                _pSyncFromThread->getChangeList()->applyNoClear();

                _pSyncBarrier->enter       (_uiSyncCount);
                
                OSG::Thread::getCurrentChangeList()->commitChangesAndClear();

                if(_bRun == false)
                {
                    //this->deactivate();
                    break;
                }

                this->frameRender   (            );
                
                _pSwapBarrier->enter(_uiSwapCount);
                
                this->frameSwap     (            );
            }
        }
        else
        {
            fprintf(stderr, "Running with n-windws\n");
            fflush (stderr);

            fprintf(stderr, "Running with one windw\n");
            fflush (stderr);

            while(_bRun == true)
            {
                _pSyncBarrier->enter               (_uiSyncCount);

                _pSyncFromThread->getChangeList()->applyNoClear();

                _pSyncBarrier->enter               (_uiSyncCount);

                OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
                
                if(_bRun == false)
                    break;

                this->frameRenderActivate(            );

                _pSwapBarrier->enter     (_uiSwapCount);

                this->frameSwapActivate  (            );
            }
        }
    }

    fprintf(stderr, "Drawer run par stop\n");


    // Main structure
    _pSyncBarrier->enter(_uiSyncCount);

    _pSyncFromThread->getChangeList()->applyNoClear();

    Thread::getCurrentChangeList()->commitChangesAndClear();

    this->frameExit();

    _pSyncBarrier->enter(_uiSyncCount);
                

    // Windows
    _pSyncBarrier->enter(_uiSyncCount);

    _pSyncFromThread->getChangeList()->applyNoClear();

    _pSyncBarrier->enter(_uiSyncCount);
                
    Thread::getCurrentChangeList()->commitChangesAndClear();
}

void Drawer::frameRenderActivate(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->frameRenderActivate(_pAction);
        
        ++winIt;
    }
}

void Drawer::frameSwapActivate(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->frameSwapActivate();
        
        ++winIt;
    }
}

void Drawer::frameExit(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->frameExit();
        
        ++winIt;
    }
}

void Drawer::activate(UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->activate();
}

void Drawer::frameRender(UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->frameRender(_pAction);
}

void Drawer::frameSwap(UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->frameSwap();
}

void Drawer::deactivate (UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->deactivate();
}

void Drawer::setRunning(bool bVal)
{
    _bRun = false;
}

void Drawer::resolveLinks(void)
{
    Inherited::resolveLinks();
}



/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType DrawThread::_type(
    "OSGDrawThread",
    "OSGThread",
    (CreateThreadF) DrawThread::create,
    NULL);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

DrawThread *DrawThread::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<DrawThread *>(pThread);
}

DrawThread *DrawThread::get(Char8 *szName) 
{
    BaseThread *pThread = ThreadManager::the()->getThread(szName,
                                                          "OSGDrawThread");

    return dynamic_cast<DrawThread *>(pThread);
}

void DrawThread::setDrawer(Drawer *pDrawer)
{
    _pDrawer = pDrawer;
}

void DrawThread::setRunning(bool bVal)
{
    _pDrawer->setRunning(bVal);
}


BaseThread *DrawThread::create(const Char8  *szName, 
                                     UInt32  uiId)
{
    return new DrawThread(szName, uiId);
}

DrawThread::DrawThread(const Char8 *szName, UInt32 uiId) :
     Inherited(szName, 
               uiId  ),
    _pDrawer  (NULL  )
{
}

DrawThread::~DrawThread(void)
{
}

void DrawThread::workProc(void)
{
    OSG_ASSERT(_pDrawer != NULL);

    _pDrawer->runParallel();
}

OSG_END_NAMESPACE
