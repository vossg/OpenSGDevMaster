/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGClusterException.h"
#include "OSGFieldDescriptionBase.h"
#include "OSGRemoteAspect.h"
#include "OSGLog.h"
#include "OSGWindow.h"
#include "OSGMaterial.h"
#include "OSGConnection.h"
#include "OSGStatCollector.h"

#include <map>

#define OSG_REMOTE_ASPECT_SILENT 1

OSG_USING_NAMESPACE

/** \class OSG::RemoteAspect
 *  \ingroup GrpSystemCluster
 *  \brief Remote aspect controll class
 *
 * The RemoteAspecet is used to synchronize changes of FieldContainers
 * with remote hosts. All changes stored in the current change list
 * are send to a Connection.
 *
 * It is possible to send changes in both directions. 
 *
 **/

RemoteAspect::FieldFilter  RemoteAspect::_fieldFilter;

StatElemDesc<StatTimeElem> RemoteAspect::statSyncTime
    ("remoteSyncTime", "time for scenegraph distribution");

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

RemoteAspect::RemoteAspect(UInt32 aspectId) :
    _aspectId(aspectId),

    _localFC(),
    _remoteFC(),
    _localType(),

    _sentFC(),
    _receivedFC(),
    _mappedFC(),
    _mappedType(),

    _createdFunctors(),
    _destroyedFunctors(),
    _changedFunctors(),
    _statistics(NULL)
{
}

/*! Destructor
 */
