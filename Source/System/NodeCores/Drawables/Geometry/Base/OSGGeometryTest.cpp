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

#include "OSGGeometry.h"
#include "OSGGeoVectorProperty.h"
#include "OSGGeoProperties.h"
#include "OSGFieldContainerFactory.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGSimpleGeometry.h"
#include "OSGTransform.h"

SUITE(GeometryTests)
{

TEST(CreateGeometry)
{
    OSG::GeometryUnrecPtr g = OSG::Geometry::create();
    CHECK(g != NULL);
}

TEST(TestInitialValues)
{
    OSG::GeometryUnrecPtr g = OSG::Geometry::create();
    CHECK(g != NULL);

    for(unsigned i=0;i<OSG::Geometry::MaxAttribs;i++)
    {
        CHECK(g->getProperty(i) == NULL);
        CHECK(g->getIndex(i) == NULL);
    }

    CHECK(g->getMaterial() == NULL);
}

// Test using the generic vector interfaces on geometry
TEST(TestGenericInterfaces)
{
    OSG::GeometryUnrecPtr g = OSG::Geometry::create();
    CHECK(g != NULL);

    OSG::GeoPnt3fPropertyUnrecPtr  pnts  = OSG::GeoPnt3fProperty ::create();
    pnts->addValue(OSG::Pnt3f(0,0,0));

    g->setPositions(pnts);

    OSG::GeoVectorPropertyUnrecPtr pnts_g = g->getPositions();
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
    OSG::GeometryUnrecPtr g = OSG::Geometry::create();
    CHECK(g != NULL);

    // Copied-and-macroed from OSGTypedGeoVectorPropertyFields
    const char* allowed_vec_prop_types[] =
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

        "GeoVec1fProperty",
        "GeoVec2fProperty",
        "GeoVec3fProperty",
        "GeoVec4fProperty",

        "GeoPnt1fProperty",
        "GeoPnt2fProperty",
        "GeoPnt3fProperty",
        "GeoPnt4fProperty",

        "GeoVec1dProperty",
        "GeoVec2dProperty",
        "GeoVec3dProperty",
        "GeoVec4dProperty",

        "GeoPnt1dProperty",
        "GeoPnt2dProperty",
        "GeoPnt3dProperty",
        "GeoPnt4dProperty",

        "GeoColor3ubProperty",
        "GeoColor4ubProperty",
        "GeoColor3NubProperty",
        "GeoColor4NubProperty",

        "GeoColor3fProperty",
        "GeoColor4fProperty"
    };

    OSG::GeoVectorPropertyUnrecPtr att;

    unsigned num_vec_props = sizeof(allowed_vec_prop_types) / sizeof(char*);

    for(unsigned i = 0; i < num_vec_props;++i)
    {
        att = OSG::dynamic_pointer_cast<OSG::GeoVectorProperty>(
                    OSG::FieldContainerFactory::the()->createContainer(
                        allowed_vec_prop_types[i]));
        unsigned prop_index = i % 16;
        g->setProperty(att,prop_index);
        CHECK(true);
    }

}

TEST(GeometryAsInnerNodesBoundingVolume)
{
    // pNGeo0:[Geometry]
    //   |
    //   +-------------------------------------+
    //   |                                     |
    // pNTrans1:pTrans1[Transform]           pNTran2:pTrans2[Transform]
    //   |                                     |
    // pNGeo1:[Geometry]                     pNGeo2:[Geometry]
    
    OSG::NodeUnrecPtr pNGeo0 = OSG::makeBox(2.0, 2.0, 4.0, 1, 1, 1);
    OSG::NodeUnrecPtr pNGeo1 = OSG::makeBox(2.0, 2.0, 2.0, 1, 1, 1);
    OSG::NodeUnrecPtr pNGeo2 = OSG::makeBox(2.0, 2.0, 2.0, 1, 1, 1);
    
    OSG::NodeUnrecPtr      pNTrans1 = OSG::Node::create();
    OSG::TransformUnrecPtr pTrans1  = OSG::Transform::create();
    OSG::NodeUnrecPtr      pNTrans2 = OSG::Node::create();
    OSG::TransformUnrecPtr pTrans2  = OSG::Transform::create();
    
    pNTrans1->setCore (pTrans1);
    pNTrans1->addChild(pNGeo1 );
    pNTrans2->setCore (pTrans2);
    pNTrans2->addChild(pNGeo2 );
    
    pNGeo0->addChild(pNTrans1);
    pNGeo0->addChild(pNTrans2);
    
    OSG::Matrix mat1;
    OSG::Matrix mat2;
    
    mat1.setTranslate(OSG::Vec3f(  3.0, 0.0, 0.0));
    mat2.setTranslate(OSG::Vec3f(- 3.0, 0.0, 0.0));
    
    pTrans1->editSFMatrix()->setValue(mat1);
    pTrans2->editSFMatrix()->setValue(mat2);
    
    OSG::commitChanges();
    
    OSG::BoxVolume bbox;
    OSG::Pnt3f     min;
    OSG::Pnt3f     max;
    
    pNGeo1->getWorldVolume(bbox);
    bbox.getBounds(min, max);
       
    CHECK_CLOSE( 2.0, min[0], 1e-6);
    CHECK_CLOSE(-1.0, min[1], 1e-6);
    CHECK_CLOSE(-1.0, min[2], 1e-6);
    
    CHECK_CLOSE( 4.0, max[0], 1e-6);
    CHECK_CLOSE( 1.0, max[1], 1e-6);
    CHECK_CLOSE( 1.0, max[2], 1e-6);
    
    pNGeo2->getWorldVolume(bbox);
    bbox.getBounds(min, max);
        
    CHECK_CLOSE(-4.0, min[0], 1e-6);
    CHECK_CLOSE(-1.0, min[1], 1e-6);
    CHECK_CLOSE(-1.0, min[2], 1e-6);
    
    CHECK_CLOSE(-2.0, max[0], 1e-6);
    CHECK_CLOSE( 1.0, max[1], 1e-6);
    CHECK_CLOSE( 1.0, max[2], 1e-6);
    
    pNGeo0->getWorldVolume(bbox);
    bbox.getBounds(min, max);
    
    CHECK_CLOSE(-4.0, min[0], 1e-6);
    CHECK_CLOSE(-1.0, min[1], 1e-6);
    CHECK_CLOSE(-2.0, min[2], 1e-6);
    
    CHECK_CLOSE( 4.0, max[0], 1e-6);
    CHECK_CLOSE( 1.0, max[1], 1e-6);
    CHECK_CLOSE( 2.0, max[2], 1e-6);
}

} // SUITE

