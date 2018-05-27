#include "Mystring.h"

using namespace std;

ostream& operator<<(ostream &output, const Mystring &s0)
{
	output << s0.str;
	return output;
}

istream& operator>>(istream &input, Mystring &s0)
{
	if(s0.str != NULL)
		delete []s0.str;
	char *s1 = new char[32768];
	input >> s1;
	s0.len = strlen(s1);
	s0.str = new char[s0.len + 1];
	strcpy(s0.str, s1);
	s0.str[s0.len] = '\0';
	delete []s1;
	return input;
}

