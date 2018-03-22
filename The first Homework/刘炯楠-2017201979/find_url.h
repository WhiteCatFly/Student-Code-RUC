#ifndef FIND_URL_H
#define FIND_URL_H


#include <string>

#define URL_SIGN_LENGTH 8

#ifndef MAXLEN
#define MAXLEN 200
#endif


using namespace std;

const string URL_SIGN = "a href=\"";

static FILE* open_page(string web_page);
int count_url(string now_web_page);
string* get_url(string now_web_page,int url_number);

#endif
