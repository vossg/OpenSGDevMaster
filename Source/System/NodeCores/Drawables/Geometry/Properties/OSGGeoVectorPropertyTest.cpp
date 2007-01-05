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

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGGeoVectorProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>

namespace {

struct GeoVectorPropertyFixture
{
    GeoVectorPropertyFixture(void) :
        p3f_0(1.0, 2.0, 3.0),
        p3f_1(2.0, 3.0, 4.0),
        p3f_2(3.0, 4.0, 5.0),
        propP3f(OSG::NullFC)
    {
        propP3f = OSG::GeoPnt3fProperty::create();

        propP3f->addValue(p3f_0);
        propP3f->addValue(p3f_1);
        propP3f->addValue(p3f_2);
    }

    ~GeoVectorPropertyFixture(void)
    {
    }

    const OSG::Pnt3f p3f_0;
    const OSG::Pnt3f p3f_1;
    const OSG::Pnt3f p3f_2;

    OSG::GeoPnt3fPropertyPtr propP3f;
};


TEST_FIXTURE(GeoVectorPropertyFixture, GeoVectorProperty_Pnt3f)
{
    OSG::GeoVectorPropertyPtr prop = propP3f;  // throw away static type info
    OSG::Pnt2f  p2f;
    OSG::Pnt2d  p2d;
    OSG::Pnt2ub p2ub;
    OSG::Pnt2us p2us;

    OSG::Pnt3f  p3f;
    OSG::Pnt3d  p3d;
    OSG::Pnt3ub p3ub;
    OSG::Pnt3us p3us;

    OSG::Vec3d  v3d;
    OSG::Vec3us v3us;

    prop->getValue(p2f, 0);
    CHECK(p2f[0] == p3f_0[0]);
    CHECK(p2f[1] == p3f_0[1]);

    prop->getValue(p2d, 0);
    CHECK(p2d[0] == p3f_0[0]);
    CHECK(p2d[1] == p3f_0[1]);

    prop->getValue(p2ub, 1);
    CHECK(p2ub[0] == p3f_1[0]);
    CHECK(p2ub[1] == p3f_1[1]);

    prop->getValue(p2us, 1);
    CHECK(p2us[0] == p3f_1[0]);
    CHECK(p2us[1] == p3f_1[1]);

    prop->getValue(p3f, 2);
    CHECK(p3f[0] == p3f_2[0]);
    CHECK(p3f[1] == p3f_2[1]);
    CHECK(p3f[2] == p3f_2[2]);

    prop->getValue(p3d, 2);
    CHECK(p3d[0] == p3f_2[0]);
    CHECK(p3d[1] == p3f_2[1]);
    CHECK(p3d[2] == p3f_2[2]);

    prop->getValue(p3ub, 2);
    CHECK(p3ub[0] == p3f_2[0]);
    CHECK(p3ub[1] == p3f_2[1]);
    CHECK(p3ub[2] == p3f_2[2]);

    prop->getValue(p3us, 2);
    CHECK(p3us[0] == p3f_2[0]);
    CHECK(p3us[1] == p3f_2[1]);
    CHECK(p3us[2] == p3f_2[2]);


    prop->getValue(v3d, 2);
    CHECK(v3d[0] == p3f_2[0]);
    CHECK(v3d[1] == p3f_2[1]);
    CHECK(v3d[2] == p3f_2[2]);

    prop->getValue(v3us, 1);
    CHECK(v3us[0] == p3f_1[0]);
    CHECK(v3us[1] == p3f_1[1]);
    CHECK(v3us[2] == p3f_1[2]);


    propP3f->getValue(p3f, 1);
    CHECK(p3f[0] == p3f_1[0]);
    CHECK(p3f[1] == p3f_1[1]);
    CHECK(p3f[2] == p3f_1[2]);

    propP3f->getValue(p3d, 2);
    CHECK(p3d[0] == p3f_2[0]);
    CHECK(p3d[1] == p3f_2[1]);
    CHECK(p3d[2] == p3f_2[2]);

    propP3f->getValue(p3ub, 2);
    CHECK(p3ub[0] == p3f_2[0]);
    CHECK(p3ub[1] == p3f_2[1]);
    CHECK(p3ub[2] == p3f_2[2]);

    propP3f->getValue(p3us, 2);
    CHECK(p3us[0] == p3f_2[0]);
    CHECK(p3us[1] == p3f_2[1]);
    CHECK(p3us[2] == p3f_2[2]);
}

} // namespace
