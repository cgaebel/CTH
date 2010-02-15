#include "stdafx.h"
#include "Failure.h"

namespace Test
{
	Failure::Failure(std::string _message, const int _lineNumber)
		: message(_message)
	{
		lineNumber = _lineNumber;
	}
}
