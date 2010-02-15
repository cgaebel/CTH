#include "stdafx.h"
#include "Failure.h"

namespace Test
{
	Failure::Failure(const std::string& _message, const int _lineNumber)
		: message(_message)
	{
		lineNumber = _lineNumber;
	}
}
