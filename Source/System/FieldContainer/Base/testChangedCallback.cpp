
#include "OSGBaseInitFunctions.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"

#include "boost/bind.hpp"

class Foo
{
  public:

    void testCB(OSG::FieldContainer *pObj, OSG::BitVector whichField)
    {
        fprintf(stderr, "Foo::testCB %llx\n", whichField);
    }
};

void testCB(OSG::FieldContainer *pObj, OSG::BitVector whichField)
{
    fprintf(stderr, "testCB %llx\n", whichField);
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    Foo foo;

    OSG::Thread::getCurrentChangeList()->clear();

    OSG::NodeRecPtr pNode = OSG::Node::create();

    OSG::ChangedFunctor objCB = boost::bind(&Foo::testCB, &foo, _1, _2);

    pNode->addChangedFunctor(testCB, "");
    pNode->addChangedFunctor(objCB, "");

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

    fprintf(stderr, "Delete\n");
    pNode = NULL;
}
