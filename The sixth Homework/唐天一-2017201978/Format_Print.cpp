#include "Format_Print.h"
#include <cstring>
using namespace std;

format_print::format_print(const char* sformat, MyString snumber) : MyString(snumber){
	memcpy(format, sformat, sizeof(sformat));
}

ostream &operator << (ostream &os, const format_print &out){
	int dot_pos = -1, precision = 0, width = 0, flength = strlen(out.format), anslen = 0, start = 0;
	MyString number(out);
	if (number[0] == '-')
		start = 1;
	char* ans = new char[max_len + 1];
	if (out.format[1] == '+' && !start)
		ans[anslen++] = '+';
	if (out.format[1] == ' ' && !start)
		ans[anslen++] = ' ';
	char fill_char = out.format[1] == '0' ? '0' : ' ';
	
	if (strchr(out.format, '.')){
		for (int i = 1; i < flength; ++i)
			if (out.format[i] == '.'){
				dot_pos = i;
				break;
			}
		if (dot_pos != -1)
			for (int i = dot_pos + 1; i < flength - 1; ++i)
				precision = precision * 10 + out.format[i] - '0';
	}
	for (int i = 1; i < flength - 1; ++i)
		if (out.format[i] != '.')
			if (isdigit(out.format[i]))
				width = width * 10 + out.format[i] - '0';
			else {}
		else break;
	
	if (strchr(out.format, 'd')){
		if (start)
			ans[anslen++] = '-';
		if (precision > out.length() - 1){
			for (int i = 0; i < precision - out.length() + 1; ++i)
				ans[anslen++] = '0';
		}
		for (int i = start; i < number.length(); ++i)
			ans[anslen++] = number[i];
	}
	else {
		int dot_pos = number.find('.') - &number[0];
		if (number.length() - dot_pos - 1 <= precision){
			if (start)
				ans[anslen++] = '-';
			for (int i = start; i < number.length(); ++i)
				ans[anslen++] = number[i];
			for (int i = 0; i < precision - number.length() + dot_pos + 1; ++i)
				ans[anslen++] = '0';
		}
		else{
			int i = dot_pos + precision, carry = (number[i + 1] >= '5');
			while (i >= start && carry){
				if (number[i] == '.'){
					--i;
					continue;
				}
				if (number[i] == '9')
					number[i] = '0', carry = 1, --i;
				else ++number[i], carry = 0;
			}
			if (start)
				ans[anslen++] = '-';
			if (carry)
				ans[anslen++] = '1';
			for (int i = start; i <= dot_pos + precision; ++i)
				ans[anslen++] = number[i];
		}
	}
	if (anslen < width){
		if (out.format[1] == '-'){
			os << ans;
			for (int i = 0 ; i < width - anslen; ++i)
				os << fill_char;
		}
		else {
			for (int i = 0 ; i < width - anslen; ++i)
				os << fill_char;
			os << ans;
		}
	}
	else os << ans;
	return os << endl;
}
