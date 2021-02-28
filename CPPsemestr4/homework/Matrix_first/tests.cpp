/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_MyTest_init = false;
#include "tests.h"

static MyTest suite_MyTest;

static CxxTest::List Tests_MyTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTest( "tests.h", 3, "MyTest", suite_MyTest, Tests_MyTest );

static class TestDescription_suite_MyTest_testGetSetNumber : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testGetSetNumber() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 7, "testGetSetNumber" ) {}
 void runTest() { suite_MyTest.testGetSetNumber(); }
} testDescription_suite_MyTest_testGetSetNumber;

static class TestDescription_suite_MyTest_testGetRowsColumnsSize : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testGetRowsColumnsSize() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 25, "testGetRowsColumnsSize" ) {}
 void runTest() { suite_MyTest.testGetRowsColumnsSize(); }
} testDescription_suite_MyTest_testGetRowsColumnsSize;

static class TestDescription_suite_MyTest_testMatrixEquel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testMatrixEquel() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 35, "testMatrixEquel" ) {}
 void runTest() { suite_MyTest.testMatrixEquel(); }
} testDescription_suite_MyTest_testMatrixEquel;

static class TestDescription_suite_MyTest_testAssigmentPlus : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testAssigmentPlus() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 56, "testAssigmentPlus" ) {}
 void runTest() { suite_MyTest.testAssigmentPlus(); }
} testDescription_suite_MyTest_testAssigmentPlus;

static class TestDescription_suite_MyTest_testMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testMultiplication() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 91, "testMultiplication" ) {}
 void runTest() { suite_MyTest.testMultiplication(); }
} testDescription_suite_MyTest_testMultiplication;

static class TestDescription_suite_MyTest_testIndexOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testIndexOperator() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 129, "testIndexOperator" ) {}
 void runTest() { suite_MyTest.testIndexOperator(); }
} testDescription_suite_MyTest_testIndexOperator;

static class TestDescription_suite_MyTest_testPointer : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testPointer() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 147, "testPointer" ) {}
 void runTest() { suite_MyTest.testPointer(); }
} testDescription_suite_MyTest_testPointer;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
