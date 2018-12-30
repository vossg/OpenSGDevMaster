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

#include <sstream>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGSocketSelection.h"
#include "OSGSocketException.h"
#include "OSGGroupSockConnection.h"
#include "OSGConnectionType.h"

OSG_USING_NAMESPACE

/** \class OSG::GroupSockConnection
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

GroupSockConnection::GroupSockConnection():
     GroupConnection  (0),
    _acceptSocket     ( ),
    _sockets          ( ),
    _remoteAddresses  ( ),
    _readIndex        (0),
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
GroupSockConnection::~GroupSockConnection(void)
{
    // close and remove sockets
    while(_sockets.size())
    {
        try
        {
            _sockets.begin()->close();
            _sockets.erase(_sockets.begin());
        }
        catch(...)
        {
        }
    }
    _acceptSocket.close();
}

/*! get connection type
 */
const ConnectionType *GroupSockConnection::getType()
{
    return &_type;
}

/*-------------------------------------------------------------------------*/
/*                            connection                                   */

/*! connect to the given point. If timeout is reached, -1 is
    returned
 */
GroupConnection::Channel GroupSockConnection::connectPoint(
    const std::string &address,
    Time               timeout)
{
    Channel channel = -1;
    StreamSocket socket;
    SocketAddress destination;
    if(connectSocket(socket,address,destination,timeout))
    {
        channel = newChannelIndex(ChannelIndex(_sockets.size()));
        _sockets        .push_back(socket);
        _remoteAddresses.push_back(destination);
        _readIndex = 0;
    }
    return channel;
}

/*! disconnect the given channel
 */
void GroupSockConnection::disconnect(Channel channel)
{
    ChannelIndex index = channelToIndex(channel);
    try
    {
        _sockets[index].close();
    }
    catch(...)
    {
    }
    _sockets        .erase(_sockets        .begin() + index);
    _remoteAddresses.erase(_remoteAddresses.begin() + index);
    delChannelIndex(index);
    _readIndex = 0;
}

/*! accept an icomming point connection. If timeout is reached,
    -1 is returned. If timeout is -1 then wait without timeout
 */
GroupConnection::Channel GroupSockConnection::acceptPoint(Time timeout)
{
    StreamSocket from;
    SocketAddress destination;
    if(GroupSockConnection::acceptSocket(_acceptSocket,
                                         from,
                                         destination,
                                         timeout))
    {
        Channel channel = newChannelIndex(ChannelIndex(_sockets.size()));
        _sockets        .push_back(from);
        _remoteAddresses.push_back(destination);
        _readIndex = 0;
        return channel;
    }
    else
    {
        return -1;
    }
}

/*! bind the connection to an network interface. The address is
    returned, on wich the port could be connected. The interface
    is determined by the connection interface filed and the
    address parameter. Address can be empty, wich means to use
    a free port or address can contain a port number.
 */
std::string GroupSockConnection::bind(const std::string &address)
{
    int         port=0;
    char        localhost[256];
    char        portStr[256];
    std::string interf;
    std::string boundedAddress;

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
    _acceptSocket.bind(SocketAddress(interf.c_str(),port));
    SINFO << "Connection bound to "
          << _acceptSocket.getAddress().getHost() << ":"
          << _acceptSocket.getAddress().getPort() << std::endl;
    _acceptSocket.listen();
    // create address
    sprintf(portStr,"%d",_acceptSocket.getAddress().getPort());
    return interf + ":" + portStr;
}

/*! parse the params string.
 */
