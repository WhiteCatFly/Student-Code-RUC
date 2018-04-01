#ifndef BFS_H_
#define BFS_H_

#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <algorithm>

#include "set.h"
#include "findurl.h"

#define string_maxlen 1024
#define string_maxnum 100
#ifndef cmd_maxlen
#define cmd_maxlen 1024
#endif

#define INDEX "index.html"

#define SLEEP_TIME 500000 //0.5s

void Bfs(std::string, std::string);
//#define DEBUG 1

#endif
