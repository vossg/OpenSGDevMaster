
#include <OSGBaseInitFunctions.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGRefPtr.h>


int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);


    // Test getting pointers
    OSG::NodePtr node_ptr = OSG::Node::create();
#ifdef OSG_MT_FIELDCONTAINERPTR
    OSG::Node* node_cptr = get_pointer(node_ptr);
#else
    OSG::Node* node_cptr = getCPtr(node_ptr);
#endif
    
    OSG::NodeRefPtr node_rptr(OSG::Node::create());
#ifdef OSG_MT_FIELDCONTAINERPTR
    node_cptr = get_pointer(node_rptr);
#endif
}
