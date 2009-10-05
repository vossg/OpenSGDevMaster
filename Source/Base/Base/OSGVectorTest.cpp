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

// Unit tests for vec classes

#include "OSGVector.h"

OSG_USING_NAMESPACE

SUITE(VectorTests)
{

TEST(InstantiateAllVectorTypes)
{
    Vec1f  v1f;
    Vec2f  v2f;
    Vec3f  v3f;
    Vec4f  v4f;

    Vec1d  v1d;
    Vec2d  v2d;
    Vec3d  v3d;
    Vec4d  v4d;

    Vec1ub v1ub;
    Vec2ub v2ub;
    Vec3ub v3ub;
    Vec4ub v4ub;

    Vec1b  v1b;
    Vec2b  v2b;
    Vec3b  v3b;
    Vec4b  v4b;

    Vec1us v1us;
    Vec2us v2us;
    Vec3us v3us;
    Vec4us v4us;

    Vec1s  v1s;
    Vec2s  v2s;
    Vec3s  v3s;
    Vec4s  v4s;

    Vec1fx v1fx;
    Vec2fx v2fx;
    Vec3fx v3fx;
    Vec4fx v4fx;

    CHECK(true);
}


TEST(InstantiateAllPointTypes)
{
    Pnt1f  p1f;
    Pnt2f  p2f;
    Pnt3f  p3f;
    Pnt4f  p4f;

    Pnt1d  p1d;
    Pnt2d  p2d;
    Pnt3d  p3d;
    Pnt4d  p4d;

    Pnt1ub p1ub;
    Pnt2ub p2ub;
    Pnt3ub p3ub;
    Pnt4ub p4ub;

    Pnt1b  p1b;
    Pnt2b  p2b;
    Pnt3b  p3b;
    Pnt4b  p4b;

    Pnt1us p1us;
    Pnt2us p2us;
    Pnt3us p3us;
    Pnt4us p4us;

    Pnt1s  p1s;
    Pnt2s  p2s;
    Pnt3s  p3s;
    Pnt4s  p4s;

    Pnt1fx p1fx;
    Pnt2fx p2fx;
    Pnt3fx p3fx;
    Pnt4fx p4fx;

    CHECK(true);
}

TEST(VectorPointIO)
{
    std::stringstream iostream;

    Vec3f v3f(1.f, 2.f, 3.f     );
    Vec4f v4f(1.f, 2.f, 3.f, 4.f);

    Pnt3f p3f(1.f, 2.f, 3.f     );
    Pnt4f p4f(1.f, 2.f, 3.f, 4.f);


    iostream << v3f;
    Vec3f v3f_2;
    iostream >> v3f_2;
    CHECK_EQUAL(v3f, v3f_2);

    iostream.clear();

    iostream << v4f;
    Vec4f v4f_2;
    iostream >> v4f_2;
    CHECK_EQUAL(v4f, v4f_2);

    iostream.clear();

    iostream << p3f;
    Pnt3f p3f_2;
    iostream >> p3f_2;
    CHECK_EQUAL(p3f, p3f_2);

    iostream.clear();

    iostream << p4f;
    Pnt4f p4f_2;
    iostream >> p4f_2;
    CHECK_EQUAL(p4f, p4f_2);
}

} // SUITE
