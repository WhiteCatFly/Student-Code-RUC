#include "Mystring.h"

using namespace std;

Mystring::Mystring()
{
	str = new char;
	*str = '\0';
	len = 0;
}

Mystring::Mystring(const char *s0)
{
	len = strlen(s0);
	str = new char[len + 1];
	strcpy(str, s0);
	str[len] = '\0';
}

int Mystring::getlen()
{
	return len;
}

Mystring::~Mystring()
{		
	delete []str;
	len = 0;
}


