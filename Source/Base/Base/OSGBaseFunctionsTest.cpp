/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
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

#include <UnitTest++.h>

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

// This test is incomplete, it only tests:
//  * byte order swapping
//  * osgIsPower2
//  * osgNextPower2

using namespace UnitTest;

SUITE(BaseFunctionsTests)
{

struct ByteOrderFixture
{
    ByteOrderFixture()
    {
        OSG::UInt8 bytes_a[] =
            { 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78 };
        OSG::UInt8 bytes_b[] =
            { 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71 };

        int16_a   = *reinterpret_cast<OSG::Int16*> (&(bytes_a[0]));
        int16_b   = *reinterpret_cast<OSG::Int16*> (&(bytes_b[6]));
        uint16_a  = *reinterpret_cast<OSG::UInt16*>(&(bytes_a[0]));
        uint16_b  = *reinterpret_cast<OSG::UInt16*>(&(bytes_b[6]));

        int32_a   = *reinterpret_cast<OSG::Int32*> (&(bytes_a[0]));
        int32_b   = *reinterpret_cast<OSG::Int32*> (&(bytes_b[4]));
        uint32_a  = *reinterpret_cast<OSG::UInt32*>(&(bytes_a[0]));
        uint32_b  = *reinterpret_cast<OSG::UInt32*>(&(bytes_b[4]));

        int64_a   = *reinterpret_cast<OSG::Int64*> (&(bytes_a[0]));
        int64_b   = *reinterpret_cast<OSG::Int64*> (&(bytes_b[0]));
        uint64_a  = *reinterpret_cast<OSG::UInt64*>(&(bytes_a[0]));
        uint64_b  = *reinterpret_cast<OSG::UInt64*>(&(bytes_b[0]));

        real32_a  = *reinterpret_cast<OSG::Real32*>(&(bytes_a[0]));
        real32_b  = *reinterpret_cast<OSG::Real32*>(&(bytes_b[4]));
        real64_a  = *reinterpret_cast<OSG::Real64*>(&(bytes_a[0]));
        real64_b  = *reinterpret_cast<OSG::Real64*>(&(bytes_b[0]));
    }

    ~ByteOrderFixture()
    {
    }

    OSG::Int16   int16_a;
    OSG::Int16   int16_b;
    OSG::UInt16  uint16_a;
    OSG::UInt16  uint16_b;
    OSG::Int32   int32_a;
    OSG::Int32   int32_b;
    OSG::UInt32  uint32_a;
    OSG::UInt32  uint32_b;
    OSG::Int64   int64_a;
    OSG::Int64   int64_b;
    OSG::UInt64  uint64_a;
    OSG::UInt64  uint64_b;

    OSG::Real32  real32_a;
    OSG::Real32  real32_b;
    OSG::Real64  real64_a;
    OSG::Real64  real64_b;
};

TEST_FIXTURE(ByteOrderFixture, HostToBigEndian)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    CHECK_EQUAL(OSG::osgHostToBigEndian(int16_a),  int16_b );
    CHECK_EQUAL(OSG::osgHostToBigEndian(uint16_a), uint16_b);
    CHECK_EQUAL(OSG::osgHostToBigEndian(int32_a),  int32_b );
    CHECK_EQUAL(OSG::osgHostToBigEndian(uint32_a), uint32_b);
    CHECK_EQUAL(OSG::osgHostToBigEndian(int64_a),  int64_b);
    CHECK_EQUAL(OSG::osgHostToBigEndian(uint64_a), uint64_b);
    CHECK_EQUAL(OSG::osgHostToBigEndian(real32_a), real32_b);
    CHECK_EQUAL(OSG::osgHostToBigEndian(real64_a), real64_b);
#else
    CHECK_EQUAL(OSG::osgHostToBigEndian(int16_a),  int16_a );
    CHECK_EQUAL(OSG::osgHostToBigEndian(uint16_a), uint16_a);
    CHECK_EQUAL(OSG::osgHostToBigEndian(int32_a),  int32_a );
    CHECK_EQUAL(OSG::osgHostToBigEndian(uint32_a), uint32_a);
    CHECK_EQUAL(OSG::osgHostToBigEndian(int64_a),  int64_a );
    CHECK_EQUAL(OSG::osgHostToBigEndian(uint64_a), uint64_a);
    CHECK_EQUAL(OSG::osgHostToBigEndian(real32_a), real32_a);
    CHECK_EQUAL(OSG::osgHostToBigEndian(real64_a), real64_a);
#endif

    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(int16_a)),  int16_a );
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(uint16_a)), uint16_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(int32_a)),  int32_a );
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(uint32_a)), uint32_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(int64_a)),  int64_a );
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(uint64_a)), uint64_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(real32_a)), real32_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(OSG::osgHostToBigEndian(real64_a)), real64_a);
}

