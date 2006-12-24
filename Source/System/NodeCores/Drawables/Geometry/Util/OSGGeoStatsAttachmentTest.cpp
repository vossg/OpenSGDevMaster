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

#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGeoBuilder.h>
#include <OpenSG/OSGGeoStatsAttachment.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGGroup.h>

OSG_USING_NAMESPACE

SUITE(GeoStatsAttachmentTests)
{

struct GSAFixture
{
    GSAFixture(void)
    {
        GeoBuilder b;

        root = makeNodeFor(Group::create());
        geos0Node = makeNodeFor(Group::create());

        root->addChild(geos0Node);

        // Test geometry 0: a single triangle
        b.begin(GL_TRIANGLES);
        b.vertex(Vec3f(0,0,0));
        b.vertex(Vec3f(1,0,0));
        b.vertex(Vec3f(0,1,0));
        b.end();

        geos[0]                         = b.getGeometry();
        geoVertices[0]                  = 3;
        geoPoints[0]                    = 0;
        geoLines[0]                     = 0;
        geoTriangles[0]                 = 1;
        geoProcessedAttributeBytes[0]   = 3*sizeof(Vec3f);
        geoStoredAttributeBytes[0]      = 3*sizeof(Vec3f);

        nodes[0] = makeNodeFor(geos[0]);
        geos0Node->addChild(nodes[0]); // Add a second level

        // Test geometry 1: a triangle and a quad
        b.reset();

        b.vertex(Vec3f(0,0,0));
        b.vertex(Vec3f(1,0,0));
        b.vertex(Vec3f(0,1,0));

        b.vertex(Vec3f(2,0,0));
        b.vertex(Vec3f(3,0,0));
        b.vertex(Vec3f(3,2,0));
        b.vertex(Vec3f(2,2,0));

        b.tri(0);
        b.quad(3);

        geos[1]                         = b.getGeometry();
        geoVertices[1]                  = 7;
        geoPoints[1]                    = 0;
        geoLines[1]                     = 0;
        geoTriangles[1]                 = 3;
        geoProcessedAttributeBytes[1]   = 7*sizeof(Vec3f);
        geoStoredAttributeBytes[1]      = 7*sizeof(Vec3f);

        nodes[1] = makeNodeFor(geos[1]);
        root->addChild(nodes[1]);

        // Test geometry 2: Sharing some vertices
        b.reset();

        b.vertex(Vec3f(0,0,0));
        b.vertex(Vec3f(1,0,0));
        b.vertex(Vec3f(0,1,0));

        b.vertex(Vec3f(2,1,0));
        b.vertex(Vec3f(3,0,0));

        b.tri(0);
        b.quad(1);

        geos[2]                         = b.getGeometry();
        geoVertices[2]                  = 7;
        geoPoints[2]                    = 0;
        geoLines[2]                     = 0;
        geoTriangles[2]                 = 3;
        geoProcessedAttributeBytes[2]   = 7*sizeof(Vec3f);
        geoStoredAttributeBytes[2]      = 5*sizeof(Vec3f);

        nodes[2] = makeNodeFor(geos[2]);
        root->addChild(nodes[2]);

        commitChanges();

        sumVertices = sumPoints = sumLines = sumTriangles =
            sumProcessedAttributeBytes = sumStoredAttributeBytes = 0;

        for(UInt32 i = 0; i < nGeos; ++i)
        {
            sumVertices += geoVertices[i];
            sumPoints += geoPoints[i];
            sumLines += geoLines[i];
            sumTriangles += geoTriangles[i];
            sumProcessedAttributeBytes += geoProcessedAttributeBytes[i];
            sumStoredAttributeBytes += geoStoredAttributeBytes[i];

        }
    }

    ~GSAFixture()
    {
    }

    // Number of test geometries
    static const int nGeos = 3;

    // Test Geometries, see above
    RefPtr<GeometryPtr> geos[nGeos];

    // Stats Data for test geometries
    UInt32 geoVertices[nGeos];
    UInt32 geoPoints[nGeos];
    UInt32 geoLines[nGeos];
    UInt32 geoTriangles[nGeos];
    UInt32 geoProcessedAttributeBytes[nGeos];
    UInt32 geoStoredAttributeBytes[nGeos];

    // Summed stats data
    UInt32 sumVertices;
    UInt32 sumPoints;
    UInt32 sumLines;
    UInt32 sumTriangles;
    UInt32 sumProcessedAttributeBytes;
    UInt32 sumStoredAttributeBytes;

    // Nodes for tree test
    RefPtr<NodePtr> nodes[nGeos];
    RefPtr<NodePtr> root;
    RefPtr<NodePtr> geos0Node;
};

TEST_FIXTURE(GSAFixture, BasicCreationAndCalculation)
{
    for(int i = 0; i < nGeos; ++i)
    {
        GeometryPtr g = geos[i];
        RefPtr<GeoStatsAttachmentPtr> st;
        st = GeoStatsAttachment::calcStatic(g);

        CHECK_EQUAL(geoVertices[i], st->getVertices());
        CHECK_EQUAL(geoPoints[i], st->getPoints());
        CHECK_EQUAL(geoLines[i], st->getLines());
        CHECK_EQUAL(geoTriangles[i], st->getTriangles());
        CHECK_EQUAL(geoProcessedAttributeBytes[i], st->getProcessedAttributeBytes());
        CHECK_EQUAL(geoStoredAttributeBytes[i], st->getStoredAttributeBytes());
    }
}

TEST_FIXTURE(GSAFixture, MathOps)
{
    RefPtr<GeoStatsAttachmentPtr> sum;

    sum = GeoStatsAttachment::create();

    UInt32 v = 0,p = 0,l = 0,t = 0,pb = 0,sb = 0;

    for(int i = 0; i < nGeos; ++i)
    {
        RefPtr<GeoStatsAttachmentPtr> st;
        GeometryPtr g = geos[i];
        st = GeoStatsAttachment::calcStatic(g);
        //sum += st;
        sum->operator+=(st);

        v  += st->getVertices();
        p  += st->getPoints();
        l  += st->getLines();
        t  += st->getTriangles();
        pb += st->getProcessedAttributeBytes();
        sb += st->getStoredAttributeBytes();
    }

    CHECK_EQUAL(v, sum->getVertices());
    CHECK_EQUAL(p, sum->getPoints());
    CHECK_EQUAL(l, sum->getLines());
    CHECK_EQUAL(t, sum->getTriangles());
    CHECK_EQUAL(pb, sum->getProcessedAttributeBytes());
    CHECK_EQUAL(sb, sum->getStoredAttributeBytes());

    //sum -= sum;
    sum->operator-=(sum);
    CHECK_EQUAL(sum->getVertices(), 0);
    CHECK_EQUAL(sum->getPoints(), 0);
    CHECK_EQUAL(sum->getLines(), 0);
    CHECK_EQUAL(sum->getTriangles(), 0);
    CHECK_EQUAL(sum->getProcessedAttributeBytes(), 0);
    CHECK_EQUAL(sum->getStoredAttributeBytes(), 0);

}

TEST_FIXTURE(GSAFixture, AddToGeometry)
{
    GeoStatsAttachment::addTo(geos[0]);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(geos[0]);

    CHECK(st != NullFC);

    st->validate();

    CHECK_EQUAL(geoVertices[0], st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0], st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());
}

