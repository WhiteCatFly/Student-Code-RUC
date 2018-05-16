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
int main(int argc,const char ** argv) {
	set <string> url_set;
	url_set.clear();

	string start_web_page;
	start_web_page = argv[1];
	if (start_web_page.find(seperate_sign) == string::npos)start_web_page = start_web_page + seperate_sign;
	order Order = order(argc,argv);
	bfs(url_set, start_web_page, Order);	
}
