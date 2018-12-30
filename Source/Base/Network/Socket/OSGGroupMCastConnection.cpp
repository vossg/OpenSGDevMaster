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

#include <set>
#include <sstream>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGBaseThread.h"
#include "OSGSocketSelection.h"
#include "OSGBinaryMessage.h"
#include "OSGGroupMCastConnection.h"
#include "OSGConnectionType.h"

#define USE_EARLY_SEND

OSG_USING_NAMESPACE

/** \class OSG::GroupMCastConnection
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

GroupMCastConnection::GroupMCastConnection():
     Inherited             (     ),
    _mcastSocket           (     ),
    _mcastAddress          (     ),
    _sendQueueThread       (NULL ),
    _sendQueueThreadRunning(false),
    _sendQueueThreadStop   (false),
    _queue                 (     ),
    _free                  (     ),
    _lock                  (NULL ),
    _seqNumber             (0    ),
    _receivers             (0    ),
    _windowSize            (0    ),
    _receiver              (     ),
    _waitFor               (     ),
    _initialized           (false)
{
    char lockName[256];
    sprintf(lockName,"GroupMCastConnection%p", static_cast<void *>(this));

    // create locks
    _lock     = Lock::get(lockName, false);
    // fill dgramqueue
    for(UInt32 dI = 0 ; dI < OSG_DGRAM_QUEUE_LEN ; ++dI)
        _free.put(new Dgram());
    // prepare mcast socket
    _mcastSocket.open();
    _mcastSocket.bind();
    _mcastSocket.setReadBufferSize(262144);
    // set window size
    _windowSize = _mcastSocket.getReadBufferSize()/(OSG_DGRAM_LEN) - 1;
    _windowSize = osgMax(UInt32(2),_windowSize);
}

/*! Destructor
 */
GroupMCastConnection::~GroupMCastConnection(void)
{
    Dgram *dgram;
    _sendQueueThreadStop = true;

    // get free dgram
    _lock->acquire();
    dgram = _free.get(_lock);
    dgram->setSize(0);
    _queue.put(dgram);
    _lock->release();
    // wait for stop
    if(_sendQueueThread)
    {
        BaseThread::join(_sendQueueThread);    

        _sendQueueThread = NULL;
    }
    // close socket
    _mcastSocket.close();
    // free queues
    _lock->acquire();
    while(!_free.empty())
        delete _free.get(_lock);
    while(!_queue.empty())
        delete _queue.get(_lock);
    _lock->release();

    _lock = NULL;
}

/*! get connection type
 */
const ConnectionType *GroupMCastConnection::getType()
{
    return &_type;
}

/*-------------------------------------------------------------------------*/
/*                            connection                                   */

/*! connect to the given point. If timeout is reached, -1 is
    returned
 */
GroupConnection::Channel GroupMCastConnection::connectPoint(
    const std::string &address,
    Time               timeout)
{
    Channel channel = Inherited::connectPoint(address,timeout);
    return channel;
}

/*! disconnect the given channel
 */
void GroupMCastConnection::disconnect(Channel channel)
{
    ChannelIndex index = channelToIndex(channel);

    Inherited::disconnect(channel);
    _lock->acquire();

    // remove channel from _receiver/_waitFor
    std::vector<SocketAddress>::iterator rIt = _receiver.begin() + index;
    std::vector<SocketAddress>::iterator wIt = std::find(_waitFor.begin(),
                                                         _waitFor.end  (),
                                                         _receiver[index] );

    if(wIt != _waitFor.end())
        _waitFor.erase(wIt);

    _receiver.erase(rIt);

    _lock->release();
}

/*! accept an icomming point connection. If timeout is reached,
    -1 is returned. If timeout is -1 then wait without timeout
 */
GroupConnection::Channel GroupMCastConnection::acceptPoint(Time timeout)
{
    Connection::Channel channel = Inherited::acceptPoint(timeout);
    return channel;
}

/*! parse the params string.
 */
void GroupMCastConnection::setParams(const std::string &params)
{
    if(params.empty())
        return;

    Inherited::setParams(params);

    std::string option = "TTL=";
    std::string::size_type i = 0;
    if((i=params.find(option)) != std::string::npos)
    {
        std::string str = params.substr(i + option.size());

        std::stringstream ss;
        std::string::size_type j = 0;
        while(j < str.length() && str[j] != ',' && isdigit(str[j]))
        {
            ss << str[j++];
        }
        UInt32 ttl;
        ss >> ttl;
        if(ttl > 255)
            ttl = 255;
        _mcastSocket.setTTL(static_cast<unsigned char>(ttl));
        FINFO(("GroupMCastConnection::setParams : setting ttl to %u.\n", ttl));
    }
}

