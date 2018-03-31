#ifndef CRAWING_H
#define CRAWING_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <queue>
#include <stdlib.h>

using std::string;

inline void download_html(const string& current_url);
void url_bfs(const string&);

#endif
