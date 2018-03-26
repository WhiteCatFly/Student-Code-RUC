#ifndef URL_GET_HZY_CPP_
#define URL_GET_HZY_CPP_

#include "Url_Get.h"
#include <bits/stdc++.h>
#include "Hzydef.h"
using namespace std;
const string Base_Site = "info.ruc.edu.cn";
const LL seed1 = 277;
const LL seed2 = 311;

set <HashValueSet> WebpageSet;
HashValueSet CalcHashValue(string str)
{
	LL HashValue1 = 0, HashValue2 = 0;
	for(int i = 0; i < str.size(); ++i)
		{
			HashValue1 = HashValue1 * seed1 + str[i];
			HashValue2 = HashValue2 * seed2 + str[i];
		}
	return HashValueSet(HashValue1, HashValue2);
}
bool IfLegal(string & str)
{
	UN LL t = str.find(Base_Site, 0);
	if(t != string::npos) 
		str.erase(0, t + Base_Site.size());
	if(!str.size()) return false;  
	if(str.find("http", 0) != string::npos) return false;
	if(str[0] == '/') str.erase(0, 1);
	HashValueSet v = CalcHashValue(str);
	set<HashValueSet>::iterator p = WebpageSet.find(v);
	if(p != WebpageSet.end()) return false;
	WebpageSet.insert(v);
	cerr << str << endl;
	return true;
}

void FindUrl(string code_str, queue<string> & url, string & temp, size_t & status)
{
	size_t code_l = code_str.size();
	size_t code_p = 0; //a pointer to underline number
	if(status)
		{
			for(; code_p < code_l && status < 3; code_p++)
				{
					if(code_str[code_p] == '\'' || code_str[code_p] == '"') status++;
					else if(!IfESC(code_str[code_p])) temp.push_back(code_str[code_p]);
				}
			if(status >= 3)
				{
					if(IfLegal(temp)) url.push(temp);
					temp.clear();
					status = 0;
				}
			if(code_p >= code_l) return ;
		}  
	while((code_p = code_str.find("href", code_p)) != string::npos)
		{
			status = 1, temp.clear();
			for(; code_p < code_l && status < 3; code_p++)
				{
					if(IfESC(code_str[code_p])) continue;
					else if(IfQuote(code_str[code_p])) status++;
					else if(status == 2) temp.push_back(code_str[code_p]);
				}
			if(status >= 3)
				{
					if(IfLegal(temp)) url.push(temp);
					temp.clear();
					status = 0;
				}
			if(code_p >= code_l) return ;		
		}
	return ;
}

string GetFileName(string s) {
	int n = s.size(), i; string Name("");
	if(s[n - 1] == '/') s.erase(n - 1, 1), n--;
	if(n == 0) Name = "index.html";
	else {
		for(i = n - 1; i >= 0; --i) if(s[i] == '/') break;
		for(++i; i < n; ++i) Name += s[i];
	}
	return Name;
}

void GetUrlFromWeb(const string File_Name, queue <string> & url)
{	
	//freopen(File_Name.c_str(), "r", stdin);
	fstream fin(File_Name.c_str());
	size_t status;
	string temp;
	status = 0;
	temp = ""; // a temporay string to restore url
	string code_s;
	while(getline(fin, code_s))
		FindUrl(code_s, url, temp, status);
	//fclose(stdin);
	//fflush(stdin);
}

#else
#endif


