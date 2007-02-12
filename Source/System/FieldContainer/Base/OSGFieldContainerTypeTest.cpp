/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2006 by the OpenSG Forum                          *
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

// Unit tests for FieldContainerType

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <string>

SUITE(FieldContainerTypeTests)
{

TEST(CreateType)
{
   OSG::NodePtr n = OSG::Node::create();
   OSG::FieldContainerType& n_type(n->getType());
   CHECK(n != OSG::NullFC);
}

TEST(GetDocs)
{
   OSG::GroupPtr tc = OSG::Group::create();
   OSG::FieldContainerType& group_type = tc->getType();

   std::string fcd_xml = group_type.getFcdXML();
   CHECK(fcd_xml != "");

   std::string class_docs = group_type.getDocumentation();
   CHECK(class_docs != "");
}

TEST(GetFieldDocs)
{
   OSG::GroupPtr tc = OSG::Group::create();
   OSG::FieldContainerType& group_type(tc->getType());

   unsigned num_field_descs = group_type.getNumFieldDescs();

   for(unsigned i; i < num_field_descs; ++i)
   {
      OSG::FieldDescriptionBase* fdesc = group_type.getFieldDesc(i);
      std::string field_doc = fdesc->getDocumentation();
      CHECK(true);
   }
}

} // SUITE

