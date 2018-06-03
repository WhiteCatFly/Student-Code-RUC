#ifndef MyString_HZY_CPP_
#define MyString_HZY_CPP_
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "MyString.h"

int CalcSize(int t) {
	int tmp = 1;
	while(t) {
		t >>= 1;
		tmp <<= 1;
	}
	return tmp;
}

void MyString::Update() {
	int tmp = CalcSize(len + 1);
	if(tmp > lim) {
		lim = tmp;
		char * temp = new char[lim];
		std::strcpy(temp, str);
		delete [] str;
		str = temp;
	}
}

MyString::MyString(const char * s) {
	len = strlen(s);
	lim = CalcSize(len + 1);
	str = new char[lim];
	std::strcpy(str, s);
	//num++;
	//cerr << num << "created£º " << str << endl;
}
MyString::MyString() {
	len = 0, lim = 2;
	str = new char[lim];
	str[0] = '\0';
	//num++;
	//cerr << num << "created: " << endl;
}
MyString::~MyString() {
	//cerr << str << " has been deleted" << endl;
	//cerr << --num << " left\n";
	delete [] str;
}
std::ostream & operator << (std::ostream & os, const MyString & s) {
	os << s.str;
	return os;
}
MyString MyString::operator + (const char * s) {
	char * tmp = new char[len + strlen(s) + 2];
	strcpy(tmp, str);
	strcat(tmp, s);
	MyString temp(tmp);
	delete [] tmp;
	return temp;
}
MyString MyString::operator + (const MyString & s) {
	return *this + s.str;
}
MyString MyString::operator + (char c) {
	char * tmp = new char[len + 2];
	strcpy(tmp, str);
	tmp[len] = c, tmp[len + 1] = '\0';
	MyString temp(tmp);
	delete [] tmp;
	return temp;
}
void MyString::operator = (const char * s) {
	len = strlen(s);
	Update();
	strcpy(str, s);
}
void MyString::operator = (const MyString & s) {
	len = s.len;
	Update();
	strcpy(str, s.str);
}
char * MyString::to_str(int begin, int end) {
	if(end == -1) end = len - 1;
	int size = end - begin + 1;
	char * s = new char[size + 1];
	for(int i = 0; i < size; ++i)
		s[i] = str[begin + i];
	s[size] = '\0';
	return s;
}
	
#endif
