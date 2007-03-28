/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2006 by the OpenSG Forum                   *
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

#include <iostream>
#include <string>
#include <vector>

SUITE(FieldContainerTests)
{

TEST(appendTypesVector)
{
    std::vector<std::string>                     typeNames;
    std::vector<const OSG::FieldContainerType *> types;

    typeNames.push_back("Node");
    typeNames.push_back("NodeCore");
    typeNames.push_back("FieldContainer");

    OSG::appendTypesVector(typeNames, types);

    CHECK_EQUAL(types.size(), 3);
    CHECK(OSG::osgStringCmp(types[0]->getCName(),
                            OSG::Node::getClassType().getCName()          ) == 0);
    CHECK(OSG::osgStringCmp(types[1]->getCName(),
                            OSG::NodeCore::getClassType().getCName()      ) == 0);
    CHECK(OSG::osgStringCmp(types[2]->getCName(),
                            OSG::FieldContainer::getClassType().getCName()) == 0);
}

TEST(appendGroupsVector)
{
    std::vector<std::string> groupNames;
    std::vector<OSG::UInt16> groups;

    groupNames.push_back("Node");
    groupNames.push_back("NodeCores");
    groupNames.push_back("FieldContainer");

    OSG::appendGroupsVector(groupNames, groups);

    CHECK_EQUAL(groups.size(), 3);
    CHECK_EQUAL(groups[0], OSG::Node::getClassGroupId());
    CHECK_EQUAL(groups[1], OSG::NodeCore::getClassGroupId());
    CHECK_EQUAL(groups[2], OSG::FieldContainer::getClassGroupId());
}

TEST(appendTypesString)
{
    std::string                                  typesString;
    std::vector<const OSG::FieldContainerType *> types;

    typesString.assign("Node, NodeCore,FieldContainer");

    OSG::appendTypesString(typesString, types);

    CHECK_EQUAL(types.size(), 3);
    CHECK(OSG::osgStringCmp(types[0]->getCName(),
                            OSG::Node::getClassType().getCName()          ) == 0);
    CHECK(OSG::osgStringCmp(types[1]->getCName(),
                            OSG::NodeCore::getClassType().getCName()      ) == 0);
    CHECK(OSG::osgStringCmp(types[2]->getCName(),
                            OSG::FieldContainer::getClassType().getCName()) == 0);

    typesString.assign("Node");
    types.clear();

    OSG::appendTypesString(typesString, types);

    CHECK_EQUAL(types.size(), 1);
    CHECK(OSG::osgStringCmp(types[0]->getCName(),
                            OSG::Node::getClassType().getCName()) == 0);
}

TEST(checkMemoryCleanup)
{
   // Check to make sure the memory is cleaned up correctly with an FCPtr
   OSG::NodeRefPtr  node(OSG::Node::create());
   OSG::UInt32   node_id   = OSG::getContainerId(node.get());
   OSG::Int32    ref_count = getRefCount(node.get());
   OSG::commitChanges();
   CHECK(OSG::FieldContainerFactory::the()->getContainer(node_id) != OSGNullFC);

   // Now release the ref and check that it was collected
   node = OSGNullFC;
   OSG::commitChanges();
   CHECK(OSG::FieldContainerFactory::the()->getContainer(node_id) == OSGNullFC);
}

// ---- Memory Debugging Tests ---- //
#ifdef OSG_ENABLE_MEMORY_DEBUGGING

TEST(checkDanglingFcPtr)
{
   // Check to make sure that dangling FCPtrs are detected.
   OSG::NodePtr node(OSG::Node::create());
   OSG::NodePtr node_copy = node;
   OSG::FieldContainer*  the_fc = node.getBaseCPtr();
   OSG::UInt32        kids = node->getNChildren();

   OSG::UInt32   node_id = OSG::getContainerId(node);
   CHECK(OSG::FieldContainerFactory::the()->getContainer(node_id) != OSGNullFC);
   OSG::UInt8* base_ptr = node._storeP;
   CHECK((base_ptr != NULL) && (base_ptr == node_copy._storeP));

   OSG::subRef(node);
   CHECK(OSG::FieldContainerFactory::the()->getContainer(node_id) == OSGNullFC);
   //CHECK(NULL == node._storeP);       // Subref clears the main one by default
   CHECK(base_ptr == node_copy._storeP);  // Still points to an invalid object

   // Now try some things that should fail
   //CHECK_ASSERT( node_copy.getBaseCPtr() );
   //CHECK_ASSERT( node_copy->getNChildren() );
   /*  If it works, these should assert
   the_fc = node_copy.getBaseCPtr();
   kids   = node_copy->getNChildren();
   */
}

TEST(checkDanglingFcPtrFreelist)
{
   // Check to make sure that dangling FCPtrs are detected even when memory is allocated in the middle
   OSG::NodePtr node(OSG::Node::create());
   OSG::NodePtr node_copy = node;
   OSG::UInt32   node_id = OSG::getContainerId(node);
   CHECK(OSG::FieldContainerFactory::the()->getContainer(node_id) != OSGNullFC);

   OSG::UInt8* base_ptr = node._storeP;
   CHECK((base_ptr != NULL) && (base_ptr == node_copy._storeP));

   OSG::subRef(node);
   CHECK(OSG::FieldContainerFactory::the()->getContainer(node_id) == OSGNullFC);
   CHECK(base_ptr == node_copy._storeP);  // Still points to an invalid object

   // Allocate and deallocate some memory
   for (unsigned i=0; i<1000;i++)
   {
      OSG::NodeRefPtr       n(OSG::Node::create());
   }

   // Now try some things that should fail
   /*  If it works, these should assert.
   OSG::FieldContainer* the_fc = node_copy.getBaseCPtr();
   OSG::UInt32          kids   = node_copy->getNChildren();
   */

}

#endif

} // SUITE
