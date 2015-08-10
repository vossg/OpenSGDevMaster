
#include "OSGBaseInitFunctions.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainer.h"

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);

    OSG::DerivedFieldContainerTypeIterator dtIt = 
        OSG::FieldContainerFactory::the()->begin(
            OSG::FieldContainer::getClassType());

    OSG::DerivedFieldContainerTypeIterator dtEnd = 
        OSG::FieldContainerFactory::the()->end();

    while(dtIt != dtEnd)
    {
        fprintf(stderr, "foo %p %s\n", 
                static_cast<void *>(*dtIt), (*dtIt)->getCName());

        ++dtIt;
    }
    
    return 0;
}