/*-------------------------------------------------------------------------*/
/*                            sync                                         */

/*! wait for signal
 */
bool GroupMCastConnection::wait(Time timeout) OSG_THROW (ReadError)
{
    // todo
    return Inherited::wait(timeout);
}

/*! send signal
 */
void GroupMCastConnection::signal(void) OSG_THROW (WriteError)
{
    UInt32 tag=314156;
    putValue(tag);
    flush();
}

/*-------------------------- helpers --------------------------------------*/

/** \brief create conneciton
 */

GroupConnection *GroupMCastConnection::create(void)
{
    return new GroupMCastConnection();
}

/*-------------------------------------------------------------------------*/
/*                              read write                                 */

/** Write data to all destinations
 *
 * \param mem   Pointer to data buffer
 * \param size  Size of bytes to write
 *
 **/

void GroupMCastConnection::write(MemoryHandle mem,UInt32 size)
{
    Dgram  *dgram  = NULL;;
    UInt32  pos    = 0;
    char   *buffer = reinterpret_cast<char*>(mem);

    if(!_initialized)
        initialize();

    while(size)
    {
        // get free dgram
        _lock->acquire();
        dgram = _free.get(_lock);
        _lock->release();
        // fill with data
        dgram->setSize(osgMin(size,dgram->getCapacity()));
        memcpy(dgram->getData(),buffer+pos,dgram->getSize());
        // set sequence number
        dgram->setId( _seqNumber++ );
        // prepate next block
        size -= dgram->getSize();
        pos  += dgram->getSize();
        // put to write queue
        _lock->acquire();
        if(!_sendQueueThreadRunning)
        {
            _lock->release();
            BaseThread::join(_sendQueueThread);    
            throw WriteError("Channel closed");
        }
#ifdef USE_EARLY_SEND
        if(_queue.waiting())
        {
            dgram->setEarlySend(true);
            _mcastSocket.sendTo(dgram->getBuffer(),
                                dgram->getBufferSize(),
                                _mcastAddress);
        }
#endif
        _queue.put(dgram);
        _lock->release();
    }
}

/** Write buffer
 *
 * Write blocksize and data.
 *
 **/
void GroupMCastConnection::writeBuffer(void)
{
    UInt32       size   = writeBufBegin()->getDataSize();
    MemoryHandle buffer = writeBufBegin()->getMem();

    write(buffer,size);
}

/*-------------------------------------------------------------------------*/
/*                              private helpers                            */

/*! check if all receivers are alive
 */
bool GroupMCastConnection::checkChannels(void)
{
    SocketSelection selection;
    UInt32          index;
    bool            valid=true;
                    
    _lock->acquire();
    for(index = 0 ; index < _sockets.size() ; ++index)
        selection.setRead(_sockets[index]);
    if(selection.select(0))
    {
        char   buffer;
        for(index = 0 ; index < _sockets.size() ; ++index)
        {
            if(selection.isSetRead(_sockets[index]))
            {
                try
                {
                    _sockets[index].send(&buffer,1);
                }
                catch(SocketException &e)
                {
                    valid = false;
                    FWARNING(("Socket error:%s\n",e.what()))
                    break;
                }
            }
        }
    }
    _lock->release();
    return valid;
}

/*! Send current write queue 
 */
