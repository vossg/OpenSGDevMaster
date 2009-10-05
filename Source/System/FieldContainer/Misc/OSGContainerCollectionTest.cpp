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

// Unit tests for the ContainerCollection container

#include "OSGContainerCollection.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGBlendChunk.h"

#include "OSGNameAttachment.h"

SUITE(ContainerCollectionTests)
{

TEST(CreatePool)
{
    OSG::ContainerCollectionUnrecPtr cc = OSG::ContainerCollection::create();
    CHECK(cc != NULL);
}

TEST(SettingName)
{
    OSG::ContainerCollectionUnrecPtr cc1(OSG::ContainerCollection::create()),
                                cc2(OSG::ContainerCollection::create()),
                                cc3(OSG::ContainerCollection::create());
    
    CHECK(cc1 != NULL);
    CHECK(cc2 != NULL);
    CHECK(cc3 != NULL);
    
    CHECK(cc1 != cc2);
    CHECK(cc1 != cc3);
    CHECK(cc2 != cc3);
    
    cc1->setName("cc1");
    cc2->setName("cc2");
    cc3->setName("cc3");
    
    CHECK(cc1->getName() == "cc1");
    CHECK(cc2->getName() == "cc2");
    CHECK(cc3->getName() == "cc3");
    
    CHECK(cc1->getName() != "cc2");
    CHECK(cc1->getName() != "cc3");
}


TEST(UsePool)
{
    OSG::ContainerCollectionUnrecPtr cc = OSG::ContainerCollection::create();
    CHECK(cc != NULL);
    
    OSG::GroupUnrecPtr      t  = OSG::Group     ::create();
    OSG::NodeUnrecPtr       n  = OSG::Node      ::create();
    OSG::BlendChunkUnrecPtr bc = OSG::BlendChunk::create();
    
    cc->setName("cc container");
    cc->addContainer(t);
    cc->addContainer(n);
    cc->addContainer(bc);
    
    CHECK_EQUAL(3, cc->getNContainers());
    CHECK_EQUAL(3, cc->getMFContainers()->size());
    
    OSG::FieldContainerUnrecPtr t_ptr  = cc->getContainers(0);
    OSG::FieldContainerUnrecPtr n_ptr  = cc->getContainers(1);
    OSG::FieldContainerUnrecPtr bc_ptr = cc->getContainers(2);
    
    CHECK(true);
    
    // Test removal
    cc->subContainer(t);
    CHECK_EQUAL(2, cc->getNContainers());
    
    cc->subContainer(n);
    CHECK_EQUAL(1, cc->getNContainers());
    
    cc->subContainer(bc);
    CHECK_EQUAL(0, cc->getNContainers());
    
    // Try it as an attachment
    OSG::NodeUnrecPtr root_node = OSG::Node::create();
    
    OSG::ContainerCollectionUnrecPtr cc2;
    CHECK(root_node->findAttachment(OSG::ContainerCollection::getClassType()) == NULL);
    
    root_node->addAttachment(cc);
    
    // now find it
    cc2 = dynamic_cast<OSG::ContainerCollection::ObjCPtr>(
            root_node->findAttachment(OSG::ContainerCollection::getClassType()));
    CHECK(cc2 != NULL);
    CHECK(cc2 == cc);
    
    // Name it and find it by name
    OSG::ContainerCollectionUnrecPtr named_cc = OSG::ContainerCollection::create();
    named_cc->setName("MyPool");
    
    for(unsigned i=0;i<10;i++)
    {
        if(i%2)
        {
            OSG::ContainerCollectionUnrecPtr new_cc =
                OSG::ContainerCollection::create();
        
            root_node->addAttachment(new_cc, i);
        }
    }
    root_node->addAttachment(named_cc, 7);
    
    unsigned x = 0;
    OSG::ContainerCollectionUnrecPtr cc3(NULL);
    
    while(NULL == cc3)
    {
        OSG::ContainerCollectionUnrecPtr temp_cc;
        temp_cc = dynamic_cast<OSG::ContainerCollection::ObjCPtr>(
                root_node->findAttachment(OSG::ContainerCollection::getClassType(), x));
        if((NULL != temp_cc) && (temp_cc->getName() == "MyPool"))
        {
            cc3 = temp_cc;
            CHECK(cc3 == named_cc);
            break;
        }
        x++;
    }
    
    CHECK_EQUAL(7, x);
    CHECK_EQUAL("MyPool", cc3->getName());
}

} // SUITE