RemoteAspect::~RemoteAspect(void)
{
    FieldContainerFactoryBase *pFactory = FieldContainerFactory::the();
    IdSetT::iterator           i;

    FieldContainer            *fcPtr = NULL;

    // subRef received field container
    for(i = _receivedFC.begin(); i != _receivedFC.end(); i++)
    {
        fcPtr = pFactory->getContainer(*i);

        if(fcPtr != NULL)
        {
            callDestroyed(fcPtr);

            fcPtr->resolveLinks();
        }
    }

    // subRef received field container
    for(i = _receivedFC.begin(); i != _receivedFC.end(); i++)
    {
        fcPtr = pFactory->getContainer(*i);

        if(fcPtr != NULL)
        {
            do
            {
                fcPtr->subReferenceUnresolved();
                fcPtr = pFactory->getContainer(*i);

            } while(fcPtr != NULL);
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                          Remote aspect functionaliy                     */

/*! \e receiveSync reads changes from the given connection and
 *  applies them to the current thread aspect.
 *  Functors for registered types are called, if they occur in the
 *  sync stream.
 * 
 *  \see registerCreated registerChanged registerDeleted
 */

void RemoteAspect::receiveSync(Connection &connection, bool applyToChangelist)
{
    bool                              finish    = false;
    UInt8                             cmd;
    FieldContainerFactoryBase        *fcFactory = FieldContainerFactory::the();
    FieldContainerVector              newContainers;
    RemoteAspectFieldContainerMapper  mapper;
    ChangeList                       *pChangeList =
        Thread::getCurrentChangeList();

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->start();
    }

    connection.selectChannel();
    connection.getValue(_remoteAspectId);

    // register mapper into factory
    mapper._remoteAspect = this;

    fcFactory->setMapper(&mapper);

    do
    {
        connection.getValue(cmd);

        switch(cmd)
        {
            case SYNCENDED:
            {
                finish = true;

#ifndef OSG_REMOTE_ASPECT_SILENT
                SLOG << "Receive SYNCENDED\n";
#endif
            }
            break;

            case NEWTYPE:
            {
                receiveNewType(connection, fcFactory);
            }
            break;
            
            case CREATED:
            {
                receiveCreated(connection, fcFactory, newContainers);
            }
            break;

            case CHANGED:
            {
                receiveChanged(connection, fcFactory);
            }
            break;

            case ADDREFED:
            {
                receiveAddRefed(connection, fcFactory, pChangeList);
            }
            break;

            case SUBREFED:
            {
                receiveSubRefed(connection, fcFactory, pChangeList);
            }
            break;
            
            case IDMAPPING:
            {
                receiveIdMapping(connection);
            }
            break;
            
            default:
            {
                SFATAL << "Unknown tag:" << Int32(cmd) << std::endl;
                throw RemoteSyncError();
            }
        }
    } 
    while(!finish);

#ifndef OSG_REMOTE_ASPECT_SILENT
    PLOG << std::flush;
#endif

    pChangeList->commitDelayedSubRefs();

#ifdef OSG_DEBUG
    FieldContainerVector::const_iterator fcIt  = newContainers.begin();
    FieldContainerVector::const_iterator fcEnd = newContainers.end  ();

    for(; fcIt != fcEnd; ++fcIt)
    {
        if((*fcIt)->getRefCount() <= 1)
        {
            SWARNING << "New container type '" << (*fcIt)->getType().getName()
                     << "' local id '" << (*fcIt)->getId()
                     << "' remote id '"
                     << static_cast<UInt32>(_remoteFC[(*fcIt)->getId()])
                     << "' dies because of missing ref counts."
                     << std::endl;
        }
    }
#endif // OSG_DEBUG

    if(applyToChangelist)
    {
        commitChanges();
    }
    else
    {
        commitChangesAndClear();
    }

    // unregister mapper into factory
    fcFactory->setMapper(NULL);

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->stop();
    }
}

/*! All changes from changeList are send to the connecteion except 
 *  the fields which are filtered. Filters are used to avoid transmission
 *  of local states. e.g. GL variables. 
 */

void RemoteAspect::sendSync(Connection &connection, ChangeList *changeList)
{
    FieldContainerFactoryBase *fcFactory = FieldContainerFactory::the();

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->start();
    }

    if(!changeList)
    {
        changeList = OSG::Thread::getCurrentChangeList();
    }

    // tell my aspect id
    connection.putValue(_aspectId);

    sendIdMapping(connection);

    ChangeList::ChangedStoreConstIt changedIt  = changeList->beginCreated();
    ChangeList::ChangedStoreConstIt changedEnd = changeList->endCreated  ();

    for(; changedIt != changedEnd; ++changedIt)
    {
        UInt32          localId = (*changedIt)->uiContainerId;
        FieldContainer *fcPtr   = fcFactory->getContainer(localId);

        // fcPtr might be locally destroyed already or
        // cluster local, no need to transmit it
        if((fcPtr  == NULL                                     ) ||
           (0x0000 == (fcPtr->getFieldFlags()->_bNamespaceMask & 
                       FCLocal::Cluster                         ))  )
        {
            continue;
        }

        if((*changedIt)->uiEntryDesc == ContainerChangeEntry::Create)
        {
            sendCreated(connection, fcPtr);
        }
    }

    changedIt  = changeList->begin();
    changedEnd = changeList->end  ();

    for(; changedIt != changedEnd; ++changedIt)
    {
        UInt32          localId = (*changedIt)->uiContainerId;
        FieldContainer *fcPtr   = fcFactory->getContainer(localId);

        // fcPtr might be cluster local, no need to transmit it.
        // but we need to transmit subrefs for locally destroyed container
        // so this test is different from the one above!
        if((fcPtr  != NULL                                      )  &&
           (0x0000 == (fcPtr->getFieldFlags()->_bNamespaceMask &
                       FCLocal::Cluster                         ))   )
        {
            continue;
        }

        if((*changedIt)->uiEntryDesc == ContainerChangeEntry::AddReference)
        {
            sendAddRefed(connection, fcPtr, localId);
        }   
        else if((*changedIt)->uiEntryDesc == ContainerChangeEntry::SubReference)
        {
            sendSubRefed(connection, fcPtr, localId);
        }
        else if((*changedIt)->uiEntryDesc == ContainerChangeEntry::Change &&
                fcPtr                     != NULL                           )
        {
            sendChanged(connection, fcPtr, (*changedIt)->whichField);
        }
    }

    UInt8 cmd = SYNCENDED;
    connection.putValue(cmd);

#ifndef OSG_REMOTE_ASPECT_SILENT
    SLOG << "Send SYNCENDED" << std::endl;
#endif

    // write buffer
    connection.flush();

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->stop();
    }
}

