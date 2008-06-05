/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

// System declarations

#include "OSGConfig.h"

// Class declarations
#include "OSGVector.h"
#include "OSGVector.ins"

#include "OSGMathIO.h"

OSG_BEGIN_NAMESPACE

// Null values

//OSG_BASE_DLLMAPPING Vec2f   OSG::NullVec2f( 0,0 );
//OSG_BASE_DLLMAPPING Vec3f   OSG::NullVec3f( 0,0,0 );
//OSG_BASE_DLLMAPPING Vec4f   OSG::NullVec4f( 0,0,0,0 );
//OSG_BASE_DLLMAPPING Vec2s   OSG::NullVec2s( 0,0 );
//OSG_BASE_DLLMAPPING Vec4ub  OSG::NullVec4ub( 0,0,0,0 );
//OSG_BASE_DLLMAPPING Pnt2f   OSG::NullPnt2f( 0,0 );
//OSG_BASE_DLLMAPPING Pnt3f   OSG::NullPnt3f( 0,0,0 );
//OSG_BASE_DLLMAPPING Pnt3d   OSG::NullPnt3d( 0,0,0 );
//OSG_BASE_DLLMAPPING Pnt4f   OSG::NullPnt4f( 0,0,0,0 );
//OSG_BASE_DLLMAPPING Pnt2s   OSG::NullPnt2s( 0,0 );

#ifdef darwinXXX

template <>
const Vector< UInt8, 1 > Vector< UInt8, 1 >::Null(0);

template <>
const Vector< UInt8, 2 > Vector< UInt8, 2 >::Null(0, 0);

template <>
const Vector< UInt8, 3 > Vector< UInt8, 3 >::Null(0, 0, 0);

template <>
const Vector< UInt8, 4 > Vector< UInt8, 4 >::Null(0, 0, 0, 1);

template <>
const Vector< Int8, 1 >  Vector< Int8, 1 >::Null(0);

template <>
const Vector< Int8, 2 > Vector< Int8, 2 >::Null(0, 0);

template <>
const Vector< Int8, 3 > Vector< Int8, 3 >::Null(0, 0, 0);

template <>
const Vector< Int8, 4 > Vector< Int8, 4 >::Null(0, 0, 0, 1);

template <>
const Vector< UInt16, 1 > Vector< UInt16, 1 >::Null(0);

template <>
const Vector< UInt16, 2 > Vector< UInt16, 2 >::Null(0, 0);

template <>
const Vector< UInt16, 3 > Vector< UInt16, 3 >::Null(0, 0, 0);

template <>
const Vector< UInt16, 4 > Vector< UInt16, 4 >::Null(0, 0, 0, 1);

template <>
const Vector< Int16, 1 > Vector< Int16, 1 >::Null(0);

template <>
const Vector< Int16, 2 > Vector< Int16, 2 >::Null(0, 0);

template <>
const Vector< Int16, 3 > Vector< Int16, 3 >::Null(0, 0, 0);

template <>
const Vector< Int16, 4 > Vector< Int16, 4 >::Null(0, 0, 0, 1);

template <>
const Vector< Real32, 1 > Vector< Real32, 1 >::Null(0.f);

template <>
const Vector< Real32, 2 > Vector< Real32, 2 >::Null(0.f, 0.f);

template <>
const Vector< Real32, 3 > Vector< Real32, 3 >::Null(0.f, 0.f, 0.f);

template <>
const Vector< Real32, 4 > Vector< Real32, 4 >::Null(0.f, 0.f, 0.f, 1.f);

template <>
const Vector< Real64, 1 > Vector< Real64, 1 >::Null(0.);

template <>
const Vector< Real64, 2 > Vector< Real64, 2 >::Null(0., 0.);

template <>
const Vector< Real64, 3 > Vector< Real64, 3 >::Null(0., 0., 0.);

template <>
const Vector< Real64, 4 > Vector< Real64, 4 >::Null(0., 0., 0., 1.);

template <>
const Vector< Real128, 1 > Vector< Real128, 1 >::Null(0.);

template <>
const Vector< Real128, 2 > Vector< Real128, 2 >::Null(0., 0.);

template <>
const Vector< Real128, 3 > Vector< Real128, 3 >::Null(0., 0., 0.);

template <>
const Vector< Real128, 4 > Vector< Real128, 4 >::Null(0., 0., 0., 1.);



template <>
const Point< UInt8, 1 > Point< UInt8, 1 >::Null(0);

template <>
const Point< UInt8, 2 > Point< UInt8, 2 >::Null(0, 0);

template <>
const Point< UInt8, 3 > Point< UInt8, 3 >::Null(0, 0, 0);

