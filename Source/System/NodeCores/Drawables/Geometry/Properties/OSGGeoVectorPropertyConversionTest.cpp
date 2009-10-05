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

#include "OSGVector.h"
#include "OSGColor.h"
#include "OSGGeoVectorProperty.h"

// In the tests below there are quite a number of tests commented out, because
// they fail to compile - all involving types with Fixed32 elements.
// The underlying reason is the limited number of mixed type arithmetic
// that the Fixed32 type supports - ticket #79 tracks the issue.

namespace {

/*! Fixture to hold all the variables for the various conversions.
    Variable names ending in "_ref" are reference values agains which results
    are compared,
    while those ending in "_dest" are targets for conversions, all others are
    input.
 */
struct GeoConvertFixture
{
    GeoConvertFixture(void) :
        vec4b_ref (1, 2, 3, 4),
        vec4ub_ref(1, 2, 3, 4),
        vec4s_ref (1, 2, 3, 4),
        vec4f_ref (1.0f, 2.0f, 3.0f, 4.0f),
        vec4d_ref (1.0,  2.0,  3.0,  4.0),
        vec4fx_ref(1.0f, 2.0f, 3.0f, 4.0f),
        
        vec1b (1,    1),        // Vec1 has no 1 argument ctor - use 2 arg ctor
        vec1s (1,    1),
        vec1f (1.0f, 1.0f),
        vec1d (1.0,  1.0),
        vec1fx(1.0f, 1.0f),
        vec2b (1,    2),
        vec2s (1,    2),
        vec2f (1.0f, 2.0f),
        vec2d (1.0,  2.0),
        vec2fx(1.0f, 2.0f),
        vec3b (1,    2,    3),
        vec3s (1,    2,    3),
        vec3f (1.0f, 2.0f, 3.0f),
        vec3d (1.0,  2.0,  3.0),
        vec3fx(1.0f, 2.0f, 3.0f),
        vec4b (1,    2,    3,    4),
        vec4s (1,    2,    3,    4),
        vec4f (1.0f, 2.0f, 3.0f, 4.0f),
        vec4d (1.0,  2.0,  3.0,  4.0),
        vec4fx(1.0f, 2.0f, 3.0f, 4.0f),
        
        pnt1b (1,    1),        // Pnt1 has no 1 argument ctor - use 2 arg ctor
        pnt1s (1,    1),
        pnt1f (1.0f, 1.0f),
        pnt1d (1.0,  1.0),
        pnt1fx(1.0f, 1.0f),
        pnt2b (1,    2),
        pnt2s (1,    2),
        pnt2f (1.0f, 2.0f),
        pnt2d (1.0,  2.0),
        pnt2fx(1.0f, 2.0f),
        pnt3b (1,    2,    3),
        pnt3s (1,    2,    3),
        pnt3f (1.0f, 2.0f, 3.0f),
        pnt3d (1.0,  2.0,  3.0),
        pnt3fx(1.0f, 2.0f, 3.0f),
        pnt4b (1,    2,    3,    4),
        pnt4s (1,    2,    3,    4),
        pnt4f (1.0f, 2.0f, 3.0f, 4.0f),
        pnt4d (1.0,  2.0,  3.0,  4.0),
        pnt4fx(1.0f, 2.0f, 3.0f, 4.0f),
        
        col3ub(1,    2,    3),
        col3f (1.0f, 2.0f, 3.0f),
        col3fx(1.0f, 2.0f, 3.0f),
        col4ub(1,    2,    3,    4),
        col4f (1.0f, 2.0f, 3.0f, 4.0f),
        col4fx(1.0f, 2.0f, 3.0f, 4.0f)
    {
    }
        
    ~GeoConvertFixture(void)
    {
    }
        
    // Reference for comparison
    const OSG::Vec4b    vec4b_ref;
    const OSG::Vec4ub   vec4ub_ref;
    const OSG::Vec4s    vec4s_ref;
    const OSG::Vec4f    vec4f_ref;
    const OSG::Vec4d    vec4d_ref;
    const OSG::Vec4fx   vec4fx_ref;

