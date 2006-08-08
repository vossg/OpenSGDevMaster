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

#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <sys/types.h>
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
#include <OSGStreamSocket.h>

OSG_USING_NAMESPACE

/** \class osg::StreamSocket
 *  \ingroup GrpBaseNetwork
 *  \brief Stream socket handler
 *
 * This class is a Handler to connection oriented sockets. A call to
 * <EM>open</EM> will assing a stream socket and <EM>close</EM>
 * releases the socket. 
 *
 * Client example
 * <PRE>
 * char buffer[100];
 * StreamSocket s;
 * s.open();
 * s.connect(Address("serverhost.com",4567);
 * s.send(buffer,100);
 * s.close();
 * </PRE>
 *
 * Server example
 * <PRE>
 * char buffer[100];
 * StreamSocket s;
 * s.open();
 * s.bind(AnySocketAddress(4567);
 * c=s.accept();               // accept incomming client
 * c.recv(buffer,100);         // read client message
 * c.close();
 * s.close();
 * </PRE>
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor. Use open to assign a system socket. No system socket is assigned by
    the constructor.
    \see StreamSocket::open
 */
StreamSocket::StreamSocket():
    Socket()
{
}

/** \brief Copy constructor
 */
StreamSocket::StreamSocket(const StreamSocket &source):
    Socket(source)
{
}

/*-------------------------------------------------------------------------*/
/*                           Socket functionaliy                           */

/*! Assign a socket. <CODE>Open</CODE> assignes a system socket to the
    StreamSocket. 
    \see Socket::close 
 */
void StreamSocket::open()
{
    _sd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(_sd < 0)
    {
        throw SocketError("socket()");
    }

    struct linger li;
    li.l_onoff = 1;
    li.l_linger = 1;
    int rc = setsockopt(_sd, SOL_SOCKET, SO_LINGER, 
                        (SocketOptT*)&li, sizeof(li));
}

/*! close socket
 */
void StreamSocket::close(void)
{
#ifdef WIN32
    ::closesocket(_sd);
#else
    ::close(_sd);
#endif
}

/*! Accept incomming connection. Use the returned StreamSocket to 
    communicate over the accepted communication. If the new StreamSocket
    is no longer used, you have to close it. A new StreamSocket is 
    returned to communicate with the accepted client.
 */
StreamSocket StreamSocket::acceptFrom(SocketAddress &address)
{
    StreamSocket client;
    SocketLenT len;
    
    len=address.getSockAddrSize();
    client._sd=::accept(_sd,
                        address.getSockAddr(),
                        &len);
    if(client._sd < 0)
    {
        throw SocketError("accept()");
    }
    return client;
}

/*! Accept incomming connection. Use the returned StreamSocket to 
    communicate over the accepted communication. If the new StreamSocket
    is no longer used, you have to close it.
 */
StreamSocket StreamSocket::accept()
{
    SocketAddress addr;
    return acceptFrom(addr);
}

/*! A Stream socket doesen't send data immediately. Only if the internal
    buffer contains enough data, an immediate write is forced. If
    delay is set to false, then data is written always immediately.
 */
void StreamSocket::setDelay(bool value)
{
    int rc,on;
    on=!value;
    rc=setsockopt(_sd, IPPROTO_TCP, TCP_NODELAY, 
                  (SocketOptT*)&on, sizeof(on));
    if(rc < 0)
    {
        throw SocketError("setsockopt(,SOCK_STREAM,TCP_NODELAY)");
    }
}

/*-------------------------------------------------------------------------*/
/*                              assignment                                 */

/*! assignment
 */
const StreamSocket & StreamSocket::operator =(const StreamSocket &source)
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSG_STREAMSOCKET_HEADER_CVSID;
}
