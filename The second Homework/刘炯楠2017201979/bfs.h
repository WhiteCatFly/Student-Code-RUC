#ifndef BFS_H_INCLUDED
#define BFS_H_INCLUDED

#include <string>
#include <queue>
#include <set>
#include "normalization.h"


inline static void queue_intialize(std::queue <std::string> & url_queue, const std::string & start_web_page);
void bfs(std::set <std::string> & url_set, const std::string & start_web_page);
#endif
