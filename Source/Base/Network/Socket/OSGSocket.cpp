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

#if defined(__sun)
#define BSD_COMP
#endif


#include <sys/types.h>
#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#endif
#include <cerrno>
#include <cstdio>
#include <cmath>
#include <map>
#include <OSGSocketAddress.h>
#include <OSGSocket.h>
#include <OSGSocketSelection.h>
#include <OSGNetworkMessage.h>
#include <OSGTime.h>
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/*! \class OSG::Socket
    \ingroup GrpBaseNetwork
    \brief Abstract network socket handler

Socket base class. The Socket class wraps a socket descriptor. This
class has no additional state variables. It is only a handle to the
underlying descriptor. Class creation and destruction has no
influence on the descriptor. Use open to assign a descriptor and
close to remove it from the system. If this class is copied, then
there are to classes which share the same descriptor. This is
acceptable until you call close for one of these classes, then any other class
sharing the same descriptor becomes practically unusable.
One purpose of this implementation is to hide the differences between
Windows and Unix sockets. Calls to this class should behave equally
on all systems. As a result, some methods will not work the way an
experienced Windows ore Unix programmer might expect. Please refer
to the function documentation for details about this.

*/

int Socket::initialized=0;

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Create a new Socket class. A valid socket descriptor will be assigned
    by calling open on a derived Socket class e.g. StreamSocket or
    DgramSocket. On Windows WSAStartup is called by the first socket
    created.
 */
Socket::Socket(void):
    _sd(-1)
{
    if(!initialized)
    {
        initialized=1;
#ifdef WIN32
        WSADATA wsaData;
        
        WORD wVersionRequested = MAKEWORD( 2, 2 ); 
        if(WSAStartup( wVersionRequested, &wsaData )!=0)
        {
            throw SocketError("WSAStartup()");
        }
#endif
    }
}

/*! Copy constructor
 */
Socket::Socket(const Socket &source):
    _sd(source._sd)
{
}

/*! Destructor. The Socket class is only a descriptor to the socket.
    Upon destruction of this class, the socket remains open.
 */
Socket::~Socket()
{
}

/*-------------------------------------------------------------------------*/
/*                        open, close, connect                             */

/*! Close the assigned socket.
 */
void Socket::close(void)
{
#ifdef WIN32
    ::closesocket(_sd);
#else
    ::close(_sd);
#endif
}

/*! Bind a socket to a given SocketAddress. It is possible to bind a 
    Socket to a special network interface ore to all availabel interfaces.

    \param[in] address The address to bind to.

    \code
    sock.bind(AnySocketAddress(23344));     // Bind Socket to port 23344
    sock.bind(Address("123.223.112.33",0);  // Bind to the given adapter
    sock.bind(AnySocketAddress(0));         // Bind to a free port
    port = sock.getAddress().getPort();     // Get bound port
    \endcode
 */
void Socket::bind(const SocketAddress &address)
{
    SocketAddress result=address;
    
    if( ::bind(_sd,
               result.getSockAddr(),
               result.getSockAddrSize()) < 0)
    {
        if(getError() ==
#if defined WIN32
            WSAEADDRINUSE 
#else
			EADDRINUSE
#endif
		)
        {
            throw SocketInUse("bind()");
        }
        else
        {
            throw SocketError("bind()");
        }
    }
}

/*! Set queue length for incomming connection requests.

    \param[in] maxPending Maximum number of simultaneous connection requests.
 */
void Socket::listen(int maxPending)
{
    if(::listen(_sd, maxPending) < 0)
    {
        throw SocketError("listen()");
    }
}

/*! Connect to the given address. After connect, all send data will be
    transfered to the address.

    \param[in] address Address to connect to.
 */
void Socket::connect(const SocketAddress &address)
{
    if( ::connect(_sd,
                  address.getSockAddr(),
                  address.getSockAddrSize()) )
    {
        throw SocketError("connect()");
    }
}

/*-------------------------------------------------------------------------*/
/*                        read, write    nnect                             */

/*! Read \a size bytes into the buffer \a buf. This function waits until there
    are size bytes available.
    On Dgram sockets data might be lost, if size is smaller then the
    incomming package. This situation will not be treated as an error.

    \param[in,out] buf Buffer that is large enough to hold \a size bytes.
    \param[in] size Number of bytes to receive.

    \see recvAvailable recvFrom
 */
int Socket::recv(void *buf, int size)
{
    int readSize;
    int pos = 0;

    while(size)
    {
        readSize = ::recv(_sd, static_cast<char *>(buf) + pos, size, 0);
        if(readSize < 0)
        {
#if defined WIN32
            if(getError() == WSAECONNRESET)
            {
                throw SocketConnReset("recv");
            }
            if(getError() == WSAEMSGSIZE)
            {
                readSize = size;
            }
            else
#endif
            throw SocketError("recv()");
        }
        if(readSize == 0)
        {
            return 0;
        }
        size -= readSize;
        pos  += readSize;
    }
    return pos;
}

