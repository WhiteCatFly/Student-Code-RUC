#ifndef NORMALIZATION_H_INCLUDED
#define NORMALIZATION_H_INCLUDED

#include <string>
 
#ifndef MAXLEN_
#define MAXLEN_
const int MAXLEN = 200;
#endif

#ifndef EXTRA_LEN_
#define EXTRA_LEN_
const int EXTRA_LEN = 50;
#endif

const int ban_num = 8;
const std::string name_head = "webpage/";
const std::string name_tail = ".html";
const std::string ban_str[ban_num] = {"+", "@", "javascript", "ftp://", "file://","twitter","google","webscan"};
const std::string absolute_sign = "http";
const std::string absolute_sign1 = "http://";
const std::string absolute_sign2 = "https://";
const char seperate_sign = '/';
const char end_sign = '\0';

inline static int find_pos(const std::string & page_name);
char * normalize_directory(const std::string & page_name);
char * normalize_file_name(const std::string & page_name);
void normalize_url(std::string & normal_url, const std::string & original_url, const std::string & now_page_name, const std::string & limit_name);

#endif
