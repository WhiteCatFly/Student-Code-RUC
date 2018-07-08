#ifndef MYSTRING_
#define MYSTRING_

#include<cstring>
#include<iostream>
using namespace std;



class MyString{
	private:
		static const int CINLIM = 80;
	public:
		MyString(const char * s);
		MyString();
		MyString(const MyString & st);
		~MyString();
		int length () const {return len;}
		
		MyString & operator = (const MyString & st);
		MyString & operator = (const char * s);
		char & operator [] (int i) {return str[i];}
		const char & operator [] (int i) const {return str[i];}
		
		friend bool operator < (const MyString & st , const MyString & st2);
		friend bool operator > (const MyString & st3 , const MyString & st4);
		friend bool operator == (const MyString & st5 , const MyString & st6);
		friend ostream & operator << (ostream & os , const MyString & st);
		friend istream & operator >> (istream & is , MyString & st);
	protected:
		char * str;
		int len;
};


#endif
