#pragma once
#include <string>

namespace Test
{
	struct Failure
	{
		std::string message;
		int lineNumber;

		inline Failure()
		{
		}

		Failure(const std::string& message, const int lineNumber);
	};
}
