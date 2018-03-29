#ifndef FIND_URL_H
#define FIND_URL_H


#include <string>

const int URL_SIGN_LENGTH = 8;

#ifndef MAXLEN_
#define MAXLEN_
const int maxlen = 200;
#endif

const std::string URL_SIGN = "a href=\"";


inline static FILE* open_page(const std::string web_page);
int count_url(const std::string now_web_page);
void get_url(std::string* & url_list, const std::string now_web_page);

#endif