    // Input
    const OSG::Vec1b    vec1b;
    const OSG::Vec1s    vec1s;
    const OSG::Vec1f    vec1f;
    const OSG::Vec1d    vec1d;
    const OSG::Vec1fx   vec1fx;
    const OSG::Vec2b    vec2b;
    const OSG::Vec2s    vec2s;
    const OSG::Vec2f    vec2f;
    const OSG::Vec2d    vec2d;
    const OSG::Vec2fx   vec2fx;
    const OSG::Vec3b    vec3b;
    const OSG::Vec3s    vec3s;
    const OSG::Vec3f    vec3f;
    const OSG::Vec3d    vec3d;
    const OSG::Vec3fx   vec3fx;
    const OSG::Vec4b    vec4b;
    const OSG::Vec4s    vec4s;
    const OSG::Vec4f    vec4f;
    const OSG::Vec4d    vec4d;
    const OSG::Vec4fx   vec4fx;

    const OSG::Pnt1b    pnt1b;
    const OSG::Pnt1s    pnt1s;
    const OSG::Pnt1f    pnt1f;
    const OSG::Pnt1d    pnt1d;
    const OSG::Pnt1fx   pnt1fx;
    const OSG::Pnt2b    pnt2b;
    const OSG::Pnt2s    pnt2s;
    const OSG::Pnt2f    pnt2f;
    const OSG::Pnt2d    pnt2d;
    const OSG::Pnt2fx   pnt2fx;
    const OSG::Pnt3b    pnt3b;
    const OSG::Pnt3s    pnt3s;
    const OSG::Pnt3f    pnt3f;
    const OSG::Pnt3d    pnt3d;
    const OSG::Pnt3fx   pnt3fx;
    const OSG::Pnt4b    pnt4b;
    const OSG::Pnt4s    pnt4s;
    const OSG::Pnt4f    pnt4f;
    const OSG::Pnt4d    pnt4d;
    const OSG::Pnt4fx   pnt4fx;

    const OSG::Color3ub col3ub;
    const OSG::Color3f  col3f;
    const OSG::Color3fx col3fx;
    const OSG::Color4ub col4ub;
    const OSG::Color4f  col4f;
    const OSG::Color4fx col4fx;

    // Output
    OSG::Vec1b  vec1b_dest;
    OSG::Vec1s  vec1s_dest;
    OSG::Vec1f  vec1f_dest;
    OSG::Vec1d  vec1d_dest;
    OSG::Vec1fx vec1fx_dest;
    OSG::Vec2b  vec2b_dest;
    OSG::Vec2s  vec2s_dest;
    OSG::Vec2f  vec2f_dest;
    OSG::Vec2d  vec2d_dest;
    OSG::Vec2fx vec2fx_dest;
    OSG::Vec3b  vec3b_dest;
    OSG::Vec3s  vec3s_dest;
    OSG::Vec3f  vec3f_dest;
    OSG::Vec3d  vec3d_dest;
    OSG::Vec3fx vec3fx_dest;
    OSG::Vec4b  vec4b_dest;
    OSG::Vec4s  vec4s_dest;
    OSG::Vec4f  vec4f_dest;
    OSG::Vec4d  vec4d_dest;
    OSG::Vec4fx vec4fx_dest;

    OSG::Pnt1b  pnt1b_dest;
    OSG::Pnt1s  pnt1s_dest;
    OSG::Pnt1f  pnt1f_dest;
    OSG::Pnt1d  pnt1d_dest;
    OSG::Pnt1fx pnt1fx_dest;
    OSG::Pnt2b  pnt2b_dest;
    OSG::Pnt2s  pnt2s_dest;
    OSG::Pnt2f  pnt2f_dest;
    OSG::Pnt2d  pnt2d_dest;
    OSG::Pnt2fx pnt2fx_dest;
    OSG::Pnt3b  pnt3b_dest;
    OSG::Pnt3s  pnt3s_dest;
    OSG::Pnt3f  pnt3f_dest;
    OSG::Pnt3d  pnt3d_dest;
    OSG::Pnt3fx pnt3fx_dest;
    OSG::Pnt4b  pnt4b_dest;
    OSG::Pnt4s  pnt4s_dest;
    OSG::Pnt4f  pnt4f_dest;
    OSG::Pnt4d  pnt4d_dest;
    OSG::Pnt4fx pnt4fx_dest;

