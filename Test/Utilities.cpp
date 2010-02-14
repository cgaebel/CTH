#include "stdafx.h"
#include "Test.h"

namespace Test
{
	namespace Utilities
	{
		template <>
		bool TEST_API AreEqual(char* expected, char* actual)
		{
			return strcmp(expected, actual) == 0;
		}

		template <>
		bool TEST_API AreEqual(const char* expected, const char* actual)
		{
			return strcmp(expected, actual) == 0;
		}
	}
}