/*! The given functor is called when a create of the specified type
 *  is received.
 *
 *  \see receiveSync
 */

void RemoteAspect::registerCreated(const FieldContainerType &type,
                                   const Functor            &func)
{
    while(type.getId() >= _createdFunctors.size())
    {
        _createdFunctors.push_back(&_defaultCreatedFunction);
    }

    _createdFunctors[type.getId()] = func;
}

/*! The given functor is called when a destroy of the specified type
 *  is received.
 *
 *  \see receiveSync
 */

void RemoteAspect::registerDestroyed(const FieldContainerType &type,
                                     const Functor &func)
{
    while(type.getId() >= _destroyedFunctors.size())
    {
        _destroyedFunctors.push_back(&_defaultDestroyedFunction);
    }

    _destroyedFunctors[type.getId()] = func;
}

/*! The given functor is called when a change of the specified type
 *  is received.
 *
 *  \see receiveSync
 */

void RemoteAspect::registerChanged(const FieldContainerType &type,
                                   const Functor &func)
{
    while(type.getId() >= _changedFunctors.size())
    {
        _changedFunctors.push_back(&_defaultChangedFunction);
    }

    _changedFunctors[type.getId()] = func;
}

/*! add a new field filter. The given fieldmaks will not be transfered
 */

/*-------------------------------------------------------------------------*/
/*                          statistics                                     */

/*! add a new field filter. The given fieldmaks will not be transfered
 */
void RemoteAspect::addFieldFilter(UInt32 typeId, BitVector mask)
{
    _fieldFilter[typeId] |= mask;
}

/*! remove the filter for the given type and mask
 */
void RemoteAspect::subFieldFilter(UInt32 typeId, BitVector mask)
{
    _fieldFilter[typeId] &= ~mask;
}

/*! Set statistics collector
 */

void RemoteAspect::setStatistics(StatCollector *statistics)
{
    OSG::setRefd(_statistics, statistics);
}

/*-------------------------------------------------------------------------*/
/*                        protected helpers                                */

/*! Call created functor for a given FieldContainer
 *
 *  \see registerCreated
 */

bool RemoteAspect::callCreated(FieldContainer * const fcp)
{
    bool    result;
    UInt32  uiFunctorIndex = fcp->getType().getId();

    if(uiFunctorIndex < _createdFunctors.size())
    {
        result = _createdFunctors[uiFunctorIndex](fcp, this);
    }
    else
    {
        result = _defaultCreatedFunction(fcp, this);
    }

    return result;
}

/*! Call destroyed functor for a given FieldContainer
 *
 *  \see registerDestroyed
 */

bool RemoteAspect::callDestroyed(FieldContainer * const fcp)
{
    bool    result;
    UInt32  uiFunctorIndex = fcp->getType().getId();

    if(uiFunctorIndex < _destroyedFunctors.size())
    {
        result = _destroyedFunctors[uiFunctorIndex](fcp, this);
    }
    else
    {
        result = _defaultDestroyedFunction(fcp, this);
    }

    return result;
}

/*! Call changed functor for a given FieldContainer
 *
 *  \see registerChanged
 */

bool RemoteAspect::callChanged(FieldContainer * const fcp)
{
    bool    result;
    UInt32  uiFunctorIndex = fcp->getType().getId();

    if(uiFunctorIndex < _changedFunctors.size())
    {
        result = _changedFunctors[uiFunctorIndex](fcp, this);
    }
    else
    {
        result = _defaultChangedFunction(fcp, this);
    }

    return result;
}

/*-------------------------------------------------------------------------*/
/* Receive Helper Functions                                                */