/*! Read at most \a size bytes of availbale data into the buffer \a buf.
    This function does not wait until enough bytes are available.

    \param[in,out] buf Buffer that is large enough to hold \a size bytes.
    \param[in] size Maximum number of bytes to receive.

    \see recv 
 */
int Socket::recvAvailable(void *buf, int size)
{
    int len;

#ifndef WIN32
    do
    {
#endif
        len = ::recv(_sd, static_cast<char *>(buf), size, 0);
#ifndef WIN32
    } 
    while(len < 0 && errno == EAGAIN);
#endif

    if(len == -1)
    {
#if defined WIN32
        switch(getError())
        {
        case WSAECONNRESET:
            throw SocketConnReset("recvAvailable()");
            break;
        case WSAEMSGSIZE:
            len=size;
            break;
        default:
            throw SocketError("recv()");
        }
#else
        throw SocketError("recv()");
#endif
    }
    return len;
}

/*! Like recv, but buffer and size are taken from the NetworkMessage.

    \param[in,out] msg NetworkMessage describing the buffer and size to receive.

    \see recv
 */
int Socket::recv(NetworkMessage &msg)
{
    NetworkMessage::Header hdr;
    peek(&hdr, sizeof(hdr));
    msg.setSize(osgNetToHost(hdr.size));
    return recv(msg.getBuffer(), msg.getSize());
}

/*! Read \a size bytes into the buffer \a buf. This function waits until there
    are size bytes available. The read bytes will not be removed from the 
    receive buffer and a subsequent call to recv or recvAvailable will
    read the same data.
    On Dgram sockets data might be lost, if size is smaller then the
    incomming package. This situation will not be treated as an error.

    \param[in,out] buf Buffer that is large enough to hold \a size bytes.
    \param[in] size Number of bytes to receive.

    \see recv recvAvailable
 */
int Socket::peek(void *buf, int size)
{
    int readSize;
    int pos = 0;

    while(size)
    {
        readSize = ::recv(_sd, static_cast<char *>(buf) + pos, size, MSG_PEEK);
        if(readSize < 0)
        {
#if defined WIN32
            if(getError() == WSAECONNRESET)
            {
                throw SocketConnReset("peek");
            }
            if(getError() == WSAEMSGSIZE)
            {
                readSize = size;
            }
            else
#endif
                throw SocketError("peek");
        }
        if(readSize == 0)
        {
            return 0;
        }
        size -= readSize;
        pos  += readSize;
    }
    return pos;
}

/*! Write size bytes to the socket. This method might block, if the
    output buffer is full.

    \param[in] buf Pointer to a buffer with the data to send.
    \param[in] size Number of bytes to send.
    \return Number of bytes sent.
 */
int Socket::send(const void *buf, int size)
{
    int writeSize;
    int pos = 0;

    while(size)
    {
#if defined(WIN32) && defined(MSG_NOSIGNAL)
        writeSize = ::send(_sd, static_cast<const char *>(buf) + pos,
                           size, MSG_NOSIGNAL                        );
#else
        writeSize = ::send(_sd, static_cast<const char *>(buf) + pos,
                           size, 0                                   );
#endif
        if(writeSize == -1)
        {
            throw SocketError("send()");
        }
        if(writeSize == 0)
        {
            return 0;
        }
        size -= writeSize;
        pos  += writeSize;
    }
    return pos;
}

/*! Like send, but buffer and size is taken from the NetworkMessage

    \param[in] msg NetworkMessage with buffer and size to send.

    \see send
 */
int Socket::send(NetworkMessage &msg)
{
    NetworkMessage::Header &hdr = msg.getHeader();
    hdr.size = osgHostToNet(msg.getSize());
    return send(msg.getBuffer(), msg.getSize());
}

/*-------------------------------------------------------------------------*/
/*                        socket state access                              */

/*! Enable or disable reuse port behavior. If reuse port is true, then
    more then one process or thread is able to bind to the same port.
    This makes sense for multicast or broadcast sockets. For StreamSockets
    this feature can be used to avoid the <EM>Socket in use</EM> message
    on not properly closed ports.

    \param[in] value True to enable port reuse, false to disable it.

 */
void Socket::setReusePort(bool value)
{
    int v = static_cast<int>(value);
#ifdef SO_REUSEPORT
    ::setsockopt(_sd, SOL_SOCKET, SO_REUSEPORT,
                 reinterpret_cast<SocketOptT*>(&v), sizeof(v));
#endif
    ::setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR,
                 reinterpret_cast<SocketOptT*>(&v), sizeof(v));
}

