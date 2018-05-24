#include "Mystring.h"

using namespace std;

int Mystring::num_strings = 0;

Mystring::Mystring()
{
	str = new char;
	*str = '\0';
	len = 0;
	
	Mystring::num_strings++;
	cout << Mystring::num_strings << ":\"" << str
		 << "\" default object created\n";
}

Mystring::Mystring(const char *s0)
{
	len = strlen(s0);
	str = new char[len + 1];
	strcpy(str, s0);
	str[len] = '\0';
	
	Mystring::num_strings++;
	cout << Mystring::num_strings << ":\"" << str
		 << "\" object created\n";
}

Mystring::Mystring(const Mystring &s0)
{
	len = strlen(s0.str);
	str = new char[len + 1];
	strcpy(str, s0.str);
	str[len] = '\0';
	
	Mystring::num_strings++;
	cout << Mystring::num_strings << ":\"" << str
		 << "\" object created\n";
}

Mystring::~Mystring()
{
	cout << "\"" << str << "\" object deleted, ";
	--Mystring::num_strings;
	cout << Mystring::num_strings << "left\n";	
		
	delete []str;
	len = 0;
}
