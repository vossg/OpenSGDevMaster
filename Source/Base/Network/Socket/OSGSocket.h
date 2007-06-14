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

#ifndef _SOCKET_H_
#define _SOCKET_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"
#include "OSGSocketException.h"
#include "OSGSocketAddress.h"

OSG_BEGIN_NAMESPACE

class NetworkMessage;

class OSG_BASE_DLLMAPPING Socket
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Socket(void);
    Socket(const Socket &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Socket();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 open, close, connect                         */
    /*! \{                                                                 */

    virtual void open   (      void                       ) = 0;
    virtual void close  (      void                       ) = 0;
            void bind   (const SocketAddress &address=
                         SocketAddress(SocketAddress::ANY));
            void listen (      int maxPending=10          );
            void connect(const SocketAddress &address     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 read, write                                  */
    /*! \{                                                                 */

    int recv         (      void           *buf,int size);
    int recvAvailable(      void           *buf,int size);
    int recv         (      NetworkMessage &msg         );
    int peek         (      void           *buf,int size);
    int send         (const void           *buf,int size);
    int send         (      NetworkMessage &msg         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 state access                                 */
    /*! \{                                                                 */

    void          setReusePort      (bool   value   );
    void          setBlocking       (bool   value   );
    SocketAddress getAddress        (void           );
    void          setReadBufferSize (int    size    );
    void          setWriteBufferSize(int    size    );
    int           getReadBufferSize (void           );
    int           getWriteBufferSize(void           );
    int           getAvailable      (void           );
    bool          waitReadable      (double duration);
    bool          waitWritable      (double duration);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assignment                              */
    /*! \{                                                                 */

	const Socket & operator =(const Socket &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Error information                       */
    /*! \{                                                                 */

    static int         getError       (void);
    static int         getHostError   (void);
    static std::string getErrorStr    (void);
    static std::string getHostErrorStr(void);

    /*! \}      
                                                           */
    /*==========================  PROTECTED ===============================*/
  protected:

    /*! Socket option type. Used to hide the different interface 
        implementations
     */
#if defined WIN32
    typedef char FAR  SocketOptT;
#else
    typedef void      SocketOptT;
#endif

    /*! Socket length type. Used to hide the different interface 
        implementations
     **/
#if defined(__linux) || defined(__APPLE__)
    typedef socklen_t SocketLenT;
#else
    typedef int       SocketLenT;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   member                                     */
    /*! \{                                                                 */

    int _sd;

    /*! \}                                                                 */
    /*==========================  PRIVATE =================================*/
  private:

    friend class SocketSelection;

    /*---------------------------------------------------------------------*/
    /*! \name                  static member                               */
    /*! \{                                                                 */

    static int  initialized;

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif
