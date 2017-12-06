#pragma once
#include "stack.h"
#include <string>

const string allOperators = "+-*/()";

enum lexemtype { LBRACKET, RBRACKET, OPERATOR, VALUE, UNKNOWN }; 
struct lexem 
{
	string str; 
	lexemtype lt;
};

class arithmetic
{		
	int nL; //Количество лексем
	lexem* pL; //Массив лексем	
	string inputStr; //Выражение
	void parse();//Разбор на лексемы
	bool Check_B();//Проверка на скобки
	bool Check_S();//Проверка на символы
	bool Check_С();//Проверка на корректность
	bool PR(lexem a, lexem b);//Приоритет
	int RPN(lexem* pLex);//Перевод в ОПЗ
public:		
	bool Check();
	double Cal();//Вычислениие
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

bool arithmetic::Check_С()
{
	bool res = true;
	int pos = -1;
	if (!(pL[0].lt == VALUE || pL[0].lt == LBRACKET || pL[0].str[0]=='-'))
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
		if (pL[i].lt == LBRACKET && ((pL[i + 1].lt == OPERATOR && pL[i+1].str[0]!='-') || pL[i + 1].lt == RBRACKET))
		{
			cout << "No operand between:" << pos + 1 << "and" << pos + 2 << endl;
			res = false;
		}			
		if (pL[i].lt == OPERATOR && (pL[i + 1].lt == OPERATOR || pL[i + 1].lt == RBRACKET))
		{
			cout << "No operand between:" << pos + 1 << "and" << pos + 2 << endl;
			res = false;
		}
	}
	return res;
}

bool arithmetic::Check() 
{
	if (Check_S())
	return Check_B()&&Check_С();
	else 	
		return false;
}

bool arithmetic::PR(lexem a, lexem b)
{
	int p1, p2;
	switch (a.str[0])
	{
	case '(':p1=0;
		break;
	case '+':;
	case '-':p1 = 1;
		break;
	default:p1 = 2;		
	}

	switch (b.str[0])
	{
	case '(':p2 = 0;
		break;
	case '+':;
	case '-':p2 = 1;
		break;
	default:p2 = 2;
	}

	return p1 > p2;
}

int arithmetic::RPN(lexem* pLex)
{
	lexem zero;
	zero.lt = VALUE;
	zero.str = "0";

	lexemtype cur;	
	int j = 0;
	Stack<lexem> s(nL);
	for (int i = 0; i < nL; i++)
	{
		cur = pL[i].lt;
		if (cur == VALUE)
		{
			pLex[j] = pL[i];
			j++;
		}
		if (cur == LBRACKET)
			s.push(pL[i]);
		if (cur == RBRACKET)
		{
			while ((s.peek()).lt != LBRACKET)
			{
				pLex[j] = s.pop();
				j++;
			}
			s.pop();
		}
		if (cur == OPERATOR)
		{
			if (pL[i].str[0] == '-' && (i == 0 || pL[i - 1].str[0] == '(' ))
			{
				pLex[j] = zero;
				j++;
			}
			if (!s.empty() && !PR(pL[i], s.peek()))
			{
				pLex[j] = s.pop();
				j++;
			}
			s.push(pL[i]);
		}

		}
	while (!s.empty())
	{
		pLex[j] = s.pop();
		j++;
	}
	return j;
}

double arithmetic::Cal()
{
	lexem* pLex = new lexem[2*nL];
	int fnL = RPN(pLex);
	Stack<double> res(2*fnL);
	for (int i = 0; i < fnL; i++)
		if (pLex[i].lt == VALUE)
			res.push(stod(pLex[i].str));
		else 
		{
			double r = res.pop(), l = res.pop();
			switch (pLex[i].str[0])
			{
			case '+': res.push(l + r);
				break;
			case '-': res.push(l - r);
				break;
			case '*': res.push(l * r);
				break;
			default: res.push(l / r);				
			}
		}
	return res.peek();
}

arithmetic::arithmetic(const string& istr)
	{
		inputStr = istr;
		pL = new lexem[inputStr.length()];
		nL = 0;
		parse();
	}

