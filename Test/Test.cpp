#include "stdafx.h"
#include "Test.h"

using namespace std;
using namespace Concurrency;

namespace Test
{
	static vector<TestContext> ConvertListToVector(const Utilities::LinkedList<TestContext>& list)
	{
		vector<TestContext> retVal;

		for(auto i = list.begin(); i != list.end(); ++i)
			retVal.push_back(*i);

		return retVal;
	}

	static void RunTestsInParallel(vector<TestContext>& list)
	{
		parallel_for_each(list.begin(), list.end(),
			[](TestContext& currentTest)
			{
				currentTest.testFunction(currentTest);
			}
		);
	}

	static void PrintAllFailures(const TestContext& test)
	{
		for(auto i = test.failures.begin(); i != test.failures.end(); ++i)
		{
			printf(
				"%s(%d): error: Failure in %s: %s\n",
				i->fileName, i->lineNumber,
				test.testName, i->message);
		}
	}

	static Utilities::LinkedList<TestContext> allTests;

	int RunAllTests()
	{
		vector<TestContext> tests = ConvertListToVector(allTests);
		RunTestsInParallel(tests);
		
		for_each(tests.begin(), tests.end(), PrintAllFailures);

		return 0;
	}

	int AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (__cdecl* testFunction)(const ::Test::TestContext&))
	{
		allTests.Push(TestContext(testName, fileName, lineNumber, testFunction));
		return 0;
	}

}
