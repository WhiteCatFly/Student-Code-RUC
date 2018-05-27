#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"StringClass.h"
using namespace std;
int main()
{
	stringC a;
	stringC b;
	a = "123";
	b = "456";
	a = a+b;
	cout << a << endl;
	return 0;
}