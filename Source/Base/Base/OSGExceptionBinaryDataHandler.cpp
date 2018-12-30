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

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGExceptionBinaryDataHandler.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ExceptionBinaryDataHandler::ExceptionBinaryDataHandler(
    UInt32 zeroCopyThreshold,
    bool   networkOrder     ) :

    _readBuffers          (                 ),
    _writeBuffers         (                 ),
    _zeroCopyBuffers      (                 ),
    _zeroCopyThreshold    (zeroCopyThreshold),
    _freeMem              (                 ),
    _currentReadBuffer    (                 ),
    _currentReadBufferPos (0                ),
    _currentWriteBuffer   (                 ),
    _currentWriteBufferPos(0                ),
    _networkOrder         (networkOrder     )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ExceptionBinaryDataHandler::~ExceptionBinaryDataHandler(void)
{
    freeMem();
}

/*-------------------------------------------------------------------------*/
/*                                Put                                      */

void ExceptionBinaryDataHandler::put(void const *src, SizeT size)
{
    UInt8 const *data = static_cast<UInt8 const *>(src);

    if(_zeroCopyThreshold && size >= _zeroCopyThreshold)
    {
        if(_zeroCopyThreshold == 1)
        {
            write(const_cast<MemoryHandle>(data), size);
        }
        else
        {
            UInt8 tag = 1;

            // we have to write a tag, to indicate the membership
            // of this zero copy block to the current data block
            put(&tag, sizeof(tag));

            _zeroCopyBuffers.push_back(
                MemoryBlock(const_cast<MemoryHandle>(data), 
                            size, 
                            size));
        }
    }
    else
    {
        SizeT copySize;

        while(size != 0)
        {
            if(_currentWriteBuffer == writeBufEnd())
            {
                pushBuffer();
            }

            copySize = osgMin((_currentWriteBuffer->getSize() -
                               _currentWriteBufferPos),
                              size);

            memcpy(_currentWriteBuffer->getMem() + _currentWriteBufferPos,
                    data,
                    copySize);

             size                  -= copySize;
            _currentWriteBufferPos += copySize;
             data                  += copySize;

            // skip to next buffer if current buffer is full
            if(_currentWriteBufferPos == _currentWriteBuffer->getSize())
            {
                _currentWriteBuffer->setDataSize(_currentWriteBufferPos);
                _currentWriteBuffer++;
                _currentWriteBufferPos = 0;
            }
        }
    }
}

/*! Put data from dynamic allocated block
    The caller doesn't know, when the block will be written. So we are
    responsible for freeing this block.
*/

