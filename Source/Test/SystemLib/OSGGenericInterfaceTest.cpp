/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2007 by the OpenSG Forum                      *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include <OSGFCDPtrTestFC.h>
#include <OSGFCDPtrTestFCNullCheckAccess.h>

#include <iostream>
#include <string>
#include <vector>

SUITE(GenericInterfaceTests)
{

TEST(NodeBasic)
{
    OSG::NodeUnrecPtr n0 = OSG::Node::create();
    OSG::NodeUnrecPtr n1 = OSG::Node::create();
    OSG::NodeUnrecPtr n2 = OSG::Node::create();
    
    OSG::FieldContainerPtrMFieldBase::EditHandlePtr childEH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::EditHandle>(
            n0->editField(OSG::Node::ChildrenFieldId));
        
    CHECK(childEH != NULL);
    CHECK(childEH->isValid());
    
    // add a child
    childEH->add(n1);
    
    CHECK_EQUAL(1,  n0->getNChildren()        );
    CHECK_EQUAL(n1, n0->getMFChildren()->at(0));
    CHECK_EQUAL(n0, n1->getParent()           );

    // add another child
    childEH->add(n2);
    
    CHECK_EQUAL(2,  n0->getNChildren()        );
    CHECK_EQUAL(n1, n0->getMFChildren()->at(0));
    CHECK_EQUAL(n2, n0->getMFChildren()->at(1));
    CHECK_EQUAL(n0, n2->getParent()           );
    
    OSG::FieldContainerPtrMFieldBase::GetHandlePtr childGH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::GetHandle>(
            n0->getField(OSG::Node::ChildrenFieldId));
            
    CHECK(childGH != NULL);
    CHECK(childGH->isValid());
    
    CHECK_EQUAL(2,  childGH->size());
    CHECK_EQUAL(n1, childGH->get(0));
    CHECK_EQUAL(n2, childGH->get(1));
    
    OSG::GroupRefPtr g0 = OSG::Group::create();
    OSG::GroupRefPtr g1 = OSG::Group::create();
    
    OSG::FieldContainerPtrSFieldBase::EditHandlePtr coreEH0 =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::EditHandle>(
            n0->editField(OSG::Node::CoreFieldId));
            
    CHECK(coreEH0 != NULL);
    CHECK(coreEH0->isValid());
    
    // set n0 core
    coreEH0->set(g0);
    
    CHECK_EQUAL(g0, n0->getCore()      );
    CHECK_EQUAL(n0, g0->getParents()[0]);
    
    OSG::FieldContainerPtrSFieldBase::EditHandlePtr coreEH1 =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::EditHandle>(
            n1->editField(OSG::Node::CoreFieldId));
            
    CHECK(coreEH1 != NULL);
    CHECK(coreEH1->isValid());
    
    // set n1 core
    coreEH1->set(g1);
    
    CHECK_EQUAL(g1, n1->getCore()      );
    CHECK_EQUAL(n1, g1->getParents()[0]);
    
    OSG::FieldContainerPtrSFieldBase::GetHandlePtr coreGH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::GetHandle>(
            n0->getField(OSG::Node::CoreFieldId));
            
    CHECK(coreGH != NULL);
    CHECK(coreGH->isValid());
    
    CHECK_EQUAL(g0, coreGH->get());
    
    coreGH = boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::GetHandle>(
        n1->getField(OSG::Node::CoreFieldId));
        
    CHECK(coreGH != NULL);
    CHECK(coreGH->isValid());
    
    CHECK_EQUAL(g1, coreGH->get());
    
} // TEST(NodeBasic) 

TEST(NodeAdvanced)
{
    OSG::NodeUnrecPtr n0 = OSG::Node::create();
    OSG::NodeUnrecPtr n1 = OSG::Node::create();
    OSG::NodeUnrecPtr n2 = OSG::Node::create();
    OSG::NodeUnrecPtr n3 = OSG::Node::create();
    
    OSG::FieldContainerPtrMFieldBase::EditHandlePtr childEH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::EditHandle>(
            n0->editField(OSG::Node::ChildrenFieldId));
    
    CHECK(childEH != NULL);
    CHECK(childEH->isValid());
                    
    childEH->add(n1);
    childEH->add(n2);
    
    CHECK_EQUAL(n1, n0->getMFChildren()->at(0));
    CHECK_EQUAL(n2, n0->getMFChildren()->at(1));
    
    // insert a child, n0 -- [n1, n3, n2]
    childEH->insert(1, n3);
    
    CHECK_EQUAL(n1, n0->getMFChildren()->at(0));
    CHECK_EQUAL(n3, n0->getMFChildren()->at(1));
    CHECK_EQUAL(n2, n0->getMFChildren()->at(2));
    
    CHECK_EQUAL(n0, n1->getParent());
    CHECK_EQUAL(n0, n2->getParent());
    CHECK_EQUAL(n0, n3->getParent());
    
    // remove a child by index, n0 -- [n3, n2]
    childEH->remove(0);
    
    CHECK_EQUAL(2,  n0->getNChildren()        );
    CHECK_EQUAL(n3, n0->getMFChildren()->at(0));
    CHECK_EQUAL(n2, n0->getMFChildren()->at(1));
    CHECK(n1->getParent() == NULL);
    
    // attempt to find a child that is not there, n0 -- [n3, n2]
    OSG::Int32 n1Idx = childEH->find(n1);
    CHECK_EQUAL(-1, n1Idx);
    
    CHECK_EQUAL(2,  n0->getNChildren()        );
    CHECK_EQUAL(n3, n0->getMFChildren()->at(0));
    CHECK_EQUAL(n2, n0->getMFChildren()->at(1));
    
    // find, then remove a child, n0 -- [n3]
    OSG::Int32 n2Idx = childEH->find(n2);
    CHECK_EQUAL(1, n2Idx);
    childEH->remove(n2Idx);
    
    CHECK_EQUAL(1,  n0->getNChildren()        );
    CHECK_EQUAL(n3, n0->getMFChildren()->at(0));
    CHECK(n2->getParent() == NULL);
    
    // replace by index, n0 -- [n1]
    childEH->replace(0, n1);
    
    CHECK_EQUAL(1,  n0->getNChildren()        );
    CHECK_EQUAL(n1, n0->getMFChildren()->at(0));
    CHECK(n3->getParent() == NULL);
    CHECK(n1->getParent() == n0  );
    
    // replace by object, n0 -- [n2]
    n1Idx = childEH->find(n1);
    CHECK_EQUAL(0, n1Idx);
    childEH->replace(n1Idx, n2);
    
    CHECK_EQUAL(1,  n0->getNChildren()        );
    CHECK_EQUAL(n2, n0->getMFChildren()->at(0));
    CHECK(n1->getParent() == NULL);
    CHECK(n2->getParent() == n0  );
    
} // TEST(NodeAdvanced)

TEST(FCDPtrTestFCStdAccess)
{
    OSG::FCDPtrTestFCUnrecPtr fc1 = OSG::FCDPtrTestFC::create();
    
    OSG::FCDTestFCUnrecPtr    fc2 = OSG::FCDTestFC::create();
    OSG::FCDTestFCUnrecPtr    fc3 = OSG::FCDTestFC::create();
    
    OSG::FieldContainerPtrSFieldBase::EditHandlePtr sfEH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::EditHandle>(
            fc1->editField(OSG::FCDPtrTestFC::FieldSFPub_ptrFieldId));
    OSG::FieldContainerPtrSFieldBase::GetHandlePtr sfGH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::GetHandle>(
            fc1->getField(OSG::FCDPtrTestFC::FieldSFPub_ptrFieldId));
    
    CHECK(sfEH != NULL   );
    CHECK(sfEH->isValid());
    
    CHECK(sfGH != NULL   );
    CHECK(sfGH->isValid());
    
    CHECK_EQUAL(true, sfEH->set(fc2));
    
    CHECK_EQUAL(fc2, sfGH->get());
    CHECK_EQUAL(fc2, sfEH->get());
    
    CHECK_EQUAL(true, sfEH->set(NULL));
    
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), sfGH->get());
    CHECK_EQUAL(static_cast<OSG::FieldContainer *>(NULL), sfEH->get());
    
    
    OSG::FieldContainerPtrMFieldBase::EditHandlePtr mfEH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::EditHandle>(
            fc1->editField(OSG::FCDPtrTestFC::FieldMFPub_ptrFieldId));
    OSG::FieldContainerPtrMFieldBase::GetHandlePtr mfGH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::GetHandle>(
            fc1->getField(OSG::FCDPtrTestFC::FieldMFPub_ptrFieldId));

    CHECK(mfEH != NULL   );
    CHECK(mfEH->isValid());
    
    CHECK(mfGH != NULL   );
    CHECK(mfGH->isValid());
            
    CHECK_EQUAL(true, mfEH->add(fc2));
    CHECK_EQUAL(true, mfEH->add(fc3));
    
    CHECK_EQUAL(2,   mfGH->size());
    CHECK_EQUAL(fc2, mfGH->get(0));
    CHECK_EQUAL(fc3, mfGH->get(1));
    
    CHECK_EQUAL(true, mfEH->replace(0, fc3));
    
    CHECK_EQUAL(2,   mfGH->size());
    CHECK_EQUAL(fc3, mfGH->get(0));
    CHECK_EQUAL(fc3, mfGH->get(1));
    
    CHECK_EQUAL(true, mfEH->remove(1));
    
    CHECK_EQUAL(1,   mfGH->size());
    CHECK_EQUAL(fc3, mfGH->get(0));
    
    CHECK_EQUAL(true, mfEH->insert(0, fc2));
    
    CHECK_EQUAL(2,   mfGH->size());
    CHECK_EQUAL(fc2, mfGH->get(0));
    CHECK_EQUAL(fc3, mfGH->get(1));
    
            
} // TEST(FCDPtrTestStdAccess)

