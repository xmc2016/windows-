#define _CRT_SECURE_NO_WARNINGS 1
#include"Data.h"
int main()
{
	Date d(2017, 1, 20);
	Date a(1995, 5, 13);
	//Date a = d - 120;
	//Date b = d -333;
	int c = d - a;

	d++.Print();
	system("pause");
	return 0;
}