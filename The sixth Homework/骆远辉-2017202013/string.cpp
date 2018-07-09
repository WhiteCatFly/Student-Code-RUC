#include"string.h"

String::String()
{
	len_ = 0;
	str_ = new char[1];
	str_[0] = '\0';
}

String::String(const String& s)
{
	len_ = s.len_;
	str_ = new char[len_+1];
	strcpy(str_,s.str_);
}

String::String(const char* s)
{
	len_ = strlen(s);
	str_ = new char[len_+1];
	strcpy(str_,s);
}

int String::find(const char c) const
{
	int i = 0;
	for (; i <= len_-1 ; i++)
		if (str_[i] == c) {
			return i;
		}
	return -1;
}

String& String::operator =(const String& s)
{
	if (s.str_== str_) {
		return *this; 
	}
	delete [] str_;
	len_ = s.len_;
	str_ = new char[len_+1];
	strcpy(str_,s.str_);
	return *this;
}

String& String::operator +(const String& s)
{
	len_ = len_ + s.len_;
	char * temp = str_;
	delete [] str_;
	str_ = new char[len_+1];
	strcpy(str_,temp);
	strcat(str_,s.str_);
	return *this;
}

bool operator==(const String& s1, const String& s2)
{
	return (strcmp(s1.str_,s2.str_) == 0);	
}

bool operator>(const String& s1, const String& s2)
{
	return (strcmp(s1.str_,s2.str_) > 0);
}

bool operator<(const String& s1,const String& s2)
{
	return (strcmp(s1.str_,s2.str_) < 0);
}

ostream& operator<<(ostream& os,const String& s)
{
	os << s.str_;
	return os;
}
