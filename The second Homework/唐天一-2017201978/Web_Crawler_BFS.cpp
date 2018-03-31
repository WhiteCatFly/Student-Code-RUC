#include "Web_Crawler.h"
#include <set>
#include <string>
#include <queue>
#include <cstdio>

void Web_Crawler_BFS(const char* crawled_web){
	std::queue<std::string> url_queue;
	while (!url_queue.empty())
		url_queue.pop();
	std::set<std::string> url_set;
	url_set.clear();
	
	std::string origin = crawled_web;
	int total = 0;
	url_queue.push(origin);
	url_set.insert(origin);
	
	while (!url_queue.empty()){
		std::string current_url = url_queue.front(), current_html = "";
		url_queue.pop();
		get_html(current_url, current_html, ++total);
		find_next_url(current_url, current_html, url_queue, url_set, origin);
	}
	
	printf("There are %d websites in %s.\n", total, crawled_web);
}
