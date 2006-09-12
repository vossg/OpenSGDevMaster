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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGConnection.h"
#include "OSGConnectionType.h"
#include "OSGConnectionFactory.h"
#include "OSGBaseInitFunctions.h"

OSG_USING_NAMESPACE

/*! \class OSG::ConnectionType
 
    A connection type describes a network connection and provides an
    interface for dynamic connection creation.
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor. A new connection with the given name is registered.
    To create a new connection, the given functions for group and
    point are called
 */
ConnectionType::ConnectionType(      CreateGroupFunction  createGroup,
                               const std::string         &name        ) :
    _createGroup(createGroup),
    _createPoint(NULL),
    _name(name)
{
    ConnectionFactory::the()->addGroupType(this);
}
 
/*! Constructor. A new connection with the given name is registered.
    To create a new connection, the given functions for group and
    point are called
 */
ConnectionType::ConnectionType(      CreatePointFunction  createPoint,
                               const std::string         &name        ) :
    _createGroup(NULL),
    _createPoint(createPoint),
    _name(name)
{
    ConnectionFactory::the()->addPointType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor. Unregister the connection from the factory
 */
ConnectionType::~ConnectionType(void)
{
    if(_createGroup != NULL && GlobalSystemState != Shutdown)
        ConnectionFactory::the()->subGroupType(this);

    if(_createPoint != NULL && GlobalSystemState != Shutdown)
        ConnectionFactory::the()->subPointType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
ConnectionType& ConnectionType::operator = (const ConnectionType &source)
{
    if(this == &source)
        return *this;

    _name        = source._name;
    _createGroup = source._createGroup;
    _createPoint = source._createPoint;

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*! less
 */
bool ConnectionType::operator < (const ConnectionType &other) const
{
    return _name < other._name;
}

/*! equal
 */
bool ConnectionType::operator == (const ConnectionType &other) const
{
    return _name == other._name;
}

/*! unequal
 */
bool ConnectionType::operator != (const ConnectionType &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*/
/*                             get                                         */

/*! get conneciton name
 */
std::string ConnectionType::getName(void) const
{
    return _name;
}

/*! get conneciton create function
 */
ConnectionType::CreateGroupFunction ConnectionType::getCreateGroup(void) const
{
    return _createGroup;
}

/*! get conneciton create function
 */
ConnectionType::CreatePointFunction ConnectionType::getCreatePoint(void) const{
    return _createPoint;
}

/*-------------------------------------------------------------------------*/
/*                             creation                                    */

/*! create Connection
 */
GroupConnection *ConnectionType::createGroup(void)
{
    return _createGroup();
}

/*! create Connection
 */
PointConnection *ConnectionType::createPoint(void)
{
     return _createPoint();
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id:$";
    static Char8 cvsid_hpp[] = OSG_CONNECTIONTYPEHEADER_CVSID;
}
