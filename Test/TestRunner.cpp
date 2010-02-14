#include "stdafx.h"
#include "TestRunner.h"
#include "Types.h"

using namespace std;
using namespace Concurrency;

namespace Test
{
	static void RunTest(DefaultTestContext& toRun)
	{
		toRun.testFunction(toRun);
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
