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
#include "OSGLog.h"
#include "OSGSocketSelection.h"
#include "OSGPointSockConnection.h"
#include "OSGGroupSockConnection.h"
#include "OSGConnectionType.h"

OSG_USING_NAMESPACE

/** \class OSG::PointSockConnection
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

PointSockConnection::PointSockConnection():
     Inherited        (0),
    _acceptSocket     ( ),
    _socket           ( ),
    _remoteAddress    ( ),
    _socketReadBuffer ( ),
    _socketWriteBuffer( )
{
    _acceptSocket.open();
    _acceptSocket.setReusePort(true);

    _socketReadBuffer.resize(131071);
    _socketWriteBuffer.resize( _socketReadBuffer.size() );
    // reserve first bytes for buffer size
    readBufAdd (&_socketReadBuffer [sizeof(SocketBufferHeader)],
                _socketReadBuffer.size() -sizeof(SocketBufferHeader));
    writeBufAdd(&_socketWriteBuffer[sizeof(SocketBufferHeader)],
                _socketWriteBuffer.size()-sizeof(SocketBufferHeader));
}

/*! Destructor
 */
PointSockConnection::~PointSockConnection(void)
{
    _acceptSocket.close();
}

/*! get connection type
 */
const ConnectionType *PointSockConnection::getType()
{
    return &_type;
}

/*-------------------------------------------------------------------------*/
/*                            connection                                   */

/*! connect to the given point. If timeout is reached, -1 is
    returned
 */
Connection::Channel PointSockConnection::connectPoint(
    const std::string &address,
    Time               timeout)
{
    StreamSocket socket;
    if(GroupSockConnection::connectSocket( socket,
                                           address,
                                          _remoteAddress,
                                           timeout))
    {
        _socket = socket;
        _pointToPoint = true;
        return 0;
    }
    else
    {
        return -1;
    }
}

/*! connect to the given group. If timeout is reached, -1 is
    returned
 */
Connection::Channel PointSockConnection::connectGroup(
    const std::string &address,
    Time               timeout)
{
    StreamSocket socket;
    if(GroupSockConnection::connectSocket( socket,
                                           address,
                                          _remoteAddress,
                                           timeout))
    {
        _socket = socket;
        _pointToPoint = false;
        return 0;
    }
    else
    {
        return -1;
    }
}

/*! disconnect the given channel
 */
void PointSockConnection::disconnect(void)
{
    _socket.close();
}

/*! accept an icomming point connection. If timeout is reached,
    -1 is returned. If timeout is -1 then wait without timeout
 */
Connection::Channel PointSockConnection::acceptPoint(Time timeout)
{
    if(GroupSockConnection::acceptSocket(_acceptSocket,
                                         _socket,
                                         _remoteAddress,
                                          timeout))
    {
        _pointToPoint = true;
        return 0;
    }
    else
    {
        return -1;
    }
}

/*! accept an icomming grop connection. If timeout is reached,
    -1 is returned. If timeout is -1 then wait without timeout
 */
Connection::Channel PointSockConnection::acceptGroup(Time timeout)
{
    if(GroupSockConnection::acceptSocket(_acceptSocket,
                                         _socket,
                                         _remoteAddress,
                                          timeout))
    {
        _pointToPoint = false;
        return 0;
    }
    else
    {
        return -1;
    }
}

/*! bind the connection to a network interface. The address is
    returned, on wich the port could be connected. The interface
    is determined by the connection interface filed and the
    address parameter. Address can be empty, wich means to use
    a free port or address can contain a port number.
 */
std::string PointSockConnection::bind(const std::string &address)
{
    int         port=0;
    char        localhost[256];
    char        portStr[256];
    std::string interf;

    // get local host name
    osgGetHostname(localhost,255);
    if(!getInterface().empty())
        interf = getInterface();
    else
        interf = localhost;

    // parse address
    if(!address.empty())
        if(sscanf(address.c_str(),"%*[^:]:%d",&port) != 1)
            if(sscanf(address.c_str(),":%d",&port) != 1)
                port = 0;
    // bind port
    _acceptSocket.setReusePort(true);
    if(!getInterface().empty())
        _acceptSocket.bind(SocketAddress(getInterface().c_str(),port));
    else
        _acceptSocket.bind(SocketAddress(SocketAddress::ANY,port));

    SINFO << "Connection bound to "
          << _acceptSocket.getAddress().getHost() << ":"
          << _acceptSocket.getAddress().getPort() << std::endl;
    _acceptSocket.listen();
    // create address
    sprintf(portStr,"%d",_acceptSocket.getAddress().getPort());
    return interf + ":" + portStr;
}

