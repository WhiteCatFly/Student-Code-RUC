#include "craw.h"
#include "standardize.h"
#include <iostream>
#include <string.h>
#include <set>
#include <queue>

using std::string;

extern std::queue<string> Q;
extern std::set<string> visited;
const string fileaddress = "tmp_url.html";
inline bool Esc(const char& s) {return s == '\t' || s == '\n' || s == '\r';}
inline bool is_info(const string& now_url)
{
  	if(now_url.find("info.ruc.edn.cn") == string::npos)	
		return 0;
	else
		return 1;
}
inline void openfile(std::ifstream& fin,const string& filename = fileaddress)
{
	fin.open(fileaddress.c_str());
}
inline string add(const string& temp,string &home_url)
{
	int now = 0;
	int flag  = 0;
	string home = home_url;
	now = home.find("//",now);
	now++;
	while(home.find("/",now+1) != string::npos && home.find("/",now+1) != home.length()-1)
	{
		flag = 1;
		now = home.find("/",now+1);
	}
	if(flag)  home.erase(now,home.length()-now);
	
	if(temp[0] == '/'||home[home.length()-1] == '/')    return home + temp;
	else 	return home+'/'+temp;
	
}

void read(string& home)
{
	std::ifstream fin;
	openfile(fin);
	string res("");
	string str; 
	while(getline(fin,str))
	{
		int len = str.length();
		int now = 0;
		while((now = str.find("<a",now)) != string::npos)
		{
			if((now = str.find("href",now)) == string::npos) continue;
			
			res.clear();
			int state = 0;
			for(;now<=len;now++)
			{
				if(!state)
				{	
					if(str[now] == '\"') state++;
					continue;
				} 
				if(str[now] == '\"') state++;
				if(state>=2) break;
				res += str[now];
			}
		        if(!is_info(res))	
			{
				if(res.find("http:") != string::npos || res.find("www.") != string::npos) continue;
				else res = add(res,home);
			}
			
			if(!visited.count(res) && state>=2)
			{			
				Q.push(res);					
				visited.insert(res);
			}
		}
	}
	fin.close();
}
