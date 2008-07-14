
#include "OSGTestFC.h"
#include "OSGBaseInitFunctions.h"

void dump(OSG::TestFC *pT)
{
    fprintf(stderr, "%d %d\n", 
            pT->getSFField2()->getValue(),
            pT->getSFField4()->getValue());
}

void testSimple(void)
{
    OSG::TestFCUnrecPtr pT1 = OSG::TestFC::create();
    OSG::TestFCUnrecPtr pT2 = OSG::TestFC::create();

    OSG::Thread::getCurrentChangeList()->clear();
    
    dump(pT1);
    dump(pT2);

    addConnection(pT1, "field2",
                  pT2, "field4");

    pT1->editSFField2()->setValue(42);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);

    pT1 = NULL;
    pT2 = NULL;
}

void testTargetDestroyed(void)
{
    OSG::TestFCUnrecPtr pT1 = OSG::TestFC::create();
    OSG::TestFCUnrecPtr pT2 = OSG::TestFC::create();

    OSG::Thread::getCurrentChangeList()->clear();
    
    dump(pT1);
    dump(pT2);

    addConnection(pT1, "field2",
                  pT2, "field4");

    pT1->editSFField2()->setValue(42);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);

    pT2 = NULL;

    pT1->editSFField2()->setValue(1199);

    OSG::commitChanges();

    pT1 = NULL;
}

void testSubConnection(void)
{
    OSG::TestFCUnrecPtr pT1 = OSG::TestFC::create();
    OSG::TestFCUnrecPtr pT2 = OSG::TestFC::create();

    OSG::Thread::getCurrentChangeList()->clear();
    
    dump(pT1);
    dump(pT2);

    addConnection(pT1, "field2",
                  pT2, "field4");

    pT1->editSFField2()->setValue(42);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);

    subConnection(pT1, "field2",
                  pT2, "field4");


    pT1->editSFField2()->setValue(1199);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);


    pT1 = NULL;
    pT2 = NULL;
}

void testSubConnectionSrcOnly(void)
{
    OSG::TestFCUnrecPtr pT1 = OSG::TestFC::create();
    OSG::TestFCUnrecPtr pT2 = OSG::TestFC::create();

    OSG::Thread::getCurrentChangeList()->clear();
    
    dump(pT1);
    dump(pT2);

    addConnection(pT1, "field2",
                  pT2, "field4");

    pT1->editSFField2()->setValue(42);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);

    subConnection(pT1, "field2",
                  NULL, NULL);


    pT1->editSFField2()->setValue(1199);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);


    pT1 = NULL;
    pT2 = NULL;
}

void testSubConnectionSrcAll(void)
{
    OSG::TestFCUnrecPtr pT1 = OSG::TestFC::create();
    OSG::TestFCUnrecPtr pT2 = OSG::TestFC::create();

    OSG::Thread::getCurrentChangeList()->clear();
    
    dump(pT1);
    dump(pT2);

    addConnection(pT1, "field2",
                  pT2, "field4");

    pT1->editSFField2()->setValue(42);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);

    subConnection(pT1, "field2",
                  NULL, NULL);


    pT1->editSFField2()->setValue(1199);

    OSG::commitChanges();

    dump(pT1);
    dump(pT2);


    pT1 = NULL;
    pT2 = NULL;
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    fprintf(stderr, "TestSimple\n");
    testSimple();

    fprintf(stderr, "TestTargetDestroyed\n");
    testTargetDestroyed();

    fprintf(stderr, "TestSubConnection\n");
    testSubConnection();

    fprintf(stderr, "TestSubConnectionSrcOnly\n");
    testSubConnectionSrcOnly();

    fprintf(stderr, "TestSubConnectionSrcAll\n");
    testSubConnectionSrcAll();
}
