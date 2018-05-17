#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <set>
#include <queue>
#include "bfs.h"
#include "find_url.h"
#include "download.h"
#include "normalization.h"

using namespace std;
string limit_name;
int main(int argc,char ** argv) {
	set <string> url_set;
	url_set.clear();
	if ((argc != 2 && argc != 4) || (argc == 4 && strcmp(argv[2],"-l") != 0)) {
		cerr<<"wrong instruction!"<<endl;
		cerr<<"there are two optional ways:"<<endl;
		cerr<<"1 ./web_crawler start_web_page(初始网站)"<<endl;
		cerr<<"2 ./web_crawler start_web_page(初始网站) -l limit_name(限制网页名称)"<<endl;
		return 1;
	}
	string start_web_page;
	if (argc == 2) {
		start_web_page = argv[argc - 1];
		limit_name = start_web_page;
	}
	if (argc == 4) {
		start_web_page = argv[1];
		limit_name = argv[3];
	}
	if (start_web_page.find('/') == -1)start_web_page = start_web_page + '/';
	bfs(url_set, start_web_page);	
}
