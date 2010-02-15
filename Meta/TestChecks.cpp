#include "stdafx.h"

TEST(TrueAndFalse)
{
	CHECK_TRUE(true);
	CHECK_TRUE(1);
	CHECK_TRUE(-1);

	ASSERT_TRUE(true);
	ASSERT_TRUE(1);
	ASSERT_TRUE(-1);

	CHECK_FALSE(false);
	CHECK_FALSE(0);

	ASSERT_FALSE(false);
	ASSERT_FALSE(0);
}

TEST(Equality)
{
#define PI 3

	CHECK_EQUAL(3, PI);
	CHECK_EQUAL(1, PI / 2);

	ASSERT_EQUAL(3, PI);
	ASSERT_EQUAL(1, PI / 3);

	CHECK_EQUAL(PI / 2, PI / 3);

	CHECK_EQUAL("Hello!", "Hello!");

	ASSERT_EQUAL("Hello!", "Hello!");

#undef PI
}

TEST(FloatingPointComparisons)
{
	CHECK_CLOSE(3.14, 3.1, 0.1);
	ASSERT_CLOSE(3.141, 3.14, 0.01);
}

TEST(Pointers)
{
	int foo;

	CHECK_NULL(nullptr);
	ASSERT_NULL(nullptr);

	CHECK_VALID(&foo);
	ASSERT_VALID(&foo);
}
