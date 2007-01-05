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
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "OSGConfig.h"
#include "OSGConnection.h"

OSG_USING_NAMESPACE

/** \class OSG::Connection
 *  \ingroup GrpBaseNetwork
 *  \brief Abstract 1 to n connection
 *
 * Connection defines an interface for a reliable 1 to n connection.
 * It implements a BinaryDataHandler which is used for reading and
 * writing binary data and OpenSG FieldContainer contents.
 *
 * Writing to n destinations is easy to handle but reading from n
 * simutanious sending sources is more complicated. To make things
 * easier, you have to select one channel for exclusiv read. This
 * is done by calling <EM>selectChannel</EM>. Implementations fo
 * <EM>selectChannel</EM> should select the channel with the most
 * pending data for getting the best read performance.
 *
 * <EM>wait</EM> and <EM>signal</EM> are used to synchronize a number
 * of programms.
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

Connection::Connection(int zeroCopyThreshold):
     BinaryDataHandler(zeroCopyThreshold),
    _interface        (""               )
{
}

/*! Destructor
 */

Connection::~Connection(void)
{
}

/*! set connections parameters, a comma separated list e.g. "TTL=255"
 */

void Connection::setParams(const std::string &OSG_CHECK_ARG(params))
{
    // do nothing this is implemented in the derived classes e.g. 
    // OSGGroupMCastConnection.cpp
}

/*! get network interface
 */

const std::string &Connection::getInterface(void)
{
    return _interface;
}

/*! set network interface
 */

void Connection::setInterface(const std::string &interf)
{
    _interface = interf;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_inl       [] = OSG_CONNECTION_INLINE_CVSID;
    static Char8 cvsid_hpp       [] = OSG_CONNECTION_HEADER_CVSID;
}

