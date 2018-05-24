#ifndef DIGIT_STRING_H
#define DIGIT_STRING_H

#include "mystring.h"

class DigitString: public String {
private:
	const static int MAXL = 1024;
public:
	DigitString() = default;
	DigitString(const char * s): String(s) {}
	String set_format(char * format) const ;
};

#endif

