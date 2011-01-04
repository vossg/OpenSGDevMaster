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

/*! \brief BitPacker class.
          packs and unpacks UInt32
    \ingroup GrpFileIOOSB
    \nohierarchy
*/

class BitPacker
{
    /*==========================  PUBLIC  =================================*/
public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef std::vector<UInt8> BufferType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    BitPacker(UInt32 size, UInt32 max);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Pack/get                                                     */
    /*! \{                                                                 */

    void pack(UInt32 value);

    const BufferType &getBuffer(void) const;
          BufferType &getBuffer(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

private:

    UInt32     _numBitsToPack;
    Int32      _nextBit;
    BufferType _buffer;

    static const Int32 BITS_PER_WORD;
};

/*! \ingroup GrpFileIOOSB
    \nohierarchy
 */

class BitUnpacker
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef std::vector<UInt8> BufferType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    BitUnpacker(const BufferType &buffer, UInt32 max);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Unpack                                                       */
    /*! \{                                                                 */

    UInt32 unpack(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

private:
    UInt32            _numBitsToUnpack;
    Int32             _numBitsRemaining;
    Int32             _nextBit;

    const BufferType &_buffer;
};

OSG_END_NAMESPACE

#endif /* _OSGNFIOBITPACKER_H_ */
