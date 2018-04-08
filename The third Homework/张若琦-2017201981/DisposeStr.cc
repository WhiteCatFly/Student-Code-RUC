#include <string>
#include <set>
#include <queue>
#include "DisposeStr.h"

extern std :: set<string> url_set;
extern std :: queue<string> url_que;

bool URLS :: check_in_set() const
{
	if (url_set.count(url_))
		return true;
	return false;
}

bool URLS :: check_out_site(const string & root_url) const
{
	if (url_.substr(0,ROOT_URL_LEN) != root_url)
		return true;
	return false;
}

bool URLS :: check_php() const
{
	if (url_.find(".php") != string :: npos)
		return true;
	return false;
}

bool URLS :: check_html() const
{
	if (url_.find(".html") != string :: npos || url_.find(".htm") != string :: npos)
		return true;
	return false;
}

bool URLS :: check_css() const
{
	int url_len = url_.size();
	if (url_len >= 4 && url_.substr(url_len - 4,4).compare(".css") == 0)
		return true;
	return false;
}

bool URLS :: check_js() const
{
	int url_len = url_.size();
	if ((url_len >= 3 && url_.substr(url_len - 3,3).compare(".js") == 0) ||
		(url_len >= 4 && url_.substr(url_len - 4,4).compare(".jsp") == 0))
		return true;
	return false;
}

bool URLS :: check_suf() const
{
	if (check_css() || check_js() || (!check_html() && !check_php()))
		return true;
	return false;
}

bool URLS :: check_pre() const
{
	int url_len = url_.size();
	for (auto str : UrlPre)
		if (url_len >= str.len && url_.substr(0,str.len) == str.pre)
			return true;

	return false;
}

void URLS :: filter_blank_character()
{
	int url_len = url_.size();
	for (int i = 0;i < url_len;i ++)
		if (url_[i] == '\n' || url_[i] == '\r' || url_[i] == '\n')
		{
			url_.erase(i,1);
			url_len --;
		}
}

void URLS :: Get_whole_url(const string & root_url,string now_url)
{
	int url_len = url_.size();
	if (url_len > 1 && url_.substr(0,2) == "//") // //
	{
		url_.erase(0,2);
		return;
	}
	if (url_[0] == '/') // / -> root
	{
		url_ = root_url + url_;
		return;
	}
	if (url_len > 2 && url_.substr(0,3) == "../") // ../
	{
		int ret_opt_num = 0;
		while (url_len > 2 && url_.substr(0,3) == "../")
		{
			url_len -= 3;
			ret_opt_num ++;
			url_.erase(0,3);
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

		url_ = now_url + '/' + url_;
		return;
	}
	if (url_len > 6 && url_.substr(0,7) == "http://")
	{
		url_.erase(0,7);
		return;
	}
	if (url_len > 7 && url_.substr(0,8) == "https://")
	{
		url_.erase(0,8);
		return;
	}
	if (url_len >= ROOT_URL_LEN && url_.substr(0,ROOT_URL_LEN) == root_url)
	{
		return;
	}

	int now_url_len = now_url.size();
	if (now_url[now_url_len - 1] == '/')
		now_url.erase(-- now_url_len,1);

	int pos = now_url.rfind('/');
	if (pos != string :: npos)
		now_url.erase(pos,now_url_len - pos);

	url_ =  now_url + '/' + url_;
}

void URLS :: insert()
{
	url_set.insert(url_);
}

void URLS :: push()
{
	url_que.push(url_);
}