void RemoteAspect::receiveNewType(Connection                &con,
                                  FieldContainerFactoryBase *fcFactory)
{
    UInt32      remoteTypeId = 0;
    UInt32      localTypeId  = 0;
    std::string typeName;

    con.getValue(remoteTypeId);
    con.getValue(typeName);

    FieldContainerType *fcType = fcFactory->findType(typeName.c_str());

    if(fcType != NULL)
    {
        localTypeId = fcType->getId();

        _localType[remoteTypeId] = localTypeId;
    }
    else
    {
        SWARNING << "Unrecognized remote type '" << typeName
                 << "' remote type id '" << remoteTypeId
                 << "'." << std::endl;
    }

#ifndef OSG_REMOTE_ASPECT_SILENT
    SLOG << "Receive NEWTYPE: type name '" << typeName
         << "' remote type '"              << remoteTypeId
         << "' local type '"               << localTypeId
         << "'\n";
#endif
}

void RemoteAspect::receiveCreated(Connection                &con,
                                  FieldContainerFactoryBase *fcFactory,
                                  FieldContainerVector      &newContainers)
{
    UInt32 remoteTypeId = 0;
    UInt32 localTypeId  = 0;
    UInt32 remoteId     = 0;

    con.getValue(remoteTypeId);
    con.getValue(remoteId);

    LocalTypeMapT::const_iterator  localTypeIt = _localType.find(remoteTypeId);
    FieldContainerType            *fcType      = NULL;
    FieldContainerUnrecPtr         fcPtr       = NULL;

    if(localTypeIt != _localType.end())
    {
        UInt64 fullRemoteId = getFullRemoteId(remoteId);

        if(_localFC.find(fullRemoteId) == _localFC.end())
        {
            localTypeId = localTypeIt->second;
            fcType      = fcFactory->findType(localTypeId);
            fcPtr       = fcType->createContainer();

            // remove this node, when aspect is removed
            _receivedFC.insert(fcPtr->getId());

            // local <-> remote mapping
            _localFC [fullRemoteId  ] = fcPtr->getId();
            _remoteFC[fcPtr->getId()] = fullRemoteId;

            callCreated(fcPtr);

            newContainers.push_back(fcPtr);

#ifndef OSG_REMOTE_ASPECT_SILENT
            SLOG << "Receive CREATED: remote type '" << remoteTypeId
                 << "' local type '"                 << localTypeId
                 << "' remote id '"                  << remoteId
                 << "' local id '"
                 << (fcPtr  != NULL ? fcPtr->getId()     : 0)
                 << "' type name '"
                 << (fcType != NULL ? fcType->getName() : "")
                 << "'\n";
#endif
        }
        else
        {
            SWARNING << "Already created a local container for "
                     << "remote container id '" << remoteId
                     << "'" << std::endl;
        }
    }
    else
    {
        SWARNING << "Unknown (remote) type id '" << remoteTypeId
                 << "' for (remote) container id '" << remoteId
                 << "'" << std::endl;
    }
}

void RemoteAspect::receiveChanged(Connection                &con,
                                  FieldContainerFactoryBase *fcFactory)
{
    UInt32          remoteId  = 0;
    UInt32          localId   = 0;
    BitVector       fieldMask = 0;
    UInt32          len       = 0;
    FieldContainer *fcPtr     = NULL;

    con.getValue(remoteId);
    con.getValue(fieldMask);
    con.getValue(len);

    if(getLocalId(remoteId, localId))
    {
        fcPtr = fcFactory->getContainer(localId);

#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Receive CHANGED: remote id '" << remoteId
             << "' local id '"                 << localId
             << "' mask '0x"
             << std::hex << fieldMask << std::dec
             << "' len '"                      << len
             << "' type name '"
             << (fcPtr != NULL ? fcPtr->getType().getName() : "")
             << "'\n";
#endif

        if(fcPtr == NULL)
        {
            clearFCMapping(localId, remoteId);

            char dummy;

            while(len--)
                con.get(&dummy, 1);
        }
        else
        {
            fcPtr->copyFromBin(con, fieldMask);

            callChanged(fcPtr);
        }
    }
    else
    {
        char dummy;

        SWARNING << "Can not do CHANGED for unknown FC remote id "
                 << remoteId
                 << " skip "
                 << len
                 << " bytes."
                 << std::endl;

        while(len--)
            con.get(&dummy, 1);
    }
}

