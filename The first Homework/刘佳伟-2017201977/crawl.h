#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <unistd.h>
using namespace std;

string UrlProcess(string FatherUrl, string url);
string UrlToDirectory(string url);
string UrlToFile(string url);

void set_root(string url);
int get_html(string url);
int num_of_found_html();
int command(string order, string para);
vector <string> search_html(string fatherUrl);