void GroupSockConnection::setParams(const std::string &params)
{
    if(params.empty())
        return;

    std::string option = "bufferSize=";
    std::string::size_type i = 0;
    if((i=params.find(option)) != std::string::npos)
    {
        std::string str = params.substr(i + option.size());

        std::stringstream ss;
        std::string::size_type j = 0;
        while(j < str.length() && str[j] != ',' && isdigit(str[j]))
        {
            ss << str[j++];
        }
        UInt32 bufferSize;
        ss >> bufferSize;

        // clear old buffer.
        readBufClear();
        writeBufClear();

        _socketReadBuffer.resize(bufferSize);
        _socketWriteBuffer.resize(_socketReadBuffer.size());
        
        // reserve first bytes for buffer size
        readBufAdd (&_socketReadBuffer [sizeof(SocketBufferHeader)],
                    _socketReadBuffer.size() -sizeof(SocketBufferHeader));
        writeBufAdd(&_socketWriteBuffer[sizeof(SocketBufferHeader)],
                    _socketWriteBuffer.size()-sizeof(SocketBufferHeader));

        FINFO(("GroupSockConnection::setParams : setting buffer size to %u.\n", bufferSize));
    }
}

/*-------------------------------------------------------------------------*/
/*                              channel handling                           */

/*! select the next channel for reading. If timeout is not -1
    then -1 is returned if timeout is reached
*/
Connection::Channel GroupSockConnection::selectChannel(Time timeout)
    OSG_THROW (ReadError)
{
    Int32 maxnread=0,nread;
    ChannelIndex index;
    SocketSelection selection,result;

    // if there is data in the read buffer, return current channel
    if(_zeroCopyThreshold != 1 &&
       _currentReadBuffer != readBufEnd())
    {
        FFATAL(("Channel change ignores data in current buffer"))
        return indexToChannel(_readIndex);
    }    

    if(_selection[_readIndex] &&
       _sockets[_readIndex].getAvailable())
    {
        return indexToChannel(_readIndex);;
    }

    // wait for first socket to deliver data
    for(  index = 0 ; 
          index < static_cast<ChannelIndex>(_sockets.size()); 
        ++index)
    {
        if(_selection[index])
            selection.setRead(_sockets[index]);
    }
    
    try 
    {
        // select ok ?
        if(!selection.select(timeout,result))
            return -1;

        // use socket with most data
        for(  index = 0; 
              index < static_cast<ChannelIndex>(_sockets.size()); 
            ++index)
        {
            if(result.isSetRead(_sockets[index]))
            {
                nread=_sockets[index].getAvailable();
                if(maxnread < nread)
                {
                    maxnread = nread;
                    _readIndex=index;
                }
            }
        }
    }
    catch(SocketException &e)
    {
        throw ReadError(e.what());
    }

    // return channel id
    return indexToChannel(_readIndex);
}

/*-------------------------------------------------------------------------*/
/*                            sync                                         */

/*! wait for signal
 */
bool GroupSockConnection::wait(Time timeout) OSG_THROW (ReadError)
{
    UInt32 len;
    UInt32 index;
    UInt32 tag=314156;
    SizeT  missing = _sockets.size();
    SocketSelection selection,result;

    for(index = 0 ; index < _sockets.size() ; ++index)
        selection.setRead(_sockets[index]);

    try
    {
        while(missing)
        {
            if(!selection.select(timeout,result))
                return false;
            for(index = 0 ; index < _sockets.size() ; ++index)
            {
                if(result.isSetRead(_sockets[index]))
                {
                    len = _sockets[index].recv(&tag,sizeof(tag));
                    tag = osgNetToHost<UInt32>(tag);
                    if(len == 0)
                        throw ReadError("Channel closed");
                    selection.clearRead(_sockets[index]);
                    missing--;
                    if(tag != 314156)
                    {
                        FFATAL(("Stream out of sync in SockConnection\n"));
                        throw ReadError("Stream out of sync");
                    }
                }
            }
        }
    }
    catch(SocketException &e)
    {
        throw ReadError(e.what());
    }
    return true;
}

/*! send signal
 */
void GroupSockConnection::signal(void) OSG_THROW (WriteError)
{
    UInt32 tag = osgHostToNet<UInt32>(314156);
    UInt32 index;

    try
    {
        for(index = 0 ; index<_sockets.size() ; ++index)
            _sockets[index].send(&tag,sizeof(tag));
    }
    catch(SocketError &e)
    {
        throw WriteError(e.what());
    }
}

/*-------------------------- create ---------------------------------------*/

/** \brief create conneciton
 */

GroupConnection *GroupSockConnection::create(void)
{
    return new GroupSockConnection();
}