void RemoteAspect::receiveAddRefed(Connection                &con,
                                   FieldContainerFactoryBase *fcFactory,
                                   ChangeList                *pChangeList)
{
    UInt32          remoteId = 0;
    UInt32          localId  = 0;
    FieldContainer *fcPtr    = NULL;

    con.getValue(remoteId);

    if(getLocalId(remoteId, localId))
    {
        fcPtr = fcFactory->getContainer(localId);

#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Receive ADDREFED: remote id '" << remoteId
             << "' local id '"                  << localId
             << "' type name '"
             << (fcPtr != NULL ? fcPtr->getType().getName() : "")
             << "'\n";
#endif

        if(fcPtr == NULL)
        {
            clearFCMapping(localId, remoteId);
        }
        else
        {
            RecordedRefCountPolicy::addRef(fcPtr);
        }
    }
    else
    {
        SWARNING << "Can not do ADDREFED for unknown FC remote id "
                 << remoteId << std::endl;
    }
}

void RemoteAspect::receiveSubRefed(Connection                &con,
                                   FieldContainerFactoryBase *fcFactory,
                                   ChangeList                *pChangeList)
{
    UInt32          remoteId = 0;
    UInt32          localId  = 0;
    FieldContainer *fcPtr    = NULL;

    con.getValue(remoteId);

    if(getLocalId(remoteId, localId))
    {
        fcPtr = fcFactory->getContainer(localId);

#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Receive SUBREFED: remote id '" << remoteId
             << "' local id '"                  << localId
             << "' type name '"
             << (fcPtr != NULL ? fcPtr->getType().getName() : "")
             << "'\n";
#endif

        if(fcPtr == NULL)
        {
            clearFCMapping(localId, remoteId);
        }
        else
        {
            pChangeList->addDelayedSubRef<RecordedRefCountPolicy>(fcPtr);
        }
    }
    else
    {
        SWARNING << "Can not do SUBREFED for unknown FC remote id "
                 << remoteId << std::endl;
    }
}

void RemoteAspect::receiveIdMapping(Connection &con)
{
    UInt32 remoteId    = 0;
    UInt32 localId     = 0;
    UInt32 localAspect = 0;

    con.getValue(remoteId);
    con.getValue(localAspect);
    con.getValue(localId);

#ifndef OSG_REMOTE_ASPECT_SILENT
    SLOG << "Receive IDMAPPING: remote id '" << remoteId
         << "' local id '"                   << localId
         << "' local aspect '"               << localAspect
         << "'\n";
#endif

    if(localAspect != _aspectId)
    {
        SFATAL << "ID mapping for wrong aspect" << std::endl;
    }

    // local <-> remote mapping
    UInt64 fullRemoteId    = getFullRemoteId(remoteId);
    _localFC[fullRemoteId] = localId;
}

/*-------------------------------------------------------------------------*/
/* Send Helper Functions                                                   */

void RemoteAspect::sendCreated(Connection     &con,
                               FieldContainer *fcPtr)
{
    UInt8  cmd         = 0;
    UInt32 localTypeId = fcPtr->getTypeId();
    UInt32 localId     = fcPtr->getId();

    if(_mappedType.count(localTypeId) == 0)
    {
        _mappedType.insert(localTypeId);

        const std::string &typeName = fcPtr->getType().getName();

#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Send NEWTYPE: type name '" << typeName
             << "' type id '"               << localTypeId
             << "'\n";
#endif

        cmd = NEWTYPE;
        con.putValue(cmd);
        con.putValue(localTypeId);
        con.putValue(typeName);
    }

#ifndef OSG_REMOTE_ASPECT_SILENT
    SLOG << "Send CREATED: type name '" << fcPtr->getType().getName()
         << "' type id '"               << localTypeId
         << "' id '"                    << localId
         << "'\n";
#endif

    cmd = CREATED;
    con.putValue(cmd);
    con.putValue(localTypeId);
    con.putValue(localId);

    // sent container to create
    _sentFC.insert(localId);

    // fc is known by remote
    _mappedFC.insert(localId);
}

