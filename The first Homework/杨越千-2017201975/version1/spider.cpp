#include<set>
#include<queue>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <unistd.h>
#define nn 1000002
#define string_maxlen 1024
#define string_maxnum 100
#define cmd_maxlen 1024
#define ULL unsigned long long
#define INDEX "index.php"
#define SLEEP_TIME 500000 //0.5s
using namespace std;

const int SEED = 257;
char str[nn];
string s,t[nn];
set<ULL> hash_set;

string MergeUrl(string s1, string s2)
{
	if(s2[0] != '/') return s1 + '/' + s2;
	else return s1 + s2;
}

bool IfUrl(string &str, string root)
{
	int str_l = str.length();
	if(!str_l) return 0;
	if(str_l == 1)
	{
		if((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')) return 1;
		else return 0;
	}
	for(int i = 0;i < str_l; ++i) if(str[i] == ' ') return 0;
	
	size_t p = str.find("http", 0);
	if(p != string::npos)
	{
		if(str.find(root, 0) != string::npos)
		{
			str.erase(0, 22);
			return 1;
		}
		else return 0;
	}
	if(str.find("javascript", 0) != string::npos) return 0;
	if(str[0] == '/' && str[1] == '/') return 0;
	return 1;
}

bool IfEsc(char s) {return s == '\t' || s == '\n' || s == '\r'; }

int FindUrl(string str, string root, string res[])
{
	size_t str_l = str.length(), res_sum = 0;
	static size_t temp_len = 0, state = 0; //state = 0:no href, 1:no first ', 2:no last '
	static string temp("");
	size_t str_p = 0;
	if(state)
	{
		for(;str_p < str_l && state < 3;str_p++)
		{
			if(str[str_p] == '\'' || str[str_p] == '"') state++;
			else if(!IfEsc(str[str_p])) temp.insert(temp_len, str, str_p, 1), temp_len++;
		}
		if(state >= 3)
		{
			if(IfUrl(temp, root)) res[res_sum++] = temp;
			temp.clear();
			temp_len = state = 0;
		}
		if(str_p >= str_l) return res_sum;
	}
	
	while((str_p = str.find("href", str_p)) != string::npos)
	{
		state = 1, temp_len = 0;
		for(;str_p < str_l && state < 3;str_p++)
		{
			if(IfEsc(str[str_p])) continue;
			else if(str[str_p] == '\'' || str[str_p] == '"') state++;
			else if(state == 2) temp.insert(temp_len, str, str_p, 1), temp_len++;
		}
		if(state >= 3)
		{
			if(IfUrl(temp, root)) res[res_sum++] = temp;
			temp.clear();
			temp_len = state = 0;
		}
		if(str_p >= str_l) return res_sum;		
	}
	return res_sum;
}

void FindDict(const char* str, char* dir)
{
	int str_l = strlen(str);
	int sum = 0, tot = 0, dir_p = 0;
	char cmd[cmd_maxlen];
	bool dir_anc = 0;
	memset(cmd, 0, sizeof(0));
	for(int i = 0;i < str_l; ++i) if(str[i] == '/') tot++;
	for(int i = 0;i < str_l; ++i)
	{
		if(sum >= 3) dir[dir_p++] = str[i];
		if(str[i] == '/') sum++;
		if(sum >= 3 && sum == tot && !dir_anc)
		{
			dir_anc = 1;
			if(dir[0] != '\0')
			{
				sprintf(cmd, "mkdir -p %s", dir);
				system(cmd);
			}
		}
	}
	dir[dir_p] = '\0';
}

bool IfMulti(string str)
{
	int str_l = str.length();
	ULL hs = 0;
	for(int i = 0;i < str_l; ++i) hs = hs * SEED + (ULL)str[i];
	if(hash_set.find(hs) != hash_set.end()) return 1;
	else return hash_set.insert(hs), 0;
}

void Bfs(string root)
{
	queue<string> bfs_Q;
	while(!bfs_Q.empty()) bfs_Q.pop();
	bfs_Q.push(root);
	char cmd[cmd_maxlen], dir[cmd_maxlen];
	char str[string_maxlen];
	memset(cmd, 0, sizeof(cmd)), memset(dir, 0, sizeof(dir)), memset(str, 0, sizeof(str));
	string url, s0, res[string_maxnum];
	int res_sum = 0, url_len = 0, url_tot = 0;
	FILE* f;
	int num = 0;
	IfMulti(INDEX);
	while(!bfs_Q.empty())
	{
		url = bfs_Q.front(), bfs_Q.pop(), url_tot++;
		memset(dir, 0, sizeof(dir));
		memset(cmd, 0, sizeof(cmd));
		url_len = url.length();
		if(url[url_len - 1] == '/') url.insert(url_len, INDEX);
		
		FindDict(url.c_str(), dir);
		if(dir[0] == '\0') sprintf(dir, INDEX); //first html
		sprintf(cmd, "wget -q -O '%s' '%s'", dir, url.c_str());
		system(cmd);
		if(url_tot % 10 == 0) usleep(SLEEP_TIME);
		
		if((f = fopen(dir, "r")) == NULL) continue;
		while(fgets(str, 1024, f) != NULL)
		{
			s0 = str;
			res_sum = FindUrl(s0, root, res);
			for(int i = 0;i < res_sum;++i)
				if(!IfMulti(res[i]))
				{
					bfs_Q.push(MergeUrl(root, res[i]));
					cout<<++num<<" "<<res[i]<<endl; //log
				}
		}
		fclose(f);
	}
}

int main()
{
	string url = "http://info.ruc.edu.cn";
	Bfs(url);
	
	return 0;
}
