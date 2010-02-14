#include "stdafx.h"
#include "Output.h"

using namespace std;

namespace Test
{
	static size_t GetNumberOfTests(const OuterTestList& tests)
	{
		size_t count = 0;

		for_each(tests.begin(), tests.end(),
		[&count](const pair<string, InnerTestList>& testList)
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

	void PrintAllFailures(const DefaultTestContext& test)
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

	void PrintSummary(
		const OuterTestList& tests,
		size_t returnCode,
		long lengthOfTest)
	{
		if(returnCode == 0)
		{
			size_t numberOfTests = GetNumberOfTests(tests);
			printf("%d unit %s passed.", numberOfTests, GetPluralOfTestIfNecessary(numberOfTests));
		}
		else
		{
			printf("%d unit %s failed.", returnCode, GetPluralOfTestIfNecessary(returnCode));
		}

		printf("\nTest time: %i ms.", lengthOfTest);
	}
}
