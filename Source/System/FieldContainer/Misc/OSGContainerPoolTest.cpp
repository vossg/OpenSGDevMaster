
#include <UnitTest++.h>

// Unit tests for vec classes

#include <OpenSG/OSGContainerPool.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGBlendChunk.h>

#include <OpenSG/OSGNameAttachment.h>


TEST(CreatePool)
{
   OSG::ContainerPoolPtr cp = OSG::ContainerPool::create();
   CHECK(cp != OSG::NullFC);
}


TEST(UsePool)
{
   OSG::ContainerPoolPtr cp = OSG::ContainerPool::create();
   CHECK(cp != OSG::NullFC);
   
   OSG::TransformPtr t = OSG::Transform::create();
   OSG::NodePtr n = OSG::Node::create();
   OSG::BlendChunkPtr bc = OSG::BlendChunk::create();
   
   cp->addContainer(t);
   cp->addContainer(n);   
   cp->addContainer(bc);
   
   CHECK(cp->getContainers().size() == 3);
   
   OSG::FieldContainerPtr t_ptr = cp->getContainers(0);
   OSG::FieldContainerPtr n_ptr = cp->getContainers(1);
   OSG::FieldContainerPtr bc_ptr = cp->getContainers(2);
   
   CHECK(true);
   
/*
   // Enable after subContainer is implemented.
   bool ret_val = cp->subContainer(t);
   CHECK(ret_val);
   CHECK(cp->getContainers().size() == 2);
   
   ret_val = cp->subContainer(n);
   CHECK(ret_val);
   CHECK(cp->getContainers().size() == 1);
   
   ret_val = cp->subContainer(bc);
   CHECK(ret_val);
   CHECK(cp->getContainers().size() == 0);
   */
   
}

