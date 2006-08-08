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

OSG_USING_NAMESPACE

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
const VectorInterface< UInt8, VecStorage1<UInt8> >
    VectorInterface< UInt8, VecStorage1<UInt8> >::Null(0);

template <>
const VectorInterface< UInt8, VecStorage2<UInt8> >
    VectorInterface< UInt8, VecStorage2<UInt8> >::Null(0, 0);

template <>
const VectorInterface< UInt8, VecStorage3<UInt8> >
    VectorInterface< UInt8, VecStorage3<UInt8> >::Null(0, 0, 0);

template <>
const VectorInterface< UInt8, VecStorage4<UInt8> >
    VectorInterface< UInt8, VecStorage4<UInt8> >::Null(0, 0, 0, 1);

template <>
const VectorInterface< Int8, VecStorage1<Int8> >
    VectorInterface< Int8, VecStorage1<Int8> >::Null(0);

template <>
const VectorInterface< Int8, VecStorage2<Int8> >
    VectorInterface< Int8, VecStorage2<Int8> >::Null(0, 0);

template <>
const VectorInterface< Int8, VecStorage3<Int8> >
    VectorInterface< Int8, VecStorage3<Int8> >::Null(0, 0, 0);

template <>
const VectorInterface< Int8, VecStorage4<Int8> >
    VectorInterface< Int8, VecStorage4<Int8> >::Null(0, 0, 0, 1);

template <>
const VectorInterface< UInt16, VecStorage1<UInt16> >
    VectorInterface< UInt16, VecStorage1<UInt16> >::Null(0);

template <>
const VectorInterface< UInt16, VecStorage2<UInt16> >
    VectorInterface< UInt16, VecStorage2<UInt16> >::Null(0, 0);

template <>
const VectorInterface< UInt16, VecStorage3<UInt16> >
    VectorInterface< UInt16, VecStorage3<UInt16> >::Null(0, 0, 0);

template <>
const VectorInterface< UInt16, VecStorage4<UInt16> >
    VectorInterface< UInt16, VecStorage4<UInt16> >::Null(0, 0, 0, 1);

template <>
const VectorInterface< Int16, VecStorage1<Int16> >
    VectorInterface< Int16, VecStorage1<Int16> >::Null(0);

template <>
const VectorInterface< Int16, VecStorage2<Int16> >
    VectorInterface< Int16, VecStorage2<Int16> >::Null(0, 0);

template <>
const VectorInterface< Int16, VecStorage3<Int16> >
    VectorInterface< Int16, VecStorage3<Int16> >::Null(0, 0, 0);

template <>
const VectorInterface< Int16, VecStorage4<Int16> >
    VectorInterface< Int16, VecStorage4<Int16> >::Null(0, 0, 0, 1);

template <>
const VectorInterface< Real32, VecStorage1<Real32> >
    VectorInterface< Real32, VecStorage1<Real32> >::Null(0.f);

template <>
const VectorInterface< Real32, VecStorage2<Real32> >
    VectorInterface< Real32, VecStorage2<Real32> >::Null(0.f, 0.f);

template <>
const VectorInterface< Real32, VecStorage3<Real32> >
    VectorInterface< Real32, VecStorage3<Real32> >::Null(0.f, 0.f, 0.f);

template <>
const VectorInterface< Real32, VecStorage4<Real32> >
    VectorInterface< Real32, VecStorage4<Real32> >::Null(0.f, 0.f, 0.f, 1.f);

template <>
const VectorInterface< Real64, VecStorage1<Real64> >
    VectorInterface< Real64, VecStorage1<Real64> >::Null(0.);

template <>
const VectorInterface< Real64, VecStorage2<Real64> >
    VectorInterface< Real64, VecStorage2<Real64> >::Null(0., 0.);

template <>
const VectorInterface< Real64, VecStorage3<Real64> >
    VectorInterface< Real64, VecStorage3<Real64> >::Null(0., 0., 0.);

template <>
const VectorInterface< Real64, VecStorage4<Real64> >
    VectorInterface< Real64, VecStorage4<Real64> >::Null(0., 0., 0., 1.);

template <>
const VectorInterface< Real128, VecStorage1<Real128> >
    VectorInterface< Real128, VecStorage1<Real128> >::Null(0.);

template <>
const VectorInterface< Real128, VecStorage2<Real128> >
    VectorInterface< Real128, VecStorage2<Real128> >::Null(0., 0.);

template <>
const VectorInterface< Real128, VecStorage3<Real128> >
    VectorInterface< Real128, VecStorage3<Real128> >::Null(0., 0., 0.);

template <>
const VectorInterface< Real128, VecStorage4<Real128> >
    VectorInterface< Real128, VecStorage4<Real128> >::Null(0., 0., 0., 1.);



