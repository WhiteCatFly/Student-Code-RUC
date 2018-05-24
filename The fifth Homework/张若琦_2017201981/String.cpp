#include <cstring>
#include "String.h"
using std::cout;

int String::num_strings = 0;

// construction & deconstruction
String::String(const char ch)
{
	len_ = 1;
	str = new char[len_ + 1];
	str[0] = ch;
	str[1] = '\0';
}

String::String(const char * s)
{
	len_ = strlen(s);
	str = new char[len_ + 1];
	strcpy(str, s);
//	num_strings ++;
//	cout << num_strings << ": \"" << str
//		<< "\" object created\n";
}

String::String()
{
	len_ = 0;
	str = new char[1];
	*str = '\0';
//	num_strings ++;
//	cout << num_strings << ": \"" << str
//		<< "\" default object created\n";
}

String::String(const String & st)
{
	len_ = st.len_;
	str = new char[len_ + 1];
	strcpy(str, st.str);
//	num_strings ++;
}

String::String(const String & st, size_t pos, size_t len)
{
	if (pos > st.len_)
		throw std::out_of_range("invalid String position");
	if (pos == st.len_ || len == 0)
	{
		len_ = 0;
		str = new char[1];
		*str = '\0';
		return;
	}

	size_t ed = (pos + len > st.len_ || len == npos) ? st.len_ : pos + len;
	len_ = ed - pos;
	str = new char[len_ + 1];
	strncpy(str, st.str + pos, len_);
	str[len_] = '\0';
}

String::String(const char * s, size_t n)
{
	len_ = n;
	str = new char[len_ + 1];
	strncpy(str, s, n);
}

String::String(size_t n, const char ch)
{
	len_ = n;
	str = new char[len_ + 1];
	for (int i = 0; i < len_; i ++)
		str[i] = ch;
	str[len_] = '\0';
}

String::~String()
{
//	cout << "\"" << str << "\" object deleted, ";
//	num_strings --;
//	cout << num_strings << " left\n";
	delete [] str;
}

// overload operator
String & String::operator=(const String & st)
{
	if (this == &st)
		return * this;
	delete [] str;
	len_ = st.len_;
	str = new char[len_ + 1];
	strcpy(str, st.str);
	return * this;
}

String & String::operator=(const char * s)
{
	delete [] str;
	len_ = strlen(s);
	str = new char[len_ + 1];
	strcpy(str, s);
	return * this;
}

String & String::operator=(char ch)
{
	delete [] str;
	len_ = 1;
	str = new char[len_ + 1];
	str[0] = ch;
	str[1] = '\0';
	return * this;
}

String & String::operator+=(const String & st)
{;
	*this = *this + st;
	return * this;
}

String & String::operator+=(const char * s)
{
	*this = *this + s;
	return * this;
}

String & String::operator+=(char ch)
{
	*this = *this + ch;
	return * this;
}

char & String::operator[](int i)
{
	return str[i];
}

const char & String::operator[](int i) const
{
	return str[i];
}

// friend overload
bool operator<(const String & st1, const String & st2)
{
	return strcmp(st1.str, st2.str) < 0;
}

bool operator>(const String & st1, const String & st2)
{
	return strcmp(st1.str, st2.str) > 0;
}

bool operator==(const String & st1, const String & st2)
{
	return strcmp(st1.str, st2.str) == 0;
}

bool operator>=(const String & st1, const String & st2)
{
	return strcmp(st1.str, st2.str) >= 0;
}

bool operator<=(const String & st1, const String & st2)
{
	return strcmp(st1.str, st2.str) <= 0;
}

bool operator!=(const String & st1, const String & st2)
{
	return strcmp(st1.str, st2.str) != 0;
}

String operator+(const String & st1, const String & st2)
{
	String ret;
	delete [] ret.str;
	ret.len_ = st1.len_ + st2.len_;
	ret.str = new char[ret.len_ + 1];
	strcpy(ret.str, st1.str);
	strcpy(ret.str + st1.len_, st2.str);
	return ret;
}

String operator+(const String & st1, const char * s)
{
	String st2(s);
	return st1 + st2;
}

String operator+(const char * s, const String & st2)
{
	String st1(s);
	return st1 + st2;
}

String operator+(const String & st1, const char ch)
{
	String st2(ch);
	return st1 + st2;
}

String operator+(const char ch, const String & st2)
{
	String st1(ch);
	return st1 + st2;
}

std::ostream & operator<<(std::ostream & os, const String & st)
{
	os << st.str;
	return os;
}

std::istream & operator>>(std::istream & is, String & st)
{
	char tmp[String::MAXL] = {0};
	if (is >> tmp)
	{
		delete [] st.str;
		st.len_ = strlen(tmp);
		st.str = new char[st.len_ + 1];
		strcpy(st.str, tmp);

	}
	return is;
}

// friend function
void swap(String & x, String & y)
{
	if (&x == &y)
		return;
	String z = x;
	x = y;
	y = z;
}

// other function
size_t String::size() const
{
	return len_;
}

size_t String::length() const
{
	return len_;
}

const char * String::c_str() const
{
	return str;
}
const char * String::data() const
{
	return str;
}

