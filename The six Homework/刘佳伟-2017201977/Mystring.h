#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class Mystring
{
protected:
	char *str;
	int len;
public:
	Mystring();
	Mystring(const char *s0);
	friend std::ostream& operator<<(std::ostream &output, const Mystring &s0);
	friend std::istream& operator>>(std::istream &input, Mystring &s0);
	int getlen();
	~Mystring();
};

#endif
