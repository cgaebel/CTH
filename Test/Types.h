#pragma once
#include <list>
#include <string>
#include <unordered_map>

#include "TestContext.h"

namespace Test
{
	typedef std::list<DefaultTestContext> InnerTestList;
	typedef std::unordered_map<std::string, InnerTestList> OuterTestList;
	typedef std::pair<const std::string, InnerTestList> OuterTestListIterator;
}
