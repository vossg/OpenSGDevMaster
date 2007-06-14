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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILE_CONNECTIONFACTORY

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGConnection.h"
#include "OSGConnectionType.h"
#include "OSGConnectionFactory.h"
#include "OSGBaseInitFunctions.h"

#include "OSGSingletonHolder.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(ConnectionFactoryBase)

template class SingletonHolder<ConnectionFactoryBase>;


/** \class OSG::ConnectionFactory
 *  \ingroup GrpBaseNetwork
 *
 * The ConnectionFactory knows all types of connections by name. 
 * A new connection object could be crated by calling 
 * <PRE>
 * Connection *c = ConnectionFactory::the().create("Multicast");
 * if(!c)
 * {
 *     SLOG << "Unknown connection:";
 * }
 * </PRE>
 *
 * Each connection type must be registered to the factory. This is done
 * by static initialisation. The following example shows registration
 * of the Multicast connection.
 *
 * <PRE>
 * ConnectionType MulticastConnection::_type(&MulticastConnection::create,
                                             "Multicast");
 * </PRE>
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor documentation
 */
ConnectionFactoryBase::ConnectionFactoryBase(void) :
    _groupMap(),
    _pointMap()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
ConnectionFactoryBase::~ConnectionFactoryBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                      public interface                                   */

/*! create group connection by name
 */
GroupConnection *ConnectionFactoryBase::createGroup(const std::string &name)
{
    TypeMap::iterator i=_groupMap.find(name);
    if(i == _groupMap.end())
        return NULL;
    else
        return i->second->createGroup();
}

/*! create point connection by name
 */
PointConnection *ConnectionFactoryBase::createPoint(const std::string &name)
{
    TypeMap::iterator i=_pointMap.find(name);
    if(i == _pointMap.end())
        return NULL;
    else
        return i->second->createPoint();
}

/*-------------------------------------------------------------------------*/
/*                      protected interface                                */

/*! add new group type
 */
void ConnectionFactoryBase::addGroupType(ConnectionType *type)
{
    _groupMap[type->getName()]=type;
    SINFO << "Group Connection type " << type->getName() 
          << " added" << std::endl;
}

/*! add new point type
 */
void ConnectionFactoryBase::addPointType(ConnectionType *type)
{
    _pointMap[type->getName()]=type;
    SINFO << "Point Connection type " << type->getName() 
          << " added" << std::endl;
}
 
/*! remove point type
 */
void ConnectionFactoryBase::subPointType(ConnectionType *type)
{
    TypeMap::iterator i=_pointMap.find(type->getName());
    if(i != _pointMap.end() && i->second == type)
        _pointMap.erase(i);

    if(GlobalSystemState != Shutdown)
    {
        SINFO << "Point connection type " << type->getName() 
              << " removed" << std::endl;
    }
}

/*! remove group type
 */
void ConnectionFactoryBase::subGroupType(ConnectionType *type)
{
    TypeMap::iterator i=_groupMap.find(type->getName());

    if(i != _groupMap.end() && i->second == type)
        _groupMap.erase(i);

    if(GlobalSystemState != Shutdown)
    {
        SINFO << "Group connection type " << type->getName() 
              << " removed" << std::endl;
    }
}

OSG_END_NAMESPACE
