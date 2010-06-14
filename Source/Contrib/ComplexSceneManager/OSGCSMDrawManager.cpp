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

#include "OSGCSMDrawManager.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMDrawManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMDrawManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMDrawManager::initMethod(InitPhase ePhase)
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

CSMDrawManager::CSMDrawManager(void) :
     Inherited   (    ),

    _pThread     (NULL),
    _pSyncBarrier(NULL),
    _pSwapBarrier(NULL),
#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock   (NULL),
#endif
    _uiSyncCount (0   )
{
}

CSMDrawManager::CSMDrawManager(const CSMDrawManager &source) :
    Inherited    (source),

    _pThread     (NULL  ),
    _pSyncBarrier(NULL  ),
    _pSwapBarrier(NULL  ),
#ifdef OSG_GLOBAL_SYNC_LOCK
    _pSyncLock   (NULL  ),
#endif
    _uiSyncCount (0     )
{
}

CSMDrawManager::~CSMDrawManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMDrawManager::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CSMDrawManager::dump(      UInt32    ,
                          const BitVector ) const
{
    SLOG << "Dump CSMDrawManager NI" << std::endl;
}

bool CSMDrawManager::init(void)
{
    bool returnValue = true;

    MFUnrecCSMDrawerPtr::const_iterator dIt  = getMFDrawer()->begin();
    MFUnrecCSMDrawerPtr::const_iterator dEnd = getMFDrawer()->end  ();


    if(_sfParallel.getValue() == true)
    {
        _pThread   = dynamic_cast<OSG::Thread *>(Thread::getCurrent());

#ifdef OSG_GLOBAL_SYNC_LOCK
        _pSyncLock = Lock::get("DM::synclock", false);
#endif

        _pSyncBarrier = Barrier::get(_sfSyncBarrierName.getValue().c_str(),
                                     false);

        if(_sfSwapBarrierName.getValue().empty() == false)
        {
            _pSwapBarrier = Barrier::get(_sfSwapBarrierName.getValue().c_str(),
                                         false);
        }

        OSG_ASSERT(_pSyncBarrier != NULL);
        OSG_ASSERT(_pThread      != NULL);
#ifdef OSG_GLOBAL_SYNC_LOCK
        OSG_ASSERT(_pSyncLock    != NULL);
#endif
       
        _uiSyncCount = _mfDrawer.size() + 1;

        while(dIt != dEnd)
        {
            (*dIt)->setParallel      ( true           );

            (*dIt)->setSyncBarrier   (_pSyncBarrier   );
            (*dIt)->setSwapBarrier   (_pSwapBarrier   );
#ifdef OSG_GLOBAL_SYNC_LOCK
            (*dIt)->setSyncLock      (_pSyncLock      );
#endif

            (*dIt)->setSyncCount     (_uiSyncCount    );
            (*dIt)->setSyncFromThread(_pThread        );

            (*dIt)->setSwapCount     (_mfDrawer.size());
            (*dIt)->init();
            
            ++dIt;
        }
    }
    else
    {
        while(dIt != dEnd)
        {
            returnValue = (*dIt)->init();
            
            if(returnValue == false)
                break;
            
            ++dIt;
        }
    }

    return returnValue;
}

