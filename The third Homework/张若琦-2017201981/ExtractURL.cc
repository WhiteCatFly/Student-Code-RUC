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
	URLS url = URLS(origin_url);

	if (url.check_suf()) return;

	url.filter_blank_character();
	
	if (url.check_pre()) {
		return;
	}

	url.Get_whole_url(root_url,now_url);
	if (url.check_out_site(root_url) || url.check_in_set())
		return;

	url.insert();
	url.push();
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