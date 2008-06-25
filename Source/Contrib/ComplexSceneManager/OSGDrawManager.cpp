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

#include "OSGDrawManager.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDrawManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGDrawManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DrawManager::initMethod(InitPhase ePhase)
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

DrawManager::DrawManager(void) :
     Inherited   (    ),

    _pThread     (NULL),
    _pSyncBarrier(NULL),
    _pSwapBarrier(NULL),
    _uiSyncCount (0   )

{
}

DrawManager::DrawManager(const DrawManager &source) :
    Inherited    (source),

    _pThread     (NULL  ),
    _pSyncBarrier(NULL  ),
    _pSwapBarrier(NULL  ),
    _uiSyncCount (0     )
{
}

DrawManager::~DrawManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DrawManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DrawManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DrawManager NI" << std::endl;
}

bool DrawManager::init(void)
{
    bool returnValue = true;

    MFUnrecDrawerPtr::const_iterator dIt  = getMFDrawer()->begin();
    MFUnrecDrawerPtr::const_iterator dEnd = getMFDrawer()->end  ();


    if(_sfParallel.getValue() == true)
    {
        _pThread      = Thread::getCurrent();

        addRef(_pThread);

        _pSyncBarrier = Barrier::get(_sfSyncBarrierName.getValue().c_str());

        addRef(_pSyncBarrier);

        if(_sfSwapBarrierName.getValue().empty() == false)
        {
            _pSwapBarrier = Barrier::get(_sfSwapBarrierName.getValue().c_str());

            addRef(_pSwapBarrier);
        }

        OSG_ASSERT(_pSyncBarrier != NULL);
        OSG_ASSERT(_pThread      != NULL);
       
        _uiSyncCount = _mfDrawer.size() + 1;

        while(dIt != dEnd)
        {
            (*dIt)->setParallel      ( true           );

            (*dIt)->setSyncBarrier   (_pSyncBarrier   );
            (*dIt)->setSwapBarrier   (_pSwapBarrier );

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

void DrawManager::shutdown(void)
{
    if(_sfParallel.getValue() == true)
    {
        MFUnrecDrawerPtr::const_iterator dIt  = getMFDrawer()->begin();
        MFUnrecDrawerPtr::const_iterator dEnd = getMFDrawer()->end  ();


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


        // sync structure takedown

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

            (*dIt)->setSyncFromThread(NULL);
           
            ++dIt;
        }

        subRef(_pThread);
        _pThread = NULL;

        subRef(_pSyncBarrier);
        _pSyncBarrier = NULL;

        subRef(_pSwapBarrier);
        _pSwapBarrier = NULL;
    }
}

void DrawManager::frame(Time oTime, UInt32 uiFrame)
{
    commitChanges();

    if(_sfParallel.getValue() == true)
    {
        _pSyncBarrier->enter(_uiSyncCount);
        _pSyncBarrier->enter(_uiSyncCount);

        _pThread->getChangeList()->clear();
    }
    else
    {
        MFUnrecDrawerPtr::const_iterator drawerIt  = getMFDrawer()->begin();
        MFUnrecDrawerPtr::const_iterator drawerEnd = getMFDrawer()->end  ();

        while(drawerIt != drawerEnd)
        {
            (*drawerIt)->frame(oTime, uiFrame);
                        
            ++drawerIt;
        }
    }
}

FieldContainer *DrawManager::findNamedComponent(const Char8 *szName) const
{
    MFUnrecDrawerPtr::const_iterator drawerIt  = _mfDrawer.begin();
    MFUnrecDrawerPtr::const_iterator drawerEnd = _mfDrawer.end  ();

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
