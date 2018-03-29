#include"WebCrawler.h"
#include<iostream>
#include<cstring>
#include<queue>
#include<map>
#include<vector>
#include<fstream>
using namespace std;
queue<string> que;
map<string, int> mp;
vector<string> sav;
string stringlo;
int num = 0;
void changetitle(const char urlname[],const char changename[])
{
	string stringhtml = string(urlname);
	int str_len = stringhtml.length();
	string typetitle = "<title>";
	string typeuntitle = "</title>";
	string deltitle = string("-");
	string deltitle2 = string(" ");
	for (int i = 0; i < str_len; i++)
	{
		if (stringhtml.substr(i, 7) == typetitle)
		{
			i += 7;
			for (int j = i; j<str_len; j++)
				if (stringhtml.substr(j, 8) == typeuntitle)
				{
					string urltitle = stringhtml.substr(i, j - i)+to_string(num)+".html";
					int findel = urltitle.find(deltitle);
					while (findel >= 0)
					{
						urltitle.erase(findel, 1);
						findel = urltitle.find(deltitle);
					}
					findel = urltitle.find(deltitle2);
					while (findel >= 0)
					{
						urltitle.erase(findel, 1);
						findel = urltitle.find(deltitle2);
					}
					string urlins = "mv "+string(changename)+" " + urltitle;
					system(urlins.c_str());
					i = str_len; break;
				}
		}
	}
}
void getotherurl(const char urlname[])
{
	string stringhtml = string(urlname);
	//if (num == 10)cout << stringhtml << endl;
	int str_len = stringhtml.length();
	string typehref = "href=";
	string typeunhref = string("\"");
	for (int i = 0; i < str_len; i++)
	{
		if (stringhtml.substr(i, 5) == typehref)
		{
			i += 6;
			for (int j = i; j<str_len; j++)
				if (stringhtml.substr(j, 1) == typeunhref)
				{
					string urlfrom= stringhtml.substr(i, j - i);
					if (urlfrom.find("http://") == -1)
					{
						if (urlfrom.find("/") != 0)
							urlfrom = stringlo + "/" + urlfrom;
						else
							urlfrom = stringlo + urlfrom;
					}
					else
					{
						if (urlfrom.find(stringlo) == -1)
							return;
					}
					if (mp[urlfrom] == 0)
						sav.push_back(urlfrom);
					i = j; break;
				}
		}
	}
}
void gethtml(char urlname[])
{
	string stringurl = string(urlname);
	string instructions = "wget -q -O ";	
	num++;
	cout <<"No:"<<num<<" - "<< "Downloading " << stringurl << "...\n";
	instructions = instructions + to_string(num)+".html" + " " + stringurl;
	string reads = to_string(num) + ".html";
	system(instructions.c_str());
	ifstream fin(reads.c_str());
	char charhtml[8192];
	string stringhtml;
	while (fin.getline(charhtml, 8192))
	{
		stringhtml = stringhtml + string(charhtml);
		strcpy(charhtml, "");
	}
	changetitle(stringhtml.c_str(),reads.c_str());
	//if(num==10)cout << stringhtml << endl;
	getotherurl(stringhtml.c_str());
}
void bfs(char beginurl[])
{
	string urlname = string(beginurl);
	que.push(urlname);
	while (!que.empty())
	{
		string geturl = que.front();
		que.pop();
		if (mp[geturl] == 0)
		{
			vector<string> v2;
			sav.swap(v2);
			mp[geturl]++;
			char charurl[1024];
			strcpy(charurl,geturl.c_str());
			gethtml(charurl);
			for (int i = 0; i < sav.size(); i++)
				que.push(sav[i]);
		}
	}
	cout << "END\n" << endl;
}
void find_url(char urlname[])
{
	string stringurl = string(urlname);
	stringlo = stringurl;
	if (stringurl.substr(0, 7) != "http://")
	{
		printf("Wrong URL\n");
		return;
	}
	cout << urlname << endl;
	bfs(urlname);
}