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
	// This function is called before a test is added to the global test
	// list. If "true" is returned, the test is added. Otherwise, it will
	// be silently ignored. This is useful for things like only executing
	// one suite of tests because running them all just takes too long.
	bool AddTestPredicate(const DefaultTestContext& /*newTest*/)
	{
		return true;
	}

	// If you want to customize the framework to do "something"
	// before a test starts, throw it in here.
	void PreTest(DefaultTestContext& /*test*/)
	{
	}

	// If you want to customize the framework to do "something"
	// after a test ends, throw it in here.
	void PostTest(DefaultTestContext& /*test*/)
	{
	}
}
