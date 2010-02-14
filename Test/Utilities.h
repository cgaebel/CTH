#pragma once
#include "stdafx.h"
#include "Types.h"
#include "TestContext.h"

namespace Test
{
	// The lambda must take a DefaultTestContext& as a parameter.
	template <typename LambdaType>
	void for_each_test(OuterTestList& testList, LambdaType functor)
	{
		std::for_each(testList.begin(), testList.end(),
		[&functor](OuterTestListIterator& currentTestList)
		{
			auto innerFunctor = functor;

			std::for_each(currentTestList.second.begin(), currentTestList.second.end(),
			[&innerFunctor](DefaultTestContext& test)
			{
				innerFunctor(test);
			});
		});
	}

	// The lambda must take a const DefaultTestContext& as a parameter.
	template <typename LambdaType>
	void for_each_test(const OuterTestList& testList, LambdaType functor)
	{
		std::for_each(testList.begin(), testList.end(),
		[&functor](const OuterTestListIterator& currentTestList)
		{
			auto innerFunctor = functor;

			std::for_each(currentTestList.second.begin(), currentTestList.second.end(),
			[&innerFunctor](const DefaultTestContext& test)
			{
				innerFunctor(test);
			});
		});
	}

	int GetNumberOfFailedTests(const OuterTestList& tests);
}
