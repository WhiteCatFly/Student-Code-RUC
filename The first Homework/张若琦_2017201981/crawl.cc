#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <set>
#include "crawl.h"

std :: queue <string> url_que;
std :: set <string> url_set;

bool check_out_site(string url,string root_url)
{
	if (url.substr(0,ROOT_URL_LEN) != root_url)
		return true;
	return false;
}

bool check_in_set(string url)
{
	if (url_set.count(url))
		return true;
	return false;
}

bool check_php(string str)
{
	if (str.find(".php") != string :: npos)
		return true;
	return false;
}

bool check_html(string str)
{
	int url_len = str.size();
	if (str.find(".html") != string :: npos || str.find(".htm") != string :: npos)
		return true;
	return false;
}

bool check_css(string str)
{
	int url_len = str.size();
	if (url_len >= 4 && str.substr(url_len - 4,4).compare(".css") == 0)
		return true;
	return false;
}

bool check_js(string str)
{
	int url_len = str.size();
	if ((url_len >= 3 && str.substr(url_len - 3,3).compare(".js") == 0) || (url_len >= 4 && str.substr(url_len - 4,4).compare(".jsp") == 0))
		return true;
	return false;
}

bool check_suf(string str)
{
	if (check_css(str) || check_js(str) || (!check_html(str) && ! check_php(str)))
		return true;
	return false;
}

string check_pre(string url)
{
	int url_len = url.size();
	if (url_len > 3 && url.substr(0,4) == "www.")
	{
		url.erase(0,4);
		return url;
	}
	if (url_len > 10 && url.substr(0,11) == "http://www.")
	{
		url.erase(0,11);
		return url;
	}
	if (url_len > 11 && url.substr(0,12) == "https://www.")
	{
		url.erase(0,12);
		return url;
	}
	return "";
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

void Delay()
{
	for (int i = 1;i <= 10000000;i ++);
}

string get_file(const char* filename)
{
	std :: ifstream infile(filename,std :: ios :: in | std :: ios :: binary);
	if (infile)
	{
		string ret;
		infile.seekg(0,std :: ios :: end);
		ret.resize(infile.tellg());
		infile.seekg(0,std :: ios :: beg);
		infile.read(&ret[0],ret.size());
		infile.close();
		return ret;
	}
}

string Get_whole_url(string url,string root_url,string now_url)
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

void ExtractURL(string root_url,string now_url,string origin_url)
{
	if (check_suf(origin_url)) return;

	string url = filter_blank_character(origin_url);

	string tmp_url = check_pre(url);
	if (tmp_url != "")
	{
		return;
	}

	url = Get_whole_url(url,root_url,now_url);
	if (check_out_site(url,root_url) || check_in_set(url))
		return;
	url_set.insert(url);
	url_que.push(url);
}

string Getfile_and_ExtractURL(string root_url,string now_url)
{
	string str_file = get_file("tmp");

	int url_len = str_file.size(),pos;
	//str_file.resize(url_len + MAXN * MAX_URL_NUM);
	for (int i = 0,j,k;i < url_len;i = k + 1)
	{
		pos = str_file.find("a href",i);
		if (pos == -1)
		{
			break;
		}
		j = str_file.find('"',pos + 4);
		k = str_file.find('"',j + 1);
		string new_url = str_file.substr(j + 1,k - j - 1);
		ExtractURL(root_url,now_url,new_url);
	}
	return str_file;
}

void crawl(string root_url)
{
	int cnt = 0;
	char order[MAXN] = {0},now_file[MAXN] = {0};

	url_que.push(root_url);
	url_set.insert(root_url);

	FILE* list_fp = fopen("list.txt","a+");

	while (!url_que.empty())
	{
		string now_url = url_que.front();
		url_que.pop();
		strcpy(now_file,now_url.c_str());

		cnt ++;
		//cout << now_url << endl;
		printf("%s\n",now_url.c_str());

		sprintf(order,"wget -q \"%s\" -O tmp",now_file);
		if (system(order)) // error
		{
			continue;
		}

		string str_file = Getfile_and_ExtractURL(root_url,now_url); // fetch each URL in the current page
 
		fprintf(list_fp,"%4d %s\n",cnt,now_url.c_str());

		if (check_php(now_url))
			sprintf(now_file,"%d.php",cnt);
		else
			sprintf(now_file,"%d.html",cnt);

		FILE* fp = fopen(now_file,"w");
		fprintf(fp,"%s",str_file.c_str());
		fclose(fp);

		Delay();
	}
	cout << "total : " << cnt << endl;
	fclose(list_fp);
}