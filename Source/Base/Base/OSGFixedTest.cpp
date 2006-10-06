/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <UnitTest++.h>

#include <OpenSG/OSGBaseTypes.h>

// NOTE:
//
// This test does not compile if the commented out code below is enabled,
// because Fixed32 plays badly with most other types. Once this is fixed this
// test should compile and maybe some checking of the computations can be done.

namespace {

#define OSG_FIXED32_TEST(VDest, VOp1, VOp2) \
    VDest = VOp1 + VOp2;                    \
    VDest = VOp1 - VOp2;                    \
    VDest = VOp1 * VOp2;                    \
    VDest = VOp1 / VOp2;                    \
    VDest = VOp2 + VOp1;                    \
    VDest = VOp2 - VOp1;                    \
    VDest = VOp2 * VOp1;                    \
    VDest = VOp2 / VOp1;

TEST(Fixed32_Interoperability)
{
    OSG::Fixed32 f32a;
    OSG::Fixed32 f32b(2.0f);

    OSG::Int8    i8   = -3;
    OSG::UInt8   ui8  =  3;

    OSG::Int16   i16  = -300;
    OSG::UInt16  ui16 =  300;

    OSG::Int32   i32  = -300000;
    OSG::UInt32  ui32 = 3000000;

    OSG::Int64   i64  = -30000000;
    OSG::UInt64  ui64 =  30000000;

    OSG::Real32  r32  = 3.0;
    OSG::Real64  r64  = 3.0;

    // Most of the next lines fail to compile because of ambigous
    // constructor calls or missing operator overloads :(
    
//     OSG_FIXED32_TEST(f32a, f32b, i8);
//     OSG_FIXED32_TEST(f32a, f32b, ui8);
//     OSG_FIXED32_TEST(f32a, f32b, i16);
//     OSG_FIXED32_TEST(f32a, f32b, ui16);
//     OSG_FIXED32_TEST(f32a, f32b, i32);
//     OSG_FIXED32_TEST(f32a, f32b, ui32);
//     OSG_FIXED32_TEST(f32a, f32b, i64);
//     OSG_FIXED32_TEST(f32a, f32b, ui64);
//     OSG_FIXED32_TEST(f32a, f32b, r32);
//     OSG_FIXED32_TEST(f32a, f32b, r64);
    
    // Make this test fail unconditonally as a remainder that the above should
    // work.
    CHECK(false);
}

} // namespace
