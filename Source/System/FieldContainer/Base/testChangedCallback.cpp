
#include "OSGBaseInitFunctions.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"


void testCB(OSG::FieldContainerPtr pObj, OSG::BitVector whichField)
{
    fprintf(stderr, "testCB\n");
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::Thread::getCurrentChangeList()->clear();

    OSG::NodePtr pNode = OSG::Node::create();

    pNode->addChangedFunctor(testCB, "");

    pNode->setTravMask(0);

    fprintf(stderr, "Test 1\n");
    OSG::Thread::getCurrentChangeList()->commitChanges();
   


    OSG::UInt32 uiId = pNode->addChangedFunctor(testCB, "");

    pNode->setTravMask(1);

    fprintf(stderr, "Test 2 %d\n", uiId);
    OSG::Thread::getCurrentChangeList()->commitChanges();



    pNode->subChangedFunctor(uiId);

    pNode->setTravMask(1);

    fprintf(stderr, "Test 3\n");
    OSG::Thread::getCurrentChangeList()->commitChanges();

    
    uiId = pNode->addChangedFunctor(testCB, "");

    pNode->setTravMask(1);

    fprintf(stderr, "Test 4 %d\n", uiId);
    OSG::Thread::getCurrentChangeList()->commitChanges();


    pNode->subChangedFunctor(testCB);

    pNode->setTravMask(1);

    fprintf(stderr, "Test 5\n");
    OSG::Thread::getCurrentChangeList()->commitChanges();

}
