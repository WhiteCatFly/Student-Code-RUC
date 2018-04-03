#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <queue>
#include "download.h"
#include "find_url.h"
#include "bfs.h"
#include "normalization.h"

using namespace std;

inline static void queue_intialize(queue <string> &url_queue, const string & start_web_page) {
	while (url_queue.empty() == false)
		url_queue.pop();
	url_queue.push(start_web_page);
}

void bfs(set <string> &url_set, const string & start_web_page, const order & Order) {
	string limit_name = Order.get_limit_name();
	queue <string> url_queue;
	queue_intialize(url_queue, start_web_page);
	url_set.clear();
	url_set.insert(start_web_page);
	while (url_queue.empty() == false) {
		string now_web_page = url_queue.front();
		url_queue.pop();
		if (now_web_page.length() >= MAXLEN)
			continue;
		bool ban_flag = false;
		for (int i = 0; i < ban_num; ++i)
			if (now_web_page.find(ban_str[i]) != std::string::npos)
				ban_flag = true;
		if (ban_flag) continue;
		if (now_web_page.find(limit_name) == std::string::npos)
			continue;
		Order.download(now_web_page);
		int url_number = count_url(now_web_page);
		string* url_list = new string[url_number];
		get_url(url_list, now_web_page, limit_name);
		for (int i = 0; i < url_number ; ++i) 
			if (url_list[i] != "") {
				if (url_set.count(url_list[i]) == 0) {
					url_set.insert(url_list[i]);
					url_queue.push(url_list[i]);
				}
			}
		delete[] url_list;
	}
}
