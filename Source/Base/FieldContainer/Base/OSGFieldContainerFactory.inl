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
UInt32 FieldContainerFactoryBase::getNumContainers(void) const
{
    UInt32 returnValue = 0;

    _pStoreLock->acquire();

    returnValue = _vContainerStore.size();

    _pStoreLock->release();

    return returnValue;
}

inline
FieldContainerFactoryBase::ContainerPtr 
    FieldContainerFactoryBase::getContainer(UInt32 uiContainerId) const
{
    ContainerPtr returnValue = NULL;

    _pStoreLock->acquire();

    if(uiContainerId < _vContainerStore.size())
    {
        if(_vContainerStore[uiContainerId] != NULL)
        {
#ifdef OSG_MT_CPTR_ASPECT
            returnValue = _vContainerStore[uiContainerId]->getPtr();
#else
            returnValue = _vContainerStore[uiContainerId];
#endif
        }
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

    if(uiContainerId < _vContainerStore.size())
    {
        returnValue = _vContainerStore[uiContainerId];
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


inline
bool FieldContainerFactoryBase::deregisterContainer(const UInt32 uiContainerId)
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
                  "id %d inconsistent with store size %"PRISize"!\n",
                uiContainerId,
                _vContainerStore.size()));
        returnValue = true;
    }
#endif

    _pStoreLock->release();

    return returnValue;
}

OSG_END_NAMESPACE