bool GroupMCastConnection::sendQueue(void)
{
    std::vector<Dgram*>                   dgram;
    std::vector<std::set<SocketAddress> > missing;
    UInt32                  count    = 0;
    UInt32                  maxCount = _windowSize-1;
    UInt32                  ack  = 0;
    UInt32                  end  = 0;
    UInt32                  send = 0;
    UInt32                  index;
    Dgram                   response;
    UInt32                  m;
    bool                    readable = false;
    Time                    lastAckTime=0;
    UInt32                  len;
    SocketAddress           fromAddress;
    Dgram                   ackRequest;
    const Time              ackTimeout = 0.01;
    UInt16                  sendId=0;
    UInt16                  lastNak=0;
    Time                    lastNakTime=0;
    bool                    stopAfterSend=false;

    // prepate buffers
    dgram.resize(_windowSize);
    missing.resize(_windowSize);

#ifdef TEST_LOST_DGRAM_RATE
    srand48((int)getSystemTime());
#endif
    do
    {
        // read new dgrams
        if(count < maxCount)
        {
            _lock->acquire();
            while(count < maxCount &&
                  (count == 0 || !_queue.empty()))
            {
                dgram[end] = _queue.get(_lock);
                // stop
                if(!dgram[end]->getSize())
                {
                    if(count)
                    {
                        // wait for ack of packages in window
                        stopAfterSend = true;
                        break;
                    }
                    else
                    {
                        // no packages in the window
                        _lock->release();
                        return true;
                    }
                }
                // insert to expected responses
                for(index=0 ; index<_waitFor.size() ; ++index)
                    missing[end].insert(_waitFor[index]);
                end = (end+1) % _windowSize;
                if(!count)
                    lastAckTime = getSystemTime();
                count++;
            }
            _lock->release();
        }

        // send all dgrams in current window
        for( ; send != end ; send = (send+1) % _windowSize)
        {
#ifdef TEST_LOST_DGRAM_RATE
            if(drand48()>TEST_LOST_DGRAM_RATE)
#endif
            {
                if(!dgram[send]->getEarlySend())
                {
                    _mcastSocket.sendTo(dgram[send]->getBuffer(),
                                        dgram[send]->getBufferSize(),
                                        _mcastAddress);
                }

                dgram[send]->setEarlySend(false);
            }
            sendId = dgram[send]->getId();


            // FLOG(("Sending dgram %d at id %d\n", send, dgram[send]->getId()));
        }

        // loop while
        // window is full and nothing to send or
        // queue is empty
        // or there is something to read
        while(count &&
              ( ( readable = _mcastSocket.waitReadable(0) ) ||
                ( count == maxCount && send == end ) || 
                ( getSystemTime() - lastAckTime > ackTimeout) ) )
        {
            if(!readable && !_mcastSocket.waitReadable(ackTimeout))
            {
#if 0
                printf("count %d\n",count);
                printf("missing %d\n",missing[ack].size());

                printf("readable %d\n",readable);
                printf("send %d end %d\n",send,end);
                printf("lastack %lf\n",getSystemTime() - lastAckTime);
#endif
                FDEBUG(("timeout count %d %d missing %" PRISize "\n",
                        count,sendId,missing[ack].size()))
//                printf("%.10f timeout count %d %d missing %d\n",getSystemTime()-t1,count,sendId,missing[ack].size());
                    
                ackRequest.setSize(0);
                ackRequest.setId(sendId);

                // send request over multicast
                _mcastSocket.sendTo(ackRequest.getBuffer(),
                                    ackRequest.getBufferSize(),
                                    _mcastAddress);

                // wait until next ack request                
                _mcastSocket.waitReadable(0.05);

                // check channels
                if(getSystemTime() - lastAckTime > 0.5)
                {
                    if(!checkChannels())
                        return false;
                }
                if(_sendQueueThreadStop && 
                   getSystemTime() - lastAckTime > 1)
                    // linger max 1 sec after close
                    break;
                else
                    // retry wait
                    continue;
            }

            // read response
#if 0
            len = _mcastSocket.recvFrom(response.getBuffer(),
                                        response.getBufferCapacity(),
                                        fromAddress);
#endif
            len = _mcastSocket.recvFrom(response,
                                        fromAddress);
            lastAckTime = getSystemTime();

            // ignore response with wrong len
            response.setResponseSize();
            if(len != response.getBufferSize())
            {
                FDEBUG(("Wrong response len %d\n",len))
                    continue;
            }

            // old ack ?
            if(!Dgram::less(response.getId(),dgram[ack]->getId()))
            {
                // first ack for this dgram from this receiver
                if(response.getResponseAck() == true)
                {
                    // FLOG(("Ack %d from %s:%d\n",
                    //       response.getId(),
                    //       fromAddress.getHost().c_str(),
                    //       fromAddress.getPort()         ));

                    for(m = ack ; 
                        dgram[m]->getId() != response.getId() ;
                        m=(m+1) % _windowSize)
                        missing[m].erase(fromAddress);
                    missing[m].erase(fromAddress);
                }
                else
                {
                    if(response.getId() == lastNak &&
                       getSystemTime() - lastNakTime < 0.02)
                        continue;
                    lastNak = response.getId();
                    lastNakTime = getSystemTime();

                    // FLOG(("Nack %d from %s:%d\n",
                    //       response.getId(),
                    //       fromAddress.getHost().c_str(),
                    //       fromAddress.getPort()         ));

                    // retransmit
                    m = ack;

                    while(m != send && dgram[m]->getId() != response.getId())
                    {
                        m = (m + 1) % _windowSize;
                    }

                    send = m;
                }
            }

            // free acknolaged packes
            if(missing[ack].empty())
            {
//                printf("ack %d\n",dgram[ack]->getId());
                _lock->acquire();
                while(count && missing[ack].empty())
                {
                    _free.put(dgram[ack]);
                    ack = (ack+1) % _windowSize;
                    count--;
                }
                _lock->release();
            }
        }
    }
    while(!stopAfterSend || send != end);

    return true;
}