/*-------------------------------------------------------------------------*/
/*                              read write                                 */

/** Read data into given memory
 *
 * Read data form the current read socket. The read socket is that
 * socket, that was selectet in selectChannel.
 *
 **/

void GroupSockConnection::read(MemoryHandle mem,UInt32 size)
{
    int len;

    // read data
    len=_sockets[_readIndex].recv(mem,size);
    if(len==0)
    {
//        throw ChannelClosed(indexToChannel(_readIndex));
        throw ReadError("Channel closed");
    }
} 

/** Read next data block
 *
 * The stream connection uses only BinaryDataHandler buffer. If more
 * then one buffer is present, then this methode must be changed!
 *
 */

void GroupSockConnection::readBuffer() OSG_THROW (ReadError)
{
    int size;
    int len;

    // read buffer header
    len=_sockets[_readIndex].recv(&_socketReadBuffer[0],sizeof(SocketBufferHeader));
    if(len==0)
        throw ReadError("Channel closed");
    // read remaining data
    size=osgNetToHost<UInt32>((reinterpret_cast<SocketBufferHeader*>(&_socketReadBuffer[0]))->size);
    len=_sockets[_readIndex].recv(&_socketReadBuffer[sizeof(SocketBufferHeader)],
                         size);
    if(len==0)
        throw ReadError("Channel closed");
    readBufBegin()->setDataSize(size);
}    

/** Write data to all destinations
 *
 * \param mem   Pointer to data buffer
 * \param size  Size of bytes to write
 *
 **/

void GroupSockConnection::write(MemoryHandle mem,UInt32 size)
{
    UInt32 index;

    try
    {
        // write to all connected sockets
        for(index = 0 ; index < _sockets.size() ; ++index)
            _sockets[index].send(mem,size);
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
void GroupSockConnection::writeBuffer(void)
{
    UInt32 index;
    UInt32 size = writeBufBegin()->getDataSize();
    // write size to header
    (reinterpret_cast<SocketBufferHeader*>(&_socketWriteBuffer[0]))->size = 
        osgHostToNet<UInt32>(size);
    if(size)
    {
        // write data to all sockets
        for(index = 0 ; index < _sockets.size() ; ++index)
        {
            // write whole block
            _sockets[index].send(&_socketWriteBuffer[0],
                                 size+sizeof(SocketBufferHeader));
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                              internal helper functions                  */

/*! connect two sockets until success or timeout
 */
bool GroupSockConnection::connectSocket(StreamSocket &socket,
                                        std::string   address,
                                        SocketAddress &destination,
                                        Time          timeout)
{
    std::string  host="unknown";
    int          port=0;
    Time         startTime = getSystemTime();
    bool         connected=false;
    
    SizeT        pos = address.find(':');

    if(pos != std::string::npos)
    {
        host = std::string(address,0,pos);
        port = atoi(std::string(address,pos+1,std::string::npos).c_str());
    }
    else
    {
        host = address;
    }
    
    socket.open();
    socket.setDelay(false);
    socket.setReadBufferSize(1048576);
    socket.setWriteBufferSize(1048576);
    destination = SocketAddress(host.c_str(),port);
    while(!connected && 
          (timeout == -1 || (getSystemTime()-startTime) < timeout))
    {
        try
        {
            socket.connect(destination);
            connected = true;
        }
        catch(...)
        {
        }
    }
    if(connected)
        return true;
    else
        return false;
}

/*! accept socket untile success or timeout
 */
bool GroupSockConnection::acceptSocket(StreamSocket &accept,
                                       StreamSocket &from,
                                       SocketAddress &destination,
                                       Time          timeout)
{
    if(!accept.waitReadable(timeout))
        return false;
    from=accept.acceptFrom(destination);
    from.setDelay(false);
    from.setReadBufferSize(1048576);
    from.setWriteBufferSize(1048576);
    return true;
}

/*-------------------------------------------------------------------------*/
/*                              static type                                */

ConnectionType GroupSockConnection::_type(
    &GroupSockConnection::create,
    "StreamSock");
