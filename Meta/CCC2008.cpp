// http://cemc.math.uwaterloo.ca/contests/computing/2008/stage1/seniorEn.pdf
#include "stdafx.h"
#include <cmath>

/*
	The game �Pennies in the Ring� is often played by bored computer programmers who have gotten
	tired of playing solitare. The objective is to see how many pennies can be put into a circle. The
	circle is drawn on a grid, with its center at the coordinate (0; 0): A single penny is placed on every
	integer grid coordinate (e.g., (1; 1); (1; 2); etc.) that lies within or on the circle. It�s not a very
	exciting game, but it�s very good for wasting time. Your goal is to calculate how many pennies are
	needed for a circle with a given radius.
*/
namespace S02
{
	struct Point
	{
		int x;
		int y;

		Point(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
	};

	static double GetDistanceFromOrigin(const Point& p)
	{
		return sqrt((double)(p.x*p.x + p.y*p.y));
	}

	static bool IsInCircle(const Point& p, int r)
	{
		return GetDistanceFromOrigin(p) <= r;
	}

	static int Solve(int r)
	{
		int numberOfSolutions = 0;

		for(int x = -r; x <= r; ++x)
			for(int y = -r; y <= r; ++y)
				if(IsInCircle(Point(x, y), r))
					++numberOfSolutions;

		return numberOfSolutions;
	}
}

TEST(Pythagorean)
{
	using namespace S02;

	double root2 = sqrt((double)2);

	CHECK_CLOSE(root2, GetDistanceFromOrigin(Point(1, 1)), 0.0001);
	CHECK_CLOSE(root2, GetDistanceFromOrigin(Point(-1, -1)), 0.0001);
}

TEST(InCircle)
{
	using namespace S02;

	CHECK_FALSE(IsInCircle(Point(2, 2), 2));
	CHECK_TRUE(IsInCircle(Point(2, 0), 2));

	CHECK_TRUE(IsInCircle(Point(0, 0), 1));
	CHECK_TRUE(IsInCircle(Point(9001, 1), 9002));
}

TEST(SampleSolutions)
{
	using namespace S02;

	CHECK_EQUAL(13, Solve(2));
	CHECK_EQUAL(29, Solve(3));
	CHECK_EQUAL(49, Solve(4));
}

TEST(Regressions)
{
	using namespace S02;

	CHECK_EQUAL(31417, Solve(100));
	CHECK_EQUAL(1, Solve(0));
	CHECK_EQUAL(2550297, Solve(901));
}

TEST(MaximumValue)
{
	//CHECK_EQUAL(-1, S02::Solve(25000));
}
