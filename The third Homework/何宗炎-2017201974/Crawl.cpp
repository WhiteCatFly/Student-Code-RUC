#ifndef Crawl_Hzy_CPP_
#define Crawl_Hzy_CPP_

#include "Hzydef.h"
#include "Web_Crawler.h"

void HzyWebCrawler::Hzy_Crawl(string s) {
	Base_Site = s;
	queue < string > Url_Queue ;
	string temp, tmp;
	Url_Queue.push("");
	while(!Url_Queue.empty()) {
		temp = Url_Queue.front(), Url_Queue.pop();
		Crawl_Web(temp) ;
		tmp = GetFileName(temp) ;
		GetUrlFromWeb(tmp, Url_Queue) ;
	}
}

void HzyWebCrawler::Crawl() {
	for(size_t i = 0; i < seed.size(); ++i)
		Hzy_Crawl(seed[i]);
}

#else
#endif
