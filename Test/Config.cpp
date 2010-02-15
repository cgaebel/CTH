#include "stdafx.h"
#include "TestContext.h"

// A WORD OF WARNING:
//
// There is no garuntee that your functions will be called from
// the same thread. DO NOT STORE SHARED DATA WITHOUT SYNCHRONIZATION.
// Seriously. That's just a bad idea. It'll probably lead to hiesenbugs.
// If you DO use synchronization, expect a huge dip in performance.
namespace Test
{
	bool PreTest(DefaultTestContext& /*test*/)
	{
		// If you want to customize the framework to do "something"
		// before a test starts, throw it in here. If this function
		// returns false, the test will not be run.
		return true;
	}

	void PostTest(DefaultTestContext& /*test*/)
	{
		// If you want to customize the framework to do "something"
		// after a test ends, throw it in here.
	}
}
