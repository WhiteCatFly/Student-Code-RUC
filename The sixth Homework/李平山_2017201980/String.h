#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include <cstring>
#include <sstream>

using std::ostream;
using std::istream;
using std::cin;
using std::cout;

class String{
	protected:
    	char *str;
		int len;
		static int num;
	public:
		String(const char *);
		String(const String &);
		String();
		~String();
		////////////////////////constructors
		String & operator=(const String &);
		String & operator=(const char *);
		char & operator[](const int );
		const char & operator[](const int ) const;
		///////////////////oper
		int length() const {return len;}
		friend bool operator<(const String &st1, const String &st2);
		friend bool operator>(const String &st1, const String &st2); 
		friend bool operator==(const String &st1, const String &st2);
		friend std::ostream & operator<<(ostream & os, const String &st);
		friend std::istream & operator>>(istream & is, String &st);
		////////////////////////////////overload
		static int sum();
};

#endif 
