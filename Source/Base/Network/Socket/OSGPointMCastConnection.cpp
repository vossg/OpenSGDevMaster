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
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGBaseThread.h"
#include "OSGSocketSelection.h"
#include "OSGBinaryMessage.h"
#include "OSGPointMCastConnection.h"
#include "OSGGroupMCastConnection.h"
#include "OSGConnectionType.h"

OSG_USING_NAMESPACE

/** \class OSG::PointMCastConnection
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

PointMCastConnection::PointMCastConnection():
     Inherited             (     ),
    _mcastSocket           (     ),
    _responseSocket        (     ),
    _recvQueueThread       (NULL ),
    _recvQueueThreadRunning(false),
    _recvQueueThreadStop   (false),
    _seqNumber             (    0),
    _mcastAddress          (     ),
    _queue                 (     ),
    _free                  (     ),
    _lock                  (NULL ),
    _sender                (     ),
    _ackDestination        (     ),
    _lastDgram             (NULL ),
    _lastDgramPos          (0    ),
    _initialized           (false),
    _combineAck            (     ),
    _maxAck                (0    )

{
    char lockName[256];
    sprintf(lockName,"PointMCastConnection%p", static_cast<void *>(this));

    // create locks
    _lock     = Lock::get(lockName, false);

    // fill dgramqueue
    for(UInt32 dI = 0 ; dI < OSG_DGRAM_QUEUE_LEN ; ++dI)
    {
        Dgram *pNew = new Dgram();

        _free.put(pNew);
    }

    _acceptSocket.open();
    _acceptSocket.setReusePort(true);

/*
    _socketWriteBuffer.resize(131071);
    // reserve first bytes for buffer size
    writeBufAdd(&_socketWriteBuffer[sizeof(SocketBufferHeader)],
                _socketWriteBuffer.size()-sizeof(SocketBufferHeader));
*/
}

/*! Destructor
 */
PointMCastConnection::~PointMCastConnection(void)
{
    // indicate thread stop
    _recvQueueThreadStop = true;
    // wait for stop
    BaseThread::join(_recvQueueThread);    

    _recvQueueThread = NULL;

    // close socket
    _mcastSocket.close();
    // free queues
    _lock->acquire();
    while(!_free.empty())
        delete _free.get(_lock);
    while(!_queue.empty())
        delete _queue.get(_lock);
    _lock->release();
    // close socket
    _acceptSocket.close();

    _lock = NULL;
}

/*! get connection type
 */
const ConnectionType *PointMCastConnection::getType()
{
    return &_type;
}

/*-------------------------------------------------------------------------*/
/*                            connection                                   */

/*! connect to the given group. If timeout is reached, -1 is
    returned
 */
Connection::Channel PointMCastConnection::connectGroup(
    const std::string &address,
    Time               timeout)
{
    Channel channel = Inherited::connectGroup(address,timeout);
    return channel;
}

/*! disconnect the given channel
 */
void PointMCastConnection::disconnect(void)
{
    _socket.close();
}

/*! accept an icomming grop connection. If timeout is reached,
    -1 is returned. If timeout is -1 then wait without timeout
 */
Connection::Channel PointMCastConnection::acceptGroup(Time timeout)
{
    Channel channel = Inherited::acceptGroup(timeout);
    return channel;
}

/*-------------------------------------------------------------------------*/
/*                              channel handling                           */

/*! select the next channel for reading. If timeout is not -1
    then -1 is returned if timeout is reached
*/
Connection::Channel PointMCastConnection::selectChannel(Time timeout)
    OSG_THROW (ReadError)
{
    if(_pointToPoint)
        return Inherited::selectChannel(timeout);
    try
    {
        if(!_initialized)
            initialize();
        // todo
        if(isReadBufferEmpty() && 
           !_lastDgram && 
           _queue.empty())
        {
            if(timeout == -1)
            {
                // wait for a dgram
                _lock->acquire();
                _queue.wait(_lock);
                _lock->release();
                return 0;
            }
            if(timeout == 0)
                return -1;
            while(_queue.empty() && timeout > 0)
            {
                _mcastSocket.waitReadable(.1);
                timeout-=.1;
            }
            if(_queue.empty())
                return -1;
        }
    }
    catch(SocketException &e)
    {
        throw ReadError(e.what());
    }
    return 0;
}

/*-------------------------------------------------------------------------*/
/*                            sync                                         */

/*! wait for signal
 */
