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

#include <set>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGBaseThread.h"
#include "OSGSocketSelection.h"
#include "OSGBinaryMessage.h"
#include "OSGGroupSockPipeline.h"
#include "OSGConnectionType.h"
#include "OSGBinaryMessage.h"

OSG_USING_NAMESPACE

/** \class OSG::GroupSockPipeline
 *  \ingroup GrpBaseNetwork
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

GroupSockPipeline::GroupSockPipeline():
    Inherited(),
    _initialized(false)
{
    _next.open();
}

/*! Destructor
 */
GroupSockPipeline::~GroupSockPipeline(void)
{
    _next.close();
}

/*! get connection type
 */
const ConnectionType *GroupSockPipeline::getType()
{
    return &_type;
}

/*-------------------------------------------------------------------------*/
/*                            connection                                   */

/*! connect to the given point. If timeout is reached, -1 is
    returned
 */
GroupConnection::Channel GroupSockPipeline::connectPoint(
    const std::string &address,
    Time               timeout)
{
    Channel channel = Inherited::connectPoint(address,timeout);
    return channel;
}

/*! disconnect the given channel
 */
void GroupSockPipeline::disconnect(Channel channel)
{
    Inherited::disconnect(channel);
}

/*! accept an icomming point connection. If timeout is reached,
    -1 is returned. If timeout is -1 then wait without timeout
 */
GroupConnection::Channel GroupSockPipeline::acceptPoint(Time timeout)
{
    Connection::Channel channel = Inherited::acceptPoint(timeout);
    return channel;
}

/*-------------------------- helpers --------------------------------------*/

/** \brief create conneciton
 */

GroupConnection *GroupSockPipeline::create(void)
{
    return new GroupSockPipeline();
}

/*-------------------------------------------------------------------------*/
/*                              read write                                 */

/** Write data to all destinations
 *
 * \param mem   Pointer to data buffer
 * \param size  Size of bytes to write
 *
 **/

void GroupSockPipeline::write(MemoryHandle mem,UInt32 size)
{
    if(!_initialized)
        initialize();

    try
    {
        if(getChannelCount())
            _next.send(mem,size);
    }
    catch(SocketException &e)
    {
        throw WriteError(e.what());
    }
}

/** Write buffer
 *
 * Write blocksize and data.
 *
 **/
void GroupSockPipeline::writeBuffer(void)
{
    Int32 index;

    if(!_initialized)
        initialize();

    UInt32 size = writeBufBegin()->getDataSize();
    // write size to header
    ((SocketBufferHeader*)&_socketWriteBuffer[0])->size=osgHostToNet(size);
    if(size)
    {
        _next.send(&_socketWriteBuffer[0],
                          size+sizeof(SocketBufferHeader));
    }
}

/*-------------------------------------------------------------------------*/
/*                              private helpers                            */

/*! initialize pipeline
 */
void GroupSockPipeline::initialize(void)
{
    UInt32         index,len;
    UInt32         nextPort;
    std::string    nextHost;
    BinaryMessage  message;

    for(index = 0 ; index<_sockets.size() ; ++index)
    {
        len = _sockets[index].recv(message);
        if(len == 0)
            throw ReadError("Channel closed\n");
        nextHost = message.getString();
        nextPort = message.getUInt32();

        message.clear();
        if(index == 0)
        {
            message.putUInt32(true);
            _sockets[_sockets.size()-1].send(message);
            for(;;)
            {
                try
                {
                    _next.connect(SocketAddress(nextHost.c_str(),
                                                nextPort));
                    break;
                }
                catch(...)
                {
                }
            }
        }
        else
        {
            message.clear();
            message.putUInt32(false);
            message.putString(nextHost);
            message.putUInt32(nextPort);
            _sockets[index-1].send(message);
        }
    }
    _initialized = true;
}

/*-------------------------------------------------------------------------*/
/*                              static type                                */

ConnectionType GroupSockPipeline::_type(
    &GroupSockPipeline::create,
    "SockPipeline");

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
    static Char8 cvsid_hpp       [] = OSG_GROUPSOCKPIPELINE_HEADER_CVSID;
}

