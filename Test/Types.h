#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "TestContext.h"

namespace Test
{
	typedef std::vector<DefaultTestContext> InnerTestList;
	typedef std::unordered_map<std::string, InnerTestList> OuterTestList;
	typedef std::pair<const std::string, InnerTestList> OuterTestListIterator;
}
