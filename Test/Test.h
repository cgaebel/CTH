#pragma once
#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

namespace Test
{
	namespace EnvironmentSanityCheck
	{
		#ifdef TEST
			#error "Test redefines TEST"
		#endif

		#ifdef CHECK_TRUE
			#error "Test redefines CHECK_TRUE"
		#endif

		#ifdef ASSERT_TRUE
			#error "Test redefines ASSERT_TRUE"
		#endif

		#ifdef CHECK_FALSE
			#error "Test redefines CHECK_FALSE"
		#endif

		#ifdef ASSERT_FALSE
			#error "Test redefines ASSERT_FALSE"
		#endif

		#ifdef CHECK_EQUAL
			#error "Test redefines CHECK_EQUAL"
		#endif

		#ifdef ASSERT_EQUAL
			#error "Test redefines ASSERT_EQUAL"
		#endif

		#ifdef CHECK_CLOSE
			#error "Test redefines CHECK_CLOSE"
		#endif

		#ifdef ASSERT_CLOSE
			#error "Test redefines ASSERT_CLOSE"
		#endif

		#ifdef CHECK_NULL
			#error "Test redefines CHECK_NULL"
		#endif

		#ifdef ASSERT_NULL
			#error "Test redefines ASSERT_NULL"
		#endif

		#ifdef CHECK_VALID
			#error "Test redefines CHECK_VALID"
		#endif

		#ifdef ASSERT_VALID
			#error "Test redefines ASSERT_VALID"
		#endif
	}

	#define TEST(TestName)														\
		static void Test__##TestName(::Test::TestContext&);						\
		static const int placeholder__##TestName = ::Test::AddToGlobalTestList(	\
			#TestName, __FILE__, __LINE__, Test__##TestName);					\
		static void Test__##TestName(::Test::TestContext& __testContext)

	namespace ChecksAndAsserts
	{
		#define CHECK_TRUE(condition)										\
		{																	\
			if((condition) == false)										\
				__testContext.AddFailure(__LINE__, #condition);				\
		} 0

		#define ASSERT_TRUE(condition)										\
		{																	\
			if((condition) == false)										\
			{																\
				__testContext.AddFailure(__LINE__, #condition);				\
				return;														\
			}																\
		} 0

		#define CHECK_FALSE(condition)										\
		{																	\
			if((condition) == true)											\
				__testContext.AddFailure(__LINE__, #condition);				\
		} 0

		#define ASSERT_FALSE(condition)										\
		{																	\
			if((condition) == true)											\
			{																\
				__testContext.AddFailure(__LINE__, #condition);	\
				return;														\
			}																\
		} 0

		#define CHECK_EQUAL(expected, actual)								\
		{																	\
			if(!::Test::CheckHelpers::AreEqual(expected, actual))			\
				__testContext.AddFailure(__LINE__,							\
					"Expected \"" #expected "\" but was \"" #actual "\".");	\
		} 0

		#define ASSERT_EQUAL(expected, actual)								\
		{																	\
			if(!::Test::CheckHelpers::AreEqual(expected, actual))			\
			{																\
				__testContext.AddFailure(__LINE__,							\
					"Expected \"" #expected "\" but was \"" #actual "\".");	\
				return;														\
			}																\
		} 0

		#define CHECK_CLOSE(expected, actual, tolerance)					\
		{																	\
			if(!::Test::CheckHelpers::AreClose(expected, actual, tolerance))\
				__testContext.AddFailure(__LINE__,							\
					"Expected \"" #expected "\" +/- " #tolerance			\
					" but was \"" #actual "\".");							\
		} 0

		#define ASSERT_CLOSE(expected, actual, tolerance)					\
		{																	\
			if(!::Test::CheckHelpers::AreClose(expected, actual, tolerance))\
			{																\
				__testContext.AddFailure(__LINE__,							\
					"Expected \"" #expected "\" +/- " #tolerance			\
					" but was \"" #actual "\".");							\
				return;														\
			}																\
		} 0

		#define CHECK_NULL(pointer)											\
		{																	\
			if((pointer) != nullptr)										\
				__testContext.AddFailure(__LINE__,							\
					"\"" #pointer "\" is not NULL.");						\
		} 0

		#define ASSERT_NULL(pointer)										\
		{																	\
			if((pointer) != nullptr)										\
			{																\
				__testContext.AddFailure(__LINE__,							\
					"\"" #pointer "\" is not NULL.");						\
					return;													\
			}																\
		} 0

		#define CHECK_VALID(pointer)										\
		{																	\
			if((pointer) == nullptr)										\
				__testContext.AddFailure(__LINE__,							\
					"\"" #pointer "\" is NULL.");							\
		} 0

		#define ASSERT_VALID(pointer)										\
		{																	\
			if((pointer) == nullptr)										\
			{ 																\
				__testContext.AddFailure(__LINE__,							\
					"\"" #pointer "\" is NULL.");							\
				return;														\
			}																\
		} 0
	}

	namespace CheckHelpers
	{
		template <typename FloatType>
		bool AreClose(
			FloatType expected,
			FloatType actual,
			FloatType tolerance)
		{
			return (actual >= (expected - tolerance))
				&& (actual <= (expected + tolerance));
		}

		template <typename DataType>
		bool AreEqual(DataType expected, DataType actual)
		{
			return expected == actual;
		}
	}

	class TestContext abstract
	{
	public:
		virtual void AddFailure(int lineNumber, const char* message) = 0;
	};

	const int TEST_API AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (*testFunction)(TestContext&));

	int TEST_API RunAllTests();
}
