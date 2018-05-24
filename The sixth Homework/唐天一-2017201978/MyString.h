#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
using std::istream;
using std::ostream;

const int max_len = 1030;

class MyString{
private:
	char *str;
	int len;
	static int total;
	
public:
	MyString(const char *s);
	MyString();
	MyString(const MyString &);
	~MyString();
	
	int length() const;
	char &operator [] (int i);
	const char &operator [] (int i) const;
	MyString &operator = (const MyString &);
	MyString &operator = (const char *);
	
	friend bool operator < (const MyString &s1, const MyString &s2);
	friend bool operator > (const MyString &s1, const MyString &s2);
	friend bool operator == (const MyString &s1, const MyString &s2);
	friend istream &operator >> (istream &is, MyString &s);
	friend ostream &operator << (ostream &os, const MyString &s);
	
	char* find(char c) const;
	
	static int howmany();
};
#endif
