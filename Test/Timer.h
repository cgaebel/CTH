#pragma once
#include <ctime>

// Takes a functor to execute, and returns how long it took
// to return in milliseconds.
template <typename LambdaType>
long TimeFunction(const LambdaType& functor)
{
	const clock_t CLOCKS_PER_MILLISECOND = CLOCKS_PER_SEC / 1000;

	clock_t begin, end;

	begin = clock();
	functor();
	end = clock();

	return (end - begin) * CLOCKS_PER_MILLISECOND;
}
