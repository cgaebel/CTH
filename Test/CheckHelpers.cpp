#include "stdafx.h"
#include "Test.h"

namespace Test
{
	namespace CheckHelpers
	{
		static bool InnerAreEqual(const char* expected, const char* actual)
		{
			return strcmp(expected, actual) == 0;
		}

#define MAKE_STRING_EQUAL(typeA, typeB)							\
		bool TEST_API AreEqual(typeA expected, typeB actual)	\
		{														\
			return InnerAreEqual(expected, actual);				\
		}

		MAKE_STRING_EQUAL(char*, char*);
		MAKE_STRING_EQUAL(char*, const char*);
		MAKE_STRING_EQUAL(const char*, char*);
		MAKE_STRING_EQUAL(const char*, const char*);

#undef MAKE_STRING_EQUAL
	}
}
