#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "goodstring.h"
using namespace std;

GoodString::GoodString(const std::string& str)
{
	len = str.length();
	ch = new char[len + 1];
	for(int i = 0;i < len; ++i) ch[i] = str[i];
	ch[len] = '\0';
}

GoodString::GoodString(const char* str)
{
	len = strlen(str);
	ch = new char[len + 1];
	strcpy(ch, str);
}

GoodString::GoodString(const GoodString& str)
{
	len = str.len, ch = new char[len + 1];
	for(int i = 0;i < len; ++i) ch[i] = str.ch[i];
	ch[len] = '\0';
}

GoodString::~GoodString() {delete[] ch; }

std::ostream& operator <<(std::ostream& os, const GoodString& str)
{
	int str_len = str.length();
	for(int i = 0;i < str_len; ++i) os << str.ch[i];
	return os;
}

GoodString& GoodString::operator =(const GoodString& str)
{
	delete[] ch;
	len = str.len, ch = new char[len + 1];
	for(int i = 0;i < len; ++i) ch[i] = str.ch[i];
	ch[len] = '\0';
	return *this;
}
