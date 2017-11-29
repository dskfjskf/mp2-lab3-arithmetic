#pragma once
#include "stack.h"
#include <string>

const string allOperators = "+-*/()";

class arithmetic
{
	enum lexemtype { LBRACKET, RBRACKET, OPERATOR, VALUE, UNKNOWN }; 
	struct lexem { string str; lexemtype lt; }; 
		
	lexem* pL; //Массив лексем
	int nL; //Количество лексем
	string inputStr; //Выражение
	void parse();//Разбор на лексемы
public:
	arithmetic(const string& istr);
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
				while (j < inputStr.length() && (inputStr[j] == isdigit(c) || inputStr[j] == '.'))
					j++;
				pL[nL].str = inputStr.substr(i, j - i);
				i = j-1;
				nL++;
				pL[nL].lt = VALUE;
			}
	}
}

	arithmetic::arithmetic(const string& istr)
	{
		inputStr = istr;
		pL = new lexem[inputStr.length()];
		nL = 0;
		parse();
	}

