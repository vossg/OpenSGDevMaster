CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(UnitTestCPP)

SET(LIB_NAME  "UnitTest++")
SET(TEST_NAME "TestUnitTest++")

SET(LIB_SOURCE_FILES    "UnitTest++/src/AssertException.cpp"
                        "UnitTest++/src/Test.cpp"
                        "UnitTest++/src/Checks.cpp"
                        "UnitTest++/src/TestRunner.cpp"
                        "UnitTest++/src/TestResults.cpp"
                        "UnitTest++/src/TestReporter.cpp"
                        "UnitTest++/src/TestReporterStdout.cpp"
                        "UnitTest++/src/ReportAssert.cpp"
                        "UnitTest++/src/TestList.cpp"
                        "UnitTest++/src/TimeConstraint.cpp"
                        "UnitTest++/src/TestDetails.cpp"
                        "UnitTest++/src/MemoryOutStream.cpp"
                        "UnitTest++/src/DeferredTestReporter.cpp"
                        "UnitTest++/src/DeferredTestResult.cpp"
                        "UnitTest++/src/XmlTestReporter.cpp"
                        "UnitTest++/src/CurrentTest.cpp")

SET(TEST_SOURCE_FILES   "UnitTest++/src/tests/Main.cpp"
                        "UnitTest++/src/tests/TestAssertHandler.cpp"
                        "UnitTest++/src/tests/TestChecks.cpp"
                        "UnitTest++/src/tests/TestUnitTest++.cpp"
                        "UnitTest++/src/tests/TestTest.cpp"
                        "UnitTest++/src/tests/TestTestResults.cpp"
                        "UnitTest++/src/tests/TestTestRunner.cpp"
                        "UnitTest++/src/tests/TestCheckMacros.cpp"
                        "UnitTest++/src/tests/TestTestList.cpp"
                        "UnitTest++/src/tests/TestTestMacros.cpp"
                        "UnitTest++/src/tests/TestTimeConstraint.cpp"
                        "UnitTest++/src/tests/TestTimeConstraintMacro.cpp"
                        "UnitTest++/src/tests/TestMemoryOutStream.cpp"
                        "UnitTest++/src/tests/TestDeferredTestReporter.cpp"
                        "UnitTest++/src/tests/TestXmlTestReporter.cpp"
                        "UnitTest++/src/tests/TestCurrentTest.cpp")


IF(WIN32)
    LIST(APPEND LIB_SOURCE_FILES "UnitTest++/src/Win32/TimeHelpers.cpp")
ELSE(WIN32)
    LIST(APPEND LIB_SOURCE_FILES "UnitTest++/src/Posix/SignalTranslator.cpp"
                                 "UnitTest++/src/Posix/TimeHelpers.cpp")
ENDIF(WIN32)

ADD_LIBRARY(${LIB_NAME} STATIC ${LIB_SOURCE_FILES})

ADD_EXECUTABLE(${TEST_NAME} ${TEST_SOURCE_FILES})

TARGET_LINK_LIBRARIES(${TEST_NAME} ${LIB_NAME})

