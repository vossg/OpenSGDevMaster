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

/*! Set the mapper to use for mapping field container ids. */
inline
void FieldContainerFactoryBase::setMapper(ContainerIdMapper *pMapper)
{
    _pMapper = pMapper;
}

inline
UInt32 FieldContainerFactoryBase::getNumLiveContainers(void) const
{
    UInt32 returnValue = 0;

    _pStoreLock->acquire();

    returnValue = _containerStore.size();

    _pStoreLock->release();

    return returnValue;
}

inline
UInt32 FieldContainerFactoryBase::getNumTotalContainers(void) const
{
    UInt32 returnValue = 0;

    _pStoreLock->acquire();

    returnValue = _nextContainerId;

    _pStoreLock->release();

    return returnValue;
}

inline
FieldContainerFactoryBase::ContainerPtr 
    FieldContainerFactoryBase::getContainer(UInt32 uiContainerId) const
{
    ContainerPtr returnValue = NULL;

    _pStoreLock->acquire();

    ContainerStoreConstIt sI = _containerStore.find(uiContainerId);

    if(sI != _containerStore.end())
    {
#ifdef OSG_MT_CPTR_ASPECT
        returnValue = (*sI).second->getPtr();
#else
        returnValue = (*sI).second;
#endif
    }

    _pStoreLock->release();

    return returnValue;
}

inline
FieldContainerFactoryBase::ContainerHandlerP
    FieldContainerFactoryBase::getContainerHandler(UInt32 uiContainerId) const
{
    ContainerHandlerP returnValue = NULL;

    _pStoreLock->acquire();

    ContainerStoreConstIt sI = _containerStore.find(uiContainerId);

    if(sI != _containerStore.end())
    {
        returnValue = (*sI).second;
    }

    _pStoreLock->release();

    return returnValue;
}

/*! Get the container for the given id remapped using the active field 
  container mapper.
    \param uiContainerId  The container id to look up.
    \return Field container found after mapping.  If no mapper is active, 
  results in standard getContainer lookup.
*/

inline
FieldContainerFactoryBase::ContainerPtr 
    FieldContainerFactoryBase::getMappedContainer(UInt32 uiContainerId) const
{
    if(_pMapper != NULL)
    {
        return getContainer(_pMapper->map(uiContainerId));
    }
    else
    {
        return getContainer(uiContainerId);
    }
}

/*! Lock the container store to allow iteration over it.
    \warning This makes it impossible to create new containers,
             be sure you know what you are doing!
 */
inline
void FieldContainerFactoryBase::lockStore(void)
{
    _pStoreLock->acquire();
}

/*! Unlock the container store.
    \warning Be sure you know what you are doing!
 */
inline
void FieldContainerFactoryBase::unlockStore(void)
{
    _pStoreLock->release();
}

/*! Returns a begin iterator over the container storage.
    The container storage should be locked with lockStore before
    iterating over it.
*/
inline
FieldContainerFactoryBase::ContainerStoreConstIt
FieldContainerFactoryBase::beginStore(void) const
{
    return _containerStore.begin();
}

/*! Returns an end iterator over the container storage.
    The container storage should be locked with lockStore before
    iterating over it.
*/
inline
FieldContainerFactoryBase::ContainerStoreConstIt
FieldContainerFactoryBase::endStore(void) const
{
    return _containerStore.end();
}

OSG_END_NAMESPACE

