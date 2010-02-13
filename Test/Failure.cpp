#include "stdafx.h"
#include "Test.h"

namespace Test
{
	Failure::Failure(const char* _fileName, const char* _message, const int _lineNumber)
	{
		fileName = _fileName;
		message = _message;
		lineNumber = _lineNumber;
	}
}
