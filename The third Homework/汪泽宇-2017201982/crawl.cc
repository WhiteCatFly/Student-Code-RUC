#include <cstdlib>
#include <string>
#include <unordered_set>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include "crawl.h"

const char *log_filename = "other_urls.log";

Crawl::Crawl() {
	while(!wait_url_.empty()) wait_url_.pop();
	insertted_url_.clear();
	flog_.open(log_filename);
}


void Crawl::insert(const std::string & url = "info.ruc.edu.cn") {
	wait_url_.push(url);
	insertted_url_.insert(url);
}

void Crawl::run() {
	int cnt = 0;
	while(!wait_url_.empty()) {
		download(++cnt);
		extract_url(wait_url_.front(), cnt);
		wait_url_.pop();
	}
}

void Crawl::download(int cnt) const {
	std::string command = "cd files\nwget -O ";
	std::ostringstream sout(std::ios_base::app);
	sout << cnt << " ";
	command += sout.str() + wait_url_.front();
	system(command.c_str());
}

std::string Crawl::get_cur_dir(std::string url) const {
	size_t slash_pos;
	if((slash_pos = url.rfind("/")) == std::string::npos) return url;
	if(url.rfind(".") == std::string::npos) return url;
	std::cerr << url.erase(slash_pos, url.length() - slash_pos) << std::endl;
	return url;
}

std::string Crawl::get_root_dir(std::string url) const {
	size_t slash_pos;
	if((slash_pos = url.find("/")) == std::string::npos) return url;
	return url.erase(slash_pos, url.length() - slash_pos);
}

extern char *domain_name;

void Crawl::extract_url(const std::string & cur_url, int cnt) {
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
			std::string new_url = newline.substr(pos + len_of_head,
					end_pos - pos - len_of_head);
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
					push(new_url.erase(0, end_pos + len_of_sign));
				}
				else std::cout << new_url << std::endl;
			}
			else if(new_url[0] == '/') {
				push(root_dir + new_url);
			}
			else if(new_url[0] != '.' ||
					(new_url[0] == '.' && new_url[1] == '/')) {
				if(new_url[0] == '.') new_url.erase(0, 2);
				push(cur_dir + "/" + new_url);
//				std::cout << cur_url << std::endl;
//				std::cout << "dir:" << get_dir(cur_url) << std::endl;
			}
			else {
				if(!flog_.is_open()) {
					std::cerr << "other_urls.log is not open\n";
					exit(1);
				}
				flog_ << new_url << std::endl;
			}
		}
	}
}
