#include "Web_Crawler.h"
#include <set>
#include <string>
#include <queue>
#include <cstdio>

void find_next_url(const std::string &current_url, const std::string &current_html, std::queue<std::string> &url_queue, std::set<std::string> &url_set, const std::string &origin){
	int url_begin = current_html.find("href=");
	std::string feature_string;
	if (origin.find("info") != origin.npos)
		feature_string = "info.ruc.edu.cn";
	else feature_string = "ruc.edu.cn";
	
	while (url_begin != -1){
		int url_end = current_html.find(current_html[url_begin + 5] == '\"' ? '\"' : '\'', url_begin + 6);
		std::string new_url = current_html.substr(url_begin + 6, url_end - url_begin - 6);
		url_begin = current_html.find("href=", url_end);
		
		if (new_url.find(feature_string) != new_url.npos){
			if (new_url.find("http:") != new_url.npos)
				new_url.erase(0,7);
		}
		else if (new_url.find("http:") == new_url.npos){
				if (new_url[0] == '/')
					new_url = current_url.substr(0, current_url.find_last_of('/') + 1) + new_url.substr(1);
				else new_url = current_url.substr(0, current_url.find_last_of('/') + 1) + new_url;
			}
			
		if (new_url.find(feature_string) != new_url.npos){
			int flag = 0;
			for (int i = 0; sensitive_words[i] != "words_end"; ++i){
				if (new_url.find(sensitive_words[i]) != new_url.npos){
					flag = 1;
					break;
				}
			}
			if (flag)
				continue;
			if (!url_set.count(new_url)){
				url_set.insert(new_url);
				url_queue.push(new_url);
			}
		}
	}
}
