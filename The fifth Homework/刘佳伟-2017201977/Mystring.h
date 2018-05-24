#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class Mystring
{
private:
	char *str;
	int len;
	static int num_strings;
public:
	Mystring();
	Mystring(const char *s0);
	Mystring(const Mystring &s0);
	friend std::ostream& operator<<(std::ostream &output, Mystring &s0);
	friend std::istream& operator>>(std::istream &input, Mystring &s0);
	Mystring operator=(const Mystring &s0);
	Mystring operator=(const char *s0);
	~Mystring();
	static void Initialize();
};

#endif
