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

#include <sys/types.h>
#ifdef WIN32
#include <windows.h>
#ifndef IP_ADD_MEMBERSHIP // VS.Net defines this within winsock2.h
#include <WS2TCPIP.h>
#endif
#include <io.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <map>
#include <OSGSocketAddress.h>
#include <OSGDgramSocket.h>
#include <OSGNetworkMessage.h>

#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/** \class OSG::DgramSocket
 *  \ingroup GrpBaseNetwork
 *  \brief Datagramm socket handler
 *
 * This class is a handler to packet oriented socket.
 * <EM>open</EM> will assing a udp socket and <EM>close</EM>
 * releases the socket. 
 * Messages send with DgramSockets can be lost or the order in
 * which they arrive can be changed.
 *
 * <PRE>
 * char buffer[100];
 * DgramSocket s;
 * SocketAddress from;
 * s.open();
 * s.sendTo(buffer,10,SocketAddress("serverhost.com",4567));
 * s.recvFrom(buffer,10,from);
 * s.close();
 * </PRE>
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor. Use open to assign a system socket. No system socket is
    assigned by the constructor.
    \see DgramSocket::open
 */
DgramSocket::DgramSocket():
    Socket()
{
}

/*! Copy constructor
 */
DgramSocket::DgramSocket(const DgramSocket &source):
    Socket(source)
{
}

/*-------------------------------------------------------------------------*/
/*                        open                                             */

/*! Assign a socket. <CODE>Open</CODE> assignes a system socket to the
    DgramSocket. 
    \see Socket::close 
 */
void DgramSocket::open()
{
    _sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(_sd<0)
    {
        throw SocketError("socket()");
    }
    // all dgram sockets are allowed to send broadcast
    int on = 1;
    if(::setsockopt(_sd, 
                    SOL_SOCKET, SO_BROADCAST, 
                    (SocketOptT*)&on, sizeof(on)) < 0)
    {
        throw SocketError("setsockopt(,SOL_SOCKET,SO_BROADCAST)");
    }
    // by default, multicast only in local network
    setTTL(2);
}

/*! close socket
 */
void DgramSocket::close(void)
{
#ifdef WIN32
    ::closesocket(_sd);
#else
    ::close(_sd);
#endif
}

/*-------------------------------------------------------------------------*/
/*                        read, write                                      */

/*! Read size bytes into the buffer. Wait until size Bytes are available
    data maight be lossed, if size is smaller then the incomming package.
    This situation will not be treated as an error.
    \see Socket::recvAvailable Socket::recv
 */
int DgramSocket::recvFrom(void *buf,int size,SocketAddress &from)
{
    int len;
    SocketLenT addrLen=from.getSockAddrSize();

#ifndef WIN32
    do
    {
#endif
        len=recvfrom(_sd,
                     (char*)buf,
                     size,
                     0,
                     from.getSockAddr(),
                     &addrLen);
#ifndef WIN32
    } 
    while(len < 0 && errno == EAGAIN);
#endif

    if(len < 0)
    {
#if defined WIN32
        if(getError() == WSAECONNRESET)
        {
            throw SocketConnReset("recvfrom");
        }
        if(getError() == WSAEMSGSIZE)
        {
            len=size;
        }
        else
#endif
        throw SocketError("recvfrom()");
    }
    return len;
}

/*! Read size bytes into the buffer. Wait until size Bytes are available
    On Dgram sockets data maight be lossed, if size is smaller then the
    incomming package. This situation will not be treated as an error.
    The read bytes will not be removed from the in buffer. A call to
    recv after peek will result in the same data.
    \see recv Socket::recv
 */
int DgramSocket::peekFrom(void *buf,int size,SocketAddress &from)
{
    int len;
    SocketLenT addrLen=from.getSockAddrSize();

    len=recvfrom(_sd,
                 (char*)buf,
                 size,
                 MSG_PEEK,
                 from.getSockAddr(),
                 &addrLen);
    if(len == -1)
    {
#if defined WIN32
        if(getError() == WSAECONNRESET)
        {
            throw SocketConnReset("recvfrom");
        }
        if(getError() == WSAEMSGSIZE)
        {
            len=size;
        }
        else
#endif
        throw SocketError("recvfrom()");
    }
    return len;
}

/*! Receive a NetworkMessage. Workes like recv, but buffer and size is
    taken from the NetworkMessage
    \see Socket::recv
 */
