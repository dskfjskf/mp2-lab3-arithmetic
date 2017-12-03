#pragma once
#include "stack.h"
#include <string>

const string allOperators = "+-*/()";

enum lexemtype { LBRACKET, RBRACKET, OPERATOR, VALUE, UNKNOWN }; 
struct lexem { string str; lexemtype lt; };

class arithmetic
{		
	int nL; //���������� ������
	lexem* pL; //������ ������	
	string inputStr; //���������
	void parse();//������ �� �������
	
	
public:	
	bool Check_B();
	bool Check_S();
	bool Check();
	arithmetic(const string& istr);
	~arithmetic() { delete[] pL; }

};

void arithmetic::parse()
{
	for (int i = 0; i < inputStr.length(); i++)
	{
		char c = inputStr[i];
		int pos = allOperators.find(c);
		if (pos != string::npos)
		{
			if (pos < 4)
				pL[nL].lt = OPERATOR;
			else
				if (pos < 5)
					pL[nL].lt = LBRACKET;
				else pL[nL].lt = RBRACKET;
				pL[nL].str = c;
				nL++;
		}
		else
			if (isdigit(c))
			{				
				int j = i;
				while (j < inputStr.length() && (isdigit(inputStr[j]) || inputStr[j] == '.'))				
					j++;
				pL[nL].str = inputStr.substr(i, j - i);
				i = j-1;				
				pL[nL].lt = VALUE;
				nL++;
			}
			else
			{
				pL[nL].lt = UNKNOWN;
				pL[nL].str = c;
				nL++;
			}
	}
}

bool arithmetic::Check_S()
{
	bool res = true;
	int k = 0;	
	for (int i = 0; i < nL; i++)
	{		
		if (pL[i].lt == UNKNOWN)
		{
			k = 0;
			if (res)
			{
				cout << "Symbol:"<< endl;
				res = false;
			}
			cout << ' ' << pL[i].str << endl;
		}

		if (pL[i].lt == VALUE)
		{
			k = 0;
			for (int j = 0; j < pL[i].str.length(); j++)
				if (pL[i].str[j] == '.')
					k++;
			if (k > 1 || pL[i].str.back() == '.')
			{
				if (res)
				{
					cout << "Symbol:" << endl;
					res = false;
				}
				cout << ' ' << pL[i].str << endl;
			}		
		}
	}

	return res;
}

bool arithmetic::Check_B()
{
	bool res = true;
	Stack<int> b(inputStr.length());
	for (int i = 0; i <inputStr.length(); i++)
		if (inputStr[i]=='(')
			b.push(i+1);
		else 
			if (inputStr[i] == ')')
				if (!(b.empty()))
					b.pop();
				else
				{
					if (res)
					{
						cout << "Bracket:" << endl;
						res = false;
					}
					cout << i << endl;
				}
	if (!(b.empty()))
	{
		if (res)
		{
			cout << "Bracket:" << endl;
			res = false;
		}
		while (!(b.empty()))
			cout << b.pop() << endl;
	}
	
	return res;
}

bool arithmetic::Check()
{
	bool res = true;
	int pos = -1;
	if (!(pL[0].lt == VALUE || pL[0].lt == LBRACKET))
	{
		res = false;
		cout << "No operand before 1" <<  endl;
	}
	for (int i = 0; i < nL - 1; i++)
	{
		pos += pL[i].str.length();
		if ((pL[i].lt == RBRACKET || pL[i].lt == VALUE) && (pL[i + 1].lt == LBRACKET || pL[i + 1].lt == VALUE))
		{
			cout << "No operator between:" << pos + 1 << "and" << pos + 2 << endl;
			res = false;
		}
		if ((pL[i].lt == LBRACKET || pL[i].lt == OPERATOR) && (pL[i + 1].lt == OPERATOR || pL[i + 1].lt == RBRACKET))
		{
			cout << "No operand between:" << pos + 1 << "and" << pos + 2 << endl;
			res = false;
		}				
	}
	return res;
}


arithmetic::arithmetic(const string& istr)
	{
		inputStr = istr;
		pL = new lexem[inputStr.length()];
		nL = 0;
		parse();
	}

