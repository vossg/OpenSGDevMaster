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

#include <cstring>
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
#endif
#include <cerrno>
#include <cstdio>

#include <OSGSocketException.h>
#include <OSGSocket.h>
#include <OSGSocketSelection.h>
#include <OSGTime.h>

OSG_USING_NAMESPACE

/** \class OSG::SocketSelection
 *  \ingroup GrpBaseNetwork
 *  \brief Wait or check one or more sockets for read/write blocking
 *  \author Marcus Roth
 *
 * You can use a SocketSelection to wait for data on one ore more sockets.
 * It is possible to use a timeout as a maximum wait time.
 *
 * Example:
 * <PRE>
 * SocketSelection sel;
 * Socket s1,s2;
 * ...
 * sel.setRead(s1);
 * sel.setRead(s2);
 * if(sel.select(2))
 * {
 *   if(sel.isSetRead(s1)) cout << "Data on s1" << endl;
 *   if(sel.isSetRead(s2)) cout << "Data on s2" << endl;
 * }
 * else
 * {
 *   cout << "No data after 2 seconds" << endl;
 * }
 * </PRE>
 **/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

SocketSelection::SocketSelection() :
    _fdSetRead (NULL),
    _fdSetWrite(NULL)
{
    _fdSetRead  = new fd_set;
    _fdSetWrite = new fd_set;

    clear();
}

/** \brief Copy constructor
 */

SocketSelection::SocketSelection(const SocketSelection &source) :
    _fdSetRead (NULL),
    _fdSetWrite(NULL)
{
    _fdSetRead  = new fd_set;
    _fdSetWrite = new fd_set;

    *_fdSetRead  = *(source._fdSetRead);
    *_fdSetWrite = *(source._fdSetWrite);
}

/** \brief Destructor
 */

SocketSelection::~SocketSelection()
{
    delete _fdSetRead;
    delete _fdSetWrite;
}

/** \brief Clear all settings
 */

void SocketSelection::clear()
{
    FD_ZERO(_fdSetRead);
    FD_ZERO(_fdSetWrite);
}

/** \brief Clear read settings for the given socket
 *
 * \param sock    For this socket the read flag is cleared
 */
void SocketSelection::clearRead(const Socket &sock)
{
    FD_CLR(sock._sd,_fdSetRead);
}

/** \brief Clear write settings for the given socket
 *
 * \param sock    For this socket the write flag is cleared
 */
void SocketSelection::clearWrite(const Socket &sock)
{
    FD_CLR(sock._sd,_fdSetWrite);
}

/** \brief Set read flag for the given socket
 *
 * \param sock    For this socket the read flag is set
 */
void SocketSelection::setRead(const Socket &sock)
{
    FD_SET(sock._sd,_fdSetRead);
}

/** \brief Set write flag for the given socket
 *
 * \param sock    For this socket the write flag is set
 */
void SocketSelection::setWrite(const Socket &sock)
{
    FD_SET(sock._sd,_fdSetWrite);
}

/** \brief Start selection
 *
 * Wait for the first read or write flag to be true. All other 
 * flags are cleared.
 *
 * \param duration   Maximum wait time in seconds
 *
 * \return Number of set flags
 */
int SocketSelection::select(double duration)
{
    timeval tVal,*tValP;
    int count;
    
    if(duration<0)
    {
        tValP=NULL;
    }
    else
    {       
        tVal.tv_sec  = int( duration );
        tVal.tv_usec = int( (duration-tVal.tv_sec)*1000000 );
        tValP=&tVal;
    }
    do
    {
        count=::select( FD_SETSIZE, 
                       _fdSetRead, 
                       _fdSetWrite,
                        NULL,
                        tValP);
        if(count < 0)
        {
#ifndef WIN32
            // select was interrupted by a signal. Ignore this
            // and retry to select
            if(errno != EINTR)
                throw SocketError("select()");
#else
            throw SocketError("select()");
#endif
        }
    }
    while(count < 0);
    return count;
}

/** \brief Start selection
 *
 * Wait for the first read or write flag to be true. The resulting
 * flags are set in result.
 *
 * \param duration   Maximum wait time in seconds
 * \param result     Result selection
 *
 * \return Number of set flags
 */
int SocketSelection::select(double duration,SocketSelection &result) const
{
    result=*this;
    return result.select(duration);
}

/** \brief Check if read flag is set for a socket
 *
 * \param sock    For this socket the read flag is tested
 */
bool SocketSelection::isSetRead(const Socket &sock)
{
    if(FD_ISSET(sock._sd, _fdSetRead))
        return true;
    else
        return false;
}

/** \brief Check if write flag is set for a socket
 *
 * \param sock    For this socket the write flag is tested
 */
bool SocketSelection::isSetWrite(const Socket &sock)
{
    if(FD_ISSET(sock._sd, _fdSetWrite))
        return true;
    else
        return false;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

const SocketSelection & SocketSelection::operator =(
    const SocketSelection &source)
{
    *_fdSetRead  = *(source._fdSetRead);
    *_fdSetWrite = *(source._fdSetWrite);

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
    static Char8 cvsid_hpp       [] = OSG_SOCKET_SELECTION_HEADER_CVSID;
}

