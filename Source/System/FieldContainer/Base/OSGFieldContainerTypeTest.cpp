
#include <UnitTest++.h>

// Unit tests for vec classes

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>
#include <string>


TEST(CreateType)
{
   OSG::NodePtr n = OSG::Node::create();
   OSG::FieldContainerType& n_type(n->getType());
   CHECK(n != OSG::NullFC);
}

TEST(GetDocs)
{
   OSG::TransformPtr tc = OSG::Transform::create();
   OSG::FieldContainerType& transform_type = tc->getType();
   
   std::string fcd_xml = transform_type.getFcdXML();
   CHECK(fcd_xml != "");
   
   std::string class_docs = transform_type.getDocumentation();
   CHECK(class_docs != "");
}

TEST(GetFieldDocs)
{
   OSG::TransformPtr tc = OSG::Transform::create();
   OSG::FieldContainerType& transform_type(tc->getType());
   
   unsigned num_field_descs = transform_type.getNumFieldDescs();
   
   for(unsigned i; i<num_field_descs; ++i)
   {
      OSG::FieldDescriptionBase* fdesc = transform_type.getFieldDesc(i);
      std::string field_doc = fdesc->getDocumentation();
      CHECK(true);      
   }
}


