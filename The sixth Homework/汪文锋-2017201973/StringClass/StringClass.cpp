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
char* stringC::strC()
{
	return c;
}
NumberString::NumberString()
{
	//cout << "Create" << endl;
	c = new char[1];
	*c = '\0';
	len = 0;
	ints = new char[1];
	*ints = '\0';
	dicimals = new char[1];
	*dicimals = '\0';
}
NumberString::NumberString(const stringC &s)
{
	//cout << "Copy by stringC" << endl;
	stringC ss = s;
	len = ss.strClen();
	c = new char[len + 1];
	strcpy(c, ss.strC());
	bool mark = 0;
	for(int i=0;i<len;i++)
		if (c[i] == '.')
		{
			ints = new char[i+1];
			dicimals = new char[len-i];
			for (int j = 0; j < i; j++)
				ints[j] = c[j];
			for (int j = i + 1, k = 0; j < len; j++, k++)
				dicimals[k] = c[j];
			ints[i] = '\0';
			dicimals[len-i-1] = '\0';
			mark = 1; break;
		}
	if (mark == 0)
	{
		ints = new char[len+1];
		strcpy(ints, c);
		dicimals = new char[1];
		*dicimals = '\0';
	}
}
NumberString::NumberString(const NumberString &s)
{
	//cout << "Copy by NumberString" << endl;
	len = s.len;
	c = new char[len + 1];
	strcpy(c, s.c);
	int intlen = strlen(s.ints);
	ints = new char[intlen + 1];
	strcpy(ints, s.ints);
	int dicimalen = strlen(s.dicimals);
	dicimals = new char[dicimalen + 1];
	strcpy(dicimals, s.dicimals);
}
NumberString::NumberString(const char* cc)
{
	//cout << "N Copy by char*" << endl;
	len = int(strlen(cc));
	c = new char[len + 1];
	strcpy(c, cc);
	bool mark = 0;
	for (int i = 0; i<len; i++)
		if (c[i] == '.')
		{
			ints = new char[i+1];
			dicimals = new char[len - i];
			for (int j = 0; j < i; j++)
				ints[j] = c[j];
			for (int j = i + 1, k = 0; j < len; j++, k++)
				dicimals[k] = c[j];
			ints[i] = '\0';
			dicimals[len - i - 1] = '\0';
			mark = 1; break;
		}
	if (mark == 0)
	{
		ints = new char[len + 1];
		strcpy(ints, cc);
		dicimals = new char[1];
		*dicimals = '\0';
	}
}
NumberString::NumberString(const int &t)
{
	//cout << "Copy by int" << endl;
	len = 0;
	dicimals = new char[1];
	*dicimals = '\0';
	int tt = t;
	int tx[101],tlen=0;
	if (tt < 0)
	{
		tt = abs(tt);
		c = new char[1];
		c[len++] = '-';
	}
	if (tt == 0)
	{
		c = new char[1];
		c[len++] = '0';
	}
	while (tt > 0)
	{
		tx[++tlen] = tt % 10;
		tt /= 10;
	}
	for (int i = tlen; i >= 1; i--)
	{
		c = new char[1];
		c[len++] = char(tx[i]+48);
	}
	c = new char[1];
	c[len + 1] = '\0';
	ints = new char[len + 1];
	strcpy(ints, c);
}
NumberString::NumberString(const double &t)
{
	//cout << "Copy by double" << endl;
	len = 0;
	int tt = t;
	int tx[101], tlen = 0;
	if (tt < 0)
	{
		tt = abs(tt);
		ints = new char[1];
		ints[len++] = '-';
	}
	if (tt == 0)
	{
		ints = new char[1];
		ints[len++] = '0';
	}
	while (tt > 0)
	{
		tx[++tlen] = tt % 10;
		tt /= 10;
	}
	for (int i = tlen; i >= 1; i--)
	{
		ints = new char[1];
		ints[len++] = char(tx[i] + 48);
	}
	ints = new char[1];
	ints[len + 1] = '\0';
	len=0;
	double ttt = t - double(tt);
	while (ttt * 10 > 0)
	{
		ttt *= 10;
		dicimals = new char[1];
		dicimals[len++] = char(48+int(ttt)%10);
	}
	dicimals = new char[1];
	dicimals[len + 1] = '\0';
	len = strlen(ints) + strlen(dicimals) + 1;
	c = new char[len + 1];
	c = strcat(c, ints);
	c = strcat(c, ".");
	c = strcat(c, dicimals);
}
NumberString::~NumberString()
{
	//cout << "Delele NumberString" << endl;
	if (nullptr != ints)
	{
		delete ints;
		ints = nullptr;
	}
	if (nullptr != dicimals)
	{
		delete dicimals;
		ints = nullptr;
	}
}
int NumberString::reint()
{
	int t=0;
	for (int i = 0; i < len; i++)
		t = t * 10 + int(ints[i]) - 48;
	return t;
}
double NumberString::redouble()
{
	double t1 = 0.0;
	for (int i = 0; i < len; i++)
		t1 = t1 * 10 + int(ints[i]) - 48;
	double t2 = 0.0;
	for (int i = 0, xx = 10; i < len; i++, xx *= 10)
		t2 = t2 + double(int(dicimals[i]) - 48.0) / double(xx);
	return t1+t2;
}
