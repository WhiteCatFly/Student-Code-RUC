#include <cstdlib>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "extract.h"

inline void push(std::unordered_map<std::string, bool> & scanned_url, std::queue<std::string> & wait_url, const std::string & url) {
	if(scanned_url.find(url) == scanned_url.end()) {
		wait_url.push(url);
		scanned_url[url] = 1;
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

extern char *log_filename;
extern char *domain_name;

void extract_url(std::unordered_map<std::string, bool> & scanned_url, std::queue<std::string> & wait_url, const std::string & cur_url, int cnt) {
	if(cur_url[cur_url.length() - 1] == '/') {
		std::cerr << "the end of cur_url is /\n";
		exit(1);
	}

	std::string filename;
	std::ostringstream sout;
	sout << "./files/" << cnt;
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
		const static char *head_of_url = "<a href=\"";
		const static int len_of_head = 9;
		while((pos = newline.find(head_of_url, pos)) != std::string::npos) {
			size_t end_pos = newline.find("\"", pos + len_of_head);
			if(end_pos == std::string::npos) {
				break;
				std::cerr << "the next quote is not in this line\n";
				exit(1);
			}
			std::string new_url = newline.substr(pos + len_of_head, end_pos - pos - len_of_head);
			pos = end_pos;
			while(new_url.length() && new_url[new_url.length() - 1] == '/') {
				new_url.pop_back();
			}
			if(!new_url.length()) continue;
			// the standardization of urls still has something to do
			const static char *sign_of_abs_url = "://";
			const static int len_of_sign = 3;
			if((end_pos = new_url.find(sign_of_abs_url)) != std::string::npos) {
				if(new_url.find(domain_name) != std::string::npos) {
					push(scanned_url, wait_url, new_url.erase(0, end_pos + len_of_sign));
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
				std::ofstream flog(log_filename, std::ios_base::app);
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
