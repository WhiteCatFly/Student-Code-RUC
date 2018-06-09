#ifndef MyNumString_HZY_H_
#define MyNumString_HZY_H_
#include "MyString.h"

class MyNumString : public MyString
{
private:
	
public:
    MyNumString(const char * s) : MyString(s) {};
    MyNumString() : MyString() {};
	~MyNumString() {};

	void operator = (const char * s) { this->MyString::operator=(s);}
	void operator = (const MyString & s) { this->MyString::operator=(s); }
	MyString Standard(bool LRAlign, int width, int precision = 6) ;

};

#endif
