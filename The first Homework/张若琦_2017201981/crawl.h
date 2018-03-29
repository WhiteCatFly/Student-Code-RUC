#ifndef __MYCRAWL__
#define __MYCRAWL__

#define MAXN 1000
#define MAX_URL_NUM 3000
#define ROOT_URL_LEN 15

using std :: cin;
using std :: cout;
using std :: endl;
using std :: string;

bool check_out_site(string url,string root_url);

bool check_in_set(string url);

bool check_php(string str);

bool check_html(string str);

bool check_css(string str);

bool check_js(string str);

bool check_suf(string str);

string check_pre(string url);

string filter_blank_character(string url);

void Delay();

string get_file(const char* filename);

string Get_whole_url(string url,string root_url,string now_url);

void ExtractURL(string root_url,string now_url,string origin_url);

string Getfile_and_ExtractURL(string root_url,string now_url);

void crawl(string root_url);

#endif // __MYCRAWL__