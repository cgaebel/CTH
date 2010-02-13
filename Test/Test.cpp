#include "stdafx.h"

#include "Test.h"
#include "TestContext.h"

#include "Timer.h"

using namespace std;
using namespace Concurrency;

namespace Test
{
	static void RunTestsInParallel(vector<DefaultTestContext>& list)
	{
		parallel_for_each(list.begin(), list.end(),
			[](DefaultTestContext& currentTest)
			{
				currentTest.testFunction(currentTest);
			}
		);
	}

	static void PrintAllFailures(const DefaultTestContext& test)
	{
		for(auto i = test.failures.begin(); i != test.failures.end(); ++i)
		{
			printf(
				"%s(%d): error: Failure in %s: %s\n",
				test.fileName, i->lineNumber,
				test.testName, i->message);
		}
	}

	static int GetReturnCode(const vector<DefaultTestContext>& tests)
	{
		int returnCode = 0;

		for_each(tests.begin(), tests.end(),
			[&returnCode](const DefaultTestContext& test)
			{
				if(!test.failures.empty())
					++returnCode;
			});

		return returnCode;
	}

	static void PrintSummary(
		const vector<DefaultTestContext>& tests,
		int returnCode,
		long lengthOfTest)
	{
		if(returnCode == 0)
			printf("%d unit tests passed.", tests.size());
		else
			printf("%d unit tests failed.", returnCode);

		printf("\nTest time: %i ms.", lengthOfTest);
	}

	static vector<DefaultTestContext> tests;

	const int TEST_API AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (*testFunction)(TestContext&))
	{
		tests.push_back(DefaultTestContext(testName, fileName, lineNumber, testFunction));
		return 0;
	}

	int TEST_API RunAllTests()
	{
		long lengthOfTest = TimeFunction([](){ RunTestsInParallel(tests); });

		for_each(tests.begin(), tests.end(), PrintAllFailures);

		int returnCode = GetReturnCode(tests);
		PrintSummary(tests, returnCode, lengthOfTest);
		return GetReturnCode(tests);
	}
}
