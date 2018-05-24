#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "dstring.h"

using namespace std;

int main()
{
	dstring x = string("12320180137245901430");
	string s1 = x.sprint("%4d", 2);
	string s2 = x.sprint("%5d", 17);
	string s3 = x.sprint("%-5d", 17);
	string s4 = x.sprint("%.5d", 17);
	string s5 = x.sprint("%10.5d", 2);
	string s6 = x.sprint("%10.5d", 17);
	string s7 = x.sprint("%-10.5d", 2);
	string s8 = x.sprint("%lf", 2);
	string s9 = x.sprint("%2lf", 2);
	string s10 = x.sprint("%.2lf", 2);
	string s11 = x.sprint("%2.2lf", 2);
	string s12 = x.sprint("%d", 2);
	cout << "s1=" << s1 << endl;
	cout << "s2=" << s2 << endl;
	cout << "s3=" << s3 << endl;
	cout << "s4=" << s4 << endl;
	cout << "s5=" << s5 << endl;
	cout << "s6=" << s6 << endl;
	cout << "s7=" << s7 << endl;
	cout << "s8=" << s8 << endl;
	cout << "s9=" << s9 << endl;
	cout << "s10=" << s10 << endl;
	cout << "s11=" << s11 << endl;
	cout << "s12=" << s12 << endl;
	

	return 0;
}
