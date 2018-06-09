#include <cctype>
#include <cstring>
#include "mystring.h"

using std::cin;
using std::cout;
using std::cerr;
using std::strcpy;
using std::strcmp;
using std::strcat;

String::String() {
	len = 0;
	s = new char[1];
	s[0] = 0;
}

String::String(const char * sp) {
	len = strlen(sp);
	s = new char[len + 1];
	strcpy(s, sp);
}

String::String(const String & rhs) {
	len = rhs.len;
	s = new char[len + 1];
	strcpy(s, rhs.s);
}

String::~String() {
	delete [] s;
}

size_t String::length() const {
	return len;
}

char * String::str() const {
	return s;
}

String & String::operator = (const String &rhs) {
	if(this == &rhs) return *this;
	delete [] s;
	len = rhs.len;
	s = new char[len + 1];
	strcpy(s, rhs.s);
	return *this;
}

String & String::operator = (const char * rhs) {
	delete [] s;
	len = strlen(rhs);
	s = new char[len + 1];
	strcpy(s, rhs);
	return *this;
}

char & String::operator [] (size_t pos) {
	return s[pos];
}

const char & String::operator [] (size_t pos) const {
	return s[pos];
}

bool String::operator < (const String & rhs) const {
	return strcmp(s, rhs.s) < 0;
}

bool String::operator > (const String & rhs) const {
	return rhs < s;
}

bool String::operator == (const String & rhs) const {
	return !strcmp(s, rhs.s);
}

istream & operator >> (istream & is, String & s) {
	char c;
	for(; is && isspace(c = is.get()); );
	s.len = 0;
	delete [] s.s;
	s.s = new char[s.INLIM];
	for(size_t lim = s.INLIM; is && !isspace(c); is.get(c)) {
		s.s[s.len++] = c;
		if(s.len + 1 == lim) {
			char str[lim];
			s.s[s.len] = 0;
			strcpy(str, s.s);
			delete [] s.s;
			s.s = new char[lim <<= 1];
			strcpy(s.s, str);
		}
	}
	s.s[s.len] = 0;
	if(!is) cerr << "istream failed\n";
//	for(int i = 0, lim = s.INLIM; ; lim = s.INLIM << (i++)) {
//		char str[lim | 1];
//		str[0] = 0;
//		is.get(str, lim, ' ');
//		if(!is || !str[0]) break;
//		char tmp[lim | 1];
//		strcpy(tmp, s.s);
//		delete [] s.s;
//		s.s = new char[lim << 1 | 1];
//		strcpy(s.s, tmp);
//		strcat(s.s, str);
//	}
//	s.len = strlen(s.s);
//	if(isspace(s.s[s.len - 1])) s.s[--s.len] = 0;
	return is;
}

ostream & operator << (ostream & os, const String & s) {
	return os << s.s;
}

