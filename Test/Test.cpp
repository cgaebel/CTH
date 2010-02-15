#include "stdafx.h"

#include "Types.h"
#include "Test.h"
#include "TestContext.h"

#include "Timer.h"
#include "Utilities.h"
#include "Output.h"
#include "TestRunner.h"

namespace Test
{
	// ALERT!!! GLOBAL VARIABLE SPOTTED!
	// Actually, this is our only one. This little sucker represents the
	// global test list that all tests are registered in to. In this case,
	// I think a global variable is appropriate.
	static OuterTestList tests;

	const int TEST_API AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (*testFunction)(TestContext&))
	{
		tests[fileName].push_back(DefaultTestContext(testName, fileName, lineNumber, testFunction));
		return 0;
	}

	int TEST_API RunAllTests()
	{
		long testTime = TimeLambda([](){ RunTestsInParallel(tests); });

		for_each_test(tests, PrintAllFailures);

		size_t numberOfFailedTests = GetNumberOfFailedTests(tests);
		PrintSummary(tests, numberOfFailedTests, testTime);
		return static_cast<int>(numberOfFailedTests);
	}
}
