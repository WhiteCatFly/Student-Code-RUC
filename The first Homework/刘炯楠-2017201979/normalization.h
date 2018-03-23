#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include <string>

#define TOP_NAME "info.ruc.edu.cn"

#ifndef MAXLEN
#define MAXLEN 200
#endif

using namespace std;

static int find_pos(string web_page);
char * normalize_directory(string web_page);
char * normalize_file_name(string web_page);
string normalize_url(string original_url, string now_web_page);

#endif
