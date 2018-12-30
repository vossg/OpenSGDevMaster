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


#ifndef _POINTSOCKCONNECTION_H_
#define _POINTSOCKCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGPointConnection.h"
#include "OSGTime.h"
#include "OSGStreamSocket.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING PointSockConnection : public PointConnection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             PointSockConnection ( void );
    virtual ~PointSockConnection ( void ); 

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
    virtual Channel     connectGroup(const std::string &address,
                                           Time        timeout=-1 );
    virtual void        disconnect  (      void                   );
    virtual Channel     acceptGroup (      Time        timeout=-1 );
    virtual Channel     acceptPoint (      Time        timeout=-1 );
    virtual std::string bind        (const std::string &interf    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   synchronisation                            */
    /*! \{                                                                 */

    virtual bool wait  (Time timeout) OSG_THROW (ReadError );
    virtual void signal(void        ) OSG_THROW (WriteError);

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
    virtual void write            (MemoryHandle mem, UInt32 size);
    virtual void writeBuffer      (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   members                                    */
    /*! \{                                                                 */

    StreamSocket              _acceptSocket;
    StreamSocket              _socket;
    SocketAddress             _remoteAddress;
    std::vector<UInt8>        _socketReadBuffer;
    std::vector<UInt8>        _socketWriteBuffer;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                   static type                                */
    /*! \{                                                                 */

    static ConnectionType _type;

    /*! \}                                                                 */

    typedef PointConnection Inherited;

	// prohibit default functions (move to 'public' if you need one)
    PointSockConnection(const PointSockConnection &source);
    PointSockConnection& operator =(const PointSockConnection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef PointSockConnection *PointSockConnectionP;

OSG_END_NAMESPACE

#endif /* _GROUPSOCKCONNECTION_H_ */
