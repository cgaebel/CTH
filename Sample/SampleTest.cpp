#include "stdafx.h"

// Normally, I would have things like...
//
// #include "../Food/ThingsILikeToEat.h"
// #include "../Food/ThingsILikeToEat.cpp"
//
// instead of inlining the following three functions directly, but I
// think inlining a whole 'nother project is overkill.
bool CanIEat(int numberOfTeeth)
{
	return numberOfTeeth == 32;
}

bool DoILikeToEatApples(int x)
{
	return x == 42;
}

bool DoILikeToEatBananas(int y)
{
	return y == /* Newfags can't... */ 7;
}
// END "SHOULD NOT BE INLINED" FUNCTIONS.


// This test will be executed. You can add more tests! In fact, I suggest
// you do to play around with the whole framework yourself. The best way
// to learn is to do!
TEST(ILikeToEatEatEatApplesAndBananas)
{
	// We use assert macros when it wouldn't make any sense to continue
	// if they fail. In this case, it's pointless to ask wether or not we
	// like to eat "x" if we can't even eat!
	ASSERT_TRUE(CanIEat(32));	// 32 - the number of teeth in an adult human.
	ASSERT_FALSE(CanIEat(0));	// If I don't have any teeth, I can't possibly eat!

	// These are just standard tests of functionality. If they fail, we will keep
	// trying the rest until either the end of the TEST, or an assert macro fails.
	CHECK_TRUE(DoILikeToEatApples(42));
	CHECK_FALSE(DoILikeToEatApples(4));

	CHECK_EQUAL(true, DoILikeToEatBananas(7));
	CHECK_EQUAL(false, DoILikeToEatBananas(2));

	// For more macros, either check out Test.h, or read the documentation.
}