template <>
const PointInterface< UInt8, VecStorage1<UInt8> >
    PointInterface< UInt8, VecStorage1<UInt8> >::Null(0);

template <>
const PointInterface< UInt8, VecStorage2<UInt8> >
    PointInterface< UInt8, VecStorage2<UInt8> >::Null(0, 0);

template <>
const PointInterface< UInt8, VecStorage3<UInt8> >
    PointInterface< UInt8, VecStorage3<UInt8> >::Null(0, 0, 0);

template <>
const PointInterface< UInt8, VecStorage4<UInt8> >
    PointInterface< UInt8, VecStorage4<UInt8> >::Null(0, 0, 0, 1);

template <>
const PointInterface< Int8, VecStorage1<Int8> >
    PointInterface< Int8, VecStorage1<Int8> >::Null(0);

template <>
const PointInterface< Int8, VecStorage2<Int8> >
    PointInterface< Int8, VecStorage2<Int8> >::Null(0, 0);

template <>
const PointInterface< Int8, VecStorage3<Int8> >
    PointInterface< Int8, VecStorage3<Int8> >::Null(0, 0, 0);

template <>
const PointInterface< Int8, VecStorage4<Int8> >
    PointInterface< Int8, VecStorage4<Int8> >::Null(0, 0, 0, 1);

template <>
const PointInterface< UInt16, VecStorage1<UInt16> >
    PointInterface< UInt16, VecStorage1<UInt16> >::Null(0);

template <>
const PointInterface< UInt16, VecStorage2<UInt16> >
    PointInterface< UInt16, VecStorage2<UInt16> >::Null(0, 0);

template <>
const PointInterface< UInt16, VecStorage3<UInt16> >
    PointInterface< UInt16, VecStorage3<UInt16> >::Null(0, 0, 0);

template <>
const PointInterface< UInt16, VecStorage4<UInt16> >
    PointInterface< UInt16, VecStorage4<UInt16> >::Null(0, 0, 0, 1);

template <>
const PointInterface< Int16, VecStorage1<Int16> >
    PointInterface< Int16, VecStorage1<Int16> >::Null(0);

template <>
const PointInterface< Int16, VecStorage2<Int16> >
    PointInterface< Int16, VecStorage2<Int16> >::Null(0, 0);

template <>
const PointInterface< Int16, VecStorage3<Int16> >
    PointInterface< Int16, VecStorage3<Int16> >::Null(0, 0, 0);

template <>
const PointInterface< Int16, VecStorage4<Int16> >
    PointInterface< Int16, VecStorage4<Int16> >::Null(0, 0, 0, 1);

template <>
const PointInterface< Real32, VecStorage1<Real32> >
    PointInterface< Real32, VecStorage1<Real32> >::Null(0.f);

template <>
const PointInterface< Real32, VecStorage2<Real32> >
    PointInterface< Real32, VecStorage2<Real32> >::Null(0.f, 0.f);

template <>
const PointInterface< Real32, VecStorage3<Real32> >
    PointInterface< Real32, VecStorage3<Real32> >::Null(0.f, 0.f, 0.f);

template <>
const PointInterface< Real32, VecStorage4<Real32> >
    PointInterface< Real32, VecStorage4<Real32> >::Null(0.f, 0.f, 0.f, 1.f);

template <>
const PointInterface< Real64, VecStorage1<Real64> >
    PointInterface< Real64, VecStorage1<Real64> >::Null(0.);

template <>
const PointInterface< Real64, VecStorage2<Real64> >
    PointInterface< Real64, VecStorage2<Real64> >::Null(0., 0.);

template <>
const PointInterface< Real64, VecStorage3<Real64> >
    PointInterface< Real64, VecStorage3<Real64> >::Null(0., 0., 0.);

template <>
const PointInterface< Real64, VecStorage4<Real64> >
    PointInterface< Real64, VecStorage4<Real64> >::Null(0., 0., 0., 1.);

template <>
const PointInterface< Real128, VecStorage1<Real128> >
    PointInterface< Real128, VecStorage1<Real128> >::Null(0.);

template <>
const PointInterface< Real128, VecStorage2<Real128> >
    PointInterface< Real128, VecStorage2<Real128> >::Null(0., 0.);

template <>
const PointInterface< Real128, VecStorage3<Real128> >
    PointInterface< Real128, VecStorage3<Real128> >::Null(0., 0., 0.);

template <>
const PointInterface< Real128, VecStorage4<Real128> >
    PointInterface< Real128, VecStorage4<Real128> >::Null(0., 0., 0., 1.);

/*
template <>
const PointInterface<>
    PointInterface<>::Null;
    */
#endif
