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
int main(int argc,const char ** argv) {
	set <string> url_set;
	url_set.clear();

	string start_web_page;
	start_web_page = argv[1];
	if (start_web_page.find('/') == -1)start_web_page = start_web_page + '/';
	order Order = order(argc,argv);
	limit_name = Order.get_limit_name();
	bfs(url_set, start_web_page, Order);	
}
