#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include "crawl.h"
#include "download.h"
#include "extract.h"

const char  *log_filename = "other_urls.log";

void crawl(const std::string & url = "info.ruc.edu.cn") {
	std::queue<std::string> wait_url;
	wait_url.push(url);
	std::unordered_map<std::string, bool> scanned_url;
	scanned_url[url] = 1;

	std::ofstream flog(log_filename);
	int cnt = 0;
	while(!wait_url.empty()) {
		download(wait_url.front(), ++cnt);
		extract_url(scanned_url, wait_url, wait_url.front(), cnt);
		wait_url.pop();
	}
}

