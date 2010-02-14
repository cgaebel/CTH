#include "stdafx.h"

#include "Test.h"

#include "TestContext.h"
#include "Failure.h"

#include "Timer.h"

using namespace std;
using namespace stdext;
using namespace Concurrency;

namespace Test
{
	typedef hash_map<string, list<DefaultTestContext>> CompleteTestList;

	// The lambda must take a DefaultTestContext& as a parameter.
	template <typename LambdaType>
	static void for_each_test(CompleteTestList& testList, LambdaType functor)
	{
		for_each(testList.begin(), testList.end(),
		[&functor](pair<string, list<DefaultTestContext>> currentTestList)
		{
			auto innerFunctor = functor;

			for_each(currentTestList.second.begin(), currentTestList.second.end(),
			[&innerFunctor](DefaultTestContext& test)
			{
				innerFunctor(test);
			});
		});
	}

	// The lambda must take a const DefaultTestContext& as a parameter.
	template <typename LambdaType>
	static void for_each_test(const CompleteTestList& testList, LambdaType functor)
	{
		for_each(testList.begin(), testList.end(),
		[&functor](const pair<string, list<DefaultTestContext>> currentTestList)
		{
			auto innerFunctor = functor;

			for_each(currentTestList.second.begin(), currentTestList.second.end(),
			[&innerFunctor](const DefaultTestContext& test)
			{
				innerFunctor(test);
			});
		});
	}

	static void RunTestsInParallel(CompleteTestList& testList)
	{
		parallel_for_each(testList.begin(), testList.end(),
		[](pair<string, list<DefaultTestContext>> currentTestList)
		{
			for_each(currentTestList.second.begin(), currentTestList.second.end(),
			[](DefaultTestContext& currentTest)
			{
				currentTest.testFunction(currentTest);
			});
		});
	}

	static void PrintAllFailures(const DefaultTestContext& test)
	{
		for_each(test.failures.begin(), test.failures.end(),
		[&test](const Failure& failure)
		{
			printf(
				"%s(%d): error: Failure in %s: %s\n",
				test.fileName, failure.lineNumber,
				test.testName, failure.message
			);
		});
	}

	static int GetNumberOfFailedTests(const CompleteTestList& tests)
	{
		int returnCode = 0;

		for_each_test(tests,
		[&returnCode](const DefaultTestContext& currentTest)
		{
			if(!currentTest.failures.empty())
				++returnCode;
		});

		return returnCode;
	}

	static size_t GetNumberOfTests(const CompleteTestList& tests)
	{
		size_t count = 0;

		for_each(tests.begin(), tests.end(),
		[&count](const pair<string, list<DefaultTestContext>>& testList)
		{
			count += testList.second.size();
		});

		return count;
	}

	static const char* GetPluralOfTestIfNecessary(size_t number)
	{
		if(number == 1)
			return "test";
		else
			return "tests";
	}

	static void PrintSummary(
		const CompleteTestList& tests,
		size_t returnCode,
		long lengthOfTest)
	{
		if(returnCode == 0)
		{
			size_t numberOfTests = GetNumberOfTests(tests);

			printf("%d unit %s passed.", numberOfTests, GetPluralOfTestIfNecessary(numberOfTests));
		}
		else
			printf("%d unit %s failed.", returnCode, GetPluralOfTestIfNecessary(returnCode));

		printf("\nTest time: %i ms.", lengthOfTest);
	}

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
