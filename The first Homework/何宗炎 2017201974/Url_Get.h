#ifndef URL_GET_HZY_H_
#define URL_GET_HZY_H_
#include "Hzydef.h"
#include <bits/stdc++.h>
#define MergeUrl(s1, s2) (s1 + s2)
#define IfESC(c) (c == '\t' || c == '\n' || c == '\r')
#define IfQuote(c) (c == '\'' || c == '"')
using namespace std;
struct HashValueSet {
	LL Value1, Value2;
	HashValueSet(LL v1, LL v2) : Value1(v1), Value2(v2) {}
	bool operator < (const HashValueSet p) const {
		if(Value1 == p.Value1) return Value2 < p.Value2;
		else return Value1 < p.Value1;
  }
};

HashValueSet CalcHashValue(string str) ;
bool IfLegal(string & str);
void FindUrl(string code_str, queue<string> & url, string & temp, size_t & status);
string GetFileName(string s);
void GetUrlFromWeb(const string File_Name, queue <string> & url);



#else
#endif
