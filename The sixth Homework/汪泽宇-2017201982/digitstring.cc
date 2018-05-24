#include <cctype>
#include <cstring>
#include <iostream>
#include "mystring.h"
#include "digitstring.hpp"

using std::cerr;

//	[l, r)
int StrToInt(char * l, char * r) {
	int num = 0;
	for(; l < r; l++) num = num * 10 + *l - '0';
	return num;
}

//	required cur_prec > prec
void Round(char * s, size_t & pos, int prec) {
	if(s[pos + prec] >= '5') {
		for(int i = pos + prec - 1; i >= 0; i--) {
			if(s[i] == '.') continue;
			if(s[i] < '9') {
				s[i]++;
				for(size_t j = i + 1; j < pos + prec; j++) {
					if(s[j] == '.') continue;
					s[j] = '0';
				}
				break;
			}
			if(!i) {
				s[0] = '1';
				for(size_t j = 1; j <= pos + prec; j++) {
					if(s[j] == '.') {
						s[j] = '0';
						s[++j] = '.';
					}
					else s[j] = '0';
				}
				pos++;
			}
		}
	}
	s[pos + prec] = 0;
}

String DigitString::set_format(char * format) const {
	size_t len = strlen(format);
	
	int type;
	if(format[--len] == 'd') type = 0;
	else type = 1, len--;
	
	size_t pos = len - 1;
	while(pos && format[pos] != '.') pos--;
	int prec;
	if(pos) {
		if(pos == len - 1) prec = 0;
		else prec = StrToInt(format + pos + 1, format + len);
		len = pos;
	}
	else {
		if(type) prec = 6;
		else prec = 1;
	}
	
	pos = 1;
	while(pos < len && !isdigit(format[pos])) pos++;
	int width;
	if(pos < len) {
		width = StrToInt(format + pos, format + len);
		len = pos;
	}
	else width = 0;
	
	int plus = 0, space = 0, align = 0, hash = 0, zero = 0;
	for(size_t i = 1; i < len; i++) {
		if(format[i] == '+') plus = 1;
		else if(format[i] == ' ') space = 1;
		else if(format[i] == '-') align = 1;
		else if(format[i] == '#') hash = 1;
		else cerr << "invalid flags\n";
	}
	if(plus) space = 0;
	if(!align && (type || prec > 1)
		&& width && format[len] == '0') zero = 1;
	
	char s[MAXL + 1];
	strcpy(s, this->str());
	len = this->length();
	
	size_t cur_len = len;
	
	char sign[2];
	memset(sign, 0, sizeof sign);
	if((plus || space) && s[0] != '-') {
		bool not0 = 0;
		for(size_t i = 0; i < cur_len; i++) {
			if(isdigit(s[i]) && s[i] != '0') {
				not0 = 1;
				break;
			}
		}
		if(not0) {
			if(plus) sign[0] = '+';
			else sign[0] = ' ';
			len++;
		}
	}
	
	if(type) {
		for(pos = 0; pos < cur_len && s[pos] != '.'; pos++);
		if(pos == cur_len) {
			s[cur_len++] = '.';
			len++;
		}
		if(pos < cur_len) pos++;
		if(cur_len - pos < (size_t)prec) {
			for(size_t i = 0; i < prec - (cur_len - pos); i++) {
				s[cur_len + i] = '0';
			}
			len += pos + prec - cur_len;
			cur_len = pos + prec;
		}
		else if(cur_len - pos > (size_t)prec) {
			Round(s, pos, prec);
			len -= cur_len - (pos + prec);
			cur_len = pos + prec;
		}
		if(s[cur_len - 1] == '.' && !hash) {
			s[--cur_len] = 0;
			len--;
		}
		else s[cur_len] = 0;
	}
	else {
		if(cur_len < (size_t)prec) {
			int dt = prec - cur_len;
			for(int i = cur_len - 1; i >= 0; i--) s[i + dt] = s[i];
			for(int i = 0; i < dt; i++) s[i] = '0';
			s[cur_len = prec] = 0;
			len += dt;
		}
	}
	
#ifdef DEBUG
	std::cout << "s:\n" << s << std::endl;
#endif
	
	char align_s[MAXL + 1];
	if(len < (size_t)width) {
		char c = zero ? '0' : ' ';
		for(size_t i = 0; i < width - len; i++) align_s[i] = c;
		align_s[width - len] = 0;
	}
	else align_s[0] = 0;
	
#ifdef DEBUG
	std::cout << "align:\n" << align_s << std::endl;
#endif
	
	char str[MAXL + 1];
	if(align) {
		strcpy(str, sign);
		strcat(str, s);
		strcat(str, align_s);
	}
	else {
		if(zero) {
			strcpy(str, sign);
			strcat(str, align_s);
		}
		else {
			strcpy(str, align_s);
			strcat(str, sign);
		}
		strcat(str, s);
	}
	return String(str);
}
