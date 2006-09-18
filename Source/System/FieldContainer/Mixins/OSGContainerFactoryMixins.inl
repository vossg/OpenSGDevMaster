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

OSG_BEGIN_NAMESPACE

template <class DescT> inline
FactoryMixinHead<DescT>::FactoryMixinHead(const Char8 *szFactoryName) :
     Inherited   (szFactoryName),

    _bInitialized(        false)
{
    FactoryController::the()->registerFactory(this);
}

template <class DescT> inline
FactoryMixinHead<DescT>::~FactoryMixinHead(void)
{
}

template <class DescT> inline
bool FactoryMixinHead<DescT>::initialize(void)
{
    return true;
}

template <class DescT> inline
bool FactoryMixinHead<DescT>::terminate(void)
{
    _bInitialized = false;

    return true;
}

template <class DescT> inline
bool  FactoryMixinHead<DescT>::initializeFactoryPost(void)
{
    return true;
}

template <class DescT> inline
bool  FactoryMixinHead<DescT>::initializePendingElementsFactoryPost(void)
{
    return true;
}


template <class ParentT> inline
UInt16 ContainerFactoryMixin<ParentT>::findGroupId(const Char8  *szName) const
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

template <class ParentT> inline
const Char8 *ContainerFactoryMixin<ParentT>::findGroupName(
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

template <class ParentT> inline
UInt32 ContainerFactoryMixin<ParentT>::getNumGroups(void) const
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

template <class ParentT> inline
void ContainerFactoryMixin<ParentT>::registerType(ContainerType *pType)
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

template <class ParentT> inline
UInt16 ContainerFactoryMixin<ParentT>::registerGroup(const Char8 *szGroupName)
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

template <class ParentT> inline
typename ContainerFactoryMixin<ParentT>::ContainerType *
    ContainerFactoryMixin<ParentT>::findType(UInt32 uiTypeId) const
{
    TypeIdMapConstIt  typeIt;
    ContainerType    *pType = NULL;

    typeIt = _mTypeIdMap.find(uiTypeId);

    pType   = (typeIt == _mTypeIdMap.end()) ? NULL : (*typeIt).second;

    return pType;
}

template <class ParentT> inline
typename ContainerFactoryMixin<ParentT>::ContainerType *
    ContainerFactoryMixin<ParentT>::findType(const Char8 *szName) const
{
    TypeNameMapCnstIt  typeIt;
    ContainerType     *pType = NULL;

    typeIt = _mTypeNameMap.find(IDStringLink(szName));

    pType  = (typeIt == _mTypeNameMap.end()) ? NULL : (*typeIt).second;

    return pType;
}

template <class ParentT> inline
UInt32 ContainerFactoryMixin<ParentT>::getNumTypes(void) const
{
    return _mTypeNameMap.size();
}


template <class ParentT> inline
ContainerFactoryMixin<ParentT>::ContainerFactoryMixin(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),

    _mTypeIdMap     (             ),
    _mTypeNameMap   (             ),

    _mGroupMap      (             ),

    _vUnitTypesStore(             ),
    _vPostUnitTypes (             )

#ifndef OSG_WINCE
    ,_pLock          (         NULL)
#endif
{
}

template <class ParentT> inline
ContainerFactoryMixin<ParentT>::~ContainerFactoryMixin(void)
{
}

template <class FactoryDescT> inline
bool ContainerFactoryMixin<FactoryDescT>::initializePendingElements(void)
{
    bool           returnValue = true;
    ContainerType *pType       = NULL;

    returnValue = Inherited::initializePendingElements();

    if(this->_bInitialized == false || returnValue == false)
        return false;

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


template <class ParentT> inline
bool ContainerFactoryMixin<ParentT>::initialize(void)
{
    if(this->_bInitialized == true)
        return true;

    this->_bInitialized = Inherited::initialize();

    if(this->_bInitialized == false)
        return false;

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

template <class ParentT> inline
bool ContainerFactoryMixin<ParentT>::initializePendingElementsFactoryPost(void)
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

template <class ParentT> inline
bool ContainerFactoryMixin<ParentT>::initializeFactoryPost(void)
{
    return this->initializePendingElementsFactoryPost();
}


template <class ParentT> inline
bool ContainerFactoryMixin<ParentT>::terminate(void)
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

    return Inherited::terminate();
}


template <class ParentT> inline
typename PrototypeFactoryMixin<ParentT>::ContainerPtr
    PrototypeFactoryMixin<ParentT>::createContainer(const Char8 *szName)
{
    ContainerPtr returnValue = Desc::getNilPtr();

    const ContainerType *pType = Inherited::findType(szName);

    if(pType != NULL)
    {
        returnValue = pType->createContainer();
    }

    return returnValue;
}

#ifdef OSG_1_COMPAT
template <class ParentT> inline
typename PrototypeFactoryMixin<ParentT>::ContainerPtr
    PrototypeFactoryMixin<ParentT>::createFieldContainer(const Char8 *szName)
{
    return createContainer(szName);
}
#endif

template <class ParentT> inline
PrototypeFactoryMixin<ParentT>::PrototypeFactoryMixin(
    const Char8 *szFactoryName) :

    Inherited(szFactoryName)
{
}

template <class ParentT> inline
PrototypeFactoryMixin<ParentT>::~PrototypeFactoryMixin(void)
{
}

template <class ParentT> inline
bool PrototypeFactoryMixin<ParentT>::initialize(void)
{
    return Inherited::initialize();
}

template <class ParentT> inline
bool PrototypeFactoryMixin<ParentT>::terminate(void)
{
    return Inherited::terminate();
}

template <class ParentT> inline
bool PrototypeFactoryMixin<ParentT>::initializeFactoryPost()
{
    return Inherited::initializeFactoryPost();
}




/*! Register a new container with the store.
The container is added to the store and its index in the store (the fcid)
is returned.
   \param pContainer  The new container to add.  Must not be NullFC
   \return The index in the store.
*/
template <class ParentT> inline
UInt32 ContainerStoreFactoryMixin<ParentT>::registerContainer(
    const ContainerPtr &pContainer)
{
    UInt32 returnValue = 0;

#ifndef OSG_WINCE
    _pStoreLock->acquire();
#endif

    _vContainerStore.push_back(pContainer);

    returnValue = _vContainerStore.size() - 1;

#ifndef OSG_WINCE
    _pStoreLock->release();
#endif

    return returnValue;
}

/*! Unregister a field container with the store.
   \param uiContainerId  The id in the store to remove.
          If id is out of range, ignore.
   \return true if compiled debug and out of range otherwise false.
*/
template <class ParentT> inline
bool ContainerStoreFactoryMixin<ParentT>::deregisterContainer(
    const UInt32 uiContainerId)
{
    bool returnValue = false;

#ifndef OSG_WINCE
    _pStoreLock->acquire();
#endif

    if(uiContainerId < _vContainerStore.size())
    {
        _vContainerStore[uiContainerId] = Desc::getNilPtr();
    }
#ifdef OSG_DEBUG
    else
    {
        FWARNING(("FieldContainerFactory::unregisterFieldContainer:"
                  "id %d inconsistent with store size %d!\n",
                uiContainerId,
                _vContainerStore.size()));
        returnValue = true;
    }
#endif

#ifndef OSG_WINCE
    _pStoreLock->release();
#endif

    return returnValue;
}

/*! Return container from the store with the given index (fcid).
   \param uiContainerId  Id of the container to lookup.
   \return Ptr to the container found.
           Null if index is out of bounds or found container is Null.
*/
template <class ParentT> inline
typename ContainerStoreFactoryMixin<ParentT>::ContainerPtr
    ContainerStoreFactoryMixin<ParentT>::getContainer(
        UInt32 uiContainerId) const
{
    ContainerPtr returnValue = Desc::getNilPtr();

#ifndef OSG_WINCE
    _pStoreLock->acquire();
#endif

    if(uiContainerId < _vContainerStore.size())
    {
        returnValue = _vContainerStore[uiContainerId];
    }

#ifndef OSG_WINCE
    _pStoreLock->release();
#endif

    return returnValue;
}

template <class ParentT> inline
typename ContainerStoreFactoryMixin<ParentT>::ContainerPtr
    ContainerStoreFactoryMixin<ParentT>::getMappedContainer(
        UInt32 uiContainerId) const
{
    return Desc::getNilPtr();
}

template <class ParentT> inline
const typename ContainerStoreFactoryMixin<ParentT>::ContainerStore &
    ContainerStoreFactoryMixin<ParentT>::getContainerStore(void)
{
    return _vContainerStore;
}

template <class ParentT> inline
ContainerStoreFactoryMixin<ParentT>::ContainerStoreFactoryMixin(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),

#ifndef OSG_WINCE
    _pStoreLock     (NULL         ),
#endif
    _vContainerStore(             )

{
}

template <class ParentT> inline
ContainerStoreFactoryMixin<ParentT>::~ContainerStoreFactoryMixin(void)
{
}


template <class ParentT> inline
bool ContainerStoreFactoryMixin<ParentT>::initialize(void)
{
    if(this->_bInitialized == true)
        return true;

#ifndef OSG_WINCE
    _pStoreLock = ThreadManager::the()->getLock(Desc::getStoreLockName());

    addRef(_pStoreLock);

    PINFO << "Got store lock " << _pStoreLock << std::endl;

    if(_pStoreLock == NULL)
    {
        return false;
    }
    else
    {
#endif
        return Inherited::initialize();
#ifndef OSG_WINCE
    }
#endif
}

template <class ParentT> inline
bool ContainerStoreFactoryMixin<ParentT>::terminate (void)
{
    bool returnValue = Inherited::terminate();

#ifndef OSG_WINCE
    subRefP(_pStoreLock);
#endif

    this->_bInitialized = false;

    return returnValue;
}

template <class ParentT> inline
bool ContainerStoreFactoryMixin<ParentT>::initializeFactoryPost(void)
{
    return Inherited::initializeFactoryPost();
}




template <class ParentT> inline
UInt32 HandledContainerStoreFactoryMixin<ParentT>::registerContainer(
    const ContainerPtr &pContainer)
{
    UInt32 returnValue = 0;

    _pStoreLock->acquire();

    ContainerHandlerP pHandler = Desc::getHandler(pContainer);

    _vContainerStore.push_back(pHandler);

    returnValue = _vContainerStore.size() - 1;

    _pStoreLock->release();

    return returnValue;
}

template <class ParentT> inline
bool HandledContainerStoreFactoryMixin<ParentT>::deregisterContainer(
    const UInt32 uiContainerId)
{
    bool returnValue = false;

    _pStoreLock->acquire();

    if(uiContainerId < _vContainerStore.size())
    {
        _vContainerStore[uiContainerId] = NULL;
    }
#ifdef OSG_DEBUG
    else
    {
        FWARNING(("FieldContainerFactory::unregisterFieldContainer:"
                  "id %d inconsistent with store size %d!\n",
                uiContainerId,
                _vContainerStore.size()));
        returnValue = true;
    }
#endif

    _pStoreLock->release();

    return returnValue;
}

template <class ParentT> inline
typename HandledContainerStoreFactoryMixin<ParentT>::ContainerPtr
    HandledContainerStoreFactoryMixin<ParentT>::getContainer(
        UInt32 uiContainerId) const
{
    ContainerPtr returnValue = Desc::getNilPtr();

    _pStoreLock->acquire();

    if(uiContainerId < _vContainerStore.size())
    {
        if(_vContainerStore[uiContainerId] != NULL)
        {
            returnValue = _vContainerStore[uiContainerId]->getPtr();
        }
    }

    _pStoreLock->release();

    return returnValue;
}

template <class ParentT> inline
typename HandledContainerStoreFactoryMixin<ParentT>::ContainerHandlerP
    HandledContainerStoreFactoryMixin<ParentT>::getContainerHandler(
        UInt32 uiContainerId) const
{
    ContainerHandlerP returnValue = NULL;

    _pStoreLock->acquire();

    if(uiContainerId < _vContainerStore.size())
    {
        returnValue = _vContainerStore[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

template <class ParentT> inline
typename HandledContainerStoreFactoryMixin<ParentT>::ContainerPtr
    HandledContainerStoreFactoryMixin<ParentT>::getMappedContainer(
        UInt32 uiContainerId) const
{
    return Desc::getNilPtr();
}

#if 0
template <class ParentT> inline
const typename HandledContainerStoreFactoryMixin<ParentT>::ContainerStore &
    HandledContainerStoreFactoryMixin<ParentT>::getContainerStore(void)
{
    return _vContainerStore;
}
#endif

template <class ParentT> inline
HandledContainerStoreFactoryMixin<ParentT>::HandledContainerStoreFactoryMixin(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),

    _pStoreLock     (NULL         ),
    _vContainerStore(             )

{
}

template <class ParentT> inline
HandledContainerStoreFactoryMixin<ParentT>::~HandledContainerStoreFactoryMixin(
    void)
{
}


template <class ParentT> inline
bool HandledContainerStoreFactoryMixin<ParentT>::initialize(void)
{
    if(this->_bInitialized == true)
        return true;

    _pStoreLock = ThreadManager::the()->getLock(Desc::getStoreLockName());

    addRef(_pStoreLock);

    PINFO << "Got store lock " << _pStoreLock << std::endl;

    if(_pStoreLock == NULL)
    {
        return false;
    }
    else
    {
        return Inherited::initialize();
    }
}

template <class ParentT> inline
bool HandledContainerStoreFactoryMixin<ParentT>::terminate (void)
{
    bool returnValue = Inherited::terminate();

    subRefP(_pStoreLock);

    this->_bInitialized = false;

    return returnValue;
}

template <class ParentT> inline
bool HandledContainerStoreFactoryMixin<ParentT>::initializeFactoryPost(void)
{
    return Inherited::initializeFactoryPost();
}


OSG_END_NAMESPACE

#define OSGCONTAINERFACTORYMIXINS_INLINE_CVSID "@(#)$Id$"

