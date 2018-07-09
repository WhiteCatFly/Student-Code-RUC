#include"mystring.h"







MyString::MyString(const char * s){
	len = strlen(s);
	str = new char [len + 1];
	strcpy(str , s);
}


MyString::MyString(){
	len = 0;
	str = 0;
}


MyString::MyString(const MyString & st){
	len = strlen(st.str);
	str = new char [len + 1];
	strcpy(str , st.str);
}


MyString::~MyString(){
	delete [] str;
}


MyString & MyString::operator = (const MyString & st){
	if(st == *this)
		return *this;
	delete [] str;
	len = strlen(st.str);
	str = new char [len + 1];
	strcpy(str , st.str);
	return *this;
}

MyString & MyString::operator = (const char * s){
	delete [] str;
	len = strlen(s);
	str = new char [len + 1];
	strcpy(str , s);
	return *this;
} 


bool operator < (const MyString & st , const MyString & st2){
	return (strcmp(st.str , st2.str) < 0);
}


bool operator > (const MyString & st3 , const MyString & st4){
	return st4 < st3;
}

bool operator == (const MyString & st5 , const MyString & st6){
	return (strcmp(st5.str , st6.str) == 0);
}


ostream & operator << (ostream & os , const MyString & st){
	os << st.str;
	return os;
}


istream & operator >> (istream & is , MyString & st){
	char temp[MyString::CINLIM];
	is.get(temp , MyString::CINLIM);
	if(is)
		st = temp;
	while(is && is.get() != '\n')
		continue;
	return is;
}
