#ifndef String_ZRQ_H_
#define String_ZRQ_H_

#include <iostream>

class String
{
private:
	char * str;
	size_t len_;
	static int num_strings;
	static const size_t MAXL = 80;
	String replace_basic(size_t pos, size_t len, const String & mid);
	size_t find_basic(char * srcbeg, char * srced, const char * dest, const size_t len) const;
public:
	static const size_t npos = -1;
	
	// construction & deconstruction
	String(const char ch);
	String(const char * s);
	String(const String & st);
	String(const String & st, size_t pos, size_t len = npos);
	String(const char * s, size_t n);
	String(size_t n, const char ch);
	String();
	virtual ~String();

	// overload operator
	String & operator=(const String & st);
	String & operator=(const char * s);
	String & operator=(char ch);
	String & operator+=(const String & st);
	String & operator+=(const char * s);
	String & operator+=(char ch);
	char & operator[](int i);
	const char & operator[](int i) const;

	// friend overload
	friend bool operator<(const String & st1, const String & st2);
	friend bool operator>(const String & st1, const String & st2);
	friend bool operator==(const String & st1, const String & st2);
	friend bool operator!=(const String & st1, const String & st2);
	friend bool operator>=(const String & st1, const String & st2);
	friend bool operator<=(const String & st1, const String & st2);

	friend String operator+(const String & st1, const String & st2);
	friend String operator+(const String & st1, const char * s);
	friend String operator+(const char * s, const String & st2);
	friend String operator+(const String & st1, const char ch);
	friend String operator+(const char ch, const String & st2);

	friend std::ostream & operator<<(std::ostream & os, const String & st);
	friend std::istream & operator>>(std::istream & is, String & st);

	// friend function
	friend void swap(String & x, String & y);

	// other function
	size_t size() const;
	size_t length() const;
	const char * c_str() const;
	const char * data() const;
	size_t copy(char * s, size_t len, size_t pos = 0) const;
	char & at(size_t pos);
	const char & at(size_t pos) const;
	bool empty() const;
	void clear();
	char & front();
	const char & front() const;
	char & back();
	const char & back() const;
	void pop_back();
	void push_back(const char ch);
	String & erase(size_t pos = 0, size_t len = npos);
	String & insert(size_t pos, const String & st);
	String & insert(size_t pos, const String & st, size_t subpos, size_t sublen);
	String & insert(size_t pos, const char * s);
	String & insert(size_t pos, const char * s, size_t n);
	String & insert(size_t pos, size_t n, char ch);
	String & replace(size_t pos, size_t len, const String & str);
	String & replace(size_t pos, size_t len, const String & str, size_t subpos, size_t sublen);
	String & replace(size_t pos, size_t len, const char * s);
	String & replace(size_t pos, size_t len, const char * s, size_t n);
	String & replace(size_t pos, size_t len, size_t n, char ch);
	String substr(size_t pos = 0, size_t len = npos) const;
	String & append(const String & st);
	String & append(const String & st, size_t subpos, size_t sublen);
	String & append(const char * s);
	String & append(const char * s, size_t n);
	String & append(size_t n, char c);
	int compare(const String & st) const;
	int compare(size_t pos, size_t len, const String & st) const;
	int compare(size_t pos, size_t len, const String & st, size_t subpos, size_t sublen) const;
	int compare(const char * s) const;
	int compare(size_t pos, size_t len, const char * s) const;
	int compare(size_t pos, size_t len, const char * s, size_t n) const;
	size_t find(const String & st, size_t pos = 0) const;
	size_t find(const char * s, size_t pos = 0) const;
	size_t find(const char * s, size_t pos, size_t n) const; // no pos=0 -> ambiguity
	size_t find(char c, size_t pos = 0) const;
};

#endif // String_ZRQ_H_