TEST_FIXTURE(ByteOrderFixture, HostToLittleEndian)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    CHECK_EQUAL(OSG::osgHostToLittleEndian(int16_a),  int16_a );
    CHECK_EQUAL(OSG::osgHostToLittleEndian(uint16_a), uint16_a);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(int32_a),  int32_a );
    CHECK_EQUAL(OSG::osgHostToLittleEndian(uint32_a), uint32_a);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(int64_a),  int64_a );
    CHECK_EQUAL(OSG::osgHostToLittleEndian(uint64_a), uint64_a);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(real32_a), real32_a);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(real64_a), real64_a);
#else
    CHECK_EQUAL(OSG::osgHostToLittleEndian(int16_a),  int16_b );
    CHECK_EQUAL(OSG::osgHostToLittleEndian(uint16_a), uint16_b);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(int32_a),  int32_b );
    CHECK_EQUAL(OSG::osgHostToLittleEndian(uint32_a), uint32_b);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(int64_a),  int64_b);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(uint64_a), uint64_b);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(real32_a), real32_b);
    CHECK_EQUAL(OSG::osgHostToLittleEndian(real64_a), real64_b);
#endif

    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(int16_a)),  int16_a );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(uint16_a)), uint16_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(int32_a)),  int32_a );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(uint32_a)), uint32_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(int64_a)),  int64_a );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(uint64_a)), uint64_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(real32_a)), real32_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(OSG::osgHostToLittleEndian(real64_a)), real64_a);
}

TEST_FIXTURE(ByteOrderFixture, BigEndianToHost)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    CHECK_EQUAL(OSG::osgBigEndianToHost(int16_a),  int16_b );
    CHECK_EQUAL(OSG::osgBigEndianToHost(uint16_a), uint16_b);
    CHECK_EQUAL(OSG::osgBigEndianToHost(int32_a),  int32_b );
    CHECK_EQUAL(OSG::osgBigEndianToHost(uint32_a), uint32_b);
    CHECK_EQUAL(OSG::osgBigEndianToHost(int64_a),  int64_b);
    CHECK_EQUAL(OSG::osgBigEndianToHost(uint64_a), uint64_b);
    CHECK_EQUAL(OSG::osgBigEndianToHost(real32_a), real32_b);
    CHECK_EQUAL(OSG::osgBigEndianToHost(real64_a), real64_b);
#else
    CHECK_EQUAL(OSG::osgBigEndianToHost(int16_a),  int16_a );
    CHECK_EQUAL(OSG::osgBigEndianToHost(uint16_a), uint16_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(int32_a),  int32_a );
    CHECK_EQUAL(OSG::osgBigEndianToHost(uint32_a), uint32_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(int64_a),  int64_a );
    CHECK_EQUAL(OSG::osgBigEndianToHost(uint64_a), uint64_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(real32_a), real32_a);
    CHECK_EQUAL(OSG::osgBigEndianToHost(real64_a), real64_a);
#endif
}

