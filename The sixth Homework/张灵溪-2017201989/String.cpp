#include <cstring>  
#include <iostream>  
#include "String.h"              
using std::cin;
using std::cout;
using std::endl;
String::String(const char* s){
    Npos = CINLIM + 1;
    len = strlen(s);         
    str = new char[len + 1];       
    strcpy(str, s);   
    str[len] = '\0'; 
}
String::String(){
	Npos = CINLIM + 1;
    len = 0;
    str = new char[1];
    str[0] = '\0';
}
String::String(const String& st){
    Npos = CINLIM + 1;
    len = st.length();
    str = new char[len + 1];
    strcpy(str, st.str_());
    str[len] = '\0';
}
String::~String(){
    delete [] str;
}
String& String::operator=(const String& st){
    if(this == &st)
        return *this;
    delete [] str;
    len = st.length();
    str = new char[len + 1];
    strcpy(str, st.str_());
    str[len] = '\0';
    return *this;
}
String& String::operator=(const char* s){
    delete [] str;
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
    str[len] = '\0';
    return *this;
}
String String::operator+(const String& st) const{
	char* temp = new char[len + st.length() + 1];
	strcpy(temp, str);
	strcat(temp, st.str_());
	temp[len + st.length()] = '\0';
	String s(temp);
	return s;
}	
char& String::operator[](int i){
    return str[i];
}
const char& String::operator[](int i) const{
    return str[i];
}
int String::Find(char t, int cur) const{
	for(int i = cur; i < len; i++){
		if(str[i] == t)
			return i;
	}
	return Npos;
}
int String::Find(char t) const{
	return Find(t, 0);
}
bool operator<(const String& st1, const String& st2){
    return (std::strcmp(st1.str, st2.str) < 0);
}
bool operator>(const String& st1, const String& st2){
    return st2 < st1;
}
bool operator==(const String& st1, const String& st2){
    return (std::strcmp(st1.str, st2.str) == 0);
}
ostream& operator<<(ostream& os, const String& st){
    os << st.str;
    return os; 
}
istream& operator>>(istream& is, String& st){
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if(is)
        st = temp;
    while(is && is.get() != '\n')
        continue;
    return is; 
}
