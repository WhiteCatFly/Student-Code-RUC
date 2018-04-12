#include <queue>
#include <string>
#include <set>
#include <fstream>
#include "crawler.h"

int main() {
	const std::string seed_url("info.ruc.edu.cn");
	std::queue<std::string> wait_url;
	wait_url.push(seed_url);
	std::set<std::string> scanned_url;
	scanned_url.insert(seed_url);

	std::ofstream flog("other_urls.log");
	int cnt = 0;
	while(!wait_url.empty()) {
		download(wait_url.front(), ++cnt);
		extract_url(scanned_url, wait_url, wait_url.front(), cnt);
		wait_url.pop();
	}
	return 0;
}