bool PointMCastConnection::wait(Time timeout) OSG_THROW (ReadError)
{
    UInt32 tag;

    if(_pointToPoint)
        return Inherited::wait(timeout);
    try
    {
        if(selectChannel(timeout) < 0)
            return false;
        getValue(tag);
        if(tag != 314156)
        {
            FFATAL(("Stream out of sync in PointMCastConnection\n"));
            throw ReadError("Stream out of sync");
        }
    }
    catch(SocketError &e)
    {
        throw ReadError(e.what());
    }
    return true;
}

/*-------------------------- create ---------------------------------------*/

/** \brief create conneciton
 */

PointConnection *PointMCastConnection::create(void)
{
    return new PointMCastConnection();
}

/*-------------------------------------------------------------------------*/
/*                              read write                                 */

/** Read data into given memory
 *
 * Read data form the current read socket. The read socket is that
 * socket, that was selectet in selectChannel.
 *
 **/

void PointMCastConnection::read(MemoryHandle mem,UInt32 size)
{
    if(_pointToPoint)
    {
        Inherited::read(mem,size);
        return;
    }
    Dgram *dgram  = NULL;
    char  *buffer = reinterpret_cast<char*>(mem);
    UInt32 len;
    UInt32 dgramPos;

    if(!_initialized)
        initialize();

    while(size)
    {
        if(_lastDgram)
        {
            dgramPos = _lastDgramPos;
            dgram = _lastDgram;
        }
        else
        {
            // get next dgram
            _lock->acquire();
            dgram = _queue.get(_lock);
            _lock->release();
            dgramPos = 0;
            if(dgram->getSize() == 0)
                throw ReadError("Channel closed\n");
        }
        // copy to buffer
        len = osgMin(size,dgram->getSize()-dgramPos);
        memcpy(buffer,dgram->getData()+dgramPos,len);
        buffer   += len;
        size     -= len;
        dgramPos += len;
        if(dgramPos == dgram->getSize())
        {
            // put to free queue
            _lock->acquire();
            _free.put(dgram);
            _lock->release();
            _lastDgram = NULL;
        }
        else
        {
            _lastDgram    = dgram;
            _lastDgramPos = dgramPos;
        }
    }
}

/** Read next data block
 *
 * The stream connection uses only BinaryDataHandler buffer. If more
 * then one buffer is present, then this methode must be changed!
 *
 */

void PointMCastConnection::readBuffer() OSG_THROW (ReadError)
{
    if(_pointToPoint)
    {
        Inherited::readBuffer();
        return;
    }

    static int sumSize=0;
    Dgram       *dgram  = NULL;
    UInt32       size   = readBufBegin()->getSize();
    MemoryHandle buffer = readBufBegin()->getMem();
    UInt32       len;
    UInt32       dgramPos;

    if(!_initialized)
        initialize();

    do
    {
        if(_lastDgram)
        {
            dgramPos = _lastDgramPos;
            dgram = _lastDgram;
        }
        else
        {
            // get next dgram
            _lock->acquire();
            dgram = _queue.get(_lock);
            _lock->release();
            dgramPos = 0;
            if(dgram->getSize() == 0)
                throw ReadError("Channel closed");
        }
        // copy to buffer
        len = osgMin(size,dgram->getSize()-dgramPos);
        memcpy(buffer,dgram->getData()+dgramPos,len);
        buffer   += len;
        size     -= len;
        dgramPos += len;
        if(dgramPos == dgram->getSize())
        {
            // put to free queue
            _lock->acquire();
            _free.put(dgram);
            _lock->release();
            _lastDgram = NULL;
        }
        else
        {
            _lastDgram    = dgram;
            _lastDgramPos = dgramPos;
        }
    }
    while(size && !_queue.empty());
    // set data size
    readBufBegin()->setDataSize(readBufBegin()->getSize()-size);
    sumSize += readBufBegin()->getDataSize();
}    

/*-------------------------------------------------------------------------*/
/*                              private helpers                            */

/*! read next dgram from mcast or private socket
 */