/*! By default all recv, send, accept calls will block until the operation
    is finished. This behavior can be switched off by setting blocking to
    false. This will lead to a more difficult programming. An easier 
    way to get non blocking behavior is to use SocketSelections or
    waitReadable, waitWritable. These methods provide a timeout
    for waiting.

    \param[in] value True to enable blocking mode, false to disable it.

    \see Socket::waitReadable Socket::waitWritable SocketSelection
 */
void Socket::setBlocking(bool value)
{
#ifndef WIN32
    int val = 0;
    
    if(value == false)
        val = O_NDELAY;
    if(fcntl(_sd, F_GETFL, &val) < 0)
    {
        throw SocketError("fcntl()");
    }
    val |= O_NDELAY;
    if(value)
    {
        val ^= O_NDELAY;
    }
    if(fcntl(_sd, F_SETFL, val) < 0) 
    {
        throw SocketError("fcntl()");
    }
#else
    u_long ulVal = !value;
    if(ioctlsocket(_sd, FIONBIO, &ulVal) != 0)
    {
        throw SocketError("ioctlsocket()");
    }
#endif
}

/*! Get the SocketAddress this Socket is bound to.

    \return The bound address of this Socket.

    \see SocketAddress 
 */
SocketAddress Socket::getAddress()
{
    SocketAddress result;
    SocketLenT len;

    len=result.getSockAddrSize();
    if( ::getsockname(_sd,result.getSockAddr(),&len) < 0)
    {
        throw SocketError("getsockname()");
    }
    return result;
}

/*! Set the internal read buffer size.

    \param[in] size Number of bytes to use as internal read buffer.

    \see Socket::getReadBufferSize
 */
void Socket::setReadBufferSize(int size)
{
    ::setsockopt(_sd, SOL_SOCKET, SO_RCVBUF,
                 reinterpret_cast<SocketOptT*>(&size), sizeof(size));
}

/*! Set the internal write buffer size.

    \param[in] size Number of bytes to use as internal write buffer.

    \see Socket::getWriteBufferSize
 */
void Socket::setWriteBufferSize(int size)
{
    ::setsockopt(_sd, SOL_SOCKET, SO_SNDBUF,
                 reinterpret_cast<SocketOptT*>(&size), sizeof(size));
}

/*! Get internal read buffer size.

    \return Number of bytes used for the internal read buffer.

    \see Socket::setReadBufferSize
 */
int Socket::getReadBufferSize() 
{
    int        v;
    SocketLenT len = sizeof(v);
    ::getsockopt(_sd, SOL_SOCKET, SO_RCVBUF,
                 reinterpret_cast<SocketOptT*>(&v), &len);
    return v;
}

/*! Get internal write buffer size.

    \return Number of bytes used for the internal write buffer.

    \see Socket::setWriteBufferSize
 */
int Socket::getWriteBufferSize() 
{
    int        v;
    SocketLenT len = sizeof(v);
    ::getsockopt(_sd, SOL_SOCKET, SO_SNDBUF,
                 reinterpret_cast<SocketOptT*>(&v), &len);
    return v;
}

/*! Get number of bytes in the internal read buffer.

    \return Number of bytes in the internal read buffer.
 */
int Socket::getAvailable(void)
{
#ifndef WIN32
    int value;
    if(::ioctl(_sd, FIONREAD, &value) < 0)
    {
        throw SocketError("ioctl()");
    }
    return value;
#else
    u_long ulVal;
    if(ioctlsocket(_sd, FIONREAD, &ulVal) != 0)
    {
        throw SocketError("ioctlsocket()");
    }
    return static_cast<int>(ulVal);
#endif
}

/*! Wait until recv or accept will not block, but no longer than the given
    duration.

    \param[in] duration Maximum wait time in seconds.
    \return True if data is available.
 */
bool Socket::waitReadable(double duration)
{
    SocketSelection selection;
    selection.setRead(*this);
    if(selection.select(duration) == 1)
        return true;
    else
        return false;
}

/*! Wait until send will not block, but no longer than the given duration.

    \param[in] duration Maximum wait time in seconds.
    \return True if next send will not block.
 */
bool Socket::waitWritable(double duration)
{
    SocketSelection selection;
    selection.setWrite(*this);
    if(selection.select(duration)==1)
        return true;
    else
        return false;
}

/*! Assign another socket to this one. This results in both sockets sharing
    a descriptor.

    \warning Be very careful when sharing descriptors, to only open or close
    them once and not use them after they where closed in one instance.
 */
const Socket & Socket::operator =(const Socket &source)
{
    _sd = source._sd;
    return *this;
}

