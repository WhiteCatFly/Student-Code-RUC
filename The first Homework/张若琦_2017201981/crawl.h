#ifndef CRAWL_H_
#define CRAWL_H_

using std :: string;

static const int MAXN = 1000;

void crawl(const string & root_url);


void Delay();

inline void Delay()
{
	for (int i = 1;i <= 10000000;i ++);
}

#endif // CRAWL_H_