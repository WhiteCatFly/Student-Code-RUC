#include"index.h"
#include<fstream>
#include<iostream>
#include<cstdio>
using namespace std;

int cnt_allword = 0;
map<string,Dict> index_;

void add_index(const string&s,int docID) 
{
	ifstream is(s.c_str());
	
	string tmpword;
cout << s << endl;
	while (is >> tmpword) {
		cnt_allword++;
		if (index_.count(tmpword) == 0) {
			Dict nword(tmpword,docID);
			index_.insert(pair<string,Dict>(tmpword,nword));
			//[tmpword] = nword;	
		}
		else {
			Dict& oword = index_[tmpword];
			oword.add(docID);
		}
	}
}	
