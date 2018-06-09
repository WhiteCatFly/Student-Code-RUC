#ifndef NUMSTRING_H
#define NUMSTRING_H

#include "Mystring.h"

class Numstring : Mystring
{
private:
	int floatdigit;
	static char Type(const char *form);
	static bool Plus(const char *form);
	static bool Minus(const char *form);
	static bool Space(const char *form);
	static int Accuracy(const char *form);
	static int IntAccuracy(const char *form);
	static int Width(const char *form);
public:
	Numstring();
	Numstring(const char *num);
	Mystring Print(const char *form);
	friend std::istream& operator>>(std::istream &input, Numstring &s0);
};

#endif
