/*---------------------------------------------------------------------------*\
 *                                Opensg                                     *
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

#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGGroup.h"
#include "OSGDirectionalLight.h"

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

    OSG::NodeRecPtr  nrcp0(OSG::Node ::create());
    OSG::NodeRecPtr  nrcp1(OSG::Node ::create());
    OSG::NodeRecPtr  nrcp2(OSG::Node ::create());
    OSG::NodeRecPtr  nrcp3(OSG::Node ::create());
    OSG::GroupRecPtr grcp0(OSG::Group::create());
    OSG::GroupRecPtr grcp1(OSG::Group::create());
    OSG::GroupRecPtr grcp2(OSG::Group::create());
    OSG::LightRecPtr lrcp0(OSG::DirectionalLight::create());
    
    OSG::Node  *np0 = nrcp0;
    OSG::Node  *np1 = nrcp1;
    OSG::Node  *np2 = nrcp2;
    OSG::Node  *np3 = nrcp3;
    OSG::Group *gp0 = grcp0;
    OSG::Group *gp1 = grcp1;
    OSG::Group *gp2 = grcp2;
    OSG::Light *lp0 = lrcp0;
    
    OSG::UInt32 ni0 = nrcp0->getId();
    OSG::UInt32 ni1 = nrcp1->getId();
    OSG::UInt32 ni2 = nrcp2->getId();
    OSG::UInt32 ni3 = nrcp3->getId();
    OSG::UInt32 gi0 = grcp0->getId();
    OSG::UInt32 gi1 = grcp1->getId();
    OSG::UInt32 gi2 = grcp2->getId();
    OSG::UInt32 li0 = lrcp0->getId();
    
    nrcp0->addChild(nrcp1);
    nrcp0->addChild(nrcp2);
    nrcp1->addChild(nrcp3);
    
    nrcp0->setCore(grcp0);
    nrcp1->setCore(grcp1);
    nrcp2->setCore(grcp2);
    nrcp3->setCore(lrcp0);
    
    lrcp0->setBeacon(nrcp0);
    
    CHECK_EQUAL(1, nrcp0->getRefCount()    );
    CHECK_EQUAL(1, nrcp0->getWeakRefCount());
    
    CHECK_EQUAL(2, nrcp1->getRefCount()    );
    CHECK_EQUAL(0, nrcp1->getWeakRefCount());
    
    CHECK_EQUAL(2, nrcp2->getRefCount()    );
    CHECK_EQUAL(0, nrcp2->getWeakRefCount());
    
    CHECK_EQUAL(2, grcp0->getRefCount()    );
    CHECK_EQUAL(0, grcp0->getWeakRefCount());
    
    CHECK_EQUAL(2, grcp1->getRefCount()    );
    CHECK_EQUAL(0, grcp1->getWeakRefCount());
    
    CHECK_EQUAL(2, grcp2->getRefCount()    );
    CHECK_EQUAL(0, grcp2->getWeakRefCount());
    
    CHECK_EQUAL(2, lrcp0->getRefCount()    );
    CHECK_EQUAL(0, lrcp0->getWeakRefCount());
    
    // remove all ref pointers (i.e. all application refs) except nrcp0
    
    nrcp1 = NULL;
    nrcp2 = NULL;
    nrcp3 = NULL;
    grcp0 = NULL;
    grcp1 = NULL;
    grcp2 = NULL;
    lrcp0 = NULL;
    
    OSG::commitChanges();
    
    // only nrcp0 is still here, check everything is still alive and has
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
    
    // remove nrcp0 as well, everything should clean up
    
    nrcp0 = NULL;
    
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
