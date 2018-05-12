#ifndef GOODSTRING_H_
#define GOODSTRING_H_

#include <string>

class GoodString{
private:
	char* ch;
	int len;
public:
	GoodString() {ch = NULL, len = 0; }
	GoodString(const std::string& str);
	GoodString(const char* str);
	GoodString(const GoodString& str);
	~GoodString();

	int length() const {return len; }
	
	friend std::ostream& operator <<(std::ostream& os, const GoodString& str);
	GoodString& operator =(const GoodString& str);
	char& operator [](int pos) {return ch[pos]; }
};

#endif
