#include "MyString.h"
#include <cstring>
using namespace std;

int MyString :: total = 0;
int MyString::howmany(){
	return total;
}

MyString::MyString(const char *s){
	len = strlen(s);
	str = new char [len + 1];
	strcpy(str, s);
	++total;
}

MyString::MyString(){
	len = 0;
	str = new char[1];
	str = nullptr;
	++total;
}

MyString::MyString(const MyString &s){
	len = s.length();
	str = new char [len + 1];
	strcpy(str, s.str);
	++total;
}

MyString::~MyString(){
	--total;
	delete [] str;
}

int MyString::length() const{
	return len;
}

char &MyString::operator [] (int i){
	return str[i];
}

const char &MyString::operator [] (int i) const{
	return str[i];
}

MyString &MyString::operator = (const MyString &s){
	if (this == &s)
		return *this;
	delete [] str;
	len = s.length();
	str = new char [len + 1];
	strcpy(str, s.str);
	return *this;
}

MyString &MyString::operator = (const char *s){
	delete [] str;
	len = strlen(s);
	str = new char [len + 1];
	strcpy(str, s);
	return *this;
}

bool operator < (const MyString &s1, const MyString &s2){
	return strcmp(s1.str, s2.str) < 0;
}

bool operator > (const MyString &s1, const MyString &s2){
	return strcmp(s1.str, s2.str) > 0;
}

bool operator == (const MyString &s1, const MyString &s2){
	return strcmp(s1.str, s2.str) == 0;
}

istream &operator >> (istream &is, MyString &s){
	char temp[MyString::max_len];
	is.get(temp, MyString::max_len);
	if (is)
		s = temp;
	while (is && is.get() != '\n')
		continue;
	return is;
}

ostream &operator << (ostream &os, const MyString &s){
	os << s.str;
	return os;
}
