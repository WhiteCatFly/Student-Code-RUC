#include <bits/stdc++.h>
#include "Web_Crawler.h"
using namespace std;
int main() {
	HzyWebCrawler c;
	c.InitGlobalSetting();
	c.CheckSetting();
	c.Crawl();
	return 0;
}
