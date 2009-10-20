/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#include <iostream>

#include "OSGSemaphore.h"

#include "OSGBaseFunctions.h"

#include "OSGThreadManager.h"

#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

SemaphoreCommonBase::SemaphoreCommonBase(void) :
     Inherited    (NULL, true),
    _uiSemaphoreId(0         )
{
}

SemaphoreCommonBase::SemaphoreCommonBase(const Char8  *szName,
                                               UInt32  uiId, 
                                               bool    bGlobal) :
     Inherited    (szName, 
                   bGlobal),
    _uiSemaphoreId(uiId   )
{
}

/*---------------------------- Destructor ---------------------------------*/

SemaphoreCommonBase::~SemaphoreCommonBase(void)
{
}



#if defined (OSG_USE_PTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

PThreadSemaphoreBase::PThreadSemaphoreBase(void):
     Inherited         (),
    _pLowLevelSemaphore()
{
}

PThreadSemaphoreBase::PThreadSemaphoreBase(const Char8  *szName,
                                                 UInt32  uiId, 
                                                 bool    bGlobal) :
     Inherited         (szName, uiId, bGlobal),
    _pLowLevelSemaphore(                     )
{
}

/*---------------------------- Destructor ---------------------------------*/

PThreadSemaphoreBase::~PThreadSemaphoreBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool PThreadSemaphoreBase::init(void)
{
    sem_init(&(_pLowLevelSemaphore), 0, 0);
    
    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void PThreadSemaphoreBase::shutdown(void)
{
    sem_destroy(&(_pLowLevelSemaphore));
}


#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

SprocSemaphoreBase::SprocSemaphoreBase(void):
     Inherited    (    ),
    _pLowLevelSema(NULL)
{
}

SprocSemaphoreBase::SprocSemaphoreBase(const Char8  *szName,
                                             UInt32  uiId, 
                                             bool    bGlobal) :
     Inherited    (szName, uiId, bGlobal),
    _pLowLevelSema(NULL                 )
{
}

/*---------------------------- Destructor ---------------------------------*/

SprocSemaphoreBase::~SprocSemaphoreBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool SprocSemaphoreBase::init(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return false;

    if(pThreadManager->getArena() == NULL)
        return false;

    _pLowLevelSema = usnewsema(pThreadManager->getArena(), 1);

    if(_pLowLevelSema == NULL)
        return false;

    usinitsema(_pLowLevelSema, 1);
    usctlsema (_pLowLevelSema, CS_RECURSIVEON, NULL);

    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void SprocSemaphoreBase::shutdown(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return;

    if(pThreadManager->getArena() == NULL)
        return;

    if(_pLowLevelSema != NULL)
    {
        usfreesema(_pLowLevelSema, pThreadManager->getArena());

        _pLowLevelSema = NULL;
    }
}

/*----------------------------- Semaphore ---------------------------------*/

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

WinThreadSemaphoreBase::WinThreadSemaphoreBase(void) :
     Inherited (    ),
    _pSemaphore(NULL)
{
}

WinThreadSemaphoreBase::WinThreadSemaphoreBase(const Char8  *szName,
                                                     UInt32  uiId, 
                                                     bool    bGlobal) :
     Inherited (szName, uiId, bGlobal),
    _pSemaphore(NULL                 )
{
}

/*---------------------------- Destructor ---------------------------------*/

WinThreadSemaphoreBase::~WinThreadSemaphoreBase(void)
{
}

/*-------------------------- Construction ---------------------------------*/

bool WinThreadSemaphoreBase::init(void)
{
    _pSemaphore = CreateSemaphore( NULL,     // no security attributes
                                   0,    // initially not owned
                                   1024,
                                  _szName);  // name of mutex

    if(_pSemaphore == NULL)
    {
        return false;
    }

    return true;
}

/*-------------------------- Destruction ----------------------------------*/

void WinThreadSemaphoreBase::shutdown(void)
{
    if(_pSemaphore != NULL)
    {
        CloseHandle(_pSemaphore);
        _pSemaphore = NULL;
    }
}

#endif /* OSG_USE_WINTHREADS */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPSemaphoreType Semaphore::_type( "OSGSemaphore", 
                                  "OSGMPBase", 
                                 &Semaphore::create);

/*------------------------------- Get -------------------------------------*/

Semaphore::ObjTransitPtr Semaphore::get(const Char8 *szName, bool bGlobal)
{
    return ThreadManager::the()->getSemaphore(szName, bGlobal, "OSGSemaphore");
}

Semaphore *Semaphore::find(const Char8 *szName)
{
    return ThreadManager::the()->findSemaphore(szName);
}


/*------------------------------ Create -----------------------------------*/

Semaphore *Semaphore::create(const Char8 *szName, UInt32 uiId, bool bGlobal)
{
    Semaphore *returnValue = NULL;

    returnValue = new Semaphore(szName, uiId, bGlobal);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }

    return returnValue;
}

/*--------------------------- Constructors --------------------------------*/

Semaphore::Semaphore(void) :
    Inherited()
{
}

Semaphore::Semaphore(const Char8 *szName, UInt32 uiId, bool bGlobal) :
    Inherited(szName, uiId, bGlobal)
{
}

/*---------------------------- Destructor ---------------------------------*/

Semaphore::~Semaphore(void)
{
    _bGlobal = false;

    ThreadManager::the()->remove(this);

    shutdown();
}


OSG_END_NAMESPACE
