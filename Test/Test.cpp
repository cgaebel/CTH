#include "stdafx.h"
#include "Test.h"

namespace Test
{
	static Utilities::LinkedList<TestContext> allTests;

	int AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (__cdecl* testFunction)(const ::Test::TestContext&))
	{
		allTests.Push(TestContext(testName, fileName, lineNumber, testFunction));
		return 0;
	}

	int RunAllTests()
	{
		/* TODO: WRITE THIS DAMN THING. */
		return 0;
	}
}