void RemoteAspect::sendChanged(Connection     &con,
                               FieldContainer *fcPtr,
                               BitVector       changedMask)
{
    UInt32 localId = fcPtr->getId();

    if(_mappedFC.count(localId) == 0)
    {
#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Container id '" << localId
             << "' type '" << fcPtr->getType().getName()
             << "' is not transmitted, dropping 'CHANGED'"
             << std::endl;
#endif
        return;
    }

    BitVector fieldMask =
        changedMask & fcPtr->getFieldFlags()->_bClusterLocalFlags;

    // apply field filter
    FieldFilter::const_iterator filterI =
        _fieldFilter.find(fcPtr->getType().getId());

    if(filterI != _fieldFilter.end())
    {
        fieldMask &= TypeTraits<BitVector>::BitsSet ^ filterI->second;
    }

    if(fieldMask)
    {
        UInt8  cmd = CHANGED;
        UInt32 len = fcPtr->getBinSize(fieldMask);

#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Send CHANGED: type name '" << fcPtr->getType().getName()
             << "' type id '"               << fcPtr->getType().getId()
             << "' id '"                    << localId
             << "' mask '0x"                << std::hex << fieldMask << std::dec
             << "' len '"                   << len
             << "'\n";
#endif

        con.putValue(cmd      );
        con.putValue(localId  ); // id
        con.putValue(fieldMask); // mask
        con.putValue(len      );

        fcPtr->copyToBin(con, fieldMask);
    }
}

void RemoteAspect::sendAddRefed(Connection     &con,
                                FieldContainer *fcPtr,
                                UInt32          localId)
{
    if(_mappedFC.count(localId) == 0)
    {
#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Container type '"
             << (fcPtr != NULL ? fcPtr->getType().getName() : "")
             << "' id '" << localId
             << "' is not transmitted, dropping 'ADDREF'"
             << std::endl;
#endif
        return;
    }

#ifndef OSG_REMOTE_ASPECT_SILENT
    SLOG << "Send ADDREFD: type name '"
         << (fcPtr != NULL ? fcPtr->getType().getName() : "")
         << "' id '" << localId << "'\n";
#endif

    UInt8 cmd = ADDREFED;
    con.putValue(cmd    );
    con.putValue(localId);
}

void RemoteAspect::sendSubRefed(Connection     &con,
                                FieldContainer *fcPtr,
                                UInt32          localId)
{
    if(_mappedFC.count(localId) == 0)
    {
#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Container type '"
             << (fcPtr != NULL ? fcPtr->getType().getName() : "")
             << "' id '" << localId
             << "' is not transmitted, dropping 'SUBREF'"
             << std::endl;
#endif
        return;
    }

#ifndef OSG_REMOTE_ASPECT_SILENT
    SLOG << "Send SUBREFD: type name '"
         << (fcPtr != NULL ? fcPtr->getType().getName() : "")
         << "' id '" << localId << "'\n";
#endif

    UInt8 cmd = SUBREFED;
    con.putValue(cmd    );
    con.putValue(localId);
}

/*! This is called if a fc was edited that was created by another
    aspect 
 */
void RemoteAspect::sendIdMapping(Connection &con)
{
    UInt8                        cmd         = IDMAPPING;
    UInt32                       remoteId;
    UInt32                       remoteAspect;
    RemoteFCMapT::const_iterator remoteFCIt  = _remoteFC.begin();
    RemoteFCMapT::const_iterator remoteFCEnd = _remoteFC.end  ();

    for(; remoteFCIt != remoteFCEnd; ++remoteFCIt)
    {
        remoteId     = UInt32(remoteFCIt->second);
        remoteAspect = UInt32(remoteFCIt->second >> 32);

#ifndef OSG_REMOTE_ASPECT_SILENT
        SLOG << "Send IDMAPPING: localId '" << remoteFCIt->first
             << "' remoteAspect '"          << remoteAspect
             << "' remoteId '"              << remoteId
             << "'\n";
#endif

        con.putValue(cmd              );
        con.putValue(remoteFCIt->first);
        con.putValue(remoteAspect     );
        con.putValue(remoteId         );

        _mappedFC.insert(remoteFCIt->first);
    }

    _remoteFC.clear();
}

