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

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGGroup.h>

SUITE(ReferenceCountTests)
{

TEST(BasicStructure)
{
    // Basic case, two nodes, each with it's own core.
    //
    //   np0[gp0]
    //    |
    //   np1[gp1]

    // create objects

    OSG::NodeRecPtr  nrcp0(OSG::Node ::create());
    OSG::NodeRecPtr  nrcp1(OSG::Node ::create());
    OSG::GroupRecPtr grcp0(OSG::Group::create());
    OSG::GroupRecPtr grcp1(OSG::Group::create());

    OSG::Node  *np0 = nrcp0.get();
    OSG::Node  *np1 = nrcp1.get();
    OSG::Group *gp0 = grcp0.get();
    OSG::Group *gp1 = grcp1.get();

    OSG::UInt32 ni0 = nrcp0->getId();
    OSG::UInt32 ni1 = nrcp1->getId();
    OSG::UInt32 gi0 = grcp0->getId();
    OSG::UInt32 gi1 = grcp1->getId();
    
    CHECK_EQUAL(1, nrcp0->getRefCount()    );
    CHECK_EQUAL(0, nrcp0->getWeakRefCount());
    
    CHECK_EQUAL(1, nrcp1->getRefCount()    );
    CHECK_EQUAL(0, nrcp1->getWeakRefCount());
    
    CHECK_EQUAL(1, grcp0->getRefCount()    );
    CHECK_EQUAL(0, grcp0->getWeakRefCount());
    
    CHECK_EQUAL(1, grcp1->getRefCount()    );
    CHECK_EQUAL(0, grcp1->getWeakRefCount());
    
    OSG::commitChanges();
    
    // link nodes
    
    nrcp0->addChild(nrcp1);
    nrcp0->setCore(grcp0);
    nrcp1->setCore(grcp1);
    
    CHECK_EQUAL(1, nrcp0->getRefCount());
    CHECK_EQUAL(2, nrcp1->getRefCount());
    CHECK_EQUAL(2, grcp0->getRefCount());
    CHECK_EQUAL(2, grcp1->getRefCount());

    CHECK_EQUAL(nrcp0, nrcp1->getParent()           );
    CHECK_EQUAL(nrcp1, nrcp0->getMFChildren()->at(0));
    
    CHECK_EQUAL(grcp0, nrcp0->getCore()            );
    CHECK_EQUAL(grcp1, nrcp1->getCore()            );
    CHECK_EQUAL(nrcp0, grcp0->getMFParents()->at(0));
    CHECK_EQUAL(nrcp1, grcp1->getMFParents()->at(0));
    
    // remove all ref pointers (i.e. all external refs)
    
    nrcp0 = NULL;
    nrcp1 = NULL;
    grcp0 = NULL;
    grcp1 = NULL;
    
    // all containers must be gone
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi1));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni1));
    
} // BasicStructure

TEST(RecPtrReuse)
{
    // Still basic case, but use fewer ref ptrs
    //
    //  np0[gp0]
    //   +-----------+
    //  np1[gp0]    np2[gp0]
    
    OSG::NodeRecPtr     nrcp0 = OSG::Node ::create();
    OSG::NodeRecPtr     nrcp1 = OSG::Node ::create();
    OSG::NodeCoreRecPtr grcp  = OSG::Group::create();
    
    OSG::Node     *np0 = nrcp0.get();
    OSG::Node     *np1 = nrcp1.get();
    OSG::NodeCore *gp0 = grcp .get();
    
    OSG::UInt32 ni0 = nrcp0->getId();
    OSG::UInt32 ni1 = nrcp1->getId();
    OSG::UInt32 gi0 = grcp ->getId();
    
    nrcp0->setCore (grcp );
    nrcp0->addChild(nrcp1);
    
    nrcp1->setCore(grcp);
    
    nrcp1 = OSG::Node::create();
    
    OSG::Node   *np2 = nrcp1.get();
    OSG::UInt32  ni2 = nrcp1->getId();
    
    nrcp0->addChild(nrcp1);
    nrcp1->setCore (grcp );
    
    CHECK_EQUAL(1, np0->getRefCount());
    CHECK_EQUAL(1, np1->getRefCount());
    CHECK_EQUAL(2, np2->getRefCount());
    CHECK_EQUAL(4, gp0->getRefCount());
    
    // remove all ref pointers (i.e. all external refs)
    
    nrcp1 = NULL;
    grcp  = NULL;
    
    // all containers must still exist
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(np2, OSG::FieldContainerFactory::the()->getContainer(ni2));
    
    nrcp0 = NULL;
    
    // all containers must be gone
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni2));
    
} // RecPtrReuse

