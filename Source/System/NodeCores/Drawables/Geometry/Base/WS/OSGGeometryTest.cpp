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

#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGeoVectorProperty.h>
#include <OpenSG/OSGGeoProperties.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>

SUITE(GeometryTests)
{

TEST(CreateGeometry)
{
    OSG::GeometryPtr g = OSG::Geometry::create();
    CHECK(g != OSGNullFC);
}

TEST(TestInitialValues)
{
    OSG::GeometryPtr g = OSG::Geometry::create();
    CHECK(g != OSGNullFC);

    for(unsigned i=0;i<OSG::Geometry::MaxAttribs;i++)
    {
        CHECK(g->getProperty(i) == OSGNullFC);
        CHECK(g->getIndex(i) == OSGNullFC);
    }

    CHECK(g->getMaterial() == OSGNullFC);
}

// Test using the generic vector interfaces on geometry
TEST(TestGenericInterfaces)
{
    OSG::GeometryPtr g = OSG::Geometry::create();
    CHECK(g != OSGNullFC);

    OSG::GeoPnt3fPropertyPtr  pnts  = OSG::GeoPnt3fProperty ::create();
    pnts->addValue(OSG::Pnt3f(0,0,0));

    g->setPositions(pnts);

    OSG::GeoVectorPropertyPtr pnts_g = g->getPositions();
    pnts_g->setValue(OSG::Pnt3f(1,1,1), 0);
    pnts_g->setValue(OSG::Pnt3s(1,1,1), 0);
    pnts_g->setValue(OSG::Pnt2f(1,1  ), 0);
    pnts_g->setValue(OSG::Vec3f(1,1,1), 0);
    pnts_g->setValue(OSG::Vec2f(1,2  ), 0);
    pnts_g->setValue(OSG::Vec4f(1,2,3,4), 0);
    pnts_g->setValue(OSG::Color3f(1,2,3), 0);
    pnts_g->setValue(OSG::Color4f(1,2,3,4), 0);
}


TEST(TestSettingVecAttribs)
{
    // Test setting attributes to all possible value types
    OSG::GeometryPtr g = OSG::Geometry::create();
    CHECK(g != OSGNullFC);

    // Copied-and-macroed from OSGTypedGeoVectorPropertyFields
    char* allowed_vec_prop_types[] =
    {
        "GeoVec1ubProperty",
        "GeoVec2ubProperty",
        "GeoVec3ubProperty",
        "GeoVec4ubProperty",

        "GeoPnt1ubProperty",
        "GeoPnt2ubProperty",
        "GeoPnt3ubProperty",
        "GeoPnt4ubProperty",

        "GeoVec1NubProperty",
        "GeoVec2NubProperty",
        "GeoVec3NubProperty",
        "GeoVec4NubProperty",

        "GeoPnt1NubProperty",
        "GeoPnt2NubProperty",
        "GeoPnt3NubProperty",
        "GeoPnt4NubProperty",


        "GeoVec1bProperty",
        "GeoVec2bProperty",
        "GeoVec3bProperty",
        "GeoVec4bProperty",

        "GeoPnt1bProperty",
        "GeoPnt2bProperty",
        "GeoPnt3bProperty",
        "GeoPnt4bProperty",

        "GeoVec1NbProperty",
        "GeoVec2NbProperty",
        "GeoVec3NbProperty",
        "GeoVec4NbProperty",

        "GeoPnt1NbProperty",
        "GeoPnt2NbProperty",
        "GeoPnt3NbProperty",
        "GeoPnt4NbProperty",


        "GeoVec1usProperty",
        "GeoVec2usProperty",
        "GeoVec3usProperty",
        "GeoVec4usProperty",

        "GeoPnt1usProperty",
        "GeoPnt2usProperty",
        "GeoPnt3usProperty",
        "GeoPnt4usProperty",

        "GeoVec1NusProperty",
        "GeoVec2NusProperty",
        "GeoVec3NusProperty",
        "GeoVec4NusProperty",

        "GeoPnt1NusProperty",
        "GeoPnt2NusProperty",
        "GeoPnt3NusProperty",
        "GeoPnt4NusProperty",


        "GeoVec1sProperty",
        "GeoVec2sProperty",
        "GeoVec3sProperty",
        "GeoVec4sProperty",

        "GeoPnt1sProperty",
        "GeoPnt2sProperty",
        "GeoPnt3sProperty",
        "GeoPnt4sProperty",

        "GeoVec1NsProperty",
        "GeoVec2NsProperty",
        "GeoVec3NsProperty",
        "GeoVec4NsProperty",

        "GeoPnt1NsProperty",
        "GeoPnt2NsProperty",
        "GeoPnt3NsProperty",
        "GeoPnt4NsProperty",

#ifndef OSG_WINCE
        "GeoVec1fProperty",
        "GeoVec2fProperty",
        "GeoVec3fProperty",
        "GeoVec4fProperty",

        "GeoPnt1fProperty",
        "GeoPnt2fProperty",
        "GeoPnt3fProperty",
        "GeoPnt4fProperty",
#endif

#ifdef OSG_WINCE
        "GeoVec1fxProperty",
        "GeoVec2fxProperty",
        "GeoVec3fxProperty",
        "GeoVec4fxProperty",

        "GeoPnt1fxProperty",
        "GeoPnt2fxProperty",
        "GeoPnt3fxProperty",
        "GeoPnt4fxProperty",
#endif

#ifndef OSG_WINCE
        "GeoVec1dProperty",
        "GeoVec2dProperty",
        "GeoVec3dProperty",
        "GeoVec4dProperty",

        "GeoPnt1dProperty",
        "GeoPnt2dProperty",
        "GeoPnt3dProperty",
        "GeoPnt4dProperty",
#endif

        "GeoColor3ubProperty",
        "GeoColor4ubProperty",
        "GeoColor3NubProperty",
        "GeoColor4NubProperty",

        "GeoColor3fProperty",
        "GeoColor4fProperty"
    };

    OSG::GeoVectorPropertyPtr att;

    unsigned num_vec_props = sizeof(allowed_vec_prop_types) / sizeof(char*);

    for(unsigned i = 0; i < num_vec_props;++i)
    {
        att = OSG::cast_dynamic<OSG::GeoVectorPropertyPtr>(
                    OSG::FieldContainerFactory::the()->createContainer(
                        allowed_vec_prop_types[i]));
        unsigned prop_index = i % 16;
        g->setProperty(att,prop_index);
        CHECK(true);
    }

}

} // SUITE