    OSG::Color3ub col3ub_dest;
    OSG::Color3f  col3f_dest;
    OSG::Color3fx col3fx_dest;
    OSG::Color4ub col4ub_dest;
    OSG::Color4f  col4f_dest;
    OSG::Color4fx col4fx_dest;
};

// variable names and their meaning
//
//  SBase, DBase: source, destination variable base part: vec, pnt, col
//  SDim,  DDim:  source, destination variable size part: 1, 2, 3, 4
//  SType, DType: source, destination variable type part: b, ub, u, f, d
//
//  TDim:  number of elements to test: 1, 2, 3, 4
//  Dir:   conversion direction: In, Out

// Macros to compare conversion results - it makes only sense to compare
// as many elements as min(SourceDimension, DestinationDimension).
#define OSG_CONVERT_CHECK_1(DBase, DDim, DType)                   \
    CHECK(DBase##DDim##DType##_dest[0] == vec4##DType##_ref[0]);

#define OSG_CONVERT_CHECK_2(DBase, DDim, DType)                   \
    CHECK(DBase##DDim##DType##_dest[0] == vec4##DType##_ref[0]);  \
    CHECK(DBase##DDim##DType##_dest[1] == vec4##DType##_ref[1]);

#define OSG_CONVERT_CHECK_3(DBase, DDim, DType)                   \
    CHECK(DBase##DDim##DType##_dest[0] == vec4##DType##_ref[0]);  \
    CHECK(DBase##DDim##DType##_dest[1] == vec4##DType##_ref[1]);  \
    CHECK(DBase##DDim##DType##_dest[2] == vec4##DType##_ref[2]);

#define OSG_CONVERT_CHECK_4(DBase, DDim, DType)                   \
    CHECK(DBase##DDim##DType##_dest[0] == vec4##DType##_ref[0]);  \
    CHECK(DBase##DDim##DType##_dest[1] == vec4##DType##_ref[1]);  \
    CHECK(DBase##DDim##DType##_dest[2] == vec4##DType##_ref[2]);  \
    CHECK(DBase##DDim##DType##_dest[3] == vec4##DType##_ref[3]);

#define OSG_CONVERT_CHECK(DBase, DDim, DType, TDim)               \
    OSG_CONVERT_CHECK_##TDim(DBase, DDim, DType)

// Conversion an results checking macros
#define OSG_CONVERT_TO_LARGER(Dir, DBase, DDim, DType, SBase, SDim, SType)        \
    OSG::GeoConvert::convert##Dir(DBase##DDim##DType##_dest, SBase##SDim##SType); \
    OSG_CONVERT_CHECK(DBase, DDim, DType, SDim)

#define OSG_CONVERT_TO_SMALLER(Dir, DBase, DDim, DType, SBase, SDim, SType)       \
    OSG::GeoConvert::convert##Dir(DBase##DDim##DType##_dest, SBase##SDim##SType); \
    OSG_CONVERT_CHECK(DBase, DDim, DType, DDim)

#define OSG_CONVERT_NORM_TO_LARGER(Dir, DBase, DDim, DType, SBase, SDim, SType)   \
    OSG::GeoConvert::convert##Dir(DBase##DDim##DType##_dest, SBase##SDim##SType); \
    OSG_CONVERT_CHECK(DBase, DDim, DType, SDim)

#define OSG_CONVERT_NORM_TO_SMALLER(Dir, DBase, DDim, DType, SBase, SDim, SType)           \
    OSG::GeoConvertNormalize::convert##Dir(DBase##DDim##DType##_dest, SBase##SDim##SType); \
    OSG_CONVERT_CHECK(DBase, DDim, DType, DDim)

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Vecb)
{
    // from vec b to vec b
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 2, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, b, vec, 4, b);

    // from vec s to vec b
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 2, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, b, vec, 4, s);

    // from vec f to vec b
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 2, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, b, vec, 4, f);

    // from vec d to vec b
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 2, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, b, vec, 4, d);
    
    // from vec fx to vec b
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, b, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, b, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, b, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, b, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, b, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 2, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, b, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, b, vec, 4, fx);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Vecs)
{
    // from vec b to vec s
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 2, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, s, vec, 4, b);

    // from vec s to vec s
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 2, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, s, vec, 4, s);

    // from vec f to vec s
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 2, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, s, vec, 4, f);

    // from vec d to vec s
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 2, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, s, vec, 4, d);
    
    // from vec fx to vec s
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, s, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, s, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, s, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, s, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, s, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 2, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, s, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, s, vec, 4, fx);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Vecf)
{
    // from vec b to vec f
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 2, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, f, vec, 4, b);

    // from vec s to vec f
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 2, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, f, vec, 4, s);

    // from vec f to vec f
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 2, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, f, vec, 4, f);

    // from vec d to vec f
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 2, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, f, vec, 4, d);
    
    // from vec fx to vec s
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, f, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, f, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, f, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, f, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, f, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 2, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, f, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, f, vec, 4, fx);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Vecd)
{
    // from vec b to vec d
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 2, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, d, vec, 4, b);

    // from vec s to vec d
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 2, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, d, vec, 4, s);

    // from vec f to vec d
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 2, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, d, vec, 4, f);

    // from vec d to vec d
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 2, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, d, vec, 4, d);
    
    // from vec fx to vec d
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, d, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, d, vec, 1, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, d, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, d, vec, 2, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, d, vec, 4, fx);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 1, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 2, fx);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, d, vec, 3, fx);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, d, vec, 4, fx);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Vecfx)
{
    // from vec b to vec fx
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 1, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 2, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 3, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 4, b);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, fx, vec, 1, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 2, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 3, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 4, b);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 1, b);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 2, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 3, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 4, b);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 1, b);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 2, b);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 3, b);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, fx, vec, 4, b);

    // from vec s to vec fx
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 1, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 2, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 3, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 4, s);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, fx, vec, 1, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 2, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 3, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 4, s);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 1, s);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 2, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 3, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 4, s);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 1, s);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 2, s);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 3, s);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, fx, vec, 4, s);

    // from vec f to vec fx
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 2, fx, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, fx, vec, 4, f);

    // from vec d to vec fx
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 1, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 2, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 3, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 4, d);

