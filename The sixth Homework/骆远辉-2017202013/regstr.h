#ifndef REGSTR_
#define REGSTR_
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include"string.h"

class Regstr : public String {
public:
	Regstr(const String& s,const String& mode);
	~Regstr() { delete [] rstr_; }
	char* getrstr() {return rstr_;}
private:
	char *rstr_;
};

#endif


