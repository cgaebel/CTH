#pragma once

namespace Test
{
	struct Failure
	{
		const char* message;
		int lineNumber;

		inline Failure()
		{
		}

		Failure(const char* message, const int lineNumber);
	};
}
