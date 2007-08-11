#include <UnitTest++.h>
#include <TestReporterStdout.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseInitFunctions.h>

int main(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);
    
    if(argc < 2)
        return UnitTest::RunAllTests();
    
    UnitTest::TestReporterStdout rep;
    
    return UnitTest::RunAllTests(rep, UnitTest::Test::GetTestList(), argv[1]);
}
