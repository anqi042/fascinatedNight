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
bool suite_MySuit1_init = false;
#include "/root/cxxtest-4.3/sample/myclass/mysuit1.h"

static MySuit1 suite_MySuit1;

static CxxTest::List Tests_MySuit1 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MySuit1( "sample/myclass/mysuit1.h", 4, "MySuit1", suite_MySuit1, Tests_MySuit1 );

static class TestDescription_suite_MySuit1_test_comp : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MySuit1_test_comp() : CxxTest::RealTestDescription( Tests_MySuit1, suiteDescription_MySuit1, 7, "test_comp" ) {}
 void runTest() { suite_MySuit1.test_comp(); }
} testDescription_suite_MySuit1_test_comp;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
