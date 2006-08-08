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

#ifndef _OSGNFIOBITPACKER_H_
#define _OSGNFIOBITPACKER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

#include <vector>

OSG_BEGIN_NAMESPACE

/* \brief BitPacker class.
          packs and unpacks UInt32
*/

class BitPacker
{
    /*==========================  PUBLIC  =================================*/
public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    BitPacker(UInt32 size, UInt32 max);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Pack/get                                  */
    /*! \{                                                                 */

    void pack(UInt32 value);
    std::vector<UInt8> &getBuffer(void);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/

private:

    UInt32 _num_bits_to_pack;
    Int32 _next_bit_to_write;
    std::vector<UInt8> _buffer;

    static const Int32 BITS_PER_WORD;
};

class BitUnpacker
{
    /*==========================  PUBLIC  =================================*/
public:
    
/*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    BitUnpacker(const std::vector<UInt8> &buffer, UInt32 range_max);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Unpack                                    */
    /*! \{                                                                 */

    UInt32 unpack(void);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/

private:
    
    UInt32 _num_bits_to_unpack;
    Int32 _num_bits_remaining;
    Int32 _next_bit_to_read;

    const std::vector<UInt8> &_buffer;
};

OSG_END_NAMESPACE

#define OSGNFIOBITPACKER_HEADER_CVSID "@(#)$Id: OSGNFIOBitPacker.h,v 1.1.2.2 2005/10/04 08:40:21 vossg Exp $"

#endif /* _OSGNFIOBITPACKER_H_ */
