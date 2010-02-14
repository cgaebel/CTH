#include "stdafx.h"
#include "Utilities.h"

namespace Test
{
	int GetNumberOfFailedTests(const OuterTestList& tests)
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
}
