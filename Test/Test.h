#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TEST_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TEST_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

namespace Test
{
	#define TEST(TestName)													\
		static void Test__TestName(const Test::TestContext&);				\
		static const int placeholder__TestName = Test::AddToGlobalTestList(	\
			#TestName, __FILE__, __LINE__, Test__TestName);					\
		static void Test__TestName(const Test::TestContext& __testContext)

	#define CHECK_TRUE(condition)										\
	{																	\
		if((condition) == false)										\
			__testContext.AddFailure(__FILE__, __LINE__, #condition);	\
	} 0

	#define ASSERT_TRUE(condition)										\
	{																	\
		if((condition) == false)										\
		{																\
			__testContext.AddFailure(__FILE__, __LINE__, #condition);	\
			return;														\
		}																\
	} 0

	#define CHECK_FALSE(condition)										\
	{																	\
		if((condition) == true)											\
			__testContext.AddFailure(__FILE__, __LINE__, #condition);	\
	} 0

	#define ASSERT_FALSE(condition)										\
	{																	\
		if((condition) == true)											\
		{																\
			__testContext.AddFailure(__FILE__, __LINE__, #condition);	\
			return;														\
		}																\
	} 0

	#define CHECK_EQUAL(expected, actual)								\
	{																	\
		if((expected) != (actual))										\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"Expected \"" expected "\" but was \"" actual "\".");	\
	} 0

	#define ASSERT_EQUAL(expected, actual)								\
	{																	\
		if((expected) != (actual))										\
		{																\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"Expected \"" expected "\" but was \"" actual "\".");	\
			return;														\
		}																\
	} 0

	#define CHECK_CLOSE(expected, actual, tolerance)					\
	{																	\
		if(!::Test::Utilities::AreClose(expected, actual, tolerance))	\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"Expected \"" expected "\" +/- " tolerance				\
				" but was \"" actual "\".");							\
	} 0

	#define ASSERT_CLOSE(expected, actual, tolerance)					\
	{																	\
		if(!::Test::Utilities::AreClose(expected, actual, tolerance))	\
		{																\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"Expected \"" expected "\" +/- " tolerance				\
				" but was \"" actual "\".");							\
			return;														\
		}																\
	} 0

	#define CHECK_NULL(pointer)											\
	{																	\
		if((pointer) != nullptr)										\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"\"" #pointer "\" is not NULL.");						\
	} 0

	#define ASSERT_NULL(pointer)										\
	{																	\
		if((pointer) != nullptr)										\
		{																\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"\"" #pointer "\" is not NULL.");						\
				return;													\
		}																\
	} 0

	#define CHECK_VALID(pointer)										\
	{																	\
		if((pointer) == nullptr)										\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"\"" #pointer "\" is NULL.");							\
	} 0

	#define ASSERT_VALID(pointer)										\
	{																	\
		if((pointer) == nullptr)										\
		{ 																\
			__testContext.AddFailure(__FILE__, __LINE__,				\
				"\"" #pointer "\" is NULL.");							\
			return;														\
		}																\
	} 0

	namespace Utilities
	{
		template <typename _T>
		class TEST_API LinkedList
		{
		private:
			struct TEST_API Node
			{
				_T data;
				Node* next;

				Node() { }

				explicit Node(const _T& newData)
				{
					data = newData;
				}
			};

			Node* sentinel;

		public:
			class TEST_API iterator
			{
			private:
				Node* me;

			public:
				explicit iterator(Node* node)
				{
					me = node;
				}

				bool operator==(const iterator& other) const
				{

					return me->next == other.me->next;
				}

				bool operator!=(const iterator& other) const
				{
					return !(*this == other);
				}

				iterator& operator++()
				{
					me = me->next;
					return *this;
				}

				iterator operator++(int)
				{
					iterator preIncrement = *this;
					++*this;
					return preIncrement;
				}

				_T operator*() const
				{
					return me->data;
				}

				_T* operator->() const
				{
					return &(me->data);
				}
			};

		private:
			void Link(Node* left, Node* newNode, Node* right)
			{
				left->next = newNode;
				newNode->next = right;
			}

			void RemoveFromParentList(Node* previousElement, Node* toRemove)
			{
				previousElement->next = toRemove->next;
				delete toRemove;
			}

		public:
			LinkedList()
			{
				sentinel = new Node;
				sentinel->next = sentinel;
			}

			LinkedList(const LinkedList& other)
			{
				sentinel = new Node;
				sentinel->next = sentinel;

				for(iterator i = other.begin(); i != other.end(); ++i)
					Push(*i);
			}

			void Push(const _T& toAdd)
			{
				Link(sentinel, new Node(toAdd), sentinel->next);
			}

			_T Pop()
			{
				_T removed = sentinel->next->data;
				RemoveFromParentList(sentinel, sentinel->next);

				return removed;
			}

			iterator begin() const
			{
				return iterator(sentinel->next);
			}

			iterator end() const
			{
				return iterator(sentinel);
			}

			unsigned int size() const
			{
				unsigned int count = 0;

				for(iterator i = begin(); i != end(); ++i)
					++count;

				return count;
			}

			bool empty() const
			{
				// To check this in O(1), we directly check
				// the pointers for the base case instead of
				// using the cleaner "return size() == 0;"
				// which would run in O(n).
				return sentinel->next == sentinel;
			}

			// Return if the element was found.
			bool remove(const _T& toRemove)
			{
				// A little hack was used here to prevent deletion
				// of an element we need the next pointer of.
				// Instead of using "current" as an iterator, we
				// use the element directly before it.
				for(
					Node* previous = sentinel;
					previous->next != sentinel;
					previous = previous->next
				)
				{
					Node* current = previous->next;

					if(current->data == toRemove)
					{
						RemoveFromParentList(previous, current);
						return true;
					}
				}

				return false;
			}

			~LinkedList()
			{
				while(!empty())
					Pop();

				delete sentinel;
			}
		};

		template <typename FloatType>
		bool AreClose(
			FloatType expected,
			FloatType actual,
			FloatType tolerance)
		{
			return (actual >= (expected - tolerance))
				&& (actual <= (expected + tolerance));
		}
	}

	struct TEST_API Failure
	{
		const char* fileName;
		const char* message;
		int lineNumber;

		inline Failure()
		{
		}

		Failure(const char* fileName, const char* message, const int lineNumber);
	};

	class TEST_API TestContext
	{
	public:
		const char* testName;
		const char* fileName;
		int lineNumber;
		void (*testFunction)(const TestContext&);

		Utilities::LinkedList<Failure> failures;

	public:
		inline TestContext()
		{
		}

		TestContext(
			const char* testName, 
			const char* fileName,
			const int lineNumber,
			void (*testFunction)(const TestContext&));

		TestContext(const TestContext& other);
		TestContext& operator=(const TestContext& other);

		void AddFailure(const char* fileName, int lineNumber, const char* message);
	};

	int TEST_API AddToGlobalTestList(
		const char* testName,
		const char* fileName,
		int lineNumber,
		void (__cdecl* testFunction)(const ::Test::TestContext&));

	int TEST_API RunAllTests();
}