template <>
const Point< UInt8, 4 > Point< UInt8, 4 >::Null(0, 0, 0, 1);

template <>
const Point< Int8, 1 > Point< Int8, 1 >::Null(0);

template <>
const Point< Int8, 2 > Point< Int8, 2 >::Null(0, 0);

template <>
const Point< Int8, 3 > Point< Int8, 3 >::Null(0, 0, 0);

template <>
const Point< Int8, 4 > Point< Int8, 4 >::Null(0, 0, 0, 1);

template <>
const Point< UInt16, 1 > Point< UInt16, 1 >::Null(0);

template <>
const Point< UInt16, 2 > Point< UInt16, 2 >::Null(0, 0);

template <>
const Point< UInt16, 3 > Point< UInt16, 3 >::Null(0, 0, 0);

template <>
const Point< UInt16, 4 > Point< UInt16, 4 >::Null(0, 0, 0, 1);

template <>
const Point< Int16, 1 > Point< Int16, 1 >::Null(0);

template <>
const Point< Int16, 2 > Point< Int16, 2 >::Null(0, 0);

template <>
const Point< Int16, 3 > Point< Int16, 3 >::Null(0, 0, 0);

template <>
const Point< Int16, 4 > Point< Int16, 4 >::Null(0, 0, 0, 1);

template <>
const Point< Real32, 1 > Point< Real32, 1 >::Null(0.f);

template <>
const Point< Real32, 2 > Point< Real32, 2 >::Null(0.f, 0.f);

template <>
const Point< Real32, 3 > Point< Real32, 3 >::Null(0.f, 0.f, 0.f);

template <>
const Point< Real32, 4 > Point< Real32, 4 >::Null(0.f, 0.f, 0.f, 1.f);

template <>
const Point< Real64, 1 > Point< Real64, 1 >::Null(0.);

template <>
const Point< Real64, 2 > Point< Real64, 2 >::Null(0., 0.);

template <>
const Point< Real64, 3 > Point< Real64, 3 >::Null(0., 0., 0.);

template <>
const Point< Real64, 4 > Point< Real64, 4 >::Null(0., 0., 0., 1.);

template <>
const Point< Real128, 1 > Point< Real128, 1 >::Null(0.);

template <>
const Point< Real128, 2 > Point< Real128, 2 >::Null(0., 0.);

template <>
const Point< Real128, 3 > Point< Real128, 3 >::Null(0., 0., 0.);

template <>
const Point< Real128, 4 > Point< Real128, 4 >::Null(0., 0., 0., 1.);

/*
template <>
const Point<> Point<>::Null;
    */
#endif

#define OSG_VECPNT_IO_OP_INST(OSG_VALUE_TYPE)                               \
OSG_POINT_OUTPUT_OP_INST(OSG_VALUE_TYPE, 2)                                 \
OSG_POINT_OUTPUT_OP_INST(OSG_VALUE_TYPE, 3)                                 \
OSG_POINT_OUTPUT_OP_INST(OSG_VALUE_TYPE, 4)                                 \
OSG_POINT_INPUT_OP_INST(OSG_VALUE_TYPE, 2)                                  \
OSG_POINT_INPUT_OP_INST(OSG_VALUE_TYPE, 3)                                  \
OSG_POINT_INPUT_OP_INST(OSG_VALUE_TYPE, 4)                                  \
                                                                            \
OSG_VECTOR_OUTPUT_OP_INST(OSG_VALUE_TYPE, 2)                                \
OSG_VECTOR_OUTPUT_OP_INST(OSG_VALUE_TYPE, 3)                                \
OSG_VECTOR_OUTPUT_OP_INST(OSG_VALUE_TYPE, 4)                                \
OSG_VECTOR_INPUT_OP_INST(OSG_VALUE_TYPE, 2)                                 \
OSG_VECTOR_INPUT_OP_INST(OSG_VALUE_TYPE, 3)                                 \
OSG_VECTOR_INPUT_OP_INST(OSG_VALUE_TYPE, 4)

OSG_VECPNT_IO_OP_INST(Real32)
OSG_VECPNT_IO_OP_INST(Real64)
OSG_VECPNT_IO_OP_INST(Fixed32)

OSG_VECPNT_IO_OP_INST(Int8)
OSG_VECPNT_IO_OP_INST(UInt8)
OSG_VECPNT_IO_OP_INST(Int16)
OSG_VECPNT_IO_OP_INST(UInt16)
OSG_VECPNT_IO_OP_INST(Int32)
OSG_VECPNT_IO_OP_INST(UInt32)

#undef OSG_VECPNT_IO_OP_INST

OSG_END_NAMESPACE
