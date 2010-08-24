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
#include "OSGRenderAction.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMDrawer::initMethod(InitPhase ePhase)
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

CSMDrawer::CSMDrawer(void) :
     Inherited      (     ),
    _pAction        (NULL ),
    _pDrawThread    (NULL ),
    _pSyncFromThread(NULL ),
    _pSyncBarrier   (NULL ),
    _pSwapBarrier   (NULL ),
#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock      (NULL ),
#endif

    _uiSyncCount    (0    ),
    _uiSwapCount    (0    ),
    _bParallel      (false),
    _bRun           (false)
{
}

CSMDrawer::CSMDrawer(const CSMDrawer &source) :
     Inherited      (source),
    _pAction        (NULL  ),
    _pDrawThread    (NULL  ),
    _pSyncFromThread(NULL ),
    _pSyncBarrier   (NULL  ),
    _pSwapBarrier   (NULL  ),
#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock      (NULL ),
#endif

    _uiSyncCount    (0     ),
    _uiSwapCount    (0     ),
    _bParallel      (false ),
    _bRun           (false)
{
}

CSMDrawer::~CSMDrawer(void)
{
    delete _pAction;
}

void CSMDrawer::setSyncFromThread(Thread *pThread)
{
    _pSyncFromThread = pThread;
}

void CSMDrawer::setSyncBarrier(Barrier *pSyncBarrier)
{
    _pSyncBarrier = pSyncBarrier;
}

void CSMDrawer::setSwapBarrier(Barrier *pSwapBarrier)
{
    _pSwapBarrier = pSwapBarrier;
}

#ifdef OSG_GLOBAL_SYNC_LOCK
void CSMDrawer::setSyncLock(Lock *pSyncLock)
{
    _pSyncLock = pSyncLock;
}
#endif


void CSMDrawer::setSyncCount(UInt32 uiSyncCount)
{
    _uiSyncCount = uiSyncCount;
}

void CSMDrawer::setSwapCount(UInt32 uiSwapCount)
{
    _uiSwapCount = uiSwapCount;
}

void CSMDrawer::setParallel(bool bParallel)
{
    _bParallel = bParallel;
}

void CSMDrawer::postSync(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator wIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator wEnd = getMFWindows()->end  ();

    for(; wIt != wEnd; ++wIt)
    {
        (*wIt)->postSync();
    }
}

/*----------------------------- class specific ----------------------------*/

void CSMDrawer::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMDrawer::dump(      UInt32    ,
                     const BitVector ) const
{
    SLOG << "Dump CSMDrawer NI" << std::endl;
}

bool CSMDrawer::init(void)
{
    bool returnValue = true;

    MFUnrecChildCSMWindowPtr::const_iterator wIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator wEnd = getMFWindows()->end  ();

    for(; wIt != wEnd; ++wIt)
    {
        returnValue = (*wIt)->init();

        if(returnValue == false)
            break;
    }

    _pAction = RenderAction::create();

    if(_bParallel == true)
    {
        _pDrawThread  = CSMDrawThread ::get(NULL, false);

        OSG_ASSERT(_pDrawThread     != NULL);
        OSG_ASSERT(_pSyncBarrier    != NULL);
        OSG_ASSERT(_pSyncFromThread != NULL);
#ifdef OSG_GLOBAL_SYNC_LOCK
        OSG_ASSERT(_pSyncLock       != NULL);
#endif

        _pDrawThread->setDrawer(this);
        _pDrawThread->run(_sfAspect.getValue());
    }

//    _pAction->setFrustumCulling(false);

    return returnValue;
}

void CSMDrawer::endDrawThread (void)
{
    if(_bParallel == true)
    {
        _pDrawThread->setRunning(false);
    }
}

void CSMDrawer::shutdown(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->shutdown();

        ++winIt;
    }
}

void CSMDrawer::joinDrawThread(void)
{
    if(_bParallel == true)
    {
        Thread::join(_pDrawThread);

        _pDrawThread = NULL;
    }
}

void CSMDrawer::frame(Time oTime, UInt32 uiFrame)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->render(_pAction);
        
        ++winIt;
    }
}

FieldContainer *CSMDrawer::findNamedComponent(const Char8 *szName) const
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
            FieldContainer *tmpVal = (*winIt)->findNamedComponent(szName);
                
            if(tmpVal != NULL)
                return tmpVal;
        }
        
        ++winIt;
    }
    
    return NULL;
}

