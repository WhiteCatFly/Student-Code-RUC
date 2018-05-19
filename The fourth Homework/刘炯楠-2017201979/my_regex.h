#ifndef MY_REGREX_H_INCLUDED
#define MY_REGREX_H_INCLUDED

#include <iostream>
#include <regex>
#include <string>
#include "normalization.h"

static const std::string title_pattern("<title>(.|\n|\r)*?</title>");
static const std::string h_pattern("((<h[1-6]>)|(<h[1-6]\\w(.|\n|\r)*?>))(.|\n|\r)*?</h[1-6]>");
static const std::string p_pattern("((<p>)|(<p\\w(.|.\n|\r)*?)>)(.|\n|\r)*?</p>");
static const std::string url_pattern("<a(.|\n|\r)*?href=(\"|')(.|\n|\r)*?(\"|')(.|\n|\r)*?>(.|\n|\r)*?</a>");

static const std::string p_st_pattern("((<p>)|(<p\\w(.|.\n|\r)*?>))");
static const std::string p_en_pattern("</p>");
static const std::string h_st_pattern("((<h[1-6]>)|(<h[1-6>\\w(.|\n|\r)*?>))");
static const std::string h_en_pattern("</h[1-6]>");
static const std::string url_st_pattern("<a(.|\n|\r)*?href=(\"|')");

const std::string title_start("<title>");
const std::string title_end("</title>");
const std::string html_start("<html>");
const std::string html_end("</html>");
const std::string head_start("<head>");
const std::string head_end("</head>");
const std::string body_start("<body>");
const std::string body_end("</body>");

const char head_sign = 'h';
const char head_range_low = '1';
const char head_range_high = '6';

int get_h(const std::string & content, std::string * & list);
int get_p(const std::string & content, std::string * & list);
int get_url(const std::string & content, std::string * & list, const std::string & now_web_page);
int get_by_regex(const std::string & content, const std::string & pattern, std::string * & list);
std::string get_title(const std::string & content);

bool has_html(const std::string & content);
bool has_head(const std::string & content);
bool has_body(const std::string & content);

#endif
