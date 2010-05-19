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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGSharedObjectHandler.h"
#include "OSGBaseFunctions.h"
#include "OSGFactoryController.h"
#include "OSGLog.h"

#ifndef WIN32
#include <dlfcn.h>
#endif

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

TChar SharedObject::_szApplicationObjectName[] = OSGT("Application");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

SharedObject::SharedObject(const TChar *szName) :
	 Inherited(       ),
    _szName   (       ),
    _pHandle  (NULL   ),
    _type     (Invalid)
{
    if(szName == NULL)
    {
        _szName.assign(_szApplicationObjectName);

        _type = Application;
    }
    else
    {
        _szName.assign(szName);

        _type = SharedLibrary;
    }    
    
    FINFO(("construct SharedObject %s\n", _szName.c_str()));
}

SharedObject::~SharedObject(void)
{
    FINFO(("destroy SharedObject %s\n", _szName.c_str()));
}

bool SharedObject::close(void)
{
    bool returnValue = false;

    if(_pHandle != NULL)
    {
#ifndef WIN32
        returnValue = (dlclose(_pHandle) == 0);
#else
        returnValue = (FreeLibrary(_pHandle) != 0);
#endif
        _pHandle    = NULL;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

bool SharedObject::open()
{
    const TChar *libName = NULL;

    if(_pHandle != NULL)
    {
        return true;
    }

    if(_type == SharedLibrary)
    {
        libName = _szName.c_str();
    }

#ifndef WIN32
#ifdef OSG_DLOPEN_LAZY
    _pHandle = dlopen(libName, RTLD_LAZY);
#else
    _pHandle = dlopen(libName, RTLD_NOW);
#endif

    if(_pHandle == NULL)
    {
        SFATAL << "SharedObject::open: Could not open shared object '"
               << _szName << "':  " << dlerror() << std::endl;
    }
#else
    if(libName != NULL)
    {
        _pHandle = LoadLibrary(libName);
    }
    else
    {
        Char8 moduleName[1024];

        GetModuleFileName(NULL, moduleName, 1024);

        _pHandle = LoadLibrary(moduleName);
    }

    if(_pHandle == NULL)
    {
        SFATAL << "SharedObject::open: Could not open shared object '"
               << _szName << "'." << std::endl;
    }
#endif

    return (_pHandle != NULL);
}

AnonSymbolHandle SharedObject::getSymbol(const TChar *szSymbolName)
{
    AnonSymbolHandle returnValue = NULL;

    if(isOpen() == false)
    {
        if(open() == false)
        {
            return returnValue;
        }
    }

    if(_pHandle != NULL && szSymbolName != NULL)
    {
#ifndef WIN32
        returnValue = dlsym(_pHandle, szSymbolName);
#else
        returnValue = (AnonSymbolHandle) GetProcAddress(_pHandle, 
                                                         szSymbolName);
#endif
    }

#ifndef WIN32
    if(returnValue == NULL)
        fprintf(stderr, "%s\n", dlerror()); // Why not using log? !!! DR
#else
#endif

    return returnValue;
}

bool SharedObject::isOpen(void)
{
    return _pHandle != NULL;
}

bool SharedObject::reOpen(void)
{
    close();
    
    return open();
}

const tstring &SharedObject::getName(void)
{
    return _szName;
}

const TChar *SharedObject::getCName(void)
{
    return _szName.c_str();
}

void SharedObject::dump(void)
{
    FLOG(("\tObject %s | %p\n", _szName.c_str(), _pHandle));
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

SharedObjectHandlerP SharedObjectHandler::_the = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

SharedObjectHandlerP SharedObjectHandler::the(void)
{
    if(_the == NULL)
    {
        _the = new SharedObjectHandler;
    }

    return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

SharedObjectHandler::SharedObjectHandler(void) :
    _mSharedObjects(),
    _vLoadedNames  ()
{
    FDEBUG(("create SharedObjectHandler\n"));
}

SharedObjectHandler::~SharedObjectHandler(void)
{
    FDEBUG(("destroy SharedObjectHandler\n"));
}

void SharedObjectHandler::terminate(void)
{
    FDEBUG(("terminate SharedObjectHandler\n"));

    //this->dump();

    SharedObjectMapIt soIt  = _mSharedObjects.begin();
    SharedObjectMapIt soEnd = _mSharedObjects.end  ();

    while(soIt != soEnd)
    {
        soIt->second->close();

        OSG::subRef(soIt->second);

        ++soIt;
    }

    _the = NULL;
    delete this;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

SharedObjectP SharedObjectHandler::getSharedObject(
    const TChar *szName)
{
    SharedObjectP returnValue = NULL;

    returnValue = findSharedObject(szName);

    if(returnValue == NULL)
    {
        returnValue = new SharedObject(szName);

        returnValue->open        ();

        OSG::addRef(returnValue);

        _mSharedObjects[returnValue->getName()] = returnValue;

        if(GlobalSystemState == Running)
        {
            FactoryController::the()->initializePendingElements();
        }
    }

    for(UInt32 i = 0; i < _vLoadedNames.size(); ++i)
    {
        FLOG(("Pulled in %s\n", _vLoadedNames[i].c_str()));
    }

    _vLoadedNames.clear();

    return returnValue;
}

SharedObjectP SharedObjectHandler::getOSGSharedObject(
    const TChar *szName)
{
    SharedObjectP returnValue = NULL;

    tstring tmpString; 

#ifndef WIN32    
    tmpString.append(OSGT("lib"));
    tmpString.append(szName);
    tmpString.append(OSGT(".so"));
#else
    tmpString.append(szName);

#ifdef OSG_DEBUG
# ifdef OSG_DEBUGRT
    tmpString.append(OSGT("D"));
# else
    tmpString.append(OSGT("RN"));
# endif
#else
# ifdef OSG_DEBUGRT
    tmpString.append(OSGT("DO"));
# endif
#endif    

    tmpString.append(OSGT(".dll"));
#endif

    returnValue = getSharedObject(tmpString.c_str());

    return returnValue;
}

SharedObjectP SharedObjectHandler::findSharedObject(
    const TChar *szName) const
{
    SharedObjectMapConstIt  mapIt;
    SharedObjectP           returnValue  = NULL;
    tstring                 szSearchName;

    if(szName != NULL)
    {
        szSearchName.assign(szName);
    }
    else
    {
        szSearchName.assign(SharedObject::_szApplicationObjectName);
    }

    mapIt = _mSharedObjects.find(szSearchName);

    if(mapIt != _mSharedObjects.end())
    {
        returnValue = mapIt->second;
    }
    
    return returnValue;
}

void SharedObjectHandler::removeSharedObject(const TChar *szName)
{
    SharedObjectMapIt  mapIt;
    tstring            szSearchName;

    if(szName != NULL)
    {
        szSearchName.assign(szName);
    }
    else
    {
        szSearchName.assign(SharedObject::_szApplicationObjectName);
    }

    mapIt = _mSharedObjects.find(szSearchName);

    _mSharedObjects.erase(mapIt);
}

void SharedObjectHandler::removeSharedObject(SharedObjectP pObject)
{
    if(pObject != NULL)
    {
        removeSharedObject(pObject->getCName());
    }
}

void SharedObjectHandler::registerLoadedObject(const TChar *szName)
{
    tstring tmpString;

#ifndef WIN32    
    tmpString.append(OSGT("lib"));
    tmpString.append(szName);
    tmpString.append(OSGT(".so"));
#else
    tmpString.append(szName);
    tmpString.append(OSGT(".dll"));
#endif

    _vLoadedNames.push_back(tmpString);
}

bool SharedObjectHandler::initialize(void)
{
    SharedObjectP pAppHandle = getSharedObject(NULL);

    for(UInt32 i = 0; i < _vLoadedNames.size(); ++i)
    {
        FLOG(("Preloaded %s %p\n", _vLoadedNames[i].c_str(), pAppHandle));

		_mSharedObjects[_vLoadedNames[i]] = pAppHandle;

        OSG::addRef(pAppHandle);
    }

    _vLoadedNames.clear();

    return true;
}

void SharedObjectHandler::dump(void)
{
    SharedObjectMapIt soIt  = _mSharedObjects.begin();
    SharedObjectMapIt soEnd = _mSharedObjects.end  ();

    while(soIt != soEnd)
    {
        FLOG(("SharedObjectHandler::dump: %s | %p\n",
              soIt->first.c_str(), soIt->second));

        soIt->second->dump();
        ++soIt;
    }
}
