#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack <int> a(4));
	ASSERT_NO_THROW(Stack <int> a);
}


TEST(Stack, can_push_element)
{
	Stack <int> a(2);
	ASSERT_NO_THROW(a.push(3));
}

TEST(Stack, can_push_element_with_too_large_index)
{
	Stack <int> a(1);
	a.push(2);
	ASSERT_NO_THROW(a.push(3));
}

TEST(Stack, can_pop_value)
{
	Stack <int> a;
	a.push(5);
	EXPECT_EQ(5,a.pop());
}

TEST(Stack, throws_when_pop_with_negative_startindex)
{
	Stack <int> a;
	ASSERT_ANY_THROW(a.pop());
}

TEST(Stack, can_peek_value)
{
	Stack <int> a;
	a.push(5);
	EXPECT_EQ(5, a.peek());
}

TEST(Stack, throws_when_peek_with_negative_startindex)
{
	Stack <int> a;
	ASSERT_ANY_THROW(a.peek());
}

TEST(Stack,empty)
{
	Stack <int> a;
	EXPECT_EQ(true, a.empty());
}