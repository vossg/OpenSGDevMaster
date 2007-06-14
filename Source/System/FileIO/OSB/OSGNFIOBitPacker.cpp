/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#include <OSGConfig.h>
#include "OSGNFIOBitPacker.h"

#include <cstring>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::BitPacker
           packs and unpacks UInt32.
 */

/*-------------------------------------------------------------------------*\
 -  Packer                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Int32 BitPacker::BITS_PER_WORD = 32;

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

BitPacker::BitPacker(UInt32 size, UInt32 max)
    : _numBitsToPack(1),
      _nextBit      (0)
{
    while(true)
    {
        UInt32 maxValue = (UInt32) (1 << _numBitsToPack) - 1;
        if (maxValue >= max)
            break;

        ++_numBitsToPack;
    }

    // calc buffer size.
    UInt32 lenInBytes = (_numBitsToPack * size + 7) / 8;

    _buffer.resize(lenInBytes);
    memset(&_buffer[0], 0, lenInBytes * sizeof(UInt8)); // unneccessary ?
}

void BitPacker::pack(UInt32 value)
{
    UInt32 numBitsToPack = _numBitsToPack;

    // Scoot the value bits up to the top of the word; this makes
    // them easier to work with.
    value <<= (BITS_PER_WORD - numBitsToPack);

    // First we do the hard part: pack bits into the first u8,
    // which may already have bits in it.

    Int32 byteIndex     = (_nextBit / 8);
    Int32 bitIndex      = (_nextBit % 8);
    Int32 spaceCurrByte = (8 - bitIndex) & 0x7;

    // Update _nextBit for the next call; we don't need
    // the old value any more
    _nextBit += numBitsToPack;

    UInt8 *dest = &_buffer[0] + byteIndex;

    if(spaceCurrByte)
    {
        Int32 toCopy = spaceCurrByte;

        if(toCopy > numBitsToPack)
        {
            // We don't have enough bits to fill up this u8.
            toCopy = numBitsToPack;
        }

        UInt32 fillBits = value >> (BITS_PER_WORD - spaceCurrByte);
        *dest |= fillBits;

        numBitsToPack -= toCopy;
        dest++;
        value <<= toCopy;
    }

    // Now we do the fast and easy part for what is hopefully
    // the bulk of the data.
    while(value)
    {
        *dest++ = value >> (BITS_PER_WORD - 8);
        value <<= 8;
    }
}

const BitPacker::BufferType &
BitPacker::getBuffer(void) const
{
    return _buffer;
}

BitPacker::BufferType &
BitPacker::getBuffer(void)
{
    return _buffer;
}

/*-------------------------------------------------------------------------*\
 -  Unpacker                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

BitUnpacker::BitUnpacker(const std::vector<UInt8> &buffer, UInt32 max) :
    _numBitsToUnpack (1                ),
    _numBitsRemaining(buffer.size() * 8),
    _nextBit         (0                ),
    _buffer          (buffer           )
{
    while(true)
    {
        UInt32 maxValue = (UInt32) (1 << _numBitsToUnpack) - 1;
        if (maxValue >= max)
            break;

        ++_numBitsToUnpack;
    }
}

UInt32 BitUnpacker::unpack(void)
{
    UInt32 result          = 0;
    UInt32 numBitsToUnpack = _numBitsToUnpack;

    while(numBitsToUnpack)
    {
        UInt32 byteIndex = (_nextBit / 8);
        UInt32 bitIndex  = (_nextBit % 8);
        UInt32 srcMask   = (1 << (7 - bitIndex));
        UInt32 destMask  = (1 << (numBitsToUnpack - 1));

        if(_buffer[byteIndex] & srcMask)
            result |= destMask;
        numBitsToUnpack--;
        _nextBit++;
    }

    _numBitsRemaining -= numBitsToUnpack;

    return result;
}
