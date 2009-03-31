
#include <UnitTest++.h>
#include <TestReporterStdout.h>

#include <OSGConfig.h>
#include <OSGBaseInitFunctions.h>

int main(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);

    return UnitTest::RunAllTests();

//     UnitTest::TestReporterStdout rep;
//     return UnitTest::RunAllTests(rep, UnitTest::Test::GetTestList(), argv[1]);
}
