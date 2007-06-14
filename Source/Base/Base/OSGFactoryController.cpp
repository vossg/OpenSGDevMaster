/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#define OSG_COMPILE_FACTORYCONTROLLER

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGFactoryController.h"

#include "OSGFactoryBase.h"
#include "OSGTypeFactory.h"
#include "OSGLog.h"

#include "OSGSingletonHolder.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

OSG_SINGLETON_INST(FactoryControllerBase)

template OSG_DLL_EXPORT class SingletonHolder<FactoryControllerBase>;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

FactoryControllerBase::FactoryControllerBase(void) :
    _pTypeFactory(NULL),
    _mFactoryMap (    )
{
    addPostFactoryExitFunction(&FactoryController::destroy);
}

FactoryControllerBase::~FactoryControllerBase(void)
{
}

bool FactoryControllerBase::initialize(void)
{
    bool returnValue = true;

    FactoryMapIt mapIt  = _mFactoryMap.begin();
    FactoryMapIt mapEnd = _mFactoryMap.end  ();

    while(mapIt != mapEnd)
    {
        returnValue &= mapIt->second->initialize();

        if(returnValue == false)
            break;

        mapIt++;
    }

    if(returnValue == false)
        return returnValue;

    if(_pTypeFactory != NULL)
        returnValue = _pTypeFactory->initialize();

    if(returnValue == false)
        return returnValue;


    mapIt  = _mFactoryMap.begin();
    mapEnd = _mFactoryMap.end  ();

    while(mapIt != mapEnd)
    {
        returnValue &= mapIt->second->initializeFactoryPost();

        if(returnValue == false)
            break;

        mapIt++;
    }

    if(returnValue == false)
        return returnValue;

    if(_pTypeFactory != NULL)
        returnValue = _pTypeFactory->initializeFactoryPost();

    return returnValue;
}

bool FactoryControllerBase::terminate(void)
{
    bool returnValue = true;

    FactoryMapIt mapIt  = _mFactoryMap.begin();
    FactoryMapIt mapEnd = _mFactoryMap.end  ();

    while(mapIt != mapEnd)
    {
        returnValue &= mapIt->second->terminate();

        if(returnValue == false)
            break;

        mapIt++;
    }

    if(_pTypeFactory != NULL)
        returnValue = _pTypeFactory->terminate();

    return returnValue;
}

bool FactoryControllerBase::initializePendingElements(void)
{
    bool returnValue = true;

    FactoryMapIt mapIt  = _mFactoryMap.begin();
    FactoryMapIt mapEnd = _mFactoryMap.end  ();

    while(mapIt != mapEnd)
    {
        returnValue &= mapIt->second->initializePendingElements();

        if(returnValue == false)
            break;

        mapIt++;
    }

    if(returnValue == false)
        return returnValue;

    if(_pTypeFactory != NULL)
        returnValue = _pTypeFactory->initializePendingElements();

    if(returnValue == false)
        return returnValue;

    mapIt  = _mFactoryMap.begin();
    mapEnd = _mFactoryMap.end  ();

    while(mapIt != mapEnd)
    {
        returnValue &= 
            mapIt->second->initializePendingElementsFactoryPost();

        if(returnValue == false)
            break;

        mapIt++;
    }


    if(returnValue == false)
        return returnValue;

    if(_pTypeFactory != NULL)
    {
        returnValue = 
            _pTypeFactory->initializePendingElementsFactoryPost();
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

bool FactoryControllerBase::registerTypeFactory(TypeFactoryBase *pFactory)
{
    if(pFactory == NULL)
    {
		SWARNING << "no type factory given" << std::endl;

		return false;        
    }

	if(pFactory->getName().isEmpty() == true) 
    {
		SWARNING << "TypeFactory without name" << std::endl;

		return false;
	}

    if(findFactory(pFactory->getCName()) != NULL || _pTypeFactory != NULL)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type factory with the name " 
                 << pFactory->getCName()
                 << std::endl;
        
        return false;
    }

    _pTypeFactory = pFactory;

    PINFO << "Registered type factory " << pFactory->getCName() 
          << std::endl;

    return true;
}

bool FactoryControllerBase::registerFactory(FactoryBase *pFactory)
{
    if(pFactory == NULL)
    {
		SWARNING << "no factory given" << std::endl;

		return false;        
    }

	if(pFactory->getName().isEmpty() == true) 
    {
		SWARNING << "FactoryBase without name" << std::endl;

		return false;
	}

    if(findFactory(pFactory->getCName()) != NULL)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type with the name " << pFactory->getCName() << std::endl;

        return false;
    }

    _mFactoryMap[pFactory->getName()] = pFactory;
    
    PINFO << "Registered factory " << pFactory->getCName() 
          << std::endl;

    return true;
}

FactoryBase *FactoryControllerBase::findFactory(const Char8 *szName)
{
	FactoryMapConstIt factIt;

    if(szName == NULL)
        return NULL;

    factIt = _mFactoryMap.find(IDStringLink(szName));

    return ((factIt == _mFactoryMap.end()) ? NULL : (*factIt).second);
}

OSG_END_NAMESPACE
