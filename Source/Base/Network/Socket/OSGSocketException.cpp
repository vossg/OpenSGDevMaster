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

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <OSGSocket.h>
#include <OSGSocketException.h>

OSG_USING_NAMESPACE

/** \class OSG::SocketException
 *  \ingroup GrpBaseNetwork
 *  \brief Base class for socket exceptions
 **/

/*! Constructor
 */
SocketException::SocketException():
    Exception()
{
    _what+="SocketLib: ";
}

/** \class OSG::SocketError
 *  \ingroup GrpBaseNetwork
 *  \brief Execption caused by socket error return codes
 **/

/*! Constructor
 */
SocketError::SocketError(const char *function):SocketException()
{
    char estr[6];
    
    sprintf(estr,"%5d",Socket::getError());
    _what=_what + function + " " + estr + " " + Socket::getErrorStr();
}

/** \class OSG::SocketHostError
 *  \ingroup GrpBaseNetwork
 *  \brief Execption caused by host name resolution
 **/

/*! Constructor
 */
SocketHostError::SocketHostError(const char *function):SocketException()
{
    char estr[6];

    sprintf(estr,"%5d",Socket::getHostError());
    _what=_what + function + " " + estr + " " + Socket::getHostErrorStr(); 
}

/** \class OSG::SocketInUse
 *  \ingroup GrpBaseNetwork
 *  \brief Execption caused by reusage of ports
 **/

/*! Constructor
 */
SocketInUse::SocketInUse(const char *function):
    SocketError(function)
{
}

/** \class OSG::SocketConnReset
 *  \ingroup GrpBaseNetwork
 *  \brief Execption caused by connection reset of remote endpoint
 **/

/*! Constructor
 */
SocketConnReset::SocketConnReset(const char *function):
    SocketError(function)
{
}
