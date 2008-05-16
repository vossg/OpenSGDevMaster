/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2007 by OpenSG Forum                      *
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

#include <OpenSG/OSGFieldContainer.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGDirectionalLight.h>

#include <iostream>
#include <string>
#include <vector>

SUITE(LightReferenceCountTests)
{

TEST(ChildLinkingCleanup)
{
    // Test lights, as their beacons can introduce loops in the pointer
    // structures (not really a problem, because the beacons ptrs are weak)
    //
    // np0[gp0] <------------+
    //  +----------+         |
    // np1[gp1]   np2[gp2]   | beacon
    //  |                    |
    // np3[lp0]--------------+
    
    // create objects

    OSG::NodeRecPtr  nrp0(OSG::Node ::create());
    OSG::NodeRecPtr  nrp1(OSG::Node ::create());
    OSG::NodeRecPtr  nrp2(OSG::Node ::create());
    OSG::NodeRecPtr  nrp3(OSG::Node ::create());
    OSG::GroupRecPtr grp0(OSG::Group::create());
    OSG::GroupRecPtr grp1(OSG::Group::create());
    OSG::GroupRecPtr grp2(OSG::Group::create());
    OSG::LightRecPtr lrp0(OSG::DirectionalLight::create());
    
    OSG::Node  *np0 = nrp0;
    OSG::Node  *np1 = nrp1;
    OSG::Node  *np2 = nrp2;
    OSG::Node  *np3 = nrp3;
    OSG::Group *gp0 = grp0;
    OSG::Group *gp1 = grp1;
    OSG::Group *gp2 = grp2;
    OSG::Light *lp0 = lrp0;
    
    OSG::UInt32 ni0 = nrp0->getId();
    OSG::UInt32 ni1 = nrp1->getId();
    OSG::UInt32 ni2 = nrp2->getId();
    OSG::UInt32 ni3 = nrp3->getId();
    OSG::UInt32 gi0 = grp0->getId();
    OSG::UInt32 gi1 = grp1->getId();
    OSG::UInt32 gi2 = grp2->getId();
    OSG::UInt32 li0 = lrp0->getId();
    
    nrp0->addChild(nrp1);
    nrp0->addChild(nrp2);
    nrp1->addChild(nrp3);
    
    nrp0->setCore(grp0);
    nrp1->setCore(grp1);
    nrp2->setCore(grp2);
    nrp3->setCore(lrp0);
    
    lrp0->setBeacon(nrp0);
    
    CHECK_EQUAL(1, nrp0->getRefCount()    );
    CHECK_EQUAL(1, nrp0->getWeakRefCount());
    
    CHECK_EQUAL(2, nrp1->getRefCount()    );
    CHECK_EQUAL(0, nrp1->getWeakRefCount());
    
    CHECK_EQUAL(2, nrp2->getRefCount()    );
    CHECK_EQUAL(0, nrp2->getWeakRefCount());
    
    CHECK_EQUAL(2, grp0->getRefCount()    );
    CHECK_EQUAL(0, grp0->getWeakRefCount());
    
    CHECK_EQUAL(2, grp1->getRefCount()    );
    CHECK_EQUAL(0, grp1->getWeakRefCount());
    
    CHECK_EQUAL(2, grp2->getRefCount()    );
    CHECK_EQUAL(0, grp2->getWeakRefCount());
    
    CHECK_EQUAL(2, lrp0->getRefCount()    );
    CHECK_EQUAL(0, lrp0->getWeakRefCount());
    
    // remove all ref pointers (i.e. all external refs)
    
    nrp1 = NULL;
    nrp2 = NULL;
    nrp3 = NULL;
    grp0 = NULL;
    grp1 = NULL;
    grp2 = NULL;
    lrp0 = NULL;
    
    OSG::commitChanges();
    
    // only nrp0 is still here, check everything is still alive and has
    // the expected ref counts
    
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(np2, OSG::FieldContainerFactory::the()->getContainer(ni2));
    CHECK_EQUAL(np3, OSG::FieldContainerFactory::the()->getContainer(ni3));
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(gp1, OSG::FieldContainerFactory::the()->getContainer(gi1));
    CHECK_EQUAL(gp2, OSG::FieldContainerFactory::the()->getContainer(gi2));
    CHECK_EQUAL(lp0, OSG::FieldContainerFactory::the()->getContainer(li0));
    
    CHECK_EQUAL(1, np0->getRefCount()    );
    CHECK_EQUAL(2, np0->getWeakRefCount()); // light chunk keeps additional weak ref
    
    CHECK_EQUAL(1, np1->getRefCount()    );
    CHECK_EQUAL(0, np1->getWeakRefCount());
    
    CHECK_EQUAL(1, np2->getRefCount()    );
    CHECK_EQUAL(0, np2->getWeakRefCount());
    
    CHECK_EQUAL(1, np3->getRefCount()    );
    CHECK_EQUAL(0, np3->getWeakRefCount());
    
    // remove nrp0 as well, everything should clean up
    
    nrp0 = NULL;
    
    OSG::commitChanges();
    
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni2));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni3));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi1));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi2));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(li0));
}

} // SUITE(LightReferenceCountTests)
