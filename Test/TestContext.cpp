#include "stdafx.h"
#include "Test.h"

#include "TestContext.h"
#include "Failure.h"

namespace Test
{
	DefaultTestContext::DefaultTestContext(
		const char* _testName,
		const char* _fileName,
		const int _lineNumber,
		void (__cdecl* _testFunction)(TestContext&))
	{
		testName = _testName;
		fileName = _fileName;
		lineNumber = _lineNumber;
		testFunction = _testFunction;
	}

	DefaultTestContext::DefaultTestContext(const DefaultTestContext& other)
	{
		testName = other.testName;
		fileName = other.fileName;
		lineNumber = other.lineNumber;
		testFunction = other.testFunction;
	}

	DefaultTestContext& DefaultTestContext::operator=(const DefaultTestContext& other)
	{
		testName = other.testName;
		fileName = other.fileName;
		lineNumber = other.lineNumber;
		testFunction = other.testFunction;

		return *this;
	}

	void DefaultTestContext::AddFailure(int lineNumber, const std::string& message)
	{
		failures.push_back(Failure(message, lineNumber));
	}
}
