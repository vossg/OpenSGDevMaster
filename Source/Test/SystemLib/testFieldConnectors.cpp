
#include "OSGTestFC.h"
#include "OSGBaseInitFunctions.h"

void dump(OSG::TestFC *pT)
{
    fprintf(stderr, "%d %d\n", 
            pT->getSFField2()->getValue(),
            pT->getSFField4()->getValue());
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

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
