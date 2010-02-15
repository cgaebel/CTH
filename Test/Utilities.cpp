#include "stdafx.h"
#include "Utilities.h"
#include "Types.h"

#include <algorithm>

namespace Test
{
	static bool InnerAccumulator(const DefaultTestContext& currentTest)
	{
		return currentTest.failures.empty() == false;
	}

	static size_t OuterAccumulator(size_t num, const OuterTestListIterator& testList)
	{
		return num + 
			std::count_if(
				testList.second.begin(),
				testList.second.end(),
				InnerAccumulator);
	}

	size_t GetNumberOfFailedTests(const OuterTestList& tests)
	{
		return std::accumulate(
			tests.begin(), tests.end(),
			static_cast<size_t>(0), 
			OuterAccumulator);
	}
}