/*-------------------------------------------------------------------------*/
/* Helper Functions                                                        */

/*! clear maps from local id
 */

void RemoteAspect::clearFCMapping(UInt32 localId,UInt32 remoteId)
{
    _mappedFC.erase(localId);
    _sentFC  .erase(localId);

    _receivedFC.erase(localId);

    if(!remoteId)
    {
        RemoteFCMapT::iterator remoteFCI=_remoteFC.find(localId);

        if(remoteFCI != _remoteFC.end())
            remoteId=static_cast<UInt32>(remoteFCI->second);
    }
    
    RemoteFCMapT::iterator remoteFCI=_remoteFC.find(localId);

    if(remoteFCI != _remoteFC.end())
        _remoteFC.erase(remoteFCI);

    LocalFCMapT::iterator localFCI=_localFC.find(remoteId);

    if(localFCI != _localFC.end())
        _localFC.erase(localFCI);
}

/*! get local id mapped from remote id
 */

bool RemoteAspect::getLocalId(UInt32  remoteId,
                              UInt32 &localId)
{
    UInt64                fullRemoteId =  getFullRemoteId(remoteId);
    LocalFCMapT::iterator localFCI     = _localFC.find(fullRemoteId);

    if( localFCI != _localFC.end() )
    {
        localId=localFCI->second;
        return true;
    }
    else
    {
        return false;
    }
}

UInt64 RemoteAspect::getFullRemoteId(UInt32 fcId)
{
    UInt64 remoteId=_remoteAspectId;

    remoteId <<= 32;
    remoteId |=  fcId;

    return remoteId;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#ifdef __sgi
/* fcp is used only if the FDEBUG macro is not removed by the
   proprocessor. Switch off error for unused fcp parameter. */
#pragma set woff 3201
#endif

/*! Default create functor
 */

bool RemoteAspect::_defaultCreatedFunction(FieldContainer * const fcp, 
                                           RemoteAspect   *          )
{
    FDEBUG(("Created:%s %d\n", 
            fcp->getType().getCName(),
            fcp->getId()))

    return true;
}

/*! Default destroyed functor
 */

bool RemoteAspect::_defaultDestroyedFunction(FieldContainer * const fcp,
                                             RemoteAspect   *          )
{
    FDEBUG(("Destroyed:%s %d\n",
            fcp->getType().getCName(),
            fcp->getId()))

    return true;
}

/*! Default changed functor
 */

bool RemoteAspect::_defaultChangedFunction(FieldContainer * const fcp,
                                           RemoteAspect   *          )
{
    FDEBUG(("Changed:%s %d\n", 
            fcp->getType().getCName(),
            fcp->getId()))

    return true;
}

#ifdef __sgi
#pragma reset woff 3201
#endif

/*! Field container id mapper. This mapper mappes remote field 
 *  container id to local ids.
 */

UInt32 RemoteAspectFieldContainerMapper::map(UInt32 uiId)
{
    UInt32                              mappedId;
    RemoteAspect::LocalFCMapT::iterator i;

    i = _remoteAspect->_localFC.find(_remoteAspect->getFullRemoteId(uiId));

    if(i == _remoteAspect->_localFC.end())
    {
        SWARNING << "Can't find container id:" << uiId << std::endl;
        mappedId = 0;
    }
    else
    {
        mappedId = i->second;
    }

    FDEBUG(("Map: %d to %d\n", uiId, mappedId)) 

    return mappedId;
}
