#include <cstdio>
#include <set>
#include <string>
#include <queue>
#include "download.h"
#include "find_url.h"
#include "bfs.h"

using namespace std;

static void queue_intialize(queue <string> &url_queue, string start_web_page) {
	while (url_queue.empty() == false)
		url_queue.pop();
	url_queue.push(start_web_page);
}

void bfs(string start_web_page, set <string> &url_set) {
	queue <string> url_queue;
	queue_intialize(url_queue, start_web_page);
	url_set.clear();
	url_set.insert(start_web_page);
	while (url_queue.empty() == false) {
		string now_web_page = url_queue.front();
		url_queue.pop();
		if (now_web_page.length() >= 150 || now_web_page.find("+") != -1)
			continue;
		//cout<<now_web_page<<endl;
		page_download(now_web_page);
		int url_number = count_url(now_web_page);
		string* url_list = get_url(now_web_page,url_number);
		for (int i = 0; i < url_number ; ++i) 
			if (url_list[i] != "") {
				//cout<<url_list[i]<<"!"	<<endl;
				if (url_set.count(url_list[i]) == 0) {
					//cout<<"!"<<endl;
					url_set.insert(url_list[i]);
					url_queue.push(url_list[i]);
				}
			}
	}
}

