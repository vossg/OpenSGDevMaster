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

// Unit tests for OSB file io.

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/operations.hpp>

namespace bf = boost::filesystem;

SUITE(OSBTests)
{

struct FileFixture
{
   FileFixture()
   {
      test_file = bf::path("test_file.osb");
      bf::remove(test_file);
   }

   ~FileFixture()
   {
      bf::remove(test_file);
   }

   bf::path test_file;
};


TEST_FIXTURE(FileFixture, CreateOSBFile)
{
   OSG::NodePtr n = OSG::Node::create();

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(n, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodePtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != OSG::NullFC);
}


TEST_FIXTURE(FileFixture, TestNameRetention)
{
   std::string start_name("node");
   OSG::NodePtr n = OSG::Node::create();
   OSG::setName(n, start_name);

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(n, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodePtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != OSG::NullFC);
   CHECK(OSG::getName(new_n) != NULL);
   std::string cur_name = std::string(OSG::getName(new_n));

   CHECK(cur_name == start_name);
}

} // SUITE
