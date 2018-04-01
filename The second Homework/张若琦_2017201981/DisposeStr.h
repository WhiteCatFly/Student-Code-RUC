#ifndef DisposeStr_H_
#define DisposeStr_H_

using std :: string;

const int ROOT_URL_LEN = 15;

/*const string url_pre[3] = {
	"www.",
	"http://www.",
	"https://www."
};

const int url_pre_len[3] = {
	4,11,12
};*/

const struct url_prefix {
	string pre;
	int len;
} UrlPre[3] = {
	{"www.",4},
	{"http://www.",11},
	{"https://www.",12}
};

bool check_out_site(string url,string root_url);

bool check_in_set(string url);

bool check_php(string str);

bool check_html(string str);

bool check_css(const string & str);

bool check_js(const string & str);

bool check_suf(const string & str);

bool check_pre(const string & url);

string filter_blank_character(string url);

string Get_whole_url(string url,const string & root_url,string now_url);

inline bool check_out_site(string url,string root_url)
{
	if (url.substr(0,ROOT_URL_LEN) != root_url)
		return true;
	return false;
}

inline bool check_php(string str)
{
	if (str.find(".php") != string :: npos)
		return true;
	return false;
}

inline bool check_html(string str)
{
	if (str.find(".html") != string :: npos || str.find(".htm") != string :: npos)
		return true;
	return false;
}

#endif // DisposeStr_H_