#include <string>
#include <set>
#include "DisposeStr.h"

extern std :: set <string> url_set;

bool check_in_set(string url)
{
	if (url_set.count(url))
		return true;
	return false;
}

bool check_css(const string & str)
{
	int url_len = str.size();
	if (url_len >= 4 && str.substr(url_len - 4,4).compare(".css") == 0)
		return true;
	return false;
}

bool check_js(const string & str)
{
	int url_len = str.size();
	if ((url_len >= 3 && str.substr(url_len - 3,3).compare(".js") == 0) ||
		(url_len >= 4 && str.substr(url_len - 4,4).compare(".jsp") == 0))
		return true;
	return false;
}

bool check_suf(const string & str)
{
	if (check_css(str) || check_js(str) || (!check_html(str) && ! check_php(str)))
		return true;
	return false;
}

bool check_pre(const string & url)
{
	int url_len = url.size();
	/*for (int i = 0;i < 3;i ++)
		if (url_len >= url_pre_len[i] && url.substr(0,url_pre_len[i]) == url_pre[i])
		{
			//url.erase(0,url_pre_len[i]);
			return true;
		}*/
	for (auto str : UrlPre)
		if (url_len >= str.len && url.substr(0,str.len) == str.pre)
			return true;

	return false;
}

string filter_blank_character(string url)
{
	int url_len = url.size();
	for (int i = 0;i < url_len;i ++)
		if (url[i] == '\n' || url[i] == '\r' || url[i] == '\n')
		{
			url.erase(i,1);
			url_len --;
		}
	return url;
}

string Get_whole_url(string url,const string & root_url,string now_url)
{
	int url_len = url.size();
	if (url_len > 1 && url.substr(0,2) == "//") // //
	{
		url.erase(0,2);
		return url;
	}
	if (url[0] == '/') // / -> root
	{
		return root_url + url;
	}
	if (url_len > 2 && url.substr(0,3) == "../") // ../
	{
		int ret_opt_num = 0;
		while (url_len > 2 && url.substr(0,3) == "../")
		{
			url_len -= 3;
			ret_opt_num ++;
			url.erase(0,3);
		}

		int now_url_len = now_url.size();
		if (now_url[now_url_len - 1] == '/')
			now_url.erase(-- now_url_len,1);

		for (int i = 0;i < ret_opt_num;i ++)
		{
			int pos = now_url.rfind('/');
			now_url.erase(pos,now_url_len - pos);
			now_url_len = pos;
		}

		return now_url + '/' + url;
	}
	if (url_len > 6 && url.substr(0,7) == "http://")
	{
		url.erase(0,7);
		return url;
	}
	if (url_len > 7 && url.substr(0,8) == "https://")
	{
		url.erase(0,8);
		return url;
	}
	if (url_len >= ROOT_URL_LEN && url.substr(0,ROOT_URL_LEN) == root_url)
	{
		return url;
	}

	int now_url_len = now_url.size();
	if (now_url[now_url_len - 1] == '/')
		now_url.erase(-- now_url_len,1);

	int pos = now_url.rfind('/');
	if (pos != string :: npos)
		now_url.erase(pos,now_url_len - pos);

	return now_url + '/' + url;
}
