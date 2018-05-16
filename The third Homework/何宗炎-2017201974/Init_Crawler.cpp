#ifndef INIT_CRAWLER_HZY_CPP_
#define INIT_CRAWLER_HZY_CPP_
#include <bits/stdc++.h>
#include "Hzydef.h"
#include "Web_Crawler.h"
#define ILEGAL() puts("Please input legal data!");
using namespace std;
HzyWebCrawler::HzyWebCrawler(vector< string > dseed, int dtime_interval = 100000) {
	seed.clear();
	for(size_t i = 0; i < dseed.size(); ++i)
		seed.push_back(dseed[i]);
	time_interval = dtime_interval;
}

void HzyWebCrawler::InitGlobalSetting() {
	seed.clear(), time_interval = 100000;
	int tmp, temp;
	string s, ss;
	puts("How to initialize the crawler ?");
	puts("1.stdin   2.files");
	scanf("%d", &tmp) ;
	while(tmp != 1 && tmp != 2) {
		ILEGAL();
		scanf("%d", &tmp) ;
	}
	if(tmp == 1) {
		puts("Please input time_interval(0 ~ 2147483647)");
		scanf("%d", &temp);
		while(temp < 0) {
			ILEGAL();
			scanf("%d", &temp);
		}
		time_interval = temp;
		
		puts("Please input crawl seeds (with the $$ ends)");
		do {
			cin >> s;
			if(s == "$$") break;
			seed.push_back(s);
		}while(s != "$$");
	}
	else {
		puts("Please input the file name");
		cin >> s;
		fstream fin(s.c_str());
		fin >> temp;
		if(temp < 0) {
			ILEGAL();
			exit(0);
		}
		time_interval = temp;
		
		while(fin >> ss) seed.push_back(s);
	}
}

#else
#endif
		
