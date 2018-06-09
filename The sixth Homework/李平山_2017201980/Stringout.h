#ifndef MYSTRINGOUT_H
#define MYSTRINGOUT_H
#include <iostream>
#include <cstring>
#include <sstream>

using std::ostream;
using std::istream;
using std::cin;
using std::cout;

class Stringout : public String
{
	private :
		char flag;
		int width;
		int sign; 
		int precision;
		char type;
	public :
		Stringout(const char *, const char , const int , const int, const int , const char);
		Stringout(const String &, const char , const int , const int, const int, const char );
		Stringout(const String &, const String &);
		Stringout();
		~Stringout() {}
		String & display();
		
};

bool is_flag(char s);
bool is_sign(char s);
bool is_tag(char s);
#endif 
