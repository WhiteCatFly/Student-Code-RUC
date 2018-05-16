#ifndef STRING_H
#define STRING_H
#include <iostream>
using std::ostream;
class stringbad{
	friend ostream& operator<<(ostream& os,const stringbad& st);
	private:
	char *str;
	int len;
	static int num_strings;
	public:
	stringbad(const char* s);
	stringbad();
	stringbad(const stringbad& s);
	~stringbad();
	stringbad& operator=(const char* s);
	stringbad& operator=(const stringbad& s);
};
#endif
	
