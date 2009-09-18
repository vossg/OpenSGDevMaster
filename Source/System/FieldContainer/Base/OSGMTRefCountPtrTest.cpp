/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2009 by OpenSG Forum                      *
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

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGGroup.h>

OSG_BEGIN_NAMESPACE
OSG_GEN_CONTAINERPTR(FieldContainer);
OSG_END_NAMESPACE

SUITE(MTRefCountPtrTests)
{

TEST(Basics)
{
    OSG::NodeMTRefPtr  n0 = OSG::Node ::create();
    OSG::GroupMTRefPtr g0 = OSG::Group::create();

    n0->setCore(g0);
    
    OSG::commitChanges();

    g0 = NULL;

    CHECK(n0            != NULL);
    CHECK(n0->getCore() != NULL);

    n0 = NULL;

    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), n0);
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), g0);
}


TEST(VectorFind)
{
    OSG::NodeMTRefPtr  n0 = OSG::Node::create();
    OSG::NodeMTRefPtr  n1 = OSG::Node::create();
    OSG::NodeMTRefPtr  n2 = OSG::Node::create();

    OSG::GroupMTRefPtr g0 = OSG::Group::create();
    OSG::GroupMTRefPtr g1 = OSG::Group::create();
    OSG::GroupMTRefPtr g2 = OSG::Group::create();

    OSG::FieldContainer *fc = g1;

    typedef std::vector<OSG::FieldContainerMTRefPtr> FCMTStore;
    FCMTStore fcStore;

    fcStore.push_back(n0);
    fcStore.push_back(n1);
    fcStore.push_back(n2);

    fcStore.push_back(g0);
    fcStore.push_back(g1);
    fcStore.push_back(g2);

    FCMTStore::iterator fcIt;

    fcIt = std::find(fcStore.begin(), fcStore.end(), fc);

    CHECK(fcIt != fcStore.end());
    CHECK(fc == *fcIt);
    CHECK(g1 == *fcIt);
    CHECK(std::distance(fcStore.begin(), fcIt) == 4);
}


} // SUITE(MTRefCountPtrTests)
