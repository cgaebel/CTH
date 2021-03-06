#include "stdafx.h"

#include "Types.h"
#include "Test.h"
#include "TestContext.h"

#include "Timer.h"
#include "Utilities.h"
#include "Output.h"

#include "TestRunner.h"
#include "TestAdder.h"

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
		void (__cdecl* testFunction)(TestContext&))
	{
		AddTestToList(
			tests,
			DefaultTestContext(testName, fileName, lineNumber, testFunction));
		return 0;
	}

	int TEST_API RunAllTests()
	{
		try
		{
			long testTime = TimeLambda([]{ RunTestsInParallel(tests); });

			for_each_test(tests, PrintAllFailures);

			size_t numberOfFailedTests = GetNumberOfFailedTests(tests);
			PrintSummary(tests, numberOfFailedTests, testTime);
			return static_cast<int>(numberOfFailedTests);
		}
		catch(...)
		{
			printf("%s",
				"Unhandled exception occured in one of the tests!\n"
				"Please re-run the tests in a debugger."
			);

			return -1;
		}
	}
}