TEST_FIXTURE(ByteOrderFixture, LittleEndianToHost)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    CHECK_EQUAL(OSG::osgLittleEndianToHost(int16_a),  int16_a );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(uint16_a), uint16_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(int32_a),  int32_a );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(uint32_a), uint32_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(int64_a),  int64_a );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(uint64_a), uint64_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(real32_a), real32_a);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(real64_a), real64_a);
#else
    CHECK_EQUAL(OSG::osgLittleEndianToHost(int16_a),  int16_b );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(uint16_a), uint16_b);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(int32_a),  int32_b );
    CHECK_EQUAL(OSG::osgLittleEndianToHost(uint32_a), uint32_b);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(int64_a),  int64_b);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(uint64_a), uint64_b);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(real32_a), real32_b);
    CHECK_EQUAL(OSG::osgLittleEndianToHost(real64_a), real64_b);
#endif
}

TEST(IsPower2)
{
#define OSG_INT32_LITERAL(value) static_cast<OSG::Int32>(value)
#define OSG_UINT32_LITERAL(value) static_cast<OSG::UInt32>(value##U)

#ifdef OSG_LONGLONG_HAS_LL
#define OSG_INT64_LITERAL(value) static_cast<OSG::Int64>(value##LL)
#define OSG_UINT64_LITERAL(value) static_cast<OSG::UInt64>(value##ULL)
#else
#define OSG_INT64_LITERAL(value) static_cast<OSG::Int64>(value)
#define OSG_UINT64_LITERAL(value) static_cast<OSG::UInt64>(value##U)
#endif

    typedef OSG::TypeTraits<OSG::UInt32> TTU32;
    typedef OSG::TypeTraits<OSG::Int32>  TTS32;

    typedef OSG::TypeTraits<OSG::UInt64> TTU64;
    typedef OSG::TypeTraits<OSG::Int64>  TTS64;

    CHECK( OSG::osgIsPower2(OSG_INT32_LITERAL(0)));
    CHECK( OSG::osgIsPower2(OSG_INT32_LITERAL(1)));
    CHECK( OSG::osgIsPower2(OSG_INT32_LITERAL(2)));
    CHECK(!OSG::osgIsPower2(OSG_INT32_LITERAL(3)));
    CHECK(!OSG::osgIsPower2(OSG_INT32_LITERAL(-1)));
    CHECK( OSG::osgIsPower2((TTS32::getOneElement() << 30)                         ));
    CHECK(!OSG::osgIsPower2((TTS32::getOneElement() << 30) + TTS32::getOneElement()));

    CHECK( OSG::osgIsPower2(OSG_UINT32_LITERAL(0)));
    CHECK( OSG::osgIsPower2(OSG_UINT32_LITERAL(1)));
    CHECK( OSG::osgIsPower2(OSG_UINT32_LITERAL(2)));
    CHECK(!OSG::osgIsPower2(OSG_UINT32_LITERAL(3)));
    CHECK( OSG::osgIsPower2((TTU32::getOneElement() << 31)                         ));
    CHECK(!OSG::osgIsPower2((TTU32::getOneElement() << 31) + TTS32::getOneElement()));

    CHECK( OSG::osgIsPower2(OSG_INT64_LITERAL(0)));
    CHECK( OSG::osgIsPower2(OSG_INT64_LITERAL(1)));
    CHECK( OSG::osgIsPower2(OSG_INT64_LITERAL(2)));
    CHECK(!OSG::osgIsPower2(OSG_INT64_LITERAL(3)));
    CHECK(!OSG::osgIsPower2(OSG_INT64_LITERAL(-1)));
    CHECK( OSG::osgIsPower2((TTS64::getOneElement() << 62)                         ));
    CHECK(!OSG::osgIsPower2((TTS64::getOneElement() << 62) + TTS64::getOneElement()));

    CHECK( OSG::osgIsPower2(OSG_UINT64_LITERAL(0)));
    CHECK( OSG::osgIsPower2(OSG_UINT64_LITERAL(1)));
    CHECK( OSG::osgIsPower2(OSG_UINT64_LITERAL(2)));
    CHECK(!OSG::osgIsPower2(OSG_UINT64_LITERAL(3)));
    CHECK( OSG::osgIsPower2((TTU64::getOneElement() << 63)                         ));
    CHECK(!OSG::osgIsPower2((TTU64::getOneElement() << 63) + TTS64::getOneElement()));

#undef OSG_INT32_LITERAL
#undef OSG_UINT32_LITERAL
#undef OSG_INT64_LITERAL
#undef OSG_UINT64_LITERAL
}

