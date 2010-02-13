#include "stdafx.h"
#include "Test.h"

namespace Test
{
	Failure::Failure(const char* _message, const int _lineNumber)
	{
		message = _message;
		lineNumber = _lineNumber;
	}
}
