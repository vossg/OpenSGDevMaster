
#include <OSGBaseInitFunctions.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGRefPtr.h>


int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);


    // Test getting pointers
    OSG::NodePtr node_ptr = OSG::Node::create();
    OSG::Node* node_cptr = get_pointer(node_ptr);
    
    OSG::NodeRefPtr node_rptr(OSG::Node::create());
    node_cptr = get_pointer(node_rptr);

}