TEST(NextPower2)
{
#define OSG_INT32_LITERAL(value) static_cast<OSG::Int32>(value)
#define OSG_UINT32_LITERAL(value) static_cast<OSG::UInt32>(value##U)

#ifdef OSG_LONGLONG_HAS_LL
#define OSG_INT64_LITERAL(value) static_cast<OSG::Int64>(value##LL)
#define OSG_UINT64_LITERAL(value) static_cast<OSG::UInt64>(value##ULL)
#else
#define OSG_INT64_LITERAL(value) static_cast<OSG::Int64>(value)
#define OSG_UINT64_LITERAL(value) static_cast<OSG::UInt64>(value##U)
#endif

    typedef OSG::TypeTraits<OSG::UInt32> TTU32;
    typedef OSG::TypeTraits<OSG::Int32>  TTS32;

    typedef OSG::TypeTraits<OSG::UInt64> TTU64;
    typedef OSG::TypeTraits<OSG::Int64>  TTS64;

    CHECK_EQUAL(OSG::osgNextPower2(OSG_INT32_LITERAL(0)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_INT32_LITERAL(1)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_INT32_LITERAL(3)), 4);
    CHECK_EQUAL(OSG::osgNextPower2((TTS32::getOneElement() << 29) + TTS32::getOneElement()),
                TTS32::getOneElement() << 30);
    CHECK_EQUAL(OSG::osgNextPower2((TTS32::getOneElement() << 30) + TTS32::getOneElement()), 0);

    CHECK_EQUAL(OSG::osgNextPower2(OSG_UINT32_LITERAL(0)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_UINT32_LITERAL(1)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_UINT32_LITERAL(3)), 4);
    CHECK_EQUAL(OSG::osgNextPower2((TTU32::getOneElement() << 30) + TTU32::getOneElement()),
                TTU32::getOneElement() << 31);
    CHECK_EQUAL(OSG::osgNextPower2((TTU32::getOneElement() << 31) + TTU32::getOneElement()), 0);

    CHECK_EQUAL(OSG::osgNextPower2(OSG_INT64_LITERAL(0)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_INT64_LITERAL(1)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_INT64_LITERAL(3)), 4);
    CHECK_EQUAL(OSG::osgNextPower2((TTS64::getOneElement() << 61) + TTS64::getOneElement()),
                TTS64::getOneElement() << 62);
    CHECK_EQUAL(OSG::osgNextPower2((TTS64::getOneElement() << 62) + TTS64::getOneElement()), 0);

    CHECK_EQUAL(OSG::osgNextPower2(OSG_UINT64_LITERAL(0)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_UINT64_LITERAL(1)), 1);
    CHECK_EQUAL(OSG::osgNextPower2(OSG_UINT64_LITERAL(3)), 4);
    CHECK_EQUAL(OSG::osgNextPower2((TTU64::getOneElement() << 62) + TTU64::getOneElement()),
                TTU64::getOneElement() << 63);
    CHECK_EQUAL(OSG::osgNextPower2((TTU64::getOneElement() << 63) + TTU64::getOneElement()), 0);

#undef OSG_INT32_LITERAL
#undef OSG_UINT32_LITERAL
#undef OSG_INT64_LITERAL
#undef OSG_UINT64_LITERAL
}

} // SUITE
