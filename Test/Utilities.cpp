#include "stdafx.h"
#include "Test.h"

namespace Test
{
	namespace Utilities
	{
		static int custom_strcmp(const char* str1, const char* str2)
		{
			for(int i = 0;; ++i)
			{
				if(str1[i] != str2[i])
					return (str1[i] > str2[i]) ? 1 : -1;

				if(str1[i] == '\0')
					return 0;
			}
		}

		template <>
		bool TEST_API AreEqual(char* expected, char* actual)
		{
			return custom_strcmp(expected, actual) == 0;
		}

		template <>
		bool TEST_API AreEqual(const char* expected, const char* actual)
		{
			return custom_strcmp(expected, actual) == 0;
		}
	}
}