void CSMDrawer::render(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->render(_pAction);
        
        ++winIt;
    }
}

void CSMDrawer::runParallel(void)
{
    fprintf(stderr, "Drawer run par\n");

    _bRun = true;

    for(UInt32 i = 0; i < 10; ++i)
    {
        _pSyncBarrier->enter(_uiSyncCount);

#ifdef OSG_GLOBAL_SYNC_LOCK
        _pSyncLock->acquire();
#endif

        _pSyncFromThread->getChangeList()->applyNoClear();

#ifdef OSG_GLOBAL_SYNC_LOCK
        _pSyncLock->release();
#endif

        _pSyncBarrier->enter(_uiSyncCount);

#if 0
        Thread::getCurrentChangeList()->commitChangesAndClear();
#else
        Thread::getCurrentChangeList()->commitChanges();
#endif
    }

    if(_pSwapBarrier == NULL)
    {
        fprintf(stderr, "Running without swap lock\n");
        fflush (stderr);

#if 0
        if(_mfWindows.size() == 1)
        {
            fprintf(stderr, "Running with one windw\n");
            fflush (stderr);

            this->activate();

            while(_bRun == true)
            {
                _pSyncBarrier->enter(_uiSyncCount);

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->acquire();
# endif

                _pSyncFromThread->getChangeList()->applyNoClear();

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->release();
# endif

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

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->acquire();
# endif

                _pSyncFromThread->getChangeList()->applyNoClear();

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->release();
# endif

                _pSyncBarrier->enter               (_uiSyncCount);

                Thread::getCurrentChangeList()->commitChangesAndClear();

                if(_bRun == false)
                    break;

                this->frameRenderActivate(            );
                this->frameSwapActivate  (            );
            }
        }
#else
        fprintf(stderr, "Running with %"PRISize"-windws\n", _mfWindows.size());
        fflush (stderr);

        while(_bRun == true)
        {
            _pSyncBarrier->enter               (_uiSyncCount);
                
# ifdef OSG_GLOBAL_SYNC_LOCK
            _pSyncLock->acquire();
# endif

            _pSyncFromThread->getChangeList()->applyNoClear();

# ifdef OSG_GLOBAL_SYNC_LOCK
            _pSyncLock->release();
# endif

            _pSyncBarrier->enter               (_uiSyncCount);

# if 0
            Thread::getCurrentChangeList()->commitChangesAndClear();

            if(_bRun == false)
                break;

            this->render();
# else
            Thread::getCurrentChangeList()->commitChanges();

            if(_bRun == false)
            {
                Thread::getCurrentChangeList()->commitChangesAndClear();
                
                break;
            }

            this->render();

            Thread::getCurrentChangeList()->commitChangesAndClear();
# endif
#endif
        }
    }
    else
    {
        fprintf(stderr, "Running with swap lock\n");
        fflush (stderr);

#if 0
        if(_mfWindows.size() == 1)
        {
            fprintf(stderr, "Running with one windw\n");
            fflush (stderr);

            this->activate();

            while(_bRun == true)
            {
                _pSyncBarrier->enter       (_uiSyncCount);

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->acquire();
# endif

                _pSyncFromThread->getChangeList()->applyNoClear();

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->release();
# endif

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

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->acquire();
# endif
                _pSyncFromThread->getChangeList()->applyNoClear();

# ifdef OSG_GLOBAL_SYNC_LOCK
                _pSyncLock->release();
# endif

                _pSyncBarrier->enter               (_uiSyncCount);

                OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
                
                if(_bRun == false)
                    break;

                this->frameRenderActivate(            );

                _pSwapBarrier->enter     (_uiSwapCount);

                this->frameSwapActivate  (            );
            }
        }
#else
        fprintf(stderr, "Running with %"PRISize"-windws\n", _mfWindows.size());
        fflush (stderr);

        while(_bRun == true)
        {
            _pSyncBarrier->enter               (_uiSyncCount);

# ifdef OSG_GLOBAL_SYNC_LOCK
            _pSyncLock->acquire();
# endif
            _pSyncFromThread->getChangeList()->applyNoClear();

# ifdef OSG_GLOBAL_SYNC_LOCK
            _pSyncLock->release();
# endif

            _pSyncBarrier->enter               (_uiSyncCount);

#if 0
            OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
                
            if(_bRun == false)
                break;

            this->frameRenderNoFinish(            );

            _pSwapBarrier->enter     (_uiSwapCount);

            this->frameFinish        (            );
# else
            OSG::Thread::getCurrentChangeList()->commitChanges();
                
            if(_bRun == false)
            {
                OSG::Thread::getCurrentChangeList()->commitChangesAndClear();

                break;
            }

            this->frameRenderNoFinish(            );

            OSG::Thread::getCurrentChangeList()->commitChangesAndClear();

            _pSwapBarrier->enter     (_uiSwapCount);

            this->frameFinish        (            );
# endif
        }
#endif
    }

    fprintf(stderr, "Drawer run par stop\n");


    // Main structure
    _pSyncBarrier->enter(_uiSyncCount);

#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock->acquire();
#endif

    _pSyncFromThread->getChangeList()->applyNoClear();

#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock->release();
#endif

    Thread::getCurrentChangeList()->commitChangesAndClear();

    this->frameExit();

    _pSyncBarrier->enter(_uiSyncCount);
                

    // gl takedown
    _pSyncBarrier->enter(_uiSyncCount);

#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock->acquire();
#endif

    _pSyncFromThread->getChangeList()->applyNoClear();

#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock->release();
#endif

    _pSyncBarrier->enter(_uiSyncCount);


    // Windows
    _pSyncBarrier->enter(_uiSyncCount);

#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock->acquire();
#endif

    _pSyncFromThread->getChangeList()->applyNoClear();

#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock->release();
#endif

    _pSyncBarrier->enter(_uiSyncCount);
                
    Thread::getCurrentChangeList()->commitChangesAndClear();
}

