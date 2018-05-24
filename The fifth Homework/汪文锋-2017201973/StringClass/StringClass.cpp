#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"StringClass.h"
using namespace std;
stringC::stringC()
{
	//cout << "Create" << endl;
	c = new char[1];
	*c = '\0';
	len = 0;
}
stringC::stringC(const stringC &s)
{
	//cout << "Copy by stringC" << endl;
	len = s.len;
	c = new char[len + 1];
	strcpy(c, s.c);
	//cout << c << endl;
}
stringC::stringC(const char *cc)
{
	//cout << "Copy by char*" << endl;
	len = int(strlen(cc));
	c = new char[len + 1];
	strcpy(c,cc);
}
stringC::~stringC()
{
	//cout << "Delele stringC" << endl;
	if (nullptr != c)
	{
		delete c;
		c = nullptr;
		len = 0;
	}
}
ostream &operator<<(ostream &out, const stringC &s)
{
	//cout << "Print It" << endl;
	out << s.c;
	return out;
}
istream &operator>>(istream &in, const stringC &s)
{
	//cout << "Read It" << endl;
	in >> s.c;
	return in;
}
stringC stringC::operator=(const stringC &s)
{
	//cout << "Copy by = stringC" << endl;
	char *temp = new char[s.len + 1];
	strcpy(temp, s.c);
	c = temp;
	len = s.len;
	return *this;
}
stringC stringC::operator=(const char *cc)
{
	//cout << "Copy by = char*" << endl;
	len = int(strlen(cc));
	c = new char[len + 1];
	strcpy(c, cc);
	return *this;
}
stringC stringC::operator+(const stringC &s)
{
	//cout << "Add by stringC" << endl;
	stringC newC;
	char *temp = new char[len + s.len + 1];
	temp = strcat(temp, c);
	temp = strcat(temp, s.c);
	newC = temp;
	return newC;
}
stringC stringC::operator+(const char *cc)
{
	//cout << "Add by char*" << endl;
	stringC newC;
	int slen = strlen(cc);
	char *temp = new char[len + slen + 1];
	temp = strcat(temp, c);
	temp = strcat(temp, cc);
	newC = temp;
	return newC;
}
int stringC::strClen()
{
	return len;
}