/*-------------------------------------------------------------------------*/
/*                              error information                          */

/*! Get the last occured error.
 */
int Socket::getError(void)
{
#ifdef WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

/*! Get last host error.
 */
int Socket::getHostError(void)
{
#ifdef WIN32
    return WSAGetLastError();
#else
    return h_errno;
#endif
}

/*! Get last occured error as string.
 */
std::string Socket::getErrorStr(void)
{
    const char *err = NULL;

#ifdef WIN32
    switch(getError())
    {
        case WSAEINTR: err= "WSAEINTR"; break;
        case WSAEBADF: err= "WSAEBADF"; break;
        case WSAEFAULT: err= "WSAEFAULT"; break; 
        case WSAEINVAL: err= "WSAEINVAL"; break; 
        case WSAEMFILE: err= "WSAEMFILE"; break; 
        case WSAEWOULDBLOCK: err= "WSAEWOULDBLOCK"; break; 
        case WSAEINPROGRESS: err= "WSAEINPROGRESS"; break; 
        case WSAEALREADY: err= "WSAEALREADY"; break; 
        case WSAENOTSOCK: err= "WSAENOTSOCK"; break; 
        case WSAEDESTADDRREQ: err= "WSAEDESTADDRREQ"; break; 
        case WSAEMSGSIZE: err= "WSAEMSGSIZE"; break; 
        case WSAEPROTOTYPE: err= "WSAEPROTOTYPE"; break; 
        case WSAENOPROTOOPT: err= "WSAENOPROTOOPT"; break; 
        case WSAEPROTONOSUPPORT: err= "WSAEPROTONOSUPPORT"; break; 
        case WSAESOCKTNOSUPPORT: err= "WSAESOCKTNOSUPPORT"; break; 
        case WSAEOPNOTSUPP: err= "WSAEOPNOTSUPP"; break; 
        case WSAEPFNOSUPPORT: err= "WSAEPFNOSUPPORT"; break; 
        case WSAEAFNOSUPPORT: err= "WSAEAFNOSUPPORT"; break; 
        case WSAEADDRINUSE: err= "WSAEADDRINUSE"; break; 
        case WSAEADDRNOTAVAIL: err= "WSAEADDRNOTAVAIL"; break; 
        case WSAENETDOWN: err= "WSAENETDOWN"; break; 
        case WSAENETUNREACH: err= "WSAENETUNREACH"; break; 
        case WSAENETRESET: err= "WSAENETRESET"; break; 
        case WSAECONNABORTED: err= "WSAECONNABORTED"; break; 
        case WSAECONNRESET: err= "WSAECONNRESET"; break; 
        case WSAENOBUFS: err= "WSAENOBUFS"; break; 
        case WSAEISCONN: err= "WSAEISCONN"; break; 
        case WSAENOTCONN: err= "WSAENOTCONN"; break; 
        case WSAESHUTDOWN: err= "WSAESHUTDOWN"; break; 
        case WSAETOOMANYREFS: err= "WSAETOOMANYREFS"; break; 
        case WSAETIMEDOUT: err= "WSAETIMEDOUT"; break; 
        case WSAECONNREFUSED: err= "WSAECONNREFUSED"; break; 
        case WSAELOOP: err= "WSAELOOP"; break; 
        case WSAENAMETOOLONG: err= "WSAENAMETOOLONG"; break; 
        case WSAEHOSTDOWN: err= "WSAEHOSTDOWN"; break; 
        case WSAEHOSTUNREACH: err= "WSAEHOSTUNREACH"; break; 
        case WSASYSNOTREADY: err= "WSASYSNOTREADY"; break; 
        case WSAVERNOTSUPPORTED: err= "WSAVERNOTSUPPORTED"; break; 
        case WSANOTINITIALISED: err= "WSANOTINITIALISED"; break; 
        case WSAHOST_NOT_FOUND: err= "WSAHOST_NOT_FOUND"; break; 
        case WSATRY_AGAIN: err= "WSATRY_AGAIN"; break; 
        case WSANO_RECOVERY: err= "WSANO_RECOVERY"; break; 
        case WSANO_DATA: err= "WSANO_DATA"; break; 
    }
#else
    err = strerror(getError());
#endif
    if(err)
        return std::string(err);
    else
        return std::string("Unknown error");
}

/*! Get last occured host error as string
 */
std::string Socket::getHostErrorStr(void)
{
    const char *err;
#if defined(WIN32) || defined(__hpux)
    err = strerror(getHostError());
#else
    err = hstrerror(getHostError());
#endif
    if(err)
        return std::string(err);
    else
        return std::string("Unknown error");
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
    static Char8 cvsid_hpp       [] = OSG_SOCKET_HEADER_CVSID;
}

