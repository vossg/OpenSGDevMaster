
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
}