TEST(SharedCore)
{
    // A bit more complex, two nodes with a shared core
    //
    //   np0[gp0]
    //    |
    //   np1[gp0]
    
    // create objects
    
    OSG::NodeRecPtr  nrcp0(OSG::Node ::create());
    OSG::NodeRecPtr  nrcp1(OSG::Node ::create());
    OSG::GroupRecPtr grcp0(OSG::Group::create());

    OSG::Node  *np0 = nrcp0.get();
    OSG::Node  *np1 = nrcp1.get();
    OSG::Group *gp0 = grcp0.get();

    OSG::UInt32 ni0 = nrcp0->getId();
    OSG::UInt32 ni1 = nrcp1->getId();
    OSG::UInt32 gi0 = grcp0->getId();
        
    CHECK_EQUAL(1, nrcp0->getRefCount());
    CHECK_EQUAL(1, nrcp1->getRefCount());
    
    CHECK_EQUAL(1, grcp0->getRefCount()    );
    CHECK_EQUAL(0, grcp0->getWeakRefCount());
    
    OSG::commitChanges();
    
    // link nodes
    
    nrcp0->addChild(nrcp1);
    
    CHECK_EQUAL(1, np0->getRefCount());
    CHECK_EQUAL(2, np1->getRefCount());
    
    CHECK_EQUAL(np0, np1->getParent()           );
    CHECK_EQUAL(np1, np0->getMFChildren()->at(0));
    
    OSG::commitChanges();
    
    // add core to np0
    
    nrcp0->setCore(gp0);
    
    CHECK_EQUAL(1, np0->getRefCount());
    CHECK_EQUAL(2, gp0->getRefCount());
    
    CHECK_EQUAL(gp0, np0->getCore()            );
    CHECK_EQUAL(np0, gp0->getMFParents()->at(0));
    
    OSG::commitChanges();
    
    // add core to np1
    
    nrcp1->setCore(gp0);
    
    CHECK_EQUAL(2, np1->getRefCount());
    CHECK_EQUAL(3, gp0->getRefCount());
        
    CHECK_EQUAL(gp0, np1->getCore()            );
    CHECK_EQUAL(np1, gp0->getMFParents()->at(1));
    
    OSG::commitChanges();
    
    // remove all ref pointers (i.e. all external refs)
    
    grcp0 = NULL;
    
    // all containers must still exist
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(2, gp0->getRefCount()    );
//     CHECK_EQUAL(0, gp0->getWeakRefCount());
    
    nrcp1 = NULL;
    
    // all containers must still exist
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(2, gp0->getRefCount());
    CHECK_EQUAL(1, np1->getRefCount());
    
    nrcp0 = NULL;
    
    // all containers must be gone
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni1));
    
} // SharedCore

