
#include <OSGBaseInitFunctions.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
//#include <OSGRefPtr.h>


int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);


    // Test getting pointers
    OSG::NodeRefPtr node_ptr = OSG::Node::create();
#ifdef OSG_MT_FIELDCONTAINERPTRX
    OSG::Node* node_cptr = get_pointer(node_ptr);
#else
    OSG::Node* node_cptr = node_ptr;
#endif
    
#ifdef OSG_MT_FIELDCONTAINERPTRX
    OSG::NodeRefPtr node_rptr(OSG::Node::create());
    node_cptr = get_pointer(node_rptr);
#endif

    node_ptr = NullFC;
}
