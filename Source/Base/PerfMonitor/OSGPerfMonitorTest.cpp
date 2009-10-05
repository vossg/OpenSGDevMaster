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

// Unit tests for Performance monitoring code

#include "OSGConfig.h"
#include "OSGPerfMonitor.h"
#include "OSGPerfMonitorGuard.h"

#include <boost/filesystem/operations.hpp>

namespace bf = boost::filesystem;

SUITE(PerfMonitorTests)
{

struct PerfFileFixture
{
   PerfFileFixture()
   {
      OSG::PerfMonitor::the()->reset();
      OSG::PerfMonitor::the()->enable(false);

      test_file = bf::path("test_perf.data");
      bf::remove(test_file);
   }

   ~PerfFileFixture()
   {
      bf::remove(test_file);
   }

   bf::path test_file;
};


TEST_FIXTURE(PerfFileFixture, TestInitialization)
{
   OSG::PerfMonitor::the()->reset();
   CHECK_EQUAL(OSG::PerfMonitor::the()->mSamples.size(), 0);
   CHECK_EQUAL(OSG::PerfMonitor::the()->getEnabled(), false);
   CHECK_EQUAL((void*)OSG::PerfMonitor::the()->mOutFile, (void*)NULL);
}


TEST_FIXTURE(PerfFileFixture, TestSample)
{
   OSG::PerfMonitor::the()->reset();
   CHECK_EQUAL(OSG::PerfMonitor::the()->mSamples.size(), 0);
   OSG::PerfMonitor::the()->sample(OSG::PerfMonitorBase::MARK, "test");
   CHECK_EQUAL(OSG::PerfMonitor::the()->mSamples.size(), 0);

   OSG::PerfMonitor::the()->enable(true);
   OSG::PerfMonitor::the()->sample(OSG::PerfMonitorBase::MARK, "test");
   CHECK_EQUAL(OSG::PerfMonitor::the()->mSamples.size(), 1);
}

TEST_FIXTURE(PerfFileFixture, TestPerfGuards)
{
   OSG::PerfMonitor::the()->reset();
   OSG::PerfMonitor::the()->enable(true);

   CHECK(OSG::PerfMonitor::the()->mSamples.size() == 0);

   // Single scope test
   {
   OSG::PerfMonitorGuard g("test_scope");
      CHECK_EQUAL(1, OSG::PerfMonitor::the()->mSamples.size());
   }
   CHECK_EQUAL(2, OSG::PerfMonitor::the()->mSamples.size());

   // Test nested scopes
   {
   OSG::PerfMonitorGuard g("test_outer_scope");
      CHECK_EQUAL(3, OSG::PerfMonitor::the()->mSamples.size());
      {
      OSG::PerfMonitorGuard g("test_inner_scope");
         CHECK_EQUAL(4, OSG::PerfMonitor::the()->mSamples.size());
      }
      CHECK_EQUAL(5, OSG::PerfMonitor::the()->mSamples.size());
   }
   CHECK_EQUAL(6, OSG::PerfMonitor::the()->mSamples.size());
}

TEST_FIXTURE(PerfFileFixture, TestPerfOutput)
{
   OSG::PerfMonitor::the()->reset();
   OSG::PerfMonitor::the()->enable(true);

   CHECK(!bf::exists(test_file));

   OSG::PerfMonitor::the()->setOutputFile(test_file.native_file_string());
   CHECK(bf::exists(test_file));

   OSG::PerfMonitor::the()->sample(OSG::PerfMonitorBase::ENTER, "test", 21.0);
   OSG::PerfMonitor::the()->flushOutput();
   OSG::PerfMonitor::the()->setOutputFile("");
   CHECK(bf::exists(test_file));

   // TODO: Add test to look at the file output
}

TEST_FIXTURE(PerfFileFixture, TestFlushing)
{
   OSG::PerfMonitor::the()->reset();
   OSG::PerfMonitor::the()->enable(true);
   OSG::PerfMonitor::the()->setOutputFlushRate(10);
   CHECK_EQUAL(0, OSG::PerfMonitor::the()->mSamples.size());

   // Check that size grows
   for(unsigned i=1; i<5; i++)
   {
      OSG::PerfMonitor::the()->sample(OSG::PerfMonitorBase::MARK, "test");
      OSG::PerfMonitor::the()->updateFrame();  // Adds frame sample
      CHECK_EQUAL(i*2, OSG::PerfMonitor::the()->mSamples.size());
   }

   // Check that this one causes a flush
   OSG::PerfMonitor::the()->sample(OSG::PerfMonitorBase::MARK, "test");
   CHECK_EQUAL(9, OSG::PerfMonitor::the()->mSamples.size());
   OSG::PerfMonitor::the()->updateFrame();
   CHECK_EQUAL(0, OSG::PerfMonitor::the()->mSamples.size());
}


/*
TEST_FIXTURE(FileFixture, CreateOSBFile)
{
   OSG::NodePtr n = OSG::Node::create();

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(n, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodePtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != OSGNullFC);
}

TEST_FIXTURE(FileFixture, CreateOSBTree)
{
   // Test larger tree
   OSG::NodePtr base_node  = OSG::Node::create();
   base_node->setCore(OSG::Group::create());
   OSG::NodePtr child_node = OSG::Node::create();
   child_node->setCore(OSG::Group::create());

   base_node->addChild(child_node);

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(base_node, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodePtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != OSGNullFC);
   CHECK(new_n->getCore() != OSGNullFC);
   CHECK(new_n->getNChildren() == 1);
   CHECK(new_n->getChild(0) != OSGNullFC);
   CHECK(new_n->getChild(0)->getCore() != OSGNullFC);
}
*/



} // SUITE