TEST_FIXTURE(GSAFixture, CreationAndAccess)
{
    GeoStatsAttachmentPtr st;

    st = GeoStatsAttachment::get(geos[0]);
    CHECK(st == NullFC);

    GeoStatsAttachment::addTo(geos[0]);

    st = GeoStatsAttachment::get(geos[0]);

    CHECK(st != NullFC);
}

TEST_FIXTURE(GSAFixture, AddToOneFCOnly)
{
    GeoStatsAttachment::addTo(geos[0]);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(geos[0]);

    CHECK(st != NullFC);

    st->attachTo(geos[1]);

    st = GeoStatsAttachment::get(geos[0]);

    CHECK(st == NullFC);   // Removed from old one?

    st = GeoStatsAttachment::get(geos[1]);

    CHECK(st != NullFC);    // Attached to new one?

    CHECK_EQUAL(st->getValid(), false); // Should be invalid now

    st->validate();

    CHECK_EQUAL(st->getValid(), true); // Should be valid now

    CHECK_EQUAL(geoVertices[1], st->getVertices());
    CHECK_EQUAL(geoPoints[1], st->getPoints());
    CHECK_EQUAL(geoLines[1], st->getLines());
    CHECK_EQUAL(geoTriangles[1], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[1], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[1], st->getStoredAttributeBytes());
}

TEST_FIXTURE(GSAFixture, AddToGeometryNode)
{
    GeoStatsAttachment::addTo(nodes[0]);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(nodes[0]);

    CHECK(st != NullFC);

    st->validate();

    CHECK_EQUAL(geoVertices[0], st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0], st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());
}

// Add to multiple tree levels
TEST_FIXTURE(GSAFixture, AddToGroupNodes)
{
    GeoStatsAttachment::addTo(geos0Node);
    GeoStatsAttachment::addTo(nodes[0]);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(geos0Node);

    CHECK(st != NullFC);

    st->validate();

    CHECK_EQUAL(geoVertices[0], st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0], st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());
}

