#include "arithmetic.h"
#include <gtest.h>

#define EPS 10e-15

struct check_test
{
	string str;
	bool res;
	check_test(string istr, bool ires)
	{
		str = istr;
		res = ires;

	}
};

struct cal_test
{
	string str;
	double res;
	cal_test(string istr, double ires)
	{
		str = istr;
		res = ires;
	}
};

class a_check : public ::testing::TestWithParam<check_test>
{
protected: arithmetic a_test;
public:
	a_check() : a_test(GetParam().str)
	{
	}
	~a_check() {}
};

class a_cal : public ::testing::TestWithParam<cal_test>
{
protected: arithmetic b_test;
		   istringstream input;
public:
	a_cal() : b_test(GetParam().str)
	{
	}
	~a_cal() {}
};

TEST_P(a_check, can_check_for_correct)
{
	EXPECT_EQ(GetParam().res, a_test.Check());
}

TEST_P(a_cal, can_calculate_expressions)
{
	EXPECT_GE(EPS, abs(GetParam().res - b_test.Cal()));
}

INSTANTIATE_TEST_CASE_P(Inst1,
	a_check,
	::testing::Values(
		check_test("5%", false),
		check_test("     ", false),
		check_test("5+.5", false),
		check_test("5+3.", false),
		check_test("2.9.8", false),
		check_test("((2)", false),
		check_test("(2))", false),
		check_test("1)(", false),
		check_test("+3", false),
		check_test("5 5", false),
		check_test("2(1)", false),
		check_test("(2)1", false),
		check_test("8++1", false),
		check_test("()", false),
		check_test("(+2)", false),
		check_test("(1+)", false),
		check_test("(-1)", true),
		check_test("-1", true),
		check_test("3+(-1*8)", true)
	));

INSTANTIATE_TEST_CASE_P(Inst2,
	a_cal,
	::testing::Values(
		cal_test("5+5", 10.0),
		cal_test("25+3*(7-2)*2-3", 52.0),
		cal_test("-2*8.1", -16.2),
		cal_test("6*(-5)/3", -10.0),
		cal_test("9*0+7/(5+2)*8", 8.0),
		cal_test("(8.1+9.9)/2", 9.0)
	));


TEST(arithmetic, rpn)
{
	arithmetic a("-25+3*(7-2)");	//0 25 - 3 7 2 - * + 
	lexem b[9];
	a.RPN_test(b);
	lexem c[9];
	c[0] = lexem("0", VALUE);
	c[1] = lexem("25", VALUE);
	c[2] = lexem("-", OPERATOR);
	c[3] = lexem("3", VALUE);
	c[4] = lexem("7", VALUE);
	c[5] = lexem("2", VALUE);
	c[6] = lexem("-", OPERATOR);
	c[7] = lexem("*", OPERATOR);
	c[8] = lexem("+", OPERATOR);

	bool res = true;
	for (int i = 0; i < 9; i++)
		if (c[i] != b[i])
		{
			cout << b[i].str << "   " << c[i].str << endl;
			res = false;
		}
	EXPECT_EQ(true, res);



}