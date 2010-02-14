#pragma once
#include "Types.h"

namespace Test
{
	void PrintAllFailures(const DefaultTestContext& test);
	void PrintSummary(const CompleteTestList& tests, size_t returnCode, long lengthOfTest);
}
