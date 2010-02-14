#pragma once
#include "stdafx.h"
#include "TestContext.h"

namespace Test
{
	typedef std::list<DefaultTestContext> InnerTestList;
	typedef stdext::hash_map<std::string, InnerTestList> OuterTestList;
	typedef std::pair<const std::string, InnerTestList> OuterTestListIterator;
}
