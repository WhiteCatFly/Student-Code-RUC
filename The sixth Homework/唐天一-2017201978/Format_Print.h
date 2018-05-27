#ifndef FORMAT_PRINT
#define FORMAT_PRINT

#include "MyString.h"

class format_print : public MyString{
private:
	char format[100];

public:
	format_print(const char* sformat, MyString snumber);
	friend ostream &operator << (ostream &os, const format_print &format);
};

#endif
