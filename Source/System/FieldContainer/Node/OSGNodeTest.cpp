
#include <UnitTest++.h>

// Unit tests for vec classes

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNameAttachment.h>


TEST(CreateNode)
{
   OSG::NodePtr n = OSG::Node::create();
   CHECK(n != OSG::NullFC);
}



// --- Cloning --- //
TEST(TreeCloningName)
{
   OSG::NodePtr root = OSG::Node::create();
   OSG::NodePtr child_node = OSG::Node::create();
   root->addChild(child_node);
   OSG::setName(root, "root");
   OSG::setName(child_node, "child_node");
   
   OSG::NodePtr new_root = OSG::cloneTree(root);
   
   CHECK(new_root->getNChildren() == 1);
   CHECK(new_root != root);
   CHECK(new_root->getChild(0) != child_node);
   
   std::string new_name = OSG::getName(new_root);
   CHECK(new_name == "root");   
}