int DgramSocket::recvFrom(NetworkMessage &msg,SocketAddress &from)
{
    NetworkMessage::Header hdr;
    peek(&hdr,sizeof(hdr));
    msg.setSize(osgntohl(hdr.size));
    return recvFrom(msg.getBuffer(),msg.getSize(),from);
}

/*! Write size bytes to the socket. This method maight block, if the
    output buffer is full.
    \see recv Socket::send
 */
int DgramSocket::sendTo(const void *buf,int size,const SocketAddress &to)
{
    int len;

    // send Request
    len=sendto(_sd,
               (const char*)buf,size,
#if defined(WIN32) && defined(MSG_NOSIGNAL)
               MSG_NOSIGNAL,
#else
               0,
#endif
               to.getSockAddr(),
               to.getSockAddrSize());

#ifdef _sgi
    /* Irix simetimes returns ENOBUFS on blocking write.
       Retry until buffer is available */
    while(len == -1 && errno == ENOBUFS)
    {
        usleep(100);
        len=sendto(_sd,
                   (const char*)buf,size,
                   0,
                   to.getSockAddr(),
                   to.getSockAddrSize());
    }
#endif

    if(len == -1)
    {
        throw SocketError("sendto()");
    }
    return len;
}

/*! Send a NetworkMessage to an address. Workes like send, but buffer
    and size is taken from the NetworkMessage.
    \see Socket::send
 */
int DgramSocket::sendTo(NetworkMessage &msg,const SocketAddress &to)
{
    NetworkMessage::Header &hdr=msg.getHeader();
    hdr.size=osghtonl(msg.getSize());
    return sendTo(msg.getBuffer(),msg.getSize(),to);
}

/*-------------------------------------------------------------------------*/
/*                        multicast                                        */

/*! The socket will receive all messages from the given multicast address
    It is possible to join more then on goup.
 */
void DgramSocket::join(const SocketAddress &group,const SocketAddress &interf)
{
    struct ip_mreq joinAddr;
    int rc;

    // group to join
    joinAddr.imr_multiaddr.s_addr =
        ((sockaddr_in*)group.getSockAddr())->sin_addr.s_addr;
    // interface that joins. (equal to bind address)
    joinAddr.imr_interface =
        ((struct sockaddr_in*)interf.getSockAddr())->sin_addr;
    rc=setsockopt(_sd,
                  IPPROTO_IP,
                  IP_ADD_MEMBERSHIP,
                  (SocketOptT*)&joinAddr,
                  sizeof(joinAddr));
    if(rc < 0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_ADD_MEMBERSHIP)");
    }
}

/*! Leave a multicast group. Don't receive messages from the given group.
 */
void DgramSocket::leave(const SocketAddress &group,const SocketAddress &interf)
{
    struct ip_mreq joinAddr;
    int rc;

    // group to join
    joinAddr.imr_multiaddr.s_addr =
        ((sockaddr_in*)group.getSockAddr())->sin_addr.s_addr;
    // interface that joins. (equal to bind address)
    joinAddr.imr_interface =
        ((sockaddr_in*)interf.getSockAddr())->sin_addr;
    rc=setsockopt(_sd,
                  IPPROTO_IP,
                  IP_DROP_MEMBERSHIP,
                  (SocketOptT*)&joinAddr,
                  sizeof(joinAddr));
    if(rc < 0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_DROP_MEMBERSHIP)");
    }
}

/*! Set TTL for broadcast and multicast. Defines how many routers a
    package will pass until it is deleted. 0 = local host, 
    1 = local network, ...
 */
void DgramSocket::setTTL(unsigned char ttl)
{
    int rc=setsockopt(_sd, IPPROTO_IP,IP_MULTICAST_TTL,
                      (SocketOptT*)&ttl,sizeof(ttl));
    if(rc < 0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_MULTICAST_TTL)");
    }
}

/*! Specify the network interface for outgoing multicast
    packages
 */
void DgramSocket::setMCastInterface(const SocketAddress &interf)
{
    int rc=setsockopt(_sd,
                      IPPROTO_IP,
                      IP_MULTICAST_IF,
                      (SocketOptT*)interf.getSockAddr(),
                      interf.getSockAddrSize());
    if(rc < 0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_MULTICAST_IF)");
    }

}


/*-------------------------------------------------------------------------*/
/*                        assignment                                       */

/*! assignment
 */
const DgramSocket & DgramSocket::operator =(const DgramSocket &source)
{
    _sd=source._sd;
    return *this;
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
    static Char8 cvsid_hpp       [] = OSG_DGRAMSOCKET_HEADER_CVSID;
}
