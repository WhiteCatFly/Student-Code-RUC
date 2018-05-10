//<a href=

#include "crawl.h"

using namespace std;

CRAWL::CRAWL(const URL &root, const std::string &rangekey)
{
	Root = root;
	RangeKey = rangekey;
}

void CRAWL::bfs(const int &PagesLimit)
{
	int total = 0;

	exist.insert(Root.GetUrl());
	Q.push(Root);
	
	while(!Q.empty() && total < PagesLimit)
	{
		URL F_URL = Q.front();
		Q.pop();
		
		HTML F(F_URL);
		if(F.DownloadSucceed() && F.ReadFromFile())
		{
			//cerr << "wuof23uuwu30f9wiwfa" << endl;
			total ++;
		
			URL NewHref = F.GetNextHref();
			string NewHrefStr = NewHref.GetUrl();
			while(NewHrefStr != HTMLEND)
			{
				if(NewHrefStr != "" && NewHrefStr.find(RangeKey) != string::npos && !exist.count(NewHrefStr))
				{
					exist.insert(NewHrefStr);
					Q.push(NewHref);
				}
				NewHref = F.GetNextHref();
				NewHrefStr = NewHref.GetUrl();
			}
			cerr << "Succeed." << endl;
		}
		else
			cerr << "Failed!!!" << endl;
			
		cerr << "********************Process********************" << endl << "    Downloaded: " << total << endl << "    Detected: " << exist.size() << endl << "    Target: ";
		if(PagesLimit == INF)
			cerr << "oo" << endl;
		else
			cerr << PagesLimit << endl;
		cerr << "***********************************************" << endl << endl;
	}
}

void CRAWL::Start(const int &PagesLimit)
{
	bfs(PagesLimit);
}

int main()
{

	string starturl, rangekey;
	int limit;

	cout << "Input the StartUrl: ";
	cin >> starturl;

	cout << "Input the RangeKey: ";
	cin >> rangekey;
	
	cout << "Input the PagesLimit(0 means NO Limit): ";
	cin >> limit;
	
	URL root(starturl);
	
	CRAWL crawl(root, rangekey);
	crawl.Start(limit == 0 ? INF : limit);
	
	return 0;
}
