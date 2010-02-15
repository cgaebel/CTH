#include "stdafx.h"
#include "Output.h"

using namespace std;

namespace Test
{
	static size_t GetNumberOfTests(const OuterTestList& tests)
	{
		return accumulate(tests.begin(), tests.end(), static_cast<size_t>(0),
		[](size_t currentCount, const OuterTestListIterator& testList)
		{
			return currentCount + testList.second.size();
		});
	}

	static inline const char* GetPluralOfTestIfNecessary(size_t number)
	{
		return (number == 1) ? "test" : "tests";
	}

	void PrintAllFailures(const DefaultTestContext& test)
	{
		for_each(test.failures.begin(), test.failures.end(),
		[&test](const Failure& failure)
		{
			printf(
				"%s(%d): error: Failure in %s: %s\n",
				test.fileName, failure.lineNumber,
				test.testName, failure.message.c_str()
			);
		});
	}

	static void PrintSuccessMessage(const OuterTestList& tests)
	{
		size_t numberOfTests = GetNumberOfTests(tests);
		printf("%d unit %s passed.", numberOfTests, GetPluralOfTestIfNecessary(numberOfTests));
	}

	static void PrintFailureMessage(size_t returnCode)
	{
		printf("%d unit %s failed.", returnCode, GetPluralOfTestIfNecessary(returnCode));
	}

	static void PrintTimingData(long elapsedTime)
	{
		printf("\nTest time: %i ms.", elapsedTime);
	}

	void PrintSummary(
		const OuterTestList& tests,
		size_t returnCode,
		long lengthOfTest)
	{
		if(returnCode == 0)
			PrintSuccessMessage(tests);
		else
			PrintFailureMessage(returnCode);

		PrintTimingData(lengthOfTest);
	}
}
