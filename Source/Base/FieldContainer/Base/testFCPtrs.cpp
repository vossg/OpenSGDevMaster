
#include <OSGBaseInitFunctions.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
//#include <OSGRefPtr.h>


int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);


    // Test getting pointers
    OSG::NodeRecPtr node_ptr = OSG::Node::create();
#ifdef OSG_MT_FIELDCONTAINERPTRX
    OSG::Node* node_cptr = get_pointer(node_ptr);
#else
//    OSG::Node* node_cptr = node_ptr;
#endif
    
#ifdef OSG_MT_FIELDCONTAINERPTRX
    OSG::NodeRecPtr node_rptr(OSG::Node::create());
    node_cptr = get_pointer(node_rptr);
#endif

   // Test Weak ref count ptrs
   {
      OSG::NodeRecPtr node_ptr(OSG::Node::create());
      OSG::NodeWeakPtr node_weak(node_ptr);
      OSG_ASSERT(NULL != node_ptr);
      OSG_ASSERT(NULL != node_weak);

      node_ptr = NULL;

      OSG_ASSERT(NULL == node_ptr);
      OSG_ASSERT(NULL == node_weak);
    }

   {
      OSG::NodeMTRecPtr node_ptr(OSG::Node::create());
      OSG::NodeMTWeakPtr node_weak(node_ptr);
      OSG_ASSERT(NULL != node_ptr);
      OSG_ASSERT(NULL != node_weak);

      node_ptr = NULL;

      OSG_ASSERT(NULL == node_ptr);
      OSG_ASSERT(NULL == node_weak);
    }

    node_ptr = NULL;
}
