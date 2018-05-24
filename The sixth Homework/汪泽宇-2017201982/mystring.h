#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>

using std::istream;
using std::ostream;

class String {
private:
	char *s;
	size_t len;
	static const size_t INLIM = 64;
public:
	String();
	String(const String &);
	String(const char *);
	~String();
	size_t length() const;
	char * str() const;
	String & operator = (const String &);
	String & operator = (const char *);
	char & operator [] (size_t);
	const char & operator [] (size_t) const;
	
	bool operator < (const String &) const;
	bool operator > (const String &) const;
	bool operator == (const String &) const;
	friend istream & operator >> (istream &, String &);
	friend ostream & operator << (ostream &, const String &);
};
#endif

