
#include <UnitTest++.h>

// Unit tests for vec classes

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/operations.hpp>
namespace bf = boost::filesystem;

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
