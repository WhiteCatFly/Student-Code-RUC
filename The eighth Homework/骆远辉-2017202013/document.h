#ifndef _DOCUMENT_
#define _DOCUMENT_

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<map>
#include<utility>

using namespace std;

class Doc {
private:
	string body;
	string title;
	string url;
	int docID;
public:
	Doc(const string& s,istream& is1,istream& is2,int t) : url(s) , docID(t) {
		stringstream buf1,buf2;
		buf1 << is1.rdbuf();		
		title = buf1.str();
		buf2 << is2.rdbuf();
		body = buf2.str();
	}
	Doc() = default;
	void output(ostream& os) {
		os << url << endl << title << endl;	
	}
};

void add_collection(const string&);

extern int cnt_collection;

#endif
