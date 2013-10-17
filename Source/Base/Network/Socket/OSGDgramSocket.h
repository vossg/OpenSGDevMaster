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

#ifndef _DGRAMSOCKET_H_
#define _DGRAMSOCKET_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBaseDef.h"
#include "OSGSocketException.h"
#include "OSGSocketAddress.h"
#include "OSGSocket.h"

OSG_BEGIN_NAMESPACE

class Dgram;

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING DgramSocket:public Socket
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DgramSocket();
    DgramSocket(const DgramSocket &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   open/close                                 */
    /*! \{                                                                 */

    virtual void open (void);
    virtual void close(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   read, write                                */
    /*! \{                                                                 */

#if 0
    int recvFrom(      void           *buf ,
                       int             size,
                       SocketAddress  &from );
#endif

    int recvFrom(      Dgram          &buf ,
                       SocketAddress  &from );
    int peekFrom(      void           *buf ,
                       int             size,
                       SocketAddress  &from );
    int recvFrom(      NetworkMessage &msg ,
                       SocketAddress  &from );
    int sendTo  (const void           *buf ,
                       int             size,
                 const SocketAddress  &to   );
    int sendTo  (      NetworkMessage &msg ,
                 const SocketAddress  &to   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                multicast                                     */
    /*! \{                                                                 */

    void join             (const SocketAddress &group,
                           const SocketAddress &interf=
                                 SocketAddress(SocketAddress::ANY));
    void leave            (const SocketAddress &group,
                           const SocketAddress &interf=
                                 SocketAddress(SocketAddress::ANY));
    void setTTL           (      unsigned char ttl                );
    void setMCastInterface(const SocketAddress &interf            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   assignment                                 */
    /*! \{                                                                 */

	const DgramSocket & operator =(const DgramSocket &source);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    int recvFromInternal(void           *buf ,
                         int             size,
                         SocketAddress  &from );

    typedef Socket Inherited;
};

OSG_END_NAMESPACE

#endif
