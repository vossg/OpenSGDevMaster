#include <UnitTest++.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseInitFunctions.h>

int main(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);
    
    return UnitTest::RunAllTests();
}