void ExceptionBinaryDataHandler::putAndFree(MemoryHandle src, SizeT size)
{
    put(src, size);

    if(_zeroCopyThreshold && size > _zeroCopyThreshold)
    {
        _freeMem.push_back(src);
    }
    else
    {
        delete [] src;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Put                                      */

void ExceptionBinaryDataHandler::get(void *dst, SizeT size) OSG_THROW (ReadError)
{
    MemoryHandle data = static_cast<MemoryHandle>(dst);

    if(_zeroCopyThreshold && size >= _zeroCopyThreshold)
    {
        if(_zeroCopyThreshold > 1)
        {
            UInt8 tag;

            // we have to read the tag, to force reading of data blocks
            // if the first data field was zero copied
            get(&tag, sizeof(tag));
        }

        // read direct into destination
        read(data, size);
    }
    else
    {
        SizeT copySize;

        while(size != 0)
        {
            // read new data if nothing left
            if(_currentReadBuffer == readBufEnd())
            {
                pullBuffer();
            }

            // num bytes to copy
            copySize = osgMin((_currentReadBuffer->getDataSize() -
                               _currentReadBufferPos),
                              size);

            // no data in buffer ?
            if(copySize != 0)
            {
                memcpy( data,
                       _currentReadBuffer->getMem() + _currentReadBufferPos,
                        copySize);

                 size                 -= copySize;
                _currentReadBufferPos += copySize;
                 data                 += copySize;
            }

            // skip to next buffer if current buffer is full
            if(_currentReadBufferPos == _currentReadBuffer->getDataSize())
            {
                _currentReadBuffer++;
                _currentReadBufferPos = 0;
            }
        }
    }
}

/*! read data in a dynamic allocated block
 
    If data was compressed or converted then it is not possible to 
    write it into the destination memory. BinaryDataHandler doesn't
    store data in continous memory areas. If the caller needs a
    continuous memory then we provide a dynamic allocated block.
    The caller is responsible to free this block.
*/

void ExceptionBinaryDataHandler::getAndAlloc(
    MemoryHandle &src, 
    SizeT         size) OSG_THROW (ReadError)
{
    src = new UInt8[size];

    get(src, size);
}

/*-------------------------------------------------------------------------*/
/*                              Flush                                      */

//! \brief write data not yet written 

void ExceptionBinaryDataHandler::flush(void)
{
    if(_currentWriteBuffer != writeBufEnd())
    {
        // mark rest of buffer as empty
        _currentWriteBuffer->setDataSize(_currentWriteBufferPos);
        _currentWriteBuffer++;

        while(_currentWriteBuffer != writeBufEnd())
        {
            _currentWriteBuffer->setDataSize(0);
            _currentWriteBuffer++;
        }
    }

    pushBuffer();
}

/*! always copy memory blocks befor write
    forceCopy must be called for all endpoints of this connection
 */
void ExceptionBinaryDataHandler::forceCopy(void)
{
    _zeroCopyThreshold = 0;
}

/*! always read or write directly into or from memory blocks
    forceDirectIO must be called for all endpoints of this connection
 */
void ExceptionBinaryDataHandler::forceDirectIO(void)
{
    _zeroCopyThreshold = 1;
}


/*--------------------------------------------------------------------------*/
/*                             NetworkOrder mode                            */

void ExceptionBinaryDataHandler::setNetworkOrder(bool value)
{
    _networkOrder = value;    
}

bool ExceptionBinaryDataHandler::getNetworkOrder(void)
{
    return _networkOrder;
}

/*-------------------------------------------------------------------------*/
/*                               Read                                      */

void ExceptionBinaryDataHandler::readBufAdd(MemoryHandle mem,
                                            SizeT        size,
                                            SizeT        dataSize)
{
    MemoryBlock memBlock(mem, size, dataSize);

    _readBuffers.push_back(memBlock);

    _currentReadBuffer = readBufEnd();
}

void ExceptionBinaryDataHandler::readBufClear(void)
{
    _readBuffers.clear();

    _currentReadBuffer=readBufEnd();
}

/*-------------------------------------------------------------------------*/
/*                               Write                                     */

void ExceptionBinaryDataHandler::writeBufAdd(MemoryHandle mem,
                                             SizeT        size,
                                             SizeT        dataSize)
{
    MemoryBlock memBlock(mem, size, dataSize);

    _writeBuffers.push_back(memBlock);

    _currentWriteBuffer    = writeBufBegin();
    _currentWriteBufferPos = 0;
}

void ExceptionBinaryDataHandler::writeBufClear(void)
{
    _writeBuffers.clear();

    _currentWriteBuffer = writeBufEnd();
}


/*-------------------------------------------------------------------------*/
/*                               Read                                      */

/*!  default buffer read
 
     Use direct read to implement buffer read. First read buffer size
     and then read rest of buffer
 
     @return buffer iterator points behind the last buffer containing data
*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

void ExceptionBinaryDataHandler::readBuffer(void) OSG_THROW (ReadError)
{
    BuffersT::iterator i;
    UInt32             size,nsize;
    UInt32             readSize;

    // read buffer size
    read(reinterpret_cast<MemoryHandle>(&nsize), sizeof(UInt32));
    size = osgNetToHost<UInt32>(nsize);

    // read rest of buffer
    for(i = readBufBegin(); size != 0; ++i)
    {
        if(i == readBufEnd())
        {
            SFATAL << "Read buffer is to small. " << size
                   << "bytes missing" << std::endl;

            throw ReadError("Read buffer to small for whole block");
        }

        readSize = osgMin(size, i->getSize());

        read(i->getMem(), readSize);

        i->setDataSize(readSize);

        size -= readSize;
    }

    for(; i != readBufEnd(); ++i)
    {
        i->setDataSize(0);
    }
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

/*! direct buffer read, write data into given buffer
*/

void ExceptionBinaryDataHandler::read(MemoryHandle OSG_CHECK_ARG(src ),
                                      UInt32       OSG_CHECK_ARG(size))
{
    SWARNING << "BinaryDataHandler::read(MemoryHandle src,int size) called" 
             << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                               Write                                     */

/*! default buffer write, use direct write to implement buffer write.
*/

void ExceptionBinaryDataHandler::writeBuffer(void)
{
    BuffersT::iterator i;
    UInt32             size = 0;
    UInt32             nsize;

    // calculate blocksize
    for(i = writeBufBegin(); i != writeBufEnd(); ++i)
    {
        size += i->getDataSize();
    }

    // write buffer size
    nsize = osgHostToNet<UInt32>(size);

    write(reinterpret_cast<MemoryHandle>(&nsize), sizeof(UInt32));

    // write buffers
    for(i = writeBufBegin(); i != writeBufEnd(); ++i)
    {
        if(i->getDataSize() != 0)
        {
            write(i->getMem(), i->getDataSize());
        }
    }
}

/*! check for data in read buffer
 */
bool ExceptionBinaryDataHandler::isReadBufferEmpty(void)
{
    if(_zeroCopyThreshold == 1)
        return true;
    if(_currentReadBuffer == readBufEnd())
        return true;

    return false;
}


/*-------------------------------------------------------------------------*/
/*                               Handle Buffer                             */

/*! direct buffer write, write data into given buffer
*/

void ExceptionBinaryDataHandler::write(MemoryHandle OSG_CHECK_ARG(src ),
                                       UInt32       OSG_CHECK_ARG(size))
{
    SWARNING << "BinaryDataHandler::write(MemoryHandle mem,int size) called" 
             << std::endl;
}


void ExceptionBinaryDataHandler::pushBuffer()
{
    BuffersT::iterator i;

    writeBuffer();

    // direct write zero copy buffers
    for(  i  = _zeroCopyBuffers.begin();
          i != _zeroCopyBuffers.end  ();
        ++i)
    {
        write(i->getMem(), i->getDataSize());
    }

    _zeroCopyBuffers.clear();

    // remove buffers given with getAndFree
    freeMem();

    // reset buffer pos
    _currentWriteBuffer    = writeBufBegin();
    _currentWriteBufferPos = 0;

    _currentWriteBuffer->setDataSize(0);
}

void ExceptionBinaryDataHandler::pullBuffer(void) OSG_THROW (ReadError)
{
    readBuffer();

    _currentReadBuffer    = readBufBegin();
    _currentReadBufferPos = 0;
}

void ExceptionBinaryDataHandler::freeMem()
{
    for(FreeMemT::iterator i= _freeMem.begin(); i!= _freeMem.end(); ++i)
    {
        delete [] *i;
    }

    _freeMem.clear();
}