void CSMDrawer::frameRenderNoFinish(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->frameRenderNoFinish(_pAction);
        
        ++winIt;
    }
}

void CSMDrawer::frameFinish(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->frameFinish();
        
        ++winIt;
    }
}

void CSMDrawer::frameExit(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->frameExit();
        
        ++winIt;
    }
}

#if 0
void CSMDrawer::activate(UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->activate();
}

void CSMDrawer::frameRender(UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->frameRender(_pAction);
}

void CSMDrawer::frameSwap(UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->frameSwap();
}

void CSMDrawer::deactivate (UInt32 uiWindow)
{
    OSG_ASSERT(uiWindow < _mfWindows.size());

    _mfWindows[uiWindow]->deactivate();
}
#endif

void CSMDrawer::setRunning(bool bVal)
{
    _bRun = false;
}

void CSMDrawer::resolveLinks(void)
{
    Inherited::resolveLinks();
}

void CSMDrawer::terminateGLContexts(void)
{
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->terminateGLContext();
        
        ++winIt;
    }
}


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType CSMDrawThread::_type(
    "OSGCSMDrawThread",
    "OSGThread",
    static_cast<CreateThreadF>(CSMDrawThread::create),
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

CSMDrawThread *CSMDrawThread::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<CSMDrawThread *>(pThread);
}

CSMDrawThread::ObjTransitPtr CSMDrawThread::get(Char8 *szName, bool bGlobal) 
{
    BaseThreadTransitPtr pThread = 
        ThreadManager::the()->getThread(szName,
                                        bGlobal,
                                        "OSGCSMDrawThread");

    return dynamic_pointer_cast<CSMDrawThread>(pThread);
}

void CSMDrawThread::setDrawer(CSMDrawer *pDrawer)
{
    _pDrawer = pDrawer;
}

void CSMDrawThread::setRunning(bool bVal)
{
    _pDrawer->setRunning(bVal);
}


BaseThread *CSMDrawThread::create(const Char8  *szName, 
                                        UInt32  uiId, 
                                        bool    bGlobal)
{
    return new CSMDrawThread(szName, uiId, bGlobal);
}

CSMDrawThread::CSMDrawThread(const Char8 *szName, UInt32 uiId, bool bGlobal) :
     Inherited(szName, 
               uiId,
               bGlobal),
    _pDrawer  (NULL   )
{
}

CSMDrawThread::~CSMDrawThread(void)
{
}

void CSMDrawThread::workProc(void)
{
    OSG_ASSERT(_pDrawer != NULL);

    _pDrawer->runParallel();
}

OSG_END_NAMESPACE
