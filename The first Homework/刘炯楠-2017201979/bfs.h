#ifndef BFS_H
#define BFS_H

#include<string>
#include<queue>
#include<set>

using namespace std;

static void queue_intialize(queue <string> &url_queue, string start_web_page);
void bfs(string start_web_page, set <string> &url_set);
#endif
