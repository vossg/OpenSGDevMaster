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
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif
#include <cstdio>
#include <cstring>
#include <cctype>

#include "OSGSocketAddress.h"
#include "OSGSocketException.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/** \class OSG::SocketAddress
 *  \brief Network address
 *
 * The class SocketAddress holds an ip-address and a socket port number.
 * It is used to connect, and sendTo Sockets.
 * 
 * Usage:
 * <PRE>
 * SocketAddress a("colossus.world.com",3334);
 * socket.bind(a);
 * cout << a.getHost() << endl;
 * cout << a.getPort() << endl;
 * </PRE>
 **/

/*-------------------------------------------------------------------------*/
/*                       constructors & destructors                        */

/*! Constructor. Create a socket address for the given port and host.
 */
SocketAddress::SocketAddress(const char *host,int port) :
    _sockaddr(NULL)
{
    _sockaddr = new sockaddr_in;

    memset(_sockaddr,0,sizeof(sockaddr_in));

    _sockaddr->sin_family = AF_INET;

    if(host)
        setHost(std::string(host));

    setPort(port);
}

/*! Constructor. Create a socket with predefined type. E.g. ANY is 
    used to bind a socket to all interfaces. BROADCAST chreates a broadcast
    address
 */

#ifdef OSG_DEBUG_OLD_C_CASTS
// For my debugging, should not be active for any other case (GV)
#ifdef INADDR_ANY
#undef INADDR_ANY
#define INADDR_ANY 0x00000000
#endif

#ifdef INADDR_BROADCAST
#undef INADDR_BROADCAST
#define INADDR_BROADCAST 0xffffffff
#endif
#endif

SocketAddress::SocketAddress(SocketAddress::Type type,int port) :
    _sockaddr(NULL)
{
    _sockaddr = new sockaddr_in;

    memset(_sockaddr,0,sizeof(sockaddr_in));

    _sockaddr->sin_family = AF_INET;

    switch(type)
    {
        case ANY:       
            _sockaddr->sin_addr.s_addr = osgHostToNet<UInt32>(
                static_cast<UInt32>(INADDR_ANY));
            break;
        case BROADCAST: 
            _sockaddr->sin_addr.s_addr = osgHostToNet<UInt32>(
                static_cast<UInt32>(INADDR_BROADCAST));
            break;
        default:        
            _sockaddr->sin_addr.s_addr = osgHostToNet<UInt32>(
                static_cast<UInt32>(INADDR_ANY));
    }
    setPort(port);
}

/*! copy Constructor
 */
SocketAddress::SocketAddress(const SocketAddress &source)  :
    _sockaddr(NULL)
{
    _sockaddr = new sockaddr_in;

    *_sockaddr = *(source._sockaddr);
}

/*! Destructor
 */
SocketAddress::~SocketAddress()
{
    delete _sockaddr;
}

/*-------------------------------------------------------------------------*/
/*                              get, set                                   */

/*! Set the port number
 */
void SocketAddress::setPort(int port)
{
    _sockaddr->sin_port = osgHostToNet<UInt16>(port);
}

/*! Set host name
 */
void SocketAddress::setHost(const std::string &host)
{
    struct hostent *hent;
    char const *c;

    // number or name ?
    for(c=host.c_str();
        *c!='\0' && (isdigit(*c) || *c == '.');
        c++) ;
    if(! *c )
    {
        // inet_aton(const char *cp, struct in_addr *pin);

        // ip number was given
        _sockaddr->sin_addr.s_addr = inet_addr(host.c_str());
    }
    else
    {
        // get address of host by name
        hent = gethostbyname(host.c_str());
        if(hent == NULL)
        {
            throw SocketHostError("gethostbyname()");
        }
        // set address
        _sockaddr->sin_addr = *reinterpret_cast<struct in_addr *>(hent->h_addr);
    }
}

/*! Get host as number std::string
 */
std::string SocketAddress::getHost(void) const
{
    return std::string(inet_ntoa(_sockaddr->sin_addr));
}

/*! Get host as name. If not found, return as number
 */
std::string SocketAddress::getHostByName() const
{
    struct hostent *hent;
    std::string result;

    hent=gethostbyaddr(reinterpret_cast<SocketAddrT*>(getSockAddr()),
                       getSockAddrSize(),AF_INET);
    if(hent == NULL)
    {
        // if no host assigned or host unknown
        // then return ip address
        result=inet_ntoa(_sockaddr->sin_addr);
    }
    else
    {
        result=hent->h_name;
    }
    return result;
}

/*! Returns true, if this is a multicast address
 */ 
bool SocketAddress::isMulticast(void)
{
    UInt32 addr = 
        osgNetToHost<UInt32>(static_cast<UInt32>(_sockaddr->sin_addr.s_addr));

    return (addr & 0xC0000) != 0x0000;
}

/*! Get a pointer to the sockaddr struct
 */
sockaddr *SocketAddress::getSockAddr(void) const
{
    return const_cast<struct sockaddr *>(
        reinterpret_cast<const struct sockaddr *>(_sockaddr));
}

/*! Get the size of the sockaddr struct
 */
int SocketAddress::getSockAddrSize(void) const
{
    return sizeof(sockaddr_in);
}

/*! Get port number
 */
int SocketAddress::getPort(void) const
{
    return osgNetToHost<UInt16>(_sockaddr->sin_port);
}

/*-------------------------------------------------------------------------*/
/*                              Comparision                                */

void SocketAddress::operator = (const SocketAddress &other) const
{
    if(this != &other)
    {
        *_sockaddr = *(other._sockaddr);
    }
}

/*! compare equal
 */
bool SocketAddress::operator == (const SocketAddress &other) const
{
    return _sockaddr->sin_addr.s_addr == other._sockaddr->sin_addr.s_addr &&
           _sockaddr->sin_port        == other._sockaddr->sin_port;
}

/*! compare not equal
 */
bool SocketAddress::operator != (const SocketAddress &other) const
{
    return ! (*this == other);
}

/*! compare less
 */
bool SocketAddress::operator < (const SocketAddress &other) const
{
    return _sockaddr->sin_addr.s_addr < other._sockaddr->sin_addr.s_addr ||
    (
        _sockaddr->sin_addr.s_addr == other._sockaddr->sin_addr.s_addr &&
        _sockaddr->sin_port        <  other._sockaddr->sin_port
    );
}
