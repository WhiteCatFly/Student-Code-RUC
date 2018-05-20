#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#include "dstring.h"

using namespace std;

static string space(int len, int ops = 0)
{
	string str("");
    for(int i = 0;i < len; ++i) str += ops ? "0" : " ";
	return str;
}

string dstring::sprint(const std::string& str, int pos) const
{
	int str_len = str.length(), last = 0;
	vector<int> vpos;
	vpos.clear();
	while(str.find("%", last) != string::npos) last = str.find("%", last) + 1, vpos.push_back(last - 1);
	vpos.push_back(str_len);
	int vlen = vpos.size();
	string form(""), res(""), tmp("");
	for(int i = 0;i < vlen - 1; ++i)
	{
		form = str.substr(vpos[i] + 1, vpos[i + 1] - vpos[i]);
		int flen = form.length(), tot_num = 0, str_num = 0, ops = 0;
		bool lef = 0, dot = 0;
		if(form.find("d") != string::npos) ops = 0;
		else if(form.find("f") != string::npos) ops = 1;
		
		for(int j = 0;j < flen; ++j)
		{
			if(form[j] == '-') lef = 1;
			if(form[j] == '.') dot = 1;
			if(form[j] >= '0' && form[j] <= '9')
			{
				if(dot) str_num = str_num * 10 + form[j] - '0';
				else tot_num = tot_num * 10 +form[j] - '0';
			}
		}
		int sel_len = length();
		if(!ops) //%d
		{
			if(dot&&!str_num) str_num = sel_len;
			if(!dot&&!str_num)
			{
				if(tot_num > 0) str_num = tot_num, tot_num = 0;
				else str_num = sel_len - pos;
			}
			tmp = substr(pos, pos + str_num - 1 < sel_len ? str_num : string::npos);
			if((int)tmp.length() < str_num) tmp = space(str_num - (int)tmp.length(), dot) + tmp;
		    if(tot_num > str_num)
			{
				if(lef) res += tmp + space(tot_num - str_num, 0);
				else res += space(tot_num - str_num, 0) + tmp;
			}
			else res += tmp;
			pos += str_num;
			if(pos >= sel_len) break;
		}
		else //%lf
		{
			if(!str_num) str_num = 6;
			if(!tot_num) tot_num = sel_len - pos;
			res += substr(pos, pos + tot_num - 1 < sel_len ? tot_num : string::npos) + "." + space(str_num, 1);
			break;
		}
	}
	return res;
}