/*-------------------------------------------------------------------------*/
/*                              channel handling                           */

/*! select the next channel for reading. If timeout is not -1
    then -1 is returned if timeout is reached
*/
Connection::Channel PointSockConnection::selectChannel(Time timeout)
    OSG_THROW (ReadError)
{
    try
    {
        if(_socket.waitReadable(timeout))
            return 0;
    }
    catch(SocketError &e)
    {
        throw ReadError(e.what());
    }
    return -1;
}

/*-------------------------------------------------------------------------*/
/*                            sync                                         */

/*! wait for signal
 */
bool PointSockConnection::wait(Time timeout) OSG_THROW (ReadError)
{
    UInt32 tag;
    try
    {
        if(!_socket.waitReadable(timeout))
            return false;
        if(!_socket.recv(&tag,sizeof(tag)))
            throw ReadError("Channel closed");

        tag = osgNetToHost<UInt32>(tag);
        if(tag != 314156)
        {
            FFATAL(("Stream out of sync in SockConnection\n"));
            throw ReadError("Stream out of sync");
        }
    }
    catch(SocketError &e)
    {
        throw ReadError(e.what());
    }
    return true;
}

/*! send signal
 */
void PointSockConnection::signal(void) OSG_THROW (WriteError)
{
    UInt32 tag = osgHostToNet<UInt32>(314156);
    try
    {
        _socket.send(&tag,sizeof(tag));
    }
    catch(SocketError &e)
    {
        throw WriteError(e.what());
    }
}

/*-------------------------- create ---------------------------------------*/

/** \brief create conneciton
 */

PointConnection *PointSockConnection::create(void)
{
    return new PointSockConnection();
}

/*-------------------------------------------------------------------------*/
/*                              read write                                 */

/** Read data into given memory
 *
 * Read data form the current read socket. The read socket is that
 * socket, that was selectet in selectChannel.
 *
 **/

void PointSockConnection::read(MemoryHandle mem,UInt32 size)
{
    int len;

    // read data
    len=_socket.recv(mem,size);
    if(len==0)
    {
        throw ReadError("read got 0 bytes!");
    }
}

/** Read next data block
 *
 * The stream connection uses only BinaryDataHandler buffer. If more
 * then one buffer is present, then this methode must be changed!
 *
 */

void PointSockConnection::readBuffer() OSG_THROW (ReadError)
{
    int size;
    int len;

    // read buffer header
    len=_socket.recv(&_socketReadBuffer[0],sizeof(SocketBufferHeader));
    if(len==0)
        throw ReadError("peek got 0 bytes!");
    // read remaining data
    size=osgNetToHost<UInt32>((reinterpret_cast<SocketBufferHeader*>(&_socketReadBuffer[0]))->size);
    len=_socket.recv(&_socketReadBuffer[sizeof(SocketBufferHeader)],
                     size);
    if(len==0)
        throw ReadError("read got 0 bytes!");
    readBufBegin()->setDataSize(size);
}    

/** Write data to destinations
 *
 * \param mem   Pointer to data buffer
 * \param size  Size of bytes to write
 *
 **/

void PointSockConnection::write(MemoryHandle mem,UInt32 size)
{
    _socket.send(mem,size);
}

/** Write buffer
 *
 * Write blocksize and data.
 *
 **/
void PointSockConnection::writeBuffer(void)
{
    UInt32 size = writeBufBegin()->getDataSize();

    // write size to header
    (reinterpret_cast<SocketBufferHeader*>(&_socketWriteBuffer[0]))->size = 
        osgHostToNet<UInt32>(size);

    if(size)
    {
        // write whole block
        _socket.send(&_socketWriteBuffer[0],
                     size+sizeof(SocketBufferHeader));
    }
}

/*-------------------------------------------------------------------------*/
/*                              static type                                */

ConnectionType PointSockConnection::_type(
    &PointSockConnection::create,
    "StreamSock");
