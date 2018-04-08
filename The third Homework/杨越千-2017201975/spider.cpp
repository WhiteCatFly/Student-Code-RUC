#include <string>
#include "spider.h"
using namespace std;

Spider::Spider()
{
	hash_set.clear();
	index = def_index;
}

Spider::~Spider()
{
	printf("Spider Deleted.\n");
}

void Spider::run(string url, string dom, int sleep_time)
{
	Bfs(url, dom, sleep_time);
}

string Spider::ask_index() const
{
	return this->index;
}

void Spider::set_index(string str)
{
	this->index = str;
}

void Spider::clear()
{
	hash_set.clear();
}
