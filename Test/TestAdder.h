#pragma once
#include "Types.h"
#include "TestContext.h"

namespace Test
{
	void AddTestToList(
		OuterTestList& testList,
		const DefaultTestContext& toAdd);
}
