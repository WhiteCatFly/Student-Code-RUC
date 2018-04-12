#include "crawl_gethtml.h"

const int INF = 2100000000;

class CRAWL
{
	private:
		URL Root;
		std::string RangeKey;
		std::set<std::string> exist;
		std::queue<URL> Q;
		int FoundPagesNum;
		void bfs(const int &PagesLimit);
	public:
		CRAWL() {}
		CRAWL(const URL &root, const std::string &rangekey);
		void Start(const int &PagesLimit);
		int Get_FoundPagesNum();
};

