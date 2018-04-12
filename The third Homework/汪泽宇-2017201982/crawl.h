#ifndef CRAW_H
#define CRAW_H

#include <string>
#include <queue>
#include <unordered_set>
#include <fstream>

void crawl(const std::string &);

class Crawl {
private:
	std::queue<std::string> wait_url_;
	std::unordered_set<std::string> insertted_url_;
	std::ofstream flog_;
	std::string get_cur_dir(std::string) const;
	std::string get_root_dir(std::string) const;
	void download(int) const;
	void extract_url(const std::string &, int cnt);
	inline void push(const std::string & url) {
		if(insertted_url_.find(url) == insertted_url_.end()) {
			wait_url_.push(url);
			insertted_url_.insert(url);
		}
	}

public:
	Crawl();
	~Crawl() {}
	void insert(const std::string &);
	void run();
};

#endif

