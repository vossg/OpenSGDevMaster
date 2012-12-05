
#include "OSGBaseInitFunctions.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"

#include "boost/bind.hpp"

class Foo
{
  public:

    void testCB(OSG::FieldContainer *pObj, OSG::BitVector whichField, OSG::UInt32 origin)
    {
        fprintf(stderr, "Foo::testCB %" PRIx64 " origin %u\n", 
                whichField, origin);
    }
};

void testCB(OSG::FieldContainer *pObj, OSG::BitVector whichField, OSG::UInt32 origin)
{
    fprintf(stderr, "testCB %" PRIx64 " origin %u\n", whichField, origin);
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    Foo foo;

    OSG::Thread::getCurrentChangeList()->clear();

    OSG::NodeRecPtr pNode = OSG::Node::create();

    OSG::ChangedFunctor objCB = boost::bind(&Foo::testCB, &foo, _1, _2, _3);

    pNode->addChangedFunctor(testCB, "");
    pNode->addChangedFunctor(objCB, "");

    pNode->setTravMask(0);

    fprintf(stderr, "Test 1\n");
    OSG::Thread::getCurrentChangeList()->commitChanges();
   


    pNode->addChangedFunctor(testCB, "");

    pNode->setTravMask(1);

    fprintf(stderr, "Test 2 \n");
    OSG::Thread::getCurrentChangeList()->commitChanges();



    pNode->subChangedFunctor(testCB);

    pNode->setTravMask(1);

    fprintf(stderr, "Test 3\n");
    OSG::Thread::getCurrentChangeList()->commitChanges();

    
    pNode->addChangedFunctor(testCB, "");

    pNode->setTravMask(1);

    fprintf(stderr, "Test 4 \n");
    OSG::Thread::getCurrentChangeList()->commitChanges();


    pNode->subChangedFunctor(testCB);

    pNode->setTravMask(1);

    fprintf(stderr, "Test 5\n");
    OSG::Thread::getCurrentChangeList()->commitChanges();

    fprintf(stderr, "Delete\n");
    pNode = NULL;
}
