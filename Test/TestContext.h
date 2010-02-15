#pragma once
#include "stdafx.h"
#include "Test.h"
#include "Failure.h"

namespace Test
{
	class DefaultTestContext : public TestContext
	{
	public:
		const char* testName;
		const char* fileName;
		int lineNumber;
		void (*testFunction)(TestContext&);

		std::list<Failure> failures;

	public:
		inline DefaultTestContext()
		{
		}

		DefaultTestContext(
			const char* testName,
			const char* fileName,
			const int lineNumber,
			void (*testFunction)(TestContext&));

		DefaultTestContext(const DefaultTestContext& other);
		DefaultTestContext& operator=(const DefaultTestContext& other);

		void AddFailure(int lineNumber, const std::string& message);
	};
}
