#include "stdafx.h"
#include "TestAdder.h"

namespace Test
{
	bool AddTestPredicate(const DefaultTestContext&);

	void AddTestToList(
		OuterTestList& testList,
		const DefaultTestContext& toAdd)
	{
		if(AddTestPredicate(toAdd))
			testList[toAdd.fileName].push_back(toAdd);
	}
}
