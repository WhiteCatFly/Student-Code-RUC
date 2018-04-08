#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <unistd.h>

std::set <std::string> exist;
std::queue <std::string> Q;
std::string RangeKey;

void bfs(const std::string &root, const int &PagesLimit);

extern void set_root(const std::string &url);
extern int get_html(const std::string &url);
extern void search_html(const std::string &fatherUrl, std::vector <std::string> &result);
extern int num_of_found_html();
