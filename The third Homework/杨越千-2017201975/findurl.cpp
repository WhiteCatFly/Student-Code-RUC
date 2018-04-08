#include <string>
#include <cstdio>

#include "spider.h"
using namespace std;

string Spider::MergeUrl(string s1, const string &s2)
{
	int l = s1.length();
	if(s2[0] != '/' && s1[l - 1] != '/') return s1 + '/' + s2;
	if(s2[0] == '/' && s1[l - 1] == '/') s1.erase(l - 1, 1);
	return s1 + s2;
}

bool Spider::IfUrl(string &str, const string &dom)
{
	int str_l = str.length();
	if(!str_l) return 0;
	for(int i = 0;i < str_l; ++i) if(str[i] == ' ' || str[i] == '{' || str[i] == '}' || str[i] == ',') return 0;
	//if(str.find(" ", 0) != string::npos) return 0;
	if(str.find("javascript", 0) != string::npos) return 0;
	size_t fir_pos = str.find("http", 0), sec_pos = str.find("http", fir_pos + 1);
	if(sec_pos == string::npos) sec_pos = str_l;
	size_t dom_pos = str.find(dom, 0);
	if(dom_pos == string::npos || dom_pos >= sec_pos) return 0;
	return 1;
}

int Spider::FindUrl(const string &str, const string &dom, const string &root, string res[])
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

void Spider::FindDir(string str, char* dir)
{
	int str_l = str.length();
	int sum = 0, dir_p = 0, tot = 0;
	static char cmd[cmd_maxlen];
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

void Spider::ModifyUrl(string &str) //ensure main_url end with '/'
{
	int str_l = str.length();
	int sum = 0;
	for(int i = 0;i < str_l; ++i) if(str[i] == '/') sum++;
	if(sum < 3) str.insert(str_l, "/"), str_l++;
	//if(str[str_l - 1] == '/') str.insert(str_l, INDEX);
}

void Spider::FindRoot(string str, string &root)
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