/*! write thread
 */
void GroupMCastConnection::sendQueueThread(void *arg)
{
    GroupMCastConnection *the = static_cast<GroupMCastConnection *>(arg);
    try
    {
        the->sendQueue();
    }
    catch(SocketException &e)
    {
        FFATAL(( "Writer Proc crashed %s\n",e.what() ));
    }
    the->_sendQueueThreadRunning = false;
}

/*! initialize connection. Connect to all points
 */
void GroupMCastConnection::initialize()
{
    std::string   group = "239.33.42.32";
//    std::string group = "146.140.32.7";
//    std::string group = "146.140.32.255";
    int           port = 15356;
    SizeT         pos  = _destination.find(':');
    int           clientPort;
    std::string   clientHost;
    UInt32        index;
    UInt32        len;
    UInt32        ackNum = UInt32(osgSqrt(Real32(_sockets.size())));
    UInt32        numSource;
    UInt32        sendTo;
    BinaryMessage message;
    char          threadName[256];

    sprintf(threadName,"GroupMCastConnection%p", static_cast<void *>(this));

    if(!getDestination().empty())
        group = getDestination();
        
    if(_sockets.size()<=16)
        ackNum = 1;

    if(pos != std::string::npos)
    {
        group = std::string(_destination,0,pos);
        port  = atoi(std::string(_destination,
                                 pos+1,
                                 std::string::npos).c_str());
    }
    else
    {
        if(_destination.size())
            group = _destination;
    }
    _mcastAddress.setHost(group);
    _mcastAddress.setPort(port );

    // set multicast interface, if given
    if(!getInterface().empty())
        _mcastSocket.setMCastInterface(
            SocketAddress(getInterface().c_str()));

    for(index = 0 ; index < _sockets.size() ; ++index)
    {
        message.clear();
        // tell the point connection the multicast address
        message.putString(_mcastAddress.getHost());
        message.putUInt32(_mcastAddress.getPort());
        // tell the current seq number
        message.putUInt32(_seqNumber);
        // tell the point from wich port requests are comming
        message.putUInt32(_mcastSocket.getAddress().getPort());
        // send the message
        _sockets[index].send(message);
        
        // receive destination address
        message.clear();
        len = _sockets[index].recv(message);
        if(len == 0)
            throw ReadError("Channel closed\n");
        clientHost = _remoteAddresses[index].getHost();
        clientPort = message.getUInt32();

        SINFO << "Server:" << clientHost 
              << " Port:" << clientPort << std::endl;
        _receiver.push_back(SocketAddress(clientHost.c_str(),clientPort));
    }
    for(index = 0 ; index < _sockets.size() ; ++index)
    {
        message.clear();
        // tell receivers, whom to report acks
        if((index % ackNum) == 0)
        {
            _waitFor.push_back(_receiver[index]);
            numSource = osgMin( ackNum-1, UInt32(_sockets.size()-index-1) );
            message.putUInt32(numSource);
            for(UInt32 r = index+1 ; r < index+1+numSource ; ++r)
            {
                message.putString(_receiver[r].getHost());
                message.putUInt32(_receiver[r].getPort());
            }
            message.putString("");
            message.putUInt32(_mcastSocket.getAddress().getPort());
        }
        else
        {
            sendTo = index - (index % ackNum);
            message.putUInt32(0);
            message.putString(_receiver[sendTo].getHost());
            message.putUInt32(_receiver[sendTo].getPort());
        }
        // send the message
        _sockets[index].send(message);
    }

    // start write thread
    _sendQueueThread=BaseThread::get(threadName, false);
    _sendQueueThreadRunning = true;
    _sendQueueThreadStop    = false;
    _sendQueueThread->runFunction( sendQueueThread, static_cast<void *>(this) );
    _initialized = true;
}

/*-------------------------------------------------------------------------*/
/*                              static type                                */

ConnectionType GroupMCastConnection::_type(
    &GroupMCastConnection::create,
    "Multicast");
