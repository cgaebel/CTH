#include "stdafx.h"
#include "TestRunner.h"
#include "Types.h"

using namespace std;
using namespace Concurrency;

namespace Test
{
	void RunTestsInParallel(CompleteTestList& testList)
	{
		parallel_for_each(testList.begin(), testList.end(),
		[](pair<string, list<DefaultTestContext>> currentTestList)
		{
			for_each(currentTestList.second.begin(), currentTestList.second.end(),
			[](DefaultTestContext& currentTest)
			{
				currentTest.testFunction(currentTest);
			});
		});
	}
}
