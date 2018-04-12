#ifndef CRAWL_SETTING_CHECKER_HZY_CPP_
#define CRAWL_SETTING_CHECKER_HZY_CPP_
#include <bits/stdc++.h>
#include "Web_Crawler.h"
using namespace std;
void HzyWebCrawler::CheckSetting() const {
	printf("The time_interval is %d\n", time_interval);
	puts("We have the seeds below:");
	for(size_t i = 0 ; i < seed.size(); ++i)
		cout << seed[i] << endl;
}

#else
#endif
