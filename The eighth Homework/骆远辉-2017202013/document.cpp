#include"document.h"
#include<fstream>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

int cnt_collection = 0;
map<int,Doc> collection;

void add_collection(const string& tmpp)
{
//	const char* ist = strcat(tmpp,".title");
//	const char* isb = strcat(tmpp,".body");
	string ist = tmpp + ".title" ;
	string isb = tmpp + ".body" ;
	
	cnt_collection++;
	ifstream istitle(ist.c_str());
	ifstream isbody(isb.c_str());	
	Doc tmpdoc(tmpp,istitle,isbody,cnt_collection);
	collection[cnt_collection] = tmpdoc;
}