// Add to one tree level, should update all lower levels automatically
TEST_FIXTURE(GSAFixture, AddToGroupNode)
{
    GeoStatsAttachment::addTo(geos0Node);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(geos0Node);

    CHECK(st != NullFC);

    st->validate();

    CHECK_EQUAL(geoVertices[0], st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0], st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());
}

// Automatic Invalidation
TEST_FIXTURE(GSAFixture, AutoInvalidateGeometryOnChange)
{
    GeoStatsAttachment::addTo(geos[0]);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(geos[0]);

    CHECK(st != NullFC);

    st->validate();

    commitChanges();

    CHECK_EQUAL(geoVertices[0], st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0], st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());

    geos[0]->getTypes()->push_back(GL_LINE_STRIP);
    geos[0]->getLengths()->push_back(3);
    geos[0]->getIndex(0)->push_back(0);
    geos[0]->getIndex(0)->push_back(1);
    geos[0]->getIndex(0)->push_back(2);

    commitChanges();

    CHECK_EQUAL(st->getValid(), false);

    st->validate();

    CHECK_EQUAL(st->getValid(), true);

    CHECK_EQUAL(geoVertices[0] + 3, st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0] + 2, st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0] + sizeof(Vec3f) * 3,
                    st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());
}

// Automatic Invalidation
TEST_FIXTURE(GSAFixture, AutoInvalidateNodeOnChange)
{
    GeoStatsAttachment::addTo(nodes[0]);

    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(nodes[0]);

    CHECK(st != NullFC);

    st->validate();

    commitChanges();

    CHECK_EQUAL(geoVertices[0], st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0], st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0], st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());

    geos[0]->getTypes()->push_back(GL_LINE_STRIP);
    geos[0]->getLengths()->push_back(3);
    geos[0]->getIndex(0)->push_back(0);
    geos[0]->getIndex(0)->push_back(1);
    geos[0]->getIndex(0)->push_back(2);

    commitChanges();

    CHECK_EQUAL(st->getValid(), false);

    st->validate();

    CHECK_EQUAL(st->getValid(), true);

    CHECK_EQUAL(geoVertices[0] + 3, st->getVertices());
    CHECK_EQUAL(geoPoints[0], st->getPoints());
    CHECK_EQUAL(geoLines[0] + 2, st->getLines());
    CHECK_EQUAL(geoTriangles[0], st->getTriangles());
    CHECK_EQUAL(geoProcessedAttributeBytes[0] + sizeof(Vec3f) * 3,
                    st->getProcessedAttributeBytes());
    CHECK_EQUAL(geoStoredAttributeBytes[0], st->getStoredAttributeBytes());
}

// Hierarchical Invalidation
TEST_FIXTURE(GSAFixture, AutoInvalidateHierarchy)
{
    RefPtr<GeoStatsAttachmentPtr> st;
    st = GeoStatsAttachment::get(root);

    CHECK(st == NullFC);

    GeoStatsAttachment::addTo(root);
    st = GeoStatsAttachment::get(root);

    CHECK(st != NullFC);

    st->validate();

    CHECK_EQUAL(sumVertices, st->getVertices());
    CHECK_EQUAL(sumPoints, st->getPoints());
    CHECK_EQUAL(sumLines, st->getLines());
    CHECK_EQUAL(sumTriangles, st->getTriangles());
    CHECK_EQUAL(sumProcessedAttributeBytes, st->getProcessedAttributeBytes());
    CHECK_EQUAL(sumStoredAttributeBytes, st->getStoredAttributeBytes());

    geos[0]->getTypes()->push_back(GL_LINE_STRIP);
    geos[0]->getLengths()->push_back(3);
    geos[0]->getIndex(0)->push_back(0);
    geos[0]->getIndex(0)->push_back(1);
    geos[0]->getIndex(0)->push_back(2);

    commitChanges();

    CHECK_EQUAL(false, st->getValid());

    st->validate();

    CHECK_EQUAL(true, st->getValid());

    CHECK_EQUAL(sumVertices + 3, st->getVertices());
    CHECK_EQUAL(sumPoints, st->getPoints());
    CHECK_EQUAL(sumLines + 2, st->getLines());
    CHECK_EQUAL(sumTriangles, st->getTriangles());
    CHECK_EQUAL(sumProcessedAttributeBytes + sizeof(Vec3f) * 3,
                    st->getProcessedAttributeBytes());
    CHECK_EQUAL(sumStoredAttributeBytes, st->getStoredAttributeBytes());
}

} // SUITE
