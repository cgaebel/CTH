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
		void (__cdecl* testFunction)(TestContext&);

		typedef std::vector<Failure> FailureList;

		FailureList failures;

	public:
		inline DefaultTestContext()
		{
		}

		DefaultTestContext(
			const char* testName,
			const char* fileName,
			const int lineNumber,
			void (__cdecl* testFunction)(TestContext&));

		DefaultTestContext(const DefaultTestContext& other);
		DefaultTestContext& operator=(const DefaultTestContext& other);

		void AddFailure(int lineNumber, const std::string& message);
	};
}
