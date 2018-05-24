#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <cstring>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>

class String{
private:
	const static unsigned int start_len = 1;
	const static unsigned int limit_len = 3000;
	static int number;
	char * str;
	unsigned int Length;
public:
	const static unsigned int npos = -1;
	//constructor and destructor
	String();
	String(int length);
	String(const char * st);
	String(const String & Str);
	virtual ~String();
	//public function
	unsigned int length() const {return Length;}
	unsigned int size() const {return Length;}
	char * c_str() const {return str;}
	unsigned int find(const char temp, unsigned int pos = 0) const;
	unsigned int find(const char * temp, unsigned int pos = 0) const;
	unsigned int find(const String & temp, unsigned int pos = 0) const;
	String substr(int start, unsigned int len = 0) const;
	//multi-operator
	String & operator = (const char * temp);
	virtual String & operator = (const String & temp);
	String operator + (const char temp) const;
	String operator + (const char * temp) const;
	String operator + (const String & temp) const;
	void operator += (const char temp);
	void operator += (const char * temp);
	void operator += (const String & temp);
	const char & operator [] (unsigned int pos) const;
	char & operator [] (unsigned int pos);
	//friend-operator
	friend bool operator == (const String & a, const String & b);
	friend bool operator < (const String & a, const String & b);
	friend bool operator > (const String & a, const String & b);
	friend String operator + (const char * temp, const String & a);
	friend String operator + (const char temp, const String & a);
	friend std::ostream & operator << (std::ostream & ofs, const String & Str);
	friend std::istream & operator >> (std::istream & ifs, String & Str);
	
	static int how_many();
};

#endif
