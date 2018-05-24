#include <iostream>
#include <cstring>
#include "String.h"
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

int String::num = 0;


//int String::num = 0;
String::String(const char *s)
{
	len = std::strlen(s);
	str = new char[len+1];
	std::strcpy(str, s);
	num++;
}
String::String()
{
	len = 0;
	str = new char[1];
	str[0] = '\0';
	num++;	
}
String::String(const String &st)
{
	len = st.len;
	str = new char [len+1];
	std::strcpy(str, st.str);
	num++;
}
String::~String()
{
	--num;	
	delete [] str;
}
String & String::operator=(const String &st)
{
	if(this == &st)	
		return *this;
	delete [] str;
	len = st.len;
	str = new char[len+1];
	std::strcpy(str, st.str);
	return *this;
}
String & String::operator=(const char *s)
{	

	delete [] str;
	len = strlen(s);
	str = new char[len+1];
	std::strcpy(str, s);
	return * this;
}
char & String::operator[](const int i)
{
	return str[i];
}
const char & String::operator[](const int i) const
{
	return str[i];	
}
bool operator<(const String &st1, const String &st2)
{
	return (std::strcmp(st1.str, st2.str) < 0);
}
bool operator>(const String &st1, const String &st2)
{
	return st2 < st1;
}
bool operator==(const String &st1, const String &st2)
{
	return (std::strcmp(st1.str, st2.str) == 0);
	return 0;
}
ostream & operator<<(ostream &os, const String &st)
{
	//cout <<st.len<< std::endl;
	os << st.str;
	return os;
}
istream & operator>>(istream &is, String &st)
{
	char tmp[100];
	is.get(tmp, 100);
	if(is)
		 st = tmp;
	//cout << st.str<< std::endl;
	while(is && is.get()!='\n')
		continue;
	return is;	
}
int String::sum()
{
	return num;
}	

