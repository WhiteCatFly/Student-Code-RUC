#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;

class String {
public:
	String(const String& s);
	String(const char *s);
	String();	
	~String() { delete [] str_; }
	
	int getlen() { return len_; }
	char& operator[](const int index) { return str_[index]; }
	const char& operator[](const int index) const { return str_[index]; }
	String& operator=(const String& s);
//	String& operator=(const char* s); can this be omitted;

	friend bool operator==(const String& s1,const String& s2);
	friend bool operator>(const String& s1,const String& s2);
	friend bool operator<(const String& s1,const String& s2);
	friend ostream& operator<<(ostream& os,const String& s2); 
private:
	char* str_;
	int len_;

};

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

int main(void)
{
	String str("mystring");
	str = "c++";
	cout << str;
	return 0;
}