TEST(MultipleChildrenSharedCores)
{
    // Test a bit more complex hierarchy, with two shared cores
    //
    // np0[gp0]
    //  +-------------+
    // np1[gp1]      np2[gp1]
    //  |
    // np3[gp0]
    
    // create objects

    OSG::NodeRecPtr  nrcp0 = OSG::Node ::create();
    OSG::NodeRecPtr  nrcp1 = OSG::Node ::create();
    OSG::NodeRecPtr  nrcp2 = OSG::Node ::create();
    OSG::NodeRecPtr  nrcp3 = OSG::Node ::create();
    OSG::GroupRecPtr grcp0 = OSG::Group::create();
    OSG::GroupRecPtr grcp1 = OSG::Group::create();

    OSG::Node  *np0 = nrcp0.get();
    OSG::Node  *np1 = nrcp1.get();
    OSG::Node  *np2 = nrcp2.get();
    OSG::Node  *np3 = nrcp3.get();
    OSG::Group *gp0 = grcp0.get();
    OSG::Group *gp1 = grcp1.get();

    OSG::UInt32 ni0 = nrcp0->getId();
    OSG::UInt32 ni1 = nrcp1->getId();
    OSG::UInt32 ni2 = nrcp2->getId();
    OSG::UInt32 ni3 = nrcp3->getId();
    OSG::UInt32 gi0 = grcp0->getId();
    OSG::UInt32 gi1 = grcp1->getId();
        
    // link nodes    
    
    nrcp0->addChild(nrcp1);
    nrcp0->addChild(nrcp2);
    nrcp1->addChild(nrcp3);
    
    nrcp0->setCore(grcp0);
    nrcp1->setCore(grcp1);
    nrcp2->setCore(grcp1);
    nrcp3->setCore(grcp0);
    
    CHECK_EQUAL(1, nrcp0->getRefCount());
    CHECK_EQUAL(2, nrcp1->getRefCount());
    CHECK_EQUAL(2, nrcp2->getRefCount());
    CHECK_EQUAL(2, nrcp3->getRefCount());
    CHECK_EQUAL(3, grcp0->getRefCount());
    CHECK_EQUAL(3, grcp1->getRefCount());
    
    // remove all ref pointers (i.e. all external refs)
    
    nrcp0 = NULL;
    nrcp1 = NULL;
    nrcp2 = NULL;
    nrcp3 = NULL;
    
    grcp0 = NULL;
    grcp1 = NULL;
    
    // all containers must be gone
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(gi1));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni2));
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), OSG::FieldContainerFactory::the()->getContainer(ni3));
    
} // MultipleChildrenSharedCores

TEST(Remove)
{
    // Test removal of objects
    
    OSG::NodeRecPtr  nrcp0 = OSG::Node::create();
    OSG::NodeRecPtr  nrcp1 = OSG::Node::create();
    
    OSG::GroupRecPtr grcp0 = OSG::Group::create();
    
    // add child and core
    nrcp0->addChild(nrcp1);
    nrcp0->setCore (grcp0);
    
    CHECK_EQUAL(1,    nrcp0->getNChildren()       );
    CHECK_EQUAL(grcp0, nrcp0->getCore()            );
    CHECK_EQUAL(nrcp0, grcp0->getMFParents()->at(0));
    
    // remove child
    nrcp0->subChild(OSG::UInt32(0));
    
    CHECK_EQUAL(0, nrcp0->getNChildren());
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), nrcp1->getParent());
    
    // remove core
    nrcp0->setCore(NULL);
    
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), nrcp0->getCore());
    CHECK_EQUAL(0, grcp0->getMFParents()->size());
    
    
    // share the core
    nrcp0->setCore(grcp0);
    nrcp1->setCore(grcp0);
    
    CHECK_EQUAL(2,    grcp0->getMFParents()->size());
    CHECK_EQUAL(nrcp0, grcp0->getMFParents()->at(0) );
    CHECK_EQUAL(nrcp1, grcp0->getMFParents()->at(1) );

    // remove core from one node
    nrcp0->setCore(NULL);
    
    CHECK_EQUAL(1,    grcp0->getMFParents()->size());
    CHECK_EQUAL(nrcp1, grcp0->getMFParents()->at(0) );
    
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), nrcp0->getCore());
    CHECK_EQUAL(grcp0, nrcp1->getCore());
    
} // Remove


TEST(MoveChild)
{
    // Test moving a child from one parent to another

    OSG::NodeRecPtr nrcp0 = OSG::Node::create();
    OSG::NodeRecPtr nrcp1 = OSG::Node::create();
    OSG::NodeRecPtr nrcp2 = OSG::Node::create();
    
    // add child to one node
    nrcp0->addChild(nrcp1);
    
    CHECK_EQUAL(1,    nrcp0->getNChildren()        );
    CHECK_EQUAL(nrcp1, nrcp0->getMFChildren()->at(0));
    CHECK_EQUAL(nrcp0, nrcp1->getParent()           );
    
    // add same child to different node
    nrcp2->addChild(nrcp1);
    
    CHECK_EQUAL(1,    nrcp2->getNChildren()        );
    CHECK_EQUAL(nrcp1, nrcp2->getMFChildren()->at(0));
    CHECK_EQUAL(nrcp2, nrcp1->getParent()           );
   
    OSG::commitChanges();
     
    // make sure it is removed from former parent
    CHECK_EQUAL(0, nrcp0->getNChildren());
    
} // MoveChild

} // SUITE(ReferenceCountTests)
