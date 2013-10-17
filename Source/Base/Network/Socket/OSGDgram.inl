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

#ifndef _DGRAM_INL_
#define _DGRAM_INL_

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                      get                                            */

inline
UInt32 Dgram::getCapacity(void) const
{
    return sizeof(DgramBuffer) - sizeof(_buffer->_id);
}

inline
UInt16 Dgram::getId(void) const
{
    return osgNetToHost<UInt16>(_buffer->_id);
}

inline
UInt32 Dgram::getSize(void) const
{
    return _size;
}

inline
UChar8 *Dgram::getData(void)
{
    return _buffer->_data;
}

inline
const UChar8 *Dgram::getData(void) const
{
    return _buffer->_data;
}

inline
UChar8 *Dgram::getBuffer(void)
{
    return reinterpret_cast<UChar8 *>(_buffer);
}

inline
UInt32 Dgram::getBufferSize(void) const
{
    return _size + sizeof(_buffer->_id);
}

inline
UInt32 Dgram::getBufferCapacity(void) const
{
    return sizeof(DgramBuffer);
}

inline
bool Dgram::getResponseAck(void) const
{
    return (_buffer->_data[0] != 0);
}

inline
bool Dgram::getEarlySend(void) const
{
    return _earlySend;
}

/*---------------------------------------------------------------------*/
/*                      set                                            */

inline 
void Dgram::setSize(UInt32 size)
{
    _size = size;
}

inline 
void Dgram::setResponseSize(void)
{
    _size = sizeof(UChar8);
}

inline 
void Dgram::setId(UInt16 id)
{
    _buffer->_id = osgHostToNet<UInt16>(id);
}

inline
void Dgram::setBufferSize(UInt32 size)
{
    _size = size - sizeof(_buffer->_id);
}

inline 
void Dgram::setResponseAck(bool value)
{
    _buffer->_data[0] = value;
}

inline 
void Dgram::setEarlySend(bool value)
{
    _earlySend = value;
}

#ifdef OSG_DEBUG
inline 
void Dgram::incUsageCounter(void)
{
    ++_uiUsageCounter;
}

inline
UInt32 Dgram::getUsageCounter(void)
{
    return _uiUsageCounter;
}
#endif

inline
void Dgram::reallocateBuffer(void)
{
    
    delete _buffer;

    _buffer = new DgramBuffer;

    memset(_buffer, 0, sizeof(DgramBuffer));

#ifdef OSG_DEBUG
    _uiUsageCounter = 0;
#endif
}

/*---------------------------------------------------------------------*/
/*                      compare                                        */

/*! Compare IDs. Use Window.
 */
inline bool Dgram::less(UInt16 a,UInt16 b)
{
    a = a - b;

    if(a & 0x8000)
        return true;
    else
        return false;
}

/*! Compare IDs. Use Window.
 */

inline 
bool Dgram::operator <(const Dgram &other) const
{
    return less(this->getId(),other.getId());
}

OSG_END_NAMESPACE

#endif







