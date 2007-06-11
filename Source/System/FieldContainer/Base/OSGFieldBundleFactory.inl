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
void FieldBundleFactoryBase::setMapper(ContainerIdMapper *pMapper)
{
    _pMapper = pMapper;
}

inline
UInt32 FieldBundleFactoryBase::getNumContainers(void) const
{
    UInt32 returnValue = 0;

#ifndef OSG_WINCE
    _pStoreLock->acquire();
#endif

    returnValue = _vContainerStore.size();

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

inline
FieldBundleFactoryBase::ContainerPtr
    FieldBundleFactoryBase::getContainer(UInt32 uiContainerId) const
{
    ContainerPtr returnValue = NULL;

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

inline
FieldBundleFactoryBase::ContainerPtr
    FieldBundleFactoryBase::getMappedContainer(UInt32 uiContainerId) const
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

/*! Register a new container with the store.
The container is added to the store and its index in the store (the fcid)
is returned.
   \param pContainer  The new container to add.  Must not be NullFC
   \return The index in the store.
*/

inline
UInt32 FieldBundleFactoryBase::registerContainer(
    const ContainerPtr &pContainer)
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(pContainer);
#endif

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
inline
bool FieldBundleFactoryBase::deregisterContainer(const UInt32 uiContainerId)
{
    bool returnValue = false;

#ifndef OSG_WINCE
    _pStoreLock->acquire();
#endif

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

#ifndef OSG_WINCE
    _pStoreLock->release();
#endif

    return returnValue;
}

OSG_END_NAMESPACE
