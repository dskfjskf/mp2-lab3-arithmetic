#include "arithmetic.h"
#include <cstdlib>
using namespace std;

int main()
{	
	double res;
	arithmetic a("");
	string input;	
	while (1)
	{
		system("cls");		
		cout << "Input expression:" << endl;			
		getline(cin, input);
		a = arithmetic(input);
		if (a.Check())
		{
			res = a.Cal();
			cout <<'='<< res << endl;
		}
		system("pause");
	}	
	return 0;
}
