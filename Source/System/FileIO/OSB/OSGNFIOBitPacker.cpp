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

BitPacker::BitPacker(UInt32 size, UInt32 range_max) :
    _num_bits_to_pack(1),
    _next_bit_to_write(0)
{
    while(true)
    {
        UInt32 max_value = (UInt32) (1 << _num_bits_to_pack) - 1;
        if (max_value >= range_max)
            break;
    
        ++_num_bits_to_pack;
    }

    // calc buffer size.
    UInt32 len_in_bytes = (_num_bits_to_pack * size + 7) / 8;

    _buffer.resize(len_in_bytes);
    memset(&_buffer[0], 0, len_in_bytes * sizeof(UInt8));
}

void BitPacker::pack(UInt32 value)
{
    UInt32 num_bits_to_pack = _num_bits_to_pack;
    
    // Scoot the value bits up to the top of the word; this makes
    // them easier to work with.

    value <<= (BITS_PER_WORD - num_bits_to_pack);

    // First we do the hard part: pack bits into the first u8,
    // which may already have bits in it.

    Int32 byte_index = (_next_bit_to_write / 8);
    Int32 bit_index = (_next_bit_to_write % 8);
    Int32 empty_space_this_byte = (8 - bit_index) & 0x7;

    // Update next_bit_to_write for the next call; we don't need 
    // the old value any more.

    _next_bit_to_write += num_bits_to_pack;

    UInt8 *dest = &_buffer[0] + byte_index;

    if (empty_space_this_byte)
    {
        Int32 to_copy = empty_space_this_byte;
    
        if (to_copy > num_bits_to_pack)
        {
            // We don't have enough bits to fill up this u8.
            to_copy = num_bits_to_pack;
        }
    
        UInt32 fill_bits = value >> (BITS_PER_WORD - empty_space_this_byte);
        *dest |= fill_bits;
    
        num_bits_to_pack -= to_copy;
        dest++;
        value <<= to_copy;
    }

    // Now we do the fast and easy part for what is hopefully
    // the bulk of the data.

    while (value)
    {
        *dest++ = value >> (BITS_PER_WORD - 8);
        value <<= 8;
    }
}

std::vector<UInt8> &BitPacker::getBuffer(void)
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

BitUnpacker::BitUnpacker(const std::vector<UInt8> &buffer, UInt32 range_max) :
    _num_bits_to_unpack(1),
    _num_bits_remaining(buffer.size() * 8),
    _next_bit_to_read(0),
    _buffer(buffer)
{
    while(true)
    {
        UInt32 max_value = (UInt32) (1 << _num_bits_to_unpack) - 1;
        if (max_value >= range_max)
            break;
    
        ++_num_bits_to_unpack;
    }
}

UInt32 BitUnpacker::unpack(void)
{
    UInt32 result = 0;
    UInt32 num_bits_to_unpack = _num_bits_to_unpack;
    
    while(num_bits_to_unpack)
    {
        UInt32 byte_index = (_next_bit_to_read / 8);
        UInt32 bit_index = (_next_bit_to_read % 8);
        
        UInt32 src_mask = (1 << (7 - bit_index));
        UInt32 dest_mask = (1 << (num_bits_to_unpack - 1));
    
        if(_buffer[byte_index] & src_mask)
            result |= dest_mask;
        num_bits_to_unpack--;
        _next_bit_to_read++;
    }

    _num_bits_remaining -= num_bits_to_unpack;

    return result;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGNFIOBITPACKER_HEADER_CVSID;
}
