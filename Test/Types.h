#pragma once
#include "stdafx.h"
#include "TestContext.h"

namespace Test
{
	typedef stdext::hash_map<
			std::string, std::list<DefaultTestContext>
		> CompleteTestList;
}
