#ifndef STRING_
#define STRING_

#include<cstring>
#include<iostream>
using namespace std;

class String {
public:
	String(const String& s);
	String(const char *s);
	String();	
	virtual ~String() { delete [] str_; }
	
	int getlen() const { return len_; }
	const char* getstr() const { return str_; }
	char& operator[](const int index) { return str_[index]; }
	const char& operator[](const int index) const { return str_[index]; }
	String& operator=(const String& s);
//	String& operator=(const char* s); can this be omitted;
	String& operator+(const String& s);
	int find(const char c) const;
	
	friend bool operator==(const String& s1,const String& s2);
	friend bool operator>(const String& s1,const String& s2);
	friend bool operator<(const String& s1,const String& s2);
	friend ostream& operator<<(ostream& os,const String& s2); 
private:
	char* str_;
	int len_;

};
#endif