//     OSG_CONVERT_TO_LARGER (In, vec, 2, fx, vec, 1, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 2, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 3, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 4, d);

//     OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 1, d);
//     OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 2, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 3, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 4, d);

//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 1, d);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 2, d);
//     OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 3, d);
//     OSG_CONVERT_TO_SMALLER(In, vec, 4, fx, vec, 4, d);
    
    // from vec fx to vec fx
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 1, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 2, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 3, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 1, fx, vec, 4, fx);

    OSG_CONVERT_TO_LARGER (In, vec, 2, fx, vec, 1, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 2, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 3, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 2, fx, vec, 4, fx);

    OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 1, fx);
    OSG_CONVERT_TO_LARGER (In, vec, 3, fx, vec, 2, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 3, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 3, fx, vec, 4, fx);

    OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 1, fx);
    OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 2, fx);
    OSG_CONVERT_TO_LARGER (In, vec, 4, fx, vec, 3, fx);
    OSG_CONVERT_TO_SMALLER(In, vec, 4, fx, vec, 4, fx);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Pntb)
{
    // from vec b to pnt b
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, b, vec, 4, b);

    // from vec s to pnt b
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, b, vec, 4, s);

    // from vec f to pnt b
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, b, vec, 4, f);

    // from vec d to pnt b
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Pnts)
{
    // from vec b to pnt s
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, s, vec, 4, b);

    // from vec s to pnt s
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, s, vec, 4, s);

    // from vec f to pnt s
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, s, vec, 4, f);

    // from vec d to pnt s
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Pntf)
{
    // from vec b to pnt f
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, f, vec, 4, b);

    // from vec s to pnt f
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, f, vec, 4, s);

    // from vec f to pnt f
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, f, vec, 4, f);

    // from vec d to pnt f
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Pntd)
{
    // from vec b to pnt d
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, d, vec, 4, b);

    // from vec s to pnt d
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, d, vec, 4, s);

    // from vec f to pnt d
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, d, vec, 4, f);

    // from vec d to pnt d
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 1, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 2, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 2, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 3, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 3, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, pnt, 4, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, pnt, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Col3ub)
{
    // vec to col3ub
    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, col, 3, ub, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, col, 3, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Col3f)
{
    // vec to col3f
    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, col, 3, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, col, 3, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Col4ub)
{
    // vec to col4ub
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, col, 4, ub, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, col, 4, ub, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, col, 4, ub, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, col, 4, ub, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, col, 4, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_In_Vec_To_Col4f)
{
    // vec to col4f
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 2, b);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(In, col, 4, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 2, s);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(In, col, 4, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 2, f);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(In, col, 4, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 2, d);
    OSG_CONVERT_TO_LARGER (In, col, 4, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(In, col, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Vecb)
{
    // from vec b to vec b
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, b, vec, 4, b);

    // from vec s to vec b
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, b, vec, 4, s);

    // from vec f to vec b
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, b, vec, 4, f);

    // from vec d to vec b
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Vecs)
{
    // from vec b to vec s
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, s, vec, 4, b);

    // from vec s to vec s
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, s, vec, 4, s);

    // from vec f to vec s
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, s, vec, 4, f);

    // from vec d to vec s
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Vecf)
{
    // from vec b to vec f
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, f, vec, 4, b);

    // from vec s to vec f
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, f, vec, 4, s);

    // from vec f to vec f
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, f, vec, 4, f);

    // from vec d to vec f
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Vecd)
{
    // from vec b to vec d
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, d, vec, 4, b);

    // from vec s to vec d
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, d, vec, 4, s);

    // from vec f to vec d
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, d, vec, 4, f);

    // from vec d to vec d
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 1, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 2, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 2, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 3, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 3, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, vec, 4, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, vec, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Pntb)
{
    // from vec b to pnt b
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, b, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, b, vec, 4, b);

    // from vec s to pnt b
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, b, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, b, vec, 4, s);

    // from vec f to pnt b
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, b, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, b, vec, 4, f);

    // from vec d to pnt b
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, b, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, b, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, b, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, b, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Pnts)
{
    // from vec b to pnt s
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, s, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, s, vec, 4, b);

    // from vec s to pnt s
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, s, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, s, vec, 4, s);

    // from vec f to pnt s
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, s, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, s, vec, 4, f);

    // from vec d to pnt s
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, s, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, s, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, s, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, s, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Pntf)
{
    // from vec b to pnt f
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, f, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, f, vec, 4, b);

    // from vec s to pnt f
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, f, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, f, vec, 4, s);

    // from vec f to pnt f
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, f, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, f, vec, 4, f);

    // from vec d to pnt f
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, f, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, f, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Pntd)
{
    // from vec b to pnt d
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, d, vec, 1, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, d, vec, 4, b);

    // from vec s to pnt d
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, d, vec, 1, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, d, vec, 4, s);

    // from vec f to pnt d
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, d, vec, 1, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, d, vec, 4, f);

    // from vec d to pnt d
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 1, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 2, d, vec, 1, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 2, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 3, d, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 3, d, vec, 4, d);

    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, pnt, 4, d, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, pnt, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Col3ub)
{
    // vec to col3ub
    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, col, 3, ub, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Col3f)
{
    // vec to col3f
    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 2, b);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 2, s);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 2, f);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, col, 3, f, vec, 2, d);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, col, 3, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Col4ub)
{
    // vec to col4ub
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, ub, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, ub, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, ub, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, col, 4, ub, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvert_Out_Vec_To_Col4f)
{
    // vec to col4f
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 1, b);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 2, b);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 3, b);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, f, vec, 4, b);

    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 1, s);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 2, s);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 3, s);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, f, vec, 4, s);

    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 1, f);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 2, f);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 3, f);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, f, vec, 4, f);

    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 1, d);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 2, d);
    OSG_CONVERT_TO_LARGER (Out, col, 4, f, vec, 3, d);
    OSG_CONVERT_TO_SMALLER(Out, col, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Vecb)
{
    // from vec b to vec b
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, b, vec, 4, b);

    // from vec s to vec b
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, b, vec, 4, s);

    // from vec f to vec b
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, b, vec, 4, f);

    // from vec d to vec b
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Vecs)
{
    // from vec b to vec s
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, s, vec, 4, b);

    // from vec s to vec s
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, s, vec, 4, s);

    // from vec f to vec s
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, s, vec, 4, f);

    // from vec d to vec s
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Vecf)
{
    // from vec b to vec f
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, f, vec, 4, b);

    // from vec s to vec f
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, f, vec, 4, s);

    // from vec f to vec f
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, f, vec, 4, f);

    // from vec d to vec f
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Vecd)
{
    // from vec b to vec d
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, d, vec, 4, b);

    // from vec s to vec d
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, d, vec, 4, s);

    // from vec f to vec d
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, d, vec, 4, f);

    // from vec d to vec d
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 1, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 2, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 2, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 3, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 3, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, vec, 4, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, vec, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Pntb)
{
    // from vec b to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, b, vec, 4, b);

    // from vec s to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, b, vec, 4, s);

    // from vec f to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, b, vec, 4, f);

    // from vec d to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Pnts)
{
    // from vec b to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, s, vec, 4, b);

    // from vec s to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, s, vec, 4, s);

    // from vec f to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, s, vec, 4, f);

    // from vec d to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Pntf)
{
    // from vec b to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, f, vec, 4, b);

    // from vec s to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, f, vec, 4, s);

    // from vec f to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, f, vec, 4, f);

    // from vec d to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Pntd)
{
    // from vec b to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, d, vec, 4, b);

    // from vec s to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, d, vec, 4, s);

    // from vec f to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, d, vec, 4, f);

    // from vec d to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 1, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 2, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 2, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 3, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 3, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, pnt, 4, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, pnt, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Col3ub)
{
    // vec to col3ub
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, ub, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Col3f)
{
    // vec to col3f
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 3, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 3, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Col4ub)
{
    // vec to col4ub
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, ub, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, ub, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, ub, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, ub, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_In_Vec_To_Col4f)
{
    // vec to col4f
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (In, col, 4, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(In, col, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Vecb)
{
    // from vec b to vec b
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, b, vec, 4, b);

    // from vec s to vec b
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, b, vec, 4, s);

    // from vec f to vec b
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, b, vec, 4, f);

    // from vec d to vec b
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Vecs)
{
    // from vec b to vec s
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, s, vec, 4, b);

    // from vec s to vec s
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, s, vec, 4, s);

    // from vec f to vec s
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, s, vec, 4, f);

    // from vec d to vec s
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Vecf)
{
    // from vec b to vec f
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, f, vec, 4, b);

    // from vec s to vec f
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, f, vec, 4, s);

    // from vec f to vec f
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, f, vec, 4, f);

    // from vec d to vec f
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Vecd)
{
    // from vec b to vec d
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, d, vec, 4, b);

    // from vec s to vec d
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, d, vec, 4, s);

    // from vec f to vec d
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, d, vec, 4, f);

    // from vec d to vec d
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 1, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 2, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 2, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 3, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 3, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, vec, 4, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, vec, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Pntb)
{
    // from vec b to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, b, vec, 4, b);

    // from vec s to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, b, vec, 4, s);

    // from vec f to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, b, vec, 4, f);

    // from vec d to pnt b
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, b, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, b, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, b, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Pnts)
{
    // from vec b to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, s, vec, 4, b);

    // from vec s to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, s, vec, 4, s);

    // from vec f to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, s, vec, 4, f);

    // from vec d to pnt s
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, s, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, s, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, s, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Pntf)
{
    // from vec b to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, f, vec, 4, b);

    // from vec s to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, f, vec, 4, s);

    // from vec f to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, f, vec, 4, f);

    // from vec d to pnt f
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, f, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Pntd)
{
    // from vec b to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, d, vec, 4, b);

    // from vec s to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, d, vec, 4, s);

    // from vec f to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, d, vec, 4, f);

    // from vec d to pnt d
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 1, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 2, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 2, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 3, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 3, d, vec, 4, d);

    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, pnt, 4, d, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, pnt, 4, d, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Col3ub)
{
    // vec to col3ub
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, ub, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Col3f)
{
    // vec to col3f
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 3, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 3, f, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Col4ub)
{
    // vec to col4ub
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, ub, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, ub, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, ub, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, ub, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, ub, vec, 4, d);
}

TEST_FIXTURE(GeoConvertFixture, GeoConvertNormalize_Out_Vec_To_Col4f)
{
    // vec to col4f
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 1, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 2, b);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 3, b);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, f, vec, 4, b);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 1, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 2, s);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 3, s);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, f, vec, 4, s);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 1, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 2, f);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 3, f);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, f, vec, 4, f);

    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 1, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 2, d);
    OSG_CONVERT_NORM_TO_LARGER (Out, col, 4, f, vec, 3, d);
    OSG_CONVERT_NORM_TO_SMALLER(Out, col, 4, f, vec, 4, d);
}

#undef OSG_CONVERT_CHECK_1
#undef OSG_CONVERT_CHECK_2
#undef OSG_CONVERT_CHECK_3
#undef OSG_CONVERT_CHECK_4
#undef OSG_CONVERT_CHECK
#undef OSG_CONVERT_TO_LARGER
#undef OSG_CONVERT_TO_SMALLER
#undef OSG_CONVERT_NORM_TO_LARGER
#undef OSG_CONVERT_NORM_TO_SMALLER

}
