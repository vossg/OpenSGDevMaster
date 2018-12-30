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


#ifndef _GROUPMCASTCONNECTION_H_
#define _GROUPMCASTCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGGroupSockConnection.h"
#include "OSGTime.h"
#include "OSGStreamSocket.h"
#include "OSGDgramQueue.h"

OSG_BEGIN_NAMESPACE

class PointMCastConnection;

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING GroupMCastConnection : 
    public GroupSockConnection
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             GroupMCastConnection ( void );
    virtual ~GroupMCastConnection ( void ); 

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   params                                     */
    /*! \{                                                                 */

    virtual void setParams(const std::string &params);

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

    struct SocketBufferHeader 
    {
        UInt32 size;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Members                                    */
    /*! \{                                                                 */

    DgramSocket                _mcastSocket;
    SocketAddress              _mcastAddress;
    BaseThreadRefPtr           _sendQueueThread;
    bool                       _sendQueueThreadRunning;
    bool                       _sendQueueThreadStop;
    DgramQueue                 _queue;
    DgramQueue                 _free;
    LockRefPtr                 _lock;
    UInt16                     _seqNumber;
    UInt32                     _receivers;
    UInt32                     _windowSize;
    std::vector<SocketAddress> _receiver;
    std::vector<SocketAddress> _waitFor;
    bool                       _initialized;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   IO Implementation                          */
    /*! \{                                                                 */

    virtual void write            (MemoryHandle mem, UInt32 size);
    virtual void writeBuffer      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   synchronisation                            */
    /*! \{                                                                 */
    
    virtual bool wait  (Time timeout) OSG_THROW (ReadError);
    virtual void signal(void        ) OSG_THROW (WriteError);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class PointMCastConnection;
    
    /*---------------------------------------------------------------------*/
    /*! \name               private helpers                                */
    /*! \{                                                                 */

           bool checkChannels     ( void      );
    static void sendQueueThread   ( void *arg );
           bool sendQueue         ( void      );
           void initialize        ( void      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   static members                             */
    /*! \{                                                                 */

    static ConnectionType _type;

    /*! \}                                                                 */

    typedef GroupSockConnection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    GroupMCastConnection(const GroupMCastConnection &source);
    GroupMCastConnection& operator =(const GroupMCastConnection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef GroupMCastConnection *GroupMCastConnectionP;

OSG_END_NAMESPACE

#endif /* _GROUPMCASTCONNECTION_H_ */
