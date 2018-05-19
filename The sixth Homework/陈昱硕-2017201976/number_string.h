#ifndef NUMBER_STRING_H
#define NUMBER_STRING_H

#include "my_string.h"

class NumberString : public MyString{
private:
    MyString PrintDigit(const char *fmt, int begin, int end);
    MyString PrintFloat(const char *fmt, int begin, int end);

public:
    MyString FormatOutput(const char *fmt);
};

#endif