size_t String::copy(char * s, size_t len, size_t pos) const
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	char * dest = s, *src = str + pos, *srced = str + len_;
	for (int i = 0; i < len && src < srced; i ++)
		*dest ++ = *src ++;
	return src - (str + pos);
}

char & String::at(size_t pos)
{
	return str[pos];
}

const char & String::at(size_t pos) const
{
	return str[pos];
}

bool String::empty() const
{
	return len_ == 0;
}

void String::clear()
{
	delete [] str;
	len_ = 0;
	str = new char[1];
	str[0] = '\0';
}

char & String::front()
{
	return str[0];
}

const char & String::front() const
{
	return str[0];
}

char & String::back()
{
	return str[len_ - 1];
}

const char & String::back() const
{
	return str[len_ - 1];
}

void String::pop_back()
{
	erase(len_ - 1);
}

void String::push_back(const char ch)
{
	insert(len_, 1, ch);
}

String & String::erase(size_t pos, size_t len)
{
	if (pos >= len_)
		throw std::out_of_range("invalid String position");
	size_t ed = (pos + len > len_ || len == npos) ? len_ : pos + len;
	*this = substr(0, pos) + substr(ed, len_ - ed);
	return *this;
}

String & String::insert(size_t pos, const String & st)
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	*this = substr(0, pos) + st + substr(pos, len_ - pos);
	return *this;
}

String & String::insert(size_t pos, const String & st, size_t subpos, size_t sublen)
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	*this = substr(0, pos) + st.substr(subpos, sublen) + substr(pos, len_ - pos);
	return *this;
}

String & String::insert(size_t pos, const char * s)
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	*this = substr(0, pos) + s + substr(pos, len_ - pos);
	return *this;
}

String & String::insert(size_t pos, const char * s, size_t n)
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	*this = substr(0, pos) + String(s, n) + substr(pos, len_ - pos);
	return *this;
}

String & String::insert(size_t pos, size_t n, char ch)
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	*this = substr(0, pos) + String(n, ch) + substr(pos, len_ - pos);
	return *this;
}

String String::replace_basic(size_t pos, size_t len, const String & mid)
{
	if (pos > len_)
		throw std::out_of_range("invalid String position");
	size_t ed = (pos + len > len_ || len == npos) ? len_ : pos + len;
	return substr(0, pos) + mid + substr(ed, len_ - ed);
}

String & String::replace(size_t pos, size_t len, const String & st)
{
	return *this = replace_basic(pos, len, st);
}

String & String::replace(size_t pos, size_t len, const String & st, size_t subpos, size_t sublen)
{
	return *this = replace_basic(pos, len, st.substr(subpos, sublen));
}

String & String::replace(size_t pos, size_t len, const char * s)
{
	return *this = replace_basic(pos, len, s);
}

String & String::replace(size_t pos, size_t len, const char * s, size_t n)
{
	return *this = replace_basic(pos, len, String(s, n));
}

String & String::replace(size_t pos, size_t len, size_t n, char ch)
{
	return *this = replace_basic(pos, len, String(n, ch));
}

String String::substr(size_t pos, size_t len) const
{
	return String(*this, pos, len);
}

String & String::append(const String & st)
{
	return *this = *this + st;
}

String & String::append(const String & st, size_t subpos, size_t sublen)
{
	return *this = *this + st.substr(subpos, sublen);
}

String & String::append(const char * s)
{
	return *this = *this + s;
}

String & String::append(const char * s, size_t n)
{
	return *this = *this + String(s, n);
}

String & String::append(size_t n, char c)
{
	return *this = *this + String(n, c);
}

int String::compare(const String & st) const // *this < str -> neg
{
	return strcmp(str, st.str);
}

int String::compare(size_t pos, size_t len, const String & st) const
{
	return substr(pos, len).compare(st);
}

int String::compare(size_t pos, size_t len, const String & st, size_t subpos, size_t sublen) const
{
	return substr(pos, len).compare(st.substr(subpos, sublen));
}

int String::compare(const char * s) const
{
	return strcmp(str, s);
}

int String::compare(size_t pos, size_t len, const char * s) const
{
	return strcmp(substr(pos, len).str, s);
}

int String::compare(size_t pos, size_t len, const char * s, size_t n) const
{
	return strncmp(substr(pos, len).str, s, n);
}

size_t String::find_basic(char * srcbeg, char * srced, const char * dest, const size_t len) const// brute-force
{
	if (srcbeg >= srced)
		return npos;
	char * src = srcbeg;
	while (src < srced)
	{
		if (strncmp(src, dest, len) == 0)
			return src - srcbeg;
		src ++;
	}
	return npos;
}

size_t String::find(const String & st, size_t pos) const
{
	size_t ret = find_basic(str + pos, str + len_, st.str, st.len_);
	return ret == npos ? npos : ret + pos;
}

size_t String::find(const char * s, size_t pos) const
{
	size_t ret = find_basic(str + pos, str + len_, s, strlen(s));
	return ret == npos ? npos : ret + pos;
}

size_t String::find(const char * s, size_t pos, size_t n) const
{
	size_t ret = find_basic(str + pos, str + len_, s, n);
	return ret == npos ? npos : ret + pos;
}

size_t String::find(char c, size_t pos) const
{
	size_t ret = find_basic(str + pos, str + len_, &c, 1);
	return ret == npos ? npos : ret + pos;
}