bool PointMCastConnection::recvNextDgram(Dgram *dgram)
{
    SocketSelection selection;
    SocketAddress   from;
    UInt32          length;
    
    selection.setRead(_mcastSocket);
    selection.setRead(_responseSocket);
    if(!selection.select(0.5))
        return false;
    if(selection.isSetRead(_responseSocket))
    {
#if 0
        length = _responseSocket.recvFrom(dgram->getBuffer(),
                                          dgram->getBufferCapacity(),
                                          from);
#endif
        length = _responseSocket.recvFrom(*dgram,
                                          from);

        dgram->setBufferSize(length);
#if 0
// ????
        // from sender
        if(from == _sender && !_combineAck.empty())
        {
            exit(0);


            if(_maxAck == dgram->getId())
            {
                // do we have all acks ?
                dgram->setId(_maxAck);
                dgram->setResponseSize();
                dgram->setResponseAck(true);
#ifdef TEST_LOST_DGRAM_RATE
                if(drand48()>TEST_LOST_DGRAM_RATE)
#endif
                    _responseSocket.sendTo(
                        dgram->getBuffer(),
                        dgram->getBufferSize(),
                        _ackDestination);
                return false;
            }
            else
            {
                return true;
            }
        }
#endif
        combineAck(dgram,from);
    } 
    if(selection.isSetRead(_mcastSocket))
    {
#if 0
        length = _mcastSocket.recvFrom(dgram->getBuffer(),
                                       dgram->getBufferCapacity(),
                                       from);
#endif
        length = _mcastSocket.recvFrom(*dgram,
                                        from);
        dgram->setBufferSize(length);
        // ignore packages from wrong destination
        if(from != _sender)
            return false;
        else
            return true;
    }
    else
    {
        return false;
    }
}

/*! combine several acks to 1 ack stream
 */
void PointMCastConnection::combineAck(Dgram *dgram,SocketAddress from)
{
    UInt16 maxAck;

    if(dgram)
    {
        // do we expect acks from different source
        if(_combineAck.count(from)==0)
        {
            FFATAL(("no ack from other expected\n"));
            return;
        }
        // ack retransmission
        if( Dgram::less(dgram->getId(),_combineAck[from] ) )
        {
//        printf("Ack restranmisson\n");
            return;
        }
        _combineAck[from] = dgram->getId();
    }

    maxAck = _seqNumber-1;
    for(std::map<SocketAddress,UInt16>::iterator aI
            = _combineAck.begin() ; 
        aI != _combineAck.end() ; ++aI)
    {
        if( Dgram::less(aI->second,maxAck) )
            maxAck = aI->second;
    }

    // when _max ack is now greate

    if( Dgram::less(_maxAck,maxAck))
    {
        Dgram response;

        _maxAck = maxAck;
        response.setResponseSize();
        response.setId(_maxAck);
        response.setResponseAck(true);

        _responseSocket.sendTo(
            response.getBuffer(),
            response.getBufferSize(),
            _ackDestination);
    }
}

/*! recv queue
 */
bool PointMCastConnection::recvQueue(void)
{
    SocketAddress  from;
    Dgram         *dgram;
    Dgram          response;
    bool           missing=false;
    Time           ignoreT=getSystemTime();
    UInt16         id;

#ifdef TEST_LOST_DGRAM_RATE
    srand48((long int)(10000*getSystemTime()));
#endif

    for(;;)
    {
        // get free dgram
        _lock->acquire();
        dgram   =_free.get(_lock);
        _lock->release();
        do
        {
            // ignore for a while
            if(missing)
                ignoreT = getSystemTime();
            do
            {
                if(_recvQueueThreadStop)
                    return true;

                while(!recvNextDgram(dgram))
                {
                    if(_recvQueueThreadStop)
                        return true;
                    try
                    {
                        while(_socket.waitReadable(0))
                        {
                            char buffer;
                            if(_socket.recv(&buffer,1) <= 0)
                            {
                                // put EOT to the queue
                                dgram->setSize(0);
                                _lock->acquire();
                                _queue.put(dgram);
                                _lock->release();
                                FLOG(("Connection lost\n"));
                                return false;
                            }
                        }
                    }
                    catch(SocketException &)
                    {
                        // put EOT to the queue
                        dgram->setSize(0);
                        _lock->acquire();
                        _queue.put(dgram);
                        _lock->release();
                        FLOG(("Connection lost\n"));
                        return false;
                    }
                }
                id = dgram->getId();
            }
            while( missing &&
                   id != _seqNumber &&
                   (getSystemTime() - ignoreT) < 0.01);

            missing = false;
            response.setId(id);

            // ack request ?
            if(dgram->getSize() == 0)
            {
                if( !Dgram::less(id,_seqNumber ) )
                {
                    missing = true;
                    response.setId(_seqNumber);
                }
//                printf("ack request %d %d\n",id,missing);
            }
            else
            {
//                printf("%d got %d\n",id,_seqNumber);
                if( dgram->getId() == _seqNumber)
                {
                    // got expected dgram.
                    // put to queue
                    _lock->acquire();
                    _queue.put(dgram);
                    _lock->release();
                }
                else
                {
                    // ignore if unneccesary retransmission
                    if( Dgram::less(id,_seqNumber ) )
                    {
                        continue;
                    }
                    else
                    {
                        missing = true;
                        response.setId(_seqNumber);
                    }
                }
            }

//                printf("Responde %d\n",response.getId());
            // prepare response
            response.setResponseAck(!missing);
            response.setResponseSize();

            // send response if nak or no data in the queue
            if(!response.getResponseAck() || 
               !_mcastSocket.waitReadable(0))
            {
#ifdef TEST_LOST_DGRAM_RATE
                if(drand48()>TEST_LOST_DGRAM_RATE)
#endif
                    if(response.getResponseAck())
                    {
                        // send response if no ack combination
                        // or ack request 
                        if(_combineAck.empty() || id == _maxAck)
                            _responseSocket.sendTo(response.getBuffer(),
                                                   response.getBufferSize(),
                                                   _ackDestination);
                        else
                            combineAck(NULL,_sender);
                    }
                    else
                    {
                        // send nak to sender
                        _responseSocket.sendTo(response.getBuffer(),
                                               response.getBufferSize(),
                                               _sender);
                    }
            }
        }
        while(id != _seqNumber || missing);
        _seqNumber++;
    }    

//    return true;
}

