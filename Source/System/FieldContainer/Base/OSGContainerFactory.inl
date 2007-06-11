/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifdef OSG_ENABLE_VALGRIND_CHECKS
#include <valgrind/memcheck.h>
#endif


OSG_BEGIN_NAMESPACE

/*! Attempt to find the id of the group with the given name.
* \param  szName  Name of group to lookup.
* \return Returns id if found, else returns 0.
* \bug t64 When 0 is returned and immediately passed to findGroupName we don't
       get the same thing back.
*      ie.  findGroupName(findGroupId("not there")) != "not there"
*/

template <class DescT> inline
UInt16 ContainerFactory<DescT>::findGroupId(const Char8  *szName) const
{
    UInt16          returnValue = 0;
    GroupMapConstIt gIt;

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->acquire();
#endif

    gIt         = _mGroupMap.find(IDStringLink(szName));

    returnValue = ((gIt == _mGroupMap.end()) ? 0 : (*gIt).second);

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->release();
#endif

    return returnValue;
}

/*! Attempt to find name of the group with the given id.
* \param  uiGroupId  Id of the group to lookup.
* \return Pointer to string of name.  If not found, returns NULL.
*/
template <class DescT> inline
const Char8 *ContainerFactory<DescT>::findGroupName(
    UInt16 uiGroupId) const
{
    const Char8 *returnValue = NULL;

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->acquire();
#endif

    GroupMap::const_iterator gIt  = _mGroupMap.begin();
    GroupMap::const_iterator gEnd = _mGroupMap.end  ();

    while(gIt != gEnd)
    {
        if((*gIt).second == uiGroupId)
            returnValue = (*gIt).first.str();

        ++gIt;
    }

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->release();
#endif

    return returnValue;
}

/*! Return the number of groups that the factory knows about. */
template <class DescT> inline
UInt32 ContainerFactory<DescT>::getNumGroups(void) const
{
    UInt32 returnValue;

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->acquire();
#endif

    returnValue = _mGroupMap.size();

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->release();
#endif

    return returnValue;
}

template <class DescT> inline
void ContainerFactory<DescT>::registerType(ContainerType *pType)
{
    if(pType == NULL)
        return;

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->acquire();
#endif

    _vUnitTypesStore.push_back(pType);

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->release();
#endif
}

/*! Register a new group name with the factory.
* \param szGroupName  The new group name to register.
* \return Returns id of the (new) group.
* \postcond If already registered, just returns the id without updating the map.
*/
template <class DescT> inline
UInt16 ContainerFactory<DescT>::registerGroup(const Char8 *szGroupName)
{
    UInt16 returnValue;

    if(szGroupName == NULL || *szGroupName == '\0')
    {
        SWARNING << "Group without name" << std::endl;
        return 0;
    }

    returnValue = findGroupId(szGroupName);

    if(returnValue == 0)
    {
#ifndef OSG_WINCE
        if(_pLock != NULL)
            _pLock->acquire();
#endif

        returnValue                           = _mGroupMap.size() + 1;

        _mGroupMap[IDStringLink(szGroupName)] = returnValue;

#ifndef OSG_WINCE
        if(_pLock != NULL)
            _pLock->release();
#endif
    }

    return returnValue;
}

template <class DescT> inline
typename ContainerFactory<DescT>::ContainerType *
    ContainerFactory<DescT>::findType(UInt32 uiTypeId) const
{
    TypeIdMapConstIt  typeIt;
    ContainerType    *pType = NULL;

    typeIt = _mTypeIdMap.find(uiTypeId);

    pType   = (typeIt == _mTypeIdMap.end()) ? NULL : (*typeIt).second;

    return pType;
}

template <class DescT> inline
typename ContainerFactory<DescT>::ContainerType *
    ContainerFactory<DescT>::findType(const Char8 *szName) const
{
    TypeNameMapCnstIt  typeIt;
    ContainerType     *pType = NULL;

    typeIt = _mTypeNameMap.find(IDStringLink(szName));

    pType  = (typeIt == _mTypeNameMap.end()) ? NULL : (*typeIt).second;

    return pType;
}

template <class DescT> inline
UInt32 ContainerFactory<DescT>::getNumTypes(void) const
{
    return _mTypeNameMap.size();
}

