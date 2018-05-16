#include <cstring>
#include "stringbad.h"
using namespace std;
int stringbad::num_strings=0;
stringbad::stringbad(const char* s){
	len=strlen(s);
	str=new char[len+1];
	strcpy(str,s);
	num_strings++;
	cout<<num_strings<<":\""<<str<<"\"object created\n";
}
stringbad::stringbad(){
	len=6;
	str=new char[6];
	strcpy(str,"empty");
	num_strings++;
	cout<<num_strings<<":\""<<str<<"\"object created\n";
}
stringbad::~stringbad(){
	cout<<"\""<<str<<"\"object deleted, ";
	num_strings--;
	cout<<num_strings<<" left\n";
	delete [] str;
}
stringbad::stringbad(const stringbad& s){
	len=s.len;
	str=new char[len+1];
	strcpy(str,s.str);
	num_strings++;
	cout<<num_strings<<":\""<<str<<"\"object created\n";
}	
stringbad& stringbad::operator=(const char* s){
	delete str;
	len=strlen(s);
	str=new char[len+1];
	strcpy(str,s);
	return *this;
}
stringbad& stringbad::operator=(const stringbad& s){
	delete str;
	len=s.len;
	str=new char[len+1];
	strcpy(str,s.str);
	return *this;
}	
ostream& operator<<(ostream& os,const stringbad& st){
	os<<st.str;
	return os;
}
