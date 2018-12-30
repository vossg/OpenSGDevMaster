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


#ifndef _GROUPSOCKCONNECTION_H_
#define _GROUPSOCKCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGGroupConnection.h"
#include "OSGTime.h"
#include "OSGStreamSocket.h"

OSG_BEGIN_NAMESPACE

class PointSockConnection;

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING GroupSockConnection : public GroupConnection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             GroupSockConnection ( void );
    virtual ~GroupSockConnection ( void ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   type info                                  */
    /*! \{                                                                 */

    virtual const ConnectionType *getType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   connection                                 */
    /*! \{                                                                 */

    virtual Channel     connectPoint(const std::string &address,
                                           Time        timeout=-1 );
    virtual void        disconnect  (      Channel     channel    );
    virtual Channel     acceptPoint (      Time        timeout=-1 );
    virtual std::string bind        (const std::string &interf    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   params                                     */
    /*! \{                                                                 */

    virtual void setParams(const std::string &params);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   channel handling                           */
    /*! \{                                                                 */

    virtual Channel selectChannel   (Time timeout=-1) OSG_THROW (ReadError);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   create                                     */
    /*! \{                                                                 */

    static GroupConnection *create(void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Types                                      */
    /*! \{                                                                 */

    /*! \nohierarchy
     */

    struct SocketBufferHeader {
        UInt32 size;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   IO Implementation                          */
    /*! \{                                                                 */

    virtual void read             (MemoryHandle mem, UInt32 size);
    virtual void readBuffer       (void) OSG_THROW (ReadError);
    virtual void write            (MemoryHandle mem, UInt32 size);
    virtual void writeBuffer      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   members                                    */
    /*! \{                                                                 */

    StreamSocket               _acceptSocket;
    std::vector<StreamSocket>  _sockets;
    std::vector<SocketAddress> _remoteAddresses;
    ChannelIndex               _readIndex;
    std::vector<UInt8>         _socketReadBuffer;
    std::vector<UInt8>         _socketWriteBuffer;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   synchronisation                            */
    /*! \{                                                                 */
    
    virtual bool wait  (Time timeout) OSG_THROW (ReadError );
    virtual void signal(void        ) OSG_THROW (WriteError);
    
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class PointSockConnection;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   static type                                */
    /*! \{                                                                 */

    static ConnectionType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   internal methods                           */
    /*! \{                                                                 */

    static bool connectSocket(StreamSocket  &socket,
                              std::string    address,
                              SocketAddress &destination,
                              Time           timeout);
    static bool acceptSocket (StreamSocket  &accept,
                              StreamSocket  &from,
                              SocketAddress &destination,
                              Time           timeout);

    /*! \}                                                                 */

    typedef GroupConnection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    GroupSockConnection(const GroupSockConnection &source);
    GroupSockConnection& operator =(const GroupSockConnection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef GroupSockConnection *GroupSockConnectionP;

OSG_END_NAMESPACE

#endif /* _GROUPSOCKCONNECTION_H_ */
