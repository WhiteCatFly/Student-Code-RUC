#ifndef StringClass
#define StringClass
#include<iostream>
using namespace std;
class stringC
{
private:
	char *c;
	int len;
public:
	stringC();
	stringC(const stringC &s);
	stringC(const char *cc);
	~stringC();
	friend ostream &operator<<(ostream& out, const stringC &s);
	friend istream &operator>>(istream& out, const stringC &s);
	stringC operator=(const stringC &s);
	stringC operator=(const char *cc);
	stringC operator+(const stringC &s);
	stringC operator+(const char *cc);
	int strClen();
};
#endif