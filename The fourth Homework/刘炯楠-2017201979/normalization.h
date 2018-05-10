#ifndef NORMALIZATION_H_INCLUDED
#define NORMALIZATION_H_INCLUDED

#include <string>

const std::string absolute_sign = "http";
const std::string absolute_sign1 = "http://";
const std::string absolute_sign2 = "https://";
const char seperate_sign = '/';

inline static int find_pos(const std::string & web_page);
void normalize_url(std::string & normal_url, const std::string & original_url, const std::string & now_web_page);

#endif
