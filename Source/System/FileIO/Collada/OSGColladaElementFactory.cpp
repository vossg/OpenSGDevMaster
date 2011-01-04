/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaElementFactory.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGBaseInitFunctions.h"
#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGSingletonHolder.ins"


OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC)
OSG_SINGLETON_INST(OSG::ColladaElementFactorySingleton, 
                   addPostFactoryExitFunction)
#endif

template class SingletonHolder<OSG::ColladaElementFactorySingleton>;


bool
ColladaElementFactorySingleton::registerElement(
    CreateFunctor createFunc,
    const std::string &elemName, const std::string &profile)
{
    bool retVal = true;
    
    if(profile.empty() == false)
    {
        retVal = doRegisterElement(createFunc, elemName,
                                   _profileHandlerMap[profile]);
    }
    else
    {
        retVal = doRegisterElement(createFunc, elemName,
                                   _defaultHandlerMap         );
    }

    return retVal;
}

bool
ColladaElementFactorySingleton::unregisterElement(
    const std::string &elemName, const std::string &profile)
{
    bool retVal = true;

    if(profile.empty() == false)
    {
        retVal = doUnregisterElement(elemName, _profileHandlerMap[profile]);
    }
    else
    {
        retVal = doUnregisterElement(elemName, _defaultHandlerMap         );
    }

    return retVal;
}

const ColladaElementFactorySingleton::HandlerMap &
ColladaElementFactorySingleton::getDefaultHandlerMap(void) const
{
    return _defaultHandlerMap;
}

ColladaElementFactorySingleton::HandlerMap &
ColladaElementFactorySingleton::editDefaultHandlerMap(void)
{
    return _defaultHandlerMap;
}

const ColladaElementFactorySingleton::ProfileHandlerMap &
ColladaElementFactorySingleton::getProfileHandlerMap(void) const
{
    return _profileHandlerMap;
}

ColladaElementFactorySingleton::ProfileHandlerMap &
ColladaElementFactorySingleton::editProfileHandlerMap(void)
{
    return _profileHandlerMap;
}

const std::string &
ColladaElementFactorySingleton::getDefaultProfile(void) const
{
    return _defaultProfile;
}

void
ColladaElementFactorySingleton::setDefaultProfile(const std::string &profile)
{
    _defaultProfile = profile;
}

ColladaElementFactorySingleton::CreateFunctor
ColladaElementFactorySingleton::getCreateFunc(const std::string &elemName,
                                              const std::string &profile  )
{
    if(profile.empty() == false)
    {
        return doGetCreateFunc(elemName, _profileHandlerMap[profile]        );
    }
    else if(_defaultProfile.empty() == false)
    {
        return doGetCreateFunc(elemName, _profileHandlerMap[_defaultProfile]);
    }
    else
    {
        return doGetCreateFunc(elemName, _defaultHandlerMap                 );
    }
}

ColladaElementTransitPtr
ColladaElementFactorySingleton::create(daeElement        *daeElem,
                                       ColladaGlobal     *global,
                                       const std::string &elemName,
                                       const std::string &profile  )
{
    ColladaElementTransitPtr retVal;
    std::string              lookupName;

    if(elemName.empty() == true)
    {
        if(daeElem->getElementName() != NULL)
        {
            lookupName = daeElem->getElementName();
        }
        else if(daeElem->getTypeName() != NULL)
        {
            lookupName = daeElem->getTypeName();
        }
    }
    else
    {
        lookupName = elemName;
    }

    if(lookupName.empty() == false)
    {
        CreateFunctor createFunc = getCreateFunc(lookupName, profile);

        if(createFunc.empty() == false)
        {
            retVal = createFunc(daeElem, global);
        }

        if(retVal != NULL)
        {
            retVal->getDOMElement()->setUserData(retVal.get());

            global->addElement                  (retVal.get());
        }
        else
        {
            daeString elemName =
                daeElem->getElementName() != NULL ?
                daeElem->getElementName()         : "??";
            daeString typeName =
                daeElem->getTypeName   () != NULL ?
                daeElem->getTypeName   ()         : "??";

            SWARNING << "ColladaElementFactory::create: No element registered "
                     << "for [" << lookupName
                     << "] - elemName [" << elemName
                     << "] typeName [" << typeName
                     << "] id [" << daeElem->typeID() << "]."
                     << std::endl;
        }
    }

    return retVal;
}


bool
ColladaElementFactorySingleton::doRegisterElement(
    CreateFunctor createFunc,
    const std::string &elemName, HandlerMap &handlerMap)
{
    bool         retVal = true;
    HandlerMapIt hIt    = handlerMap.find(elemName);

    if(hIt != handlerMap.end())
    {
        SWARNING << "ColladaElementFactorySingleton::doRegisterElement: "
                 << "elemName [" << elemName << "] already registered."
                 << std::endl;

        retVal = false;
    }
    else
    {
        handlerMap.insert(hIt, HandlerMap::value_type(elemName, createFunc));
    }

    return retVal;
}

bool
ColladaElementFactorySingleton::doUnregisterElement(
    const std::string &elemName, HandlerMap &handlerMap)
{
    bool         retVal = true;
    HandlerMapIt hIt    = handlerMap.find(elemName);

    if(hIt != handlerMap.end())
    {
        handlerMap.erase(hIt);
    }
    else
    {
        SWARNING << "ColladaElemnetFactorySingleton::doUnregisterElement: "
                 << "elemName [" << elemName << "] not registered."
                 << std::endl;

        retVal = false;
    }

    return false;
}

ColladaElementFactorySingleton::CreateFunctor
ColladaElementFactorySingleton::doGetCreateFunc(
    const std::string &elemName, HandlerMap &handlerMap)
{
    CreateFunctor retVal;
    HandlerMapIt  hIt    = handlerMap.find(elemName);

    if(hIt != handlerMap.end())
    {
        retVal = hIt->second;
    }

    return retVal;
}

ColladaElementFactorySingleton::ColladaElementFactorySingleton(void)
    : _defaultProfile   ()
    , _defaultHandlerMap()
    , _profileHandlerMap()
{
}

ColladaElementFactorySingleton::~ColladaElementFactorySingleton(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
