#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "include/thulac.h"
using namespace std;

int main()
{
	freopen("check.in", "r", stdin);
	ofstream of("check.out");	
	THULAC x;
	x.init("models/");	
	string str;
	THULAC_result res;
	cin >> str;
	x.cut(str, res);
	for(auto i = res.begin(); i != res.end(); ++i)
	{
	    of << i -> first << " " << i -> second << " ";
	}
	of.close();

	return 0;
}
