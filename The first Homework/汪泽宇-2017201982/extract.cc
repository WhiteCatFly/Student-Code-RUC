#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <set>
#include <sstream>
#include "crawler.h"

void push(std::set<std::string> & scanned_url, std::queue<std::string> & wait_url, const std::string & url) {
	if(scanned_url.find(url) == scanned_url.end()) {
		wait_url.push(url);
		scanned_url.insert(url);
	}
}

std::string get_cur_dir(std::string url) {
	size_t slash_pos;
	if((slash_pos = url.rfind("/")) == std::string::npos) return url;
	if(url.rfind(".") == std::string::npos) return url;
	std::cerr << url.erase(slash_pos, url.length() - slash_pos) << std::endl;
	return url;
}

std::string get_root_dir(std::string url) {
	size_t slash_pos;
	if((slash_pos = url.find("/")) == std::string::npos) return url;
	return url.erase(slash_pos, url.length() - slash_pos);
}

void extract_url(std::set<std::string> & scanned_url, std::queue<std::string> & wait_url, const std::string & cur_url, int cnt) {
	if(cur_url[cur_url.length() - 1] == '/') {
		std::cerr << "the end of cur_url is /\n";
		exit(1);
	}

	std::string filename;
	std::ostringstream sout;
	sout << cnt;
	filename = sout.str();
	std::ifstream fin(filename.c_str());
	if(!fin.is_open()) {
		std::cerr << filename << " is not open\n";
		return;
		exit(1);
	}

	std::string newline;
	size_t pos;
	std::string cur_dir = get_cur_dir(cur_url);
	std::string root_dir = get_root_dir(cur_url);
	while(getline(fin, newline)) {
		pos = 0;
		while((pos = newline.find("<a href=\"", pos)) != std::string::npos) {
			size_t end_pos = newline.find("\"", pos + 9);
			if(end_pos == std::string::npos) {
				break;
				std::cerr << "the next quote is not in this line\n";
				exit(1);
			}
			std::string new_url = newline.substr(pos + 9, end_pos - pos - 9);
			pos = end_pos;
			while(new_url.length() && new_url[new_url.length() - 1] == '/') {
				new_url.pop_back();
			}
			if(!new_url.length()) continue;
			// the standardization of urls still has something to do
			if((end_pos = new_url.find("://")) != std::string::npos) {
				if(new_url.find("info.ruc.edu.cn") != std::string::npos) {
					push(scanned_url, wait_url, new_url.erase(0, end_pos + 3));
				}
				else std::cout << new_url << std::endl;
			}
			else if(new_url[0] == '/') {
				push(scanned_url, wait_url, root_dir + new_url);
			}
			else if(new_url[0] != '.' || (new_url[0] == '.' && new_url[1] == '/')) {
				if(new_url[0] == '.') new_url.erase(0, 2);
				push(scanned_url, wait_url, cur_dir + "/" + new_url);
//				std::cout << cur_url << std::endl;
//				std::cout << "dir:" << get_dir(cur_url) << std::endl;
			}
			else {
				std::ofstream flog("other_urls.log", std::ios_base::app);
				if(!flog.is_open()) {
					std::cerr << "other_urls.log is not open\n";
					exit(1);
				}
				flog << new_url << std::endl;
			}
		}
	}
	/*
	for(int state = 0; ; ) {
		if(!state && (pos = newline.find("<a", pos)) != string::npos) {
			state = 1;
		}
		else if(state == 1 && (pos = newline.find("href", pos)) != string::npos) {
			state = 2;
		}
		else if(state == 2 && (pos = newline.find("=", pos)) != string::npos) {
			state = 3;
		}
		else if(state == 3 && (pos = newline.find("\"", pos)) != string::npos) {
			state = 4;
		}
		else if(state == 4 && 
	*/
}
