#include "stdafx.h"
#include "Test.h"

namespace Test
{
	namespace Utilities
	{
		int custom_strcmp(const char* str1, const char* str2)
		{
			for(int i = 0;; ++i)
			{
				if(str1[i] != str2[i])
					return (str1[i] > str2[i]) ? 1 : -1;

				if(str1[i] == '\0')
					return 0;
			}
		}
	}
}
