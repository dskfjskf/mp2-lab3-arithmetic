#include "arithmetic.h"
#include <gtest.h>

TEST(a, b)
{
	arithmetic a("5(5");
	a.Check();
}