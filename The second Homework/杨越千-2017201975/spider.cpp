#include<set>
#include<queue>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <unistd.h>
#define mk_pr(x,y) make_pair((x),(y))
#define nn 1000002
#define string_maxlen 1024
#define string_maxnum 100
#define cmd_maxlen 1024
#define ULL unsigned long long
#define INDEX "index.html"
#define SLEEP_TIME 500000 //0.5s
//#define DEBUG 1
using namespace std;

const int SEED = 257, SEED2 = 263;
char str[nn];
string s,t[nn];
set<pair<ULL, ULL> > hash_set;

string MergeUrl(string s1, string s2)
{
	int l = s1.length();
	if(s2[0] != '/' && s1[l - 1] != '/') return s1 + '/' + s2;
	if(s2[0] == '/' && s1[l - 1] == '/') s1.erase(l - 1, 1);
	return s1 + s2;
}

bool IfUrl(string &str, string dom)
{
	int str_l = str.length();
	if(!str_l) return 0;
	for(int i = 0;i < str_l; ++i) if(str[i] == ' ' || str[i] == '{' || str[i] == '}') return 0;
	//if(str.find(" ", 0) != string::npos) return 0;
	if(str.find("javascript", 0) != string::npos) return 0;
	size_t fir_pos = str.find("http", 0), sec_pos = str.find("http", fir_pos + 1);
	if(sec_pos == string::npos) sec_pos = str_l;
	size_t dom_pos = str.find(dom, 0);
	if(dom_pos == string::npos || dom_pos >= sec_pos) return 0;
	return 1;
}

bool IfEsc(char s) {return s == '\t' || s == '\n' || s == '\r'; }

int FindUrl(string str, string dom, string root, string res[])
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
			if(temp.find("http", 0) == string::npos) temp = MergeUrl(root, temp);
			if(IfUrl(temp, dom)) res[res_sum++] = temp;
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
			if(temp.find("http", 0) == string::npos) temp = MergeUrl(root, temp);
			if(IfUrl(temp, dom)) res[res_sum++] = temp;
			temp.clear();
			temp_len = state = 0;
		}
		if(str_p >= str_l) return res_sum;		
	}
	return res_sum;
}

void FindDir(string str, char* dir)
{
	int str_l = str.length();
	int sum = 0, dir_p = 0, tot = 0;
	char cmd[cmd_maxlen];
	bool dir_anc = 0;
	memset(cmd, 0, sizeof(0));
	for(int i = 0;i < str_l; ++i) if(str[i] == '/') tot++;
	for(int i = 0;i < str_l; ++i)
	{
		if(sum >= 2) dir[dir_p++] = str[i];
		if(str[i] == '/') sum++;
		if(sum >= 2 && sum == tot && !dir_anc)
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
	ULL hs = 0, hs2 = 0;
	for(int i = 0;i < str_l; ++i) hs = hs * SEED + (ULL)str[i], hs2 = hs2 * SEED2 + (ULL)str[i];
	if(hash_set.find(mk_pr(hs, hs2)) != hash_set.end()) return 1;
	else return hash_set.insert(mk_pr(hs, hs2)), 0;
}

void ModifyUrl(string &str) //ensure main_url end with '/'
{
	int str_l = str.length();
	int sum = 0;
	for(int i = 0;i < str_l; ++i) if(str[i] == '/') sum++;
	if(sum < 3) str.insert(str_l, "/"), str_l++;
	//if(str[str_l - 1] == '/') str.insert(str_l, INDEX);
}

void FindRoot(string str, string &root)
{
	int str_l = str.length();
	int sum = 0;
	string temp("");
	for(int i = 0;i < str_l; ++i)
	{
		if(str[i] == '/') sum++;
		if(sum >= 3)
		{
			temp.insert(0, str, 0, i); //don't include end '/'
			root = temp;
			return;
		}
	}
}

void Bfs(string root, string dom)
{
	queue<string> bfs_Q;
	while(!bfs_Q.empty()) bfs_Q.pop();
	bfs_Q.push(root);
	char cmd[cmd_maxlen], dir[cmd_maxlen];
	char str[string_maxlen];
	memset(cmd, 0, sizeof(cmd)), memset(dir, 0, sizeof(dir)), memset(str, 0, sizeof(str));
	string url, s0, res[string_maxnum];
	int res_sum = 0, url_len = 0, url_tot = 0, dir_len = 0;
	FILE* f;
	int num = 0;
	while(!bfs_Q.empty())
	{
		url = bfs_Q.front(), bfs_Q.pop(), url_tot++;
		cout<< url_tot << " " << url << endl;
		memset(dir, 0, sizeof(dir));
		memset(cmd, 0, sizeof(cmd));
		ModifyUrl(url);
		FindRoot(url, root);
		
		FindDir(url, dir);
		dir_len = strlen(dir);
		if(dir[dir_len - 1] == '/') sprintf(dir + dir_len, "%s", INDEX);
		sprintf(cmd, "wget -q -O '%s' '%s' -T 10 -t 2", dir, url.c_str());
		system(cmd);
		if(url_tot % 10 == 0) usleep(SLEEP_TIME);
		
		if((f = fopen(dir, "r")) == NULL) continue;
		#ifdef DEBUG
		int deb = 0;
		#endif
		while(fgets(str, 1024, f) != NULL)
		{
			#ifdef DEBUG
			deb++;
			#endif
			s0 = str;
			res_sum = FindUrl(s0, dom, root, res);
			for(int i = 0;i < res_sum;++i)
				if(!IfMulti(res[i]))
				{
					bfs_Q.push(res[i]);
					//cout << ++num << " " << res[i] << endl; //log
				}
		}
		fclose(f);
	}
}

int main()
{
	string url = "http://www.ruc.edu.cn/";
	string dom = "ruc.edu.cn"; //domain name
	Bfs(url, dom);
	
	return 0;
}
