#include <string>
#include "spider.h"
using namespace std;

void Spider::run(string url, string dom, int sleep_time)
{
	Bfs(url, dom, sleep_time);
}

void Spider::clear()
{
	hash_set.clear();
}
