#include "stdafx.h"
#include "Test.h"

namespace Test
{
	TestContext::TestContext(
		const char* _testName,
		const char* _fileName,
		const int _lineNumber,
		void (*_testFunction)(const TestContext&))
	{
		testName = _testName;
		fileName = _fileName;
		lineNumber = _lineNumber;
		testFunction = _testFunction;
	}

	TestContext::TestContext(const TestContext& other)
	{
		testName = other.testName;
		fileName = other.fileName;
		lineNumber = other.lineNumber;
		testFunction = other.testFunction;
	}

	TestContext& TestContext::operator=(const TestContext& other)
	{
		testName = other.testName;
		fileName = other.fileName;
		lineNumber = other.lineNumber;
		testFunction = other.testFunction;

		return *this;
	}

	void TestContext::AddFailure(const char* fileName, int lineNumber, const char* message)
	{
		failures.Push(Failure(fileName, message, lineNumber));
	}
}