void PointMCastConnection::recvQueueThread(void *arg)
{
    PointMCastConnection *the=static_cast<PointMCastConnection*>(arg);
    try 
    {
        the->recvQueue();
    }
    catch(SocketException &e)
    {
        SFATAL << "Error in dgram reader thread:" << e.what() << std::endl;
    }
    the->_recvQueueThreadRunning = false;
}

/*! initialize connection
 */
void PointMCastConnection::initialize()
{
    std::string   group;
    BinaryMessage message;
    std::string   fromHost;
    UInt32        fromPort;
    UInt32        combineCount;
    std::string   host;
    UInt32        port;
    char          threadName[256];

    sprintf(threadName,"PointMCastConnection%p", static_cast<void *>(this));

    // get info about the group
    _socket.recv(message);
    // group and port
    group = message.getString();
    port  = message.getUInt32();
    // get seq number
    _seqNumber = message.getUInt32();
    _maxAck = _seqNumber - 1;
    // get port
    fromPort = message.getUInt32();

    _sender = SocketAddress(_remoteAddress.getHost().c_str(),fromPort);

    std::cout << _remoteAddress.getHost() << " " << fromPort << std::endl;

    // prepare socket to receive mcast packages
    _mcastSocket.open();
    _mcastSocket.setReusePort(true);
    _mcastSocket.setReadBufferSize(524288);
    _mcastSocket.bind(SocketAddress(SocketAddress::ANY,port));
    try
    {
        _mcastSocket.join(SocketAddress(group.c_str()));
    }
    catch(...) {}
    // set multicast interface
    if(!getInterface().empty())
    {
        _mcastSocket.setMCastInterface(SocketAddress(getInterface().c_str()));
    }

    _responseSocket.open();
    _responseSocket.bind(SocketAddress(SocketAddress::ANY,0));

    // tell the group from wich port requests are comming
    message.clear();
    message.putUInt32(_responseSocket.getAddress().getPort());
    _socket.send(message);

    // get ack destination info
    _socket.recv(message);

    message.getUInt32(combineCount);
//    printf("%d\n",combineCount);
    while(combineCount--)
    {
        host=message.getString();
        port=message.getUInt32();
        _combineAck[SocketAddress(host.c_str(),port)]=_seqNumber-1;
    }

    host=message.getString();
    port=message.getUInt32();
    if(host.empty())
        host = _remoteAddress.getHost();
    _ackDestination = SocketAddress(host.c_str(),port);

    // start reader thread
    _recvQueueThread=BaseThread::get(threadName, false);
    _recvQueueThreadRunning = true;
    _recvQueueThreadStop    = false;
    _recvQueueThread->runFunction( recvQueueThread, static_cast<void *>(this));

    _initialized = true;
//    printf("init end\n");
}

/*-------------------------------------------------------------------------*/
/*                              static type                                */

ConnectionType PointMCastConnection::_type(
    &PointMCastConnection::create,
    "Multicast");
