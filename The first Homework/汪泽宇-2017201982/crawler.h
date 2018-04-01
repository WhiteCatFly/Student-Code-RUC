#ifndef CRAWLER
#define CRAWLER

#include <string>
#include <queue>
#include <set>

void download(const std::string & , int);

void extract_url(std::set<std::string> & ,std::queue<std::string> & , const std::string & , int cnt);

#endif

