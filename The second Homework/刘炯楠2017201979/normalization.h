#ifndef NORMALIZATION_H_INCLUDED
#define NORMALIZATION_H_INCLUDED

#include <string>

#ifndef MAXLEN_
#define MAXLEN_
const int MAXLEN = 200;
#endif

const int ban_num = 5;
const std::string ban_str[5] = {"+", "@", "javascript", "ftp://", "file://"};

inline static int find_pos(const std::string & web_page);
char * normalize_directory(const std::string & web_page);
char * normalize_file_name(const std::string & web_page);
void normalize_url(std::string & normal_url, const std::string & original_url, const std::string & now_web_page);

#endif
