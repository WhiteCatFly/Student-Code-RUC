#include <string>
#include <queue>
#include <set>
#include "ExtractURL.h"
#include "DisposeStr.h"
#include "ReadFile.h"

extern std :: queue <string> url_que;
extern std :: set <string> url_set;

void ExtractURL(const string & root_url,const string & now_url,const string & origin_url)
{
	if (check_suf(origin_url)) return;

	string url = filter_blank_character(origin_url);

	/*string tmp_url = check_pre(url);
	if (tmp_url != "")
	{
		return;
	}*/
	if (check_pre(url)) {
		return;
	}

	url = Get_whole_url(url,root_url,now_url);
	if (check_out_site(url,root_url) || check_in_set(url))
		return;

	url_set.insert(url);
	url_que.push(url);
}

void Getfile_and_ExtractURL(const string & root_url,const string & now_url,string & str_file)
{
	str_file = get_file("tmp");

	int url_len = str_file.size(),pos;
	//str_file.resize(url_len + MAXN * MAX_URL_NUM);
	for (int i = 0,j,k;i < url_len;i = k + 1)
	{
		pos = str_file.find("a href",i);
		if (pos == string :: npos)
		{
			break;
		}
		j = str_file.find('"',pos + 4);
		k = str_file.find('"',j + 1);
		string new_url = str_file.substr(j + 1,k - j - 1);
		ExtractURL(root_url,now_url,new_url);
	}
//	return str_file;
}