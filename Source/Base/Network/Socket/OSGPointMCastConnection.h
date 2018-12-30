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


#ifndef _POINTMCASTCONNECTION_H_
#define _POINTMCASTCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>
#include <map>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGPointSockConnection.h"
#include "OSGTime.h"
#include "OSGDgramSocket.h"
#include "OSGDgram.h"
#include "OSGDgramQueue.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING PointMCastConnection : public PointSockConnection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             PointMCastConnection ( void );
    virtual ~PointMCastConnection ( void ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   type info                                  */
    /*! \{                                                                 */

    virtual const ConnectionType *getType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   connection                                 */
    /*! \{                                                                 */

    virtual Channel     connectGroup(const std::string &address,
                                           Time        timeout=-1 );
    virtual void        disconnect  (      void                   );
    virtual Channel     acceptGroup (      Time        timeout=-1 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   synchronisation                            */
    /*! \{                                                                 */

    virtual bool wait  (Time timeout) OSG_THROW (ReadError);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   channel handling                           */
    /*! \{                                                                 */

    virtual Channel selectChannel (Time timeout=-1) OSG_THROW (ReadError);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   create                                     */
    /*! \{                                                                 */

    static PointConnection *create(void);

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   members                                    */
    /*! \{                                                                 */

    DgramSocket                    _mcastSocket;
    DgramSocket                    _responseSocket;
    BaseThreadRefPtr               _recvQueueThread;
    bool                           _recvQueueThreadRunning;
    bool                           _recvQueueThreadStop;
    UInt16                         _seqNumber;
    SocketAddress                  _mcastAddress;
    DgramQueue                     _queue;
    DgramQueue                     _free;
    LockRefPtr                     _lock;
    SocketAddress                  _sender;
    SocketAddress                  _ackDestination;
    Dgram                         *_lastDgram;
    UInt32                         _lastDgramPos;
    bool                           _initialized;
    std::map<SocketAddress,UInt16> _combineAck;
    UInt16                         _maxAck;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name               private helpers                                */
    /*! \{                                                                 */

           bool recvNextDgram  (Dgram *dgram                   );
           void combineAck     (Dgram *dgram,SocketAddress from);
    static void recvQueueThread( void *arg                     );
           bool recvQueue      ( void                          );
           void initialize     ( void                          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   static type                                */
    /*! \{                                                                 */

    static ConnectionType _type;

    /*! \}                                                                 */

    typedef PointSockConnection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    PointMCastConnection(const PointMCastConnection &source);
    PointMCastConnection& operator =(const PointMCastConnection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef PointMCastConnection *PointMCastConnectionP;

OSG_END_NAMESPACE

#endif /* _GROUPMCASTCONNECTION_H_ */
