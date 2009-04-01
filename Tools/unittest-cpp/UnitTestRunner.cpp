
#include <UnitTest++.h>
#include <TestReporterStdout.h>

#include <OSGConfig.h>
#include <OSGBaseInitFunctions.h>

struct TestNameEquals
{
	TestNameEquals(const std::string &testName)
		: _testName(testName)
	{
	}

	bool operator()(const UnitTest::Test * const test) const
	{
		return (_testName == test->m_details.testName);
	}

	std::string _testName;
};

int main(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);

	int retVal = -1;

	if(argc > 1)
	{
		TestNameEquals               pred(argv[1]);
		UnitTest::TestReporterStdout rep;
		UnitTest::TestRunner         runner(rep);

		retVal = runner.RunTestsIf(
			UnitTest::Test::GetTestList(), NULL, pred, 0);
	}
	else
	{
		retVal = UnitTest::RunAllTests();
	}

	OSG::osgExit();

    return retVal;
}
