#include <cstring>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

const unsigned int String::npos;
const unsigned int String::start_len;
const unsigned int String::limit_len;
int String::number = 0;

int String::how_many() {
	return String::number;
}

String::String() {
	number++;
	str = new char[start_len + 1];
	Length = start_len;
	str[Length] = '\0';
	cout << number << ": \"" << str << "\" default object created\n";
}

String::String(int length) {
	number++;
	str = new char[length + 1];
	Length = length;
	str[Length] = '\0';
	cout << number << ": \"" << str << "\" object by length created\n";
}

String::String(const char * st) {
	number++;
	Length = strlen(st);
	str = new char[Length + 1];
	strcpy(str,st);
	str[Length] = '\0';
	cout << number << ": \"" << str << "\" object created\n";
}

String::String(const String & Str) {
	number++;
	Length = Str.Length;
	str = new char[Length + 1];
	strcpy(str,Str.str);
	str[Length] = '\0';
	cout << number << ": \"" << str << "\" object (copy by String) created\n";
}

String::~String() {
	cout << "\"" << str << "\" object deleted, ";
	number--;
	cout << number << " left\n";
	delete[] str;
}

unsigned int String::find(const char temp, unsigned int pos) const {
	for (unsigned int i = pos;i < Length; ++i)
		if (str[i] == temp)
			return i;
	return String::npos;
}

unsigned int String::find(const char * temp, unsigned int pos) const{
	int len = strlen(temp);
	for (unsigned int i = pos;i < Length - len + 1; ++i) {
		bool flag = true;
		for (int j = 0; j < len; ++j)
			if (str[i + j] != temp[j]) {
				flag = false;
				break;
			}
		if (flag) return i;
	}
	return String::npos;
}
unsigned int String::find(const String & temp, unsigned int pos) const{
	return find(temp.str,pos);
}

String & String::operator = (const char * temp) {
	delete[] str;
	Length = strlen(temp);
	str = new char[Length + 1];
	strcpy(str,temp);
	str[Length] = '\0';
	return *this;
}

String & String::operator = (const String & Str) {
	if (this == &Str)
		return *this;
	delete[] str;
	Length = Str.Length;
	str = new char[Length + 1];
	strcpy(str,Str.str);
	str[Length] = '\0';
	return *this;
}


String String::operator + (const char temp) const {
	char tp[Length + 1];
	strcpy(tp,str);
	tp[Length] = temp;
	tp[Length + 1] = '\0';
	String ret(tp);
	return ret;
}

String String::operator + (const char * temp) const {
	char tp[Length + strlen(temp)];
	strcpy(tp,str);
	strcat(tp,temp);
	String ret(tp);
	return ret;
}

String String::operator + (const String & temp) const {
	char tp[Length + temp.Length];
	strcpy(tp,str);
	strcat(tp,temp.str);
	String ret(tp);
	return ret;
}

void String::operator += (const char temp) {
	Length++;
	char tp[Length];
	strcpy(tp,str);
	tp[Length - 1] = temp;
	tp[Length] = '\0';
	delete[] str;
	str = new char[Length + 1];
	strcpy(str,tp);
	str[Length] = '\0';
}

void String::operator += (const char * temp) {
	Length += strlen(temp); 
	char tp[Length];
	strcpy(tp,str);
	strcat(tp,temp);
	tp[Length] = '\0';
	delete[] str;
	str = new char[Length + 1];
	strcpy(str,tp);
	str[Length] = '\0';
}

void String::operator += (const String & temp) {
	Length += temp.Length; 
	char tp[Length];
	strcpy(tp,str);
	strcat(tp,temp.str);
	tp[Length] = '\0';
	delete[] str;
	str = new char[Length + 1];
	strcpy(str,tp);
	str[Length] = '\0';
}

const char & String::operator [] (unsigned int pos) const {
	if (pos >= Length) {
		cerr<<"out of length!"<<endl;
		exit(1);
	}
	return str[pos];
}

char & String::operator [] (unsigned int pos) {
	if (pos >= Length) {
		cerr<<"out of length!"<<endl;
		exit(1);
	}
	return str[pos];
}

bool operator == (const String & a, const String &b) {
	return (strcmp(a.str,b.str) == 0);
}

bool operator < (const String & a, const String &b) {
	return (strcmp(a.str,b.str) < 0);
}

bool operator > (const String & a, const String &b) {
	return (strcmp(a.str,b.str) > 0);
}

ostream & operator << (ostream & ofs, const String & Str) {
	ofs<<Str.str;
	return ofs;
}

istream & operator >> (istream & ifs, String & Str) {
	char str[String::limit_len];
	ifs.get(str,String::limit_len);
	if (ifs)
		Str = str;
	while (ifs && ifs.get() != '\n')
		continue;
	return ifs;
}