void CSMDrawManager::shutdown(void)
{
    if(_sfParallel.getValue() == true)
    {
        MFUnrecCSMDrawerPtr::const_iterator dIt  = getMFDrawer()->begin();
        MFUnrecCSMDrawerPtr::const_iterator dEnd = getMFDrawer()->end  ();


        // Stop drawer

        commitChanges();

        _pSyncBarrier->enter(_uiSyncCount);

        while(dIt != dEnd)
        {
            (*dIt)->endDrawThread();
            
            ++dIt;
        }

        _pSyncBarrier->enter(_uiSyncCount);

        _pThread->getChangeList()->clear();


        // resolve structure

        dIt  = getMFDrawer()->begin();

        while(dIt != dEnd)
        {
            (*dIt)->shutdown();
            
            ++dIt;
        }

        AttachmentContainer::resolveLinks();

        // sync structure takedown

        commitChanges();

        _pSyncBarrier->enter(_uiSyncCount);
        _pSyncBarrier->enter(_uiSyncCount);

        _pThread->getChangeList()->clear();


        // release gl contexts

        dIt  = getMFDrawer()->begin();

        while(dIt != dEnd)
        {
            (*dIt)->terminateGLContexts();
            
            ++dIt;
        }

        // sync gl takedown

        commitChanges();

        _pSyncBarrier->enter(_uiSyncCount);
        _pSyncBarrier->enter(_uiSyncCount);

        _pThread->getChangeList()->clear();


        // release windows

        dIt  = getMFDrawer()->begin();

        while(dIt != dEnd)
        {
            (*dIt)->resolveLinks();
            
            ++dIt;
        }

        commitChanges();

        _pSyncBarrier->enter(_uiSyncCount);
        _pSyncBarrier->enter(_uiSyncCount);

        _pThread->getChangeList()->clear();


        // wait for draw threads to finish

        dIt  = getMFDrawer()->begin();

        while(dIt != dEnd)
        {
            (*dIt)->joinDrawThread();
            
            ++dIt;
        }

        dIt  = getMFDrawer()->begin();

        while(dIt != dEnd)
        {
            (*dIt)->setSyncBarrier   (NULL);
            (*dIt)->setSwapBarrier   (NULL);

#ifdef OSG_GLOBAL_SYNC_LOCK
            (*dIt)->setSyncLock      (NULL);
#endif

            (*dIt)->setSyncFromThread(NULL);
           
            ++dIt;
        }

        _pThread      = NULL;
        _pSyncBarrier = NULL;
        _pSwapBarrier = NULL;

#ifdef OSG_GLOBAL_SYNC_LOCK
        _pSyncLock    = NULL;
#endif
    }
    else
    {
        MFUnrecCSMDrawerPtr::const_iterator dIt  = getMFDrawer()->begin();
        MFUnrecCSMDrawerPtr::const_iterator dEnd = getMFDrawer()->end  ();

        for(; dIt != dEnd; ++dIt)
        {
            (*dIt)->shutdown();
        }

        commitChanges();

        AttachmentContainer::resolveLinks();

        dIt  = getMFDrawer()->begin();

        while(dIt != dEnd)
        {
            (*dIt)->terminateGLContexts();
            
            ++dIt;
        }

        commitChanges();
    }
}

void CSMDrawManager::frame(Time oTime, UInt32 uiFrame)
{
    commitChanges();

    if(_sfParallel.getValue() == true)
    {
        _pSyncBarrier->enter(_uiSyncCount);
        _pSyncBarrier->enter(_uiSyncCount);

        MFUnrecCSMDrawerPtr::const_iterator drawerIt  = getMFDrawer()->begin();
        MFUnrecCSMDrawerPtr::const_iterator drawerEnd = getMFDrawer()->end  ();

        for(; drawerIt != drawerEnd; ++drawerIt)
        {
            (*drawerIt)->postSync();
        }

        _pThread->getChangeList()->clear();
    }
    else
    {
        MFUnrecCSMDrawerPtr::const_iterator drawerIt  = getMFDrawer()->begin();
        MFUnrecCSMDrawerPtr::const_iterator drawerEnd = getMFDrawer()->end  ();

        for(; drawerIt != drawerEnd; ++drawerIt)
        {
            (*drawerIt)->frame(oTime, uiFrame);
        }
    }
}

FieldContainer *CSMDrawManager::findNamedComponent(const Char8 *szName) const
{
    MFUnrecCSMDrawerPtr::const_iterator drawerIt  = _mfDrawer.begin();
    MFUnrecCSMDrawerPtr::const_iterator drawerEnd = _mfDrawer.end  ();

    const Char8               *szTmpName   = NULL;

    while(drawerIt != drawerEnd)
    {
        szTmpName = OSG::getName(*drawerIt);
            
        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return *drawerIt;
        }
        else
        {
            FieldContainer *tmpVal = (*drawerIt)->findNamedComponent(szName);
                
            if(tmpVal != NULL)
                return tmpVal;
        }
        
        ++drawerIt;
    }
    
    return NULL;
}

OSG_END_NAMESPACE
