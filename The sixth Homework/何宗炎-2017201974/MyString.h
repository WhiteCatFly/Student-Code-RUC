#ifndef MyString_HZY_H_
#define MyString_HZY_H_
#include <iostream>
class MyString {
private:
	char * str;
	int len, lim;
	//static int num;
	void Update();
	
public:
	MyString(const char * s);
	MyString();
	virtual ~MyString() ;
	MyString operator + (const MyString & s) ;
	MyString operator + (const char * s);
	MyString operator + (char c) ;
	void operator = (const MyString & s);
	void operator = (const char * c);
	char * to_str(int begin = 0, int end = -1) ;

	friend std::ostream & operator << (std::ostream & os, const MyString & s);
};
#endif
