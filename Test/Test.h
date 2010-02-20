#pragma once
#include <string>
#include <sstream>

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
		static void __cdecl Test__##TestName(::Test::TestContext&);				\
		static const int placeholder__##TestName = ::Test::AddToGlobalTestList(	\
			#TestName, __FILE__, __LINE__, Test__##TestName);					\
		static void __cdecl Test__##TestName(::Test::TestContext& __testContext)

	namespace ChecksAndAsserts
	{
		#define TERMINATE_TEST(message)										\
		{																	\
			__testContext.AddFailure(__LINE__, message);					\
			return;															\
		} 0

		#define CHECK_TRUE(condition)										\
		{																	\
			if((condition) == false)										\
				__testContext.AddFailure(__LINE__, #condition " is false.");\
		} 0

		#define ASSERT_TRUE(condition)										\
		{																	\
			if((condition) == false)										\
				TERMINATE_TEST(#condition " is false.");					\
		} 0

		#define CHECK_FALSE(condition)										\
		{																	\
			if((condition) == true)											\
				__testContext.AddFailure(__LINE__, #condition " is true.");	\
		} 0

		#define ASSERT_FALSE(condition)										\
		{																	\
			if((condition) == true)											\
				TERMINATE_TEST(#condition " is true.");						\
		} 0

		#define CHECK_EQUAL(expected, actual)								\
			::Test::CheckHelpers::ProcessAreEqual(							\
				__testContext, expected, actual, __LINE__)

		#define ASSERT_EQUAL(expected, actual)								\
		{																	\
			if(!::Test::CheckHelpers::ProcessAreEqual(						\
				__testContext, expected, actual, __LINE__))					\
					return;													\
		} 0

		#define CHECK_CLOSE(expected, actual, tolerance)					\
			::Test::CheckHelpers::ProcessAreClose(							\
				__testContext, expected, actual, tolerance, __LINE__)		\

		#define ASSERT_CLOSE(expected, actual, tolerance)					\
		{																	\
			if(!::Test::CheckHelpers::ProcessAreClose(						\
				__testContext, expected, actual, tolerance, __LINE__))		\
					return;													\
		} 0

		#define CHECK_NULL(pointer)											\
		{																	\
			if((pointer) != nullptr)										\
				__testContext.AddFailure(__LINE__,							\
					#pointer " is not NULL.");								\
		} 0

		#define ASSERT_NULL(pointer)										\
		{																	\
			if((pointer) != nullptr)										\
				TERMINATE_TEST(#pointer " is not NULL.");					\
		} 0

		#define CHECK_VALID(pointer)										\
		{																	\
			if((pointer) == nullptr)										\
				__testContext.AddFailure(__LINE__,							\
					#pointer " is NULL.");									\
		} 0

		#define ASSERT_VALID(pointer)										\
		{																	\
			if((pointer) == nullptr)										\
				TERMINATE_TEST(#pointer " is NULL.");						\
		} 0
	}

	class TEST_API TestContext abstract
	{
	public:
		virtual void AddFailure(int lineNumber, const std::string& message) = 0;
	};

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

		template <typename D1, typename D2>
		bool AreEqual(D1 expected, D2 actual)
		{
			return expected == actual;
		}

		bool TEST_API AreEqual(const char* expected, const char* actual);
		bool TEST_API AreEqual(const char* expected, char* actual);
		bool TEST_API AreEqual(char* expected, const char* actual);
		bool TEST_API AreEqual(char* expected, char* actual);
		
		template <typename D1, typename D2>
		std::string MakeErrorStringEqual(
			D1 expected,
			D2 actual)
		{
			std::ostringstream out;
			out << "Expected " << expected
				<< " but was " << actual;
			return out.str();
		}

		template <typename D1, typename D2, typename D3>
		std::string MakeErrorStringClose(
			D1 expected,
			D2 actual,
			D3 tolerance)
		{
			std::ostringstream out;
			out << "Expected " << expected << " +/- " << tolerance
				<< " but was " << actual;
			return out.str();
		}

		// The follow two functions return true if we are to continue the test, false if we don't.
		template <typename T1, typename T2>
		bool ProcessAreEqual(TestContext& context, T1 expected, T2 actual, int lineNumber)
		{
			if(!AreEqual(expected, actual))
			{
				context.AddFailure(lineNumber, MakeErrorStringEqual(expected, actual));
				return false;
			}

			return true;
		}

		template <typename T1, typename T2, typename T3>
		bool ProcessAreClose(TestContext& context, T1 expected, T2 actual, T3 tolerance, int lineNumber)
		{
			if(!AreClose(expected, actual, tolerance))
			{
				context.AddFailure(lineNumber, MakeErrorStringClose(expected, actual, tolerance));
				return false;
			}

			return true;
		}
	}

	const int TEST_API AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (__cdecl* testFunction)(TestContext&));

	int TEST_API RunAllTests();
}
