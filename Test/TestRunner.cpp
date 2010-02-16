#include "stdafx.h"
#include "TestRunner.h"
#include "Types.h"

using namespace std;
using namespace Concurrency;

namespace Test
{
	void PreTest(DefaultTestContext& test);
	void PostTest(DefaultTestContext& test);

	static void RunTest(DefaultTestContext& toRun)
	{
		PreTest(toRun);
		toRun.testFunction(toRun);
		PostTest(toRun);
	}

	static void RunMappedTests(OuterTestListIterator& tests)
	{
		for_each(tests.second.begin(), tests.second.end(), RunTest);
	}
	
	void RunTestsInParallel(OuterTestList& testList)
	{
		parallel_for_each(testList.begin(), testList.end(), RunMappedTests);
	}
}
