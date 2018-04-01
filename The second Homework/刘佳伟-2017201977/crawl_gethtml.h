#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <unistd.h>

extern std::set <std::string> exist;
extern std::string RangeKey;

void set_root(const std::string &url);
int get_html(const std::string &url);
int num_of_found_html();
inline int command(std::string order, const std::string &para);
void search_html(const std::string &fatherUrl, std::vector <int> &result);

extern std::string UrlProcess(const std::string &FatherUrl, std::string url);
extern std::string UrlToDirectory(const std::string &url);
extern std::string UrlToFile(const std::string &url);
