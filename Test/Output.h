#pragma once
#include "Types.h"

namespace Test
{
	void PrintAllFailures(const DefaultTestContext& test);
	void PrintSummary(const OuterTestList& tests, size_t returnCode, long lengthOfTest);
}
