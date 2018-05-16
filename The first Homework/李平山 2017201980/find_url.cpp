#include "craw.h"
#include <iostream>
#include <string.h>
#include <set>
#include <queue>

using namespace std;

extern queue<string> Q;
extern set<string> visited;

string add(string temp,string home)
{
	int flag = 0;
	int now = 0;
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

void read(string home)
{
	ifstream fin;
	fin.open("tmp_url.html");
	
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
	
			
			
		        if(res.find("info.ruc.edn.cn") == string::npos)	
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