template <class DescT> inline
typename ContainerFactory<DescT>::ContainerPtr
    ContainerFactory<DescT>::createContainer(const Char8 *szName)
{
    ContainerPtr returnValue = NULL;

    const ContainerType *pType = Self::findType(szName);

    if(pType != NULL)
    {
        returnValue = pType->createContainer();
    }

    return returnValue;
}

#ifdef OSG_1_COMPAT
template <class DescT> inline
typename ContainerFactory<DescT>::ContainerPtr
    ContainerFactory<DescT>::createFieldContainer(const Char8 *szName)
{
    return createContainer(szName);
}
#endif

template <class DescT> inline
ContainerFactory<DescT>::ContainerFactory(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),

    _bInitialized   (        false),
    _mTypeIdMap     (             ),
    _mTypeNameMap   (             ),

    _mGroupMap      (             ),

    _vUnitTypesStore(             ),
    _vPostUnitTypes (             )

#ifndef OSG_WINCE
    ,_pLock          (         NULL)
#endif
{
    FactoryController::the()->registerFactory(this);
}

template <class DescT> inline
ContainerFactory<DescT>::~ContainerFactory(void)
{
}

template <class FactoryDescT> inline
bool ContainerFactory<FactoryDescT>::initializePendingElements(void)
{
    bool           returnValue = true;
    ContainerType *pType       = NULL;

    PINFO << this->_szName.str() << " init pending types" << std::endl;

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->acquire();
#endif

    UninitTypeStoreIt uninitIt  = _vUnitTypesStore.begin();

    while(uninitIt != _vUnitTypesStore.end())
    {
        pType = *uninitIt;

        if(pType->isInitialized() == true)
        {
            uninitIt = _vUnitTypesStore.erase(uninitIt);

            _mTypeIdMap  [pType->getId()                  ] = pType;
            _mTypeNameMap[IDStringLink(pType->getCName()) ] = pType;

            _vPostUnitTypes.push_back(pType);
        }
        else
        {
            if(pType->initialize() == true)
            {
                uninitIt = _vUnitTypesStore.erase(uninitIt);

                _mTypeIdMap  [pType->getId()                  ] = pType;
                _mTypeNameMap[IDStringLink(pType->getCName()) ] = pType;

                _vPostUnitTypes.push_back(pType);
            }
            else
            {
                returnValue = false;

                uninitIt++;
            }
        }
    }

#ifndef OSG_WINCE
    if(_pLock != NULL)
        _pLock->release();
#endif

    PINFO << "("
             << returnValue
             << "|"
             << _vUnitTypesStore.size()
             << "|"
             << _mTypeIdMap.size()
             << ")"
             << std::endl;

    return returnValue;
}


template <class DescT> inline
bool ContainerFactory<DescT>::initialize(void)
{
    if(this->_bInitialized == true)
        return true;


    PINFO << "init singleton " << this->_szName.str() << std::endl;

#ifndef OSG_WINCE
    _pLock   =
        ThreadManager::the()->getLock(Desc::getContainerFactoryLockName());

    addRef(_pLock);

    PINFO << "Got map   lock " << _pLock   << std::endl;

    this->_bInitialized = (_pLock != NULL);
#endif

    if(this->_bInitialized == false)
        return false;

    this->_bInitialized = this->initializePendingElements();

    return this->_bInitialized;
}

template <class DescT> inline
bool ContainerFactory<DescT>::initializePendingElementsFactoryPost(void)
{
    UninitTypeStoreIt uninitIt  = _vPostUnitTypes.begin();

    while(uninitIt != _vPostUnitTypes.end())
    {
        (*uninitIt)->initialize(TypeBase::FactoryPost);

        ++uninitIt;
    }

    _vPostUnitTypes.clear();

    return true;
}

template <class DescT> inline
bool ContainerFactory<DescT>::initializeFactoryPost(void)
{
    return this->initializePendingElementsFactoryPost();
}


template <class DescT> inline
bool ContainerFactory<DescT>::terminate(void)
{
    SINFO << "terminate singleton FieldContainerFactory" << std::endl;

    TypeIdMapIt      typeIt  = _mTypeIdMap.begin();
    TypeIdMapConstIt typeEnd = _mTypeIdMap.end  ();

    while(typeIt != typeEnd)
    {
        (*typeIt).second->terminate();

        ++typeIt;
    }

#ifndef OSG_WINCE
    subRef(_pLock);
#endif

    _bInitialized = false;
    
    return true;
}



OSG_END_NAMESPACE


