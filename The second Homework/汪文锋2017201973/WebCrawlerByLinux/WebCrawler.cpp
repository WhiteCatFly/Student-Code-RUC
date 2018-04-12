#include"WebCrawler.h"
#include"url.h"
#include"finread.h"
#include<iostream>
#include<cstring>
#include<queue>
#include<map>
#include<vector>
#include<fstream>
using namespace std;
queue<url> que;
map<string, int> mp;
vector<string> sav;
int num = 0;
void bfs(string beginurl)
{
	que.push(url(beginurl,"",++num));
	while (!que.empty())
	{
		url gurl = que.front();
		que.pop();
		//if (mp[gurl.geturl()] == 0)
		//{
			vector<string> v2;
			sav.swap(v2);
			mp[gurl.geturl()]++;
			ifstream fin = gurl.downloadurl();
			gurl = ioreader(fin,gurl);
			gurl.getitle();
			gurl.getotherurl(sav);
			for (int i = 0; i < sav.size(); i++)
			{
				url turl = url(gurl.gethost(), sav[i], num);
				if ((sav[i].find(gurl.gethost()) != -1 || sav[i].find(gurl.setting.findhttp) == -1) && mp[turl.geturl()] == 0)
				{
					mp[turl.geturl()]++;
					que.push(url(gurl.gethost(), sav[i], ++num));
				}
			}
		//}
	}
	cout << "The project is ending , It 's craw " << num << " webs" << endl;
	deldust();
}