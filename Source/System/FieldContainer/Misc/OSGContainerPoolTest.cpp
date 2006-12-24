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

#include <OpenSG/OSGContainerPool.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGBlendChunk.h>

#include <OpenSG/OSGNameAttachment.h>

SUITE(ContainerPoolTests)
{

TEST(CreatePool)
{
   OSG::ContainerPoolPtr cp = OSG::ContainerPool::create();
   CHECK(cp != OSG::NullFC);
}

TEST(SettingName)
{
   OSG::ContainerPoolPtr cp1(OSG::ContainerPool::create()),
                         cp2(OSG::ContainerPool::create()),
                         cp3(OSG::ContainerPool::create());

   CHECK(cp1 != OSG::NullFC);
   CHECK(cp2 != OSG::NullFC);
   CHECK(cp3 != OSG::NullFC);

   CHECK(cp1 != cp2);
   CHECK(cp1 != cp3);
   CHECK(cp2 != cp3);

   cp1->setName("cp1");
   cp2->setName("cp2");
   cp3->setName("cp3");

   CHECK(cp1->getName() == "cp1");
   CHECK(cp2->getName() == "cp2");
   CHECK(cp3->getName() == "cp3");

   CHECK(cp1->getName() != "cp2");
   CHECK(cp1->getName() != "cp3");
}


TEST(UsePool)
{
   OSG::ContainerPoolPtr cp = OSG::ContainerPool::create();
   CHECK(cp != OSG::NullFC);

   OSG::TransformPtr t = OSG::Transform::create();
   OSG::NodePtr n = OSG::Node::create();
   OSG::BlendChunkPtr bc = OSG::BlendChunk::create();

   cp->setName("cp container");
   cp->addContainer(t);
   cp->addContainer(n);
   cp->addContainer(bc);

   CHECK(cp->getNContainers() == 3);
   CHECK(cp->getContainers().size() == 3);

   OSG::FieldContainerPtr t_ptr = cp->getContainers(0);
   OSG::FieldContainerPtr n_ptr = cp->getContainers(1);
   OSG::FieldContainerPtr bc_ptr = cp->getContainers(2);

   CHECK(true);

   // Test removal
   cp->subContainer(t);
   CHECK(cp->getNContainers() == 2);

   cp->subContainer(n);
   CHECK(cp->getNContainers() == 1);

   cp->subContainer(bc);
   CHECK(cp->getNContainers() == 0);

   // Try it as an attachment
   OSG::NodePtr root_node = OSG::Node::create();

   OSG::ContainerPoolPtr cp2;
   CHECK(root_node->findAttachment(OSG::ContainerPool::getClassType()) == OSG::NullFC);

   root_node->addAttachment(cp);

   // now find it
   cp2 = OSG::cast_dynamic<OSG::ContainerPoolPtr>(
                        root_node->findAttachment(OSG::ContainerPool::getClassType()));
   CHECK(cp2 != OSG::NullFC);
   CHECK(cp2 == cp);

   // Name it and find it by name
   OSG::ContainerPoolPtr named_cp = OSG::ContainerPool::create();
   named_cp->setName("MyPool");

   for(unsigned i=0;i<10;i++)
   {
      if(i%2)
      {
         root_node->addAttachment(OSG::ContainerPool::create(), i);
      }
   }
   root_node->addAttachment(named_cp, 7);

   unsigned x = 0;
   OSG::ContainerPoolPtr cp3(OSG::NullFC);

   while(OSG::NullFC == cp3)
   {
      OSG::ContainerPoolPtr temp_cp;
      temp_cp = OSG::cast_dynamic<OSG::ContainerPoolPtr>(
                        root_node->findAttachment(OSG::ContainerPool::getClassType(), x));
      if((OSG::NullFC != temp_cp) && (temp_cp->getName() == "MyPool"))
      {
         cp3 = temp_cp;
         CHECK(cp3 == named_cp);
         break;
      }
      x++;
   }

   CHECK_EQUAL(7, x);
   CHECK_EQUAL(cp3->getName(), "MyPool");
}

} // SUITE
