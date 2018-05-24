#ifndef STRING_H_
#define STRING_H_

#include <string>

const int def_pos = 0;

class dstring:public std::string{
public:
	dstring(const std::string& str):std::string(str) {}
	dstring(const std::string& str, size_t pos, size_t len = std::string::npos):std::string(str, pos, len) {}
	dstring(const char* s):std::string(s) {}
	dstring(const char* s, size_t n):std::string(s, n) {}
	dstring(size_t n, char c):std::string(n, c) {}
	template<class InputIterator>
	dstring(InputIterator first, InputIterator last):std::string(first, last) {}
	
	virtual ~dstring() {}

	int is(int pos) const {return (*this)[pos] - '0'; }
	std::string sprint(const std::string& str, int pos = def_pos) const;
};

#endif
