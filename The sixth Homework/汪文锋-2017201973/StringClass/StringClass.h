#ifndef StringClass
#define StringClass
#include<iostream>
using namespace std;
class stringC
{
protected:
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
	char* strC();
};
class NumberString :public stringC
{
private:
	char *ints;
	char *dicimals;
public:
	NumberString();
	NumberString(const NumberString &s);
	NumberString(const stringC &s);
	NumberString(const char *cc);
	NumberString(const int &t);
	NumberString(const double &t);
	~NumberString();
	int reint();
	double redouble();
};
#endif