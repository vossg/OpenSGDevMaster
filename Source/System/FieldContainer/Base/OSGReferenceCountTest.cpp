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

SUITE(ReferenceCountTests)
{

// TODO: XXX At the moment parent pointers are uncounted instead of weak, 
//           so we skip the weak ref count checks for now

TEST(BasicStructure)
{
    // Basic case, two nodes, each with it's own core.
    //
    //   np0[gp0]
    //    |
    //   np1[gp1]

    // create objects

    OSG::NodeRecPtr  nrp0(OSG::Node ::create());
    OSG::NodeRecPtr  nrp1(OSG::Node ::create());
    OSG::GroupRecPtr grp0(OSG::Group::create());
    OSG::GroupRecPtr grp1(OSG::Group::create());

    OSG::Node  *np0 = nrp0.get();
    OSG::Node  *np1 = nrp1.get();
    OSG::Group *gp0 = grp0.get();
    OSG::Group *gp1 = grp1.get();

    OSG::UInt32 ni0 = nrp0->getId();
    OSG::UInt32 ni1 = nrp1->getId();
    OSG::UInt32 gi0 = grp0->getId();
    OSG::UInt32 gi1 = grp1->getId();
    
    CHECK_EQUAL(1, nrp0->getRefCount()    );
    CHECK_EQUAL(0, nrp0->getWeakRefCount());
    
    CHECK_EQUAL(1, nrp1->getRefCount()    );
    CHECK_EQUAL(0, nrp1->getWeakRefCount());
    
    CHECK_EQUAL(1, grp0->getRefCount()    );
    CHECK_EQUAL(0, grp0->getWeakRefCount());
    
    CHECK_EQUAL(1, grp1->getRefCount()    );
    CHECK_EQUAL(0, grp1->getWeakRefCount());
    
    OSG::commitChanges();
    
    // link nodes
    
    nrp0->addChild(nrp1);
    nrp0->setCore(grp0);
    nrp1->setCore(grp1);
    
    CHECK_EQUAL(1, nrp0->getRefCount());
    CHECK_EQUAL(2, nrp1->getRefCount());
    CHECK_EQUAL(2, grp0->getRefCount());
    CHECK_EQUAL(2, grp1->getRefCount());

    CHECK_EQUAL(nrp0, nrp1->getParent()           );
    CHECK_EQUAL(nrp1, nrp0->getMFChildren()->at(0));
    
    CHECK_EQUAL(grp0, nrp0->getCore()            );
    CHECK_EQUAL(grp1, nrp1->getCore()            );
    CHECK_EQUAL(nrp0, grp0->getMFParents()->at(0));
    CHECK_EQUAL(nrp1, grp1->getMFParents()->at(0));
    
    // remove all ref pointers (i.e. all external refs)
    
    nrp0 = NULL;
    nrp1 = NULL;
    grp0 = NULL;
    grp1 = NULL;
    
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
    
    OSG::NodeRecPtr     nrp0 = OSG::Node ::create();
    OSG::NodeRecPtr     nrp1 = OSG::Node ::create();
    OSG::NodeCoreRecPtr grp  = OSG::Group::create();
    
    OSG::Node     *np0 = nrp0.get();
    OSG::Node     *np1 = nrp1.get();
    OSG::NodeCore *gp0 = grp .get();
    
    OSG::UInt32 ni0 = nrp0->getId();
    OSG::UInt32 ni1 = nrp1->getId();
    OSG::UInt32 gi0 = grp ->getId();
    
    nrp0->setCore (grp );
    nrp0->addChild(nrp1);
    
    nrp1->setCore(grp);
    
    nrp1 = OSG::Node::create();
    
    OSG::Node   *np2 = nrp1.get();
    OSG::UInt32  ni2 = nrp1->getId();
    
    nrp0->addChild(nrp1);
    nrp1->setCore (grp );
    
    CHECK_EQUAL(1, np0->getRefCount());
    CHECK_EQUAL(1, np1->getRefCount());
    CHECK_EQUAL(2, np2->getRefCount());
    CHECK_EQUAL(4, gp0->getRefCount());
    
    // remove all ref pointers (i.e. all external refs)
    
    nrp1 = NULL;
    grp  = NULL;
    
    // all containers must still exist
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(np2, OSG::FieldContainerFactory::the()->getContainer(ni2));
    
    nrp0 = NULL;
    
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
    
    OSG::NodeRecPtr  nrp0(OSG::Node ::create());
    OSG::NodeRecPtr  nrp1(OSG::Node ::create());
    OSG::GroupRecPtr grp0(OSG::Group::create());

    OSG::Node  *np0 = nrp0.get();
    OSG::Node  *np1 = nrp1.get();
    OSG::Group *gp0 = grp0.get();

    OSG::UInt32 ni0 = nrp0->getId();
    OSG::UInt32 ni1 = nrp1->getId();
    OSG::UInt32 gi0 = grp0->getId();
        
    CHECK_EQUAL(1, nrp0->getRefCount());
    CHECK_EQUAL(1, nrp1->getRefCount());
    
    CHECK_EQUAL(1, grp0->getRefCount()    );
    CHECK_EQUAL(0, grp0->getWeakRefCount());
    
    OSG::commitChanges();
    
    // link nodes
    
    nrp0->addChild(nrp1);
    
    CHECK_EQUAL(1, np0->getRefCount());
    CHECK_EQUAL(2, np1->getRefCount());
    
    CHECK_EQUAL(np0, np1->getParent()           );
    CHECK_EQUAL(np1, np0->getMFChildren()->at(0));
    
    OSG::commitChanges();
    
    // add core to np0
    
    nrp0->setCore(gp0);
    
    CHECK_EQUAL(1, np0->getRefCount());
    CHECK_EQUAL(2, gp0->getRefCount());
    
    CHECK_EQUAL(gp0, np0->getCore()            );
    CHECK_EQUAL(np0, gp0->getMFParents()->at(0));
    
    OSG::commitChanges();
    
    // add core to np1
    
    nrp1->setCore(gp0);
    
    CHECK_EQUAL(2, np1->getRefCount());
    CHECK_EQUAL(3, gp0->getRefCount());
        
    CHECK_EQUAL(gp0, np1->getCore()            );
    CHECK_EQUAL(np1, gp0->getMFParents()->at(1));
    
    OSG::commitChanges();
    
    // remove all ref pointers (i.e. all external refs)
    
    grp0 = NULL;
    
    // all containers must still exist
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(2, gp0->getRefCount()    );
//     CHECK_EQUAL(0, gp0->getWeakRefCount());
    
    nrp1 = NULL;
    
    // all containers must still exist
    CHECK_EQUAL(gp0, OSG::FieldContainerFactory::the()->getContainer(gi0));
    CHECK_EQUAL(np0, OSG::FieldContainerFactory::the()->getContainer(ni0));
    CHECK_EQUAL(np1, OSG::FieldContainerFactory::the()->getContainer(ni1));
    CHECK_EQUAL(2, gp0->getRefCount());
    CHECK_EQUAL(1, np1->getRefCount());
    
    nrp0 = NULL;
    
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

    OSG::NodeRecPtr  nrp0 = OSG::Node ::create();
    OSG::NodeRecPtr  nrp1 = OSG::Node ::create();
    OSG::NodeRecPtr  nrp2 = OSG::Node ::create();
    OSG::NodeRecPtr  nrp3 = OSG::Node ::create();
    OSG::GroupRecPtr grp0 = OSG::Group::create();
    OSG::GroupRecPtr grp1 = OSG::Group::create();

    OSG::Node  *np0 = nrp0.get();
    OSG::Node  *np1 = nrp1.get();
    OSG::Node  *np2 = nrp2.get();
    OSG::Node  *np3 = nrp3.get();
    OSG::Group *gp0 = grp0.get();
    OSG::Group *gp1 = grp1.get();

    OSG::UInt32 ni0 = nrp0->getId();
    OSG::UInt32 ni1 = nrp1->getId();
    OSG::UInt32 ni2 = nrp2->getId();
    OSG::UInt32 ni3 = nrp3->getId();
    OSG::UInt32 gi0 = grp0->getId();
    OSG::UInt32 gi1 = grp1->getId();
        
    // link nodes    
    
    nrp0->addChild(nrp1);
    nrp0->addChild(nrp2);
    nrp1->addChild(nrp3);
    
    nrp0->setCore(grp0);
    nrp1->setCore(grp1);
    nrp2->setCore(grp1);
    nrp3->setCore(grp0);
    
    CHECK_EQUAL(1, nrp0->getRefCount());
    CHECK_EQUAL(2, nrp1->getRefCount());
    CHECK_EQUAL(2, nrp2->getRefCount());
    CHECK_EQUAL(2, nrp3->getRefCount());
    CHECK_EQUAL(3, grp0->getRefCount());
    CHECK_EQUAL(3, grp1->getRefCount());
    
    // remove all ref pointers (i.e. all external refs)
    
    nrp0 = NULL;
    nrp1 = NULL;
    nrp2 = NULL;
    nrp3 = NULL;
    
    grp0 = NULL;
    grp1 = NULL;
    
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
    
    OSG::NodeRecPtr  nrp0 = OSG::Node::create();
    OSG::NodeRecPtr  nrp1 = OSG::Node::create();
    
    OSG::GroupRecPtr grp0 = OSG::Group::create();
    
    // add child and core
    nrp0->addChild(nrp1);
    nrp0->setCore (grp0);
    
    CHECK_EQUAL(1,    nrp0->getNChildren()       );
    CHECK_EQUAL(grp0, nrp0->getCore()            );
    CHECK_EQUAL(nrp0, grp0->getMFParents()->at(0));
    
    // remove child
    nrp0->subChild(OSG::UInt32(0));
    
    CHECK_EQUAL(0, nrp0->getNChildren());
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), nrp1->getParent());
    
    // remove core
    nrp0->setCore(NULL);
    
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), nrp0->getCore());
    CHECK_EQUAL(0, grp0->getMFParents()->size());
    
    
    // share the core
    nrp0->setCore(grp0);
    nrp1->setCore(grp0);
    
    CHECK_EQUAL(2,    grp0->getMFParents()->size());
    CHECK_EQUAL(nrp0, grp0->getMFParents()->at(0) );
    CHECK_EQUAL(nrp1, grp0->getMFParents()->at(1) );

    // remove core from one node
    nrp0->setCore(NULL);
    
    CHECK_EQUAL(1,    grp0->getMFParents()->size());
    CHECK_EQUAL(nrp1, grp0->getMFParents()->at(0) );
    
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), nrp0->getCore());
    CHECK_EQUAL(grp0, nrp1->getCore());
    
} // Remove


TEST(MoveChild)
{
    // Test moving a child from one parent to another

    OSG::NodeRecPtr nrp0 = OSG::Node::create();
    OSG::NodeRecPtr nrp1 = OSG::Node::create();
    OSG::NodeRecPtr nrp2 = OSG::Node::create();
    
    // add child to one node
    nrp0->addChild(nrp1);
    
    CHECK_EQUAL(1,    nrp0->getNChildren()        );
    CHECK_EQUAL(nrp1, nrp0->getMFChildren()->at(0));
    CHECK_EQUAL(nrp0, nrp1->getParent()           );
    
    // add same child to different node
    nrp2->addChild(nrp1);
    
    CHECK_EQUAL(1,    nrp2->getNChildren()        );
    CHECK_EQUAL(nrp1, nrp2->getMFChildren()->at(0));
    CHECK_EQUAL(nrp2, nrp1->getParent()           );
   
    OSG::commitChanges();
     
    // make sure it is removed from former parent
    CHECK_EQUAL(0, nrp0->getNChildren());
    
} // MoveChild

} // SUITE(ReferenceCountTests)
