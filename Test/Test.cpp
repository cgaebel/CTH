#include "stdafx.h"

#include "Types.h"
#include "Test.h"
#include "TestContext.h"
#include "Failure.h"

#include "Timer.h"
#include "Utilities.h"
#include "Output.h"
#include "TestRunner.h"

namespace Test
{
	static CompleteTestList tests;

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

		size_t returnCode = GetNumberOfFailedTests(tests);
		PrintSummary(tests, returnCode, testTime);
		return (int)returnCode;
	}
}