TEST(FCDPtrTestFCNullCheckAccess)
{
    OSG::FCDPtrTestFCNullCheckAccessUnrecPtr fc1 = 
        OSG::FCDPtrTestFCNullCheckAccess::create();
    
    OSG::FCDTestFCUnrecPtr    fc2 = OSG::FCDTestFC::create();
    OSG::FCDTestFCUnrecPtr    fc3 = OSG::FCDTestFC::create();
    
    OSG::FieldContainerPtrSFieldBase::EditHandlePtr sfEH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::EditHandle>(
            fc1->editField(OSG::FCDPtrTestFC::FieldSFPub_ptrFieldId));
    OSG::FieldContainerPtrSFieldBase::GetHandlePtr sfGH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrSFieldBase::GetHandle>(
            fc1->getField(OSG::FCDPtrTestFC::FieldSFPub_ptrFieldId));
    
    CHECK(sfEH != NULL   );
    CHECK(sfEH->isValid());
    
    CHECK(sfGH != NULL   );
    CHECK(sfGH->isValid());
    
    CHECK_EQUAL(true, sfEH->set(fc2));
    
    CHECK_EQUAL(fc2, sfGH->get());
    CHECK_EQUAL(fc2, sfEH->get());
    
    // attempt to set NULL
    CHECK_EQUAL(false, sfEH->set(NULL));
    
    // previous value must still be present
    CHECK_EQUAL(fc2, sfGH->get());
    CHECK_EQUAL(fc2, sfEH->get());
    
    
    OSG::FieldContainerPtrMFieldBase::EditHandlePtr mfEH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::EditHandle>(
            fc1->editField(OSG::FCDPtrTestFC::FieldMFPub_ptrFieldId));
    OSG::FieldContainerPtrMFieldBase::GetHandlePtr mfGH =
        boost::dynamic_pointer_cast<OSG::FieldContainerPtrMFieldBase::GetHandle>(
            fc1->getField(OSG::FCDPtrTestFC::FieldMFPub_ptrFieldId));

    CHECK(mfEH != NULL   );
    CHECK(mfEH->isValid());
    
    CHECK(mfGH != NULL   );
    CHECK(mfGH->isValid());
            
    CHECK_EQUAL(true, mfEH->add(fc2));
    CHECK_EQUAL(true, mfEH->add(fc3));
    
    CHECK_EQUAL(2,   mfGH->size());
    CHECK_EQUAL(fc2, mfGH->get(0));
    CHECK_EQUAL(fc3, mfGH->get(1));
    
    CHECK_EQUAL(true, mfEH->replace(0, fc3));
    
    CHECK_EQUAL(2,   mfGH->size());
    CHECK_EQUAL(fc3, mfGH->get(0));
    CHECK_EQUAL(fc3, mfGH->get(1));
    
    CHECK_EQUAL(true, mfEH->remove(1));
    
    CHECK_EQUAL(1,   mfGH->size());
    CHECK_EQUAL(fc3, mfGH->get(0));
    
    CHECK_EQUAL(true, mfEH->insert(0, fc2));
    
    CHECK_EQUAL(2,   mfGH->size());
    CHECK_EQUAL(fc2, mfGH->get(0));
    CHECK_EQUAL(fc3, mfGH->get(1));
            
} // TEST(FCDPtrTestFCNullCheckAccess)




} // SUITE

